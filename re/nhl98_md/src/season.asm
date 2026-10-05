; ============================================================================
; Season mode: menus, standings, player stats, transactions, simulation (partly compiled C)
; ROM range $00B8DE-$01B8B7
; ============================================================================


; ----------------------------------------------------------------------
; called from $014A30, $014A72, $014AAC, $014ADC, $014E60, $014E70, $014EA0, $014ECA (+5 more)
sub_00B8DE:
	movem.l	d0-d6/a0,-(sp)
	movea.l	#$200000,a0
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a0
	moveq	#-$1,d5
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d5
	lsr.l	d4,d5
	not.l	d5
	lsl.l	d6,d0
	lsr.l	d4,d0
	move.b	$1(a0),d6
	lsl.w	#8,d6
	move.b	$3(a0),d6
	swap	d6
	move.b	$5(a0),d6
	lsl.w	#8,d6
	move.b	$7(a0),d6
	and.l	d5,d6
	or.l	d0,d6
	move.b	d6,$7(a0)
	lsr.w	#8,d6
	move.b	d6,$5(a0)
	swap	d6
	move.b	d6,$3(a0)
	lsr.w	#8,d6
	move.b	d6,$1(a0)
	btst	#6,(SysFlags).l
	bne.w	loc_00B94C
	jsr	(SRAM_UpdateChecksum).l
loc_00B94C:
	movem.l	(sp)+,d0-d6/a0
	rts


; ----------------------------------------------------------------------
; called from $0149EC, $014A4E, $014A9E, $014ACE, $014F28, $014F46, $014FA0, $015194 (+8 more)
sub_00B952:
	movem.l	d1-d6/a0,-(sp)
	movea.l	#$200000,a0
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a0
	moveq	#-$1,d5
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d5
	lsr.l	d4,d5
	move.b	$1(a0),d0
	lsl.w	#8,d0
	move.b	$3(a0),d0
	swap	d0
	move.b	$5(a0),d0
	lsl.w	#8,d0
	move.b	$7(a0),d0
	and.l	d5,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	movem.l	(sp)+,d1-d6/a0
	rts


; ----------------------------------------------------------------------
; called from $1D4DDC, $1D4E0E
sub_00B99A:
	movem.l	d0/d2-d4/d6/d7/a1/a2/a4-a6,-(sp)
	move.w	d3,d7
	ext.l	d5
	bra.w	loc_00BA00
loc_00B9A6:
	movea.l	#$200000,a4
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a4
	moveq	#-$1,d3
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d3
	lsr.l	d4,d3
	move.b	$1(a4),d0
	lsl.w	#8,d0
	move.b	$3(a4),d0
	swap	d0
	move.b	$5(a4),d0
	lsl.w	#8,d0
	move.b	$7(a4),d0
	and.l	d3,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	cmp.w	(ram_DDE4).l,d7
	bge.w	loc_00B9F0
	clr.w	d0
loc_00B9F0:
	tst.w	d0
	beq.w	loc_00B9FC
	move.w	d5,(a3)+
	addq.w	#1,(a2)
	move.w	d0,(a0)+
loc_00B9FC:
	addq.l	#1,d5
	add.l	d2,d1
loc_00BA00:
	dbra	d7,loc_00B9A6
	movem.l	(sp)+,d0/d2-d4/d6/d7/a1/a2/a4-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4E40
sub_00BA0A:
	movem.l	d0/d2-d4/d6/d7/a1/a2/a4-a6,-(sp)
	move.w	d3,d7
	ext.l	d5
	bra.w	loc_00BAE2
loc_00BA16:
	movea.l	#$200000,a4
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a4
	moveq	#-$1,d3
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d3
	lsr.l	d4,d3
	move.b	$1(a4),d0
	lsl.w	#8,d0
	move.b	$3(a4),d0
	swap	d0
	move.b	$5(a4),d0
	lsl.w	#8,d0
	move.b	$7(a4),d0
	and.l	d3,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	cmp.w	(ram_DDE4).l,d7
	bge.w	loc_00BA60
	clr.w	d0
loc_00BA60:
	movem.l	d0/d1,-(sp)
	btst	#2,(ram_DD9E).l
	beq.w	loc_00BA7A
	addi.l	#$FA0,d1
	bra.w	loc_00BA80
loc_00BA7A:
	addi.l	#$1D40,d1
loc_00BA80:
	movea.l	#$200000,a4
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a4
	moveq	#-$1,d3
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d3
	lsr.l	d4,d3
	move.b	$1(a4),d0
	lsl.w	#8,d0
	move.b	$3(a4),d0
	swap	d0
	move.b	$5(a4),d0
	lsl.w	#8,d0
	move.b	$7(a4),d0
	and.l	d3,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	move.l	d0,d6
	cmp.w	(ram_DDE4).l,d7
	bge.w	loc_00BACC
	clr.w	d0
loc_00BACC:
	movem.l	(sp)+,d0/d1
	add.w	d6,d0
	tst.w	d0
	beq.w	loc_00BADE
	move.w	d5,(a3)+
	addq.w	#1,(a2)
	move.w	d0,(a0)+
loc_00BADE:
	addq.l	#1,d5
	add.l	d2,d1
loc_00BAE2:
	dbra	d7,loc_00BA16
	movem.l	(sp)+,d0/d2-d4/d6/d7/a1/a2/a4-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4DAC
sub_00BAEC:
	movem.l	d0/d2/d3/d6/d7/a1/a2/a4-a6,-(sp)
	move.w	d3,d7
	ext.l	d5
	move.l	d4,-(sp)
	move.l	d6,-(sp)
	bra.w	loc_00BBC0
loc_00BAFC:
	moveq	#$E,d2
	movea.l	#$200000,a4
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a4
	moveq	#-$1,d3
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d3
	lsr.l	d4,d3
	move.b	$1(a4),d0
	lsl.w	#8,d0
	move.b	$3(a4),d0
	swap	d0
	move.b	$5(a4),d0
	lsl.w	#8,d0
	move.b	$7(a4),d0
	and.l	d3,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	move.l	(sp),d2
	move.l	$4(sp),d3
	movem.l	d0/d1,-(sp)
	move.l	d3,d1
	movea.l	#$200000,a4
	move.l	d1,d3
	lsr.l	#3,d3
	add.l	d3,d3
	move.l	d1,d4
	andi.l	#$7,d4
	adda.l	d3,a4
	moveq	#-$1,d3
	move.w	#$20,d6
	sub.w	d2,d6
	lsl.l	d6,d3
	lsr.l	d4,d3
	move.b	$1(a4),d0
	lsl.w	#8,d0
	move.b	$3(a4),d0
	swap	d0
	move.b	$5(a4),d0
	lsl.w	#8,d0
	move.b	$7(a4),d0
	and.l	d3,d0
	lsl.l	d4,d0
	lsr.l	d6,d0
	move.l	d0,d6
	movem.l	(sp)+,d0/d1
	tst.w	d6
	beq.w	loc_00BBB2
	mulu.w	#$A,d6
	divu.w	#$3C,d6
	bvs.w	loc_00BBB2
	cmp.w	#$A,d6	; general form
	blt.w	loc_00BBB2
	mulu.w	#$3E8,d0
	divu.w	d6,d0
	move.w	d5,(a3)+
	addq.w	#1,(a2)
	move.w	d0,(a0)+
loc_00BBB2:
	addq.l	#1,d5
	addi.l	#$E,d1
	move.l	(sp),d3
	add.l	d3,$4(sp)
loc_00BBC0:
	dbra	d7,loc_00BAFC
	addq.w	#4,sp
	move.l	(sp)+,d4
	movem.l	(sp)+,d0/d2/d3/d6/d7/a1/a2/a4-a6
	rts


; ----------------------------------------------------------------------
; called from $00BD52, $00BD82
sub_00BBCE:
	movem.l	d0-d3/a0,-(sp)
	movea.l	#dat_00BCF2,a0
	asl.w	#2,d0
	move.l	$0(a0,d0.w),d0
	moveq	#$41,d3
	move.l	#$D87,d1
	bsr.w	sub_00BBF4
	bsr.w	sub_00BC20
	movem.l	(sp)+,d0-d3/a0
	rts


; ----------------------------------------------------------------------
; called from $00BBE6, $00BDFA, $00BE18, $00BE36
sub_00BBF4:
	movem.l	d0-d3/a0/a1,-(sp)
	movea.l	#$200000,a1
	add.l	d0,d0
	adda.l	d0,a1
	movea.l	#$200000,a0
	add.l	d3,d3
	adda.l	d3,a0
	subq.l	#1,d1
loc_00BC0E:
	move.w	(a0),d0
	move.w	(a1),d3
	move.w	d0,(a1)+
	move.w	d3,(a0)+
	dbra	d1,loc_00BC0E
	movem.l	(sp)+,d0-d3/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $00BBEA, $00BD32, $015344
sub_00BC20:
	movem.l	d0/d1/a0-a2,-(sp)
	movea.l	#ram_DDAA,a2
	movea.l	#$200000,a1
	move.w	#$3,d0
	movea.l	#dat_00BC58,a0
loc_00BC3A:
	move.l	(a0)+,d1
	addi.l	#$C,d1
	add.l	d1,d1
	move.w	$0(a1,d1.w),d1
	andi.w	#$FF,d1
	move.b	d1,(a2)+
	dbra	d0,loc_00BC3A
	movem.l	(sp)+,d0/d1/a0-a2
	rts
dat_00BC58:
	dc.w	$0000,$0041,$0000,$2135,$0000,$2EBC,$0000,$3C43


; ----------------------------------------------------------------------
; called from $015358
sub_00BC68:
	movem.l	d1/a0,-(sp)
	bsr.w	sub_00BCB0
	tst.l	d0
	bmi.w	loc_00BCA8
	movea.l	#$200000,a0
	addi.l	#$2,d0
	add.l	d0,d0
	move.w	$0(a0,d0.l),d1
	btst	#0,d1
	beq.w	loc_00BCA0
	btst	#1,d1
	beq.w	loc_00BCA0
	move.w	#$1,d0
	bra.w	loc_00BCAA
loc_00BCA0:
	move.w	#$2,d0
	bra.w	loc_00BCAA
loc_00BCA8:
	clr.w	d0
loc_00BCAA:
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $00BC6C, $00BD38, $015374, $0153AE, $0153E8, $015422, $015908
sub_00BCB0:
	movem.l	d1/a0,-(sp)
	movea.l	#ram_DDAA,a0
	move.w	#$1,d1
loc_00BCBE:
	cmp.b	(a0)+,d0
	beq.w	loc_00BCCC
	addq.w	#1,d1
	cmp.w	#$5,d1	; general form
	blt.s	loc_00BCBE
loc_00BCCC:
	cmp.w	#$5,d1	; general form
	bge.w	loc_00BCEA
	andi.l	#$FF,d1
	asl.w	#2,d1
	movea.l	#dat_00BCF2,a0
	move.l	$0(a0,d1.w),d0
	bra.w	loc_00BCEC
loc_00BCEA:
	moveq	#-$1,d0
loc_00BCEC:
	movem.l	(sp)+,d1/a0
	rts
dat_00BCF2:
	dc.w	$0000,$0000,$0000,$0041,$0000,$2135,$0000,$2EBC
	dc.w	$0000,$3C43


; ----------------------------------------------------------------------
; called from $00BD42
sub_00BD06:
	move.l	a0,-(sp)
	move.w	#$0,d0
	movea.l	#ram_DDAA,a0
loc_00BD12:
	tst.b	(a0)+
	beq.w	loc_00BD26
	addq.w	#1,d0
	cmp.w	#$4,d0	; general form
	blt.s	loc_00BD12
	clr.w	d0
	bra.w	loc_00BD28
loc_00BD26:
	addq.w	#1,d0
loc_00BD28:
	movea.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $0156E0
sub_00BD2C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	d0,d6
	bsr.w	sub_00BC20
	move.w	d6,d0
	bsr.w	sub_00BCB0
	tst.l	d0
	bpl.w	loc_00BD60
	bsr.s	sub_00BD06
	tst.w	d0
	cmp.w	#$1,d0	; general form
	beq.w	loc_00BD8C
	move.w	#$1,d1
	bsr.w	sub_00BBCE
	jsr	(SRAM_UpdateChecksum).l
	bra.w	loc_00BD8C
loc_00BD60:
	movea.l	#dat_00BCF2,a0
	move.w	#$4,d1
loc_00BD6A:
	cmp.l	$0(a0,d1.w),d0
	beq.w	loc_00BD76
	addq.w	#4,d1
	bra.s	loc_00BD6A
loc_00BD76:
	asr.w	#2,d1
	move.w	d1,d0
	cmp.w	#$1,d0	; general form
	beq.w	loc_00BD8C
	bsr.w	sub_00BBCE
	jsr	(SRAM_UpdateChecksum).l
loc_00BD8C:
	move.b	d6,(ram_DDAA).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DB2C2, $1DB674
sub_00BD98:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$0,d7
	movea.l	#$200000,a0
	btst	#7,(SysFlags).l
	beq.w	loc_00BDC0
	clr.w	d7
	move.b	(ram_DDAA).l,d7
	beq.w	loc_00BDC0
	addq.w	#1,d7
loc_00BDC0:
	move.l	#loc_00F8D4,d0
	move.w	#$5,d1
	clr.w	d2
loc_00BDCC:
	move.w	$0(a0,d0.l),d3
	andi.w	#$FF,d3
	cmp.w	d7,d3
	beq.w	loc_00BDE6
	addq.w	#1,d2
	addq.l	#2,d0
	dbra	d1,loc_00BDCC
	bra.w	loc_00BE40
loc_00BDE6:
	tst.w	d2
	beq.w	loc_00BE40
	ext.l	d2
	moveq	#$1,d1
	move.l	#dat_007C6A,d0
	move.l	d0,d3
	add.l	d2,d3
	bsr.w	sub_00BBF4
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	d2,d3
	asl.l	#2,d3
	movea.l	#ptrs_00BE46,a0
	move.l	$0(a0,d3.l),d3
	bsr.w	sub_00BBF4
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	d2,d3
	asl.l	#2,d3
	movea.l	#dat_00BE5E,a0
	move.l	$0(a0,d3.l),d3
	bsr.w	sub_00BBF4
	jsr	(SRAM_UpdateChecksum).l
loc_00BE40:
	movem.l	(sp)+,d0-d7/a0-a6
	rts

ptrs_00BE46:
	dc.l	dat_0017A2
	dc.l	dat_004D1C
	dc.l	dat_005692
	dc.l	dat_006008
	dc.l	dat_00697E
	dc.l	dat_0072F4

dat_00BE5E:
	dc.l	dat_000DCA
	dc.l	dat_0049CA
	dc.l	dat_004A74
	dc.l	dat_004B1E
	dc.l	dat_004BC8
	dc.l	dat_004C72
loc_00BE76:
	btst	#6,(ram_C346).w
	beq.w	loc_00BE82
	rts
loc_00BE82:
	move.w	$36(a3),d4
	cmpi.b	#$17,$38(a3,d4.w)
	bne.w	loc_00C926
	movea.w	#$BFE8,a0
	btst	#7,$62(a3)
	beq.w	loc_00BEA2
	movea.w	#$BFEA,a0
loc_00BEA2:
	move.w	d0,(a0)
	btst	#1,$63(a3)
	bne.w	loc_00C926
	btst	#4,d1
	beq.w	loc_00BEC6
	move.w	#$21E4,d1
	bset	#1,$63(a3)
	jmp	(sub_01F3B2).l
loc_00BEC6:
	move.w	#$220E,d1
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $00F656
sub_00BED0:
	btst	#5,$62(a3)
	bne.w	loc_00BEE4
	btst	#0,(ram_C33E).w
	beq.w	loc_00BEE6
loc_00BEE4:
	rts
loc_00BEE6:
	jmp	(sub_01F156).l


; ----------------------------------------------------------------------
; called from $00F65A
sub_00BEEC:
	btst	#5,$62(a3)
	bne.w	loc_00BF80
	btst	#0,(ram_C33E).w
	beq.w	loc_00BF76
	bclr	#1,$62(a3)
	beq.w	loc_00BF0E
	clr.w	$40(a3)
loc_00BF0E:
	movea.l	#ram_BDC0,a0
	btst	#6,$62(a3)
	beq.w	loc_00BF20
	addq.w	#4,a0
loc_00BF20:
	move.w	$5A(a3),d0
	lsr.w	#2,d0
	addq.w	#1,d0
	btst	#0,$77(a3)
	bne.w	loc_00BF34
	addq.w	#3,d0
loc_00BF34:
	move.w	d0,(a0)
	btst	#3,$62(a3)
	bne.w	loc_00BF80
	bset	#1,$63(a3)
	bne.w	loc_00BF80
	move.w	#$21E4,d1
	cmpi.w	#$12,(ram_B7A0).w
	bls.w	loc_00BF6A
	moveq	#$8,d0
	jsr	(Random).l
	tst.w	d0
	beq.w	loc_00BF6A
	move.w	#$220E,d1
loc_00BF6A:
	bset	#1,$63(a3)
	jmp	(sub_01F3B2).l
loc_00BF76:
	move.b	#$14,$5E(a3)
	bra.w	loc_00BEE6
loc_00BF80:
	rts


; ----------------------------------------------------------------------
; called from $00F66A
sub_00BF82:
	st	(ram_D254).w
	st	(ram_D256).w
	st	(ram_D258).w
	bclr	#4,(ram_C34E).w
	btst	#0,(ram_C34A).w
	beq.w	loc_00BFB0
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	move.w	#$1E,d0
	jmp	(sub_01F172).l
loc_00BFB0:
	bclr	#1,$62(a3)
	beq.w	loc_00C26A
	move.l	(ram_C39C).w,(ram_C394).w
	move.l	(ram_C3A0).w,(ram_C398).w
	bclr	#4,(ram_C35C).w
	bclr	#5,(ram_C35C).w
	bclr	#0,(ram_C34E).w
	beq.w	loc_00BFE4
	clr.w	(ram_BFE4).w
	clr.w	(ram_BFE6).w
loc_00BFE4:
	bclr	#7,(ram_C34C).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	bclr	#6,(ram_C34C).w
	bclr	#2,(ram_C34C).w
	bset	#2,(ram_C358).w
	jsr	(sub_1D1B92).l
	tst.w	(ram_D49C).w
	bmi.w	loc_00C01E
	move.w	(ram_D49C).w,d0
	bra.w	loc_00C02A
loc_00C01E:
	jsr	(sub_1D1B44).l
	tst.w	d0
	bmi.w	loc_00C030
loc_00C02A:
	jsr	(sub_1D149E).l
loc_00C030:
	bclr	#1,(TextFlags).w
	bclr	#1,(ram_C34A).w
	tst.w	(ram_C4CA).w
	beq.w	loc_00C316
	btst	#6,(ram_C33A).w
	bne.w	loc_00C316
	cmpi.w	#$3,(ram_C4C8).w
	bne.w	loc_00C06A
	move.w	(ram_C73E).w,d0
	cmp.w	(ram_CADC).w,d0
	beq.w	loc_00C06A
	jmp	(loc_019586).l
loc_00C06A:
	btst	#3,(ram_C33A).w
	bne.w	loc_00C31C
	move.w	(ram_C4CE).w,d0
	asr.w	#1,d0
	cmp.w	(ram_C4CA).w,d0
	bls.w	loc_00C0C2
	cmpi.w	#$3C,(ram_C4CA).w
	blt.w	loc_00C0C2
	bclr	#7,(ram_C340).w
	beq.w	loc_00C0C2
	btst	#0,(ram_C33A).w
	beq.w	loc_00C0C2
	btst	#6,(ram_C34E).w
	bne.w	loc_00C0C2
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$3,(ram_D4AC).w
	jsr	(sub_092274).l
	bset	#4,(ram_C34E).w
loc_00C0C2:
	jsr	(sub_01E512).l
	st	$40(a3)
	st	$42(a3)
	tst.w	(ram_D280).w
	bne.w	loc_00C26A
	bclr	#1,(ram_C762).w
	bclr	#1,(ram_CB00).w
	movea.w	#$B060,a0
	moveq	#$B,d0
loc_00C0EA:
	bclr	#3,$63(a0)
	adda.w	#$80,a0
	dbra	d0,loc_00C0EA
	move.w	(ram_C394).w,d0
	or.w	(ram_C396).w,d0
	beq.w	loc_00C13C
	btst	#7,(ram_C33C).w
	beq.w	loc_00C13C
	jsr	(sub_01FFA2).l
	bset	#6,(ram_C33C).w
	jsr	(sub_022252).l
	move.w	#$18,(FadeCounter).w
	tst.w	(ram_D280).w
	bne.w	loc_00C13C
	btst	#4,(ram_C34C).w
	beq.w	loc_00C13C
	clr.w	(FadeCounter).w
loc_00C13C:
	move.w	(ram_C388).w,d0
	bmi.w	loc_00C14C
	cmp.w	#$6,d0	; general form
	blt.w	loc_00C178
loc_00C14C:
	move.w	(ram_C38A).w,d0
	bmi.w	loc_00C15C
	cmp.w	#$6,d0	; general form
	blt.w	loc_00C178
loc_00C15C:
	move.w	(ram_C38C).w,d0
	bmi.w	loc_00C16C
	cmp.w	#$6,d0	; general form
	blt.w	loc_00C178
loc_00C16C:
	move.w	(ram_C38E).w,d0
	cmp.w	#$6,d0	; general form
	bge.w	loc_00C182
loc_00C178:
	tst.w	d0
	bmi.w	loc_00C182
	bsr.w	sub_00C21C
loc_00C182:
	move.w	(ram_C388).w,d0
	cmp.w	#$6,d0	; general form
	bge.w	loc_00C1B2
	move.w	(ram_C38A).w,d0
	cmp.w	#$6,d0	; general form
	bge.w	loc_00C1B2
	move.w	(ram_C38C).w,d0
	cmp.w	#$6,d0	; general form
	bge.w	loc_00C1B2
	move.w	(ram_C38E).w,d0
	cmp.w	#$6,d0	; general form
	blt.w	loc_00C1BC
loc_00C1B2:
	tst.w	d0
	bmi.w	loc_00C1BC
	bsr.w	sub_00C21C
loc_00C1BC:
	movea.w	#$C732,a1
	lea	$39E(a1),a2
	moveq	#$2,d0
	jsr	(sub_00C1D0).l
	bra.w	loc_00C26A


; ----------------------------------------------------------------------
; called from $00C1C6, $00C294
sub_00C1D0:
	tst.w	(ram_D280).w
	bne.w	loc_00C21A
	btst	#4,(ram_C34C).w
	bne.w	loc_00C202
	cmp.w	(ram_C394).w,d0
	beq.w	loc_00C21A
	cmp.w	(ram_C396).w,d0
	beq.w	loc_00C21A
	cmp.w	(ram_C398).w,d0
	beq.w	loc_00C21A
	cmp.w	(ram_C39A).w,d0
	beq.w	loc_00C21A
loc_00C202:
	jsr	(sub_01E590).l
	jsr	(sub_025122).l
	jsr	(sub_022296).l
	move.w	#$2710,(ram_C36C).w
loc_00C21A:
	rts


; ----------------------------------------------------------------------
; called from $00C17E, $00C1B8
sub_00C21C:
	exg	a2,a3
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	bclr	#3,$63(a3)
	move.l	a2,-(sp)
	jsr	(sub_0125A6).l
	movea.l	(sp)+,a2
	btst	#3,$63(a3)
	beq.w	loc_00C266
	btst	#6,$62(a3)
	beq.w	loc_00C25A
	move.w	#$168,$42(a2)
	move.w	$52(a3),$46(a2)
	bra.w	loc_00C266
loc_00C25A:
	move.w	#$258,$40(a2)
	move.w	$52(a3),$44(a2)
loc_00C266:
	exg	a2,a3
	rts
loc_00C26A:
	move.w	#$40,d0
	jsr	(sub_00C2B6).l
	move.w	#$42,d0
	jsr	(sub_00C2B6).l
	tst.w	$40(a3)
	bpl.s	loc_00C21A
	tst.w	$42(a3)
	bpl.s	loc_00C21A
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	moveq	#$1,d0
	jsr	(sub_00C1D0).l
	move.w	(ram_C4CA).w,d0
	move.w	d0,(ram_DE3C).w
	move.w	d0,(ram_DE3E).w
	move.w	#$FFFF,(ram_D4A6).w
	move.w	#$1C,d0
	jmp	(sub_01F172).l


; ----------------------------------------------------------------------
; called from $00C26E, $00C278
sub_00C2B6:
	tst.w	$0(a3,d0.w)
	bmi.w	loc_00C21A
	move.w	$4(a3,d0.w),d1
	asl.w	#7,d1
	movea.w	#$B060,a0
	movea.w	#$C732,a2
	btst	#6,$62(a0,d1.w)
	beq.w	loc_00C2DA
	adda.w	#$39E,a2
loc_00C2DA:
	btst	#3,$63(a0,d1.w)
	bne.w	loc_00C2EC
	st	$0(a3,d0.w)
	bra.w	sub_0125E4
loc_00C2EC:
	sub.w	d7,$0(a3,d0.w)
	bpl.w	loc_00C21A
	move.l	a3,-(sp)
	lea	$0(a0,d1.w),a3
	btst	#3,$63(a3)
	beq.w	loc_00C312
	clr.w	d2
	jsr	(sub_012808).l
	jsr	(sub_0125E4).l
loc_00C312:
	movea.l	(sp)+,a3
	rts
loc_00C316:
	jmp	(loc_026BC6).l
loc_00C31C:
	jmp	(sub_02197E).l


; ----------------------------------------------------------------------
; called from $00F66E
sub_00C322:
	bclr	#1,$62(a3)
	beq.w	loc_00C784
	bclr	#1,(ram_C358).w
	bclr	#2,(ram_C342).w
	bclr	#5,(ram_C342).w
	bclr	#0,(ram_C344).w
	bclr	#1,(ram_C344).w
	bclr	#0,(ram_C350).w
	bclr	#1,(ram_C350).w
	bclr	#2,(ram_C350).w
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01FFA2).l
loc_00C366:
	btst	#0,(VideoFlags).w
	bne.s	loc_00C366
	bclr	#0,(ram_C35C).w
	move.w	sr,-(sp)
	move.w	#$3C,(ram_D2FE).w
	tst.w	(ram_BFE4).w
	bne.w	loc_00C396
	tst.w	(ram_BFE6).w
	bne.w	loc_00C396
	move.w	#$FFFF,(ram_D49C).w
	bra.w	loc_00C39A
loc_00C396:
	move.w	#$2700,sr
loc_00C39A:
	cmpi.w	#$258,(ram_B8B4).w
	bls.w	loc_00C3AA
	move.w	#$258,(ram_B8B4).w
loc_00C3AA:
	bset	#3,(VideoFlags).w
	bclr	#0,(ram_C33C).w
	bclr	#0,(ram_C340).w
	move.w	#$3E8,(ram_BF18).w
	move.w	#$3E8,(ram_BF16).w
	clr.b	(ram_BFBC).w
	st	(ram_C452).w
	st	(ram_BF1E).w
	st	(ram_BF22).w
	bclr	#1,(ram_C33E).w
	bset	#0,(ram_C33E).w
	bset	#2,(ram_C33E).w
	st	(ram_BF14).w
	st	(ram_BFA8).w
	btst	#3,(ram_C350).w
	bne.w	loc_00C402
	bset	#4,(VideoFlags).w
loc_00C402:
	bclr	#4,(ram_C350).w
	jsr	(sub_022252).l
	move.w	#$2710,(ram_C36C).w
	clr.w	(ram_BD30).w
	clr.w	(ram_BD34).w
	btst	#3,(ram_C350).w
	beq.w	loc_00C45A
	move.w	(ram_BFE4).w,(ram_BD34).w
	cmpi.w	#$FFC4,(ram_BD34).w
	blt.w	loc_00C44E
	cmpi.w	#$3C,(ram_BD34).w
	bgt.w	loc_00C444
	bra.w	loc_00C454
loc_00C444:
	move.w	#$3C,(ram_BD34).w
	bra.w	loc_00C454
loc_00C44E:
	move.w	#$FFC4,(ram_BD34).w
loc_00C454:
	move.w	(ram_BFE6).w,(ram_BD30).w
loc_00C45A:
	move.w	(ram_BFE4).w,(ram_B760).w
	move.w	(ram_BFE6).w,(ram_B774).w
	st	(ram_B778).w
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	clr.w	(ram_B78C).w
	st	(ram_B7C0).w
	movea.w	#$B660,a0
	clr.w	$28(a0)
	clr.w	$2A(a0)
	clr.w	(a0)
	move.w	#$122,$14(a0)
	adda.w	#$80,a0
	clr.w	$28(a0)
	clr.w	$2A(a0)
	clr.w	(a0)
	move.w	#$FEDE,$14(a0)
	movea.w	#$B7E0,a0
	move.w	#$299,$6(a0)
	clr.w	$58(a0)
	clr.w	$4(a0)
	clr.w	(ram_B764).w
	bclr	#6,(ram_C33C).w
	moveq	#$64,d4
loc_00C4C0:
	jsr	(sub_01B29A).l
	dbra	d4,loc_00C4C0
	move.w	#$3C,(ram_BFE2).w
	jsr	(sub_0253C4).l
	movea.w	#$C732,a2
	jsr	(sub_025122).l
	jsr	(sub_025352).l
	adda.w	#$39E,a2
	jsr	(sub_025122).l
	jsr	(sub_025352).l
	jsr	(sub_026A0C).l
	btst	#3,(ram_C350).w
	beq.w	loc_00C50C
	jsr	(sub_1E4838).l
loc_00C50C:
	move.l	a3,-(sp)
	movea.w	#$B060,a3
	moveq	#$B,d2
loc_00C514:
	move.w	#$FF10,(a3)
	clr.w	$14(a3)
	clr.w	$6(a3)
	move.w	$34(a3),d1
	bmi.w	loc_00C624
	beq.w	loc_00C576
	move.l	#$16,d0
	cmp.w	#$4,d1	; general form
	bne.w	loc_00C570
	movea.w	#$C732,a2
	btst	#6,$62(a3)
	beq.w	loc_00C54C
	adda.w	#$39E,a2
loc_00C54C:
	clr.w	$18(a2)
	move.b	$67(a3),$19(a2)
	bclr	#7,(ram_C34E).w
	st	$1A(a2)
	st	$1C(a2)
	bclr	#3,$30(a2)
	move.l	#$17,d0
loc_00C570:
	jsr	(sub_01F168).l
loc_00C576:
	move.w	(ram_C756).w,d4
	btst	#6,$62(a3)
	beq.w	loc_00C588
	move.w	(ram_CAF4).w,d4
loc_00C588:
	neg.w	d4
	addq.w	#6,d4
	asl.w	#3,d4
	movea.l	#dat_00C7B8,a1
	adda.w	d4,a1
	move.b	$0(a1,d1.w),d4
	asl.w	#2,d4
	movea.l	#dat_00C7D0,a1
	move.w	$0(a1,d4.w),d0
	move.w	$2(a1,d4.w),d1
	btst	#7,$62(a3)
	bne.w	loc_00C5B8
	neg.w	d0
	neg.w	d1
loc_00C5B8:
	tst.w	$34(a3)
	beq.w	loc_00C5EA
	cmp.w	#$8,d4	; general form
	bgt.w	loc_00C5E2
	move.w	(ram_BFE4).w,d3
	eor.w	d0,d3
	bpl.w	loc_00C5DA
	move.w	(ram_BFE6).w,d3
	asr.w	#3,d3
	sub.w	d3,d1
loc_00C5DA:
	move.w	(ram_BFE4).w,d3
	asr.w	#2,d3
	sub.w	d3,d0
loc_00C5E2:
	add.w	(ram_BFE4).w,d0
	add.w	(ram_BFE6).w,d1
loc_00C5EA:
	move.w	d0,(a3)
	move.w	d1,$14(a3)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	sub.w	(ram_B760).w,d0
	sub.w	(ram_B774).w,d1
	neg.w	d0
	neg.w	d1
	jsr	(sub_01F186).l
	move.w	d0,$54(a3)
	bclr	#2,$63(a3)
	bclr	#5,$62(a3)
	move.w	#$870,d1
	jsr	(sub_01F3B2).l
loc_00C624:
	adda.w	#$80,a3
	dbra	d2,loc_00C514
	jsr	(sub_02698A).l
	movea.l	(sp)+,a3
	jsr	(sub_01E68E).l
	move.w	(ram_B03C).w,d4
	movea.l	#Art_09E52A_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B028).w
	movea.l	#Art_IngameMisc_Tiles,a2
	jsr	(sub_020780).l
	move.w	#$FFFF,(ram_D492).w
	btst	#0,(ram_C34C).w
	beq.w	loc_00C678
	move.w	(ram_D49C).w,d0
	bmi.w	loc_00C678
	jsr	(sub_1D1470).l
loc_00C678:
	btst	#3,(ram_C350).w
	bne.w	loc_00C686
	bsr.w	sub_00C7EC
loc_00C686:
	move.w	#$78,d0
	jsr	(Random).l
	addi.w	#$12C,d0
	cmpi.w	#$0,(ram_D492).w
	beq.w	loc_00C6C6
	cmpi.w	#$1,(ram_D492).w
	beq.w	loc_00C6C6
	cmpi.w	#$5,(ram_D492).w
	beq.w	loc_00C6C6
	cmpi.w	#$4,(ram_D492).w
	beq.w	loc_00C6C6
	cmpi.w	#$2,(ram_D492).w
	bne.w	loc_00C6D2
loc_00C6C6:
	cmp.w	#$186,d0	; general form
	bgt.w	loc_00C6D2
	move.w	#$186,d0
loc_00C6D2:
	move.w	#$2,$40(a3)
	btst	#3,(ram_C350).w
	bne.w	loc_00C6E6
	move.w	d0,$40(a3)
loc_00C6E6:
	move.w	#$18,(FadeCounter).w
	movea.l	#ram_BDC0,a0
	move.w	#$1,(a0)
	move.w	#$8000,$2(a0)
	move.w	#$4,$4(a0)
	move.w	#$A800,$6(a0)
	move.w	#$7,$8(a0)
	move.w	#$8000,$A(a0)
	btst	#1,(ram_C33A).w
	bne.w	loc_00C72A
	eori.w	#$800,$2(a0)
	eori.w	#$800,$6(a0)
loc_00C72A:
	move.w	#$FFFF,(ram_BFE8).w
	move.w	#$FFFF,(ram_BFEA).w
	jsr	(sub_1D21D6).l
	bclr	#6,(ram_C34E).w
	bne.w	loc_00C750
	bclr	#4,(ram_C34E).w
	beq.w	loc_00C760
loc_00C750:
	bclr	#4,(ram_C34E).w
	move.w	(ram_D4A8).w,-(sp)
	jsr	(sub_092172).l
loc_00C760:
	btst	#3,(ram_C350).w
	bne.w	loc_00C776
	move.w	#$78,(ram_C3B0).w
	jsr	(sub_1E2F06).l
loc_00C776:
	move.w	#$18,(FadeCounter).w
	move.w	(sp)+,sr
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_00C784:
	subq.w	#1,(ram_C3B0).w
	bne.w	loc_00C79E
	jsr	(sub_1E30D6).l
	bclr	#2,(ram_C358).w
	bset	#3,(ram_C358).w
loc_00C79E:
	subq.w	#1,$40(a3)
	bpl.w	loc_00C7B2
	jsr	(sub_1D14AA).l
	jmp	(loc_00C928).l
loc_00C7B2:
	jmp	(loc_01E83E).l
dat_00C7B8:
	dc.w	$0001,$0203,$0405,$0600,$0001,$0503,$0402,$0000
	dc.w	$0003,$0501,$0400,$0000
dat_00C7D0:
	dc.w	$0000,$FEF0,$FFDD,$FFCE,$0023,$FFCE,$FFCE,$FFF6
	dc.w	$0000,$FFF1,$0032,$FFF6,$0000,$FFC4


; ----------------------------------------------------------------------
; called from $00C682, $1DD032
sub_00C7EC:
	jsr	(Text_Print).l
inl_00C7F2:
	dc.w	loc_00C7F8-inl_00C7F2
	dc.b	$BF,$00,$00,$00
loc_00C7F8:
	moveq	#$36,d0
	tst.w	(ram_BFE4).w
	bpl.w	loc_00C806
	move.w	#$BE,d0
loc_00C806:
	move.w	d0,(ram_B04C).w
	subi.w	#$2E,d0
	asr.w	#3,d0
	move.w	d0,(TextX).w
	moveq	#$5C,d0
	move.w	d0,(ram_B04E).w
	subi.w	#$44,d0
	asr.w	#3,d0
	move.w	d0,(TextY).w
	move.w	(ram_B03C).w,d4
	movea.l	#Art_09E52A,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$C,d2
	moveq	#$9,d3
	moveq	#$0,d5
	bset	#0,(TextFlags).w
	jsr	(TileMap_Draw).l
	bclr	#0,(TextFlags).w
	tst.w	(ram_D280).w
	bne.w	loc_00C8BA
	jsr	(Text_PrintCmd).l
inl_00C860:
	dc.w	loc_00C866-inl_00C860
	dc.b	$FA,$0A,$FE,$04
loc_00C866:
	moveq	#$C,d0
	moveq	#$3,d1
	jsr	(Text_PrintDigitsBig).l
	move.w	(ram_C748).w,d0
	move.w	(ram_CAE6).w,d1
	btst	#1,(ram_C33A).w
	bne.w	loc_00C884
	exg	d0,d1
loc_00C884:
	jsr	(Text_PrintCmd).l
inl_00C88A:
	dc.w	loc_00C890-inl_00C88A
	dc.b	$FB,$01,$FA,$FE
loc_00C890:
	movea.l	#dat_0289AC,a1
	jsr	(List_Skip).l
	jsr	(Text_Print_Worker).l
	addq.w	#4,(TextX).w
	move.w	d1,d0
	movea.l	#dat_0289AC,a1
	jsr	(List_Skip).l
	jsr	(Text_Print_Worker).l
loc_00C8BA:
	rts


; ----------------------------------------------------------------------
; called from $021A32
sub_00C8BC:
	movem.l	d0/d1/a0/a1,-(sp)
	movea.w	#$C3B2,a0
loc_00C8C4:
	bsr.w	sub_00C8D4
	addq.w	#2,a0
	tst.w	(a0)
	bne.s	loc_00C8C4
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $00C8C4
sub_00C8D4:
	move.b	$1(a0),d0
	andi.w	#$7F,d0
	asl.w	#7,d0
	movea.w	#$B060,a1
	move.w	#$76,d1
	btst	#7,$62(a1,d0.w)
	bne.w	loc_00C904
	neg.w	d1
	cmp.w	(ram_BFE6).w,d1
	blt.w	loc_00C924
	move.w	#$FF98,(ram_BFE6).w
	bra.w	loc_00C912
loc_00C904:
	cmp.w	(ram_BFE6).w,d1
	bgt.w	loc_00C924
	move.w	#$68,(ram_BFE6).w
loc_00C912:
	move.w	#$51,d0
	tst.w	(ram_BFE4).w
	bpl.w	loc_00C920
	neg.w	d0
loc_00C920:
	move.w	d0,(ram_BFE4).w
loc_00C924:
	rts
loc_00C926:
	rts
loc_00C928:
	move.w	#$2C,-(sp)
	jsr	(sub_09205A).l
	bclr	#0,(ram_C33E).w
	move.w	#$3C,(ram_D2FE).w
	move.w	(ram_B03C).w,d4
	movea.l	#Art_RefereeCutscene_Tiles,a2
	jsr	(sub_020780).l
	bclr	#2,(ram_C33E).w
	bclr	#0,(ram_C33A).w
	bclr	#0,$63(a3)
	clr.w	(ram_C36C).w
	bset	#4,(ram_C340).w
	move.w	(ram_BFE8).w,d3
	move.w	#$800,d4
	movea.l	#dat_00CA3C,a0
	movea.w	#$BDC0,a1
	moveq	#$10,d2
	move.w	(a1),d1
	sub.b	-$1(a0,d1.w),d2
	move.w	$4(a1),d1
	add.b	-$1(a0,d1.w),d2
	moveq	#$21,d0
	jsr	(Random).l
	cmp.b	d0,d2
	bls.w	loc_00C99C
	addq.w	#4,a1
loc_00C99C:
	btst	#3,$2(a1)
	beq.w	loc_00C9AC
	move.w	(ram_BFEA).w,d3
	neg.w	d4
loc_00C9AC:
	move.w	d3,d0
	btst	#3,d0
	bne.w	loc_00C9C8
	andi.w	#$7,d0
	move.w	(VDP_HVCOUNTER).l,d1
	andi.w	#$3,d1
	bne.w	loc_00C9E0
loc_00C9C8:
	moveq	#$5,d0
	jsr	(Random).l
	subq.w	#2,d0
	andi.w	#$7,d0
	tst.w	d4
	bmi.w	loc_00C9E0
	eori.w	#$4,d0
loc_00C9E0:
	btst	#3,(ram_C350).w
	beq.w	loc_00C9FA
	clr.w	$28(a3)
	clr.w	$2A(a3)
	clr.w	$2C(a3)
	bra.w	loc_00CA26
loc_00C9FA:
	asl.w	#2,d0
	movea.l	#dat_01FEB0,a0
	move.w	$0(a0,d0.w),d1
	asl.w	#5,d1
	move.w	d1,$28(a3)
	move.w	$2(a0,d0.w),d1
	asl.w	#5,d1
	add.w	d4,d1
	move.w	d1,$2A(a3)
	move.w	#$800,d0
	jsr	(Random).l
	move.w	d0,$2C(a3)
loc_00CA26:
	clr.w	(ram_B778).w
	bclr	#2,$62(a3)
	move.l	#$18,d0
	jmp	(sub_01F172).l
dat_00CA3C:
	dc.b	$00,$08,$10,$00,$08,$10


; ----------------------------------------------------------------------
; called from $01B13E
sub_00CA42:
	cmp.w	(ram_C388).w,d6
	bne.w	loc_00CA62
	jsr	(Joypad_Read1).l
	clr.w	d4
	move.w	#$FFFF,(ram_C380).w
	jsr	(sub_00CAFE).l
	bra.w	loc_00CA80
loc_00CA62:
	cmp.w	(ram_C38A).w,d6
	bne.w	loc_00CA80
	jsr	(Joypad_Read2).l
	move.w	#$2,d4
	move.w	#$FFFF,(ram_C380).w
	jsr	(sub_00CAFE).l
loc_00CA80:
	cmp.w	(ram_C38C).w,d6
	bne.w	loc_00CA9E
	jsr	(Joypad_Read3).l
	move.w	#$4,d4
	move.w	#$FFFF,(ram_C380).w
	jsr	(sub_00CAFE).l
loc_00CA9E:
	cmp.w	(ram_C38E).w,d6
	bne.w	loc_00CABC
	jsr	(Joypad_Read4).l
	move.w	#$6,d4
	move.w	#$FFFF,(ram_C380).w
	jsr	(sub_00CAFE).l
loc_00CABC:
	jsr	(sub_029EC6).l
	clr.w	$4E(a3)
	clr.w	$50(a3)
	move.w	(a3),d2
	move.w	$14(a3),d3
	cmp.w	$1C(a3),d2
	bne.w	loc_00CAE0
	cmp.w	$20(a3),d3
	beq.w	loc_00CAE6
loc_00CAE0:
	jsr	(sub_022A82).l
loc_00CAE6:
	move.w	d7,d0
	asl.w	#1,d0
	sub.w	d0,$32(a3)
	bpl.w	loc_00CAF6
	clr.w	$32(a3)
loc_00CAF6:
	move.w	$32(a3),$30(a3)
	rts


; ----------------------------------------------------------------------
; called from $00CA58, $00CA7A, $00CA98, $00CAB6
sub_00CAFE:
	btst	#7,(ram_C350).w
	beq.w	loc_00CB0E
	jmp	(loc_1E61C2).l
loc_00CB0E:
	cmpi.w	#$3924,$58(a3)
	bne.w	loc_00CB3A
	cmpi.w	#$C,$5A(a3)
	bne.w	loc_00CB3A
	bclr	#1,(SysFlags).w
	bclr	#2,(SysFlags).w
	bclr	#0,(ram_C35E).w
	jmp	(loc_01B434).l
loc_00CB3A:
	bclr	#0,(ram_C35A).w
	btst	#4,d3
	beq.w	loc_00CB4E
	bset	#0,(ram_C35A).w
loc_00CB4E:
	btst	#6,d3
	bne.w	loc_00CB74
	btst	#6,d2
	bne.w	loc_00CB74
	movem.l	a0,-(sp)
	movea.l	#ram_C390,a0
	asr.w	#1,d4
	clr.b	$0(a0,d4.w)
	add.w	d4,d4
	movem.l	(sp)+,a0
loc_00CB74:
	btst	#4,d1
	beq.w	loc_00CB92
	btst	#5,d1
	beq.w	loc_00CB92
	bclr	#4,d1
	bset	#6,$64(a3)
	bra.w	loc_00CBCC
loc_00CB92:
	btst	#4,d1
	beq.w	loc_00CBA0
	bclr	#6,$64(a3)
loc_00CBA0:
	btst	#4,d2
	beq.w	loc_00CBCC
	bclr	#6,$64(a3)
	beq.w	loc_00CBCC
	tst.w	d4
	bne.w	loc_00CBC2
	move.b	#$F,(ram_BF3C).w
	bra.w	loc_00CBC8
loc_00CBC2:
	move.b	#$F,(ram_BF3D).w
loc_00CBC8:
	bclr	#4,d2
loc_00CBCC:
	btst	#7,(ram_C34A).w
	beq.w	loc_00CBE4
	cmp.b	#$8,d0	; general form
	beq.w	loc_00CBE4
	jsr	(sub_1D1060).l
loc_00CBE4:
	move.w	d0,(ram_BF48).w
	andi.w	#$F,(ram_BF48).w
	jsr	(sub_01B86A).l
	btst	#7,d1
	beq.w	loc_00CC54
	tst.w	$34(a3)
	beq.w	loc_00CC1E
	movem.w	d3,-(sp)
	andi.b	#$F,d3
	movem.w	(sp)+,d3
	beq.w	loc_00CC1E
	jsr	(sub_00D5CC).l
	bra.w	loc_00CC6C
loc_00CC1E:
	tst.w	d4
	bne.w	loc_00CC2A
	jmp	(loc_019720).l
loc_00CC2A:
	cmp.w	#$2,d4	; general form
	bne.w	loc_00CC38
	jmp	(loc_019726).l
loc_00CC38:
	cmp.w	#$4,d4	; general form
	bne.w	loc_00CC46
	jmp	(loc_01972E).l
loc_00CC46:
	cmp.w	#$6,d4	; general form
	bne.w	loc_00CC54
	jmp	(loc_019736).l
loc_00CC54:
	btst	#7,(ram_C33C).w
	beq.w	loc_00CC6C
	btst	#3,d0
	bne.w	loc_00CC6C
	addq.w	#2,d0
	andi.w	#$7,d0
loc_00CC6C:
	btst	#0,(ram_C33E).w
	bne.w	loc_00BE76
	btst	#3,$63(a3)
	bne.w	loc_012784
	btst	#3,$62(a3)
	beq.w	loc_00D0F2
	movem.l	d0-d2/a0/a3,-(sp)
	move.w	(ram_BF0E).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_00CD26
	tst.w	(ram_BF14).w
	bmi.w	loc_00CD26
	tst.w	(ram_BFA8).w
	bpl.w	loc_00CD26
	btst	#5,d1
	beq.w	loc_00CD26
	bclr	#3,(SysFlags).w
	bsr.w	sub_00CCC6
	beq.w	loc_00CD26
	movem.l	(sp)+,d0-d2/a0/a3
	rts


; ----------------------------------------------------------------------
; called from $00CCB8, $00CDF0
sub_00CCC6:
	move.w	(ram_BF14).w,d0
	bmi.w	loc_00CD22
	tst.w	(ram_B7C0).w
	bpl.w	loc_00CD22
	asl.w	#7,d0
	movea.l	#ram_B060,a3
	adda.w	d0,a3
	tst.w	$34(a3)
	beq.w	loc_00CD22
	jsr	(sub_1CF2C4).l
	beq.w	loc_00CD22
	btst	#3,$62(a3)
	bne.w	loc_00CD22
	btst	#3,$64(a3)
	bne.w	loc_00CD22
	move.w	d4,(ram_DCEA).w
	bsr.w	sub_00DE38
	beq.w	loc_00CD22
	move.w	#$23,d0
	jsr	(sub_01F172).l
	move.w	#$1,d0
	rts
loc_00CD22:
	clr.w	d0
	rts
loc_00CD26:
	movem.l	(sp)+,d0-d2/a0/a3
	btst	#6,d1
	beq.w	loc_00CD60
	cmpi.w	#$1850,$58(a3)
	bne.w	loc_00CD60
	tst.w	$5A(a3)
	bne.w	loc_00CD60
	movem.w	d1,-(sp)
	move.w	#$9B4,d1
	jsr	(sub_01F3B2).l
	bset	#5,$62(a3)
	movem.w	(sp)+,d1
	bra.w	loc_00D54C
loc_00CD60:
	btst	#0,$63(a3)
	beq.w	loc_00CD78
	btst	#5,$62(a3)
	bne.w	loc_00D54C
	bra.w	loc_00F322
loc_00CD78:
	move.w	(ram_B7C0).w,d5
	cmp.w	$52(a3),d5
	bne.w	loc_00CD9C
	btst	#3,$64(a3)
	bne.w	loc_00D3C6
	btst	#5,$62(a3)
	beq.w	loc_00D3C6
	bra.w	loc_00D54C
loc_00CD9C:
	tst.w	$34(a3)
	bne.w	loc_00CDBC
	btst	#3,$64(a3)
	bne.w	loc_00CE88
	btst	#5,$62(a3)
	bne.w	loc_00CDBC
	bra.w	loc_00CE88
loc_00CDBC:
	btst	#3,$64(a3)
	beq.w	loc_00CDD4
	btst	#5,$62(a3)
	bne.w	loc_00D54C
	bra.w	loc_00CE88
loc_00CDD4:
	btst	#6,d1
	beq.w	loc_00CE04
	btst	#0,(ram_C35A).w
	bne.w	loc_00CE04
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#3,(SysFlags).w
	bsr.w	sub_00CCC6
	movem.l	(sp)+,d0-d7/a0-a6
	beq.w	loc_00CE12
	bset	#3,(SysFlags).w
	rts
loc_00CE04:
	btst	#5,$62(a3)
	bne.w	loc_00D54C
	bra.w	loc_00CE88
loc_00CE12:
	movem.l	d7/a0,-(sp)
	move.w	(ram_BF0E).w,d7
	asl.w	#7,d7
	movea.l	#ram_B060,a0
	adda.w	d7,a0
	tst.w	$34(a0)
	movem.l	(sp)+,d7/a0
	beq.w	loc_00CE78
	movem.w	d7,-(sp)
	move.w	$52(a3),d7
	cmp.w	(ram_BF14).w,d7
	movem.w	(sp)+,d7
	bne.w	loc_00CE78
	tst.w	(ram_B7C0).w
	bpl.w	loc_00CE78
	bset	#3,(SysFlags).w
	jsr	(sub_1CF2C4).l
	beq.w	loc_00CE78
	move.w	d0,-(sp)
	move.w	d4,(ram_DCEA).w
	bsr.w	sub_00DE38
	beq.w	loc_00CE74
	move.w	#$23,d0
	jsr	(sub_01F172).l
loc_00CE74:
	move.w	(sp)+,d0
	rts
loc_00CE78:
	btst	#5,$62(a3)
	bne.w	loc_00D54C
	jmp	(loc_01B488).l
loc_00CE88:
	tst.w	$34(a3)
	beq.w	loc_00CE9E
	btst	#2,(ram_C342).w
	bne.w	loc_00D0B0
	bra.w	loc_00CEEA
loc_00CE9E:
	btst	#6,(ram_C346).w
	bne.w	loc_00CEEA
	movem.l	a0,-(sp)
	movea.l	#ram_C394,a0
	cmpi.w	#$1,$0(a0,d4.w)
	movem.l	(sp)+,a0
	beq.w	loc_00CEC8
	tst.w	(ram_D28C).w
	bra.w	loc_00CECC
loc_00CEC8:
	tst.w	(ram_D28A).w
loc_00CECC:
	beq.w	loc_00CEEA
	movem.w	d0,-(sp)
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	movem.w	(sp)+,d0
	beq.w	loc_00CEEA
loc_00CEE4:
	jmp	(sub_01B546).l
loc_00CEEA:
	btst	#4,d3
	beq.w	loc_00CF90
	tst.w	(ram_D2FE).w
	bne.w	loc_00CF90
	tst.w	d4
	beq.w	loc_00CF4A
	tst.b	(ram_BF3D).w
	beq.w	loc_00D0B0
	subq.b	#1,(ram_BF3D).w
	bpl.w	loc_00CF16
	move.b	#$0,(ram_BF3D).w
loc_00CF16:
	tst.b	(ram_BF3D).w
	bne.w	loc_00CF90
	movem.l	a0,-(sp)
	movea.l	#ram_C394,a0
	cmpi.w	#$1,$0(a0,d4.w)
	movem.l	(sp)+,a0
	beq.w	loc_00CF3E
	tst.w	(ram_D28C).w
	bra.w	loc_00CF42
loc_00CF3E:
	tst.w	(ram_D28A).w
loc_00CF42:
	bne.w	loc_00CF90
	bra.w	loc_00D03C
loc_00CF4A:
	tst.b	(ram_BF3C).w
	beq.w	loc_00D0B0
	subq.b	#1,(ram_BF3C).w
	bpl.w	loc_00CF60
	move.b	#$0,(ram_BF3C).w
loc_00CF60:
	movem.l	a0,-(sp)
	movea.l	#ram_C394,a0
	cmpi.w	#$1,$0(a0,d4.w)
	movem.l	(sp)+,a0
	beq.w	loc_00CF80
	tst.w	(ram_D28C).w
	bra.w	loc_00CF84
loc_00CF80:
	tst.w	(ram_D28A).w
loc_00CF84:
	bne.w	loc_00CF90
	tst.b	(ram_BF3C).w
	beq.w	loc_00D03C
loc_00CF90:
	btst	#4,d1
	beq.w	loc_00CFB2
	tst.w	d4
	bne.w	loc_00CFA8
	move.b	#$F,(ram_BF3C).w
	bra.w	loc_00D0B0
loc_00CFA8:
	move.b	#$F,(ram_BF3D).w
	bra.w	loc_00D0B0
loc_00CFB2:
	btst	#4,d2
	beq.w	loc_00D0B0
	btst	#4,d3
	bne.w	loc_00D0B0
	move.w	(ram_BF3C).w,d0
	tst.w	d4
	beq.w	loc_00D006
	move.b	#$F,(ram_BF3D).w
	andi.w	#$FF,d0
	bne.w	loc_00CEE4
	movem.l	a0,-(sp)
	movea.l	#ram_C394,a0
	cmpi.w	#$1,$0(a0,d4.w)
	movem.l	(sp)+,a0
	beq.w	loc_00CFFA
	tst.w	(ram_D28C).w
	bra.w	loc_00CFFE
loc_00CFFA:
	tst.w	(ram_D28A).w
loc_00CFFE:
	bne.w	loc_00CEE4
	bra.w	loc_00D03C
loc_00D006:
	move.b	#$F,(ram_BF3C).w
	andi.w	#$FF00,d0
	bne.w	loc_00CEE4
	movem.l	a0,-(sp)
	movea.l	#ram_C394,a0
	cmpi.w	#$1,$0(a0,d4.w)
	movem.l	(sp)+,a0
	beq.w	loc_00D034
	tst.w	(ram_D28C).w
	bra.w	loc_00D038
loc_00D034:
	tst.w	(ram_D28A).w
loc_00D038:
	bne.w	loc_00CEE4
loc_00D03C:
	tst.w	(ram_D2FE).w
	beq.w	loc_00D04A
	jmp	(sub_01B546).l
loc_00D04A:
	move.w	#$5,d0
	cmp.w	#$5,d6	; general form
	ble.w	loc_00D05A
	move.w	#$B,d0
loc_00D05A:
	jsr	(sub_01B3B8).l
	tst.w	d0
	bmi.w	loc_00D0F2
	movem.l	d0/a3,-(sp)
	movea.l	#ram_B060,a3
	asl.w	#7,d0
	adda.w	d0,a3
	btst	#3,$62(a3)
	movem.l	(sp)+,d0/a3
	bne.w	loc_00D0F2
	tst.w	d4
	bne.w	loc_00D08E
	jmp	(sub_01B752).l
loc_00D08E:
	cmp.w	#$2,d4	; general form
	bne.w	loc_00D09C
	jmp	(sub_01B75C).l
loc_00D09C:
	cmp.w	#$4,d4	; general form
	bne.w	loc_00D0AA
	jmp	(sub_01B768).l
loc_00D0AA:
	jmp	(sub_01B774).l
loc_00D0B0:
	tst.w	$34(a3)
	bne.w	loc_00D344
	btst	#6,d1
	beq.w	loc_00D0F4
	move.w	(ram_BF48).w,d0
	cmp.b	#$8,d0	; general form
	beq.w	loc_00D0F4
	move.w	d0,$54(a3)
	move.b	#$8,$5E(a3)
	move.w	#$4BE,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	bset	#5,$62(a3)
	addi.w	#$96,(ram_B8B4).w
loc_00D0F2:
	rts
loc_00D0F4:
	btst	#5,d1
	bne.w	loc_00D154
	btst	#5,d3
	bne.w	loc_00D10E
	bclr	#7,$63(a3)
	bra.w	loc_00D29E
loc_00D10E:
	btst	#7,$63(a3)
	beq.w	loc_00D29E
	movem.l	d0-d3/a0-a3,-(sp)
	movea.l	#dat_0078B4,a0
	adda.w	$58(a3),a0
	move.w	$54(a3),d0
	btst	#3,$4(a3)
	beq.w	loc_00D13C
	neg.w	d0
	addq.w	#8,d0
	andi.w	#$7,d0
loc_00D13C:
	asl.w	#1,d0
	adda.w	$0(a0,d0.w),a0
	tst.b	$5B(a3)
	movem.l	(sp)+,d0-d3/a0-a3
	bpl.s	loc_00D0F2
	move.w	#$A,$5C(a3)
	rts
loc_00D154:
	btst	#5,$62(a3)
	bne.w	loc_00D29E
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	move.w	(ram_B774).w,d1
	sub.w	$14(a3),d1
	jsr	(sub_01F186).l
	move.w	d0,$54(a3)
	movem.w	(sp)+,d0/d1
	move.w	(ram_BF48).w,d0
	bclr	#0,(ram_C342).w
	move.w	(ram_C4CA).w,d0
	andi.w	#$7,d0
	asl.w	#4,d0
	addi.w	#$A0,d0
	cmpi.w	#$F1,(ram_B774).w
	bgt.w	loc_00D1AA
	cmpi.w	#$FF0F,(ram_B774).w
	bgt.w	loc_00D1AE
loc_00D1AA:
	subi.w	#$40,d0
loc_00D1AE:
	move.w	d0,d1
	muls.w	(ram_B788).w,d0
	swap	d0
	add.w	(ram_B760).w,d0
	muls.w	(ram_B78A).w,d1
	swap	d1
	add.w	(ram_B774).w,d1
	bsr.w	sub_00D260
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	#$384,d0	; general form
	bhi.w	loc_00D1E4
	movem.w	(sp)+,d0/d1
	bra.w	loc_00D20A
loc_00D1E4:
	jsr	(ISqrt).l
	moveq	#$1,d2
	add.w	d0,d2
	moveq	#$12,d4
	btst	#3,(ram_C33C).w
	beq.w	loc_00D1FC
	addq.w	#8,d4
loc_00D1FC:
	movem.w	(sp)+,d0/d1
	muls.w	d4,d1
	addq.w	#8,d4
	muls.w	d4,d0
	divs.w	d2,d0
	divs.w	d2,d1
loc_00D20A:
	add.w	d3,d1
	move.w	d1,d2
	cmpi.w	#$22,$2(a0)
	cmpi.w	#$18,(a0)
	cmpi.w	#$FFE8,(a0)
	cmpi.w	#$C,$2(a0)
	cmpi.w	#$11E,(ram_B774).w
	cmpi.w	#$FEE2,(ram_B774).w
	bset	#1,$63(a3)
	bne.w	loc_00D29E
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_BF1C,a0
	move.w	#$11E,d3
	btst	#7,$62(a3)
	beq.w	loc_00D254
	neg.w	d3
	addq.w	#4,a0
loc_00D254:
	jsr	(sub_01C91C).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00D1C4
sub_00D260:
	move.w	(ram_B7C0).w,d2
	cmp.w	$52(a3),d2
	bne.w	loc_00D26E
	clr.w	d0
loc_00D26E:
	cmp.w	#$119,d1	; general form
	blt.w	loc_00D27A
	move.w	#$119,d1
loc_00D27A:
	cmp.w	#$FEE7,d1	; general form
	bgt.w	loc_00D286
	move.w	#$FEE7,d1
loc_00D286:
	sub.w	d3,d1
	rts

	dc.w	$0152,$01EE,$0464,$040A,$028A,$0230,$0152,$01EE
	dc.w	$028A,$0230
loc_00D29E:
	btst	#1,$63(a3)
	beq.w	loc_00D2AA
	rts
loc_00D2AA:
	tst.w	$34(a3)
	bne.w	loc_00D5C6
	bclr	#1,(ram_C342).w
	cmpi.w	#$24,(a3)
	ble.w	loc_00D2D6
	tst.w	$28(a3)
	bmi.w	loc_00D2D6
	beq.w	loc_00D2D6
	bset	#1,(ram_C342).w
	clr.w	$28(a3)
loc_00D2D6:
	cmpi.w	#$FFDC,(a3)
	bge.w	loc_00D2F0
	tst.w	$28(a3)
	bpl.w	loc_00D2F0
	bset	#1,(ram_C342).w
	clr.w	$28(a3)
loc_00D2F0:
	cmpi.w	#$E7,$14(a3)
	bgt.w	loc_00D330
	cmpi.w	#$FF19,$14(a3)
	ble.w	loc_00D330
	bra.w	loc_00D308
loc_00D308:
	movem.w	d0/d1,-(sp)
	move.w	$14(a3),d0
	move.w	$2A(a3),d1
	eor.w	d1,d0
	movem.w	(sp)+,d0/d1
	bpl.w	loc_00D330
	tst.w	$2A(a3)
	beq.w	loc_00D330
	bset	#1,(ram_C342).w
	clr.w	$2A(a3)
loc_00D330:
	btst	#1,(ram_C342).w
	bne.w	loc_00D0F2
	move.w	(ram_BF48).w,d0
	jmp	(loc_01F3C8).l
loc_00D344:
	move.w	(ram_BF48).w,d0
	btst	#3,$64(a3)
	bne.w	loc_00C926
	btst	#5,d1
	beq.w	loc_00D5C6
	movem.l	d7/a0,-(sp)
	move.w	(ram_BF0E).w,d7
	asl.w	#7,d7
	movea.l	#ram_B060,a0
	adda.w	d7,a0
	tst.w	$34(a0)
	movem.l	(sp)+,d7/a0
	bne.w	loc_00D37E
loc_00D378:
	jmp	(loc_01B434).l
loc_00D37E:
	movem.w	d7,-(sp)
	move.w	$52(a3),d7
	cmp.w	(ram_BF14).w,d7
	movem.w	(sp)+,d7
	bne.s	loc_00D378
	tst.w	(ram_B7C0).w
	bpl.s	loc_00D378
	bclr	#3,(SysFlags).w
	jsr	(sub_1CF2C4).l
	beq.s	loc_00D378
	move.w	d0,-(sp)
	move.w	d4,(ram_DCEA).w
	bsr.w	sub_00DE38
	beq.w	loc_00D3C2
	move.w	#$23,d0
	bclr	#3,(SysFlags).w
	jsr	(sub_01F172).l
loc_00D3C2:
	move.w	(sp)+,d0
	rts
loc_00D3C6:
	jsr	(sub_01D4C8).l
	tst.w	$34(a3)
	bne.w	loc_00D3DE
	btst	#1,$63(a3)
	bne.w	loc_00D0F2
loc_00D3DE:
	btst	#2,(ram_C33C).w
	bne.w	loc_01327C
	btst	#3,(ram_C33C).w
	bne.w	sub_012EDA
	btst	#4,d1
	beq.w	loc_00D404
	jsr	(sub_1D1C98).l
	bra.w	sub_013242
loc_00D404:
	movem.l	a0,-(sp)
	btst	#6,d1
	beq.w	loc_00D424
	movea.l	#ram_D30A,a0
	move.w	#$F,$0(a0,d4.w)
	movem.l	(sp)+,a0
	bra.w	loc_00D44E
loc_00D424:
	btst	#6,d3
	beq.w	loc_00D44E
	movea.l	#ram_D30A,a0
	subq.w	#1,$0(a0,d4.w)
	bpl.w	loc_00D43E
	clr.w	$0(a0,d4.w)
loc_00D43E:
	tst.w	$0(a0,d4.w)
	bne.w	loc_00D44E
	movem.l	(sp)+,a0
	bra.w	sub_0125A6
loc_00D44E:
	movem.l	(sp)+,a0
	btst	#6,d3
	bne.w	loc_00D52C
	btst	#6,d2
	beq.w	loc_00D52C
	movem.l	a0,-(sp)
	movea.l	#ram_C390,a0
	asr.w	#1,d4
	tst.b	$0(a0,d4.w)
	bmi.w	loc_00D526
	add.w	d4,d4
	movea.l	#ram_D30A,a0
	cmpi.w	#$3DE,$0(a0,d4.w)
	movem.l	(sp)+,a0
	bge.w	loc_00D52C
	btst	#3,$63(a3)
	bne.w	loc_00D51C
	movem.w	d0,-(sp)
	move.w	(ram_B774).w,d0
	bpl.w	loc_00D4A4
	neg.w	d0
loc_00D4A4:
	cmp.w	#$76,d0	; general form
	blt.w	loc_00D518
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_00D4BC
	neg.w	d0
loc_00D4BC:
	tst.w	d0
	bmi.w	loc_00D518
	movem.w	(sp)+,d0
	btst	#3,(ram_BF49).w
	bne.w	loc_00D506
	movem.w	d1,-(sp)
	move.w	#$1,d1
	btst	#7,$62(a3)
	bne.w	loc_00D4E6
	move.w	#$0,d1
loc_00D4E6:
	btst	d1,d3
	movem.w	(sp)+,d1
	beq.w	loc_00D506
	move.w	(ram_BF48).w,d0
	bset	#1,(SysFlags).w
	bset	#2,(SysFlags).w
	jmp	(sub_013242).l
loc_00D506:
	bset	#0,(SysFlags).w
	bne.w	loc_00D516
	jmp	(sub_012E40).l
loc_00D516:
	rts
loc_00D518:
	movem.w	(sp)+,d0
loc_00D51C:
	bset	#3,(ram_C346).w
	bra.w	sub_013242
loc_00D526:
	movem.l	(sp)+,a0
	add.w	d4,d4
loc_00D52C:
	tst.w	$34(a3)
	bne.w	loc_00D53A
	jmp	(loc_01F3C8).l
loc_00D53A:
	btst	#5,d1
	beq.w	loc_00D5C6
	jsr	(sub_1D1C98).l
	bra.w	sub_012E40
loc_00D54C:
	move.w	(ram_B7C0).w,d5
	cmp.w	$52(a3),d5
	beq.w	loc_00D0F2
	btst	#4,d1
	beq.w	loc_00C926
	btst	#6,(ram_C346).w
	bne.w	loc_00C926
	jsr	(sub_01B546).l
	movem.l	d0/a0,-(sp)
	tst.w	d4
	beq.w	loc_00D5A6
	cmp.w	#$2,d4	; general form
	beq.w	loc_00D59E
	cmp.w	#$4,d4	; general form
	beq.w	loc_00D596
	bra.w	loc_00D58E
loc_00D58E:
	move.w	(ram_C38E).w,d0
	bra.w	loc_00D5AA
loc_00D596:
	move.w	(ram_C38C).w,d0
	bra.w	loc_00D5AA
loc_00D59E:
	move.w	(ram_C38A).w,d0
	bra.w	loc_00D5AA
loc_00D5A6:
	move.w	(ram_C388).w,d0
loc_00D5AA:
	tst.w	d0
	bmi.w	loc_00D5C0
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	adda.w	d0,a0
	bset	#6,$64(a0)
loc_00D5C0:
	movem.l	(sp)+,d0/a0
	rts
loc_00D5C6:
	jmp	(loc_01F3C8).l


; ----------------------------------------------------------------------
; called from $00CC14
sub_00D5CC:
	btst	#2,$63(a3)
	bne.w	loc_00D612
	btst	#0,(ram_C33A).w
	bne.w	loc_00D612
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_00D5F8
	bsr.w	sub_00D614
	beq.w	loc_00D60E
loc_00D5F8:
	move.w	#$294A,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	addi.w	#$64,$28(a3)
loc_00D60E:
	movem.l	(sp)+,d0-d7/a0-a6
loc_00D612:
	rts


; ----------------------------------------------------------------------
; called from $00D5F0
sub_00D614:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a2
	btst	#6,$62(a3)
	beq.w	loc_00D62C
	adda.w	#$39E,a2
loc_00D62C:
	move.w	$28(a2),d7
	clr.w	d0
	move.b	$67(a3),d0
	jsr	(sub_013E44).l
	beq.w	loc_00D732
	jsr	(sub_013C76).l
	adda.w	(a1),a1
	clr.w	d0
	move.b	(a1),d0
	movea.l	#dat_00D73C,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_00D660
	movea.l	#dat_00D84C,a0
loc_00D660:
	asl.w	#3,d7
	move.w	#$3,d1
loc_00D666:
	cmp.b	$0(a0,d7.w),d0
	beq.w	loc_00D678
	addq.w	#2,d7
	dbra	d1,loc_00D666
	bra.w	loc_00D732
loc_00D678:
	clr.l	d0
	move.b	$1(a0,d7.w),d0
	cmp.w	#$4,d0	; general form
	beq.w	loc_00D68E
	cmp.w	#$9,d0	; general form
	bne.w	loc_00D6A0
loc_00D68E:
	tst.w	$54(a3)
	beq.w	loc_00D6A0
	cmpi.w	#$4,$54(a3)
	bne.w	loc_00D732
loc_00D6A0:
	cmp.w	#$6,d0	; general form
	beq.w	loc_00D6B0
	cmp.w	#$A,d0	; general form
	bne.w	loc_00D6C2
loc_00D6B0:
	tst.w	$54(a3)
	beq.w	loc_00D6C2
	cmpi.w	#$4,$54(a3)
	bne.w	loc_00D732
loc_00D6C2:
	cmp.w	#$7,d0	; general form
	beq.w	loc_00D6D2
	cmp.w	#$8,d0	; general form
	bne.w	loc_00D71C
loc_00D6D2:
	btst	#7,$62(a3)
	bne.w	loc_00D6FE
	cmpi.w	#$4,$54(a3)
	beq.w	loc_00D71C
	cmpi.w	#$3,$54(a3)
	beq.w	loc_00D71C
	cmpi.w	#$5,$54(a3)
	beq.w	loc_00D71C
	bra.w	loc_00D732
loc_00D6FE:
	cmpi.w	#$0,$54(a3)
	beq.w	loc_00D71C
	cmpi.w	#$1,$54(a3)
	beq.w	loc_00D71C
	cmpi.w	#$7,$54(a3)
	bne.w	loc_00D732
loc_00D71C:
	asl.w	#2,d0
	movea.l	#ptrtbl_00D95C,a0
	movea.l	$0(a0,d0.w),a0
	jsr	(a0)
	move.w	#$0,d0
	bra.w	loc_00D736
loc_00D732:
	move.w	#$1,d0
loc_00D736:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_00D73C:
	dc.b	$09,$00,$08,$0A,$FF,$00,$FF,$00,$77,$08,$08,$02,$FF,$00,$FF,$00
	dc.b	$16,$04,$FF,$00,$FF,$00,$FF,$00,$14,$05,$FF,$00,$FF,$00,$FF,$00
	dc.b	$27,$0B,$07,$08,$FF,$00,$FF,$00,$21,$0B,$19,$07,$FF,$00,$FF,$00
	dc.b	$09,$09,$FF,$00,$FF,$00,$FF,$00,$91,$0C,$19,$0A,$FF,$00,$FF,$00
	dc.b	$07,$03,$FF,$00,$FF,$00,$FF,$00,$55,$06,$44,$04,$FF,$00,$FF,$00
	dc.b	$94,$09,$FF,$00,$FF,$00,$FF,$00,$25,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$77,$04,$08,$02,$FF,$00,$FF,$00,$04,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$16,$01,$FF,$00,$FF,$00,$FF,$00,$11,$08,$20,$0B,$FF,$00,$FF,$00
	dc.b	$19,$09,$91,$05,$FF,$00,$FF,$00,$88,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$07,$0A,$FF,$00,$FF,$00,$FF,$00,$66,$06,$68,$00,$FF,$00,$FF,$00
	dc.b	$11,$07,$14,$0B,$FF,$00,$FF,$00,$16,$08,$99,$0C,$FF,$00,$FF,$00
	dc.b	$44,$01,$FF,$00,$FF,$00,$FF,$00,$93,$0C,$17,$07,$FF,$00,$FF,$00
	dc.b	$96,$05,$89,$0C,$FF,$00,$FF,$00,$90,$0A,$12,$01,$FF,$00,$FF,$00
	dc.b	$94,$0C,$66,$06,$68,$00,$07,$04,$96,$05,$09,$0C,$21,$0B,$19,$07
	dc.b	$66,$06,$99,$0C,$88,$03,$14,$05,$27,$0B,$09,$09,$96,$04,$17,$0A
	dc.b	$96,$05,$91,$0C,$68,$00,$89,$0A,$FF,$00,$FF,$00,$FF,$00,$FF,$00
	dc.b	$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00
dat_00D84C:
	dc.b	$09,$00,$08,$0A,$FF,$00,$FF,$00,$77,$08,$08,$02,$FF,$00,$FF,$00
	dc.b	$16,$04,$FF,$00,$FF,$00,$FF,$00,$14,$05,$FF,$00,$FF,$00,$FF,$00
	dc.b	$27,$0B,$07,$08,$FF,$00,$FF,$00,$21,$0B,$19,$07,$FF,$00,$FF,$00
	dc.b	$09,$09,$FF,$00,$FF,$00,$FF,$00,$91,$0C,$19,$0A,$FF,$00,$FF,$00
	dc.b	$07,$03,$FF,$00,$FF,$00,$FF,$00,$55,$06,$44,$04,$FF,$00,$FF,$00
	dc.b	$94,$09,$FF,$00,$FF,$00,$FF,$00,$25,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$77,$04,$08,$02,$FF,$00,$FF,$00,$04,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$16,$01,$FF,$00,$FF,$00,$FF,$00,$11,$08,$20,$0B,$FF,$00,$FF,$00
	dc.b	$19,$09,$91,$05,$FF,$00,$FF,$00,$88,$03,$FF,$00,$FF,$00,$FF,$00
	dc.b	$07,$0A,$FF,$00,$FF,$00,$FF,$00,$66,$06,$68,$00,$FF,$00,$FF,$00
	dc.b	$11,$07,$14,$0B,$FF,$00,$FF,$00,$16,$08,$99,$0C,$FF,$00,$FF,$00
	dc.b	$44,$01,$FF,$00,$FF,$00,$FF,$00,$93,$0C,$17,$07,$FF,$00,$FF,$00
	dc.b	$96,$05,$89,$0C,$FF,$00,$FF,$00,$90,$0A,$12,$01,$FF,$00,$FF,$00
	dc.b	$19,$0C,$77,$0B,$39,$03,$71,$05,$33,$0C,$77,$0B,$22,$03,$55,$06
	dc.b	$66,$06,$99,$0C,$88,$03,$14,$05,$27,$0B,$09,$09,$96,$04,$17,$0A
	dc.b	$96,$05,$91,$0C,$68,$00,$89,$0A,$FF,$00,$FF,$00,$FF,$00,$FF,$00
	dc.b	$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00,$FF,$00

ptrtbl_00D95C:
	dc.l	sub_00D990
	dc.l	sub_00D9AE
	dc.l	sub_00D9D4
	dc.l	sub_00D9FA
	dc.l	sub_00DA0C
	dc.l	sub_00DDF2
	dc.l	sub_00DAFC
	dc.l	sub_00DE14
	dc.l	sub_00DE26
	dc.l	sub_00DA84
	dc.l	sub_00DB74
	dc.l	sub_00DC16
	dc.l	sub_00DBEC


; ----------------------------------------------------------------------
; called from $00D728
sub_00D990:
	move.w	(ram_BF48).w,d0
	bset	#1,(SysFlags).w
	bset	#2,(SysFlags).w
	bset	#0,(ram_C35E).w
	jsr	(sub_013242).l
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00D9AE:
	move.w	#$39B6,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	$28(a3),d0
	asr.w	#1,d0
	move.w	d0,$28(a3)
	move.w	$2A(a3),d0
	asr.w	#1,d0
	move.w	d0,$2A(a3)
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00D9D4:
	move.w	#$E9C,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	$28(a3),d0
	asr.w	#1,d0
	move.w	d0,$28(a3)
	move.w	$2A(a3),d0
	asr.w	#1,d0
	move.w	d0,$2A(a3)
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00D9FA:
	move.w	#$3A68,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DA0C:
	move.w	#$3B1E,d1
	btst	#3,$4(a3)
	beq.w	loc_00DA1E
	move.w	#$3ABA,d1
loc_00DA1E:
	tst.w	$54(a3)
	bne.w	loc_00DA30
	tst.w	(a3)
	bmi.w	loc_00DA48
	bra.w	loc_00DA36
loc_00DA30:
	tst.w	(a3)
	bpl.w	loc_00DA48
loc_00DA36:
	move.w	#$3ABA,d1
	btst	#3,$4(a3)
	beq.w	loc_00DA48
	move.w	#$3B1E,d1
loc_00DA48:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	#$1500,$28(a3)
	btst	#3,$4(a3)
	bne.w	loc_00DA68
	neg.w	$28(a3)
loc_00DA68:
	cmpi.w	#$3B1E,$58(a3)
	bne.w	loc_00DA76
	neg.w	$28(a3)
loc_00DA76:
	tst.w	$54(a3)
	beq.w	loc_00DA82
	neg.w	$28(a3)
loc_00DA82:
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DA84:
	move.w	#$3B50,d1
	btst	#3,$4(a3)
	beq.w	loc_00DA96
	move.w	#$3AEC,d1
loc_00DA96:
	tst.w	$54(a3)
	bne.w	loc_00DAA8
	tst.w	(a3)
	bmi.w	loc_00DAC0
	bra.w	loc_00DAAE
loc_00DAA8:
	tst.w	(a3)
	bpl.w	loc_00DAC0
loc_00DAAE:
	move.w	#$3AEC,d1
	btst	#3,$4(a3)
	beq.w	loc_00DAC0
	move.w	#$3B50,d1
loc_00DAC0:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	#$1500,$28(a3)
	btst	#3,$4(a3)
	bne.w	loc_00DAE0
	neg.w	$28(a3)
loc_00DAE0:
	cmpi.w	#$3B50,$58(a3)
	bne.w	loc_00DAEE
	neg.w	$28(a3)
loc_00DAEE:
	tst.w	$54(a3)
	beq.w	loc_00DAFA
	neg.w	$28(a3)
loc_00DAFA:
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DAFC:
	move.w	#$3C98,d1
	btst	#3,$4(a3)
	beq.w	loc_00DB0E
	move.w	#$3C34,d1
loc_00DB0E:
	tst.w	$54(a3)
	bne.w	loc_00DB20
	tst.w	(a3)
	bmi.w	loc_00DB38
	bra.w	loc_00DB26
loc_00DB20:
	tst.w	(a3)
	bpl.w	loc_00DB38
loc_00DB26:
	move.w	#$3C34,d1
	btst	#3,$4(a3)
	beq.w	loc_00DB38
	move.w	#$3C98,d1
loc_00DB38:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	#$1000,$28(a3)
	btst	#3,$4(a3)
	bne.w	loc_00DB58
	neg.w	$28(a3)
loc_00DB58:
	cmpi.w	#$3C98,$58(a3)
	bne.w	loc_00DB66
	neg.w	$28(a3)
loc_00DB66:
	tst.w	$54(a3)
	beq.w	loc_00DB72
	neg.w	$28(a3)
loc_00DB72:
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DB74:
	move.w	#$3CCA,d1
	btst	#3,$4(a3)
	beq.w	loc_00DB86
	move.w	#$3C66,d1
loc_00DB86:
	tst.w	$54(a3)
	bne.w	loc_00DB98
	tst.w	(a3)
	bmi.w	loc_00DBB0
	bra.w	loc_00DB9E
loc_00DB98:
	tst.w	(a3)
	bpl.w	loc_00DBB0
loc_00DB9E:
	move.w	#$3C66,d1
	btst	#3,$4(a3)
	beq.w	loc_00DBB0
	move.w	#$3CCA,d1
loc_00DBB0:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	#$1000,$28(a3)
	btst	#3,$4(a3)
	bne.w	loc_00DBD0
	neg.w	$28(a3)
loc_00DBD0:
	cmpi.w	#$3CCA,$58(a3)
	bne.w	loc_00DBDE
	neg.w	$28(a3)
loc_00DBDE:
	tst.w	$54(a3)
	beq.w	loc_00DBEA
	neg.w	$28(a3)
loc_00DBEA:
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DBEC:
	bsr.w	sub_00DC2C
	cmp.w	#$3E22,d1	; general form
	beq.w	sub_00DC00
	move.w	#$3FB8,d1
	bra.w	loc_00DC04


; ----------------------------------------------------------------------
; called from $00DBF4, $1E76D4, $1E76D8, $1E76DC
sub_00DC00:
	move.w	#$3F46,d1
loc_00DC04:
	jsr	(sub_01F3B2).l
	bsr.w	sub_00DCA8
	bset	#1,$63(a3)
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DC16:
	bsr.w	sub_00DC2C
	jsr	(sub_01F3B2).l
	bsr.w	sub_00DCA8
	bset	#1,$63(a3)
	rts


; ----------------------------------------------------------------------
; called from $00DBEC, $00DC16
sub_00DC2C:
	movem.l	d2-d4/a0/a1,-(sp)
	move.w	#$0,d2
	tst.w	(a3)
	bmi.w	loc_00DC4A
	tst.w	$14(a3)
	bmi.w	loc_00DC5A
	move.w	#$1,d2
	bra.w	loc_00DC5E
loc_00DC4A:
	tst.w	$14(a3)
	bpl.w	loc_00DC5E
	move.w	#$3,d2
	bra.w	loc_00DC5E
loc_00DC5A:
	move.w	#$2,d2
loc_00DC5E:
	movea.l	#dat_00DC88,a0
	ext.l	d2
	asl.w	#3,d2
	adda.l	d2,a0
	move.w	$54(a3),d3
	move.l	#dat_003E22,d1
	tst.b	$0(a0,d3.w)
	bne.w	loc_00DC82
	move.l	#dat_003EB4,d1
loc_00DC82:
	movem.l	(sp)+,d2-d4/a0/a1
	rts
dat_00DC88:
	dc.w	$0101,$0100,$0000,$0001,$0000,$0101,$0101,$0000
	dc.w	$0000,$0000,$0101,$0100,$0101,$0000,$0001,$0101


; ----------------------------------------------------------------------
; called from $00DC0A, $00DC20, $01F4E6, $01F4F2
sub_00DCA8:
	movem.l	d2/d3/a0/a1,-(sp)
	movea.l	#dat_00DCF2,a0
	cmpi.w	#$3E22,$58(a3)
	beq.w	loc_00DCCC
	cmpi.w	#$3FB8,$58(a3)
	beq.w	loc_00DCCC
	movea.l	#dat_00DD72,a0
loc_00DCCC:
	move.w	$5A(a3),d2
	ext.l	d2
	asl.w	#3,d2
	adda.l	d2,a0
	move.w	$54(a3),d3
	andi.w	#$7,d3
	asl.w	#2,d3
	move.w	$0(a0,d3.w),$28(a3)
	move.w	$2(a0,d3.w),$2A(a3)
	movem.l	(sp)+,d2/d3/a0/a1
	rts
dat_00DCF2:
	dc.w	$16DB,$16DB,$2000,$0000,$16DB,$E925,$0000,$E000
	dc.w	$E925,$E925,$E000,$0000,$E925,$16DB,$0000,$2000
	dc.w	$0000,$2000,$16DB,$16DB,$2000,$0000,$16DB,$E925
	dc.w	$0000,$E000,$E925,$E925,$E000,$0000,$E925,$16DB
	dc.w	$E925,$16DB,$0000,$2000,$16DB,$16DB,$2000,$0000
	dc.w	$16DB,$E925,$0000,$E000,$E925,$E925,$E000,$0000
	dc.w	$0000,$2000,$16DB,$16DB,$2000,$0000,$16DB,$E925
	dc.w	$0000,$E000,$E925,$E925,$E000,$0000,$E925,$16DB
dat_00DD72:
	dc.w	$E925,$16DB,$0000,$2000,$16DB,$16DB,$2000,$0000
	dc.w	$16DB,$E925,$0000,$E000,$E925,$E925,$E000,$0000
	dc.w	$0000,$2000,$16DB,$16DB,$2000,$0000,$16DB,$E925
	dc.w	$0000,$E000,$E925,$E925,$E000,$0000,$E925,$16DB
	dc.w	$16DB,$16DB,$2000,$0000,$16DB,$E925,$0000,$E000
	dc.w	$E925,$E925,$E000,$0000,$E925,$16DB,$0000,$2000
	dc.w	$0000,$2000,$16DB,$16DB,$2000,$0000,$16DB,$E925
	dc.w	$0000,$E000,$E925,$E925,$E000,$0000,$E925,$16DB


; ----------------------------------------------------------------------
; called from $00D728
sub_00DDF2:
	cmpi.w	#$3B82,$58(a3)
	beq.w	loc_00DE12
	move.w	#$3B82,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	jsr	(sub_01B3EC).l
loc_00DE12:
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DE14:
	move.w	#$3D3E,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	rts


; ----------------------------------------------------------------------
; called from $00D728
sub_00DE26:
	move.w	#$3DB0,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	rts


; ----------------------------------------------------------------------
; called from $00CD0A, $00CE62, $00D3AA
sub_00DE38:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_C394,a0
	move.w	(ram_DCEA).w,d0
	move.w	$0(a0,d0.w),d0
	bmi.w	loc_00DE6E
	move.w	#$1,d1
	btst	#6,$62(a3)
	beq.w	loc_00DE60
	move.w	#$2,d1
loc_00DE60:
	cmp.w	d1,d0
	bne.w	loc_00DE6E
	move.w	#$1,d0
	bra.w	loc_00DE72
loc_00DE6E:
	move.w	#$0,d0
loc_00DE72:
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $026FB2, $1D2A3C
sub_00DE78:
	tst.w	(ram_D294).w
	bmi.w	loc_00DE96
loc_00DE80:
	clr.w	(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	clr.w	(ram_D272).w
	rts
loc_00DE96:
	clr.w	(ram_D058).w
	clr.w	(ram_D05A).w
	btst	#6,(ram_C35C).w
	bne.w	loc_00DEAE
	move.w	#$1,(ram_C394).w
loc_00DEAE:
	btst	#7,(SysFlags).w
	beq.w	loc_00DECA
	move.w	(ram_C3AC).w,d0
	cmp.b	(ram_DDA2).w,d0
	beq.w	loc_00DECA
	move.w	#$2,(ram_C394).w
loc_00DECA:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_00DEE8
	cmpi.w	#$3,(ram_D270).w
	beq.w	loc_00DEE8
	cmpi.w	#$2,(ram_D270).w
	bne.w	loc_00DF0A
loc_00DEE8:
	move.w	(ram_CFD8).w,d0
	movea.l	#ram_CFDE,a0
	move.b	$0(a0,d0.w),d0
	move.w	#$1,(ram_C394).w
	cmp.w	(ram_C3AC).w,d0
	beq.w	loc_00DF0A
	move.w	#$2,(ram_C394).w
loc_00DF0A:
	btst	#6,(ram_C35C).w
	bne.w	loc_00DF20
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
loc_00DF20:
	bsr.w	sub_00E2D4
	bsr.w	sub_00E13C
	jsr	(sub_019BF0).l
	jsr	(sub_019BF0).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D330).w
loc_00DF44:
	move.w	(FrameCounter).w,d0
loc_00DF48:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_00DF48
	cmpi.w	#$5460,(ram_D330).w
	bge.w	loc_00DE80
	bsr.w	sub_00E59A
	tst.w	(ram_BF54).w
	beq.w	loc_00DF68
	clr.w	(ram_D330).w
loc_00DF68:
	btst	#7,(ram_BF55).w
	bne.w	loc_00E114
	move.w	#$1,d4
	tst.w	(FourWayPlay).w
	beq.w	loc_00DF96
	btst	#3,(ram_C350).w
	bne.w	loc_00DF96
	btst	#0,(ram_C34A).w
	bne.w	loc_00DF96
	move.w	#$3,d4
loc_00DF96:
	movea.l	#ram_C394,a0
	movea.l	#ram_BF49,a3
loc_00DFA2:
	move.b	(a3),d1
	btst	#2,d1
	beq.w	loc_00E014
	move.w	(a0),d0
	cmp.w	#$2,d0	; general form
	beq.w	loc_00E07A
	movea.l	#dat_00E12C,a4
	btst	#6,(ram_C35C).w
	beq.w	loc_00DFCC
	movea.l	#dat_00E130,a4
loc_00DFCC:
	move.b	$0(a4,d0.w),d0
	move.w	d0,(a0)
	btst	#3,(ram_C350).w
	beq.w	loc_00E002
	move.w	(ram_C394).w,d5
	cmp.w	(ram_C396).w,d5
	bne.w	loc_00E002
	lea	(ram_C3A4).w,a4
	subq.w	#1,d0
	lsl.w	#1,d0
	move.w	$0(a4,d0.w),d5
	bne.w	loc_00E002
	move.w	#$1,$0(a4,d0.w)
	bsr.w	sub_00E634
loc_00E002:
	move.w	(FrameCounter).w,d0
loc_00E006:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_00E006
	bsr.w	sub_00E13C
	bra.w	loc_00E108
loc_00E014:
	btst	#3,d1
	beq.w	loc_00E07A
	move.w	(a0),d0
	cmp.w	#$1,d0	; general form
	beq.w	loc_00E07A
	movea.l	#dat_00E134,a4
	btst	#6,(ram_C35C).w
	beq.w	loc_00E03C
	movea.l	#dat_00E138,a4
loc_00E03C:
	move.b	$0(a4,d0.w),d0
	move.w	d0,(a0)
	bsr.w	sub_00E13C
	btst	#3,(ram_C350).w
	beq.w	loc_00E076
	move.w	(ram_C394).w,d5
	cmp.w	(ram_C396).w,d5
	bne.w	loc_00E076
	lea	(ram_C3A4).w,a4
	subq.w	#1,d0
	lsl.w	#1,d0
	move.w	$0(a4,d0.w),d5
	bne.w	loc_00E076
	move.w	#$1,$0(a4,d0.w)
	bsr.w	sub_00E634
loc_00E076:
	bra.w	loc_00E108
loc_00E07A:
	btst	#3,(ram_C350).w
	beq.w	loc_00E108
	btst	#0,d1
	beq.w	loc_00E0C6
	move.w	(a0),d0
	beq.w	loc_00E108
	subq.w	#1,d0
	lsl.w	#1,d0
	lea	(ram_C3A4).w,a4
	move.w	$0(a4,d0.w),d5
	subq.w	#1,d5
	blt.w	loc_00E0C6
	move.w	d5,$0(a4,d0.w)
	move.w	(ram_C3A4).w,d6
	or.w	(ram_C3A6).w,d6
	bne.w	loc_00E0BE
	move.w	#$1,$0(a4,d0.w)
	bra.w	loc_00E108
loc_00E0BE:
	bsr.w	sub_00E634
	bra.w	loc_00E108
loc_00E0C6:
	btst	#1,d1
	beq.w	loc_00E108
	move.w	(a0),d0
	beq.w	loc_00E108
	subq.w	#1,d0
	lsl.w	#1,d0
	lea	(ram_C3A4).w,a4
	move.w	$0(a4,d0.w),d5
	cmp.w	#$2,d5	; general form
	bge.w	loc_00E108
	addq.w	#1,d5
	move.w	d5,$0(a4,d0.w)
	move.w	(ram_C3A4).w,d6
	or.w	(ram_C3A6).w,d6
	bne.w	loc_00E104
	move.w	#$1,$0(a4,d0.w)
	bra.w	loc_00E108
loc_00E104:
	bsr.w	sub_00E634
loc_00E108:
	addq.w	#2,a0
	addq.w	#2,a3
	dbra	d4,loc_00DFA2
	bra.w	loc_00DF44
loc_00E114:
	move.w	#$4,(ram_D272).w
	clr.w	(ram_B8B2).w
	move.l	(ram_C394).w,(ram_C39C).w
	move.l	(ram_C398).w,(ram_C3A0).w
	rts
dat_00E12C:
	dc.b	$02,$00,$02,$FF
dat_00E130:
	dc.b	$02,$02,$02,$FF
dat_00E134:
	dc.b	$01,$01,$00,$FF
dat_00E138:
	dc.b	$01,$01,$01,$FF


; ----------------------------------------------------------------------
; called from $00DF24, $00E00C, $00E042
sub_00E13C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$8,(TextY).w
	move.w	#$1,d4
	tst.w	(FourWayPlay).w
	beq.w	loc_00E16A
	btst	#0,(ram_C34A).w
	bne.w	loc_00E16A
	btst	#3,(ram_C350).w
	bne.w	loc_00E16A
	move.w	#$3,d4
loc_00E16A:
	movea.l	#ram_C394,a0
	move.w	#$0,d7
loc_00E174:
	move.w	(TextY).w,-(sp)
	move.w	#$10,(TextX).w
	tst.w	(a0)
	beq.w	loc_00E198
	move.w	#$1B,(TextX).w
	cmpi.w	#$1,(a0)
	beq.w	loc_00E198
	move.w	#$6,(TextX).w
loc_00E198:
	movem.l	d4/d7/a0,-(sp)
	add.w	d7,d7
	movea.l	#ram_C360,a0
	move.w	(TextX).w,d4
	cmp.w	$0(a0,d7.w),d4
	beq.w	loc_00E1FE
	move.w	d4,$0(a0,d7.w)
	movem.l	(sp)+,d4/d7/a0
	move.w	(TextX).w,-(sp)
	subq.w	#1,(TextY).w
	movea.l	#dat_00E2A8,a1
	bsr.w	sub_00E556
	addq.w	#1,(TextY).w
	bsr.w	sub_00E556
	addq.w	#1,(TextY).w
	bsr.w	sub_00E556
	addq.w	#1,(TextY).w
	bsr.w	sub_00E556
	jsr	(Text_Print).l
inl_00E1E8:
	dc.w	loc_00E1EE-inl_00E1E8
	dc.b	$BF,$00,$00,$00
loc_00E1EE:
	move.w	(sp)+,(TextX).w
	move.w	(sp)+,(TextY).w
	bsr.w	sub_00E218
	bra.w	loc_00E206
loc_00E1FE:
	movem.l	(sp)+,d4/d7/a0
	move.w	(sp)+,(TextY).w
loc_00E206:
	addq.w	#2,a0
	addq.w	#4,(TextY).w
	addq.w	#1,d7
	dbra	d4,loc_00E174
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00E1F6
sub_00E218:
	move.w	(TextX).w,-(sp)
	move.w	(TextY).w,-(sp)
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#dat_00E288,a0
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	move.w	(a0),d4
	movea.l	#ptrs_00E298,a0
	movea.l	$0(a0,d0.w),a0
	cmpi.w	#$10,(TextX).w
	bne.w	loc_00E252
	movea.l	#Art_1B4AFE,a0
	move.w	(ram_B8BA).w,d4
loc_00E252:
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	addq.w	#1,(TextX).w
	clr.w	d1
	subq.w	#1,(TextY).w
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$0,d5
	movea.l	#NullEntry,a2
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a6
	move.w	(sp)+,(TextY).w
	move.w	(sp)+,(TextX).w
	rts
dat_00E288:
	dc.w	$FFFF,$B8B2,$FFFF,$B8B4,$FFFF,$B8B6,$FFFF,$B8B8

ptrs_00E298:
	dc.l	Art_1B3486
	dc.l	Art_1B3A24
	dc.l	Art_1B3FC2
	dc.l	Art_1B4560
dat_00E2A8:
	dc.b	$00,$2C,$FD,$00
	dc.b	"                                        "


; ----------------------------------------------------------------------
; called from $00DF20
sub_00E2D4:
	move.l	#VBlank_Main2,(VBlankVector).l
	move.w	#$2500,sr
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B400,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_00E34E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_00E356:
	move.l	#Font_Menu,(FontPtr).l
	move.w	d4,(ram_B016).w
	lea	(Font_Narrow_Tiles).l,a2
	jsr	(Draw_RunScript).l
inl_00E370:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_00E378:
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Narrow,(FontPtr2).l
	move.w	d4,(ram_B020).w
	lea	(Art_1AAD96_Tiles).l,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B8BA).w
	movea.l	#Art_1B4AFE_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,-(sp)
	jsr	(Text_Print).l
inl_00E3B0:
	dc.w	loc_00E3B6-inl_00E3B0
	dc.b	$BF,$00,$0A,$00
loc_00E3B6:
	movea.l	#Art_1B4AFE,a0
	move.w	(ram_B8BA).w,d4
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	addq.w	#1,(TextX).w
	clr.w	d1
	subq.w	#1,(TextY).w
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$2,d5
	movea.l	#NullEntry,a2
	jsr	(TileMap_Draw).l
	move.w	(sp)+,d4
	move.w	d4,(ram_B8B2).w
	movea.l	#Art_1B3486_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B8B4).w
	movea.l	#Art_1B3A24_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B8B6).w
	movea.l	#Art_1B3FC2_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B8B8).w
	movea.l	#Art_1B4560_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_00E430:
	dc.w	loc_00E438-inl_00E430
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_00E438:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_00E44C:
	dc.w	loc_00E452-inl_00E44C
	dc.b	$FE,$00,$00,$00
loc_00E452:
	movea.l	#Art_PlayoffLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$9,d5
	jsr	(TileMap_Draw).l
	btst	#3,(ram_C350).w
	beq.w	loc_00E4A0
	jsr	(Text_PrintNarrow).l
inl_00E480:
	dc.w	loc_00E48E-inl_00E480
	dc.b	$F8,$04,$01,$12,$14
	dc.b	"SKATERS"
loc_00E48E:
	move.w	#$2,(ram_C3A4).w
	move.w	#$2,(ram_C3A6).w
	jsr	(sub_00E634).l
loc_00E4A0:
	jsr	(Text_Print).l
inl_00E4A6:
	dc.w	loc_00E4AC-inl_00E4A6
	dc.b	$BF,$06,$04,$00
loc_00E4AC:
	move.w	(ram_C3AE).w,d7
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	jsr	(Text_Print).l
inl_00E4C0:
	dc.w	loc_00E4C6-inl_00E4C0
	dc.b	$BF,$18,$04,$00
loc_00E4C6:
	move.w	(ram_C3AC).w,d7
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	(FrameCounter).w,d0
loc_00E4D8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_00E4D8
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_00E4EA:
	dc.w	loc_00E500-inl_00E4EA
	dc.b	$FF,$05,$01
	dc.b	"CONTROLLER SETUP",0
loc_00E500:
	btst	#3,(ram_C350).w
	bne.w	loc_00E528
	jsr	(Text_PrintFont).l
inl_00E510:
	dc.w	loc_00E524-inl_00E510
	dc.b	$BF,$0F,$1A
	dc.b	"[] select team",0
loc_00E524:
	bra.w	loc_00E554
loc_00E528:
	jsr	(Text_PrintFont).l
inl_00E52E:
	dc.w	loc_00E554-inl_00E52E
	dc.b	$BF,$06,$1A
	dc.b	"[]select team {}change # players",0
loc_00E554:
	rts


; ----------------------------------------------------------------------
; called from $00E1C6, $00E1CE, $00E1D6, $00E1DE
sub_00E556:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	a1,-(sp)
	jsr	(Text_PrintCmd).l
inl_00E562:
	dc.w	loc_00E56A-inl_00E562
	dc.b	$FE,$05,$FF,$01,$F9,$00
loc_00E56A:
	movea.l	(sp)+,a1
	jsr	(Text_PrintCmd_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$48E7,$FFFE,$2F09,$4EB9,$0002,$0A7E,$0008,$FE05
	dc.w	$FF01,$F901,$225F,$4EB9,$0002,$0A90,$4CDF,$7FFF
	dc.w	$4E75


; ----------------------------------------------------------------------
; called from $00DF58, $1D29E8, $1D2CC0, $1D358E
sub_00E59A:
	jsr	(Joypad_Read1).l
	jsr	(Joypad_DpadFilter).l
	move.w	d1,(ram_BF48).w
	jsr	(Joypad_Read2).l
	jsr	(Joypad_DpadFilter).l
	move.w	d1,(ram_BF4A).w
	tst.w	(FourWayPlay).w
	beq.w	loc_00E5E2
	jsr	(Joypad_Read3).l
	jsr	(Joypad_DpadFilter).l
	move.w	d1,(ram_BF4C).w
	jsr	(Joypad_Read4).l
	jsr	(Joypad_DpadFilter).l
	move.w	d1,(ram_BF4E).w
loc_00E5E2:
	move.w	(ram_BF48).w,d1
	or.w	(ram_BF4A).w,d1
	tst.w	(FourWayPlay).w
	beq.w	loc_00E5FA
	or.w	(ram_BF4C).w,d1
	or.w	(ram_BF4E).w,d1
loc_00E5FA:
	move.w	d1,(ram_BF54).w
	rts


; ----------------------------------------------------------------------
sub_00E600:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#6,(ram_C35C).w
	move.w	#$FFFF,(ram_C360).w
	move.w	#$FFFF,(ram_C362).w
	move.w	#$FFFF,(ram_C364).w
	move.w	#$FFFF,(ram_C366).w
	jsr	(sub_1D2A34).l
	bclr	#6,(ram_C35C).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00DFFE, $00E072, $00E0BE, $00E104, $00E49A
sub_00E634:
	move.w	#$0,(ram_DDF2).w
	move.w	#$3,(ram_DDF4).w
	move.w	#$1,(ram_DDF6).w
	move.w	#$C,(ram_DDF8).w
	move.w	#$14,(ram_DDFA).w
	lea	(ram_DDFC).w,a0
	move.w	(ram_C3A6).w,d0
	jsr	(sub_1E0286).l
	jsr	(sub_1E0196).l
	move.w	#$1D,(ram_DDF8).w
	move.w	(ram_C3A4).w,d0
	jsr	(sub_1E0286).l
	jsr	(sub_1E0196).l
	rts


; ----------------------------------------------------------------------
; sets up the I/O ports and detects an EA 4-Way Play adapter on port 2 (ram_FourWayPlay)
; called from $018FBC
Joypad_InitPorts:
	move.w	#$0,(Z80_RESET).l
	move.b	#$40,(IO_CTRL1).l
	move.b	#$43,(IO_CTRL2).l
	nop
	move.b	#$7C,(IO_DATA2).l
	nop
	move.b	#$7F,(IO_CTRL2).l
	nop
	move.b	#$7C,(IO_DATA2).l
	nop
	move.b	(IO_DATA1).l,d0
	andi.b	#$3,d0
	cmp.b	#$0,d0	; general form
	bne.s	loc_00E6CE
	move.w	#$1,(FourWayPlay).w
	bra.s	loc_00E6DC
loc_00E6CE:
	move.w	#$0,(FourWayPlay).w
	move.b	#$40,(IO_CTRL2).l
loc_00E6DC:
	move.w	#$100,(Z80_RESET).l
	rts


; ----------------------------------------------------------------------
; selects pad 1 on the 4-Way Play and reads it
Joypad_Read4Way1:
	move.b	#$0,(IO_DATA2).l
	move.w	(ram_BF34).w,(ram_BF30).w
	jsr	(Joypad_Read1).l
	move.w	(ram_BF30).w,(ram_BF34).w
	rts


; ----------------------------------------------------------------------
Joypad_Read4Way2:
	move.b	#$10,(IO_DATA2).l
	move.w	(ram_BF36).w,(ram_BF30).w
	jsr	(Joypad_Read1).l
	move.w	(ram_BF30).w,(ram_BF36).w
	rts


; ----------------------------------------------------------------------
Joypad_Read4Way3:
	move.b	#$20,(IO_DATA2).l
	move.w	(ram_BF38).w,(ram_BF30).w
	jsr	(Joypad_Read1).l
	move.w	(ram_BF30).w,(ram_BF38).w
	rts


; ----------------------------------------------------------------------
Joypad_Read4Way4:
	move.b	#$30,(IO_DATA2).l
	move.w	(ram_BF3A).w,(ram_BF30).w
	jsr	(Joypad_Read1).l
	move.w	(ram_BF30).w,(ram_BF3A).w
	rts


; ----------------------------------------------------------------------
; called from $022CF6
sub_00E756:
	tst.w	(ram_D282).w
	bne.w	loc_00E912
	btst	#5,(SysFlags).w
	bne.w	loc_00EA3C
	tst.w	(ram_C4C8).w
	beq.w	loc_00EA3C
	cmpi.w	#$A,$32(a3)
	blt.w	loc_00EA3C
	cmpi.w	#$A,$32(a2)
	blt.w	loc_00EA3C
	btst	#5,$62(a3)
	bne.w	loc_00EA3C
	btst	#5,$62(a2)
	bne.w	loc_00EA3C
	btst	#4,$63(a3)
	bne.w	loc_00EA3C
	btst	#4,$63(a2)
	bne.w	loc_00EA3C
	tst.w	$34(a3)
	beq.w	loc_00EA3C
	tst.w	$34(a2)
	beq.w	loc_00EA3C
	btst	#0,(ram_C33A).w
	bne.w	loc_00EA3C
	btst	#0,(ram_B7C3).w
	bne.w	loc_00EA3C
	cmpi.w	#$10A,$14(a3)
	bgt.w	loc_00EA3C
	cmpi.w	#$10A,$14(a3)
	bgt.w	loc_00EA3C
	movem.l	d0-d4/a0-a3,-(sp)
	movea.w	#$B760,a0
	move.w	$36(a0),d0
	cmpi.b	#$1B,$38(a0,d0.w)
	beq.w	loc_00E90E
	move.w	(ram_C4D0).w,d0
	cmp.w	#$64,d0	; general form
	blt.w	loc_00E90E
	bsr.w	sub_00E986
	exg	a2,a3
	bsr.w	sub_00E986
	exg	a2,a3
	btst	#0,$63(a3)
	beq.w	loc_00E90E
	clr.w	(ram_C4D0).w
	moveq	#$1B,d0
	movea.w	#$C862,a0
loc_00E826:
	clr.b	$39E(a0)
	clr.b	(a0)+
	dbra	d0,loc_00E826
	addi.w	#$3E8,(ram_B8B4).w
	addi.w	#$23,(ram_B8BA).w
	clr.w	(ram_DD08).w
	clr.l	(ram_DCFE).w
	clr.l	(ram_DD02).w
	bclr	#1,(ram_C354).w
	bclr	#2,(ram_C354).w
	bclr	#2,(ram_C33C).w
	bclr	#3,(ram_C33C).w
	move.w	$52(a3),(ram_B7C0).w
	move.w	$14(a3),d1
	add.w	$14(a2),d1
	asr.w	#1,d1
	move.w	d1,(ram_BFE0).w
	bset	#2,(ram_C33E).w
	bset	#6,(ram_C33C).w
	moveq	#$2,d1
	move.w	(a3),d0
	cmp.w	(a2),d0
	blt.w	loc_00E88E
	eori.w	#$7,d1
loc_00E88E:
	move.w	d1,$54(a3)
	eori.w	#$7,d1
	move.w	d1,$54(a2)
	move.l	a3,-(sp)
	bsr.w	sub_00E914
	exg	a2,a3
	bsr.w	sub_00E914
	movea.w	#$B060,a3
	move.l	#$15,d0
	moveq	#$B,d1
loc_00E8B2:
	btst	#0,$63(a3)
	bne.w	loc_00E8EA
	tst.w	$34(a3)
	beq.w	loc_00E8EA
	btst	#2,$63(a3)
	bne.w	loc_00E8EA
	movem.w	d0,-(sp)
	move.w	$36(a3),d0
	cmpi.b	#$D,$38(a3,d0.w)
	movem.w	(sp)+,d0
	beq.w	loc_00E8EA
	jsr	(sub_01F168).l
loc_00E8EA:
	adda.w	#$80,a3
	dbra	d1,loc_00E8B2
	movea.w	#$B760,a3
	bset	#0,$63(a3)
	move.l	#$1A,d0
	jsr	(sub_01F168).l
	st	(ram_BFF0).w
	movea.l	(sp)+,a3
loc_00E90E:
	movem.l	(sp)+,d0-d4/a0-a3
loc_00E912:
	rts


; ----------------------------------------------------------------------
; called from $00E89C, $00E8A2
sub_00E914:
	move.w	$52(a2),$2E(a3)
	move.w	#$2E,d0
	jsr	(sub_02135E).l
	move.w	#$140,(ram_C3F4).w
	clr.w	(ram_DCFC).w
	move.w	$52(a3),d0
	jsr	(sub_024BAA).l
	move.l	#$14,d0
	jsr	(sub_01F168).l
	bclr	#3,$4(a3)
	move.w	#$FC00,d1
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00E960
	bset	#3,$4(a3)
	neg.w	d1
loc_00E960:
	move.w	d1,$28(a3)
	bset	#2,$63(a3)
	bclr	#1,$63(a3)
	bset	#5,$63(a3)
	bclr	#5,$62(a3)
	move.w	#$31D8,d1
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $00E806, $00E80C
sub_00E986:
	cmpi.b	#$1,$75(a3)
	blt.w	loc_00EA3C
	cmpi.b	#$1,$75(a2)
	blt.w	loc_00EA3C
	clr.w	d1
	move.b	$67(a2),d1
	movea.w	#$C732,a0
	btst	#6,$62(a2)
	beq.w	loc_00E9B2
	adda.w	#$39E,a0
loc_00E9B2:
	adda.w	d1,a0
	move.b	$130(a0),d1
	asl.b	#1,d1
	neg.b	d1
	addi.b	#$10,d1
	cmp.b	$75(a2),d1
	bset	#0,$63(a2)
	bset	#0,$63(a3)
	bne.w	loc_00EA3C
	rts


; ----------------------------------------------------------------------
sub_00E9D6:
	tst.w	(ram_D27E).w
	beq.w	loc_00EA3C
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	bne.w	loc_00EA3C
	movea.l	a3,a4
	moveq	#$5,d0
	movea.w	#$B060,a3
	btst	#6,$62(a4)
	beq.w	loc_00EA02
	adda.w	#$300,a3
loc_00EA02:
	cmpa.w	a3,a4
	beq.w	loc_00EA32
	tst.w	$34(a3)
	ble.w	loc_00EA32
	btst	#4,$63(a3)
	bne.w	loc_00EA32
	btst	#2,$63(a3)
	bne.w	loc_00EA32
	move.w	#$2A,d0
	jsr	(sub_02135E).l
	movea.l	a4,a3
	rts
loc_00EA32:
	adda.w	#$80,a3
	dbra	d0,loc_00EA02
	movea.l	a4,a3
loc_00EA3C:
	rts


; ----------------------------------------------------------------------
; called from $00F64E
sub_00EA3E:
	btst	#5,$62(a3)
	bne.s	loc_00EA3C
	tst.w	(ram_C3F4).w
	bpl.w	loc_00EA54
	jmp	(loc_01BE3A).l
loc_00EA54:
	bclr	#1,$62(a3)
	beq.w	loc_00EA8C
	bclr	#7,(ram_C358).w
	clr.w	d0
	move.b	$75(a3),d0
	add.w	d0,d0
	addq.w	#3,d0
	move.w	d0,$44(a3)
	clr.w	$42(a3)
	move.w	#$FFFF,$46(a3)
	cmpi.w	#$2,$54(a3)
	bne.w	loc_00EA8C
	move.w	#$5A,$46(a3)
loc_00EA8C:
	sub.w	d7,$46(a3)
	bcc.w	loc_00EA98
	bsr.w	sub_00F17C
loc_00EA98:
	tst.w	$44(a3)
	bmi.s	loc_00EA3C
	move.w	$2E(a3),d0
	asl.w	#7,d0
	movea.w	#$B060,a0
	adda.w	d0,a0
	move.w	(a3),d0
	add.w	(a0),d0
	asr.w	#1,d0
	move.w	d0,(ram_BFDE).w
	btst	#3,$62(a3)
	bne.w	loc_00EBA2
	bset	#1,$63(a3)
	bne.w	loc_00EBA2
	cmpi.w	#$31D8,$58(a3)
	bne.w	loc_00EAEA
	cmpi.w	#$3E8,(ram_BF18).w
	bne.w	loc_00EAE6
	cmpi.w	#$3E8,(ram_BF16).w
	beq.w	loc_00EAEA
loc_00EAE6:
	bsr.w	sub_00F11E
loc_00EAEA:
	btst	#1,(ram_C354).w
	bne.w	loc_00EC44
	tst.w	$58(a3)
	bne.w	loc_00EB06
	move.w	#$321A,d1
	jsr	(sub_01F3B2).l
loc_00EB06:
	move.w	(a3),d0
	sub.w	(a0),d0
	move.w	$28(a3),d1
	asr.w	#8,d1
	add.w	d1,d0
	move.w	$28(a0),d1
	asr.w	#8,d1
	sub.w	d1,d0
	cmp.w	#$16,d0	; general form
	bgt.w	loc_00EBA2
	cmp.w	#$FFEA,d0	; general form
	blt.w	loc_00EBA2
	cmpi.w	#$3E8,(ram_BF16).w
	beq.w	loc_00EBA2
	cmpi.w	#$3E8,(ram_BF18).w
	beq.w	loc_00EBA2
	move.w	(a3),d1
	sub.w	(a0),d1
	bpl.w	loc_00EB48
	neg.w	d1
loc_00EB48:
	move.w	(ram_DD08).w,d0
	subq.w	#1,d0
	move.w	d0,(ram_DD08).w
	bpl.w	loc_00EBA2
	move.w	#$1,d0
	jsr	(Random).l
	move.w	d0,(ram_DD08).w
	moveq	#$8,d0
	jsr	(Random).l
	cmp.w	#$1,d0	; general form
	bls.w	loc_00EB78
	andi.w	#$1,d0
loc_00EB78:
	asl.w	#1,d0
	bra.w	loc_00EB94


; ----------------------------------------------------------------------
sub_00EB7E:
	moveq	#$8,d0
	jsr	(Random).l
	cmp.w	#$2,d0	; general form
	bls.w	loc_00EB92
	andi.w	#$1,d0
loc_00EB92:
	asl.w	#1,d0
loc_00EB94:
	lea	sub_00EC3E(pc),a1
	move.w	$0(a1,d0.w),d1
	jsr	(sub_01F3B2).l
loc_00EBA2:
	bsr.w	sub_00ECC4
	btst	#1,(ram_C354).w
	bne.w	loc_00EC26
	cmpi.w	#$31D8,$58(a3)
	beq.w	loc_00EBEC
	cmpi.w	#$325C,$58(a3)
	beq.w	loc_00EBEC
	btst	#3,$62(a3)
	bne.w	loc_00EBEC
	move.w	(ram_BFDE).w,d0
	addi.w	#$A,d0
	cmpi.w	#$2,$54(a3)
	bne.w	loc_00EBE4
	subi.w	#$14,d0
loc_00EBE4:
	sub.w	(a3),d0
	asl.w	#5,d0
	add.w	d0,$28(a3)
loc_00EBEC:
	move.w	(ram_BFE0).w,d1
	sub.w	$14(a3),d1
	asl.w	#8,d1
	cmp.w	#$1000,d1	; general form
	blt.w	loc_00EC02
	move.w	#$1000,d1
loc_00EC02:
	cmp.w	#$F000,d1	; general form
	bgt.w	loc_00EC0E
	move.w	#$F000,d1
loc_00EC0E:
	move.w	d1,$2A(a3)
	tst.w	$58(a3)
	bne.w	loc_00EC24
	move.w	#$321A,d1
	jsr	(sub_01F3B2).l
loc_00EC24:
	rts
loc_00EC26:
	bsr.w	sub_00EC72
	tst.w	$58(a3)
	bne.w	loc_00EC3C
	move.w	#$32F0,d1
	jsr	(sub_01F3B2).l
loc_00EC3C:
	rts


; ----------------------------------------------------------------------
; called from $00EB94
sub_00EC3E:
	move.w	d0,($33FA33C0).l
loc_00EC44:
	bsr.w	sub_00EC72
	moveq	#$8,d0
	jsr	(Random).l
	andi.w	#$3,d0
	asl.w	#1,d0
	lea	dat_00EC6A(pc),a1
	move.w	$0(a1,d0.w),d1
	jsr	(sub_01F3B2).l
	bsr.w	sub_00ECC4
	rts
dat_00EC6A:
	dc.w	$3386,$346E,$3386,$346E


; ----------------------------------------------------------------------
; called from $00EC26, $00EC44
sub_00EC72:
	clr.w	$2A(a3)
	clr.w	$28(a3)
	movem.l	d0,-(sp)
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$18,d0	; general form
	bgt.w	loc_00EC98
	cmp.w	#$FFE8,d0	; general form
	blt.w	loc_00EC98
loc_00EC92:
	movem.l	(sp)+,d0
	rts
loc_00EC98:
	asl.w	#5,d0
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00ECB0
	tst.w	d0
	bmi.w	loc_00ECB8
	neg.w	d0
	bra.w	loc_00ECB8
loc_00ECB0:
	tst.w	d0
	bpl.w	loc_00ECB8
	neg.w	d0
loc_00ECB8:
	move.w	d0,$28(a3)
	neg.w	d0
	move.w	d0,$28(a0)
	bra.s	loc_00EC92


; ----------------------------------------------------------------------
; called from $00EBA2, $00EC64
sub_00ECC4:
	movem.l	d0/a0-a3,-(sp)
	move.w	$6(a3),d0
	cmp.w	$8(a3),d0
	beq.w	loc_00EDDC
	btst	#1,(ram_C354).w
	bne.w	loc_00EDE2
	cmp.w	#$5EA,d0	; general form
	beq.w	loc_00EF48
	btst	#3,$62(a0)
	beq.w	loc_00ED1C
	btst	#3,$62(a3)
	beq.w	loc_00ED1C
	cmpi.w	#$2,$54(a0)
	beq.w	loc_00ED12
	btst	#1,(ram_DD0A).w
	bne.w	loc_00EDDC
	bra.w	loc_00ED1C
loc_00ED12:
	btst	#0,(ram_DD0A).w
	bne.w	loc_00EDDC
loc_00ED1C:
	cmpi.w	#$34A8,$58(a0)
	beq.w	loc_00EDDC
	cmpi.w	#$34E2,$58(a0)
	beq.w	loc_00EDDC
	cmpi.w	#$351C,$58(a0)
	beq.w	loc_00EDDC
	cmpi.w	#$3556,$58(a0)
	beq.w	loc_00EDDC
	cmpi.w	#$3590,$58(a0)
	beq.w	loc_00EDDC
	cmpi.w	#$35CA,$58(a0)
	beq.w	loc_00EDDC
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$16,d0	; general form
	bgt.w	loc_00EDDC
	cmp.w	#$FFEA,d0	; general form
	blt.w	loc_00EDDC
	tst.w	d0
	bpl.w	loc_00ED74
	neg.w	d0
loc_00ED74:
	cmp.w	#$8,d0	; general form
	blt.w	loc_00EDDC
	move.w	$14(a3),d0
	sub.w	$14(a0),d0
	cmp.w	#$8,d0	; general form
	bgt.w	loc_00EDDC
	cmp.w	#$FFF8,d0	; general form
	blt.w	loc_00EDDC
	cmpi.w	#$3E8,(ram_BF16).w
	beq.w	loc_00EDDC
	cmpi.w	#$3E8,(ram_BF18).w
	beq.w	loc_00EDDC
	move.w	$6(a3),d0
	cmp.w	#$5F6,d0	; general form
	beq.w	loc_00EFD8
	cmp.w	#$5FA,d0	; general form
	beq.w	loc_00EFD8
	cmp.w	#$606,d0	; general form
	beq.w	loc_00F02A
	cmp.w	#$60A,d0	; general form
	beq.w	loc_00F02A
	cmp.w	#$613,d0	; general form
	beq.w	loc_00EF9C
	cmp.w	#$617,d0	; general form
	beq.w	loc_00EF9C
loc_00EDDC:
	movem.l	(sp)+,d0/a0-a3
	rts
loc_00EDE2:
	btst	#2,(ram_C354).w
	beq.w	loc_00EE1C
	move.w	(ram_DD06).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_00EE1C
	move.w	#$379A,d1
	jsr	(sub_01F3B2).l
	move.w	#$37D0,d1
	exg	a0,a3
	jsr	(sub_01F3B2).l
	bsr.w	sub_00F0A4
	move.w	#$B4,(ram_C3F4).w
	bra.w	loc_00F0FA
loc_00EE1C:
	cmpi.w	#$363E,$58(a0)
	beq.s	loc_00EDDC
	cmpi.w	#$3678,$58(a0)
	beq.s	loc_00EDDC
	cmpi.w	#$36B2,$58(a0)
	beq.s	loc_00EDDC
	cmpi.w	#$36EC,$58(a0)
	beq.s	loc_00EDDC
	cmpi.w	#$3726,$58(a0)
	beq.s	loc_00EDDC
	cmpi.w	#$3760,$58(a0)
	beq.s	loc_00EDDC
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$1E,d0	; general form
	bgt.s	loc_00EDDC
	cmp.w	#$FFE2,d0	; general form
	blt.s	loc_00EDDC
	move.w	$6(a3),d0
	cmp.w	#$61D,d0	; general form
	beq.w	loc_00EE84
	cmp.w	#$621,d0	; general form
	beq.w	loc_00EE84
	cmp.w	#$62E,d0	; general form
	beq.w	loc_00EED6
	cmp.w	#$632,d0	; general form
	beq.w	loc_00EED6
	bra.w	loc_00EDDC
loc_00EE84:
	exg	a0,a3
	bsr.w	sub_00EF28
	bset	#1,$63(a3)
	subq.w	#1,$44(a3)
	bmi.w	loc_00F0EE
	movem.l	d0/a0,-(sp)
	movea.l	#dat_00EECE,a0
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$3,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	movem.l	(sp)+,d0/a0
	jsr	(sub_01F3B2).l
	move.w	#$9,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_00EDDC
dat_00EECE:
	dc.w	$363E,$3678,$36B2,$363E
loc_00EED6:
	exg	a0,a3
	bsr.w	sub_00EF28
	bset	#1,$63(a3)
	subq.w	#1,$44(a3)
	bmi.w	loc_00F0EE
	movem.l	d0/a0,-(sp)
	movea.l	#sub_00EF20,a0
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$3,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	movem.l	(sp)+,d0/a0
	jsr	(sub_01F3B2).l
	move.w	#$A,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_00EDDC


; ----------------------------------------------------------------------
; called from $00EEEE
sub_00EF20:
	move.w	$3726(a4),(a3)+
	move.w	-(a0),$36EC(a3)

; ----------------------------------------------------------------------
; called from $00EE86, $00EED8
sub_00EF28:
	addi.w	#$100,(ram_B8B4).w
	addi.w	#$40,(ram_B8BA).w
	move.w	#$3,d0
	cmpi.w	#$2,$54(a3)
	bne.w	loc_00EF44
	neg.w	d0
loc_00EF44:
	add.w	d0,(a3)
	rts
loc_00EF48:
	bclr	#5,$63(a3)
	move.w	(ram_BFDE).w,d0
	cmp.w	#$5A,d0	; general form
	blt.w	loc_00EF5C
	moveq	#$5A,d0
loc_00EF5C:
	cmp.w	#$FFA6,d0	; general form
	bgt.w	loc_00EF66
	moveq	#-$5A,d0
loc_00EF66:
	asr.w	#2,d0
	bne.w	loc_00EF6E
	addq.w	#1,d0
loc_00EF6E:
	movem.l	a0,-(sp)
	movea.l	#ram_BF16,a0
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00EF88
	movea.l	#ram_BF18,a0
loc_00EF88:
	move.b	d0,(a0)
	move.w	(ram_BFE0).w,d0
	asr.w	#2,d0
	move.b	d0,$1(a0)
	movem.l	(sp)+,a0
	bra.w	loc_00EDDC
loc_00EF9C:
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_00EDDC
	cmp.w	#$FFE2,d0	; general form
	blt.w	loc_00EDDC
	bset	#1,(ram_C354).w
	bset	#2,$62(a3)
	bset	#2,$62(a0)
	exg	a0,a3
	bset	#1,$63(a3)
	move.w	#$332A,d1
	jsr	(sub_01F3B2).l
	bra.w	loc_00EDDC
loc_00EFD8:
	exg	a0,a3
	bsr.w	sub_00F07C
	bset	#1,$63(a3)
	subq.w	#1,$44(a3)
	bmi.w	loc_00F0EE
	movem.l	d0/a0,-(sp)
	movea.l	#dat_00F022,a0
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$3,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	movem.l	(sp)+,d0/a0
	jsr	(sub_01F3B2).l
	move.w	#$9,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_00EDDC
dat_00F022:
	dc.w	$34A8,$34E2,$351C,$34A8
loc_00F02A:
	exg	a0,a3
	bsr.w	sub_00F07C
	bset	#1,$63(a3)
	subq.w	#1,$44(a3)
	bmi.w	loc_00F0EE
	movem.l	d0/a0,-(sp)
	movea.l	#dat_00F074,a0
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$3,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	movem.l	(sp)+,d0/a0
	jsr	(sub_01F3B2).l
	move.w	#$A,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_00EDDC
dat_00F074:
	dc.w	$3556,$3590,$35CA,$3556


; ----------------------------------------------------------------------
; called from $00EFDA, $00F02C
sub_00F07C:
	addi.w	#$100,(ram_B8B4).w
	addi.w	#$40,(ram_B8BA).w
	moveq	#$5,d0
	add.w	$44(a0),d0
	mulu.w	#$0,d0
	cmpi.w	#$2,$54(a3)
	bne.w	loc_00F09E
	neg.w	d0
loc_00F09E:
	add.w	d0,$28(a3)
	rts


; ----------------------------------------------------------------------
; called from $00EE0E, $00F0EE
sub_00F0A4:
	movem.l	a1,-(sp)
	movea.w	#$C3B0,a1
loc_00F0AC:
	addq.w	#2,a1
	cmpi.b	#$26,(a1)
	bne.s	loc_00F0AC
	move.b	$1(a1),d0
	andi.w	#$F,d0
	cmp.w	$52(a0),d0
	bne.s	loc_00F0AC
	move.b	#$28,(a1)
	movem.l	(sp)+,a1
	move.w	#$9,-(sp)
	jsr	(sub_09205A).l
	move.w	#$3C,(ram_C3F4).w
	move.w	#$FFFF,$44(a0)
	addi.w	#$300,(ram_B8B4).w
	addi.w	#$80,(ram_B8BA).w
	rts
loc_00F0EE:
	bsr.s	sub_00F0A4
	move.w	#$3806,d1
	jsr	(sub_01F3B2).l
loc_00F0FA:
	movea.w	#$C732,a2
	move.w	#$B,-(sp)
	btst	#6,$62(a3)
	bne.w	loc_00F114
	lea	$39E(a2),a2
	move.w	#$C,(sp)
loc_00F114:
	jsr	(sub_092172).l
	bra.w	loc_00EDDC


; ----------------------------------------------------------------------
; called from $00EAE6, $00F4DA
sub_00F11E:
	movem.l	d0-d3,-(sp)
	clr.w	$28(a3)
	addq.w	#1,(ram_DCFC).w
	move.w	#$325C,d1
	jsr	(sub_01F3B2).l
	cmpi.w	#$2,(ram_DCFC).w
	beq.w	loc_00F148
	move.w	#$140,(ram_C3F4).w
	bra.w	loc_00F152
loc_00F148:
	bsr.w	sub_00F5D2
	bset	#5,(SysFlags).w
loc_00F152:
	movem.l	(sp)+,d0-d3
	rts


; ----------------------------------------------------------------------
; called from $021500, $021C94
sub_00F158:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_00F162:
	dc.w	loc_00F168-inl_00F162
	dc.b	$BF,$00,$01,$00
loc_00F168:
	moveq	#$28,d0
	moveq	#$5,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00EA94
sub_00F17C:
	movem.l	d0-d3/a0-a4,-(sp)
	movea.w	#$C732,a2
	jsr	(sub_01283A).l
	adda.w	#$39E,a2
	jsr	(sub_01283A).l
	jsr	(sub_0284C2).l
	movea.w	#$C3B2,a0
	clr.w	d2
loc_00F1A0:
	tst.w	(a0)+
	bne.s	loc_00F1A0
	move.b	-$3(a0),d0
	clr.b	d3
	bsr.w	sub_00F21C
	neg.b	d3
	move.b	-$5(a0),d0
	bsr.w	sub_00F21C
	jsr	(Text_Print).l
inl_00F1BE:
	dc.w	loc_00F1C4-inl_00F1BE
	dc.b	$BF,$0F,$01,$00
loc_00F1C4:
	move.w	d2,d0
	lsr.w	#1,d2
	sub.w	d2,(TextX).w
	moveq	#$5,d1
	jsr	(Text_PrintDigitsBig).l
	move.w	#$2,(TextY).w
	tst.b	d3
	bmi.w	loc_00F1E6
	move.w	#$4,(TextY).w
loc_00F1E6:
	move.b	-$3(a0),d0
	bsr.w	sub_00F21C
	jsr	(Text_Print_Worker).l
	eori.w	#$6,(TextY).w
	move.b	-$5(a0),d0
	bsr.w	sub_00F21C
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_00F20E:
	dc.w	loc_00F216-inl_00F20E
	dc.b	$BF,$0F,$03,$76,$73,$00
loc_00F216:
	movem.l	(sp)+,d0-d3/a0-a4
	rts


; ----------------------------------------------------------------------
; called from $00F1AA, $00F1B4, $00F1EA, $00F1FE
sub_00F21C:
	movea.w	#$B060,a1
	andi.w	#$F,d0
	asl.w	#7,d0
	add.b	$75(a1,d0.w),d3
	movea.w	#$C732,a2
	btst	#6,$62(a1,d0.w)
	beq.w	loc_00F23C
	adda.w	#$39E,a2
loc_00F23C:
	move.b	$67(a1,d0.w),d0
	ext.w	d0
	jsr	(sub_0284FC).l
	movea.w	a1,a3
	jsr	(Text_AppendInline).l
inl_00F250:
	dc.w	loc_00F254-inl_00F250
	dc.b	$20,$00
loc_00F254:
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	jsr	(Text_AppendInline_Worker).l
	cmp.w	(a3),d2
	bgt.w	loc_00F26C
	move.w	(a3),d2
loc_00F26C:
	movea.w	a3,a1
	move.w	(a1),d0
	lsr.w	#1,d0
	neg.w	d0
	addi.w	#$10,d0
	move.w	d0,(TextX).w
	rts


; ----------------------------------------------------------------------
; called from $00F652
sub_00F27E:
	btst	#5,$62(a3)
	bne.w	loc_00EA3C
	btst	#3,$62(a3)
	bne.w	loc_00EA3C
	bclr	#1,$62(a3)
	beq.w	loc_00F2A0
	clr.w	$40(a3)
loc_00F2A0:
	sub.w	d7,$40(a3)
	bpl.w	loc_00F30A
	addi.w	#$3C,$40(a3)
	move.w	(a3),d0
	sub.w	(ram_BFDE).w,d0
	move.w	$14(a3),d1
	sub.w	(ram_BFE0).w,d1
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	jsr	(ISqrt).l
	move.w	d0,d2
	bne.w	loc_00F2D4
	moveq	#$1,d2
loc_00F2D4:
	movem.w	(sp)+,d0/d1
	muls.w	#$50,d0
	divs.w	d2,d0
	add.w	(ram_BFDE).w,d0
	move.w	#$8C,d3
	cmp.w	d3,d0
	blt.w	loc_00F2EE
	move.w	d3,d0
loc_00F2EE:
	neg.w	d3
	cmp.w	d3,d0
	bgt.w	loc_00F2F8
	move.w	d3,d0
loc_00F2F8:
	move.w	d0,$44(a3)
	muls.w	#$50,d1
	divs.w	d2,d1
	add.w	(ram_BFE0).w,d1
	move.w	d1,$46(a3)
loc_00F30A:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_00EA3C(pc),a0
	jsr	(sub_01EDE8).l
	jmp	(sub_01DA26).l
loc_00F322:
	btst	#2,(ram_C354).w
	beq.w	loc_00F344
	movem.w	d0,-(sp)
	move.w	(ram_DD06).w,d0
	cmp.w	$52(a3),d0
	movem.w	(sp)+,d0
	bne.w	loc_00F344
	bra.w	loc_00F35E
loc_00F344:
	tst.w	$44(a3)
	bmi.w	loc_00EA3C
	tst.w	(ram_C3F4).w
	bmi.w	loc_00EA3C
	cmpi.w	#$325C,$58(a3)
	beq.w	loc_00EA3C
loc_00F35E:
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00F372
	bclr	#1,(ram_DD0A).w
	bra.w	loc_00F378
loc_00F372:
	bclr	#0,(ram_DD0A).w
loc_00F378:
	move.w	d0,d2
	move.w	d1,-(sp)
	cmpi.w	#$2,(ram_DCFC).w
	beq.w	loc_00F390
	move.w	#$280,(ram_DDD8).w
	bne.w	loc_00F3BC
loc_00F390:
	tst.w	d1
	bne.w	loc_00F3B6
	tst.w	(ram_DDD8).w
	beq.w	loc_00F3A6
	subq.w	#1,(ram_DDD8).w
	bra.w	loc_00F3BC
loc_00F3A6:
	bset	#7,(ram_C358).w
	bne.w	loc_00F3BC
	move.w	#$8,(ram_C3F4).w
loc_00F3B6:
	move.w	#$280,(ram_DDD8).w
loc_00F3BC:
	btst	#3,d2
	bne.w	loc_00F476
	btst	#1,(ram_C354).w
	bne.w	loc_00F476
	cmpi.w	#$31D8,$58(a3)
	beq.w	loc_00F40E
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00F408
	cmp.w	#$2,d2	; general form
	bne.w	loc_00F40E
loc_00F3EA:
	cmpi.w	#$2,$54(a3)
	beq.w	loc_00F3FE
	bset	#1,(ram_DD0A).w
	bra.w	loc_00F404
loc_00F3FE:
	bset	#0,(ram_DD0A).w
loc_00F404:
	bra.w	loc_00F40E
loc_00F408:
	cmp.w	#$6,d2	; general form
	beq.s	loc_00F3EA
loc_00F40E:
	cmpi.w	#$31D8,$58(a3)
	bne.w	loc_00F46C
	movem.l	d0/a0,-(sp)
	movea.l	#ram_B060,a0
	cmpi.w	#$6,$52(a3)
	bge.w	loc_00F432
	movea.l	#ram_B360,a0
loc_00F432:
	move.w	#$5,d0
loc_00F436:
	btst	#0,$63(a0)
	bne.w	loc_00F44C
	adda.w	#$80,a0
	dbra	d0,loc_00F436
	bra.w	loc_00F468
loc_00F44C:
	move.w	(a3),d0
	sub.w	(a0),d0
	bpl.w	loc_00F456
	neg.w	d0
loc_00F456:
	cmp.w	#$20,d0	; general form
	bgt.w	loc_00F468
	cmp.w	$54(a3),d2
	bne.w	loc_00F468
	clr.w	d2
loc_00F468:
	movem.l	(sp)+,d0/a0
loc_00F46C:
	andi.w	#$7,d2
	jsr	(sub_01FBA6).l
loc_00F476:
	move.w	(ram_BFDE).w,d0
	addi.w	#$C,d0
	cmpi.w	#$2,$54(a3)
	bne.w	loc_00F48C
	subi.w	#$18,d0
loc_00F48C:
	sub.w	(a3),d0
	move.w	$28(a3),d1
	eor.w	d0,d1
	bpl.w	loc_00F4AA
	tst.w	d0
	bpl.w	loc_00F4A0
	neg.w	d0
loc_00F4A0:
	muls.w	$28(a3),d0
	asr.l	#4,d0
	sub.w	d0,$28(a3)
loc_00F4AA:
	move.w	(sp)+,d1
	bset	#1,$63(a3)
	bne.w	loc_00EA3C
	move.w	d1,d2
	cmpi.w	#$31D8,$58(a3)
	bne.w	loc_00F4DE
	btst	#5,d2
	bne.w	loc_00F4DA
	btst	#6,d2
	bne.w	loc_00F4DA
	btst	#4,d2
	beq.w	loc_00F50C
loc_00F4DA:
	bra.w	sub_00F11E
loc_00F4DE:
	btst	#1,(ram_C354).w
	bne.w	loc_00F514
	move.w	#$33C0,d1
	btst	#6,d2
	bne.w	loc_00F5CC
	move.w	#$33FA,d1
	btst	#4,d2
	bne.w	loc_00F5CC
	move.w	#$32F0,d1
	btst	#5,d2
	bne.w	loc_00F5CC
loc_00F50C:
	bclr	#1,$63(a3)
	rts
loc_00F514:
	btst	#2,(ram_C354).w
	bne.w	loc_00F544
	move.w	#$3386,d1
	btst	#6,d2
	bne.w	loc_00F5CC
	move.w	#$346E,d1
	btst	#4,d2
	bne.w	loc_00F5CC
	move.w	#$32B6,d1
	btst	#5,d2
	bne.w	loc_00F564
	bra.s	loc_00F50C
loc_00F544:
	tst.w	(ram_C3F4).w
	bmi.s	loc_00F50C
	btst	#6,d2
	bne.w	loc_00F55C
	btst	#4,d2
	bne.w	loc_00F55C
	bra.s	loc_00F50C
loc_00F55C:
	move.w	#$3434,d1
	bra.w	loc_00F5CC
loc_00F564:
	movem.l	a0,-(sp)
	movea.l	#ram_DCFE,a0
	addq.w	#1,$0(a0,d4.w)
	cmpi.w	#$11,$0(a0,d4.w)
	movem.l	(sp)+,a0
	blt.w	loc_00F590
	bset	#2,(ram_C354).w
	move.w	$52(a3),(ram_DD06).w
	bra.w	loc_00F5CC
loc_00F590:
	movem.l	d1/a0/a3,-(sp)
	movea.l	#ram_B060,a0
	move.w	#$B,d0
loc_00F59E:
	btst	#0,$63(a0)
	beq.w	loc_00F5AE
	cmpa.l	a0,a3
	bne.w	loc_00F5B6
loc_00F5AE:
	adda.w	#$80,a0
	dbra	d0,loc_00F59E
loc_00F5B6:
	movea.l	a0,a3
	move.w	#$3604,d1
	bset	#1,$63(a3)
	jsr	(sub_01F3B2).l
	movem.l	(sp)+,d1/a0/a3
loc_00F5CC:
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $00F148
sub_00F5D2:
	movem.l	a1,-(sp)
	movea.w	#$C3B0,a1
loc_00F5DA:
	addq.w	#2,a1
	cmpi.b	#$2E,(a1)
	bne.s	loc_00F5DA
	move.b	#$26,(a1)
loc_00F5E6:
	addq.w	#2,a1
	cmpi.b	#$2E,(a1)
	bne.s	loc_00F5E6
	move.b	#$26,(a1)
	move.w	#$B40,(ram_C3F4).w
	movem.l	(sp)+,a1
	rts

ptrtbl_00F5FE:
	dc.l	NullSub
	dc.l	sub_011422
	dc.l	sub_010B80
	dc.l	sub_010F08
	dc.l	sub_01190C
	dc.l	sub_011216
	dc.l	sub_0116EE
	dc.l	sub_01BEA4
	dc.l	sub_01BE50
	dc.l	sub_01BAEA
	dc.l	sub_01BD2C
	dc.l	sub_01B94A
	dc.l	sub_01BB74
	dc.l	sub_01BCFC
	dc.l	sub_01C182
	dc.l	sub_01CB5C
	dc.l	sub_01CD70
	dc.l	sub_01D58E
	dc.l	sub_01DCD4
	dc.l	sub_01DBBE

ptrtbl_00F64E:
	dc.l	sub_00EA3E
	dc.l	sub_00F27E
	dc.l	sub_00BED0
	dc.l	sub_00BEEC
	dc.l	sub_01E8AE
	dc.l	sub_01ECA0
	dc.l	sub_01EC5C
	dc.l	sub_00BF82
	dc.l	sub_00C322
	dc.l	sub_01BF76
	dc.l	sub_01DD40
	dc.l	sub_01E04E
	dc.l	sub_01BDDE
	dc.l	sub_01CD46
	dc.l	sub_01D568
	dc.l	sub_1CEFD0
	dc.l	sub_010554
	dc.l	sub_0109CE
	dc.l	sub_010294
	dc.l	sub_010814
	dc.l	sub_01009C
	dc.w	$0001,$009A,$0000,$FE68,$0000,$FE66

ptrtbl_00F6AE:
	dc.l	sub_00FC70
	dc.l	sub_00FB00
	dc.l	sub_00F8CE
	dc.l	sub_00F6F0
	dc.b	$00,$01,$1B,$8A

ptrtbl_00F6C2:
	dc.l	sub_1E52DC
	dc.l	sub_1E533E
	dc.l	sub_011B8C
	dc.l	sub_011CB6
	dc.l	sub_011E3A
	dc.l	sub_011D6A
	dc.l	sub_011E6A
	dc.l	sub_011EAE
	dc.l	sub_0120AA
	dc.l	sub_0120E4
loc_00F6EA:
	jmp	(sub_01F172).l


; ----------------------------------------------------------------------
; called from $00F6BA
sub_00F6F0:
	btst	#5,$62(a3)
	bne.w	loc_00F8CC
	cmpi.w	#$4,$24(a2)
	beq.w	loc_00F724
	move.w	#$6,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_00F714
	bra.s	loc_00F6EA
loc_00F714:
	move.w	#$2E,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_00F724
	bra.s	loc_00F6EA
loc_00F724:
	btst	#0,(ram_C33A).w
	beq.w	loc_00F734
	jmp	(loc_01BE3A).l
loc_00F734:
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_00F8CC
	move.w	#$2D,d0
	move.w	(ram_B774).w,d1
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.s	loc_00F6EA
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_00F768
	neg.w	d1
loc_00F768:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_00F784
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_00F784:
	sub.b	d7,$40(a3)
	bpl.w	loc_00F812
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_00F7AE
	btst	#6,(ram_C34C).w
	beq.w	loc_00F7B2
	tst.b	$40(a3)
	beq.w	loc_00F7B2
loc_00F7AE:
	subq.b	#1,$40(a3)
loc_00F7B2:
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_00F7C4
	move.w	$34(a3),d1
	bmi.w	loc_00F8CC
loc_00F7C4:
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_00F7D4
	neg.w	d1
loc_00F7D4:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F808
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_00F7EC
	neg.w	d0
loc_00F7EC:
	move.w	d0,$44(a3)
	move.w	#$96,d1
	btst	#7,$62(a3)
	beq.w	loc_00F800
	neg.w	d1
loc_00F800:
	move.w	d1,$46(a3)
	bra.w	loc_00F812
loc_00F808:
	move.w	(ram_B760).w,$44(a3)
	clr.w	$46(a3)
loc_00F812:
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_00F870
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_00F834
	adda.w	#$300,a0
loc_00F834:
	move.w	#$5,d2
loc_00F838:
	btst	#2,$63(a0)
	bne.w	loc_00F864
	tst.b	$65(a0)
	bpl.w	loc_00F852
	tst.w	$34(a0)
	bmi.w	loc_00F864
loc_00F852:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	bgt.w	loc_00F864
	move.w	d0,d1
loc_00F864:
	adda.w	#$80,a0
	dbra	d2,loc_00F838
	bra.w	loc_00F8BC
loc_00F870:
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_00F884
	adda.w	#$300,a0
loc_00F884:
	move.w	#$5,d2
loc_00F888:
	btst	#2,$63(a0)
	bne.w	loc_00F8B4
	tst.b	$65(a0)
	bpl.w	loc_00F8A2
	tst.w	$34(a0)
	bmi.w	loc_00F8B4
loc_00F8A2:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	blt.w	loc_00F8B4
	move.w	d0,d1
loc_00F8B4:
	adda.w	#$80,a0
	dbra	d2,loc_00F888
loc_00F8BC:
	move.w	$44(a3),d0
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_00F8CC:
	rts


; ----------------------------------------------------------------------
; called from $00F6B6
sub_00F8CE:
	cmpi.w	#$5,$24(a2)
loc_00F8D4:
	beq.w	loc_00F8FC
	move.w	#$6,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_00F8EA
	bra.w	loc_00F6EA
loc_00F8EA:
	move.w	#$2F,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_00F8FC
	bra.w	loc_00F6EA
loc_00F8FC:
	btst	#5,$62(a3)
	bne.w	loc_00FAFE
	btst	#0,(ram_C33A).w
	beq.w	loc_00F916
	jmp	(loc_01BE3A).l
loc_00F916:
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_00FAFE
	moveq	#$2C,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_00F938
	neg.w	d1
loc_00F938:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F6EA
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00F956
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
loc_00F956:
	bclr	#1,$62(a3)
	beq.w	loc_00F96E
	st	$48(a3)
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_00F96E:
	sub.b	d7,$40(a3)
	bpl.w	loc_00FADE
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_00F992
	tst.b	$40(a3)
	beq.w	loc_00F992
	subq.b	#1,$40(a3)
loc_00F992:
	move.w	(ram_B78A).w,d0
	asr.w	#7,d0
	add.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_00F9A8
	neg.w	d0
loc_00F9A8:
	clr.w	d2
	jsr	(sub_1D3B76).l
	cmp.w	$48(a3),d2
	bne.w	loc_00F9C8
	move.w	(FrameCounter).w,d0
	andi.w	#$7F,d0
	cmp.w	#$2,d0	; general form
	bgt.w	loc_00FADE
loc_00F9C8:
	move.w	d2,$48(a3)
	move.w	$16(a2),d0
	asl.w	#1,d0
	lea	(ram_DEFE).w,a0
	move.w	$0(a0,d0.w),d0
	tst.w	d0
	beq.s	loc_00F9F2
	cmp.w	#$1,d0	; general form
	beq.s	loc_00F9FA
	cmp.w	#$2,d0	; general form
	beq.s	loc_00FA02
	cmp.w	#$3,d0	; general form
	beq.s	loc_00FA0A
	bra.s	loc_00FA12
loc_00F9F2:
	lea	dat_00FA3E(pc),a0
	bra.w	loc_00FA16
loc_00F9FA:
	lea	dat_00FA5E(pc),a0
	bra.w	loc_00FA16
loc_00FA02:
	lea	dat_00FA7E(pc),a0
	bra.w	loc_00FA16
loc_00FA0A:
	lea	dat_00FA9E(pc),a0
	bra.w	loc_00FA16
loc_00FA12:
	lea	dat_00FABE(pc),a0
loc_00FA16:
	move.w	$2(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$0(a0,d2.w),d0
	move.w	d0,$44(a3)
	move.w	$6(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$4(a0,d2.w),d0
	move.w	d0,$46(a3)
	bra.w	loc_00FADE
dat_00FA3E:
	dc.w	$0000,$003C,$FFB0,$000A,$0000,$003C,$0032,$000A
	dc.w	$0000,$0028,$00A0,$001E,$0000,$0050,$00A0,$0014
dat_00FA5E:
	dc.w	$0000,$003C,$FFBF,$000A,$0000,$003C,$0041,$000A
	dc.w	$0000,$0028,$00AF,$001E,$0000,$0050,$00AF,$0014
dat_00FA7E:
	dc.w	$0000,$003C,$FFCE,$000A,$0000,$003C,$0050,$000A
	dc.w	$0000,$0028,$00BE,$001E,$0000,$0050,$00BE,$0014
dat_00FA9E:
	dc.w	$0000,$003C,$FFDD,$000A,$0000,$003C,$005F,$000A
	dc.w	$0000,$0028,$00CD,$001E,$0000,$0050,$00CD,$0014
dat_00FABE:
	dc.w	$0000,$003C,$FFEC,$000A,$0000,$003C,$006E,$000A
	dc.w	$0000,$0028,$00DC,$001E,$0000,$0050,$00DC,$0014
loc_00FADE:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_00FAF2
	neg.w	d1
loc_00FAF2:
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_00FAFE:
	rts


; ----------------------------------------------------------------------
; called from $00F6B2
sub_00FB00:
	cmpi.w	#$4,$24(a2)
	beq.w	loc_00FB2E
	move.w	#$5,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_00FB1C
	bra.w	loc_00F6EA
loc_00FB1C:
	move.w	#$2C,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_00FB2E
	bra.w	loc_00F6EA
loc_00FB2E:
	btst	#5,$62(a3)
	bne.w	loc_00FC68
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_00FC68
	bclr	#1,$62(a3)
	beq.w	loc_00FB66
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_00FB66:
	sub.b	d7,$40(a3)
	bpl.w	loc_00FC56
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_00FB8A
	tst.b	$40(a3)
	beq.w	loc_00FB8A
	subq.b	#1,$40(a3)
loc_00FB8A:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00FBBA
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_00FBA2
	neg.w	d0
loc_00FBA2:
	cmp.w	#$76,d0	; general form
	bgt.w	loc_00FBBA
	moveq	#$2F,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bpl.w	loc_00F6EA
loc_00FBBA:
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_00FBCA
	neg.w	d0
loc_00FBCA:
	cmp.w	#$76,d0	; general form
	blt.w	loc_00FC3C
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_00FBE6
	adda.w	#$300,a0
loc_00FBE6:
	move.w	(ram_B7C0).w,d0
	bpl.w	loc_00FBF2
	move.w	#$E,d0
loc_00FBF2:
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	adda.w	d0,a0
	move.w	$28(a0),d0
	asr.w	#7,d0
	add.w	(a0),d0
	asr.w	#2,d0
	move.w	d0,d1
	add.w	d0,d1
	add.w	d0,d1
	move.w	d1,$44(a3)
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_00FC20
	neg.w	d0
loc_00FC20:
	move.w	$2A(a0),d1
	asr.w	#7,d1
	add.w	$14(a0),d1
	sub.w	d0,d1
	asr.w	#2,d1
	add.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	move.w	d0,$46(a3)
	bra.w	loc_00FC56
loc_00FC3C:
	move.w	(ram_B760).w,$44(a3)
	move.w	#$76,d0
	btst	#7,$62(a3)
	beq.w	loc_00FC52
	neg.w	d0
loc_00FC52:
	move.w	d0,$46(a3)
loc_00FC56:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_00FC68(pc),a0
	jmp	(sub_01EDE8).l
loc_00FC68:
	rts
loc_00FC6A:
	jmp	(loc_01BE3A).l


; ----------------------------------------------------------------------
; called from $00F6AE
sub_00FC70:
	cmpi.w	#$5,$24(a2)
	beq.w	loc_00FC9E
	move.w	#$5,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_00FC8C
	bra.w	loc_00F6EA
loc_00FC8C:
	move.w	#$2D,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_00FC9E
	bra.w	loc_00F6EA
loc_00FC9E:
	btst	#5,$62(a3)
	bne.w	loc_00FE64
	btst	#0,(ram_C33A).w
	bne.s	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_00FE64
	bclr	#1,$62(a3)
	beq.w	loc_00FCD4
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_00FCD4:
	sub.b	d7,$40(a3)
	bpl.w	loc_00FE52
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_00FCF8
	tst.b	$40(a3)
	beq.w	loc_00FCF8
	subq.b	#1,$40(a3)
loc_00FCF8:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00FD28
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_00FD10
	neg.w	d0
loc_00FD10:
	cmp.w	#$76,d0	; general form
	bgt.w	loc_00FD28
	moveq	#$2E,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bpl.w	loc_00F6EA
loc_00FD28:
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_00FD38
	neg.w	d0
loc_00FD38:
	cmp.w	#$76,d0	; general form
	blt.w	loc_00FE20
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00FD8E
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00FD8E
	move.w	#$FFAF,d1
	btst	#7,$62(a3)
	beq.w	loc_00FD66
	neg.w	d1
loc_00FD66:
	move.w	#$14,d0
	jsr	(sub_0200EA).l
	add.w	d1,d0
	move.w	d0,$44(a3)
	move.w	#$76,d1
	btst	#7,$62(a3)
	beq.w	loc_00FD86
	neg.w	d1
loc_00FD86:
	move.w	d1,$46(a3)
	bra.w	loc_00FE52
loc_00FD8E:
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_00FDA2
	adda.w	#$300,a0
loc_00FDA2:
	move.w	#$1,d0
	bsr.w	sub_011B4C
	move.w	$14(a0),d1
	btst	#7,$62(a3)
	beq.w	loc_00FDBA
	neg.w	d1
loc_00FDBA:
	cmp.w	#$76,d1	; general form
	bge.w	loc_00FDE0
	move.w	(a0),d0
	move.w	#$A3,d1
	btst	#7,$62(a3)
	beq.w	loc_00FDD4
	neg.w	d1
loc_00FDD4:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
	bra.w	loc_00FE52
loc_00FDE0:
	move.w	$28(a0),d0
	asr.w	#7,d0
	add.w	(a0),d0
	asr.w	#2,d0
	move.w	d0,d1
	add.w	d0,d1
	add.w	d0,d1
	move.w	d1,$44(a3)
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_00FE04
	neg.w	d0
loc_00FE04:
	move.w	$2A(a0),d1
	asr.w	#7,d1
	add.w	$14(a0),d1
	sub.w	d0,d1
	asr.w	#2,d1
	add.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	move.w	d0,$46(a3)
	bra.w	loc_00FE52
loc_00FE20:
	move.w	(ram_B760).w,d0
	move.w	(a3),d1
	eor.w	d1,d0
	bmi.w	loc_00FE4A
	move.w	(ram_B760).w,$44(a3)
loc_00FE32:
	move.w	#$76,d0
	btst	#7,$62(a3)
	beq.w	loc_00FE42
	neg.w	d0
loc_00FE42:
	move.w	d0,$46(a3)
	bra.w	loc_00FE52
loc_00FE4A:
	move.w	#$0,$44(a3)
	bra.s	loc_00FE32
loc_00FE52:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_00FE64(pc),a0
	jmp	(sub_01EDE8).l
loc_00FE64:
	rts

	dc.w	$4E75,$0C6A,$0005,$0024,$6700,$0026,$303C,$0004
	dc.w	$0C6A,$0006,$0024,$6600,$0006,$6000,$F868,$303C
	dc.w	$002B,$0C6A,$0004,$0024,$6600,$0006,$6000,$F856
	dc.w	$082B,$0005,$0062,$6600,$01FA,$0838,$0000,$C33A
	dc.w	$6600,$FDC2,$4EB9,$0001,$B8B8,$082B,$0003,$0062
	dc.w	$6600,$01E0,$7028,$3238,$B7C0,$6B00,$0010,$5D41
	dc.w	$342B,$0052,$5D42,$B541,$6B00,$F81A,$08AB,$0001
	dc.w	$0062,$6700,$0010,$50EB,$0048,$426B,$0040,$377C
	dc.w	$0008,$0042,$9F2B,$0040,$6A00,$0186,$176B,$006C
	dc.w	$0040,$0838,$0006,$C34C,$6700,$000E,$4A2B,$0040
	dc.w	$6700,$0006,$532B,$0040,$3238,$B774,$082B,$0007
	dc.w	$0062,$6700,$0004,$4441,$B27C,$0076,$6E00,$F7C6
	dc.w	$3038,$B774,$3638,$B78A,$EC43,$D640,$082B,$0007
	dc.w	$0062,$6600,$0006,$4440,$4443,$4242,$4EB9,$001D
	dc.w	$3C7A,$B46B,$0048,$6600,$0012,$3038,$B054,$0240
	dc.w	$007F,$B07C,$0002,$6E00,$0118,$3742,$0048,$302A
	dc.w	$0016,$E340,$41F8,$DEFE,$3030,$0000,$4A40,$6714
	dc.w	$B07C,$0001,$6716,$B07C,$0002,$6718,$B07C,$0003
	dc.w	$671A,$6020,$41FA,$004A,$6000,$001E,$41FA,$0062
	dc.w	$6000,$0016,$41FA,$007A,$6000,$000E,$41FA,$0092
	dc.w	$6000,$0006


; ----------------------------------------------------------------------
sub_00FFAA:
	lea	dat_010056(pc),a0
	move.w	$2(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$0(a0,d2.w),d0
	move.w	d0,$44(a3)
	move.w	$6(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$4(a0,d2.w),d0
	move.w	d0,$46(a3)
	bra.w	sub_010076

	dc.w	$0050,$0014,$FF9C,$000A,$0064,$0014,$003A,$0005
	dc.w	$0047,$0032,$00C8,$0014,$0050,$001E,$00DC,$0014
	dc.w	$0050,$0014,$FFAB,$000A,$0064
dat_010000:
	dc.b	$00,$14
dat_010002:
	dc.w	$0049,$0005,$0047,$0032,$00D7,$0014,$0050,$001E
	dc.w	$00EB,$0014,$0050,$0014,$FFBA,$000A,$0064,$0014
	dc.w	$0058,$0005,$0047,$0032,$00E6,$0014,$0050,$001E
	dc.w	$00FA,$0014,$0050,$0014,$FFC9,$000A,$0064,$0014
	dc.w	$0067,$0005,$0047,$0032,$00F5,$0014,$0050,$001E
	dc.w	$0109,$0014
dat_010056:
	dc.w	$0050,$0014,$FFD8,$000A,$0064,$0014,$0076,$0005
	dc.w	$0047,$0032,$0104,$0014,$0050,$001E,$0118,$0014


; ----------------------------------------------------------------------
; called from $00FFD2
sub_010076:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_01008C
	neg.w	d0
	neg.w	d1
loc_01008C:
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l

	dc.b	"NuNu"


; ----------------------------------------------------------------------
; called from $00F69E
sub_01009C:
	cmpi.w	#$5,$24(a2)
	beq.w	loc_0100CA
	move.w	#$3,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_0100B8
	bra.w	loc_00F6EA
loc_0100B8:
	move.w	#$29,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_0100CA
	bra.w	loc_00F6EA
loc_0100CA:
	btst	#5,$62(a3)
	bne.w	loc_010292
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_010292
	bclr	#1,$62(a3)
	beq.w	loc_010102
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_010102:
	sub.b	d7,$40(a3)
	bpl.w	loc_010280
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_010126
	tst.b	$40(a3)
	beq.w	loc_010126
	subq.b	#1,$40(a3)
loc_010126:
	moveq	#$2A,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_010138
	neg.w	d1
loc_010138:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_010156
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_010156
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bpl.w	loc_00F6EA
loc_010156:
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_010166
	neg.w	d0
loc_010166:
	cmp.w	#$76,d0	; general form
	blt.w	loc_01024E
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_0101BC
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_0101BC
	move.w	#$51,d1
	btst	#7,$62(a3)
	beq.w	loc_010194
	neg.w	d1
loc_010194:
	move.w	#$14,d0
	jsr	(sub_0200EA).l
	add.w	d1,d0
	move.w	d0,$44(a3)
	move.w	#$76,d1
	btst	#7,$62(a3)
	beq.w	loc_0101B4
	neg.w	d1
loc_0101B4:
	move.w	d1,$46(a3)
	bra.w	loc_010280
loc_0101BC:
	move.w	#$2,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_0101D4
	adda.w	#$300,a0
loc_0101D4:
	bsr.w	sub_011B4C
	move.w	$14(a0),d1
	btst	#7,$62(a3)
	beq.w	loc_0101E8
	neg.w	d1
loc_0101E8:
	cmp.w	#$76,d1	; general form
	bge.w	loc_01020E
	move.w	(a0),d0
	move.w	#$A3,d1
	btst	#7,$62(a3)
	beq.w	loc_010202
	neg.w	d1
loc_010202:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
	bra.w	loc_010280
loc_01020E:
	move.w	#$76,d1
	btst	#7,$62(a3)
	beq.w	loc_01021E
	neg.w	d1
loc_01021E:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	sub.w	d1,d0
	asr.w	#2,d0
	add.w	d0,d1
	add.w	d0,d1
	add.w	d0,d1
	move.w	d1,$46(a3)
	move.w	$28(a0),d1
	asr.w	#7,d1
	add.w	(a0),d1
	asr.w	#2,d1
	move.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	move.w	d0,$44(a3)
	bra.w	loc_010280
loc_01024E:
	move.w	(ram_B760).w,d0
	move.w	(a3),d1
	eor.w	d1,d0
	bmi.w	loc_010278
	move.w	(ram_B760).w,$44(a3)
loc_010260:
	move.w	#$76,d0
	btst	#7,$62(a3)
	beq.w	loc_010270
	neg.w	d0
loc_010270:
	move.w	d0,$46(a3)
	bra.w	loc_010280
loc_010278:
	move.w	#$0,$44(a3)
	bra.s	loc_010260
loc_010280:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_010292(pc),a0
	jmp	(sub_01EDE8).l
loc_010292:
	rts


; ----------------------------------------------------------------------
; called from $00F696
sub_010294:
	btst	#5,$62(a3)
	bne.w	loc_010552
	cmpi.w	#$4,$24(a2)
	beq.w	loc_0102CC
	move.w	#$1,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_0102BA
	bra.w	loc_00F6EA
loc_0102BA:
	move.w	#$24,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_0102CC
	bra.w	loc_00F6EA
loc_0102CC:
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_010552
	move.w	#$27,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_0102FA
	neg.w	d1
loc_0102FA:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F6EA
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00F6EA
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_01032C
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_01032C:
	sub.b	d7,$40(a3)
	bpl.w	loc_010498
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_010356
	btst	#6,(ram_C34C).w
	beq.w	loc_01035A
	tst.b	$40(a3)
	beq.w	loc_01035A
loc_010356:
	subq.b	#1,$40(a3)
loc_01035A:
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_01036C
	move.w	$34(a3),d1
	bmi.w	loc_010552
loc_01036C:
	cmp.w	#$2,d1	; general form
	bne.w	loc_010406
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_010384
	neg.w	d1
loc_010384:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_0103B8
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_01039C
	neg.w	d0
loc_01039C:
	move.w	d0,$44(a3)
	move.w	#$96,d1
	btst	#7,$62(a3)
	beq.w	loc_0103B0
	neg.w	d1
loc_0103B0:
	move.w	d1,$46(a3)
	bra.w	loc_010498
loc_0103B8:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_0103C8
	neg.w	d0
loc_0103C8:
	tst.w	d0
	bpl.w	loc_0103DA
	clr.w	$44(a3)
	clr.w	$46(a3)
	bra.w	loc_010498
loc_0103DA:
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_0103EA
	neg.w	d0
loc_0103EA:
	move.w	d0,$44(a3)
	move.w	#$6C,d1
	btst	#7,$62(a3)
	bne.w	loc_0103FE
	neg.w	d1
loc_0103FE:
	move.w	d1,$46(a3)
	bra.w	loc_010498
loc_010406:
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_010416
	neg.w	d1
loc_010416:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_01044A
	move.w	#$FFAF,d0
	btst	#7,$62(a3)
	bne.w	loc_01042E
	neg.w	d0
loc_01042E:
	move.w	d0,$44(a3)
	move.w	#$96,d1
	btst	#7,$62(a3)
	beq.w	loc_010442
	neg.w	d1
loc_010442:
	move.w	d1,$46(a3)
	bra.w	loc_010498
loc_01044A:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_01045A
	neg.w	d0
loc_01045A:
	tst.w	d0
	bmi.w	loc_01046C
	clr.w	$44(a3)
	clr.w	$46(a3)
	bra.w	loc_010498
loc_01046C:
	move.w	#$FFAF,d0
	btst	#7,$62(a3)
	bne.w	loc_01047C
	neg.w	d0
loc_01047C:
	move.w	d0,$44(a3)
	move.w	#$6C,d1
	btst	#7,$62(a3)
	bne.w	loc_010490
	neg.w	d1
loc_010490:
	move.w	d1,$46(a3)
	bra.w	loc_010498
loc_010498:
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_0104F6
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_0104BA
	adda.w	#$300,a0
loc_0104BA:
	move.w	#$5,d2
loc_0104BE:
	btst	#2,$63(a0)
	bne.w	loc_0104EA
	tst.b	$65(a0)
	bpl.w	loc_0104D8
	tst.w	$34(a0)
	bmi.w	loc_0104EA
loc_0104D8:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	bgt.w	loc_0104EA
	move.w	d0,d1
loc_0104EA:
	adda.w	#$80,a0
	dbra	d2,loc_0104BE
	bra.w	loc_010542
loc_0104F6:
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_01050A
	adda.w	#$300,a0
loc_01050A:
	move.w	#$5,d2
loc_01050E:
	btst	#2,$63(a0)
	bne.w	loc_01053A
	tst.b	$65(a0)
	bpl.w	loc_010528
	tst.w	$34(a0)
	bmi.w	loc_01053A
loc_010528:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	blt.w	loc_01053A
	move.w	d0,d1
loc_01053A:
	adda.w	#$80,a0
	dbra	d2,loc_01050E
loc_010542:
	move.w	$44(a3),d0
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_010552:
	rts


; ----------------------------------------------------------------------
; called from $00F68E
sub_010554:
	btst	#5,$62(a3)
	bne.w	loc_010812
	cmpi.w	#$5,$24(a2)
	beq.w	loc_01058C
	move.w	#$1,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_01057A
	bra.w	loc_00F6EA
loc_01057A:
	move.w	#$26,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_01058C
	bra.w	loc_00F6EA
loc_01058C:
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_010812
	move.w	#$25,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_0105BA
	neg.w	d1
loc_0105BA:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F6EA
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00F6EA
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_0105EC
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_0105EC:
	sub.b	d7,$40(a3)
	bpl.w	loc_010758
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_010616
	btst	#6,(ram_C34C).w
	beq.w	loc_01061A
	tst.b	$40(a3)
	beq.w	loc_01061A
loc_010616:
	subq.b	#1,$40(a3)
loc_01061A:
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_01062C
	move.w	$34(a3),d1
	bmi.w	loc_010812
loc_01062C:
	cmp.w	#$2,d1	; general form
	bne.w	loc_0106C6
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_010644
	neg.w	d1
loc_010644:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_010678
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_01065C
	neg.w	d0
loc_01065C:
	move.w	d0,$44(a3)
	move.w	#$96,d1
	btst	#7,$62(a3)
	beq.w	loc_010670
	neg.w	d1
loc_010670:
	move.w	d1,$46(a3)
	bra.w	loc_010758
loc_010678:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010688
	neg.w	d0
loc_010688:
	tst.w	d0
	bpl.w	loc_01069A
	clr.w	$44(a3)
	clr.w	$46(a3)
	bra.w	loc_010758
loc_01069A:
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_0106AA
	neg.w	d0
loc_0106AA:
	move.w	d0,$44(a3)
	move.w	#$6C,d1
	btst	#7,$62(a3)
	bne.w	loc_0106BE
	neg.w	d1
loc_0106BE:
	move.w	d1,$46(a3)
	bra.w	loc_010758
loc_0106C6:
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_0106D6
	neg.w	d1
loc_0106D6:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_01070A
	move.w	#$FFAF,d0
	btst	#7,$62(a3)
	bne.w	loc_0106EE
	neg.w	d0
loc_0106EE:
	move.w	d0,$44(a3)
	move.w	#$96,d1
	btst	#7,$62(a3)
	beq.w	loc_010702
	neg.w	d1
loc_010702:
	move.w	d1,$46(a3)
	bra.w	loc_010758
loc_01070A:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_01071A
	neg.w	d0
loc_01071A:
	tst.w	d0
	bmi.w	loc_01072C
	clr.w	$44(a3)
	clr.w	$46(a3)
	bra.w	loc_010758
loc_01072C:
	move.w	#$FFAF,d0
	btst	#7,$62(a3)
	bne.w	loc_01073C
	neg.w	d0
loc_01073C:
	move.w	d0,$44(a3)
	move.w	#$6C,d1
	btst	#7,$62(a3)
	bne.w	loc_010750
	neg.w	d1
loc_010750:
	move.w	d1,$46(a3)
	bra.w	loc_010758
loc_010758:
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_0107B6
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_01077A
	adda.w	#$300,a0
loc_01077A:
	move.w	#$5,d2
loc_01077E:
	btst	#2,$63(a0)
	bne.w	loc_0107AA
	tst.b	$65(a0)
	bpl.w	loc_010798
	tst.w	$34(a0)
	bmi.w	loc_0107AA
loc_010798:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	bgt.w	loc_0107AA
	move.w	d0,d1
loc_0107AA:
	adda.w	#$80,a0
	dbra	d2,loc_01077E
	bra.w	loc_010802
loc_0107B6:
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_0107CA
	adda.w	#$300,a0
loc_0107CA:
	move.w	#$5,d2
loc_0107CE:
	btst	#2,$63(a0)
	bne.w	loc_0107FA
	tst.b	$65(a0)
	bpl.w	loc_0107E8
	tst.w	$34(a0)
	bmi.w	loc_0107FA
loc_0107E8:
	move.w	$2A(a0),d0
	asr.w	#7,d0
	add.w	$14(a0),d0
	cmp.w	d0,d1
	blt.w	loc_0107FA
	move.w	d0,d1
loc_0107FA:
	adda.w	#$80,a0
	dbra	d2,loc_0107CE
loc_010802:
	move.w	$44(a3),d0
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_010812:
	rts


; ----------------------------------------------------------------------
; called from $00F69A
sub_010814:
	btst	#5,$62(a3)
	bne.w	loc_0109CC
	cmpi.w	#$4,$24(a2)
	beq.w	loc_01084C
	move.w	#$2,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_01083A
	bra.w	loc_00F6EA
loc_01083A:
	move.w	#$25,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_01084C
	bra.w	loc_00F6EA
loc_01084C:
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_0109CC
	bclr	#1,$62(a3)
	beq.w	loc_01087A
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_01087A:
	sub.b	d7,$40(a3)
	bpl.w	loc_010980
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_01089E
	tst.b	$40(a3)
	beq.w	loc_01089E
	subq.b	#1,$40(a3)
loc_01089E:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_0108D4
	moveq	#$26,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_0108D4
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_0108CC
	neg.w	d1
loc_0108CC:
	cmp.w	#$76,d1	; general form
	blt.w	loc_00F6EA
loc_0108D4:
	clr.w	d0
	move.b	$65(a3),d0
	bpl.w	loc_0108E6
	move.w	$34(a3),d0
	bmi.w	loc_0109CC
loc_0108E6:
	cmp.w	#$2,d0	; general form
	beq.w	loc_010978
	move.w	#$FFFF,d1
loc_0108F2:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010902
	neg.w	d1
loc_010902:
	move.w	d1,$44(a3)
	eor.w	d0,d1
	bpl.w	loc_010924
	move.w	#$FF14,d1
	btst	#7,$62(a3)
	bne.w	loc_01091C
	neg.w	d1
loc_01091C:
	move.w	d1,$46(a3)
	bra.w	loc_010980
loc_010924:
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	bpl.w	loc_010936
	move.w	#$E,d0
loc_010936:
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	$28(a0),d0
	asr.w	#7,d0
	add.w	(a0),d0
	ext.l	d0
	divs.w	#$3,d0
	move.w	d0,$44(a3)
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_01095C
	neg.w	d0
loc_01095C:
	move.w	$2A(a0),d1
	asr.w	#7,d1
	add.w	$14(a0),d1
	sub.w	d0,d1
	ext.l	d1
	divs.w	#$3,d1
	add.w	d1,d0
	move.w	d0,$46(a3)
	bra.w	loc_010980
loc_010978:
	move.w	#$1,d1
	bra.w	loc_0108F2
loc_010980:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	move.b	$6A(a3),-(sp)
	cmpi.l	#$15F9,$2A(a2)
	blt.w	loc_0109A4
	move.b	#$1E,$6A(a3)
loc_0109A4:
	jsr	(sub_01EDE8).l
	move.b	(sp)+,$6A(a3)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_0109BE
	neg.w	d0
loc_0109BE:
	cmp.w	#$76,d0	; general form
	bgt.w	loc_0109CC
	jmp	(sub_01DA26).l
loc_0109CC:
	rts


; ----------------------------------------------------------------------
; called from $00F692
sub_0109CE:
	btst	#5,$62(a3)
	bne.w	loc_010B7E
	cmpi.w	#$5,$24(a2)
	beq.w	loc_010A06
	move.w	#$2,d0
	cmpi.w	#$6,$24(a2)
	bne.w	loc_0109F4
	bra.w	loc_00F6EA
loc_0109F4:
	move.w	#$27,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_010A06
	bra.w	loc_00F6EA
loc_010A06:
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_010B7E
	bclr	#1,$62(a3)
	beq.w	loc_010A34
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_010A34:
	sub.b	d7,$40(a3)
	bpl.w	loc_010B32
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_010A58
	tst.b	$40(a3)
	beq.w	loc_010A58
	subq.b	#1,$40(a3)
loc_010A58:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_010A8E
	moveq	#$24,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_010A8E
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_010A86
	neg.w	d1
loc_010A86:
	cmp.w	#$76,d1	; general form
	blt.w	loc_00F6EA
loc_010A8E:
	clr.w	d0
	move.b	$65(a3),d0
	bpl.w	loc_010AA0
	move.w	$34(a3),d0
	bmi.w	loc_010B7E
loc_010AA0:
	cmp.w	#$2,d0	; general form
	beq.w	loc_010B2A
	move.w	#$FFFF,d1
loc_010AAC:
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010ABC
	neg.w	d1
loc_010ABC:
	move.w	d1,$44(a3)
	eor.w	d0,d1
	bpl.w	loc_010ADE
	move.w	#$FF14,d1
	btst	#7,$62(a3)
	bne.w	loc_010AD6
	neg.w	d1
loc_010AD6:
	move.w	d1,$46(a3)
	bra.w	loc_010B32
loc_010ADE:
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	bpl.w	loc_010AF0
	move.w	#$E,d0
loc_010AF0:
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	$28(a0),d0
	asr.w	#7,d0
	add.w	(a0),d0
	asr.w	#1,d0
	move.w	d0,$44(a3)
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_010B12
	neg.w	d0
loc_010B12:
	move.w	$2A(a0),d1
	asr.w	#7,d1
	add.w	$14(a0),d1
	sub.w	d0,d1
	asr.w	#1,d1
	add.w	d1,d0
	move.w	d0,$46(a3)
	bra.w	loc_010B32
loc_010B2A:
	move.w	#$1,d1
	bra.w	loc_010AAC
loc_010B32:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	move.b	$6A(a3),-(sp)
	cmpi.l	#$15F9,$2A(a2)
	blt.w	loc_010B56
	move.b	#$1E,$6A(a3)
loc_010B56:
	jsr	(sub_01EDE8).l
	move.b	(sp)+,$6A(a3)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_010B70
	neg.w	d0
loc_010B70:
	cmp.w	#$76,d0	; general form
	blt.w	loc_010B7E
	jmp	(sub_01DA26).l
loc_010B7E:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_010B80:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_010BAE
	move.w	#$25,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_010B9C
	bra.w	loc_00F6EA
loc_010B9C:
	move.w	#$27,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_010BAE
	bra.w	loc_00F6EA
loc_010BAE:
	btst	#5,$62(a3)
	bne.w	loc_010F06
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_010F06
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_010BF0
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_010BF0:
	btst	#4,$30(a2)
	bne.w	loc_010C3A
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_010C3A
	cmpi.b	#$4,$40(a3)
	bge.w	loc_010C3A
	moveq	#$1,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_010C3A
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_010C32
	neg.w	d1
loc_010C32:
	cmp.w	#$76,d1	; general form
	blt.w	loc_00F6EA
loc_010C3A:
	sub.b	d7,$40(a3)
	bpl.w	loc_010EA2
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_010C5E
	tst.b	$40(a3)
	beq.w	loc_010C5E
	subq.b	#1,$40(a3)
loc_010C5E:
	st	(ram_D25A).w
	clr.w	d0
	move.b	$65(a3),d0
	bpl.w	loc_010C74
	move.w	$34(a3),d0
	bmi.w	loc_010F06
loc_010C74:
	cmp.w	#$2,d0	; general form
	bne.w	loc_010D62
	move.w	#$1,d1
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010C90
	neg.w	d1
loc_010C90:
	move.w	d1,$44(a3)
	eor.w	d0,d1
	bpl.w	loc_010CD2
	move.w	#$FF14,d1
	btst	#7,$62(a3)
	bne.w	loc_010CAA
	neg.w	d1
loc_010CAA:
	move.w	d1,$46(a3)
	move.w	$52(a3),(ram_D25A).w
	movem.w	d0,-(sp)
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	movem.w	(sp)+,d0
	bne.w	loc_010E44
	jsr	(sub_01F11C).l
	bra.w	loc_010E44
loc_010CD2:
	move.w	#$3,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_010CEA
	adda.w	#$300,a0
loc_010CEA:
	bsr.w	sub_011B4C
	move.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_010CFE
	neg.w	d0
loc_010CFE:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_010D28
	move.w	#$F6,d1
	move.w	#$FFC3,d0
	btst	#7,$62(a3)
	beq.w	loc_010D1C
	neg.w	d1
	neg.w	d0
loc_010D1C:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
	bra.w	loc_010EA2
loc_010D28:
	move.w	(a0),d0
	asr.w	#1,d0
	move.w	d0,$44(a3)
	move.w	#$11E,d1
	btst	#7,$62(a3)
	beq.w	loc_010D40
	neg.w	d1
loc_010D40:
	sub.w	$14(a0),d1
	asr.w	#1,d1
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_010D56
	neg.w	d0
loc_010D56:
	neg.w	d1
	add.w	d0,d1
	move.w	d1,$46(a3)
	bra.w	loc_010E44
loc_010D62:
	move.w	#$FFFF,d1
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010D76
	neg.w	d1
loc_010D76:
	move.w	d1,$44(a3)
	eor.w	d0,d1
	bpl.w	loc_010DB8
	move.w	#$FF14,d1
	btst	#7,$62(a3)
	bne.w	loc_010D90
	neg.w	d1
loc_010D90:
	move.w	d1,$46(a3)
	move.w	$52(a3),(ram_D25A).w
	movem.w	d0,-(sp)
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	movem.w	(sp)+,d0
	bne.w	loc_010E44
	jsr	(sub_01F11C).l
	bra.w	loc_010E44
loc_010DB8:
	move.w	#$5,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_010DD0
	adda.w	#$300,a0
loc_010DD0:
	bsr.w	sub_011B4C
	move.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_010DE4
	neg.w	d0
loc_010DE4:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_010E0E
	move.w	#$F6,d1
	move.w	#$3D,d0
	btst	#7,$62(a3)
	beq.w	loc_010E02
	neg.w	d1
	neg.w	d0
loc_010E02:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
	bra.w	loc_010EA2
loc_010E0E:
	move.w	(a0),d0
	asr.w	#1,d0
	move.w	d0,$44(a3)
	move.w	#$11E,d1
	btst	#7,$62(a3)
	beq.w	loc_010E26
	neg.w	d1
loc_010E26:
	sub.w	$14(a0),d1
	asr.w	#1,d1
	move.w	#$11E,d0
	btst	#7,$62(a3)
	beq.w	loc_010E3C
	neg.w	d0
loc_010E3C:
	neg.w	d1
	add.w	d0,d1
	move.w	d1,$46(a3)
loc_010E44:
	cmpi.w	#$11E,(ram_B774).w
	bgt.w	loc_010ED2
	cmpi.w	#$FEE2,(ram_B774).w
	blt.w	loc_010ED2
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_010E72
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	adda.w	d0,a0
	tst.w	$34(a0)
	beq.w	loc_010ED2
loc_010E72:
	move.w	$46(a3),d1
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_010E88
	neg.w	d1
	neg.w	d0
loc_010E88:
	addi.w	#$A,d0
	cmp.w	d0,d1
	bgt.w	loc_010ED2
	btst	#7,$62(a3)
	beq.w	loc_010E9E
	neg.w	d0
loc_010E9E:
	move.w	d0,$46(a3)
loc_010EA2:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	move.b	$6A(a3),-(sp)
	cmpi.l	#$15F9,$2A(a2)
	blt.w	loc_010EC6
	move.b	#$1E,$6A(a3)
loc_010EC6:
	jsr	(sub_01EDE8).l
	move.b	(sp)+,$6A(a3)
	rts
loc_010ED2:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	move.b	$6A(a3),-(sp)
	cmpi.l	#$15F9,$2A(a2)
	blt.w	loc_010EF6
	move.b	#$1E,$6A(a3)
loc_010EF6:
	jsr	(sub_01EDE8).l
	move.b	(sp)+,$6A(a3)
	jmp	(sub_01DA26).l
loc_010F06:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_010F08:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_010F36
	move.w	#$28,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_010F24
	bra.w	loc_00F6EA
loc_010F24:
	move.w	#$29,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_010F36
	bra.w	loc_00F6EA
loc_010F36:
	btst	#5,$62(a3)
	bne.w	loc_011214
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_011214
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_010F78
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_010F78:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_010F90
	moveq	#$4,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bpl.w	loc_00F6EA
loc_010F90:
	sub.b	d7,$40(a3)
	bpl.w	loc_011202
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_010FB4
	tst.b	$40(a3)
	beq.w	loc_010FB4
	subq.b	#1,$40(a3)
loc_010FB4:
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_010FC6
	move.w	$34(a3),d1
	bmi.w	loc_011214
loc_010FC6:
	cmp.w	#$5,d1	; general form
	bne.w	loc_0110CE
	move.w	#$1,d1
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_010FE2
	neg.w	d1
loc_010FE2:
	eor.w	d0,d1
	bmi.w	loc_01108E
	btst	#4,$30(a1)
	bne.w	loc_0111E6
	move.w	#$76,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_011006
	neg.w	d1
loc_011006:
	cmp.w	d0,d1
	blt.w	loc_0111CE
loc_01100C:
	move.w	#$1,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_011024
	adda.w	#$300,a0
loc_011024:
	bsr.w	sub_011B4C
	move.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_011038
	neg.w	d0
loc_011038:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_011056
	move.w	(a0),d0
	move.w	#$E2,d1
	btst	#7,$62(a3)
	beq.w	loc_011052
	neg.w	d1
loc_011052:
	bra.w	loc_0111FA
loc_011056:
	move.w	(a0),d1
	asr.w	#2,d1
	move.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	move.w	d0,-(sp)
	move.w	$14(a0),d0
	move.w	#$11E,d1
	btst	#7,$62(a3)
	beq.w	loc_011076
	neg.w	d1
loc_011076:
	move.w	d1,-(sp)
	sub.w	d0,d1
	asr.w	#2,d1
	move.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	sub.w	(sp)+,d0
	neg.w	d0
	move.w	d0,d1
	move.w	(sp)+,d0
	bra.w	loc_0111FA
loc_01108E:
	move.w	#$51,d0
	btst	#7,$62(a3)
	bne.w	loc_01109E
	neg.w	d0
loc_01109E:
	btst	#4,$30(a1)
	bne.w	loc_0111D2
	movem.w	d0,-(sp)
	move.w	#$76,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_0110C0
	neg.w	d1
loc_0110C0:
	cmp.w	d0,d1
	movem.w	(sp)+,d0
	blt.w	loc_0111D2
	bra.w	loc_01100C
loc_0110CE:
	move.w	#$1,d1
	move.w	(ram_B760).w,d0
	btst	#7,$62(a3)
	bne.w	loc_0110E2
	neg.w	d1
loc_0110E2:
	eor.w	d0,d1
	bmi.w	loc_01118E
	btst	#4,$30(a1)
	bne.w	loc_0111E6
	move.w	#$76,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_011106
	neg.w	d1
loc_011106:
	cmp.w	d0,d1
	blt.w	loc_0111CE
loc_01110C:
	move.w	#$2,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_011124
	adda.w	#$300,a0
loc_011124:
	bsr.w	sub_011B4C
	move.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_011138
	neg.w	d0
loc_011138:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_011156
	move.w	(a0),d0
	move.w	#$3A,d1
	btst	#7,$62(a3)
	beq.w	loc_011152
	neg.w	d1
loc_011152:
	bra.w	loc_0111FA
loc_011156:
	move.w	(a0),d1
	asr.w	#2,d1
	move.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	move.w	d0,-(sp)
	move.w	$14(a0),d0
	move.w	#$11E,d1
	btst	#7,$62(a3)
	beq.w	loc_011176
	neg.w	d1
loc_011176:
	move.w	d1,-(sp)
	sub.w	d0,d1
	asr.w	#2,d1
	move.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	sub.w	(sp)+,d0
	neg.w	d0
	move.w	d0,d1
	move.w	(sp)+,d0
	bra.w	loc_0111FA
loc_01118E:
	move.w	#$51,d0
	btst	#7,$62(a3)
	beq.w	loc_01119E
	neg.w	d0
loc_01119E:
	btst	#4,$30(a1)
	bne.w	loc_0111D2
	movem.w	d0,-(sp)
	move.w	#$76,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_0111C0
	neg.w	d1
loc_0111C0:
	cmp.w	d0,d1
	movem.w	(sp)+,d0
	blt.w	loc_0111D2
	bra.w	loc_01110C
loc_0111CE:
	move.w	(ram_B760).w,d0
loc_0111D2:
	move.w	#$67,d1
	btst	#7,$62(a3)
	beq.w	loc_0111E2
	neg.w	d1
loc_0111E2:
	bra.w	loc_0111FA
loc_0111E6:
	move.w	(ram_B788).w,d0
	asr.w	#8,d0
	add.w	(ram_B760).w,d0
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
loc_0111FA:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
loc_011202:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_011214(pc),a0
	jmp	(sub_01EDE8).l
loc_011214:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_011216:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_011244
	move.w	#$2C,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_011232
	bra.w	loc_00F6EA
loc_011232:
	move.w	#$2D,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_011244
	bra.w	loc_00F6EA
loc_011244:
	btst	#5,$62(a3)
	bne.w	loc_011420
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_011420
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_011286
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_011286:
	sub.b	d7,$40(a3)
	bpl.w	loc_0113F4
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_0112AA
	tst.b	$40(a3)
	beq.w	loc_0112AA
	subq.b	#1,$40(a3)
loc_0112AA:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_0112C2
	moveq	#$6,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bpl.w	loc_00F6EA
loc_0112C2:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_0112F6
	asl.w	#7,d1
	movea.l	#ram_B060,a0
	adda.w	d1,a0
	tst.w	$34(a0)
	bne.w	loc_0112F6
	move.b	$62(a0),d1
	move.b	$62(a3),d0
	eor.b	d1,d0
	btst	#6,d0
	beq.w	loc_0112F6
	clr.w	d0
	clr.w	d1
	bra.w	loc_0113EC
loc_0112F6:
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_011306
	neg.w	d1
loc_011306:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_011350
	move.w	(ram_B760).w,d0
	cmp.w	#$19,d0	; general form
	bgt.w	loc_01133A
	cmp.w	#$FFE7,d0	; general form
	blt.w	loc_01133A
	move.w	(ram_B788).w,d0
	asr.w	#8,d0
	add.w	(ram_B760).w,d0
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	bra.w	loc_0113EC
loc_01133A:
	clr.w	d0
	move.w	#$6C,d1
	btst	#7,$62(a3)
	beq.w	loc_01134C
	neg.w	d1
loc_01134C:
	bra.w	loc_0113EC
loc_011350:
	move.w	#$4,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_011368
	adda.w	#$300,a0
loc_011368:
	bsr.w	sub_011B4C
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	beq.w	loc_01137C
	neg.w	d0
loc_01137C:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_01139A
	clr.w	d0
	move.w	#$E7,d1
	btst	#7,$62(a3)
	beq.w	loc_011396
	neg.w	d1
loc_011396:
	bra.w	loc_0113EC
loc_01139A:
	move.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_0113AA
	neg.w	d0
loc_0113AA:
	cmp.w	#$11E,d0	; general form
	blt.w	loc_0113C8
	move.w	(a0),d0
	move.w	#$F1,d1
	btst	#7,$62(a3)
	beq.w	loc_0113C4
	neg.w	d1
loc_0113C4:
	bra.w	loc_0113EC
loc_0113C8:
	move.w	(ram_B760).w,d0
	sub.w	(a0),d0
	asr.w	#3,d0
	move.w	d0,d1
	add.w	d1,d0
	add.w	d1,d0
	add.w	(a0),d0
	move.w	(ram_B774).w,d1
	sub.w	$14(a0),d1
	asr.w	#3,d1
	move.w	d1,-(sp)
	add.w	(sp),d1
	add.w	(sp)+,d1
	add.w	$14(a0),d1
loc_0113EC:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
loc_0113F4:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	loc_011420(pc),a0
	move.b	$6A(a3),-(sp)
	cmpi.l	#$15F9,$2A(a2)
	blt.w	loc_011416
	move.b	#$1E,$6A(a3)
loc_011416:
	jsr	(sub_01EDE8).l
	move.b	(sp)+,$6A(a3)
loc_011420:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_011422:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_011450
	move.w	#$24,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_01143E
	bra.w	loc_00F6EA
loc_01143E:
	move.w	#$26,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_011450
	bra.w	loc_00F6EA
loc_011450:
	btst	#5,$62(a3)
	bne.w	loc_0116EC
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_0116EC
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	moveq	#$2,d0
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	beq.w	loc_011490
	neg.w	d1
loc_011490:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_00F6EA
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_00F6EA
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_0114C2
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_0114C2:
	sub.b	d7,$40(a3)
	bpl.w	loc_0116D8
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_0114EC
	btst	#6,(ram_C34C).w
	beq.w	loc_0114F0
	tst.b	$40(a3)
	beq.w	loc_0114F0
loc_0114EC:
	subq.b	#1,$40(a3)
loc_0114F0:
	movea.l	#sub_01D42E,a0
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_011508
	move.w	$34(a3),d1
	bmi.w	loc_0116EC
loc_011508:
	cmp.w	#$2,d1	; general form
	beq.w	loc_0115D4
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_011520
	neg.w	d1
loc_011520:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_011542
	move.w	#$FFAF,d0
	move.w	#$FF8A,d1
	btst	#7,$62(a3)
	bne.w	loc_01153E
	neg.w	d0
	neg.w	d1
loc_01153E:
	bra.w	loc_011698
loc_011542:
	move.w	#$80,d1
	move.w	#$FF88,d0
	btst	#7,$62(a3)
	bne.w	loc_011558
	neg.w	d0
	neg.w	d1
loc_011558:
	bra.w	loc_0115B6


; ----------------------------------------------------------------------
sub_01155C:
	movem.l	d0/a0,-(sp)
	move.w	#$5,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_011578
	adda.w	#$300,a0
loc_011578:
	bsr.w	sub_011B4C
	move.w	$14(a0),d2
	btst	#7,$62(a3)
	bne.w	loc_011592
	addi.w	#$F,d2
	bra.w	loc_011596
loc_011592:
	subi.w	#$F,d2
loc_011596:
	movem.l	(sp)+,d0/a0
	btst	#7,$62(a3)
	bne.w	loc_0115AE
	cmp.w	d1,d2
	blt.w	loc_0115B6
	bra.w	loc_0115B4
loc_0115AE:
	cmp.w	d1,d2
	bgt.w	loc_0115B6
loc_0115B4:
	move.w	d2,d1
loc_0115B6:
	move.w	(ram_B760).w,d2
	eor.w	d0,d2
	bpl.w	loc_0115D0
	move.w	#$FFF6,d0
	btst	#7,$62(a3)
	bne.w	loc_0115D0
	neg.w	d0
loc_0115D0:
	bra.w	loc_011698
loc_0115D4:
	move.w	(ram_B774).w,d1
	btst	#7,$62(a3)
	bne.w	loc_0115E4
	neg.w	d1
loc_0115E4:
	cmp.w	#$76,d1	; general form
	bgt.w	loc_011606
	move.w	#$51,d0
	move.w	#$FF8A,d1
	btst	#7,$62(a3)
	bne.w	loc_011602
	neg.w	d0
	neg.w	d1
loc_011602:
	bra.w	loc_011698
loc_011606:
	move.w	#$80,d1
	move.w	#$78,d0
	btst	#7,$62(a3)
	bne.w	loc_01161C
	neg.w	d0
	neg.w	d1
loc_01161C:
	bra.w	loc_01167A


; ----------------------------------------------------------------------
sub_011620:
	movem.l	d0/a0,-(sp)
	move.w	#$3,d0
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	bne.w	loc_01163C
	adda.w	#$300,a0
loc_01163C:
	bsr.w	sub_011B4C
	move.w	$14(a0),d2
	btst	#7,$62(a3)
	bne.w	loc_011656
	addi.w	#$F,d2
	bra.w	loc_01165A
loc_011656:
	subi.w	#$F,d2
loc_01165A:
	movem.l	(sp)+,d0/a0
	btst	#7,$62(a3)
	bne.w	loc_011672
	cmp.w	d1,d2
	blt.w	loc_01167A
	bra.w	loc_011678
loc_011672:
	cmp.w	d1,d2
	bgt.w	loc_01167A
loc_011678:
	move.w	d2,d1
loc_01167A:
	move.w	(ram_B760).w,d2
	eor.w	d0,d2
	bpl.w	loc_011694
	move.w	#$A,d0
	btst	#7,$62(a3)
	bne.w	loc_011694
	neg.w	d0
loc_011694:
	bra.w	loc_011698
loc_011698:
	btst	#4,$30(a2)
	beq.w	loc_0116D0
	btst	#7,$62(a3)
	bne.w	loc_0116C0
	cmp.w	(ram_B774).w,d1
	bgt.w	loc_0116D0
	move.w	(ram_B774).w,d1
	addi.w	#$A,d1
	bra.w	loc_0116D0
loc_0116C0:
	cmp.w	(ram_B774).w,d1
	blt.w	loc_0116D0
	move.w	(ram_B774).w,d1
	subi.w	#$A,d1
loc_0116D0:
	move.w	d0,$44(a3)
	move.w	d1,$46(a3)
loc_0116D8:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_0116EC:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_0116EE:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_01171C
	move.w	#$2E,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_01170A
	bra.w	loc_00F6EA
loc_01170A:
	move.w	#$2F,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_01171C
	bra.w	loc_00F6EA
loc_01171C:
	btst	#5,$62(a3)
	bne.w	loc_01190A
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_01190A
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_011762
	st	$48(a3)
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_011762:
	sub.b	d7,$40(a3)
	bpl.w	loc_0118EA
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_011786
	tst.b	$40(a3)
	beq.w	loc_011786
	subq.b	#1,$40(a3)
loc_011786:
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_01179E
	moveq	#$5,d0
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
loc_01179E:
	move.w	(ram_B78A).w,d0
	asr.w	#8,d0
	add.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_0117B4
	neg.w	d0
loc_0117B4:
	clr.w	d2
	jsr	(sub_1D3B76).l
	cmp.w	$48(a3),d2
	bne.w	loc_0117D4
	move.w	(FrameCounter).w,d0
	andi.w	#$7F,d0
	cmp.w	#$2,d0	; general form
	bgt.w	loc_0118EA
loc_0117D4:
	move.w	d2,$48(a3)
	move.w	$16(a2),d0
	asl.w	#1,d0
	lea	(ram_DEFE).w,a0
	move.w	$0(a0,d0.w),d0
	tst.w	d0
	beq.s	loc_0117FE
	cmp.w	#$1,d0	; general form
	beq.s	loc_011806
	cmp.w	#$2,d0	; general form
	beq.s	loc_01180E
	cmp.w	#$3,d0	; general form
	beq.s	loc_011816
	bra.s	loc_01181E
loc_0117FE:
	lea	dat_01184A(pc),a0
	bra.w	loc_011822
loc_011806:
	lea	dat_01186A(pc),a0
	bra.w	loc_011822
loc_01180E:
	lea	dat_01188A(pc),a0
	bra.w	loc_011822
loc_011816:
	lea	dat_0118AA(pc),a0
	bra.w	loc_011822
loc_01181E:
	lea	dat_0118CA(pc),a0
loc_011822:
	move.w	$2(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$0(a0,d2.w),d0
	move.w	d0,$44(a3)
	move.w	$6(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$4(a0,d2.w),d0
	move.w	d0,$46(a3)
	bra.w	loc_0118EA
dat_01184A:
	dc.w	$0000,$003C,$FF9C,$000A,$0000,$003C,$005A,$000A
	dc.w	$0000,$0028,$00E9,$001E,$0000,$0050,$00E9,$0014
dat_01186A:
	dc.w	$0000,$003C,$FFAB,$000A,$0000,$003C,$004B,$000A
	dc.w	$0000,$0028,$00DA,$001E,$0000,$0050,$00DA,$0014
dat_01188A:
	dc.w	$0000,$003C,$FFBA,$000A,$0000,$003C,$003C,$000A
	dc.w	$0000,$0028,$00CB,$001E,$0000,$0050,$00CB,$0014
dat_0118AA:
	dc.w	$0000,$003C,$FFC9,$000A,$0000,$003C,$002D,$000A
	dc.w	$0000,$0028,$00BC,$001E,$0000,$0050,$00BC,$0014
dat_0118CA:
	dc.w	$0000,$003C,$FFD8,$000A,$0000,$003C,$001E,$000A
	dc.w	$0000,$0028,$00AD,$001E,$0000,$0050,$00AD,$0014
loc_0118EA:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_0118FE
	neg.w	d1
loc_0118FE:
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_01190A:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_01190C:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_01193A
	move.w	#$2A,d0
	cmpi.w	#$5,$24(a2)
	bne.w	loc_011928
	bra.w	loc_00F6EA
loc_011928:
	move.w	#$2B,d0
	cmpi.w	#$4,$24(a2)
	bne.w	loc_01193A
	bra.w	loc_00F6EA
loc_01193A:
	btst	#5,$62(a3)
	bne.w	loc_011B4A
	btst	#0,(ram_C33A).w
	bne.w	loc_00FC6A
	jsr	(sub_01B8B8).l
	btst	#3,$62(a3)
	bne.w	loc_011B4A
	jsr	(sub_0139DC).l
	bne.w	loc_00F6EA
	bclr	#1,$62(a3)
	beq.w	loc_011980
	st	$48(a3)
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
loc_011980:
	sub.b	d7,$40(a3)
	bpl.w	loc_011B0C
	move.b	$6C(a3),$40(a3)
	btst	#6,(ram_C34C).w
	beq.w	loc_0119A4
	tst.b	$40(a3)
	beq.w	loc_0119A4
	subq.b	#1,$40(a3)
loc_0119A4:
	moveq	#$3,d0
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_0119BC
	subq.w	#6,d1
	move.w	$52(a3),d2
	subq.w	#6,d2
	eor.w	d2,d1
	bmi.w	loc_00F6EA
loc_0119BC:
	move.w	(ram_B774).w,d0
	move.w	(ram_B78A).w,d3
	asr.w	#6,d3
	add.w	d0,d3
	btst	#7,$62(a3)
	bne.w	loc_0119D6
	neg.w	d0
	neg.w	d3
loc_0119D6:
	clr.w	d2
	jsr	(sub_1D3C7A).l
	cmp.w	$48(a3),d2
	bne.w	loc_0119F6
	move.w	(FrameCounter).w,d0
	andi.w	#$7F,d0
	cmp.w	#$2,d0	; general form
	bgt.w	loc_011B0C
loc_0119F6:
	move.w	d2,$48(a3)
	move.w	$16(a2),d0
	asl.w	#1,d0
	lea	(ram_DEFE).w,a0
	move.w	$0(a0,d0.w),d0
	tst.w	d0
	beq.s	loc_011A20
	cmp.w	#$1,d0	; general form
	beq.s	loc_011A28
	cmp.w	#$2,d0	; general form
	beq.s	loc_011A30
	cmp.w	#$3,d0	; general form
	beq.s	loc_011A38
	bra.s	loc_011A40
loc_011A20:
	lea	dat_011A6C(pc),a0
	bra.w	loc_011A44
loc_011A28:
	lea	dat_011A8C(pc),a0
	bra.w	loc_011A44
loc_011A30:
	lea	dat_011AAC(pc),a0
	bra.w	loc_011A44
loc_011A38:
	lea	dat_011ACC(pc),a0
	bra.w	loc_011A44
loc_011A40:
	lea	dat_011AEC(pc),a0
loc_011A44:
	move.w	$2(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$0(a0,d2.w),d0
	move.w	d0,$44(a3)
	move.w	$6(a0,d2.w),d0
	jsr	(sub_0200EA).l
	add.w	$4(a0,d2.w),d0
	move.w	d0,$46(a3)
	bra.w	loc_011B0C
dat_011A6C:
	dc.w	$0050,$0014,$FF9C,$000A,$0064,$0014,$0076,$0005
	dc.w	$0047,$0032,$0104,$0014,$0050,$001E,$0118,$0014
dat_011A8C:
	dc.w	$0050,$0014,$FFAB,$000A,$0064,$0014,$0067,$0005
	dc.w	$0047,$0032,$00F5,$0014,$0050,$001E,$0109,$0014
dat_011AAC:
	dc.w	$0050,$0014,$FFBA,$000A,$0064,$0014,$0058,$0005
	dc.w	$0047,$0032,$00E6,$0014,$0050,$001E,$00FA,$0014
dat_011ACC:
	dc.w	$0050,$0014,$FFC9,$000A,$0064,$0014,$0049,$0005
	dc.w	$0047,$0032,$00D7,$0014,$0050,$001E,$00EB,$0014
dat_011AEC:
	dc.w	$0050,$0014,$FFD8,$000A,$0064,$0014,$003A,$0005
	dc.w	$0047,$0032,$00C8,$0014,$0050,$001E,$00DC,$0014
loc_011B0C:
	move.w	$44(a3),d0
	clr.w	d1
	move.b	$65(a3),d1
	bpl.w	loc_011B22
	move.w	$34(a3),d1
	bmi.w	loc_011B4A
loc_011B22:
	cmp.w	#$5,d1	; general form
	beq.w	loc_011B2C
	neg.w	d0
loc_011B2C:
	move.w	$46(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_011B3E
	neg.w	d0
	neg.w	d1
loc_011B3E:
	movea.l	#sub_01D42E,a0
	jmp	(sub_01EDE8).l
loc_011B4A:
	rts


; ----------------------------------------------------------------------
; called from $00FDA6, $0101D4, $010CEA, $010DD0, $011024, $011124, $011368, $011578 (+1 more)
sub_011B4C:
	move.w	d1,-(sp)
	move.w	#$5,d1
loc_011B52:
	btst	#2,$63(a0)
	bne.w	loc_011B78
	tst.b	$65(a0)
	bmi.w	loc_011B70
	cmp.b	$65(a0),d0
	bne.w	loc_011B78
	bra.w	loc_011B86
loc_011B70:
	cmp.w	$34(a0),d0
	beq.w	loc_011B86
loc_011B78:
	adda.w	#$80,a0
	dbra	d1,loc_011B52
	movea.l	#ram_B760,a0
loc_011B86:
	move.w	(sp)+,d1
	rts

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $00F6CA
sub_011B8C:
	bclr	#1,$62(a3)
	beq.w	loc_011B9C
	move.w	#$A,$40(a3)
loc_011B9C:
	btst	#2,(ram_C34A).w
	beq.w	loc_011CB4
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_011BDE
	tst.w	$40(a3)
	beq.w	loc_011CB4
	subq.w	#1,$40(a3)
	bne.w	loc_011CB4
	move.w	#$A,$48(a3)
	move.w	#$A,d0
	jsr	(Random).l
	addq.w	#5,d0
	move.w	d0,(ram_DE98).w
	jsr	(sub_012E00).l
loc_011BDE:
	tst.w	$58(a3)
	bne.w	loc_011C00
	tst.w	$48(a3)
	bmi.w	loc_011C00
	subq.w	#1,$48(a3)
	bpl.w	loc_011C00
	move.w	#$870,d1
	jsr	(sub_01F3B2).l
loc_011C00:
	tst.w	(ram_DE98).w
	beq.w	loc_011C10
	subq.w	#1,(ram_DE98).w
	bra.w	loc_011CB4
loc_011C10:
	addq.w	#1,(ram_DE90).w
	cmpi.w	#$A,(ram_DE90).w
	bne.w	loc_011C24
	jmp	(sub_1E5E86).l
loc_011C24:
	movem.l	a0-a2,-(sp)
	movea.l	#ram_B360,a0
	cmpi.w	#$6,$52(a3)
	bne.w	loc_011C3E
	movea.l	#ram_B3E0,a0
loc_011C3E:
	move.w	#$30,d0
	jsr	(sub_01F172).l
	exg	a0,a3
	move.w	#$33,d0
	jsr	(sub_01F172).l
	move.w	$52(a3),d0
	move.w	d0,(ram_B7C0).w
	exg	a0,a3
	move.l	a3,-(sp)
	movea.w	#$B760,a3
	move.w	#$18,d0
	jsr	(sub_01F172).l
	movea.l	(sp)+,a3
	clr.w	$40(a3)
	clr.w	$48(a3)
	bclr	#2,(ram_DEA2).w
	bclr	#0,(ram_C344).w
	jsr	(sub_1E5530).l
	move.w	(ram_DE90).w,d0
	andi.w	#$1,d0
	beq.w	loc_011C9A
	neg.w	(ram_B760).w
loc_011C9A:
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	clr.w	(ram_B778).w
	clr.w	(ram_B78C).w
	bclr	#2,(ram_B7C2).w
	movem.l	(sp)+,a0-a2
loc_011CB4:
	rts


; ----------------------------------------------------------------------
; called from $00F6CE
sub_011CB6:
	bclr	#1,$62(a3)
	beq.w	loc_011CCE
	clr.w	(ram_DE9A).w
	clr.w	$42(a3)
	move.w	#$78,$44(a3)
loc_011CCE:
	btst	#2,(ram_C34A).w
	beq.w	loc_011D10
	move.b	#$64,$5E(a3)
	tst.w	$42(a3)
	beq.w	loc_011D0E
	btst	#3,(ram_C33C).w
	bne.w	loc_011D0E
	tst.w	$44(a3)
	bpl.w	loc_011D0A
	bclr	#2,(ram_C34A).w
	move.w	#$B4,$44(a3)
	jmp	(loc_1E6556).l
loc_011D0A:
	subq.w	#1,$44(a3)
loc_011D0E:
	rts
loc_011D10:
	tst.w	$42(a3)
	beq.s	loc_011D0E
	subq.w	#1,$44(a3)
	bpl.s	loc_011D0E
	move.w	#$B4,(ram_DE96).w
	move.l	a3,-(sp)
	movea.l	#ram_B760,a3
	move.w	#$31,d0
	jsr	(sub_01F172).l
	movea.l	(sp)+,a3
	bset	#1,$62(a3)
	addq.w	#1,(ram_DE94).w
	cmpi.w	#$3,(ram_DE94).w
	blt.w	loc_011D62
	clr.w	(ram_DE94).w
	addq.w	#1,(ram_DE92).w
	cmpi.w	#$3,(ram_DE92).w
	blt.w	loc_011D62
	jmp	(sub_1E5E86).l
loc_011D62:
	jmp	(loc_0191EE).l

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $00F6D6
sub_011D6A:
	bclr	#1,$62(a3)
	beq.w	loc_011D78
	clr.w	$40(a3)
loc_011D78:
	clr.w	$28(a3)
	clr.w	$2A(a3)
	bset	#0,$62(a3)
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_011E14
	btst	#2,(ram_C34A).w
	beq.w	loc_011E12
	move.w	(ram_B060).w,d0
	sub.w	(a3),d0
	move.w	(ram_B074).w,d1
	cmp.w	#$76,d1	; general form
	bgt.w	loc_011DC0
	tst.w	(ram_D344).w
	bne.w	loc_011E2A
	jmp	(sub_1E5E86).l

	dc.b	$60,$00,$00,$6C
loc_011DC0:
	sub.w	$14(a3),d1
	jsr	(sub_01F186).l
	tst.w	(a3)
	bpl.w	loc_011DE0
	cmp.w	#$2,d0	; general form
	bne.w	loc_011DEC
	move.w	#$3,d0
	bra.w	loc_011DEC
loc_011DE0:
	cmp.w	#$6,d0	; general form
	bne.w	loc_011DEC
	move.w	#$5,d0
loc_011DEC:
	move.w	d0,(ram_BF10).w
	bset	#3,d0
	bset	#2,(ram_C342).w
	jsr	(sub_0132A0).l
	move.w	#$A,$40(a3)
	move.w	#$78,(ram_DE98).w
	bclr	#2,(ram_C342).w
loc_011E12:
	rts
loc_011E14:
	tst.w	$40(a3)
	beq.w	loc_011E2A
	sub.w	d7,(ram_DE98).w
	bpl.w	loc_011E2A
	jsr	(sub_1E6630).l
loc_011E2A:
	tst.w	$58(a3)
	bne.s	loc_011E12
	move.w	#$870,d1
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $00F6D2
sub_011E3A:
	bclr	#1,$62(a3)
	beq.w	loc_011E48
	clr.w	$40(a3)
loc_011E48:
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_011E68
	tst.w	$40(a3)
	bne.w	loc_011E68
	move.w	#$78,(ram_DE98).w
	move.w	#$A,$40(a3)
loc_011E68:
	rts


; ----------------------------------------------------------------------
; called from $00F6DA
sub_011E6A:
	bclr	#1,$62(a3)
	beq.w	loc_011E78
	clr.w	$40(a3)
loc_011E78:
	bset	#2,$62(a3)
	tst.w	$40(a3)
	beq.w	loc_011E9A
	cmpi.w	#$3886,$58(a3)
	bne.w	loc_011EAC
	move.w	#$389C,d1
	jmp	(sub_01F3B2).l
loc_011E9A:
	tst.w	$58(a3)
	bne.w	loc_011EAC
	move.w	#$3886,d1
	jsr	(sub_01F3B2).l
loc_011EAC:
	rts


; ----------------------------------------------------------------------
; called from $00F6DE
sub_011EAE:
	bclr	#1,$62(a3)
	beq.w	loc_011EBC
	clr.w	(ram_DE8E).w
loc_011EBC:
	jsr	(sub_02698A).l
	move.w	$14(a3),d0
	move.w	d0,(ram_BFE0).w
	cmpi.w	#$B2,(ram_BFE0).w
	ble.w	loc_011EDA
	move.w	#$B2,(ram_BFE0).w
loc_011EDA:
	cmpi.w	#$FF9E,(ram_BFE0).w
	bge.w	loc_011EEA
	move.w	#$FF9E,(ram_BFE0).w
loc_011EEA:
	tst.w	(ram_D344).w
	beq.w	loc_011FD6
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_011FF2
	move.w	(ram_DE8E).w,d0
	muls.w	#$C,d0
	movea.l	#dat_011FF4,a0
	cmpi.w	#$FFFF,$0(a0,d0.w)
	beq.w	loc_011F70
	move.w	$0(a0,d0.w),d1
	cmp.w	(a3),d1
	bgt.w	loc_011FF2
	move.w	$2(a0,d0.w),d1
	cmp.w	$14(a3),d1
	blt.w	loc_011FF2
	move.w	$4(a0,d0.w),d1
	cmp.w	(a3),d1
	blt.w	loc_011FF2
	move.w	$6(a0,d0.w),d1
	cmp.w	$14(a3),d1
	bgt.w	loc_011FF2
	move.w	$8(a0,d0.w),d1
	beq.w	loc_011F5C
	move.w	$28(a3),d2
	eor.w	d2,d1
	bmi.w	loc_011FF2
loc_011F54:
	addq.w	#1,(ram_DE8E).w
	bra.w	loc_011FF2
loc_011F5C:
	move.w	$A(a0,d0.w),d1
	beq.w	loc_011FF2
	move.w	$2A(a3),d2
	eor.w	d2,d1
	bmi.w	loc_011FF2
	bra.s	loc_011F54
loc_011F70:
	clr.w	(ram_DE8E).w
	move.w	$52(a3),d0
	cmp.w	#$2,d0	; general form
	beq.w	loc_011FD6
	addq.w	#1,d0
	move.w	d0,(ram_C388).w
	st	(ram_B7C0).w
	move.l	a3,-(sp)
	asl.w	#7,d0
	movea.l	#ram_B060,a3
	adda.w	d0,a3
	move.w	#$38,d0
	jsr	(sub_01F172).l
	bset	#3,$62(a3)
	movea.l	(sp)+,a3
	move.w	#$51,(ram_B760).w
	move.w	#$F4,(ram_B774).w
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	bclr	#3,$62(a3)
	move.w	#$870,d1
	jsr	(sub_01F3B2).l
	move.w	#$30,d0
	jmp	(sub_01F172).l
loc_011FD6:
	move.w	#$30,d0
	jsr	(sub_01F172).l
	bclr	#3,$62(a3)
	move.w	#$FFFF,(ram_C388).w
	jsr	(sub_1E5E86).l
loc_011FF2:
	rts
dat_011FF4:
	dc.w	$0051,$00DB,$0096,$00D3,$0000,$FFFF,$0051,$00DB
	dc.w	$0059,$00A3,$FFFF,$0000,$0033,$00DB,$003B,$00A3
	dc.w	$FFFF,$0000,$0033,$00A3,$003B,$005D,$0001,$0000
	dc.w	$006F,$00DB,$0077,$008F,$0001,$0000,$006F,$008F
	dc.w	$0077,$005D,$FFFF,$0000,$0051,$008F,$0059,$005D
	dc.w	$FFFF,$0000,$0051,$005D,$0059,$0028,$0001,$0000
	dc.w	$006F,$005D,$0077,$0028,$0001,$0000,$006F,$0028
	dc.w	$0077,$FFDD,$FFFF,$0000,$0033,$005D,$003B,$0014
	dc.w	$FFFF,$0000,$0033,$0014,$003B,$FFDD,$0001,$0000
	dc.w	$0051,$0014,$0059,$FFDD,$0001,$0000,$0051,$FFDD
	dc.w	$0096,$FFD5,$0000,$FFFF,$FF6A,$FF8A,$0096,$FF82
	dc.w	$0000,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $00F6E2
sub_0120AA:
	move.w	#$38E8,d1
	bsr.w	sub_01211E
	bne.w	loc_0120BA
	move.w	#$390E,d1
loc_0120BA:
	jsr	(sub_01F3B2).l
	bclr	#3,$4(a3)
	clr.l	$28(a3)
	clr.l	$2A(a3)
	move.w	$1C(a3),d0
	move.w	d0,(a3)
	move.w	$20(a3),d0
	move.w	d0,$14(a3)
	move.b	#$64,$5E(a3)
	rts


; ----------------------------------------------------------------------
; called from $00F6E6
sub_0120E4:
	move.w	#$38C2,d1
	bsr.w	sub_01211E
	bne.w	loc_0120F4
	move.w	#$390E,d1
loc_0120F4:
	jsr	(sub_01F3B2).l
	bclr	#3,$4(a3)
	clr.l	$28(a3)
	clr.l	$2A(a3)
	move.w	$1C(a3),d0
	move.w	d0,(a3)
	move.w	$20(a3),d0
	move.w	d0,$14(a3)
	move.b	#$64,$5E(a3)
	rts


; ----------------------------------------------------------------------
; called from $0120AE, $0120E8
sub_01211E:
	move.w	$44(a3),d0
	asl.w	#1,d0
	move.l	a0,-(sp)
	movea.l	#dat_012148,a0
	move.w	$0(a0,d0.w),d0
	movea.l	(sp)+,a0
	cmp.w	(ram_DE8E).w,d0
	ble.w	loc_012142
	move.w	#$1,d0
	bra.w	loc_012146
loc_012142:
	move.w	#$0,d0
loc_012146:
	rts
dat_012148:
	dc.w	$0000,$0002,$0004,$0006,$0008,$000A,$000C,$000D
dat_012158:
	incbin	"data/bin/data_012158.bin"	; 984 bytes
dat_012530:
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
	dc.w	$FFFF,$FFFF,$0046,$004A,$0044,$0048,$003C,$003E
	dc.w	$0042,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$004C
	dc.w	$004E,$FFFF,$FFFF,$FFFF,$FFFF
dat_01256A:
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$0036,$0038,$FFFF
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $00C22E, $00D44A
sub_0125A6:
	tst.w	(ram_D280).w
	bne.w	loc_00C926
	btst	#4,(ram_C34C).w
	bne.w	loc_00C926
	jsr	(sub_022566).l
	bset	#1,$30(a2)
	bne.w	loc_00C926
	btst	#3,(ram_C346).w
	bne.w	loc_0125D8
	bclr	#2,(ram_C33C).w
loc_0125D8:
	bclr	#3,(ram_C33C).w
	bset	#3,$63(a3)

; ----------------------------------------------------------------------
; called from $00C2E8, $00C30C, $0127A8
sub_0125E4:
	btst	#0,(ram_C33A).w
	beq.w	loc_012608
	bsr.w	sub_0126BC
	cmpi.w	#$F,(TextY).w
	blt.w	loc_012618
	jsr	(sub_1E30D6).l
	bclr	#2,(ram_C358).w
loc_012608:
	bset	#2,(ram_C358).w
	bne.w	loc_012618
	jsr	(sub_022218).l
loc_012618:
	bsr.w	sub_0126BC
	cmpi.w	#$F,(TextY).w
	blt.w	loc_012630
	bset	#0,(ram_C340).w
	bra.w	loc_01263A
loc_012630:
	jsr	(sub_0284C2).l
	bsr.w	sub_0126BC
loc_01263A:
	jsr	(Text_PrintDigitsBig).l
	subq.w	#2,(TextY).w
	addq.w	#1,(TextX).w
	moveq	#$2,d4
loc_01264A:
	move.w	d4,d0
	bsr.w	sub_012700
	tst.w	d0
	bmi.w	loc_0126A4
	btst	#1,$30(a2)
	bne.w	loc_01266C
	cmp.w	$2E(a2),d4
	bne.w	loc_0126A0
	move.w	$16(a2),d0
loc_01266C:
	movea.w	#$BFF4,a1
	move.l	#dat_044120,(a1)
	add.b	d4,$2(a1)
	jsr	(Text_Print_Worker).l
	move.w	d0,-(sp)
	movea.l	#dat_0289AC,a1
	jsr	(List_Skip).l
	jsr	(Text_Print_Worker).l
	move.w	(sp)+,d0
	jsr	(sub_022382).l
	subq.w	#5,(TextX).w
loc_0126A0:
	subq.w	#1,(TextY).w
loc_0126A4:
	dbra	d4,loc_01264A
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	addq.w	#2,(TextX).w
	jmp	(Text_Print_Worker).l


; ----------------------------------------------------------------------
; called from $0125EE, $012618, $012636, $012844
sub_0126BC:
	clr.w	d0
	cmpa.w	#$C732,a2
	bne.w	loc_0126CA
	eori.w	#$16,d0
loc_0126CA:
	btst	#1,(ram_C33A).w
	beq.w	loc_0126D8
	eori.w	#$16,d0
loc_0126D8:
	jsr	(Text_Print).l
inl_0126DE:
	dc.w	loc_0126E4-inl_0126DE
	dc.b	$BF,$16,$00,$00
loc_0126E4:
	add.w	d0,(TextY).w
	moveq	#$2,d0
	bsr.w	sub_012700
	moveq	#$6,d1
	tst.w	d0
	bpl.w	loc_0126FC
	subq.w	#1,d1
	addq.w	#1,(TextY).w
loc_0126FC:
	moveq	#$9,d0
	rts


; ----------------------------------------------------------------------
; called from $01264C, $0126EA, $01280E
sub_012700:
	movem.l	d1/d2,-(sp)
	move.w	$3C2(a2),d2
	cmpa.w	#$C732,a2
	beq.w	loc_012714
	move.w	-$37A(a2),d2
loc_012714:
	sub.w	$24(a2),d2
	beq.w	loc_01272A
	addi.w	#$15,d0
	tst.w	d2
	bmi.w	loc_01272A
	addi.w	#$15,d0
loc_01272A:
	move.w	$16(a2),d1
	add.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
	lea	dat_012744(pc),a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movem.l	(sp)+,d1/d2
	rts
dat_012744:
	dc.w	$0001,$0201,$0200,$0200,$0100,$0102,$0001,$0200
	dc.w	$0102,$0001,$0203,$04FF,$0304,$FF03,$04FF,$0304
	dc.w	$FF04,$03FF,$0304,$FF03,$04FF,$0506,$FF05,$06FF
	dc.w	$0506,$FF05,$06FF,$0506,$FF05,$06FF,$0605,$FFFF
loc_012784:
	movem.w	d1/d4,-(sp)
	movea.w	#$C732,a2
	btst	#6,$62(a3)
	beq.w	loc_01279A
	adda.w	#$39E,a2
loc_01279A:
	bclr	#0,$30(a2)
	beq.w	loc_0127AC
	bsr.w	sub_01283A
	bsr.w	sub_0125E4
loc_0127AC:
	movem.w	(sp)+,d1/d4
	clr.w	d2
	btst	#6,d1
	bne.w	loc_0127F4
	addq.w	#1,d2
	btst	#4,d1
	bne.w	sub_012808
	addq.w	#1,d2
	btst	#5,d1
	bne.w	sub_012808
	btst	#3,$62(a3)
	beq.w	loc_0127EC
	btst	#5,$62(a3)
	bne.w	loc_0127EC
	btst	#0,$63(a3)
	beq.w	loc_0127EE
loc_0127EC:
	rts
loc_0127EE:
	jmp	(loc_01F3C8).l
loc_0127F4:
	movem.l	a0,-(sp)
	movea.l	#ram_D30A,a0
	move.w	#$3E8,$0(a0,d4.w)
	movem.l	(sp)+,a0

; ----------------------------------------------------------------------
; called from $00C306, $0127C0, $0127CA
sub_012808:
	move.w	d2,d0
	move.w	d2,$2E(a2)
	bsr.w	sub_012700
	tst.w	d0
	bmi.w	loc_01327A
	bclr	#3,$63(a3)
	bset	#3,$62(a3)
	jsr	(sub_022566).l
	bclr	#1,$30(a2)
	move.w	d0,$16(a2)
	jsr	(sub_025122).l

; ----------------------------------------------------------------------
; called from $00F184, $00F18E, $0127A4, $0282E0, $0282EA
sub_01283A:
	btst	#4,(ram_C350).w
	bne.w	loc_01327A
	bsr.w	sub_0126BC
	cmpi.w	#$F,(TextY).w
	blt.w	loc_012858
	bclr	#0,(ram_C340).w
loc_012858:
	addq.w	#1,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	bclr	#2,(ram_C358).w
	bset	#3,(ram_C358).w
	jmp	(sub_022296).l


; ----------------------------------------------------------------------
; called from $029BCE
sub_012876:
	rts


; ----------------------------------------------------------------------
; called from $026B46, $026B70, $1CF7E2, $1D0C60
sub_012878:
	movem.l	d0-d7/a1-a6,-(sp)
	bsr.w	sub_012C84
	bne.w	loc_0128A6
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_012898
	movea.l	#RosterTable,a0
loc_012898:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	adda.w	$6(a0),a0
	bra.w	loc_0129AE
loc_0128A6:
	movea.l	#ram_D18D,a3
	move.w	#$0,d5
	bsr.w	sub_012B74
	movea.l	#ram_D193,a3
	move.w	#$1,d5
	bsr.w	sub_012B74
	movea.l	#ram_D1B1,a3
	move.w	#$2,d5
	bsr.w	sub_012B74
	movea.l	#ram_D1CF,a3
	move.w	#$3,d5
	bsr.w	sub_012B74
	movea.l	#ram_D1ED,a3
	move.w	#$4,d5
	bsr.w	sub_012B74
	movea.l	#ram_D20B,a3
	move.w	#$5,d5
	bsr.w	sub_012B74
	movea.l	#ram_D14C,a0
	bsr.w	sub_012B6A
	move.w	#$2,d1
	bsr.w	sub_012A1E
	move.l	(ram_D14C).w,(ram_D154).w
	move.l	(ram_D150).w,(ram_D158).w
	bsr.w	sub_012A86
	movea.l	#ram_D15C,a0
	bsr.w	sub_012B6A
	move.w	#$3,d1
	bsr.w	sub_012A1E
	bsr.w	sub_012A86
	movea.l	#ram_D164,a0
	bsr.w	sub_012B6A
	move.w	#$4,d1
	bsr.w	sub_012A1E
	move.l	(ram_D14C).w,(ram_D16C).w
	move.l	(ram_D150).w,(ram_D170).w
	move.l	(ram_D15C).w,(ram_D174).w
	move.l	(ram_D160).w,(ram_D178).w
	bsr.w	sub_012A86
	movea.l	#ram_D1CF,a3
	move.w	#$FFFF,d5
	bsr.w	sub_012B74
	movea.l	#ram_D17C,a0
	bsr.w	sub_012B6A
	move.w	#$2,d1
	bsr.w	sub_0129B4
	move.w	#$2,d1
	bsr.w	sub_0129D4
	bsr.w	sub_012A86
	move.b	(ram_D17C).w,(ram_D184).w
	movea.l	#ram_D185,a0
	move.w	#$3,d1
	bsr.w	sub_0129B4
	move.w	#$4,d1
	bsr.w	sub_0129D4
	movea.l	#ram_D14C,a0
loc_0129AE:
	movem.l	(sp)+,d0-d7/a1-a6
	rts


; ----------------------------------------------------------------------
; called from $01297C, $01299C
sub_0129B4:
	movea.l	#ram_D193,a1
	movea.l	#dat_012B56,a2
	bsr.w	sub_012AD8
	movea.l	#ram_D1B1,a1
	movea.l	#dat_012B56,a2
	bra.w	sub_012AD8


; ----------------------------------------------------------------------
; called from $012984, $0129A4
sub_0129D4:
	movea.l	#ram_D1CF,a1
	movea.l	#dat_012B56,a2
	bsr.w	sub_012AD8
	addq.w	#1,d1
	movea.l	#ram_D1CF,a1
	movea.l	#dat_012B56,a2
	bsr.w	sub_012AD8
	addq.w	#1,d1
	movea.l	#ram_D1CF,a1
	movea.l	#dat_012B56,a2
	bsr.w	sub_012AD8
	addq.w	#1,d1
	movea.l	#ram_D1CF,a1
	movea.l	#dat_012B56,a2
	bsr.w	sub_012AD8
	clr.b	(a0)+
	rts


; ----------------------------------------------------------------------
; called from $012908, $01292A, $012940
sub_012A1E:
	movea.l	#ram_D193,a1
	movea.l	#dat_012B42,a2
	bsr.w	sub_012AD8
	movea.l	#ram_D1B1,a1
	movea.l	#dat_012B42,a2
	bsr.w	sub_012AD8
	movea.l	#ram_D1CF,a1
	movea.l	#dat_012B2E,a2
	bsr.w	sub_012AD8
	movea.l	#ram_D1ED,a1
	movea.l	#dat_012B2E,a2
	bsr.w	sub_012AD8
	movea.l	#ram_D20B,a1
	movea.l	#dat_012B2E,a2
	bsr.w	sub_012AD8
	move.w	#$3,d1
	movea.l	#ram_D1ED,a1
	movea.l	#dat_012B2E,a2
	bsr.w	sub_012AD8
	clr.b	(a0)+
	rts


; ----------------------------------------------------------------------
; called from $012918, $01292E, $01295C, $012988
sub_012A86:
	movem.l	d0-d3/a0,-(sp)
	movea.l	#ram_D1ED,a0
	bsr.w	sub_012AC2
	movea.l	#ram_D1CF,a0
	bsr.w	sub_012AC2
	movea.l	#ram_D20B,a0
	bsr.w	sub_012AC2
	movea.l	#ram_D193,a0
	bsr.w	sub_012AC2
	movea.l	#ram_D1B1,a0
	bsr.w	sub_012AC2
	movem.l	(sp)+,d0-d3/a0
	rts


; ----------------------------------------------------------------------
; called from $012A90, $012A9A, $012AA4, $012AAE, $012AB8
sub_012AC2:
	move.b	(a0),d1
	ext.w	d1
	addq.w	#2,a0
	subq.w	#1,d1
	bmi.w	loc_012AD6
loc_012ACE:
	andi.b	#$7F,(a0)+
	dbra	d1,loc_012ACE
loc_012AD6:
	rts


; ----------------------------------------------------------------------
; called from $0129C0, $0129D0, $0129E0, $0129F2, $012A04, $012A16, $012A2A, $012A3A (+4 more)
sub_012AD8:
	bsr.w	sub_012AE6
	bne.w	loc_012AE4
	bsr.w	sub_012B10
loc_012AE4:
	rts


; ----------------------------------------------------------------------
; called from $012AD8, $012B1A
sub_012AE6:
	movem.w	d1,-(sp)
	subq.w	#1,d1
	cmp.b	(a1),d1
	movem.w	(sp)+,d1
	bgt.w	loc_012B0A
	move.b	$0(a1,d1.w),d0
	bmi.w	loc_012B0A
	addq.b	#1,d0
	move.b	d0,(a0)+
	ori.b	#$80,$0(a1,d1.w)
	rts
loc_012B0A:
	move.w	#$0,d0
	rts


; ----------------------------------------------------------------------
; called from $012AE0
sub_012B10:
	move.w	d1,-(sp)
loc_012B12:
	clr.w	d4
	addq.w	#1,d1
loc_012B16:
	movea.l	$0(a2,d4.w),a1
	bsr.s	sub_012AE6
	bne.w	loc_012B2A
	addq.w	#4,d4
	cmp.w	#$14,d4	; general form
	beq.s	loc_012B12
	bra.s	loc_012B16
loc_012B2A:
	move.w	(sp)+,d1
	rts
dat_012B2E:
	dc.w	$FFFF,$D1ED,$FFFF,$D20B,$FFFF,$D1CF,$FFFF,$D1B1
	dc.w	$FFFF,$D193
dat_012B42:
	dc.w	$FFFF,$D193,$FFFF,$D1B1,$FFFF,$D1ED,$FFFF,$D20B
	dc.w	$FFFF,$D1CF
dat_012B56:
	dc.w	$FFFF,$D193,$FFFF,$D1B1,$FFFF,$D1CF,$FFFF,$D1CF
	dc.w	$FFFF,$D1CF


; ----------------------------------------------------------------------
; called from $012900, $012922, $012938, $012974
sub_012B6A:
	move.b	(ram_D18F).w,d0
	addq.b	#1,d0
	move.b	d0,(a0)+
	rts


; ----------------------------------------------------------------------
; called from $0128B0, $0128BE, $0128CC, $0128DA, $0128E8, $0128F6, $01296A
sub_012B74:
	clr.b	(a3)
	clr.b	$1(a3)
	movea.l	a3,a2
	addq.w	#2,a2
	movea.l	#ram_D229,a5
	jsr	(sub_01A278).l
	subq.w	#1,d0
	move.w	d0,d3
	clr.w	d2
loc_012B90:
	movem.l	d2/d3,-(sp)
	move.w	d2,d0
	jsr	(sub_013E80).l
	tst.w	d5
	bpl.w	loc_012BDA
	cmp.w	#$FFFF,d5	; general form
	beq.w	loc_012BBE
	cmp.w	#$1,d0	; general form
	beq.w	loc_012BE0
	cmp.w	#$2,d0	; general form
	beq.w	loc_012BE0
	bra.w	loc_012C1E
loc_012BBE:
	cmp.w	#$4,d0	; general form
	beq.w	loc_012BE0
	cmp.w	#$3,d0	; general form
	beq.w	loc_012BE0
	cmp.w	#$5,d0	; general form
	beq.w	loc_012BE0
	bra.w	loc_012C1E
loc_012BDA:
	cmp.w	d0,d5
	bne.w	loc_012C1E
loc_012BE0:
	move.b	d2,(a2)+
	addq.b	#1,(a3)
	move.w	d2,d0
	jsr	(sub_013C76).l
	adda.w	(a1),a1
	addq.w	#8,a1
	movea.l	a1,a0
	movea.l	#sub_012C84,a4
	movea.l	#dat_1D9E00,a6
	move.l	(dat_028C22).l,d4
	tst.w	d5
	beq.w	loc_012C16
	movea.l	#dat_1D9DF0,a6
	move.l	(dat_028AC0).l,d4
loc_012C16:
	jsr	(sub_1D9CB0).l
	move.b	d0,(a5)+
loc_012C1E:
	movem.l	(sp)+,d2/d3
	addq.w	#1,d2
	dbra	d3,loc_012B90
	move.b	(a3),d0
	ext.w	d0
	subq.w	#2,d0
	bmi.w	loc_012C6E
loc_012C32:
	move.w	d0,d1
	clr.w	d6
	movea.l	a3,a0
	addq.w	#2,a0
	movea.l	#ram_D229,a1
loc_012C40:
	move.b	(a1),d3
	cmp.b	$1(a1),d3
	bge.w	loc_012C62
	move.b	$1(a1),d4
	move.b	d3,$1(a1)
	move.b	d4,(a1)
	move.b	(a0),d3
	move.b	$1(a0),d4
	move.b	d3,$1(a0)
	move.b	d4,(a0)
	st	d6
loc_012C62:
	addq.w	#1,a0
	addq.w	#1,a1
	dbra	d1,loc_012C40
	tst.w	d6
	bne.s	loc_012C32
loc_012C6E:
	rts

	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000


; ----------------------------------------------------------------------
; called from $01287C
sub_012C84:
	movem.l	d0-d7/a0-a6,-(sp)
	cmp.w	#$1A,d7	; general form
	bge.w	loc_012D04
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_012CA4
	movea.l	#RosterTable,a0
loc_012CA4:
	move.w	d7,-(sp)
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	adda.w	(a0),a0
	clr.w	d0
loc_012CB0:
	addq.w	#1,d0
	adda.w	(a0),a0
	addq.w	#8,a0
	cmpi.w	#$2,(a0)
	bne.s	loc_012CB0
	move.w	(sp)+,d7
	move.w	d0,d1
	jsr	(sub_01A278).l
	cmp.w	d0,d1
	bne.w	loc_012CFC
	subq.w	#1,d1
	clr.w	d2
	move.w	d7,d0
	mulu.w	#$6C,d0
	movea.l	#$202F44,a0
	adda.l	d0,a0
loc_012CDE:
	move.w	(a0)+,d0
	andi.w	#$1F,d0
	cmp.b	d0,d7
	bne.w	loc_012CFC
	move.w	(a0)+,d0
	cmp.b	d0,d2
	bne.w	loc_012CFC
	addq.w	#1,d2
	dbra	d1,loc_012CDE
	bra.w	loc_012D04
loc_012CFC:
	move.w	#$1,d0
	bra.w	loc_012D08
loc_012D04:
	move.w	#$0,d0
loc_012D08:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $012FD6, $1E63C8
sub_012D0E:
	btst	#3,$64(a3)
	bne.w	loc_012D22
	btst	#3,$62(a3)
	bne.w	loc_012DEC
loc_012D22:
	moveq	#$8,d0
	moveq	#$5,d1
	movea.w	#$AFE0,a0
	btst	#6,$62(a3)
	bne.w	loc_012D38
	adda.w	#$300,a0
loc_012D38:
	adda.w	#$80,a0
	tst.w	$34(a0)
	dbeq	d1,loc_012D38
	bne.w	loc_012DCE
	move.b	$28(a0),d0
	ext.w	d0
	asr.w	#1,d0
	add.w	(a0),d0
	sub.w	(ram_B760).w,d0
	move.b	$2A(a0),d1
	ext.w	d1
	asr.w	#1,d1
	add.w	$14(a0),d1
	sub.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	addq.l	#1,d0
	jsr	(ISqrt).l
	move.w	d0,d2
	movem.w	(sp)+,d0/d1
	moveq	#$12,d3
	move.w	#$11E,d4
	btst	#7,$62(a3)
	bne.w	loc_012D90
	neg.w	d4
loc_012D90:
	movem.w	d3/d4,-(sp)
	bsr.w	sub_012DEE
	move.w	d4,d5
	movem.w	(sp)+,d3/d4
	neg.w	d3
	bsr.w	sub_012DEE
	add.w	d5,d4
	clr.w	d0
	cmp.w	#$2C,d4	; general form
	bgt.w	loc_012DCE
	cmp.w	#$FFD4,d4	; general form
	blt.w	loc_012DCE
	btst	#7,$62(a3)
	beq.w	loc_012DC4
	neg.w	d4
loc_012DC4:
	moveq	#$2,d0
	tst.w	d4
	bpl.w	loc_012DCE
	moveq	#$6,d0
loc_012DCE:
	move.w	d0,(ram_BF10).w
	btst	#2,(ram_C342).w
	bne.w	loc_012DE6
	btst	#0,(ram_C34A).w
	beq.w	loc_012DEC
loc_012DE6:
	jsr	(sub_1D1510).l
loc_012DEC:
	rts


; ----------------------------------------------------------------------
; called from $012D94, $012DA0
sub_012DEE:
	sub.w	(ram_B760).w,d3
	sub.w	(ram_B774).w,d4
	muls.w	d0,d4
	muls.w	d1,d3
	sub.l	d3,d4
	divs.w	d2,d4
	rts


; ----------------------------------------------------------------------
; called from $011BD8, $01CF30, $01D0E4, $01D166, $01D1BA
sub_012E00:
	addq.w	#4,sp
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_012E12
	neg.w	d0
loc_012E12:
	move.w	#$11E,d1
	sub.w	d0,d1
	lsr.w	#3,d1
	cmp.w	#$14,d1	; general form
	blt.w	loc_012E24
	moveq	#$14,d1
loc_012E24:
	move.w	d1,$42(a3)
	moveq	#$12,d0
	btst	#7,(ram_C350).w
	bne.w	loc_012E3A
	jmp	(sub_01F172).l
loc_012E3A:
	jmp	(sub_01F168).l


; ----------------------------------------------------------------------
; called from $00D510, $00D548, $01DCE8, $1E629E, $1E62FA
sub_012E40:
	btst	#2,(ram_C342).w
	beq.w	loc_012E70
	btst	#0,(SysFlags).w
	bne.w	loc_012E70
	bclr	#2,(ram_C34A).w
	bset	#5,(ram_C342).w
	bne.w	loc_00C926
	bclr	#5,(ram_C34A).w
	move.w	#$64,(ram_C384).w
loc_012E70:
	move.w	#$8,(ram_BF10).w
	bset	#3,(ram_C33C).w
	clr.w	d0
	move.w	#$13A,d1
	btst	#7,$62(a3)
	bne.w	loc_012E8E
	neg.w	d1
loc_012E8E:
	sub.w	(a3),d0
	sub.w	$14(a3),d1
	jsr	(sub_01F186).l
	move.w	#$F,(ram_BF12).w
	move.w	#$1194,d1
	btst	#0,(SysFlags).w
	beq.w	loc_012EB2
	move.w	#$2F74,d1
loc_012EB2:
	jsr	(sub_01B836).l
	beq.w	loc_012ED4
	move.w	#$F90,d1
	btst	#0,(SysFlags).w
	beq.w	loc_012ECE
	move.w	#$30A6,d1
loc_012ECE:
	move.w	#$F,(ram_BF12).w
loc_012ED4:
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $00D3EE, $01DD3A, $1E627A
sub_012EDA:
	cmpi.w	#$1C,$5A(a3)
	bge.w	loc_012F24
	btst	#3,d0
	bne.w	loc_012EF4
	andi.w	#$7,d0
	move.w	d0,(ram_BF10).w
loc_012EF4:
	cmpi.w	#$10,$5A(a3)
	bge.w	loc_012F22
	add.w	d7,(ram_BF12).w
	cmpi.w	#$C,$5A(a3)
	bne.w	loc_012F10
	addq.w	#1,(ram_BF12).w
loc_012F10:
	btst	#5,d2
	beq.w	loc_012F22
	neg.w	$5A(a3)
	addi.w	#$1C,$5A(a3)
loc_012F22:
	rts
loc_012F24:
	bclr	#4,(ram_C346).w
	move.w	#$B,d0
	btst	#6,$62(a3)
	beq.w	loc_012F3C
	move.w	#$5,d0
loc_012F3C:
	jsr	(sub_01B3B8).l
	tst.w	d0
	bmi.w	loc_012F6C
	movem.l	a0,-(sp)
	asl.w	#7,d0
	movea.l	#ram_B060,a0
	cmpi.w	#$464,$58(a0,d0.w)
	beq.w	loc_012F64
	cmpi.w	#$40A,$58(a0,d0.w)
loc_012F64:
	movem.l	(sp)+,a0
	bne.w	loc_012F9E
loc_012F6C:
	cmpi.w	#$1,(ram_BF10).w
	ble.w	loc_012F80
	cmpi.w	#$7,(ram_BF10).w
	bne.w	loc_012F9E
loc_012F80:
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_012F90
	neg.w	d0
loc_012F90:
	cmp.w	#$D8,d0	; general form
	blt.w	loc_012F9E
	bset	#4,(ram_C346).w
loc_012F9E:
	bra.w	sub_012FA2


; ----------------------------------------------------------------------
; called from $012F9E, $01F62A, $01F650, $1CF3D2
sub_012FA2:
	movem.l	d0-d7/a0-a3,-(sp)
	bclr	#0,(SysFlags).w
	beq.w	loc_012FBA
	bclr	#3,(ram_C33C).w
	bra.w	loc_013218
loc_012FBA:
	move.b	$62(a3),(ram_C368).w
	bclr	#4,(ram_C34A).w
	btst	#1,$64(a3)
	beq.w	loc_012FD6
	bset	#4,(ram_C34A).w
loc_012FD6:
	bsr.w	sub_012D0E
	move.w	#$5,-(sp)
	move.w	$52(a3),(ram_BF0C).w
	bclr	#3,(ram_C33C).w
	bset	#5,$62(a3)
	btst	#3,$64(a3)
	bne.w	loc_013006
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_013212
loc_013006:
	move.w	#$18,(sp)
	bset	#4,(ram_C33E).w
	cmpi.w	#$F90,$58(a3)
	bne.w	loc_013028
	move.w	#$14,(sp)
	move.w	(ram_BF12).w,d0
	lsr.w	#2,d0
	sub.w	d0,(ram_BF12).w
loc_013028:
	btst	#3,$64(a3)
	beq.w	loc_013042
	movem.l	d0/d1,-(sp)
	move.w	#$1F,d0
	move.w	d0,(ram_BF12).w
	movem.l	(sp)+,d0/d1
loc_013042:
	clr.w	d0
	move.b	$6D(a3),d0
	lsr.b	#1,d0
	movea.l	a3,a0
	jsr	(sub_0250CA).l
	addi.w	#$14,d0
	mulu.w	(ram_BF12).w,d0
	mulu.w	#$5249,d0
	swap	d0
	move.w	d0,(ram_BF12).w
	btst	#0,$6D(a3)
	beq.w	loc_013074
	asr.w	#4,d0
	add.w	(ram_BF12).w,d0
loc_013074:
	lsr.w	#4,d0
	neg.w	d0
	addq.w	#3,d0
	bpl.w	loc_013080
	clr.w	d0
loc_013080:
	add.w	d0,(sp)
	st	(ram_B7C0).w
	move.b	#$10,$5E(a3)
	move.w	$52(a3),(ram_BF0E).w
	move.w	#$11E,d1
	btst	#7,$62(a3)
	bne.w	loc_0130A2
	neg.w	d1
loc_0130A2:
	move.w	(ram_BF10).w,d2
	asl.w	#2,d2
	lea	dat_01321E(pc),a0
	move.w	$0(a0,d2.w),d0
	move.w	$2(a0,d2.w),d2
	sub.w	(ram_B760).w,d0
	sub.w	(ram_B774).w,d1
	movem.w	d0-d2,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	jsr	(ISqrt).l
	tst.w	d0
	bne.w	loc_0130D4
	addq.w	#1,d0
loc_0130D4:
	move.w	d0,d3
	btst	#4,(ram_C33A).w
	bne.w	loc_013182
	cmp.w	#$C8,d3	; general form
	bhi.w	loc_013110
	jsr	(sub_1D1DE0).l
	bmi.w	loc_013182
	btst	#0,(ram_C34A).w
	bne.w	loc_013182
	moveq	#$10,d0
	add.b	$6E(a3),d0
	jsr	(Random).l
	cmp.w	#$E,d0	; general form
	bgt.w	loc_013182
loc_013110:
	clr.w	d0
	move.b	$6E(a3),d0
	lsr.w	#1,d0
	move.b	d0,-(sp)
	move.w	(ram_BF12).w,d0
	lsr.w	#4,d0
	sub.b	(sp)+,d0
	addi.b	#$10,d0
	mulu.w	d3,d0
	lsr.w	#6,d0
	cmp.w	#$FA,d3	; general form
	bhi.w	loc_013134
	lsr.w	#1,d0
loc_013134:
	cmp.w	#$96,d0	; general form
	blt.w	loc_013140
	move.w	#$96,d0
loc_013140:
	move.w	d0,-(sp)
	jsr	(sub_0200EA).l
	asr.w	#2,d0
	add.w	d0,$2(sp)
	move.w	(sp),d0
	cmp.w	#$3C,d0	; general form
	bls.w	loc_01315C
	moveq	#$3C,d0
	move.w	d0,(sp)
loc_01315C:
	tst.w	$4(sp)
	bpl.w	loc_013166
	lsr.w	#1,d0
loc_013166:
	jsr	(sub_0200EA).l
	asr.w	#2,d0
	add.w	d0,$4(sp)
	move.w	(sp)+,d0
	lsr.w	#1,d0
	jsr	(Random).l
	asr.w	#2,d0
	add.w	d0,$4(sp)
loc_013182:
	move.w	(ram_BF12).w,d2
	muls.w	#$44,d2
	muls.w	(sp)+,d2
	divs.w	d3,d2
	move.w	d2,(ram_B788).w
	move.w	(ram_BF12).w,d2
	muls.w	#$44,d2
	muls.w	(sp)+,d2
	divs.w	d3,d2
	move.w	d2,(ram_B78A).w
	move.w	#$8000,d1
	btst	#7,$62(a3)
	beq.w	loc_0131B2
	clr.w	d1
loc_0131B2:
	eor.w	d2,d1
	bpl.w	loc_0131CE
	move.w	#$3810,(ram_B78A).w
	btst	#7,$62(a3)
	bne.w	loc_0131CE
	move.w	#$C7F0,(ram_B78A).w
loc_0131CE:
	move.w	(sp)+,d1
	beq.w	loc_013212
	mulu.w	(ram_BF12).w,d1
	mulu.w	#$44,d1
	divu.w	d3,d1
	mulu.w	#$B33,d3
	divu.w	(ram_BF12).w,d3
	add.w	d1,d3
	cmp.w	#$1800,d3	; general form
	bls.w	loc_0131F4
	move.w	#$1800,d3
loc_0131F4:
	move.w	d3,(ram_B78C).w
	bclr	#4,(ram_C346).w
	beq.w	loc_013212
	btst	#3,$64(a3)
	bne.w	loc_013212
	jsr	(sub_1CED80).l
loc_013212:
	jsr	(sub_09205A).l
loc_013218:
	movem.l	(sp)+,d0-d7/a0-a3
	rts
dat_01321E:
	dc.w	$0000,$000C,$0010,$000C,$0010,$0006,$0010,$0000
	dc.w	$0000,$0000,$FFF0,$0000,$FFF0,$0006,$FFF0,$000C
	dc.w	$0000,$0006


; ----------------------------------------------------------------------
; called from $00D400, $00D500, $00D522, $00D9A6
sub_013242:
	move.w	$54(a3),(ram_BF10).w
	andi.w	#$7,(ram_BF10).w
	btst	#2,(ram_C342).w
	beq.w	loc_013274
	bclr	#2,(ram_C34A).w
	bset	#5,(ram_C342).w
	bne.w	loc_00C926
	bclr	#5,(ram_C34A).w
	move.w	#$64,(ram_C384).w
loc_013274:
	bset	#2,(ram_C33C).w
loc_01327A:
	rts
loc_01327C:
	btst	#4,d2
	bne.w	sub_0132A0
	btst	#3,(ram_C346).w
	bne.w	sub_0132A0
	btst	#3,d0
	bne.s	loc_01327A
	andi.w	#$7,d0
	move.w	d0,(ram_BF10).w
	bset	#3,d0

; ----------------------------------------------------------------------
; called from $011DFA, $013280, $01328A, $01D160, $01D41A, $1CF3B8
sub_0132A0:
	movem.l	d0-d5/a0/a1,-(sp)
	bclr	#2,(ram_C33C).w
	st	(ram_B7C0).w
	move.b	#$10,$5E(a3)
	move.w	$52(a3),(ram_BF0E).w
	btst	#1,(SysFlags).w
	beq.w	loc_0132EE
	btst	#0,(ram_C35E).w
	beq.w	loc_0132D6
	clr.b	$5E(a3)
	bra.w	loc_0132EE
loc_0132D6:
	btst	#2,(ram_C35E).w
	beq.w	loc_0132EA
	addi.w	#$28,$5E(a3)
	bra.w	loc_0132EE
loc_0132EA:
	addq.b	#8,$5E(a3)
loc_0132EE:
	bclr	#3,(ram_C346).w
	beq.w	loc_01331E
	jsr	(sub_1CEE76).l
	move.w	#$9,(ram_D304).w
	btst	#2,(TextFlags).w
	beq.w	loc_013314
	move.w	#$20,(ram_D304).w
loc_013314:
	jsr	(sub_1CEE0A).l
	bra.w	loc_0134CE
loc_01331E:
	moveq	#$8,d0
	tst.w	$34(a3)
	beq.w	loc_01332C
	move.b	$6F(a3),d0
loc_01332C:
	asl.w	#2,d0
	asr.w	#1,d0
	addi.w	#$A0,d0
	move.w	d0,(ram_BF12).w
	btst	#0,$6F(a3)
	beq.w	loc_013348
	asr.w	#4,d0
	add.w	d0,(ram_BF12).w
loc_013348:
	moveq	#-$1,d4
	moveq	#$5,d3
	movea.w	#$B060,a1
	cmpi.w	#$6,$52(a3)
	blt.w	loc_013368
	adda.w	#$300,a1
	btst	#2,(ram_C342).w
	bne.w	loc_013412
loc_013368:
	cmpa.l	a1,a3
	beq.w	loc_0133E8
	tst.w	$34(a1)
	ble.w	loc_0133E8
	btst	#2,$63(a1)
	bne.w	loc_0133E8
	move.w	(a1),d0
	sub.w	(ram_B760).w,d0
	move.w	$14(a1),d1
	sub.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	jsr	(sub_01F186).l
	movem.w	(sp)+,d1/d2
	sub.w	(ram_BF10).w,d0
	btst	#4,(SysFlags).w
	beq.w	loc_0133AC
	clr.w	d0
loc_0133AC:
	andi.w	#$7,d0
	asl.b	#5,d0
	ext.w	d0
	asl.w	#3,d0
	muls.w	d0,d0
	btst	#1,(SysFlags).w
	bne.w	loc_0133CC
	cmp.l	#dat_010000,d0	; general form
	bhi.w	loc_0133E8
loc_0133CC:
	muls.w	d1,d1
	muls.w	d2,d2
	add.l	d1,d2
	btst	#1,(SysFlags).w
	bne.w	loc_0133DE
	add.l	d0,d2
loc_0133DE:
	cmp.l	d4,d2
	bhi.w	loc_0133E8
	move.l	d2,d4
	movea.l	a1,a0
loc_0133E8:
	adda.w	#$80,a1
	dbra	d3,loc_013368
	tst.l	d4
	bmi.w	loc_013412
	move.w	(ram_B760).w,(ram_DEC6).w
	move.w	(ram_B774).w,(ram_DEC8).w
	move.l	a2,(ram_DECE).w
	move.l	a3,(ram_DECA).w
	bsr.w	sub_0135BA
	bra.w	loc_0134CE
loc_013412:
	move.w	$52(a3),(ram_D254).w
	move.w	(ram_BF10).w,d0
	asl.w	#2,d0
	movea.l	#dat_01FEB0,a0
	move.w	$2(a0,d0.w),d1
	muls.w	(ram_BF12).w,d1
	moveq	#$A,d2
	asl.l	d2,d1
	divs.w	#$BB8,d1
	add.w	$2A(a3),d1
	move.w	d1,(ram_B78A).w
	move.w	$0(a0,d0.w),d1
	muls.w	(ram_BF12).w,d1
	asl.l	d2,d1
	divs.w	#$BB8,d1
	add.w	$28(a3),d1
	move.w	d1,(ram_B788).w
	move.w	#$1000,d0
	jsr	(Random).l
	move.w	d0,(ram_B78C).w
	btst	#7,(ram_C350).w
	beq.w	loc_01346E
	clr.w	(ram_B78C).w
loc_01346E:
	btst	#1,(SysFlags).w
	beq.w	loc_0134CE
	clr.w	(ram_B78C).w
	move.w	(ram_B788).w,d0
	asr.w	#2,d0
	move.w	d0,(ram_B788).w
	move.w	(ram_B78A).w,d0
	asr.w	#2,d0
	move.w	d0,(ram_B78A).w
	bclr	#1,(ram_C35E).w
	beq.w	loc_0134A6
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	bra.w	loc_0134CE
loc_0134A6:
	btst	#2,(ram_C35E).w
	beq.w	loc_0134BC
	neg.w	(ram_B788).w
	neg.w	(ram_B78A).w
	bra.w	loc_0134CE
loc_0134BC:
	btst	#0,(ram_C35E).w
	beq.w	loc_0134CE
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
loc_0134CE:
	bclr	#4,(SysFlags).w
	tst.w	$34(a3)
	bne.w	loc_0134FA
	tst.w	(ram_B78A).w
	btst	#7,$62(a3)
	beq.w	loc_0134F2
	bmi.w	loc_0134F6
	bra.w	loc_0134FA
loc_0134F2:
	bmi.w	loc_0134FA
loc_0134F6:
	neg.w	(ram_B78A).w
loc_0134FA:
	move.w	(ram_B788).w,d0
	move.w	(ram_B78A).w,d1
	jsr	(sub_01F186).l
	move.w	#$2,d1
	tst.w	$34(a3)
	beq.w	loc_01357A
	move.w	#$B86,d1
	btst	#1,(SysFlags).w
	beq.w	loc_013542
	move.w	#$A8A,d1
	btst	#0,(ram_C35E).w
	beq.w	loc_013534
	move.w	#$3924,d1
loc_013534:
	btst	#2,(ram_C35E).w
	beq.w	loc_013542
	move.w	#$3CFC,d1
loc_013542:
	jsr	(sub_01B836).l
	beq.w	loc_01357A
	move.w	#$B34,d1
	btst	#1,(SysFlags).w
	beq.w	loc_01357A
	move.w	#$A8A,d1
	btst	#0,(ram_C35E).w
	beq.w	loc_01356C
	move.w	#$3924,d1
loc_01356C:
	btst	#2,(ram_C35E).w
	beq.w	loc_01357A
	move.w	#$3CFC,d1
loc_01357A:
	jsr	(sub_01F3B2).l
	bset	#5,$62(a3)
	moveq	#$C,d0
	sub.b	(ram_B78C).w,d0
	lsr.w	#2,d0
	andi.w	#$3,d0
	addi.w	#$10,d0
	bclr	#0,(ram_C35E).w
	bclr	#2,(ram_C35E).w
	btst	#1,(SysFlags).w
	bne.w	loc_0135B4
	move.w	d0,-(sp)
	jsr	(sub_09205A).l
loc_0135B4:
	movem.l	(sp)+,d0-d5/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $01340A
sub_0135BA:
	st	(ram_D254).w
	jsr	(sub_022566).l
	addq.w	#1,$12(a2)
	move.w	$52(a0),(ram_BF14).w
	move.w	(ram_BF12).w,d5
	asr.w	#2,d5
	exg	a0,a3
	moveq	#$13,d0
	jsr	(sub_01F168).l
	exg	a0,a3
	btst	#4,(ram_C354).w
	beq.w	loc_0135FE
	cmpi.w	#$11E,(ram_B774).w
	bgt.w	loc_013786
	cmpi.w	#$FEE2,(ram_B774).w
	blt.w	loc_013786
loc_0135FE:
	move.l	a0,-(sp)
	jsr	(sub_01F1F0).l
	add.w	(a0),d0
	sub.w	(ram_B760).w,d0
	add.w	$14(a0),d1
	sub.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	movem.w	(sp),d2/d3
	asr.w	#2,d2
	asr.w	#2,d3
	move.w	$28(a0),d0
	muls.w	#$F0,d0
	swap	d0
	move.w	$2A(a0),d1
	muls.w	#$F0,d1
	swap	d1
	movem.w	d0/d1,-(sp)
	muls.w	d2,d0
	muls.w	d3,d1
	add.w	d1,d0
	asl.w	#1,d0
	move.w	d0,d4
	movem.w	(sp),d0/d1
	muls.w	d0,d0
	muls.w	d1,d1
	muls.w	d5,d5
	neg.l	d5
	add.l	d0,d5
	add.l	d1,d5
	muls.w	d2,d2
	muls.w	d3,d3
	add.l	d2,d3
	muls.w	d5,d3
	asl.l	#2,d3
	move.w	d4,d0
	muls.w	d0,d0
	sub.l	d3,d0
	jsr	(ISqrt).l
	moveq	#$1,d3
	asr.w	#2,d5
	bne.w	loc_013672
	moveq	#$1,d5
loc_013672:
	move.w	d0,d2
	neg.w	d0
	sub.w	d4,d2
	ext.l	d2
	divs.w	d5,d2
	dbpl	d3,loc_013672
	bne.w	loc_013686
	addq.w	#1,d2
loc_013686:
	cmp.w	#$18,d2	; general form
	bls.w	loc_013690
	moveq	#$18,d2
loc_013690:
	btst	#1,(SysFlags).w
	beq.w	loc_01369C
	asl.w	#2,d2
loc_01369C:
	move.b	d2,(ram_B78C).w
	cmp.w	#$C,d2	; general form
	blt.w	loc_0136AE
	move.b	#$C,(ram_B78C).w
loc_0136AE:
	btst	#1,(SysFlags).w
	beq.w	loc_0136BC
	clr.w	(ram_B78C).w
loc_0136BC:
	move.w	d2,d0
	asl.w	#3,d0
	subi.w	#$A,d0
	move.b	d0,$40(a0)
	subq.w	#6,d0
	move.b	d0,(ram_B7BE).w
	movem.w	(sp)+,d0/d1
	muls.w	d2,d0
	asr.l	#1,d0
	add.w	(sp)+,d0
	move.w	(ram_B760).w,$44(a0)
	add.w	d0,$44(a0)
	muls.w	d2,d1
	asr.l	#1,d1
	add.w	(sp)+,d1
	move.w	(ram_B774).w,$46(a0)
	add.w	d1,$46(a0)
	mulu.w	#$78,d2
	swap	d0
	divs.w	d2,d0
	btst	#4,(ram_C354).w
	beq.w	loc_01377A
	swap	d1
	divs.w	d2,d1
	movem.w	d2,-(sp)
	move.w	(ram_B788).w,d2
	eor.w	d0,d2
	movem.w	(sp)+,d2
	bmi.w	loc_01377A
	movem.w	d2,-(sp)
	move.w	(ram_B78A).w,d2
	eor.w	d1,d2
	movem.w	(sp)+,d2
	bmi.w	loc_01377A
	movem.w	d2-d5,-(sp)
loc_013730:
	move.w	d0,d2
	move.w	d1,d3
	move.w	(ram_B788).w,d4
	move.w	(ram_B78A).w,d5
	tst.w	d2
	bpl.w	loc_013746
	neg.w	d2
	neg.w	d4
loc_013746:
	cmp.w	d2,d4
	blt.w	loc_01375C
	tst.w	d3
	bpl.w	loc_013756
	neg.w	d3
	neg.w	d5
loc_013756:
	cmp.w	d3,d5
	bgt.w	loc_01376A
loc_01375C:
	move.w	d0,d2
	asr.w	#3,d2
	sub.w	d2,d0
	move.w	d1,d2
	asr.w	#3,d2
	sub.w	d2,d1
	bra.s	loc_013730
loc_01376A:
	movem.w	(sp)+,d2-d5
	move.w	d0,(ram_B788).w
	move.w	d1,(ram_B78A).w
	bra.w	loc_013786
loc_01377A:
	move.w	d0,(ram_B788).w
	swap	d1
	divs.w	d2,d1
	move.w	d1,(ram_B78A).w
loc_013786:
	rts


; ----------------------------------------------------------------------
; called from $0193BC
sub_013788:
	movem.l	d0-d7/a0-a5,-(sp)
	bsr.w	sub_013AE4
	move.w	(ram_B760).w,d0
	cmp.w	#$32,d0	; general form
	bgt.w	loc_0137AC
	cmp.w	#$FFCE,d0	; general form
	blt.w	loc_0137B4
	move.w	#$1,d7
	bra.w	loc_0137B6
loc_0137AC:
	move.w	#$2,d7
	bra.w	loc_0137B6
loc_0137B4:
	clr.w	d7
loc_0137B6:
	movea.l	#ram_B060,a5
	move.w	(ram_D256).w,d6
	bmi.w	loc_0137D2
	cmpi.w	#$6,(ram_C756).w
	bne.w	loc_0137D2
	bsr.w	sub_0137F4
loc_0137D2:
	movea.l	#ram_B360,a5
	move.w	(ram_D258).w,d6
	bmi.w	loc_0137EE
	cmpi.w	#$6,(ram_CAF4).w
	bne.w	loc_0137EE
	bsr.w	sub_0137F4
loc_0137EE:
	movem.l	(sp)+,d0-d7/a0-a5
	rts


; ----------------------------------------------------------------------
; called from $0137CE, $0137EA
sub_0137F4:
	move.w	d7,-(sp)
	asl.w	#7,d6
	movea.l	#ram_B060,a3
	adda.w	d6,a3
	move.w	$34(a3),d6
	bmi.w	loc_01391A
	tst.b	$65(a3)
	bmi.w	loc_013816
	clr.w	d6
	move.b	$65(a3),d6
loc_013816:
	move.w	d6,d4
	lsl.b	#2,d6
	or.b	d7,d6
	andi.w	#$1F,d6
	asl.w	#2,d6
	movea.l	#dat_01391E,a0
	movea.l	$0(a0,d6.w),a0
	cmpa.l	#$0,a0
	beq.w	loc_01391A
	movem.l	d0/d5-d7/a3/a5,-(sp)
	cmp.w	#$1,d4	; general form
	bne.w	loc_01389E
	movea.l	a5,a3
	movea.l	#ram_B060,a5
	asl.w	#7,d6
	adda.w	d6,a5
	move.w	#$5,d6
loc_013852:
	cmpi.b	#$3,$65(a3)
	beq.w	loc_01386E
	tst.b	$65(a3)
	bpl.w	loc_013876
	cmpi.w	#$3,$34(a3)
	bne.w	loc_013876
loc_01386E:
	move.w	$14(a3),d7
	bra.w	loc_013882
loc_013876:
	adda.w	#$80,a3
	dbra	d6,loc_013852
	bra.w	loc_0138EC
loc_013882:
	move.w	$14(a5),d0
	btst	#7,$62(a5)
	bne.w	loc_013894
	neg.w	d0
	neg.w	d7
loc_013894:
	cmp.w	d7,d0
	blt.w	loc_0138E4
	bra.w	loc_0138EC
loc_01389E:
	cmp.w	#$2,d4	; general form
	bne.w	loc_0138EC
	movea.l	a5,a3
	movea.l	#ram_B060,a5
	asl.w	#7,d6
	adda.w	d6,a5
	move.w	#$5,d6
loc_0138B6:
	cmpi.b	#$5,$65(a3)
	beq.w	loc_0138D2
	tst.b	$65(a3)
	bpl.w	loc_0138D8
	cmpi.w	#$5,$34(a3)
	bne.w	loc_0138D8
loc_0138D2:
	move.w	$14(a3),d7
	bra.s	loc_013882
loc_0138D8:
	adda.w	#$80,a3
	dbra	d6,loc_0138B6
	bra.w	loc_0138EC
loc_0138E4:
	movem.l	(sp)+,d0/d5-d7/a3/a5
	bra.w	loc_01391A
loc_0138EC:
	movem.l	(sp)+,d0/d5-d7/a3/a5
	move.w	#$5,d5
loc_0138F4:
	clr.w	d1
	move.b	$65(a5),d1
	bpl.w	loc_013906
	move.w	$34(a5),d1
	bmi.w	loc_013912
loc_013906:
	move.b	$0(a0,d1.w),d2
	bmi.w	loc_013912
	move.b	d2,$65(a5)
loc_013912:
	adda.w	#$80,a5
	dbra	d5,loc_0138F4
loc_01391A:
	move.w	(sp)+,d7
	rts
dat_01391E:
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0001,$39CD,$0001,$39CD,$0001,$39CD,$0000,$0000
	dc.w	$0001,$39D4,$0001,$39D4,$0001,$39D4,$0000,$0000
	dc.w	$0001,$398E,$0001,$399C,$0001,$3995,$0000,$0000
	dc.w	$0001,$39A3,$0001,$39B1,$0001,$39AA,$0000,$0000
	dc.w	$0001,$39B8,$0001,$39C6,$0001,$39BF,$0000,$0000
	dc.w	$0001,$39A3,$0001,$39B1,$0001,$39AA,$0000,$0000
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$0503,$04FF,$FFFF
	dc.w	$FF04,$03FF,$FFFF,$FFFF,$0403,$FFFF,$FFFF,$FFFF
	dc.w	$0504,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FF04,$0503
	dc.w	$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$0504,$FFFF
	dc.w	$03FF,$01FF,$FFFF,$FFFF,$05FF,$FF02,$FFFF


; ----------------------------------------------------------------------
; called from $010BD2, $010F5A, $011268, $011474, $011740, $01195E
sub_0139DC:
	movem.l	d1-d3/a0,-(sp)
	cmpi.w	#$2,(ram_D284).w
	beq.w	loc_013A2C
	tst.w	$34(a3)
	bmi.w	loc_013A2C
	clr.w	d0
	move.b	$65(a3),d0
	bpl.w	loc_013A00
	move.w	$34(a3),d0
loc_013A00:
	move.w	$36(a3),d1
	move.b	$38(a3,d1.w),d1
	movea.l	#dat_013A36,a0
	cmp.b	$0(a0,d0.w),d1
	beq.w	loc_013A2C
	movea.l	#dat_013A3D,a0
	cmp.b	$0(a0,d0.w),d1
	beq.w	loc_013A2C
	move.b	$0(a0,d0.w),d0
	bra.w	loc_013A30
loc_013A2C:
	move.w	#$0,d0
loc_013A30:
	movem.l	(sp)+,d1-d3/a0
	rts
dat_013A36:
	dc.b	$00,$01,$01,$04,$06,$04,$06
dat_013A3D:
	dc.b	$00,$02,$02,$03,$05,$03,$05


; ----------------------------------------------------------------------
; called from $0193C2
sub_013A44:
	tst.w	(ram_B7C0).w
	bmi.w	loc_013AC8
	movem.l	d0-d4/a0-a3,-(sp)
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	movea.l	#ram_B060,a0
	btst	#6,$62(a3)
	beq.w	loc_013A70
	adda.w	#$300,a0
loc_013A70:
	move.w	(ram_B774).w,d0
	move.w	#$76,d1
	btst	#7,$62(a3)
	beq.w	loc_013A84
	neg.w	d0
loc_013A84:
	cmp.w	d1,d0
	blt.w	loc_013A96
	tst.w	$34(a3)
	bne.w	loc_013AC4
	bra.w	loc_013AB4
loc_013A96:
	neg.w	d0
	cmp.w	d1,d0
	blt.w	loc_013AC4
	move.b	$62(a3),d0
	move.b	$62(a0),d1
	eor.b	d1,d0
	btst	#6,d0
	beq.w	loc_013AC4
	bra.w	loc_013AC4
loc_013AB4:
	move.w	#$5,d1
loc_013AB8:
	st	$65(a0)
	adda.w	#$80,a0
	dbra	d1,loc_013AB8
loc_013AC4:
	movem.l	(sp)+,d0-d4/a0-a3
loc_013AC8:
	rts


; ----------------------------------------------------------------------
; called from $013B24
sub_013ACA:
	movem.l	d1/a0,-(sp)
	move.w	#$5,d1
loc_013AD2:
	st	$65(a0)
	adda.w	#$80,a0
	dbra	d1,loc_013AD2
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $01378C
sub_013AE4:
	movem.l	d0/d1/a0/a1,-(sp)
	movea.l	#ram_B060,a0
	bsr.w	sub_013B02
	movea.l	#ram_B360,a0
	bsr.w	sub_013B02
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $013AEE, $013AF8
sub_013B02:
	movea.l	a0,a1
	clr.w	d2
	move.w	#$5,d0
loc_013B0A:
	clr.w	d1
	move.b	$65(a0),d1
	bpl.w	loc_013B1C
	move.w	$34(a0),d1
	bmi.w	loc_013B2A
loc_013B1C:
	bset	d1,d2
	beq.w	loc_013B2A
	movea.l	a1,a0
	bsr.s	sub_013ACA
	bra.w	loc_013B32
loc_013B2A:
	adda.w	#$80,a0
	dbra	d0,loc_013B0A
loc_013B32:
	rts


; ----------------------------------------------------------------------
; called from $029AFE, $1D6328
sub_013B34:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$0,d1
	movea.l	#ram_17A2,a6
	movea.l	#ram_1D1E,a5
	movea.l	#ram_1D52,a4
loc_013B4E:
	clr.w	d2
	movea.l	a6,a0
	move.w	#$1A,d5
loc_013B56:
	move.w	#$8000,(a0)+
	dbra	d5,loc_013B56
	movea.l	a6,a0
	movea.l	a4,a2
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_013B76
	movea.l	#RosterTable,a1
loc_013B76:
	move.w	d1,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	(a1),a1
	bra.w	loc_013B8E
loc_013B84:
	cmpi.w	#$2,(a1)
	beq.w	loc_013B9C
	addq.w	#1,d2
loc_013B8E:
	move.b	d1,(a0)+
	move.b	d2,(a0)+
	adda.w	(a1),a1
	move.b	(a1),d4
	move.b	d4,(a2)+
	addq.w	#8,a1
	bra.s	loc_013B84
loc_013B9C:
	movem.l	d1-d7/a0,-(sp)
	move.w	d1,d7
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_013BB6
	movea.l	#RosterTable,a0
loc_013BB6:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	adda.w	$A(a0),a0
	move.w	(a0),d1
	clr.w	d0
loc_013BC4:
	addq.w	#1,d0
	asl.w	#4,d1
	bne.s	loc_013BC4
	movea.l	a5,a0
	move.b	d2,(a0)
	addq.b	#1,(a0)
	andi.b	#$3,d0
	move.b	d0,$1(a0)
	movem.l	(sp)+,d1-d7/a0
	adda.l	#$36,a6
	adda.l	#$1B,a4
	addq.l	#2,a5
	addq.w	#1,d1
	cmp.w	#$1A,d1	; general form
	blt.w	loc_013B4E
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D50BC
sub_013BFA:
	movem.l	d0-d3/d7/a0/a2,-(sp)
	bsr.w	sub_013C4E
	movea.l	a0,a1
	movem.l	(sp)+,d0-d3/d7/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $1D50F2, $1D5D0E, $1E11D6
sub_013C0A:
	movem.l	d0-d3/d7/a0/a2,-(sp)
	bsr.w	sub_013C4E
	move.l	a0,-(sp)
	movea.w	#$BFF6,a1
	adda.w	(a0),a0
	jsr	(sub_013D6E).l
	move.b	(ram_DDCF).w,d0
	jsr	(sub_02872E).l
	move.b	#$20,(a1)+
	movea.l	(sp)+,a0
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
loc_013C36:
	cmpi.b	#$20,(a0)+
	bne.s	loc_013C36
loc_013C3C:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_013C3C
	jsr	(sub_028714).l
	movem.l	(sp)+,d0-d3/d7/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $013BFE, $013C0E
sub_013C4E:
	movem.l	d0/d7/a2,-(sp)
	bra.w	loc_013C5E


; ----------------------------------------------------------------------
; called from $02850A, $028570, $0285BC, $02862A, $028666, $028678, $0286DC, $1DCE2A
sub_013C56:
	movem.l	d0/d7/a2,-(sp)
	move.w	$28(a2),d7
loc_013C5E:
	jsr	(sub_013C76).l
	movea.l	a1,a0
	movem.l	(sp)+,d0/d7/a2
	rts


; ----------------------------------------------------------------------
; called from $1D88AC, $1E3892
sub_013C6C:
	movem.l	d0/d1/d5-d7/a0,-(sp)
	bra.w	loc_013D00

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $00D640, $012BE6, $013C5E, $013DF0, $01DF40, $022346, $025570, $1D0822 (+1 more)
sub_013C76:
	movem.l	d0/d1/d5-d7/a0,-(sp)
	jsr	(sub_014016).l
	bne.w	loc_013C8E
	btst	#4,(ram_C356).w
	beq.w	loc_013CBE
loc_013C8E:
	move.w	d7,d6
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_013CA4
	movea.l	#RosterTable,a1
loc_013CA4:
	asl.w	#2,d6
	movea.l	$0(a1,d6.w),a1
	adda.w	(a1),a1
	bra.w	loc_013CB4
loc_013CB0:
	adda.w	(a1),a1
	addq.w	#8,a1
loc_013CB4:
	dbra	d0,loc_013CB0
	movem.l	(sp)+,d0/d1/d5-d7/a0
	rts
loc_013CBE:
	cmp.w	#$1B,d7	; general form
	ble.w	loc_013CD4
	add.w	d0,d0
	ext.l	d0
	addi.l	#dat_000DCA,d0
	bra.w	loc_013CE6
loc_013CD4:
	move.w	d7,d6
	mulu.w	#$36,d7
	add.w	d0,d0
	ext.l	d0
	add.l	d7,d0
	addi.l	#dat_0017A2,d0
loc_013CE6:
	movea.l	#ram_BF80,a0
	movea.l	#$200000,a1
	add.w	d0,d0
	move.b	$1(a1,d0.w),(a0)
	move.b	$3(a1,d0.w),$1(a0)
	move.w	(a0),d0
loc_013D00:
	move.w	d0,-(sp)
	andi.w	#$2F00,d0
	cmp.w	#$2800,d0	; general form
	bne.w	loc_013D32
	move.w	(sp)+,d0
	andi.w	#$FF,d0
	asl.w	#5,d0
	ext.l	d0
	addi.l	#$1521,d0
	moveq	#$20,d1
	movea.l	#ram_DDAE,a0
	jsr	(SRAM_Read).l
	movea.l	a0,a1
	bra.w	loc_013D68
loc_013D32:
	move.w	(sp)+,d0
	move.w	d0,d6
	lsr.w	#8,d6
	andi.w	#$1F,d6
	andi.w	#$FF,d0
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_013D54
	movea.l	#RosterTable,a1
loc_013D54:
	asl.w	#2,d6
	movea.l	$0(a1,d6.w),a1
	adda.w	(a1),a1
	bra.w	loc_013D64
loc_013D60:
	adda.w	(a1),a1
	addq.w	#8,a1
loc_013D64:
	dbra	d0,loc_013D60
loc_013D68:
	movem.l	(sp)+,d0/d1/d5-d7/a0
	rts


; ----------------------------------------------------------------------
; called from $013C1A, $025576, $028504, $02856A, $0285B6, $028624, $1D75EE, $1D9F3C
sub_013D6E:
	movem.l	d0/d1/a0/a1,-(sp)
	bsr.w	sub_014016
	bne.w	loc_013D84
	btst	#4,(ram_C356).w
	beq.w	loc_013DBE
loc_013D84:
	move.w	d7,-(sp)
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_013D9A
	movea.l	#RosterTable,a0
loc_013D9A:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	adda.w	(a0),a0
	bra.w	loc_013DAA
loc_013DA6:
	adda.w	(a0),a0
	addq.w	#8,a0
loc_013DAA:
	dbra	d0,loc_013DA6
	adda.w	(a0),a0
	clr.w	(ram_DDCE).w
	move.b	(a0),(ram_DDCF).w
	move.w	(sp)+,d7
	bra.w	loc_013E00
loc_013DBE:
	cmp.w	#$26,d7	; general form
	beq.w	loc_013DF0
	move.w	d7,d1
	muls.w	#$1B,d1
	ext.l	d1
	ext.l	d0
	add.l	d1,d0
	addi.l	#dat_001D52,d0
	add.l	d0,d0
	movea.l	#$200000,a0
	move.w	$0(a0,d0.w),d0
	andi.w	#$FF,d0
	move.w	d0,(ram_DDCE).w
	bra.w	loc_013E00
loc_013DF0:
	jsr	(sub_013C76).l
	adda.w	(a1),a1
	clr.w	d0
	move.b	(a1),d0
	move.w	d0,(ram_DDCE).w
loc_013E00:
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
sub_013E06:
	movem.l	d0/d1,-(sp)
	move.w	d7,d0
	moveq	#$36,d1
	mulu.w	d1,d0
	addi.l	#dat_0017A2,d0
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
sub_013E22:
	movem.l	d0/d1,-(sp)
	move.w	d7,d0
	moveq	#$36,d1
	mulu.w	d1,d0
	addi.l	#dat_0017A2,d0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $00D636, $1D72DC
sub_013E44:
	btst	#4,(ram_C356).w
	bne.w	loc_013E7E
	jsr	(sub_014016).l
	bne.w	loc_013E7E
	movem.l	d0/d7/a0,-(sp)
	asl.w	#2,d0
	ext.l	d0
	movea.l	#$202F44,a0
	mulu.w	#$2,d7
	add.l	d7,d7
	add.l	d0,d7
	move.w	$0(a0,d7.l),d0
	andi.w	#$2F,d0
	cmp.w	#$28,d0	; general form
	movem.l	(sp)+,d0/d7/a0
loc_013E7E:
	rts


; ----------------------------------------------------------------------
; called from $012B96, $019C32, $1D7282, $1D7554, $1DD968, $1E3B32, $1E3C24, $1E3CBE
sub_013E80:
	movem.l	d1/d6/d7/a0/a1,-(sp)
	jsr	(sub_014016).l
	bne.w	loc_013E98
	btst	#4,(ram_C356).w
	beq.w	loc_013EDA
loc_013E98:
	move.w	d7,d6
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_013EAE
	movea.l	#RosterTable,a1
loc_013EAE:
	asl.w	#2,d6
	movea.l	$0(a1,d6.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	move.w	d0,d1
	asr.w	#1,d0
	move.b	$0(a1,d0.w),d0
	btst	#0,d1
	bne.w	loc_013ED2
	lsr.w	#4,d0
loc_013ED2:
	andi.w	#$F,d0
	bra.w	loc_013FA2
loc_013EDA:
	cmp.w	#$1B,d7	; general form
	ble.w	loc_013EF0
	add.w	d0,d0
	ext.l	d0
	addi.l	#dat_000DCA,d0
	bra.w	loc_013F02
loc_013EF0:
	move.w	d7,d6
	mulu.w	#$36,d7
	add.w	d0,d0
	ext.l	d0
	add.l	d7,d0
	addi.l	#dat_0017A2,d0
loc_013F02:
	movea.l	#ram_BF80,a0
	movea.l	#$200000,a1
	add.w	d0,d0
	move.b	$1(a1,d0.w),(a0)
	move.b	$3(a1,d0.w),$1(a0)
	move.w	(a0),d0
	move.w	d0,-(sp)
	andi.w	#$2F00,d0
	cmp.w	#$2800,d0	; general form
	bne.w	loc_013F54
	move.w	(sp)+,d0
	andi.w	#$FF,d0
	asl.w	#5,d0
	ext.l	d0
	addi.l	#$1521,d0
	moveq	#$20,d1
	movea.l	#ram_DDAE,a0
	jsr	(SRAM_Read).l
	adda.w	(a0),a0
	addq.w	#8,a0
	move.b	(a0),d0
	ext.w	d0
	bra.w	loc_013FA2
loc_013F54:
	move.w	(sp)+,d0
	move.w	d0,d6
	lsr.w	#8,d6
	andi.w	#$1F,d6
	andi.w	#$FF,d0
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_013F76
	movea.l	#RosterTable,a1
loc_013F76:
	asl.w	#2,d6
	movea.l	$0(a1,d6.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	move.w	d0,d6
	lsr.b	#1,d6
	move.b	$0(a1,d6.w),d6
	btst	#0,d0
	bne.w	loc_013F9A
	lsr.b	#4,d6
loc_013F9A:
	andi.w	#$F,d6
	clr.w	d0
	move.b	d6,d0
loc_013FA2:
	movem.l	(sp)+,d1/d6/d7/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1D764E, $1D78DA
sub_013FA8:
	movem.l	d0/d1,-(sp)
	move.w	d7,d0
	mulu.w	#$36,d0
	addi.l	#dat_0017A2,d0
	moveq	#$36,d1
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $1D7670, $1D7936
sub_013FC6:
	movem.l	d0/d1,-(sp)
	move.w	d7,d0
	mulu.w	#$36,d0
	addi.l	#dat_0017A2,d0
	moveq	#$36,d1
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $1E3AD6, $1E3B08, $1E3B60, $1E3B9E, $1E3C4A, $1E3C88, $1E3CD8, $1E3D5C
sub_013FEA:
	movem.l	d0/d7/a0/a1,-(sp)
	mulu.w	#$36,d7
	add.w	d0,d0
	ext.l	d0
	add.l	d7,d0
	addi.l	#dat_0017A2,d0
	movea.l	#$200000,a1
	add.w	d0,d0
	move.b	$1(a1,d0.w),(a0)
	move.b	$3(a1,d0.w),$1(a0)
	movem.l	(sp)+,d0/d7/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $013C7A, $013D72, $013E4E, $013E84
sub_014016:
	cmp.w	#$1A,d7	; general form
	blt.w	loc_01402C
	cmp.w	#$1F,d7	; general form
	bge.w	loc_01402C
	cmp.w	#$FFFF,d7	; general form
	rts
loc_01402C:
	cmp.w	d7,d7
	rts


; ----------------------------------------------------------------------
; called from $014BF4
sub_014030:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	a0,(ram_BF54).w
	clr.w	d0
	move.b	(a0),d0
	movea.l	#ram_5208,a5
	movea.l	#ram_5244,a4
	bsr.w	sub_0141AC
	clr.w	d1
	movea.l	(ram_BF54).w,a0
	move.b	$1(a0),d1
	bsr.w	sub_0140C6
	move.b	d2,$2(a0)
	clr.w	d0
	move.b	$1(a0),d0
	movea.l	#ram_55F0,a5
	movea.l	#ram_562C,a4
	bsr.w	sub_0141AC
	clr.w	d1
	movea.l	(ram_BF54).w,a0
	move.b	(a0),d1
	bsr.w	sub_0140C6
	movea.l	(ram_BF54).w,a0
	move.b	d2,$3(a0)
	btst	#7,(SysFlags).w
	beq.w	loc_0140C0
	btst	#2,(ram_DD9E).w
	beq.w	loc_0140C0
	move.b	$2(a0),d0
	move.b	$3(a0),d1
	cmp.b	d0,d1
	bne.w	loc_0140C0
	btst	#2,(FrameCounter).w
	beq.w	loc_0140BC
	addq.b	#1,$3(a0)
	bra.w	loc_0140C0
loc_0140BC:
	addq.b	#1,$2(a0)
loc_0140C0:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014056, $01407C
sub_0140C6:
	move.w	d1,(ram_BF4E).w
	movea.l	#dat_01432B,a1
	move.b	$0(a1,d1.w),d1
	sub.w	d1,d3
	movea.l	#ram_CAD0,a2
	move.w	(ram_BF4E).w,d4
	move.w	d3,-(sp)
	move.w	d4,$28(a2)
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_0140FA
	movea.l	#RosterTable,a1
loc_0140FA:
	asl.w	#2,d4
	move.l	$0(a1,d4.w),(ram_CAEE).w
	move.l	(dat_028C22).l,d4
	clr.w	d0
	jsr	(sub_1D07D4).l
	muls.w	#$64,d0
	divs.w	d1,d0
	movea.l	#dat_014292,a0
	clr.w	d1
	move.b	$0(a0,d0.w),d1
	move.w	(sp)+,d3
	sub.w	d1,d3
	movea.l	(ram_BF54).w,a0
	movea.l	#dat_014345,a1
	move.w	(ram_BF4E).w,d0
	cmp.b	(a0),d0
	beq.w	loc_014140
	movea.l	#dat_01435F,a1
loc_014140:
	move.b	$0(a1,d0.w),d1
	ext.w	d1
	add.w	d1,d3
	bpl.w	loc_01414E
	clr.w	d3
loc_01414E:
	cmp.w	#$64,d3	; general form
	ble.w	loc_01415A
	move.w	#$64,d3
loc_01415A:
	movea.l	#dat_014194,a1
	move.w	d3,d0
	clr.w	d3
loc_014164:
	cmp.b	$0(a1,d3.w),d0
	ble.w	loc_014170
	addq.w	#1,d3
	bra.s	loc_014164
loc_014170:
	muls.w	#$A,d3
	movea.l	#dat_014379,a1
	adda.l	d3,a1
	move.w	#$64,d0
	jsr	(Random).l
	clr.w	d2
loc_014188:
	cmp.b	$0(a1,d2.w),d0
	ble.w	loc_0141AA
	addq.w	#1,d2
	bra.s	loc_014188
dat_014194:
	dc.w	$0913,$181D,$2124,$272A,$2D30,$3336,$393C,$3F42
	dc.w	$464B,$505A,$64FF
loc_0141AA:
	rts


; ----------------------------------------------------------------------
; called from $014048, $014070
sub_0141AC:
	movem.l	d0-d2/d4-d7/a0-a6,-(sp)
	move.w	d0,(ram_BF48).w
	movea.l	#$202F44,a6
	move.w	d0,d1
	muls.w	#$6C,d1
	adda.l	d1,a6
	movea.l	#ram_C8EE,a0
	move.w	#$6F,d1
loc_0141CC:
	clr.l	(a0)+
	dbra	d1,loc_0141CC
	movea.l	#ram_C732,a2
	move.w	d0,$28(a2)
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_0141F0
	movea.l	#RosterTable,a0
loc_0141F0:
	asl.w	#2,d0
	move.l	$0(a0,d0.w),(ram_C750).w
	move.l	(dat_028AC0).l,d4
	bsr.w	sub_01A268
	move.w	d0,-(sp)
	bsr.w	sub_01A2D0
	sub.w	(sp),d0
	subq.w	#1,d0
	move.w	d0,d2
	move.w	(sp)+,d0
	movem.l	a4/a5,-(sp)
loc_014214:
	btst	#6,$1(a6)
	bne.w	loc_01423E
	movem.l	d0/d2/d4,-(sp)
	movem.l	a4-a6,-(sp)
	jsr	(sub_1D07D4).l
	muls.w	#$64,d0
	divs.w	d1,d0
	movem.l	(sp)+,a4-a6
	move.w	d0,(a5)+
	movem.l	(sp)+,d0/d2/d4
	move.b	d0,(a4)
loc_01423E:
	addq.w	#1,a4
	addq.w	#1,d0
	addq.w	#4,a6
	dbra	d2,loc_014214
	move.b	#$FF,(a4)
	movem.l	(sp)+,a4/a5
	bsr.w	sub_0147F2
	move.w	#$D,d0
	clr.w	d3
	movea.l	#dat_014292,a2
loc_014260:
	move.w	(a5)+,d2
	move.b	$0(a2,d2.w),d2
	add.w	d2,d3
	dbra	d0,loc_014260
	move.w	(ram_BF48).w,d0
	movea.l	#dat_014311,a1
	clr.w	d1
	move.b	$0(a1,d0.w),d1
	sub.w	d1,d3
	movea.l	#dat_0142F7,a1
	clr.w	d1
	move.b	$0(a1,d0.w),d1
	add.w	d1,d3
	movem.l	(sp)+,d0-d2/d4-d7/a0-a6
	rts
dat_014292:
	dc.b	$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	dc.b	$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	dc.b	$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	dc.b	$01,$01,$01,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02
	dc.b	$02,$02,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03
	dc.b	$03,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$05,$05,$05,$05,$05
	dc.b	$06,$06,$06,$06,$06
dat_0142F7:
	dc.b	$21,$2B,$1F,$24,$2D,$31,$1D,$32,$1E,$2C,$20,$1C,$2A,$27,$1B,$2E
	dc.b	$19,$30,$22,$2F,$1A,$25,$28,$26,$23,$29
dat_014311:
	dc.b	$2A,$2F,$2B,$2C,$2E,$2C,$2C,$2F,$2A,$2A,$2B,$2A,$28,$2A,$27,$30
	dc.b	$29,$2D,$2C,$31,$29,$2C,$2A,$2C,$2F,$2B
dat_01432B:
	dc.b	$04,$03,$03,$05,$05,$05,$02,$06,$01,$05,$03,$01,$04,$06,$01,$05
	dc.b	$02,$06,$02,$02,$01,$04,$04,$03,$02,$06
dat_014345:
	dc.b	$01,$01,$01,$01,$01,$02,$00,$03,$00,$02,$01,$01,$01,$01,$01,$01
	dc.b	$00,$02,$01,$02,$00,$00,$01,$01,$00,$01
dat_01435F:
	dc.b	$FE,$00,$FE,$FF,$00,$00,$FE,$00,$FF,$FF,$FE,$FE,$FF,$FF,$FD,$00
	dc.b	$FD,$00,$FE,$00,$FD,$FF,$FF,$FF,$00,$00
dat_014379:
	dc.b	$0A,$19,$2E,$43,$52,$5C,$62,$64,$64,$64,$0A,$18,$2C,$40,$4E,$59
	dc.b	$61,$64,$64,$64,$09,$17,$2A,$3D,$4B,$56,$60,$64,$64,$64,$09,$16
	dc.b	$28,$3B,$49,$55,$60,$64,$64,$64,$08,$14,$25,$38,$46,$53,$5F,$64
	dc.b	$64,$64,$07,$12,$1E,$31,$45,$52,$5E,$63,$64,$64,$07,$11,$1C,$2F
	dc.b	$43,$50,$5C,$63,$64,$64,$06,$0F,$1A,$2D,$41,$4E,$5A,$62,$64,$64
	dc.b	$06,$0F,$1A,$2C,$3E,$4C,$59,$62,$64,$64,$05,$0D,$17,$29,$3B,$49
	dc.b	$57,$61,$64,$64,$05,$0C,$15,$23,$35,$48,$57,$61,$64,$64,$04,$0A
	dc.b	$12,$20,$32,$45,$54,$60,$64,$64,$04,$0A,$12,$1E,$30,$43,$52,$5F
	dc.b	$64,$64,$03,$08,$0F,$1B,$2D,$40,$4F,$5D,$63,$64,$03,$08,$0F,$1B
	dc.b	$2C,$3D,$4C,$5B,$62,$64,$02,$06,$0D,$19,$2A,$3B,$4A,$59,$61,$64
	dc.b	$02,$05,$0B,$15,$23,$36,$49,$58,$60,$64,$01,$03,$09,$13,$21,$3E
	dc.b	$47,$56,$5F,$64,$01,$03,$09,$12,$1F,$32,$45,$54,$5E,$64,$00,$01
	dc.b	$06,$0F,$1C,$2F,$42,$52,$5D,$64,$00,$00,$04,$0C,$19,$2C,$3F,$50
	dc.b	$5C,$64,$FF


; ----------------------------------------------------------------------
; called from $014BF8
sub_01444C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(FrameCounter).w,d0
	jsr	(Random).l
	movea.l	#ram_C732,a1
	move.w	#$39D,d0
loc_014464:
	clr.w	(a1)+
	dbra	d0,loc_014464
	clr.w	d0
	move.b	(a0),d0
	move.w	d0,(ram_C3AC).w
	clr.w	d0
	move.b	$1(a0),d0
	move.w	d0,(ram_C3AE).w
	movea.l	#ram_C732,a1
	movea.l	#ram_CAD0,a2
	move.w	(ram_C3AC).w,$28(a1)
	move.w	(ram_C3AE).w,$28(a2)
	movem.l	a2,-(sp)
	movea.l	#ram_C732,a2
	jsr	(sub_1E41B2).l
	movea.l	#ram_CAD0,a2
	jsr	(sub_1E41B2).l
	movem.l	(sp)+,a2
	clr.w	d0
	move.b	$2(a0),d0
	move.w	d0,$C(a1)
	move.w	d0,(ram_BF52).w
	move.w	(ram_C3AC).w,d1
	move.w	(ram_C3AE).w,d2
	bsr.w	sub_0147AA
	move.w	d0,(a1)
	movea.l	#ram_5208,a5
	movea.l	#ram_5244,a4
	bsr.w	sub_0146EC
	bsr.w	sub_014740
	movea.l	#ram_5668,a6
	bsr.w	sub_01453A
	clr.w	d0
	move.b	$3(a0),d0
	move.w	d0,$C(a2)
	move.w	d0,(ram_BF52).w
	move.w	(ram_C3AE).w,d1
	move.w	(ram_C3AC).w,d2
	bsr.w	sub_0147AA
	move.w	d0,(a2)
	movea.l	a2,a1
	movea.l	#ram_55F0,a5
	movea.l	#ram_562C,a4
	bsr.w	sub_0146EC
	bsr.w	sub_014740
	movea.l	#ram_56A4,a6
	bsr.w	sub_01453A
	bsr.w	sub_014654
	jsr	(sub_014832).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0144EA, $014526
sub_01453A:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$C0,d0
	jsr	(Random).l
	asr.w	#5,d0
	movea.l	#dat_01463A,a3
	add.b	$0(a3,d1.w),d0
	cmp.b	#$1,d0	; general form
	ble.w	loc_01455E
	asr.b	#1,d0
loc_01455E:
	move.l	a1,-(sp)
	addq.w	#6,a1
	move.w	d0,(a1)
	movea.l	(sp)+,a1
	move.w	d1,$28(a1)
	movem.l	d1/a0/a1,-(sp)
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_014582
	movea.l	#RosterTable,a0
loc_014582:
	asl.w	#2,d1
	move.l	$0(a0,d1.w),-(sp)
	adda.w	#$1E,a1
	move.l	(sp)+,(a1)
	movem.l	(sp)+,d1/a0/a1
	movem.l	a4/a6,-(sp)
	move.l	(dat_028BDE).l,d4
	movea.l	a1,a2
loc_01459E:
	clr.w	d0
	move.b	(a4)+,d0
	bmi.w	loc_0145C4
	movem.l	d2-d7/a0-a6,-(sp)
	bset	#4,(ram_C35A).w
	jsr	(sub_1D07D4).l
	bclr	#4,(ram_C35A).w
	movem.l	(sp)+,d2-d7/a0-a6
	move.w	d0,(a6)+
	bra.s	loc_01459E
loc_0145C4:
	movem.l	(sp)+,a4/a6
	move.l	a5,-(sp)
	movea.l	a6,a5
	bsr.w	sub_0147F2
	movea.l	(sp)+,a5
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	$6(a1),d6
	move.w	d6,d7
	subq.w	#1,d7
	movea.l	#dat_0147E3,a3
	bra.w	loc_01462C
loc_0145E8:
	move.w	#$64,d0
	jsr	(Random).l
	clr.w	d5
loc_0145F4:
	cmp.b	$0(a3,d5.w),d0
	ble.w	loc_014600
	addq.w	#1,d5
	bra.s	loc_0145F4
loc_014600:
	clr.w	d0
	move.b	$0(a4,d5.w),d0
	move.w	d0,d1
	asl.w	#1,d1
	addi.w	#$6C,d1
	tst.w	$0(a1,d1.w)
	bne.w	loc_01462C
	move.l	a1,-(sp)
	adda.w	#$114,a1
	addq.b	#2,$0(a1,d0.w)
	cmp.w	d7,d6
	bne.w	loc_01462A
	addq.b	#3,$0(a1,d0.w)
loc_01462A:
	movea.l	(sp)+,a1
loc_01462C:
	dbra	d6,loc_0145E8
	movem.l	(sp)+,d0-d7/a0-a6
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_01463A:
	dc.w	$0404,$0609,$0707,$0608,$0405,$0605,$0405,$0404
	dc.w	$0406,$0405,$0607,$0407,$0808


; ----------------------------------------------------------------------
; called from $01452A
sub_014654:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_C3AC).w,d7
	movea.l	#ram_C732,a1
	movea.l	#ram_CAD0,a2
	bsr.w	sub_014686
	move.w	(ram_C3AE).w,d7
	movea.l	#ram_CAD0,a1
	movea.l	#ram_C732,a2
	bsr.w	sub_014686
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014668, $01467C
sub_014686:
	jsr	(sub_01A20E).l
	subq.w	#1,d0
	bsr.w	sub_0146C8
	move.w	d0,d3
	add.w	d3,d3
	addi.w	#$14C,d3
	addi.w	#$E10,$0(a1,d3.w)
	move.w	(a2),d4
	cmp.w	#$FF,d4	; general form
	ble.w	loc_0146AE
	move.w	#$FF,d4
loc_0146AE:
	move.w	d0,d3
	addi.w	#$F8,d3
	move.b	d4,$0(a1,d3.w)
	move.w	$C(a2),d4
	move.w	d0,d3
	addi.w	#$C0,d3
	move.b	d4,$0(a1,d3.w)
	rts


; ----------------------------------------------------------------------
; called from $01468E
sub_0146C8:
	movem.l	d1-d7,-(sp)
	clr.w	d1
	move.w	#$64,d0
	jsr	(Random).l
	cmp.w	#$2D,d0	; general form
	bgt.w	loc_0146E4
	move.w	#$1,d1
loc_0146E4:
	move.w	d1,d0
	movem.l	(sp)+,d1-d7
	rts


; ----------------------------------------------------------------------
; called from $0144DC, $014518
sub_0146EC:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_BF52).w,d6
	movea.l	#dat_0147E3,a3
	bra.w	loc_014736
loc_0146FE:
	move.w	#$64,d0
	jsr	(Random).l
	clr.w	d5
loc_01470A:
	cmp.b	$0(a3,d5.w),d0
	ble.w	loc_014716
	addq.w	#1,d5
	bra.s	loc_01470A
loc_014716:
	clr.w	d0
	move.b	$0(a4,d5.w),d0
	move.w	d0,d1
	asl.w	#1,d1
	addi.w	#$6C,d1
	tst.w	$0(a1,d1.w)
	bne.s	loc_0146FE
	move.l	a1,-(sp)
	adda.w	#$C0,a1
	addq.b	#1,$0(a1,d0.w)
	movea.l	(sp)+,a1
loc_014736:
	dbra	d6,loc_0146FE
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0144E0, $01451C
sub_014740:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_BF52).w,d6
	move.w	#$64,d0
	jsr	(Random).l
	addi.w	#$64,d0
	muls.w	d0,d6
	divs.w	#$64,d6
	movea.l	#dat_0147D4,a3
	bra.w	loc_0147A0
loc_014766:
	move.w	#$64,d0
	jsr	(Random).l
	clr.w	d5
loc_014772:
	cmp.b	$0(a3,d5.w),d0
	ble.w	loc_01477E
	addq.w	#1,d5
	bra.s	loc_014772
loc_01477E:
	clr.w	d0
	move.b	$0(a4,d5.w),d0
	move.w	d0,d1
	asl.w	#1,d1
	addi.w	#$6C,d1
	tst.w	$0(a1,d1.w)
	bne.w	loc_0147A0
	move.l	a1,-(sp)
	adda.w	#$DC,a1
	addq.b	#1,$0(a1,d0.w)
	movea.l	(sp)+,a1
loc_0147A0:
	dbra	d6,loc_014766
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0144CA, $014504
sub_0147AA:
	movem.l	d1-d7/a0-a6,-(sp)
	movea.l	#dat_01432B,a1
	clr.w	d3
	move.b	$0(a1,d2.w),d3
	sub.w	d3,d0
	move.w	d0,-(sp)
	move.w	#$14,d0
	jsr	(Random).l
	addi.w	#$1E,d0
	add.w	(sp)+,d0
	movem.l	(sp)+,d1-d7/a0-a6
	rts
dat_0147D4:
	dc.b	$0C,$18
	dc.b	"$.6>FLRVZ^`bd"
dat_0147E3:
	dc.b	$0D,$19
	dc.b	"",$22,"+4;BHNTX\`bd"


; ----------------------------------------------------------------------
; called from $014250, $0145CC
sub_0147F2:
	movem.l	a4/a5,-(sp)
loc_0147F6:
	clr.w	d2
	movem.l	a4/a5,-(sp)
loc_0147FC:
	tst.b	$1(a4)
	bmi.w	loc_014824
	move.w	(a5)+,d0
	move.w	(a5),d1
	cmp.w	d0,d1
	ble.w	loc_014820
	st	d2
	move.w	d0,(a5)
	move.w	d1,-$2(a5)
	move.b	(a4),d0
	move.b	$1(a4),(a4)
	move.b	d0,$1(a4)
loc_014820:
	addq.w	#1,a4
	bra.s	loc_0147FC
loc_014824:
	movem.l	(sp)+,a4/a5
	tst.w	d2
	bne.s	loc_0147F6
	movem.l	(sp)+,a4/a5
	rts


; ----------------------------------------------------------------------
; called from $01452E, $022652
sub_014832:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#6,(SysFlags).w
	movea.l	#ram_C732,a1
	bsr.w	sub_01486A
	movea.l	#ram_CAD0,a1
	bsr.w	sub_01486A
	move.w	(ram_C75A).w,d0
	move.w	(ram_CAF8).w,d1
	jsr	(sub_014A84).l
	bclr	#6,(SysFlags).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014842, $01484C
sub_01486A:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	$28(a1),d7
	moveq	#$C,d2
	move.w	#$18,d3
	move.l	#$120,d4
	move.l	#loc_000278,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_0148A0
	moveq	#$A,d2
	move.w	#$19,d3
	move.l	#$FA,d4
	move.l	#loc_000458,d1
loc_0148A0:
	movea.l	a1,a0
	adda.w	#$C0,a0
	jsr	(sub_01A20E).l
	adda.w	d0,a0
	bsr.w	sub_0149D2
	moveq	#$E,d2
	jsr	(sub_01A20E).l
	move.w	d0,d3
	moveq	#$2A,d4
	move.l	#dat_00599C,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_0148D6
	moveq	#$2A,d4
	move.l	#dat_003448,d1
loc_0148D6:
	movea.l	a1,a0
	adda.w	#$C0,a0
	bsr.w	sub_0149D2
	moveq	#$C,d2
	move.w	#$18,d3
	move.l	#$120,d4
	move.l	#dat_001FB8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_01490E
	moveq	#$A,d2
	move.w	#$19,d3
	move.l	#$FA,d4
	move.l	#dat_0013F8,d1
loc_01490E:
	movea.l	a1,a0
	adda.w	#$DC,a0
	jsr	(sub_01A20E).l
	adda.w	d0,a0
	bsr.w	sub_0149D2
	moveq	#$E,d2
	jsr	(sub_01A20E).l
	move.w	d0,d3
	move.w	#$2A,d4
	move.l	#dat_005558,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_014948
	move.w	#$2A,d4
	move.l	#dat_0031A8,d1
loc_014948:
	movea.l	a1,a0
	adda.w	#$F8,a0
	bsr.w	sub_0149D2
	moveq	#$A,d2
	move.w	#$18,d3
	move.w	#$F0,d4
	move.l	#dat_003CF8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_01497C
	moveq	#$9,d2
	move.w	#$19,d3
	move.w	#$E1,d4
	move.l	#dat_002398,d1
loc_01497C:
	movea.l	a1,a0
	adda.w	#$114,a0
	jsr	(sub_01A20E).l
	adda.w	d0,a0
	bsr.w	sub_0149D2
	moveq	#$D,d2
	jsr	(sub_01A20E).l
	move.w	d0,d3
	move.w	#$27,d4
	move.l	#dat_005DE0,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_0149B6
	move.w	#$27,d4
	move.l	#dat_0036E8,d1
loc_0149B6:
	movea.l	a1,a0
	adda.w	#$14C,a0
	bset	#3,(ram_C356).w
	bsr.w	sub_0149D2
	bclr	#3,(ram_C356).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0148AE, $0148DC, $01491C, $01494E, $01498A, $0149C2
sub_0149D2:
	movem.l	d0/d1/d4/d7/a0,-(sp)
	btst	#2,(ram_DD9E).w
	beq.w	loc_0149E4
	bsr.w	sub_0188B6
loc_0149E4:
	mulu.w	d7,d4
	add.l	d4,d1
	bra.w	loc_014A38
loc_0149EC:
	jsr	(sub_00B952).l
	btst	#3,(ram_C356).w
	beq.w	loc_014A02
	move.w	(a0)+,d4
	bra.w	loc_014A06
loc_014A02:
	move.b	(a0)+,d4
	ext.w	d4
loc_014A06:
	btst	#3,(ram_C356).w
	beq.w	loc_014A2E
	ext.l	d4
	divu.w	#$3C,d4
	cmpi.w	#$2,(ram_D278).w
	beq.w	loc_014A2E
	asl.w	#1,d4
	cmpi.w	#$1,(ram_D278).w
	beq.w	loc_014A2E
	asl.w	#1,d4
loc_014A2E:
	add.l	d4,d0
	jsr	(sub_00B8DE).l
	add.l	d2,d1
loc_014A38:
	dbra	d3,loc_0149EC
	movem.l	(sp)+,d0/d1/d4/d7/a0
	rts


; ----------------------------------------------------------------------
; called from $027C70, $027C86, $027C9C, $027CB4, $027CC8, $1D5A74, $1D5AAC, $1D5B0A (+4 more)
sub_014A42:
	movem.l	d0/d1/d3/d4/a0,-(sp)
	mulu.w	d7,d4
	add.l	d4,d1
	bra.w	loc_014A58
loc_014A4E:
	jsr	(sub_00B952).l
	move.w	d0,(a0)+
	add.l	d2,d1
loc_014A58:
	dbra	d3,loc_014A4E
	movem.l	(sp)+,d0/d1/d3/d4/a0
	rts


; ----------------------------------------------------------------------
; called from $027BD4, $027BEA, $027C00, $027C18, $027C2C, $1D78B6, $1D7BD2
sub_014A62:
	movem.l	d0/d1/d3/d4/a0,-(sp)
	mulu.w	d7,d4
	add.l	d4,d1
	bra.w	loc_014A7A
loc_014A6E:
	move.w	(a0)+,d0
	ext.l	d0
	jsr	(sub_00B8DE).l
	add.l	d2,d1
loc_014A7A:
	dbra	d3,loc_014A6E
	movem.l	(sp)+,d0/d1/d3/d4/a0
	rts


; ----------------------------------------------------------------------
; called from $014858
sub_014A84:
	movem.l	d0-d4/a0,-(sp)
	move.l	d1,-(sp)
	move.w	#$1A,d4
	move.l	#$10080,d1
	mulu.w	#$51,d0
	add.l	d0,d1
	move.w	#$3,d2
loc_014A9E:
	jsr	(sub_00B952).l
	tst.w	d0
	beq.w	loc_014AB2
	subq.w	#1,d0
	jsr	(sub_00B8DE).l
loc_014AB2:
	addq.l	#3,d1
	dbra	d4,loc_014A9E
	move.l	(sp)+,d0
	move.w	#$1A,d4
	move.l	#$10080,d1
	mulu.w	#$51,d0
	add.l	d0,d1
	move.w	#$3,d2
loc_014ACE:
	jsr	(sub_00B952).l
	tst.w	d0
	beq.w	loc_014AE2
	subq.w	#1,d0
	jsr	(sub_00B8DE).l
loc_014AE2:
	addq.l	#3,d1
	dbra	d4,loc_014ACE
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d4/a0
	rts


; ----------------------------------------------------------------------
; called from $026EAC
sub_014AF4:
	btst	#7,(SysFlags).w
	beq.w	loc_014B72
	bclr	#6,(ram_C354).w
	beq.w	loc_014B72
	bset	#6,(SysFlags).w
	clr.w	(ram_DD9C).w
	clr.b	(ram_DDA3).w
	clr.b	(ram_DD9E).w
	bclr	#1,(ram_C35A).w
	move.b	#$0,(ram_DD9F).w
	move.b	#$1,(ram_DDA0).w
	move.b	#$0,(ram_DDA1).w
	move.b	#$0,(ram_DDA4).w
	move.b	#$1,(ram_DDA5).w
	move.b	#$0,(ram_DDA6).w
	move.b	#$0,(ram_DDA7).w
	movem.l	d0,-(sp)
	move.b	(ram_DDAA).w,d0
	move.b	d0,(ram_DDA8).w
	movem.l	(sp)+,d0
	jsr	(sub_014FCE).l
	jsr	(sub_0150A2).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
loc_014B72:
	rts


; ----------------------------------------------------------------------
; called from $026F0C
sub_014B74:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D278).w,-(sp)
	move.w	#$2,(ram_D278).w
	bset	#6,(SysFlags).w
	move.w	(ram_DDD4).w,d7
	bra.w	loc_014C9C
loc_014B90:
	bsr.w	sub_014CBA
	movea.l	#ram_DD18,a2
	clr.w	d6
	move.b	(ram_DD17).w,d6
	bra.w	loc_014BFE
loc_014BA4:
	move.b	(ram_DDA2).w,d0
	cmp.b	(a2),d0
	beq.w	loc_014BB6
	cmp.b	$1(a2),d0
	bne.w	loc_014BBE
loc_014BB6:
	bsr.w	sub_014F12
	bne.w	loc_014BFC
loc_014BBE:
	movem.l	d3/a3,-(sp)
	lea	$2(a2),a3
	suba.l	a2,a3
	move.l	a3,d3
	divu.w	#$5,d3
	mulu.w	#$10,d3
	movea.l	#ram_CF50,a3
	adda.l	d3,a3
	cmpi.w	#$4,$4(a3)
	beq.w	loc_014BEA
	cmpi.w	#$4,$6(a3)
loc_014BEA:
	movem.l	(sp)+,d3/a3
	beq.w	loc_014BFC
	movea.l	a2,a0
	bsr.w	sub_014030
	bsr.w	sub_01444C
loc_014BFC:
	addq.w	#5,a2
loc_014BFE:
	dbra	d6,loc_014BA4
	bset	#6,(SysFlags).w
	bsr.w	sub_014D76
	btst	#2,(ram_DD9E).w
	beq.w	loc_014C6E
	jsr	(sub_0183B0).l
	btst	#1,(ram_DD9E).w
	bne.w	loc_014C8C
	jsr	(sub_027B42).l
	movea.l	#ram_CF50,a0
	clr.w	d0
	move.b	(ram_DDA2).w,d0
loc_014C38:
	cmp.w	(a0),d0
	beq.w	loc_014C52
	cmp.w	$2(a0),d0
	beq.w	loc_014C52
	adda.w	#$10,a0
	dbra	d1,loc_014C38
	bra.w	loc_014C8C
loc_014C52:
	cmpi.w	#$4,$4(a0)
	beq.w	loc_014C8C
	cmpi.w	#$4,$6(a0)
	beq.w	loc_014C8C
	addq.w	#1,(ram_DD9C).w
	bra.w	loc_014C8C
loc_014C6E:
	cmpi.w	#$C0,(ram_DD9C).l
	blt.w	loc_014C94
	bset	#0,(ram_DD9E).w
	bclr	#1,(ram_DD9E).w
	bclr	#2,(ram_DD9E).w
loc_014C8C:
	bsr.w	sub_014FCE
	bra.w	loc_014CA0
loc_014C94:
	addq.w	#1,(ram_DD9C).w
	bsr.w	sub_014FCE
loc_014C9C:
	dbra	d7,loc_014B90
loc_014CA0:
	clr.w	(ram_DDD4).w
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	move.w	(sp)+,(ram_D278).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014B90, $026EE6
sub_014CBA:
	move.w	(ram_DD9C).w,d1
	clr.w	d2
	movea.l	#ram_DD16,a2
	btst	#2,(ram_DD9E).w
	beq.w	loc_014CD4
	bra.w	loc_014D1C
loc_014CD4:
	movem.l	d0-d7/a0-a6,-(sp)
	move.b	d1,(a2)+
	movea.l	#dat_017A9C,a0
	clr.w	d5
	move.b	(a0)+,d5
	add.w	d2,d1
	cmp.w	d5,d1
	blt.w	loc_014CEE
	sub.w	d5,d1
loc_014CEE:
	bra.w	loc_014CFC
loc_014CF2:
	clr.l	d3
	move.b	(a0)+,d3
	move.w	d3,d4
	add.w	d4,d4
	adda.w	d4,a0
loc_014CFC:
	dbra	d1,loc_014CF2
	clr.w	d1
	move.b	(a0)+,d1
	move.b	d1,(a2)+
	bra.w	loc_014D12
loc_014D0A:
	move.b	(a0)+,(a2)
	move.b	(a0)+,$1(a2)
	addq.w	#5,a2
loc_014D12:
	dbra	d1,loc_014D0A
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_014D1C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$3,d2
	sub.w	(ram_CFD6).w,d2
	move.w	#$1,d0
	asl.w	d2,d0
	move.b	d0,$1(a2)
	addq.w	#2,a2
	movea.l	#ram_CF50,a0
	cmpi.w	#$3,(ram_CFD6).w
	bne.w	loc_014D6C
	cmpi.w	#$4,$4(a0)
	beq.w	loc_014D70
	cmpi.w	#$4,$6(a0)
	beq.w	loc_014D70
	bra.w	loc_014D6C
loc_014D5C:
	move.b	$1(a0),(a2)
	move.b	$3(a0),$1(a2)
	addq.w	#5,a2
	adda.w	#$10,a0
loc_014D6C:
	dbra	d0,loc_014D5C
loc_014D70:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014C08, $018528
sub_014D76:
	clr.w	d2
	movea.l	#ram_DD16,a2
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d1
	move.b	(a2)+,d1
	btst	#0,(ram_DD9E).w
	beq.w	loc_014DC0
	clr.w	d1
	clr.w	d0
	move.b	(a2),d0
	move.l	a2,-(sp)
	addq.w	#1,a2
	movea.l	#ram_CF50,a0
	bra.w	loc_014DB6
loc_014DA4:
	move.b	$2(a2),$B(a0)
	move.b	$3(a2),$D(a0)
	addq.w	#5,a2
	adda.w	#$10,a0
loc_014DB6:
	dbra	d0,loc_014DA4
	movea.l	(sp)+,a2
	bra.w	loc_014DD4
loc_014DC0:
	movea.l	#dat_017A9C,a0
	clr.w	d5
	move.b	(a0)+,d5
	add.w	d2,d1
	cmp.w	d5,d1
	blt.w	loc_014DD4
	sub.w	d5,d1
loc_014DD4:
	bra.w	loc_014DE2
loc_014DD8:
	clr.l	d3
	move.b	(a0)+,d3
	move.w	d3,d4
	add.w	d4,d4
	adda.w	d4,a0
loc_014DE2:
	dbra	d1,loc_014DD8
	clr.w	d1
	move.b	(a2)+,d1
	bra.w	loc_014E1A
loc_014DEE:
	move.b	(ram_DDA2).w,d0
	cmp.b	(a2),d0
	beq.w	loc_014E00
	cmp.b	$1(a2),d0
	bne.w	loc_014E14
loc_014E00:
	bsr.w	sub_014F12
	bne.w	loc_014E14
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_014E2A
	movem.l	(sp)+,d0-d7/a0-a6
loc_014E14:
	bsr.w	sub_014F52
	addq.w	#5,a2
loc_014E1A:
	dbra	d1,loc_014DEE
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $014E0C, $02264C
sub_014E2A:
	movem.l	d0-d2,-(sp)
	move.b	(ram_DDA2).w,d0
	cmp.b	(a2),d0
	beq.w	loc_014E40
	cmp.b	$1(a2),d0
	bne.w	loc_014F0C
loc_014E40:
	bsr.w	sub_014F38
	move.l	d0,d1
	move.l	d1,-(sp)
	clr.l	d0
	move.b	$2(a2),d0
	asl.w	#3,d1
	andi.l	#$FFFF,d1
	addi.l	#$6608,d1
	move.w	#$8,d2
	jsr	(sub_00B8DE).l
	addi.l	#$2A0,d1
	move.b	$3(a2),d0
	jsr	(sub_00B8DE).l
	btst	#2,(ram_DD9E).w
	beq.w	loc_014EA6
	addi.l	#$FFFFD2D8,d1
	move.w	#$8,d2
	move.b	(a2),d0
	cmp.b	(ram_DDA2).w,d0
	beq.w	loc_014E9C
	ori.b	#$80,d0
	bra.w	loc_014EA0
loc_014E9C:
	move.b	$1(a2),d0
loc_014EA0:
	jsr	(sub_00B8DE).l
loc_014EA6:
	move.l	(sp),d1
	mulu.w	#$2,d1
	addi.l	#$6B48,d1
	move.w	#$2,d2
	clr.l	d0
	btst	#7,(ram_C354).w
	beq.w	loc_014EC6
	bset	#0,d0
loc_014EC6:
	bset	#1,d0
	jsr	(sub_00B8DE).l
	move.w	(ram_DD9C).w,d1
	mulu.w	#$1,d1
	addi.l	#$6BF0,d1
	move.w	#$1,d2
	moveq	#$1,d0
	jsr	(sub_00B8DE).l
	move.l	(sp)+,d1
	addq.l	#1,d1
	move.l	d1,d0
	move.l	#$240,d1
	move.w	#$8,d2
	jsr	(sub_00B8DE).l
	jsr	(SRAM_UpdateChecksum).l
	jsr	(sub_014FEE).l
loc_014F0C:
	movem.l	(sp)+,d0-d2
	rts


; ----------------------------------------------------------------------
; called from $014BB6, $014E00, $026EFC
sub_014F12:
	movem.l	d0-d2,-(sp)
	move.w	(ram_DD9C).w,d1
	mulu.w	#$1,d1
	addi.l	#$6BF0,d1
	move.w	#$1,d2
	jsr	(sub_00B952).l
	btst	#0,d0
	movem.l	(sp)+,d0-d2
	rts


; ----------------------------------------------------------------------
; called from $014E40
sub_014F38:
	movem.l	d1/d2,-(sp)
	move.l	#$240,d1
	move.w	#$8,d2
	jsr	(sub_00B952).l
	movem.l	(sp)+,d1/d2
	rts


; ----------------------------------------------------------------------
; called from $014E14
sub_014F52:
	btst	#2,(ram_DD9E).w
	bne.w	loc_014F86
	movem.l	d0-d3,-(sp)
	clr.w	d1
	move.b	(a2),d1
	move.b	$2(a2),d2
	move.b	$3(a2),d3
	bsr.w	sub_014F88
	clr.w	d1
	move.b	$1(a2),d1
	move.b	$3(a2),d2
	move.b	$2(a2),d3
	bsr.w	sub_014F88
	movem.l	(sp)+,d0-d3
loc_014F86:
	rts


; ----------------------------------------------------------------------
; called from $014F6C, $014F7E
sub_014F88:
	cmp.b	d2,d3
	blt.w	loc_014FAE
	beq.w	loc_014FBE
	mulu.w	#$7,d1
	addi.l	#dat_006496,d1
	move.w	#$7,d2
loc_014FA0:
	jsr	(sub_00B952).l
	addq.l	#1,d0
	jmp	(sub_00B8DE).l
loc_014FAE:
	mulu.w	#$7,d1
	addi.l	#dat_0063E0,d1
	move.w	#$7,d2
	bra.s	loc_014FA0
loc_014FBE:
	mulu.w	#$7,d1
	addi.l	#dat_00654C,d1
	move.w	#$7,d2
	bra.s	loc_014FA0


; ----------------------------------------------------------------------
; called from $014B5A, $014C8C, $014C98, $017A28, $018808, $026FFC, $029C72, $1D449A
sub_014FCE:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_DD9C,a0
	moveq	#$E,d1
	moveq	#$41,d0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $014F06, $0150D6, $0187E8, $0188A4, $026E18, $026EBC, $1D4388, $1D76AC (+3 more)
sub_014FEE:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_DD9C,a0
	moveq	#$E,d1
	moveq	#$41,d0
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
sub_015008:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_015034
	jsr	(sub_1DC2AA).l
	jsr	(sub_1DC2B2).l
	jsr	(sub_1DC2DA).l
	jsr	(sub_1DC2F4).l
	jsr	(sub_1DC288).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01500C, $1D438E
sub_015034:
	move.b	(ram_DD9F).w,(ram_D279).w
	move.b	(ram_DDA0).w,(ram_D27F).w
	move.b	(ram_DDA1).w,(ram_D281).w
	move.b	(ram_DDA4).w,(ram_D283).w
	move.b	(ram_DDA5).w,(ram_D285).w
	move.b	(ram_DDA6).w,(ram_D27B).w
	move.b	(ram_DDA7).w,(ram_D27D).w
	rts


; ----------------------------------------------------------------------
; called from $016946, $022630, $026EEC
sub_015060:
	movem.l	d0-d2/a0,-(sp)
	movea.l	#$0,a2
	movea.l	#ram_DD18,a0
	clr.w	d0
	move.b	(ram_DD17).w,d0
	bra.w	loc_015092
loc_01507A:
	move.b	(a0),d2
	cmp.b	(ram_DDA2).w,d2
	beq.w	loc_01509A
	move.b	$1(a0),d2
	cmp.b	(ram_DDA2).w,d2
	beq.w	loc_01509A
	addq.w	#5,a0
loc_015092:
	dbra	d0,loc_01507A
	bra.w	loc_01509C
loc_01509A:
	movea.l	a0,a2
loc_01509C:
	movem.l	(sp)+,d0-d2/a0
	rts


; ----------------------------------------------------------------------
; called from $014B60
sub_0150A2:
	movem.l	d0/d1,-(sp)
	moveq	#$4F,d0
	move.l	#$D79,d1
	jsr	(sub_029D2A).l
	move.l	#dat_002010,d0
	move.l	#$108,d1
	jsr	(sub_029D2A).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $1D6346
sub_0150D2:
	movem.l	d0/d1,-(sp)
	jsr	(sub_014FEE).l
	moveq	#$4F,d0
	move.l	#$BEC,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_0150FA
	move.l	#$8B,d0
	move.l	#$6A0,d1
loc_0150FA:
	jsr	(sub_029D2A).l
	move.l	#$DF3,d0
	moveq	#$9,d1
	jsr	(sub_029D2A).l
	move.l	#dat_002010,d0
	move.l	#$108,d1
	jsr	(sub_029D2A).l
	move.l	#$DFC,d0
	moveq	#$78,d1
	jsr	(sub_029D2A).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $0151F4, $026EC2
sub_01513A:
	clr.w	(ram_D278).w
	move.b	(ram_DD9F).w,(ram_D279).w
	clr.w	(ram_D27E).w
	move.b	(ram_DDA0).w,(ram_D27F).w
	clr.w	(ram_D280).w
	move.b	(ram_DDA1).w,(ram_D281).w
	clr.w	(ram_D270).w
	btst	#2,(ram_DD9E).w
	beq.w	loc_01516C
	move.w	#$1,(ram_D270).w
loc_01516C:
	rts


; ----------------------------------------------------------------------
; called from $01539E, $0153D8, $015412, $01544C
sub_01516E:
	movem.l	d0-d7/a0,-(sp)
	bra.w	loc_01518C


; ----------------------------------------------------------------------
; called from $01859E, $1D3DA8, $1E3BBE, $1E3D8E, $1E3DC6
sub_015176:
	movem.l	d0-d7/a0,-(sp)
	move.l	#dat_0063E0,d3
	move.l	#dat_00654C,d4
	move.l	#dat_006496,d5
loc_01518C:
	moveq	#$7,d2
	move.w	#$19,d7
loc_015192:
	move.l	d3,d1
	jsr	(sub_00B952).l
	move.b	d0,(a0)+
	addq.l	#7,d3
	move.l	d4,d1
	jsr	(sub_00B952).l
	move.b	d0,(a0)+
	addq.l	#7,d4
	move.l	d5,d1
	jsr	(sub_00B952).l
	move.b	d0,(a0)+
	addq.l	#7,d5
	dbra	d7,loc_015192
	movem.l	(sp)+,d0-d7/a0
	rts


; ----------------------------------------------------------------------
sub_0151C0:
	movem.l	d0/a0,-(sp)
	clr.w	d0
	movea.l	#ram_CFDE,a0
loc_0151CC:
	cmp.b	(a0)+,d7
	beq.w	loc_0151D6
	addq.w	#1,d0
	bra.s	loc_0151CC
loc_0151D6:
	move.w	d0,d7
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
sub_0151DE:
	movem.l	a0,-(sp)
	clr.w	d0
	movea.l	#ram_CFDE,a0
	move.b	$0(a0,d7.w),d7
	movem.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $026F5A
sub_0151F4:
	jsr	(sub_01513A).l
	move.b	(a2),(ram_D275).w
	move.w	(ram_D274).w,(ram_C3AC).w
	move.b	$1(a2),(ram_D277).w
	move.w	(ram_D276).w,(ram_C3AE).w
	rts


; ----------------------------------------------------------------------
; called from $016C2C
sub_015212:
	movem.l	d0-d7/a0/a2-a6,-(sp)
	move.w	(ram_DD9C).w,d0
	addq.w	#3,d0
	clr.w	d1
	movea.l	#dat_015338,a0
	clr.w	d2
loc_015226:
	move.b	$0(a0,d1.w),d2
	cmp.w	d2,d0
	ble.w	loc_015238
	addq.w	#1,d1
	sub.w	d2,d0
	subq.w	#1,d0
	bra.s	loc_015226
loc_015238:
	movea.l	#dat_0152F6,a1
	bra.w	loc_015244
loc_015242:
	adda.w	(a1),a1
loc_015244:
	dbra	d1,loc_015242
	move.w	d0,-(sp)
	movea.l	#ram_BF56,a3
	move.w	(a1),d0
	subq.w	#1,d0
loc_015254:
	move.b	(a1)+,(a3)+
	dbra	d0,loc_015254
	move.w	(sp)+,d0
	addq.w	#1,d0
	cmp.w	#$9,d0	; general form
	ble.w	loc_01526E
	move.w	#$3,d1
	bra.w	loc_015272
loc_01526E:
	move.w	#$2,d1
loc_015272:
	move.w	d0,-(sp)
	jsr	(Num_ToDecimal).l
	movea.l	#ram_BF56,a3
	jsr	(Text_AppendInline_Worker).l
	movea.l	#ptrs_0152E6,a1
	move.w	(sp)+,d0
	ext.l	d0
	cmp.w	#$A,d0	; general form
	blt.w	loc_0152A0
	cmp.w	#$15,d0	; general form
	blt.w	loc_0152D8
loc_0152A0:
	divs.w	#$A,d0
	swap	d0
	cmp.w	#$1,d0	; general form
	bne.w	loc_0152B8
	movea.l	#dat_0152EA,a1
	bra.w	loc_0152D8
loc_0152B8:
	cmp.w	#$2,d0	; general form
	bne.w	loc_0152CA
	movea.l	#dat_0152EE,a1
	bra.w	loc_0152D8
loc_0152CA:
	cmp.w	#$3,d0	; general form
	bne.w	loc_0152D8
	movea.l	#dat_0152F2,a1
loc_0152D8:
	jsr	(Text_AppendInline_Worker).l
	movea.l	a3,a1
	movem.l	(sp)+,d0-d7/a0/a2-a6
	rts

ptrs_0152E6:
	dc.l	dat_045448

dat_0152EA:
	dc.l	dat_045354

dat_0152EE:
	dc.l	dat_044E44

dat_0152F2:
	dc.l	dat_045244
dat_0152F6:
	dc.b	$00,$0A
	dc.b	"OCTOBER",0
	dc.b	$00,$0A
	dc.b	"NOVEMBER",0
	dc.b	$0A
	dc.b	"DECEMBER",0
	dc.b	$0A
	dc.b	"JANUARY",0
	dc.b	$00,$0A
	dc.b	"FEBRUARY",0
	dc.b	$08
	dc.b	"MARCH",0
	dc.b	$00,$08
	dc.b	"APRIL",0
dat_015338:
	dc.w	$1E1D,$1E1E,$1C1E,$1DFF


; ----------------------------------------------------------------------
; called from $1DB66E
sub_015340:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_00BC20).l
	movea.l	#ram_BF56,a5
	move.l	a5,-(sp)
	move.w	#$1,d1
loc_015356:
	move.w	d1,d0
	jsr	(sub_00BC68).l
	move.w	d0,(a5)+
	addq.w	#1,d1
	cmp.w	#$5,d1	; general form
	blt.s	loc_015356
	movea.l	(sp)+,a5
	movea.l	#SaveDataMirror,a0
	move.w	#$1,d0
	jsr	(sub_00BCB0).l
	tst.l	d0
	bmi.w	loc_0153A4
	add.l	d0,d0
	add.l	d0,d0
	add.l	d0,d0
	move.l	#dat_0061D8,d3
	add.l	d0,d3
	move.l	#dat_006344,d4
	add.l	d0,d4
	move.l	#dat_00628E,d5
	add.l	d0,d5
	jsr	(sub_01516E).l
loc_0153A4:
	movea.l	#ram_01F4,a0
	move.w	#$2,d0
	jsr	(sub_00BCB0).l
	tst.l	d0
	bmi.w	loc_0153DE
	add.l	d0,d0
	add.l	d0,d0
	add.l	d0,d0
	move.l	#dat_0061D8,d3
	add.l	d0,d3
	move.l	#dat_006344,d4
	add.l	d0,d4
	move.l	#dat_00628E,d5
	add.l	d0,d5
	jsr	(sub_01516E).l
loc_0153DE:
	movea.l	#ram_03E8,a0
	move.w	#$3,d0
	jsr	(sub_00BCB0).l
	tst.l	d0
	bmi.w	loc_015418
	add.l	d0,d0
	add.l	d0,d0
	add.l	d0,d0
	move.l	#dat_0061D8,d3
	add.l	d0,d3
	move.l	#dat_006344,d4
	add.l	d0,d4
	move.l	#dat_00628E,d5
	add.l	d0,d5
	jsr	(sub_01516E).l
loc_015418:
	movea.l	#ram_05DC,a0
	move.w	#$4,d0
	jsr	(sub_00BCB0).l
	tst.l	d0
	bmi.w	loc_015452
	add.l	d0,d0
	add.l	d0,d0
	add.l	d0,d0
	move.l	#dat_0061D8,d3
	add.l	d0,d3
	move.l	#dat_006344,d4
	add.l	d0,d4
	move.l	#dat_00628E,d5
	add.l	d0,d5
	jsr	(sub_01516E).l
loc_015452:
	bsr.w	sub_0156EC
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_DDE2).w
	move.w	#$1,d0
	bsr.w	sub_015A36
loc_015474:
	bsr.w	sub_015892
loc_015478:
	move.w	(FrameCounter).w,d0
loc_01547C:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_01547C
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_015478
	btst	#4,d1
	beq.w	loc_0154A6
	bclr	#7,(SysFlags).w
	jmp	(loc_026D3E).l
loc_0154A6:
	btst	#0,d1
	beq.w	loc_0154C6
	subq.w	#1,(ram_DDE2).w
	bpl.w	loc_0154BC
	move.w	#$3,(ram_DDE2).w
loc_0154BC:
	move.w	#$FFFF,d0
	bsr.w	sub_015A36
	bra.s	loc_015474
loc_0154C6:
	btst	#1,d1
	beq.w	loc_0154EA
	addq.w	#1,(ram_DDE2).w
	cmpi.w	#$4,(ram_DDE2).w
	blt.w	loc_0154E0
	clr.w	(ram_DDE2).w
loc_0154E0:
	move.w	#$1,d0
	bsr.w	sub_015A36
	bra.s	loc_015474
loc_0154EA:
	btst	#5,d1
	beq.s	loc_015478
	btst	#6,(ram_C354).w
	beq.w	loc_0156D4
	movea.l	#ram_BF56,a3
	move.w	(ram_DDE2).w,d0
	add.w	d0,d0
	cmpi.w	#$2,$0(a3,d0.w)
	bne.w	loc_0156D4
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01A).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_015520:
	dc.w	loc_015542-inl_015520
	dc.b	$BF,$06,$14
	dc.b	"         WARNING !          ",0
loc_015542:
	jsr	(Text_PrintFont).l
inl_015548:
	dc.w	loc_01556A-inl_015548
	dc.b	$BF,$06,$15
	dc.b	"                            ",0
loc_01556A:
	jsr	(Text_PrintFont).l
inl_015570:
	dc.w	loc_015592-inl_015570
	dc.b	$BF,$06,$16
	dc.b	" You are about to overwrite ",0
loc_015592:
	jsr	(Text_PrintFont).l
inl_015598:
	dc.w	loc_0155BA-inl_015598
	dc.b	$BF,$06,$17
	dc.b	"    the existing season     ",0
loc_0155BA:
	jsr	(Text_PrintFont).l
inl_0155C0:
	dc.w	loc_0155E2-inl_0155C0
	dc.b	$BF,$06,$18
	dc.b	" C to continue, B to cancel ",0
loc_0155E2:
	move.w	(sp)+,(FontTileBase).w
loc_0155E6:
	move.w	(FrameCounter).w,d0
loc_0155EA:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_0155EA
	jsr	(sub_0202D2).l
	tst.w	d1
	beq.s	loc_0155EA
	btst	#5,d1
	bne.w	loc_0156D4
	btst	#4,d1
	beq.s	loc_0155E6
	jsr	(Text_PrintFont).l
inl_01560E:
	dc.w	loc_015630-inl_01560E
	dc.b	$BF,$06,$14
	dc.b	"                            ",0
loc_015630:
	jsr	(Text_PrintFont).l
inl_015636:
	dc.w	loc_015658-inl_015636
	dc.b	$BF,$06,$15
	dc.b	"                            ",0
loc_015658:
	jsr	(Text_PrintFont).l
inl_01565E:
	dc.w	loc_015680-inl_01565E
	dc.b	$BF,$06,$16
	dc.b	"                            ",0
loc_015680:
	jsr	(Text_PrintFont).l
inl_015686:
	dc.w	loc_0156A8-inl_015686
	dc.b	$BF,$06,$17
	dc.b	"                            ",0
loc_0156A8:
	jsr	(Text_PrintFont).l
inl_0156AE:
	dc.w	loc_0156D0-inl_0156AE
	dc.b	$BF,$06,$18
	dc.b	"                            ",0
loc_0156D0:
	bra.w	loc_015478
loc_0156D4:
	move.w	(ram_DDE2).w,d0
	addq.w	#1,d0
	jmp	(loc_0156E0).l
loc_0156E0:
	jsr	(sub_00BD2C).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $015452
sub_0156EC:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).l
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B400,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_015768:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_015770:
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_015780:
	dc.w	$0123,$4567,$89EE,$EEEF
loc_015788:
	move.w	d4,(ram_B01A).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_015798:
	dc.w	$E123,$4567,$89DE,$EEEF
loc_0157A0:
	move.l	#Font_Menu,(FontPtr).l
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_0157BA:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_0157C2:
	bclr	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).l
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_0157E8:
	dc.w	loc_0157F0-inl_0157E8
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_0157F0:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintFont).l
inl_015804:
	dc.w	loc_01582C-inl_015804
	dc.b	$8F,$02,$1A
	dc.b	"{}-CHANGE SLOT  B-CANCEL  C-SELECT",0
loc_01582C:
	jsr	(Text_Print).l
inl_015832:
	dc.w	loc_015838-inl_015832
	dc.b	$FE,$00,$00,$00
loc_015838:
	movea.l	#Art_PlayoffLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$9,d5
	jsr	(TileMap_Draw).l
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_015862:
	dc.w	loc_015874-inl_015862
	dc.b	$BF,$09,$01
	dc.b	"TRANSACTIONS",0
loc_015874:
	jsr	(Text_PrintBig).l
inl_01587A:
	dc.w	loc_01588C-inl_01587A
	dc.b	$BF,$08,$01
	dc.b	"SELECT SEASON"
loc_01588C:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $015474
sub_015892:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d1
	movea.l	#ram_BF56,a3
loc_01589E:
	movea.l	#dat_015A1E,a1
	move.w	d1,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	cmp.w	(ram_DDE2).w,d1
	bne.w	loc_0158C4
	jsr	(Text_PrintCmd).l
inl_0158C0:
	dc.w	loc_0158C4-inl_0158C0
	dc.b	$FE,$07
loc_0158C4:
	move.w	d1,d0
	add.w	d0,d0
	tst.w	$0(a3,d0.w)
	bne.w	loc_015904
	btst	#6,(ram_C354).w
	bne.w	loc_0158E4
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
loc_0158E4:
	jsr	(Text_PrintFont).l
inl_0158EA:
	dc.w	loc_0158F2-inl_0158EA
	dc.b	"unused"
loc_0158F2:
	btst	#6,(ram_C354).w
	bne.w	loc_015900
	move.w	(sp)+,(FontTileBase).w
loc_015900:
	bra.w	loc_015A0E
loc_015904:
	move.w	d1,d0
	addq.w	#1,d0
	jsr	(sub_00BCB0).l
	move.l	d0,(ram_BF4E).w
	movea.l	#$200000,a4
	addq.l	#6,d0
	add.l	d0,d0
	move.w	$0(a4,d0.l),d7
	andi.w	#$FF,d7
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_015938
	movea.l	#RosterTable,a1
loc_015938:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_015950:
	dc.w	loc_015954-inl_015950
	dc.b	$20,$00
loc_015954:
	move.l	(ram_BF4E).w,d0
	addq.l	#2,d0
	add.l	d0,d0
	move.w	$0(a4,d0.l),d6
	andi.w	#$FF,d6
	btst	#0,d6
	beq.w	loc_01598E
	btst	#1,d6
	beq.w	loc_01598E
	jsr	(Text_PrintFont).l
inl_01597A:
	dc.w	loc_01598A-inl_01597A
	dc.b	"- season over",0
loc_01598A:
	bra.w	loc_015A0E
loc_01598E:
	btst	#2,d6
	beq.w	loc_0159AC
	jsr	(Text_PrintFont).l
inl_01599C:
	dc.w	loc_0159A8-inl_01599C
	dc.b	"- playoffs"
loc_0159A8:
	bra.w	loc_015A0E
loc_0159AC:
	movea.l	#SaveDataMirror,a0
	move.w	d1,d0
	mulu.w	#$1F4,d0
	adda.w	d0,a0
	move.w	d7,d5
	mulu.w	#$3,d5
	clr.w	d0
	move.w	d1,-(sp)
	move.w	#$2,d1
	move.b	$0(a0,d5.w),d0
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_0159DE:
	dc.w	loc_0159E2-inl_0159DE
	dc.b	$2D,$00
loc_0159E2:
	move.b	$2(a0,d5.w),d0
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_0159F8:
	dc.w	loc_0159FC-inl_0159F8
	dc.b	$2D,$00
loc_0159FC:
	move.b	$1(a0,d5.w),d0
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp)+,d1
loc_015A0E:
	addq.w	#1,d1
	cmp.w	#$4,d1	; general form
	blt.w	loc_01589E
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_015A1E:
	dc.w	$0006,$BF0F,$0A00,$0006,$BF0F,$0C00,$0006,$BF0F
	dc.w	$0E00,$0006,$BF0F,$1000


; ----------------------------------------------------------------------
; called from $015470, $0154C0, $0154E4
sub_015A36:
	btst	#6,(ram_C354).w
	bne.w	loc_015A7A
	movem.l	d1/a0,-(sp)
	movea.l	#ram_BF56,a0
loc_015A4A:
	move.w	(ram_DDE2).w,d1
	add.w	d1,d1
	tst.w	$0(a0,d1.w)
	bne.w	loc_015A76
	add.w	d0,(ram_DDE2).w
	bpl.w	loc_015A68
	move.w	#$3,(ram_DDE2).w
	bra.s	loc_015A4A
loc_015A68:
	cmpi.w	#$4,(ram_DDE2).w
	blt.s	loc_015A4A
	clr.w	(ram_DDE2).w
	bra.s	loc_015A4A
loc_015A76:
	movem.l	(sp)+,d1/a0
loc_015A7A:
	rts


; ----------------------------------------------------------------------
; called from $026E90, $026F8C, $1E4970
sub_015A7C:
	clr.w	(ram_D330).w
	bsr.w	sub_016538
	btst	#7,(SysFlags).w
	beq.w	loc_015A98
	btst	#6,(ram_C354).w
	beq.w	loc_015F30
loc_015A98:
	btst	#7,(SysFlags).w
	bne.w	loc_015AAC
	move.w	#$2,-(sp)
	jsr	(sub_092172).l
loc_015AAC:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#7,(ram_C350).w
	beq.w	loc_015AC0
	bset	#7,(SysFlags).w
loc_015AC0:
	btst	#7,(SysFlags).w
	beq.w	loc_015AD4
	move.b	#$0,(ram_DDA2).w
	bra.w	loc_015B3C
loc_015AD4:
	tst.w	(ram_D294).w
	bne.w	loc_015B0C
	move.w	#$19,d0
	jsr	(Random).l
	move.w	d0,(ram_D274).w
	move.w	#$19,d0
	jsr	(Random).l
	cmp.w	(ram_D274).w,d0
	bne.w	loc_015B08
	addq.w	#1,d0
	cmp.w	#$1A,d0	; general form
	blt.w	loc_015B08
	clr.w	d0
loc_015B08:
	move.w	d0,(ram_D276).w
loc_015B0C:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_015B3C
	move.w	(ram_D274).w,(ram_C3AC).w
	move.w	(ram_D276).w,(ram_C3AE).w
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_015B36
	cmpi.w	#$3,(ram_D270).w
	bne.w	loc_015B3C
loc_015B36:
	jsr	(sub_027276).l
loc_015B3C:
	bsr.w	sub_015F32
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	btst	#7,(SysFlags).w
	bne.w	loc_015B62
	bsr.w	sub_01615E
	bsr.w	sub_0161FA
	bra.w	loc_015B66
loc_015B62:
	bsr.w	sub_016296
loc_015B66:
	bset	#0,(ram_2710).l
	bclr	#1,(ram_2710).l
	bclr	#2,(ram_2710).l
	move.w	#$1,(ram_2720).l
loc_015B86:
	move.w	(FrameCounter).w,d0
loc_015B8A:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_015B8A
	tst.w	(ram_D294).w
	bne.w	loc_015B9C
	addq.w	#1,(ram_D330).w
loc_015B9C:
	cmpi.w	#$2A30,(ram_D330).w
	blt.w	loc_015BAE
	clr.w	(ram_D294).w
	bra.w	loc_015EA4
loc_015BAE:
	bclr	#0,(ram_2710).l
	beq.w	loc_015C00
	btst	#7,(SysFlags).w
	bne.w	loc_015BF8
	bsr.w	sub_01659A
	bclr	#1,(ram_2710).l
	bne.w	loc_015BD8
	bra.w	loc_015BE0
loc_015BD8:
	bsr.w	sub_01649E
	bsr.w	sub_01615E
loc_015BE0:
	bclr	#2,(ram_2710).l
	beq.w	loc_015C00
	bsr.w	sub_0164C4
	bsr.w	sub_0161FA
	bra.w	loc_015C00
loc_015BF8:
	bsr.w	sub_016476
	bsr.w	sub_016296
loc_015C00:
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_015C16
	clr.w	(ram_D330).w
loc_015C16:
	tst.w	(ram_D270).w
	bne.w	loc_015CD8
	tst.b	(ram_DEB0).w
	beq.w	loc_015CD8
	tst.b	(ram_DEB1).w
	bne.s	loc_015C6C
	st	(ram_DEB1).w
	move.w	#$19,d0
	jsr	(Random).l
	move.w	d0,(ram_D274).w
	move.w	#$19,d0
	jsr	(Random).l
	cmp.w	(ram_D274).w,d0
	bne.w	loc_015B08
	addq.w	#1,d0
	cmp.w	#$1A,d0	; general form
	blt.w	loc_015C5C
	clr.w	d0
loc_015C5C:
	move.w	d0,(ram_D276).w
	move.w	(ram_D274).w,(ram_C3AC).w
	move.w	(ram_D276).w,(ram_C3AE).w
loc_015C6C:
	btst	#7,d1
	beq.s	loc_015C90
	move.w	#$78,d2
loc_015C76:
	move.w	(FrameCounter).w,d0
loc_015C7A:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_015C7A
	dbra	d2,loc_015C76
	clr.b	(ram_DEB0).w
	clr.b	(ram_DEB1).w
	bra.w	loc_015EA4
loc_015C90:
	addq.b	#1,(ram_DEB4).w
	andi.b	#$1,(ram_DEB4).w
	bne.s	loc_015CB4
	bset	#2,(ram_2710).l
	subq.w	#1,(ram_C3AE).w
	bpl.s	loc_015CC8
	move.w	#$1E,(ram_C3AE).w
	bra.w	loc_015CC8
loc_015CB4:
	bset	#1,(ram_2710).l
	subq.w	#1,(ram_C3AC).w
	bpl.s	loc_015CC8
	move.w	#$1E,(ram_C3AC).w
loc_015CC8:
	bset	#0,(ram_2710).l
	move.w	#$2500,sr
	bra.w	loc_015B86
loc_015CD8:
	btst	#7,d1
	bne.w	loc_015EA4
	btst	#7,(SysFlags).w
	bne.w	loc_015D48
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_015B86
	btst	#2,d1
	beq.w	loc_015D20
	subi.w	#$1,(ram_2720).l
	bpl.w	loc_015D12
	clr.w	(ram_2720).l
	bra.w	loc_015B86
loc_015D12:
	jsr	(sub_01659A).l
	move.w	#$2500,sr
	bra.w	loc_015B86
loc_015D20:
	btst	#3,d1
	beq.w	loc_015D48
	tst.w	(ram_2720).l
	bne.w	loc_015B86
	move.w	#$1,(ram_2720).l
	jsr	(sub_01659A).l
	move.w	#$2500,sr
	bra.w	loc_015B86
loc_015D48:
	btst	#0,d1
	beq.w	loc_015DEE
	cmpi.w	#$3,(ram_D270).w
	beq.w	loc_015D64
	cmpi.w	#$2,(ram_D270).w
	bne.w	loc_015D8C
loc_015D64:
	subq.w	#1,(ram_D274).w
	bpl.w	loc_015D72
	move.w	#$19,(ram_D274).w
loc_015D72:
	jsr	(sub_027276).l
	bset	#1,(ram_2710).l
	bset	#2,(ram_2710).l
	bra.w	loc_015DE2
loc_015D8C:
	btst	#7,(SysFlags).w
	bne.w	loc_015DD4
	tst.w	(ram_2720).l
	bne.w	loc_015DBA
	bset	#2,(ram_2710).l
	subq.w	#1,(ram_C3AE).w
	bpl.w	loc_015DE2
	move.w	#$1E,(ram_C3AE).w
	bra.w	loc_015DE2
loc_015DBA:
	bset	#1,(ram_2710).l
	subq.w	#1,(ram_C3AC).w
	bpl.w	loc_015DE2
	move.w	#$1E,(ram_C3AC).w
	bra.w	loc_015DE2
loc_015DD4:
	subq.b	#1,(ram_DDA2).w
	bpl.w	loc_015DE2
	move.b	#$19,(ram_DDA2).w
loc_015DE2:
	bset	#0,(ram_2710).l
	bra.w	loc_015B86
loc_015DEE:
	btst	#1,d1
	beq.w	loc_015B86
	cmpi.w	#$3,(ram_D270).w
	beq.w	loc_015E0A
	cmpi.w	#$2,(ram_D270).w
	bne.w	loc_015E36
loc_015E0A:
	addq.w	#1,(ram_D274).w
	cmpi.w	#$1A,(ram_D274).w
	blt.w	loc_015E1C
	clr.w	(ram_D274).w
loc_015E1C:
	bset	#1,(ram_2710).l
	bset	#2,(ram_2710).l
	jsr	(sub_027276).l
	bra.w	loc_015E98
loc_015E36:
	btst	#7,(SysFlags).w
	bne.w	loc_015E86
	tst.w	(ram_2720).l
	bne.w	loc_015E68
	bset	#2,(ram_2710).l
	addq.w	#1,(ram_C3AE).w
	cmpi.w	#$1F,(ram_C3AE).w
	blt.w	loc_015E98
	clr.w	(ram_C3AE).w
	bra.w	loc_015E98
loc_015E68:
	bset	#1,(ram_2710).l
	addq.w	#1,(ram_C3AC).w
	cmpi.w	#$1F,(ram_C3AC).w
	blt.w	loc_015E98
	clr.w	(ram_C3AC).w
	bra.w	loc_015E98
loc_015E86:
	addq.b	#1,(ram_DDA2).w
	cmpi.b	#$1A,(ram_DDA2).w
	blt.w	loc_015E98
	clr.b	(ram_DDA2).w
loc_015E98:
	bset	#0,(ram_2710).l
	bra.w	loc_015B86
loc_015EA4:
	movea.l	#ram_C732,a0
	jsr	(sub_1CF682).l
	movea.l	#ram_CAD0,a0
	jsr	(sub_1CF682).l
	btst	#0,(ram_C34A).w
	beq.w	loc_015EE4
	move.w	(ram_D472).w,-(sp)
	clr.w	(ram_D472).w
	jsr	(sub_1D0C3E).l
	move.w	#$1,(ram_D472).w
	jsr	(sub_1D0C3E).l
	move.w	(sp)+,(ram_D472).w
loc_015EE4:
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_015EF8
	cmpi.w	#$3,(ram_D270).w
	bne.w	loc_015F0C
loc_015EF8:
	move.b	#$1,($204233).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
loc_015F0C:
	btst	#7,(ram_C350).w
	beq.w	loc_015F2C
	bclr	#7,(SysFlags).w
	clr.w	(ram_C3AC).w
	move.b	(ram_DDA2).w,(ram_C3AD).w
	move.w	(ram_C3AC).w,(ram_C3AE).w
loc_015F2C:
	movem.l	(sp)+,d0-d7/a0-a6
loc_015F30:
	rts


; ----------------------------------------------------------------------
; called from $015B3C
sub_015F32:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).l
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B400,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(ram_B014).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_015FB2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_015FBA:
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_2716).l
	addi.w	#$A0,d4
	move.w	d4,(ram_2718).l
	addi.w	#$A0,d4
	jsr	(Text_PrintCmd).l
inl_015FEA:
	dc.w	loc_015FF2-inl_015FEA
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_015FF2:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_016006:
	dc.w	loc_01600C-inl_016006
	dc.b	$FE,$00,$00,$00
loc_01600C:
	movea.l	#Art_PlayoffLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$9,d5
	jsr	(TileMap_Draw).l
	tst.w	(ram_D270).w
	bne.s	loc_016056
	tst.b	(ram_DEB0).w
	beq.s	loc_016056
	jsr	(Text_PrintBig).l
inl_01603C:
	dc.w	loc_016054-inl_01603C
	dc.b	$FF,$03,$01
	dc.b	"RANDOM TEAM SELECT",0
loc_016054:
	bra.s	loc_01606C
loc_016056:
	jsr	(Text_PrintBig).l
inl_01605C:
	dc.w	loc_01606C-inl_01605C
	dc.b	$FF,$0A,$01
	dc.b	"TEAM SELECT"
loc_01606C:
	btst	#7,(ram_C350).w
	bne.w	loc_016080
	btst	#7,(SysFlags).w
	beq.w	loc_016088
loc_016080:
	bsr.w	sub_016476
	bra.w	loc_016090
loc_016088:
	bsr.w	sub_01649E
	bsr.w	sub_0164C4
loc_016090:
	btst	#7,(SysFlags).w
	bne.w	loc_0160F8
	jsr	(Text_PrintNarrow).l
inl_0160A0:
	dc.w	loc_0160F4-inl_0160A0
	dc.b	$F8,$04,$01,$0E,$10
	dc.b	"EVEN-STRENGTH"
	dc.b	$F8,$04,$01,$0F,$12
	dc.b	"POWER-PLAY"
	dc.b	$F8,$04,$01,$0D,$14
	dc.b	"PENALTY KILLING"
	dc.b	$F8,$04,$01,$0F,$16
	dc.b	"GOALTENDING"
	dc.b	$F8,$04,$01,$11,$18
	dc.b	"OVERALL",0
loc_0160F4:
	bra.w	loc_016152
loc_0160F8:
	jsr	(Text_PrintNarrow).l
inl_0160FE:
	dc.w	loc_016152-inl_0160FE
	dc.b	$F8,$04,$01,$12,$06
	dc.b	"EVEN-STRENGTH"
	dc.b	$F8,$04,$01,$12,$08
	dc.b	"POWER-PLAY"
	dc.b	$F8,$04,$01,$12,$0A
	dc.b	"PENALTY KILLING"
	dc.b	$F8,$04,$01,$12,$0C
	dc.b	"GOALTENDING"
	dc.b	$F8,$04,$01,$12,$0E
	dc.b	"OVERALL",0
loc_016152:
	jsr	(sub_01659A).l
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $015B56, $015BDC, $0165A8
sub_01615E:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_B014).w,-(sp)
	cmpi.w	#$1,(ram_DDDA).w
	bne.w	loc_016186
	move.w	(ram_B018).w,(ram_B014).w
	jsr	(Text_Print).l
inl_01617C:
	dc.w	loc_016182-inl_01617C
	dc.b	$8F,$1E,$10,$00
loc_016182:
	bra.w	loc_016192
loc_016186:
	jsr	(Text_Print).l
inl_01618C:
	dc.w	loc_016192-inl_01618C
	dc.b	$BF,$1E,$10,$00
loc_016192:
	move.w	(TextX).w,-(sp)
	movea.l	#ptrtbl_016462,a5
	move.w	#$4,d7
loc_0161A0:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a0
	move.w	(ram_C3AC).w,d0
	jsr	(a0)
	move.w	#$2,d1
	tst.w	d0
	bmi.w	loc_0161CC
	move.w	d0,-(sp)
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,d0
	bra.w	loc_0161DC
loc_0161CC:
	jsr	(Text_PrintNarrow).l
inl_0161D2:
	dc.w	loc_0161D8-inl_0161D2
	dc.b	"N/A "
loc_0161D8:
	bra.w	loc_0161E0
loc_0161DC:
	bsr.w	sub_0162F0
loc_0161E0:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	dbra	d7,loc_0161A0
	move.w	(sp)+,(TextX).w
	move.w	(sp)+,(ram_B014).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $015B5A, $015BF0, $0165A4
sub_0161FA:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_B014).w,-(sp)
	cmpi.w	#$2,(ram_DDDA).w
	bne.w	loc_016222
	move.w	(ram_B018).w,(ram_B014).w
	jsr	(Text_Print).l
inl_016218:
	dc.w	loc_01621E-inl_016218
	dc.b	$8F,$06,$10,$00
loc_01621E:
	bra.w	loc_01622E
loc_016222:
	jsr	(Text_Print).l
inl_016228:
	dc.w	loc_01622E-inl_016228
	dc.b	$BF,$06,$10,$00
loc_01622E:
	move.w	(TextX).w,-(sp)
	movea.l	#ptrtbl_016462,a5
	move.w	#$4,d7
loc_01623C:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a0
	move.w	(ram_C3AE).w,d0
	jsr	(a0)
	move.w	#$2,d1
	tst.w	d0
	bmi.w	loc_016268
	move.w	d0,-(sp)
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,d0
	bra.w	loc_016278
loc_016268:
	jsr	(Text_PrintNarrow).l
inl_01626E:
	dc.w	loc_016274-inl_01626E
	dc.b	"N/A "
loc_016274:
	bra.w	loc_01627C
loc_016278:
	bsr.w	sub_0162F0
loc_01627C:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	dbra	d7,loc_01623C
	move.w	(sp)+,(TextX).w
	move.w	(sp)+,(ram_B014).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $015B62, $015BFC
sub_016296:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_0162A0:
	dc.w	loc_0162A6-inl_0162A0
	dc.b	$BF,$22,$06,$00
loc_0162A6:
	move.w	(TextX).w,-(sp)
	movea.l	#ptrtbl_016462,a5
	move.w	#$4,d7
loc_0162B4:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a0
	move.b	(ram_DDA2).w,d0
	jsr	(a0)
	move.w	#$2,d1
	move.w	d0,-(sp)
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,d0
	bsr.w	sub_0162F0
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	dbra	d7,loc_0162B4
	move.w	(sp)+,(TextX).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0161DC, $016278, $0162D6
sub_0162F0:
	ext.l	d0
	cmp.w	#$A,d0	; general form
	blt.w	loc_01630E
	cmp.w	#$15,d0	; general form
	bge.w	loc_01630E
	movea.l	#dat_01634E,a1
	jmp	(Text_PrintNarrow_Worker).l
loc_01630E:
	divs.w	#$A,d0
	swap	d0
	asl.w	#2,d0
	movea.l	#ptrs_016326,a0
	movea.l	$0(a0,d0.w),a1
	jmp	(Text_PrintNarrow_Worker).l

ptrs_016326:
	dc.l	dat_01634E
	dc.l	dat_016352
	dc.l	dat_016356
	dc.l	dat_01635A
	dc.l	dat_01634E
	dc.l	dat_01634E
	dc.l	dat_01634E
	dc.l	dat_01634E
	dc.l	dat_01634E
	dc.l	dat_01634E

dat_01634E:
	dc.l	dat_045448

dat_016352:
	dc.l	dat_045354

dat_016356:
	dc.l	dat_044E44

dat_01635A:
	dc.l	dat_045244


; ----------------------------------------------------------------------
; called from $016472
sub_01635E:
	move.l	a0,-(sp)
	ext.w	d0
	movea.l	#dat_016372,a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movea.l	(sp)+,a0
	rts
dat_016372:
	dc.w	$091A,$0615,$130E,$0102,$050D,$0718,$1103,$1608
	dc.w	$1004,$0B0A,$190C,$1417,$0F12,$FFFF,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $01646E
sub_016392:
	move.l	a0,-(sp)
	ext.w	d0
	movea.l	#dat_0163A6,a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movea.l	(sp)+,a0
	rts
dat_0163A6:
	dc.w	$0910,$1A08,$0411,$0313,$0706,$1519,$0D17,$1601
	dc.w	$0B12,$0502,$140F,$180E,$0A0C,$FFFF,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $01646A
sub_0163C6:
	move.l	a0,-(sp)
	ext.w	d0
	movea.l	#dat_0163DA,a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movea.l	(sp)+,a0
	rts
dat_0163DA:
	dc.w	$1615,$0D11,$0A0B,$0210,$0412,$0703,$1A01,$0F19
	dc.w	$1406,$0517,$0C0E,$0813,$1809,$FFFF,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $016466
sub_0163FA:
	move.l	a0,-(sp)
	ext.w	d0
	movea.l	#dat_01640E,a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movea.l	(sp)+,a0
	rts
dat_01640E:
	dc.w	$0B1A,$060D,$1307,$0503,$0210,$0414,$1701,$120A
	dc.w	$0C08,$0F19,$180E,$1116,$1509,$FFFF,$FFFF,$FFFF


; ----------------------------------------------------------------------
; called from $016462
sub_01642E:
	move.l	a0,-(sp)
	ext.w	d0
	movea.l	#dat_016442,a0
	move.b	$0(a0,d0.w),d0
	ext.w	d0
	movea.l	(sp)+,a0
	rts
dat_016442:
	dc.w	$091A,$0615,$130E,$0102,$050D,$0718,$1103,$1608
	dc.w	$1004,$0B0A,$190C,$1417,$0F12,$FFFF,$FFFF,$FFFF

ptrtbl_016462:
	dc.l	sub_01642E
	dc.l	sub_0163FA
	dc.l	sub_0163C6
	dc.l	sub_016392
	dc.l	sub_01635E


; ----------------------------------------------------------------------
; called from $015BF8, $016080
sub_016476:
	jsr	(Text_Print).l
inl_01647C:
	dc.w	loc_016482-inl_01647C
	dc.b	$BF,$02,$08,$00
loc_016482:
	clr.l	d7
	move.b	(ram_DDA2).w,d7
	move.w	(ram_2716).l,d4
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $015BD8, $016088
sub_01649E:
	jsr	(Text_Print).l
inl_0164A4:
	dc.w	loc_0164AA-inl_0164A4
	dc.b	$BF,$18,$04,$00
loc_0164AA:
	move.w	(ram_C3AC).w,d7
	move.w	(ram_2716).l,d4
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $015BEC, $01608C
sub_0164C4:
	jsr	(Text_Print).l
inl_0164CA:
	dc.w	loc_0164D0-inl_0164CA
	dc.b	$8F,$02,$04,$00
loc_0164D0:
	move.w	(ram_C3AE).w,d7
	move.w	(ram_2718).l,d4
	clr.w	d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $1DD1E4
sub_0164EA:
	move.w	#$1,d4
	lea	$8(a1),a2
	adda.l	(a1),a1
	jmp	(sub_020780).l


; ----------------------------------------------------------------------
; called from $1DD5D0
sub_0164FA:
	move.w	#$80,d0
	move.w	#$80,d1
	move.w	#$0,d2
	move.w	#$1,d3
	ori.w	#$6000,d3
	movea.l	#ram_C068,a6
	move.w	#$1,d6
	jsr	(sub_1D4A46).l
	clr.b	-$5(a6)
	move.l	a6,d0
	subi.l	#ram_C068,d0
	lsr.w	#1,d0
	move.w	d0,(ram_C338).w
	bset	#0,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $015A80, $01659A
sub_016538:
	clr.w	(ram_DDDA).w
	btst	#7,(SysFlags).w
	bne.w	loc_016598
	movem.l	d0/a0,-(sp)
	tst.w	(ram_D270).w
	beq.w	loc_016576
	cmpi.w	#$3,(ram_D270).w
	bgt.w	loc_016576
	move.w	(ram_CFD8).w,d0
	movea.l	#ram_CFDE,a0
	move.b	$0(a0,d0.w),d0
	cmp.w	(ram_C3AC).w,d0
	beq.w	loc_016584
	bra.w	loc_01658E
loc_016576:
	tst.w	(ram_2720).l
	bne.w	loc_016584
	bra.w	loc_01658E
loc_016584:
	move.w	#$1,(ram_DDDA).w
	bra.w	loc_016594
loc_01658E:
	move.w	#$2,(ram_DDDA).w
loc_016594:
	movem.l	(sp)+,d0/a0
loc_016598:
	rts


; ----------------------------------------------------------------------
; called from $015BC4, $015D12, $015D3A, $016152
sub_01659A:
	bsr.s	sub_016538
	tst.w	(ram_DDDA).w
	beq.w	loc_0165AC
	bsr.w	sub_0161FA
	bsr.w	sub_01615E
loc_0165AC:
	rts


; ----------------------------------------------------------------------
; called from $026F3C, $026F68, $02706C
sub_0165AE:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	(ram_D01E).w,-(sp)
	move.l	(ram_D022).w,-(sp)
	move.w	(ram_D01A).w,-(sp)
	move.w	(ram_D01C).w,-(sp)
	btst	#1,(ram_C35C).w
	bne.w	loc_0165D6
	move.w	#$3,-(sp)
	jsr	(sub_092172).l
loc_0165D6:
	movea.l	(ram_DDD0).w,a0
	cmpa.l	#NullEntry,a0
	beq.w	loc_0165F8
	move.w	(ram_C3AC).w,-(sp)
	move.w	(ram_C3AE).w,-(sp)
	jsr	(a0)
	move.w	(sp)+,(ram_C3AE).w
	move.w	(sp)+,(ram_C3AC).w
	bra.s	loc_0165D6
loc_0165F8:
	bclr	#1,(ram_C35C).w
	move.l	(sp)+,(ram_D022).w
	move.w	(sp)+,(ram_D01A).w
	move.w	(sp)+,(ram_D01C).w
	move.l	(sp)+,(ram_D01E).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $026F34, $026F60, $027064, $1D5596, $1D60D8, $1E0864, $1E1FF2
sub_016614:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_D330).w
	bsr.w	sub_016858
	clr.w	d0
	move.b	(ram_DDA3).w,d0
	move.w	d0,(ram_2722).l
	beq.w	loc_016636
	subq.w	#1,(ram_2722).l
loc_016636:
	cmp.w	(ram_2724).l,d0
	blt.w	loc_016650
	move.w	(ram_2724).l,(ram_2722).l
	subq.w	#1,(ram_2722).l
loc_016650:
	bsr.w	sub_0172C2
	bset	#5,(ram_C358).w
	bsr.w	sub_016972
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	bset	#2,(ram_C346).w
	bsr.w	sub_016CD4
	bclr	#2,(ram_C346).w
	move.w	(FrameCounter).w,d0
loc_01667E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_01667E
	bsr.w	sub_017334
	clr.w	(ram_2710).l
loc_01668E:
	move.w	(FrameCounter).w,d0
loc_016692:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_016692
	bclr	#0,(ram_2710).l
	beq.w	loc_0166A8
	bsr.w	sub_016CD4
loc_0166A8:
	cmpi.w	#$5460,(ram_D330).w
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_0166C4
	clr.w	(ram_D330).w
loc_0166C4:
	btst	#7,d1
	bne.w	loc_01684C
	btst	#5,d1
	bne.w	loc_01684C
	btst	#0,d1
	beq.w	loc_0166E6
	subq.w	#1,(ram_D01A).w
	bsr.w	sub_017334
	bra.s	loc_01668E
loc_0166E6:
	btst	#1,d1
	beq.w	loc_0166F8
	addq.w	#1,(ram_D01A).w
	bsr.w	sub_017334
	bra.s	loc_01668E
loc_0166F8:
	btst	#2,d1
	beq.w	loc_016798
	tst.w	(ram_2722).l
	beq.s	loc_01668E
	cmpi.w	#$2,(ram_2722).l
	ble.w	loc_01671C
	bset	#1,(ram_2710).l
loc_01671C:
	move.w	(ram_271E).l,-(sp)
	move.w	(ram_271C).l,(ram_271E).l
	move.w	(ram_271A).l,(ram_271C).l
	move.w	(ram_2718).l,(ram_271A).l
	move.w	(ram_2716).l,(ram_2718).l
	move.w	(sp)+,(ram_2716).l
	subq.w	#1,(ram_2722).l
	bset	#0,(ram_2710).l
	move.w	(ram_2722).l,d0
	addq.w	#1,d0
	cmp.b	(ram_DDA3).w,d0
	bne.w	loc_01677A
	clr.w	(ram_D01C).w
	clr.w	(ram_D01A).w
	bsr.w	sub_017334
loc_01677A:
	move.w	(ram_2722).l,d0
	cmp.b	(ram_DDA3).w,d0
	bne.w	loc_01668E
	clr.w	(ram_D01C).w
	clr.w	(ram_D01A).w
	bsr.w	sub_017334
	bra.w	loc_01668E
loc_016798:
	btst	#3,d1
	beq.w	loc_016848
	move.w	(ram_2724).l,d0
	subq.w	#1,d0
	cmp.w	(ram_2722).l,d0
	ble.w	loc_01668E
	move.w	(ram_2724).l,d0
	subq.w	#3,d0
	cmp.w	(ram_2722).l,d0
	blt.w	loc_0167CC
	bset	#2,(ram_2710).l
loc_0167CC:
	move.w	(ram_2716).l,-(sp)
	move.w	(ram_2718).l,(ram_2716).l
	move.w	(ram_271A).l,(ram_2718).l
	move.w	(ram_271C).l,(ram_271A).l
	move.w	(ram_271E).l,(ram_271C).l
	move.w	(sp)+,(ram_271E).l
	addq.w	#1,(ram_2722).l
	bset	#0,(ram_2710).l
	move.w	(ram_2722).l,d0
	subq.w	#1,d0
	cmp.b	(ram_DDA3).w,d0
	bne.w	loc_01682A
	clr.w	(ram_D01C).w
	clr.w	(ram_D01A).w
	bsr.w	sub_017334
loc_01682A:
	move.w	(ram_2722).l,d0
	cmp.b	(ram_DDA3).w,d0
	bne.w	loc_01668E
	clr.w	(ram_D01C).w
	clr.w	(ram_D01A).w
	bsr.w	sub_017334
	bra.w	loc_01668E
loc_016848:
	bra.w	loc_01668E
loc_01684C:
	movea.l	(ram_D028).w,a0
	jsr	(a0)
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01661C
sub_016858:
	btst	#2,(ram_DD9E).w
	bne.w	loc_0168DA
	clr.w	(ram_2724).l
	movea.l	#ram_2726,a0
	movea.l	#dat_017A9C,a1
	move.b	(ram_DDA2).w,d1
	clr.w	d3
	move.b	(a1)+,d3
	clr.w	d4
	bra.w	loc_0168D4
loc_016882:
	clr.w	d2
	move.b	(a1)+,d2
	bra.w	loc_0168CE
loc_01688A:
	cmp.b	(a1),d1
	beq.w	loc_016898
	cmp.b	$1(a1),d1
	bne.w	loc_0168CC
loc_016898:
	addq.w	#1,(ram_2724).l
	move.b	(a1),(a0)+
	move.b	$1(a1),(a0)+
	move.w	d4,(a0)+
	movea.l	#$201982,a3
	movea.l	#$201A2A,a4
	move.w	(ram_2724).l,d0
	subq.w	#1,d0
	add.w	d0,d0
	clr.w	(a0)+
	move.b	$1(a3,d0.w),-$1(a0)
	clr.w	(a0)+
	move.b	$1(a4,d0.w),-$1(a0)
loc_0168CC:
	addq.w	#2,a1
loc_0168CE:
	dbra	d2,loc_01688A
	addq.w	#1,d4
loc_0168D4:
	dbra	d3,loc_016882
	rts
loc_0168DA:
	clr.w	(ram_2724).l
	movea.l	#ram_2726,a0
	movea.l	#$200EE0,a1
	movea.l	#$201982,a3
	movea.l	#$201A2A,a4
	move.b	(ram_DDA2).w,d1
	clr.w	d3
	move.b	(ram_DDA3).w,d3
	clr.w	d4
	bra.w	loc_016942
loc_016908:
	move.w	(a1)+,d0
	btst	#7,d0
	bne.w	loc_016920
	andi.w	#$7F,d0
	move.b	(ram_DDA2).w,(a0)+
	move.b	d0,(a0)+
	bra.w	loc_01692A
loc_016920:
	andi.w	#$7F,d0
	move.b	d0,(a0)+
	move.b	(ram_DDA2).w,(a0)+
loc_01692A:
	move.w	d4,(a0)+
	move.w	(a3)+,d0
	andi.w	#$FF,d0
	move.w	d0,(a0)+
	move.w	(a4)+,d0
	andi.w	#$FF,d0
	move.w	d0,(a0)+
	addq.w	#1,(ram_2724).l
loc_016942:
	dbra	d3,loc_016908
	jsr	(sub_015060).l
	cmpa.l	#$0,a2
	beq.w	loc_016970
	btst	#1,(ram_DD9E).w
	bne.w	loc_016970
	move.b	(a2),(a0)+
	move.b	$1(a2),(a0)+
	move.w	(ram_DD9C).w,(a0)+
	addq.w	#1,(ram_2724).l
loc_016970:
	rts


; ----------------------------------------------------------------------
; called from $01665A
sub_016972:
	move.l	#VBlank_Main,(VBlankVector).l
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B400,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_0169E8:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_0169F0:
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_016A00:
	dc.w	$E123,$4567,$89DE,$EEEF
loc_016A08:
	move.l	#Font_Menu,(FontPtr).l
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_016A22:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_016A2A:
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_2716).l
	addi.w	#$19,d4
	move.w	d4,(ram_2718).l
	addi.w	#$19,d4
	move.w	d4,(ram_271A).l
	addi.w	#$19,d4
	move.w	d4,(ram_271C).l
	addi.w	#$19,d4
	move.w	d4,(ram_271E).l
	addi.w	#$19,d4
	move.w	d4,-(sp)
	movea.l	#dat_017196,a3
	tst.w	(ram_DEA8).w
	beq.w	loc_016A88
	movea.l	#dat_017212,a3
loc_016A88:
	movea.l	#ram_2716,a1
	move.w	(ram_2722).l,d0
	subq.w	#2,d0
	bpl.w	loc_016AA6
	addq.w	#2,a1
	addq.w	#1,d0
	bpl.w	loc_016AA6
	addq.w	#2,a1
	addq.w	#1,d0
loc_016AA6:
	asl.w	#3,d0
	movea.l	#ram_2726,a0
	move.b	$0(a0,d0.w),d7
	cmp.b	(ram_DDA2).w,d7
	bne.w	loc_016ABE
	move.b	$1(a0,d0.w),d7
loc_016ABE:
	cmp.w	#$1A,d7	; general form
	bge.w	loc_016AEE
	ext.w	d7
	asl.w	#2,d7
	movea.l	$0(a3,d7.w),a2
	addq.w	#8,a2
	move.w	(a1),d4
	jsr	(sub_020780).l
	cmpa.l	#ram_271E,a1
	beq.w	loc_016AEE
	asr.w	#3,d0
	addq.w	#2,a1
	addq.w	#1,d0
	cmp.w	#$53,d0	; general form
	ble.s	loc_016AA6
loc_016AEE:
	move.w	(sp)+,d4
	move.w	d4,(ram_2712).l
	addi.w	#$20,d4
	move.w	d4,(ram_2714).l
	addi.w	#$20,d4
	jsr	(Text_PrintCmd).l
inl_016B0A:
	dc.w	loc_016B12-inl_016B0A
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_016B12:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintFont).l
inl_016B26:
	dc.w	loc_016B4A-inl_016B26
	dc.b	$8F,$0C,$19
	dc.b	"{}-MENU OPTIONS"
	dc.b	$8F,$0C,$1A
	dc.b	"[]-CHANGE DAY"
loc_016B4A:
	jsr	(Text_Print).l
inl_016B50:
	dc.w	loc_016B56-inl_016B50
	dc.b	$BF,$01,$04,$00
loc_016B56:
	clr.w	d7
	move.b	(ram_DDA2).w,d7
	moveq	#$2,d5
	bsr.w	sub_016EF4
	jsr	(Text_Print).l
inl_016B68:
	dc.w	loc_016B6E-inl_016B68
	dc.b	$FE,$00,$00,$00
loc_016B6E:
	movea.l	#Art_PlayoffLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$40,d2
	moveq	#$1C,d3
	moveq	#$9,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_016B92:
	dc.w	loc_016B98-inl_016B92
	dc.b	$BF,$13,$16,$00
loc_016B98:
	movea.l	#Art_179434,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$3,d2
	moveq	#$2,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_016BC2:
	dc.w	loc_016BD6-inl_016BC2
	dc.b	$FF,$07,$01
	dc.b	"LEAGUE OPTIONS",0
loc_016BD6:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $016D16
sub_016BDC:
	move.w	(ram_DD9C).w,-(sp)
	tst.w	(ram_2722).l
	beq.w	loc_016BF8
	jsr	(Text_PrintNarrow).l
inl_016BF0:
	dc.w	loc_016BF8-inl_016BF0
	dc.b	$F8,$04,$01,$0D,$14,$5B
loc_016BF8:
	btst	#2,(ram_DD9E).w
	beq.w	loc_016C24
	jsr	(Text_PrintNarrow).l
inl_016C08:
	dc.w	loc_016C10-inl_016C08
	dc.b	$F8,$04,$01,$0E,$14,$00
loc_016C10:
	jsr	(Text_PrintNarrow).l
inl_016C16:
	dc.w	loc_016C20-inl_016C16
	dc.b	"PLAYOFFS"
loc_016C20:
	bra.w	loc_016C44
loc_016C24:
	move.w	(ram_2720).l,(ram_DD9C).w
	jsr	(sub_015212).l
	jsr	(Text_Print).l
inl_016C38:
	dc.w	loc_016C3E-inl_016C38
	dc.b	$BF,$0E,$14,$00
loc_016C3E:
	jsr	(Text_PrintNarrow_Worker).l
loc_016C44:
	move.w	(ram_2722).l,d0
	addq.w	#1,d0
	cmp.w	(ram_2724).l,d0
	bge.w	loc_016C60
	jsr	(Text_PrintNarrow).l
inl_016C5C:
	dc.w	loc_016C60-inl_016C5C
	dc.b	$5D,$00
loc_016C60:
	move.w	(sp)+,(ram_DD9C).w
	rts


; ----------------------------------------------------------------------
; called from $016D1A
sub_016C66:
	clr.w	d0
	move.b	(ram_DDA3).w,d0
	beq.w	loc_016CD2
	subq.w	#1,d0
	cmp.w	(ram_2722).l,d0
	blt.w	loc_016CD2
	move.w	(ram_2722).l,d0
	asl.w	#3,d0
	movea.l	#ram_2726,a0
	movem.l	d0/a0,-(sp)
	move.w	$4(a0,d0.w),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print).l
inl_016CA2:
	dc.w	loc_016CA8-inl_016CA2
	dc.b	$BF,$1F,$14,$00
loc_016CA8:
	jsr	(Text_PrintNarrow_Worker).l
	movem.l	(sp)+,d0/a0
	move.w	$6(a0,d0.w),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print).l
inl_016CC6:
	dc.w	loc_016CCC-inl_016CC6
	dc.b	$BF,$08,$14,$00
loc_016CCC:
	jsr	(Text_PrintNarrow_Worker).l
loc_016CD2:
	rts


; ----------------------------------------------------------------------
; called from $016670, $0166A4
sub_016CD4:
	jsr	(Text_PrintNarrow).l
inl_016CDA:
	dc.w	loc_016CFC-inl_016CDA
	dc.b	$F8,$04,$01,$08,$14
	dc.b	"                           "
loc_016CFC:
	move.w	(ram_2722).l,d0
	asl.w	#3,d0
	movea.l	#ram_2726,a0
	move.w	$2(a0,d0.w),(ram_2720).l
	movem.l	d0/a0,-(sp)
	bsr.w	sub_016BDC
	bsr.w	sub_016C66
	move.w	(FrameCounter).w,d0
loc_016D22:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_016D22
	movem.l	(sp),d0/a0
	clr.w	d7
	move.b	$0(a0,d0.w),d7
	jsr	(Text_Print).l
inl_016D38:
	dc.w	loc_016D3E-inl_016D38
	dc.b	$BF,$17,$16,$00
loc_016D3E:
	move.w	(ram_2712).l,d4
	bsr.w	sub_016EB8
	move.b	$1(a0,d0.w),d7
	jsr	(Text_Print).l
inl_016D52:
	dc.w	loc_016D58-inl_016D52
	dc.b	$BF,$01,$16,$00
loc_016D58:
	move.w	(ram_2714).l,d4
	bsr.w	sub_016EB8
	move.w	(FrameCounter).w,d0
loc_016D66:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_016D66
	movem.l	(sp),d0/a0
	bsr.w	sub_016D7A
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
; called from $016D70
sub_016D7A:
	move.w	#$4,d6
	movea.l	#ram_271E,a2
	move.w	(ram_2722).l,d5
	addq.w	#2,d5
	bset	#0,(TextFlags).w
loc_016D92:
	move.w	(ram_2724).l,d0
	subq.w	#1,d0
	cmp.w	d0,d5
	ble.w	loc_016DA8
	bsr.w	sub_016E84
	bra.w	loc_016E6E
loc_016DA8:
	tst.w	d5
	bpl.w	loc_016DB6
	bsr.w	sub_016E84
	bra.w	loc_016E6E
loc_016DB6:
	move.w	(a2),d4
	jsr	(Text_Print).l
inl_016DBE:
	dc.w	loc_016DC4-inl_016DBE
	dc.b	$BF,$00,$0E,$00
loc_016DC4:
	movea.l	#dat_016E7E,a0
	move.b	$0(a0,d6.w),(ram_B043).w
	move.w	d5,d0
	asl.w	#3,d0
	movea.l	#ram_2726,a0
	move.b	$0(a0,d0.w),d1
	cmp.b	(ram_DDA2).w,d1
	bne.w	loc_016DEA
	move.b	$1(a0,d0.w),d1
loc_016DEA:
	movea.l	#dat_017196,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_016DFE
	movea.l	#dat_017212,a0
loc_016DFE:
	ext.w	d1
	asl.w	#2,d1
	movea.l	$0(a0,d1.w),a0
	bset	#0,(TextFlags).w
	cmp.w	#$4,d6	; general form
	bne.w	loc_016E26
	bclr	#2,(ram_2710).l
	beq.w	loc_016E26
	bclr	#0,(TextFlags).w
loc_016E26:
	tst.w	d6
	bne.w	loc_016E3E
	bclr	#1,(ram_2710).l
	beq.w	loc_016E3E
	bclr	#0,(TextFlags).w
loc_016E3E:
	btst	#2,(ram_C346).w
	beq.w	loc_016E4E
	bclr	#0,(TextFlags).w
loc_016E4E:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$5,d2
	moveq	#$5,d3
	moveq	#$4,d5
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a6
loc_016E6E:
	subq.l	#2,a2
	subq.w	#1,d5
	dbra	d6,loc_016D92
	bclr	#0,(TextFlags).w
	rts
dat_016E7E:
	dc.b	$02,$0A,$12,$1A,$22,$FF


; ----------------------------------------------------------------------
; called from $016DA0, $016DAE
sub_016E84:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_016E8E:
	dc.w	loc_016E94-inl_016E8E
	dc.b	$BF,$00,$0E,$00
loc_016E94:
	movea.l	#dat_016E7E,a0
	move.b	$0(a0,d6.w),(ram_B043).w
	moveq	#$5,d0
	moveq	#$5,d1
	move.w	#$7FF,d2
	ori.w	#$8000,d2
	jsr	(Text_FillRect).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00E4B0, $00E4CA, $016D44, $016D5E, $1D28B6, $1D28D0, $1D581C, $1DE024 (+5 more)
sub_016EB8:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#TeamArtTable,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_016ED0
	movea.l	#dat_017022,a0
loc_016ED0:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	moveq	#$2,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $016490, $0164B6, $0164DC, $016B5E, $1D27DA, $1D27FE, $1D34DE, $1DDD0C (+5 more)
sub_016EF4:
	movem.l	d0-d3/d5-d7/a0-a6,-(sp)
	movea.l	#dat_01709E,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_016F0C
	movea.l	#dat_01711A,a0
loc_016F0C:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	tst.w	d5
	bne.w	loc_016F88
	movea.l	a0,a1
	adda.l	(a1),a1
	adda.w	#$20,a1
	movea.l	#ram_BD80,a2
	move.w	#$7,d0
loc_016F2A:
	move.l	(a1)+,(a2)+
	dbra	d0,loc_016F2A
	move.l	a0,-(sp)
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	#$8,d3
	move.w	d4,-(sp)
	jsr	(TileMap_Draw).l
	move.w	(sp)+,d4
	movea.l	(sp)+,a0
	jsr	(Text_PrintCmd).l
inl_016F56:
	dc.w	loc_016F5A-inl_016F56
	dc.b	$FE,$00
loc_016F5A:
	addq.w	#8,(TextY).w
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	move.w	#$8,d1
	move.w	(a1),d2
	move.w	#$2,d3
	bset	#0,(TextFlags).w
	jsr	(TileMap_Draw).l
	bclr	#0,(TextFlags).w
	bra.w	loc_016FA0
loc_016F88:
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	jsr	(TileMap_Draw).l
loc_016FA0:
	movem.l	(sp)+,d0-d3/d5-d7/a0-a6
	rts

; 6 groups of 31 pointers (team name banner, logo, icon; two team orderings each)
TeamArtTable:
	dc.l	Art_TeamName_Anaheim
	dc.l	Art_TeamName_Boston
	dc.l	Art_TeamName_Buffalo
	dc.l	Art_TeamName_Calgary
	dc.l	Art_TeamName_Carolina
	dc.l	Art_TeamName_Chicago
	dc.l	Art_TeamName_Colorado
	dc.l	Art_TeamName_Dallas
	dc.l	Art_TeamName_Detroit
	dc.l	Art_TeamName_Edmonton
	dc.l	Art_TeamName_Florida
	dc.l	Art_TeamName_LosAngeles
	dc.l	Art_TeamName_Montreal
	dc.l	Art_TeamName_NewJersey
	dc.l	Art_TeamName_NewYorkIslanders
	dc.l	Art_TeamName_NewYorkRangers
	dc.l	Art_TeamName_Ottawa
	dc.l	Art_TeamName_Philadelphia
	dc.l	Art_TeamName_Phoenix
	dc.l	Art_TeamName_Pittsburgh
	dc.l	Art_TeamName_SanJose
	dc.l	Art_TeamName_StLouis
	dc.l	Art_TeamName_TampaBay
	dc.l	Art_TeamName_Toronto
	dc.l	Art_TeamName_Vancouver
	dc.l	Art_TeamName_Washington
	dc.l	Art_TeamName_EaSports
	dc.l	Art_TeamName_006AC8
	dc.l	Art_TeamName_TeamCanada
	dc.l	Art_TeamName_TeamUsa
	dc.l	Art_TeamName_TeamEurope

dat_017022:
	dc.l	Art_TeamName_Anaheim
	dc.l	Art_TeamName_Boston
	dc.l	Art_TeamName_Buffalo
	dc.l	Art_TeamName_Calgary
	dc.l	Art_TeamName_Carolina
	dc.l	Art_TeamName_Chicago
	dc.l	Art_TeamName_Colorado
	dc.l	Art_TeamName_Dallas
	dc.l	Art_TeamName_Detroit
	dc.l	Art_TeamName_Edmonton
	dc.l	Art_TeamName_Florida
	dc.l	Art_TeamName_LosAngeles
	dc.l	Art_TeamName_Montreal
	dc.l	Art_TeamName_NewJersey
	dc.l	Art_TeamName_NewYorkIslanders
	dc.l	Art_TeamName_NewYorkRangers
	dc.l	Art_TeamName_Ottawa
	dc.l	Art_TeamName_Philadelphia
	dc.l	Art_TeamName_Phoenix
	dc.l	Art_TeamName_Pittsburgh
	dc.l	Art_TeamName_SanJose
	dc.l	Art_TeamName_StLouis
	dc.l	Art_TeamName_TampaBay
	dc.l	Art_TeamName_Toronto
	dc.l	Art_TeamName_Vancouver
	dc.l	Art_TeamName_Washington
	dc.l	Art_TeamNameAlt_EaSports
	dc.l	Art_TeamNameAlt_006AC8
	dc.l	Art_TeamName_TeamCanada
	dc.l	Art_TeamName_TeamUsa
	dc.l	Art_TeamName_TeamEurope

dat_01709E:
	dc.l	Art_TeamLogo_Anaheim
	dc.l	Art_TeamLogo_Boston
	dc.l	Art_TeamLogo_Buffalo
	dc.l	Art_TeamLogo_Calgary
	dc.l	Art_TeamLogo_Carolina
	dc.l	Art_TeamLogo_Chicago
	dc.l	Art_TeamLogo_Colorado
	dc.l	Art_TeamLogo_Dallas
	dc.l	Art_TeamLogo_Detroit
	dc.l	Art_TeamLogo_Edmonton
	dc.l	Art_TeamLogo_Florida
	dc.l	Art_TeamLogo_LosAngeles
	dc.l	Art_TeamLogo_Montreal
	dc.l	Art_TeamLogo_NewJersey
	dc.l	Art_TeamLogo_NewYorkIslanders
	dc.l	Art_TeamLogo_NewYorkRangers
	dc.l	Art_TeamLogo_Ottawa
	dc.l	Art_TeamLogo_Philadelphia
	dc.l	Art_TeamLogo_Phoenix
	dc.l	Art_TeamLogo_Pittsburgh
	dc.l	Art_TeamLogo_SanJose
	dc.l	Art_TeamLogo_StLouis
	dc.l	Art_TeamLogo_TampaBay
	dc.l	Art_TeamLogo_Toronto
	dc.l	Art_TeamLogo_Vancouver
	dc.l	Art_TeamLogo_Washington
	dc.l	Art_TeamLogo_EaSports
	dc.l	Art_TeamLogo_006AC8
	dc.l	Art_TeamLogo_TeamCanada
	dc.l	Art_TeamLogo_TeamUsa
	dc.l	Art_TeamLogo_TeamEurope

dat_01711A:
	dc.l	Art_TeamLogo_Anaheim
	dc.l	Art_TeamLogo_Boston
	dc.l	Art_TeamLogo_Buffalo
	dc.l	Art_TeamLogo_Calgary
	dc.l	Art_TeamLogo_Carolina
	dc.l	Art_TeamLogo_Chicago
	dc.l	Art_TeamLogo_Colorado
	dc.l	Art_TeamLogo_Dallas
	dc.l	Art_TeamLogo_Detroit
	dc.l	Art_TeamLogo_Edmonton
	dc.l	Art_TeamLogo_Florida
	dc.l	Art_TeamLogo_LosAngeles
	dc.l	Art_TeamLogo_Montreal
	dc.l	Art_TeamLogo_NewJersey
	dc.l	Art_TeamLogo_NewYorkIslanders
	dc.l	Art_TeamLogo_NewYorkRangers
	dc.l	Art_TeamLogo_Ottawa
	dc.l	Art_TeamLogo_Philadelphia
	dc.l	Art_TeamLogo_Phoenix
	dc.l	Art_TeamLogo_Pittsburgh
	dc.l	Art_TeamLogo_SanJose
	dc.l	Art_TeamLogo_StLouis
	dc.l	Art_TeamLogo_TampaBay
	dc.l	Art_TeamLogo_Toronto
	dc.l	Art_TeamLogo_Vancouver
	dc.l	Art_TeamLogo_Washington
	dc.l	Art_TeamLogoAlt_EaSports
	dc.l	Art_TeamLogoAlt_006AC8
	dc.l	Art_TeamLogo_TeamCanada
	dc.l	Art_TeamLogo_TeamUsa
	dc.l	Art_TeamLogo_TeamEurope

dat_017196:
	dc.l	Art_TeamIcon_Anaheim
	dc.l	Art_TeamIcon_Boston
	dc.l	Art_TeamIcon_Buffalo
	dc.l	Art_TeamIcon_Calgary
	dc.l	Art_TeamIcon_Carolina
	dc.l	Art_TeamIcon_Chicago
	dc.l	Art_TeamIcon_Colorado
	dc.l	Art_TeamIcon_Dallas
	dc.l	Art_TeamIcon_Detroit
	dc.l	Art_TeamIcon_Edmonton
	dc.l	Art_TeamIcon_Florida
	dc.l	Art_TeamIcon_LosAngeles
	dc.l	Art_TeamIcon_Montreal
	dc.l	Art_TeamIcon_NewJersey
	dc.l	Art_TeamIcon_NewYorkIslanders
	dc.l	Art_TeamIcon_NewYorkRangers
	dc.l	Art_TeamIcon_Ottawa
	dc.l	Art_TeamIcon_Philadelphia
	dc.l	Art_TeamIcon_Phoenix
	dc.l	Art_TeamIcon_Pittsburgh
	dc.l	Art_TeamIcon_SanJose
	dc.l	Art_TeamIcon_StLouis
	dc.l	Art_TeamIcon_TampaBay
	dc.l	Art_TeamIcon_Toronto
	dc.l	Art_TeamIcon_Vancouver
	dc.l	Art_TeamIcon_Washington
	dc.l	Art_TeamIcon_EaSports
	dc.l	Art_TeamIcon_006AC8
	dc.l	Art_TeamIcon_TeamCanada
	dc.l	Art_TeamIcon_TeamUsa
	dc.l	Art_TeamIcon_TeamEurope

dat_017212:
	dc.l	Art_TeamIcon_Anaheim
	dc.l	Art_TeamIcon_Boston
	dc.l	Art_TeamIcon_Buffalo
	dc.l	Art_TeamIcon_Calgary
	dc.l	Art_TeamIcon_Carolina
	dc.l	Art_TeamIcon_Chicago
	dc.l	Art_TeamIcon_Colorado
	dc.l	Art_TeamIcon_Dallas
	dc.l	Art_TeamIcon_Detroit
	dc.l	Art_TeamIcon_Edmonton
	dc.l	Art_TeamIcon_Florida
	dc.l	Art_TeamIcon_LosAngeles
	dc.l	Art_TeamIcon_Montreal
	dc.l	Art_TeamIcon_NewJersey
	dc.l	Art_TeamIcon_NewYorkIslanders
	dc.l	Art_TeamIcon_NewYorkRangers
	dc.l	Art_TeamIcon_Ottawa
	dc.l	Art_TeamIcon_Philadelphia
	dc.l	Art_TeamIcon_Phoenix
	dc.l	Art_TeamIcon_Pittsburgh
	dc.l	Art_TeamIcon_SanJose
	dc.l	Art_TeamIcon_StLouis
	dc.l	Art_TeamIcon_TampaBay
	dc.l	Art_TeamIcon_Toronto
	dc.l	Art_TeamIcon_Vancouver
	dc.l	Art_TeamIcon_Washington
	dc.l	Art_TeamIconAlt_EaSports
	dc.l	Art_TeamIconAlt_006AC8
	dc.l	Art_TeamIcon_TeamCanada
	dc.l	Art_TeamIcon_TeamUsa
	dc.l	Art_TeamIcon_TeamEurope


; ----------------------------------------------------------------------
; DMA transfers, palette fade, frame counter, sound update
; called from $0156F2, $015F38, $1D26B6, $1D2B18, $1D56AC, $1D6118, $1DB6FE, $1E0950 (+5 more)
VBlank_Main:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_0172B2
	bclr	#0,(VideoFlags).w
	beq.w	loc_0172AC
	jsr	(VBlank_DMATransfers).l
loc_0172AC:
	jsr	(Palette_FadeStep).l
loc_0172B2:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $016650
sub_0172C2:
	move.l	#dat_01767E,(ram_D01E).l
	tst.w	(ram_DD9C).w
	bne.w	loc_0172DE
	move.l	#dat_0175BA,(ram_D01E).l
loc_0172DE:
	btst	#0,(ram_DD9E).w
	beq.w	loc_01730A
	btst	#2,(ram_DD9E).w
	beq.w	loc_017300
	move.l	#dat_017756,(ram_D01E).l
	bra.w	loc_01730A
loc_017300:
	move.l	#dat_01781A,(ram_D01E).l
loc_01730A:
	btst	#1,(ram_DD9E).w
	beq.w	loc_01731E
	move.l	#dat_0173E6,(ram_D01E).l
loc_01731E:
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$17,(ram_B03E).w
	move.w	#$7,(ram_B040).w
	rts


; ----------------------------------------------------------------------
; called from $016684, $0166E0, $0166F2, $016776, $016790, $016826, $016840
sub_017334:
	move.w	#$6,(ram_D026).w
	move.l	#dat_01767E,(ram_D01E).l
	tst.w	(ram_DD9C).w
	bne.w	loc_017356
	move.l	#dat_0175BA,(ram_D01E).l
loc_017356:
	btst	#2,(ram_DD9E).w
	beq.w	loc_017382
	move.l	#dat_017756,(ram_D01E).l
	btst	#1,(ram_DD9E).w
	beq.w	loc_017382
	move.l	#dat_0173E6,(ram_D01E).l
	bra.w	loc_0173DE
loc_017382:
	move.w	(ram_2722).l,d0
	cmp.b	(ram_DDA3).w,d0
	beq.w	loc_0173C0
	bgt.w	loc_0173B6
	move.l	#dat_0173E6,(ram_D01E).l
	btst	#2,(ram_DD9E).w
	beq.w	loc_0173C0
	move.l	#dat_017482,(ram_D01E).l
	bra.w	loc_0173C0
loc_0173B6:
	move.l	#dat_01750A,(ram_D01E).l
loc_0173C0:
	btst	#0,(ram_DD9E).w
	beq.w	loc_0173DE
	btst	#2,(ram_DD9E).w
	bne.w	loc_0173DE
	move.l	#dat_01781A,(ram_D01E).l
loc_0173DE:
	jsr	(sub_01890C).l
	rts
dat_0173E6:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"TRANSACTIONS  ",0
	dc.b	$01,$7A,$8E,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_017482:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_01750A:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"SIMULATE GAME ",0
	dc.b	$01,$79,$42,$00,$10
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"TRANSACTIONS  ",0
	dc.b	$01,$7A,$8E,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_0175BA:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"PLAY GAME     ",0
	dc.b	$01,$79,$28,$00,$10
	dc.b	"SIMULATE GAME ",0
	dc.b	$01,$79,$42,$00,$10
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"TRANSACTIONS  ",0
	dc.b	$01,$7A,$8E,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_01767E:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"PLAY GAME     ",0
	dc.b	$01,$79,$28,$00,$10
	dc.b	"SIMULATE GAME ",0
	dc.b	$01,$79,$42,$00,$10
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"TRANSACTIONS  ",0
	dc.b	$01,$7A,$8E,$00,$10
	dc.b	"END SEASON NOW",0
	dc.b	$01,$7A,$10,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_017756:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010
	dc.b	"PLAY GAME     ",0
	dc.b	$01,$79,$28,$00,$10
	dc.b	"SIMULATE GAME ",0
	dc.b	$01,$79,$42,$00,$10
	dc.b	"NHL STANDINGS ",0
	dc.b	$01,$7A,$46,$00,$10
	dc.b	"TEAM ROSTER   ",0
	dc.b	$01,$7A,$52,$00,$10
	dc.b	"PLAYER STATS  ",0
	dc.b	$01,$7A,$82,$00,$10
	dc.b	"LEAGUE LEADERS",0
	dc.b	$01,$7A,$6A,$00,$10
	dc.b	"GAME OPTIONS  ",0
	dc.b	$01,$7A,$5E,$00,$10
	dc.b	"PLAYOFF TREE  ",0
	dc.b	$01,$7A,$76,$00,$10
	dc.b	"EXIT SEASON   ",0
	dc.b	$01,$7A,$02,$00,$04,$FF,$00
dat_01781A:
	dc.w	$0006,$FE07,$F900,$0006,$FE07,$F901,$0010,$4245
	dc.w	$4749,$4E20,$504C,$4159,$4F46,$4653,$0001,$7898
	dc.w	$0010,$4E48,$4C20,$5354,$414E,$4449,$4E47,$5320
	dc.w	$0001,$7A46,$0010,$504C,$4159,$4552,$2053,$5441
	dc.w	$5453,$2020,$0001,$7A82,$0010,$4C45,$4147,$5545
	dc.w	$204C,$4541,$4445,$5253,$0001,$7A6A,$0010,$4558
	dc.w	$4954,$2053,$4541,$534F,$4E20,$2020,$0001,$7A02
	dc.w	$0004,$FF00,$21FC,$0001,$6614,$DDD0,$4E75,$4EB9
	dc.w	$0002,$0A7E,$0008,$FF01,$FD15,$FC07,$303C,$0010
	dc.w	$323C,$0006,$343C,$07FF,$0042,$8000,$4EB9,$0002
	dc.w	$09C6,$4EB9,$0002,$0A7E,$0066,$FE07,$F900,$FD15
	dc.w	$FC07,$2020,$2020,$2020,$2020,$2020,$2020,$FD15
	dc.w	$FA01,$2020,$504C,$4541,$5345,$2057,$4149,$5420
	dc.w	$2020,$FD15,$FA02,$3C3C,$3C3C,$3C3C,$4E4F,$5445
	dc.w	$3C3C,$3C3C,$3C3C,$FD15,$FA01,$5245,$5345,$5420
	dc.w	$5749,$4C4C,$2043,$4155,$5345,$FD15,$FA01,$4441
	dc.w	$5441,$2043,$4F52,$5255,$5054,$494F,$4E20,$4278
	dc.w	$DDD4,$4EB9,$0001,$4FEE,$4EB9,$0001,$5008,$21FC
	dc.w	$0000,$0772,$DDD0,$4E75,$3039,$FFFF,$2722,$E740
	dc.w	$207C,$FFFF,$2726,$3030,$0002,$9078,$DD9C,$5240
	dc.w	$31C0,$DDD4,$4EB9,$0002,$0A7E,$0008,$FF01,$FD15
	dc.w	$FC07,$303C,$0010,$323C,$0006,$343C,$07FF,$0042
	dc.w	$8000,$4EB9,$0002,$09C6,$4EB9,$0002,$0A7E,$006A
	dc.w	$FE07,$F900,$FD15,$FC07,$4741,$4D45,$2053,$494D
	dc.w	$554C,$4154,$494F,$4E20,$FD15,$FA01,$2020,$504C
	dc.w	$4541,$5345,$2057,$4149,$5420,$2020,$FD15,$FA02
	dc.w	$3C3C,$3C3C,$3C3C,$4E4F,$5445,$3C3C,$3C3C,$3C3C
	dc.w	$FD15,$FA01,$5245,$5345,$5420,$5749,$4C4C,$2043
	dc.w	$4155,$5345,$FD15,$FA01,$4441,$5441,$2043,$4F52
	dc.w	$5255,$5054,$494F,$4E20,$08B8,$0005,$C358,$21FC
	dc.w	$0000,$0772,$DDD0,$4E75,$08B8,$0007,$C352,$4EF9
	dc.w	$0002,$6D3E,$4E75


; ----------------------------------------------------------------------
sub_017A10:
	bset	#0,(ram_DD9E).w
	bset	#0,(ram_DD9E).w
	bclr	#1,(ram_DD9E).w
	bclr	#2,(ram_DD9E).w
	bsr.w	sub_014FCE
	clr.w	(ram_DDD4).w
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	move.l	#NullEntry,(ram_DDD0).w
	rts


; ----------------------------------------------------------------------
sub_017A46:
	move.l	#sub_1D3D7E,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A52:
	move.l	#sub_1DD778,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A5E:
	move.l	#sub_1D437C,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A6A:
	move.l	#sub_1D4AA8,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A76:
	move.l	#sub_1E1F76,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A82:
	move.l	#loc_1D535A,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
sub_017A8E:
	move.l	#sub_1D5E7E,(ram_DDD0).l
	rts


; ----------------------------------------------------------------------
; called from $026CB2
sub_017A9A:
	rts
dat_017A9C:
	incbin	"data/bin/data_017A9C.bin"	; 2322 bytes


; ----------------------------------------------------------------------
; called from $026FDE
sub_0183AE:
	rts


; ----------------------------------------------------------------------
; called from $014C16
sub_0183B0:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_BF52).w
	jsr	(sub_027B42).l
	movea.l	#ram_CF50,a0
	moveq	#$10,d3
	mulu.w	d1,d3
	adda.w	d3,a0
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_01847C
loc_0183D4:
	cmpi.w	#$4,$4(a0)
	beq.w	loc_018410
	cmpi.w	#$4,$6(a0)
	beq.w	loc_018410
	st	(ram_BF52).w
	clr.w	d3
	btst	#0,$E(a0)
	beq.w	loc_0183FC
	eori.w	#$2,d3
loc_0183FC:
	move.w	$A(a0),d0
	sub.w	$C(a0),d0
	bpl.w	loc_01840C
	eori.w	#$2,d3
loc_01840C:
	addq.w	#1,$4(a0,d3.w)
loc_018410:
	suba.w	#$10,a0
	dbra	d1,loc_0183D4
	addq.w	#1,(ram_CFD4).w
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_018432
	tst.w	(ram_BF52).w
	beq.w	loc_018432
	bra.w	loc_0184B4
loc_018432:
	clr.w	(ram_CFD4).w
	jsr	(sub_027B42).l
	movea.w	#$CF50,a0
	moveq	#$10,d3
	mulu.w	d1,d3
	adda.w	d3,a0
	clr.w	d3
loc_018448:
	cmpi.w	#$4,$4(a0)
	beq.w	loc_018454
	bset	d1,d3
loc_018454:
	clr.w	$4(a0)
	clr.w	$6(a0)
	suba.w	#$10,a0
	dbra	d1,loc_018448
	moveq	#$1,d1
	asl.w	d2,d1
	subq.w	#1,d1
	and.w	d1,(ram_CFDC).w
	asl.w	d2,d3
	or.w	d3,(ram_CFDC).w
	addq.w	#1,(ram_CFD6).w
	bra.w	loc_0184B4
loc_01847C:
	clr.w	d3
loc_01847E:
	move.w	$A(a0),d0
	cmp.w	$C(a0),d0
	bhi.w	loc_01848C
	bset	d1,d3
loc_01848C:
	btst	#0,$E(a0)
	beq.w	loc_018498
	bchg	d1,d3
loc_018498:
	suba.w	#$10,a0
	dbra	d1,loc_01847E
	moveq	#$1,d1
	asl.w	d2,d1
	subq.w	#1,d1
	and.w	d1,(ram_CFDC).w
	asl.w	d2,d3
	or.w	d3,(ram_CFDC).w
	addq.w	#1,(ram_CFD6).w
loc_0184B4:
	cmpi.w	#$4,(ram_CFD6).w
	bne.w	loc_0184FE
	bset	#1,(ram_DD9E).w
	movem.l	d0/a0/a1,-(sp)
	movea.l	#ram_DD16,a0
	lea	$2(a0),a1
	move.b	$2(a1),d0
	cmp.b	$3(a1),d0
	bgt.w	loc_0184E0
	addq.w	#1,a1
loc_0184E0:
	move.b	(a1),d0
	bclr	#3,(ram_DD9E).w
	cmp.b	(ram_DDA2).w,d0
	bne.w	loc_0184F6
	bset	#3,(ram_DD9E).w
loc_0184F6:
	movem.l	(sp)+,d0/a0/a1
	bra.w	loc_018504
loc_0184FE:
	jsr	(sub_027354).l
loc_018504:
	movea.w	#$D2B4,a3
	jsr	(sub_027A4A).l
	jsr	(sub_027A10).l
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	jsr	(sub_014D76).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $02728C
sub_018534:
	bset	#6,(SysFlags).w
	bset	#0,(ram_C356).w
	bsr.w	sub_01856C
	bclr	#0,(ram_C356).w
	btst	#1,(ram_C356).w
	bsr.w	sub_0187AE
	bsr.w	sub_01856C
	jsr	(sub_027354).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	rts


; ----------------------------------------------------------------------
; called from $018540, $018554
sub_01856C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$C,d0
	movea.l	#SaveDataMirror,a0
	movea.l	#dat_018794,a1
	bsr.w	sub_01878C
	move.w	#$C,d0
	movea.l	#ram_0014,a0
	movea.l	#dat_0187A1,a1
	bsr.w	sub_01878C
	movea.l	#ram_0032,a0
	jsr	(sub_015176).l
	bsr.w	sub_018740
	move.w	#$D,(ram_00B4).l
	movea.l	#SaveDataMirror,a0
	bsr.w	sub_0186C4
	move.w	#$D,(ram_00B4).l
	movea.l	#ram_0014,a0
	bsr.w	sub_0186C4
	movea.l	#$2000B2,a0
	btst	#0,(ram_C356).w
	beq.w	loc_0185E2
	movea.l	#ram_00B6,a0
loc_0185E2:
	movea.l	#SaveDataMirror,a1
	bsr.w	sub_018642
	adda.l	#$10,a0
	movea.l	#ram_0014,a1
	bsr.w	sub_018642
	btst	#0,(ram_C356).w
	beq.w	loc_018632
	bset	#1,(ram_C356).w
	movea.l	#ram_00B6,a0
	move.b	(ram_DDA2).w,d1
	move.w	#$F,d0
loc_01861A:
	cmp.b	$1(a0),d1
	bne.w	loc_018628
	bclr	#1,(ram_C356).w
loc_018628:
	tst.w	(a0)+
	dbra	d0,loc_01861A
	bra.w	loc_01863C
loc_018632:
	bsr.w	sub_0188DE
	jsr	(SRAM_UpdateChecksum).l
loc_01863C:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0185E8, $0185F8
sub_018642:
	movea.l	#dat_0186AA,a2
	clr.w	d0
	move.b	(a1)+,d0
	move.b	d0,$3(a0)
	move.b	$0(a2,d0.w),d1
	clr.w	d2
loc_018656:
	move.b	$0(a1,d2.w),d0
	cmp.b	$0(a2,d0.w),d1
	bne.w	loc_018666
	addq.w	#1,d2
	bra.s	loc_018656
loc_018666:
	move.b	d0,$F(a0)
	move.b	d0,d1
loc_01866C:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_01866C
	move.b	d0,$B(a0)
loc_018676:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_018676
	move.b	d0,$7(a0)
loc_018680:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_018680
	move.b	d0,$5(a0)
loc_01868A:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_01868A
	move.b	d0,$9(a0)
loc_018694:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_018694
	move.b	d0,$D(a0)
loc_01869E:
	move.b	(a1)+,d0
	cmp.b	d0,d1
	beq.s	loc_01869E
	move.b	d0,$1(a0)
	rts
dat_0186AA:
	dc.w	$0002,$0200,$0100,$0101,$0003,$0200,$0203,$0303
	dc.w	$0203,$0102,$0001,$0301,$0003


; ----------------------------------------------------------------------
; called from $0185B6, $0185C8
sub_0186C4:
	movea.l	#ram_0080,a1
	movea.l	#ram_009A,a2
	move.w	d1,-(sp)
loc_0186D2:
	bclr	#6,(TextFlags).w
	clr.w	d7
loc_0186DA:
	clr.w	d6
	move.b	$0(a0,d7.w),d6
	clr.w	d0
	move.b	$0(a1,d6.w),d0
	move.b	$1(a0,d7.w),d6
	clr.w	d1
	move.b	$0(a1,d6.w),d1
	cmp.w	d1,d0
	bgt.w	loc_018724
	blt.w	loc_01870E
	move.b	$0(a0,d7.w),d6
	move.b	$0(a2,d6.w),d0
	move.b	$1(a0,d7.w),d6
	cmp.b	$0(a2,d6.w),d0
	bge.w	loc_018724
loc_01870E:
	bset	#6,(TextFlags).w
	move.b	$0(a0,d7.w),d5
	move.b	$1(a0,d7.w),d4
	move.b	d5,$1(a0,d7.w)
	move.b	d4,$0(a0,d7.w)
loc_018724:
	addq.w	#2,d7
	cmp.w	(ram_00B4).l,d7
	bge.w	loc_018734
	subq.w	#1,d7
	bra.s	loc_0186DA
loc_018734:
	btst	#6,(TextFlags).w
	bne.s	loc_0186D2
	move.w	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $0185A4
sub_018740:
	move.w	#$1A,d0
	movea.l	#ram_0032,a1
	movea.l	#ram_0080,a2
	movea.l	#ram_009A,a3
	clr.w	d2
	move.w	d1,-(sp)
	bra.w	loc_018784
loc_01875E:
	move.w	d2,d5
	mulu.w	#$3,d5
	clr.w	d3
	move.b	$0(a1,d5.w),d3
	add.w	d3,d3
	clr.w	d1
	move.b	$1(a1,d5.w),d1
	add.w	d1,d3
	move.b	d3,$0(a2,d2.w)
	clr.w	d3
	move.b	$0(a1,d5.w),d3
	move.b	d3,$0(a3,d2.w)
	addq.w	#1,d2
loc_018784:
	dbra	d0,loc_01875E
	move.w	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $018580, $018594, $01878E
sub_01878C:
	move.b	(a1)+,(a0)+
	dbra	d0,sub_01878C
	rts
dat_018794:
	dc.b	$00,$03,$09,$0B,$14,$18,$06,$05,$07,$08,$15,$17,$12
dat_0187A1:
	dc.b	$01,$02,$04,$0C,$10,$13,$0A,$0D,$0E,$0F,$11,$16,$19


; ----------------------------------------------------------------------
; called from $018550
sub_0187AE:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#6,(SysFlags).w
	move.b	(ram_DD9F).w,-(sp)
	move.b	(ram_DDA0).w,-(sp)
	move.b	(ram_DDA1).w,-(sp)
	move.b	(ram_DDA2).w,-(sp)
	movea.l	#$200082,a0
	movea.l	#$2000D2,a1
	move.w	#$E,d0
	subq.w	#1,d0
loc_0187DA:
	move.w	(a0)+,(a1)+
	dbra	d0,loc_0187DA
	movea.l	#$200082,a0
	clr.l	(a0)
	jsr	(sub_014FEE).l
	bset	#2,(ram_DD9E).w
	move.b	(sp)+,(ram_DDA2).w
	move.b	(sp)+,(ram_DDA1).w
	move.b	(sp)+,(ram_DDA0).w
	move.b	(sp)+,(ram_DD9F).w
	clr.b	(ram_DDA3).w
	jsr	(sub_014FCE).l
	move.l	#$CC1,d0
	move.w	#$54,d1
	jsr	(sub_029D2A).l
	move.l	#$D15,d0
	move.w	#$54,d1
	jsr	(sub_029D2A).l
	move.l	#$D69,d0
	move.w	#$15,d1
	jsr	(sub_029D2A).l
	move.l	#$D7E,d0
	move.w	#$19,d1
	jsr	(sub_029D2A).l
	move.l	#$8B,d0
	move.l	#$6FA,d1
	jsr	(sub_029D2A).l
	jsr	(sub_1D9EDA).l
	moveq	#$4F,d0
	moveq	#$A,d1
	jsr	(sub_029D2A).l
	move.w	#$1,(ram_D270).w
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_018888:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#$200082,a0
	movea.l	#$2000D2,a1
	move.w	#$E,d0
	subq.w	#1,d0
loc_01889E:
	move.w	(a1)+,(a0)+
	dbra	d0,loc_01889E
	jsr	(sub_014FEE).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0149E0, $1D5A3C, $1D5B3E
sub_0188B6:
	move.l	a0,-(sp)
	movea.l	#$2000E2,a0
	add.w	d7,d7
	move.w	$0(a0,d7.w),d7
	ext.w	d7
	movea.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $1D4E7A, $1D4EF6, $1D53A6, $1D5816, $1D59F6, $1D5D08, $1D5D34
sub_0188CA:
	move.l	a0,-(sp)
	movea.l	#$2000B2,a0
	add.w	d7,d7
	move.w	$0(a0,d7.w),d7
	ext.w	d7
	movea.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $018632
sub_0188DE:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#$2000B2,a0
	movea.l	#$2000E2,a1
	move.w	#$F,d1
loc_0188F2:
	move.w	d1,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d2
	ext.w	d2
	add.w	d2,d2
	move.b	d1,$1(a1,d2.w)
	dbra	d1,loc_0188F2
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0173DE
sub_01890C:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	(ram_D01E).w,a3
	movea.l	a3,a4
	adda.w	(a4),a4
	clr.w	d7
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
loc_018922:
	tst.w	$2(a0)
	bmi.w	loc_018932
	addq.w	#1,d7
	adda.w	(a0),a0
	addq.w	#4,a0
	bra.s	loc_018922
loc_018932:
	move.w	(ram_D01A).w,d0
	bpl.w	loc_018940
	clr.w	(ram_D01A).w
	clr.w	d0
loc_018940:
	cmp.w	d7,d0
	blt.w	loc_01894E
	move.w	d7,d0
	subq.w	#1,d0
	move.w	d0,(ram_D01A).w
loc_01894E:
	move.w	(ram_D01C).w,d1
	add.w	(ram_D026).w,d1
	cmp.w	(ram_D01A).w,d1
	bgt.w	loc_018964
	addq.w	#1,(ram_D01C).w
	bra.s	loc_01894E
loc_018964:
	move.w	(ram_D01C).w,d1
	cmp.w	(ram_D01A).w,d1
	ble.w	loc_018976
	subq.w	#1,(ram_D01C).w
	bra.s	loc_018964
loc_018976:
	move.w	(ram_D01C).w,d0
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
	move.w	(ram_D01C).w,d0
	bra.w	loc_01898E
loc_01898A:
	adda.w	(a0),a0
	addq.w	#4,a0
loc_01898E:
	dbra	d0,loc_01898A
	move.w	(ram_B03E).w,(TextX).w
	move.w	(ram_B040).w,(TextY).w
	move.w	(ram_D026).w,d0
	cmp.w	d7,d0
	ble.w	loc_0189AA
	move.w	d7,d0
loc_0189AA:
	clr.w	d1
	bra.w	loc_0189EA
loc_0189B0:
	move.w	d1,d2
	add.w	(ram_D01C).w,d2
	movea.l	a3,a1
	cmp.w	(ram_D01A).w,d2
	bne.w	loc_0189CC
	movea.l	a4,a1
	move.l	a0,-(sp)
	adda.w	(a0),a0
	move.l	(a0),(ram_D028).w
	movea.l	(sp)+,a0
loc_0189CC:
	jsr	(Text_PrintCmd_Worker).l
	movea.l	a0,a1
	jsr	(Text_PrintCmd_Worker).l
	move.w	(ram_B03E).w,(TextX).w
	addq.w	#1,(TextY).w
	adda.w	(a0),a0
	addq.w	#4,a0
	addq.w	#1,d1
loc_0189EA:
	dbra	d0,loc_0189B0
	move.w	(ram_B03E).w,d0
	subq.w	#2,d0
	move.w	d0,(TextX).w
	move.w	(ram_B040).w,(TextY).w
	movea.l	#dat_018A56,a1
	tst.w	(ram_D01C).w
	beq.w	loc_018A12
	movea.l	#dat_018A5C,a1
loc_018A12:
	jsr	(Text_PrintCmd_Worker).l
	move.w	(ram_B03E).w,d0
	subq.w	#2,d0
	move.w	d0,(TextX).w
	move.w	(ram_B040).w,d0
	add.w	(ram_D026).w,d0
	subq.w	#1,d0
	move.w	d0,(TextY).w
	movea.l	#dat_018A56,a1
	move.w	(ram_D01C).w,d0
	add.w	(ram_D026).w,d0
	cmp.w	d7,d0
	bge.w	loc_018A4A
	movea.l	#dat_018A62,a1
loc_018A4A:
	jsr	(Text_PrintCmd_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_018A56:
	dc.b	$00,$06,$F9,$00,$20,$00
dat_018A5C:
	dc.b	$00,$06,$F9,$00,$7B,$00
dat_018A62:
	dc.b	$00,$06,$F9,$00,$7D,$00


; ----------------------------------------------------------------------
; called from $1D44D2, $1D60E0, $1DB6EC
sub_018A68:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	(ram_D01E).w,a3
	movea.l	a3,a4
	adda.w	(a4),a4
	clr.w	d7
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
loc_018A7E:
	tst.l	(a0)
	bmi.w	loc_018A8A
	addq.w	#1,d7
	addq.w	#4,a0
	bra.s	loc_018A7E
loc_018A8A:
	move.w	(ram_D01A).w,d0
	bpl.w	loc_018A98
	clr.w	(ram_D01A).w
	clr.w	d0
loc_018A98:
	cmp.w	d7,d0
	blt.w	loc_018AA6
	move.w	d7,d0
	subq.w	#1,d0
	move.w	d0,(ram_D01A).w
loc_018AA6:
	move.w	(ram_D01C).w,d1
	add.w	(ram_D026).w,d1
	cmp.w	(ram_D01A).w,d1
	bgt.w	loc_018ABC
	addq.w	#1,(ram_D01C).w
	bra.s	loc_018AA6
loc_018ABC:
	move.w	(ram_D01C).w,d1
	cmp.w	(ram_D01A).w,d1
	ble.w	loc_018ACE
	subq.w	#1,(ram_D01C).w
	bra.s	loc_018ABC
loc_018ACE:
	move.w	(ram_D01C).w,d0
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
	move.w	(ram_D01C).w,d0
	bra.w	loc_018AE4
loc_018AE2:
	addq.w	#4,a0
loc_018AE4:
	dbra	d0,loc_018AE2
	move.w	(ram_B03E).w,(TextX).w
	move.w	(ram_B040).w,(TextY).w
	move.w	(ram_D026).w,d0
	cmp.w	d7,d0
	ble.w	loc_018B00
	move.w	d7,d0
loc_018B00:
	clr.w	d1
	bra.w	loc_018B3E
loc_018B06:
	move.w	d1,d2
	add.w	(ram_D01C).w,d2
	movea.l	a3,a1
	cmp.w	(ram_D01A).w,d2
	bne.w	loc_018B18
	movea.l	a4,a1
loc_018B18:
	jsr	(Text_PrintCmd_Worker).l
	movem.l	d0/d1/a0,-(sp)
	movea.l	(a0),a0
	jsr	(a0)
	movem.l	(sp)+,d0/d1/a0
	jsr	(Text_PrintCmd_Worker).l
	move.w	(ram_B03E).w,(TextX).w
	addq.w	#2,(TextY).w
	addq.w	#4,a0
	addq.w	#1,d1
loc_018B3E:
	dbra	d0,loc_018B06
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$0006,$F900,$2000,$0006,$F900,$7B00,$0006,$F900
	dc.w	$7D00,$48E7,$FFFE,$6100,$02A0,$4EB9,$0001,$8DC0
	dc.w	$31FC,$0018,$BD3E,$08B8,$0002,$BFB4,$4278,$D052
	dc.w	$4278,$D04C,$4278,$D04E,$46FC,$2500,$6100,$012E
	dc.w	$3038,$B054,$B078,$B054,$67FA,$4238,$D04E,$4EB9
	dc.w	$0002,$02D2,$4EB9,$0002,$0370,$4A41,$67E2,$0801
	dc.w	$0007,$6600,$004E,$0801,$0000,$6700,$0010,$4A78
	dc.w	$D04C,$6700,$0008,$5378,$D04C,$60C0,$0801,$0001
	dc.w	$6700,$0012,$0C78,$0006,$D04C,$6700,$0008,$5278
	dc.w	$D04C,$60A8,$0801,$0002,$6700,$0008,$11C1,$D04E
	dc.w	$609A,$0801,$0003,$6700,$0008,$11C1,$D04E,$608C
	dc.w	$608E,$4CDF,$7FFF,$4E75


; ----------------------------------------------------------------------
sub_018C00:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ptrs_018C98,a0
	move.w	(ram_D052).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	jsr	(a0)
	move.w	#$1E,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_018C28:
	move.w	#$1,d5
	bra.w	loc_018C32


; ----------------------------------------------------------------------
; called from $018CA0, $018CA4, $018CA8, $018CAC, $018CB0
sub_018C30:
	clr.w	d5
loc_018C32:
	movea.l	#ram_DE7C,a0
	move.w	d2,d0
	move.b	$0(a0,d0.w),d1
	move.b	(ram_D04E).w,d4
	cmp.w	(ram_D04C).w,d2
	bne.w	loc_018C5E
	move.w	#$1,d3
	btst	#2,d4
	bne.w	loc_018C60
	btst	#3,d4
	bne.w	loc_018C60
loc_018C5E:
	clr.w	d3
loc_018C60:
	eor.w	d3,d1
	move.b	d1,$0(a0,d0.w)
	movea.l	#dat_018C80,a1
	clr.w	d0
	move.b	d1,d0
	tst.w	d5
	beq.w	loc_018C7A
	eori.w	#$1,d0
loc_018C7A:
	jmp	(List_Skip).l
dat_018C80:
	dc.b	$00,$0C
	dc.b	"off       ",0
	dc.b	$0C
	dc.b	"on        "

ptrs_018C98:
	dc.l	sub_018C30
	dc.l	sub_018C28

ptrtbl_018CA0:
	dc.l	sub_018C30
	dc.l	sub_018C30
	dc.l	sub_018C30
	dc.l	sub_018C30
	dc.l	sub_018C30
	dc.w	$3A38,$D052,$BA78,$D04C,$6F00,$0008,$5378,$D052
	dc.w	$60EE,$0645,$000A,$BA78,$D04C,$6C00,$0008,$5278
	dc.w	$D052,$60DC,$3438,$D052,$4EB9,$0002,$0CC2,$0006
	dc.w	$8F02,$0500,$323C,$0006,$4243,$3002,$227C,$0001
	dc.w	$8D34,$4EB9,$0002,$2A76,$4EB9,$0002,$0CC2,$0006
	dc.w	$BF02,$0500,$B478,$D04C,$6600,$000E,$4EB9,$0002
	dc.w	$0CC2,$0006,$8F02,$0500,$D778,$B044,$4EB9,$0002
	dc.w	$0CD4,$6100,$FED8
	dc.b	"RBRCQ"
	dc.b	$C9,$FF,$BE,$4E,$75,$00,$14
	dc.b	"lots of penalties",0
	dc.b	$00,$16
	dc.b	"Multi-game injuries",0
	dc.b	$00,$12
	dc.b	"lots of injuries",0
	dc.b	$16
	dc.b	"lots of interference",0
	dc.b	$16
	dc.b	"easy goalie injuries",0
	dc.b	$10
	dc.b	"easy bump net",0
	dc.b	$00,$14
	dc.b	"many double mino"


; ----------------------------------------------------------------------
sub_018DBE:
	moveq	#$73,d1
	movem.l	a0/a1,-(sp)
	movea.l	#dat_1AD3E8,a0
	movea.l	#ram_BD60,a1
	move.w	#$7,d0
loc_018DD4:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_018DD4
	movea.l	#dat_1AD3E8,a0
	movea.l	#PaletteBuffer,a1
	move.w	#$7,d0
loc_018DEA:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_018DEA
	movea.l	#ram_BD48,a1
	move.w	#$FFF,(a1)
	movem.l	(sp)+,a0/a1
	rts

	dc.w	$08F8,$0005,$C358,$21FC,$0001,$728E,$D260,$08B8
	dc.w	$0000,$BFB4,$08F8,$0002,$BFB4,$08B8,$0001,$BFB4
	dc.w	$31FC,$0000,$B000,$31FC,$B400,$B002,$31FC,$B800
	dc.w	$B00C,$31FC,$0005,$B00E,$31FC,$C000,$B008,$31FC
	dc.w	$0006,$B00A,$31FC,$E000,$B004,$31FC,$0006,$B006
	dc.w	$303C,$0000,$08B8,$0005,$BFB4,$4EB9,$0002,$05CE
	dc.w	$4EB9,$0002,$0314,$3038,$B000,$4EB9,$0002,$06C8
	dc.w	$30BC,$0000,$30BC,$0000,$31C4,$B01C,$247C,$001A
	dc.w	$9842,$4EB9,$0002,$0780,$31C4,$B01E,$247C,$001A
	dc.w	$9842,$4EB9,$0002,$0780,$23FC,$001A,$983A,$FFFF
	dc.w	$BF8C,$4EB9,$0002,$0A7E,$0008,$FF01,$FD00,$FC00
	dc.w	$7028,$721C,$343C,$87FF,$4EB9,$0002,$09C6,$4EB9
	dc.w	$0002,$0A7E,$0008,$FF02,$FD00,$FC00,$7028,$721C
	dc.w	$343C,$07FF,$4EB9,$0002,$09C6,$3F38,$B01C,$31F8
	dc.w	$B01E,$B01C,$4EB9,$0002,$0CC2,$0024,$BF04,$1A7B
	dc.w	$7D2D,$7365,$6C65,$6374,$2069,$7465,$6D20,$2020
	dc.w	$5B5D,$2D6D,$616B,$6520,$6368,$6F69,$6365,$4EB9
	dc.w	$0002,$0CC2,$0012,$BF0E,$0264,$6562,$7567,$2073
	dc.w	$6372,$6565,$6E00,$31DF,$B01C,$46FC,$2500,$4E75
; main program entry after the boot checks: clears work RAM, loads the sound driver, inits hardware and jumps to the title loop
Main_Init:
	move.w	#$2700,sr
	movea.w	#$FDFA,sp
	movea.w	#$B000,a0
loc_018F3C:
	clr.l	(a0)+
	cmpa.w	#$DF20,a0
	blt.s	loc_018F3C
	clr.w	(ram_DD14).w
	move.w	(VDP_CTRL).l,d0
	andi.w	#$1,d0
	move.w	d0,(ram_D29E).w
	beq.w	loc_018F60
	bset	#0,(ram_DD14).w
loc_018F60:
	move.w	#$FFFF,(ram_DE44).w
	move.w	#$FFFF,(ram_DE62).w
	move.w	#$FFFF,(ram_D2C0).w
	move.w	#$0,d0
	move.w	#$1B24,d1
	movea.l	#Z80_SoundDriver,a0
	jsr	(Sound_Call).l
	move.w	#$9,d0
	jsr	(Sound_Call).l
	move.w	#$6,d0
	clr.w	d1
	movea.l	#SoundBank,a0
	jsr	(Sound_Call).l
	move.w	#$7,d0
	move.w	#$0,d1
	jsr	(Sound_Call).l
	jsr	(sub_092262).l
	jsr	(sub_026404).l
	jsr	(Joypad_InitPorts).l
	jsr	(sub_02709A).l
	jsr	(sub_02993A).l
	jsr	(sub_1D1BC4).l
	jsr	(sub_0271D0).l
	move.w	(ram_D280).w,(ram_D2A6).w
	move.w	(ram_D270).w,(ram_D2A8).w
	jsr	(Joypad_ReadAll).l
	jmp	(loc_026CE6).l
loc_018FF2:
	move.l	#VBlank_InGame,(VBlankVector).l
	clr.w	(ram_C454).w
	bclr	#5,(SysFlags).w
	st	(ram_D492).w
	jsr	(Joypad_Read1).l
	cmp.b	#$E0,d3	; general form
	bne.w	loc_01901E
	move.w	#$3,(ram_D278).w
loc_01901E:
	clr.b	(ram_C33A).w
	cmpi.w	#$1,(ram_D27E).w
	bne.w	loc_019032
	bset	#5,(ram_C33A).w
loc_019032:
	cmpi.w	#$1,(ram_D270).w
	ble.w	loc_019040
	bsr.w	sub_019134
loc_019040:
	jsr	(sub_026A5E).l
	btst	#7,(ram_C350).w
	bne.w	loc_019064
	btst	#0,(ram_C34A).w
	bne.w	loc_019064
	btst	#3,(ram_C350).w
	beq.w	loc_019080
loc_019064:
	move.l	a0,-(sp)
	movea.l	#ram_C732,a0
	jsr	(sub_1CF682).l
	movea.l	#ram_CAD0,a0
	jsr	(sub_1CF682).l
	movea.l	(sp)+,a0
loc_019080:
	btst	#7,(ram_C350).w
	bne.w	loc_01909E
	btst	#0,(ram_C34A).w
	bne.w	loc_01909E
	btst	#3,(ram_C350).w
	bne.w	loc_01909E
loc_01909E:
	clr.w	(ram_C4D6).w
	clr.w	(ram_C640).w
	clr.w	(ram_C4C8).w
	clr.w	(ram_C4D0).w
	bsr.w	sub_01914E
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_1D26A8).l
	movem.l	(sp)+,d0-d7/a0-a6
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	move.b	#$E7,(PSG).l
	move.b	#$C8,(PSG).l
	move.b	#$1,(PSG).l
	jsr	(sub_022728).l
	jsr	(sub_02642E).l
	jsr	(sub_1CF480).l
	jmp	(loc_026C12).l


; ----------------------------------------------------------------------
; called from $01903C
sub_019134:
	move.l	#$E8E,d0
	move.l	#$A7,d1
	jsr	(sub_029D2A).l
	jsr	(SRAM_UpdateChecksum).l
	rts


; ----------------------------------------------------------------------
; called from $0190AE, $1DDD48
sub_01914E:
	movea.w	#$C732,a2
	bsr.w	sub_01915A
	adda.w	#$39E,a2

; ----------------------------------------------------------------------
; called from $019152
sub_01915A:
	move.w	#$6,$24(a2)
	moveq	#$36,d0
loc_019162:
	move.w	#$FFFE,$6C(a2,d0.w)
	subq.w	#2,d0
	bpl.s	loc_019162
	rts


; ----------------------------------------------------------------------
; called from $019264, $026C12
sub_01916E:
	bsr.w	sub_0191D6
	cmpi.w	#$3,(ram_C4C8).w
	blt.w	loc_0191B6
	tst.w	(ram_D270).w
	bne.w	loc_01918C
	move.w	#$12C,d0
	bra.w	loc_0191B6
loc_01918C:
	cmpi.w	#$3,(ram_D270).w
	bgt.w	loc_01919E
	move.w	#$4B0,d0
	bra.w	loc_0191B6
loc_01919E:
	btst	#7,(SysFlags).w
	beq.w	loc_0191B6
	btst	#2,(ram_DD9E).w
	beq.w	loc_0191B6
	move.w	#$4B0,d0
loc_0191B6:
	move.w	d0,(ram_C4CA).w
	move.w	d0,(ram_C4CE).w
	move.w	d0,(ram_B05E).w
	asr.w	#1,d0
	jsr	(Random).l
	sub.w	d0,(ram_B05E).w
	bset	#0,(ram_C33A).w
	rts


; ----------------------------------------------------------------------
; called from $01916E, $025530, $027F9C
sub_0191D6:
	move.w	(ram_D278).w,d0
	asl.w	#1,d0
	lea	dat_0191E6(pc),a0
	move.w	$0(a0,d0.w),d0
	rts
dat_0191E6:
	dc.w	$012C,$0258,$04B0,$001E
loc_0191EE:
	btst	#7,(ram_C350).w
	beq.w	loc_01921A
	move.w	#$B4,(ram_DE96).w
	bclr	#2,(ram_C34A).w
	bclr	#1,(ram_C33A).w
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_01921A
	bset	#1,(ram_C33A).w
loc_01921A:
	cmpi.w	#$3,(ram_C4C8).w
	bne.w	loc_019230
	bset	#1,(ram_C34C).w
	bset	#5,(SysFlags).w
loc_019230:
	tst.w	(ram_C4C8).w
	bne.w	loc_019250
	bclr	#2,(ram_C35C).w
	bclr	#3,(ram_C35C).w
	move.w	#$FFFF,(ram_DE3C).w
	move.w	#$FFFF,(ram_DE3E).w
loc_019250:
	st	(ram_D49C).w
	movea.w	#$FDFA,sp
	jsr	(sub_092262).l
	jsr	(sub_02642E).l
	bsr.w	sub_01916E
	ori.l	#$F00000,(ram_BEAC).w
	st	(ram_C388).w
	st	(ram_C38A).w
	st	(ram_C38C).w
	st	(ram_C38E).w
	movea.w	#$B760,a3
	clr.w	(ram_BFE4).w
	clr.w	(ram_BFE6).w
	btst	#7,(ram_C350).w
	beq.w	loc_01929E
	move.w	#$31,d0
	bra.w	loc_019302
loc_01929E:
	btst	#0,(ram_C34A).w
	beq.w	loc_0192BC
	move.w	#$1E,d0
	move.w	#$8,(ram_D2F6).w
	move.w	#$B,(ram_D2F4).w
	bra.w	loc_019302
loc_0192BC:
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	moveq	#$1B,d0
loc_019302:
	jsr	(sub_01F172).l
	bset	#2,(ram_C33E).w
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	move.w	(FrameCounter).w,(ram_B056).w
	bsr.w	sub_01939E
	move.w	#$FFFF,(FadeCounter).w
	bsr.w	sub_01939E
	move.w	(ram_CFD6).w,d0
	asl.w	#4,d0
	move.w	d0,(ram_B8BA).w
	clr.w	(ram_C376).w
	move.w	(ram_C3AC).w,(ram_D4AA).w
	btst	#0,(ram_C34A).w
	bne.s	loc_019362
	tst.w	(ram_C4C8).w
	bne.s	loc_019362
	move.w	#$0,(ram_D4AC).w
	bra.w	loc_019368
loc_019362:
	move.w	#$1,(ram_D4AC).w
loc_019368:
	jsr	(sub_092274).l
	move.w	(ram_D4A8).w,-(sp)
	jsr	(sub_092172).l
	cmpi.w	#$2,(ram_C4C8).w
	bge.w	loc_019388
	bset	#7,(ram_C340).w
loc_019388:
	bsr.w	sub_01939E
	bsr.w	sub_01967A
	btst	#0,(ram_C33C).w
	beq.s	loc_019388
	bsr.w	sub_01973E
	bra.s	loc_019388


; ----------------------------------------------------------------------
; called from $019328, $019332, $019388, $0193A6
sub_01939E:
	move.w	(FrameCounter).w,d7
	sub.w	(ram_B056).w,d7
	beq.s	sub_01939E
	move.w	(FrameCounter).w,(ram_B056).w
	bsr.w	sub_019404
	btst	#6,(ram_C340).w
	beq.w	loc_0193C8
	jsr	(sub_013788).l
	jsr	(sub_013A44).l
loc_0193C8:
	bsr.w	sub_01ADDC
	tst.w	(ram_DCDE).w
	beq.w	loc_0193F0
	bmi.w	loc_0193F0
	subq.w	#1,(ram_DCDE).w
	bne.w	loc_0193F0
	jsr	(sub_0921E8).l
	move.w	(ram_DCE0).w,-(sp)
	jsr	(sub_092172).l
loc_0193F0:
	jsr	(sub_1CFA9A).l
	bsr.w	sub_01B29A
	bsr.w	sub_01ACCE
	jmp	(sub_025926).l


; ----------------------------------------------------------------------
; called from $0193AE
sub_019404:
	move.w	(ram_B8B0).w,d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01941C
	bclr	#0,(SysFlags).w
	bclr	#1,(SysFlags).w
loc_01941C:
	move.w	(ram_B7C0).w,(ram_B8B0).w
	tst.w	(ram_B7C0).w
	bmi.w	loc_01942E
	st	(ram_D254).w
loc_01942E:
	jsr	(sub_0213FE).l
	bsr.w	sub_0194C8
	jsr	(sub_1D116C).l
	jsr	(sub_091FBE).l
	bsr.w	sub_01955A
	btst	#7,(ram_C33C).w
	bne.w	loc_01ADDA
	sub.w	d7,(ram_B05C).w
	bpl.w	loc_01ADDA
	addi.w	#$18,(ram_B05C).w
	bsr.w	sub_01E4AA
	jsr	(sub_091F96).l
	jsr	(sub_092018).l
	bsr.w	sub_01948C
	bsr.w	sub_01947E
	jmp	(loc_0220BE).l


; ----------------------------------------------------------------------
; called from $019474
sub_01947E:
	subq.w	#1,(ram_C44E).w
	bne.w	loc_01ADDA
	jmp	(loc_028096).l


; ----------------------------------------------------------------------
; called from $019470
sub_01948C:
	tst.w	(ram_D280).w
	bne.w	loc_0194C6
	movea.w	#$C732,a2
	bsr.w	sub_0194A0
	lea	$39E(a2),a2

; ----------------------------------------------------------------------
; called from $019498
sub_0194A0:
	moveq	#$36,d0
loc_0194A2:
	cmpi.w	#$FFFE,$6C(a2,d0.w)
	bne.w	loc_0194C2
	addi.w	#$9,$34(a2,d0.w)
	cmpi.w	#$1000,$34(a2,d0.w)
	blt.w	loc_0194C2
	move.w	#$1000,$34(a2,d0.w)
loc_0194C2:
	subq.w	#2,d0
	bpl.s	loc_0194A2
loc_0194C6:
	rts


; ----------------------------------------------------------------------
; called from $019434
sub_0194C8:
	cmpi.w	#$15E,(ram_B8B4).w
	blt.w	loc_0194D6
	subq.w	#3,(ram_B8B4).w
loc_0194D6:
	sub.w	d7,(ram_B8B4).w
	bpl.w	loc_0194E2
	clr.w	(ram_B8B4).w
loc_0194E2:
	sub.w	d7,(ram_B8B8).w
	bpl.w	loc_01952C
	move.w	(ram_B8B4).w,d0
	lsr.w	#1,d0
	cmp.w	#$7F,d0	; general form
	bls.w	loc_0194FA
	moveq	#$7F,d0
loc_0194FA:
	andi.w	#$60,d0
	addq.w	#2,(ram_B8B6).w
	andi.w	#$1E,(ram_B8B6).w
	add.w	(ram_B8B6).w,d0
	movea.l	#dat_0288B2,a0
	move.b	$0(a0,d0.w),(ram_B8B3).w
	clr.w	d1
	move.b	$1(a0,d0.w),d1
	move.w	(VDP_HVCOUNTER).l,d2
	and.w	d1,d2
	add.w	d2,d1
	move.w	d1,(ram_B8B8).w
loc_01952C:
	clr.b	(ram_B8B2).w
	cmpi.w	#$118,(ram_B8B4).w
	bls.w	loc_01ADDA
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$7F,d0
	cmp.w	#$13,d0	; general form
	blt.w	loc_01ADDA
	cmp.w	#$19,d0	; general form
	bgt.w	loc_01ADDA
	move.b	d0,(ram_B8B2).w
	rts


; ----------------------------------------------------------------------
; called from $019444
sub_01955A:
	btst	#0,(ram_C33A).w
	bne.w	loc_01ADDA
	tst.w	(ram_C4CA).w
	bne.w	loc_01ADDA
	bset	#3,(VideoFlags).w
	jsr	(sub_0921E8).l
	move.w	#$4,-(sp)
	jsr	(sub_09205A).l
	bsr.w	sub_01B286
loc_019586:
	movea.w	#$B760,a3
	moveq	#$18,d0
	jsr	(sub_01F168).l
	cmpi.w	#$2,(ram_C4C8).w
	blt.w	loc_019658
	moveq	#$7,d0
	movea.w	#$B060,a3
	cmpi.w	#$3,(ram_CFD6).w
	bne.w	loc_019602
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_0195EC
	moveq	#$10,d3
	mulu.w	(ram_CFD0).w,d3
	movea.w	#$CF50,a0
	adda.w	d3,a0
	clr.w	d3
	btst	#0,$E(a0)
	beq.w	loc_0195D2
	eori.w	#$2,d3
loc_0195D2:
	move.w	(ram_C73E).w,d1
	sub.w	(ram_CADC).w,d1
	bpl.w	loc_0195E2
	eori.w	#$2,d3
loc_0195E2:
	cmpi.w	#$3,$4(a0,d3.w)
	bne.w	loc_019602
loc_0195EC:
	moveq	#$8,d0
	moveq	#$B,d2
loc_0195F0:
	bclr	#3,$62(a3)
	adda.w	#$80,a3
	dbra	d2,loc_0195F0
	movea.w	#$B060,a3
loc_019602:
	moveq	#$5,d2
	move.w	(ram_C73E).w,d1
	sub.w	(ram_CADC).w,d1
	beq.w	loc_019658
	bpl.w	loc_019618
	adda.w	#$300,a3
loc_019618:
	tst.w	$34(a3)
	ble.w	loc_019628
	jsr	(sub_01F168).l
	moveq	#$7,d0
loc_019628:
	adda.w	#$80,a3
	dbra	d2,loc_019618
loc_019630:
	jsr	(sub_021EC6).l
	addi.w	#$3E8,(ram_B8B4).w
	bset	#0,(ram_C33A).w
	bset	#6,(ram_C33A).w
	jsr	(sub_1D2282).l
	move.w	#$4,d0
	jmp	(sub_02135E).l
loc_019658:
	btst	#3,(ram_C350).w
	bne.s	loc_019630
	cmpi.w	#$3,(ram_C4C8).w
	bne.w	loc_019670
	tst.w	(ram_D270).w
	beq.s	loc_019630
loc_019670:
	move.w	#$2,d0
	jmp	(sub_02135E).l


; ----------------------------------------------------------------------
; called from $01938C
sub_01967A:
	tst.w	(ram_C394).w
	bne.w	loc_019716
	tst.w	(ram_C396).w
	bne.w	loc_019716
	tst.w	(ram_C398).w
	bne.w	loc_019716
	tst.w	(ram_C39A).w
	bne.w	loc_019716
	jsr	(Joypad_Read1).l
	btst	#7,d1
	beq.w	loc_0196AE
	jmp	(loc_019720).l
loc_0196AE:
	bsr.w	sub_0196FA
	jsr	(Joypad_Read2).l
	btst	#7,d1
	beq.w	loc_0196C6
	jmp	(loc_019726).l
loc_0196C6:
	tst.w	(FourWayPlay).w
	beq.w	sub_0196FA
	jsr	(Joypad_Read3).l
	btst	#7,d1
	beq.w	loc_0196E2
	jmp	(loc_01972E).l
loc_0196E2:
	bsr.w	sub_0196FA
	jsr	(Joypad_Read4).l
	btst	#7,d1
	beq.w	sub_0196FA
	jmp	(loc_019736).l


; ----------------------------------------------------------------------
; called from $0196AE, $0196CA, $0196E2, $0196F0
sub_0196FA:
	tst.w	d1
	beq.w	loc_019716
	st	(ram_D294).w
	move.w	#$64,(ram_D31A).w
	move.w	#$64,(ram_D31C).w
	jmp	(loc_026CE2).l
loc_019716:
	rts
loc_019718:
	bset	#0,(ram_C33C).w
	rts
loc_019720:
	clr.w	(ram_D26E).w
	bra.s	loc_019718
loc_019726:
	move.w	#$1,(ram_D26E).w
	bra.s	loc_019718
loc_01972E:
	move.w	#$2,(ram_D26E).w
	bra.s	loc_019718
loc_019736:
	move.w	#$3,(ram_D26E).w
	bra.s	loc_019718


; ----------------------------------------------------------------------
; called from $019398
sub_01973E:
	jsr	(sub_01FFA2).l
	move.w	d0,-(sp)
	move.w	(FrameCounter).w,d0
loc_01974A:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_01974A
	move.w	(sp)+,d0
	jsr	(sub_092262).l
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
	move.w	(ram_C33C).w,-(sp)
	bsr.w	sub_019930
	jsr	(sub_1D22D2).l
	movea.l	#dat_028DDA,a0
	tst.w	(ram_D27C).w
	bne.w	loc_0197B8
	movea.l	#dat_028F66,a0
loc_0197B8:
	lea	sub_019924(pc),a1
	btst	#0,(ram_C34A).w
	beq.w	loc_0197D0
	movea.l	#dat_028D56,a0
	bra.w	loc_019816
loc_0197D0:
	btst	#3,(ram_C350).w
	beq.w	loc_0197E4
	movea.l	#dat_028D56,a0
	bra.w	loc_019816
loc_0197E4:
	btst	#7,(ram_C350).w
	beq.w	loc_0197F8
	movea.l	#dat_028D1A,a0
	bra.w	loc_019816
loc_0197F8:
	btst	#2,$30(a2)
	beq.w	loc_019816
	movea.l	#dat_0290DA,a0
	tst.w	(ram_D27C).w
	bne.w	loc_019816
	movea.l	#dat_02924E,a0
loc_019816:
	bsr.w	sub_019980
loc_01981A:
	bsr.w	sub_019BF0
	bsr.w	sub_01A7B4
	jsr	(Joypad_Repeat).l
	bsr.w	sub_0199B8
	bne.s	loc_01981A
	jsr	(sub_01FFA2).l
	btst	#3,(ram_C350).w
	beq.w	loc_019844
	jsr	(sub_1E48DE).l
loc_019844:
	move.w	(sp)+,(ram_C33C).w
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	jmp	(sub_1DCE6A).l


; ----------------------------------------------------------------------
sub_019892:
	jsr	(sub_022252).l
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	movea.l	#VDP_DATA,a0
	move.w	#$9100,$4(a0)
	move.w	#$9200,$4(a0)
	bset	#3,(VideoFlags).w
	bclr	#0,(ram_C33C).w
	btst	#7,(ram_C350).w
	bne.w	loc_01990A
	jsr	(sub_022296).l
loc_01990A:
	jsr	(sub_025926).l
	move.w	#$18,(FadeCounter).w
loc_019916:
	tst.w	(FadeCounter).w
	bpl.s	loc_019916
	move.w	(FrameCounter).w,(ram_B056).w
	rts


; ----------------------------------------------------------------------
; called from $0197B8, $0226BA
sub_019924:
	jsr	(sub_1DD152).l
	jsr	(sub_026404).l

; ----------------------------------------------------------------------
; called from $01979A, $0199E8
sub_019930:
	movea.l	#ram_C732,a2
	tst.w	(ram_D26E).w
	beq.w	loc_019970
	cmpi.w	#$1,(ram_D26E).w
	beq.w	loc_019966
	cmpi.w	#$2,(ram_D26E).w
	beq.w	loc_01995C
	cmpi.w	#$1,(ram_C39A).w
	bra.w	loc_019976
loc_01995C:
	cmpi.w	#$1,(ram_C398).w
	bra.w	loc_019976
loc_019966:
	cmpi.w	#$1,(ram_C396).w
	bra.w	loc_019976
loc_019970:
	cmpi.w	#$1,(ram_C394).w
loc_019976:
	beq.w	loc_01997E
	adda.w	#$39E,a2
loc_01997E:
	rts


; ----------------------------------------------------------------------
; called from $019816, $0226C0
sub_019980:
	move.l	a0,(ram_D01E).w
	move.l	a1,(ram_D022).w
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w

; ----------------------------------------------------------------------
; called from $019A48
sub_019990:
	movea.l	(ram_D022).w,a0
	jsr	(a0)
	bsr.w	sub_019A58
	move.w	#$18,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $019AAC, $019ADA, $019B10, $019B50, $019B6A
sub_0199A2:
	move.w	#$5,(TextX).w
	btst	#1,(VideoFlags).w
	bne.w	loc_01ADDA
	addq.w	#4,(TextX).w
	rts


; ----------------------------------------------------------------------
; called from $019828, $02028E, $0226EE
sub_0199B8:
	btst	#7,d1
	bne.w	loc_019A52
	btst	#1,d1
	beq.w	loc_0199D0
	addq.w	#1,(ram_D01A).w
	bra.w	sub_019A58
loc_0199D0:
	btst	#0,d1
	beq.w	loc_0199E0
	subq.w	#1,(ram_D01A).w
	bra.w	sub_019A58
loc_0199E0:
	btst	#5,d1
	beq.w	loc_019A52
	bsr.w	sub_019930
	move.w	(ram_D01A).w,d0
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
	bra.w	loc_0199FE
loc_0199FC:
	addq.w	#4,a0
loc_0199FE:
	adda.w	(a0),a0
	dbra	d0,loc_0199FC
	movea.l	(a0),a0
	move.l	a0,-(sp)
	bset	#4,(ram_C358).w
	jsr	(a0)
	bclr	#4,(ram_C358).w
	movea.l	(sp)+,a0
	bclr	#1,(ram_C346).w
	bne.w	loc_019A4C
	cmpa.l	#dat_019F80,a0
	beq.w	loc_019A40
	cmpa.l	#dat_01A026,a0
	beq.w	loc_019A40
	cmpa.l	#sub_1D108E,a0
	bne.w	loc_019A48
loc_019A40:
	bsr.w	sub_019A58
	bra.w	loc_019A4C
loc_019A48:
	bsr.w	sub_019990
loc_019A4C:
	tst.w	(ram_D01A).w
	rts
loc_019A52:
	eori	#$4,ccr
	rts


; ----------------------------------------------------------------------
; called from $019996, $0199CC, $0199DC, $019A40
sub_019A58:
	jsr	(Text_PrintCmd).l
inl_019A5E:
	dc.w	loc_019A62-inl_019A5E
	dc.b	$FE,$04
loc_019A62:
	move.w	(ram_D01A).w,d0
	bpl.w	loc_019A70
	clr.w	(ram_D01A).w
	clr.w	d0
loc_019A70:
	movea.l	(ram_D01E).w,a0
	adda.w	(a0),a0
	adda.w	(a0),a0
	bra.w	loc_019A84
loc_019A7C:
	adda.w	(a0),a0
	addq.w	#4,a0
	tst.w	$2(a0)
loc_019A84:
	dbmi	d0,loc_019A7C
	addq.w	#1,d0
	sub.w	d0,(ram_D01A).w
	move.w	(ram_D01A).w,d0
	cmp.w	(ram_D01C).w,d0
	bge.w	loc_019A9E
	move.w	d0,(ram_D01C).w
loc_019A9E:
	subq.w	#7,d0
	cmp.w	(ram_D01C).w,d0
	ble.w	loc_019AAC
	move.w	d0,(ram_D01C).w
loc_019AAC:
	bsr.w	sub_0199A2
	move.w	#$6,(TextY).w
	movea.l	(ram_D01E).w,a1
	jsr	(sub_020F4A).l
	adda.w	(a1),a1
	move.w	(ram_D01C).w,d0
	bra.w	loc_019ACE
loc_019ACA:
	adda.w	(a1),a1
	addq.w	#4,a1
loc_019ACE:
	dbra	d0,loc_019ACA
	moveq	#$7,d1
	move.w	#$4,(TextY).w
	bsr.w	sub_0199A2
	jsr	(Text_PrintCmd).l
inl_019AE4:
	dc.w	loc_019AF2-inl_019AE4
	dc.w	$FB00,$FA03,$20FB,$1420,$FAFD,$FBEA
loc_019AF2:
	move.w	(ram_D01C).w,d0
	beq.w	loc_019B10
	jsr	(Text_PrintCmd).l
inl_019B00:
	dc.w	loc_019B10-inl_019B00
	dc.w	$FE07,$FB00,$FA03,$7BFB,$147B,$FAFD,$FE04
loc_019B10:
	bsr.w	sub_0199A2
	jsr	(Text_PrintCmd).l
inl_019B1A:
	dc.w	loc_019B20-inl_019B1A
	dc.b	$FB,$02,$FA,$02
loc_019B20:
	move.l	a1,-(sp)
	movea.l	(ram_D01E).w,a1
	jsr	(sub_020F4A).l
	cmp.w	(ram_D01A).w,d0
	bne.w	loc_019B3A
	jsr	(sub_020F4A).l
loc_019B3A:
	movea.l	(sp)+,a1
	bsr.w	sub_019B80
	addq.w	#1,d0
	addq.w	#4,a1
	tst.w	$2(a1)
	dbmi	d1,loc_019B10
	bmi.w	loc_019B6A
	bsr.w	sub_0199A2
	jsr	(Text_PrintCmd).l
inl_019B5A:
	dc.w	loc_019B68-inl_019B5A
	dc.w	$FE07,$FB00,$FC13,$7DFB,$147D,$FE04
loc_019B68:
	rts
loc_019B6A:
	bsr.w	sub_0199A2
	jsr	(Text_PrintCmd).l
inl_019B74:
	dc.w	loc_019B7E-inl_019B74
	dc.w	$FB00,$FC13,$20FB,$1420
loc_019B7E:
	rts


; ----------------------------------------------------------------------
; called from $019B3C
sub_019B80:
	cmpi.b	#$78,$2(a1)
	bne.w	loc_019BC0
	move.l	a1,-(sp)
	movea.l	#dat_019BC8,a1
	btst	#1,(ram_C33C).w
	beq.w	loc_019BA4
	tst.w	(ram_D28C).w
	bra.w	loc_019BA8
loc_019BA4:
	tst.w	(ram_D28A).w
loc_019BA8:
	beq.w	loc_019BB2
	movea.l	#dat_019BDC,a1
loc_019BB2:
	jsr	(sub_020F4A).l
	movea.l	(sp)+,a1
	adda.w	(a1),a1
	bra.w	loc_019BC6
loc_019BC0:
	jsr	(sub_020F4A).l
loc_019BC6:
	rts
dat_019BC8:
	dc.b	$00,$14
	dc.b	"  MANUAL GOALIE   "
dat_019BDC:
	dc.b	$00,$14
	dc.b	"   AUTO GOALIE    "


; ----------------------------------------------------------------------
; called from $00DF28, $00DF2E, $01981A, $01A90E, $01A914, $01A932, $01A94E, $0226DC (+8 more)
sub_019BF0:
	move.w	d0,-(sp)
	move.w	(ram_B056).w,d0
	move.w	(ram_B056).w,d0
loc_019BFA:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_019BFA
	move.w	(ram_B056).w,(FrameCounter).w
	move.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $1DDAE0, $1E4CAA
sub_019C0A:
	movem.l	d0-d4/d7/a0/a1/a4/a5,-(sp)
	move.w	(TextX).w,-(sp)
	pea	sub_019C70(pc)
	jsr	(sub_0284FC).l
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp),(TextX).w
	addi.w	#$18,(TextX).w
	move.w	$28(a2),d7
	move.w	d0,-(sp)
	jsr	(sub_013E80).l
	movea.l	#ptrs_1D8AEA,a1
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp)+,d0
	move.w	(sp),(TextX).w
	addi.w	#$1C,(TextX).w
	cmp.w	#$2,d4	; general form
	bls.w	loc_019C66
	jsr	(sub_1D07D4).l
	swap	d4
loc_019C66:
	lea	jmptbl_019CB2(pc),a0
	adda.w	$0(a0,d4.w),a0
	jmp	(a0)


; ----------------------------------------------------------------------
; called from $019C12
sub_019C70:
	move.w	(sp)+,d0
	movem.l	(sp)+,d0-d4/d7/a0/a1/a4/a5
	rts


; ----------------------------------------------------------------------
sub_019C78:
	movem.l	d0-d4/a0/a1/a4/a5,-(sp)
	pea	sub_019CAC(pc)
	jsr	(sub_0284FC).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$1E,(TextX).w
	cmp.w	#$2,d4	; general form
	bls.w	loc_019CA2
	jsr	(sub_1D07D4).l
	swap	d4
loc_019CA2:
	lea	jmptbl_019CB2(pc),a0
	adda.w	$0(a0,d4.w),a0
	jmp	(a0)


; ----------------------------------------------------------------------
; called from $019C7C
sub_019CAC:
	movem.l	(sp)+,d0-d4/a0/a1/a4/a5
	rts

jmptbl_019CB2:
	dc.w	loc_019CBE-jmptbl_019CB2
	dc.w	loc_019DDC-jmptbl_019CB2
	dc.w	loc_019E24-jmptbl_019CB2
	dc.b	$01,$98,$01,$44,$01,$4A
loc_019CBE:
	move.w	d0,(ram_DDDE).w
	add.w	d0,d0
	move.w	$6C(a2,d0.w),d0
	bpl.w	loc_019D12
	not.w	d0
	cmp.w	#$3,d0	; general form
	bls.w	loc_019CDE
	moveq	#$1,d0
	bra.w	loc_019CDE
loc_019CDC:
	moveq	#$3,d0
loc_019CDE:
	cmp.w	#$3,d0	; general form
	bne.w	loc_019D08
	movem.l	d0/d1/d7,-(sp)
	move.w	(ram_DDDE).w,d1
	move.w	$28(a2),d7
	jsr	(sub_1E41EC).l
	lea	dat_019D78(pc),a1
	jsr	(sub_022A6E).l
	movem.l	(sp)+,d0/d1/d7
	rts
loc_019D08:
	lea	dat_019D44(pc),a1
	jmp	(sub_022A6E).l
loc_019D12:
	btst	#12,d0
	bne.s	loc_019CDC
	subq.w	#1,(TextX).w
	move.w	d0,d1
	andi.w	#$7FF,d0
	jsr	(sub_020DD4).l
	jsr	(Text_PrintFont_Worker).l
	moveq	#$4,d0
	bclr	#14,d1
	beq.w	loc_019D3A
	moveq	#$5,d0
loc_019D3A:
	lea	dat_019D44(pc),a1
	jmp	(sub_022A6E).l
dat_019D44:
	dc.b	$00,$0A
	dc.b	"Ice     ",0
	dc.b	$0A
	dc.b	"Bench   ",0
	dc.b	$0A
	dc.b	"Injury P",0
	dc.b	$0A
	dc.b	"Injury G",0
	dc.b	$06
	dc.b	"    ",0
	dc.b	$06
	dc.b	" C  "
dat_019D78:
	dc.b	$00,$0A
	dc.b	"Inj. G  ",0
	dc.b	$0A
	dc.b	"Inj.1G  ",0
	dc.b	$0A
	dc.b	"Inj.2G  ",0
	dc.b	$0A
	dc.b	"Inj.3G  ",0
	dc.b	$0A
	dc.b	"Inj.4G  ",0
	dc.b	$0A
	dc.b	"Inj.5G  ",0
	dc.b	$0A
	dc.b	"Inj.6G  ",0
	dc.b	$0A
	dc.b	"Inj.7G  ",0
	dc.b	$0A
	dc.b	"Inj.8G  ",0
	dc.b	$0A
	dc.b	"Inj.9G  "
loc_019DDC:
	add.w	d0,d0
	move.w	$34(a2,d0.w),d0
	ext.l	d0
	divu.w	#$28,d0
	cmp.w	#$64,d0	; general form
	ble.w	loc_019E08
	moveq	#$64,d0
	bra.w	loc_019E08

	dc.w	$0240,$000E,$5341,$C0FC,$0064,$80C1,$4EB9,$001D
	dc.w	$1D90
loc_019E08:
	moveq	#$4,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_019E1C:
	dc.w	loc_019E22-inl_019E1C
	dc.b	"    "
loc_019E22:
	rts
loc_019E24:
	andi.w	#$1,d0
	eori.w	#$1,d0
	lea	dat_019E36(pc),a1
	jmp	(sub_022A6E).l
dat_019E36:
	dc.w	$000A,$5269,$6768,$7479,$2020,$000A,$4C65,$6674
	dc.w	$7920,$2020,$6100,$001E,$4EB9,$0002,$0E38,$4EB9
	dc.w	$0002,$0CD4,$4EB9,$0002,$0CC2,$0008,$206C,$6220
	dc.w	$2000,$4E75


; ----------------------------------------------------------------------
; called from $1D8A64, $1D9096
sub_019E6A:
	movem.l	a0,-(sp)
	movea.l	#dat_019E80,a0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	movem.l	(sp)+,a0
	rts
dat_019E80:
	dc.w	$008C,$0094,$0098,$00A4,$00AC,$00B4,$00BC,$00C4
	dc.w	$00CC,$00D4,$00DC,$00E4,$00EC,$00F4,$00FC,$0104


; ----------------------------------------------------------------------
; called from $026CC6
sub_019EA0:
	btst	#7,(SysFlags).w
	beq.w	loc_019EB0
	jmp	(loc_1D535A).l
loc_019EB0:
	movem.l	a2,-(sp)
	jsr	(sub_027C40).l
	movea.w	#$CFDE,a0
	move.w	(ram_CFD8).w,d0
	move.b	$0(a0,d0.w),d0
	movea.w	#$C732,a2
	cmp.w	$28(a2),d0
	beq.w	loc_019ED6
	adda.w	#$39E,a2
loc_019ED6:
	moveq	#$1,d7
	jsr	(sub_1E05D2).l
	movem.l	(sp)+,a2
	rts

	dc.b	$61,$00,$60,$BC


; ----------------------------------------------------------------------
; called from $01A72E, $022262
sub_019EE8:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	move.w	(ram_B000).w,d0
	bsr.w	VDP_SetWriteAddr
	move.l	#$0,(a0)
	move.w	#$8D00,d0
	move.b	(ram_B000).w,d0
	lsr.b	#2,d0
	move.w	d0,$4(a0)
	move.w	#$8C00,$4(a0)
	move.w	#$5,(ram_B00E).w
	move.w	(sp)+,(VideoFlags).w
	bset	#1,(VideoFlags).w
	move.w	(ram_B024).w,d4
	movea.l	#Art_Rink_Tiles,a2
	btst	#4,(ram_C344).w
	beq.w	loc_019F38
loc_019F38:
	bsr.w	sub_020780
	jsr	(sub_1D1856).l
	jsr	(sub_1D1846).l
	move.w	(FontTileBase).w,d4
	jsr	(sub_029EE6).l
	move.w	(ram_B02A).w,d4
	jsr	(sub_021310).l
	jsr	(sub_02668C).l
	jsr	(sub_02669E).l
	jsr	(sub_0266AC).l
	jsr	(sub_026676).l
	bset	#7,(ram_C356).w
	jmp	(sub_026B9C).l
dat_019F80:
	dc.w	$4EB9,$001D,$D740,$5378,$D01A,$5378,$D01C,$23FC
	dc.w	$0002,$90DA,$FFFF,$D01E,$4A78,$D27C,$6600,$000C
	dc.w	$23FC,$0002,$924E,$FFFF,$D01E,$08EA,$0002,$0030
	dc.w	$6100,$6C2C,$0006,$BF04,$0C00,$7016,$7206,$6100
	dc.w	$6F66,$001A,$F804,$010C,$06F9,$0120,$2020,$2054
	dc.w	$696D,$656F,$7574,$F804,$0115,$0800


; ----------------------------------------------------------------------
sub_019FDC:
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bsr.w	sub_020F4A
	movea.w	#$C732,a2
	jsr	(sub_0225BE).l
	adda.w	#$39E,a2
	jsr	(sub_0225BE).l
	btst	#0,(ram_C33A).w
	bne.w	loc_01A020
	clr.w	(ram_B04C).w
	clr.w	(ram_B04E).w
	move.w	#$A,d0
	jsr	(sub_02135E).l
loc_01A020:
	moveq	#$78,d0
	bra.w	sub_0201A2
dat_01A026:
	dc.w	$4EB9,$001D,$D740,$3F38,$D01A,$3F38,$D01C,$6100
	dc.w	$0232,$31C0,$D01C,$6100,$6BA0,$0006,$BF04,$0C00
	dc.w	$7018,$7203,$D278,$D01C,$302A,$0026,$6A00,$0004
	dc.w	$70FF,$5240,$31C0,$D01A,$6100,$00E6,$6100,$027C
	dc.w	$0801,$0007,$6600,$00AC,$0801,$0005,$6600,$00A4
	dc.w	$0801,$0001,$6700,$0046,$3038,$D01A,$5240,$B078
	dc.w	$D01C,$6ED4,$48A7,$8000,$5340,$D040,$0C72,$FFFD
	dc.w	$006C,$4C9F,$0001,$6700,$0018,$48A7,$8000,$5340
	dc.w	$D040,$0C72,$FFFC,$006C,$4C9F,$0001,$6600,$000A
	dc.w	$5240,$B078,$D01C,$6EA0,$31C0,$D01A,$0801,$0000
	dc.w	$6796,$5378,$D01A,$48A7,$2000,$3438,$D01A,$48A7
	dc.w	$2000,$5342,$D442,$0C72,$FFFC,$206C,$4C9F,$0004
	dc.w	$6700,$0018,$48A7,$2000,$5342,$D442,$0C72,$FFFD
	dc.w	$206C,$4C9F,$0004,$6600,$0006,$5378,$D01A,$4C9F
	dc.w	$0004,$4A78,$D01A,$6A00,$FF50,$4278,$D01A,$6000
	dc.w	$FF48


; ----------------------------------------------------------------------
sub_01A118:
	move.w	(ram_D01A).w,d0
	subq.w	#1,d0
	bpl.w	loc_01A132
	btst	#0,(ram_C33E).w
	beq.w	loc_01A132
	move.w	#$A,(ram_B7A0).w
loc_01A132:
	move.w	d0,$26(a2)
	jsr	(sub_025122).l
	move.w	(sp)+,(ram_D01C).w
	move.w	(sp)+,(ram_D01A).w
	rts

	dc.w	$31FC,$0006,$B044,$3238,$D01C,$7000,$31FC,$000B
	dc.w	$B042,$4EB9,$0002,$0F26,$0008,$FE04,$FF01,$F901
	dc.w	$B078,$D01A,$6600,$0010,$4EB9,$0002,$0F26,$0008
	dc.w	$FE04,$FF01,$F902,$6100,$6DA8,$0014,$2020,$2020
	dc.w	$2020,$2020,$2020,$2020,$2020,$2020,$2020,$4A40
	dc.w	$6600,$0020,$31FC,$000B,$B042,$6100,$6D84,$0010
	dc.w	$2020,$6E6F,$2067,$6F61,$6C69,$6520,$2000,$6000
	dc.w	$004C,$3400,$5342,$31C2,$C4D4,$B5FC,$FFFF,$C732
	dc.w	$6700,$0006,$50F8,$C4D4,$4EB9,$0002,$86B6,$31FC
	dc.w	$000B,$B042,$4EB9,$0002,$0F26,$0004,$2020,$0CB9
	dc.w	$001B,$509C,$FFFF,$B010,$6600,$0008,$08F8,$0006
	dc.w	$C35A,$6100,$6D50,$08B8,$0006,$C35A,$5478,$B044
	dc.w	$5240,$51C9,$FF48,$4E75


; ----------------------------------------------------------------------
; called from $014686, $0148A6, $0148B4, $014914, $014922, $014982, $014990, $01A270 (+21 more)
sub_01A20E:
	movem.l	d1/d7/a0,-(sp)
	btst	#4,(ram_C356).w
	bne.w	loc_01A23E
	cmp.w	#$1A,d7	; general form
	bge.w	loc_01A23E
	movea.l	#$203A3C,a0
	mulu.w	#$4,d7
	clr.w	d0
	move.b	$3(a0,d7.w),d0
	andi.w	#$3,d0
loc_01A238:
	movem.l	(sp)+,d1/d7/a0
	rts
loc_01A23E:
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_01A252
	movea.l	#RosterTable,a0
loc_01A252:
	asl.w	#2,d7
	adda.w	d7,a0
	movea.l	(a0),a0
	adda.w	$A(a0),a0
	move.w	(a0),d1
	clr.w	d0
loc_01A260:
	addq.w	#1,d0
	asl.w	#4,d1
	bne.s	loc_01A260
	bra.s	loc_01A238


; ----------------------------------------------------------------------
; called from $0141FE, $028006, $1D06E6, $1D06F6, $1D258A, $1DD924, $1DD956, $1DD9CC (+2 more)
sub_01A268:
	movem.l	d1/d7/a0,-(sp)
	move.w	$28(a2),d7
	bsr.s	sub_01A20E
	movem.l	(sp)+,d1/d7/a0
	rts


; ----------------------------------------------------------------------
; called from $012B84, $012CC0, $01A2D8, $01DF22, $1D4F02, $1D53CE, $1D5A06, $1D7266 (+7 more)
sub_01A278:
	movem.l	d7/a0,-(sp)
	btst	#4,(ram_C356).w
	bne.w	loc_01A2A4
	cmp.w	#$1A,d7	; general form
	bge.w	loc_01A2A4
	movea.l	#$203A3C,a0
	mulu.w	#$4,d7
	clr.w	d0
	move.b	$1(a0,d7.w),d0
loc_01A29E:
	movem.l	(sp)+,d7/a0
	rts
loc_01A2A4:
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_01A2B8
	movea.l	#RosterTable,a0
loc_01A2B8:
	asl.w	#2,d7
	movea.l	$0(a0,d7.w),a0
	adda.w	(a0),a0
	clr.w	d0
loc_01A2C2:
	addq.w	#1,d0
	adda.w	(a0),a0
	addq.w	#8,a0
	cmpi.w	#$2,(a0)
	bne.s	loc_01A2C2
	bra.s	loc_01A29E


; ----------------------------------------------------------------------
; called from $014204, $025286, $1D0710, $1D0720, $1DD94E, $1DD9EA, $1E4AA4
sub_01A2D0:
	movem.l	d7/a0,-(sp)
	move.w	$28(a2),d7
	bsr.s	sub_01A278
	movem.l	(sp)+,d7/a0
	rts


; ----------------------------------------------------------------------
; called from $01A2F4
sub_01A2E0:
	move.w	(FrameCounter).w,d1
loc_01A2E4:
	cmp.w	(FrameCounter).w,d1
	beq.s	loc_01A2E4
	bsr.w	sub_01A7B4
	bsr.w	Joypad_DpadFilter
	tst.b	d1
	beq.s	sub_01A2E0
	rts


; ----------------------------------------------------------------------
sub_01A2F8:
	bclr	#0,(ram_C346).w
	bsr.w	sub_01FFA2
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	move.w	(VideoFlags).w,-(sp)
	bset	#3,(ram_C33E).w
	bclr	#4,(ram_C344).w
	jsr	(sub_1DCF24).l
	jsr	(sub_01A7D4).l
	bclr	#5,(ram_C33C).w
	bclr	#5,(ram_C340).w
	st	(ram_BE6E).w
	movea.l	(ram_B050).w,a4
loc_01A376:
	bsr.w	sub_01A8BC
	tst.w	d7
	bne.s	loc_01A376
	jsr	(sub_02698A).l
	jsr	(sub_025926).l
	bclr	#1,(ram_C340).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	move.w	#$18,(FadeCounter).w
	moveq	#$1,d7
loc_01A3A4:
	move.w	(FrameCounter).w,d0
	sub.w	(ram_B056).w,d0
	cmp.w	d0,d7
	bhi.s	loc_01A3A4
	move.w	(FrameCounter).w,(ram_B056).w
	tst.w	(ram_DCC6).w
	bmi.w	loc_01A3D0
	sub.w	d7,(ram_DCC6).w
	bpl.w	loc_01A3D0
	clr.w	(ram_DCC6).w
	jsr	(sub_01A806).l
loc_01A3D0:
	movem.l	d0/a3,-(sp)
	movea.l	#ram_B660,a3
	move.w	#$1,$8(a3)
	movea.l	#ram_B6E0,a3
	move.w	#$1,$8(a3)
	movem.l	(sp)+,d0/a3
	moveq	#$1,d7
	bsr.w	sub_01A7B4
	btst	#0,(ram_C346).w
	beq.w	loc_01A410
	andi.w	#$FFF0,d0
	ori.w	#$8,d0
	andi.w	#$FFF0,d1
	andi.w	#$FFF0,d3
loc_01A410:
	movea.w	#$BE58,a5
	btst	#5,(ram_C340).w
	beq.w	loc_01A428
	move.w	d1,d5
	andi.w	#$F,d5
	beq.w	loc_01A5AE
loc_01A428:
	btst	#3,d0
	bne.w	loc_01A5AE
	cmpi.w	#$FF60,(a5)
	bgt.w	loc_01A440
	move.w	#$0,(a5)
	bra.w	loc_01A440
loc_01A440:
	cmpi.w	#$FEB0,$14(a5)
	bgt.w	loc_01A450
	move.w	#$0,$14(a5)
loc_01A450:
	bset	#5,(ram_C33C).w
	bne.w	loc_01A464
	move.w	(ram_BD34).w,(a5)
	move.w	(ram_BD30).w,$14(a5)
loc_01A464:
	move.w	d0,d5
	andi.w	#$7,d5
	eori.w	#$4,d5
	movea.w	#$B060,a1
	st	d3
	bclr	#5,(ram_C340).w
	beq.w	loc_01A482
	move.w	$16(a5),d3
loc_01A482:
	move.w	(a5),d0
	move.w	$14(a5),d1
	moveq	#$B,d2
	move.l	#$100,d4
	movem.w	d0/d1,-(sp)
loc_01A494:
	cmp.w	$52(a1),d3
	beq.w	loc_01A4F2
	movem.w	(sp),d0/d1
	sub.w	(a1),d0
	sub.w	$14(a1),d1
	jsr	(sub_01F186).l
	btst	#3,d0
	bne.w	loc_01A4F2
	sub.w	d5,d0
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bhi.w	loc_01A4F2
	movem.w	(sp),d0/d1
	sub.w	(a1),d0
	sub.w	$14(a1),d1
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	#$4,d0	; general form
	bls.w	loc_01A4F2
	cmp.l	d4,d0
	bhi.w	loc_01A4F2
	move.l	d0,d4
	move.w	$52(a1),$16(a5)
	bset	#5,(ram_C340).w
loc_01A4F2:
	adda.w	#$80,a1
	dbra	d2,loc_01A494
	addq.w	#4,sp
	btst	#5,(ram_C340).w
	beq.w	loc_01A526
	move.w	$16(a5),d0
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	moveq	#$4,d4
	bsr.w	sub_01B86A
	bsr.w	sub_01A9D6
	jsr	(sub_025926).l
	bra.w	loc_01A3A4
loc_01A526:
	bset	#5,(ram_C33C).w
	eori.w	#$4,d5
	asl.w	#2,d5
	lea	dat_01A58E(pc),a0
	move.w	$0(a0,d5.w),d0
	add.w	(a5),d0
	cmp.w	#$96,d0	; general form
	bgt.w	loc_01A54E
	cmp.w	#$FF6A,d0	; general form
	blt.w	loc_01A54E
	move.w	d0,(a5)
loc_01A54E:
	move.w	$2(a0,d5.w),d1
	add.w	$14(a5),d1
	cmp.w	#$13C,d1	; general form
	bgt.w	loc_01A56A
	cmp.w	#$FEC4,d1	; general form
	blt.w	loc_01A56A
	move.w	d1,$14(a5)
loc_01A56A:
	movea.w	a5,a3
	clr.w	$18(a5)
	andi.l	#$FFFFF,(ram_BEAC).w
	ori.l	#$E00000,(ram_BEAC).w
	bsr.w	sub_01A9D6
	jsr	(sub_025926).l
	bra.w	loc_01A3A4
dat_01A58E:
	dc.w	$0000,$0002,$0002,$0002,$0002,$0000,$0002,$FFFE
	dc.w	$0000,$FFFE,$FFFE,$FFFE,$FFFE,$0000,$FFFE,$0002
loc_01A5AE:
	st	$18(a5)
	btst	#5,d1
	beq.w	loc_01A5CA
	btst	#0,(ram_C346).w
	bne.w	loc_01A5CA
	bchg	#1,(ram_C340).w
loc_01A5CA:
	btst	#6,d3
	beq.w	loc_01A600
	btst	#0,(ram_C346).w
	bne.w	loc_01A600
	bsr.w	sub_01A8BC
	bsr.w	sub_01A8BC
	bsr.w	sub_01A8BC
	bsr.w	sub_01A8BC
	jsr	(sub_02698A).l
	jsr	(sub_025926).l
	moveq	#$1,d7
	bclr	#1,(ram_C340).w
loc_01A600:
	btst	#0,(ram_C346).w
	bne.w	loc_01A65A
	btst	#4,d3
	beq.w	loc_01A65A
	btst	#6,d3
	beq.w	loc_01A642
	bclr	#5,(ram_C340).w
	bclr	#5,(ram_C33C).w
	move.l	d0,-(sp)
	move.l	(ram_BEAC).w,d0
	andi.l	#$FFFFF,d0
	ori.l	#$E00000,d0
	move.l	d0,(ram_BEAC).w
	move.l	(sp)+,d0
	bra.w	loc_01A3A4
loc_01A642:
	bsr.w	sub_01A8EE
	jsr	(sub_02698A).l
	jsr	(sub_025926).l
	asl.w	#1,d7
	bclr	#1,(ram_C340).w
loc_01A65A:
	btst	#1,(ram_C340).w
	beq.w	loc_01A67C
	st	(ram_C066).w
	bsr.w	sub_01A8EE
	move.w	(ram_C066).w,-(sp)
	jsr	(sub_09205A).l
	jsr	(sub_02698A).l
loc_01A67C:
	jsr	(sub_025926).l
	btst	#0,(ram_C346).w
	bne.w	loc_01A6AE
	btst	#7,d1
	beq.w	loc_01A3A4
	jsr	(sub_01A824).l
	bclr	#1,(ram_C340).w
	bset	#0,(ram_C346).w
	bne.w	loc_01A6AE
	bra.w	loc_01A3A4
loc_01A6AE:
	btst	#7,d1
	bne.w	loc_01A6F4
	btst	#6,d1
	bne.w	loc_01A6EE
	btst	#4,d1
	bne.w	loc_01A6FE
	btst	#5,d1
	beq.w	loc_01A3A4
	bset	#6,(ram_C344).w
	bclr	#0,(ram_C346).w
	jsr	(sub_01A89E).l
	bsr.w	sub_01A8EE
	jsr	(sub_02698A).l
	bra.w	loc_01A3A4
loc_01A6EE:
	jmp	(loc_01A3A4).l
loc_01A6F4:
	clr.w	(ram_D01A).w
	bset	#1,(ram_C346).w
loc_01A6FE:
	bsr.w	sub_01FFA2
	ori.l	#$F0000000,(ram_BEAC).w
	bclr	#5,(ram_C33C).w
	movea.l	(ram_B050).w,a4
	bclr	#4,(ram_C344).w
	bsr.w	sub_01AA4C
	jsr	(sub_02698A).l
	bclr	#3,(ram_C33E).w
	move.w	(sp)+,(VideoFlags).w
	jsr	(sub_019EE8).l
	jsr	(sub_02668C).l
	jsr	(sub_02669E).l
	jsr	(sub_0266AC).l
	jsr	(sub_0266C8).l
	move.w	#$FFFF,(ram_D2C0).w
	move.w	#$0,d0
	move.w	#$1B24,d1
	movea.l	#Z80_SoundDriver,a0
	jsr	(Sound_Call).l
	move.w	#$9,d0
	jsr	(Sound_Call).l
	move.w	#$6,d0
	clr.w	d1
	movea.l	#SoundBank,a0
	jsr	(Sound_Call).l
	move.w	#$7,d0
	move.w	#$0,d1
	jsr	(Sound_Call).l
	btst	#4,(VideoFlags).w
	beq.w	loc_01A7A6
	jsr	(sub_0266E4).l
	jsr	(sub_0266D6).l
loc_01A7A6:
	jsr	(sub_025926).l
	move.w	#$18,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $01981E, $01A2EA, $01A3F2, $1DD812, $1DDD74, $1DE0E6, $1DE432, $1DF8BA (+2 more)
sub_01A7B4:
	tst.w	(ram_D26E).w
	beq.w	Joypad_Read1
	cmpi.w	#$1,(ram_D26E).w
	beq.w	Joypad_Read2
	cmpi.w	#$2,(ram_D26E).w
	beq.w	Joypad_Read3
	bra.w	Joypad_Read4


; ----------------------------------------------------------------------
; called from $01A35C, $01A984
sub_01A7D4:
	move.w	#$F0,(ram_DCC6).w
	bsr.w	Text_Print
inl_01A7DE:
	dc.w	loc_01A7E4-inl_01A7DE
	dc.b	$BF,$01,$01,$00
loc_01A7E4:
	clr.w	d0
	clr.w	d1
	moveq	#$D,d2
	moveq	#$6,d3
	move.w	(ram_B032).w,d4
	move.w	#$0,d5
	movea.l	#Art_1706CA,a1
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	bra.w	TileMap_Draw


; ----------------------------------------------------------------------
; called from $01A3CA, $01A824
sub_01A806:
	jsr	(Text_Print).l
inl_01A80C:
	dc.w	loc_01A812-inl_01A80C
	dc.b	$BF,$01,$01,$00
loc_01A812:
	move.w	#$D,d0
	move.w	#$6,d1
	move.w	#$7FF,d2
	jmp	(Text_FillRect).l


; ----------------------------------------------------------------------
; called from $01A694
sub_01A824:
	jsr	(sub_01A806).l
	st	(ram_DCC6).w
	bsr.w	Text_Print
inl_01A832:
	dc.w	loc_01A838-inl_01A832
	dc.b	$BF,$02,$00,$00
loc_01A838:
	moveq	#$0,d0
	moveq	#$0,d1
	moveq	#$14,d2
	moveq	#$8,d3
	move.w	(ram_B03C).w,d4
	move.w	#$0,d5
	movea.l	#Art_170DF4,a1
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	bsr.w	TileMap_Draw
	jsr	(Text_PrintScoreboard).l
inl_01A860:
	dc.w	loc_01A880-inl_01A860
	dc.b	$F8,$04,$01,$07,$01
	dc.b	"options"
	dc.b	$FD,$07,$FA,$02
	dc.b	"reverse angle",0
loc_01A880:
	jsr	(Text_PrintScoreboardAlt).l
inl_01A886:
	dc.w	loc_01A89C-inl_01A886
	dc.b	$FD,$05,$FC,$05
	dc.b	"start - to game",0
loc_01A89C:
	rts


; ----------------------------------------------------------------------
; called from $01A6DA
sub_01A89E:
	jsr	(Text_Print).l
inl_01A8A4:
	dc.w	loc_01A8AA-inl_01A8A4
	dc.b	$BF,$02,$00,$00
loc_01A8AA:
	move.w	#$14,d0
	move.w	#$8,d1
	move.w	#$7FF,d2
	jmp	(Text_FillRect).l


; ----------------------------------------------------------------------
; called from $01A376, $01A5DC, $01A5E0, $01A5E4, $01A5E8
sub_01A8BC:
	cmpa.l	#SaveDataMirror,a4
	bne.w	loc_01A8D6
	btst	#4,(ram_C33C).w
	beq.w	loc_01A8E6
	movea.l	#ram_AF64,a4
loc_01A8D6:
	suba.w	#$64,a4
	cmpa.l	(ram_B050).w,a4
	bne.w	sub_01AA4C
	adda.w	#$64,a4
loc_01A8E6:
	bsr.w	sub_01AA4C
	clr.w	d7
	rts


; ----------------------------------------------------------------------
; called from $01A642, $01A668, $01A6E0
sub_01A8EE:
	bclr	#6,(ram_C344).w
	beq.w	loc_01A994
	movem.l	d0-d7/a0-a6,-(sp)
	bchg	#4,(ram_C344).w
	move.w	(ram_BD34).w,-(sp)
	move.w	(ram_BD30).w,-(sp)
	bsr.w	sub_01FFCC
	jsr	(sub_019BF0).l
	jsr	(sub_019BF0).l
	clr.w	(ram_BD34).w
	clr.w	(ram_BD30).w
	move.w	#$7D0,(ram_BD32).w
	move.w	#$1,d0
loc_01A92C:
	jsr	(sub_025926).l
	jsr	(sub_019BF0).l
	dbra	d0,loc_01A92C
	move.w	(sp)+,(ram_BD30).w
	move.w	(sp)+,(ram_BD34).w
	move.w	#$1,d0
	jsr	(sub_025926).l
loc_01A94E:
	jsr	(sub_019BF0).l
	dbra	d0,loc_01A94E
	movem.l	a0,-(sp)
	movea.l	#ram_B660,a0
	move.w	#$1,$8(a0)
	adda.w	#$80,a0
	move.w	#$1,$8(a0)
	movem.l	(sp)+,a0
	bsr.w	sub_01AA3C
	btst	#5,(ram_C33C).w
	beq.w	loc_01A984
loc_01A984:
	jsr	(sub_01A7D4).l
	move.w	#$64,(FadeCounter).w
	movem.l	(sp)+,d0-d7/a0-a6
loc_01A994:
	clr.w	d7
	btst	#2,(ram_C33E).w
	beq.w	loc_01A9B4
	movem.l	a4,-(sp)
	bsr.w	sub_01A9C0
	cmpa.l	(ram_B050).w,a4
	movem.l	(sp)+,a4
	beq.w	loc_01ADDA
loc_01A9B4:
	cmpa.l	(ram_B050).w,a4
	beq.w	loc_01ADDA
	bsr.w	sub_01AA4C

; ----------------------------------------------------------------------
; called from $01A9A4
sub_01A9C0:
	adda.w	#$64,a4
	cmpa.l	#ram_AF64,a4
	bne.w	loc_01ADDA
	movea.l	#SaveDataMirror,a4
	rts


; ----------------------------------------------------------------------
; called from $01A518, $01A580, $01AC5C
sub_01A9D6:
	movem.l	d0-d2,-(sp)
	move.w	(a3),d0
	btst	#7,(ram_C344).w
	beq.w	loc_01A9E8
	neg.w	d0
loc_01A9E8:
	move.w	d0,(a5)
	move.w	$14(a3),d1
	btst	#7,(ram_C344).w
	beq.w	loc_01A9FA
	neg.w	d1
loc_01A9FA:
	move.w	d1,$14(a5)
	cmp.w	#$3C,d0	; general form
	blt.w	loc_01AA0A
	move.w	#$3C,d0
loc_01AA0A:
	cmp.w	#$FFC4,d0	; general form
	bgt.w	loc_01AA16
	move.w	#$FFC4,d0
loc_01AA16:
	move.w	d0,(ram_BD34).w
	cmp.w	#$F8,d1	; general form
	blt.w	loc_01AA26
	move.w	#$F8,d1
loc_01AA26:
	cmp.w	#$FF18,d1	; general form
	bgt.w	loc_01AA32
	move.w	#$FF18,d1
loc_01AA32:
	move.w	d1,(ram_BD30).w
	movem.l	(sp)+,d0-d2
	rts


; ----------------------------------------------------------------------
; called from $01A976
sub_01AA3C:
	btst	#4,(ram_C344).w
	beq.w	sub_01AA4C
	bset	#7,(ram_C344).w

; ----------------------------------------------------------------------
; called from $01A71A, $01A8DE, $01A8E6, $01A9BC, $01AA42
sub_01AA4C:
	movem.l	d0-d2/a0/a6,-(sp)
	movea.l	#dat_1CDDDC,a6
	movea.l	a4,a0
	moveq	#$F,d1
	movea.w	#$B060,a3
loc_01AA5E:
	move.w	$2(a0),d2
	andi.w	#$1FF,d2
	btst	#8,d2
	beq.w	loc_01AA72
	ori.w	#$FE00,d2
loc_01AA72:
	btst	#4,(ram_C344).w
	beq.w	loc_01AA7E
	neg.w	d2
loc_01AA7E:
	move.w	d2,(a3)
	move.l	(a0),d2
	asr.l	#3,d2
	asr.w	#6,d2
	btst	#9,d2
	beq.w	loc_01AA92
	ori.w	#$FC00,d2
loc_01AA92:
	btst	#4,(ram_C344).w
	beq.w	loc_01AAA8
	neg.w	d2
	cmp.w	#$0,d1	; general form
	bne.w	loc_01AAA8
	addq.w	#2,d2
loc_01AAA8:
	move.w	d2,$14(a3)
	move.w	(a0),d2
	asr.w	#3,d2
	andi.w	#$7FF,d2
	btst	#4,(ram_C344).w
	beq.w	loc_01AAFA
	asl.w	#1,d2
	move.w	$0(a6,d2.w),d2
	subq.w	#1,d2
	cmpi.w	#$F,$52(a3)
	bne.w	loc_01AADE
	cmp.w	#$299,d2	; general form
	beq.w	loc_01AADE
	move.w	#$FC00,$14(a3)
loc_01AADE:
	cmp.w	#$1,d2	; general form
	blt.w	loc_01AAF2
	cmp.w	#$7BA,d2	; general form
	bge.w	loc_01AAF2
	bra.w	loc_01AAFA
loc_01AAF2:
	move.w	(a0),d2
	asr.w	#3,d2
	andi.w	#$7FF,d2
loc_01AAFA:
	move.w	d2,$6(a3)
	cmp.w	#$59D,d2	; general form
	blt.w	loc_01AB0E
	cmp.w	#$5B5,d2	; general form
	blt.w	loc_01AB1E
loc_01AB0E:
	cmp.w	#$73A,d2	; general form
	blt.w	loc_01AB2E
	cmp.w	#$73F,d2	; general form
	bge.w	loc_01AB2E
loc_01AB1E:
	btst	#4,(ram_C344).w
	beq.w	loc_01AB2E
	move.w	#$190,$14(a3)
loc_01AB2E:
	btst	#4,(ram_C344).w
	beq.w	loc_01AB4E
	cmp.w	#$213,d2	; general form
	blt.w	loc_01AB4E
	cmp.w	#$222,d2	; general form
	bgt.w	loc_01AB4E
	move.w	#$190,$14(a3)
loc_01AB4E:
	move.w	(a0),d2
	asr.w	#3,d2
	andi.w	#$1800,d2
	andi.w	#$E7FF,$4(a3)
	or.w	d2,$4(a3)
	btst	#4,(ram_C344).w
	beq.w	loc_01AB84
	move.w	$6(a3),d2
	cmp.w	#$5E3,d2	; general form
	blt.w	loc_01AB84
	cmp.w	#$67E,d2	; general form
	bge.w	loc_01AB84
	bchg	#3,$4(a3)
loc_01AB84:
	move.w	$6(a3),d2
	cmp.w	#$213,d2	; general form
	blt.w	loc_01AB9E
	cmp.w	#$222,d2	; general form
	bgt.w	loc_01AB9E
	bclr	#3,$4(a3)
loc_01AB9E:
	addq.w	#4,a0
	adda.w	#$80,a3
	dbra	d1,loc_01AA5E
	moveq	#$5,d2
	movea.w	#$B060,a3
loc_01ABAE:
	move.b	(a0)+,$70(a3)
	move.b	(a0),d0
	andi.w	#$F,d0
	cmp.w	#$F,d0	; general form
	bne.w	loc_01ABC2
	moveq	#-$1,d0
loc_01ABC2:
	move.w	d0,$34(a3)
	adda.w	#$80,a3
	move.b	(a0)+,d0
	lsr.b	#4,d0
	move.b	d0,$70(a3)
	move.b	(a0),d0
	asl.b	#4,d0
	or.b	d0,$70(a3)
	move.b	(a0)+,d0
	lsr.b	#4,d0
	andi.w	#$F,d0
	cmp.w	#$F,d0	; general form
	bne.w	loc_01ABEC
	moveq	#-$1,d0
loc_01ABEC:
	move.w	d0,$34(a3)
	adda.w	#$80,a3
	dbra	d2,loc_01ABAE
	move.b	(a0)+,d0
	ext.w	d0
	move.w	d0,(ram_B778).w
	move.b	(a0)+,d0
	ext.w	d0
	move.w	d0,(ram_B7F8).w
	move.b	(a0)+,d0
	ext.w	d0
	move.w	d0,(ram_C066).w
	clr.w	d7
	move.b	(a0)+,d7
	move.w	(a0)+,d0
	move.w	d0,(ram_BEAE).w
	move.w	(a0)+,(ram_B8B2).w
	move.w	(a0)+,(ram_BF18).w
	move.w	(a0)+,(ram_BF16).w
	move.b	(a0)+,(ram_C3F8).w
	clr.w	d0
	move.b	(a0)+,d0
	ori.w	#$FF00,d0
	move.w	d0,(ram_BEAC).w
	btst	#5,(ram_C33C).w
	beq.w	loc_01AC64
	movea.w	a5,a3
	btst	#5,(ram_C340).w
	beq.w	loc_01AC5C
	clr.w	$18(a5)
	move.w	$16(a5),d0
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
loc_01AC5C:
	bsr.w	sub_01A9D6
	bra.w	loc_01AC84
loc_01AC64:
	move.w	(a0)+,(ram_BD34).w
	move.w	(a0)+,(ram_BD30).w
	btst	#4,(ram_C344).w
	beq.w	loc_01AC84
	neg.w	(ram_BD34).w
	neg.w	(ram_BD30).w
	jsr	(sub_01AC90).l
loc_01AC84:
	bclr	#7,(ram_C344).w
	movem.l	(sp)+,d0-d2/a0/a6
	rts


; ----------------------------------------------------------------------
; called from $01AC7E
sub_01AC90:
	move.w	d0,-(sp)
	move.w	#$3C,d0
	cmp.w	(ram_BD34).w,d0
	blt.w	loc_01ACAA
	move.w	#$FFC4,d0
	cmp.w	(ram_BD34).w,d0
	ble.w	loc_01ACAE
loc_01ACAA:
	move.w	d0,(ram_BD34).w
loc_01ACAE:
	move.w	#$100,d0
	cmp.w	(ram_BD30).w,d0
	blt.w	loc_01ACC6
	move.w	#$FF38,d0
	cmp.w	(ram_BD30).w,d0
	ble.w	loc_01ACCA
loc_01ACC6:
	move.w	d0,(ram_BD30).w
loc_01ACCA:
	move.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $0193FA
sub_01ACCE:
	btst	#4,(ram_C33A).w
	bne.w	loc_01ADDA
	btst	#2,(ram_C33E).w
	beq.w	loc_01ACFA
	tst.w	(ram_DD10).w
	beq.w	loc_01AD1C
	subq.w	#1,(ram_DD10).w
	bpl.w	loc_01ACFA
	clr.w	(ram_DD10).w
	bra.w	loc_01AD1C
loc_01ACFA:
	addi.l	#$64,(ram_B050).w
	cmpi.l	#$FFFFAF64,(ram_B050).w
	bne.w	loc_01AD1C
	bset	#4,(ram_C33C).w
	move.l	#SaveDataMirror,(ram_B050).w
loc_01AD1C:
	movea.l	(ram_B050).w,a0
	moveq	#$F,d2
	movea.w	#$B060,a3
loc_01AD26:
	clr.l	(a0)
	move.w	(a3),d1
	andi.w	#$1FF,d1
	move.w	d1,$2(a0)
	clr.l	d1
	move.w	$14(a3),d1
	asl.w	#6,d1
	asl.l	#3,d1
	or.l	d1,(a0)
	move.w	$6(a3),d1
	asl.w	#3,d1
	or.w	d1,(a0)
	move.w	$4(a3),d1
	andi.w	#$1800,d1
	asl.w	#3,d1
	or.w	d1,(a0)
	addq.w	#4,a0
	adda.w	#$80,a3
	dbra	d2,loc_01AD26
	moveq	#$5,d2
	movea.w	#$B060,a3
loc_01AD62:
	move.b	$70(a3),(a0)+
	move.w	$34(a3),d0
	bpl.w	loc_01AD70
	moveq	#$F,d0
loc_01AD70:
	andi.w	#$F,d0
	move.b	d0,(a0)
	adda.w	#$80,a3
	move.b	$70(a3),d0
	asl.w	#4,d0
	or.b	d0,(a0)+
	move.b	$70(a3),d0
	lsr.b	#4,d0
	move.b	d0,(a0)
	move.w	$34(a3),d0
	bpl.w	loc_01AD94
	moveq	#$F,d0
loc_01AD94:
	asl.w	#4,d0
	or.b	d0,(a0)+
	adda.w	#$80,a3
	dbra	d2,loc_01AD62
	move.b	(ram_B779).w,(a0)+
	move.b	(ram_B7F9).w,(a0)+
	move.b	(ram_C067).w,(a0)+
	bset	#7,(ram_C067).w
	move.b	d7,(a0)+
	move.w	(ram_BEAE).w,(a0)+
	move.w	(ram_B8B2).w,(a0)+
	move.w	(ram_BF16).w,(a0)+
	move.w	(ram_BF18).w,(a0)+
	move.b	(ram_C3F8).w,(a0)+
	move.w	d0,-(sp)
	move.w	(ram_BEAC).w,d0
	move.b	d0,(a0)+
	move.w	(sp)+,d0
	move.w	(ram_BD34).w,(a0)+
	move.w	(ram_BD30).w,(a0)+
loc_01ADDA:
	rts


; ----------------------------------------------------------------------
; called from $0193C8
sub_01ADDC:
	btst	#7,(ram_C33C).w
	bne.w	loc_01AE2A
	ori.l	#$F,(ram_BEAC).w
	cmpi.w	#$5,(ram_B778).w
	bgt.w	loc_01AE00
loc_01ADF8:
	clr.w	(ram_DCE4).w
	bra.w	loc_01AE2A
loc_01AE00:
	move.w	(ram_DCE8).w,d0
	cmp.w	(ram_B778).w,d0
	beq.w	loc_01AE14
	move.w	(ram_B778).w,(ram_DCE8).w
	bra.s	loc_01ADF8
loc_01AE14:
	addq.w	#1,(ram_DCE4).w
	cmpi.w	#$10,(ram_DCE4).w
	blt.w	loc_01AE2A
	clr.w	(ram_DCE4).w
	subq.w	#1,(ram_B778).w
loc_01AE2A:
	bclr	#6,(ram_C34C).w
	move.w	(ram_C376).w,d0
	cmp.w	(ram_C378).w,d0
	blt.w	loc_01AE42
	bset	#6,(ram_C34C).w
loc_01AE42:
	jsr	(sub_1D1D7A).l
	tst.w	(ram_B7C0).w
	bmi.w	loc_01AE7A
	bclr	#7,(ram_C34E).w
	bclr	#1,(TextFlags).w
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a3
	adda.w	d0,a3
	btst	#1,$64(a3)
	beq.w	loc_01AE7A
	bclr	#4,(ram_C34A).w
loc_01AE7A:
	movea.w	#$B060,a3
loc_01AE7E:
	move.l	(a3),$1C(a3)
	move.l	$14(a3),$20(a3)
	move.l	$18(a3),$24(a3)
	btst	#5,$64(a3)
	beq.w	loc_01AF80
	clr.w	$28(a3)
	clr.w	$2A(a3)
	tst.w	$5A(a3)
	bne.w	loc_01AEB2
	jsr	(sub_1D1A16).l
	bra.w	loc_01AF80
loc_01AEB2:
	cmpi.w	#$2142,$58(a3)
	beq.w	loc_01AF72
	cmpi.w	#$2582,$58(a3)
	beq.w	loc_01AF5C
	cmpi.w	#$241E,$58(a3)
	beq.w	loc_01AF30
	cmpi.w	#$236C,$58(a3)
	beq.w	loc_01AEE8
	cmpi.w	#$24D0,$58(a3)
	beq.w	loc_01AF0C
	bra.w	loc_01AF80
loc_01AEE8:
	move.w	#$124,d0
	cmpi.w	#$56,(ram_D308).w
	bgt.w	loc_01AF00
	cmpi.w	#$FFAA,(ram_D308).w
	bgt.w	loc_01AF04
loc_01AF00:
	move.w	#$116,d0
loc_01AF04:
	move.w	d0,$14(a3)
	bra.w	loc_01AF80
loc_01AF0C:
	move.w	#$FEDC,d0
	cmpi.w	#$56,(ram_D308).w
	bgt.w	loc_01AF24
	cmpi.w	#$FFAA,(ram_D308).w
	bgt.w	loc_01AF28
loc_01AF24:
	move.w	#$FEEA,d0
loc_01AF28:
	move.w	d0,$14(a3)
	bra.w	loc_01AF80
loc_01AF30:
	move.w	#$90,(a3)
	btst	#3,$4(a3)
	beq.w	loc_01AF80
	move.w	#$FF70,(a3)
	bra.w	loc_01AF80


; ----------------------------------------------------------------------
sub_01AF46:
	move.w	#$96,(a3)
	btst	#3,$4(a3)
	beq.w	loc_01AF80
	move.w	#$FF6A,(a3)
	bra.w	loc_01AF80
loc_01AF5C:
	move.w	#$FF70,(a3)
	btst	#3,$4(a3)
	beq.w	loc_01AF80
	move.w	#$90,(a3)
	bra.w	loc_01AF80
loc_01AF72:
	move.w	#$FF6A,(a3)
	btst	#3,$4(a3)
	beq.w	loc_01AF80
loc_01AF80:
	tst.w	$34(a3)
	bmi.w	loc_01B144
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01AF9A
	bclr	#1,$64(a3)
loc_01AF9A:
	bsr.w	sub_01B154
	sub.b	d7,$5E(a3)
	bpl.w	loc_01AFAA
	clr.b	$5E(a3)
loc_01AFAA:
	sub.b	d7,$5F(a3)
	bpl.w	loc_01AFB6
	clr.b	$5F(a3)
loc_01AFB6:
	btst	#6,(ram_C340).w
	beq.w	loc_01AFDA
	clr.w	d0
	move.b	$67(a3),d0
	bmi.w	loc_01AFDA
	add.w	d0,d0
	addi.w	#$14C,d0
	jsr	(sub_022566).l
	addq.w	#1,$0(a2,d0.w)
loc_01AFDA:
	cmpi.w	#$18A2,$58(a3)
	blt.w	loc_01AFEE
	cmpi.w	#$2034,$58(a3)
	ble.w	loc_01B0EA
loc_01AFEE:
	move.w	(ram_D2A2).w,d4
	tst.w	(ram_D29E).w
	beq.w	loc_01AFFE
	move.w	(ram_D2A4).w,d4
loc_01AFFE:
	cmpi.w	#$2,(ram_D284).w
	bne.w	loc_01B014
	btst	#3,$62(a3)
	beq.w	loc_01B014
	addq.w	#2,d4
loc_01B014:
	mulu.w	d7,d4
	cmpi.w	#$2C46,$58(a3)
	beq.w	loc_01B0EA
	cmpi.w	#$2C78,$58(a3)
	beq.w	loc_01B0EA
	btst	#7,$64(a3)
	bne.w	loc_01B0EA
	tst.w	$18(a3)
	bne.w	loc_01B072
	moveq	#$6,d2
	btst	#0,$62(a3)
	beq.w	loc_01B04A
	moveq	#$9,d2
loc_01B04A:
	move.w	$28(a3),d0
	beq.w	loc_01B05E
	asr.w	d2,d0
	bne.w	loc_01B05A
	moveq	#$1,d0
loc_01B05A:
	sub.w	d0,$28(a3)
loc_01B05E:
	move.w	$2A(a3),d0
	beq.w	loc_01B072
	asr.w	d2,d0
	bne.w	loc_01B06E
	moveq	#$1,d0
loc_01B06E:
	sub.w	d0,$2A(a3)
loc_01B072:
	move.w	$28(a3),d0
	beq.w	loc_01B07E
	muls.w	d4,d0
	add.l	d0,(a3)
loc_01B07E:
	move.w	$2A(a3),d0
	beq.w	loc_01B08C
	muls.w	d4,d0
	add.l	d0,$14(a3)
loc_01B08C:
	tst.w	$18(a3)
	bmi.w	loc_01B0EA
	bne.w	loc_01B0A0
	tst.w	$2C(a3)
	beq.w	loc_01B0EA
loc_01B0A0:
	asl.w	#1,d4
	sub.w	d4,$2C(a3)
	asl.w	#1,d4
	sub.w	d4,$2C(a3)
	lsr.w	#2,d4
	move.w	$2C(a3),d0
	muls.w	d4,d0
	add.l	d0,$18(a3)
	bpl.w	loc_01B0EA
	clr.l	$18(a3)
	neg.w	$2C(a3)
	asr.w	$2C(a3)
	moveq	#$5,d0
	sub.b	$2C(a3),d0
	bpl.w	loc_01B0D4
	clr.w	d0
loc_01B0D4:
	cmp.w	#$3,d0	; general form
	bhi.w	loc_01B0EA
	clr.w	d0
	addi.w	#$2C,d0
	move.w	d0,-(sp)
	jsr	(sub_09205A).l
loc_01B0EA:
	move.w	$52(a3),d6
	cmp.w	(ram_B7C0).w,d6
	bne.w	loc_01B110
	btst	#0,$63(a3)
	bne.w	loc_01B110
	btst	#7,(ram_C33C).w
	bne.w	loc_01B110
	moveq	#-$2,d4
	bsr.w	sub_01B86A
loc_01B110:
	btst	#0,(ram_C33E).w
	bne.w	loc_01B13E
	tst.w	(ram_D2FE).w
	beq.w	loc_01B13E
	subq.w	#1,(ram_D2FE).w
	beq.w	loc_01B12E
	bpl.w	loc_01B13E
loc_01B12E:
	clr.w	(ram_D2FE).w
	move.w	#$F0F,(ram_BF3C).w
	move.w	#$F0F,(ram_BF3E).w
loc_01B13E:
	jsr	(sub_00CA42).l
loc_01B144:
	adda.w	#$80,a3
	cmpi.w	#$F,-$2E(a3)
	blt.w	loc_01AE7E
	rts


; ----------------------------------------------------------------------
; called from $01AF9A
sub_01B154:
	tst.w	$58(a3)
	bne.w	loc_01B16A
	bclr	#5,$62(a3)
	bclr	#1,$63(a3)
	rts
loc_01B16A:
	movea.l	#dat_0078B4,a0
	adda.w	$58(a3),a0
	move.w	$10(a0),d1
	move.w	$54(a3),d0
	btst	#7,(ram_C33C).w
	beq.w	loc_01B196
	cmpi.w	#$C,$52(a3)
	bge.w	loc_01B196
	subq.w	#2,d0
	andi.w	#$7,d0
loc_01B196:
	btst	#3,$4(a3)
	beq.w	loc_01B1A8
	neg.w	d0
	addq.w	#8,d0
	andi.w	#$7,d0
loc_01B1A8:
	asl.w	#1,d0
	adda.w	$0(a0,d0.w),a0
	move.w	$5A(a3),d0
	move.w	$0(a0,d0.w),d2
	tst.w	$5C(a3)
	bmi.w	loc_01B258
	sub.w	d7,$5C(a3)
	bpl.w	loc_01B266
	btst	#0,(ram_C33A).w
	beq.w	loc_01B1EE
	cmpi.w	#$3434,$58(a3)
	bne.w	loc_01B1EE
	cmpi.w	#$8,$5A(a3)
	bne.w	loc_01B1EE
	move.w	#$2F,-(sp)
	jsr	(sub_09205A).l
loc_01B1EE:
	btst	#4,(ram_C350).w
	beq.w	loc_01B216
	cmpi.w	#$ABC,$58(a3)
	bne.w	loc_01B216
	cmpi.w	#$10,$5A(a3)
	bne.w	loc_01B216
	move.w	#$30,-(sp)
	jsr	(sub_09205A).l
loc_01B216:
	addq.w	#4,$5A(a3)
	addq.w	#4,d0
	tst.w	-$2(a0,d0.w)
	bpl.w	loc_01B258
	cmpi.w	#$39E,$58(a3)
	bne.w	loc_01B234
	bset	#1,(ram_C358).w
loc_01B234:
	clr.w	d0
	clr.w	$5A(a3)
	bclr	#5,$62(a3)
	bclr	#1,$63(a3)
	bclr	#5,$64(a3)
	btst	#0,d1
	bne.w	loc_01B258
	clr.w	$58(a3)
loc_01B258:
	move.w	$2(a0,d0.w),d0
	bpl.w	loc_01B262
	neg.w	d0
loc_01B262:
	move.w	d0,$5C(a3)
loc_01B266:
	sub.b	d7,$66(a3)
	bpl.w	loc_01B284
	clr.b	$66(a3)
	cmp.w	$6(a3),d2
	beq.w	loc_01B284
	move.w	d2,$6(a3)
	move.b	#$4,$66(a3)
loc_01B284:
	rts


; ----------------------------------------------------------------------
; called from $019582, $01E442, $023E14, $1D0DA4, $1E5E6C, $1E5E7E
sub_01B286:
	move.w	(ram_BD30).w,(ram_BFE0).w
	move.w	(ram_BD34).w,(ram_BFDE).w
	bset	#6,(ram_C33C).w
	rts


; ----------------------------------------------------------------------
; called from $00C4C0, $0193F6, $01E130, $1E54C8
sub_01B29A:
	move.w	(ram_BFE0).w,d2
	move.w	(ram_BFDE).w,d3
	btst	#6,(ram_C33C).w
	bne.w	loc_01B312
	movea.w	#$B760,a3
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_01B2FA
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	move.w	d7,d0
	add.w	d0,d0
	btst	#7,$62(a3)
	beq.w	loc_01B2E6
	add.w	d0,(ram_BFE2).w
	cmpi.w	#$32,(ram_BFE2).w
	blt.w	loc_01B2FA
	move.w	#$32,(ram_BFE2).w
	bra.w	loc_01B2FA
loc_01B2E6:
	sub.w	d0,(ram_BFE2).w
	cmpi.w	#$FFCE,(ram_BFE2).w
	bgt.w	loc_01B2FA
	move.w	#$FFCE,(ram_BFE2).w
loc_01B2FA:
	move.w	$2A(a3),d2
	asr.w	#7,d2
	add.w	$14(a3),d2
	add.w	(ram_BFE2).w,d2
	move.w	(a3),d3
	move.w	d2,(ram_BFE0).w
	move.w	d3,(ram_BFDE).w
loc_01B312:
	move.w	d2,d0
	sub.w	(ram_BD30).w,d0
	cmp.w	#$FFF6,d0	; general form
	bge.w	loc_01B336
	move.w	d2,d1
	subi.w	#$FFF6,d1
	cmp.w	#$FF18,d1	; general form
	bgt.w	loc_01B350
	move.w	#$FF18,d1
	bra.w	loc_01B350
loc_01B336:
	cmp.w	#$A,d0	; general form
	ble.w	loc_01B364
	move.w	d2,d1
	subi.w	#$A,d1
	cmp.w	#$F8,d1	; general form
	blt.w	loc_01B350
	move.w	#$F8,d1
loc_01B350:
	sub.w	(ram_BD30).w,d1
	beq.w	loc_01B364
	asr.w	#4,d1
	bne.w	loc_01B360
	addq.w	#1,d1
loc_01B360:
	add.w	d1,(ram_BD30).w
loc_01B364:
	move.w	d3,d0
	sub.w	(ram_BD34).w,d0
	cmp.w	#$FFD8,d0	; general form
	bge.w	loc_01B388
	move.w	d3,d1
	subi.w	#$FFD8,d1
	cmp.w	#$FFC4,d1	; general form
	bge.w	loc_01B3A2
	move.w	#$FFC4,d1
	bra.w	loc_01B3A2
loc_01B388:
	cmp.w	#$28,d0	; general form
	ble.w	loc_01B3B6
	move.w	d3,d1
	subi.w	#$28,d1
	cmp.w	#$3C,d1	; general form
	ble.w	loc_01B3A2
	move.w	#$3C,d1
loc_01B3A2:
	sub.w	(ram_BD34).w,d1
	beq.w	loc_01B3B6
	asr.w	#4,d1
	bne.w	loc_01B3B2
	addq.w	#1,d1
loc_01B3B2:
	add.w	d1,(ram_BD34).w
loc_01B3B6:
	rts


; ----------------------------------------------------------------------
; called from $00D05A, $012F3C, $01E6EC, $01E750, $01E7B6, $01E81C, $021662
sub_01B3B8:
	movem.l	d1/a0,-(sp)
	movea.l	#ram_B060,a0
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	#$5,d1
loc_01B3CA:
	tst.w	$34(a0)
	beq.w	loc_01B3E2
	suba.w	#$80,a0
	dbra	d1,loc_01B3CA
	move.w	#$FFFF,d0
	bra.w	loc_01B3E6
loc_01B3E2:
	move.w	$52(a0),d0
loc_01B3E6:
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $00DE0C, $01F0E8, $1E6236
sub_01B3EC:
	jsr	(sub_0250F4).l
	tst.w	(ram_D280).w
	bne.w	loc_01B412
	subi.w	#$BA,d0
	jsr	(sub_025114).l
	btst	#4,(ram_C34C).w
	beq.w	loc_01B412
	move.w	#$1000,d0
loc_01B412:
	lsr.w	#7,d0
	move.w	d0,d1
	move.w	$54(a3),d2
	asl.w	#2,d2
	movea.l	#dat_01FEB0,a0
	muls.w	$0(a0,d2.w),d0
	muls.w	$2(a0,d2.w),d1
	add.w	d0,$28(a3)
	add.w	d1,$2A(a3)
	rts
loc_01B434:
	jsr	(sub_0250F4).l
	tst.w	(ram_D280).w
	bne.w	loc_01B45A
	subi.w	#$BA,d0
	jsr	(sub_025114).l
	btst	#4,(ram_C34C).w
	beq.w	loc_01B45A
	move.w	#$1000,d0
loc_01B45A:
	lsr.w	#7,d0
	move.w	d0,d1
	move.w	$54(a3),d2
	asl.w	#2,d2
	movea.l	#dat_01FEB0,a0
	muls.w	$0(a0,d2.w),d0
	muls.w	$2(a0,d2.w),d1
	add.w	d0,$28(a3)
	add.w	d1,$2A(a3)
	bset	#5,$62(a3)
	move.w	#$2D90,d1
	bra.w	sub_01F3B2
loc_01B488:
	bset	#5,$62(a3)
	move.w	#$1850,d1
	tst.w	$32(a3)
	beq.w	sub_01F3B2
	movea.w	#$B060,a0
	move.w	$2E(a3),d0
	asl.w	#7,d0
	adda.w	d0,a0
loc_01B4A6:
	bset	#5,$62(a3)
	move.w	#$1850,d1
	tst.w	$32(a3)
	beq.w	loc_01B50E
	btst	#4,$64(a0)
	bne.w	loc_01B4EA
	cmpi.w	#$76,(a0)
	bgt.w	loc_01B4EA
	cmpi.w	#$FF8A,(a0)
	blt.w	loc_01B4EA
	cmpi.w	#$136,$14(a0)
	bgt.w	loc_01B4EA
	cmpi.w	#$FECA,$14(a0)
	blt.w	loc_01B4EA
	bra.w	loc_01B4F2
loc_01B4EA:
	move.w	#$17AC,d1
	bra.w	loc_01B50E
loc_01B4F2:
	move.w	$14(a3),d0
	sub.w	$14(a0),d0
	btst	#7,$62(a3)
	beq.w	loc_01B506
	neg.w	d0
loc_01B506:
	bmi.w	loc_01B50E
	move.w	#$175A,d1
loc_01B50E:
	btst	#3,$62(a0)
	beq.w	sub_01F3B2
	tst.w	$34(a0)
	beq.w	sub_01F3B2
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a0),d0
	bne.w	sub_01F3B2
	move.w	$28(a0),d0
	or.w	$2A(a0),d0
	bne.w	sub_01F3B2
	st	(ram_B7C0).w
	move.b	#$1E,$5E(a0)
	bra.w	sub_01F3B2


; ----------------------------------------------------------------------
; called from $00CEE4, $00D044, $00D56A, $01BCDA, $01BCE4, $01BCF0, $01BCF8, $01E704 (+3 more)
sub_01B546:
	btst	#6,(ram_C346).w
	bne.w	loc_01B6CE
	movem.l	d0-d6/a0/a1,-(sp)
	move.w	(ram_B788).w,d0
	asr.w	#8,d0
	add.w	(ram_B760).w,d0
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	moveq	#$5,d2
	move.w	d4,d3
	moveq	#-$1,d5
	movea.l	#ram_C388,a0
	move.w	$0(a0,d4.w),d6
	movea.w	#$B060,a0
	movea.w	#$C394,a1
	cmpi.w	#$1,$0(a1,d4.w)
	beq.w	loc_01B592
	adda.w	#$300,a0
loc_01B592:
	movea.w	#$C388,a1
loc_01B596:
	tst.w	$34(a0)
	bne.w	loc_01B5BA
	tst.w	(ram_B7C0).w
	bmi.w	loc_01B5BA
	movem.w	d1,-(sp)
	move.w	$52(a0),d1
	cmp.w	$0(a1,d4.w),d1
	movem.w	(sp)+,d1
	beq.w	loc_01B5C2
loc_01B5BA:
	tst.w	$34(a0)
	ble.w	loc_01B68C
loc_01B5C2:
	btst	#2,$63(a0)
	bne.w	loc_01B68C
	movem.w	d1,-(sp)
	move.w	$52(a0),d1
	cmp.w	$0(a1,d4.w),d1
	movem.w	(sp)+,d1
	beq.w	loc_01B5EA
	btst	#3,$62(a0)
	bne.w	loc_01B68C
loc_01B5EA:
	btst	#2,(ram_C342).w
	beq.w	loc_01B61C
	movem.l	d0,-(sp)
	move.w	(ram_D2F2).w,d0
	cmp.w	$52(a0),d0
	movem.l	(sp)+,d0
	beq.w	loc_01B61C
	movem.l	d0,-(sp)
	move.w	(ram_D2F4).w,d0
	cmp.w	$52(a0),d0
	movem.l	(sp)+,d0
	bne.w	loc_01B68C
loc_01B61C:
	movem.w	d1,-(sp)
	move.w	$52(a0),d1
	cmp.w	$0(a1,d4.w),d1
	movem.w	(sp)+,d1
	beq.w	loc_01B63A
	btst	#5,$62(a0)
	bne.w	loc_01B68C
loc_01B63A:
	movem.w	(sp),d0/d1
	sub.w	(a0),d0
	muls.w	d0,d0
	sub.w	$14(a0),d1
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	d5,d0
	bhi.w	loc_01B68C
	btst	#3,$62(a0)
	beq.w	loc_01B684
	move.w	$52(a0),d1
	cmp.w	$0(a1,d4.w),d1
	bne.w	loc_01B68C
	btst	#5,$62(a0)
	beq.w	loc_01B684
	cmpi.w	#$2634,$58(a0)
	beq.w	loc_01B68C
	cmpi.w	#$2786,$58(a0)
	beq.w	loc_01B68C
loc_01B684:
	move.w	$52(a0),d1
	move.l	d0,d5
	move.w	d1,d6
loc_01B68C:
	adda.w	#$80,a0
	dbra	d2,loc_01B596
	tst.l	d5
	bpl.w	loc_01B6B2
	tst.w	$0(a1,d4.w)
	bpl.w	loc_01B6B2
	tst.w	d6
	bpl.w	loc_01B6B2
	addq.w	#4,sp
	pea	(sub_01B6CA).l
	rts
loc_01B6B2:
	addq.w	#4,sp
	pea	(sub_01B6CA).l
	cmp.w	$0(a1,d4.w),d6
	beq.w	loc_01B6D0
	move.w	d6,d0
	jmp	(sub_01B6FA).l


; ----------------------------------------------------------------------
; called from $01B6AA, $01B6B4
sub_01B6CA:
	movem.l	(sp)+,d0-d6/a0/a1
loc_01B6CE:
	rts
loc_01B6D0:
	btst	#5,$62(a3)
	beq.w	loc_01B6DC
	rts
loc_01B6DC:
	tst.w	$34(a3)
	beq.w	loc_01B6EA
	jmp	(loc_01B782).l
loc_01B6EA:
	bset	#5,$62(a3)
	move.w	#$550,d1
	jmp	(sub_01F3B2).l


; ----------------------------------------------------------------------
; called from $01B6C4, $01B756, $01B762, $01B76E, $01B77A
sub_01B6FA:
	movem.l	d0/a0/a1,-(sp)
	movea.l	#ram_C388,a0
	cmp.w	$0(a0,d4.w),d0
	beq.w	loc_01B74A
	movem.w	d0/d1,-(sp)
	subq.w	#6,d0
	move.w	$0(a0,d4.w),d1
	bpl.w	loc_01B722
	movem.w	(sp)+,d0/d1
	bra.w	loc_01B72E
loc_01B722:
	subq.w	#6,d1
	eor.w	d0,d1
	movem.w	(sp)+,d0/d1
	bmi.w	loc_01B750
loc_01B72E:
	asr.w	#1,d4
	movea.l	#ram_C390,a1
	st	$0(a1,d4.w)
	add.w	d4,d4
	move.w	$0(a0,d4.w),d1
	jsr	(sub_01B79C).l
	move.w	d0,$0(a0,d4.w)
loc_01B74A:
	movem.l	(sp)+,d0/a0/a1
	rts
loc_01B750:
	bra.s	loc_01B74A


; ----------------------------------------------------------------------
; called from $00D088, $01E31A, $01E6F4, $024C2E, $024C64, $024C9C, $024CC6, $1CF042 (+1 more)
sub_01B752:
	move.w	d4,-(sp)
	clr.w	d4
	bsr.s	sub_01B6FA
	move.w	(sp)+,d4
	rts


; ----------------------------------------------------------------------
; called from $00D096, $01E32C, $01E75A, $024C3C, $024C72, $024C8E, $024CD4, $1CF04C (+1 more)
sub_01B75C:
	move.w	d4,-(sp)
	move.w	#$2,d4
	bsr.s	sub_01B6FA
	move.w	(sp)+,d4
	rts


; ----------------------------------------------------------------------
; called from $00D0A4, $01E7C0, $024C48, $024C56, $024CAA, $024CE2, $1CF056
sub_01B768:
	move.w	d4,-(sp)
	move.w	#$4,d4
	bsr.s	sub_01B6FA
	move.w	(sp)+,d4
	rts


; ----------------------------------------------------------------------
; called from $00D0AA, $01E826, $024C20, $024C80, $024CB8, $024CF0, $1CF038
sub_01B774:
	move.w	d4,-(sp)
	move.w	#$6,d4
	bsr.w	sub_01B6FA
	move.w	(sp)+,d4
	rts
loc_01B782:
	move.w	#$2228,d1
	tst.w	$34(a3)
	bne.w	loc_01B792
	move.w	#$550,d1
loc_01B792:
	bset	#5,$62(a3)
	bra.w	sub_01F3B2


; ----------------------------------------------------------------------
; called from $01B740
sub_01B79C:
	movem.l	a0,-(sp)
	movea.l	#ram_B060,a0
	tst.w	d1
	blt.w	loc_01B7DE
	cmp.w	#$B,d1	; general form
	bgt.w	loc_01B7DE
	asl.w	#7,d1
	btst	#3,$63(a0,d1.w)
	beq.w	loc_01B7C8
	lsr.w	#7,d1
	move.w	d1,d0
	bra.w	loc_01B830
loc_01B7C8:
	bclr	#3,$62(a0,d1.w)
	btst	#3,$64(a0,d1.w)
	bne.w	loc_01B7DE
	bset	#1,$62(a0,d1.w)
loc_01B7DE:
	tst.w	d0
	blt.w	loc_01B830
	cmp.w	#$B,d0	; general form
	bgt.w	loc_01B830
	move.w	d0,d1
	asl.w	#7,d1
	btst	#2,(ram_C342).w
	bne.w	loc_01B804
	btst	#0,(ram_C34A).w
	beq.w	loc_01B82A
loc_01B804:
	tst.w	$34(a0,d1.w)
	bne.w	loc_01B82A
	btst	#6,$62(a0,d1.w)
	beq.w	loc_01B81E
	tst.w	(ram_D28C).w
	bra.w	loc_01B822
loc_01B81E:
	tst.w	(ram_D28A).w
loc_01B822:
	beq.w	loc_01B82A
	bra.w	loc_01B830
loc_01B82A:
	bset	#3,$62(a0,d1.w)
loc_01B830:
	movem.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $012EB2, $013542, $1CF472
sub_01B836:
	movem.l	d0/d1,-(sp)
	move.w	#$8,d1
	sub.w	$54(a3),d1
	andi.w	#$7,d1
	add.w	d1,d0
	andi.w	#$7,d0
	btst	#3,$4(a3)
	beq.w	loc_01B860
	btst	d0,#$1E
	movem.l	(sp)+,d0/d1
	rts
loc_01B860:
	btst	d0,#$F0
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $00CBEE, $01A514, $01B10C, $01BB94, $1E6212, $1E624C, $1E62B0
sub_01B86A:
	movem.l	d0/d1,-(sp)
	btst	#7,(ram_C350).w
	bne.w	loc_01B882
	btst	#0,(ram_C34A).w
	beq.w	loc_01B898
loc_01B882:
	btst	#3,$62(a3)
	bne.w	loc_01B898
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_01B8B2
loc_01B898:
	moveq	#$2,d0
	add.w	d4,d0
	add.w	d0,d0
	moveq	#-$10,d1
	rol.l	d0,d1
	and.l	d1,(ram_BEAC).w
	clr.l	d1
	move.w	$52(a3),d1
	asl.l	d0,d1
	or.l	d1,(ram_BEAC).w
loc_01B8B2:
	movem.l	(sp)+,d0/d1
loc_01B8B6:
	rts

