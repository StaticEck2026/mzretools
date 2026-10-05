; ============================================================================
; Sound call wrapper and sound effect helpers
; ROM range $091F88-$0924C1
; ============================================================================


; ----------------------------------------------------------------------
; d0 = function number (index into Sound_FuncTable), other arguments per function
; called from $018F80, $018F8A, $018F9C, $018FAA, $0190CA, $0190DE, $0190F0, $0190FE (+64 more)
Sound_Call:
	jsr	(Sound_Dispatch).l
	bcc.w	loc_091F94
	nop
loc_091F94:
	rts


; ----------------------------------------------------------------------
; called from $019464
sub_091F96:
	move.w	(ram_B8BA).w,d0
	cmp.w	(ram_B8BC).w,d0
	bls.w	loc_091FA6
	move.w	d0,(ram_B8BC).w
loc_091FA6:
	ext.l	d0
	add.l	d0,(ram_B8C0).w
	addq.w	#1,(ram_B8BE).w
	subq.w	#1,(ram_B8BA).w
	bpl.w	loc_091FBC
	clr.w	(ram_B8BA).w
loc_091FBC:
	rts


; ----------------------------------------------------------------------
; called from $01943E, $1E46F6
sub_091FBE:
	move.w	(ram_B8B4).w,d0
	asl.w	#3,d0
	addi.w	#$400,d0
	cmp.w	#$EFF,d0	; general form
	bls.w	loc_091FD4
	move.w	#$EFF,d0
loc_091FD4:
	moveq	#$28,d2
	sub.w	(ram_B05A).w,d0
	cmp.w	d2,d0
	bgt.w	loc_091FE8
	neg.w	d2
	cmp.w	d2,d0
	bge.w	loc_091FF4
loc_091FE8:
	add.w	d2,(ram_B05A).w
	bpl.w	loc_091FF4
	clr.w	(ram_B05A).w
loc_091FF4:
	move.b	#$C8,(PSG).l
	move.b	#$1,(PSG).l
	move.b	(ram_B05A).w,d0
	eori.b	#$F,d0
	ori.b	#$F0,d0
	move.b	d0,(PSG).l
	rts


; ----------------------------------------------------------------------
; called from $01946A
sub_092018:
	cmpi.w	#$2,(ram_C4C8).w
	bne.w	loc_092058
	btst	#4,(ram_C33A).w
	bne.w	loc_092058
	move.w	(ram_C4CA).w,d0
	cmp.w	(ram_B05E).w,d0
	bgt.w	loc_092058
	st	(ram_B05E).w
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$6,(ram_D4AC).w
	jsr	(sub_092274).l
	move.w	(ram_D4A8).w,-(sp)
	jsr	(sub_092172).l
loc_092058:
	rts


; ----------------------------------------------------------------------
; called from $00C92C, $00EEC4, $00EF16, $00F018, $00F06A, $00F0CE, $013212, $0135AE (+28 more)
sub_09205A:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.l	d0
	move.w	$40(sp),d0
	bpl.w	loc_092074
	movem.l	(sp)+,d0-d7/a0-a6
	move.l	(sp),$2(sp)
	addq.w	#2,sp
	rts
loc_092074:
	cmp.w	#$B,d0	; general form
	beq.w	loc_092084
	cmp.w	#$C,d0	; general form
	bne.w	loc_092086
loc_092084:
	nop
loc_092086:
	cmp.w	#$57,d0	; general form
	bgt.w	loc_092132
	cmp.w	#$32,d0	; general form
	blt.w	loc_09209E
	move.w	d0,(ram_D2C0).w
	bra.w	loc_092118
loc_09209E:
	movea.l	#dat_09213E,a1
	tst.b	$0(a1,d0.w)
	bmi.w	loc_092132
	cmpi.b	#$26,$0(a1,d0.w)
	bne.w	loc_092100
	movem.l	d0-d4/a0/a1,-(sp)
	movea.l	#ram_FDFE,a0
	movea.w	#$FE3E,a1
	move.w	#$7,d4
	clr.w	d3
loc_0920CA:
	cmpi.l	#$FFFFFFFF,(a0)
	beq.w	loc_0920F4
	cmpi.w	#$31,$0(a1,d3.w)
	ble.w	loc_0920F4
	move.w	$0(a1,d3.w),d1
	move.w	#$5,d0
	move.w	#$FFFF,d2
	jsr	(Sound_Dispatch).l
	bra.w	loc_0920FC
loc_0920F4:
	addq.w	#4,a0
	addq.w	#2,d3
	dbra	d4,loc_0920CA
loc_0920FC:
	movem.l	(sp)+,d0-d4/a0/a1
loc_092100:
	cmp.w	#$B,d0	; general form
	beq.w	loc_092114
	cmp.w	#$C,d0	; general form
	beq.w	loc_092114
	move.w	d0,(ram_C066).w
loc_092114:
	move.b	$0(a1,d0.w),d0
loc_092118:
	ext.w	d0
	move.w	d0,d1
	move.w	#$4,d0
	move.w	#$FFFF,d2
	move.w	#$7F,d3
	move.w	#$100,d4
	jsr	(Sound_Call).l
loc_092132:
	movem.l	(sp)+,d0-d7/a0-a6
	move.l	(sp),$2(sp)
	addq.w	#2,sp
	rts
dat_09213E:
	dc.w	$261C,$1D17,$16FF,$0925,$045A,$5B10,$1E13,$200E
	dc.w	$0B0B,$0B0B,$0808,$0808,$0808,$0808,$2123,$2322
	dc.w	$1815,$1515,$2504,$0404,$1818,$1818,$111A,$1A5C
	dc.w	$5D2E,$5FFF


; ----------------------------------------------------------------------
; called from $00C75A, $00F114, $015AA6, $0165D0, $019372, $0193EA, $01DE1C, $0213A0 (+10 more)
sub_092172:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.l	d0
	move.w	$40(sp),d0
	bmi.w	loc_0921AC
	cmp.w	#$32,d0	; general form
	blt.w	loc_09219A
	cmp.w	#$55,d0	; general form
	bgt.w	loc_09219A
	jsr	(sub_0921E8).l
	move.w	d0,(ram_D2C0).w
loc_09219A:
	cmp.w	#$3,d0	; general form
	ble.w	loc_0921A6
	bra.w	loc_092074
loc_0921A6:
	jsr	(sub_0921B8).l
loc_0921AC:
	movem.l	(sp)+,d0-d7/a0-a6
	move.l	(sp),$2(sp)
	addq.w	#2,sp
	rts


; ----------------------------------------------------------------------
; called from $0921A6
sub_0921B8:
	tst.w	d0
	bmi.w	loc_0921E6
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_0921E8
	move.w	d0,(ram_D2C0).w
	move.w	d0,d1
	move.w	#$4,d0
	move.w	#$FFFF,d2
	move.w	#$7F,d3
	move.w	#$100,d4
	jsr	(Sound_Call).l
	movem.l	(sp)+,d0-d7/a0-a6
loc_0921E6:
	rts


; ----------------------------------------------------------------------
; called from $0190C0, $0192BC, $0193E0, $019572, $019848, $019898, $01A302, $021A42 (+8 more)
sub_0921E8:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$5,d0
	move.w	(ram_D2C0).w,d1
	bmi.w	loc_092208
	move.w	#$FFFF,d2
	jsr	(Sound_Call).l
	move.w	#$FFFF,(ram_D2C0).w
loc_092208:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_09220E:
	tst.w	(ram_D2C0).w
	bmi.w	loc_092236
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$5,d0
	move.w	(ram_D2C0).w,d1
	move.w	#$FFFF,d2
	jsr	(Sound_Call).l
	movem.l	(sp)+,d0-d7/a0-a6
	move.w	#$FFFF,(ram_D2C0).w
loc_092236:
	rts


; ----------------------------------------------------------------------
sub_092238:
	move.b	#$E7,(PSG).l
	move.b	#$DF,(PSG).l
	move.b	#$C8,(PSG).l
	move.b	#$1,(PSG).l
	move.b	#$FF,(PSG).l
	rts


; ----------------------------------------------------------------------
; called from $018FB0, $019258, $019752, $026C24, $1E4636, $1E470A
sub_092262:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$F,d0
	bsr.w	Sound_Call
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00C0B6, $019368, $01DDF8, $01DE12, $023F16, $092048, $1D224C, $1D2268
sub_092274:
	movem.l	d0/d1/a0/a1,-(sp)
	btst	#4,(ram_C33A).w
	beq.w	loc_09228A
	move.w	#$FFFF,d1
	bra.w	loc_0922C4
loc_09228A:
	bclr	#6,(ram_C34E).w
	movea.l	#dat_0922D0,a0
	movea.l	#dat_092443,a1
	move.w	(ram_D4AA).w,d0
	mulu.w	#$7,d0
	add.w	(ram_D4AC).w,d0
	clr.w	d1
	move.b	$0(a0,d0.w),d1
	bne.w	loc_0922C4
	move.w	#$8,d0
	jsr	(Random).l
	andi.w	#$7,d0
	move.b	$0(a1,d0.w),d1
loc_0922C4:
	ext.w	d1
	move.w	d1,(ram_D4A8).w
	movem.l	(sp)+,d0/d1/a0/a1
	rts
dat_0922D0:
	dc.b	"V:@ITF",0
	dc.b	"VQB@",0
	dc.b	"FQV3223F",0
	dc.b	"W4545IIV6976FNVHIH",0
	dc.b	"FIVQBB",0
	dc.b	$46,$00
	dc.b	"V8?9",0
	dc.b	"F?W;QQ",0
	dc.b	$46,$00
	dc.b	"VEH<UF",0
	dc.b	"V=>E>F=V??95F@W?U?DFCV272",0
	dc.b	"F8V2B2AFAVQB2",0
	dc.b	$46,$00
	dc.b	"WJ59RF",0
	dc.b	"VE7E3",0
	dc.b	"3V2?U",0
	dc.b	$46,$00
	dc.b	"V4E4GFGVJJKLMNVPBBPFCVQRR",0
	dc.b	$46,$00
	dc.b	"W44S",0
	dc.b	$46,$00
	dc.b	"WCBT",0
	dc.b	$46,$00
	dc.b	"V?2?",0
	dc.b	"FJVQB2",0
	dc.b	$46,$00
	dc.b	"VQB2",0
	dc.b	$46,$00
	dc.b	"W2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
	dc.b	"V2?U",0
	dc.b	$46,$00
dat_092443:
	dc.b	"3=>A3GNO"
	dc.b	$FF


; ----------------------------------------------------------------------
Z80_Reset:
	movem.l	d0-d2/a0-a2,-(sp)
	bsr.w	sub_092494
	move.w	#$100,(Z80_RESET).l
	move.w	#$100,(Z80_BUSREQ).l
loc_092464:
	btst	#0,(Z80_BUSREQ).l
	bne.s	loc_092464
	move.w	#$0,(Z80_RESET).l
	move.w	#$0,(Z80_BUSREQ).l
	move.w	#$1F4,d0
loc_092482:
	dbra	d0,loc_092482
	move.w	#$100,(Z80_RESET).l
	movem.l	(sp)+,d0-d2/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $092450
sub_092494:
	move.w	#$FFFF,(ram_D2C0).w
	rts


; ----------------------------------------------------------------------
; called from $022CE8, $02398E
sub_09249C:
	move.l	d0,-(sp)
	moveq	#$3,d0
	jsr	(Random).l
	addq.w	#1,d0
	add.w	(ram_C064).w,d0
	andi.w	#$3,d0
	move.w	d0,(ram_C064).w
	addi.w	#$1C,d0
	move.w	d0,-(sp)
	bsr.w	sub_09205A
	move.l	(sp)+,d0
	rts

