; ============================================================================
; Vector table, ROM header, entry point, region lockout check, VBlank stub
; ROM range $000000-$00077D
; ============================================================================

; 68000 exception vectors
VectorTable:
	dc.l	$00FFFFF6	;  0: initial stack pointer
	dc.l	EntryPoint	;  1: entry point
	dc.l	Exception_AddressError	;  2: bus error
	dc.l	Exception_AddressError	;  3: address error
	dc.l	Exception_IllegalInstr	;  4: illegal instruction
	dc.l	Exception_DivideByZero	;  5: zero divide
	dc.l	$FFFFFFFF	;  6: CHK
	dc.l	$FFFFFFFF	;  7: TRAPV
	dc.l	$FFFFFFFF	;  8: privilege violation
	dc.l	$FFFFFFFF	;  9: trace
	dc.l	$FFFFFFFF	; 10: line 1010 emulator
	dc.l	$FFFFFFFF	; 11: line 1111 emulator
	dc.l	$FFFFFFFF	; 12: reserved
	dc.l	$FFFFFFFF	; 13: reserved
	dc.l	$FFFFFFFF	; 14: reserved
	dc.l	$FFFFFFFF	; 15: uninitialised interrupt
	dc.l	$FFFFFFFF	; 16: reserved
	dc.l	$FFFFFFFF	; 17: reserved
	dc.l	$FFFFFFFF	; 18: reserved
	dc.l	$FFFFFFFF	; 19: reserved
	dc.l	$FFFFFFFF	; 20: reserved
	dc.l	$FFFFFFFF	; 21: reserved
	dc.l	$FFFFFFFF	; 22: reserved
	dc.l	$FFFFFFFF	; 23: reserved
	dc.l	Int_Null	; 24: spurious interrupt
	dc.l	Int_Null	; 25: IRQ level 1
	dc.l	Int_Null	; 26: IRQ level 2 (external)
	dc.l	Int_Null	; 27: IRQ level 3
	dc.l	Int_Null	; 28: IRQ level 4 (horizontal interrupt)
	dc.l	$00000000	; 29: IRQ level 5
	dc.l	VBlank_Dispatch	; 30: IRQ level 6 (vertical interrupt)
	dc.l	Int_Null	; 31: IRQ level 7
	dc.l	$00000000	; 32: TRAP #0
	dc.l	$00000000	; 33: TRAP #1
	dc.l	$00000000	; 34: TRAP #2
	dc.l	$00000000	; 35: TRAP #3
	dc.l	$FFFFFFFF	; 36: TRAP #4
	dc.l	$FFFFFFFF	; 37: TRAP #5
	dc.l	$FFFFFFFF	; 38: TRAP #6
	dc.l	$FFFFFFFF	; 39: TRAP #7
	dc.l	$FFFFFFFF	; 40: TRAP #8
	dc.l	$FFFFFFFF	; 41: TRAP #9
	dc.l	$FFFFFFFF	; 42: TRAP #10
	dc.l	$FFFFFFFF	; 43: TRAP #11
	dc.l	$FFFFFFFF	; 44: TRAP #12
	dc.l	$FFFFFFFF	; 45: TRAP #13
	dc.l	$FFFFFFFF	; 46: TRAP #14
	dc.l	$FFFFFFFF	; 47: TRAP #15
	dc.l	$FFFFFFFF	; 48: reserved
	dc.l	$FFFFFFFF	; 49: reserved
	dc.l	$FFFFFFFF	; 50: reserved
	dc.l	$FFFFFFFF	; 51: reserved
	dc.l	$FFFFFFFF	; 52: reserved
	dc.l	$FFFFFFFF	; 53: reserved
	dc.l	$FFFFFFFF	; 54: reserved
	dc.l	$FFFFFFFF	; 55: reserved
	dc.l	$FFFFFFFF	; 56: reserved
	dc.l	$FFFFFFFF	; 57: reserved
	dc.l	$FFFFFFFF	; 58: reserved
	dc.l	$FFFFFFFF	; 59: reserved
	dc.l	$FFFFFFFF	; 60: reserved
	dc.l	$FFFFFFFF	; 61: reserved
	dc.l	$FFFFFFFF	; 62: reserved
	dc.l	$FFFFFFFF	; 63: reserved

; ROM header
Header:
Header_Console:
	dc.b	"SEGA GENESIS    "	; console name
Header_Copyright:
	dc.b	"(C)T-5O 1997.SEP"	; copyright / release date
Header_DomesticName:
	dc.b	"NHL 98                                          "	; domestic name
Header_OverseasName:
	dc.b	"NHL 98                                          "	; overseas name
Header_Serial:
	dc.b	"GM T-172176-00"	; serial number
Header_Checksum:
	dc.w	$5B3A	; checksum (over $200-$7FFFF)
Header_IO:
	dc.b	"J4              "	; I/O support
Header_RomStart:
	dc.l	$00000000	; ROM start
Header_RomEnd:
	dc.l	$0007FFFF	; ROM end (as declared)
Header_RamStart:
	dc.l	$00FF0000	; RAM start
Header_RamEnd:
	dc.l	$00FFFFFF	; RAM end
Header_SRAM:
	dc.b	"            "	; SRAM info (none)
Header_Modem:
	dc.b	"            "	; modem info
Header_Notes:
	dc.b	"                                        "	; notes
Header_Region:
	dc.b	"4               "	; region


; ----------------------------------------------------------------------
; reset entry: TMSS, VDP and Z80 setup (skipped on soft reset), then Boot_RegionCheck
; called from $000004
EntryPoint:
	tst.l	(IO_CTRL1_L).l
	bne.s	loc_00020E
	tst.w	(IO_CTRL3_W).l
loc_00020E:
	bne.s	loc_00028C
	lea	BootParamTable(pc),a5
	movem.w	(a5)+,d5-d7
	movem.l	(a5)+,a0-a4
	move.b	-$10FF(a1),d0
	andi.b	#$F,d0
	beq.s	loc_00022E
	move.l	#$53454741,$2F00(a1)
loc_00022E:
	move.w	(a4),d0
	moveq	#$0,d0
	movea.l	d0,a6
	move.l	a6,usp
	moveq	#$17,d1
loc_000238:
	move.b	(a5)+,d5
	move.w	d5,(a4)
	add.w	d7,d5
	dbra	d1,loc_000238
	move.l	(a5)+,(a4)
	move.w	d0,(a3)
	move.w	d7,(a1)
	move.w	d7,(a2)
loc_00024A:
	btst	d0,(a1)
	bne.s	loc_00024A
	moveq	#$25,d2
loc_000250:
	move.b	(a5)+,(a0)+
	dbra	d2,loc_000250
	move.w	d0,(a2)
	move.w	d0,(a1)
	move.w	d7,(a2)
loc_00025C:
	move.l	d0,-(a6)
	dbra	d6,loc_00025C
	move.l	(a5)+,(a4)
	move.l	(a5)+,(a4)
	moveq	#$1F,d3
loc_000268:
	move.l	d0,(a3)
	dbra	d3,loc_000268
	move.l	(a5)+,(a4)
	moveq	#$13,d4
loc_000272:
	move.l	d0,(a3)
	dbra	d4,loc_000272
loc_000278:
	moveq	#$3,d5
loc_00027A:
	move.b	(a5)+,$11(a3)
	dbra	d5,loc_00027A
	move.w	d0,(a2)
	movem.l	(a6),d0-d7/a0-a6
	move.w	#$2700,sr
loc_00028C:
	bra.s	Boot_RegionCheck
; VDP register values, PSG mute data and Z80 init program used by EntryPoint
BootParamTable:
	dc.w	$8000,$3FFF,$0100,$00A0,$0000,$00A1,$1100,$00A1
	dc.w	$1200,$00C0,$0000,$00C0,$0004,$0414,$303C,$076C
	dc.w	$0000,$0000,$FF00,$8137,$0001,$0100,$00FF,$FF00
	dc.w	$0080,$4000,$0080,$AF01,$D91F,$1127
dat_0002CA:
	dc.w	$0021,$2600,$F977,$EDB0,$DDE1,$FDE1,$ED47,$ED4F
	dc.w	$D1E1,$F108,$D9C1,$D1E1,$F1F9,$F3ED,$5636,$E9E9
	dc.w	$8104,$8F02,$C000,$0000,$4000,$0010,$9FBF,$DFFF
; console version / region lockout check, draws the "DEVELOPED FOR USE ONLY WITH" screen
Boot_RegionCheck:
	tst.w	(VDP_CTRL).l
	clr.l	d0
	move.b	(HW_VERSION).l,d0
	lsr.b	#6,d0
	andi.b	#$3,d0
	cmpi.b	#$0,d0
	bne.s	loc_00031A
	lea	RegionTable_Ver0(pc),a6
	bra.s	loc_00033E
loc_00031A:
	cmpi.b	#$1,d0
	bne.s	loc_000326
	lea	RegionTable_Ver1(pc),a6
	bra.s	loc_00033E
loc_000326:
	cmpi.b	#$2,d0
	bne.s	loc_000332
	lea	RegionTable_Ver2(pc),a6
	bra.s	loc_00033E
loc_000332:
	cmpi.b	#$3,d0
	bne.w	loc_000464
	lea	RegionTable_Ver3(pc),a6
loc_00033E:
	clr.l	d6
	lea	(Header_Region).l,a0
	move.b	(a0),d6
	cmpi.b	#$40,d6
	blt.s	loc_000356
	move.b	#$37,d7
	sub.b	d7,d6
	bra.s	loc_00035A
loc_000356:
	lsl.b	#4,d6
	lsr.b	#4,d6
loc_00035A:
	move.b	d6,d7
	move.b	$0(a6,d6.w),d6
	tst.b	d6
	beq.w	Boot_JumpToMain
	lea	(VDP_DATA).l,a4
	lea	(VDP_CTRL).l,a5
	move.w	#$8164,(a5)
	move.w	#$8230,(a5)
	move.w	#$8C81,(a5)
	move.w	#$8F02,(a5)
	move.w	#$9001,(a5)
	move.l	#$C0020000,(a5)
	move.w	#$EEE,(a4)
	move.l	#$40000000,(a5)
	lea	Font_Boot1bpp(pc),a0
	move.w	#$3A,d0
loc_00039E:
	move.l	#$10000000,d2
loc_0003A4:
	move.w	#$7,d6
loc_0003A8:
	move.b	(a0)+,d1
	move.l	#$0,d4
	move.w	#$7,d5
loc_0003B4:
	rol.l	#4,d2
	ror.b	#1,d1
	bcc.s	loc_0003BC
	or.l	d2,d4
loc_0003BC:
	dbra	d5,loc_0003B4
	move.l	d4,(a4)
	dbra	d6,loc_0003A8
	dbra	d0,loc_0003A4
	cmpi.b	#$1,d7
	bne.s	loc_0003DC
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintNtscMegaDrive
	bra.w	loc_000458
loc_0003DC:
	cmpi.b	#$4,d7
	bne.s	loc_0003EE
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintNtscGenesis
	bra.w	loc_000458
loc_0003EE:
	cmpi.b	#$5,d7
	bne.s	loc_000408
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintNtscGenesis
	bsr.w	Region_PrintAnd
loc_000400:
	bsr.w	Region_PrintNtscMegaDrive
	bra.w	loc_000458
loc_000408:
	cmpi.b	#$A,d7
	bne.s	loc_00041A
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintPalMegaDrive
	bra.w	loc_000458
loc_00041A:
	cmpi.b	#$B,d7
	bne.s	loc_000434
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintNtscMegaDrive
	bsr.w	Region_PrintAnd
	bsr.w	Region_PrintPalMegaDrive
	bra.w	loc_000458
loc_000434:
	cmpi.b	#$C,d7
	bne.s	loc_00043C
	bra.s	loc_000442
loc_00043C:
	cmpi.b	#$E,d7
	bne.s	loc_000456
loc_000442:
	bsr.w	Region_PrintDevelopedFor
	bsr.w	Region_PrintNtscGenesis
	bsr.w	Region_PrintAnd
	bsr.w	Region_PrintPalMegaDrive
	bra.w	loc_000458
loc_000456:
	bra.s	loc_000464
loc_000458:
	lea	str_Systems(pc),a0
	move.b	(a0)+,d0
	addq.w	#1,d1
	bsr.w	Region_PrintString
loc_000464:
	bra.s	loc_000464


; ----------------------------------------------------------------------
; called from $0003D0, $0003E2, $0003F4, $00040E, $000420, $000442
Region_PrintDevelopedFor:
	move.b	#$8,d1
	lea	str_DevelopedFor(pc),a0
	move.b	(a0)+,d0
	bsr.w	Region_PrintString
	rts


; ----------------------------------------------------------------------
; called from $0003D4, $000400, $000424
Region_PrintNtscMegaDrive:
	lea	str_NtscMegaDrive(pc),a0
	move.b	(a0)+,d0
	addq.w	#1,d1
	bsr.w	Region_PrintString
	rts


; ----------------------------------------------------------------------
; called from $0003E6, $0003F8, $000446
Region_PrintNtscGenesis:
	lea	str_NtscGenesis(pc),a0
	move.b	(a0)+,d0
	addq.w	#1,d1
	bsr.w	Region_PrintString
	rts


; ----------------------------------------------------------------------
; called from $000412, $00042C, $00044E
Region_PrintPalMegaDrive:
	lea	str_PalSecamMegaDrive(pc),a0
	move.b	(a0)+,d0
	addq.w	#1,d1
	bsr.w	Region_PrintString
	rts


; ----------------------------------------------------------------------
; called from $0003FC, $000428, $00044A
Region_PrintAnd:
	lea	str_And(pc),a0
	move.b	(a0)+,d0
	addq.w	#1,d1
	bsr.w	Region_PrintString
	rts


; ----------------------------------------------------------------------
; a0 = length prefixed string, d0 = length, d1 = row; renders with the 1bpp boot font
; called from $000460, $000470, $00047E, $00048C, $00049A, $0004A8
Region_PrintString:
	move.b	d1,d2
	andi.l	#$FF,d2
	swap	d2
	lsl.l	#7,d2
	move.b	d0,d3
	andi.l	#$FF,d3
	swap	d3
	asl.l	#1,d3
	add.l	d3,d2
	addi.l	#$40000003,d2
	move.l	d2,(a5)
loc_0004D0:
	tst.b	(a0)
	beq.s	loc_0004E2
	move.b	(a0)+,d2
	subi.b	#$20,d2
	andi.w	#$FF,d2
	move.w	d2,(a4)
	bra.s	loc_0004D0
loc_0004E2:
	rts
; allowed region characters per hardware version (bits 7-6 of HW_VERSION)
RegionTable_Ver0:
	dc.w	$0100,$0100,$0100,$0100,$0100,$0100,$0100,$0100
RegionTable_Ver1:
	dc.w	$0101,$0000,$0101,$0000,$0101,$0000,$0101,$0000
RegionTable_Ver2:
	dc.w	$0101,$0101,$0000,$0000,$0101,$0101,$0000,$0000
RegionTable_Ver3:
	dc.w	$0101,$0101,$0101,$0101,$0000,$0000,$0000,$0000
str_DevelopedFor:
	dc.b	$06
	dc.b	"DEVELOPED FOR USE ONLY WITH",0
str_And:
	dc.b	$12,$26,$00
str_Systems:
	dc.b	$0F
	dc.b	"SYSTEMS.",0
str_NtscMegaDrive:
	dc.b	$0C
	dc.b	"NTSC MEGA DRIVE",0
str_NtscGenesis:
	dc.b	$0D
	dc.b	"NTSC GENESIS",0
str_PalSecamMegaDrive:
	dc.b	$04
	dc.b	"PAL AND FRENCH SECAM MEGA DRIVE",0
; 1 bit per pixel font used by the region lockout screen
Font_Boot1bpp:
	dc.w	$0000,$0000,$0000,$0000,$1818,$1818,$0018,$1800
	dc.w	$3636,$4800,$0000,$0000,$1212,$7F12,$7F24,$2400
	dc.w	$083F,$483E,$097E,$0800,$7152,$7408,$1725,$4700
	dc.w	$1824,$1829,$4546,$3900,$3030,$4000,$0000,$0000
	dc.w	$0C10,$2020,$2010,$0C00,$3008,$0404,$0408,$3000
	dc.w	$0008,$2A1C,$2A08,$0000,$0808,$087F,$0808,$0800
	dc.w	$0000,$0000,$0030,$3040,$0000,$007F,$0000,$0000
	dc.w	$0000,$0000,$0030,$3000,$0102,$0408,$1020,$4000
	dc.w	$1E33,$3333,$3333,$1E00,$1838,$1818,$1818,$3C00
	dc.w	$3E63,$630E,$3860,$7F00,$3E63,$031E,$0363,$3E00
	dc.w	$060E,$1E36,$667F,$0600,$7E60,$7E63,$0363,$3E00
	dc.w	$3E63,$607E,$6363,$3E00,$3F63,$0606,$0C0C,$1800
	dc.w	$3E63,$633E,$6363,$3E00,$3E63,$633F,$0363,$3E00
	dc.w	$0018,$1800,$0018,$1800,$0018,$1800,$0018,$1820
	dc.w	$030C,$3040,$300C,$0300,$0000,$7F00,$7F00,$0000
	dc.w	$6018,$0601,$0618,$6000,$3E63,$031E,$1800,$1800
	dc.w	$3C42,$3949,$4949,$3600,$1C1C,$3636,$7F63,$6300
	dc.w	$7E63,$637E,$6363,$7E00,$3E73,$6060,$6073,$3E00
	dc.w	$7E63,$6363,$6363,$7E00,$3F30,$303E,$3030,$3F00
	dc.w	$3F30,$303E,$3030,$3000,$3E73,$6067,$6373,$3E00
	dc.w	$6666,$667E,$6666,$6600,$1818,$1818,$1818,$1800
	dc.w	$0C0C,$0C0C,$CCCC,$7800,$6366,$6C78,$6C66,$6300
	dc.w	$6060,$6060,$6060,$7F00,$6377,$7F6B,$6B63,$6300
	dc.w	$6373,$7B7F,$6F67,$6300,$3E63,$6363,$6363,$3E00
	dc.w	$7E63,$637E,$6060,$6000,$3E63,$6363,$6F63,$3F00
	dc.w	$7E63,$637E,$6866,$6700,$3E63,$703E,$0763,$3E00
	dc.w	$7E18,$1818,$1818,$1800,$6666,$6666,$6666,$3C00
	dc.w	$6363,$6336,$361C,$1C00,$6B6B,$6B6B,$6B7F,$3600
	dc.w	$6363,$361C,$3663,$6300,$6666,$663C,$1818,$1800
	dc.w	$7F07,$0E1C,$3870,$7F00
Boot_JumpToMain:
	nop
	nop
	nop
	jmp	(Main_Init).l
; 4 zero bytes; pointers compare against this address as "no entry"
NullEntry:
	dc.b	$00,$00,$00,$00


; ----------------------------------------------------------------------
; level 6 interrupt: jumps through ram_VBlankVector
; called from $000078
VBlank_Dispatch:
	move.l	(VBlankVector).l,-(sp)
	rts
