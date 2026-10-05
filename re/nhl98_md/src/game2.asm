; ============================================================================
; Game engine, second part: AI, animation, in-game screens
; ROM range $022A82-$0288B1
; ============================================================================


; ----------------------------------------------------------------------
; called from $00CAE0
sub_022A82:
	clr.w	(ram_BFF0).w
	btst	#7,(ram_C33C).w
	beq.w	loc_022A92
	exg	d2,d3
loc_022A92:
	btst	#2,$62(a3)
	bne.w	loc_022AF8
	movem.l	d0-d7,-(sp)
	move.w	(a3),d2
	move.w	$14(a3),d3
	move.w	$4A(a3),(ram_BD3A).w
	move.w	$4C(a3),(ram_BD3C).w
	bsr.w	sub_023AA2
	move.w	$4E(a3),d0
	or.w	$50(a3),d0
	bne.w	loc_022AF0
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_022AF0
	movem.l	(sp),d0-d7
	move.l	a3,-(sp)
	bsr.w	sub_01F1F0
	move.w	(a3),d2
	move.w	$14(a3),d3
	add.w	d0,d2
	add.w	d1,d3
	move.w	#$1,(ram_BD3A).w
	move.w	#$1,(ram_BD3C).w
	bsr.w	sub_023AA2
loc_022AF0:
	movem.l	(sp)+,d0-d7
	bsr.w	sub_022B7C
loc_022AF8:
	tst.w	(ram_BFF0).w
	bne.w	loc_022B70
	move.w	$52(a3),d0
	asl.w	#1,d0
	movea.w	#$B880,a0
	movea.w	#$B8A0,a1
	movea.w	#$B860,a2
	move.w	$0(a0,d0.w),d1
loc_022B16:
	cmp.w	#$F,d1	; general form
	beq.w	loc_022B40
	clr.w	d4
	move.b	$1(a1,d1.w),d4
	cmp.w	$0(a2,d4.w),d3
	ble.w	loc_022B40
	addq.w	#1,$0(a0,d0.w)
	subq.w	#1,$0(a0,d4.w)
	move.b	d4,$0(a1,d1.w)
	move.b	d0,$1(a1,d1.w)
	addq.w	#1,d1
	bra.s	loc_022B16
loc_022B40:
	move.w	$0(a0,d0.w),d1
	beq.w	loc_022B6A
loc_022B48:
	clr.w	d4
	move.b	-$1(a1,d1.w),d4
	cmp.w	$0(a2,d4.w),d3
	bge.w	loc_022B6A
	subq.w	#1,$0(a0,d0.w)
	addq.w	#1,$0(a0,d4.w)
	move.b	d4,$0(a1,d1.w)
	move.b	d0,-$1(a1,d1.w)
	subq.w	#1,d1
	bne.s	loc_022B48
loc_022B6A:
	move.w	d3,$0(a2,d0.w)
	rts
loc_022B70:
	move.w	$1C(a3),(a3)
	move.w	$20(a3),$14(a3)
	rts


; ----------------------------------------------------------------------
; called from $022AF4
sub_022B7C:
	btst	#5,$63(a3)
	bne.w	loc_022BEE
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_022BEE
	move.w	$52(a3),d0
	asl.w	#1,d0
	movea.w	#$B880,a0
	movea.w	#$B8A0,a1
	movea.w	#$B860,a2
	move.w	$0(a0,d0.w),d1
loc_022BA6:
	cmp.w	#$F,d1	; general form
	beq.w	loc_022BCA
	clr.w	d4
	move.b	$1(a1,d1.w),d4
	move.w	$0(a2,d4.w),d5
	sub.w	d3,d5
	cmp.w	#$10,d5	; general form
	bgt.w	loc_022BCA
	bsr.w	sub_022BF0
	addq.w	#1,d1
	bra.s	loc_022BA6
loc_022BCA:
	move.w	$0(a0,d0.w),d1
	beq.w	loc_022BEE
loc_022BD2:
	clr.w	d4
	move.b	-$1(a1,d1.w),d4
	move.w	d3,d5
	sub.w	$0(a2,d4.w),d5
	cmp.w	#$10,d5	; general form
	bgt.w	loc_022BEE
	bsr.w	sub_022BF0
	subq.w	#1,d1
	bne.s	loc_022BD2
loc_022BEE:
	rts


; ----------------------------------------------------------------------
; called from $022BC2, $022BE6
sub_022BF0:
	movem.l	d0-d7/a0-a3,-(sp)
	asl.w	#6,d4
	movea.l	#ram_B060,a2
	adda.w	d4,a2
	btst	#2,$62(a2)
	bne.w	loc_022DE6
	btst	#5,$63(a2)
	bne.w	loc_022DE6
	cmpi.w	#$B,$52(a2)
	bgt.w	loc_022DE6
	move.w	(a2),d0
	btst	#7,(ram_C33C).w
	beq.w	loc_022C2C
	move.w	$14(a2),d0
loc_022C2C:
	sub.w	d2,d0
	cmp.w	#$FFF0,d0	; general form
	blt.w	loc_022DE6
	cmp.w	#$10,d0	; general form
	bgt.w	loc_022DE6
	muls.w	d5,d5
	muls.w	d0,d0
	add.l	d5,d0
	cmp.l	#$100,d0	; general form
	bgt.w	loc_022DE6
	move.w	#$0,(ram_BFF2).w
	move.b	$62(a3),d6
	move.b	$62(a2),d0
	eor.b	d0,d6
	move.w	$28(a3),d0
	sub.w	$28(a2),d0
	move.w	$2A(a3),d1
	sub.w	$2A(a2),d1
	move.w	(a3),d2
	sub.w	(a2),d2
	neg.w	d2
	move.w	$14(a3),d3
	sub.w	$14(a2),d3
	neg.w	d3
	movem.w	d0/d1,-(sp)
	muls.w	d3,d1
	muls.w	d2,d0
	add.l	d0,d1
	bmi.w	loc_022E3A
	asr.l	#4,d1
	btst	#6,d6
	beq.w	loc_022CFC
	move.w	d1,d4
	lsr.w	#8,d4
	cmp.w	#$5,d4	; general form
	bgt.w	loc_022CA4
	moveq	#$5,d4
loc_022CA4:
	add.w	d4,$32(a3)
	add.w	d4,$32(a2)
	btst	#0,$63(a2)
	bne.w	loc_022CBC
	move.w	$52(a3),$2E(a2)
loc_022CBC:
	btst	#0,$63(a3)
	bne.w	loc_022CCC
	move.w	$52(a2),$2E(a3)
loc_022CCC:
	cmp.w	#$14,d4	; general form
	blt.w	loc_022CEE
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	beq.w	loc_022CE8
	cmp.w	$52(a2),d0
	bne.w	loc_022CEE
loc_022CE8:
	jsr	(sub_09249C).l
loc_022CEE:
	bsr.w	sub_022E3E
	bsr.w	sub_022FC6
	jsr	(sub_00E756).l
loc_022CFC:
	move.w	d1,d4
	movem.w	(sp)+,d0/d1
	tst.w	(ram_BFF0).w
	bmi.w	loc_022DE6
	movem.l	d0/a0,-(sp)
	movea.l	a3,a0
	bsr.w	sub_022DEC
	movea.l	a2,a0
	bsr.w	sub_022DEC
	movem.l	(sp)+,d0/a0
	muls.w	d2,d1
	muls.w	d3,d0
	sub.l	d1,d0
	asr.l	#4,d0
	move.w	d0,d5
	clr.w	d0
	move.b	$68(a3),d0
	tst.w	$34(a3)
	bne.w	loc_022D3A
	move.b	#$78,d0
loc_022D3A:
	tst.w	$34(a2)
	bne.w	loc_022D44
	clr.b	d0
loc_022D44:
	addi.w	#$8C,d0
	clr.w	d1
	move.b	$68(a2),d1
	tst.w	$34(a2)
	bne.w	loc_022D5A
	move.b	#$78,d1
loc_022D5A:
	tst.w	$34(a3)
	bne.w	loc_022D64
	clr.b	d1
loc_022D64:
	addi.w	#$8C,d1
	move.w	(ram_BFF2).w,d7
	mulu.w	d1,d7
	lsr.w	#4,d7
	add.w	d0,d1
	sub.w	d7,d0
	muls.w	d4,d0
	divs.w	d1,d0
	move.w	(ram_BFF2).w,d1
	muls.w	d4,d1
	asr.w	#4,d1
	add.w	d0,d1
	movem.w	d2/d3,-(sp)
	muls.w	d5,d3
	muls.w	d0,d2
	add.l	d2,d3
	asr.l	#4,d3
	tst.w	$34(a3)
	beq.w	loc_022D9A
	add.w	$28(a2),d3
loc_022D9A:
	tst.w	$34(a3)
	bne.w	loc_022DA4
	asr.w	#2,d3
loc_022DA4:
	move.w	d3,$28(a3)
	movem.w	(sp),d2/d3
	muls.w	d5,d2
	muls.w	d0,d3
	sub.l	d2,d3
	asr.l	#4,d3
	tst.w	$34(a3)
	beq.w	loc_022DC0
	add.w	$2A(a2),d3
loc_022DC0:
	tst.w	$34(a3)
	bne.w	loc_022DCA
	asr.w	#2,d3
loc_022DCA:
	move.w	d3,$2A(a3)
	movem.w	(sp)+,d2/d3
	muls.w	d1,d2
	asr.l	#4,d2
	add.w	d2,$28(a2)
	muls.w	d1,d3
	asr.l	#4,d3
	add.w	d3,$2A(a2)
	st	(ram_BFF0).w
loc_022DE6:
	movem.l	(sp)+,d0-d7/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $022D10, $022D16
sub_022DEC:
	tst.w	$34(a0)
	beq.w	loc_022E38
	btst	#3,$62(a0)
	beq.w	loc_022E38
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a0),d0
	bne.w	loc_022E38
	move.w	$28(a0),d0
	bpl.w	loc_022E14
	neg.w	d0
loc_022E14:
	cmp.w	#$2,d0	; general form
	bgt.w	loc_022E38
	move.w	$2A(a0),d0
	bpl.w	loc_022E26
	neg.w	d0
loc_022E26:
	cmp.w	#$2,d0	; general form
	bgt.w	loc_022E38
	st	(ram_B7C0).w
	move.b	#$1E,$5E(a0)
loc_022E38:
	rts
loc_022E3A:
	addq.w	#4,sp
	bra.s	loc_022DE6


; ----------------------------------------------------------------------
; called from $022CEE
sub_022E3E:
	move.l	d0,-(sp)
	bsr.w	sub_022E50
	exg	a2,a3
	bsr.w	sub_022E50
	exg	a2,a3
	move.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $022E40, $022E46
sub_022E50:
	tst.w	$34(a2)
	bne.w	NullSub
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	tst.b	(ram_DE7F).w
	bne.w	loc_022E8A
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	beq.w	loc_022E80
	cmpi.w	#$19,$32(a3)
	ble.w	NullSub
loc_022E80:
	cmpi.w	#$2,$32(a3)
	ble.w	NullSub
loc_022E8A:
	btst	#6,$62(a2)
	beq.w	loc_022EA2
	btst	#3,(ram_C35C).w
	beq.w	loc_022EAC
	bra.w	loc_022F04
loc_022EA2:
	btst	#2,(ram_C35C).w
	bne.w	loc_022F04
loc_022EAC:
	tst.w	$34(a2)
	bne.w	loc_022F04
	btst	#7,(ram_C350).w
	bne.w	loc_022F04
	btst	#0,(ram_C34A).w
	bne.w	loc_022F04
	tst.b	(ram_DE80).w
	bne.w	loc_022EE2
	move.w	#$3E8,d0
	jsr	(Random).l
	cmp.w	#$9,d0	; general form
	bgt.w	loc_022F04
loc_022EE2:
	btst	#6,$62(a2)
	beq.w	loc_022EF6
	bset	#3,(ram_C35C).w
	bra.w	loc_022EFC
loc_022EF6:
	bset	#2,(ram_C35C).w
loc_022EFC:
	bsr.w	sub_023484
	bra.w	loc_022F16
loc_022F04:
	exg	a2,a3
	bsr.w	sub_023484
	exg	a2,a3
	cmpi.w	#$14,$32(a2)
	ble.w	NullSub
loc_022F16:
	btst	#4,$63(a3)
	bne.w	NullSub
	cmpi.w	#$3,(ram_C4C8).w
	beq.w	NullSub
	tst.w	$34(a2)
	bne.w	NullSub
	move.w	#$1,d0
	btst	#6,$62(a3)
	beq.w	loc_022F44
	move.w	#$2,d0
loc_022F44:
	cmp.w	(ram_C394).w,d0
	beq.w	loc_022F64
	cmp.w	(ram_C396).w,d0
	beq.w	loc_022F64
	cmp.w	(ram_C398).w,d0
	beq.w	loc_022F64
	cmp.w	(ram_C39A).w,d0
	bne.w	loc_022F6E
loc_022F64:
	btst	#3,$62(a3)
	beq.w	NullSub
loc_022F6E:
	move.w	$14(a2),d0
	btst	#7,$62(a2)
	beq.w	loc_022F7E
	neg.w	d0
loc_022F7E:
	cmp.w	#$EF,d0	; general form
	blt.w	NullSub
	cmp.w	#$11E,d0	; general form
	bgt.w	NullSub
	move.w	(a2),d0
	cmp.w	#$14,d0	; general form
	bgt.w	NullSub
	cmp.w	#$FFEC,d0	; general form
	blt.w	NullSub
	move.w	#$28,d0
	sub.b	$74(a3),d0
	bsr.w	Random
	cmp.w	#$4,d0	; general form
	bhi.w	NullSub
	btst	#4,(ram_C33A).w
	bne.w	NullSub
	moveq	#$22,d0
	jmp	(sub_02131E).l


; ----------------------------------------------------------------------
; called from $022CF2
sub_022FC6:
	movem.l	d0-d4/a0-a3,-(sp)
	btst	#3,$62(a2)
	beq.w	loc_022FFE
	tst.w	$34(a2)
	beq.w	loc_022FFE
	move.w	$28(a2),d0
	or.w	$2A(a2),d0
	bne.w	loc_022FFE
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a2),d0
	bne.w	loc_022FFE
	st	(ram_B7C0).w
	move.b	#$14,$5E(a2)
loc_022FFE:
	bsr.w	sub_02300E
	exg	a2,a3
	bsr.w	sub_02300E
	movem.l	(sp)+,d0-d4/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $022FFE, $023004
sub_02300E:
	cmpi.w	#$175A,$58(a2)
	beq.w	loc_0232C6
	cmpi.w	#$17AC,$58(a2)
	beq.w	loc_0232C6
	cmpi.w	#$1850,$58(a2)
	beq.w	loc_0232C6
	cmpi.w	#$2228,$58(a2)
	beq.w	loc_0233D4
	cmpi.w	#$550,$58(a2)
	beq.w	loc_0233D4
	cmpi.w	#$3A68,$58(a3)
	bne.w	loc_02304E
	bra.w	loc_023058
loc_02304E:
	cmpi.w	#$2D90,$58(a3)
	bne.w	NullSub
loc_023058:
	btst	#0,(ram_C33A).w
	beq.w	loc_02306E
	move.w	#$100,$32(a3)
	move.w	#$100,$32(a2)
loc_02306E:
	move.w	(a2),d0
	sub.w	(a3),d0
	move.w	$14(a2),d1
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	sub.w	$54(a3),d0
	andi.w	#$7,d0
	btst	#3,$4(a3)
	beq.w	loc_023098
	neg.w	d0
	addq.w	#8,d0
	andi.w	#$7,d0
loc_023098:
	asl.w	#1,d0
	lea	dat_0231BE(pc),a0
	move.w	$0(a0,d0.w),d1
	cmpi.w	#$3A68,$58(a3)
	beq.w	loc_0230B6
	bset	#5,$62(a3)
	bsr.w	sub_01F3B2
loc_0230B6:
	tst.w	$34(a2)
	beq.w	NullSub
	cmpi.w	#$3A68,$58(a3)
	beq.w	loc_0230D0
	cmp.w	#$14,d4	; general form
	blt.w	NullSub
loc_0230D0:
	moveq	#$64,d0
	btst	#3,$62(a3)
	beq.w	loc_0230DC
loc_0230DC:
	sub.b	$68(a3),d0
	add.b	$68(a2),d0
	lsr.w	#1,d0
	exg	a2,a3
	jsr	(sub_1CFA54).l
	exg	a2,a3
	cmpi.w	#$3A68,$58(a3)
	beq.w	loc_02316C
	sub.w	$32(a2),d0
	beq.w	loc_02316C
	bmi.w	loc_02316C
	btst	#4,$64(a3)
	bne.w	loc_02316C
	bsr.w	Random
	clr.w	(ram_BF48).w
	move.b	$76(a3),(ram_BF49).w
	lsr.w	(ram_BF48).w
	cmp.b	(ram_BF49).w,d0
	ble.w	loc_02316C
	bsr.w	sub_0231D6
	cmp.w	#$4,d0	; general form
	bhi.w	NullSub
	btst	#4,(ram_C33A).w
	bne.w	NullSub
	move.b	(VDP_HVCOUNTER).l,d0
	andi.w	#$2,d0
	addi.w	#$16,d0
	tst.b	(ram_DE82).w
	beq.w	loc_023160
	move.w	#$36,d0
	jmp	(sub_02131E).l
loc_023160:
	jsr	(sub_0215B4).l
	jmp	(sub_02131E).l
loc_02316C:
	bsr.w	sub_0231D6
	cmp.w	#$3,d0	; general form
	bhi.w	loc_0231BA
	btst	#4,(ram_C33A).w
	bne.w	loc_0231BA
	move.b	(ram_D297).w,d0
	andi.w	#$3,d0
	move.l	a0,-(sp)
	movea.l	#dat_0231CE,a0
	tst.b	(ram_DE82).w
	beq.w	loc_02319C
	clr.w	d0
loc_02319C:
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	movea.l	(sp)+,a0
	jsr	(sub_0215B4).l
	bpl.w	loc_0231B4
	jsr	(sub_02159A).l
loc_0231B4:
	jsr	(sub_02131E).l
loc_0231BA:
	bra.w	sub_023484
dat_0231BE:
	dc.w	$1500,$146E,$1592,$1592,$1592,$1604,$1604,$1500
dat_0231CE:
	dc.w	$001A,$001C,$0030,$0032


; ----------------------------------------------------------------------
; called from $02312A, $02316C, $023398, $023460
sub_0231D6:
	move.w	#$28,d0
	sub.b	$74(a3),d0
	lsr.b	#1,d0
	mulu.w	#$D,d0
	btst	#3,$62(a3)
	beq.w	loc_0231F0
	asl.w	#1,d0
loc_0231F0:
	move.w	(a3),d1
	sub.w	(ram_B760).w,d1
	cmp.w	#$28,d1	; general form
	bgt.w	loc_023220
	cmp.w	#$FFD8,d1	; general form
	blt.w	loc_023220
	move.w	$14(a3),d1
	sub.w	(ram_B774).w,d1
	cmp.w	#$28,d1	; general form
	bgt.w	loc_023220
	cmp.w	#$FFD8,d1	; general form
	blt.w	loc_023220
	asr.w	#1,d0
loc_023220:
	bsr.w	Random
	btst	#1,$64(a2)
	beq.w	loc_02326A
	move.w	$14(a2),d1
	bpl.w	loc_023238
	neg.w	d1
loc_023238:
	subi.w	#$11E,d1
	neg.w	d1
	move.w	#$4,d0
	cmp.w	#$70,d1	; general form
	bgt.w	loc_023266
	move.w	#$3,d0
	cmp.w	#$38,d1	; general form
	bgt.w	loc_023266
	move.w	#$2,d0
	cmp.w	#$2A,d1	; general form
	bgt.w	loc_023266
	move.w	#$1,d0
loc_023266:
	bsr.w	Random
loc_02326A:
	tst.b	(ram_DE7C).w
	beq.w	loc_023274
	clr.w	d0
loc_023274:
	movem.w	d1,-(sp)
	move.w	(ram_C4CC).w,d1
	andi.w	#$F,d1
	cmp.w	#$4,d1	; general form
	movem.w	(sp)+,d1
	bge.w	loc_023290
	move.w	#$7F,d0
loc_023290:
	btst	#6,$62(a3)
	bne.w	loc_0232A8
	btst	#2,(ram_C350).w
	bne.w	loc_0232B2
	bra.w	loc_0232B6
loc_0232A8:
	btst	#1,(ram_C350).w
	beq.w	loc_0232B6
loc_0232B2:
	move.w	#$7F,d0
loc_0232B6:
	cmpi.w	#$3,(ram_C4C8).w
	bne.w	loc_0232C4
	move.w	#$7F,d0
loc_0232C4:
	rts
loc_0232C6:
	btst	#5,$62(a3)
	bne.w	NullSub
	tst.w	$34(a3)
	beq.w	NullSub
	btst	#0,$63(a3)
	bne.w	NullSub
	move.w	(a3),d0
	sub.w	(a2),d0
	move.w	$14(a3),d1
	sub.w	$14(a2),d1
	bsr.w	sub_01F186
	sub.w	$54(a2),d0
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bhi.w	NullSub
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_023316
	bclr	#3,(ram_C33C).w
loc_023316:
	move.w	$28(a3),d0
	add.w	$28(a2),d0
	asr.w	#1,d0
	move.w	d0,$28(a3)
	move.w	d0,$28(a2)
	move.w	$2A(a3),d0
	add.w	$2A(a2),d0
	asr.w	#1,d0
	move.w	d0,$2A(a3)
	move.w	d0,$2A(a2)
	bset	#5,$62(a3)
	move.w	#$1378,d1
	cmpi.w	#$17AC,$58(a2)
	bne.w	loc_023368
	move.w	#$BD8,d1
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_023368
	st	(ram_B7C0).w
	move.b	#$20,$5E(a3)
loc_023368:
	bsr.w	sub_01F3B2
	exg	a2,a3
	bset	#5,$62(a3)
	move.w	#$17AC,d1
	cmpi.w	#$17AC,$58(a3)
	beq.w	loc_023394
	move.w	#$1708,d1
	cmpi.w	#$175A,$58(a3)
	beq.w	loc_023394
	move.w	#$17FE,d1
loc_023394:
	bsr.w	sub_01F3B2
	bsr.w	sub_0231D6
	cmp.w	#$3,d0	; general form
	bhi.w	loc_0233CC
	btst	#4,(ram_C33A).w
	bne.w	loc_0233CC
	move.w	#$24,d0
	cmpi.w	#$1708,$58(a3)
	beq.w	loc_0233C0
	move.w	#$1E,d0
loc_0233C0:
	jsr	(sub_0215B4).l
	jsr	(sub_02131E).l
loc_0233CC:
	exg	a2,a3
	st	(ram_BFF0).w
	rts
loc_0233D4:
	btst	#5,$62(a3)
	bne.w	NullSub
	tst.w	$34(a3)
	beq.w	NullSub
	btst	#0,$63(a3)
	bne.w	NullSub
	tst.w	(ram_D27E).w
	bne.w	loc_023430
	btst	#3,$62(a2)
	beq.w	loc_023430
	move.w	#$20,d0
	add.b	$76(a2),d0
	sub.b	$69(a3),d0
	btst	#1,(ram_C34E).w
	bne.w	loc_023422
	btst	#6,(ram_C34C).w
	beq.w	loc_023424
loc_023422:
	subq.b	#2,d0
loc_023424:
	bsr.w	Random
	cmp.w	#$18,d0	; general form
	blt.w	NullSub
loc_023430:
	move.w	(a3),d0
	sub.w	(a2),d0
	move.w	$14(a3),d1
	sub.w	$14(a2),d1
	bsr.w	sub_01F186
	sub.w	$54(a2),d0
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bhi.w	NullSub
	exg	a2,a3
	bsr.w	sub_023484
	tst.w	$34(a3)
	beq.w	loc_02347C
	bsr.w	sub_0231D6
	cmp.w	#$4,d0	; general form
	bhi.w	loc_02347C
	move.w	#$20,d0
	jsr	(sub_0215B4).l
	jsr	(sub_02131E).l
loc_02347C:
	exg	a2,a3
	st	(ram_BFF0).w
	rts


; ----------------------------------------------------------------------
; called from $022EFC, $022F06, $0231BA, $023454, $024D76, $024EDE
sub_023484:
	cmpi.w	#$B,$52(a2)
	bgt.w	NullSub
	tst.w	$34(a2)
	bne.w	loc_0234B8
	btst	#0,(ram_C34A).w
	bne.w	NullSub
	btst	#3,(ram_C350).w
	bne.w	NullSub
	cmpi.w	#$3E0,$58(a2)
	beq.w	NullSub
	bra.w	loc_02350E
loc_0234B8:
	cmpi.w	#$18A2,$58(a2)
	blt.w	loc_0234CC
	cmpi.w	#$2034,$58(a2)
	ble.w	NullSub
loc_0234CC:
	cmpi.w	#$12C6,$58(a2)
	beq.w	NullSub
	cmpi.w	#$2634,$58(a2)
	beq.w	NullSub
	cmpi.w	#$2786,$58(a2)
	beq.w	NullSub
	cmpi.w	#$EEE,$58(a2)
	beq.w	NullSub
	cmpa.l	(ram_DCEC).w,a2
	bne.w	loc_023506
	cmpa.l	(ram_DCF0).w,a3
	bne.w	loc_023506
	rts
loc_023506:
	move.l	a2,(ram_DCEC).w
	move.l	a3,(ram_DCF0).w
loc_02350E:
	btst	#3,$64(a2)
	bne.w	NullSub
	btst	#3,$64(a3)
	bne.w	NullSub
	tst.w	$34(a2)
	beq.w	loc_02356A
	move.w	#$12C6,d1
	btst	#4,$64(a3)
	bne.w	loc_02356A
	cmpi.b	#$18,$72(a2)
	blt.w	loc_02356A
	tst.b	$5F(a2)
	bne.w	loc_02356A
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$F,d0
	addi.w	#$10,d0
	cmp.w	$32(a2),d0
	ble.w	loc_02356A
	move.b	#$3C,$5F(a2)
	bra.w	loc_023840
loc_02356A:
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_0235AE
	tst.w	$34(a3)
	beq.w	loc_0235AE
	movea.w	#$C732,a0
	btst	#6,$62(a3)
	beq.w	loc_02358E
	adda.w	#$39E,a0
loc_02358E:
	addq.w	#1,$10(a0)
	clr.w	d0
	move.b	$67(a3),d0
	adda.w	d0,a0
	addq.b	#1,$130(a0)
	addq.w	#1,(ram_C4D0).w
	tst.b	$75(a3)
	bne.w	loc_0235AE
	addq.w	#2,(ram_C4D0).w
loc_0235AE:
	move.b	#$78,$5E(a2)
	move.w	(a3),d0
	sub.w	(a2),d0
	move.w	$14(a3),d1
	sub.w	$14(a2),d1
	bsr.w	sub_01F186
	tst.w	$34(a2)
	beq.w	loc_0237E8
	jsr	(sub_1CFA54).l
	btst	#4,$64(a2)
	beq.w	loc_0237E8
	movem.l	d1-d4,-(sp)
	move.w	$28(a2),d1
	bpl.w	loc_0235EA
	neg.w	d1
loc_0235EA:
	move.w	$2A(a2),d2
	bpl.w	loc_0235F4
	neg.w	d2
loc_0235F4:
	move.w	(a2),d3
	sub.w	(a3),d3
	move.w	$14(a2),d4
	sub.w	$14(a3),d4
	cmpi.w	#$11E,$14(a3)
	bgt.w	loc_023648
	cmpi.w	#$FEE2,$14(a3)
	blt.w	loc_02363E
	tst.w	(a3)
	bpl.w	loc_02362C
	tst.w	d3
	bpl.w	loc_023652
	cmp.w	#$FFFD,d3	; general form
	bgt.w	loc_023652
	bra.w	loc_02365A
loc_02362C:
	tst.w	d3
	bmi.w	loc_023652
	cmp.w	#$3,d3	; general form
	blt.w	loc_023652
	bra.w	loc_02365A
loc_02363E:
	tst.w	d4
	bpl.w	loc_023652
	bra.w	loc_02365A
loc_023648:
	tst.w	d4
	bmi.w	loc_023652
	bra.w	loc_02365A
loc_023652:
	movem.l	(sp)+,d1-d4
	bra.w	loc_0237E8
loc_02365A:
	movem.l	(sp)+,d1-d4
	bra.w	loc_023662
loc_023662:
	cmpi.w	#$122,$14(a2)
	bgt.w	loc_02368A
	cmpi.w	#$FEDE,$14(a2)
	blt.w	loc_02368A
	cmpi.w	#$76,(a2)
	bgt.w	loc_02368A
	cmpi.w	#$FF8A,(a2)
	blt.w	loc_02368A
	bra.w	loc_0237E8
loc_02368A:
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_0236C2
	addi.w	#$A,(ram_B8BA).w
	addi.w	#$96,(ram_B8B4).w
	move.w	d1,-(sp)
	move.b	#$0,$40(a3)
	move.b	#$0,$66(a3)
	move.w	#$1676,d1
	jsr	(sub_01F3B2).l
	clr.w	$28(a3)
	clr.w	$2A(a3)
	move.w	(sp)+,d1
loc_0236C2:
	movem.l	d0/a0,-(sp)
	cmpi.w	#$122,$14(a2)
	bgt.w	loc_0236F0
	cmpi.w	#$FEDE,$14(a2)
	blt.w	loc_0236F8
	tst.w	(a2)
	bmi.w	loc_0236E8
	move.w	#$2,d0
	bra.w	loc_0236FC
loc_0236E8:
	move.w	#$6,d0
	bra.w	loc_0236FC
loc_0236F0:
	move.w	#$0,d0
	bra.w	loc_0236FC
loc_0236F8:
	move.w	#$4,d0
loc_0236FC:
	add.w	d0,d0
	movea.l	#dat_0237D8,a0
	move.w	$0(a0,d0.w),d1
	move.w	$14(a2),(ram_D306).w
	move.w	(a2),(ram_D308).w
	cmp.w	#$2582,d1	; general form
	bne.w	loc_023752
	cmpi.w	#$59,$14(a2)
	bgt.w	loc_023752
	cmpi.w	#$FFA7,$14(a2)
	blt.w	loc_023752
	move.w	d0,-(sp)
	move.w	#$7,d0
	jsr	(sub_1D1470).l
	move.w	(sp)+,d0
	addq.w	#3,(ram_C4D0).w
	move.w	#$2142,d1
	btst	#3,$4(a2)
	beq.w	loc_02377C
	bra.w	loc_02377C
loc_023752:
	addq.w	#2,(ram_C4D0).w
	btst	#3,$4(a2)
	beq.w	loc_02377C
	cmp.w	#$241E,d1	; general form
	beq.w	loc_023778
	cmp.w	#$2582,d1	; general form
	bne.w	loc_02377C
	move.w	#$241E,d1
	bra.w	loc_02377C
loc_023778:
	move.w	#$2582,d1
loc_02377C:
	clr.w	$28(a2)
	clr.w	$2A(a2)
	btst	#5,$64(a2)
	bne.w	loc_0237C4
	tst.w	$14(a2)
	bmi.w	loc_0237AC
	cmpi.w	#$57,(a2)
	bgt.w	loc_0237AC
	cmpi.w	#$FFA9,(a2)
	blt.w	loc_0237AC
	move.w	#$3C,(ram_DDEE).w
loc_0237AC:
	move.w	#$C,-(sp)
	btst	#6,$62(a2)
	beq.w	loc_0237BE
	move.w	#$B,(sp)
loc_0237BE:
	jsr	(sub_09205A).l
loc_0237C4:
	bset	#5,$64(a2)
	bset	#0,$62(a2)
	movem.l	(sp)+,d0/a0
	bra.w	loc_023812
dat_0237D8:
	dc.w	$236C,$236C,$241E,$241E,$24D0,$24D0,$2582,$2582
loc_0237E8:
	tst.w	$34(a2)
	bne.w	loc_0237F8
	move.w	#$3E0,d1
	bra.w	loc_023840
loc_0237F8:
	move.w	#$2786,d1
	sub.w	$54(a2),d0
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bls.w	loc_023840
	move.w	#$2634,d1
loc_023812:
	move.w	$54(a2),d0
	andi.w	#$3,d0
	bne.w	loc_023840
	cmpi.b	#$14,$76(a3)
	blt.w	loc_023840
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_023840
	btst	#5,$64(a2)
	bne.w	loc_023840
	move.w	#$EEE,d1
loc_023840:
	exg	a2,a3
	bset	#5,$62(a3)
	bsr.w	sub_01F3B2
	exg	a2,a3
	tst.w	$34(a3)
	beq.w	loc_02386A
	tst.w	$34(a2)
	beq.w	loc_02386A
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$F,(ram_B8BA).w
loc_02386A:
	tst.w	$34(a2)
	bne.w	loc_023886
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a2),d0
	bne.w	loc_023882
	st	(ram_B7C0).w
loc_023882:
	bra.w	loc_0238DC
loc_023886:
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_02398E
	cmp.w	$52(a2),d0
	bne.w	loc_02398E
	st	(ram_B7C0).w
	btst	#4,(ram_C33A).w
	bne.w	loc_023970
	tst.b	(ram_DE7E).w
	bne.w	loc_0238DC
	cmpi.w	#$2786,$58(a2)
	bne.w	loc_023970
	move.w	$54(a2),d0
	andi.w	#$3,d0
	bne.w	loc_023970
	btst	#4,$63(a2)
	bne.w	loc_023970
	move.w	#$145,d0
	bsr.w	Random
	cmp.w	$32(a2),d0
	bgt.w	loc_023970
loc_0238DC:
	btst	#0,(ram_C33A).w
	bne.w	loc_023970
	btst	#0,(ram_C34A).w
	bne.w	loc_023970
	tst.w	$34(a2)
	beq.w	loc_023912
	exg	a2,a3
	move.w	#$18A2,d1
	btst	#0,(ram_D297).w
	beq.w	loc_02390C
	move.w	#$1F6A,d1
loc_02390C:
	bsr.w	sub_01F3B2
	exg	a2,a3
loc_023912:
	bsr.w	sub_02399A
	tst.w	$34(a2)
	beq.w	loc_023942
	btst	#5,(ram_C34C).w
	bne.w	loc_023942
	exg	a2,a3
	move.w	#$194C,d1
	btst	#0,(ram_D297).w
	bne.w	loc_02393C
	move.w	#$2034,d1
loc_02393C:
	bsr.w	sub_01F3B2
	exg	a2,a3
loc_023942:
	move.w	#$4,(ram_C44E).w
	moveq	#$14,d0
	tst.w	$34(a3)
	beq.w	loc_023994
	tst.w	$34(a2)
	beq.w	loc_023994
	tst.w	(ram_D27E).w
	beq.w	loc_023994
	moveq	#$12,d0
	jsr	(sub_02135E).l
	jmp	(sub_02197E).l
loc_023970:
	addq.w	#5,(ram_C4D0).w
	move.w	#$B,-(sp)
	btst	#6,$62(a2)
	bne.w	loc_023986
	move.w	#$C,(sp)
loc_023986:
	jsr	(sub_092172).l
	rts
loc_02398E:
	jmp	(sub_09249C).l
loc_023994:
	jmp	(sub_02135E).l


; ----------------------------------------------------------------------
; called from $023912
sub_02399A:
	bclr	#2,(ram_C35A).w
	addq.w	#5,(ram_C4D0).w
	tst.w	$34(a2)
	bne.w	loc_0239E2
	movea.w	#$C732,a0
	btst	#6,$62(a2)
	beq.w	loc_0239BE
	adda.w	#$39E,a0
loc_0239BE:
	tst.w	$26(a0)
	bmi.w	loc_0239E2
	addq.w	#1,$26(a0)
	cmpi.w	#$2,$26(a0)
	blt.w	loc_0239D8
	clr.w	$26(a0)
loc_0239D8:
	exg	a2,a0
	jsr	(sub_025122).l
	exg	a2,a0
loc_0239E2:
	move.w	d0,-(sp)
	bset	#2,$63(a2)
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$1E,(ram_B8BA).w
	move.w	#$D,-(sp)
	jsr	(sub_09205A).l
	move.w	(a2),(ram_BFDE).w
	move.w	$14(a2),(ram_BFE0).w
	bset	#6,(ram_C33C).w
	clr.w	d1
	movea.w	#$C732,a0
	btst	#6,$62(a2)
	beq.w	loc_023A28
	move.w	#$8000,d1
	adda.w	#$39E,a0
loc_023A28:
	move.b	$67(a2),d1
	move.w	d1,(ram_C4D4).w
	ext.w	d1
	add.w	d1,d1
	exg	a2,a3
	jsr	(sub_1D1B12).l
	exg	a2,a3
	tst.w	d0
	bne.w	loc_023A54
	bclr	#5,(ram_C34C).w
	move.w	#$FFFD,$6C(a0,d1.w)
	bra.w	loc_023A9E
loc_023A54:
	cmp.w	#$3,d0	; general form
	beq.w	loc_023A72
	bclr	#5,(ram_C34C).w
	move.w	#$FFFD,$6C(a0,d1.w)
	jsr	(sub_1D1B1C).l
	beq.w	loc_023A9E
loc_023A72:
	bset	#5,(ram_C34C).w
	move.w	#$FFFC,$6C(a0,d1.w)
	btst	#7,(SysFlags).w
	beq.w	loc_023A9E
	tst.b	(ram_DE7D).w
	bne.w	loc_023A9E
	tst.w	$34(a2)
	beq.w	loc_023A9E
	jsr	(sub_1E4106).l
loc_023A9E:
	move.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $022AB2, $022AEC
sub_023AA2:
	bclr	#4,$64(a3)
	move.w	#$96,d4
	sub.w	(ram_BD3A).w,d4
	move.w	#$148,d5
	sub.w	(ram_BD3C).w,d5
	movem.w	d2-d5,-(sp)
	neg.w	d4
	neg.w	d5
	addi.w	#$40,d4
	addi.w	#$40,d5
	cmp.w	d5,d3
	bgt.w	loc_023AE8
	cmp.w	d4,d2
	blt.w	loc_023B0A
	neg.w	d4
	cmp.w	d4,d2
	bgt.w	loc_023B0A
	movea.w	#$B6E0,a2
	bsr.w	sub_023B76
	bra.w	loc_023B3C
loc_023AE8:
	neg.w	d5
	cmp.w	d5,d3
	blt.w	loc_023B3C
	cmp.w	d4,d2
	blt.w	loc_023B0A
	neg.w	d4
	cmp.w	d4,d2
	bgt.w	loc_023B0A
	movea.w	#$B660,a2
	bsr.w	sub_023B76
	bra.w	loc_023B3C
loc_023B0A:
	sub.w	d4,d2
	sub.w	d5,d3
	move.w	d3,d0
	move.w	d2,d1
	neg.w	d1
	muls.w	d3,d3
	muls.w	d2,d2
	add.l	d2,d3
	cmp.l	#dat_001000,d3	; general form
	bls.w	loc_023B3C
	exg	d0,d3
	bsr.w	ISqrt
	exg	d0,d3
	ext.l	d0
	asl.l	#8,d0
	divs.w	d3,d0
	ext.l	d1
	asl.l	#8,d1
	divs.w	d3,d1
	bsr.w	sub_0242E4
loc_023B3C:
	movem.w	(sp)+,d2-d5
	move.w	$4E(a3),d0
	or.w	$50(a3),d0
	bne.w	NullSub
	move.w	#$100,d0
	clr.w	d1
	cmp.w	d5,d3
	bge.w	sub_0242E4
	neg.w	d5
	neg.w	d0
	cmp.w	d5,d3
	ble.w	sub_0242E4
	exg	d0,d1
	cmp.w	d4,d2
	bge.w	sub_0242E4
	neg.w	d4
	neg.w	d1
	cmp.w	d4,d2
	ble.w	sub_0242E4
	rts


; ----------------------------------------------------------------------
; called from $023AE0, $023B02
sub_023B76:
	cmpi.w	#$D,$18(a3)
	bgt.w	NullSub
	cmpi.w	#$E,$52(a3)
	bne.w	loc_0240C4
	tst.w	(ram_B7C0).w
	bmi.w	loc_023BBC
	movem.l	d0/a0,-(sp)
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	adda.w	d0,a0
	move.w	$14(a0),d4
	movem.l	(sp)+,d0/a0
	cmp.w	#$11E,d4	; general form
	bgt.w	loc_023BBC
	cmp.w	#$FEE2,d4	; general form
	bge.w	NullSub
loc_023BBC:
	sub.w	(a2),d2
	moveq	#$10,d4
	add.w	(ram_BD3A).w,d4
	cmp.w	d4,d2
	bgt.w	NullSub
	neg.w	d4
	cmp.w	d4,d2
	blt.w	NullSub
	sub.w	$14(a2),d3
	move.w	#$2,d5
	add.w	(ram_BD3C).w,d5
	cmp.w	d5,d3
	bgt.w	NullSub
	neg.w	d5
	cmp.w	d5,d3
	blt.w	NullSub
	st	(ram_BFF0).w
	cmpi.w	#$D,$24(a3)
	blt.w	loc_023C04
	move.w	$24(a3),$18(a3)
	bra.w	loc_023D06
loc_023C04:
	bclr	#7,$62(a3)
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_023C3E
	st	(ram_B7C0).w
	asl.w	#7,d0
	movea.w	#$B060,a0
	move.b	#$8,$5E(a0,d0.w)
	move.w	(ram_B774).w,d1
	btst	#7,$62(a0,d0.w)
	bne.w	loc_023C32
	neg.w	d1
loc_023C32:
	tst.w	d1
	bpl.w	loc_023C3E
	bset	#7,$62(a3)
loc_023C3E:
	move.w	#$FF00,d0
	move.l	$14(a3),d1
	sub.l	$20(a3),d1
	asr.l	#8,d1
	beq.w	loc_023D14
	bmi.w	loc_023C58
	neg.w	d0
	neg.w	d5
loc_023C58:
	add.w	d3,d5
	move.l	(a3),d3
	sub.l	$1C(a3),d3
	asr.l	#8,d3
	muls.w	d3,d5
	divs.w	d1,d5
	bvs.w	loc_023D14
	sub.w	d5,d2
	cmp.w	d4,d2
	blt.w	loc_023D14
	neg.w	d4
	cmp.w	d4,d2
	bgt.w	loc_023D14
	clr.w	d1
	move.w	$14(a3),d3
	eor.w	d0,d3
	bmi.w	sub_0243AE
	neg.w	d0
	btst	#7,$62(a3)
	bne.w	sub_0243AE
	cmpi.w	#$D,$18(a3)
	beq.w	loc_023CAC
	subq.w	#1,d4
	cmp.w	d4,d2
	bgt.w	loc_023CAC
	neg.w	d4
	cmp.w	d4,d2
	bge.w	loc_023D2A
loc_023CAC:
	bsr.w	sub_02244C
	move.w	#$25,-(sp)
	btst	#0,(ram_C33A).w
	bne.w	loc_023CCE
	move.w	#$8,(sp)
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$28,(ram_B8BA).w
loc_023CCE:
	jsr	(sub_09205A).l
	move.w	#$1000,d0
	bsr.w	Random
	tst.w	$14(a3)
	bmi.w	loc_023CE6
	neg.w	d0
loc_023CE6:
	move.w	d0,$2A(a3)
	move.w	#$1000,d0
	bsr.w	sub_0200EA
	move.w	d0,$28(a3)
	move.w	#$1000,d0
	bsr.w	sub_0200EA
	move.w	d0,$2C(a3)
	bra.w	sub_01EC86
loc_023D06:
	neg.w	$2C(a3)
	bpl.w	NullSub
	neg.w	$2C(a3)
	rts
loc_023D14:
	clr.w	d0
	move.w	#$100,d1
	move.w	(a3),d2
	sub.w	$1C(a3),d2
	bmi.w	sub_0243AE
	neg.w	d1
	bra.w	sub_0243AE
loc_023D2A:
	tst.w	(ram_B7C0).w
	bpl.w	NullSub
	btst	#7,(ram_C350).w
	beq.w	loc_023D46
	jsr	(sub_1E5DC4).l
	bra.w	loc_023DCE
loc_023D46:
	btst	#2,(ram_C342).w
	beq.w	loc_023DC4
	btst	#0,(ram_C34A).w
	bne.w	loc_023D7E
	movem.l	d0/a0,-(sp)
	move.w	(ram_D2F2).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	adda.w	d0,a0
	btst	#7,$62(a0)
	movem.l	(sp)+,d0/a0
	bne.w	loc_023D86
	bra.w	loc_023D92
loc_023D7E:
	tst.w	(ram_D472).w
	bne.w	loc_023D92
loc_023D86:
	tst.w	(ram_B774).w
	bmi.w	NullSub
	bra.w	loc_023D9A
loc_023D92:
	tst.w	(ram_B774).w
	bpl.w	NullSub
loc_023D9A:
	bset	#5,(ram_C344).w
	tst.w	(ram_D472).w
	beq.w	loc_023DB0
	addq.w	#1,(ram_D454).w
	bra.w	loc_023DB4
loc_023DB0:
	addq.w	#1,(ram_D452).w
loc_023DB4:
	bset	#0,(ram_C34E).w
	jsr	(sub_01E442).l
	bra.w	loc_023DCE
loc_023DC4:
	btst	#0,(ram_C33A).w
	bne.w	NullSub
loc_023DCE:
	bset	#0,(ram_C344).w
	bclr	#3,(ram_C34E).w
	btst	#7,(ram_C350).w
	bne.w	loc_023DEE
	bsr.w	sub_02244C
	jsr	(sub_0921E8).l
loc_023DEE:
	move.w	d0,-(sp)
	move.w	(FrameCounter).w,d0
loc_023DF4:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_023DF4
	move.w	(sp)+,d0
	addq.w	#5,(ram_C4D0).w
	btst	#7,(ram_C350).w
	bne.w	loc_023FF2
	move.w	#$0,-(sp)
	jsr	(sub_09205A).l
	jsr	(sub_01B286).l
	addi.w	#$1F4,(ram_B8B4).w
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	tst.w	$14(a3)
	bpl.w	loc_023E32
	exg	a2,a1
loc_023E32:
	btst	#1,(ram_C33A).w
	beq.w	loc_023E3E
	exg	a2,a1
loc_023E3E:
	cmpi.w	#$7D,$C(a2)
	bge.w	loc_023E4C
	addq.w	#1,$C(a2)
loc_023E4C:
	jsr	(sub_1D252E).l
	movem.l	d0/a0/a1,-(sp)
	movea.l	#ram_DE3C,a0
	movea.l	#ram_DE44,a1
	cmpa.l	#ram_C732,a2
	beq.w	loc_023E72
	addq.w	#2,a0
	adda.w	#$1E,a1
loc_023E72:
	move.w	(a0),d0
	sub.w	(ram_C4CA).w,d0
	ext.l	d0
	tst.w	(a1)
	bmi.w	loc_023E86
	cmp.w	(a1),d0
	bge.w	loc_023E88
loc_023E86:
	move.w	d0,(a1)
loc_023E88:
	movem.l	(sp)+,d0/a0/a1
	btst	#5,(ram_C344).w
	beq.w	loc_023EA4
	btst	#0,(ram_C34A).w
	bne.w	loc_023EA4
	addq.w	#1,$39C(a2)
loc_023EA4:
	bclr	#4,(ram_C34A).w
	beq.w	loc_023EB2
	addq.w	#1,$394(a2)
loc_023EB2:
	btst	#5,(ram_C33E).w
	beq.w	loc_023EE0
	btst	#6,(ram_C33E).w
	bne.w	loc_023ED8
	cmpa.l	#ram_CAD0,a2
	bne.w	loc_023EE0
loc_023ED0:
	addq.w	#1,$390(a2)
	bra.w	loc_023EE0
loc_023ED8:
	cmpa.l	#ram_C732,a2
	beq.s	loc_023ED0
loc_023EE0:
	movem.l	d0/a2,-(sp)
	move.w	(ram_C4C8).w,d0
	add.w	d0,d0
	adda.w	d0,a2
	addq.w	#1,$37C(a2)
	movem.l	(sp)+,d0/a2
	bclr	#7,(ram_C34E).w
	beq.w	loc_023F02
	addq.w	#1,$398(a2)
loc_023F02:
	cmpa.w	#$C732,a2
	bne.w	loc_023F2A
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$4,(ram_D4AC).w
	jsr	(sub_092274).l
	move.w	#$78,(ram_DCDE).w
	move.w	(ram_D4A8).w,-(sp)
	move.w	(sp)+,(ram_DCE0).w
loc_023F2A:
	cmpi.w	#$168,(ram_C4D6).w
	bne.w	loc_023F38
	subq.w	#6,(ram_C4D6).w
loc_023F38:
	movea.w	#$C4D8,a0
	adda.w	(ram_C4D6).w,a0
	addq.w	#6,(ram_C4D6).w
	bsr.w	sub_0240B0
	move.w	d0,(a0)+
	moveq	#$2,d0
	add.w	$24(a2),d0
	sub.w	$24(a1),d0
	move.b	d0,(a0)+
	addi.w	#$1E,(ram_B8BA).w
	cmpa.w	#$C732,a2
	beq.w	loc_023F70
	subi.w	#$14,(ram_B8BA).w
	bset	#7,-$1(a0)
loc_023F70:
	move.w	$18(a2),d0
	move.b	d0,(a0)+
	move.w	#$FFFF,(a0)
	addi.w	#$C0,d0
	addq.b	#1,$0(a2,d0.w)
	move.w	$1A(a2),d0
	bmi.w	loc_023FB6
	cmp.w	$18(a2),d0
	beq.w	loc_023FB6
	move.b	d0,(a0)+
	addi.w	#$DC,d0
	addq.b	#1,$0(a2,d0.w)
	move.w	$1C(a2),d0
	bmi.w	loc_023FB6
	cmp.w	$18(a2),d0
	beq.w	loc_023FB6
	move.b	d0,(a0)
	addi.w	#$DC,d0
	addq.b	#1,$0(a2,d0.w)
loc_023FB6:
	move.w	$26(a1),d0
	bmi.w	loc_023FC6
	addi.w	#$C0,d0
	addq.b	#1,$0(a1,d0.w)
loc_023FC6:
	bsr.w	sub_02244C
	bsr.w	sub_021E4C
	bclr	#3,(ram_C342).w
	bsr.w	sub_022296
	move.w	#$2710,(ram_C36C).w
	btst	#0,(ram_C34A).w
	beq.w	loc_023FEC
	bra.w	loc_023FF2
loc_023FEC:
	moveq	#$7,d0
	bsr.w	sub_024070
loc_023FF2:
	clr.w	(ram_BFF0).w
	clr.w	$28(a3)
	clr.w	$2A(a3)
	moveq	#$6,d0
	tst.w	(a3)
	bpl.w	loc_024008
	neg.w	d0
loc_024008:
	move.w	d0,(a3)
	move.w	#$126,d0
	tst.w	$14(a3)
	bpl.w	loc_024018
	neg.w	d0
loc_024018:
	move.w	d0,$14(a3)
	move.w	#$600,$2C(a3)
	clr.w	$18(a3)
	st	(ram_BF1E).w
	st	(ram_BF22).w
	bset	#2,$62(a3)
	move.w	#$1A,d0
	bsr.w	sub_01F172
	btst	#7,(ram_C350).w
	bne.w	NullSub
	move.l	a3,-(sp)
	adda.w	#$80,a3
	move.w	#$298C,d1
	tst.w	$14(a3)
	bpl.w	loc_02405C
	move.w	#$29DE,d1
loc_02405C:
	bsr.w	sub_01F3B2
	movea.w	$22(a1),a3
	moveq	#$E,d0
	jsr	(sub_02135E).l
	movea.l	(sp)+,a3
	rts


; ----------------------------------------------------------------------
; called from $023FEE
sub_024070:
	move.l	a3,-(sp)
	movea.w	$22(a2),a3
	moveq	#$5,d3
loc_024078:
	tst.w	$34(a3)
	ble.w	loc_0240A4
	btst	#0,$63(a3)
	bne.w	loc_0240A4
	bclr	#2,$62(a3)
	bclr	#3,$64(a3)
	beq.w	loc_0240A0
	jsr	(sub_1D1E04).l
loc_0240A0:
	bsr.w	sub_01F168
loc_0240A4:
	adda.w	#$80,a3
	dbra	d3,loc_024078
	movea.l	(sp)+,a3
	rts


; ----------------------------------------------------------------------
; called from $021760, $023F44
sub_0240B0:
	move.w	(ram_C4C8).w,d0
	swap	d0
	clr.w	d0
	lsr.l	#2,d0
	or.w	(ram_C4CE).w,d0
	sub.w	(ram_C4CA).w,d0
	rts
loc_0240C4:
	btst	#5,$63(a3)
	bne.w	NullSub
	cmpi.w	#$A,$18(a3)
	bgt.w	NullSub
	cmpi.w	#$B,$52(a3)
	bgt.w	NullSub
	tst.w	$34(a3)
	beq.w	loc_02415C
	movem.w	d2/d3,-(sp)
	sub.w	$14(a2),d3
	move.w	d3,d0
	sub.w	(a2),d2
	move.w	d2,d1
	neg.w	d0
	asl.w	#4,d2
	muls.w	d2,d2
	divu.w	#$400,d2
	cmp.w	#$100,d2	; general form
	bhi.w	loc_024156
	asl.w	#4,d3
	muls.w	d3,d3
	divu.w	#$79,d3
	add.w	d2,d3
	cmp.w	#$100,d3	; general form
	bhi.w	loc_024156
	movem.w	(sp)+,d2/d3
	bsr.w	sub_024202
	movem.w	d2/d3,-(sp)
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	bsr.w	ISqrt
	move.w	d0,d2
	movem.w	(sp)+,d0/d1
	addq.w	#1,d2
	asl.l	#8,d0
	divs.w	d2,d0
	asl.l	#8,d1
	divs.w	d2,d1
	bset	#4,(TextFlags).w
	bsr.w	sub_0243AE
	bclr	#4,(TextFlags).w
loc_024156:
	movem.w	(sp)+,d2/d3
	rts
loc_02415C:
	movem.w	d2/d3,-(sp)
	btst	#3,$62(a3)
	bne.w	loc_02419A
	movem.w	d0,-(sp)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_02417E
	neg.w	d0
loc_02417E:
	cmp.w	#$11E,d0	; general form
	movem.w	(sp)+,d0
	bge.w	loc_02419A
	cmpi.w	#$2,$54(a3)
	beq.s	loc_024156
	cmpi.w	#$6,$54(a3)
	beq.s	loc_024156
loc_02419A:
	sub.w	$14(a2),d3
	move.w	d3,d0
	sub.w	(a2),d2
	move.w	d2,d1
	neg.w	d0
	asl.w	#4,d2
	muls.w	d2,d2
	divu.w	#$384,d2
	cmp.w	#$100,d2	; general form
	bhi.s	loc_024156
	asl.w	#4,d3
	muls.w	d3,d3
	divu.w	#$64,d3
	add.w	d2,d3
	cmp.w	#$100,d3	; general form
	bhi.s	loc_024156
	movem.w	(sp)+,d2/d3
	bsr.w	sub_024202
	movem.w	d2/d3,-(sp)
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	bsr.w	ISqrt
	move.w	d0,d2
	movem.w	(sp)+,d0/d1
	addq.w	#1,d2
	asl.l	#8,d0
	divs.w	d2,d0
	asl.l	#8,d1
	divs.w	d2,d1
	bset	#4,(TextFlags).w
	bsr.w	sub_0243AE
	bclr	#4,(TextFlags).w
	bra.w	loc_024156


; ----------------------------------------------------------------------
; called from $024120, $0241C8
sub_024202:
	movem.l	d0/d1,-(sp)
	tst.b	(ram_DE81).w
	bne.w	loc_02421C
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$1F,d0
	bne.w	loc_024264
loc_02421C:
	move.w	(ram_B774).w,d0
	sub.w	$14(a2),d0
	cmp.w	#$28,d0	; general form
	bgt.w	loc_024264
	cmp.w	#$FFD8,d0	; general form
	blt.w	loc_024264
	move.w	$28(a3),d0
	move.w	$2A(a3),d1
	tst.b	(ram_DE81).w
	bne.w	loc_02426A
	cmp.w	#$2000,d0	; general form
	bgt.w	loc_02426A
	cmp.w	#$E000,d0	; general form
	blt.w	loc_02426A
	cmp.w	#$2000,d1	; general form
	bgt.w	loc_02426A
	cmp.w	#$E000,d1	; general form
	blt.w	loc_02426A
loc_024264:
	movem.l	(sp)+,d0/d1
	rts
loc_02426A:
	btst	#0,(ram_C34A).w
	bne.s	loc_024264
	adda.w	#$C,sp
	asr.w	#2,d0
	asr.w	#2,d1
	move.w	d0,$28(a2)
	move.w	d1,$2A(a2)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	bset	#6,(ram_C33C).w
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	movem.w	d1,-(sp)
	move.w	#$FFFF,d0
	btst	#7,$62(a3)
	bne.w	loc_0242AE
	neg.w	d0
loc_0242AE:
	move.w	$14(a2),d1
	eor.w	d1,d0
	bmi.w	loc_0242D8
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_0242D8
	subq.w	#6,d0
	move.w	$52(a3),d1
	subq.w	#6,d1
	eor.w	d1,d0
	bpl.w	loc_0242D8
	move.w	#$34,d0
	jsr	(sub_02131E).l
loc_0242D8:
	movem.w	(sp)+,d1
	moveq	#$8,d0
	jmp	(sub_02135E).l


; ----------------------------------------------------------------------
; called from $023B38, $023B54, $023B5E, $023B66, $023B70, $1CF67C
sub_0242E4:
	cmpi.w	#$E,$52(a3)
	bne.w	sub_0243AE
	cmpi.w	#$1D,$18(a3)
	bgt.w	loc_02436C
	cmpi.w	#$12,$18(a3)
	bls.w	sub_0243AE
	cmpi.w	#$118,$14(a3)
	blt.w	loc_02436C
	cmpi.w	#$46,(a3)
	blt.w	sub_0243AE
	cmpi.w	#$4A,(a3)
	bgt.w	sub_0243AE
	cmpi.w	#$FA0,$2A(a3)
	blt.w	sub_0243AE
	move.l	a3,-(sp)
	asr.w	$2A(a3)
	adda.w	#$80,a3
	move.w	#$48,(a3)
	move.w	#$13C,$14(a3)
	move.w	#$18,$18(a3)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	clr.w	$28(a3)
	move.w	#$2C46,d1
	bsr.w	sub_01F3B2
	movea.l	(sp)+,a3
	move.w	#$E,-(sp)
	jsr	(sub_09205A).l
	addi.w	#$258,(ram_B8B4).w
	addi.w	#$F,(ram_B8BA).w
loc_02436C:
	bset	#6,(ram_C33C).w
	bset	#2,$62(a3)
	tst.w	$14(a3)
	bpl.w	loc_024386
	ori.w	#$8000,$4(a3)
loc_024386:
	clr.w	$86(a3)
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	move.l	a3,-(sp)
	move.w	(ram_BFB6).w,d0
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	moveq	#$6,d0
	jsr	(sub_02135E).l
	movea.l	(sp)+,a3
	rts


; ----------------------------------------------------------------------
; called from $023C82, $023C8E, $023D20, $023D26, $02414C, $0241F4, $0242EA, $0242FE (+3 more)
sub_0243AE:
	move.w	d0,$4E(a3)
	move.w	d1,$50(a3)
	movem.l	d2/d3,-(sp)
	movem.w	d0/d1,-(sp)
	muls.w	$2A(a3),d0
	muls.w	$28(a3),d1
	sub.l	d1,d0
	asr.l	#8,d0
	move.w	d0,d2
	movem.w	(sp),d0/d1
	muls.w	$28(a3),d0
	muls.w	$2A(a3),d1
	add.l	d1,d0
	asr.l	#8,d0
	move.w	d0,d3
	neg.w	d2
	cmpi.w	#$E,$52(a3)
	bne.w	loc_02443E
	bclr	#4,(ram_C33E).w
	tst.w	d2
	bpl.w	loc_024514
	asr.w	#2,d2
	cmp.w	#$FC00,d2	; general form
	bgt.w	loc_024430
	move.w	#$800,d0
	bsr.w	Random
	neg.w	d0
	move.w	d0,$2C(a3)
	bsr.w	sub_01EC86
	move.w	d2,d0
	asr.w	#8,d0
	asr.w	#2,d0
	addq.w	#4,d0
	bpl.w	loc_024420
	clr.w	d0
loc_024420:
	andi.w	#$3,d0
	addi.w	#$28,d0
	move.w	d0,-(sp)
	jsr	(sub_09205A).l
loc_024430:
	move.w	d3,d0
	asr.w	#6,d0
	sub.w	d0,d3
	asr.w	#1,d0
	sub.w	d0,d3
	bra.w	loc_024480
loc_02443E:
	cmp.w	#$3E8,d2	; general form
	bgt.w	loc_024514
	bclr	#4,(TextFlags).w
	bne.w	loc_024456
	bset	#4,$64(a3)
loc_024456:
	cmp.w	#$F000,d2	; general form
	bgt.w	loc_024472
	cmpi.w	#$A,$32(a3)
	blt.w	loc_024472
	move.w	#$20,-(sp)
	jsr	(sub_09205A).l
loc_024472:
	asr.w	#2,d2
	cmp.w	#$FC7C,d2	; general form
	blt.w	loc_024480
	move.w	#$FC18,d2
loc_024480:
	movem.w	(sp),d0/d1
	movem.w	d2/d3,-(sp)
	muls.w	d0,d3
	muls.w	d1,d2
	sub.l	d2,d3
	asr.l	#8,d3
	tst.w	$34(a3)
	bne.w	loc_0244C0
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_0244C0
	cmpi.w	#$128,$14(a3)
	bgt.w	loc_0244C0
	cmpi.w	#$FED8,$14(a3)
	blt.w	loc_0244C0
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
loc_0244C0:
	move.w	d3,$28(a3)
	movem.w	(sp)+,d2/d3
	movem.w	(sp),d0/d1
	muls.w	d1,d3
	muls.w	d0,d2
	add.l	d2,d3
	asr.l	#8,d3
	tst.w	$34(a3)
	bne.w	loc_024504
	cmpi.w	#$B,$52(a3)
	bgt.w	loc_024504
	cmpi.w	#$128,$14(a3)
	bgt.w	loc_024504
	cmpi.w	#$FED8,$14(a3)
	blt.w	loc_024504
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
	asr.l	#1,d3
loc_024504:
	move.w	d3,$2A(a3)
	tst.w	$2C(a3)
	bmi.w	loc_024514
	clr.w	$2C(a3)
loc_024514:
	addq.w	#4,sp
	movem.l	(sp)+,d2/d3
	rts
loc_02451C:
	bclr	#2,(ram_C344).w
	beq.w	NullSub
	move.w	#$5,-(sp)
	jmp	(sub_09205A).l
loc_024530:
	cmpi.w	#$190,$14(a3)
	bgt.w	loc_024544
	cmpi.w	#$FE70,$14(a3)
	bgt.w	loc_024548
loc_024544:
	clr.w	$2A(a3)
loc_024548:
	cmpi.w	#$10,$18(a3)
	bgt.s	loc_02451C
	move.w	$52(a3),d0
	asl.w	#1,d0
	movea.w	#$B880,a0
	movea.w	#$B8A0,a1
	movea.w	#$B860,a2
	move.w	$0(a0,d0.w),d1
loc_024566:
	cmp.w	#$F,d1	; general form
	beq.w	loc_02458C
	clr.w	d4
	move.b	$1(a1,d1.w),d4
	move.w	$0(a2,d4.w),d5
	sub.w	$14(a3),d5
	cmp.w	#$18,d5	; general form
	bgt.w	loc_02458C
	bsr.w	sub_0245B4
	addq.w	#1,d1
	bra.s	loc_024566
loc_02458C:
	move.w	$0(a0,d0.w),d1
	beq.w	loc_0245B2
loc_024594:
	clr.w	d4
	move.b	-$1(a1,d1.w),d4
	move.w	$14(a3),d5
	sub.w	$0(a2,d4.w),d5
	cmp.w	#$18,d5	; general form
	bgt.w	loc_0245B2
	bsr.w	sub_0245B4
	subq.w	#1,d1
	bne.s	loc_024594
loc_0245B2:
	rts


; ----------------------------------------------------------------------
; called from $024584, $0245AA
sub_0245B4:
	movem.l	d0-d7/a0-a3,-(sp)
	lsr.w	#1,d4
	cmp.w	(ram_B7C0).w,d4
	beq.w	loc_0246C6
	cmp.w	#$B,d4	; general form
	bgt.w	loc_0246C6
	asl.w	#7,d4
	movea.w	#$B060,a2
	adda.w	d4,a2
	btst	#2,(ram_C342).w
	beq.w	loc_0245EE
	asr.w	#7,d4
	cmp.w	(ram_D2F2).w,d4
	beq.w	loc_0245EE
	cmp.w	(ram_D2F4).w,d4
	bne.w	loc_0246C6
loc_0245EE:
	btst	#2,$62(a2)
	bne.w	loc_0246C6
	tst.b	$5E(a2)
	bne.w	loc_0246C6
	btst	#2,$63(a2)
	bne.w	loc_024674
	cmpi.w	#$5,$18(a3)
	bgt.w	loc_024674
	cmpi.w	#$200,$2C(a3)
	bgt.w	loc_024674
	move.l	a2,-(sp)
	bsr.w	sub_01F1F0
	add.w	(a2),d0
	sub.w	(a3),d0
	cmp.w	#$10,d0	; general form
	bgt.w	loc_024674
	cmp.w	#$FFF0,d0	; general form
	blt.w	loc_024674
	add.w	$14(a2),d1
	sub.w	$14(a3),d1
	cmp.w	#$10,d1	; general form
	bgt.w	loc_024674
	cmp.w	#$FFF0,d1	; general form
	blt.w	loc_024674
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	move.l	#$100,d1
	tst.b	$5E(a3)
	ble.w	loc_024666
	lsr.w	#2,d1
loc_024666:
	cmp.l	d1,d0
	bhi.w	loc_024674
	bsr.w	sub_024922
	bra.w	loc_0246C6
loc_024674:
	tst.w	$34(a2)
	beq.w	loc_02474A
	btst	#3,$64(a2)
	bne.w	loc_0246C6
	move.w	(a2),d0
	sub.w	(a3),d0
	cmp.w	#$8,d0	; general form
	bgt.w	loc_0246C6
	cmp.w	#$FFF8,d0	; general form
	blt.w	loc_0246C6
	move.w	$14(a2),d1
	sub.w	$14(a3),d1
	cmp.w	#$8,d1	; general form
	bgt.w	loc_0246C6
	cmp.w	#$FFF8,d1	; general form
	blt.w	loc_0246C6
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	#$40,d0	; general form
	bhi.w	loc_0246C6
	bsr.w	sub_024CF6
loc_0246C6:
	movem.l	(sp)+,d0-d7/a0-a3
	rts
dat_0246CC:
	dc.w	$0000,$0003,$0003,$0004,$0004,$0004,$0005,$0005
	dc.w	$0005,$0005,$0005,$0005,$0005,$0005,$0005,$0005
	dc.w	$0005,$0005,$0005,$0005,$0005
dat_0246F6:
	dc.w	$0000,$0001,$0001,$0001,$0001,$0001,$0001,$0001
	dc.w	$0002,$0002,$0002,$0002,$0002,$0002,$0002,$0002
	dc.w	$0002,$0002,$0002,$0002,$0002
dat_024720:
	dc.w	$0000,$0002,$0002,$0003,$0003,$0003,$0003,$0003
	dc.w	$0004,$0004,$0004,$0004,$0004,$0004,$0004,$0004
	dc.w	$0004,$0004,$0004,$0004,$0004
loc_02474A:
	move.l	a0,-(sp)
	movea.l	#dat_0246CC,a0
	cmpi.w	#$1,(ram_D284).w
	beq.w	loc_0247E0
	cmpi.w	#$2,(ram_D284).w
	bne.w	loc_0247AA
	move.w	#$1,d0
	move.w	#$2,d1
	btst	#6,$62(a2)
	beq.w	loc_024780
	move.w	#$2,d0
	move.w	#$1,d1
loc_024780:
	cmp.w	(ram_C394).w,d0
	beq.w	loc_0247B4
	cmp.w	(ram_C396).w,d0
	beq.w	loc_0247B4
	cmp.w	(ram_C398).w,d0
	beq.w	loc_0247B4
	cmp.w	(ram_C39A).w,d0
	beq.w	loc_0247B4
	movea.l	#dat_0246F6,a0
	bra.w	loc_0247E0
loc_0247AA:
	movea.l	#dat_024720,a0
	bra.w	loc_0247E0
loc_0247B4:
	movea.l	#dat_0246F6,a0
	cmp.w	(ram_C394).w,d1
	beq.w	loc_0247E0
	cmp.w	(ram_C396).w,d1
	beq.w	loc_0247E0
	cmp.w	(ram_C398).w,d1
	beq.w	loc_0247E0
	cmp.w	(ram_C39A).w,d1
	beq.w	loc_0247E0
	movea.l	#dat_0246CC,a0
loc_0247E0:
	clr.w	d0
	clr.w	d1
	move.b	$74(a2),d0
	move.b	$6F(a2),d1
	add.w	d1,d0
	move.b	$71(a2),d1
	add.w	d1,d0
	move.b	$73(a2),d1
	add.w	d1,d0
	asr.w	#3,d0
	andi.w	#$F,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),(ram_BFA0).w
	movea.l	(sp)+,a0
	cmpi.w	#$15,(a2)
	bgt.w	loc_024852
	cmpi.w	#$FFEB,(a2)
	blt.w	loc_024852
	btst	#7,$62(a2)
	beq.w	loc_024838
	move.w	(ram_B774).w,d0
	subi.w	#$FEE0,d0
	move.w	$14(a2),d1
	subi.w	#$FEE0,d1
	bra.w	loc_024848
loc_024838:
	move.w	(ram_B774).w,d0
	subi.w	#$120,d0
	move.w	$14(a2),d1
	subi.w	#$120,d1
loc_024848:
	eor.w	d1,d0
	bpl.w	loc_024852
	bra.w	loc_0248FE
loc_024852:
	move.w	(ram_BFA0).w,(ram_BFA6).w
	addq.w	#7,(ram_BFA6).w
	move.w	(a2),d0
	move.w	$14(a2),d1
	bsr.w	sub_0248DE
	ble.w	loc_0248C8
	cmp.w	#$28,d0	; general form
	bge.w	loc_0248FE
	cmp.w	#$28,d1	; general form
	bge.w	loc_0248FE
	move.l	a2,-(sp)
	jsr	(sub_01F24A).l
	move.w	(ram_BFA0).w,(ram_BFA6).w
	addq.w	#6,(ram_BFA6).w
	bsr.w	sub_0248DE
	ble.w	loc_0248C8
	move.l	a2,-(sp)
	jsr	(sub_01F2C2).l
	move.w	(ram_BFA0).w,(ram_BFA6).w
	addq.w	#3,(ram_BFA6).w
	bsr.w	sub_0248DE
	ble.w	loc_0248C8
	move.l	a2,-(sp)
	jsr	(sub_01F33A).l
	move.w	(ram_BFA0).w,(ram_BFA6).w
	addq.w	#3,(ram_BFA6).w
	bsr.w	sub_0248DE
	bgt.w	loc_0248FE
loc_0248C8:
	move.w	(a2),d0
	sub.w	(a3),d0
	move.w	$14(a2),d1
	sub.w	$14(a3),d1
	jsr	(sub_024D94).l
	bra.w	loc_0246C6


; ----------------------------------------------------------------------
; called from $024862, $02488C, $0248A6, $0248C0
sub_0248DE:
	sub.w	(a3),d0
	bpl.w	loc_0248E6
	neg.w	d0
loc_0248E6:
	sub.w	$14(a3),d1
	bpl.w	loc_0248F0
	neg.w	d1
loc_0248F0:
	cmp.w	(ram_BFA6).w,d0
	bgt.w	loc_0248FC
	cmp.w	(ram_BFA6).w,d1
loc_0248FC:
	rts
loc_0248FE:
	bclr	#2,(ram_C344).w
	beq.w	loc_0246C6
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a2),d0
	beq.w	loc_0246C6
	move.w	#$5,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_0246C6


; ----------------------------------------------------------------------
; called from $02466C
sub_024922:
	tst.w	$34(a2)
	bne.w	loc_024934
	btst	#4,(ram_C33A).w
	bne.w	NullSub
loc_024934:
	bclr	#0,$62(a2)
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_024A1E
	asl.w	#7,d1
	movea.w	#$B060,a0
	adda.w	d1,a0
	move.b	$62(a0),d1
	move.b	$62(a2),d2
	eor.w	d1,d2
	btst	#6,d2
	beq.w	NullSub
	btst	#5,(TextFlags).w
	beq.w	loc_024974
	cmp.l	#$40,d0	; general form
	bhi.w	NullSub
	bra.w	loc_02497E
loc_024974:
	cmp.l	#$24,d0	; general form
	bhi.w	NullSub
loc_02497E:
	tst.w	$34(a2)
	beq.w	loc_0249D2
	tst.w	$34(a0)
	beq.w	NullSub
	move.b	$72(a0),d0
	lsr.b	#1,d0
	bsr.w	sub_0250CA
	move.w	d0,-(sp)
	exg	a0,a2
	move.b	$72(a0),d0
	lsr.b	#1,d0
	bsr.w	sub_0250CA
	exg	a0,a2
	neg.w	d0
	add.w	(sp)+,d0
	addi.w	#$24,d0
	bsr.w	Random
	btst	#5,(TextFlags).w
	beq.w	loc_0249CA
	cmp.w	#$4,d0	; general form
	bhi.w	NullSub
	bra.w	loc_0249D2
loc_0249CA:
	cmp.w	#$2,d0	; general form
	bhi.w	NullSub
loc_0249D2:
	move.b	$72(a0),d0
	lsr.b	#1,d0
	bsr.w	sub_0250CA
	addi.w	#$14,d0
	move.b	d0,$5E(a0)
	exg	a0,a2
	move.b	$72(a0),d0
	lsr.b	#1,d0
	bsr.w	sub_0250CA
	addi.w	#$14,d0
	move.b	d0,$5E(a0)
	exg	a0,a2
	move.w	$52(a0),(ram_BF0E).w
	bclr	#2,(ram_C33C).w
	bclr	#3,(ram_C33C).w
loc_024A0C:
	move.w	#$6,-(sp)
	jsr	(sub_09205A).l
	bsr.w	sub_01EAE0
	bra.w	loc_02509E
loc_024A1E:
	tst.w	$34(a2)
	bne.w	loc_024A30
	cmp.l	#$40,d0	; general form
	bhi.w	NullSub
loc_024A30:
	btst	#3,$64(a2)
	beq.w	loc_024A64
	cmp.l	#$64,d0	; general form
	bhi.w	loc_024AE0
	btst	#3,(SysFlags).w
	bne.w	loc_024A5E
	cmpi.w	#$18,$5A(a2)
	bge.w	loc_024A64
	move.w	#$18,$5A(a2)
loc_024A5E:
	bset	#7,(ram_C34E).w
loc_024A64:
	move.w	(ram_B788).w,d0
	move.w	(ram_B78A).w,d1
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	clr.w	d1
	btst	#4,(ram_C33E).w
	bne.w	loc_024A90
	btst	#3,$64(a2)
	bne.w	loc_024AD4
	move.b	$72(a2),d1
	mulu.w	#$15E,d1
loc_024A90:
	addi.l	#$32C8,d1
	movem.w	d2,-(sp)
	move.w	(ram_BF14).w,d2
	cmp.w	$52(a2),d2
	movem.w	(sp)+,d2
	bne.w	loc_024AB6
	jsr	(sub_1D2A6E).l
	addi.l	#$32C8,d1
loc_024AB6:
	mulu.w	d1,d1
	cmpi.w	#$9B4,$58(a2)
	bne.w	loc_024AC4
	asl.l	#2,d0
loc_024AC4:
	cmp.l	d1,d0
	bls.w	loc_024B06
	move.b	#$8,$5E(a2)
	bra.w	loc_024A0C
loc_024AD4:
	exg	a2,a3
	jsr	(sub_1CF344).l
	exg	a2,a3
	rts
loc_024AE0:
	cmp.l	#$144,d0	; general form
	bhi.w	loc_024B04
	btst	#3,(SysFlags).w
	bne.w	loc_024B04
	cmpi.w	#$18,$5A(a2)
	bge.w	loc_024B04
	move.w	#$18,$5A(a2)
loc_024B04:
	rts
loc_024B06:
	move.w	#$7,-(sp)
	move.w	$52(a2),d0
	move.w	d0,(ram_B7C0).w
	movea.w	#$C732,a0
	lea	$39E(a0),a1
	btst	#6,$62(a2)
	bne.w	loc_024B26
	exg	a0,a1
loc_024B26:
	st	$1A(a0)
	st	$1C(a0)
	bset	#3,$30(a0)
	bclr	#4,(ram_C340).w
	beq.w	loc_024B62
	addq.w	#1,$E(a1)
	addi.w	#$C8,(ram_B8B4).w
	addq.w	#5,(ram_C4D0).w
	move.w	#$C,(sp)
	cmpa.w	#$C732,a1
	bne.w	loc_024B62
	addi.w	#$A,(ram_B8BA).w
	move.w	#$B,(sp)
loc_024B62:
	jsr	(sub_092172).l
	move.w	$52(a2),d0
	cmp.w	(ram_BF14).w,d0
	bne.w	loc_024B78
	addq.w	#1,$14(a1)
loc_024B78:
	st	(ram_BF14).w
	bclr	#2,(ram_C33C).w
	bclr	#3,(ram_C33C).w
	tst.w	$34(a2)
	bne.w	sub_024BAA
	bsr.w	sub_02244C
	move.w	#$8C,$48(a2)
	cmpi.w	#$4BE,$58(a2)
	bne.w	sub_024BAA
	move.w	#$5,$48(a2)

; ----------------------------------------------------------------------
; called from $00E932, $024B8C, $024BA0
sub_024BAA:
	cmp.w	(ram_C388).w,d0
	beq.w	loc_024BEC
	cmp.w	(ram_C38A).w,d0
	beq.w	loc_024BEC
	cmp.w	(ram_C38C).w,d0
	beq.w	loc_024BEC
	cmp.w	(ram_C38E).w,d0
	beq.w	loc_024BEC
	movem.l	d0/a3,-(sp)
	asl.w	#7,d0
	movea.l	#ram_B060,a3
	tst.w	$34(a3,d0.w)
	bne.w	loc_024BEE
	btst	#3,$62(a3,d0.w)
	beq.w	loc_024BEE
	movem.l	(sp)+,d0/a3
loc_024BEC:
	rts
loc_024BEE:
	movem.l	(sp)+,d0/a3
	cmp.w	#$6,d0	; general form
	slt	d1
	ext.w	d1
	addq.w	#2,d1
	move.w	(ram_BF0E).w,d2
	cmp.w	(ram_C388).w,d2
	beq.w	loc_024CBE
	cmp.w	(ram_C38A).w,d2
	beq.w	loc_024C86
	cmp.w	(ram_C38C).w,d2
	beq.w	loc_024C4E
	cmp.w	(ram_C39A).w,d1
	bne.w	loc_024C26
	jmp	(sub_01B774).l
loc_024C26:
	cmp.w	(ram_C394).w,d1
	bne.w	loc_024C34
	jmp	(sub_01B752).l
loc_024C34:
	cmp.w	(ram_C396).w,d1
	bne.w	loc_024C42
	jmp	(sub_01B75C).l
loc_024C42:
	cmp.w	(ram_C398).w,d1
	bne.s	loc_024BEC
	jmp	(sub_01B768).l
loc_024C4E:
	cmp.w	(ram_C398).w,d1
	bne.w	loc_024C5C
	jmp	(sub_01B768).l
loc_024C5C:
	cmp.w	(ram_C394).w,d1
	bne.w	loc_024C6A
	jmp	(sub_01B752).l
loc_024C6A:
	cmp.w	(ram_C396).w,d1
	bne.w	loc_024C78
	jmp	(sub_01B75C).l
loc_024C78:
	cmp.w	(ram_C39A).w,d1
	bne.w	loc_024BEC
	jmp	(sub_01B774).l
loc_024C86:
	cmp.w	(ram_C396).w,d1
	bne.w	loc_024C94
	jmp	(sub_01B75C).l
loc_024C94:
	cmp.w	(ram_C394).w,d1
	bne.w	loc_024CA2
	jmp	(sub_01B752).l
loc_024CA2:
	cmp.w	(ram_C398).w,d1
	bne.w	loc_024CB0
	jmp	(sub_01B768).l
loc_024CB0:
	cmp.w	(ram_C39A).w,d1
	bne.w	loc_024BEC
	jmp	(sub_01B774).l
loc_024CBE:
	cmp.w	(ram_C394).w,d1
	bne.w	loc_024CCC
	jmp	(sub_01B752).l
loc_024CCC:
	cmp.w	(ram_C396).w,d1
	bne.w	loc_024CDA
	jmp	(sub_01B75C).l
loc_024CDA:
	cmp.w	(ram_C398).w,d1
	bne.w	loc_024CE8
	jmp	(sub_01B768).l
loc_024CE8:
	cmp.w	(ram_C39A).w,d1
	bne.w	loc_024BEC
	jmp	(sub_01B774).l


; ----------------------------------------------------------------------
; called from $0246C2
sub_024CF6:
	btst	#3,$64(a2)
	bne.w	NullSub
	cmpi.w	#$8,$18(a3)
	bgt.w	loc_024D14
	move.w	d0,d1
	andi.w	#$F,d1
	bne.w	NullSub
loc_024D14:
	bsr.w	sub_01EAE0
	move.w	#$24,-(sp)
	jsr	(sub_09205A).l
	clr.w	$2C(a3)
	move.b	#$8,$5E(a2)
	move.w	(a3),d0
	sub.w	(a2),d0
	move.w	$14(a3),d1
	sub.w	$14(a2),d1
	bne.w	loc_024D42
	move.l	a2,-(sp)
	bsr.w	sub_01F1F0
loc_024D42:
	move.w	$28(a3),d2
	move.w	$2A(a3),d3
	move.b	d0,$28(a3)
	move.b	d1,$2A(a3)
	bsr.w	sub_01EC86
	cmpi.w	#$8,$18(a3)
	ble.w	NullSub
	muls.w	d2,d2
	muls.w	d3,d3
	add.l	d3,d2
	cmp.l	#$9000000,d2	; general form
	bls.w	loc_024D7C
	cmpi.w	#$C,$18(a3)
	bgt.w	sub_023484
	rts
loc_024D7C:
	bset	#5,$62(a2)
	bne.w	NullSub
	move.w	#$141C,d1
	exg	a2,a3
	bsr.w	sub_01F3B2
	exg	a2,a3

; ----------------------------------------------------------------------
; called from $01CDDA, $01D07C, $01D092, $01D09A, $01D0A8, $01D0B2, $01D0D2, $01D286 (+236 more)
NullSub:
	rts


; ----------------------------------------------------------------------
; called from $0248D4
sub_024D94:
	btst	#4,(ram_C33A).w
	bne.s	NullSub
	clr.w	d2
	cmpi.w	#$8,$18(a3)
	bgt.w	loc_024DAA
	addq.w	#2,d2
loc_024DAA:
	neg.w	d0
	neg.w	d1
	bsr.w	sub_01F186
	sub.w	$54(a2),d0
	andi.w	#$7,d0
	move.w	d0,d1
	andi.w	#$3,d1
	bne.w	loc_024DCA
	move.w	(VDP_HVCOUNTER).l,d0
loc_024DCA:
	andi.w	#$4,d0
	lsr.w	#2,d0
	eori.w	#$1,d0
	add.w	d0,d2
	add.w	d2,d2
	lea	dat_024FCA(pc),a0
	move.w	$0(a0,d2.w),d0
	moveq	#$F,d1
	add.b	$0(a2,d0.w),d1
	lea	dat_024FD2(pc),a0
	btst	#3,$4(a2)
	beq.w	loc_024DF8
	eori.w	#$2,d2
loc_024DF8:
	move.w	$6(a2),d0
	bclr	#2,(ram_C344).w
	bsr.w	sub_02244C
	bsr.w	sub_01EAE0
	cmpi.w	#$3000,(ram_B78A).w
	bgt.w	loc_024E1E
	cmpi.w	#$D000,(ram_B78A).w
	bgt.w	loc_024E36
loc_024E1E:
	move.w	#$B,-(sp)
	btst	#6,$62(a2)
	beq.w	loc_024E30
	move.w	#$D,(sp)
loc_024E30:
	jsr	(sub_092172).l
loc_024E36:
	move.w	#$24,-(sp)
	jsr	(sub_09205A).l
	move.w	(ram_B7C0).w,d2
	bmi.w	loc_024F22
	st	(ram_B7C0).w
	asl.w	#7,d2
	movea.w	#$B060,a0
	adda.w	d2,a0
	move.b	#$14,$5E(a0)
	move.w	$52(a0),(ram_BF0E).w
	bclr	#2,(ram_C33C).w
	bclr	#3,(ram_C33C).w
loc_024E6C:
	movem.l	d2/d3,-(sp)
	move.w	$28(a3),d2
	move.w	$2A(a3),d3
	muls.w	d2,d2
	muls.w	d3,d3
	add.l	d3,d2
	cmp.l	#$9000000,d2	; general form
	movem.l	(sp)+,d2/d3
	bgt.w	loc_024E94
	tst.b	(ram_DE80).w
	beq.w	loc_024EE8
loc_024E94:
	tst.b	(ram_DE80).w
	bne.w	loc_024EB8
	btst	#7,(ram_C350).w
	bne.w	loc_024EE8
	move.w	#$3E8,d0
	jsr	(Random).l
	cmp.w	#$3,d0	; general form
	bgt.w	loc_024EE8
loc_024EB8:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#6,$62(a2)
	beq.w	loc_024ED4
	bset	#3,(ram_C35C).w
	beq.w	loc_024EDE
	bra.w	loc_024EE4
loc_024ED4:
	bset	#2,(ram_C35C).w
	bne.w	loc_024EE4
loc_024EDE:
	jsr	(sub_023484).l
loc_024EE4:
	movem.l	(sp)+,d0-d7/a0-a6
loc_024EE8:
	clr.w	$2C(a3)
	move.b	#$A,$5E(a2)
	move.w	#$4,$46(a2)
	move.w	(a3),d0
	sub.w	(a2),d0
	move.w	$14(a3),d1
	sub.w	$14(a2),d1
	bne.w	loc_024F0E
	move.l	a2,-(sp)
	bsr.w	sub_01F1F0
loc_024F0E:
	move.b	d0,$28(a3)
	move.b	d1,$2A(a3)
	bra.w	sub_01EC86


; ----------------------------------------------------------------------
sub_024F1A:
	bset	#2,(ram_C344).w
	rts
loc_024F22:
	cmpi.w	#$4BE,$58(a2)
	beq.w	loc_024E6C
	moveq	#$2,d0
	add.b	$6D(a2),d0
	asl.w	#8,d0
	asl.w	#1,d0
	bsr.w	Random
	addi.w	#$C00,d0
	add.w	d0,d0
	bpl.w	loc_024F48
	move.w	#$7FFF,d0
loc_024F48:
	btst	#1,$63(a2)
	bne.w	loc_024F8C
	cmpi.w	#$2C,(a3)
	bgt.w	loc_024F8C
	cmpi.w	#$FFD4,(a3)
	blt.w	loc_024F8C
	cmpi.w	#$124,$14(a3)
	bgt.w	loc_024F8C
	cmpi.w	#$FEDC,$14(a3)
	blt.w	loc_024F8C
	cmpi.w	#$E8,$14(a3)
	bgt.w	loc_024F8A
	cmpi.w	#$FF18,$14(a3)
	bgt.w	loc_024F8C
loc_024F8A:
	asr.w	#2,d0
loc_024F8C:
	cmp.w	(ram_B788).w,d0
	blt.w	loc_024E6C
	cmp.w	(ram_B78A).w,d0
	blt.w	loc_024E6C
	neg.w	d0
	cmp.w	(ram_B788).w,d0
	bgt.w	loc_024E6C
	cmp.w	(ram_B78A).w,d0
	bgt.w	loc_024E6C
	btst	#2,$63(a2)
	bne.w	loc_024E6C
	btst	#7,(ram_C350).w
	bne.w	loc_024E6C
	clr.w	$2C(a3)
	bra.w	loc_024B06
dat_024FCA:
	dc.w	$0074,$006F,$0071,$0073
dat_024FD2:
	dc.w	$559D,$6755,$9D67,$559D,$6755,$9D67,$559D,$6755
	dc.w	$9D67,$559D,$6755,$9D67,$5555,$5555,$5555,$5555
	dc.w	$5555,$5555,$5555,$5555,$55F0,$55F0,$55F0,$55F0
	dc.w	$55F0,$55F0,$55F0,$55F0,$55F0,$55F0,$55F0,$55F0
	dc.w	$D575,$D575,$D575,$D575,$D575,$D575,$D575,$D575
	dc.w	$5555,$5555,$5555,$5555,$5555,$5555,$5555,$5555
	dc.w	$5555,$5555,$5555,$5555,$5555,$5555,$5555,$5555
	dc.w	$F0F0,$F0F0,$F0F0,$F0F0,$F0F0,$F0F0,$F0F0,$F0F0
	dc.w	$5757,$5757,$A5A5,$A5A5,$A5A5,$A5A5,$A5A5,$A5A5
	dc.w	$A5A5,$A5A5,$A5A5,$A5A5,$A5A5,$A5A5,$9D67,$9D67
	dc.w	$9D67,$9D67,$9D67,$9D67,$9D67,$9D67,$D5D5,$7575
	dc.w	$D5D5,$7575,$D5D5,$7575,$D5D5,$7575,$D5D5,$7575
	dc.w	$D5D5,$7575,$D5D5,$7575,$D5D5,$7575
loc_02509E:
	st	(ram_B7C0).w
	move.w	#$1000,d0
	bsr.w	sub_0200EA
	move.w	d0,$2A(a3)
	move.w	#$1000,d0
	bsr.w	sub_0200EA
	move.w	d0,$28(a3)
	move.w	#$1000,d0
	bsr.w	Random
	move.w	d0,$2C(a3)
	bra.w	sub_01EC86


; ----------------------------------------------------------------------
; called from $01304C, $024994, $0249A2, $0249D8, $0249EC
sub_0250CA:
	ext.w	d0
	move.w	d0,-(sp)
	movem.l	d1/a2/a3,-(sp)
	movea.l	a0,a3
	bsr.w	sub_0250F4
	btst	#4,(ram_C34C).w
	beq.w	loc_0250E6
	move.w	#$1000,d0
loc_0250E6:
	movem.l	(sp)+,d1/a2/a3
	muls.w	(sp)+,d0
	asl.l	#4,d0
	swap	d0
	ext.l	d0
	rts


; ----------------------------------------------------------------------
; called from $01B3EC, $01B434, $01FC6E, $01FD42, $0250D4
sub_0250F4:
	movea.w	#$C732,a2
	btst	#6,$62(a3)
	beq.w	loc_025106
	adda.w	#$39E,a2
loc_025106:
	move.b	$67(a3),d1
	ext.w	d1
	add.w	d1,d1
	move.w	$34(a2,d1.w),d0
	rts


; ----------------------------------------------------------------------
; called from $01B3FE, $01B446, $01FD4E, $01FD5C, $01FD76
sub_025114:
	tst.w	d0
	bpl.w	loc_02511C
	clr.w	d0
loc_02511C:
	move.w	d0,$34(a2,d1.w)
	rts


; ----------------------------------------------------------------------
; called from $00C208, $00C4DA, $00C4EA, $012834, $01A136, $01D0DA, $01E146, $01E152 (+6 more)
sub_025122:
	movem.l	d0-d5/a0-a4,-(sp)
	btst	#7,(SysFlags).w
	beq.w	loc_025136
	jsr	(sub_1E41B2).l
loc_025136:
	movea.w	$22(a2),a3
	moveq	#$5,d4
loc_02513C:
	st	$60(a3)
	st	$61(a3)
	adda.w	#$80,a3
	dbra	d4,loc_02513C
	bsr.w	sub_0251DC
	moveq	#$5,d4
	movea.w	#$D00E,a4
loc_025156:
	clr.w	d5
	move.b	$0(a4,d4.w),d5
	beq.w	loc_02518A
	subq.w	#1,d5
	moveq	#$5,d3
	movea.w	$22(a2),a3
	suba.w	#$80,a3
loc_02516C:
	adda.w	#$80,a3
	cmp.b	$67(a3),d5
	dbeq	d3,loc_02516C
	bne.w	loc_02518A
	move.b	$6(a4,d4.w),$60(a3)
	move.b	d5,$61(a3)
	clr.b	$0(a4,d4.w)
loc_02518A:
	dbra	d4,loc_025156
	moveq	#$5,d4
	movea.w	#$D00E,a4
loc_025194:
	clr.w	d5
	move.b	$0(a4,d4.w),d5
	beq.w	loc_0251D2
	subq.w	#1,d5
	moveq	#$5,d3
	movea.w	$22(a2),a3
	suba.w	#$80,a3
loc_0251AA:
	adda.w	#$80,a3
	tst.b	$61(a3)
	dbmi	d3,loc_0251AA
	bpl.w	loc_0251BC
	movea.w	a3,a0
loc_0251BC:
	tst.w	$34(a3)
	dbpl	d3,loc_0251AA
	move.b	$6(a4,d4.w),$60(a0)
	move.b	d5,$61(a0)
	clr.b	$0(a4,d4.w)
loc_0251D2:
	dbra	d4,loc_025194
	movem.l	(sp)+,d0-d5/a0-a4
	rts


; ----------------------------------------------------------------------
; called from $02514C
sub_0251DC:
	movea.w	#$D00E,a4
	clr.l	(a4)
	clr.w	$4(a4)
	movea.l	#dat_028A90,a0
	tst.w	$26(a2)
	bpl.w	loc_0251F6
	addq.w	#1,a0
loc_0251F6:
	lea	$184(a2),a1
	move.w	$16(a2),d0
	asl.w	#3,d0
	adda.w	d0,a1
	move.w	$24(a2),d4
	bra.w	loc_025228
loc_02520A:
	clr.w	d5
	move.b	$0(a0,d4.w),d5
	move.b	$0(a1,d5.w),$0(a4,d4.w)
	move.b	d5,$6(a4,d4.w)
	bne.w	loc_025228
	moveq	#$1,d3
	add.w	$26(a2),d3
	move.b	d3,$0(a4,d4.w)
loc_025228:
	dbra	d4,loc_02520A
	moveq	#$5,d4
loc_02522E:
	move.b	$0(a4,d4.w),d3
	beq.w	loc_025280
	ext.w	d3
	subq.w	#1,d3
	add.w	d3,d3
	cmpi.w	#$FFFD,$6C(a2,d3.w)
	beq.w	loc_025258
	cmpi.w	#$FFFC,$6C(a2,d3.w)
	beq.w	loc_025258
	tst.w	$6C(a2,d3.w)
	ble.w	loc_025280
loc_025258:
	lea	$184(a2),a1
	move.b	$6(a4,d4.w),d0
	ext.w	d0
	asl.w	#1,d0
	movea.l	#dat_028A26,a0
	adda.w	$0(a0,d0.w),a0
loc_02526E:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	loc_025286
	move.b	$0(a1,d0.w),d0
	bsr.w	sub_02529C
	beq.s	loc_02526E
loc_025280:
	dbra	d4,loc_02522E
	rts
loc_025286:
	jsr	(sub_01A2D0).l
	move.w	d0,d3
loc_02528E:
	move.w	d3,d0
	subq.w	#1,d3
	bmi.s	loc_025280
	bsr.w	sub_02529C
	beq.s	loc_02528E
	bra.s	loc_025280


; ----------------------------------------------------------------------
; called from $02527A, $025294
sub_02529C:
	move.w	d0,d1
	subq.w	#1,d0
	add.w	d0,d0
	tst.w	$6C(a2,d0.w)
	bgt.w	loc_0252D2
	cmpi.w	#$FFFD,$6C(a2,d0.w)
	beq.w	loc_0252D2
	cmpi.w	#$FFFC,$6C(a2,d0.w)
	beq.w	loc_0252D2
	moveq	#$5,d0
loc_0252C0:
	cmp.b	$0(a4,d0.w),d1
	dbeq	d0,loc_0252C0
	beq.w	loc_0252D2
	move.b	d1,$0(a4,d4.w)
	rts
loc_0252D2:
	clr.w	d1
	rts


; ----------------------------------------------------------------------
; called from $01E14A, $01E156
sub_0252D6:
	movem.l	d0-d5/a0-a3,-(sp)
	movea.w	$22(a2),a3
	moveq	#$5,d4
loc_0252E0:
	move.w	$52(a3),d0
	cmp.w	(ram_D2F2).w,d0
	beq.w	loc_025306
	cmp.w	(ram_D2F4).w,d0
	beq.w	loc_025320
	bset	#2,$63(a3)
	move.w	#$20,d0
	bsr.w	sub_01F172
	bra.w	loc_02533C
loc_025306:
	bsr.w	sub_025428
	move.b	$61(a3),(ram_C386).w
	move.b	(ram_D2F7).w,$61(a3)
	move.w	#$4,$34(a3)
	bra.w	loc_025328
loc_025320:
	bsr.w	sub_025428
	clr.w	$34(a3)
loc_025328:
	clr.w	d3
	move.b	$61(a3),d3
	add.w	d3,d3
	move.w	#$FFFF,$6C(a2,d3.w)
	lsr.w	#1,d3
	bsr.w	sub_025470
loc_02533C:
	st	$61(a3)
	st	$60(a3)
	adda.w	#$80,a3
	dbra	d4,loc_0252E0
	movem.l	(sp)+,d0-d5/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $00C4E0, $00C4F0
sub_025352:
	movem.l	d0-d4/a0-a3,-(sp)
	movea.w	$22(a2),a3
	moveq	#$5,d4
loc_02535C:
	move.b	$60(a3),d0
	ext.w	d0
	tst.w	$34(a3)
	bne.w	loc_02537E
	tst.w	d0
	beq.w	loc_02537E
	move.w	$52(a3),-(sp)
	move.w	#$F,$52(a3)
	move.w	(sp)+,$52(a3)
loc_02537E:
	move.w	d0,$34(a3)
	bmi.w	loc_0253AE
	bsr.w	sub_025428
	cmpi.w	#$4,$34(a3)
	bne.w	loc_02539A
	moveq	#$11,d0
	bsr.w	sub_01F168
loc_02539A:
	clr.w	d3
	move.b	$61(a3),d3
	add.w	d3,d3
	move.w	#$FFFF,$6C(a2,d3.w)
	lsr.w	#1,d3
	bsr.w	sub_025470
loc_0253AE:
	st	$61(a3)
	st	$60(a3)
	adda.w	#$80,a3
	dbra	d4,loc_02535C
	movem.l	(sp)+,d0-d4/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $00C4D0, $01E13E, $02257C, $1E54D8
sub_0253C4:
	clr.b	(ram_C3F8).w
	moveq	#$10,d1
	movea.w	#$C732,a0
	bsr.w	sub_0253D8
	moveq	#$1,d1
	adda.w	#$39E,a0

; ----------------------------------------------------------------------
; called from $0253CE
sub_0253D8:
	moveq	#$36,d0
loc_0253DA:
	add.b	d1,(ram_C3F8).w
	tst.w	$6C(a0,d0.w)
	ble.w	loc_025404
	btst	#4,$6C(a0,d0.w)
	beq.w	loc_025422
	move.w	$6C(a0,d0.w),d2
	andi.w	#$7FF,d2
	bne.w	loc_025422
	sub.b	d1,(ram_C3F8).w
	bra.w	loc_025422
loc_025404:
	sub.b	d1,(ram_C3F8).w
	cmpi.w	#$FFFD,$6C(a0,d0.w)
	beq.w	loc_025422
	cmpi.w	#$FFFC,$6C(a0,d0.w)
	beq.w	loc_025422
	move.w	#$FFFE,$6C(a0,d0.w)
loc_025422:
	subq.w	#2,d0
	bpl.s	loc_0253DA
	rts


; ----------------------------------------------------------------------
; called from $01B934, $01B944, $01BADA, $022058, $025306, $025320, $025386
sub_025428:
	move.w	$34(a3),d0
	bmi.w	NullSub
	st	$65(a3)
	lea	dat_025440(pc),a0
	move.b	$0(a0,d0.w),d0
	bra.w	sub_01F172
dat_025440:
	dc.w	$0E02,$0203,$0503,$05FF


; ----------------------------------------------------------------------
; called from $1D1E40
sub_025448:
	move.w	$34(a3),d0
	bmi.w	NullSub
	tst.b	$65(a3)
	bmi.w	loc_02545C
	move.b	$65(a3),d0
loc_02545C:
	lea	dat_025468(pc),a0
	move.b	$0(a0,d0.w),d0
	bra.w	sub_01F172
dat_025468:
	dc.w	$0E02,$0203,$0503,$05FF


; ----------------------------------------------------------------------
; called from $01BAAA, $01E1B0, $01E252, $02205C, $025338, $0253AA, $1D0DDE, $1E593C
sub_025470:
	st	$65(a3)
	bclr	#6,$63(a3)
	movea.w	#$C732,a0
	btst	#6,$62(a3)
	beq.w	loc_02548C
	adda.w	#$39E,a0
loc_02548C:
	move.b	d3,$67(a3)
	moveq	#$A,d0
	ext.w	d3
	add.w	d3,d3
	move.w	$6C(a0,d3.w),d1
	bpl.w	loc_0254A8
	moveq	#$9,d0
	cmp.w	#$FFFE,d1	; general form
	bne.w	loc_0254B6
loc_0254A8:
	bsr.w	sub_01F168
	bclr	#5,$62(a3)
	clr.w	$58(a3)
loc_0254B6:
	move.w	#$FFFF,$6C(a0,d3.w)
	lsr.w	#1,d3
	move.l	a0,-(sp)
	movea.l	$1E(a0),a0
	adda.w	$8(a0),a0
	clr.l	(ram_D044).w
	tst.w	$34(a3)
	beq.w	loc_025564
	btst	#5,(ram_C33E).w
	beq.w	loc_025504
	jsr	(sub_01D0FA).l
	beq.w	loc_0254F8
	move.b	$1(a0),(ram_D044).w
	andi.b	#$F,(ram_D044).w
	bra.w	loc_025504
loc_0254F8:
	move.b	$1(a0),d0
	lsr.b	#4,d0
	neg.b	d0
	move.b	d0,(ram_D045).w
loc_025504:
	move.b	$2(a0),d0
	andi.b	#$F,d0
	neg.b	d0
	btst	#6,$62(a3)
	bne.w	loc_02551E
	move.b	$2(a0),d0
	lsr.b	#4,d0
loc_02551E:
	move.b	d0,(ram_D047).w
	cmpi.w	#$2,(ram_C4C8).w
	blt.w	loc_025564
	bgt.w	loc_025540
	jsr	(sub_0191D6).l
	lsr.w	#1,d0
	cmp.w	(ram_C4CA).w,d0
	bgt.w	loc_025564
loc_025540:
	move.w	(ram_C73E).w,d0
	sub.w	(ram_CADC).w,d0
	beq.w	loc_02555E
	btst	#6,$62(a3)
	beq.w	loc_02555A
	eori	#$8,ccr
loc_02555A:
	bpl.w	loc_025564
loc_02555E:
	move.b	#$2,(ram_D046).w
loc_025564:
	movea.l	(sp)+,a0
	movem.l	d0/d7/a1,-(sp)
	move.w	$28(a0),d7
	move.w	d3,d0
	jsr	(sub_013C76).l
	jsr	(sub_013D6E).l
	adda.w	(a1),a1
	movea.l	a1,a0
	movem.l	(sp)+,d0/d7/a1
	move.b	(ram_DDCF).w,$70(a3)
	move.b	$1(a0),d3
	andi.w	#$F0,d3
	lsr.w	#1,d3
	move.b	d3,$68(a3)
	move.b	$1(a0),d3
	andi.b	#$F,d3
	move.w	#$3,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	move.b	d3,$69(a3)
	move.b	$2(a0),d3
	lsr.b	#4,d3
	move.w	#$4,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	move.b	d3,$6A(a3)
	move.b	$2(a0),d3
	andi.b	#$F,d3
	move.w	#$5,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D044).w,d3
	add.b	(ram_D045).w,d3
	add.b	(ram_D047).w,d3
	add.b	(ram_D046).w,d3
	bsr.w	sub_025798
	lsr.b	#1,d3
	eori.b	#$F,d3
	addi.b	#$F,d3
	lsr.b	#1,d3
	move.b	d3,$6B(a3)
	move.b	$3(a0),d3
	lsr.b	#4,d3
	move.w	#$6,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D047).w,d3
	bsr.w	sub_025798
	lsr.b	#1,d3
	eori.b	#$F,d3
	addi.b	#$F,d3
	lsr.b	#1,d3
	move.b	d3,$6C(a3)
	move.b	$3(a0),$6D(a3)
	andi.b	#$F,$6D(a3)
	move.b	$6D(a3),d3
	move.w	#$7,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	move.b	d3,$6D(a3)
	move.b	$4(a0),d3
	lsr.b	#4,d3
	move.w	#$8,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D046).w,d3
	bsr.w	sub_025798
	move.b	d3,$76(a3)
	bclr	#3,$4(a3)
	move.b	$4(a0),$77(a3)
	andi.b	#$1,$77(a3)
	eori.b	#$1,$77(a3)
	bne.w	loc_025688
	bset	#3,$4(a3)
loc_025688:
	move.b	$4(a0),d3
	tst.w	$34(a3)
	bne.w	loc_02569A
	move.b	$5(a0),d3
	lsr.b	#3,d3
loc_02569A:
	andi.b	#$FE,d3
	or.b	d3,$77(a3)
	clr.b	$75(a3)
	tst.w	$34(a3)
	beq.w	loc_0256C4
	move.b	$7(a0),d3
	andi.b	#$F,d3
	cmp.b	#$6,d3	; general form
	ble.w	loc_0256C4
	subq.w	#6,d3
	move.b	d3,$75(a3)
loc_0256C4:
	move.b	$5(a0),d3
	lsr.b	#4,d3
	move.w	#$A,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D044).w,d3
	add.b	(ram_D045).w,d3
	add.b	(ram_D047).w,d3
	bsr.w	sub_025798
	move.b	d3,$72(a3)
	move.b	$5(a0),d3
	andi.b	#$F,d3
	move.w	#$B,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D044).w,d3
	add.b	(ram_D045).w,d3
	add.b	(ram_D047).w,d3
	bsr.w	sub_025798
	move.b	d3,$6E(a3)
	move.b	$6(a0),d3
	lsr.b	#4,d3
	move.w	#$C,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	move.b	d3,$73(a3)
	move.b	$6(a0),d3
	andi.b	#$F,d3
	move.w	#$D,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D046).w,d3
	add.b	(ram_D046).w,d3
	bsr.w	sub_025798
	move.b	d3,$71(a3)
	move.b	$7(a0),d3
	lsr.b	#4,d3
	move.w	#$E,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	add.b	(ram_D044).w,d3
	add.b	(ram_D047).w,d3
	bsr.w	sub_025798
	move.b	d3,$6F(a3)
	move.b	$7(a0),d3
	andi.b	#$F,d3
	cmp.b	#$6,d3	; general form
	ble.w	loc_025780
	subq.b	#6,d3
loc_025780:
	move.w	#$F,(ram_BF4A).w
	jsr	(sub_1CF6C4).l
	move.b	d3,$74(a3)
	andi.b	#$F,$74(a3)
	rts


; ----------------------------------------------------------------------
; called from $0255EA, $025614, $02565E, $0256E2, $02570A, $025744, $025766
sub_025798:
	tst.b	d3
	bpl.w	loc_0257A0
	clr.w	d3
loc_0257A0:
	cmp.b	#$1E,d3	; general form
	ble.w	loc_0257AC
	move.w	#$1E,d3
loc_0257AC:
	rts


; ----------------------------------------------------------------------
; as VBlank_Main plus game timer handling
; called from $018FF2, $026558, $1DCF44
VBlank_InGame:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_0257CE
	bclr	#0,(VideoFlags).w
	beq.w	loc_0257CA
	bsr.w	VBlank_DMATransfers2
loc_0257CA:
	bsr.w	Palette_FadeStep
loc_0257CE:
	btst	#0,(ram_C33C).w
	bne.w	loc_02586E
	btst	#2,(ram_C34A).w
	bne.w	loc_0257F6
	btst	#0,(ram_C33A).w
	bne.w	loc_02586E
	btst	#0,(ram_C344).w
	bne.w	loc_02586E
loc_0257F6:
	btst	#1,(ram_C34A).w
	bne.w	loc_02587E
	tst.w	(ram_C4CA).w
	beq.w	loc_02586E
	subi.w	#$AAA,(ram_C4CC).w
	bcc.w	loc_02586E
	bset	#3,(VideoFlags).w
	subq.w	#1,(ram_C4CA).w
	addq.w	#1,(ram_C4D2).w
	tst.w	(ram_C4C8).w
	beq.w	loc_025836
	cmpi.w	#$28,(ram_C4D2).w
	blt.w	loc_025850
	bra.w	loc_025840
loc_025836:
	cmpi.w	#$14,(ram_C4D2).w
	blt.w	loc_025850
loc_025840:
	clr.w	(ram_C4D2).w
	tst.w	(ram_C4D0).w
	beq.w	loc_025850
	subq.w	#1,(ram_C4D0).w
loc_025850:
	cmpi.w	#$3D,(ram_C4CA).w
	bgt.w	loc_02586E
	cmpi.w	#$3C,(ram_C4CA).w
	blt.w	loc_02586E
	move.w	#$2,-(sp)
	jsr	(sub_09205A).l
loc_02586E:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte
loc_02587E:
	tst.w	(ram_D344).w
	beq.s	loc_02586E
	subi.w	#$AAA,(ram_D346).w
	bcc.s	loc_02586E
	bset	#3,(VideoFlags).w
	btst	#7,(ram_C34A).w
	bne.s	loc_02586E
	subq.w	#1,(ram_D344).w
	bra.s	loc_02586E


; ----------------------------------------------------------------------
; palette fade only (installed while waiting for fades)
; called from $020006, $02709A, $1D1BC4
VBlank_Simple:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_0258B2
	bsr.w	Palette_FadeStep
loc_0258B2:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6

; ----------------------------------------------------------------------
; rte for unused interrupts and the level 4 (horizontal) interrupt
; called from $000060, $000064, $000068, $00006C, $000070, $00007C
Int_Null:
	rte


; ----------------------------------------------------------------------
; called from $0257C6
VBlank_DMATransfers2:
	bsr.w	sub_02590A

; ----------------------------------------------------------------------
; called from $0271B8
sub_0258C6:
	movea.w	#$C068,a0
	move.w	(ram_C338).w,d0
	move.w	(HScrollTableAddr).w,d1
	bsr.w	VDP_DMASafe

; ----------------------------------------------------------------------
; called from $026670
sub_0258D6:
	movea.l	(ram_BD2C).w,a6
	cmpa.l	#ram_B8CC,a6
	beq.w	NullSub
loc_0258E4:
	move.w	-(a6),d1
	move.w	-(a6),d0
	movea.l	-(a6),a0
	bsr.w	VDP_DMASafe
	cmpa.l	#ram_B8CC,a6
	bne.s	loc_0258E4
	rts


; ----------------------------------------------------------------------
; called from $0172A6, $1DD724
VBlank_DMATransfers:
	movea.w	#$C068,a0
	move.w	(ram_C338).w,d0
	move.w	(HScrollTableAddr).w,d1
	bsr.w	VDP_DMASafe
	rts


; ----------------------------------------------------------------------
; called from $0258C2
sub_02590A:
	move.w	(ram_B000).w,d0
	addq.w	#2,d0
	bsr.w	VDP_SetWriteAddr
	move.w	(ram_BD36).w,(a0)
	move.l	#$40020010,$4(a0)
	move.w	(ram_BD38).w,(a0)
	rts


; ----------------------------------------------------------------------
; called from $0193FE, $01990A, $01A384, $01A51C, $01A584, $01A5F2, $01A64C, $01A67C (+5 more)
sub_025926:
	movem.l	d0-d7/a0-a6,-(sp)
loc_02592A:
	btst	#0,(VideoFlags).w
	bne.s	loc_02592A
	movea.w	#$B8CC,a5
	bsr.w	sub_025998
	movea.w	#$C068,a6
	moveq	#$1,d6
	bsr.w	sub_025AA0
	bsr.w	sub_025E86
	bsr.w	sub_026002
	bsr.w	sub_026042
	bsr.w	sub_025CFE
	jsr	(sub_1D0EBE).l
	bsr.w	sub_025BE4
	jsr	(sub_025A58).l
	jsr	(sub_1CF49E).l
	cmpa.w	#$C068,a6
	bne.w	loc_025976
	clr.l	(a6)+
	clr.l	(a6)+
loc_025976:
	clr.b	-$5(a6)
	move.l	a6,d0
	subi.l	#ram_C068,d0
	lsr.w	#1,d0
	move.w	d0,(ram_C338).w
	move.l	a5,(ram_BD2C).w
	bset	#0,(VideoFlags).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $025936
sub_025998:
	btst	#7,(ram_C33C).w
	bne.w	NullSub
	moveq	#-$40,d0
	sub.w	(ram_BD34).w,d0
	move.w	(ram_BD30).w,d1
	move.w	d0,(ram_BD36).w
	move.w	d1,(ram_BD38).w
	neg.w	(ram_BD38).w
	move.w	(ram_BD32).w,d4
	asr.w	#3,d1
	move.w	d1,(ram_BD32).w
	moveq	#$1F,d3
	cmp.w	d4,d1
	beq.w	NullSub
	movea.l	#Art_Rink,a0
	btst	#4,(ram_C344).w
	beq.w	loc_0259E4
	movea.l	#dat_16E566,a0
	bra.w	loc_0259E8
loc_0259E4:
	adda.l	$4(a0),a0
loc_0259E8:
	blt.w	loc_025A22
loc_0259EC:
	move.w	d1,d0
	neg.w	d0
	addi.w	#$1E,d0
	andi.w	#$1F,d0
	asl.w	#7,d0
	add.w	(SpriteTableAddr).w,d0
	move.w	d0,$6(a5)
	move.w	#$1E,d0
	sub.w	d1,d0
	move.w	(a0),$4(a5)
	mulu.w	(a0),d0
	add.w	d0,d0
	lea	$4(a0,d0.w),a1
	move.l	a1,(a5)
	addq.w	#8,a5
	subq.w	#1,d1
	cmp.w	d4,d1
	dbeq	d3,loc_0259EC
	rts
loc_025A22:
	move.w	d1,d0
	neg.w	d0
	addi.w	#$1D,d0
	andi.w	#$1F,d0
	asl.w	#7,d0
	add.w	(SpriteTableAddr).w,d0
	move.w	d0,$6(a5)
	move.w	#$3D,d0
	sub.w	d1,d0
	move.w	(a0),$4(a5)
	mulu.w	(a0),d0
	add.w	d0,d0
	lea	$4(a0,d0.w),a1
	move.l	a1,(a5)
	addq.w	#8,a5
	addq.w	#1,d1
	cmp.w	d4,d1
	dbeq	d3,loc_025A22
	rts


; ----------------------------------------------------------------------
; called from $02595E
sub_025A58:
	bclr	#1,(ram_C33E).w
	beq.w	NullSub
	movea.w	#$C458,a0
	movea.w	#$B004,a1
	move.w	$2(a1),d2
	moveq	#$2,d0
	asl.w	d2,d0
	moveq	#$2,d1
	asl.w	d2,d1
	addq.w	#2,d0
	btst	#7,(ram_C33C).w
	beq.w	loc_025A86
	addi.w	#$B,d0
loc_025A86:
	asl.w	#1,d0
	add.w	(a1),d0
	moveq	#$7,d2
loc_025A8C:
	move.l	a0,(a5)+
	move.w	#$7,(a5)+
	move.w	d0,(a5)+
	adda.w	#$E,a0
	add.w	d1,d0
	dbra	d2,loc_025A8C
	rts


; ----------------------------------------------------------------------
; called from $025940
sub_025AA0:
	btst	#0,(ram_C33C).w
	bne.w	NullSub
	btst	#4,(VideoFlags).w
	beq.w	NullSub
	movea.w	#$BDC0,a3
	moveq	#$2,d0
loc_025ABA:
	move.w	(a3),d4
	bmi.w	loc_025B86
	beq.w	loc_025B86
	btst	#3,$2(a3)
	beq.w	loc_025ADE
	cmp.w	#$3,d4	; general form
	bgt.w	loc_025ADC
	addq.w	#3,d4
	bra.w	loc_025ADE
loc_025ADC:
	subq.w	#3,d4
loc_025ADE:
	movea.l	#Art_IngameMisc,a2
	adda.l	$4(a2),a2
	subq.w	#1,d4
	add.w	d4,d4
	move.w	$2(a2,d4.w),d5
	sub.w	$0(a2,d4.w),d5
	lsr.w	#3,d5
	subq.w	#1,d5
	adda.w	$0(a2,d4.w),a2
loc_025AFC:
	move.w	(a2),d2
	addi.w	#$70,d2
	add.w	(ram_B04E).w,d2
	move.w	d2,(a6)
	move.w	$6(a2),d2
	btst	#3,$2(a3)
	beq.w	loc_025B28
	move.b	$2(a2),d2
	andi.w	#$C,d2
	addq.w	#4,d2
	asl.w	#1,d2
	neg.w	d2
	sub.w	$6(a2),d2
loc_025B28:
	addi.w	#$84,d2
	add.w	(ram_B04C).w,d2
	move.w	d2,$6(a6)
	move.b	$2(a2),$2(a6)
	move.b	d6,$3(a6)
	move.b	$4(a2),d2
	asl.w	#8,d2
	andi.w	#$FF00,d2
	or.b	$2(a2),d2
	andi.w	#$F800,d2
	movem.w	d0,-(sp)
	move.b	$3(a2),d0
	asl.w	#8,d0
	andi.w	#$FF00,d0
	or.b	$5(a2),d0
	or.w	d0,d2
	movem.w	(sp)+,d0
	move.w	$2(a3),d1
	andi.w	#$F800,d1
	eor.w	d1,d2
	add.w	(ram_B028).w,d2
	move.w	d2,$4(a6)
	addq.w	#1,d6
	addq.w	#8,a6
	addq.w	#8,a2
	dbra	d5,loc_025AFC
	addq.w	#4,a3
loc_025B86:
	dbra	d0,loc_025ABA
	rts


; ----------------------------------------------------------------------
sub_025B8C:
	cmp.w	#$40,d6	; general form
	bge.w	NullSub
	movem.l	d0-d5/a0,-(sp)
	adda.l	$4(a0),a0
	add.w	d2,d2
	move.w	$2(a0,d2.w),d4
	sub.w	$0(a0,d2.w),d4
	lsr.w	#3,d4
	subq.w	#1,d4
	adda.w	$0(a0,d2.w),a0
loc_025BAE:
	move.w	$2(a0),(a6)
	add.w	d1,(a6)+
	move.b	$7(a0),(a6)+
	move.b	d6,(a6)+
	move.w	$6(a0),d2
	andi.w	#$F800,d2
	add.w	$4(a0),d2
	add.w	d3,d2
	move.w	d2,(a6)+
	move.w	(a0),(a6)
	add.w	d0,(a6)+
	addq.w	#1,d6
	cmp.w	#$40,d6	; general form
	beq.w	loc_025BDE
	addq.w	#8,a0
	dbra	d4,loc_025BAE
loc_025BDE:
	movem.l	(sp)+,d0-d5/a0
	rts


; ----------------------------------------------------------------------
; called from $02595A
sub_025BE4:
	btst	#4,(ram_C344).w
	bne.w	loc_025CFC
	movea.l	#Art_16A662,a1
	adda.l	$4(a1),a1
	move.w	(ram_BD34).w,d4
	move.w	(ram_BD30).w,d5
	clr.w	d0
	move.b	(ram_C3F8).w,d2
	move.w	#$1C,d3
	bsr.w	sub_025C24
	move.b	(ram_C3F8).w,d2
	lsr.w	#4,d2
	move.w	#$19,d3
	bsr.w	sub_025C24
	move.b	(ram_B8B3).w,d0
	bra.w	sub_025C44


; ----------------------------------------------------------------------
; called from $025C0A, $025C18
sub_025C24:
	andi.w	#$F,d2
	cmp.w	#$3,d2	; general form
	bls.w	loc_025C32
	moveq	#$3,d2
loc_025C32:
	bra.w	loc_025C3E
loc_025C36:
	move.w	d3,d0
	add.w	d2,d0
	bsr.w	sub_025C44
loc_025C3E:
	dbra	d2,loc_025C36
	rts


; ----------------------------------------------------------------------
; called from $025C20, $025C3A
sub_025C44:
	ext.w	d0
	beq.w	NullSub
	cmp.w	#$40,d6	; general form
	bge.w	NullSub
	movem.l	d0-d5,-(sp)
	add.w	d0,d0
	movea.l	a1,a0
	move.w	$2(a0,d0.w),d1
	sub.w	$0(a0,d0.w),d1
	lsr.w	#3,d1
	subq.w	#1,d1
	move.w	d1,-(sp)
	adda.w	$0(a0,d0.w),a0
	move.w	d4,d0
	addi.w	#$C0,d0
	move.w	d0,d1
	subi.w	#$90,d0
	addi.w	#$80,d1
	move.w	#$170,d2
	sub.w	d5,d2
	move.w	d2,d3
	subi.w	#$80,d2
	addi.w	#$70,d3
	move.w	(sp)+,d4
loc_025C8E:
	cmp.w	(a0),d2
	bgt.w	loc_025CF2
	cmp.w	(a0),d3
	blt.w	loc_025CF2
	cmp.w	$6(a0),d0
	bgt.w	loc_025CF2
	cmp.w	$6(a0),d1
	blt.w	loc_025CF2
	move.w	(a0),d5
	addi.w	#$70,d5
	sub.w	d2,d5
	move.w	d5,(a6)+
	move.b	$2(a0),(a6)+
	andi.b	#$F,-$1(a6)
	move.b	d6,(a6)+
	move.b	$4(a0),d5
	andi.w	#$F8,d5
	lsl.w	#8,d5
	move.w	d5,-(sp)
	move.w	$4(a0),d5
	andi.w	#$7FF,d5
	add.w	(ram_B026).w,d5
	or.w	(sp)+,d5
	move.w	d5,(a6)+
	move.w	$6(a0),d5
	addi.w	#$70,d5
	sub.w	d0,d5
	move.w	d5,(a6)+
	addq.w	#1,d6
	cmp.w	#$40,d6	; general form
	beq.w	loc_025CF8
loc_025CF2:
	addq.w	#8,a0
	dbra	d4,loc_025C8E
loc_025CF8:
	movem.l	(sp)+,d0-d5
loc_025CFC:
	rts


; ----------------------------------------------------------------------
; called from $025950
sub_025CFE:
	jmp	(loc_1E2C92).l

	dc.w	$0838,$0007,$C33C,$6700,$00B8,$0838,$0000,$C34A
	dc.w	$6600,$0072,$2F09,$4EB9,$0002,$0BDE,$0006,$BE0D
	dc.w	$0500,$3038,$C4CA,$48C0,$80FC,$0258,$2F00,$4A40
	dc.w	$6600,$000A,$5278,$B042,$6000,$0008,$4EB9,$0002
	dc.w	$5D8A,$201F,$4840,$48C0,$80FC,$003C,$2F00,$4EB9
	dc.w	$0002,$5D8A,$201F,$4840,$48C0,$5478,$B042,$80FC
	dc.w	$000A,$2F00,$4EB9,$0002,$5D8A,$201F,$4840,$48C0
	dc.w	$4EB9,$0002,$5D8A,$225F,$4EB9,$0002,$0BDE,$0006
	dc.w	$BD0D,$0500,$4E75,$227C,$0002,$5D9C,$E540,$D2C0
	dc.w	$4EB9,$0002,$0BF0,$4E75,$0004,$3000,$0004,$3100
	dc.w	$0004,$3200,$0004,$3300,$0004,$3400,$0004,$3500
	dc.w	$0004,$3600,$0004,$3700,$0004,$3800,$0004,$3900
	dc.w	$08B8,$0003,$BFB4,$6700,$EFC6,$0838,$0003,$C33E
	dc.w	$6600,$EFBC,$0C78,$0004,$C4C8,$6700,$EFB2,$307C
	dc.w	$BFC8,$227C,$001A,$CCFA,$D3E9,$0004,$3029,$0078
	dc.w	$D078,$B01C,$0040,$8000,$31C0,$BFC2,$3038,$C4CA
	dc.w	$0838,$0001,$C34A,$6700,$0006,$3038,$D344,$48C0
	dc.w	$80FC,$000A,$6100,$0054,$80FC,$0006,$6100,$004C
	dc.w	$5548,$80FC,$000A


; ----------------------------------------------------------------------
sub_025E2A:
	bsr.w	sub_025E6E
	swap	d0
	tst.l	d0
	bne.w	loc_025E3A
	moveq	#-$10,d0
	swap	d0
loc_025E3A:
	bsr.w	sub_025E6E
	move.l	a0,(a5)+
	move.w	#$5,(a5)+
	movea.w	#$B004,a1
	moveq	#$18,d0
	moveq	#$3,d2
	btst	#7,(ram_C33C).w
	beq.w	loc_025E5E
	movea.w	#$B008,a1
	moveq	#$5,d0
	moveq	#$D,d2
loc_025E5E:
	move.w	$2(a1),d1
	asl.w	d1,d0
	add.w	d2,d0
	asl.w	#1,d0
	add.w	(a1),d0
	move.w	d0,(a5)+
	rts


; ----------------------------------------------------------------------
; called from $025E2A, $025E3A
sub_025E6E:
	swap	d0
	asl.w	#1,d0
	move.w	$64(a1,d0.w),d0
	add.w	(FontTileBase).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	swap	d0
	ext.l	d0
	rts


; ----------------------------------------------------------------------
; called from $025944
sub_025E86:
	btst	#4,(ram_C350).w
	bne.w	NullSub
	movea.w	#$BDE8,a0
	movea.w	#$BEBC,a3
	move.w	#$72E,d3
	bsr.w	sub_025EDC
	adda.w	#$1C,a0
	adda.w	#$14,a3
	move.w	#$731,d3
	bsr.w	sub_025EDC
	tst.w	(ram_C398).w
	beq.w	NullSub
	movea.w	#$BE20,a0
	adda.w	#$14,a3
	move.w	#$734,d3
	bsr.w	sub_025EDC
	tst.w	(ram_C39A).w
	beq.w	NullSub
	movea.w	#$BE3C,a0
	adda.w	#$14,a3
	move.w	#$737,d3

; ----------------------------------------------------------------------
; called from $025E9C, $025EAC, $025EC4
sub_025EDC:
	tst.w	$18(a0)
	bmi.w	NullSub
	st	$6(a3)
	move.w	(a0),d0
	btst	#0,(ram_C34A).w
	bne.w	loc_025F08
	btst	#3,(ram_C33E).w
	bne.w	loc_025F08
	btst	#2,(ram_C342).w
	beq.w	loc_025F20
loc_025F08:
	move.w	d0,-(sp)
	tst.w	d0
	bpl.w	loc_025F12
	neg.w	d0
loc_025F12:
	cmp.w	#$B4,d0	; general form
	blt.w	loc_025F1E
	move.w	(sp)+,d0
	rts
loc_025F1E:
	move.w	(sp)+,d0
loc_025F20:
	move.w	$14(a0),d1
	btst	#7,(ram_C33C).w
	beq.w	loc_025F3A
	exg	d0,d1
	neg.w	d0
	subi.w	#$C5,d1
	bra.w	loc_025F42
loc_025F3A:
	sub.w	(ram_BD34).w,d0
	sub.w	(ram_BD30).w,d1
loc_025F42:
	clr.w	d2
	cmp.w	#$74,d0	; general form
	blt.w	loc_025F50
	bset	#3,d2
loc_025F50:
	cmp.w	#$FF8C,d0	; general form
	bgt.w	loc_025F5C
	bset	#2,d2
loc_025F5C:
	cmp.w	#$64,d1	; general form
	blt.w	loc_025F68
	bset	#0,d2
loc_025F68:
	cmp.w	#$FF9C,d1	; general form
	bgt.w	loc_025F74
	bset	#1,d2
loc_025F74:
	tst.w	d2
	beq.w	NullSub
	movea.l	#Joypad_RemapTable,a1
	move.b	$0(a1,d2.w),d2
	asl.w	#3,d2
	movea.l	#dat_025FC2,a1
	move.w	$0(a1,d2.w),d4
	beq.w	loc_025F96
	move.w	d4,d0
loc_025F96:
	addi.w	#$100,d0
	move.w	d0,(a3)
	move.w	$2(a1,d2.w),d4
	beq.w	loc_025FA6
	move.w	d4,d1
loc_025FA6:
	neg.w	d1
	addi.w	#$F0,d1
	move.w	d1,$2(a3)
	add.w	$4(a1,d2.w),d3
	move.w	d3,$6(a3)
	move.w	$6(a1,d2.w),$4(a3)
	bra.w	sub_0261F2
dat_025FC2:
	dc.w	$0000,$0064,$0000,$0000,$0074,$0064,$0001,$0000
	dc.w	$0074,$0000,$0002,$0000,$0074,$FF9C,$0001,$1000
	dc.w	$0000,$FF9C,$0000,$1000,$FF8C,$FF9C,$0001,$1800
	dc.w	$FF8C,$0000,$0002,$0800,$FF8C,$0064,$0001,$0800


; ----------------------------------------------------------------------
; called from $025948
sub_026002:
	movea.w	#$B8A0,a4
	move.w	#$F,d0
loc_02600A:
	clr.w	d1
	move.b	(a4)+,d1
	asl.w	#6,d1
	movea.w	#$B060,a3
	adda.w	d1,a3
	move.b	$4(a3),-(sp)
	cmpi.w	#$B0E,$58(a3)
	beq.w	loc_02602E
	cmpi.w	#$2142,$58(a3)
	bne.w	loc_026034
loc_02602E:
	bclr	#3,$4(a3)
loc_026034:
	bsr.w	sub_0261CA
	move.b	(sp)+,$4(a3)
	dbra	d0,loc_02600A
	rts


; ----------------------------------------------------------------------
; called from $02594C
sub_026042:
	bsr.w	sub_026070
	move.w	#$7,d0
	movea.w	#$BDCC,a3
loc_02604E:
	movea.w	a6,a0
	bsr.w	sub_0261CA
	cmpa.w	a6,a0
	beq.w	loc_026066
	move.w	$2(a3),d1
	add.w	d1,$6(a0)
	add.w	d1,$E(a0)
loc_026066:
	adda.w	#$1C,a3
	dbra	d0,loc_02604E
	rts


; ----------------------------------------------------------------------
; called from $026042
sub_026070:
	movea.w	#$BE74,a0
	st	$18(a0)
	cmpi.w	#$3E8,(ram_BF18).w
	beq.w	loc_02609C
	move.b	(ram_BF18).w,d0
	move.b	(ram_BF19).w,d1
	ext.w	d0
	asl.w	#2,d0
	move.w	d0,(a0)
	ext.w	d1
	asl.w	#2,d1
	move.w	d1,$14(a0)
	clr.w	$18(a0)
loc_02609C:
	movea.w	#$BE90,a0
	st	$18(a0)
	cmpi.w	#$3E8,(ram_BF16).w
	beq.w	loc_0260C8
	move.b	(ram_BF16).w,d0
	move.b	(ram_BF17).w,d1
	ext.w	d0
	asl.w	#2,d0
	move.w	d0,(a0)
	ext.w	d1
	asl.w	#2,d1
	move.w	d1,$14(a0)
	clr.w	$18(a0)
loc_0260C8:
	move.w	#$5,d4
	movea.w	#$BDCC,a0
	movea.w	#$BEB0,a1
	movea.w	#$B060,a2
	move.l	(ram_BEAC).w,d3
loc_0260DC:
	move.w	d3,d0
	andi.w	#$F,d0
	move.w	#$F,d1
	cmp.w	#$E,d0	; general form
	beq.w	loc_026114
	st	$18(a0)
	cmp.w	#$F,d0	; general form
	beq.w	loc_026120
	asl.w	#7,d0
	move.w	$0(a2,d0.w),(a0)
	move.w	$14(a2,d0.w),$14(a0)
	clr.w	$18(a0)
	move.b	$35(a2,d0.w),d1
	asl.w	#8,d1
	move.b	$70(a2,d0.w),d1
loc_026114:
	cmp.w	(a1),d1
	beq.w	loc_026120
	move.w	d1,(a1)
	bsr.w	sub_02612E
loc_026120:
	lsr.l	#4,d3
	adda.w	#$1C,a0
	addq.w	#2,a1
	dbra	d4,loc_0260DC
	rts


; ----------------------------------------------------------------------
; called from $02611C
sub_02612E:
	lea	dat_0261C2(pc),a4
	clr.w	$2(a0)
	move.w	d1,d2
	lsr.w	#4,d2
	andi.w	#$F,d2
	bne.w	loc_02614A
	move.w	#$FFF0,d2
	subq.w	#4,$2(a0)
loc_02614A:
	addi.w	#$30,d2
	clr.w	d0
	bsr.w	sub_026192
	move.w	d1,d2
	andi.w	#$F,d2
	cmp.w	#$F,d2	; general form
	bne.w	loc_026166
	move.w	#$FFF0,d2
loc_026166:
	addi.w	#$30,d2
	moveq	#$1,d0
	bsr.w	sub_026192
	move.w	d1,d2
	btst	#7,(ram_C34C).w
	beq.w	loc_02617E
	clr.w	d2
loc_02617E:
	lsr.w	#8,d2
	andi.w	#$7,d2
	bne.w	loc_02618C
	addq.w	#4,$2(a0)
loc_02618C:
	move.b	$0(a4,d2.w),d2
	moveq	#$2,d0

; ----------------------------------------------------------------------
; called from $026150, $02616C
sub_026192:
	movea.l	#Font_Small,a3
	adda.l	$4(a3),a3
	add.w	d2,d2
	move.w	$4(a3,d2.w),d2
	andi.w	#$7FF,d2
	asl.w	#5,d2
	movea.l	#Font_Small,a3
	lea	$A(a3,d2.w),a3
	move.l	a3,(a5)+
	move.w	#$10,(a5)+
	add.w	$12(a0),d0
	asl.w	#5,d0
	move.w	d0,(a5)+
	rts
dat_0261C2:
	dc.b	" DDLCRX"
	dc.b	$FF


; ----------------------------------------------------------------------
; called from $026034, $026050
sub_0261CA:
	movem.l	d0-d2,-(sp)
	move.w	(a3),d0
	move.w	$14(a3),d1
	move.w	$18(a3),d2
	bmi.w	loc_0261EC
	bsr.w	sub_0263AE
	cmp.w	#$4E20,d1	; general form
	beq.w	loc_0261EC
	bsr.w	sub_0261F2
loc_0261EC:
	movem.l	(sp)+,d0-d2
	rts


; ----------------------------------------------------------------------
; called from $025FBE, $0261E8, $02663A, $026642, $02664A, $026652, $02665A, $026662
sub_0261F2:
	move.w	$4(a3),-(sp)
	movem.l	d0-d5/a0-a2,-(sp)
	move.w	$6(a3),d4
	bmi.w	loc_0263A4
	beq.w	loc_0263A4
	andi.w	#$F800,d4
	eor.w	d4,$4(a3)
	move.w	$6(a3),d4
	andi.w	#$7FF,d4
	movea.l	#Art_PlayerSprites,a2
	adda.l	$4(a2),a2
	asl.w	#1,d4
	cmp.w	(a2),d4
	bge.w	loc_0263A4
	move.w	$2(a2,d4.w),d5
	sub.w	$0(a2,d4.w),d5
	lsr.w	#3,d5
	subq.w	#1,d5
	clr.l	d3
	move.w	$0(a2,d4.w),d3
	adda.l	d3,a2
	clr.w	d3
	clr.w	d4
loc_026240:
	move.w	d0,-(sp)
	move.w	$6(a3),d0
	andi.w	#$7FF,d0
	cmp.w	$8(a3),d0
	beq.w	loc_026306
	tst.w	d5
	bne.w	loc_02625C
	move.w	d0,$8(a3)
loc_02625C:
	movem.w	d0-d4,-(sp)
	move.w	$2(a2),d2
	andi.w	#$F000,d2
	lsr.w	#1,d2
	move.w	d2,-(sp)
	move.w	$4(a2),d2
	andi.w	#$7FF,d2
	or.w	(sp)+,d2
	clr.w	d4
	move.b	$2(a2),d4
	andi.w	#$F,d4
	movea.l	#dat_028A16,a0
	move.b	$0(a0,d4.w),d4
	btst	#0,(ram_C358).w
	beq.w	loc_02629C
	cmp.w	#$1,d4	; general form
	beq.w	loc_0262C6
loc_02629C:
	cmp.w	$8(sp),d4
	bgt.w	loc_0262C6
	cmp.w	$4(sp),d2
	blt.w	loc_0262C6
	move.w	$4(sp),d0
	add.w	$8(sp),d0
	sub.w	d2,d0
	sub.w	d4,d0
	bmi.w	loc_0262C6
	movem.w	(sp)+,d0/d1
	addq.w	#6,sp
	bra.w	loc_026302
loc_0262C6:
	add.w	$8(sp),d3
	movem.w	(sp)+,d0/d1
	addq.w	#6,sp
	movem.w	d0-d4,-(sp)
	add.w	$12(a3),d3
	ext.l	d2
	asl.l	#5,d2
	movem.l	d0/a2,-(sp)
	movea.l	#Art_PlayerSprites,a2
	move.l	a2,d0
	addi.l	#$A,d0
	add.l	d0,d2
	movem.l	(sp)+,d0/a2
	asl.w	#4,d4
	asl.w	#5,d3
	move.l	d2,(a5)+
	move.w	d4,(a5)+
	move.w	d3,(a5)+
	movem.w	(sp)+,d0-d4
loc_026302:
	move.b	d3,$A(a3,d5.w)
loc_026306:
	move.w	(sp)+,d0
	movem.w	d0-d2,-(sp)
	move.w	(a2),d2
	btst	#4,$4(a3)
	beq.w	loc_026328
	move.b	$2(a2),d2
	andi.w	#$3,d2
	addq.w	#1,d2
	asl.w	#3,d2
	neg.w	d2
	sub.w	(a2),d2
loc_026328:
	add.w	d2,d1
	move.w	d1,(a6)
	move.w	$6(a2),d2
	btst	#3,$4(a3)
	beq.w	loc_02634C
	move.b	$2(a2),d2
	andi.w	#$C,d2
	addq.w	#4,d2
	asl.w	#1,d2
	neg.w	d2
	sub.w	$6(a2),d2
loc_02634C:
	add.w	d2,d0
	move.w	d0,$6(a6)
	move.b	$2(a2),$2(a6)
	move.b	d6,$3(a6)
	move.b	$4(a2),d2
	andi.w	#$F8,d2
	lsl.w	#8,d2
	move.b	$2(a2),d2
	move.w	$4(a3),d0
	eor.w	d0,d2
	andi.w	#$F800,d2
	btst	#0,$5(a3)
	beq.w	loc_02638A
	btst	#14,d2
	beq.w	loc_02638A
	bset	#13,d2
loc_02638A:
	or.b	$A(a3,d5.w),d2
	add.w	$12(a3),d2
	move.w	d2,$4(a6)
	movem.w	(sp)+,d0-d2
	addq.w	#1,d6
	addq.w	#8,a6
	addq.w	#8,a2
	dbra	d5,loc_026240
loc_0263A4:
	movem.l	(sp)+,d0-d5/a0-a2
	move.w	(sp)+,$4(a3)
	rts


; ----------------------------------------------------------------------
; called from $0261DC
sub_0263AE:
	btst	#7,(ram_C33C).w
	beq.w	loc_0263C4
	exg	d0,d1
	neg.w	d0
	subi.w	#$C5,d1
	bra.w	loc_0263CC
loc_0263C4:
	sub.w	(ram_BD34).w,d0
	sub.w	(ram_BD30).w,d1
loc_0263CC:
	cmp.w	#$90,d0	; general form
	bgt.w	loc_0263FE
	cmp.w	#$FF70,d0	; general form
	blt.w	loc_0263FE
	addi.w	#$100,d0
	add.w	d2,d1
	asr.w	#1,d2
	add.w	d2,d1
	cmp.w	#$90,d1	; general form
	bgt.w	loc_0263FE
	cmp.w	#$FF70,d1	; general form
	blt.w	loc_0263FE
	neg.w	d1
	addi.w	#$F0,d1
	rts
loc_0263FE:
	move.w	#$4E20,d1
	rts


; ----------------------------------------------------------------------
; called from $018FB6, $01992A, $026CE6, $026D82, $1E4704
sub_026404:
	move.b	#$E7,(PSG).l
	move.b	#$DF,(PSG).l
	move.b	#$C8,(PSG).l
	move.b	#$1,(PSG).l
	move.b	#$FF,(PSG).l
	rts


; ----------------------------------------------------------------------
; called from $019122, $01925E
sub_02642E:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#1,(VideoFlags).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$DC00,(HScrollTableAddr).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$F000,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$FC00,(ram_B000).w
	moveq	#$0,d0
	bsr.w	Palette_SetAll
	bclr	#0,(ram_C33C).w
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	clr.w	(ram_BD34).w
	clr.w	(ram_BD30).w
	move.w	#$7D0,(ram_BD32).w
	st	(ram_B8C4).w
	move.w	#$800,d0
	move.w	(PlaneAAddr).w,d1
	move.w	#$7FF,d2
	bsr.w	sub_02057E
	clr.w	d4
	move.w	d4,(ram_B024).w
	movea.l	#Art_Rink_Tiles,a2
	btst	#4,(ram_C344).w
	beq.w	loc_0264B6
loc_0264B6:
	bsr.w	sub_020780
	jsr	(sub_1D1856).l
	jsr	(sub_1D1846).l
	move.w	d4,(ram_B02C).w
	bsr.w	sub_02668C
	move.w	d4,(ram_B022).w
	movea.l	#Art_16CE5C_Tiles,a2
	bsr.w	sub_020780
	move.w	d4,(ram_B026).w
	jsr	(sub_0266AC).l
	move.w	d4,(ram_B030).w
	bsr.w	sub_0266F2
	bsr.w	sub_026676
	bsr.w	sub_021310
	move.w	d4,(ram_B03A).w
	jsr	(sub_029EE6).l
	jsr	(sub_029F00).l
	move.w	d4,(ram_B03C).w
	btst	#1,(ram_C33A).w
	beq.w	loc_026528
	movea.w	#$B060,a3
	moveq	#$B,d0
loc_02651A:
	bchg	#7,$62(a3)
	adda.w	#$80,a3
	dbra	d0,loc_02651A
loc_026528:
	bsr.w	sub_026B9C
	move.l	#$FFFFFFFF,(ram_BEAC).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	st	(ram_C388).w
	st	(ram_C38A).w
	st	(ram_C38C).w
	st	(ram_C38E).w
	bsr.w	sub_026622
	move.w	(sp)+,(VideoFlags).w
	move.l	#VBlank_InGame,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bclr	#2,(VideoFlags).w
	move.w	#$2300,sr
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_026576:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_01FFA2
	bclr	#0,(ram_C33C).w
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	clr.w	(ram_BD34).w
	clr.w	(ram_BD30).w
	move.w	#$7D0,(ram_BD32).w
	st	(ram_B8C4).w
	move.w	(ram_B030).w,d4
	bsr.w	sub_0266F2
	bsr.w	sub_026676
	btst	#1,(ram_C33A).w
	beq.w	loc_0265CA
	movea.w	#$B060,a3
	moveq	#$B,d0
loc_0265BC:
	bchg	#7,$62(a3)
	adda.w	#$80,a3
	dbra	d0,loc_0265BC
loc_0265CA:
	bsr.w	sub_026B9C
	move.l	#$FFFFFFFF,(ram_BEAC).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	st	(ram_C388).w
	st	(ram_C38A).w
	st	(ram_C38C).w
	st	(ram_C38E).w
	bsr.w	sub_02668C
	bsr.w	sub_026622
	move.w	#$1C,(FadeCounter).w
	move.w	(sp)+,(VideoFlags).w
	move.l	#VBlank_InGame,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bclr	#2,(VideoFlags).w
	move.w	#$2300,sr
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $026550, $0265F6, $1DCFF8
sub_026622:
	movea.w	#$B8CC,a5
	movea.w	#$C068,a6
	moveq	#$1,d6
	movea.w	#$BDCC,a3
	clr.w	d0
	clr.w	d1
	bset	#0,(ram_C358).w
	bsr.w	sub_0261F2
	adda.w	#$1C,a3
	bsr.w	sub_0261F2
	adda.w	#$1C,a3
	bsr.w	sub_0261F2
	adda.w	#$1C,a3
	bsr.w	sub_0261F2
	adda.w	#$1C,a3
	bsr.w	sub_0261F2
	adda.w	#$1C,a3
	bsr.w	sub_0261F2
	bclr	#0,(ram_C358).w
	move.l	a5,(ram_BD2C).w
	bsr.w	sub_0258D6
	rts


; ----------------------------------------------------------------------
; called from $019F6E, $0264EE, $0265A8, $1DCF94, $1DD0AE
sub_026676:
	movea.l	#Art_Rink,a0
	adda.l	(a0),a0
	moveq	#$F,d0
	movea.w	#$BD40,a1
loc_026684:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_026684
	rts


; ----------------------------------------------------------------------
; called from $019F5C, $01A734, $0264CA, $0265F2, $1DCFF2
sub_02668C:
	move.w	(ram_B02C).w,d4
	movea.l	#Art_16D16A_Tiles,a2
	jmp	(sub_020780).l

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $019F62, $01A73A
sub_02669E:
	move.w	(ram_B022).w,d4
	movea.l	#Art_16CE5C_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $019F68, $01A740, $0264E0
sub_0266AC:
	move.w	(ram_B026).w,d4
	movea.l	#Art_16A662_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
sub_0266BA:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_0A5714_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $01A746
sub_0266C8:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_RefereeCutscene_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $01A7A0
sub_0266D6:
	move.w	(ram_B028).w,d4
	movea.l	#Art_IngameMisc_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $01A79A
sub_0266E4:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_09E52A_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $0264EA, $0265A4
sub_0266F2:
	movea.l	#dat_026756,a2
	movea.w	#$BEBC,a3
	moveq	#$3,d0
loc_0266FE:
	move.w	#$FFFF,$8(a3)
	move.w	(a2)+,(a3)
	move.w	(a2)+,$2(a3)
	move.w	(a2)+,$6(a3)
	move.w	(a2)+,$4(a3)
	move.w	d4,$12(a3)
	add.w	(a2)+,d4
	adda.w	#$14,a3
	dbra	d0,loc_0266FE
	movea.l	#dat_02677E,a2
	movea.l	#ram_BDCC,a3
	moveq	#$7,d0
loc_02672E:
	st	$8(a3)
	move.w	(a2)+,(a3)
	move.w	(a2)+,$14(a3)
	move.w	(a2)+,$18(a3)
	move.w	(a2)+,$6(a3)
	move.w	(a2)+,$4(a3)
	move.w	d4,$12(a3)
	add.w	(a2)+,d4
	adda.w	#$1C,a3
	dbra	d0,loc_02672E
	bra.w	loc_0267DE
dat_026756:
	dc.w	$0000,$0000,$0000,$0000,$0009,$0000,$0000,$0000
	dc.w	$0000,$0009,$0000,$0000,$0000,$0000,$0009,$0000
	dc.w	$0000,$0000,$0000,$0009
dat_02677E:
	dc.w	$0000,$0000,$FFFF,$0728,$0000,$0007,$0000,$0000
	dc.w	$FFFF,$072A,$0000,$0007,$0000,$0000,$FFFF,$072B
	dc.w	$0000,$0007,$0000,$0000,$FFFF,$072C,$0000,$0007
	dc.w	$0000,$0000,$FFFF,$072D,$0000,$0007,$0000,$0000
	dc.w	$FFFF,$0729,$8000,$0007,$0000,$0000,$FFFF,$067B
	dc.w	$0800,$0005,$0000,$0000,$FFFF,$067B,$0000,$0005
loc_0267DE:
	clr.w	d6
	movea.w	#$B8A0,a1
	lea	dat_02684A(pc),a2
	movea.w	#$B060,a3
	movea.w	#$B880,a4
loc_0267F0:
	moveq	#$1F,d0
	movea.w	a3,a0
loc_0267F4:
	clr.l	(a0)+
	dbra	d0,loc_0267F4
	move.w	d6,$52(a3)
	st	$8(a3)
	st	$67(a3)
	move.w	(a2)+,(a3)
	move.w	(a2)+,$14(a3)
	move.w	(a2)+,$18(a3)
	move.w	(a2)+,$6(a3)
	move.w	(a2)+,$4(a3)
	move.w	d4,$12(a3)
	add.w	(a2)+,d4
	move.w	(a2)+,$4A(a3)
	move.w	(a2)+,$4C(a3)
	addq.w	#1,a2
	move.b	(a2)+,$38(a3)
	addq.w	#1,a2
	move.b	(a2)+,$62(a3)
	adda.w	#$80,a3
	asl.w	#1,d6
	move.b	d6,(a1)+
	lsr.w	#1,d6
	move.w	d6,(a4)+
	addq.w	#1,d6
	cmp.w	#$10,d6	; general form
	bne.s	loc_0267F0
	bra.w	sub_02698A
dat_02684A:
	dc.w	$0180,$00C0,$0000,$0001,$0000,$0014,$0008,$0004
	dc.w	$0000,$0080,$FF38,$FF9C,$0000,$0001,$0000,$0014
	dc.w	$0008,$0004,$0000,$0080,$FF38,$FFB0,$0000,$0001
	dc.w	$0000,$0014,$0008,$0004,$0000,$0080,$FF38,$FFC4
	dc.w	$0000,$0001,$0000,$0014,$0008,$0004,$0000,$0080
	dc.w	$FF38,$FFD8,$0000,$0001,$0000,$0014,$0008,$0004
	dc.w	$0000,$0080,$FF38,$FFEC,$0000,$0001,$0000,$0014
	dc.w	$0008,$0004,$0000,$0080,$00C0,$00C0,$0000,$0001
	dc.w	$0001,$0014,$0008,$0004,$0000,$0040,$FF38,$0028
	dc.w	$0000,$0001,$0001,$0014,$0008,$0004,$0000,$0040
	dc.w	$FF38,$003C,$0000,$0001,$0001,$0014,$0008,$0004
	dc.w	$0000,$0040,$FF38,$0050,$0000,$0001,$0001,$0014
	dc.w	$0008,$0004,$0000,$0040,$FF38,$0064,$0000,$0001
	dc.w	$0001,$0014,$0008,$0004,$0000,$0040,$FF38,$0078
	dc.w	$0000,$0001,$0001,$0014,$0008,$0004,$0000,$0040
	dc.w	$0000,$0122,$0000,$071D,$0000,$000D,$0014,$0006
	dc.w	$0000,$0000,$0000,$FEDE,$0000,$071C,$0000,$0011
	dc.w	$0014,$0006,$0000,$0000,$0000,$0000,$0000,$029A
	dc.w	$0000,$0001,$0005,$0005,$0018,$0001,$0000,$0000
	dc.w	$0000,$0299,$0000,$0011,$0003,$0003,$0019,$0004


; ----------------------------------------------------------------------
; called from $00C62C, $011EBC, $01A37E, $01A5EC, $01A646, $01A676, $01A6E4, $01A71E (+5 more)
sub_02698A:
	movem.l	d0-d4/a0-a2,-(sp)
	movea.l	#ram_B880,a2
	movea.l	#ram_B860,a1
	movea.l	#ram_B060,a0
	move.w	#$F,d3
loc_0269A4:
	move.w	$14(a0),d4
	btst	#7,(ram_C33C).w
	beq.w	loc_0269B4
	move.w	(a0),d4
loc_0269B4:
	move.w	d4,(a1)+
	adda.w	#$80,a0
	dbra	d3,loc_0269A4
	movea.l	#ram_B860,a1
loc_0269C4:
	clr.w	d4
	movea.l	#ram_B8A0,a0
	move.w	#$E,d3
	clr.w	d0
	clr.w	d1
loc_0269D4:
	move.b	(a0)+,d0
	move.b	(a0),d1
	move.w	$0(a1,d0.w),d2
	cmp.w	$0(a1,d1.w),d2
	ble.w	loc_0269FE
	move.b	d0,(a0)
	move.b	d1,-$1(a0)
	move.l	a0,d2
	subi.l	#$FFFFB8A0,d2
	move.w	d2,$0(a2,d0.w)
	subq.w	#1,d2
	move.w	d2,$0(a2,d1.w)
	st	d4
loc_0269FE:
	dbra	d3,loc_0269D4
	tst.w	d4
	bne.s	loc_0269C4
	movem.l	(sp)+,d0-d4/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $00C4F6, $01E15A, $1E54FE
sub_026A0C:
	movem.l	d0-d2/a0-a3,-(sp)
	movea.w	#$C732,a2
	bsr.w	sub_026A26
	movea.w	#$CAD0,a2
	bsr.w	sub_026A26
	movem.l	(sp)+,d0-d2/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $026A14, $026A1C
sub_026A26:
	bclr	#4,$30(a2)
	moveq	#$5,d2
	movea.w	$22(a2),a3
loc_026A32:
	clr.b	$63(a3)
	tst.w	$34(a3)
	bmi.w	loc_026A54
	move.w	#$870,d1
	bsr.w	sub_01F3B2
	clr.w	$32(a3)
	clr.b	$5E(a3)
	andi.b	#$C2,$62(a3)
loc_026A54:
	adda.w	#$80,a3
	dbra	d2,loc_026A32
	rts


; ----------------------------------------------------------------------
; called from $019040, $1E4976
sub_026A5E:
	move.w	(ram_C758).w,-(sp)
	move.w	(ram_CAF6).w,-(sp)
	movem.l	a1-a3,-(sp)
	move.w	#$1BF,d0
	movea.l	#ram_CC8C,a1
	movea.l	#ram_C8EE,a0
	movea.l	#ram_D4B2,a2
	movea.l	#ram_D672,a3
loc_026A86:
	move.b	(a0)+,(a2)+
	move.b	(a1)+,(a3)+
	dbra	d0,loc_026A86
	movem.l	(sp)+,a1-a3
	move.l	#$39D,d0
	movea.w	#$C732,a0
loc_026A9C:
	clr.b	(a0)+
	dbra	d0,loc_026A9C
	movea.w	#$CAD0,a0
	move.w	#$39D,d0
loc_026AAA:
	clr.b	(a0)+
	dbra	d0,loc_026AAA
	movem.l	a1-a3,-(sp)
	move.w	#$1BF,d0
	movea.l	#ram_CC8C,a1
	movea.l	#ram_C8EE,a0
	movea.l	#ram_D4B2,a2
	movea.l	#ram_D672,a3
loc_026AD0:
	move.b	(a2)+,(a0)+
	move.b	(a3)+,(a1)+
	dbra	d0,loc_026AD0
	movem.l	(sp)+,a1-a3
	move.w	(sp)+,(ram_CAF6).w
	move.w	(sp)+,(ram_C758).w
	st	(ram_C7D6).w
	st	(ram_CB74).w
	movem.l	d0/a0-a2,-(sp)
	movea.w	#$C732,a2
	move.w	(ram_C3AC).w,d0
	move.w	#$B060,$22(a2)
	bsr.w	sub_026B1A
	movea.w	#$CAD0,a2
	move.w	(ram_C3AE).w,d0
	move.w	#$B360,$22(a2)
	bsr.w	sub_026B1A
	movem.l	(sp)+,d0/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $026AFE, $026B10
sub_026B1A:
	move.w	d0,$28(a2)
	movea.w	#$7FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_026B30
	movea.l	#RosterTable,a0
loc_026B30:
	asl.w	#2,d0
	move.l	$0(a0,d0.w),$1E(a2)
	tst.w	(ram_D280).w
	beq.w	loc_026B68
	move.w	d7,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_012878).l
	move.w	(sp)+,d7
	lea	$184(a2),a1
	move.l	(a0)+,(a1)+
	move.l	(a0)+,(a1)+
	addq.w	#8,a0
	move.w	#$B,d0
loc_026B5C:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_026B5C
	bsr.w	sub_026B8A
	rts
loc_026B68:
	moveq	#$D,d0
	move.w	d7,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_012878).l
	move.w	(sp)+,d7
	addq.w	#8,a0
	lea	$184(a2),a1
loc_026B7E:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_026B7E
	bsr.w	sub_026B8A
	rts


; ----------------------------------------------------------------------
; called from $026B62, $026B84
sub_026B8A:
	move.w	d0,-(sp)
	clr.w	d0
	move.b	$184(a2),d0
	subq.w	#1,d0
	move.w	d0,$26(a2)
	move.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $019F7A, $026528, $0265CA, $1DCF8E, $1DD0A8
sub_026B9C:
	clr.w	d1
	movea.w	#$C732,a0
	bsr.w	sub_026BAC
	moveq	#$20,d1
	adda.w	#$39E,a0

; ----------------------------------------------------------------------
; called from $026BA2
sub_026BAC:
	movea.l	$1E(a0),a2
	adda.w	$2(a2),a2
	adda.w	d1,a2
	movea.w	#$BD80,a1
	adda.w	d1,a1
	moveq	#$7,d0
loc_026BBE:
	move.l	(a2)+,(a1)+
	dbra	d0,loc_026BBE
	rts
loc_026BC6:
	btst	#3,(ram_C350).w
	bne.w	loc_026C08
	addq.w	#1,(ram_C4C8).w
	bchg	#1,(ram_C33A).w
	cmpi.w	#$3,(ram_C4C8).w
	blt.w	loc_026C0E
	beq.w	loc_026BFC
	move.w	#$3,(ram_C4C8).w
	tst.w	(ram_D270).w
	bne.w	loc_026BFC
	move.w	#$4,(ram_C4C8).w
loc_026BFC:
	move.w	(ram_C73E).w,d0
	sub.w	(ram_CADC).w,d0
	beq.w	loc_026C0E
loc_026C08:
	move.w	#$4,(ram_C4C8).w
loc_026C0E:
	bsr.w	sub_01FFA2
loc_026C12:
	jsr	(sub_01916E).l
	move.w	d0,-(sp)
	move.w	(FrameCounter).w,d0
loc_026C1E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_026C1E
	jsr	(sub_092262).l
	move.w	d0,-(sp)
	move.w	(FrameCounter).w,d0
loc_026C30:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_026C30
	move.w	(sp)+,d0
	jsr	(sub_0921E8).l
	move.w	#$9,d0
	jsr	(Sound_Call).l
	move.w	#$0,d0
	move.w	#$1B24,d1
	movea.l	#Z80_SoundDriver,a0
	jsr	(Sound_Call).l
	move.w	#$6,d0
	clr.w	d1
	movea.l	#SoundBank,a0
	jsr	(Sound_Call).l
	move.w	#$7,d0
	move.w	#$0,d1
	jsr	(Sound_Call).l
	bsr.w	sub_022772
	cmpi.w	#$4,(ram_C4C8).w
	bne.w	loc_026C8E
	bsr.w	sub_027B5A
loc_026C8E:
	bsr.w	sub_02260C
	cmpi.w	#$4,(ram_C4C8).w
	beq.w	loc_026CAE
	bset	#5,(ram_C356).w
	jsr	(sub_1DCE6A).l
	jmp	(loc_0191EE).l
loc_026CAE:
	bsr.w	sub_0278FC
	jsr	(sub_017A9A).l
	tst.w	(ram_D270).w
	beq.w	loc_026CCC
	bclr	#1,(ram_C33C).w
	jsr	(sub_019EA0).l
loc_026CCC:
	btst	#7,(SysFlags).w
	bne.w	loc_026CDC
	jsr	(sub_1E1F76).l
loc_026CDC:
	jmp	(loc_026CE2).l
loc_026CE2:
	bra.w	loc_026D3E
loc_026CE6:
	bsr.w	sub_026404
	jsr	(sub_0921E8).l
	move.w	#$9,d0
	jsr	(Sound_Call).l
	move.w	#$0,d0
	move.w	#$1B24,d1
	movea.l	#Z80_SoundDriver,a0
	jsr	(Sound_Call).l
	move.w	#$6,d0
	clr.w	d1
	movea.l	#SoundBank,a0
	jsr	(Sound_Call).l
	move.w	#$7,d0
	move.w	#$0,d1
	jsr	(Sound_Call).l
	jsr	(sub_1E43D0).l
	jsr	(sub_1E420E).l
	bra.w	loc_026DB2
loc_026D3E:
	jsr	(sub_0921E8).l
	move.w	#$9,d0
	jsr	(Sound_Call).l
	move.w	#$0,d0
	move.w	#$1B24,d1
	movea.l	#Z80_SoundDriver,a0
	jsr	(Sound_Call).l
	move.w	#$6,d0
	clr.w	d1
	movea.l	#SoundBank,a0
	jsr	(Sound_Call).l
	move.w	#$7,d0
	move.w	#$0,d1
	jsr	(Sound_Call).l
	bsr.w	sub_026404
	btst	#7,(SysFlags).w
	beq.w	loc_026DA8
	btst	#6,(ram_C354).w
	bne.w	loc_026DA8
	move.w	#$3,-(sp)
	jsr	(sub_092172).l
	bra.w	loc_026DB2
loc_026DA8:
	move.w	#$0,-(sp)
	jsr	(sub_092172).l
loc_026DB2:
	movea.w	#$FDFA,sp
	btst	#7,(SysFlags).w
	beq.w	loc_026E48
	movea.l	#ram_D2B4,a3
	jsr	(sub_027A4A).l
	jsr	(sub_027A10).l
	movea.l	#SaveDataMirror,a0
	movea.l	#ram_CF50,a1
	move.w	#$1F,d0
loc_026DE2:
	move.l	(a1)+,(a0)+
	dbra	d0,loc_026DE2
	move.w	(ram_CFD0).w,(a0)
	movea.w	#$B000,a0
loc_026DF0:
	clr.l	(a0)+
	cmpa.w	#$D25C,a0
	blt.s	loc_026DF0
	movea.l	#SaveDataMirror,a0
	movea.l	#ram_CF50,a1
	move.w	#$1F,d0
loc_026E08:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_026E08
	move.w	(a0),(ram_CFD0).w
	bset	#7,(SysFlags).w
	jsr	(sub_014FEE).l
	btst	#2,(ram_DD9E).w
	beq.w	loc_026E44
	jsr	(sub_0279E6).l
	jsr	(sub_027354).l
	jsr	(sub_0271FE).l
	btst	#1,(ram_DD9E).w
	bne.w	loc_026E44
loc_026E44:
	bra.w	loc_026E6C
loc_026E48:
	movea.l	#ram_B000,a0
loc_026E4E:
	clr.l	(a0)+
	cmpa.w	#$D25C,a0
	blt.s	loc_026E4E
	jsr	(sub_1DB224).l
	btst	#3,(ram_C350).w
	beq.w	loc_026E6C
	jsr	(sub_1E48DE).l
loc_026E6C:
	bset	#5,(ram_C354).w
	btst	#7,(SysFlags).w
	beq.w	loc_026E86
	btst	#6,(ram_C354).w
	beq.w	loc_026EB2
loc_026E86:
	btst	#7,(ram_C350).w
	bne.w	loc_026E9C
	jsr	(sub_015A7C).l
	jsr	(sub_01FFA2).l
loc_026E9C:
	move.w	(VDP_HVCOUNTER).l,(RandomSeed).w
	move.w	(VDP_HVCOUNTER).l,(ram_D298).w
	jsr	(sub_014AF4).l
loc_026EB2:
	btst	#7,(SysFlags).w
	beq.w	loc_026F92
	jsr	(sub_014FEE).l
	jsr	(sub_01513A).l
	btst	#0,(ram_DD9E).w
	beq.w	loc_026EE6
	btst	#1,(ram_DD9E).w
	bne.w	loc_026F20
	btst	#2,(ram_DD9E).w
	beq.w	loc_026F20
loc_026EE6:
	jsr	(sub_014CBA).l
	jsr	(sub_015060).l
	cmpa.l	#$0,a2
	beq.w	loc_026F06
	jsr	(sub_014F12).l
	beq.w	loc_026F5A
loc_026F06:
	move.w	#$1,(ram_DDD4).w
loc_026F0C:
	jsr	(sub_014B74).l
	bset	#1,(ram_C35C).w
	btst	#0,(ram_DD9E).w
	beq.s	loc_026EE6
loc_026F20:
	btst	#1,(ram_DD9E).w
	bne.w	loc_02700C
	btst	#2,(ram_DD9E).w
	bne.w	loc_026F58
	move.l	#sub_016614,(ram_DDD0).w
	jsr	(sub_0165AE).l
	jsr	(sub_1E3AA2).l
	jsr	(sub_027276).l
	btst	#1,(ram_C356).w
	bne.w	loc_026FEA
loc_026F58:
	bra.s	loc_026EE6
loc_026F5A:
	jsr	(sub_0151F4).l
	move.l	#sub_016614,(ram_DDD0).w
	jsr	(sub_0165AE).l
	btst	#0,(ram_DD9E).w
	beq.w	loc_026F80
	btst	#2,(ram_DD9E).w
	beq.s	loc_026F20
loc_026F80:
	tst.w	(ram_DDD4).w
	bne.s	loc_026F0C
	bclr	#5,(ram_C354).w
	jsr	(sub_015A7C).l
loc_026F92:
	btst	#7,(ram_C350).w
	beq.w	loc_026FB2
	move.w	#$1,(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	bra.w	loc_026FC8
loc_026FB2:
	jsr	(sub_00DE78).l
	btst	#3,(ram_C350).w
	beq.w	loc_026FC8
	jsr	(sub_1E48DE).l
loc_026FC8:
	jsr	(sub_1E1BFE).l
	jsr	(sub_1E1F76).l
	btst	#0,(ram_C34A).w
	bne.w	loc_026FE4
	jsr	(sub_0183AE).l
loc_026FE4:
	jmp	(loc_018FF2).l
loc_026FEA:
	jsr	(sub_1E3122).l
	bset	#1,(ram_DD9E).w
	bclr	#6,(SysFlags).w
	jsr	(sub_014FCE).l
	bclr	#7,(SysFlags).w
	bra.w	loc_026D3E
loc_02700C:
	cmpi.w	#$4,(ram_CFD6).w
	beq.w	loc_02701A
	bra.w	loc_027044
loc_02701A:
	btst	#3,(ram_DD9E).w
	beq.w	loc_02702A
	jsr	(sub_1E4632).l
loc_02702A:
	btst	#1,(ram_C35A).w
	bne.w	loc_02703A
	jsr	(sub_1E1F76).l
loc_02703A:
	btst	#3,(ram_DD9E).w
	beq.w	loc_027054
loc_027044:
	move.w	#$0,-(sp)
	jsr	(sub_092172).l
	jsr	(sub_1E3E5A).l
loc_027054:
	jsr	(sub_1E3122).l
	btst	#1,(ram_C35A).w
	bne.w	loc_027072
	move.l	#sub_016614,(ram_DDD0).w
	jsr	(sub_0165AE).l
loc_027072:
	bclr	#7,(SysFlags).w
	bra.w	loc_026D3E


; ----------------------------------------------------------------------
sub_02707C:
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	st	(ram_D294).w
	jmp	(loc_026D3E).l


; ----------------------------------------------------------------------
; called from $018FC2
sub_02709A:
	move.l	#VBlank_Simple,(VBlankVector).w
	bclr	#1,(VideoFlags).w
	move.w	#$5,(ram_B00E).w
	move.w	#$A000,(SpriteTableAddr).w
	move.w	#$7,(ram_B00A).w
	move.w	#$C000,(PlaneAAddr).w
	move.w	#$7,(PlaneSize).w
	move.w	#$F000,(PlaneBAddr).w
	move.w	#$F800,(HScrollTableAddr).w
	move.w	#$FC00,(ram_B000).w
	movea.w	#$BD40,a0
	moveq	#$1F,d1
loc_0270DE:
	clr.l	(a0)+
	dbra	d1,loc_0270DE
	bsr.w	Palette_LoadImmediate
	bsr.w	VDP_Init
	bsr.w	Text_Print
inl_0270F0:
	dc.w	loc_0270F6-inl_0270F0
	dc.b	$FE,$00,$00,$00
loc_0270F6:
	movea.l	#dat_16D640,a2
	movea.l	a2,a0
	movea.l	a2,a1
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	clr.w	d4
	moveq	#$F,d5
	bsr.w	TileMap_Draw
	move.w	#$EEE,(PaletteBuffer).w
	move.w	#$0,(ram_BD4E).w
	move.w	#$18,(FadeCounter).w
	move.w	#$2500,sr
	move.w	#$50,(RandomSeed).w
loc_027132:
	moveq	#$4,d0
	bsr.w	sub_0201A2
	tst.w	d1
	bne.w	loc_027144
	subq.w	#1,(RandomSeed).w
	bpl.s	loc_027132
loc_027144:
	move.w	#$2700,sr
	rts


; ----------------------------------------------------------------------
sub_02714A:
	cmpi.w	#$2,(ram_D270).w
	blt.w	NullSub
	cmpi.w	#$4,(ram_D270).w
	beq.w	NullSub
	moveq	#$7,d0
	tst.w	(FourWayPlay).w
	beq.w	loc_02716C
	move.w	#$B,d0
loc_02716C:
	sub.w	(ram_D272).w,d0
	move.w	d0,(ram_CFDA).w
	rts


; ----------------------------------------------------------------------
sub_027176:
	bsr.w	sub_027186
	moveq	#$C,d0
	moveq	#$2,d1
	move.w	#$7FF,d2
	bra.w	Text_FillRect


; ----------------------------------------------------------------------
; called from $027176
sub_027186:
	bsr.w	Text_Print
inl_02718A:
	dc.w	loc_027190-inl_02718A
	dc.b	$BF,$02,$0A,$00
loc_027190:
	cmpa.w	#$C732,a2
	bne.w	NullSub
	move.w	#$1A,(TextX).w
	rts


; ----------------------------------------------------------------------
sub_0271A0:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_0271C0
	bclr	#0,(VideoFlags).w
	beq.w	loc_0271BC
	bsr.w	sub_0258C6
loc_0271BC:
	bsr.w	Palette_FadeStep
loc_0271C0:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $018FD4
sub_0271D0:
	st	(ram_D294).w
	movea.l	#ram_D270,a0
	movea.l	#dat_0271EC,a1
	move.w	#$9,d0
loc_0271E4:
	move.w	(a1)+,(a0)+
	dbra	d0,loc_0271E4
	rts
dat_0271EC:
	dc.w	$0000,$0001,$0006,$000A,$0001,$0000,$0001,$0000
	dc.w	$0001


; ----------------------------------------------------------------------
; called from $026E34
sub_0271FE:
	movem.l	d0-d7/a0-a3,-(sp)
	movea.l	#ram_D2B4,a3
	bsr.w	sub_027834
	move.w	(ram_CFD6).w,d0
	or.w	(ram_CFD4).w,d0
	beq.w	loc_027270
	bsr.w	sub_027354
	moveq	#$7,d0
	tst.w	(FourWayPlay).w
	beq.w	loc_02722A
	move.w	#$B,d0
loc_02722A:
	tst.w	(FourWayPlay).w
	bne.w	loc_027244
	cmpi.w	#$2,(ram_CFDA).w
	ble.w	loc_027268
	subq.w	#2,(ram_CFDA).w
	bra.w	loc_027268
loc_027244:
	cmpi.w	#$1,(ram_CFDA).w
	bne.w	loc_027258
	move.w	#$3,(ram_CFDA).w
	bra.w	loc_027268
loc_027258:
	cmpi.w	#$2,(ram_CFDA).w
	bne.w	loc_027268
	move.w	#$4,(ram_CFDA).w
loc_027268:
	sub.w	(ram_CFDA).w,d0
	move.w	d0,(ram_D272).w
loc_027270:
	movem.l	(sp)+,d0-d7/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $015B36, $015D72, $015E2C, $026F48, $1DB6B6
sub_027276:
	bset	#7,(ram_C35C).w
	btst	#7,(SysFlags).w
	beq.w	loc_0272C2
	bclr	#7,(ram_C35C).w
	jsr	(sub_018534).l
	btst	#1,(ram_C356).w
	beq.w	loc_02729E
	rts
loc_02729E:
	move.w	(ram_DDA2).w,(ram_D274).w
	movea.l	#ram_D14C,a0
	moveq	#$59,d0
	moveq	#$10,d1
	jsr	(SRAM_Read).l
	clr.w	(ram_D274).w
	move.b	(ram_DDA2).w,(ram_D275).w
	bra.w	loc_0272E8
loc_0272C2:
	move.l	#$E74,d0
	moveq	#$A,d1
	jsr	(sub_029D2A).l
	moveq	#$20,d0
	bsr.w	Random
loc_0272D6:
	addq.w	#1,d0
	andi.w	#$1F,d0
	asl.w	#4,d0
	movea.l	#dat_006D74,a0
	adda.w	d0,a0
	lsr.w	#4,d0
loc_0272E8:
	moveq	#$F,d1
	move.w	(ram_D274).w,d2
	cmp.w	#$1C,d2	; general form
	bls.w	loc_0272F8
	moveq	#$1C,d2
loc_0272F8:
	cmp.b	(a0)+,d2
	dbeq	d1,loc_0272F8
	bne.s	loc_0272D6
	eori.w	#$F,d1
	move.w	d1,(ram_CFD8).w
	move.w	d0,(ram_CFD2).w
	clr.w	(ram_CFD6).w
	btst	#7,(SysFlags).w
	bne.w	loc_027336
	jsr	(sub_029FCC).l
	jsr	(SRAM_UpdateChecksum).l
	move.w	#$7,(ram_CFD4).w
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_027350
loc_027336:
	clr.w	(ram_CFD4).w
	moveq	#$7,d0
	movea.w	#$CF50,a0
loc_027340:
	clr.w	$4(a0)
	clr.w	$6(a0)
	adda.w	#$10,a0
	dbra	d0,loc_027340
loc_027350:
	clr.w	(ram_CFDC).w

; ----------------------------------------------------------------------
; called from $0184FE, $018558, $026E2E, $027218, $02792C, $027982, $1D5EBE, $1DB290 (+3 more)
sub_027354:
	movem.l	d0-d4/a0-a3,-(sp)
	btst	#7,(SysFlags).w
	beq.w	loc_02737C
	btst	#2,(ram_DD9E).w
	beq.w	loc_0275F4
	movea.l	#ram_D14C,a0
	moveq	#$59,d0
	moveq	#$10,d1
	jsr	(SRAM_Read).l
loc_02737C:
	jsr	(sub_029FF4).l
	movea.l	#ram_CFFE,a1
	movea.l	#ram_CFDE,a0
	btst	#7,(SysFlags).w
	beq.w	loc_02739E
	movea.l	#ram_D14C,a1
loc_02739E:
	movem.l	d5/d6/a4/a5,-(sp)
	movea.l	#ram_D124,a5
	movea.l	#dat_0275FA,a4
	move.l	(a4),(a5)
	move.l	$4(a4),$4(a5)
	move.l	$8(a4),$8(a5)
	move.l	$C(a4),$C(a5)
	lea	$10(a5),a4
	move.l	(a1),(a0)
	move.l	$4(a1),$4(a0)
	move.l	$8(a1),$8(a0)
	move.l	$C(a1),$C(a0)
	lea	$10(a0),a1
	moveq	#$E,d2
	move.w	(ram_CFDC).w,d0
loc_0273E4:
	move.w	d0,d1
	andi.w	#$1,d1
	move.b	$0(a0,d1.w),(a1)+
	move.b	$0(a5,d1.w),(a4)+
	addq.w	#2,a0
	addq.l	#2,a5
	cmp.w	#$B,d2	; general form
	beq.w	loc_0274EE
	cmp.w	#$7,d2	; general form
	beq.w	loc_0274EE
	cmp.w	#$5,d2	; general form
	beq.w	loc_0274C2
	cmp.w	#$3,d2	; general form
	beq.w	loc_0274C2
	cmp.w	#$1,d2	; general form
	beq.w	loc_027422
	bra.w	loc_02759E
loc_027422:
	btst	#7,(SysFlags).w
	beq.w	loc_02759E
	bsr.w	sub_027434
	bra.w	loc_02759E


; ----------------------------------------------------------------------
; called from $02742C, $0275B4
sub_027434:
	movem.l	d0-d3,-(sp)
	clr.l	d1
	move.b	-$2(a4),d1
	mulu.w	#$7,d1
	addi.l	#dat_0063E0,d1
	moveq	#$7,d2
	jsr	(sub_00B952).l
	add.l	d0,d0
	move.l	d0,-(sp)
	clr.l	d1
	move.b	-$2(a4),d1
	mulu.w	#$7,d1
	addi.l	#dat_00654C,d1
	moveq	#$7,d2
	jsr	(sub_00B952).l
	add.l	(sp)+,d0
	move.l	d0,d5
	clr.l	d1
	move.b	-$1(a4),d1
	mulu.w	#$7,d1
	addi.l	#dat_0063E0,d1
	moveq	#$7,d2
	jsr	(sub_00B952).l
	add.l	d0,d0
	move.l	d0,-(sp)
	clr.l	d1
	move.b	-$1(a4),d1
	mulu.w	#$7,d1
	addi.l	#dat_00654C,d1
	moveq	#$7,d2
	jsr	(sub_00B952).l
	add.l	(sp)+,d0
	move.l	d0,d6
	cmp.w	d5,d6
	bge.w	loc_0274BC
	move.b	-$1(a4),d5
	move.b	-$2(a4),-$1(a4)
	move.b	d5,-$2(a4)
loc_0274BC:
	movem.l	(sp)+,d0-d3
	rts
loc_0274C2:
	move.b	-$2(a4),d5
	cmp.b	-$1(a4),d5
	bge.w	loc_02759E
	move.b	-$1(a4),d6
	move.b	d5,-$1(a4)
	move.b	d6,-$2(a4)
	move.b	-$2(a1),d5
	move.b	-$1(a1),d6
	move.b	d5,-$1(a1)
	move.b	d6,-$2(a1)
	bra.w	loc_02759E
loc_0274EE:
	clr.w	d6
	move.b	-$4(a4),d5
	cmp.b	-$3(a4),d5
	ble.w	loc_027516
	move.b	-$3(a4),d6
	move.b	d5,-$3(a4)
	move.b	d6,-$4(a4)
	move.b	-$3(a1),-(sp)
	move.b	-$4(a1),-$3(a1)
	move.b	(sp)+,-$4(a1)
loc_027516:
	move.b	-$3(a4),d5
	cmp.b	-$2(a4),d5
	ble.w	loc_02753C
	move.b	-$2(a4),d6
	move.b	d5,-$2(a4)
	move.b	d6,-$3(a4)
	move.b	-$3(a1),-(sp)
	move.b	-$2(a1),-$3(a1)
	move.b	(sp)+,-$2(a1)
loc_02753C:
	move.b	-$2(a4),d5
	cmp.b	-$1(a4),d5
	ble.w	loc_027562
	move.b	-$1(a4),d6
	move.b	d5,-$1(a4)
	move.b	d6,-$2(a4)
	move.b	-$2(a1),-(sp)
	move.b	-$1(a1),-$2(a1)
	move.b	(sp)+,-$1(a1)
loc_027562:
	tst.w	d6
	bne.s	loc_0274EE
	move.b	-$4(a4),d5
	move.b	-$4(a1),d6
	move.b	-$3(a4),-$4(a4)
	move.b	-$3(a1),-$4(a1)
	move.b	d5,-$3(a4)
	move.b	d6,-$3(a1)
	move.b	-$4(a4),d5
	move.b	-$4(a1),d6
	move.b	-$1(a4),-$4(a4)
	move.b	-$1(a1),-$4(a1)
	move.b	d5,-$1(a4)
	move.b	d6,-$1(a1)
loc_02759E:
	lsr.w	#1,d0
	dbra	d2,loc_0273E4
	btst	#7,(SysFlags).w
	beq.w	loc_0275B8
	movea.l	#ram_CFFC,a4
	bsr.w	sub_027434
loc_0275B8:
	movem.l	(sp)+,d5/d6/a4/a5
	bsr.w	sub_027B42
	tst.w	d1
	bmi.w	loc_0275F4
	movea.w	#$CFDE,a0
	adda.w	d2,a0
	adda.w	d2,a0
	movea.w	#$CF50,a1
loc_0275D2:
	clr.w	$A(a1)
	clr.w	$C(a1)
	clr.w	$8(a1)
	bclr	#1,$E(a1)
	bsr.w	sub_02760A
	adda.w	#$10,a1
	dbra	d1,loc_0275D2
	bsr.w	sub_027648
loc_0275F4:
	movem.l	(sp)+,d0-d4/a0-a3
	rts
dat_0275FA:
	dc.w	$0801,$0504,$0603,$0702,$0801,$0504,$0603,$0702


; ----------------------------------------------------------------------
; called from $0275E4
sub_02760A:
	cmpi.w	#$2,(ram_CFD4).w
	beq.w	loc_027638
	cmpi.w	#$3,(ram_CFD4).w
	beq.w	loc_027638
	cmpi.w	#$5,(ram_CFD4).w
	beq.w	loc_027638
	bset	#0,$E(a1)
	move.b	(a0)+,$3(a1)
	move.b	(a0)+,$1(a1)
	rts
loc_027638:
	bclr	#0,$E(a1)
	move.b	(a0)+,$1(a1)
	move.b	(a0)+,$3(a1)
	rts


; ----------------------------------------------------------------------
; called from $0275F0
sub_027648:
	movem.l	d0-d3/a0/a1,-(sp)
	clr.w	(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	tst.w	(ram_D294).w
	beq.w	loc_0277CC
	tst.w	(ram_D270).w
	beq.w	loc_0277B6
	btst	#0,(ram_C34A).w
	bne.w	loc_0277B6
	bsr.w	sub_027B42
	movea.w	#$CFDE,a0
	move.w	(ram_CFD8).w,d2
	move.b	$0(a0,d2.w),d2
	btst	#7,(SysFlags).w
	beq.w	loc_027696
	clr.w	d2
	move.b	(ram_DDA2).w,d2
loc_027696:
	movea.w	#$CF50,a1
	moveq	#$10,d4
	mulu.w	d1,d4
	adda.w	d4,a1
	st	(ram_CFD0).w
	clr.w	d0
loc_0276A6:
	cmp.w	(a1),d2
	beq.w	loc_0276DC
	cmp.w	$2(a1),d2
	beq.w	loc_0276C0
	suba.w	#$10,a1
	dbra	d1,loc_0276A6
	bra.w	loc_0277CC
loc_0276C0:
	moveq	#$4,d0
	tst.w	(FourWayPlay).w
	beq.w	loc_0276CE
	move.w	#$5,d0
loc_0276CE:
	move.w	(a1),(ram_D276).w
	move.w	$2(a1),(ram_D274).w
	bra.w	loc_0276E8
loc_0276DC:
	clr.w	d0
	move.w	$2(a1),(ram_D276).w
	move.w	(a1),(ram_D274).w
loc_0276E8:
	add.w	(ram_CFDA).w,d0
	move.w	d1,(ram_CFD0).w
	move.w	(a1),(ram_C3AC).w
	move.w	$2(a1),(ram_C3AE).w
	btst	#0,$E(a1)
	asl.w	#2,d0
	lea	dat_02776E(pc),a0
	tst.w	(FourWayPlay).w
	beq.w	loc_027712
	lea	ptrs_02778E(pc),a0
loc_027712:
	move.w	$0(a0,d0.w),(ram_C394).w
	move.w	$2(a0,d0.w),(ram_C396).w
	tst.w	(FourWayPlay).w
	beq.w	loc_0277CC
	cmp.w	#$4,d0	; general form
	beq.w	loc_02773A
	cmp.w	#$18,d0	; general form
	beq.w	loc_02773A
	bra.w	loc_02774A
loc_02773A:
	move.w	(ram_C394).w,(ram_C398).w
	move.w	(ram_C396).w,(ram_C39A).w
	bra.w	loc_0277CC
loc_02774A:
	cmp.w	#$8,d0	; general form
	beq.w	loc_02775E
	cmp.w	#$1C,d0	; general form
	beq.w	loc_02775E
	bra.w	loc_0277CC
loc_02775E:
	move.w	(ram_C394).w,(ram_C398).w
	move.w	#$0,(ram_C39A).w
	bra.w	loc_0277CC
dat_02776E:
	dc.w	$0001,$0000,$0001,$0001,$0001,$0002,$0002,$0001
	dc.w	$0002,$0000,$0002,$0002,$0002,$0001,$0001,$0002

ptrs_02778E:
	dc.l	dat_010000
	dc.l	dat_010002
	dc.l	dat_010002
	dc.w	$0001,$0001,$0001,$0002,$0002,$0000,$0002,$0001
	dc.w	$0002,$0001,$0002,$0002,$0002,$0001
loc_0277B6:
	move.w	(ram_D272).w,d0
	asl.w	#2,d0
	lea	dat_0277D2(pc),a0
	move.w	$0(a0,d0.w),(ram_C394).w
	move.w	$2(a0,d0.w),(ram_C396).w
loc_0277CC:
	movem.l	(sp)+,d0-d3/a0/a1
	rts
dat_0277D2:
	dc.w	$0000,$0000,$0001,$0000,$0002,$0000,$0001,$0001
	dc.w	$0001,$0002,$0001,$0002,$0001,$0002,$0838,$0007
	dc.w	$C352,$6600,$003C


; ----------------------------------------------------------------------
sub_0277F8:
	st	(ram_CFD0).w
	clr.l	d3
	move.w	(ram_C3AC).w,d1
	bset	d1,d3
	move.w	(ram_C3AE).w,d1
	bset	d1,d3
	movea.w	#$CF50,a1
	moveq	#$7,d2
loc_027810:
	bsr.w	sub_027828
	move.w	d0,(a1)
	bsr.w	sub_027828
	move.w	d0,$2(a1)
	adda.w	#$10,a1
	dbra	d2,loc_027810
	rts


; ----------------------------------------------------------------------
; called from $027810, $027816, $027830
sub_027828:
	moveq	#$1D,d0
	bsr.w	Random
	bset	d0,d3
	bne.s	sub_027828
	rts


; ----------------------------------------------------------------------
; called from $027208, $02797E, $1D5EA2, $1DB27E, $1DB6A0
sub_027834:
	moveq	#$4,d0
	lea	$A(a3),a0
loc_02783A:
	move.w	-(a0),-(sp)
	dbra	d0,loc_02783A
	moveq	#$7,d2
	movea.w	#$CFC0,a1
loc_027846:
	bclr	#2,$E(a1)
	moveq	#$5,d0
	bsr.w	sub_027B24
	move.w	d0,$6(a1)
	cmp.w	#$4,d0	; general form
	bne.w	loc_027864
	bset	#2,$E(a1)
loc_027864:
	moveq	#$5,d0
	bsr.w	sub_027B24
	move.w	d0,$4(a1)
	cmp.w	#$4,d0	; general form
	bne.w	loc_02787C
	bset	#2,$E(a1)
loc_02787C:
	suba.w	#$10,a1
	dbra	d2,loc_027846
	move.w	#$4000,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFDC).w
	move.w	#$8,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFDA).w
	tst.w	(FourWayPlay).w
	beq.w	loc_0278C8
	cmpi.w	#$1,(ram_CFDA).w
	bne.w	loc_0278B8
	move.w	#$3,(ram_CFDA).w
	bra.w	loc_0278C8
loc_0278B8:
	cmpi.w	#$2,(ram_CFDA).w
	bne.w	loc_0278C8
	move.w	#$4,(ram_CFDA).w
loc_0278C8:
	moveq	#$10,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFD8).w
	moveq	#$4,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFD6).w
	moveq	#$8,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFD4).w
	moveq	#$20,d0
	bsr.w	sub_027B24
	move.w	d0,(ram_CFD2).w
	moveq	#$4,d0
	lea	(a3),a0
loc_0278F4:
	move.w	(sp)+,(a0)+
	dbra	d0,loc_0278F4
	rts


; ----------------------------------------------------------------------
; called from $026CAE
sub_0278FC:
	tst.w	(ram_D272).w
	beq.w	NullSub
	tst.w	(ram_D270).w
	beq.w	NullSub
	cmpi.w	#$4,(ram_D270).w
	beq.w	NullSub
	bset	#6,(SysFlags).w
	move.w	#$1,(ram_D270).w
	move.w	#$1,(ram_D2A8).w
	bsr.w	sub_027CD0
	bsr.w	sub_027354
	cmpi.w	#$4,(ram_CFD6).w
	beq.w	loc_027994
	btst	#7,(SysFlags).w
	bne.w	loc_02794C
	tst.w	(ram_CFD0).w
	bmi.w	loc_027994
loc_02794C:
	movea.l	#ram_D2B4,a3
	bsr.w	sub_027A4A
	jsr	(sub_027A10).l
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	btst	#2,(ram_C340).w
	beq.w	loc_027986
	movea.w	#$D2AA,a3
	bsr.w	sub_027834
	bsr.w	sub_027354
loc_027986:
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	rts
loc_027994:
	movea.w	#$D2B4,a3
	bsr.w	sub_027AC6
	jsr	(sub_027A10).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	move.w	#$2,(ram_D270).w
	move.w	#$2,(ram_D2A8).w
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	NullSub
	move.w	#$3,(ram_D270).w
	move.w	#$3,(ram_D2A8).w
	rts


; ----------------------------------------------------------------------
; called from $026E28, $1D5E92, $1DB272, $1DB69A
sub_0279E6:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$E74,d0
	btst	#7,(SysFlags).w
	beq.w	loc_0279FC
	moveq	#$4F,d0
loc_0279FC:
	moveq	#$A,d1
	movea.l	#ram_D2B4,a0
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01850E, $026DCC, $027956, $02799C
sub_027A10:
	movem.l	d0/d1/a0,-(sp)
	move.l	#$E74,d0
	btst	#7,(SysFlags).w
	beq.w	loc_027A30
	btst	#2,(ram_DD9E).w
	beq.w	loc_027A44
	moveq	#$4F,d0
loc_027A30:
	moveq	#$A,d1
	movea.l	#ram_D2B4,a0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
loc_027A44:
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $018508, $026DC6, $027952, $027DF6
sub_027A4A:
	bsr.w	sub_027AC6
	move.w	(ram_CFD2).w,d0
	moveq	#$20,d1
	bsr.w	sub_027AAE
	move.w	(ram_CFD4).w,d0
	moveq	#$8,d1
	bsr.w	sub_027AAE
	move.w	(ram_CFD6).w,d0
	moveq	#$4,d1
	bsr.w	sub_027AAE
	move.w	(ram_CFD8).w,d0
	moveq	#$10,d1
	bsr.w	sub_027AAE
	move.w	(ram_CFDA).w,d0
	moveq	#$8,d1
	bsr.w	sub_027AAE
	move.w	(ram_CFDC).w,d0
	move.w	#$4000,d1
	bsr.w	sub_027AAE
	moveq	#$5,d1
	moveq	#$7,d2
	movea.w	#$CF50,a1
loc_027A94:
	move.w	$4(a1),d0
	bsr.w	sub_027AAE
	move.w	$6(a1),d0
	bsr.w	sub_027AAE
	adda.w	#$10,a1
	dbra	d2,loc_027A94
	rts


; ----------------------------------------------------------------------
; called from $027A54, $027A5E, $027A68, $027A72, $027A7C, $027A88, $027A98, $027AA0
sub_027AAE:
	movem.l	d0/d1,-(sp)
	exg	d0,d1
	bsr.w	sub_027AEE
	clr.l	d0
	move.w	d1,d0
	bsr.w	sub_027AD2
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $027998, $027A4A
sub_027AC6:
	movea.w	a3,a0
	moveq	#$4,d0
loc_027ACA:
	clr.w	(a0)+
	dbra	d0,loc_027ACA
	rts


; ----------------------------------------------------------------------
; called from $027ABC
sub_027AD2:
	movem.l	d1/a0,-(sp)
	lea	$A(a3),a0
	moveq	#$3,d1
	add.l	d0,-(a0)
	bra.w	loc_027AE4
loc_027AE2:
	addq.w	#1,-(a0)
loc_027AE4:
	dbcc	d1,loc_027AE2
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $027AB4
sub_027AEE:
	movem.l	d1-d4/a0,-(sp)
	movea.w	a3,a0
	moveq	#$4,d4
loc_027AF6:
	move.w	(a0),-(sp)
	clr.w	(a0)+
	dbra	d4,loc_027AF6
	moveq	#$4,d4
loc_027B00:
	move.w	d0,d1
	mulu.w	(sp)+,d1
	lea	$2(a3),a0
	adda.w	d4,a0
	adda.w	d4,a0
	move.w	d4,d2
	add.l	d1,-(a0)
	bra.w	loc_027B16
loc_027B14:
	addq.w	#1,-(a0)
loc_027B16:
	dbcc	d2,loc_027B14
	dbra	d4,loc_027B00
	movem.l	(sp)+,d1-d4/a0
	rts


; ----------------------------------------------------------------------
; called from $02784E, $027866, $027888, $027894, $0278CA, $0278D4, $0278DE, $0278E8
sub_027B24:
	movem.l	d1/d2/a0,-(sp)
	movea.w	a3,a0
	moveq	#$4,d1
	clr.l	d2
loc_027B2E:
	move.w	(a0),d2
	divu.w	d0,d2
	move.w	d2,(a0)+
	dbra	d1,loc_027B2E
	swap	d2
	move.w	d2,d0
	movem.l	(sp)+,d1/d2/a0
	rts


; ----------------------------------------------------------------------
; called from $014C26, $0183B8, $018436, $022732, $022772, $0275BC, $027676, $027CF0 (+2 more)
sub_027B42:
	move.l	d0,-(sp)
	moveq	#-$10,d2
	moveq	#$10,d1
	move.w	(ram_CFD6).w,d0
loc_027B4C:
	add.w	d1,d2
	lsr.w	#1,d1
	dbra	d0,loc_027B4C
	subq.w	#1,d1
	move.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $026C8A
sub_027B5A:
	btst	#7,(SysFlags).w
	bne.w	loc_027C3E
	cmpi.w	#$1,(ram_D270).w
	blt.w	NullSub
	bsr.w	sub_027C40
	movea.w	#$CFDE,a0
	move.w	(ram_CFD8).w,d2
	move.b	$0(a0,d2.w),d2
	movea.w	#$C732,a2
	cmp.w	$28(a2),d2
	beq.w	loc_027B96
	adda.w	#$39E,a2
	cmp.w	$28(a2),d2
	bne.w	loc_027C3E
loc_027B96:
	adda.w	#$C0,a2
	moveq	#$6F,d0
	movea.w	#$CE6E,a1
loc_027BA0:
	clr.w	d1
	move.b	(a2)+,d1
	add.w	d1,(a1)+
	dbra	d0,loc_027BA0
	bset	#6,(SysFlags).w
	move.w	d2,d7
	jsr	(sub_01A20E).l
	move.w	d0,d6
	move.w	#$1B,d3
	sub.w	d6,d3
	add.w	d6,d6
	clr.w	d7
	moveq	#$A,d2
	move.l	#dat_007470,d1
	movea.l	#ram_CE6E,a0
	adda.w	d6,a0
	jsr	(sub_014A62).l
	moveq	#$A,d2
	move.l	#dat_007560,d1
	movea.l	#ram_CEA6,a0
	adda.w	d6,a0
	jsr	(sub_014A62).l
	moveq	#$9,d2
	move.l	#dat_007650,d1
	movea.l	#ram_CF16,a0
	adda.w	d6,a0
	jsr	(sub_014A62).l
	asr.w	#1,d6
	move.w	d6,d3
	moveq	#$D,d2
	move.l	#dat_007728,d1
	movea.l	#ram_CEDE,a0
	jsr	(sub_014A62).l
	moveq	#$D,d2
	move.l	#$774F,d1
	movea.l	#ram_CE6E,a0
	jsr	(sub_014A62).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
loc_027C3E:
	rts


; ----------------------------------------------------------------------
; called from $019EB4, $027B6E
sub_027C40:
	movea.w	#$CFDE,a0
	move.w	(ram_CFD8).w,d2
	move.b	$0(a0,d2.w),d2
	move.w	d2,d7
	jsr	(sub_01A20E).l
	move.w	d0,d6
	move.w	#$1B,d3
	sub.w	d6,d3
	add.w	d6,d6
	clr.w	d7
	moveq	#$A,d2
	move.l	#dat_007470,d1
	movea.l	#ram_CE6E,a0
	adda.w	d6,a0
	jsr	(sub_014A42).l
	moveq	#$A,d2
	move.l	#dat_007560,d1
	movea.l	#ram_CEA6,a0
	adda.w	d6,a0
	jsr	(sub_014A42).l
	moveq	#$9,d2
	move.l	#dat_007650,d1
	movea.l	#ram_CF16,a0
	adda.w	d6,a0
	jsr	(sub_014A42).l
	asr.w	#1,d6
	move.w	d6,d3
	moveq	#$D,d2
	move.l	#dat_007728,d1
	movea.l	#ram_CEDE,a0
	jsr	(sub_014A42).l
	moveq	#$D,d2
	move.l	#$774F,d1
	movea.l	#ram_CE6E,a0
	jsr	(sub_014A42).l
	rts


; ----------------------------------------------------------------------
; called from $027928
sub_027CD0:
	tst.w	(ram_CFD0).w
	bmi.w	loc_027CF0
	move.w	(ram_CFD0).w,d0
	mulu.w	#$10,d0
	movea.w	#$CF50,a0
	move.w	(ram_C73E).w,$A(a0,d0.w)
	move.w	(ram_CADC).w,$C(a0,d0.w)
loc_027CF0:
	bsr.w	sub_027B42
	movea.w	#$CF50,a0
	moveq	#$10,d3
	mulu.w	d1,d3
	adda.w	d3,a0
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_027E46
loc_027D08:
	cmpi.w	#$4,$4(a0)
	beq.w	loc_027D4A
	cmpi.w	#$4,$6(a0)
	beq.w	loc_027D4A
	clr.w	d3
	btst	#0,$E(a0)
	beq.w	loc_027D2C
	eori.w	#$2,d3
loc_027D2C:
	move.w	$A(a0),d0
	sub.w	$C(a0),d0
	bpl.w	loc_027D3C
	eori.w	#$2,d3
loc_027D3C:
	btst	#7,(SysFlags).w
	bne.w	loc_027D4A
	addq.w	#1,$4(a0,d3.w)
loc_027D4A:
	suba.w	#$10,a0
	dbra	d1,loc_027D08
	btst	#7,(SysFlags).w
	bne.w	loc_027D60
	addq.w	#1,(ram_CFD4).w
loc_027D60:
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_027E00
	move.w	(ram_CFD0).w,d0
	mulu.w	#$10,d0
	movea.w	#$CF50,a0
	adda.w	d0,a0
	cmpi.w	#$4,$4(a0)
	beq.w	loc_027D8C
	cmpi.w	#$4,$6(a0)
	bne.w	NullSub
loc_027D8C:
	cmpi.w	#$3,(ram_CFD6).w
	bge.w	loc_027E00
	btst	#7,(SysFlags).w
	bne.w	NullSub
	bsr.w	sub_027B42
	movea.w	#$CF50,a0
	moveq	#$10,d3
	mulu.w	d1,d3
	adda.w	d3,a0
loc_027DAE:
	cmp.w	(ram_CFD0).w,d1
	beq.w	loc_027DEA
	cmpi.w	#$4,$4(a0)
	beq.w	loc_027DEA
	cmpi.w	#$4,$6(a0)
	beq.w	loc_027DEA
	addq.w	#1,$4(a0)
	move.l	#$C8,d0
	jsr	(Random).l
	andi.w	#$1,d0
	beq.s	loc_027DAE
	subq.w	#1,$4(a0)
	addq.w	#1,$6(a0)
	bra.s	loc_027DAE
loc_027DEA:
	suba.w	#$10,a0
	dbra	d1,loc_027DAE
	movea.w	#$D2AA,a3
	bsr.w	sub_027A4A
	bset	#2,(ram_C340).w
loc_027E00:
	clr.w	(ram_CFD4).w
	bsr.w	sub_027B42
	movea.w	#$CF50,a0
	moveq	#$10,d3
	mulu.w	d1,d3
	adda.w	d3,a0
	clr.w	d3
loc_027E14:
	cmpi.w	#$4,$4(a0)
	beq.w	loc_027E20
	bset	d1,d3
loc_027E20:
	clr.w	$4(a0)
	clr.w	$6(a0)
	suba.w	#$10,a0
	dbra	d1,loc_027E14
	moveq	#$1,d1
	asl.w	d2,d1
	subq.w	#1,d1
	and.w	d1,(ram_CFDC).w
	asl.w	d2,d3
	or.w	d3,(ram_CFDC).w
	addq.w	#1,(ram_CFD6).w
	rts
loc_027E46:
	clr.w	d3
loc_027E48:
	move.w	$A(a0),d0
	cmp.w	$C(a0),d0
	bhi.w	loc_027E56
	bset	d1,d3
loc_027E56:
	btst	#0,$E(a0)
	beq.w	loc_027E62
	bchg	d1,d3
loc_027E62:
	suba.w	#$10,a0
	dbra	d1,loc_027E48
	moveq	#$1,d1
	asl.w	d2,d1
	subq.w	#1,d1
	and.w	d1,(ram_CFDC).w
	asl.w	d2,d3
	or.w	d3,(ram_CFDC).w
	addq.w	#1,(ram_CFD6).w
	rts


; ----------------------------------------------------------------------
; called from $021A78
sub_027E80:
	cmpi.w	#$40,(ram_C452).w
	bgt.w	NullSub
	bset	#7,(ram_C33A).w
	bne.w	NullSub
	btst	#3,(ram_C350).w
	bne.w	NullSub
	jsr	(sub_1E30D6).l
	jsr	(sub_022218).l
	movem.l	d0/a1,-(sp)
	bset	#3,(VideoFlags).w
	move.w	(FrameCounter).w,d0
loc_027EB8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_027EB8
	movem.l	(sp)+,d0/a1
	movem.l	d0-d5/a0-a4,-(sp)
	bsr.w	Text_Print
inl_027ECA:
	dc.w	loc_027ED0-inl_027ECA
	dc.b	$BF,$02,$0E,$00
loc_027ED0:
	moveq	#$1C,d0
	moveq	#$9,d1
	bsr.w	Text_PrintDigitsBig
	bsr.w	Text_PrintScoreboardAlt
inl_027EDC:
	dc.w	loc_027F02-inl_027EDC
	dc.b	$F8,$04,$01,$03,$10
	dc.b	"    Stars of the Game     "
	dc.b	$F8,$04,$01,$03,$0F
loc_027F02:
	bsr.w	sub_027F98
	move.w	#$12,(TextY).w
	moveq	#$2,d2
loc_027F0E:
	bsr.w	sub_027F58
	move.w	#$1A,(TextX).w
	addq.w	#1,(TextY).w
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	bsr.w	Text_Print_Worker
	bsr.w	sub_0284FC
	move.w	#$3,(TextX).w
	bsr.w	Text_Print_Worker
	dbra	d2,loc_027F0E
	move.w	(ram_C73E).w,d0
	sub.w	(ram_CADC).w,d0
	ble.w	loc_027F52
	move.w	#$F,-(sp)
	jsr	(sub_092172).l
loc_027F52:
	movem.l	(sp)+,d0-d5/a0-a4
	rts


; ----------------------------------------------------------------------
; called from $027F0E
sub_027F58:
	movem.l	d1/d2/a1/a4,-(sp)
	movea.w	#$D14C,a4
	clr.l	d0
	moveq	#$37,d2
loc_027F64:
	cmp.l	(a4)+,d0
	bge.w	loc_027F70
	lea	-$4(a4),a1
	move.l	(a1),d0
loc_027F70:
	dbra	d2,loc_027F64
	clr.l	(a1)
	move.w	a1,d0
	subi.w	#$D14C,d0
	lsr.w	#2,d0
	movea.w	#$C732,a2
	cmp.w	#$1C,d0	; general form
	blt.w	loc_027F92
	subi.w	#$1C,d0
	adda.w	#$39E,a2
loc_027F92:
	movem.l	(sp)+,d1/d2/a1/a4
	rts


; ----------------------------------------------------------------------
; called from $027F02
sub_027F98:
	movea.w	#$D14C,a4
	jsr	(sub_0191D6).l
	move.w	d0,d5
	add.w	d2,d5
	movea.w	#$C732,a2
	lea	$39E(a2),a3
	bsr.w	sub_027FF8
	movea.w	a3,a2
	lea	-$39E(a2),a3
	bsr.w	sub_027FF8
	cmpi.w	#$3,(ram_C4C8).w
	bne.w	loc_027FF6
	tst.w	d3
	beq.w	loc_027FF6
	movea.w	#$C4D2,a0
	adda.w	(ram_C4D6).w,a0
	clr.w	d0
	btst	#7,$2(a0)
	beq.w	loc_027FE4
	addi.w	#$1C,d0
loc_027FE4:
	add.b	$3(a0),d0
	asl.w	#2,d0
	movea.w	#$D14C,a0
	move.l	#$7FFFFFFF,$0(a0,d0.w)
loc_027FF6:
	rts


; ----------------------------------------------------------------------
; called from $027FAE, $027FB8
sub_027FF8:
	movea.w	a2,a1
	move.w	$C(a2),d3
	sub.w	$C(a3),d3
	ext.l	d3
	moveq	#$1B,d4
	jsr	(sub_01A268).l
	neg.w	d0
	add.w	d4,d0
loc_028010:
	move.l	d3,(a4)
	cmp.w	d0,d4
	bhi.w	loc_028052
	clr.w	d1
	move.b	$C0(a2),d1
	mulu.w	#$2AF8,d1
	add.l	d1,(a4)
	clr.w	d1
	move.b	$DC(a2),d1
	mulu.w	#$2774,d1
	add.l	d1,(a4)
	clr.w	d1
	move.b	$F8(a2),d1
	mulu.w	#$A,d1
	tst.w	d3
	bne.w	loc_02804C
	mulu.w	#$64,d1
	add.l	d1,(a4)
	clr.l	d1
	add.w	$14C(a1),d1
loc_02804C:
	add.l	d1,(a4)
	bra.w	loc_02808A
loc_028052:
	cmp.w	$14C(a1),d5
	bhi.w	loc_02808A
	clr.w	d1
	move.b	$C0(a2),d1
	mulu.w	#$64,d1
	clr.w	d2
	move.b	$F8(a2),d2
	beq.w	loc_02808A
	divu.w	d2,d1
	cmp.w	#$4,d1	; general form
	bhi.w	loc_02808A
	addi.l	#$7D00,(a4)
	tst.w	d1
	bne.w	loc_02808A
	addi.l	#$124F8,(a4)
loc_02808A:
	addq.w	#2,a1
	addq.w	#1,a2
	addq.w	#4,a4
	dbra	d4,loc_028010
	rts
loc_028096:
	movem.l	d0-d2/a0-a4,-(sp)
	bsr.w	Text_Print
inl_02809E:
	dc.w	loc_0280A4-inl_02809E
	dc.b	$BF,$0B,$02,$00
loc_0280A4:
	moveq	#$12,d0
	moveq	#$6,d1
	bsr.w	Text_PrintDigitsBig
	btst	#3,(ram_C35A).w
	bne.w	loc_028136
	btst	#5,(ram_C34C).w
	bne.w	loc_0280FC
	bsr.w	Text_PrintScoreboardAlt
inl_0280C4:
	dc.w	loc_0280DC-inl_0280C4
	dc.b	$F8,$04,$01,$0C,$03
	dc.b	"Injured player  ",0
loc_0280DC:
	jsr	(Text_Print).l
inl_0280E2:
	dc.w	loc_0280F8-inl_0280E2
	dc.b	$BF,$0C,$06
	dc.b	"Out for period"
	dc.b	$BF,$0C,$05
loc_0280F8:
	bra.w	loc_0281B0
loc_0280FC:
	bsr.w	Text_PrintScoreboardAlt
inl_028100:
	dc.w	loc_028118-inl_028100
	dc.b	$F8,$04,$01,$0C,$03
	dc.b	"Injured player  ",0
loc_028118:
	jsr	(Text_Print).l
inl_02811E:
	dc.w	loc_028132-inl_02811E
	dc.b	$BF,$0C,$06
	dc.b	"Out for game"
	dc.b	$BF,$0C,$05
loc_028132:
	bra.w	loc_0281B0
loc_028136:
	bsr.w	Text_PrintScoreboardAlt
inl_02813A:
	dc.w	loc_028152-inl_02813A
	dc.b	$F8,$04,$01,$0C,$03
	dc.b	"Injured player  ",0
loc_028152:
	jsr	(Text_Print).l
inl_028158:
	dc.w	loc_028166-inl_028158
	dc.b	$BF,$0C,$06
	dc.b	"Out for ",0
loc_028166:
	move.w	(ram_DDDC).w,d0
	move.w	#$1,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	cmpi.w	#$1,(ram_DDDC).w
	bgt.w	loc_028196
	jsr	(Text_Print).l
inl_02818A:
	dc.w	loc_028192-inl_02818A
	dc.b	" game",0
loc_028192:
	bra.w	loc_0281A4
loc_028196:
	jsr	(Text_Print).l
inl_02819C:
	dc.w	loc_0281A4-inl_02819C
	dc.b	" games"
loc_0281A4:
	jsr	(Text_Print).l
inl_0281AA:
	dc.w	loc_0281B0-inl_0281AA
	dc.b	$BF,$0C,$05,$00
loc_0281B0:
	bsr.w	sub_028540
	bsr.w	Text_Print_Worker
	btst	#0,(ram_B7C3).w
	beq.w	loc_0281D4
	bsr.w	Text_Print
inl_0281C6:
	dc.w	loc_0281D4-inl_0281C6
	dc.b	$BF,$14,$06
	dc.b	"the game",0
loc_0281D4:
	movem.l	(sp)+,d0-d2/a0-a4
	rts


; ----------------------------------------------------------------------
; called from $0214BA
sub_0281DA:
	bset	#7,(ram_C34A).w
	btst	#0,(ram_C34A).w
	beq.w	loc_0281F0
	jmp	(loc_1D0982).l
loc_0281F0:
	movem.l	d0-d2/a0-a4,-(sp)
	move.w	#$FFFF,d0
	jsr	(sub_021BF4).l
	bsr.w	Text_Print
inl_028202:
	dc.w	loc_028208-inl_028202
	dc.b	$BF,$06,$02,$00
loc_028208:
	moveq	#$15,d0
	moveq	#$8,d1
	bsr.w	Text_PrintDigitsBig
	lea	dat_0282A8(pc),a1
	jsr	(Text_PrintScoreboardAlt_Worker).l
	move.w	(ram_D2F2).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a2
	adda.w	d0,a2
	clr.w	d0
	move.b	$67(a2),d0
	movea.l	#ram_C732,a2
	tst.w	(ram_D2F0).w
	beq.w	loc_028242
	movea.l	#ram_CAD0,a2
loc_028242:
	bsr.w	sub_0285AE
	bsr.w	Text_Print_Worker
	bsr.w	Text_Print
inl_02824E:
	dc.w	loc_028254-inl_02824E
	dc.b	$BF,$07,$07,$00
loc_028254:
	movem.l	a1/a3,-(sp)
	move.w	(ram_D2FC).w,d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	lea	$2(a1),a1
	bsr.w	Text_Print_Worker
	movem.l	(sp)+,a1/a3
	bsr.w	Text_Print
inl_028276:
	dc.w	loc_02827E-inl_028276
	dc.b	$20,$62,$79,$BF,$07,$08
loc_02827E:
	move.w	(ram_D2FA).w,d0
	movea.l	#ram_CAD0,a2
	tst.w	(ram_D2F0).w
	beq.w	loc_028296
	movea.l	#ram_C732,a2
loc_028296:
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	movem.l	(sp)+,d0-d2/a0-a4
	rts
dat_0282A8:
	dc.w	$0020,$F804,$0107,$0320,$2020,$5045,$4E41,$4C54
	dc.w	$5920,$5348,$4F54,$2020,$2020,$F804,$0107,$0500


; ----------------------------------------------------------------------
; called from $021AC6
sub_0282C8:
	movem.l	d0-d2/a0-a4,-(sp)
	btst	#2,(ram_C342).w
	beq.w	loc_0282DC
	bset	#2,(ram_C33E).w
loc_0282DC:
	movea.w	#$C732,a2
	jsr	(sub_01283A).l
	adda.w	#$39E,a2
	jsr	(sub_01283A).l
	jsr	(sub_1E2F06).l
	movea.w	#$C4D2,a4
	adda.w	(ram_C4D6).w,a4
	bsr.w	Text_Print
inl_028302:
	dc.w	loc_028308-inl_028302
	dc.b	$BF,$0B,$02,$00
loc_028308:
	moveq	#$13,d0
	move.w	#$5,d1
	tst.b	$4(a4)
	bmi.w	loc_028322
	addq.w	#2,d1
	tst.b	$5(a4)
	bmi.w	loc_028322
	addq.w	#1,d1
loc_028322:
	bsr.w	Text_PrintDigitsBig
	jsr	(sub_1D06DC).l
	movea.w	#$C732,a2
	move.w	(ram_D338).w,(ram_BF7E).w
	btst	#7,$2(a4)
	beq.w	loc_02834A
	adda.w	#$39E,a2
	move.w	(ram_D33A).w,(ram_BF7E).w
loc_02834A:
	lea	dat_02844A(pc),a1
	bclr	#0,(ram_C350).w
	beq.w	loc_02835C
	lea	dat_028486(pc),a1
loc_02835C:
	clr.w	d0
	move.b	$3(a4),d0
	addi.w	#$C0,d0
	cmpi.b	#$3,$0(a2,d0.w)
	bne.w	loc_0283A2
	movem.w	d1,-(sp)
	clr.w	d1
	move.b	$3(a4),d1
	cmp.w	(ram_BF7E).w,d1
	movem.w	(sp)+,d1
	blt.w	loc_0283A2
	adda.w	(a1),a1
	move.w	d0,-(sp)
	move.w	$28(a2),d0
	cmp.w	(ram_C3AC).w,d0
	bne.w	loc_0283A0
	move.w	#$0,d0
	jsr	(sub_1D1470).l
loc_0283A0:
	move.w	(sp)+,d0
loc_0283A2:
	jsr	(Text_PrintScoreboardAlt_Worker).l
	clr.w	d0
	move.b	$3(a4),d0
	move.w	d0,-(sp)
	move.w	#$C,(TextX).w
	bsr.w	sub_02861C
	bsr.w	Text_Print_Worker
	move.w	(sp)+,d0
	movem.w	d1,-(sp)
	clr.w	d1
	move.b	$3(a4),d1
	cmp.w	(ram_BF7E).w,d1
	movem.w	(sp)+,d1
	blt.w	loc_0283DC
	jsr	(sub_1D19BC).l
loc_0283DC:
	clr.w	d0
	move.b	$4(a4),d0
	bmi.w	loc_02843E
	bclr	#5,(ram_C344).w
	bne.w	loc_02843E
	bsr.w	Text_Print
inl_0283F4:
	dc.w	loc_028406-inl_0283F4
	dc.b	$BF,$0E,$06
	dc.b	"Assist by:"
	dc.b	$BF,$0C,$07
loc_028406:
	move.w	d0,-(sp)
	bsr.w	sub_02861C
	bsr.w	Text_Print_Worker
	move.w	(sp)+,d0
	jsr	(sub_1D19A6).l
	clr.w	d0
	move.b	$5(a4),d0
	bmi.w	loc_02843E
	bsr.w	Text_Print
inl_028426:
	dc.w	loc_02842C-inl_028426
	dc.b	$BF,$0C,$08,$00
loc_02842C:
	move.w	d0,-(sp)
	bsr.w	sub_02861C
	bsr.w	Text_Print_Worker
	move.w	(sp)+,d0
	jsr	(sub_1D19A6).l
loc_02843E:
	bclr	#5,(ram_C344).w
	movem.l	(sp)+,d0-d2/a0-a4
	rts
dat_02844A:
	dc.w	$001E,$F804,$010C,$0320,$2020,$2020,$2047,$4F41
	dc.w	$4C21,$2020,$2020,$2020,$F804,$010C,$0500,$001E
	dc.w	$F804,$010C,$0320,$2020,$4841,$5420,$5452,$4943
	dc.w	$4B21,$2020,$2020,$F804,$010C,$0500
dat_028486:
	dc.w	$001E,$F804,$010C,$0320,$2020,$2050,$5020,$474F
	dc.w	$414C,$2120,$2020,$2020,$F804,$010C,$0500,$001E
	dc.w	$F804,$010C,$0320,$2020,$4841,$5420,$5452,$4943
	dc.w	$4B21,$2020,$2020,$F804,$010C,$0500


; ----------------------------------------------------------------------
; called from $00F194, $012630
sub_0284C2:
	bsr.w	Text_Print
inl_0284C6:
	dc.w	loc_0284CC-inl_0284C6
	dc.b	$FF,$0B,$02,$00
loc_0284CC:
	moveq	#$14,d0
	moveq	#$C,d1
	move.l	#$7FF,d2
	bra.w	Text_FillRect


; ----------------------------------------------------------------------
; called from $021A98
sub_0284DA:
	movem.l	d0/a2,-(sp)
	movea.w	#$C732,a2
	move.w	(ram_C4D4).w,d0
	bpl.w	loc_0284F2
	andi.w	#$FF,d0
	adda.w	#$39E,a2
loc_0284F2:
	bsr.w	sub_0284FC
	movem.l	(sp)+,d0/a2
	rts


; ----------------------------------------------------------------------
; called from $00F242, $019C16, $019C80, $027F2A, $0284F2
sub_0284FC:
	movem.l	d0-d3/d7/a0/a2/a3,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_013D6E).l
	jsr	(sub_013C56).l
	move.l	a0,-(sp)
	movea.w	#$BFF4,a3
	move.w	#$4,(a3)
	lea	$2(a3),a1
	adda.w	(a0),a0
	move.w	(ram_DDCE).w,d0
	bsr.w	sub_02872E
	bsr.w	Text_AppendInline
inl_02852C:
	dc.w	loc_028530-inl_02852C
	dc.b	$20,$00
loc_028530:
	movea.l	(sp)+,a1
	bsr.w	Text_AppendInline_Worker
	movea.w	#$BFF4,a1
	movem.l	(sp)+,d0-d3/d7/a0/a2/a3
	rts


; ----------------------------------------------------------------------
; called from $021D34, $0281B0
sub_028540:
	movem.l	d0/a2,-(sp)
	movea.w	#$C732,a2
	move.w	(ram_C4D4).w,d0
	bpl.w	loc_028558
	andi.w	#$FF,d0
	adda.w	#$39E,a2
loc_028558:
	bsr.w	sub_0285AE
	movem.l	(sp)+,d0/a2
	rts


; ----------------------------------------------------------------------
; called from $1DE39C
sub_028562:
	movem.l	d0-d3/d7/a0/a2,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_013D6E).l
	jsr	(sub_013C56).l
	move.l	a0,-(sp)
	movea.w	#$BFF6,a1
	adda.w	(a0),a0
	move.w	(ram_DDCE).w,d0
	bsr.w	sub_02872E
	move.b	#$20,(a1)+
	movea.l	(sp)+,a0
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
	move.b	(a0)+,(a1)+
	move.b	#$2E,(a1)+
loc_028598:
	cmpi.b	#$20,(a0)+
	bne.s	loc_028598
loc_02859E:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_02859E
	bsr.w	sub_028714
	movem.l	(sp)+,d0-d3/d7/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $028242, $028296, $028558, $1D09C8, $1D0A1C, $1D0FE4, $1DDEB0, $1E5B48 (+9 more)
sub_0285AE:
	movem.l	d0-d3/d7/a0/a2,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_013D6E).l
	jsr	(sub_013C56).l
	move.l	a0,-(sp)
	movea.w	#$BFF6,a1
	adda.w	(a0),a0
	move.w	(ram_DDCE).w,d0
	bsr.w	sub_02872E
	move.b	#$20,(a1)+
	movea.l	(sp)+,a0
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
	move.b	(a0)+,(a1)+
	move.w	#$2E20,(a1)+
loc_0285E4:
	cmpi.b	#$20,(a0)+
	bne.s	loc_0285E4
loc_0285EA:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_0285EA
	bsr.w	sub_028714
	movem.l	(sp)+,d0-d3/d7/a0/a2
	rts


; ----------------------------------------------------------------------
sub_0285FA:
	movem.l	d0/a2,-(sp)
	movea.w	#$C732,a2
	move.w	(ram_C4D4).w,d0
	bpl.w	loc_028612
	andi.w	#$FF,d0
	adda.w	#$39E,a2
loc_028612:
	bsr.w	sub_02861C
	movem.l	(sp)+,d0/a2
	rts


; ----------------------------------------------------------------------
; called from $0283B6, $028408, $02842E, $028612, $1DC60C, $1DF15A, $1E4F8C
sub_02861C:
	movem.l	d0-d3/d7/a0/a2,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_013D6E).l
	jsr	(sub_013C56).l
	move.l	a0,-(sp)
	movea.w	#$BFF6,a1
	adda.w	(a0),a0
	move.w	(ram_DDCE).w,d0
	bsr.w	sub_02872E
	move.b	#$20,(a1)+
	movea.l	(sp)+,a0
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
loc_02864C:
	cmpi.b	#$20,(a0)+
	bne.s	loc_02864C
loc_028652:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_028652
	bsr.w	sub_028714
	movem.l	(sp)+,d0-d3/d7/a0/a2
	rts


; ----------------------------------------------------------------------
sub_028662:
	movem.l	d0-d3/a0/a2,-(sp)
	jsr	(sub_013C56).l
	movea.w	#$BFF6,a1
	bra.w	loc_028686


; ----------------------------------------------------------------------
; called from $1E50AA
sub_028674:
	movem.l	d0-d3/a0/a2,-(sp)
	jsr	(sub_013C56).l
	movea.w	#$BFF6,a1
	move.b	#$20,(a1)+
loc_028686:
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
loc_02868C:
	cmpi.b	#$20,(a0)+
	bne.s	loc_02868C
loc_028692:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	beq.w	loc_0286A6
	tst.b	(a0)
	bne.s	loc_028692
	bra.w	loc_0286A6
loc_0286A2:
	move.b	#$20,(a1)+
loc_0286A6:
	cmpa.w	#$C002,a1
	blt.s	loc_0286A2
	bsr.w	sub_028714
	movem.l	(sp)+,d0-d3/a0/a2
	rts


; ----------------------------------------------------------------------
sub_0286B6:
	movem.l	d0/a2,-(sp)
	movea.w	#$C732,a2
	move.w	(ram_C4D4).w,d0
	bpl.w	loc_0286CE
	andi.w	#$FF,d0
	adda.w	#$39E,a2
loc_0286CE:
	bsr.w	sub_0286D8
	movem.l	(sp)+,d0/a2
	rts


; ----------------------------------------------------------------------
; called from $0286CE, $1D2958, $1D2974, $1D2994, $1D29B0
sub_0286D8:
	movem.l	d0-d3/a0/a2,-(sp)
	jsr	(sub_013C56).l
	move.l	a0,-(sp)
	movea.w	#$BFF6,a1
	adda.w	(a0),a0
	move.b	(a0),d0
	movea.l	(sp)+,a0
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
	move.b	(a0)+,(a1)+
	move.b	#$2E,(a1)+
	move.b	#$20,(a1)+
loc_0286FE:
	cmpi.b	#$20,(a0)+
	bne.s	loc_0286FE
loc_028704:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_028704
	bsr.w	sub_028714
	movem.l	(sp)+,d0-d3/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $013C42, $0285A4, $0285F0, $028658, $0286AC, $02870A, $1DCE5E, $1E38C2
sub_028714:
	move.w	a1,d0
	subi.w	#$BFF4,d0
	btst	#0,d0
	beq.w	loc_028726
	clr.b	(a1)+
	addq.w	#1,d0
loc_028726:
	movea.w	#$BFF4,a1
	move.w	d0,(a1)
	rts


; ----------------------------------------------------------------------
; called from $013C24, $02235E, $028524, $028582, $0285CE, $02863C, $1DD652
sub_02872E:
	move.w	d0,-(sp)
	lsr.b	#4,d0
	andi.b	#$F,d0
	bne.w	loc_02873E
	move.b	#$F0,d0
loc_02873E:
	addi.b	#$30,d0
	move.b	d0,(a1)+
	move.w	(sp)+,d0
	andi.w	#$F,d0
	addi.b	#$30,d0
	move.b	d0,(a1)+
	rts


; ----------------------------------------------------------------------
; called from $1D517A
sub_028752:
	movem.l	d0-d3,-(sp)
	movea.w	#$C05A,a1
	moveq	#$1,d2
	sub.w	d2,d1
	bra.w	loc_028766
loc_028762:
	mulu.w	#$A,d2
loc_028766:
	dbra	d1,loc_028762
	moveq	#$30,d3
loc_02876C:
	ext.l	d0
	divu.w	d2,d0
	bne.w	loc_028782
	cmp.w	#$1,d2	; general form
	beq.w	loc_028782
	move.w	d3,d0
	bra.w	loc_028786
loc_028782:
	moveq	#$30,d3
	add.w	d3,d0
loc_028786:
	move.b	d0,(a1)+
	swap	d0
	divu.w	#$A,d2
	bne.s	loc_02876C
	move.l	a1,d0
	subi.w	#$C058,d0
	btst	#0,d0
	beq.w	loc_0287A2
	clr.b	(a1)+
	addq.w	#1,d0
loc_0287A2:
	movea.w	#$C058,a1
	move.w	d0,(a1)
	movem.l	(sp)+,d0-d3
	rts


; ----------------------------------------------------------------------
; bus/address error: prints "Address Error" and the fault address
; called from $000008, $00000C
Exception_AddressError:
	move.w	#$2700,sr
	jsr	(Text_PrintFont).l
inl_0287B8:
	dc.w	loc_0287CA-inl_0287B8
	dc.b	$BD,$00,$00
	dc.b	"Address Error"
loc_0287CA:
	move.l	$A(sp),d0
	move.l	$2(sp),d1
	bra.w	loc_028824


; ----------------------------------------------------------------------
; called from $000010
Exception_IllegalInstr:
	move.w	#$2700,sr
	bsr.w	Text_PrintFont
inl_0287DE:
	dc.w	loc_0287F6-inl_0287DE
	dc.b	$BD,$00,$00
	dc.b	"Illegal Instruction"
loc_0287F6:
	move.l	$2(sp),d0
	move.l	d0,d1
	bra.w	loc_028824


; ----------------------------------------------------------------------
; called from $000014
Exception_DivideByZero:
	move.w	#$2700,sr
	bsr.w	Text_PrintFont
inl_028808:
	dc.w	loc_02881E-inl_028808
	dc.b	$BD,$00,$00
	dc.b	"Division by zero",0
loc_02881E:
	move.l	$2(sp),d0
	move.l	d0,d1
loc_028824:
	movea.w	#$BFF4,a0
	move.w	#$18,(a0)+
	move.b	#$BD,(a0)+
	move.b	#$0,(a0)+
	move.b	#$2,(a0)+
	move.l	d1,-(sp)
	bsr.w	sub_028892
	move.b	#$BD,(a0)+
	move.b	#$0,(a0)+
	move.b	#$4,(a0)+
	move.l	(sp)+,d0
	bsr.w	sub_028892
	movea.w	#$BFF4,a1
	jsr	(Text_PrintFont_Worker).l
	movea.l	#VDP_DATA,a0
	move.w	#$9100,$4(a0)
	move.w	#$9206,$4(a0)
	move.w	#$8F02,$4(a0)
	move.l	#$C0200000,$4(a0)
	movea.l	#Art_Rink,a1
	adda.l	(a1),a1
	adda.w	#$20,a1
	moveq	#$7,d0
loc_028888:
	move.l	(a1)+,(a0)
	dbra	d0,loc_028888
loc_02888E:
	bra.w	loc_02888E


; ----------------------------------------------------------------------
; called from $02883A, $02884C
sub_028892:
	moveq	#$7,d2
loc_028894:
	rol.l	#4,d0
	move.w	d0,d1
	andi.w	#$F,d1
	addi.w	#$30,d1
	cmp.w	#$39,d1	; general form
	ble.w	loc_0288AA
	addq.w	#7,d1
loc_0288AA:
	move.b	d1,(a0)+
	dbra	d2,loc_028894
	rts
