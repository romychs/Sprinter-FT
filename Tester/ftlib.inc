    IFNDEF  _FT_LIB_INC
    DEFINE  _FT_LIB_INC


FT_CTRL			EQU 0x77
FT_DATA			EQU 0x57
FT_BUFFER_SIZE  EQU 128

FT_CS_ON		EQU 0x04
FT_CS_OFF       EQU 0xFB

PORT_FT_CTRL	EQU ISA_BASE_A + FT_CTRL			; Memory address to read Strinter-FT Control port
PORT_FT_DATA    EQU ISA_BASE_A + FT_DATA			; Memory address to read Strinter-FT Data port



FT_MODE_640_480_57             EQU 0	;  0: 640x480@57Hz (48MHz)
FT_MODE_640_480_74             EQU 1	;  1: 640x480@74Hz (64MHz)
FT_MODE_640_480_76             EQU 2	;  2: 640x480@76Hz (64MHz)
FT_MODE_800_600_60             EQU 3	;  3: 800x600@60Hz (40MHz)
FT_MODE_800_600_60_80MHZ       EQU 4	;  4: 800x600@60Hz (80MHz)
FT_MODE_800_600_69             EQU 5	;  5: 800x600@69Hz (48MHz)
FT_MODE_800_600_85             EQU 6	;  6: 800x600@85Hz (56MHz)
FT_MODE_1024_768_59            EQU 7	;  7: 1024x768@59Hz (64MHz)
FT_MODE_1024_768_67            EQU 8	;  8: 1024x768@67Hz (72MHz)
FT_MODE_1024_768_76            EQU 9	;  9: 1024x768@76Hz (80MHz)
FT_MODE_1280_1024_60_HALF      EQU 10	; 10: 1280/2x1024@60Hz (56MHz)
FT_MODE_1280_720_58            EQU 11	; 11: 1280x720@58Hz (72MHz)
FT_MODE_1280_720_60            EQU 12	; 12: 1280x720@60Hz (72MHz)
FT_MODE_800_600_48_7           EQU 13	; 13: 800x600@48.7Hz (40MHz)  - for ZX-Evo sync
FT_MODE_1024_768_48_7          EQU 14	; 14: 1024x768@48.7Hz (64MHz) - for ZX-Evo sync
FT_MODE_MAX					   EQU 15



; Videomode parameters 10 bytes each
FT_MODE
; f_mul, f_div, h_fporch, h_sync, h_bporch, h_visible, v_fporch, v_sync, v_bporch, v_visible
	DW 6,  2, 16, 96,  48,  640,  11, 2, 31, 480   		;  0: 640x480@57Hz (48MHz)
	DW 8,  2, 24, 40,  128, 640,  9,  3, 28, 480 		;  1: 640x480@74Hz (64MHz)
	DW 8,  2, 16, 96,  48,  640,  11, 2, 31, 480 		;  2: 640x480@76Hz (64MHz)
	DW 5,  1, 40, 128, 88,  800,  1,  4, 23, 600 		;  3: 800x600@60Hz (40MHz)
	DW 10, 2, 40, 128, 88,  800,  1,  4, 23, 600 		;  4: 800x600@60Hz (80MHz)
	DW 6,  1, 56, 120, 64,  800,  37, 6, 23, 600 		;  5: 800x600@69Hz (48MHz)
	DW 7,  1, 32, 64,  152, 800,  1,  3, 27, 600 		;  6: 800x600@85Hz (56MHz)
	DW 8,  1, 24, 136, 160, 1024, 3,  6, 29, 768 		;  7: 1024x768@59Hz (64MHz)
	DW 9,  1, 24, 136, 144, 1024, 3,  6, 29, 768 		;  8: 1024x768@67Hz (72MHz)
	DW 10, 1, 16, 96,  176, 1024, 1,  3, 28, 768 		;  9: 1024x768@76Hz (80MHz)
	DW 7,  1, 24, 56,  124, 640,  1,  3, 38, 1024		; 10: 1280/2x1024@60Hz (56MHz)
	DW 9, 1, 110, 40,  220, 1280, 5,  5, 20, 720 		; 11: 1280x720@58Hz (72MHz)
	DW 9,  1, 93, 40,  187, 1280, 5,  5, 20, 720 		; 12: 1280x720@60Hz (72MHz)
	DW 5,  1, 40, 128, 88,  800,  1,  4, 23, 748 		; 13: 800x600@48.7Hz (40MHz)  - for ZX-Evo sync
	DW 8,  1, 24, 136, 160, 1024, 3,  6, 29, 938 		; 14: 1024x768@48.7Hz (64MHz) - for ZX-Evo sync
; Offsets in FT_MODE table
f_mul		EQU 0
f_div		EQU 2
h_fporch	EQU	4
h_sync		EQU 6
h_bporch	EQU 8
h_visible	EQU 10
v_fporch	EQU 12
v_sync		EQU 14
v_bporch	EQU 16
v_visible	EQU 18


; -------------------------------------------------------
; Memory addresses
; -------------------------------------------------------
FT_RAM_G           EQU	0x000000   ; Main graphics RAM
FT_ROM_CHIPID      EQU	0x0C0000   ; Chip ID and revision
FT_ROM_FONT        EQU	0x1E0000   ; Fonts
FT_ROM_FONT_ADDR   EQU	0x2FFFFC   ; Font table pointer address
FT_RAM_DL          EQU	0x300000   ; Display list RAM
FT_RAM_REG         EQU	0x302000   ; Registers
FT_RAM_CMD         EQU	0x308000   ; Coprocessor command buffer
FT_RAM_ERR_REPORT  EQU	0x309800   ; Error message

; -------------------------------------------------------
; Commands
; -------------------------------------------------------
FT_CMD_ACTIVE      EQU	0x00   ; cc 00 00
FT_CMD_STANDBY     EQU	0x41   ; cc 00 00
FT_CMD_SLEEP       EQU	0x42   ; cc 00 00
FT_CMD_PWRDOWN     EQU	0x43   ; cc 00 00
FT_CMD_CLKEXT      EQU	0x44   ; cc 00 00
FT_CMD_CLKINT      EQU	0x48   ; cc 00 00
FT_CMD_PDROMS      EQU	0x49   ; cc xx 00
FT_CMD_CLKSEL      EQU	0x61   ; cc xx 00 -> [5:0] - mul, [7:6] - PLL range (0 for mul=0..3, 1 for mul=4..5)
FT_CMD_RST_PULSE   EQU	0x68   ; cc 00 00

; -------------------------------------------------------
; ID
; -------------------------------------------------------
FT_ID   EQU	0x7C

; -------------------------------------------------------
; Registers
; -------------------------------------------------------
FT_REG_ID                 EQU	0x302000
FT_REG_FRAMES             EQU	0x302004
FT_REG_CLOCK              EQU	0x302008
FT_REG_FREQUENCY          EQU	0x30200C
FT_REG_RENDERMODE         EQU	0x302010
FT_REG_SNAPY              EQU	0x302014
FT_REG_SNAPSHOT           EQU	0x302018
FT_REG_SNAPFORMAT         EQU	0x30201C
FT_REG_CPURESET           EQU	0x302020
FT_REG_TAP_CRC            EQU	0x302024
FT_REG_TAP_MASK           EQU	0x302028
FT_REG_HCYCLE             EQU	0x30202C
FT_REG_HOFFSET            EQU	0x302030
FT_REG_HSIZE              EQU	0x302034
FT_REG_HSYNC0             EQU	0x302038
FT_REG_HSYNC1             EQU	0x30203C
FT_REG_VCYCLE             EQU	0x302040
FT_REG_VOFFSET            EQU	0x302044
FT_REG_VSIZE              EQU	0x302048
FT_REG_VSYNC0             EQU	0x30204C
FT_REG_VSYNC1             EQU	0x302050
FT_REG_DLSWAP             EQU	0x302054
FT_REG_ROTATE             EQU	0x302058
FT_REG_OUTBITS            EQU	0x30205C
FT_REG_DITHER             EQU	0x302060
FT_REG_SWIZZLE            EQU	0x302064
FT_REG_CSPREAD            EQU	0x302068
FT_REG_PCLK_POL           EQU	0x30206C
FT_REG_PCLK               EQU	0x302070
FT_REG_TAG_X              EQU	0x302074
FT_REG_TAG_Y              EQU	0x302078
FT_REG_TAG                EQU	0x30207C
FT_REG_VOL_PB             EQU	0x302080
FT_REG_VOL_SOUND          EQU	0x302084
FT_REG_SOUND              EQU	0x302088
FT_REG_PLAY               EQU	0x30208C
FT_REG_GPIO_DIR           EQU	0x302090
FT_REG_GPIO               EQU	0x302094
FT_REG_GPIOX_DIR          EQU	0x302098
FT_REG_GPIOX              EQU	0x30209C
FT_REG_INT_FLAGS          EQU	0x3020A8
FT_REG_INT_EN             EQU	0x3020AC
FT_REG_INT_MASK           EQU	0x3020B0
FT_REG_PLAYBACK_START     EQU	0x3020B4
FT_REG_PLAYBACK_LENGTH    EQU	0x3020B8
FT_REG_PLAYBACK_READPTR   EQU	0x3020BC
FT_REG_PLAYBACK_FREQ      EQU	0x3020C0
FT_REG_PLAYBACK_FORMAT    EQU	0x3020C4
FT_REG_PLAYBACK_LOOP      EQU	0x3020C8
FT_REG_PLAYBACK_PLAY      EQU	0x3020CC
FT_REG_PWM_HZ             EQU	0x3020D0
FT_REG_PWM_DUTY           EQU	0x3020D4
FT_REG_MACRO_0            EQU	0x3020D8
FT_REG_MACRO_1            EQU	0x3020DC
FT_REG_CMD_READ           EQU	0x3020F8
FT_REG_CMD_WRITE          EQU	0x3020FC
FT_REG_CMD_DL             EQU	0x302100
FT_REG_TOUCH_MODE         EQU	0x302104
FT_REG_TOUCH_ADC_MODE     EQU	0x302108
FT_REG_TOUCH_CHARGE       EQU	0x30210C
FT_REG_TOUCH_SETTLE       EQU	0x302110
FT_REG_TOUCH_OVERSAMPLE   EQU	0x302114
FT_REG_TOUCH_RZTHRESH     EQU	0x302118
FT_REG_TOUCH_RAW_XY       EQU	0x30211C
FT_REG_TOUCH_RZ           EQU	0x302120
FT_REG_TOUCH_SCREEN_XY    EQU	0x302124
FT_REG_TOUCH_TAG_XY       EQU	0x302128
FT_REG_TOUCH_TAG          EQU	0x30212C
FT_REG_TOUCH_TAG1_XY      EQU	0x302130
FT_REG_TOUCH_TAG1         EQU	0x302134
FT_REG_TOUCH_TAG2_XY      EQU	0x302138
FT_REG_TOUCH_TAG2         EQU	0x30213C
FT_REG_TOUCH_TAG3_XY      EQU	0x302140
FT_REG_TOUCH_TAG3         EQU	0x302144
FT_REG_TOUCH_TAG4_XY      EQU	0x302148
FT_REG_TOUCH_TAG4         EQU	0x30214C
FT_REG_TOUCH_TRANSFORM_A  EQU	0x302150
FT_REG_TOUCH_TRANSFORM_B  EQU	0x302154
FT_REG_TOUCH_TRANSFORM_C  EQU	0x302158
FT_REG_TOUCH_TRANSFORM_D  EQU	0x30215C
FT_REG_TOUCH_TRANSFORM_E  EQU	0x302160
FT_REG_TOUCH_TRANSFORM_F  EQU	0x302164
FT_REG_TOUCH_CONFIG       EQU	0x302168
FT_REG_CTOUCH_TOUCH4_X    EQU	0x30216C
FT_REG_BIST_EN            EQU	0x302174
FT_REG_TRIM               EQU	0x302180
FT_REG_ANA_COMP           EQU	0x302184
FT_REG_SPI_WIDTH          EQU	0x302188
FT_REG_TOUCH_DIRECT_XY    EQU	0x30218C
FT_REG_TOUCH_DIRECT_Z1Z2  EQU	0x302190
FT_REG_DATESTAMP          EQU	0x302564
FT_REG_CMDB_SPACE         EQU	0x302574
FT_REG_CMDB_WRITE         EQU	0x302578
FT_REG_ADAPTIVE_FRAMERATE EQU	0x30257C
FT_REG_PLAYBACK_PAUSE     EQU	0x3025EC
FT_REG_FLASH_STATUS       EQU	0x3025F0
REG_MEDIAFIFO_READ        EQU	0x309014
REG_MEDIAFIFO_WRITE       EQU	0x309018
FT_REG_FLASH_SIZE         EQU	0x309024

FT_REG_TRACKER            EQU	0x309000
FT_REG_TRACKER_1          EQU	0x309004
FT_REG_TRACKER_2          EQU	0x309008
FT_REG_TRACKER_3          EQU	0x30900C
FT_REG_TRACKER_4          EQU	0x309010
FT_REG_MEDIAFIFO_READ     EQU	0x309014
FT_REG_MEDIAFIFO_WRITE    EQU	0x309018

; -------------------------------------------------------
; Co-processor commands
; -------------------------------------------------------
FT_CCMD_APPEND            EQU	0xFFFFFF1E
FT_CCMD_BGCOLOR           EQU	0xFFFFFF09
FT_CCMD_BITMAP_TRANSFORM  EQU	0xFFFFFF21
FT_CCMD_BUTTON            EQU	0xFFFFFF0D
FT_CCMD_CALIBRATE         EQU	0xFFFFFF15
FT_CCMD_CLOCK             EQU	0xFFFFFF14
FT_CCMD_COLDSTART         EQU	0xFFFFFF32
FT_CCMD_CRC               EQU	0xFFFFFF03
FT_CCMD_CSKETCH           EQU	0xFFFFFF35
FT_CCMD_DIAL              EQU	0xFFFFFF2D
FT_CCMD_DLSTART           EQU	0xFFFFFF00
FT_CCMD_EXECUTE           EQU	0xFFFFFF07
FT_CCMD_FGCOLOR           EQU	0xFFFFFF0A
FT_CCMD_FLASHATTACH       EQU	0xFFFFFF49
FT_CCMD_FLASHDETACH       EQU	0xFFFFFF48
FT_CCMD_FLASHERASE        EQU	0xFFFFFF44
FT_CCMD_FLASHFAST         EQU	0xFFFFFF4A
FT_CCMD_FLASHRX           EQU	0xFFFFFF4D
FT_CCMD_FLASHSOURCE       EQU	0xFFFFFF4E
FT_CCMD_FLASHSPIDESEL     EQU	0xFFFFFF4B
FT_CCMD_FLASHTX           EQU	0xFFFFFF4C
FT_CCMD_FLASHUPDATE       EQU	0xFFFFFF47
FT_CCMD_GAUGE             EQU	0xFFFFFF13
FT_CCMD_GETMATRIX         EQU	0xFFFFFF33
FT_CCMD_GETPOINT          EQU	0xFFFFFF08
FT_CCMD_GETPROPS          EQU	0xFFFFFF25
FT_CCMD_GETPTR            EQU	0xFFFFFF23
FT_CCMD_GRADCOLOR         EQU	0xFFFFFF34
FT_CCMD_GRADIENT          EQU	0xFFFFFF0B
FT_CCMD_HAMMERAUX         EQU	0xFFFFFF04
FT_CCMD_IDCT_DELETED      EQU	0xFFFFFF06
FT_CCMD_INFLATE           EQU	0xFFFFFF22
FT_CCMD_INTERRUPT         EQU	0xFFFFFF02
FT_CCMD_INT_RAMSHARED     EQU	0xFFFFFF3D
FT_CCMD_INT_SWLOADIMAGE   EQU	0xFFFFFF3E
FT_CCMD_KEYS              EQU	0xFFFFFF0E
FT_CCMD_LOADIDENTITY      EQU	0xFFFFFF26
FT_CCMD_LOADIMAGE         EQU	0xFFFFFF24
FT_CCMD_LOGO              EQU	0xFFFFFF31
FT_CCMD_MARCH             EQU	0xFFFFFF05
FT_CCMD_MEDIAFIFO         EQU	0xFFFFFF39
FT_CCMD_MEMCPY            EQU	0xFFFFFF1D
FT_CCMD_MEMCRC            EQU	0xFFFFFF18
FT_CCMD_MEMSET            EQU	0xFFFFFF1B
FT_CCMD_MEMWRITE          EQU	0xFFFFFF1A
FT_CCMD_MEMZERO           EQU	0xFFFFFF1C
FT_CCMD_NUMBER            EQU	0xFFFFFF2E
FT_CCMD_PLAYVIDEO         EQU	0xFFFFFF3A
FT_CCMD_PROGRESS          EQU	0xFFFFFF0F
FT_CCMD_REGREAD           EQU	0xFFFFFF19
FT_CCMD_ROMFONT           EQU	0xFFFFFF3F
FT_CCMD_ROTATE            EQU	0xFFFFFF29
FT_CCMD_SCALE             EQU	0xFFFFFF28
FT_CCMD_SCREENSAVER       EQU	0xFFFFFF2F
FT_CCMD_SCROLLBAR         EQU	0xFFFFFF11
FT_CCMD_SETBASE           EQU	0xFFFFFF38
FT_CCMD_SETBITMAP         EQU	0xFFFFFF43
FT_CCMD_SETFONT           EQU	0xFFFFFF2B
FT_CCMD_SETFONT2          EQU	0xFFFFFF3B
FT_CCMD_SETMATRIX         EQU	0xFFFFFF2A
FT_CCMD_SETROTATE         EQU	0xFFFFFF36
FT_CCMD_SETSCRATCH        EQU	0xFFFFFF3C
FT_CCMD_SKETCH            EQU	0xFFFFFF30
FT_CCMD_SLIDER            EQU	0xFFFFFF10
FT_CCMD_SNAPSHOT          EQU	0xFFFFFF1F
FT_CCMD_SNAPSHOT2         EQU	0xFFFFFF37
FT_CCMD_SPINNER           EQU	0xFFFFFF16
FT_CCMD_STOP              EQU	0xFFFFFF17
FT_CCMD_SWAP              EQU	0xFFFFFF01
FT_CCMD_SYNC              EQU	0xFFFFFF42
FT_CCMD_TEXT              EQU	0xFFFFFF0C
FT_CCMD_TOGGLE            EQU	0xFFFFFF12
FT_CCMD_TOUCH_TRANSFORM   EQU	0xFFFFFF20
FT_CCMD_TRACK             EQU	0xFFFFFF2C
FT_CCMD_TRANSLATE         EQU	0xFFFFFF27
FT_CCMD_VIDEOFRAME        EQU	0xFFFFFF41
FT_CCMD_VIDEOSTART        EQU	0xFFFFFF40

; ubsigned long
FT_OPT_CENTER     EQU 1536
FT_OPT_CENTERX    EQU 512
FT_OPT_CENTERY    EQU 1024
FT_OPT_FLAT       EQU 256
FT_OPT_MONO       EQU 1
FT_OPT_NOBACK     EQU 4096
FT_OPT_NODL       EQU 2
FT_OPT_NOHANDS    EQU 49152
FT_OPT_NOHM       EQU 16384
FT_OPT_NOPOINTER  EQU 16384
FT_OPT_NOSECS     EQU 32768
FT_OPT_NOTICKS    EQU 8192
FT_OPT_RIGHTX     EQU 2048
FT_OPT_SIGNED     EQU 256
OPT_NOTEAR        EQU 4
OPT_FULLSCREEN    EQU 8
OPT_MEDIAFIFO     EQU 16
OPT_SOUND         EQU 32

; -------------------------------------------------------
; Primitives
; -------------------------------------------------------
FT_BITMAPS        EQU	1
FT_POINTS         EQU	2
FT_LINES          EQU	3
FT_LINE_STRIP     EQU	4
FT_EDGE_STRIP_R   EQU	5
FT_EDGE_STRIP_L   EQU	6
FT_EDGE_STRIP_A   EQU	7
FT_EDGE_STRIP_B   EQU	8
FT_RECTS          EQU	9

; -------------------------------------------------------
; Formats
; -------------------------------------------------------
FT_ARGB1555       EQU	0
FT_L1             EQU	1
FT_L4             EQU	2
FT_L8             EQU	3
FT_RGB332         EQU	4
FT_ARGB2          EQU	5
FT_ARGB4          EQU	6
FT_RGB565         EQU	7
FT_TEXT8X8        EQU	9
FT_TEXTVGA        EQU	10
FT_BARGRAPH       EQU	11
FT_PALETTED565    EQU	14
FT_PALETTED4444   EQU	15
FT_PALETTED8      EQU	16
FT_L2             EQU	17

; -------------------------------------------------------
; Blend functions
; -------------------------------------------------------
FT_ZERO                 EQU	0
FT_ONE                  EQU	1
FT_SRC_ALPHA            EQU	2
FT_DST_ALPHA            EQU	3
FT_ONE_MINUS_SRC_ALPHA  EQU	4
FT_ONE_MINUS_DST_ALPHA  EQU	5

; -------------------------------------------------------
; Stencil test functions
; -------------------------------------------------------
FT_NEVER          EQU	0
FT_LESS           EQU	1
FT_LEQUAL         EQU	2
FT_GREATER        EQU	3
FT_GEQUAL         EQU	4
FT_EQUAL          EQU	5
FT_NOTEQUAL       EQU	6
FT_ALWAYS         EQU	7

; -------------------------------------------------------
; Stencil operations
; -------------------------------------------------------
FT_KEEP         EQU	1
FT_REPLACE      EQU	2
FT_INCR         EQU	3
FT_DECR         EQU	4
FT_INVERT       EQU	5
FT_INCR_WRAP    EQU	6 							; undocumented???
FT_DECR_WRAP    EQU	7 							; undocumented???

; -------------------------------------------------------
; Bitmap wrap mode
; -------------------------------------------------------
FT_REPEAT     	EQU	1
FT_BORDER     	EQU	0

; -------------------------------------------------------
; Bitmap filtering mode
; -------------------------------------------------------
FT_NEAREST    	EQU	0
FT_BILINEAR   	EQU	1

; -------------------------------------------------------
; DL_SWAP modes
; -------------------------------------------------------
FT_DLSWAP_DONE  EQU	0
FT_DLSWAP_LINE  EQU	1
FT_DLSWAP_FRAME EQU	2

; -------------------------------------------------------
; INT sources
; -------------------------------------------------------
FT_INT_SWAP        	EQU	1
FT_INT_TOUCH       	EQU	2
FT_INT_TAG         	EQU	4
FT_INT_SOUND       	EQU	8
FT_INT_PLAYBACK    	EQU	16
FT_INT_CMDEMPTY    	EQU	32
FT_INT_CMDFLAG     	EQU	64
FT_INT_CONVCOMPLETE	EQU	128

; -------------------------------------------------------
; Playback formats
; -------------------------------------------------------
FT_LINEAR_SAMPLES    EQU	0
FT_ULAW_SAMPLES      EQU	1
FT_ADPCM_SAMPLES     EQU	2

; -------------------------------------------------------
; Touch ADC modes
; -------------------------------------------------------
FT_ADC_SINGLE_ENDED		EQU	0
FT_ADC_DIFFERENTIAL		EQU	1

; -------------------------------------------------------
; Touch modes
; -------------------------------------------------------
FT_TOUCHMODE_OFF       	EQU 0
FT_TOUCHMODE_ONESHOT   	EQU 1
FT_TOUCHMODE_FRAME     	EQU 2
FT_TOUCHMODE_CONTINUOUS	EQU 3

; -------------------------------------------------------
; Constants
; -------------------------------------------------------
FT_DL_SIZE              EQU	8192  						; 8KB Display List buffer size
FT_CMD_FIFO_SIZE        EQU	4096  						; 4KB coprocessor Fifo size
FT_CMD_SIZE             EQU	4     						; 4 byte per coprocessor command of EVE
FT_GPU_NUMCHAR_PERFONT  EQU	128
FT_GPU_FONT_TABLE_SIZE  EQU	148



	MACRO	ft_cmd cmd
	LD		A, cmd
	CALL	@FT.FT_CMD
	ENDM

	MACRO	ft_rreg8 reg16
	LD		BC, reg16
	CALL	@FT.FT_RREG8
	ENDM

	MACRO	ft_rreg16 reg16
	LD		BC, reg16
	CALL	@FT.FT_RREG16
	ENDM

	MACRO	ft_cmdp cmd, par
	LD		B, cmd
	LD		C, par
	CALL	@FT.FT_CMDP
	ENDM

	ENDIF