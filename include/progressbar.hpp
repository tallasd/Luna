#pragma once
#include <tesla.hpp>
#include <cstdio>
#include <vector>
#include <string>

namespace tsl 
{
    namespace elm 
    {
        static std::vector<const char *> loadingSquares = { "\uE020", "\uE021", "\uE022", "\uE023", "\uE024", "\uE025", "\uE026", "\uE027" };

        /**
        * @brief A customizable analog progressbar going from 0% to 100%
        *
        */
        class ProgressBar : public Element {
        public:

            /**
             * @brief Constructor
             */
            ProgressBar() {}
            //get image
            //File *rgba = fopen(LUNA_DIR + "/" + "/user.rgba", "rb");
            //this->m_bmp = (char*)malloc(sizeof(char) * ftell(rgba));
            //fread(this->m_bmp, 1, ftell(rgba), rgba);
            //fclose(rgba);

            virtual ~ProgressBar() {}


            virtual void draw(gfx::Renderer* renderer) override {
                //draw the icon
                if(this->m_progress != 100)
                    renderer->drawString(loadingSquares[this->m_change], false, this->getX() + 18, this->getY() + 57, 27, a(tsl::style::color::ColorText));
                //draw a heart when we are done.
                else renderer->drawString("\uE017", false, this->getX() + 18, this->getY() + 55, 27, a(tsl::style::color::ColorText));
                //draw bar
                u16 handlePos = (this->getWidth() - 95) * static_cast<float>(this->m_progress) / 100;
                renderer->drawRect(this->getX() + 60, this->getY() + 35, this->getWidth() - 95, 20, a(tsl::style::color::ColorHandle));
                renderer->drawRect(this->getX() + 60, this->getY() + 35, handlePos, 20, a(tsl::style::color::ColorHighlight));

                //draw Status
                renderer->drawString(this->getStatusFull().c_str(), false, (this->getWidth() / 2) - this->getStatusFull().length() * 2.4f, this->getY() + 27, 16, a(tsl::style::color::ColorText));

                //draw user
                //renderer->drawBitmap(this->getX(), this->getY() + 30, 240, 143, this->m_bmp);
            }

            virtual void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override {
                this->setBoundaries(this->getX(), this->getY(), this->getWidth(), 90);
            }

            virtual void drawFocusBackground(gfx::Renderer* renderer) {
                // No background drawn here in HOS
            }

             /**
             * @brief Gets the current status of the progressbar
             *
             * @return State
             */
            virtual inline std::string getStatus() {
                return this->m_status;
            }

            /**
            * @brief Gets the current status of the progressbar
            *
            * @return State
            */
            virtual inline std::string getStatusFull() {
                std::string s(this->m_status_prefix);
                std::string f(this->m_status);
                std::string b = s + f;
                return b;
            }
            /**
             * @brief Sets the current status of the progressbar.
             *
             * @param string: status displayed above the progressbar
             */
            virtual void setStatus(const char* string) {
                this->m_status = string;
            }

            /**
            * @brief Sets the status prefix for the progressbar
            *
            * @param string: status prefix that is displayed before the status message (Default is "Status: ")
             */
            virtual void setStatusPrefix(const char* string) {
                this->m_status_prefix = string;
            }

            /**
             * @brief Gets the current value of the progressbar
             *
             * @return State
             */
            virtual inline u8 getProgress() {
                return this->m_progress;
            }
            /**
             * @brief Sets the current progress of the progressbar
             *
             * @param value: State in %
             */
            virtual void setProgress(u8 value) {
                this->m_progress = value;
            }

            virtual void Spin() {
                if (this->m_change + 1 == 8)
                    this->m_change = 0;
                else this->m_change++;
            }

        protected:
            u8 m_progress = 0;
            u8 m_change = 0;
            const char* m_icon = loadingSquares[this->m_change];
            const char* m_status = "nothing";
            //const u8 *m_bmp;
            const char* m_status_prefix = "Status: ";



        };
    }
}