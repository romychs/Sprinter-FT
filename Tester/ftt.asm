; ======================================================
; FT-Test to test Sprinter-FT
; FT812 Video card for Sprinter computer
; By Roman Boykov. Copyright (c) 2025
; https://github.com/romychs
; License: BSD 3-Clause
; ======================================================

; Set to 1 to turn debug ON with DeZog VSCode plugin
; Set to 0 to compile .EXE
DEBUG               EQU 0

; Set to 1 to output TRACE messages
TRACE               EQU 0

; Version of EXE file, 1 for DSS 1.70+
EXE_VERSION         EQU 0

; Timeout to wait ESP response
DEFAULT_TIMEOUT		EQU	2000

    SLDOPT COMMENT WPMEM, LOGPOINT, ASSERTION

    DEVICE NOSLOT64K

	INCLUDE "macro.inc"
	INCLUDE "dss.inc"
	INCLUDE "sprinter.inc"

	MODULE	MAIN

    ORG	0x8080
; ------------------------------------------------------
EXE_HEADER
    DB  "EXE"
    DB  EXE_VERSION                                     ; EXE Version
    DW  0x0080                                          ; Code offset
    DW  0
    DW  0                                               ; Primary loader size
    DW  0                                               ; Reserved
    DW  0
    DW  0
    DW  START                                           ; Loading Address
    DW  START                                           ; Entry Point
    DW  STACK_TOP                                       ; Stack address
    DS  106, 0                                          ; Reserved

    ORG 0x8100
@STACK_TOP

; ------------------------------------------------------
START

    IFDEF	DEBUG
    	; LD 		IX,CMD_LINE1
		LD		SP, STACK_TOP
		; JP 		MAIN_LOOP
    ENDIF

//	CALL	@WCOMMON.INIT_VMODE

    PRINTLN MSG_START

	CALL	ISA.ISA_RESET								; Reset ISA Devices

; ------------------------------------------------------
; Do Some
; ------------------------------------------------------

MAIN_LOOP

	; Find FT
	CALL	FT.FT_FIND
	LD		HL, MSG_NO_FT
	JR		C, MSG_NF_OUT
	; FT is Found
	;	A = ISA slot
	ADD		A, '1'										; 0x31
	LD		(MSG_SLOT_NO), A
	PRINTLN MSG_IS_FT

	; Activate
	;CALL	FT.FT_ACTIVATE
	LD		A, FT_MODE_800_600_60
	CALL	FT.FT_INIT

	; Get FT chip info
	PRINTLN MSG_GET_CHIP_ID
	CALL	FT.FT_GET_CHIP_ID

	LD		HL, FT.FT_BUFFER
	LD	 	DE, MSG_CTB
	LD		B, 4
.NXT_ID
	LD		C, (HL)
	CALL	UTIL.HEXB
	INC		HL
	DJNZ	.NXT_ID
	PRINTLN MSG_CHIP_TYPE


; ------------------------------------------------------
OK_EXIT
	LD		B, 0
NOK_EXIT
	DSS_EXEC    DSS_EXIT

	; Out message about FT slot
MSG_NF_OUT
	PRINTLN_HL
	LD		B, 1
	JR		NOK_EXIT

; ------------------------------------------------------
; Custom messages
; ------------------------------------------------------

MSG_START
	DB "Sprinter-FT tester by Sprinter Team. v1.0.b1, ", __DATE__, "\r\n", 0

MSG_NO_FT
	DB "Sprinter-FT not found!", 0

MSG_GET_CHIP_ID
	DB "Read Chip Identification Code", 0
MSG_IS_FT
	DB "Sprinter-FT found at ISA-"
MSG_SLOT_NO
	DB 0, 0

MSG_CHIP_TYPE
	DB "Chip type bytes: 0x"
MSG_CTB
	DS	9, 0

; ------------------------------------------------------
; Custom commands
; ------------------------------------------------------

	ENDMODULE

	INCLUDE "ftlib.asm"
	INCLUDE "util.asm"
	INCLUDE "isa.asm"

    END MAIN.START
