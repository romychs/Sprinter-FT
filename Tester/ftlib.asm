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
	INCLUDE "ftlib.inc"

	MODULE	FT

; ------------------------------------------------------
; Reset ESP module
; ------------------------------------------------------

FT_RESET
    PUSH    AF,HL

    CALL    ISA.ISA_OPEN

	; TODO: FT Init code here

	XOR 	A
	LD		(PORT_FT_CTRL),A

    CALL    ISA.ISA_CLOSE

    ; wait 2s for ESP firmware boot
    LD      HL,2000
    CALL    UTIL.DELAY

    POP     HL,AF
    RET

; ------------------------------------------------------
; Init FT videomode
; Inp: A - videomode
; ------------------------------------------------------
FT_INIT
	LD		H, 0
	LD		L, A
	CALL	UTIL.MUL_10
	LD		IX, FT_MODE
	ADD		IX, BC										; IX -> Mode parameters

  	ft_cmd	FT_CMD_PWRDOWN
  	ft_cmd	FT_CMD_ACTIVE
  	ft_cmd	FT_CMD_SLEEP
  	ft_cmd	FT_CMD_CLKEXT

	LD		A, (IX + f_mul)								; ft_cmdp(FT_CMD_CLKSEL, mode->f_mul | 0x40);
	AND		0x40
	LD		C, A
	LD		B, FT_CMD_CLKSEL
	CALL	FT_CMD_P

  	ft_cmd	FT_CMD_ACTIVE
  	ft_cmd	FT_CMD_RST_PULSE

	; Wait for reset complete
	; while ft_rreg8(FT_REG_ID) != FT_ID)
.IN_CMPL1
	ft_rreg8 FT_REG_ID
	CP	FT_ID
	JP	NZ, .IN_CMPL1
	; while (ft_rreg16(FT_REG_CPURESET) != 0);
.IN_CMPL2
	ft_rreg16 FT_REG_CPURESET
	LD	A, B
	OR	C
	JP	NZ, .IN_CMPL2

	; TODO: Init videomode

	RET

; ------------------------------------------------------
; Check ISA slots for Sprinter-FT card
; Out:	CF if no card found;
; 		A = Slot number, 0 - ISA-1, 1 - ISA2
; ------------------------------------------------------
FT_FIND
	PUSH	BC, HL

	LD		HL, ISA.ISA_SLOT
	XOR		A
	LD		(HL),A
	LD		B,2

.FT_CHK_SLOT:
	CALL	ISA.ISA_OPEN
	LD		A,	(PORT_FT_CTRL)
	CALL	ISA.ISA_CLOSE
	CP		0xFC
	JR		Z, .FT_FOUND
	; HL -> ISA.ISA_SLOT
	INC		(HL)
	DJNZ	.FT_CHK_SLOT
	SCF
.FT_FOUND
	LD		A, (HL)
	POP		HL, BC
	RET

; ------------------------------------------------------
; Activate FT chip. Sent ACTIVE command
; ------------------------------------------------------
FT_ACTIVATE
	XOR		A
	LD		B, A
	LD		C,  A
	CALL	FT_CMD_P
	RET

; ------------------------------------------------------
; Get FT chip info
; Out:	A = 0x10..0x14 for FT810-814
; 		DE -> response buffer: 0x08, id=0x10..0x14, 0x01, 0x00
; ------------------------------------------------------
FT_GET_CHIP_ID
	;PUSH		HL
	CALL	ISA.ISA_OPEN
	LD		HL, PORT_FT_DATA
	LD		BC, PORT_FT_CTRL

	; #FT_CS="0" active
	LD		A,	(BC)
	OR 		FT_CS_ON
	LD		(BC), A

	; Send cmd read addr 0xC0000
	LD		A, 0x0C
	LD		(HL), A										; addr3
	XOR		A
	LD		(HL), A										; addr2
	NOP
	LD		(HL), A										; addr1
	NOP
	LD		(HL), A										; dummy

	; Get response (4 bytes)
	LD 		DE, FT_BUFFER

	LD		A, (HL)										; dummy ZC
	NOP

	LD		A, (HL)
	LD		(DE), A
	INC		DE

	LD		A, (HL)
	LD		(DE), A
	;PUSH	AF
	INC		DE

	LD		A, (HL)
	LD		(DE), A
	INC		DE

	LD		A, (HL)
	LD		(DE), A
	INC		DE

	; #FT_CS="1" deactivate
	LD		A,	(BC)
	AND 	FT_CS_OFF
	LD		(BC), A

	; close ISA and return
	CALL	ISA.ISA_CLOSE
	;LD 		DE, FT_BUFFER
	;POP 	AF
	RET


; ------------------------------------------------------
; Send command to FT
; Inp:	A - cmd to send
; ------------------------------------------------------
FT_CMD_P
	PUSH 	BC
	LD		B, A
	LD		C, 0
	CALL    FT_CMD
	POP		BC
	RET

; ------------------------------------------------------
; Send command to FT
; Inp:	B - cmd code;
;		C = cmd parameter
; ------------------------------------------------------
FT_CMD
	PUSH	HL, DE
	CALL	START_SPI
	; Send cmd
	LD		A, B										; code
	LD		(HL), A										;
	LD		A, C										; parameter
	LD		(HL), A										;
	XOR		A
	LD		(HL), A										; dummy 0
	CALL	STOP_SPI
	POP		DE, HL
	RET

; ------------------------------------------------------
; Read 8 bit FT register
; Inp: BC - Register
; Out: A - value
; ------------------------------------------------------
FT_RREG8
	PUSH	HL, DE
	CALL	START_SPI

    LD		A, FT_RAM_REG >> 16
    LD		(HL), A
    NOP
    LD		(HL), B
    NOP
    LD		(HL), C
    NOP
    LD		(HL), C										; dummy (FT812)
	NOP
    LD		A, (HL)										; dummy (ZC)
	NOP
    LD		B, (HL)
	CALL	STOP_SPI
	LD		A, B
	POP		DE, HL
	RET


; ------------------------------------------------------
; Read 16 bit FT register
; Inp: BC - Register
; Out: BC - value
; ------------------------------------------------------
FT_RREG16
	PUSH	HL, DE
	CALL	START_SPI

    LD		A, FT_RAM_REG >> 16
    LD		(HL), A
    NOP
    LD		(HL), B
    NOP
    LD		(HL), C
    NOP
    LD		(HL), C										; dummy FT

    NOP
    LD		A, (HL)										; dummy (ZC)
    NOP
    LD		B, (HL)
    NOP
    LD		C, (HL)

	CALL	STOP_SPI
	POP		DE, HL
	RET


; ------------------------------------------------------
; Open ISA and apply FT_CS=0 (active)
; ------------------------------------------------------
START_SPI
	CALL	ISA.ISA_OPEN
	LD		HL, PORT_FT_DATA
	LD		DE, PORT_FT_CTRL

	; #FT_CS="0" active
	LD		A,	(DE)
	OR 		FT_CS_ON
	LD		(DE), A
	RET

; ------------------------------------------------------
; Apply FT_CS=1 (passive) and close ISA
; ------------------------------------------------------
STOP_SPI
	; #FT_CS="1" deactivate
	LD		A,	(DE)
	AND 	FT_CS_OFF
	LD		(DE), A

	; close ISA and return
	CALL	ISA.ISA_CLOSE
	RET



; ------------------------------------------------------
; Read byte from FT (ISA will be opened)
; Inp:	DE -> buffer to receive byte
; Out:	A - received byte;
; 		DE = DE+1
; ------------------------------------------------------
FT_READ_BYTE
	LD		A, (PORT_FT_DATA)
	LD		(DE), A
	INC		DE
	RET

FT_BUFFER DS FT_BUFFER_SIZE, 0


	ENDMODULE

	ENDIF
