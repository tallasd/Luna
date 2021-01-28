#define LUNA_DIR							"/config/luna"
#define LUNA_DUMP_DIR						LUNA_DIR "/dump/"
#define LUNA_TEMPLATE_DIR					LUNA_DIR "/template/"

#define TID									0x01006F8002326000

//*1.7.0 specific stuff*//

#define BID									0x0400F824B4DA556E
#define MAINFILE_SIZE						8690736

#define REVISION_MAJOR						0x74001
#define REVISION_MINOR						0x74005
#define REVISION_SAVE						16

//**********************//

//it's my 18th birthday and I planned on changing minor version based on ACNH revisions (it's the first revision since i made this tool), so this worked out well i think :^)
#define MAJOR_VERSION						0
#define MINOR_VERSION						1
#define REVISION_VERSION					8
#define STRINGIFY(x)						#x
#define TOSTRING(x)							STRINGIFY(x)
#define STRING_VERSION						"" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) ""

#define DEBUG								0
#define DEBUG_UI							0
#define DEBUG_FS							0
#define DEBUG_FC							1