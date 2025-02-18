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
	JR		C, MSG_FNF_OUT
	; FT is Found
	LD		A, (ISA.ISA_SLOT)
	INC		A
	LD		L, A
	LD		H, 0
	LD		DE, MSG_SLOT_NO
	CALL	UTIL.FAST_UTOA
	LD		HL, MSG_IS_FT
	; Out message about FT slot
MSG_FNF_OUT
	PRINTLN_HL


OK_EXIT
	LD		B,0
	DSS_EXEC    DSS_EXIT

; ------------------------------------------------------
; Custom messages
; ------------------------------------------------------

MSG_START
	DB "FTTest for Sprinter-FT by Sprinter Team. v1.0.b1, ", __DATE__, "\r\n", 0

MSG_NO_FT
	DB "Sprinter-FT not found!",0


MSG_IS_FT
	DB "Sprinter-FT found at ISA"
MSG_SLOT_NO
	DB 0,0,0

;MSG_EXIT
;	DB "Bye!",0

; ------------------------------------------------------
; Custom commands
; ------------------------------------------------------

	ENDMODULE

	INCLUDE "ftlib.asm"
	INCLUDE "util.asm"
	INCLUDE "isa.asm"

    END MAIN.START
