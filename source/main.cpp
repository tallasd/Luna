#define TESLA_INIT_IMPL // If you have more than one file using the tesla header, only define this in the main one
#include <tesla.hpp>    // The Tesla Header
#include <util.h>
#include "dump.hpp"
#include "luna.h"
#include <fcntl.h>		/* for open */

static char ret[100];
static bool isRunning = false;

//seperate thread that runs after createUI or something
#if !DEBUG_UI
std::thread dump;
#endif

class GuiDump : public tsl::Gui {
public:
    //ctor
    GuiDump() { }

    //dtor
    ~GuiDump() {
#if !DEBUG_UI
        dump.join();
#endif
        isRunning = false;
    }

    // Called once when this Gui gets loaded to create the UI
    // Allocate all elements on the heap. libtesla will make sure to clean them up when not needed anymore
    virtual tsl::elm::Element *createUI() override {
        auto frame = new tsl::elm::OverlayFrame("Luna", STRING_VERSION);

        this->m_progressBar = new tsl::elm::ProgressBar();
        this->m_Log = new tsl::elm::Log(20);
        auto list = new tsl::elm::List();

        list->addItem(this->m_progressBar);
        list->addItem(this->m_Log);
#if !DEBUG_UI
        //assign dump thread our Dumper function
        dump = std::thread([this]() { Dumper(&this->progress, &this->status, &this->m_Log); });
#endif
        isRunning = true;

        frame->setContent(list);

        return frame;
    }

    // Called once every frame to update values
    virtual void update() override {

        if (isRunning) {
            this->tem++;
            this->m_progressBar->setProgress(this->progress);
            this->m_progressBar->setStatus(this->status);
            //should change 4 times a second
            if (this->tem % 15 == 0) {
                this->m_progressBar->Spin();
                this->tem = 0;
            }
        }
    }

    // Called once every frame to handle inputs not handled by other UI elements
    virtual bool handleInput(u64 keysDown, u64 keysHeld, touchPosition touchInput, JoystickPosition leftJoyStick, JoystickPosition rightJoyStick) override {
        return false;   // Return true here to singal the inputs have been consumed
    }

private:
    tsl::elm::ProgressBar *m_progressBar = nullptr;
    u8 progress = 0;
    u8 tem = 0;
    const char *status = "preparing...";
    tsl::elm::Log *m_Log = nullptr;
};

class SelectionGui : public tsl::Gui {
public:
    SelectionGui() { }

    // Called when this Gui gets loaded to create the UI
    // Allocate all elements on the heap. libtesla will make sure to clean them up when not needed anymore
    virtual tsl::elm::Element* createUI() override {
        // A OverlayFrame is the base element every overlay consists of. This will draw the default Title and Subtitle.
        // If you need more information in the header or want to change it's look, use a HeaderOverlayFrame.
        auto frame = new tsl::elm::OverlayFrame("Luna", STRING_VERSION);

        // A list that can contain sub elements and handles scrolling
        auto list = new tsl::elm::List();

        // List Items
        list->addItem(new tsl::elm::CategoryHeader("Dump Options"));

        auto* clickableListItem = new tsl::elm::ListItem("Dump Dream Island", "...");
        clickableListItem->setClickListener([](u64 keys) {
            if (keys & KEY_A) {
                tsl::changeTo<GuiDump>();
                return true;
            }

            return false;
            });

        list->addItem(clickableListItem);

        // Add the list to the frame for it to be drawn
        frame->setContent(list);

        // Return the frame to have it become the top level element of this Gui
        return frame;
    }

    // Called once every frame to update values
    virtual void update() override {

    }

    // Called once every frame to handle inputs not handled by other UI elements
    virtual bool handleInput(u64 keysDown, u64 keysHeld, touchPosition touchInput, JoystickPosition leftJoyStick, JoystickPosition rightJoyStick) override {
        return false;   // Return true here to signal the inputs have been consumed
    }
};

class GuiError : public tsl::Gui {
public:
    GuiError(tsl::elm::Element* elm) { this->m_elm = elm; }

    virtual tsl::elm::Element *createUI() override {

        tsl::elm::OverlayFrame *rootFrame = new tsl::elm::OverlayFrame("Luna", STRING_VERSION);

        rootFrame->setContent(this->m_elm);

        return rootFrame;
    }
private:
    tsl::elm::Element *m_elm;
};

enum class CheckResult {
    Success,
    WrongBID,
    WrongTID,
    NoDream,
    NoTemplate,
};

struct Check {
    CheckResult check_result;
    tsl::elm::Element* elm;
};

Check Checker() {
    Check checkvar;

    u64 pid = 0, tid = 0, bid = 0;
    pmdmntGetApplicationProcessId(&pid);
    pminfoGetProgramId(&tid, pid);
    DmntCheatProcessMetadata metadata;
    dmntchtGetCheatProcessMetadata(&metadata);
    memcpy(&bid, metadata.main_nso_build_id, 0x8);

    tsl::elm::Element *warning;

    //fix endianess of hash
    bid = __builtin_bswap64(bid);

    bool isACNH = false;
    if (tid == TID) isACNH = true;

    //dream check
    u32 dreamstrval;
    u64 IslandNameOffset = 0x18;
    //[[[main+3C957B0]+10]+F8]+60
    u64 mainAddr = util::FollowPointerMain(0x3C957B0, 0x10, 0xF8, 0xFFFFFFFFFFFFFFFF) + 0x60;
    dmntchtReadCheatProcessMemory(mainAddr + IslandNameOffset, &dreamstrval, sizeof(u32));

    if (isACNH) {
        if (bid != BID) {
            std::snprintf(ret, 100, "BID 0x%lX", bid);
            const char* description = ret;

            warning = new tsl::elm::CustomDrawer([description](tsl::gfx::Renderer* renderer, s32 x, s32 y, s32 w, s32 h) {
                renderer->drawString("\uE150", false, 180, 250, 90, renderer->a(0xFFFF));
                renderer->drawString("Version missmatch:", false, 110, 340, 25, renderer->a(0xFFFF));
                renderer->drawString(description, false, 60, 375, 25, renderer->a(0xFFFF));
                });

            checkvar.check_result = CheckResult::WrongBID;
            checkvar.elm = warning;
            return checkvar;
        }
        else {
//if debug is enabled, dont perform dream check
#if !DEBUG_UI
            if (dreamstrval == 0x0) {
                warning = new tsl::elm::CustomDrawer([](tsl::gfx::Renderer* renderer, s32 x, s32 y, s32 w, s32 h) {
                    renderer->drawString("\uE008", false, 180, 250, 90, renderer->a(0xFFFF));
                    renderer->drawString("you didnt pass", false, x + 95, 340, 25, renderer->a(0xFFFF));
                    renderer->drawString("the simp check.", false, x + 95, 375, 25, renderer->a(0xFFFF));
                    });
                checkvar.check_result = CheckResult::NoDream;
                checkvar.elm = warning;
                return checkvar;
            }
#endif
            checkvar.check_result = CheckResult::Success;
            return checkvar;
        }
    }
    else {
#if DEBUG_UI
        std::snprintf(ret, 100, "TID 0x%lX", tid);
        const char* description = ret;
#else
        const char* description = "Please open ACNH!";
#endif
        warning = new tsl::elm::CustomDrawer([description](tsl::gfx::Renderer* renderer, s32 x, s32 y, s32 w, s32 h) {
            renderer->drawString("\uE150", false, 180, 250, 90, renderer->a(0xFFFF));
            renderer->drawString(description, false, 60, 340, 25, renderer->a(0xFFFF));
            });

        checkvar.check_result = CheckResult::WrongTID;
        checkvar.elm = warning;
        return checkvar;
    }
}

class OverlayTest : public tsl::Overlay {
public:
    // libtesla already initialized fs, hid, pl, pmdmnt, hid:sys and set:sys
    virtual void initServices() override {
        pminfoInitialize();
        dmntchtInitialize();
        dmntchtForceOpenCheatProcess();
        timeInitialize();
    }  // Called at the start to initialize all services necessary for this Overlay

    virtual void exitServices() override {
        pminfoExit();
        dmntchtExit();
        timeExit();
    }  // Called at the end to clean up all services previously initialized

    // Called before overlay wants to change from invisible to visible state
    virtual void onShow() override {}
    // Called before overlay wants to change from visible to invisible state
    virtual void onHide() override {}

    virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        
        bool hasTemplate = false;
        bool isDecrypted = true;
        
        tsl::hlp::doWithSDCardHandle([&hasTemplate, &isDecrypted]{
            if (access("/config/luna", F_OK) == -1) {
                mkdir("/config/luna", 0777);
            }
            if (access("/config/luna/dump", F_OK) == -1) {
                mkdir("/config/luna/dump", 0777);
            }
            if (access("/config/luna/template", F_OK) == -1) {
                mkdir("/config/luna/template", 0777);
                return;
            }
            if (access("/config/luna/template/main.dat", F_OK) == -1) {
                return;
            }
            else {
                int fd = open("/config/luna/template/main.dat", O_RDONLY);

                int size = lseek(fd, 0, SEEK_END);
                //template for wrong version
                if (size != MAINFILE_SIZE) return;
            }
            //if there is a header, its encrypted, therefore not Decrypted!
            if (access("/config/luna/template/mainHeader.dat", F_OK) != -1) {
                isDecrypted = false;
                return;
            }
            if (access("/config/luna/template/Villager0", F_OK) == -1) return;

            hasTemplate = true;
        });

        if (hasTemplate) {
            Check cr = Checker();
            if (cr.check_result == CheckResult::Success) return initially<SelectionGui>();
            else return initially<GuiError>(cr.elm);
        }
        else {
            if (isDecrypted) {
                auto warning = new tsl::elm::CustomDrawer([](tsl::gfx::Renderer* renderer, s32 x, s32 y, s32 w, s32 h) {
                    renderer->drawString("\uE150", false, 180, 250, 90, renderer->a(0xFFFF));
                    renderer->drawString("No valid template found.", false, 70, 340, 25, renderer->a(0xFFFF));
                    });
                return initially<GuiError>(warning);
            }
            else {
                auto warning = new tsl::elm::CustomDrawer([](tsl::gfx::Renderer* renderer, s32 x, s32 y, s32 w, s32 h) {
                    renderer->drawString("\uE150", false, 180, 250, 90, renderer->a(0xFFFF));
                    renderer->drawString("A template was found,", false, 85, 340, 25, renderer->a(0xFFFF));
                    renderer->drawString(  "but is encrypted.", false, 125, 375, 25, renderer->a(0xFFFF));
                    });
                return initially<GuiError>(warning);
            }
        }
    }
};

int main(int argc, char** argv) {
    return tsl::loop<OverlayTest>(argc, argv);
}
