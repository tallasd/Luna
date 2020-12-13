#pragma once
#include <tesla.hpp>
#include <cstdio>
#include <vector>
#include <string>

namespace tsl
{
    namespace elm
    {
        class LogElement : public Element {
        public:

            LogElement(std::string text) {
                this->m_text = text;
            }

            virtual ~LogElement() {}

            virtual void draw(gfx::Renderer *renderer) override {
                    renderer->drawString(this->m_text.c_str(), false, this->getX() + 18, this->getY() + 18, 16, renderer->a(tsl::style::color::ColorText));
                }

            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                    this->setBoundaries(this->getX(), this->getY(), this->getWidth(), 20);
                }


        protected:
            std::string m_text = "";
        
        };


        /**
        * @brief An UI Element for logging text
        */
        class Log : public Element {
        public:

            /**
             * @brief Constructor
             * 
             * @param s32 maxlogheight : the max amount of lines displayed by the log 
             */
            Log(s32 maxlogheight) {
                //maxlogheight in lines, 1 line a 20 pixels
                this->m_maxheight = maxlogheight * 20;
            }

            /**
            * @brief Destructor
            */
            virtual ~Log() {
                for (auto& entry : this->logtxt)
                    delete entry;
            }


            virtual void draw(gfx::Renderer* renderer) override {

                for (auto &entry : this->m_itemsToAdd) {
                    entry->invalidate();
                    this->logtxt.push_back(entry);
                    this->invalidate();
                    this->updateScrollOffset();
                }
                this->m_itemsToAdd.clear();

                if (this->m_scrolling) {
                    ScrollDown();
                    this->m_scrolling = false;
                }


                renderer->enableScissoring(this->getLeftBound(), this->getTopBound() - 5, this->getWidth(), this->getHeight() + 4);


                for (auto& entry : this->logtxt) {
                    if (entry->getBottomBound() > (this->getTopBound() - 20) && entry->getTopBound() < (this->m_maxheight + this->getBottomBound())) {
                        entry->frame(renderer);
                    }
                }

                renderer->disableScissoring();

                if (this->m_listHeight > this->m_maxheight) {
                    float scrollbarHeight = static_cast<float>(this->m_maxheight * this->m_maxheight) / this->m_listHeight;
                    float scrollbarOffset = 10 + ((static_cast<double>(this->m_offset)) / static_cast<double>(this->m_listHeight - this->m_maxheight) * (this->m_maxheight - std::ceil(scrollbarHeight)));

                    renderer->drawRect(this->getRightBound() - 20, this->getY() + scrollbarOffset, 5, scrollbarHeight - 50, a(tsl::style::color::ColorHandle));
                    renderer->drawCircle(this->getRightBound() - 18, this->getY() + scrollbarOffset, 2, true, a(tsl::style::color::ColorHandle));
                    renderer->drawCircle(this->getRightBound() - 18, this->getY() + scrollbarOffset + scrollbarHeight - 50, 2, true, a(tsl::style::color::ColorHandle));

                    float prevOffset = this->m_offset;

                    if (Element::getInputMode() == InputMode::Controller)
                        this->m_offset += ((this->m_nextOffset) - this->m_offset) * 0.1F;
                    else if (Element::getInputMode() == InputMode::TouchScroll)
                        this->m_offset += ((this->m_nextOffset) - this->m_offset);

                    if (static_cast<u32>(prevOffset) != static_cast<u32>(this->m_offset))
                        this->invalidate();
                }
            }

            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX(), this->getY(), this->getWidth(), this->m_maxheight - 5);

                s32 y = this->getY() - this->m_offset - 10;

                this->m_listHeight = 0;
                for (auto& entry : this->logtxt)
                    this->m_listHeight += entry->getHeight();

                for (auto& entry : this->logtxt) {
                    entry->setBoundaries(this->getX(), y, this->getWidth(), entry->getHeight());
                    entry->invalidate();
                    y += entry->getHeight();
                }
            }

            virtual bool onTouch(TouchEvent event, s32 currX, s32 currY, s32 prevX, s32 prevY, s32 initialX, s32 initialY) {

                // Discard touches out of bounds
                if (!this->inBounds(currX, currY))
                    return false;

                // Handle scrolling
                if (event != TouchEvent::Release && Element::getInputMode() == InputMode::TouchScroll) {
                    if (prevX != 0 && prevY != 0)
                        this->m_nextOffset += (prevY - currY);

                    if (this->m_nextOffset < 0)
                        this->m_nextOffset = 0;

                    if (this->m_nextOffset > (this->m_listHeight - this->m_maxheight))
                        this->m_nextOffset = (this->m_listHeight - this->m_maxheight);

                    return true;
                }

                return false;
            }

            /**
            * @brief adds a line to the log
            * 
            * @param string text : text to be added
            * @param bool scroll : true if you want to scroll, when you add an element. true by default.
            */
            virtual void addLine(std::string text, bool scroll = true) {
                LogElement *newLogElement = new LogElement(text);
                if (newLogElement != nullptr) {
                    if(newLogElement->getHeight() != 0)
                        newLogElement->setBoundaries(this->getX(), this->getY(), this->getWidth(), newLogElement->getHeight());

                    newLogElement->setParent(this);
                    newLogElement->invalidate();

                    this->m_itemsToAdd.push_back(newLogElement);
                    if (scroll) this->m_scrolling = scroll;
                }
            }

            virtual void ScrollDown() {
                this->m_nextOffset = (this->m_listHeight - this->m_maxheight);
                this->invalidate();
                this->updateScrollOffset();
            }

            virtual void ScrollUp() {
                this->m_nextOffset = 0;
                this->invalidate();
                this->updateScrollOffset();
            }

        protected:
            std::vector<LogElement*> logtxt;

            float m_offset = 0, m_nextOffset = 0;
            s32 m_listHeight = 0;
            s32 m_maxheight = 0;

            bool m_scrolling = false;

            std::vector<LogElement*> m_itemsToAdd;



        private:

            virtual void updateScrollOffset() {
                if (this->getInputMode() != InputMode::Controller)
                    return;

                if (this->m_listHeight <= this->m_maxheight) {
                    this->m_nextOffset = 0;
                    this->m_offset = 0;

                    return;
                }

                this->m_nextOffset = 0;
                for (u16 i = 0; i < this->logtxt.size(); i++)
                    this->m_nextOffset += 20;

                this->m_nextOffset -= this->m_maxheight / 3;

                if (this->m_nextOffset < 0)
                    this->m_nextOffset = 0;

                if (this->m_nextOffset > (this->m_listHeight - this->m_maxheight))
                    this->m_nextOffset = (this->m_listHeight - this->m_maxheight);
            }
        };
    }
}