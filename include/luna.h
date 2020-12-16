#define LUNA_DIR "/config/luna"
#define LUNA_DUMP_DIR LUNA_DIR "/dump/"
#define LUNA_TEMPLATE_DIR LUNA_DIR "/template/"

#define TID 0x01006F8002326000
#define BID 0x36EEBA0C26F14216	//1.6.0
#define MAINFILE_SIZE 11688160	//1.6.0

#define MAJOR_VERSION       0
#define MINOR_VERSION       0
#define REVISION_VERSION    1
#define STRINGIFY(x)        #x
#define TOSTRING(x)         STRINGIFY(x)
#define STRING_VERSION      "" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) ""

#define DEBUG				0
#define DEBUG_UI			0
#define DEBUG_FS			0