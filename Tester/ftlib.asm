; ======================================================
; Library for Sprinter-FT ISA Card
; By Roman Boykov. Copyright (c) 2025
; https://github.com/romychs
; License: BSD 3-Clause
; ======================================================

    IFNDEF  _FT_LIB
    DEFINE  _FT_LIB


    INCLUDE "isa.asm"
    INCLUDE "util.asm"


FT_CTRL			EQU 0x77
FT_DATA			EQU 0x57

PORT_FT_CTRL	EQU ISA_BASE_A + FT_CTRL			; Memory address to read Strinter-FT Control port
PORT_FT_DATA    EQU ISA_BASE_A + FT_DATA			; Memory address to read Strinter-FT Data port

	MODULE	FT

; ------------------------------------------------------
; Reset ESP module
; ------------------------------------------------------

FT_RESET
    PUSH    AF,HL

    CALL    ISA.ISA_OPEN

; TODO: FT Init code here

    CALL    ISA.ISA_CLOSE

    ; wait 2s for ESP firmware boot
    LD      HL,2000
    CALL    UTIL.DELAY

    POP     HL,AF
    RET

; ------------------------------------------------------
; Check ISA slots for Sprinter-FT card
; Out:	CF if no card found
; 		(ISA.ISA_SLOT) = slot no 0 - ISA1, 1-ISA2
; ------------------------------------------------------
FT_FIND
	PUSH	BC, HL

	XOR		A
	LD		B,2
	LD		(ISA.ISA_SLOT),A

.FT_CHK_SLOT:
	CALL	ISA.ISA_OPEN
	LD		A,	(PORT_FT_CTRL)
	CALL	ISA.ISA_CLOSE
	CP		0xFC
	JR		Z, .FT_FOUND
	LD		HL, ISA.ISA_SLOT
	INC		(HL)
	DJNZ	.FT_CHK_SLOT
	SCF
.FT_FOUND
	POP		HL, BC
	RET

	ENDMODULE

	ENDIF
