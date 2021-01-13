#define LUNA_DIR							"/config/luna"
#define LUNA_DUMP_DIR						LUNA_DIR "/dump/"
#define LUNA_TEMPLATE_DIR					LUNA_DIR "/template/"

#define TID									0x01006F8002326000

//*1.6.0 specific stuff*//

#define BID									0x36EEBA0C26F14216
#define MAINFILE_SIZE						11688160

#define REVISION_MAJOR						0x70001
#define REVISION_MINOR						0x70006
#define REVISION_SAVE						15

//**********************//

#define MAJOR_VERSION						0
#define MINOR_VERSION						0
#define REVISION_VERSION					7
#define STRINGIFY(x)						#x
#define TOSTRING(x)							STRINGIFY(x)
#define STRING_VERSION						"" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) ""

#define DEBUG								0
#define DEBUG_UI							0
#define DEBUG_FS							0
#define DEBUG_FC							1