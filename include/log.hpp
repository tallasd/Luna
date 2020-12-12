#pragma once
#include <tesla.hpp>
#include <cstdio>
#include <vector>
#include <string>

namespace tsl
{
    namespace elm
    {
        class Log : public Element {
        public:

            /**
             * @brief Constructor
             */
            Log(u64 maxlength) {
                this->maxlogsize = maxlength;
            }

            /**
            * @brief Destructor
            */
            virtual ~Log() {}


            virtual void draw(gfx::Renderer* renderer) override {
                for (u64 i = 0; i < this->logtxt.size(); i++) {
                    renderer->drawString(this->logtxt[i].c_str(), false, this->getX() + 18, this->getY() + 20 + (s64)(i * 20), 16, renderer->a(tsl::style::color::ColorText));
                }
            }

            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX(), this->getY(), this->getWidth(), logtxt.size() * 20);
            }

            virtual void addLine(std::string text) {
                //make space on screen to draw
                if (this->logtxt.size() == this->maxlogsize) {
                    this->logtxt.clear();
                }
                this->logtxt.push_back(text);
                this->invalidate();
            }

        protected:
            std::vector<std::string> logtxt{};
            size_t maxlogsize = 0;

        };
    }
}