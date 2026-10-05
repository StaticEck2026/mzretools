; ============================================================================
; Front end: team select, playoffs, rosters and trades, options, shootout, stats screens, awards, skills challenge
; ROM range $1CED80-$1E672F
; ============================================================================


; ----------------------------------------------------------------------
; called from $01320C
sub_1CED80:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_B774).w,d0
	bpl.w	loc_1CED8E
	neg.w	d0
loc_1CED8E:
	subi.w	#$11E,d0
	bpl.w	loc_1CED98
	neg.w	d0
loc_1CED98:
	swap	d0
	andi.l	#$FFFF0000,d0
	move.w	(ram_B78A).w,d1
	beq.w	loc_1CEE04
	bpl.w	loc_1CEDAE
	neg.w	d1
loc_1CEDAE:
	move.w	(ram_D2A2).w,d2
	tst.w	(ram_D29E).w
	beq.w	loc_1CEDBE
	move.w	(ram_D2A4).w,d2
loc_1CEDBE:
	divu.w	d1,d0
	andi.l	#$FFFF,d0
	divu.w	d2,d0
	tst.w	d0
	bne.w	loc_1CEDD2
	move.w	#$1,d0
loc_1CEDD2:
	move.l	#dat_0A0000,d1
	move.w	d0,d3
	mulu.w	d2,d0
	divu.w	d0,d1
	move.w	d2,d4
	add.w	d2,d2
	add.w	d4,d2
	mulu.w	d3,d2
	cmp.l	#$7FFF,d2	; general form
	blt.w	loc_1CEDF4
	move.w	#$7FFF,d2
loc_1CEDF4:
	add.w	d2,d1
	tst.w	d1
	bpl.w	loc_1CEE00
	move.w	#$7FFF,d1
loc_1CEE00:
	move.w	d1,(ram_B78C).w
loc_1CEE04:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $013314
sub_1CEE0A:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$C,d0
	move.w	(ram_D304).w,d1
	mulu.w	d1,d0
	swap	d0
	andi.l	#$FFFF0000,d0
	jsr	(ISqrt).l
	move.w	d0,(ram_B78C).w
	ext.l	d0
	move.w	#$3,d4
	divu.w	d4,d0
	clr.l	d1
	move.w	(ram_D300).w,d1
	sub.w	(ram_B760).w,d1
	swap	d1
	tst.w	d0
	bne.w	loc_1CEE48
	move.w	#$1,d0
loc_1CEE48:
	divs.w	d0,d1
	move.w	d1,(ram_B788).w
	clr.l	d1
	move.w	(ram_D302).w,d1
	sub.w	(ram_B774).w,d1
	swap	d1
	divs.w	d0,d1
	move.w	d1,(ram_B78A).w
	movea.l	#ram_B760,a3
	move.w	(ram_B78C).w,d0
	jsr	(sub_01EC86).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $0132F8
sub_1CEE76:
	movem.l	d0-d7/a0-a6,-(sp)
	bclr	#2,(TextFlags).w
	tst.w	$34(a3)
	bne.w	loc_1CEE92
	movea.l	#dat_1CEFB0,a0
	bra.w	loc_1CEEC2
loc_1CEE92:
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	bne.w	loc_1CEEA2
	neg.w	d0
loc_1CEEA2:
	bset	#2,(TextFlags).w
	movea.l	#dat_1CEF70,a0
	cmp.w	#$76,d0	; general form
	blt.w	loc_1CEEC2
	movea.l	#dat_1CEF90,a0
	bclr	#2,(TextFlags).w
loc_1CEEC2:
	move.w	$54(a3),d0
	btst	#7,$62(a3)
	bne.w	loc_1CEED6
	addq.w	#4,d0
	andi.w	#$7,d0
loc_1CEED6:
	asl.w	#2,d0
	move.w	$0(a0,d0.w),d1
	move.w	$2(a0,d0.w),d2
	cmpa.l	#dat_1CEF90,a0
	bne.w	loc_1CEF10
	move.w	$14(a3),d0
	bpl.w	loc_1CEEF4
	neg.w	d0
loc_1CEEF4:
	cmp.w	#$A8,d0	; general form
	blt.w	loc_1CEF10
	move.w	(a3),d0
	bpl.w	loc_1CEF04
	neg.w	d0
loc_1CEF04:
	cmp.w	#$37,d0	; general form
	bgt.w	loc_1CEF10
	move.w	#$119,d2
loc_1CEF10:
	btst	#7,$62(a3)
	bne.w	loc_1CEF1E
	neg.w	d1
	neg.w	d2
loc_1CEF1E:
	move.w	#$A,d0
	jsr	(Random).l
	add.w	d0,d1
	move.w	#$A,d0
	jsr	(Random).l
	add.w	d0,d2
	move.w	d1,(ram_D300).w
	tst.w	$34(a3)
	beq.w	loc_1CEF66
	sub.w	(a3),d1
	bmi.w	loc_1CEF5A
	subi.w	#$3C,d1
	bpl.w	loc_1CEF66
	neg.w	d1
	add.w	d1,(ram_D300).w
	bra.w	loc_1CEF66
loc_1CEF5A:
	addi.w	#$3C,d1
	bmi.w	loc_1CEF66
	sub.w	d1,(ram_D300).w
loc_1CEF66:
	move.w	d2,(ram_D302).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1CEF70:
	dc.w	$006E,$00D8,$006E,$00D8,$006E,$00D8,$006E,$00D8
	dc.w	$FF92,$00D8,$FF92,$00D8,$FF92,$00D8,$FF92,$00D8
dat_1CEF90:
	dc.w	$FFFB,$00C5,$FFFB,$00C5,$FFFB,$00C5,$FFFB,$00C5
	dc.w	$FFFB,$00C5,$FFFB,$00C5,$FFFB,$00C5,$FFFB,$00C5
dat_1CEFB0:
	dc.w	$FFFB,$FFE1,$0032,$FFE1,$0032,$FFE1,$0032,$FFE1
	dc.w	$FFFB,$FFE1,$FFCE,$FFE1,$FFCE,$FFE1,$FFCE,$FFE1


; ----------------------------------------------------------------------
; called from $00F68A
sub_1CEFD0:
	bclr	#1,$62(a3)
	beq.w	loc_1CF086
	bset	#3,$64(a3)
	bne.w	loc_1CF086
	move.w	#$2D,(ram_DD12).w
	bclr	#0,(ram_BFB2).w
	bclr	#5,(ram_C34E).w
	clr.w	(ram_BFB2).w
	clr.w	(ram_BFAA).w
	st	(ram_BF14).w
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	$52(a3),d0
	move.w	d0,(ram_BFA8).w
	btst	#3,$62(a3)
	bne.w	loc_1CF060
	tst.w	(ram_DCEA).w
	bmi.w	loc_1CF060
	beq.w	loc_1CF042
	cmpi.w	#$2,(ram_DCEA).w
	beq.w	loc_1CF04C
	cmpi.w	#$4,(ram_DCEA).w
	beq.w	loc_1CF056
	jsr	(sub_01B774).l
	bra.w	loc_1CF060
loc_1CF042:
	jsr	(sub_01B752).l
	bra.w	loc_1CF060
loc_1CF04C:
	jsr	(sub_01B75C).l
	bra.w	loc_1CF060
loc_1CF056:
	jsr	(sub_01B768).l
	bra.w	loc_1CF060
loc_1CF060:
	move.w	d0,-(sp)
	bsr.w	sub_1CF278
	clr.w	$5A(a3)
	jsr	(sub_01F3B2).l
	bset	#5,$62(a3)
	bset	#1,$63(a3)
	move.w	(sp)+,d0
	movem.l	(sp)+,d0-d7/a0-a6
	bra.w	loc_1CF276
loc_1CF086:
	btst	#0,(ram_BFB2).w
	bne.w	loc_1CF0E0
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	cmp.w	#$3C,d0	; general form
	bgt.w	loc_1CF0AA
	cmp.w	#$FFC4,d0	; general form
	bgt.w	loc_1CF0BC
loc_1CF0AA:
	move.w	(ram_B788).w,d1
	eor.w	d1,d0
	bmi.w	loc_1CF0BC
loc_1CF0B4:
	movem.w	(sp)+,d0/d1
	bra.w	loc_1CF0E8
loc_1CF0BC:
	move.w	(ram_B774).w,d0
	sub.w	$14(a3),d0
	cmp.w	#$3C,d0	; general form
	bgt.w	loc_1CF0D4
	cmp.w	#$FFC4,d0	; general form
	bgt.w	loc_1CF0DC
loc_1CF0D4:
	move.w	(ram_B78A).w,d1
	eor.w	d1,d0
	bpl.s	loc_1CF0B4
loc_1CF0DC:
	movem.w	(sp)+,d0/d1
loc_1CF0E0:
	tst.w	(ram_B7C0).w
	bmi.w	loc_1CF0F2
loc_1CF0E8:
	bclr	#7,(ram_C34E).w
	bra.w	loc_1CF270
loc_1CF0F2:
	btst	#0,(ram_C33A).w
	bne.w	loc_1CF270
	movem.l	d0/d1,-(sp)
	btst	#3,(SysFlags).w
	bne.w	loc_1CF232
	cmpi.w	#$10,$5A(a3)
	bge.w	loc_1CF1AC
	btst	#2,(ram_BFB2).w
	bne.w	loc_1CF1AC
	move.w	(a3),d0
	move.w	(ram_B760).w,d1
	sub.w	d1,d0
	bpl.w	loc_1CF12C
	neg.w	d0
loc_1CF12C:
	move.w	$14(a3),d1
	move.w	(ram_B774).w,d2
	sub.w	d2,d1
	bpl.w	loc_1CF13C
	neg.w	d1
loc_1CF13C:
	move.w	(ram_B788).w,d2
	beq.w	loc_1CF14A
	cmp.w	d0,d1
	ble.w	loc_1CF150
loc_1CF14A:
	move.w	(ram_B78A).w,d2
	move.w	d1,d0
loc_1CF150:
	swap	d0
	andi.l	#$FFFF0000,d0
	tst.w	d2
	bpl.w	loc_1CF160
	neg.w	d2
loc_1CF160:
	move.w	(ram_D2A2).w,d1
	tst.w	(ram_D29E).w
	beq.w	loc_1CF170
	move.w	(ram_D2A4).w,d1
loc_1CF170:
	tst.w	d2
	bne.w	loc_1CF17A
	move.w	#$1,d2
loc_1CF17A:
	divu.w	d2,d0
	andi.l	#$FFFF,d0
	divu.w	d1,d0
	move.w	$5A(a3),d2
	lsr.w	#2,d2
	subq.w	#6,d2
	neg.w	d2
	asl.w	#2,d2
	cmp.w	d2,d0
	bgt.w	loc_1CF1A4
	neg.w	$5A(a3)
	addi.w	#$18,$5A(a3)
	bra.w	loc_1CF21C
loc_1CF1A4:
	add.w	d7,(ram_BFAA).w
	bra.w	loc_1CF1D2
loc_1CF1AC:
	bset	#2,(ram_BFB2).w
	btst	#1,(ram_BFB2).w
	bne.w	loc_1CF1D2
	cmpi.w	#$18,$5A(a3)
	bne.w	loc_1CF1D2
	addi.w	#$30,$5C(a3)
	bset	#1,(ram_BFB2).w
loc_1CF1D2:
	btst	#1,(ram_BFB2).w
	beq.w	loc_1CF1F8
	cmpi.w	#$18,$5A(a3)
	ble.w	loc_1CF1F8
	btst	#0,(ram_BFB2).w
	bne.w	loc_1CF1F8
	movem.l	(sp)+,d0/d1
	bra.w	loc_1CF270
loc_1CF1F8:
	btst	#0,(ram_BFB2).w
	beq.w	loc_1CF21C
	cmpi.w	#$18,$5A(a3)
	bne.w	loc_1CF21C
	cmpi.w	#$1,$5C(a3)
	ble.w	loc_1CF21C
	move.w	#$1,$5C(a3)
loc_1CF21C:
	btst	#1,$63(a3)
	bne.w	loc_1CF22E
	movem.l	(sp)+,d0/d1
	bra.w	loc_1CF266
loc_1CF22E:
	move.w	$5A(a3),d0
loc_1CF232:
	movem.l	(sp)+,d0/d1
	btst	#0,(ram_BFB2).w
	beq.w	loc_1CF24A
	bclr	#5,$62(a3)
	bra.w	loc_1CF266
loc_1CF24A:
	nop
	btst	#3,(SysFlags).w
	beq.w	loc_1CF266
	tst.w	(ram_DD12).w
	bmi.w	loc_1CF266
	subq.w	#1,(ram_DD12).w
	bra.w	loc_1CF276
loc_1CF266:
	btst	#1,$63(a3)
	bne.w	loc_1CF276
loc_1CF270:
	jsr	(sub_1D1E04).l
loc_1CF276:
	rts


; ----------------------------------------------------------------------
; called from $1CF062
sub_1CF278:
	btst	#3,(SysFlags).w
	beq.w	loc_1CF28A
	move.w	#$870,d1
	bra.w	loc_1CF2C2
loc_1CF28A:
	move.w	#$1194,d1
	movem.w	d0/d1,-(sp)
	move.w	(a3),d0
	neg.w	d0
	move.w	#$11E,d1
	btst	#7,$62(a3)
	bne.w	loc_1CF2A6
	neg.w	d1
loc_1CF2A6:
	sub.w	$14(a3),d1
	jsr	(sub_01F186).l
	jsr	(sub_1CF46E).l
	movem.w	(sp)+,d0/d1
	beq.w	loc_1CF2C2
	move.w	#$F90,d1
loc_1CF2C2:
	rts


; ----------------------------------------------------------------------
; called from $00CCE8, $00CE52, $00D39C, $01DC58
sub_1CF2C4:
	movem.w	d0/d1,-(sp)
	btst	#3,(SysFlags).w
	bne.w	loc_1CF33A
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_1CF2E2
	neg.w	d0
loc_1CF2E2:
	tst.w	d0
	bpl.w	loc_1CF33A
	bra.w	loc_1CF332


; ----------------------------------------------------------------------
sub_1CF2EC:
	move.w	(ram_BF10).w,d0
	addq.w	#4,d0
	andi.w	#$7,d0
	move.w	$54(a3),d1
	cmp.w	d0,d1
	bra.w	loc_1CF33A

	dc.w	$6700,$0038,$5241,$0241,$0007,$B240,$6700,$002C
	dc.w	$5241,$0241,$0007,$B240,$6700,$0020,$5741,$0241
	dc.w	$0007,$B240,$6700,$0014,$5341,$0241,$0007,$6700
	dc.w	$000A
loc_1CF332:
	move.w	#$0,d0
	bra.w	loc_1CF33E
loc_1CF33A:
	move.w	#$1,d0
loc_1CF33E:
	movem.w	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $024AD6
sub_1CF344:
	btst	#3,(SysFlags).w
	beq.w	loc_1CF3CC
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_BFA8).w,d0
	cmp.w	(ram_C388).w,d0
	beq.w	loc_1CF38C
	cmp.w	(ram_C38A).w,d0
	beq.w	loc_1CF3A0
	cmp.w	(ram_C38C).w,d0
	beq.w	loc_1CF3A8
	cmp.w	(ram_C38E).w,d0
	beq.w	loc_1CF3B0
loc_1CF376:
	move.w	$54(a3),(ram_BF10).w
	andi.w	#$7,(ram_BF10).w
	bset	#4,(SysFlags).w
	bra.w	loc_1CF3B8
loc_1CF38C:
	jsr	(Joypad_Read1).l
loc_1CF392:
	btst	#3,d0
	bne.s	loc_1CF376
	move.w	d0,(ram_BF10).w
	bra.w	loc_1CF3B8
loc_1CF3A0:
	jsr	(Joypad_Read2).l
	bra.s	loc_1CF392
loc_1CF3A8:
	jsr	(Joypad_Read3).l
	bra.s	loc_1CF392
loc_1CF3B0:
	jsr	(Joypad_Read4).l
	bra.s	loc_1CF392
loc_1CF3B8:
	jsr	(sub_0132A0).l
	bclr	#4,(SysFlags).w
	movem.l	(sp)+,d0-d7/a0-a6
	bra.w	loc_1CF3D8
loc_1CF3CC:
	move.w	#$4,(ram_BF10).w
	jsr	(sub_012FA2).l
loc_1CF3D8:
	movem.l	d0/a0,-(sp)
	movea.l	#ram_C732,a0
	btst	#6,$62(a3)
	beq.w	loc_1CF3F0
	lea	$39E(a0),a0
loc_1CF3F0:
	move.w	$52(a3),d0
	addq.w	#1,$14(a0)
	movem.l	d0/a0-a3,-(sp)
	exg	a2,a3
	jsr	(sub_01EA8A).l
	movem.l	(sp)+,d0/a0-a3
	exg	a2,a3
	jsr	(sub_01EBAC).l
	exg	a2,a3
	clr.w	d0
	move.b	$67(a3),d0
	move.w	$1A(a0),$1C(a0)
	move.w	$18(a0),$1A(a0)
	move.w	d0,$18(a0)
	bset	#7,(ram_C34E).w
	addi.w	#$96,(ram_B8B4).w
	addi.w	#$A,(ram_B8BA).w
	btst	#3,(SysFlags).w
	beq.w	loc_1CF448
	bra.w	loc_1CF44C
loc_1CF448:
	addq.w	#1,$396(a0)
loc_1CF44C:
	movem.l	(sp)+,d0/a0
	bset	#0,(ram_BFB2).w
	btst	#3,(SysFlags).w
	bne.w	loc_1CF46C
	bset	#1,$63(a3)
	bset	#1,(TextFlags).w
loc_1CF46C:
	rts


; ----------------------------------------------------------------------
; called from $1CF2B0
sub_1CF46E:
	movem.w	d0,-(sp)
	jsr	(sub_01B836).l
	movem.w	(sp)+,d0
	rts

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $019128
sub_1CF480:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_C3AC).w,d1
	ext.l	d1
	movea.l	#ram_D14C,a0
	move.w	#$50,d0
	move.w	d0,(ram_C378).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $025964
sub_1CF49E:
	btst	#7,(ram_C33C).w
	bne.w	loc_1CF56A
	btst	#0,(ram_C34A).w
	bne.w	loc_1CF56A
	btst	#0,(ram_C340).w
	bne.w	loc_1CF4DA
	btst	#7,(ram_C346).w
	bne.w	loc_1CF504
	tst.w	(ram_C36C).w
	beq.w	loc_1CF4DC
	subq.w	#1,(ram_C36C).w
	bpl.w	loc_1CF56A
	clr.w	(ram_C36C).w
loc_1CF4DA:
	rts
loc_1CF4DC:
	move.w	(ram_C378).w,d0
	move.w	d0,(ram_C37A).w
	subi.w	#$B,(ram_C37A).w
	subi.w	#$49,d0
	muls.w	d0,d0
	asr.l	#2,d0
	addq.w	#6,d0
	cmp.w	(ram_B8BA).w,d0
	bgt.w	loc_1CF56A
	bset	#7,(ram_C346).w
	rts
loc_1CF504:
	move.w	(ram_C37A).w,d0
	subi.w	#$41,d0
	muls.w	d0,d0
	asr.l	#2,d0
	cmp.w	(ram_B8BA).w,d0
	blt.w	loc_1CF51E
	bclr	#7,(ram_C346).w
loc_1CF51E:
	sub.w	d7,(ram_C36E).w
	bpl.w	loc_1CF56A
	move.w	#$14,(ram_C36E).w
	addq.w	#1,(ram_C370).w
	move.w	(ram_B8BA).w,d0
	ext.l	d0
	asl.w	#2,d0
	jsr	(ISqrt).l
	addi.w	#$41,d0
	move.w	d0,(ram_C376).w
	cmp.w	(ram_C37C).w,d0
	ble.w	loc_1CF552
	move.w	d0,(ram_C37C).w
loc_1CF552:
	move.w	(ram_C376).w,d0
	cmp.w	(ram_C378).w,d0
	blt.w	loc_1CF562
	bra.w	loc_1CF562
loc_1CF562:
	movem.l	d0-d7/a0-a6,-(sp)
	movem.l	(sp)+,d0-d7/a0-a6
loc_1CF56A:
	rts


; ----------------------------------------------------------------------
; called from $01F9A0, $01F9AA, $01FA9A, $01FE22, $01FE60
sub_1CF56C:
	tst.w	$28(a3)
	bpl.w	loc_1CF582
	addi.w	#$7D0,$28(a3)
	bmi.w	loc_1CF590
	clr.w	$28(a3)
loc_1CF582:
	subi.w	#$7D0,$28(a3)
	bpl.w	loc_1CF590
	clr.w	$28(a3)
loc_1CF590:
	tst.w	$2A(a3)
	bpl.w	loc_1CF5A6
	addi.w	#$7D0,$2A(a3)
	bmi.w	loc_1CF5B4
	clr.w	$2A(a3)
loc_1CF5A6:
	subi.w	#$7D0,$2A(a3)
	bpl.w	loc_1CF5B4
	clr.w	$2A(a3)
loc_1CF5B4:
	rts


; ----------------------------------------------------------------------
; called from $1CFA88
sub_1CF5B6:
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
	bgt.w	loc_1CF5F4
	cmp.w	d4,d2
	blt.w	loc_1CF60E
	neg.w	d4
	cmp.w	d4,d2
	bgt.w	loc_1CF60E
	bra.w	loc_1CF642
loc_1CF5F4:
	neg.w	d5
	cmp.w	d5,d3
	blt.w	loc_1CF642
	cmp.w	d4,d2
	blt.w	loc_1CF60E
	neg.w	d4
	cmp.w	d4,d2
	bgt.w	loc_1CF60E
	bra.w	loc_1CF642
loc_1CF60E:
	sub.w	d4,d2
	sub.w	d5,d3
	move.w	d3,d0
	move.w	d2,d1
	neg.w	d1
	muls.w	d3,d3
	muls.w	d2,d2
	add.l	d2,d3
	cmp.l	#dat_001000,d3	; general form
	bls.w	loc_1CF642
	exg	d0,d3
	jsr	(ISqrt).l
	exg	d0,d3
	ext.l	d0
	asl.l	#8,d0
	divs.w	d3,d0
	ext.l	d1
	asl.l	#8,d1
	divs.w	d3,d1
	bsr.w	sub_1CF67C
loc_1CF642:
	movem.w	(sp)+,d2-d5
	move.w	$4E(a3),d0
	or.w	$50(a3),d0
	bne.w	loc_1CF67A
	move.w	#$100,d0
	clr.w	d1
	cmp.w	d5,d3
	bge.w	sub_1CF67C
	neg.w	d5
	neg.w	d0
	cmp.w	d5,d3
	ble.w	sub_1CF67C
	exg	d0,d1
	cmp.w	d4,d2
	bge.w	sub_1CF67C
	neg.w	d4
	neg.w	d1
	cmp.w	d4,d2
	ble.w	sub_1CF67C
loc_1CF67A:
	rts


; ----------------------------------------------------------------------
; called from $1CF63E, $1CF65A, $1CF664, $1CF66C, $1CF676
sub_1CF67C:
	jmp	(sub_0242E4).l


; ----------------------------------------------------------------------
; called from $015EAA, $015EB6, $01906C, $019078
sub_1CF682:
	movem.l	d0-d7,-(sp)
	move.w	#$1BF,d1
loc_1CF68A:
	move.w	#$9,d0
	jsr	(sub_0200EA).l
	move.l	a0,-(sp)
	adda.l	#$1BC,a0
	move.b	d0,$0(a0,d1.w)
	movea.l	(sp)+,a0
	dbra	d1,loc_1CF68A
	movem.l	(sp)+,d0-d7
	rts


; ----------------------------------------------------------------------
sub_1CF6AC:
	tst.w	d3
	bpl.w	loc_1CF6B6
	clr.w	d3
	rts
loc_1CF6B6:
	cmp.w	#$64,d3	; general form
	ble.w	loc_1CF6C2
	move.w	#$64,d3
loc_1CF6C2:
	rts


; ----------------------------------------------------------------------
; called from $0255A6, $0255BC, $0255D4, $02560A, $02563E, $025654, $0256D0, $0256F8 (+4 more)
sub_1CF6C4:
	movem.l	d0-d2/a1,-(sp)
	move.w	(ram_BF4A).w,d1
	movea.l	#ram_C732,a1
	btst	#6,$62(a3)
	beq.w	loc_1CF6E2
	adda.l	#loc_00039E,a1
loc_1CF6E2:
	clr.w	d1
	move.b	$67(a3),d1
	asl.w	#4,d1
	adda.l	#$1BC,a1
	move.b	$0(a1,d1.w),d1
	ext.w	d1
	ext.l	d1
	divs.w	#$3,d1
	move.w	d3,-(sp)
	asl.w	#2,d3
	add.w	(sp)+,d3
	add.w	d1,d3
	bmi.w	loc_1CF718
	cmp.w	#$1E,d3	; general form
	blt.w	loc_1CF71A
	move.w	#$1E,d3
	bra.w	loc_1CF71A
loc_1CF718:
	clr.w	d3
loc_1CF71A:
	andi.w	#$FF,d3
	movem.l	(sp)+,d0-d2/a1
	rts


; ----------------------------------------------------------------------
sub_1CF724:
	movem.l	d0/a0,-(sp)
	movea.l	#ram_BF9A,a0
	move.w	(ram_BF92).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	cmpi.w	#$0,(ram_BF92).w
	bge.w	loc_1CF746
	addq.w	#1,(ram_BF92).w
loc_1CF746:
	movem.l	(sp)+,d0/a0
	movea.l	#ram_C732,a1
	rts


; ----------------------------------------------------------------------
sub_1CF752:
	movem.l	d0/a0,-(sp)
	movea.l	#ram_BF98,a0
	move.w	(ram_BF90).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	cmpi.w	#$0,(ram_BF90).w
	bge.w	loc_1CF774
	addq.w	#1,(ram_BF90).w
loc_1CF774:
	movem.l	(sp)+,d0/a0
	movea.l	#ram_CAD0,a1
	rts

	dc.b	$4E,$75


; ----------------------------------------------------------------------
sub_1CF782:
	clr.w	(ram_BF90).w
	clr.w	(ram_BF92).w
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a0
	bsr.w	sub_1CF7D0
	movea.l	#ram_BF9A,a0
	bsr.w	sub_1CF8C0
	movea.l	#ram_BF9E,a0
	bsr.w	sub_1CF8E0
	movea.l	#ram_CAD0,a0
	bsr.w	sub_1CF7D0
	movea.l	#ram_BF98,a0
	bsr.w	sub_1CF8C0
	movea.l	#ram_BF9C,a0
	bsr.w	sub_1CF8E0
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1CF794, $1CF7B2, $1CF964
sub_1CF7D0:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	a0,a2
	adda.l	#$1BC,a2
	move.w	d7,-(sp)
	move.w	$28(a0),d7
	jsr	(sub_012878).l
	move.w	(sp)+,d7
	movea.l	#ram_BF56,a1
	move.w	#$5,d0
loc_1CF7F4:
	move.b	(a0)+,d1
	subq.b	#1,d1
	move.b	d1,(a1)+
	ext.w	d1
	asl.w	#4,d1
	clr.b	(a1)
	addq.w	#3,d1
	move.w	#$3,d7
loc_1CF806:
	clr.w	d2
	move.b	$0(a2,d1.w),d2
	cmp.b	#$9,d7	; general form
	beq.w	loc_1CF81E
	cmp.b	#$D,d7	; general form
	beq.w	loc_1CF81E
	add.b	d2,(a1)
loc_1CF81E:
	addq.w	#1,d1
	addq.w	#1,d7
	cmp.b	#$10,d7	; general form
	bne.s	loc_1CF806
	tst.b	(a1)+
	dbra	d0,loc_1CF7F4
loc_1CF82E:
	movea.l	#ram_BF56,a1
	clr.w	d1
	move.w	#$4,d0
loc_1CF83A:
	move.b	$3(a1),d6
	cmp.b	$1(a1),d6
	ble.w	loc_1CF852
	st	d1
	move.w	$2(a1),d2
	move.w	(a1),$2(a1)
	move.w	d2,(a1)
loc_1CF852:
	tst.w	(a1)+
	dbra	d0,loc_1CF83A
	tst.w	d1
	bne.s	loc_1CF82E
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1CF862:
	movem.l	d0/a0,-(sp)
	movea.l	#ram_BF9E,a0
	move.w	(ram_BF96).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	cmpi.w	#$0,(ram_BF96).w
	bge.w	loc_1CF884
	addq.w	#1,(ram_BF96).w
loc_1CF884:
	movem.l	(sp)+,d0/a0
	movea.l	#ram_C732,a1
	rts


; ----------------------------------------------------------------------
sub_1CF890:
	movem.l	d0/a0,-(sp)
	movea.l	#ram_BF9C,a0
	move.w	(ram_BF94).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d1
	cmpi.w	#$0,(ram_BF94).w
	bge.w	loc_1CF8B2
	addq.w	#1,(ram_BF94).w
loc_1CF8B2:
	movem.l	(sp)+,d0/a0
	movea.l	#ram_CAD0,a1
	rts

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $1CF79E, $1CF7BC
sub_1CF8C0:
	movem.l	d0/d1/a0/a1,-(sp)
	movea.l	#ram_BF56,a1
	move.w	#$0,d0
loc_1CF8CE:
	clr.b	(a0)+
	move.b	(a1),d1
	move.b	d1,(a0)+
	tst.w	(a1)+
	dbra	d0,loc_1CF8CE
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1CF7A8, $1CF7C6
sub_1CF8E0:
	movem.l	d0/a0/a1,-(sp)
	movea.l	#ram_BF60,a1
	move.w	#$0,d0
loc_1CF8EE:
	clr.b	(a0)+
	move.b	(a1),(a0)+
	tst.w	-(a1)
	dbra	d0,loc_1CF8EE
	movem.l	(sp)+,d0/a0/a1
	rts


; ----------------------------------------------------------------------
sub_1CF8FE:
	movem.l	d1-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a0
	bsr.w	sub_1CF964
	move.w	d1,(ram_BF48).w
	movea.l	#ram_CAD0,a0
	bsr.w	sub_1CF964
	move.w	d1,(ram_BF4A).w
	move.w	(ram_BF48).w,d1
	move.w	(ram_BF4A).w,d2
	sub.w	d1,d2
	move.w	#$0,(ram_BF88).w
	tst.w	d2
	bmi.w	loc_1CF93A
	move.w	#$1,(ram_BF88).w
loc_1CF93A:
	tst.w	d2
	bpl.w	loc_1CF942
	neg.w	d2
loc_1CF942:
	move.w	#$FFFF,d0
	cmp.w	#$5E,d2	; general form
	blt.w	loc_1CF95E
	move.w	#$22,d0
	cmp.w	#$BD,d2	; general form
	blt.w	loc_1CF95E
	move.w	#$23,d0
loc_1CF95E:
	movem.l	(sp)+,d1-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1CF908, $1CF916
sub_1CF964:
	bsr.w	sub_1CF7D0
	move.w	#$6,d0
	movea.l	#ram_BF56,a0
	clr.w	d1
loc_1CF974:
	move.b	$1(a0),d2
	ext.w	d2
	add.w	d2,d1
	tst.w	(a0)+
	dbra	d0,loc_1CF974
	rts

	dc.w	$4E75,$4E75,$48E7,$FF00,$08B8,$0000,$D31E,$6700
	dc.w	$00A2,$08B8,$0006,$D31E,$08B8,$0007,$D31E,$4EB9
	dc.w	$0002,$0BDE,$0006,$EF00,$0000,$31FC,$0005,$B044
	dc.w	$7008,$7208,$343C,$07FF,$0838,$0001,$D31E,$6700
	dc.w	$003C,$31FC,$0003,$B042,$4EB9,$0002,$09C6,$4EB9
	dc.w	$0002,$0BDE,$0006,$FF00,$0000


; ----------------------------------------------------------------------
sub_1CF9DE:
	move.w	#$B,(TextX).w
	move.w	#$5,(TextY).w
	move.w	#$19,d0
	move.w	#$8,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	bra.w	loc_1CFA36

	dc.w	$31FC,$001C,$B042,$4EB9,$0002,$09C6,$4EB9,$0002
	dc.w	$0BDE,$0006,$FF00,$0000


; ----------------------------------------------------------------------
sub_1CFA18:
	move.w	#$3,(TextX).w
	move.w	#$5,(TextY).w
	move.w	#$19,d0
	move.w	#$8,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
loc_1CFA36:
	movem.l	(sp)+,d0-d7
	rts


; ----------------------------------------------------------------------
sub_1CFA3C:
	move.w	#$AA,(ram_D32C).w
	btst	#5,(ram_D31E).w
	beq.w	loc_1CFA52
	move.w	#$53,(ram_D32C).w
loc_1CFA52:
	rts


; ----------------------------------------------------------------------
; called from $0230E8, $0235CC
sub_1CFA54:
	tst.w	$34(a2)
	beq.w	loc_1CFA98
	movem.l	d0-d7,-(sp)
	move.w	(a2),d2
	move.w	$14(a2),d3
	move.w	$4A(a2),(ram_BD3A).w
	addi.w	#$17,(ram_BD3A).l
	move.w	$4C(a2),(ram_BD3C).w
	addi.w	#$17,(ram_BD3C).l
	movem.l	a0-a6,-(sp)
	exg	a2,a3
	jsr	(sub_1CF5B6).l
	exg	a2,a3
	movem.l	(sp)+,a0-a6
	movem.l	(sp)+,d0-d7
loc_1CFA98:
	rts


; ----------------------------------------------------------------------
; called from $0193F0
sub_1CFA9A:
	bclr	#5,(TextFlags).w
	tst.w	(ram_B7C0).w
	bmi.w	loc_1CFAEC
	movem.l	d0/a0,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	$14(a0),d0
	btst	#7,$62(a0)
	bne.w	loc_1CFACA
	neg.w	d0
loc_1CFACA:
	cmp.w	#$76,d0	; general form
	blt.w	loc_1CFAE8
	cmpi.w	#$51,(a0)
	bgt.w	loc_1CFAE8
	cmpi.w	#$FFAF,(a0)
	blt.w	loc_1CFAE8
	bset	#5,(TextFlags).w
loc_1CFAE8:
	movem.l	(sp)+,d0/a0
loc_1CFAEC:
	rts

	incbin	"data/bin/data_1CFAEE.bin"	; 1792 bytes


; ----------------------------------------------------------------------
; called from $1D0786
sub_1D01EE:
	movem.l	d0,-(sp)
	move.w	(a1),d0
	subq.w	#1,d0
loc_1D01F6:
	move.b	(a1)+,(a3)+
	dbra	d0,loc_1D01F6
	movem.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
sub_1D0202:
	movem.w	d0-d6/a0,-(sp)
	move.l	a1,-(sp)
	move.w	d0,d6
	addq.l	#2,a1
	clr.w	d1
	ext.l	d0
	divu.w	#$64,d0
	tst.w	d0
	beq.w	loc_1D0222
	addi.w	#$30,d0
	move.b	d0,(a1)+
	addq.w	#1,d1
loc_1D0222:
	swap	d0
	ext.l	d0
	divu.w	#$A,d0
	addi.w	#$30,d0
	cmp.b	#$30,d0	; general form
	bne.w	loc_1D023E
	cmp.w	#$A,d6	; general form
	blt.w	loc_1D0242
loc_1D023E:
	move.b	d0,(a1)+
	addq.w	#1,d1
loc_1D0242:
	swap	d0
	addi.w	#$30,d0
	move.b	d0,(a1)+
	addq.w	#1,d1
	btst	#0,d1
	beq.w	loc_1D025A
	move.b	#$0,(a1)+
	addq.w	#1,d1
loc_1D025A:
	movea.l	(sp)+,a0
	addq.w	#2,d1
	move.w	d1,(a0)
	movem.w	(sp)+,d0-d6/a0
	rts


; ----------------------------------------------------------------------
; called from $1D0610
sub_1D0266:
	bclr	#6,(TextFlags).w
loc_1D026C:
	movem.l	d0/d1/a0/a1,-(sp)
	move.l	d1,d0
	asl.w	#4,d0
	addi.l	#$F35,d0
	moveq	#$10,d1
	btst	#6,(TextFlags).w
	beq.w	loc_1D0290
	jsr	(SRAM_Write).l
	bra.w	loc_1D0296
loc_1D0290:
	jsr	(SRAM_Read).l
loc_1D0296:
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1D06D2
sub_1D029C:
	bset	#6,(TextFlags).w
	bra.s	loc_1D026C


; ----------------------------------------------------------------------
; called from $1E1B80
sub_1D02A4:
	bset	#6,(TextFlags).w
	bra.w	loc_1D02B4


; ----------------------------------------------------------------------
; called from $1DF888, $1E1448
sub_1D02AE:
	bclr	#6,(TextFlags).w
loc_1D02B4:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$80,d1
	move.l	#$FB5,d0
	movea.l	#ram_D34A,a0
	btst	#6,(TextFlags).w
	beq.w	loc_1D02DE
	jsr	(SRAM_Write).l
	bra.w	loc_1D02E4
loc_1D02DE:
	jsr	(SRAM_Read).l
loc_1D02E4:
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$001C,$0038,$0054,$0070,$008C,$00A8,$00C4,$00E0
	dc.w	$00FC,$0118,$0134,$0150,$016C,$0188,$01A4,$01C0
	dc.w	$01DC,$01F8,$0214,$0230,$024C,$0268,$0284,$02A0
	dc.w	$02BC,$02D8,$02F4,$0310,$032C


; ----------------------------------------------------------------------
; called from $02261C
sub_1D0324:
	tst.w	(ram_D348).w
	bmi.w	loc_1D039E
	tst.w	(ram_D27C).w
	bne.w	loc_1D039E
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D06DC
	bsr.w	sub_1D0706
	movea.l	#ram_D14C,a0
	move.w	(ram_D264).w,d1
	ext.l	d1
	move.w	(ram_D266).w,d2
	move.w	(ram_C3AC).w,d3
	move.w	(ram_C3AE).w,d4
	movea.l	#ram_C732,a1
	movea.l	#ram_CAD0,a2
	bsr.w	sub_1D060C
	movea.l	#ram_D14C,a0
	move.w	(ram_D266).w,d1
	ext.l	d1
	move.w	(ram_D264).w,d2
	move.w	(ram_C3AE).w,d3
	move.w	(ram_C3AC).w,d4
	movea.l	#ram_CAD0,a1
	movea.l	#ram_C732,a2
	bsr.w	sub_1D060C
	bsr.w	sub_1D03A0
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
loc_1D039E:
	rts


; ----------------------------------------------------------------------
; called from $1D0390
sub_1D03A0:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_1D2488).l
	clr.w	-(sp)
loc_1D03AC:
	move.w	(sp)+,d0
	cmp.w	#$4,d0	; general form
	bge.w	loc_1D054E
	move.w	d0,-(sp)
	addq.w	#1,(sp)
	lea	(ram_C394).w,a2
	lsl.w	#1,d0
	move.w	$0(a2,d0.w),d3
	ble.s	loc_1D03AC
	subq.w	#1,d3
	lea	(ram_D264).w,a2
	lsl.w	#1,d3
	move.w	$0(a2,d3.w),d2
	ble.s	loc_1D03AC
	move.w	d2,-(sp)
	lea	(ram_DE40).w,a2
	lea	($200000).l,a0
	subq.w	#1,d2
	lsl.w	#5,d2
	move.w	#$20,d0
	lsr.w	#1,d3
	mulu.w	#$1E,d3
	lea	$0(a2,d3.w),a2
	lea	(a2),a1
	move.w	#$99A8,d1
	jsr	(sub_1D0554).l
	lea	$2(a2),a1
	move.w	#$9A88,d1
	jsr	(sub_1D0554).l
	lea	(a2),a1
	lea	$2(a2),a3
	move.w	#$9B68,d1
	move.w	#$9C48,d3
	jsr	(sub_1D0590).l
	lea	$6(a2),a1
	move.w	#$9D28,d1
	jsr	(sub_1D0554).l
	lea	$8(a2),a1
	move.w	#$9E08,d1
	jsr	(sub_1D0554).l
	lea	$6(a2),a1
	lea	$8(a2),a3
	move.w	#$9FC8,d1
	move.w	#$A0A8,d3
	jsr	(sub_1D0590).l
	lea	$A(a2),a1
	move.w	#$9EE8,d1
	jsr	(sub_1D0554).l
	lea	$C(a2),a1
	move.w	#$A188,d1
	jsr	(sub_1D0554).l
	lea	$E(a2),a1
	lea	$10(a2),a3
	move.w	#$A268,d1
	move.w	#$A348,d3
	jsr	(sub_1D0590).l
	lea	$14(a2),a1
	move.w	#$A428,d1
	jsr	(sub_1D0554).l
	lea	$16(a2),a1
	move.w	#$A508,d1
	jsr	(sub_1D0554).l
	lea	$18(a2),a1
	move.w	#$A5E8,d1
	jsr	(sub_1D0554).l
	lea	$1A(a2),a3
	lea	$1C(a2),a1
	move.w	#$A6C8,d3
	move.w	#$A7A8,d1
	jsr	(sub_1D0590).l
	move.w	#$10,d0
	lsr.w	#1,d2
	move.w	d2,-(sp)
	move.w	#$A888,d1
	add.w	d2,d1
	jsr	(sub_1DFEF0).l
	cmp.w	$12(a2),d1
	bgt.w	loc_1D04E4
	move.w	$12(a2),d1
loc_1D04E4:
	move.w	#$10,d0
	move.w	(sp)+,d2
	addi.w	#$A888,d2
	lea	($200000).l,a0
	jsr	(sub_1E0012).l
	move.w	#$10,d0
	move.w	#$A8F8,d1
	lea	($200000).l,a0
	jsr	(sub_1DFEF0).l
	clr.l	d2
	move.w	(sp)+,d2
	tst.w	$4(a2)
	bmi.w	loc_1D054A
	andi.l	#$1FFF,d1
	beq.w	loc_1D052C
	cmp.w	$4(a2),d1
	ble.w	loc_1D054A
loc_1D052C:
	move.w	$4(a2),d1
	ror.w	#3,d2
	or.w	d1,d2
	move.w	#$10,d0
	move.w	#$A8F8,d1
	exg	d1,d2
	lea	($200000).l,a0
	jsr	(sub_1E0012).l
loc_1D054A:
	bra.w	loc_1D03AC
loc_1D054E:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D03F8, $1D0406, $1D0428, $1D0436, $1D045A, $1D0468, $1D048C, $1D049A (+1 more)
sub_1D0554:
	movem.l	d0/d2-d7/a0-a6,-(sp)
	move.w	d1,-(sp)
	move.w	d2,-(sp)
	add.w	d2,d1
	jsr	(sub_1DFEF0).l
	cmp.w	(a1),d1
	bge.w	loc_1D0588
	clr.l	d1
	move.w	(a1)+,d1
	lea	($200000).l,a0
	move.w	(sp)+,d2
	add.w	(sp)+,d2
	move.w	#$20,d0
	jsr	(sub_1E0012).l
	movem.l	(sp)+,d0/d2-d7/a0-a6
	rts
loc_1D0588:
	addq.l	#4,sp
	movem.l	(sp)+,d0/d2-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D041A, $1D044C, $1D047E, $1D04BE
sub_1D0590:
	movem.l	d0/d2-d7/a0-a6,-(sp)
	move.w	d1,-(sp)
	move.w	d2,-(sp)
	move.w	d3,-(sp)
	add.w	d2,d1
	jsr	(sub_1DFEF0).l
	move.l	d1,d3
	move.w	(sp),d1
	add.w	$2(sp),d1
	jsr	(sub_1DFEF0).l
	move.l	d3,d4
	move.l	d1,d5
	jsr	(sub_1E057A).l
	move.l	d4,d3
	move.w	(a1),d4
	move.w	(a3),d5
	jsr	(sub_1E057A).l
	cmp.l	d4,d3
	bge.w	loc_1D0604
	lea	($200000).l,a0
	clr.l	d2
	move.w	(sp)+,d2
	add.w	(sp),d2
	move.w	#$20,d0
	clr.l	d1
	move.w	(a3),d1
	jsr	(sub_1E0012).l
	lea	($200000).l,a0
	move.w	(sp)+,d2
	add.w	(sp)+,d2
	move.w	#$20,d0
	clr.l	d1
	move.w	(a1),d1
	jsr	(sub_1E0012).l
	movem.l	(sp)+,d0/d2-d7/a0-a6
	rts
loc_1D0604:
	addq.l	#6,sp
	movem.l	(sp)+,d0/d2-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D0364, $1D038C
sub_1D060C:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D0266
	st	d7
	movem.w	d0,-(sp)
	clr.w	d0
	move.b	$A(a0),d0
	lsl.w	#8,d0
	move.b	$B(a0),d0
	cmp.w	#$2328,d0	; general form
	bge.w	loc_1D067E
	addq.w	#1,d0
	move.b	d0,$B(a0)
	lsr.w	#8,d0
	move.b	d0,$A(a0)
	move.w	$C(a1),d0
	cmp.w	$C(a2),d0
	bgt.w	loc_1D0666
	blt.w	loc_1D067E
	clr.w	d0
	move.b	$C(a0),d0
	lsl.w	#8,d0
	move.b	$D(a0),d0
	addq.w	#1,d0
	move.b	d0,$D(a0)
	lsr.w	#8,d0
	move.b	d0,$C(a0)
	bra.w	loc_1D067E
loc_1D0666:
	clr.w	d0
	move.b	$8(a0),d0
	lsl.w	#8,d0
	move.b	$9(a0),d0
	addq.w	#1,d0
	move.b	d0,$9(a0)
	lsr.w	#8,d0
	move.b	d0,$8(a0)
loc_1D067E:
	movem.w	(sp)+,d0
	movem.w	d0,-(sp)
	move.w	$C(a1),d0
	cmp.w	$C(a2),d0
	movem.w	(sp)+,d0
	ble.w	loc_1D06D2
	move.w	$C(a1),d5
	cmp.b	(a0),d5
	ble.w	loc_1D06B0
	st	d7
	move.b	d5,(a0)
	move.b	d3,$1(a0)
	move.b	d4,$2(a0)
	move.b	d2,$3(a0)
loc_1D06B0:
	move.w	$C(a2),d5
	move.w	(a2),d6
	sub.w	d5,d6
	cmp.b	$4(a0),d6
	ble.w	loc_1D06D2
	st	d7
	move.b	d6,$4(a0)
	move.b	d3,$5(a0)
	move.b	d4,$6(a0)
	move.b	d2,$7(a0)
loc_1D06D2:
	bsr.w	sub_1D029C
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $028326, $1D0338
sub_1D06DC:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a2
	jsr	(sub_01A268).l
	move.w	d0,(ram_D338).w
	movea.l	#ram_CAD0,a2
	jsr	(sub_01A268).l
	move.w	d0,(ram_D33A).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D033C
sub_1D0706:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a2
	jsr	(sub_01A2D0).l
	move.w	d0,(ram_D33C).w
	movea.l	#ram_CAD0,a2
	jsr	(sub_01A2D0).l
	move.w	d0,(ram_D33E).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D0730:
	movem.l	d0-d3/a0-a3,-(sp)
	movea.l	a1,a2
	tst.w	d2
	beq.w	loc_1D077C
	move.w	#$9,d0
	clr.w	d3
	movea.l	#ram_D34A,a0
	mulu.w	#$A,d2
	adda.l	d2,a0
loc_1D074E:
	move.b	$0(a0,d3.w),d1
	bne.w	loc_1D075A
	move.b	#$20,d1
loc_1D075A:
	move.b	d1,$2(a1)
	tst.b	(a1)+
	addq.w	#1,d3
	dbra	d0,loc_1D074E
	move.w	#$C,(a2)
	btst	#7,(TextFlags).w
	beq.w	loc_1D0778
	bsr.w	sub_1D095C
loc_1D0778:
	bra.w	loc_1D0792
loc_1D077C:
	movea.l	a1,a3
	move.l	a3,-(sp)
	movea.l	#dat_1D0798,a1
	jsr	(sub_1D01EE).l
	movea.l	(sp)+,a2
	bsr.w	sub_1D095C
loc_1D0792:
	movem.l	(sp)+,d0-d3/a0-a3
	rts
dat_1D0798:
	dc.b	$00,$02


; ----------------------------------------------------------------------
sub_1D079A:
	movem.l	d0/a0-a3,-(sp)
	ext.w	d0
	asl.w	#2,d0
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1D07B6
	movea.l	#RosterTable,a0
loc_1D07B6:
	movea.l	$0(a0,d0.w),a0
	move.w	$4(a0),d0
	ext.l	d0
	adda.l	d0,a0
	adda.w	(a0),a0
	movea.l	a1,a3
	movea.l	a0,a1
	jsr	(Text_AppendInline_Worker).l
	movem.l	(sp)+,d0/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $01410A, $014226, $0145B0, $019C5E, $019C9A, $1D72C8
sub_1D07D4:
	move.l	a6,-(sp)
	clr.w	(ram_D4AE).w
	clr.w	(ram_D4B0).w
	movea.l	#dat_1D094C,a6
	cmp.l	(dat_028AC0).l,d4
	bne.w	loc_1D07F4
	movea.l	#dat_1D092C,a6
loc_1D07F4:
	cmp.l	(dat_028C22).l,d4
	bne.w	loc_1D0804
	movea.l	#dat_1D093C,a6
loc_1D0804:
	movea.l	$1E(a2),a0
	lea	$1BC(a2),a4
	clr.l	d1
	move.w	d0,d1
	asl.w	#4,d1
	adda.l	d1,a4
	adda.l	#$10,a4
	movem.l	d7/a1,-(sp)
	move.w	$28(a2),d7
	jsr	(sub_013C76).l
	adda.w	(a1),a1
	addq.w	#8,a1
	movea.l	a1,a0
	movem.l	(sp)+,d7/a1
	clr.w	d0
	clr.w	d1
	moveq	#$F,d2
	swap	d4
loc_1D083A:
	btst	d2,d4
	beq.w	loc_1D08F0
	move.w	d2,d3
	lsr.w	#1,d3
	neg.w	d3
	move.b	-$1(a0,d3.w),d3
	btst	#0,d2
	beq.w	loc_1D0854
	lsr.w	#4,d3
loc_1D0854:
	andi.w	#$F,d3
	cmp.w	#$D,d2	; general form
	bne.w	loc_1D0864
	bra.w	loc_1D08EA
loc_1D0864:
	tst.w	d2
	bne.w	loc_1D0884
	btst	#4,(ram_C35A).w
	beq.w	loc_1D087A
	asr.b	#1,d3
	bra.w	loc_1D0884
loc_1D087A:
	cmp.b	#$6,d3	; general form
	ble.w	loc_1D0884
	subq.b	#6,d3
loc_1D0884:
	cmp.w	#$6,d2	; general form
	beq.w	loc_1D08EA
	movem.l	d5-d7,-(sp)
	move.b	$0(a6,d2.w),d5
	ext.w	d5
	cmp.w	#$2,d5	; general form
	beq.w	loc_1D08AC
	move.w	d3,-(sp)
	subq.w	#2,d5
loc_1D08A2:
	add.w	(sp),d3
	dbra	d5,loc_1D08A2
	asr.w	#1,d3
	tst.w	(sp)+
loc_1D08AC:
	movem.l	(sp)+,d5-d7
	cmpa.l	#dat_1D094C,a6
	beq.w	loc_1D08D4
	neg.w	d2
	move.w	d7,-(sp)
	move.b	-$1(a4,d2.w),d7
	ext.w	d7
	add.w	d7,(ram_D4AE).w
	addq.w	#1,(ram_D4B0).w
	move.w	(sp)+,d7
	neg.w	d2
	bra.w	loc_1D08EA
loc_1D08D4:
	move.w	d3,-(sp)
	asl.w	#4,d3
	add.w	(sp),d3
	add.w	(sp)+,d3
	neg.w	d2
	add.b	-$1(a4,d2.w),d3
	bpl.w	loc_1D08E8
	clr.b	d3
loc_1D08E8:
	neg.w	d2
loc_1D08EA:
	add.w	d3,d0
	addi.w	#$64,d1
loc_1D08F0:
	dbra	d2,loc_1D083A
	cmpa.l	#dat_1D094C,a6
	beq.w	loc_1D0918
	move.w	#$64,d1
	movem.l	d6/d7,-(sp)
	move.w	(ram_D4AE).w,d6
	ext.l	d6
	move.w	(ram_D4B0).w,d7
	divs.w	d7,d6
	add.w	d6,d0
	movem.l	(sp)+,d6/d7
loc_1D0918:
	cmp.w	d1,d0
	blt.w	loc_1D0922
	move.w	d0,d1
	subq.w	#1,d0
loc_1D0922:
	jsr	(sub_1D9DC6).l
	movea.l	(sp)+,a6
	rts
dat_1D092C:
	dc.w	$0202,$0202,$0406,$0204,$0204,$0606,$0402,$0202
dat_1D093C:
	dc.w	$0202,$0202,$0202,$0202,$0909,$0202,$0902,$0202
dat_1D094C:
	dc.w	$0202,$0202,$0202,$0202,$0202,$0202,$0202,$0202


; ----------------------------------------------------------------------
; called from $1D0774, $1D078E
sub_1D095C:
	movem.l	a3,-(sp)
	movea.l	a2,a3
	adda.w	(a2),a3
loc_1D0964:
	move.b	-(a3),d0
	cmp.b	#$20,d0	; general form
	bne.w	loc_1D0976
	move.b	#$0,(a3)
	subq.w	#1,(a2)
	bra.s	loc_1D0964
loc_1D0976:
	addq.w	#1,(a2)
	andi.w	#$FE,(a2)
	movem.l	(sp)+,a3
	rts
loc_1D0982:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,d0
	jsr	(sub_021BF4).l
	jsr	(Text_Print).l
inl_1D0996:
	dc.w	loc_1D099C-inl_1D0996
	dc.b	$BF,$03,$02,$00
loc_1D099C:
	moveq	#$1B,d0
	moveq	#$C,d1
	jsr	(Text_PrintDigitsBig).l
	lea	dat_1D0B36(pc),a1
	jsr	(Text_PrintScoreboardAlt_Worker).l
	move.w	(ram_D2F6).w,d0
	movea.l	#ram_C732,a2
	tst.w	(ram_D2F0).w
	beq.w	loc_1D09C8
	movea.l	#ram_CAD0,a2
loc_1D09C8:
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	addq.w	#6,(TextX).w
	jsr	(Text_Print).l
inl_1D09EA:
	dc.w	loc_1D09F4-inl_1D09EA
	dc.b	" vs."
	dc.b	$BF,$04,$07,$00
loc_1D09F4:
	move.w	(ram_D2F4).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a2
	adda.w	d0,a2
	clr.w	d0
	move.b	$67(a2),d0
	movea.l	#ram_CAD0,a2
	tst.w	(ram_D2F0).w
	beq.w	loc_1D0A1C
	movea.l	#ram_C732,a2
loc_1D0A1C:
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1D0A2E:
	dc.w	loc_1D0A6C-inl_1D0A2E
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"                         "
	dc.b	$FA,$02,$FD,$04
	dc.b	"                         ",0
loc_1D0A6C:
	jsr	(Text_PrintScoreboard).l
inl_1D0A72:
	dc.w	loc_1D0A8A-inl_1D0A72
	dc.b	$F8,$04,$01,$05,$08
	dc.b	"<            >"
	dc.b	$FD,$06,$00
loc_1D0A8A:
	movea.l	#ram_C732,a1
	movea.l	$1E(a1),a1
	adda.w	$4(a1),a1
	jsr	(Text_PrintScoreboard_Worker).l
	move.w	#$15,(TextX).w
	move.w	(ram_D452).w,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	jsr	(Text_PrintScoreboard).l
inl_1D0ABE:
	dc.w	loc_1D0AD6-inl_1D0ABE
	dc.b	$F8,$04,$01,$05,$0A
	dc.b	"<            >"
	dc.b	$FD,$06,$00
loc_1D0AD6:
	movea.l	#ram_CAD0,a1
	movea.l	$1E(a1),a1
	adda.w	$4(a1),a1
	jsr	(Text_PrintScoreboard_Worker).l
	move.w	#$15,(TextX).w
	move.w	(ram_D454).w,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	jsr	(Text_Print).l
inl_1D0B0A:
	dc.w	loc_1D0B1C-inl_1D0B0A
	dc.b	$BF,$04,$0C
	dc.b	"       Round "
loc_1D0B1C:
	move.w	(ram_D456).w,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D0B36:
	dc.w	$0026,$F804,$0104,$0320,$2020,$2020,$2053,$484F
	dc.w	$4F54,$4F55,$5420,$4D4F,$4445,$2020,$2020,$2020
	dc.w	$F804,$0104,$0500


; ----------------------------------------------------------------------
; called from $1DC264
sub_1D0B5C:
	movea.l	#ram_B060,a0
	move.w	#$3FF,d0
loc_1D0B66:
	clr.w	(a0)+
	dbra	d0,loc_1D0B66
	clr.w	(ram_DCE2).w
	move.w	#$1,(ram_D456).w
	bclr	#3,(ram_C34A).w
	clr.w	(ram_D452).w
	clr.w	(ram_D454).w
	clr.w	(ram_D464).w
	clr.w	(ram_D472).w
	rts


; ----------------------------------------------------------------------
; called from $01DD72
sub_1D0B8E:
	btst	#3,(ram_C34A).w
	beq.w	loc_1D0B9E
	jmp	(loc_026CE2).l
loc_1D0B9E:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D154A
	move.w	(ram_D472).w,(ram_D2F0).w
	move.w	#$B,(ram_D2F4).w
	movea.l	#ram_D458,a0
	tst.w	(ram_D472).w
	beq.w	loc_1D0BCC
	move.w	#$5,(ram_D2F4).w
	movea.l	#ram_D466,a0
loc_1D0BCC:
	move.w	(ram_D464).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),(ram_D2F6).w
	bclr	#2,(ram_B7C2).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01E4A2
sub_1D0BE4:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#0,(ram_D473).w
	beq.w	loc_1D0C18
	cmpi.w	#$5,(ram_D456).w
	blt.w	loc_1D0C18
	move.w	(ram_D452).w,d0
	cmp.w	(ram_D454).w,d0
	beq.w	loc_1D0C18
	bset	#3,(ram_C34A).w
	jsr	(sub_1D0D9A).l
	bra.w	loc_1D0C38
loc_1D0C18:
	eori.w	#$1,(ram_D472).w
	bne.w	loc_1D0C38
	addq.w	#1,(ram_D464).w
	cmpi.w	#$5,(ram_D464).w
	blt.w	loc_1D0C34
	clr.w	(ram_D464).w
loc_1D0C34:
	addq.w	#1,(ram_D456).w
loc_1D0C38:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $015ECE, $015EDA
sub_1D0C3E:
	movea.l	#ram_D464,a0
	move.w	(ram_C3AC).w,d0
	tst.w	(ram_D472).w
	beq.w	loc_1D0C5A
	move.w	(ram_C3AE).w,d0
	movea.l	#ram_D472,a0
loc_1D0C5A:
	movem.l	d7/a0,-(sp)
	move.w	d0,d7
	jsr	(sub_012878).l
	movea.l	a0,a1
	movem.l	(sp)+,d7/a0
	move.w	#$5,d0
loc_1D0C70:
	clr.w	d1
	move.b	(a1)+,d1
	subq.w	#1,d1
	move.w	d1,-(a0)
	dbra	d0,loc_1D0C70
	rts


; ----------------------------------------------------------------------
; called from $021ADE
sub_1D0C7E:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1D0C88:
	dc.w	loc_1D0C8E-inl_1D0C88
	dc.b	$BF,$01,$0D,$00
loc_1D0C8E:
	move.w	#$6,d1
	move.w	#$1E,d0
	jsr	(Text_PrintDigitsBig).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1D0CA2:
	dc.w	loc_1D0CC6-inl_1D0CA2
	dc.b	$F8,$04,$01,$02,$0E
	dc.b	"      SHOOTOUT WON BY       ",0
loc_1D0CC6:
	addq.w	#2,(TextY).w
	move.w	(ram_C3AC).w,d1
	move.w	(ram_D452).w,d0
	cmp.w	(ram_D454).w,d0
	bgt.w	loc_1D0CDE
	move.w	(ram_C3AE).w,d1
loc_1D0CDE:
	asl.w	#2,d1
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1D0CF4
	movea.l	#RosterTable,a1
loc_1D0CF4:
	movea.l	$0(a1,d1.w),a1
	adda.w	$4(a1),a1
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	move.w	#$10,(TextX).w
	sub.w	d0,(TextX).w
	subq.w	#1,(TextX).w
	jsr	(Text_PrintScoreboard).l
inl_1D0D16:
	dc.w	loc_1D0D1A-inl_1D0D16
	dc.b	$3C,$00
loc_1D0D1A:
	jsr	(Text_PrintScoreboard_Worker).l
	jsr	(Text_PrintScoreboard).l
inl_1D0D26:
	dc.w	loc_1D0D2A-inl_1D0D26
	dc.b	$3E,$00
loc_1D0D2A:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D0D30:
	movem.l	d0/a0/a2,-(sp)
	movea.l	a2,a1
	movea.l	$1E(a1),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	cmpi.w	#$2,(a1)
	bne.w	loc_1D0D60
	movea.l	#dat_1D0D66,a1
	cmpa.l	#ram_C732,a2
	beq.w	loc_1D0D60
	movea.l	#dat_1D0D6C,a1
loc_1D0D60:
	movem.l	(sp)+,d0/a0/a2
	rts
dat_1D0D66:
	dc.b	$00,$06
	dc.b	"Home"
dat_1D0D6C:
	dc.b	$00,$0A


; ----------------------------------------------------------------------
sub_1D0D6E:
	addq.w	#3,$7369(a1)
	moveq	#$6F,d2
	moveq	#$73,d1
	movem.l	d0/a0/a2,-(sp)
	movea.l	a2,a1
	movea.l	$1E(a1),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	movem.l	(sp)+,d0/a0/a2
	rts


; ----------------------------------------------------------------------
sub_1D0D90:
	movem.l	d0-d7/a0-a6,-(sp)
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D0C0E
sub_1D0D9A:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#2,(ram_C33E).w
	jsr	(sub_01B286).l
	move.w	#$60,(ram_DCE2).w
	movea.l	#ram_B060,a3
	move.w	#$0,d0
	move.w	(ram_D452).w,d2
	cmp.w	(ram_D454).w,d2
	bgt.w	loc_1D0DCA
	move.w	#$6,d0
loc_1D0DCA:
	asl.w	#7,d0
	adda.w	d0,a3
	move.w	#$4,d2
	move.w	#$6,d3
	bra.w	loc_1D0E26
loc_1D0DDA:
	movem.w	d2/d3,-(sp)
	jsr	(sub_025470).l
	move.w	#$2,$34(a3)
	move.w	#$F0,d0
	tst.w	(ram_BD30).w
	bmi.w	loc_1D0DFA
	move.w	#$FF10,d0
loc_1D0DFA:
	add.w	(ram_BD30).w,d0
	move.w	d0,$14(a3)
	move.w	#$0,(a3)
	move.w	#$7,d0
	jsr	(sub_01F168).l
	bclr	#5,$62(a3)
	bclr	#1,$63(a3)
	bclr	#2,$62(a3)
	movem.w	(sp)+,d2/d3
loc_1D0E26:
	adda.l	#$80,a3
	dbra	d2,loc_1D0DDA
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D0E36:
	movem.l	d0-d7/a0,-(sp)
	move.w	$34(a3),d7
	subq.w	#1,d7
	movea.l	#dat_1D0E9E,a0
	btst	#7,$62(a3)
	beq.w	loc_1D0E56
	movea.l	#dat_1D0EAE,a0
loc_1D0E56:
	add.w	d7,d7
	move.w	$0(a0,d7.w),d0
	cmp.w	$44(a3),d0
	blt.w	loc_1D0E68
	move.w	d0,$44(a3)
loc_1D0E68:
	move.w	$2(a0,d7.w),d0
	cmp.w	$44(a3),d0
	bgt.w	loc_1D0E78
	move.w	d0,$44(a3)
loc_1D0E78:
	move.w	$4(a0,d7.w),d0
	cmp.w	$46(a3),d0
	blt.w	loc_1D0E88
	move.w	d0,$46(a3)
loc_1D0E88:
	move.w	$6(a0,d7.w),d0
	cmp.w	$46(a3),d0
	bgt.w	loc_1D0E98
	move.w	d0,$46(a3)
loc_1D0E98:
	movem.l	(sp)+,d0-d7/a0
	rts
dat_1D0E9E:
	dc.w	$FFB5,$0000,$0000,$011E,$0000,$004B,$0000,$011E
dat_1D0EAE:
	dc.w	$FFB5,$0000,$FEE2,$0000,$0000,$004B,$FEE2,$0000


; ----------------------------------------------------------------------
; called from $025954
sub_1D0EBE:
	rts


; ----------------------------------------------------------------------
sub_1D0EC0:
	tst.w	(ram_D492).w
	bmi.w	loc_1D0FDE
	tst.l	(ram_D498).w
	beq.w	loc_1D0FDE
	btst	#4,(ram_C344).w
	bne.w	loc_1D0FDE
	btst	#3,(ram_C33E).w
	bne.w	loc_1D0FDE
	btst	#7,(ram_C33C).w
	bne.w	loc_1D0FDE
	movea.l	(ram_D498).w,a1
	adda.l	$4(a1),a1
	move.w	(ram_BD34).w,d4
	move.w	(ram_BD30).w,d5
	move.w	(ram_D48C).w,d0
	bra.w	sub_1D0F26


; ----------------------------------------------------------------------
sub_1D0F06:
	andi.w	#$F,d2
	cmp.w	#$3,d2	; general form
	bls.w	loc_1D0F14
	moveq	#$3,d2
loc_1D0F14:
	bra.w	loc_1D0F20
loc_1D0F18:
	move.w	d3,d0
	add.w	d2,d0
	bsr.w	sub_1D0F26
loc_1D0F20:
	dbra	d2,loc_1D0F18
	rts


; ----------------------------------------------------------------------
; called from $1D0F02, $1D0F1C
sub_1D0F26:
	ext.w	d0
	beq.w	loc_1D0FDE
	cmp.w	#$40,d6	; general form
	bge.w	loc_1D0FDE
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
loc_1D0F70:
	cmp.w	(a0),d2
	bgt.w	loc_1D0FD4
	cmp.w	(a0),d3
	blt.w	loc_1D0FD4
	cmp.w	$6(a0),d0
	bgt.w	loc_1D0FD4
	cmp.w	$6(a0),d1
	blt.w	loc_1D0FD4
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
	add.w	(ram_D48A).w,d5
	or.w	(sp)+,d5
	move.w	d5,(a6)+
	move.w	$6(a0),d5
	addi.w	#$70,d5
	sub.w	d0,d5
	move.w	d5,(a6)+
	addq.w	#1,d6
	cmp.w	#$40,d6	; general form
	beq.w	loc_1D0FDA
loc_1D0FD4:
	addq.w	#8,a0
	dbra	d4,loc_1D0F70
loc_1D0FDA:
	movem.l	(sp)+,d0-d5
loc_1D0FDE:
	rts


; ----------------------------------------------------------------------
sub_1D0FE0:
	movem.l	d0-d7/a0/a2/a3,-(sp)
	jsr	(sub_0285AE).l
	move.w	(a1),d0
	subq.w	#2,d0
	move.w	d0,$2(a1)
	addq.w	#2,a1
	movem.l	(sp)+,d0-d7/a0/a2/a3
	rts

	dc.w	$0006,$202E,$2000,$4E75


; ----------------------------------------------------------------------
; called from $021EFC
sub_1D1002:
	btst	#5,(ram_C33E).w
	beq.w	loc_1D1026
	movea.l	#ram_C732,a2
	btst	#6,(ram_C33E).w
	beq.w	loc_1D1022
	movea.l	#ram_CAD0,a2
loc_1D1022:
	addq.w	#1,$38C(a2)
loc_1D1026:
	rts


; ----------------------------------------------------------------------
sub_1D1028:
	movem.l	d1-d7/a0-a6,-(sp)
	move.w	$28(a2),d0
	movea.l	#dat_1D1044,a0
	clr.w	d1
	move.b	$0(a0,d0.w),d1
	move.w	d1,d0
	movem.l	(sp)+,d1-d7/a0-a6
	rts
dat_1D1044:
	dc.b	"3LIKNCKC4BJIDBJ7EKG8E8HGHF[Y"


; ----------------------------------------------------------------------
; called from $00CBDE
sub_1D1060:
	movem.l	d0,-(sp)
	tst.w	(ram_C396).w
	beq.w	loc_1D1078
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_1D1088
loc_1D1078:
	cmpi.w	#$2,(ram_C382).w
	ble.w	loc_1D1088
	move.w	#$2,(ram_C382).w
loc_1D1088:
	movem.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
sub_1D108E:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_D272).w
	beq.w	loc_1D10B8
	bsr.w	sub_1D22D2
	btst	#1,(ram_C33C).w
	beq.w	loc_1D10B2
	eori.w	#$1,(ram_D28C).w
	bra.w	loc_1D10B8
loc_1D10B2:
	eori.w	#$1,(ram_D28A).w
loc_1D10B8:
	btst	#0,(ram_C34A).w
	bne.w	loc_1D10CC
	btst	#2,(ram_C342).w
	beq.w	loc_1D1166
loc_1D10CC:
	btst	#1,(ram_C33C).w
	bne.w	loc_1D112E
	cmpi.w	#$2,(ram_D272).w
	bne.w	loc_1D10EE
	cmpi.w	#$5,(ram_D2F2).w
	bgt.w	loc_1D1166
	bra.w	loc_1D10F8
loc_1D10EE:
	cmpi.w	#$5,(ram_D2F2).w
	ble.w	loc_1D1166
loc_1D10F8:
	move.w	#$0,d0
	cmpi.w	#$2,(ram_D272).w
	bne.w	loc_1D110A
	move.w	#$6,d0
loc_1D110A:
	tst.w	(ram_D28A).w
	bne.w	loc_1D1124
	move.w	#$5,d0
	cmpi.w	#$2,(ram_D272).w
	bne.w	loc_1D1124
	move.w	#$B,d0
loc_1D1124:
	jsr	(sub_01B752).l
	bra.w	loc_1D1166
loc_1D112E:
	cmpi.w	#$2,(ram_D272).w
	bne.w	loc_1D1146
	cmpi.w	#$5,(ram_D2F2).w
	ble.w	loc_1D1166
	bra.w	loc_1D1150
loc_1D1146:
	cmpi.w	#$5,(ram_D2F2).w
	bgt.w	loc_1D1166
loc_1D1150:
	move.w	#$6,d0
	tst.w	(ram_D28C).w
	bne.w	loc_1D1160
	move.w	#$B,d0
loc_1D1160:
	jsr	(sub_01B75C).l
loc_1D1166:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $019438
sub_1D116C:
	rts


; ----------------------------------------------------------------------
sub_1D116E:
	tst.w	(ram_D492).w
	bmi.w	loc_1D11CA
	movem.l	d0-d7/a0-a6,-(sp)
	tst.l	(ram_D498).w
	bne.w	loc_1D11B6
	move.w	(ram_D492).w,d0
	asl.w	#3,d0
	movea.l	#ptrs_1D120A,a0
	move.l	$0(a0,d0.w),(ram_D494).w
	move.l	$4(a0,d0.w),(ram_D498).w
	movea.l	$4(a0,d0.w),a2
	addq.w	#8,a2
	move.w	(ram_D48A).w,d4
	jsr	(sub_020780).l
	clr.w	(ram_D48E).w
	bsr.w	sub_1D11CC
	bra.w	loc_1D11C6
loc_1D11B6:
	sub.w	d7,(ram_D490).w
	bpl.w	loc_1D11C6
	addq.w	#1,(ram_D48E).w
	bsr.w	sub_1D11CC
loc_1D11C6:
	movem.l	(sp)+,d0-d7/a0-a6
loc_1D11CA:
	rts


; ----------------------------------------------------------------------
; called from $1D11AE, $1D11C2, $1D11F8
sub_1D11CC:
	movea.l	(ram_D494).w,a0
	move.w	(ram_D48E).w,d0
	add.w	d0,d0
	move.b	$0(a0,d0.w),d1
	ext.w	d1
	move.w	d1,(ram_D48C).w
	move.b	$1(a0,d0.w),d1
	ext.w	d1
	move.w	d1,(ram_D490).w
	cmpi.w	#$FFFF,(ram_D48C).w
	bne.w	loc_1D11FA
	clr.w	(ram_D48E).w
	bra.s	sub_1D11CC
loc_1D11FA:
	cmpi.w	#$FFFE,(ram_D48C).w
	bne.w	loc_1D1208
	bsr.w	sub_1D14AA
loc_1D1208:
	rts

ptrs_1D120A:
	dc.l	dat_1D143A
	dc.l	Art_171382
	dc.l	dat_1D1372
	dc.l	Art_171382
	dc.l	dat_1D141A
	dc.l	Art_171382
	dc.l	dat_1D13D2
	dc.l	Art_171382
	dc.l	dat_1D13A0
	dc.l	Art_171382
	dc.l	dat_1D141A
	dc.l	Art_171382
	dc.l	dat_1D127C
	dc.l	Art_171382
	dc.l	dat_1D124A
	dc.l	Art_171382
dat_1D124A:
	dc.b	$01,$0A,$02,$0A,$03,$0A,$04,$0A,$05,$0A,$06,$0A,$07,$0A,$08,$0A
	dc.b	$01,$0A,$02,$0A,$03,$0A,$04,$0A,$05,$0A,$06,$0A,$07,$0A,$08,$0A
	dc.b	$01,$0A,$02,$0A,$03,$0A,$04,$0A,$05,$0A,$06,$0A,$07,$0A,$08,$0A
	dc.b	$FE,$00
dat_1D127C:
	dc.b	$01,$0A,$02,$0A,$03,$0A,$04,$0A,$05,$0A,$06,$0A,$07,$0A,$08,$0A
	dc.b	$FF,$00,$01,$0A,$02,$0A,$03,$0A,$04,$0A,$05,$0A,$06,$0A,$07,$0A
	dc.b	$08,$0A,$09,$0A,$0A,$0A,$0B,$0A,$0C,$0A,$0D,$0A,$0E,$0A,$0F,$0A
	dc.b	$10,$0A,$11,$0A,$12,$0A,$13,$0A,$14,$0A,$15,$0A,$16,$0A,$17,$0A
	dc.b	$FE,$00,$01,$08,$02,$08,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C
	dc.b	$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C
	dc.b	$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C
	dc.b	$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C
	dc.b	$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C,$04,$3C,$03,$3C
	dc.b	$04,$3C,$02,$08,$01,$08,$FF,$00,$01,$08,$02,$08,$03,$08,$04,$08
	dc.b	$05,$08,$06,$08,$07,$08,$08,$08,$FF,$00,$01,$08,$02,$08,$03,$08
	dc.b	$04,$1E,$05,$08,$06,$08,$07,$08,$08,$1E,$05,$08,$06,$08,$07,$08
	dc.b	$08,$1E,$09,$08,$0A,$08,$0B,$08,$0C,$08,$0D,$08,$0E,$08,$FE,$00
	dc.b	$0F,$08,$10,$08,$11,$08,$12,$1E,$13,$08,$14,$08,$15,$08,$16,$1E
	dc.b	$13,$08,$14,$08,$15,$08,$16,$1E,$17,$08,$18,$08,$19,$08,$1A,$08
	dc.b	$1B,$08,$1C,$08,$FE,$00
dat_1D1372:
	dc.b	$01,$08,$02,$08,$03,$08,$04,$08,$05,$08,$06,$08,$07,$08,$08,$08
	dc.b	$09,$08,$0A,$08,$0B,$08,$0C,$08,$0D,$08,$0E,$08,$0F,$08,$10,$08
	dc.b	$11,$08,$12,$08,$13,$08,$14,$08,$15,$08,$16,$08,$FE,$00
dat_1D13A0:
	dc.b	$01,$08,$02,$08,$03,$08,$04,$08,$05,$08,$06,$08,$07,$08,$08,$08
	dc.b	$09,$08,$0A,$08,$0B,$08,$0C,$08,$0D,$08,$0E,$08,$0F,$08,$10,$08
	dc.b	$11,$08,$12,$08,$13,$08,$14,$08,$15,$08,$16,$08,$17,$08,$18,$08
	dc.b	$18,$7F
dat_1D13D2:
	dc.b	$01,$08,$02,$08,$03,$08,$04,$08,$05,$08,$06,$08,$07,$08,$08,$08
	dc.b	$09,$08,$0A,$08,$0B,$08,$0C,$08,$0D,$08,$0E,$08,$0F,$08,$10,$08
	dc.b	$11,$08,$12,$08,$13,$08,$14,$08,$15,$08,$16,$08,$17,$08,$18,$08
	dc.b	$19,$08,$1A,$08,$1B,$08,$1C,$08,$1D,$08,$1E,$08,$1F,$08,$20,$08
	dc.b	$21,$08,$22,$08,$23,$08,$FE,$00
dat_1D141A:
	dc.b	$01,$08,$02,$08,$03,$08,$04,$08,$05,$08,$06,$08,$07,$08,$08,$08
	dc.b	$09,$08,$0A,$08,$0B,$08,$0C,$08,$0D,$08,$0E,$08,$0F,$08,$FF,$00
dat_1D143A:
	dc.w	$010A,$020A,$030A,$040A,$050A,$060A,$070A,$080A
	dc.w	$080A,$080A,$080A,$080A,$080A,$080A,$087F,$087F
	dc.w	$FE00,$08F8,$0006,$C33C,$31FC,$0000,$BFDE,$31FC
	dc.w	$0160,$BFE0,$4E75


; ----------------------------------------------------------------------
; called from $00C672, $023734, $02839A
sub_1D1470:
	rts


; ----------------------------------------------------------------------
sub_1D1472:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	d0,(ram_D492).w
	move.l	#$0,(ram_D494).w
	move.l	#$0,(ram_D498).w
	move.w	#$1,(ram_D48C).w
	clr.w	(ram_D48E).w
	st	(ram_D49C).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00C02A
sub_1D149E:
	bset	#0,(ram_C34C).w
	move.w	d0,(ram_D49C).w
	rts


; ----------------------------------------------------------------------
; called from $00C7A6, $1D1204
sub_1D14AA:
	move.w	#$FFFF,(ram_D492).w
	bclr	#0,(ram_C34C).w
	rts


; ----------------------------------------------------------------------
sub_1D14B8:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D14C,a0
	move.w	#$7,d7
loc_1D14C6:
	clr.b	$8(a0)
	clr.b	$9(a0)
	clr.b	$A(a0)
	clr.b	$B(a0)
	clr.b	(a0)
	clr.b	$4(a0)
	clr.b	$C(a0)
	clr.b	$D(a0)
	adda.w	#$10,a0
	dbra	d7,loc_1D14C6
	move.l	#$F35,d0
	move.l	#$80,d1
	movea.l	#ram_D14C,a0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $012DE6
sub_1D1510:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D83A).w,d0
	btst	#7,$62(a3)
	bne.w	loc_1D152E
	movea.l	#dat_1D1538,a0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
loc_1D152E:
	move.w	d0,(ram_BF10).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D1538:
	dc.w	$0000,$0007,$0006,$0005,$0004,$0003,$0002,$0001
	dc.w	$0008


; ----------------------------------------------------------------------
; called from $01DD7C, $1D0BA2
sub_1D154A:
	movem.l	d0-d7/a0-a6,-(sp)
loc_1D154E:
	move.w	#$7,d0
	jsr	(Random).l
	cmp.w	#$6,d0	; general form
	bgt.s	loc_1D154E
	move.w	d0,(ram_D832).w
	bclr	#3,(ram_C34C).w
	move.w	#$FFFF,(ram_D834).w
	clr.w	(ram_D836).w
	bsr.w	sub_1D15F0
	movem.l	(sp)+,d0-d7/a0-a6
	rts

ptrs_1D157C:
	dc.l	dat_1D1598
	dc.l	dat_1D15A4
	dc.l	dat_1D15B4
	dc.l	dat_1D15C0
	dc.l	dat_1D15CC
	dc.l	dat_1D15D8
	dc.l	dat_1D15E4

dat_1D1598:
	dc.l	dat_1000E2
	dc.l	dat_1000D0
	dc.b	$80,$20,$00,$05
dat_1D15A4:
	dc.w	$FFC9,$00A0,$FFFF,$00C8,$FFE0,$00D0,$8020,$0005
dat_1D15B4:
	dc.w	$FFB0,$0040,$001A,$00BC,$8020,$0005
dat_1D15C0:
	dc.w	$FFCE,$0058,$0014,$00D0,$802C,$0005
dat_1D15CC:
	dc.w	$FFCE,$0008,$0020,$00D0,$8028,$0006
dat_1D15D8:
	dc.w	$001C,$00F4,$0008,$00E0,$8020,$0006
dat_1D15E4:
	dc.w	$FFE6,$00F8,$0000,$00E0,$8020,$0002


; ----------------------------------------------------------------------
; called from $1D1572, $1D16CE
sub_1D15F0:
	movem.l	d0-d7/a0-a6,-(sp)
	cmpi.b	#$80,(ram_D836).w
	beq.w	loc_1D1652
	addq.w	#1,(ram_D834).w
	move.w	(ram_D834).w,d0
	asl.w	#2,d0
	movea.l	#ptrs_1D157C,a0
	move.w	(ram_D832).w,d1
	asl.w	#2,d1
	movea.l	$0(a0,d1.w),a0
	move.w	$0(a0,d0.w),(ram_D836).w
	btst	#0,$77(a3)
	beq.w	loc_1D162C
	neg.w	(ram_D836).w
loc_1D162C:
	move.w	$2(a0,d0.w),(ram_D838).w
	cmpi.b	#$80,$4(a0,d0.w)
	bne.w	loc_1D1652
	bset	#3,(ram_C34C).w
	clr.w	(ram_D83C).w
	move.b	$5(a0,d0.w),(ram_D83D).w
	move.w	$6(a0,d0.w),(ram_D83A).w
loc_1D1652:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01CF70
sub_1D1658:
	movem.l	d2-d7/a0-a6,-(sp)
	cmpi.b	#$80,(ram_D836).w
	beq.w	loc_1D16DA
	move.w	(ram_D836).w,d0
	move.w	(ram_D838).w,d1
	btst	#7,$62(a3)
	bne.w	loc_1D167C
	neg.w	d0
	neg.w	d1
loc_1D167C:
	sub.w	(a3),d0
	bpl.w	loc_1D1684
	neg.w	d0
loc_1D1684:
	tst.w	$28(a3)
	bne.w	loc_1D169C
	tst.w	$2A(a3)
	bne.w	loc_1D169C
	cmp.w	#$12,d0	; general form
	ble.w	loc_1D16A4
loc_1D169C:
	cmp.w	#$A,d0	; general form
	bgt.w	loc_1D16D2
loc_1D16A4:
	sub.w	$14(a3),d1
	bpl.w	loc_1D16AE
	neg.w	d1
loc_1D16AE:
	tst.w	$28(a3)
	bne.w	loc_1D16C6
	tst.w	$2A(a3)
	bne.w	loc_1D16C6
	cmp.w	#$12,d1	; general form
	ble.w	loc_1D16CE
loc_1D16C6:
	cmp.w	#$A,d1	; general form
	bgt.w	loc_1D16D2
loc_1D16CE:
	bsr.w	sub_1D15F0
loc_1D16D2:
	move.w	(ram_D836).w,d0
	move.w	(ram_D838).w,d1
loc_1D16DA:
	movem.l	(sp)+,d2-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $01CF26
sub_1D16E0:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#1,(ram_C34A).w
	beq.w	loc_1D1774
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_1D1774
	cmpi.w	#$3,(ram_D344).w
	ble.w	loc_1D176E
	cmpi.b	#$80,(ram_D836).w
	beq.w	loc_1D176E
	btst	#3,(ram_C34C).w
	bne.w	loc_1D1736
	tst.w	(ram_B788).w
	bne.w	loc_1D1774
	tst.w	(ram_B78A).w
	bne.w	loc_1D1774
	cmpi.w	#$F,(ram_D344).w
	blt.w	loc_1D176E
	bra.w	loc_1D1774
loc_1D1736:
	move.w	(ram_D836).w,d0
	move.w	(ram_D838).w,d1
	btst	#7,$62(a3)
	bne.w	loc_1D174C
	neg.w	d0
	neg.w	d1
loc_1D174C:
	sub.w	(a3),d0
	bpl.w	loc_1D1754
	neg.w	d0
loc_1D1754:
	sub.w	$14(a3),d1
	bpl.w	loc_1D175E
	neg.w	d1
loc_1D175E:
	cmp.w	(ram_D83C).w,d0
	bgt.w	loc_1D1774
	cmp.w	(ram_D83C).w,d1
	bgt.w	loc_1D1774
loc_1D176E:
	clr.w	d0
	bra.w	loc_1D1778
loc_1D1774:
	move.w	#$1,d0
loc_1D1778:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D177E:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D83E,a0
	movea.l	#ram_DCC0,a1
	move.w	(a2)+,d0
	move.w	d0,(a0)+
	asl.w	#3,d0
	subq.w	#1,d0
loc_1D1796:
	clr.l	(a0)
	clr.l	(a1)
	move.b	(a2)+,(a1)
	move.b	(a2)+,$1(a1)
	move.b	(a2)+,$2(a1)
	move.l	#$0,-(sp)
	move.l	(a1),d2
	andi.l	#$E0000000,d2
	lsr.l	#1,d2
	addi.l	#$50000000,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$1C000000,d2
	lsr.l	#2,d2
	addi.l	#$5000000,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$3800000,d2
	lsr.l	#3,d2
	addi.l	#$500000,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$700000,d2
	lsr.l	#4,d2
	addi.l	#$50000,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$E0000,d2
	lsr.l	#5,d2
	addi.l	#$5000,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$1C000,d2
	lsr.l	#6,d2
	addi.l	#$500,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$3800,d2
	lsr.l	#7,d2
	addi.l	#$50,d2
	or.l	d2,(sp)
	move.l	(a1),d2
	andi.l	#$700,d2
	move.w	#$8,d5
	lsr.l	d5,d2
	addq.l	#5,d2
	or.l	d2,(sp)
	move.l	(sp)+,(a0)+
	dbra	d0,loc_1D1796
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $019F42, $0264C0, $1DD0A2
sub_1D1846:
	move.w	d4,(ram_B032).w
	movea.l	#Art_1706CA_Tiles,a2
	jmp	(sub_020780).l


; ----------------------------------------------------------------------
; called from $019F3C, $0264BA, $1DD092
sub_1D1856:
	move.w	d0,-(sp)
	subi.w	#$18,d4
	movea.l	#ptrs_1D1886,a2
	tst.w	(ram_DEA8).w
	beq.w	loc_1D1870
	movea.l	#dat_1D1916,a2
loc_1D1870:
	move.w	(ram_C3AC).w,d0
	asl.w	#2,d0
	movea.l	$0(a2,d0.w),a2
	addq.w	#8,a2
	jsr	(sub_020780).l
	move.w	(sp)+,d0
	rts

ptrs_1D1886:
	dc.l	dat_17159E
	dc.l	dat_1718A8
	dc.l	dat_171BB2
	dc.l	dat_171EBC
	dc.l	dat_173402
	dc.l	dat_1721C6
	dc.l	dat_1724D0
	dc.l	dat_1727DA
	dc.l	dat_172AE4
	dc.l	dat_172DEE
	dc.l	dat_1730F8
	dc.l	dat_17370C
	dc.l	dat_173A16
	dc.l	dat_173D20
	dc.l	dat_17402A
	dc.l	dat_174334
	dc.l	dat_17463E
	dc.l	dat_174948
	dc.l	dat_174C52
	dc.l	dat_174F5C
	dc.l	dat_175266
	dc.l	dat_175570
	dc.l	dat_17587A
	dc.l	dat_175B84
	dc.l	dat_175E8E
	dc.l	dat_176198
	dc.l	dat_1764A2
	dc.l	dat_1767AC
	dc.l	dat_176AB6
	dc.l	dat_176DC0
	dc.l	dat_1770CA
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E

dat_1D1916:
	dc.l	dat_17159E
	dc.l	dat_1718A8
	dc.l	dat_171BB2
	dc.l	dat_171EBC
	dc.l	dat_173402
	dc.l	dat_1721C6
	dc.l	dat_1724D0
	dc.l	dat_1727DA
	dc.l	dat_172AE4
	dc.l	dat_172DEE
	dc.l	dat_1730F8
	dc.l	dat_17370C
	dc.l	dat_173A16
	dc.l	dat_173D20
	dc.l	dat_17402A
	dc.l	dat_174334
	dc.l	dat_17463E
	dc.l	dat_174948
	dc.l	dat_174C52
	dc.l	dat_174F5C
	dc.l	dat_175266
	dc.l	dat_175570
	dc.l	dat_17587A
	dc.l	dat_175B84
	dc.l	dat_175E8E
	dc.l	dat_176198
	dc.l	dat_1773D4
	dc.l	dat_1776DE
	dc.l	dat_176AB6
	dc.l	dat_176DC0
	dc.l	dat_1770CA
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E
	dc.l	dat_17159E


; ----------------------------------------------------------------------
; called from $028412, $028438
sub_1D19A6:
	movem.l	d0/a2,-(sp)
	jsr	(Text_Print).l
inl_1D19B0:
	dc.w	loc_1D19B4-inl_1D19B0
	dc.b	$20,$28
loc_1D19B4:
	adda.w	#$DC,a2
	bra.w	loc_1D19CE


; ----------------------------------------------------------------------
; called from $0283D6
sub_1D19BC:
	movem.l	d0/a2,-(sp)
	jsr	(Text_Print).l
inl_1D19C6:
	dc.w	loc_1D19CA-inl_1D19C6
	dc.b	$20,$28
loc_1D19CA:
	adda.w	#$C0,a2
loc_1D19CE:
	move.b	$0(a2,d0.w),d0
	ext.w	d0
	move.w	#$1,d1
	cmp.w	#$9,d0	; general form
	ble.w	loc_1D19F0
	move.w	#$2,d1
	cmp.w	#$63,d0	; general form
	ble.w	loc_1D19F0
	move.w	#$3,d1
loc_1D19F0:
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1D1A02:
	dc.w	loc_1D1A06-inl_1D1A02
	dc.b	$29,$00
loc_1D1A06:
	addq.w	#1,(TextY).w
	move.w	#$E,(TextX).w
	movem.l	(sp)+,d0/a2
	rts


; ----------------------------------------------------------------------
; called from $01AEA8
sub_1D1A16:
	cmpi.w	#$2142,$58(a3)
	beq.w	loc_1D1AFC
	cmpi.w	#$2582,$58(a3)
	beq.w	loc_1D1AE0
	cmpi.w	#$241E,$58(a3)
	beq.w	loc_1D1AA8
	cmpi.w	#$236C,$58(a3)
	beq.w	loc_1D1A4C
	cmpi.w	#$24D0,$58(a3)
	beq.w	loc_1D1A7A
	bra.w	loc_1D1B10
loc_1D1A4C:
	move.w	#$124,d0
	cmpi.w	#$56,(ram_D308).w
	bgt.w	loc_1D1A64
	cmpi.w	#$FFAA,(ram_D308).w
	bgt.w	loc_1D1A68
loc_1D1A64:
	move.w	#$116,d0
loc_1D1A68:
	sub.w	$14(a3),d0
	bmi.w	loc_1D1B10
	asr.w	#1,d0
	add.w	d0,$14(a3)
	bra.w	loc_1D1B10
loc_1D1A7A:
	move.w	#$FEDC,d0
	cmpi.w	#$56,(ram_D308).w
	bgt.w	loc_1D1A92
	cmpi.w	#$FFAA,(ram_D308).w
	bgt.w	loc_1D1A96
loc_1D1A92:
	move.w	#$FEEA,d0
loc_1D1A96:
	sub.w	$14(a3),d0
	bpl.w	loc_1D1B10
	asr.w	#1,d0
	add.w	d0,$14(a3)
	bra.w	loc_1D1B10
loc_1D1AA8:
	move.w	#$90,d0
	btst	#3,$4(a3)
	beq.w	loc_1D1ABA
	move.w	#$FF70,d0
loc_1D1ABA:
	sub.w	(a3),d0
	asr.w	#1,d0
	add.w	d0,(a3)
	bra.w	loc_1D1B10


; ----------------------------------------------------------------------
sub_1D1AC4:
	move.w	#$96,d0
	btst	#3,$4(a3)
	beq.w	loc_1D1AD6
	move.w	#$FF6A,d0
loc_1D1AD6:
	sub.w	(a3),d0
	asr.w	#1,d0
	add.w	d0,(a3)
	bra.w	loc_1D1B10
loc_1D1AE0:
	move.w	#$FF70,d0
	btst	#3,$4(a3)
	beq.w	loc_1D1AF2
	move.w	#$90,d0
loc_1D1AF2:
	sub.w	(a3),d0
	asr.w	#1,d0
	add.w	d0,(a3)
	bra.w	loc_1D1B10
loc_1D1AFC:
	move.w	#$FF6A,d0
	btst	#3,$4(a3)
	beq.w	loc_1D1B0A
loc_1D1B0A:
	sub.w	(a3),d0
	asr.w	#1,d0
	add.w	d0,(a3)
loc_1D1B10:
	rts


; ----------------------------------------------------------------------
; called from $023A36
sub_1D1B12:
	clr.w	d0
	move.b	$75(a2),d0
	lsr.w	#2,d0
	rts


; ----------------------------------------------------------------------
; called from $023A68
sub_1D1B1C:
	cmpi.b	#$2,$77(a2)
	ble.w	loc_1D1B36
	movem.w	d0,-(sp)
	move.w	#$1,d0
	movem.w	(sp)+,d0
	bra.w	loc_1D1B42
loc_1D1B36:
	movem.w	d0,-(sp)
	move.w	#$0,d0
	movem.w	(sp)+,d0
loc_1D1B42:
	rts


; ----------------------------------------------------------------------
; called from $00C01E
sub_1D1B44:
	movem.l	a0,-(sp)
	movea.l	#dat_1D1B80,a0
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$7,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	cmpi.w	#$FFC0,(ram_BFE4).w
	bgt.w	loc_1D1B7A
	cmpi.w	#$C0,(ram_BFE6).w
	bgt.w	loc_1D1B7A
	move.w	#$6,d0
loc_1D1B7A:
	movem.l	(sp)+,a0
	rts
dat_1D1B80:
	dc.w	$0003,$0005,$0003,$0001,$0005,$0002,$0003,$0003
	dc.w	$FFFF


; ----------------------------------------------------------------------
; called from $00C008
sub_1D1B92:
	movem.l	d0-d2/a0-a2,-(sp)
	movea.l	#ram_C732,a0
	movea.l	#ram_CAD0,a1
	move.w	$24(a0),d0
	sub.w	$24(a1),d0
	beq.w	loc_1D1BBE
	bpl.w	loc_1D1BB4
	exg	a0,a1
loc_1D1BB4:
	cmpi.w	#$8,$28(a0)
	bne.w	loc_1D1BBE
loc_1D1BBE:
	movem.l	(sp)+,d0-d2/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $018FCE
sub_1D1BC4:
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
	jsr	(sub_01FFA2).l
	movea.w	#$BD40,a0
	moveq	#$1F,d1
loc_1D1C0E:
	clr.l	(a0)+
	dbra	d1,loc_1D1C0E
	jsr	(VDP_Init).l
	jsr	(Text_Print).l
inl_1D1C20:
	dc.w	loc_1D1C26-inl_1D1C20
	dc.b	$FF,$00,$FF,$00
loc_1D1C26:
	movea.l	#Art_THQLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$20,(a0)
	move.w	#$0,(a0)
	move.w	#$18,(FadeCounter).w
	move.w	#$2500,sr
	move.w	#$3C,(RandomSeed).w
loc_1D1C68:
	moveq	#$4,d0
	jsr	(sub_0201A2).l
	subq.w	#1,(RandomSeed).w
	bpl.s	loc_1D1C68
	jsr	(sub_01FFA2).l
	move.w	#$2700,sr
	rts


; ----------------------------------------------------------------------
sub_1D1C82:
	movea.l	#ram_C732,a2
	cmp.w	$28(a2),d2
	beq.w	loc_1D1C96
	movea.l	#ram_CAD0,a2
loc_1D1C96:
	rts


; ----------------------------------------------------------------------
; called from $00D3FA, $00D542
sub_1D1C98:
	movem.l	d1-d7/a0,-(sp)
	btst	#0,(ram_C33A).w
	bne.w	loc_1D1CAA
	move.w	(ram_BF48).w,d1
loc_1D1CAA:
	movem.l	(sp)+,d1-d7/a0
	rts


; ----------------------------------------------------------------------
sub_1D1CB0:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_DCCC,a1
	jsr	(sub_1E1AD6).l
	move.w	(ram_D3DE).w,d0
	move.b	#$0,$0(a1,d0.w)
	addq.w	#1,d0
	andi.w	#$FFFE,d0
	move.w	d0,-$2(a1)
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$48E7,$FFBE,$3038,$D264,$4A40,$6700,$0080,$227C
	dc.w	$FFFF,$D3CC,$31C0,$D3E0,$4EB9,$001E,$1AD6,$D2F8
	dc.w	$D3DE,$12BC,$0000,$5278,$D3DE,$0278,$FFFE,$D3DE
	dc.w	$5478,$D3DE,$31F8,$D3DE,$D3CA,$227C,$FFFF,$D3CA
	dc.w	$2F09,$267C,$FFFF,$BF56,$227C,$001D,$1D56,$6100
	dc.w	$E4C4,$225F,$267C,$FFFF,$BF56,$4EB9,$0002,$0ED0
	dc.w	$267C,$FFFF,$BF56,$4EB9,$0002,$0EC8,$0004,$2900
	dc.w	$227C,$FFFF,$BF56,$4CDF,$7DFF,$4E75,$000E,$2870
	dc.w	$6C61,$7965,$6420,$6279,$2000,$0002,$227C,$001D
	dc.w	$1D64,$60E2,$48E7,$FFBE,$3038,$D266,$6000,$FF6A


; ----------------------------------------------------------------------
; called from $01AE42
sub_1D1D7A:
	bra.w	loc_1D1D88


; ----------------------------------------------------------------------
sub_1D1D7E:
	bclr	#1,(ram_C34E).w
	bra.w	loc_1D1D8E
loc_1D1D88:
	bset	#1,(ram_C34E).w
loc_1D1D8E:
	rts


; ----------------------------------------------------------------------
; called from $1D915E
sub_1D1D90:
	cmp.w	#$50,d0	; general form
	bge.w	loc_1D1D9E
	asr.w	#1,d0
	addi.w	#$28,d0
loc_1D1D9E:
	rts


; ----------------------------------------------------------------------
sub_1D1DA0:
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_1D1DDA
	move.w	(ram_B788).w,d1
	eor.w	d1,d0
	andi.w	#$8000,d0
	beq.w	loc_1D1DDA
	move.w	(ram_B774).w,d0
	sub.w	$14(a3),d0
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_1D1DDA
	move.w	(ram_B78A).w,d1
	eor.w	d1,d0
	andi.w	#$8000,d0
loc_1D1DDA:
	movem.w	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $00F792, $01033A, $0105FA, $0114D0, $0130E8, $01CE96, $01D6AC
sub_1D1DE0:
	movem.l	a1,-(sp)
	movea.l	#ram_C732,a1
	btst	#6,$62(a3)
	beq.w	loc_1D1DFA
	movea.l	#ram_CAD0,a1
loc_1D1DFA:
	tst.w	$26(a1)
	movem.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $02409A, $1CF270
sub_1D1E04:
	movem.l	d0/a0,-(sp)
	bclr	#3,$64(a3)
	bclr	#5,$62(a3)
	bclr	#1,$63(a3)
	clr.w	(ram_BFB2).w
	st	(ram_BFA8).w
	move.w	d1,-(sp)
	move.w	#$870,d1
	jsr	(sub_01F3B2).l
	tst.w	$34(a3)
	bpl.w	loc_1D1E40
	jsr	(sub_01F156).l
	bra.w	loc_1D1E46
loc_1D1E40:
	jsr	(sub_025448).l
loc_1D1E46:
	clr.w	$5A(a3)
	st	$5C(a3)
	move.w	(sp)+,d1
	movem.l	(sp)+,d0/a0
	rts

	incbin	"data/bin/data_1D1E56.bin"	; 896 bytes


; ----------------------------------------------------------------------
; called from $00C736
sub_1D21D6:
	movem.l	d0/a0-a3,-(sp)
	move.w	(ram_C33E).w,-(sp)
	btst	#1,(ram_C34A).w
	bne.w	loc_1D2278
	movea.w	#$C732,a2
	lea	$39E(a2),a3
	move.w	$24(a2),d0
	sub.w	$24(a3),d0
	beq.w	loc_1D2278
	bpl.w	loc_1D2218
	btst	#6,(ram_C33E).w
	bne.w	loc_1D222E
	bsr.w	sub_1D2270
	bset	#6,(ram_C33E).w
	bra.w	loc_1D222E
loc_1D2218:
	exg	a2,a3
	btst	#6,(ram_C33E).w
	beq.w	loc_1D222E
	bsr.w	sub_1D2270
	bclr	#6,(ram_C33E).w
loc_1D222E:
	bset	#5,(ram_C33E).w
	bne.w	loc_1D2278
	cmpa.w	#$C732,a3
	bne.w	loc_1D225C
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$2,(ram_D4AC).w
	jsr	(sub_092274).l
loc_1D2252:
	bset	#6,(ram_C34E).w
	bra.w	loc_1D2278
loc_1D225C:
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$5,(ram_D4AC).w
	jsr	(sub_092274).l
	bra.s	loc_1D2252


; ----------------------------------------------------------------------
; called from $1D220A, $1D2224
sub_1D2270:
	bclr	#5,(ram_C33E).w
	rts
loc_1D2278:
	move.w	(sp)+,(ram_C33E).w
	movem.l	(sp)+,d0/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $019648
sub_1D2282:
	movem.l	d0/a0,-(sp)
	clr.w	(ram_C3F8).w
	clr.w	(ram_C3F6).w
	clr.w	(ram_C3F4).w
	move.w	#$10,d0
	movea.l	#ram_C3B2,a0
loc_1D229C:
	clr.l	(a0)+
	dbra	d0,loc_1D229C
	movea.l	#ram_C732,a0
	bsr.w	sub_1D22BC
	movea.l	#ram_CAD0,a0
	bsr.w	sub_1D22BC
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
; called from $1D22A8, $1D22B2
sub_1D22BC:
	move.w	#$1B,d0
	adda.w	#$6C,a0
loc_1D22C4:
	move.w	#$FFFE,(a0)+
	dbra	d0,loc_1D22C4
	move.w	#$FFFF,(a0)
	rts


; ----------------------------------------------------------------------
; called from $01979E, $1D109A
sub_1D22D2:
	movem.l	d0/a0/a1,-(sp)
	movea.l	#dat_1D2304,a0
	move.w	(ram_D26E).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	cmpi.w	#$1,(a0)
	movem.l	(sp)+,d0/a0/a1
	ble.w	loc_1D22FC
	bset	#1,(ram_C33C).w
	bra.w	loc_1D2302
loc_1D22FC:
	bclr	#1,(ram_C33C).w
loc_1D2302:
	rts
dat_1D2304:
	dc.w	$FFFF,$C394,$FFFF,$C396,$FFFF,$C398,$FFFF,$C39A
	dc.w	$0838,$0003,$C33C,$6600,$002E,$48E7,$A080,$102B
	dc.w	$0062,$1238,$C368,$B300,$0800,$0006,$6700,$0044
	dc.w	$6000,$0038,$0838,$0003,$C33C,$6700,$003A,$4A78
	dc.w	$B7C0,$6B00,$0032,$48E7,$A080,$207C,$FFFF,$B060
	dc.w	$3038,$B7C0,$EF40,$D0C0,$1028,$0062,$142B,$0062
	dc.w	$B500,$0800,$0006,$6700,$000A,$323C,$09B4,$6000
	dc.w	$0002,$4CDF,$0105,$4E75


; ----------------------------------------------------------------------
; called from $01DA3A
sub_1D237C:
	movem.l	d0-d3/a0-a2,-(sp)
	btst	#5,$62(a3)
	bne.w	loc_1D2480
	btst	#3,(ram_C33C).w
	bne.w	loc_1D239A
	bclr	#3,(ram_C354).w
loc_1D239A:
	btst	#3,(ram_C354).w
	bne.w	loc_1D2480
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_1D23B4
	neg.w	d0
loc_1D23B4:
	cmp.w	#$76,d0	; general form
	blt.w	loc_1D2480
	tst.w	(ram_B7C0).w
	bmi.w	loc_1D2480
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	adda.w	d0,a0
	move.b	$62(a0),d0
	move.b	$62(a3),d1
	eor.b	d1,d0
	btst	#6,d0
	beq.w	loc_1D2480
	btst	#3,(ram_C33C).w
	beq.w	loc_1D2480
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	move.w	(ram_B774).w,d1
	sub.w	$14(a3),d1
	jsr	(sub_01F186).l
	move.w	d0,-(sp)
	move.w	(ram_B760).w,d0
	move.w	#$11E,d1
	btst	#7,$62(a3)
	beq.w	loc_1D2418
	neg.w	d1
loc_1D2418:
	sub.w	(ram_B774).w,d1
	neg.w	d1
	jsr	(sub_01F186).l
	cmp.w	(sp)+,d0
	bne.w	loc_1D2480
	movem.w	d0,-(sp)
	move.w	(a3),d1
	move.w	(ram_B760).w,d0
	eor.w	d0,d1
	movem.w	(sp)+,d0
	bmi.w	loc_1D2480
	move.w	(ram_B774).w,d1
	sub.w	$14(a3),d1
	bpl.w	loc_1D244C
	neg.w	d1
loc_1D244C:
	cmp.w	#$BE,d1	; general form
	bgt.w	loc_1D2480
	cmp.w	$54(a3),d0
	beq.w	loc_1D2478
	addq.w	#1,d0
	andi.w	#$3,d0
	cmp.w	$54(a3),d0
	beq.w	loc_1D2478
	subq.w	#2,d0
	andi.w	#$3,d0
	cmp.w	$54(a3),d0
	bne.w	loc_1D2480
loc_1D2478:
	move.w	#$1,d0
	bra.w	loc_1D2482
loc_1D2480:
	clr.w	d0
loc_1D2482:
	movem.l	(sp)+,d0-d3/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $1D03A4
sub_1D2488:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_DE40,a0
	movea.l	#ram_C732,a1
	bsr.w	sub_1D24B2
	movea.l	#ram_DE5E,a0
	movea.l	#ram_CAD0,a1
	bsr.w	sub_1D24B2
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D2498, $1D24A8
sub_1D24B2:
	move.w	$C(a1),(a0)+
	move.w	(a1),(a0)+
	addq.w	#2,a0
	move.w	$2(a1),(a0)+
	move.w	$4(a1),(a0)+
	move.w	$390(a1),(a0)+
	move.w	$392(a1),(a0)+
	move.w	$398(a1),(a0)+
	move.w	$396(a1),(a0)+
	move.w	$39A(a1),(a0)+
	move.w	$E(a1),(a0)+
	move.w	$10(a1),(a0)+
	move.w	$6(a1),(a0)+
	move.w	$12(a1),(a0)+
	move.w	$14(a1),(a0)+
	rts


; ----------------------------------------------------------------------
; called from $1E434C
sub_1D24EC:
	clr.b	(ram_DEAE).w
	clr.b	(ram_DEAF).w
	clr.b	(ram_DEAC).w
	bsr.w	sub_1D25F2
	clr.b	(ram_DEB2).w
	clr.b	(ram_DEB3).w
	clr.w	(ram_D288).w
	clr.b	(ram_DEF8).w
	clr.b	(ram_DEF9).w
	clr.w	(ram_DEFA).w
	clr.w	(ram_DEFC).w
	lea	(ram_DEFE).w,a0
	moveq	#$6,d0
loc_1D251E:
	move.w	#$2,$E(a0)
	move.w	#$2,(a0)+
	dbra	d0,loc_1D251E
	rts


; ----------------------------------------------------------------------
; called from $023E4C
sub_1D252E:
	movem.l	d0-d7/a0-a6,-(sp)
	cmpa.l	#ram_C732,a2
	beq.s	loc_1D2554
	tst.w	(ram_C394).w
	bne.w	loc_1D25EC
	addq.b	#1,(ram_DEB3).w
	clr.b	(ram_DEB2).w
	movea.l	#ram_C732,a2
	bra.w	loc_1D256A
loc_1D2554:
	tst.w	(ram_C396).w
	bne.w	loc_1D25EC
	addq.b	#1,(ram_DEB2).w
	clr.b	(ram_DEB3).w
	movea.l	#ram_CAD0,a2
loc_1D256A:
	move.b	(ram_DEB2).w,d1
	cmp.b	(ram_DEAD).w,d1
	bne.s	loc_1D257C
	clr.b	(ram_DEB2).w
	bra.w	loc_1D258A
loc_1D257C:
	move.b	(ram_DEB3).w,d1
	cmp.b	(ram_DEAD).w,d1
	bne.s	loc_1D25EC
	clr.b	(ram_DEB3).w
loc_1D258A:
	jsr	(sub_01A268).l
	move.w	$26(a2),d1
	cmp.w	d0,d1
	beq.s	loc_1D259E
	addq.w	#1,d1
	bra.w	loc_1D25A0
loc_1D259E:
	moveq	#$0,d1
loc_1D25A0:
	cmpa.l	#ram_C732,a2
	beq.s	loc_1D25B6
	tst.b	(ram_DEF9).w
	bne.s	loc_1D25EC
	st	(ram_DEF9).w
	bra.w	loc_1D25C0
loc_1D25B6:
	tst.b	(ram_DEF8).w
	bne.s	loc_1D25EC
	st	(ram_DEF8).w
loc_1D25C0:
	move.w	d1,$26(a2)
	jsr	(sub_025122).l
	jsr	(Text_PrintScoreboard).l
inl_1D25D0:
	dc.w	loc_1D25EC-inl_1D25D0
	dc.b	$F8,$04,$01,$07,$0E
	dc.b	" GOALTENDER CHANGED ",0
loc_1D25EC:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D24F8
sub_1D25F2:
	jsr	(Random).l
	andi.b	#$3,d0
	addq.b	#3,d0
	move.b	d0,(ram_DEAD).w
	rts


; ----------------------------------------------------------------------
; called from $1E436E
sub_1D2604:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Joypad_Read1).l
	tst.b	d3
	beq.s	loc_1D2638
	cmp.b	(ram_DEAF).w,d3
	beq.s	loc_1D2638
	move.b	d3,(ram_DEAF).w
	moveq	#$0,d7
	move.b	(ram_DEAE).w,d7
	asl.b	#2,d7
	jsr	dat_1D263E(pc,d7.w)
	tst.b	d7
	bpl.s	loc_1D2638
	cmpi.b	#$B,(ram_DEAE).w
	bne.s	loc_1D2638
	st	(ram_DEB0).w
loc_1D2638:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D263E:
	dc.w	$6000,$002A,$6000,$0030,$6000,$0036,$6000,$001E
	dc.w	$6000,$0038,$6000,$0016,$6000,$003A,$6000,$000E
	dc.w	$6000,$0014,$6000,$001A,$6000,$0002,$0803,$0006
	dc.w	$6730,$6000,$0026,$0803,$0004,$6726,$6000,$001C
	dc.w	$0803,$0003,$671C,$6000,$0012,$0803,$0005,$6712
	dc.w	$6000,$0008,$0803,$0001,$6708,$5238,$DEAE,$50C7
	dc.w	$4E75,$4238,$DEAE,$4207,$4E75


; ----------------------------------------------------------------------
; called from $0190B6
sub_1D26A8:
	cmpi.w	#$5,(ram_DEF4).w
	ble.s	loc_1D26B2
	rts
loc_1D26B2:
	move.w	#$2300,sr
	move.l	#VBlank_Main,(VBlankVector).w
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
inl_1D272E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D2736:
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_2716).l
	addi.w	#$A0,d4
	move.w	d4,(ram_2718).l
	addi.w	#$A0,d4
	move.w	d4,-(sp)
	jsr	(Text_PrintCmd).l
inl_1D2768:
	dc.w	loc_1D2770-inl_1D2768
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D2770:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	(sp)+,d4
	jsr	(Text_Print).l
inl_1D2786:
	dc.w	loc_1D278C-inl_1D2786
	dc.b	$FE,$00,$00,$00
loc_1D278C:
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
	move.w	d4,-(sp)
	jsr	(Text_PrintBig).l
inl_1D27B2:
	dc.w	loc_1D27C2-inl_1D27B2
	dc.b	$FF,$0A,$01
	dc.b	"TODAYS GAME"
loc_1D27C2:
	jsr	(Text_Print).l
inl_1D27C8:
	dc.w	loc_1D27CE-inl_1D27C8
	dc.b	$BF,$01,$06,$00
loc_1D27CE:
	move.w	(ram_C3AC).w,d7
	move.w	(ram_2716).l,d4
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	jsr	(Text_Print).l
inl_1D27EC:
	dc.w	loc_1D27F2-inl_1D27EC
	dc.b	$8F,$01,$10,$00
loc_1D27F2:
	move.w	(ram_C3AE).w,d7
	move.w	(ram_2718).l,d4
	clr.w	d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	jsr	(Text_PrintCmd).l
inl_1D2810:
	dc.w	loc_1D2818-inl_1D2810
	dc.b	$FF,$01,$FD,$00,$FC,$0E
loc_1D2818:
	moveq	#$28,d0
	moveq	#$2,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintCmd).l
inl_1D282C:
	dc.w	loc_1D2834-inl_1D282C
	dc.b	$FF,$01,$FD,$00,$FC,$18
loc_1D2834:
	moveq	#$28,d0
	moveq	#$2,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintNarrow).l
inl_1D2848:
	dc.w	loc_1D2876-inl_1D2848
	dc.b	$F8,$04,$01,$05,$04
	dc.b	"EA SPORTS HOCKEY NIGHT PRESENTS"
	dc.w	$F804,$0114,$0E56,$5300
loc_1D2876:
	jsr	(Text_PrintNarrow).l
inl_1D287C:
	dc.w	loc_1D28A4-inl_1D287C
	dc.b	$F8,$04,$01,$12,$09
	dc.b	"HOT:"
	dc.b	$F8,$04,$01,$12,$0B
	dc.b	"COLD:"
	dc.b	$F8,$04,$01,$12,$13
	dc.b	"HOT:"
	dc.b	$F8,$04,$01,$12,$15
	dc.b	"COLD:"
loc_1D28A4:
	move.w	(sp)+,d4
	jsr	(Text_Print).l
inl_1D28AC:
	dc.w	loc_1D28B2-inl_1D28AC
	dc.b	$BF,$12,$07,$00
loc_1D28B2:
	move.w	(ram_C3AC).w,d7
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	jsr	(Text_Print).l
inl_1D28C6:
	dc.w	loc_1D28CC-inl_1D28C6
	dc.b	$BF,$12,$11,$00
loc_1D28CC:
	move.w	(ram_C3AE).w,d7
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	#$0,(TextAttr).w
	move.w	#$0,(TextPlaneOffset).w
	movea.w	#$C732,a2
	move.w	#$16,d0
	bsr.w	sub_1D2A58
	move.w	d0,(ram_DEBA).w
loc_1D28F6:
	move.w	#$16,d0
	bsr.w	sub_1D2A58
	cmp.w	(ram_DEBA).w,d0
	beq.s	loc_1D28F6
	move.w	d0,(ram_DEBC).w
loc_1D2908:
	move.w	#$16,d0
	bsr.w	sub_1D2A58
	cmp.w	(ram_DEBA).w,d0
	beq.s	loc_1D2908
	cmp.w	(ram_DEBC).w,d0
	beq.s	loc_1D2908
	move.w	d0,(ram_DEBE).w
loc_1D2920:
	move.w	#$16,d0
	bsr.w	sub_1D2A58
	cmp.w	(ram_DEBA).w,d0
	beq.s	loc_1D2920
	cmp.w	(ram_DEBC).w,d0
	beq.s	loc_1D2920
	cmp.w	(ram_DEBE).w,d0
	beq.s	loc_1D2920
	move.w	d0,(ram_DEC0).w
	move.w	(ram_C3AC).w,d0
	cmp.w	(ram_C3AE).w,d0
	bne.s	loc_1D2954
	move.w	(ram_DEBA).w,(ram_DEBE).w
	move.w	(ram_DEBC).w,(ram_DEC0).w
loc_1D2954:
	move.w	(ram_DEBA).w,d0
	jsr	(sub_0286D8).l
	move.w	#$18,(TextX).w
	move.w	#$9,(TextY).w
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(ram_DEBC).w,d0
	jsr	(sub_0286D8).l
	move.w	#$18,(TextX).w
	move.w	#$B,(TextY).w
	jsr	(Text_PrintNarrow_Worker).l
	adda.w	#$39E,a2
	move.w	(ram_DEBE).w,d0
	jsr	(sub_0286D8).l
	move.w	#$18,(TextX).w
	move.w	#$13,(TextY).w
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(ram_DEC0).w,d0
	jsr	(sub_0286D8).l
	move.w	#$18,(TextX).w
	move.w	#$15,(TextY).w
	jsr	(Text_PrintNarrow_Worker).l
	move.w	#$2500,sr
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	#$2A30,(ram_D330).w
loc_1D29DE:
	move.w	(FrameCounter).w,d0
loc_1D29E2:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D29E2
	jsr	(sub_00E59A).l
	btst	#7,(ram_BF55).w
	bne.s	loc_1D2A06
	tst.w	(ram_D294).w
	bne.s	loc_1D29DE
	subq.w	#1,(ram_D330).w
	bpl.s	loc_1D29DE
	clr.w	(ram_D294).w
loc_1D2A06:
	rts


; ----------------------------------------------------------------------
; called from $1DC27C
sub_1D2A08:
	movem.l	d0/d1,-(sp)
	move.w	(ram_D288).w,d0
	add.w	d0,d0
	move.w	dat_1D2A28(pc,d0.w),d1
	add.w	d1,(ram_D2A2).w
	move.w	dat_1D2A2E(pc,d0.w),d1
	add.w	d1,(ram_D2A4).w
	movem.l	(sp)+,d0/d1
	rts
dat_1D2A28:
	dc.b	$00,$00,$00,$02,$FF,$FE
dat_1D2A2E:
	dc.b	$00,$00,$00,$02,$FF,$FE


; ----------------------------------------------------------------------
; called from $00E622
sub_1D2A34:
	move.l	(ram_C398).w,-(sp)
	move.l	(ram_C394).w,-(sp)
	jsr	(sub_00DE78).l
	move.l	(ram_C394).w,(ram_C39C).w
	move.l	(ram_C398).w,(ram_C3A0).w
	move.l	(sp)+,(ram_C394).w
	move.l	(sp)+,(ram_C398).w
	rts


; ----------------------------------------------------------------------
; called from $1D28EE, $1D28FA, $1D290C, $1D2924
sub_1D2A58:
	jsr	(Random).l
	andi.w	#$1F,d0
	cmp.w	#$17,d0	; general form
	blt.s	loc_1D2A6C
	subi.w	#$A,d0
loc_1D2A6C:
	rts


; ----------------------------------------------------------------------
; called from $024AAA
sub_1D2A6E:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_DEC8).w,d1
	bmi.s	loc_1D2A94
	cmp.w	#$76,d1	; general form
	bge.s	loc_1D2A8A
	cmpi.w	#$FF8A,(ram_B774).w
	ble.s	loc_1D2AB0
	bra.w	loc_1D2AFA
loc_1D2A8A:
	tst.w	(ram_B774).w
	bmi.s	loc_1D2AB0
	bra.w	loc_1D2AFA
loc_1D2A94:
	cmp.w	#$FF8A,d1	; general form
	ble.s	loc_1D2AA6
	cmpi.w	#$76,(ram_B774).w
	bge.s	loc_1D2AB0
	bra.w	loc_1D2AFA
loc_1D2AA6:
	tst.w	(ram_B774).w
	bpl.s	loc_1D2AB0
	bra.w	loc_1D2AFA
loc_1D2AB0:
	btst	#6,$62(a2)
	beq.s	loc_1D2AD4
	btst	#7,$62(a2)
	bne.s	loc_1D2ACA
	cmp.w	(ram_B774).w,d1
	blt.s	loc_1D2AFA
	bra.w	loc_1D2AEC
loc_1D2ACA:
	cmp.w	(ram_B774).w,d1
	bgt.s	loc_1D2AFA
	bra.w	loc_1D2AEC
loc_1D2AD4:
	btst	#7,$62(a2)
	bne.s	loc_1D2AE6
	cmp.w	(ram_B774).w,d1
	blt.s	loc_1D2AFA
	bra.w	loc_1D2AEC
loc_1D2AE6:
	cmp.w	(ram_B774).w,d1
	bgt.s	loc_1D2AFA
loc_1D2AEC:
	movea.l	(ram_DECA).w,a3
	move.w	#$3A,d0
	jsr	(sub_02135E).l
loc_1D2AFA:
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$1204,$1206,$1208,$120A,$120C,$120E,$1210,$1212
	dc.w	$1214,$1216


; ----------------------------------------------------------------------
; called from $1DB224
sub_1D2B14:
	move.w	#$2300,sr
	move.l	#VBlank_Main,(VBlankVector).w
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
	jsr	(Text_PrintCmd).l
inl_1D2B7E:
	dc.w	loc_1D2B86-inl_1D2B7E
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D2B86:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	#$1,d4
	move.w	d4,(ram_DEDA).w
	move.l	#Art_1A861E,(ram_DEDE).w
	movea.l	#Art_1A861E_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEE2).w
	move.l	#Art_1A8F2C,(ram_DEE6).w
	movea.l	#Art_1A8F2C_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEEA).w
	move.l	#Font_Menu,(ram_DEEE).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D2BE0:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D2BE8:
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_Print).l
inl_1D2BFE:
	dc.w	loc_1D2C04-inl_1D2BFE
	dc.b	$FE,$00,$00,$00
loc_1D2C04:
	movea.l	#Art_MenuBackground,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	move.w	#$400,d4
	movea.l	#Art_1A7990_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_Print).l
inl_1D2C38:
	dc.w	loc_1D2C3E-inl_1D2C38
	dc.b	$FF,$03,$05,$00
loc_1D2C3E:
	movea.l	#Art_NHL98Logo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$E,d2
	moveq	#$B,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_PrintBig).l
inl_1D2C62:
	dc.w	loc_1D2C70-inl_1D2C62
	dc.b	$FF,$0C,$01
	dc.b	"MAIN MENU"
loc_1D2C70:
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D2C82:
	dc.w	loc_1D2C98-inl_1D2C82
	dc.b	$BF,$0C,$1A
	dc.b	"{} selects option"
loc_1D2C98:
	clr.w	(ram_DED8).w
	bsr.w	sub_1D2D22
	move.w	#$2500,sr
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	#$2A30,(ram_D330).w
loc_1D2CB6:
	move.w	(FrameCounter).w,d0
loc_1D2CBA:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D2CBA
	jsr	(sub_00E59A).l
	btst	#7,(ram_BF55).w
	beq.s	loc_1D2CD6
	move.w	(ram_DED8).w,(ram_DEF4).w
	rts
loc_1D2CD6:
	btst	#1,d1
	beq.w	loc_1D2CF4
	cmpi.w	#$9,(ram_DED8).w
	bne.s	loc_1D2CEC
	move.w	#$FFFF,(ram_DED8).w
loc_1D2CEC:
	addq.w	#1,(ram_DED8).w
	bra.w	loc_1D2D0C
loc_1D2CF4:
	btst	#0,d1
	beq.w	loc_1D2D10
	tst.w	(ram_DED8).w
	bne.s	loc_1D2D08
	move.w	#$A,(ram_DED8).w
loc_1D2D08:
	subq.w	#1,(ram_DED8).w
loc_1D2D0C:
	bsr.w	sub_1D2D22
loc_1D2D10:
	tst.w	(ram_D294).w
	bne.s	loc_1D2CB6
	subq.w	#1,(ram_D330).w
	bpl.s	loc_1D2CB6
	clr.w	(ram_D294).w
	rts


; ----------------------------------------------------------------------
; called from $1D2C9C, $1D2D0C
sub_1D2D22:
	move.w	#$13,d0
	moveq	#$4,d1
	move.w	#$F,d2
	moveq	#$0,d3
loc_1D2D2E:
	tst.w	d3
	beq.s	loc_1D2D40
	cmp.w	#$9,d3	; general form
	bne.s	loc_1D2D48
	bsr.w	sub_1D31A8
	bra.w	loc_1D2D4C
loc_1D2D40:
	bsr.w	sub_1D3170
	bra.w	loc_1D2D4C
loc_1D2D48:
	bsr.w	sub_1D318C
loc_1D2D4C:
	addq.w	#1,d3
	cmp.w	#$A,d3	; general form
	bne.s	loc_1D2D2E
	move.w	(ram_DED8).w,d1
	asl.w	#1,d1
	addq.w	#4,d1
	tst.w	(ram_DED8).w
	bne.s	loc_1D2D6A
	bsr.w	sub_1D311C
	bra.w	loc_1D2D7E
loc_1D2D6A:
	cmpi.w	#$9,(ram_DED8).w
	bne.s	loc_1D2D7A
	bsr.w	sub_1D3154
	bra.w	loc_1D2D7E
loc_1D2D7A:
	bsr.w	sub_1D3138
loc_1D2D7E:
	moveq	#$0,d5
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2D8A:
	dc.w	loc_1D2DA0-inl_1D2D8A
	dc.b	$BF,$14,$05
	dc.b	"  regular game  ",0
loc_1D2DA0:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2DAA:
	dc.w	loc_1D2DC0-inl_1D2DAA
	dc.b	$BF,$14,$07
	dc.b	"continue playoff",0
loc_1D2DC0:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2DCA:
	dc.w	loc_1D2DE0-inl_1D2DCA
	dc.b	$BF,$14,$09
	dc.b	"  new playoffs  ",0
loc_1D2DE0:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2DEA:
	dc.w	loc_1D2E00-inl_1D2DEA
	dc.b	$BF,$14,$0B
	dc.b	"playoffs best/7 ",0
loc_1D2E00:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2E0A:
	dc.w	loc_1D2E20-inl_1D2E0A
	dc.b	$BF,$14,$0D
	dc.b	"continue season ",0
loc_1D2E20:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2E2A:
	dc.w	loc_1D2E40-inl_1D2E2A
	dc.b	$BF,$14,$0F
	dc.b	"   new season   ",0
loc_1D2E40:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2E4A:
	dc.w	loc_1D2E60-inl_1D2E4A
	dc.b	$BF,$14,$11
	dc.b	"    shootout    ",0
loc_1D2E60:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2E6A:
	dc.w	loc_1D2E80-inl_1D2E6A
	dc.b	$BF,$14,$13
	dc.b	"  transactions  ",0
loc_1D2E80:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2E8A:
	dc.w	loc_1D2EA0-inl_1D2E8A
	dc.b	$BF,$14,$15
	dc.b	"    practice    ",0
loc_1D2EA0:
	bsr.w	sub_1D2EC2
	jsr	(Text_PrintFont).l
inl_1D2EAA:
	dc.w	loc_1D2EC0-inl_1D2EAA
	dc.b	$BF,$14,$17
	dc.b	"skills challenge",0
loc_1D2EC0:
	rts


; ----------------------------------------------------------------------
; called from $1D2D80, $1D2DA0, $1D2DC0, $1D2DE0, $1D2E00, $1D2E20, $1D2E40, $1D2E60 (+2 more)
sub_1D2EC2:
	cmp.w	(ram_DED8).w,d5
	beq.s	loc_1D2ED8
	move.l	(ram_DEE6).w,(FontPtr).w
	move.l	(ram_DEE2).w,(FontTileBase).w
	addq.w	#1,d5
	rts
loc_1D2ED8:
	move.l	(ram_DEDE).w,(FontPtr).w
	move.l	(ram_DEDA).w,(FontTileBase).w
	addq.w	#1,d5
	rts


; ----------------------------------------------------------------------
; called from $1DB384
sub_1D2EE8:
	move.w	(ram_D01A).w,d0
	cmp.w	(ram_DEF6).w,d0
	bne.s	sub_1D2EF4
	rts


; ----------------------------------------------------------------------
; called from $1D2EF0, $1DB354
sub_1D2EF4:
	move.w	d0,(ram_DEF6).w
	moveq	#$15,d0
	moveq	#$5,d1
	move.w	#$F,d2
	moveq	#$0,d3
loc_1D2F02:
	tst.w	d3
	beq.s	loc_1D2F14
	cmp.w	#$8,d3	; general form
	bne.s	loc_1D2F1C
	bsr.w	sub_1D31A8
	bra.w	loc_1D2F20
loc_1D2F14:
	bsr.w	sub_1D3170
	bra.w	loc_1D2F20
loc_1D2F1C:
	bsr.w	sub_1D318C
loc_1D2F20:
	addq.w	#1,d3
	cmp.w	#$9,d3	; general form
	bne.s	loc_1D2F02
	move.w	(ram_D01A).w,d1
	asl.w	#1,d1
	addq.w	#5,d1
	tst.w	(ram_D01A).w
	bne.s	loc_1D2F3E
	bsr.w	sub_1D311C
	bra.w	loc_1D2F52
loc_1D2F3E:
	cmpi.w	#$8,(ram_D01A).w
	bne.s	loc_1D2F4E
	bsr.w	sub_1D3154
	bra.w	loc_1D2F52
loc_1D2F4E:
	bsr.w	sub_1D3138
loc_1D2F52:
	rts


; ----------------------------------------------------------------------
; called from $1D4768, $1D47BC, $1D4822, $1D4876, $1D48DC, $1D4942, $1D4996, $1D49FC (+16 more)
sub_1D2F54:
	cmp.w	(ram_D01A).w,d5
	beq.s	loc_1D2F68
	move.l	(ram_DEE6).w,(FontPtr).w
	move.l	(ram_DEE2).w,(FontTileBase).w
	rts
loc_1D2F68:
	move.l	(ram_DEDE).w,(FontPtr).w
	move.l	(ram_DEDA).w,(FontTileBase).w
	rts


; ----------------------------------------------------------------------
; called from $1D43D2
sub_1D2F76:
	move.w	(ram_D01A).w,d0
	cmp.w	(ram_DEF6).w,d0
	bne.s	sub_1D2F82
	rts


; ----------------------------------------------------------------------
; called from $1D2F7E, $1D43B6
sub_1D2F82:
	move.w	d0,(ram_DEF6).w
	moveq	#$15,d0
	moveq	#$5,d1
	move.w	#$F,d2
	moveq	#$0,d3
loc_1D2F90:
	tst.w	d3
	beq.s	loc_1D2FA2
	cmp.w	#$7,d3	; general form
	bne.s	loc_1D2FAA
	bsr.w	sub_1D31A8
	bra.w	loc_1D2FAE
loc_1D2FA2:
	bsr.w	sub_1D3170
	bra.w	loc_1D2FAE
loc_1D2FAA:
	bsr.w	sub_1D318C
loc_1D2FAE:
	addq.w	#1,d3
	cmp.w	#$8,d3	; general form
	bne.s	loc_1D2F90
	move.w	(ram_D01A).w,d1
	asl.w	#1,d1
	addq.w	#5,d1
	tst.w	(ram_D01A).w
	bne.s	loc_1D2FCC
	bsr.w	sub_1D311C
	bra.w	loc_1D2FE0
loc_1D2FCC:
	cmpi.w	#$7,(ram_D01A).w
	bne.s	loc_1D2FDC
	bsr.w	sub_1D3154
	bra.w	loc_1D2FE0
loc_1D2FDC:
	bsr.w	sub_1D3138
loc_1D2FE0:
	rts


; ----------------------------------------------------------------------
; called from $1D5F2E
sub_1D2FE2:
	move.w	(ram_D01A).w,d0
	cmp.w	(ram_DEF6).w,d0
	bne.s	sub_1D2FEE
	rts


; ----------------------------------------------------------------------
; called from $1D2FEA, $1D5F00, $1D5FF4
sub_1D2FEE:
	move.w	d0,(ram_DEF6).w
	moveq	#$B,d0
	moveq	#$5,d1
	move.w	#$F,d2
	moveq	#$0,d3
loc_1D2FFC:
	tst.w	d3
	beq.s	loc_1D300E
	cmp.w	#$6,d3	; general form
	bne.s	loc_1D3016
	bsr.w	sub_1D31A8
	bra.w	loc_1D301A
loc_1D300E:
	bsr.w	sub_1D3170
	bra.w	loc_1D301A
loc_1D3016:
	bsr.w	sub_1D318C
loc_1D301A:
	addq.w	#1,d3
	cmp.w	#$7,d3	; general form
	bne.s	loc_1D2FFC
	move.w	(ram_D01A).w,d1
	asl.w	#1,d1
	addq.w	#5,d1
	tst.w	(ram_D01A).w
	bne.s	loc_1D3038
	bsr.w	sub_1D311C
	bra.w	loc_1D304C
loc_1D3038:
	cmpi.w	#$6,(ram_D01A).w
	bne.s	loc_1D3048
	bsr.w	sub_1D3154
	bra.w	loc_1D304C
loc_1D3048:
	bsr.w	sub_1D3138
loc_1D304C:
	rts


; ----------------------------------------------------------------------
; called from $1D5F24
sub_1D304E:
	move.w	(ram_D01A).w,d0
	cmp.w	(ram_DEF6).w,d0
	bne.s	loc_1D305A
	rts
loc_1D305A:
	move.w	d0,(ram_DEF6).w
	move.w	#$11,d0
	moveq	#$E,d1
	moveq	#$4,d2
	moveq	#$0,d3
loc_1D3068:
	tst.w	d3
	beq.s	loc_1D307A
	cmp.w	#$1,d3	; general form
	bne.s	loc_1D3082
	bsr.w	sub_1D31A8
	bra.w	loc_1D3086
loc_1D307A:
	bsr.w	sub_1D3170
	bra.w	loc_1D3086
loc_1D3082:
	bsr.w	sub_1D318C
loc_1D3086:
	addq.w	#1,d3
	cmp.w	#$2,d3	; general form
	bne.s	loc_1D3068
	move.w	(ram_D01A).w,d1
	asl.w	#1,d1
	addi.w	#$E,d1
	tst.w	(ram_D01A).w
	bne.s	loc_1D30A6
	bsr.w	sub_1D311C
	bra.w	loc_1D30BA
loc_1D30A6:
	cmpi.w	#$1,(ram_D01A).w
	bne.s	loc_1D30B6
	bsr.w	sub_1D3154
	bra.w	loc_1D30BA
loc_1D30B6:
	bsr.w	sub_1D3138
loc_1D30BA:
	rts

	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0000,$0000,$0000,$0000,$0000,$0000,$0000,$0000
	dc.w	$0A05,$0900,$0A08,$0400,$050B,$0B00,$080F,$0E00
	dc.w	$FFFF,$48E7,$FFFE,$41F9,$001D,$30BC,$4CD8,$00FF
	dc.w	$2078,$DED4,$B1FC,$0000,$0000,$6700,$000E,$1018
	dc.w	$6B08,$1218,$1418,$1618,$60F4,$4CDF,$7FFF,$4E75


; ----------------------------------------------------------------------
; called from $1D2D62, $1D2F36, $1D2FC4, $1D3030, $1D309E
sub_1D311C:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D31C4
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32A4
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	loc_1D3264


; ----------------------------------------------------------------------
; called from $1D2D7A, $1D2F4E, $1D2FDC, $1D3048, $1D30B6
sub_1D3138:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D3244
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32A4
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	loc_1D3264


; ----------------------------------------------------------------------
; called from $1D2D72, $1D2F46, $1D2FD4, $1D3040, $1D30AE
sub_1D3154:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D3244
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32A4
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	loc_1D31E4


; ----------------------------------------------------------------------
; called from $1D2D40, $1D2F14, $1D2FA2, $1D300E, $1D307A
sub_1D3170:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D3204
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32CA
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	sub_1D3284


; ----------------------------------------------------------------------
; called from $1D2D48, $1D2F1C, $1D2FAA, $1D3016, $1D3082
sub_1D318C:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D3284
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32CA
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	sub_1D3284


; ----------------------------------------------------------------------
; called from $1D2D38, $1D2F0C, $1D2F9A, $1D3006, $1D3072
sub_1D31A8:
	bsr.w	sub_1D32F0
	bsr.w	sub_1D3284
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bsr.w	sub_1D32CA
	addq.w	#1,d1
	bsr.w	sub_1D32F0
	bra.w	loc_1D3224


; ----------------------------------------------------------------------
; called from $1D3120
sub_1D31C4:
	move.w	#$8407,(VDP_DATA).l
	move.w	d2,d4
loc_1D31CE:
	move.w	#$8408,(VDP_DATA).l
	dbra	d4,loc_1D31CE
	move.w	#$8409,(VDP_DATA).l
	rts
loc_1D31E4:
	move.w	#$840B,(VDP_DATA).l
	move.w	d2,d4
loc_1D31EE:
	move.w	#$840C,(VDP_DATA).l
	dbra	d4,loc_1D31EE
	move.w	#$840D,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D3174
sub_1D3204:
	move.w	#$8400,(VDP_DATA).l
	move.w	d2,d4
loc_1D320E:
	move.w	#$8401,(VDP_DATA).l
	dbra	d4,loc_1D320E
	move.w	#$8402,(VDP_DATA).l
	rts
loc_1D3224:
	move.w	#$8404,(VDP_DATA).l
	move.w	d2,d4
loc_1D322E:
	move.w	#$8405,(VDP_DATA).l
	dbra	d4,loc_1D322E
	move.w	#$8406,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D313C, $1D3158
sub_1D3244:
	move.w	#$840E,(VDP_DATA).l
	move.w	d2,d4
loc_1D324E:
	move.w	#$840F,(VDP_DATA).l
	dbra	d4,loc_1D324E
	move.w	#$8410,(VDP_DATA).l
	rts
loc_1D3264:
	move.w	#$8411,(VDP_DATA).l
	move.w	d2,d4
loc_1D326E:
	move.w	#$8412,(VDP_DATA).l
	dbra	d4,loc_1D326E
	move.w	#$8413,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D3188, $1D3190, $1D31A4, $1D31AC
sub_1D3284:
	move.w	#$8414,(VDP_DATA).l
	move.w	d2,d4
loc_1D328E:
	move.w	#$8415,(VDP_DATA).l
	dbra	d4,loc_1D328E
	move.w	#$8416,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D312A, $1D3146, $1D3162
sub_1D32A4:
	move.w	#$840A,(VDP_DATA).l
	move.w	d2,d6
	addq.w	#2,d6
	asl.w	#1,d6
	add.w	(ram_DEF2).w,d6
	bsr.w	sub_1D331E
	move.l	d7,(VDP_CTRL).l
	move.w	#$1C0A,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D317E, $1D319A, $1D31B6
sub_1D32CA:
	move.w	#$8403,(VDP_DATA).l
	move.w	d2,d6
	addq.w	#2,d6
	asl.w	#1,d6
	add.w	(ram_DEF2).w,d6
	bsr.w	sub_1D331E
	move.l	d7,(VDP_CTRL).l
	move.w	#$9C03,(VDP_DATA).l
	rts


; ----------------------------------------------------------------------
; called from $1D311C, $1D3126, $1D3130, $1D3138, $1D3142, $1D314C, $1D3154, $1D315E (+16 more)
sub_1D32F0:
	move.w	d0,d6
	move.w	d1,d7
	asl.w	#7,d7
	asl.w	#1,d6
	add.w	d7,d6
	add.w	(PlaneAAddr).w,d6
	move.w	d6,(ram_DEF2).w
	move.w	d6,d7
	asl.l	#2,d7
	move.w	d6,d7
	swap	d7
	andi.l	#$3FFF0003,d7
	ori.l	#$40000000,d7
	move.l	d7,(VDP_CTRL).l
	rts


; ----------------------------------------------------------------------
; called from $1D32B6, $1D32DC
sub_1D331E:
	move.w	d6,d7
	asl.l	#2,d7
	move.w	d6,d7
	swap	d7
	andi.l	#$3FFF0003,d7
	ori.l	#$40000000,d7
	rts


; ----------------------------------------------------------------------
sub_1D3334:
	move.w	#$2300,sr
	move.l	#VBlank_Main,(VBlankVector).w
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
	cmpa.w	#$C732,a2
	beq.s	loc_1D33AA
	move.l	#$FFFFDF0C,(ram_DF1A).w
	move.w	(ram_C3AE).w,(ram_DF1E).w
	bra.w	loc_1D33B8
loc_1D33AA:
	move.l	#ram_DEFE,(ram_DF1A).w
	move.w	(ram_C3AC).w,(ram_DF1E).w
loc_1D33B8:
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(ram_DEDA).w
	move.l	#Art_1A861E,(ram_DEDE).w
	movea.l	#Art_1A861E_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEE2).w
	move.l	#Font_Menu,(ram_DEE6).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D33F2:
	dc.w	$0123,$4567,$8934,$CDEF
loc_1D33FA:
	move.w	d4,(ram_DEEA).w
	move.l	#Font_Menu,(ram_DEEE).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D3412:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D341A:
	move.w	d4,(ram_B014).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D342E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D3436:
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_2716).l
	addi.w	#$A0,d4
	move.w	d4,(ram_2718).l
	addi.w	#$A0,d4
	move.w	d4,-(sp)
	jsr	(Text_PrintCmd).l
inl_1D3468:
	dc.w	loc_1D3470-inl_1D3468
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D3470:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	(sp)+,d4
	jsr	(Text_Print).l
inl_1D3486:
	dc.w	loc_1D348C-inl_1D3486
	dc.b	$FE,$00,$00,$00
loc_1D348C:
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
	move.w	d4,-(sp)
	jsr	(Text_PrintBig).l
inl_1D34B2:
	dc.w	loc_1D34C6-inl_1D34B2
	dc.b	$FF,$08,$01
	dc.b	"COACHING STYLE",0
loc_1D34C6:
	jsr	(Text_Print).l
inl_1D34CC:
	dc.w	loc_1D34D2-inl_1D34CC
	dc.b	$BF,$17,$04,$00
loc_1D34D2:
	move.w	(ram_DF1E).w,d7
	move.w	(ram_2716).l,d4
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	move.w	#$64,(FadeCounter).w
	move.l	(ram_DEE6).w,(FontPtr).w
	move.l	(ram_DEE2).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D34FC:
	dc.w	loc_1D352C-inl_1D34FC
	dc.b	$BF,$0C,$19
	dc.b	"[] changes line"
	dc.b	$BF,$07,$1A
	dc.b	"{} changes coaching style"
loc_1D352C:
	jsr	(Text_PrintFont).l
inl_1D3532:
	dc.w	loc_1D356E-inl_1D3532
	dc.b	$BF,$08,$0A
	dc.b	"line :"
	dc.b	$BF,$07,$0C
	dc.b	"style :"
	dc.b	$BF,$02,$0F
	dc.b	"defenseman :"
	dc.b	$BF,$06,$12
	dc.b	"center :"
	dc.b	$BF,$05,$15
	dc.b	"wingman :",0
loc_1D356E:
	bsr.w	sub_1D3634
	move.w	(sp)+,d4
	move.w	#$2500,sr
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
loc_1D3584:
	move.w	(FrameCounter).w,d0
loc_1D3588:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D3588
	jsr	(sub_00E59A).l
	btst	#7,(ram_BF55).w
	bne.w	loc_1D3632
	btst	#2,(ram_BF55).w
	beq.s	loc_1D35BC
	tst.w	(ram_DEFC).w
	bne.s	loc_1D35B2
	move.w	#$7,(ram_DEFC).w
loc_1D35B2:
	subq.w	#1,(ram_DEFC).w
	bsr.w	sub_1D3634
	bra.s	loc_1D3584
loc_1D35BC:
	btst	#3,(ram_BF55).w
	beq.s	loc_1D35DC
	cmpi.w	#$6,(ram_DEFC).w
	bne.s	loc_1D35D2
	move.w	#$FFFF,(ram_DEFC).w
loc_1D35D2:
	addq.w	#1,(ram_DEFC).w
	bsr.w	sub_1D3634
	bra.s	loc_1D3584
loc_1D35DC:
	btst	#0,(ram_BF55).w
	beq.s	loc_1D3604
	movea.l	(ram_DF1A).w,a0
	move.w	(ram_DEFC).w,d0
	asl.w	#1,d0
	tst.w	$0(a0,d0.w)
	bne.s	loc_1D35FA
	move.w	#$5,$0(a0,d0.w)
loc_1D35FA:
	subq.w	#1,$0(a0,d0.w)
	bsr.w	sub_1D3634
	bra.s	loc_1D3584
loc_1D3604:
	btst	#1,(ram_BF55).w
	beq.w	loc_1D3584
	movea.l	(ram_DF1A).w,a0
	move.w	(ram_DEFC).w,d0
	asl.w	#1,d0
	cmpi.w	#$4,$0(a0,d0.w)
	bne.s	loc_1D3626
	move.w	#$FFFF,$0(a0,d0.w)
loc_1D3626:
	addq.w	#1,$0(a0,d0.w)
	bsr.w	sub_1D3634
	bra.w	loc_1D3584
loc_1D3632:
	rts


; ----------------------------------------------------------------------
; called from $1D356E, $1D35B6, $1D35D6, $1D35FE, $1D362A
sub_1D3634:
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	bsr.w	sub_1D3648
	bra.w	loc_1D36EA


; ----------------------------------------------------------------------
; called from $1D3640
sub_1D3648:
	tst.w	(ram_DEFC).w
	beq.w	loc_1D36DA
	cmpi.w	#$1,(ram_DEFC).w
	beq.w	loc_1D36CA
	cmpi.w	#$2,(ram_DEFC).w
	beq.s	loc_1D36BA
	cmpi.w	#$3,(ram_DEFC).w
	beq.s	loc_1D36AA
	cmpi.w	#$4,(ram_DEFC).w
	beq.s	loc_1D369A
	cmpi.w	#$5,(ram_DEFC).w
	beq.s	loc_1D368A
	jsr	(Text_PrintFont).l
inl_1D3680:
	dc.w	loc_1D3688-inl_1D3680
	dc.b	$BF,$0F,$0A,$70,$6B,$32
loc_1D3688:
	rts
loc_1D368A:
	jsr	(Text_PrintFont).l
inl_1D3690:
	dc.w	loc_1D3698-inl_1D3690
	dc.b	$BF,$0F,$0A,$70,$6B,$31
loc_1D3698:
	rts
loc_1D369A:
	jsr	(Text_PrintFont).l
inl_1D36A0:
	dc.w	loc_1D36A8-inl_1D36A0
	dc.b	$BF,$0F,$0A,$70,$70,$32
loc_1D36A8:
	rts
loc_1D36AA:
	jsr	(Text_PrintFont).l
inl_1D36B0:
	dc.w	loc_1D36B8-inl_1D36B0
	dc.b	$BF,$0F,$0A,$70,$70,$31
loc_1D36B8:
	rts
loc_1D36BA:
	jsr	(Text_PrintFont).l
inl_1D36C0:
	dc.w	loc_1D36C8-inl_1D36C0
	dc.b	$BF,$0F,$0A,$63,$68,$6B
loc_1D36C8:
	rts
loc_1D36CA:
	jsr	(Text_PrintFont).l
inl_1D36D0:
	dc.w	loc_1D36D8-inl_1D36D0
	dc.b	$BF,$0F,$0A,$73,$63,$32
loc_1D36D8:
	rts
loc_1D36DA:
	jsr	(Text_PrintFont).l
inl_1D36E0:
	dc.w	loc_1D36E8-inl_1D36E0
	dc.b	$BF,$0F,$0A,$73,$63,$31
loc_1D36E8:
	rts
loc_1D36EA:
	movea.l	(ram_DF1A).w,a0
	move.w	(ram_DEFC).w,d0
	asl.w	#1,d0
	move.w	$0(a0,d0.w),d0
	tst.w	d0
	beq.w	loc_1D3A96
	cmp.w	#$1,d0	; general form
	beq.w	loc_1D39B6
	cmp.w	#$2,d0	; general form
	beq.w	loc_1D38D6
	cmp.w	#$3,d0	; general form
	beq.w	loc_1D37F6
	jsr	(Text_PrintFont).l
inl_1D371C:
	dc.w	loc_1D3734-inl_1D371C
	dc.b	$BF,$0F,$0C
	dc.b	"all out "
	dc.b	$BF,$0F,$0D
	dc.b	"offense",0
loc_1D3734:
	jsr	(Text_PrintFont).l
inl_1D373A:
	dc.w	loc_1D376A-inl_1D373A
	dc.b	$BF,$0F,$0F
	dc.b	"plays between blue  "
	dc.b	$BF,$0F,$10
	dc.b	"lines              ",0
loc_1D376A:
	jsr	(Text_PrintFont).l
inl_1D3770:
	dc.w	loc_1D37A2-inl_1D3770
	dc.b	$BF,$0F,$12
	dc.b	"plays from beyond red"
	dc.b	$BF,$0F,$13
	dc.b	"line to opponents net"
loc_1D37A2:
	jsr	(Text_PrintFont).l
inl_1D37A8:
	dc.w	loc_1D37F4-inl_1D37A8
	dc.b	$BF,$0F,$15
	dc.b	"plays beyond red line"
	dc.b	$BF,$0F,$16
	dc.b	"                     "
	dc.b	$BF,$0F,$17
	dc.b	"                      ",0
loc_1D37F4:
	rts
loc_1D37F6:
	jsr	(Text_PrintFont).l
inl_1D37FC:
	dc.w	loc_1D3814-inl_1D37FC
	dc.b	$BF,$0F,$0C
	dc.b	"offense "
	dc.b	$BF,$0F,$0D
	dc.b	"       ",0
loc_1D3814:
	jsr	(Text_PrintFont).l
inl_1D381A:
	dc.w	loc_1D384A-inl_1D381A
	dc.b	$BF,$0F,$0F
	dc.b	"plays between blue  "
	dc.b	$BF,$0F,$10
	dc.b	"lines              ",0
loc_1D384A:
	jsr	(Text_PrintFont).l
inl_1D3850:
	dc.w	loc_1D3882-inl_1D3850
	dc.b	$BF,$0F,$12
	dc.b	"plays from opponents "
	dc.b	$BF,$0F,$13
	dc.b	"red line to net      "
loc_1D3882:
	jsr	(Text_PrintFont).l
inl_1D3888:
	dc.w	loc_1D38D4-inl_1D3888
	dc.b	$BF,$0F,$15
	dc.b	"plays from opponents "
	dc.b	$BF,$0F,$16
	dc.b	"red line to net      "
	dc.b	$BF,$0F,$17
	dc.b	"                      ",0
loc_1D38D4:
	rts
loc_1D38D6:
	jsr	(Text_PrintFont).l
inl_1D38DC:
	dc.w	loc_1D38F4-inl_1D38DC
	dc.b	$BF,$0F,$0C
	dc.b	"balanced"
	dc.b	$BF,$0F,$0D
	dc.b	"       ",0
loc_1D38F4:
	jsr	(Text_PrintFont).l
inl_1D38FA:
	dc.w	loc_1D392A-inl_1D38FA
	dc.b	$BF,$0F,$0F
	dc.b	"plays from opponents"
	dc.b	$BF,$0F,$10
	dc.b	"blue line and back ",0
loc_1D392A:
	jsr	(Text_PrintFont).l
inl_1D3930:
	dc.w	loc_1D3962-inl_1D3930
	dc.b	$BF,$0F,$12
	dc.b	"plays from opponents "
	dc.b	$BF,$0F,$13
	dc.b	"net and back         "
loc_1D3962:
	jsr	(Text_PrintFont).l
inl_1D3968:
	dc.w	loc_1D39B4-inl_1D3968
	dc.b	$BF,$0F,$15
	dc.b	"plays forward of     "
	dc.b	$BF,$0F,$16
	dc.b	"defending blue line  "
	dc.b	$BF,$0F,$17
	dc.b	"                      ",0
loc_1D39B4:
	rts
loc_1D39B6:
	jsr	(Text_PrintFont).l
inl_1D39BC:
	dc.w	loc_1D39D4-inl_1D39BC
	dc.b	$BF,$0F,$0C
	dc.b	"defense "
	dc.b	$BF,$0F,$0D
	dc.b	"       ",0
loc_1D39D4:
	jsr	(Text_PrintFont).l
inl_1D39DA:
	dc.w	loc_1D3A0A-inl_1D39DA
	dc.b	$BF,$0F,$0F
	dc.b	"plays red line back "
	dc.b	$BF,$0F,$10
	dc.b	"to face-off circles",0
loc_1D3A0A:
	jsr	(Text_PrintFont).l
inl_1D3A10:
	dc.w	loc_1D3A42-inl_1D3A10
	dc.b	$BF,$0F,$12
	dc.b	"plays between blue   "
	dc.b	$BF,$0F,$13
	dc.b	"lines                "
loc_1D3A42:
	jsr	(Text_PrintFont).l
inl_1D3A48:
	dc.w	loc_1D3A94-inl_1D3A48
	dc.b	$BF,$0F,$15
	dc.b	"plays from opponents "
	dc.b	$BF,$0F,$16
	dc.b	"face-off circles back"
	dc.b	$BF,$0F,$17
	dc.b	"to defending blue line",0
loc_1D3A94:
	rts
loc_1D3A96:
	jsr	(Text_PrintFont).l
inl_1D3A9C:
	dc.w	loc_1D3AB4-inl_1D3A9C
	dc.b	$BF,$0F,$0C
	dc.b	"all out "
	dc.b	$BF,$0F,$0D
	dc.b	"defense",0
loc_1D3AB4:
	jsr	(Text_PrintFont).l
inl_1D3ABA:
	dc.w	loc_1D3AEA-inl_1D3ABA
	dc.b	$BF,$0F,$0F
	dc.b	"plays just past blue"
	dc.b	$BF,$0F,$10
	dc.b	"line and back      ",0
loc_1D3AEA:
	jsr	(Text_PrintFont).l
inl_1D3AF0:
	dc.w	loc_1D3B22-inl_1D3AF0
	dc.b	$BF,$0F,$12
	dc.b	"plays red line back  "
	dc.b	$BF,$0F,$13
	dc.b	"to net               "
loc_1D3B22:
	jsr	(Text_PrintFont).l
inl_1D3B28:
	dc.w	loc_1D3B74-inl_1D3B28
	dc.b	$BF,$0F,$15
	dc.b	"plays opponents blue "
	dc.b	$BF,$0F,$16
	dc.b	"back to defense      "
	dc.b	$BF,$0F,$17
	dc.b	"face-off circle       ",0
loc_1D3B74:
	rts


; ----------------------------------------------------------------------
; called from $00F9AA, $0117B6
sub_1D3B76:
	move.w	$16(a2),d1
	asl.w	#1,d1
	movea.l	(ram_DF1A).w,a0
	move.w	$0(a0,d1.w),d1
	tst.w	d1
	beq.s	loc_1D3BA0
	cmp.w	#$1,d1	; general form
	beq.s	loc_1D3BCC
	cmp.w	#$2,d1	; general form
	beq.s	loc_1D3BF8
	cmp.w	#$3,d1	; general form
	beq.w	loc_1D3C24
	bra.w	loc_1D3C50
loc_1D3BA0:
	cmp.w	#$FF6C,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$94,d0	; general form
	blt.w	loc_1D3C78
	btst	#4,$30(a2)
	bne.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$11E,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	bra.w	loc_1D3C78
loc_1D3BCC:
	cmp.w	#$FF7B,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$85,d0	; general form
	blt.w	loc_1D3C78
	btst	#4,$30(a2)
	bne.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$11E,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	bra.w	loc_1D3C78
loc_1D3BF8:
	cmp.w	#$FF8A,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$76,d0	; general form
	blt.w	loc_1D3C78
	btst	#4,$30(a2)
	bne.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$11E,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	bra.w	loc_1D3C78
loc_1D3C24:
	cmp.w	#$FF99,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$67,d0	; general form
	blt.w	loc_1D3C78
	btst	#4,$30(a2)
	bne.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$11E,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	bra.w	loc_1D3C78
loc_1D3C50:
	cmp.w	#$FFA8,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$58,d0	; general form
	blt.w	loc_1D3C78
	btst	#4,$30(a2)
	bne.w	loc_1D3C78
	addq.w	#8,d2
	cmp.w	#$11E,d0	; general form
	blt.w	loc_1D3C78
	addq.w	#8,d2
loc_1D3C78:
	rts


; ----------------------------------------------------------------------
; called from $0119D8
sub_1D3C7A:
	move.w	$16(a2),d1
	asl.w	#1,d1
	movea.l	(ram_DF1A).w,a0
	move.w	$0(a0,d1.w),d1
	tst.w	d1
	beq.s	loc_1D3CA4
	cmp.w	#$1,d1	; general form
	beq.s	loc_1D3CD0
	cmp.w	#$2,d1	; general form
	beq.s	loc_1D3CFC
	cmp.w	#$3,d1	; general form
	beq.w	loc_1D3D28
	bra.w	loc_1D3D54
loc_1D3CA4:
	cmp.w	#$FF6C,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$94,d0	; general form
	blt.w	loc_1D3D7C
	btst	#4,$30(a2)
	bne.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$11E,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	bra.w	loc_1D3D7C
loc_1D3CD0:
	cmp.w	#$FF6C,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$94,d0	; general form
	blt.w	loc_1D3D7C
	btst	#4,$30(a2)
	bne.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$11E,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	bra.w	loc_1D3D7C
loc_1D3CFC:
	cmp.w	#$FF8A,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$76,d0	; general form
	blt.w	loc_1D3D7C
	btst	#4,$30(a2)
	bne.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$11E,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	bra.w	loc_1D3D7C
loc_1D3D28:
	cmp.w	#$FFA8,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$58,d0	; general form
	blt.w	loc_1D3D7C
	btst	#4,$30(a2)
	bne.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$11E,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	bra.w	loc_1D3D7C
loc_1D3D54:
	cmp.w	#$FFA8,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$58,d0	; general form
	blt.w	loc_1D3D7C
	btst	#4,$30(a2)
	bne.w	loc_1D3D7C
	addq.w	#8,d2
	cmp.w	#$11E,d3	; general form
	blt.w	loc_1D3D7C
	addq.w	#8,d2
loc_1D3D7C:
	rts


; ----------------------------------------------------------------------
sub_1D3D7E:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_D330).w
	bsr.w	sub_1D3E3E
	bsr.w	sub_1D3E40
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D168).w
loc_1D3D9E:
	bsr.w	sub_1D4034
	movea.l	#ram_D184,a0
	jsr	(sub_015176).l
	bsr.w	sub_1D3FE8
	bsr.w	sub_1D40B4
	bsr.w	sub_1D4134
	move.w	#$2500,sr
loc_1D3DBE:
	move.w	(FrameCounter).w,d0
loc_1D3DC2:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D3DC2
	cmpi.w	#$5460,(ram_D330).w
	jsr	(Joypad_ReadAll).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D3DE4
	clr.w	(ram_D330).w
loc_1D3DE4:
	btst	#7,d1
	bne.w	loc_1D3E30
	btst	#2,d1
	beq.w	loc_1D3DFC
	eori.w	#$1,(ram_D168).w
	bra.s	loc_1D3D9E
loc_1D3DFC:
	btst	#3,d1
	beq.w	loc_1D3E0C
	eori.w	#$1,(ram_D168).w
	bra.s	loc_1D3D9E
loc_1D3E0C:
	btst	#0,d1
	beq.w	loc_1D3E1C
	eori.w	#$2,(ram_D168).w
	bra.s	loc_1D3D9E
loc_1D3E1C:
	btst	#1,d1
	beq.w	loc_1D3E2E
	eori.w	#$2,(ram_D168).w
	bra.w	loc_1D3D9E
loc_1D3E2E:
	bra.s	loc_1D3DBE
loc_1D3E30:
	move.l	#sub_016614,(ram_DDD0).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D3D86
sub_1D3E3E:
	rts


; ----------------------------------------------------------------------
; called from $1D3D8A
sub_1D3E40:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B400,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$BC00,(HScrollTableAddr).w
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
inl_1D3EBA:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D3EC2:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D3EDA:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D3EE2:
	move.l	#Font_Narrow,(FontPtr2).w
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	#$19,d1
	clr.w	d2
	movea.l	#ram_2328,a0
	movea.l	#TeamArtTable,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1D3F20
	movea.l	#dat_017022,a1
loc_1D3F20:
	move.w	d4,(a0)+
	move.w	d2,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a2
	addq.w	#8,a2
	jsr	(sub_020780).l
	addq.w	#1,d2
	dbra	d1,loc_1D3F20
	jsr	(Text_PrintCmd).l
inl_1D3F3E:
	dc.w	loc_1D3F46-inl_1D3F3E
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D3F46:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1D3F5A:
	dc.w	loc_1D3F60-inl_1D3F5A
	dc.b	$FE,$00,$00,$00
loc_1D3F60:
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
inl_1D3F8A:
	dc.w	loc_1D3F9C-inl_1D3F8A
	dc.b	$BF,$08,$01
	dc.b	"NHL STANDINGS"
loc_1D3F9C:
	jsr	(Text_PrintFont).l
inl_1D3FA2:
	dc.w	loc_1D3FC0-inl_1D3FA2
	dc.b	$8F,$06,$1A
	dc.b	"{} CONFERENCE [] DIVISION"
loc_1D3FC0:
	jsr	(Text_PrintNarrow).l
inl_1D3FC6:
	dc.w	loc_1D3FE2-inl_1D3FC6
	dc.w	$F804,$0116,$0857,$F804,$011A,$084C,$F804,$011F
	dc.w	$0854,$F804,$0123,$0850,$5453
loc_1D3FE2:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $1D3DAE, $1E3BC4, $1E3D94, $1E3DCC
sub_1D3FE8:
	move.w	#$1A,d0
	movea.l	#ram_D184,a1
	movea.l	#ram_D14E,a2
	movea.l	#ram_D16A,a3
	clr.w	d2
	move.w	d1,-(sp)
	bra.w	loc_1D402C
loc_1D4006:
	move.w	d2,d5
	mulu.w	#$3,d2
	clr.w	d3
	move.b	$0(a1,d2.w),d3
	add.w	d3,d3
	clr.w	d1
	move.b	$1(a1,d2.w),d1
	add.w	d1,d3
	move.b	d3,$0(a2,d5.w)
	move.b	$0(a1,d2.w),d3
	move.b	d3,$0(a3,d5.w)
	move.w	d5,d2
	addq.w	#1,d2
loc_1D402C:
	dbra	d0,loc_1D4006
	move.w	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $1D3D9E, $1E3D82, $1E3DBA
sub_1D4034:
	movea.l	#dat_1D4062,a5
	move.w	(ram_D168).w,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a5
	clr.w	(ram_D14C).w
	move.b	(a5)+,(ram_D14D).w
	move.w	(ram_D14C).w,d0
	movea.l	#ram_D1D2,a4
	bra.w	loc_1D405C
loc_1D405A:
	move.b	(a5)+,(a4)+
loc_1D405C:
	dbra	d0,loc_1D405A
	rts
dat_1D4062:
	dc.w	$001D,$407A,$001D,$4082,$001D,$4089,$001D,$4090
	dc.w	$001D,$4098,$001D,$40A6,$0700,$0309,$0B14,$1806
	dc.w	$0605,$0708,$1517,$1206,$0102,$040C,$1013,$070A
	dc.w	$0D0E,$0F11,$1619
dat_1D4098:
	dc.w	$0D00,$0309,$0B14,$1806,$0507,$0815,$1712,$0D01
	dc.w	$0204,$0C10,$130A,$0D0E,$0F11,$1619


; ----------------------------------------------------------------------
; called from $1D3DB2, $1E3D9A, $1E3DD2
sub_1D40B4:
	movea.l	#ram_D1D2,a0
	movea.l	#ram_D14E,a1
	movea.l	#ram_D16A,a2
	move.w	d1,-(sp)
loc_1D40C8:
	bclr	#6,(TextFlags).w
	clr.w	d7
loc_1D40D0:
	clr.w	d6
	move.b	$0(a0,d7.w),d6
	clr.w	d0
	move.b	$0(a1,d6.w),d0
	move.b	$1(a0,d7.w),d6
	clr.w	d1
	move.b	$0(a1,d6.w),d1
	cmp.w	d1,d0
	bgt.w	loc_1D411A
	blt.w	loc_1D4104
	move.b	$0(a0,d7.w),d6
	move.b	$0(a2,d6.w),d0
	move.b	$1(a0,d7.w),d6
	cmp.b	$0(a2,d6.w),d0
	bge.w	loc_1D411A
loc_1D4104:
	bset	#6,(TextFlags).w
	move.b	$0(a0,d7.w),d5
	move.b	$1(a0,d7.w),d4
	move.b	d5,$1(a0,d7.w)
	move.b	d4,$0(a0,d7.w)
loc_1D411A:
	addq.w	#2,d7
	cmp.w	(ram_D14C).w,d7
	bge.w	loc_1D4128
	subq.w	#1,d7
	bra.s	loc_1D40D0
loc_1D4128:
	btst	#6,(TextFlags).w
	bne.s	loc_1D40C8
	move.w	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $1D3DB6
sub_1D4134:
	move.w	#$10,d0
	move.w	#$2,d1
	move.w	#$7FF,d2
	ori.w	#$8000,d2
	jsr	(Text_Print).l
inl_1D414A:
	dc.w	loc_1D4150-inl_1D414A
	dc.b	$BF,$01,$17,$00
loc_1D4150:
	jsr	(Text_FillRect).l
	move.w	#$12,d0
	move.w	#$2,d1
	move.w	#$7FF,d2
	ori.w	#$8000,d2
	jsr	(Text_Print).l
inl_1D416C:
	dc.w	loc_1D4172-inl_1D416C
	dc.b	$BF,$13,$17,$00
loc_1D4172:
	jsr	(Text_FillRect).l
	movea.l	#dat_1D42BC,a1
	move.w	(ram_D168).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(ram_D14C).w,d7
	clr.w	d6
	movea.l	#ram_D1D2,a4
	jsr	(Text_Print).l
inl_1D41A0:
	dc.w	loc_1D41A6-inl_1D41A0
	dc.b	$BF,$01,$0B,$00
loc_1D41A6:
	bra.w	loc_1D41CC
loc_1D41AA:
	clr.w	d1
	move.b	$0(a4,d6.w),d1
	bsr.w	sub_1D426E
	move.w	(TextAttr).w,-(sp)
	bsr.w	sub_1D41D2
	move.w	(sp)+,(TextAttr).w
	addq.w	#2,(TextY).w
	move.w	#$1,(TextX).w
	addq.w	#1,d6
loc_1D41CC:
	dbra	d7,loc_1D41AA
	rts


; ----------------------------------------------------------------------
; called from $1D41B8
sub_1D41D2:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(TextY).w,-(sp)
	move.w	d1,d2
	jsr	(Text_Print).l
inl_1D41E2:
	dc.w	loc_1D41E8-inl_1D41E2
	dc.b	$CF,$00,$0B,$00
loc_1D41E8:
	move.w	d6,d1
	add.w	d1,d1
	add.w	d1,(TextY).w
	movea.l	#ram_D184,a4
	move.w	d2,d5
	mulu.w	#$3,d5
	clr.w	d0
	move.w	#$3,d1
	move.b	$0(a4,d5.w),d0
	jsr	(Num_ToDecimal).l
	move.w	#$14,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	move.b	$2(a4,d5.w),d0
	jsr	(Num_ToDecimal).l
	move.w	#$18,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	move.b	$1(a4,d5.w),d0
	jsr	(Num_ToDecimal).l
	move.w	#$1D,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	move.b	$0(a4,d5.w),d0
	add.b	d0,d0
	add.b	$1(a4,d5.w),d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	move.w	#$22,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,(TextY).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D41B0
sub_1D426E:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d0
	asl.w	#2,d1
	movea.l	#TeamArtTable,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1D428A
	movea.l	#dat_017022,a0
loc_1D428A:
	movea.l	$0(a0,d1.w),a0
	lsr.w	#1,d1
	movea.l	#ram_2328,a1
	move.w	$0(a1,d1.w),d4
	movea.l	a0,a1
	adda.l	(a0),a0
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	move.w	(a1),d2
	moveq	#$2,d3
	clr.w	d0
	clr.w	d1
	moveq	#$6,d5
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D42BC:
	dc.b	$00,$30,$F8,$04,$01,$0B,$05
	dc.b	"WESTERN CONFERENCE"
	dc.b	$F8,$04,$01,$01,$08
	dc.b	"PACIFIC DIVISION ",0
	dc.b	$00,$30,$F8,$04,$01,$0B,$05
	dc.b	"WESTERN CONFERENCE"
	dc.b	$F8,$04,$01,$01,$08
	dc.b	"CENTRAL DIVISION ",0
	dc.b	$00,$30,$F8,$04,$01,$0B,$05
	dc.b	"EASTERN CONFERENCE"
	dc.b	$F8,$04,$01,$01,$08
	dc.b	"N.EAST DIVISION  ",0
	dc.b	$00,$30,$F8,$04,$01,$0B,$05
	dc.b	"EASTERN CONFERENCE"
	dc.b	$F8,$04,$01,$01,$08
	dc.b	"ATLANTIC DIVISION",0


; ----------------------------------------------------------------------
; called from $017A5E
sub_1D437C:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_B8C8).w
	clr.w	(ram_B8CA).w
	jsr	(sub_014FEE).l
	jsr	(sub_015034).l
	clr.w	(ram_D330).w
	bsr.w	sub_1D44DE
	bsr.w	sub_1D4504
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	(ram_D01A).w,d0
	jsr	(sub_1D2F82).l
loc_1D43BC:
	move.w	sr,-(sp)
	bsr.w	sub_1D44CE
	move.w	(sp)+,sr
loc_1D43C4:
	move.w	(FrameCounter).w,d0
loc_1D43C8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D43C8
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_1D2F76).l
	movem.l	(sp)+,d0-d7/a0-a6
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D43F2
	clr.w	(ram_D330).w
loc_1D43F2:
	btst	#7,d1
	bne.w	sub_1D4470
	btst	#1,d1
	beq.w	loc_1D4418
	cmpi.w	#$7,(ram_D01A).w
	beq.s	loc_1D43C4
	addq.w	#1,(ram_D01A).w
	cmpi.w	#$5,(ram_D01A).w
	bne.s	loc_1D43BC
	bra.s	loc_1D43BC
loc_1D4418:
	btst	#0,d1
	beq.w	loc_1D4434
	tst.w	(ram_D01A).w
	beq.s	loc_1D43C4
	subq.w	#1,(ram_D01A).w
	cmpi.w	#$5,(ram_D01A).w
	bne.s	loc_1D43BC
	bra.s	loc_1D43BC
loc_1D4434:
	btst	#2,d1
	beq.w	loc_1D4452
	movea.l	#dat_1D44AE,a0
	move.w	(ram_D01A).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	subq.w	#1,(a0)
	bra.w	loc_1D43BC
loc_1D4452:
	btst	#3,d1
	beq.w	loc_1D43C4
	movea.l	#dat_1D44AE,a0
	move.w	(ram_D01A).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	addq.w	#1,(a0)
	bra.w	loc_1D43BC


; ----------------------------------------------------------------------
; called from $1D43F6
sub_1D4470:
	move.b	(ram_D279).w,(ram_DD9F).w
	move.b	(ram_D27B).w,(ram_DDA6).w
	move.b	(ram_D27D).w,(ram_DDA7).w
	move.b	(ram_D27F).w,(ram_DDA0).w
	move.b	(ram_D281).w,(ram_DDA1).w
	move.b	(ram_D283).w,(ram_DDA4).w
	move.b	(ram_D285).w,(ram_DDA5).w
	jsr	(sub_014FCE).l
	move.l	#sub_016614,(ram_DDD0).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D44AE:
	dc.w	$FFFF,$D278,$FFFF,$D27A,$FFFF,$D27C,$FFFF,$D27E
	dc.w	$FFFF,$D280,$FFFF,$D282,$FFFF,$D284,$FFFF,$D288


; ----------------------------------------------------------------------
; called from $1D43BE
sub_1D44CE:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_018A68).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4398
sub_1D44DE:
	move.l	#dat_1D471C,(ram_D01E).l
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$8,(ram_D026).w
	move.w	#$16,(ram_B03E).w
	move.w	#$6,(ram_B040).w
	rts


; ----------------------------------------------------------------------
; called from $1D439C
sub_1D4504:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_DEDA).w
	move.l	#Art_1A861E,(ram_DEDE).w
	movea.l	#Art_1A861E_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEE2).w
	move.l	#Art_1A8F2C,(ram_DEE6).w
	movea.l	#Art_1A8F2C_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEEA).w
	move.l	#Font_Menu,(ram_DEEE).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D45B6:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D45BE:
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D45CE:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D45D6:
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1D45F2:
	dc.w	loc_1D45FA-inl_1D45F2
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D45FA:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1D460E:
	dc.w	loc_1D4614-inl_1D460E
	dc.b	$FE,$00,$00,$00
loc_1D4614:
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
	move.w	#$400,d4
	movea.l	#Art_1A7990_Tiles,a2
	jsr	(sub_020780).l
	bclr	#2,(ram_C356).w
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D465A:
	dc.w	loc_1D4684-inl_1D465A
	dc.b	$BF,$0B,$19
	dc.b	"{}-SELECTS OPTION"
	dc.b	$BF,$0B,$1A
	dc.b	"[]-CHANGES OPTION"
loc_1D4684:
	jsr	(Text_PrintBig).l
inl_1D468A:
	dc.w	loc_1D469C-inl_1D468A
	dc.b	$BF,$0A,$01
	dc.b	"GAME OPTIONS",0
loc_1D469C:
	jsr	(Text_PrintFont).l
inl_1D46A2:
	dc.w	loc_1D4716-inl_1D46A2
	dc.b	$BF,$04,$06
	dc.b	"PERIOD LENGTH:"
	dc.b	$BF,$04,$08
	dc.b	"GOALIES:"
	dc.b	$BF,$04,$0A
	dc.b	"USER RECORDS:"
	dc.b	$BF,$04,$0C
	dc.b	"PENALTIES:"
	dc.b	$BF,$04,$0E
	dc.b	"LINE CHANGES:"
	dc.b	$BF,$04,$10
	dc.b	"FIGHTING:"
	dc.b	$BF,$04,$12
	dc.b	"SKILL LEVEL:"
	dc.b	$BF,$04,$14
	dc.b	"GAME SPEED:"
loc_1D4716:
	move.w	#$2500,sr
	rts
dat_1D471C:
	dc.w	$0006,$FE04,$F900,$0006,$FE04,$F900

ptrtbl_1D4728:
	dc.l	sub_1D47A0
	dc.l	sub_1D474C
	dc.l	sub_1D4806
	dc.l	sub_1D485A
	dc.l	sub_1D48C0
	dc.l	sub_1D4926
	dc.l	sub_1D497A
	dc.l	sub_1D49E0
	dc.b	$FF,$FF,$FF,$FF


; ----------------------------------------------------------------------
; called from $1D472C
sub_1D474C:
	move.w	(ram_D27A).w,d0
	bpl.w	loc_1D4758
	move.w	#$1,d0
loc_1D4758:
	cmp.w	#$1,d0	; general form
	ble.w	loc_1D4762
	clr.w	d0
loc_1D4762:
	move.w	d0,(ram_D27A).w
	moveq	#$1,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D477C,a1
	jsr	(List_Skip).l
	rts
dat_1D477C:
	dc.b	$00,$12
	dc.b	" MANUAL CONTROL ",0
	dc.b	$12
	dc.b	"  AUTO CONTROL  "


; ----------------------------------------------------------------------
; called from $1D4728
sub_1D47A0:
	move.w	(ram_D278).w,d0
	bpl.w	loc_1D47AC
	move.w	#$2,d0
loc_1D47AC:
	cmp.w	#$2,d0	; general form
	ble.w	loc_1D47B6
	clr.w	d0
loc_1D47B6:
	move.w	d0,(ram_D278).w
	moveq	#$0,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D47D0,a1
	jsr	(List_Skip).l
	rts
dat_1D47D0:
	dc.b	$00,$12
	dc.b	"   5 MINUTES    ",0
	dc.b	$12
	dc.b	"   10 MINUTES   ",0
	dc.b	$12
	dc.b	"   20 MINUTES   "


; ----------------------------------------------------------------------
; called from $1D4730
sub_1D4806:
	move.w	(ram_D27C).w,d0
	bpl.w	loc_1D4812
	move.w	#$1,d0
loc_1D4812:
	cmp.w	#$1,d0	; general form
	ble.w	loc_1D481C
	clr.w	d0
loc_1D481C:
	move.w	d0,(ram_D27C).w
	moveq	#$2,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D4836,a1
	jsr	(List_Skip).l
	rts
dat_1D4836:
	dc.b	$00,$12
	dc.b	"      OFF       ",0
	dc.b	$12
	dc.b	"      ON        "


; ----------------------------------------------------------------------
; called from $1D4734
sub_1D485A:
	move.w	(ram_D27E).w,d0
	bpl.w	loc_1D4866
	move.w	#$2,d0
loc_1D4866:
	cmp.w	#$2,d0	; general form
	ble.w	loc_1D4870
	clr.w	d0
loc_1D4870:
	move.w	d0,(ram_D27E).w
	moveq	#$3,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D488A,a1
	jsr	(List_Skip).l
	rts
dat_1D488A:
	dc.b	$00,$12
	dc.b	"      OFF       ",0
	dc.b	$12
	dc.b	"ON, NO OFFSIDES ",0
	dc.b	$12
	dc.b	"      ON        "


; ----------------------------------------------------------------------
; called from $1D4738
sub_1D48C0:
	move.w	(ram_D280).w,d0
	bpl.w	loc_1D48CC
	move.w	#$2,d0
loc_1D48CC:
	cmp.w	#$2,d0	; general form
	ble.w	loc_1D48D6
	clr.w	d0
loc_1D48D6:
	move.w	d0,(ram_D280).w
	moveq	#$4,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D48F0,a1
	jsr	(List_Skip).l
	rts
dat_1D48F0:
	dc.b	$00,$12
	dc.b	"      OFF       ",0
	dc.b	$12
	dc.b	"      AUTO      ",0
	dc.b	$12
	dc.b	"      ON        "


; ----------------------------------------------------------------------
; called from $1D473C
sub_1D4926:
	move.w	(ram_D282).w,d0
	bpl.w	loc_1D4932
	move.w	#$1,d0
loc_1D4932:
	cmp.w	#$1,d0	; general form
	ble.w	loc_1D493C
	clr.w	d0
loc_1D493C:
	move.w	d0,(ram_D282).w
	moveq	#$5,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D4956,a1
	jsr	(List_Skip).l
	rts
dat_1D4956:
	dc.b	$00,$12
	dc.b	"      ON        ",0
	dc.b	$12
	dc.b	"      OFF       "


; ----------------------------------------------------------------------
; called from $1D4740
sub_1D497A:
	move.w	(ram_D284).w,d0
	bpl.w	loc_1D4986
	move.w	#$2,d0
loc_1D4986:
	cmp.w	#$2,d0	; general form
	ble.w	loc_1D4990
	clr.w	d0
loc_1D4990:
	move.w	d0,(ram_D284).w
	moveq	#$6,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D49AA,a1
	jsr	(List_Skip).l
	rts
dat_1D49AA:
	dc.b	$00,$12
	dc.b	"      PRO       ",0
	dc.b	$12
	dc.b	"    ALL-STAR    ",0
	dc.b	$12
	dc.b	"     ROOKIE     "


; ----------------------------------------------------------------------
; called from $1D4744
sub_1D49E0:
	move.w	(ram_D288).w,d0
	bpl.w	loc_1D49EC
	move.w	#$2,d0
loc_1D49EC:
	cmp.w	#$2,d0	; general form
	ble.w	loc_1D49F6
	clr.w	d0
loc_1D49F6:
	move.w	d0,(ram_D288).w
	moveq	#$7,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D4A10,a1
	jsr	(List_Skip).l
	rts
dat_1D4A10:
	dc.b	$00,$12
	dc.b	"     normal     ",0
	dc.b	$12
	dc.b	"      high      ",0
	dc.b	$12
	dc.b	"      low       "


; ----------------------------------------------------------------------
; called from $016518
sub_1D4A46:
	cmp.w	#$40,d6	; general form
	bge.w	loc_1D4AA6
	movem.l	d0-d5/a0,-(sp)
	adda.l	$4(a0),a0
	add.w	d2,d2
	move.w	$2(a0,d2.w),d4
	sub.w	$0(a0,d2.w),d4
	lsr.w	#3,d4
	subq.w	#1,d4
	adda.w	$0(a0,d2.w),a0
loc_1D4A68:
	move.w	$2(a0),d2
	andi.w	#$F000,d2
	lsr.w	#1,d2
	move.w	d2,-(sp)
	move.w	$4(a0),d2
	andi.w	#$7FF,d2
	or.w	(sp)+,d2
	add.w	d3,d2
	move.w	(a0),(a6)
	add.w	d1,(a6)+
	move.b	$2(a0),(a6)+
	move.b	d6,(a6)+
	move.w	d2,(a6)+
	move.w	$6(a0),(a6)
	add.w	d0,(a6)+
	addq.w	#1,d6
	cmp.w	#$40,d6	; general form
	beq.w	loc_1D4AA2
	addq.w	#8,a0
	dbra	d4,loc_1D4A68
loc_1D4AA2:
	movem.l	(sp)+,d0-d5/a0
loc_1D4AA6:
	rts


; ----------------------------------------------------------------------
sub_1D4AA8:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_D330).w
	bsr.w	sub_1D51CC
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_BF5A).w
	move.w	#$D,(ram_BF5E).w
	move.w	#$C,(ram_BF5C).w
	clr.w	(ram_BF58).w
loc_1D4ADA:
	bsr.w	sub_1D4D52
	move.w	(ram_BF62).w,d0
	cmp.w	#$14,d0	; general form
	ble.w	loc_1D4AEE
	move.w	#$14,d0
loc_1D4AEE:
	subq.w	#1,d0
	move.w	d0,(ram_BF60).w
loc_1D4AF4:
	move.w	(FrameCounter).w,d0
loc_1D4AF8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D4AF8
	bsr.w	sub_1D4C20
	move.w	(FrameCounter).w,d0
loc_1D4B06:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D4B06
	bset	#2,(VideoFlags).w
	bsr.w	sub_1D5014
	move.w	#$2500,sr
	bsr.w	sub_1D4BCA
	bclr	#2,(VideoFlags).w
loc_1D4B24:
	bsr.w	sub_1D4C6E
	tst.w	d1
	beq.w	loc_1D4BB6
	btst	#7,d1
	bne.w	loc_1D4BBC
	btst	#2,d1
	beq.w	loc_1D4B60
	bsr.w	sub_1D4CEE
	subq.w	#1,(ram_BF58).w
	bpl.w	loc_1D4B52
	move.w	#$3,d0
	move.w	d0,(ram_BF58).w
loc_1D4B52:
	clr.w	(ram_BF5A).w
	move.w	#$C,(ram_BF5C).w
	bra.w	loc_1D4ADA
loc_1D4B60:
	btst	#0,d1
	beq.w	loc_1D4B7A
	tst.w	(ram_BF5A).w
	beq.s	loc_1D4B24
	subq.w	#1,(ram_BF5A).w
	subq.w	#1,(ram_BF5C).w
	bra.w	loc_1D4AF4
loc_1D4B7A:
	btst	#1,d1
	beq.w	loc_1D4B98
	move.w	(ram_BF5C).w,d0
	cmp.w	(ram_BF60).w,d0
	bge.s	loc_1D4B24
	addq.w	#1,(ram_BF5A).w
	addq.w	#1,(ram_BF5C).w
	bra.w	loc_1D4AF4
loc_1D4B98:
	btst	#3,d1
	beq.s	loc_1D4B24
	bsr.w	sub_1D4CEE
	addq.w	#1,(ram_BF58).w
	move.w	#$3,d0
	cmp.w	(ram_BF58).w,d0
	bge.s	loc_1D4B52
	clr.w	(ram_BF58).w
	bra.s	loc_1D4B52
loc_1D4BB6:
	jmp	(loc_026D3E).l
loc_1D4BBC:
	move.l	#sub_016614,(ram_DDD0).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4B1A
sub_1D4BCA:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_BF5A).w
	beq.w	loc_1D4BE6
	jsr	(Text_PrintFont).l
inl_1D4BDC:
	dc.w	loc_1D4BE2-inl_1D4BDC
	dc.b	$8F,$02,$0B,$7B
loc_1D4BE2:
	bra.w	loc_1D4BF2
loc_1D4BE6:
	jsr	(Text_PrintFont).l
inl_1D4BEC:
	dc.w	loc_1D4BF2-inl_1D4BEC
	dc.b	$8F,$02,$0B,$20
loc_1D4BF2:
	move.w	(ram_BF5C).w,d1
	cmp.w	(ram_BF60).w,d1
	bge.w	loc_1D4C0E
	jsr	(Text_PrintFont).l
inl_1D4C04:
	dc.w	loc_1D4C0A-inl_1D4C04
	dc.b	$8F,$02,$17,$7D
loc_1D4C0A:
	bra.w	loc_1D4C1A
loc_1D4C0E:
	jsr	(Text_PrintFont).l
inl_1D4C14:
	dc.w	loc_1D4C1A-inl_1D4C14
	dc.b	$8F,$02,$17,$20
loc_1D4C1A:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4AFE
sub_1D4C20:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1D4C2A:
	dc.w	loc_1D4C30-inl_1D4C2A
	dc.b	$BF,$1E,$08,$00
loc_1D4C30:
	move.w	(ram_BF58).w,d0
	movea.l	#dat_1D4C46,a1
	jsr	(sub_022A66).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D4C46:
	dc.b	$00,$0A
	dc.b	"Goals  ",0
	dc.b	$00,$0A
	dc.b	"Assists",0
	dc.b	$00,$0A
	dc.b	"Points ",0
	dc.b	$00,$0A
	dc.b	"    GAA",0


; ----------------------------------------------------------------------
; called from $1D4B24
sub_1D4C6E:
	move.l	#dat_005460,d6
loc_1D4C74:
	move.w	#$64,d6
	move.w	(FrameCounter).w,d1
	sub.w	(ram_B056).w,d1
	beq.s	loc_1D4C74
	move.w	(FrameCounter).w,(ram_B056).w
	jsr	(Joypad_Read1).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D4C9E
	bra.w	loc_1D4CEC
loc_1D4C9E:
	jsr	(Joypad_Read2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D4CB4
	bra.w	loc_1D4CEC
loc_1D4CB4:
	tst.w	(FourWayPlay).w
	beq.w	loc_1D4CE8
	jsr	(Joypad_Read3).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D4CD2
	bra.w	loc_1D4CEC
loc_1D4CD2:
	jsr	(Joypad_Read4).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D4CE8
	bra.w	loc_1D4CEC
loc_1D4CE8:
	dbra	d6,loc_1D4C74
loc_1D4CEC:
	rts


; ----------------------------------------------------------------------
; called from $1D4B3E, $1D4B9E
sub_1D4CEE:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$24,d0
	move.w	#$D,d1
	move.w	#$7FF,d2
	ori.w	#$8000,d2
	jsr	(Text_Print).l
inl_1D4D08:
	dc.w	loc_1D4D0E-inl_1D4D08
	dc.b	$BF,$02,$0B,$00
loc_1D4D0E:
	jsr	(Text_FillRect).l
	jsr	(Text_PrintNarrow).l
inl_1D4D1A:
	dc.w	loc_1D4D28-inl_1D4D1A
	dc.b	$F8,$04,$01,$1E,$08
	dc.b	"       "
loc_1D4D28:
	jsr	(Text_PrintNarrow).l
inl_1D4D2E:
	dc.w	loc_1D4D4C-inl_1D4D2E
	dc.b	$F8,$04,$01,$09,$05
	dc.b	"                      ",0
loc_1D4D4C:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D4ADA, $1E3AAC, $1E3B7A, $1E3C02, $1E3C64, $1E3CA0, $1E3D06
sub_1D4D52:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_BF58).w,d0
	asl.w	#2,d0
	movea.l	#ptrtbl_1D4D6E,a0
	movea.l	$0(a0,d0.w),a0
	jmp	(a0)
loc_1D4D68:
	movem.l	(sp)+,d0-d7/a0-a6
	rts

ptrtbl_1D4D6E:
	dc.l	sub_1D4DBE
	dc.l	sub_1D4DF0
	dc.l	sub_1D4E22
	dc.l	sub_1D4D7E


; ----------------------------------------------------------------------
; called from $1D4D66
sub_1D4D7E:
	move.l	#dat_00599C,d1
	moveq	#$E,d2
	moveq	#$3,d3
	move.l	#dat_005DE0,d4
	moveq	#$D,d6
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4DAC
	move.l	#dat_003448,d1
	moveq	#$E,d2
	moveq	#$3,d3
	move.l	#dat_0036E8,d4
	moveq	#$D,d6
loc_1D4DAC:
	movea.l	#sub_00BAEC,a5
	bset	#1,(ram_C342).w
	bsr.w	sub_1D4E54
	bra.s	loc_1D4D68


; ----------------------------------------------------------------------
; called from $1D4D66
sub_1D4DBE:
	move.l	#loc_000278,d1
	moveq	#$C,d2
	moveq	#$18,d3
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4DDC
	move.l	#loc_000458,d1
	moveq	#$A,d2
	moveq	#$19,d3
loc_1D4DDC:
	movea.l	#sub_00B99A,a5
	bclr	#1,(ram_C342).w
	bsr.w	sub_1D4ED0
	bra.w	loc_1D4D68


; ----------------------------------------------------------------------
; called from $1D4D66
sub_1D4DF0:
	move.l	#dat_001FB8,d1
	moveq	#$C,d2
	moveq	#$18,d3
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4E0E
	move.l	#dat_0013F8,d1
	moveq	#$A,d2
	moveq	#$19,d3
loc_1D4E0E:
	movea.l	#sub_00B99A,a5
	bclr	#1,(ram_C342).w
	bsr.w	sub_1D4ED0
	bra.w	loc_1D4D68


; ----------------------------------------------------------------------
; called from $1D4D66
sub_1D4E22:
	move.l	#loc_000278,d1
	moveq	#$C,d2
	moveq	#$18,d3
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4E40
	move.l	#loc_000458,d1
	moveq	#$A,d2
	moveq	#$19,d3
loc_1D4E40:
	movea.l	#sub_00BA0A,a5
	bclr	#1,(ram_C342).w
	bsr.w	sub_1D4ED0
	bra.w	loc_1D4D68


; ----------------------------------------------------------------------
; called from $1D4DB8
sub_1D4E54:
	movea.l	#ram_193A,a0
	movea.l	#ram_BF62,a2
	movea.l	#ram_1388,a3
	clr.w	d7
	clr.w	(a2)
	clr.w	d5
loc_1D4E6C:
	movem.l	d1/d4/d5/d7,-(sp)
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4E86
	jsr	(sub_0188CA).l
	move.w	d7,d5
	mulu.w	#$1B,d5
loc_1D4E86:
	jsr	(sub_01A20E).l
	move.w	d0,d3
	jsr	(a5)
	movem.l	(sp)+,d1/d4/d5/d7
	addi.l	#$2A,d1
	addi.l	#$27,d4
	addi.w	#$1B,d5
	addq.w	#1,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4EBA
	cmp.w	#$10,d7	; general form
	blt.s	loc_1D4E6C
	bra.w	loc_1D4EC0
loc_1D4EBA:
	cmp.w	#$1A,d7	; general form
	blt.s	loc_1D4E6C
loc_1D4EC0:
	move.w	(ram_BF62).w,d3
	beq.w	loc_1D4FC0
	subq.w	#1,d3
	clr.w	d4
	bra.w	loc_1D4F54


; ----------------------------------------------------------------------
; called from $1D4DE8, $1D4E1A, $1D4E4C
sub_1D4ED0:
	movea.l	#ram_193A,a0
	movea.l	#ram_BF62,a2
	movea.l	#ram_1388,a3
	clr.w	d7
	clr.w	(a2)
	clr.w	d5
loc_1D4EE8:
	movem.w	d5/d7,-(sp)
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4F02
	jsr	(sub_0188CA).l
	move.w	d7,d5
	mulu.w	#$1B,d5
loc_1D4F02:
	jsr	(sub_01A278).l
	move.w	d0,(ram_DDE4).w
	jsr	(sub_01A20E).l
	sub.w	d0,(ram_DDE4).w
	subi.w	#$18,(ram_DDE4).w
	neg.w	(ram_DDE4).w
	add.w	d0,d5
	jsr	(a5)
	movem.w	(sp)+,d5/d7
	addi.w	#$1B,d5
	addq.w	#1,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D4F42
	cmp.w	#$10,d7	; general form
	blt.s	loc_1D4EE8
	bra.w	loc_1D4F48
loc_1D4F42:
	cmp.w	#$1A,d7	; general form
	blt.s	loc_1D4EE8
loc_1D4F48:
	move.w	(ram_BF62).w,d3
	beq.w	loc_1D4FC0
	subq.w	#1,d3
	clr.w	d4
loc_1D4F54:
	movea.l	#ram_193A,a1
	movea.l	#ram_1388,a0
	btst	#1,(ram_C342).w
	bne.w	loc_1D4FC2
loc_1D4F6A:
	clr.w	d0
	clr.w	(ram_BF48).w
	move.w	(ram_BF62).w,d2
	beq.w	loc_1D4FC0
	subq.w	#2,d2
	beq.w	loc_1D4FC0
	bmi.w	loc_1D4FC0
loc_1D4F82:
	move.w	$0(a1,d0.w),d5
	move.w	$2(a1,d0.w),d6
	cmp.w	d5,d6
	ble.w	loc_1D4FB4
	st	(ram_BF48).w
	move.w	$0(a1,d0.w),-(sp)
	move.w	$2(a1,d0.w),-(sp)
	move.w	(sp)+,$0(a1,d0.w)
	move.w	(sp)+,$2(a1,d0.w)
	move.w	$0(a0,d0.w),-(sp)
	move.w	$2(a0,d0.w),-(sp)
	move.w	(sp)+,$0(a0,d0.w)
	move.w	(sp)+,$2(a0,d0.w)
loc_1D4FB4:
	addq.w	#2,d0
	dbra	d2,loc_1D4F82
	tst.w	(ram_BF48).w
	bne.s	loc_1D4F6A
loc_1D4FC0:
	rts
loc_1D4FC2:
	clr.w	d0
	clr.w	(ram_BF48).w
	move.w	(ram_BF62).w,d2
	beq.s	loc_1D4FC0
	subq.w	#2,d2
	beq.s	loc_1D4FC0
	bmi.s	loc_1D4FC0
loc_1D4FD4:
	move.w	$0(a1,d0.w),d5
	move.w	$2(a1,d0.w),d6
	cmp.w	d5,d6
	bge.w	loc_1D5006
	st	(ram_BF48).w
	move.w	$0(a1,d0.w),-(sp)
	move.w	$2(a1,d0.w),-(sp)
	move.w	(sp)+,$0(a1,d0.w)
	move.w	(sp)+,$2(a1,d0.w)
	move.w	$0(a0,d0.w),-(sp)
	move.w	$2(a0,d0.w),-(sp)
	move.w	(sp)+,$0(a0,d0.w)
	move.w	(sp)+,$2(a0,d0.w)
loc_1D5006:
	addq.w	#2,d0
	dbra	d2,loc_1D4FD4
	tst.w	(ram_BF48).w
	bne.s	loc_1D4FC2
	rts


; ----------------------------------------------------------------------
; called from $1D4B12
sub_1D5014:
	jsr	(Text_Print).l
inl_1D501A:
	dc.w	loc_1D5020-inl_1D501A
	dc.b	$8F,$00,$00,$00
loc_1D5020:
	clr.w	d6
	movea.l	#ram_193A,a5
	move.w	#$B,(TextY).w
loc_1D502E:
	move.w	#$4,(TextX).w
	movea.l	#dat_1D51A8,a1
	jsr	(Text_PrintFont_Worker).l
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	cmp.w	(ram_BF62).w,d0
	blt.w	loc_1D5064
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	cmp.w	(ram_BF60).w,d0
	bge.w	loc_1D5194
	move.w	d0,(ram_BF60).w
	bra.w	loc_1D5194
loc_1D5064:
	move.w	#$4,(TextX).w
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	move.w	d0,-(sp)
	addq.w	#1,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$7,(TextX).w
	movea.l	#ram_1388,a0
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	tst.w	(sp)+
	bne.w	loc_1D50F2
	move.w	(TextX).w,-(sp)
	move.w	(TextY).w,-(sp)
	move.w	(TextAttr).w,-(sp)
	move.w	(TextPlaneOffset).w,-(sp)
	jsr	(sub_013BFA).l
	jsr	(Text_Print).l
inl_1D50C8:
	dc.w	loc_1D50CE-inl_1D50C8
	dc.b	$BF,$14,$05,$00
loc_1D50CE:
	move.w	d0,-(sp)
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	sub.w	d0,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,d0
	move.w	(sp)+,(TextPlaneOffset).w
	move.w	(sp)+,(TextAttr).w
	move.w	(sp)+,(TextY).w
	move.w	(sp)+,(TextX).w
loc_1D50F2:
	jsr	(sub_013C0A).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$19,(TextX).w
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1D5118
	movea.l	#RosterTable,a1
loc_1D5118:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	jsr	(Text_PrintFont_Worker).l
	move.w	#$20,(TextX).w
	movea.l	#ram_193A,a0
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	cmpi.w	#$3,(ram_BF58).w
	bne.w	loc_1D5184
	ext.l	d0
	divu.w	#$64,d0
	swap	d0
	move.w	d0,-(sp)
	swap	d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_1D5170:
	dc.w	loc_1D5174-inl_1D5170
	dc.b	$2E,$00
loc_1D5174:
	move.w	(sp)+,d0
	move.w	#$2,d1
	jsr	(sub_028752).l
	bra.w	loc_1D518E
loc_1D5184:
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
loc_1D518E:
	jsr	(Text_PrintFont_Worker).l
loc_1D5194:
	addq.w	#1,(TextY).w
	addq.w	#1,d6
	cmp.w	(ram_BF5E).w,d6
	blt.w	loc_1D502E
	bra.w	loc_1D51A6
loc_1D51A6:
	rts
dat_1D51A8:
	dc.b	$00
	dc.b	"$                                  "


; ----------------------------------------------------------------------
; called from $1D4AB0
sub_1D51CC:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D524A:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D5252:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D526A:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D5272:
	bset	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1D5296:
	dc.w	loc_1D529E-inl_1D5296
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D529E:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D52BC:
	dc.w	loc_1D52E4-inl_1D52BC
	dc.b	$8F,$0A,$19
	dc.b	"{}-SCROLL LIST"
	dc.b	$8F,$0A,$1A
	dc.b	"[]-CHANGE CATEGORY"
loc_1D52E4:
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_Print).l
inl_1D52EE:
	dc.w	loc_1D52F4-inl_1D52EE
	dc.b	$FE,$00,$00,$00
loc_1D52F4:
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
	bset	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_1D531E:
	dc.w	loc_1D5332-inl_1D531E
	dc.b	$BF,$07,$01
	dc.b	"LEAGUE LEADERS",0
loc_1D5332:
	jsr	(Text_PrintNarrow).l
inl_1D5338:
	dc.w	loc_1D5354-inl_1D5338
	dc.b	$F8,$04,$01,$07,$08,$23,$F8,$04,$01,$0B,$08
	dc.b	"PLAYER"
	dc.b	$F8,$04,$01,$18,$08
	dc.b	"TEAM"
loc_1D5354:
	move.w	#$2500,sr
	rts
loc_1D535A:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_D330).w
	clr.w	(ram_BF58).w
	clr.w	(ram_2720).l
	bset	#5,(ram_C358).w
	bsr.w	sub_1D56A6
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_BF5A).w
	move.w	#$D,(ram_BF5E).w
	move.w	#$C,(ram_BF5C).w
	clr.w	(ram_BF58).w
loc_1D5396:
	move.w	(ram_2720).l,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D53AC
	jsr	(sub_0188CA).l
loc_1D53AC:
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D53C6
	jsr	(sub_01A20E).l
	subq.w	#1,d0
	move.w	d0,(ram_BF60).w
	bra.w	loc_1D53DC
loc_1D53C6:
	jsr	(sub_01A20E).l
	move.w	d0,-(sp)
	jsr	(sub_01A278).l
	sub.w	(sp)+,d0
	subq.w	#1,d0
	move.w	d0,(ram_BF60).w
loc_1D53DC:
	bsr.w	sub_1D59E2
	move.w	(FrameCounter).w,d0
loc_1D53E4:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D53E4
	bsr.w	sub_1D567A
loc_1D53EE:
	move.w	(FrameCounter).w,d0
loc_1D53F2:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D53F2
	bsr.w	sub_1D5940
	bsr.w	sub_1D57F2
	bsr.w	sub_1D5890
	bsr.w	sub_1D5824
	move.w	(FrameCounter).w,d0
loc_1D540C:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D540C
	bset	#2,(VideoFlags).w
	bsr.w	sub_1D5C62
	move.w	#$2500,sr
	bsr.w	sub_1D5624
	bclr	#2,(VideoFlags).w
loc_1D542A:
	bsr.w	sub_1D55A4
	tst.w	d1
	beq.w	loc_1D5584
	btst	#7,d1
	bne.w	loc_1D5590
	btst	#2,d1
	beq.w	loc_1D5482
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5466
	subq.w	#1,(ram_BF58).w
	cmpi.w	#$4,(ram_BF58).w
	bge.w	loc_1D5474
	move.w	#$6,(ram_BF58).w
	bra.w	loc_1D5474
loc_1D5466:
	subq.w	#1,(ram_BF58).w
	bpl.w	loc_1D5474
	move.w	#$3,(ram_BF58).w
loc_1D5474:
	clr.w	(ram_BF5A).w
	move.w	#$C,(ram_BF5C).w
	bra.w	loc_1D5396
loc_1D5482:
	btst	#0,d1
	beq.w	loc_1D549C
	tst.w	(ram_BF5A).w
	beq.s	loc_1D542A
	subq.w	#1,(ram_BF5A).w
	subq.w	#1,(ram_BF5C).w
	bra.w	loc_1D53EE
loc_1D549C:
	btst	#1,d1
	beq.w	loc_1D54BC
	move.w	(ram_BF5C).w,d0
	cmp.w	(ram_BF60).w,d0
	bge.w	loc_1D542A
	addq.w	#1,(ram_BF5A).w
	addq.w	#1,(ram_BF5C).w
	bra.w	loc_1D53EE
loc_1D54BC:
	btst	#6,d1
	beq.w	loc_1D54F0
	subq.w	#1,(ram_2720).l
	bpl.w	loc_1D5396
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D54E4
	move.w	#$F,(ram_2720).l
	bra.w	loc_1D5396
loc_1D54E4:
	move.w	#$19,(ram_2720).l
	bra.w	loc_1D5396
loc_1D54F0:
	btst	#5,d1
	beq.w	loc_1D552A
	addq.w	#1,(ram_2720).l
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5514
	cmpi.w	#$10,(ram_2720).l
	bra.w	loc_1D551C
loc_1D5514:
	cmpi.w	#$1A,(ram_2720).l
loc_1D551C:
	bne.w	loc_1D5396
	clr.w	(ram_2720).l
	bra.w	loc_1D5396
loc_1D552A:
	btst	#4,d1
	beq.w	loc_1D554E
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5544
	clr.w	(ram_BF58).w
	bra.w	loc_1D5396
loc_1D5544:
	move.w	#$4,(ram_BF58).w
	bra.w	loc_1D5396
loc_1D554E:
	btst	#3,d1
	beq.w	loc_1D542A
	addq.w	#1,(ram_BF58).w
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5474
	bgt.w	loc_1D5570
	clr.w	(ram_BF58).w
	bra.w	loc_1D5474
loc_1D5570:
	cmpi.w	#$6,(ram_BF58).w
	ble.w	loc_1D5474
	move.w	#$4,(ram_BF58).w
	bra.w	loc_1D5474
loc_1D5584:
	bclr	#5,(ram_C358).w
	jmp	(loc_026D3E).l
loc_1D5590:
	bclr	#5,(ram_C358).w
	move.l	#sub_016614,(ram_DDD0).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D542A
sub_1D55A4:
	move.l	#dat_005460,d6
loc_1D55AA:
	move.w	#$64,d6
	move.w	(FrameCounter).w,d1
	sub.w	(ram_B056).w,d1
	beq.s	loc_1D55AA
	move.w	(FrameCounter).w,(ram_B056).w
	jsr	(Joypad_Read1).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D55D4
	bra.w	loc_1D5622
loc_1D55D4:
	jsr	(Joypad_Read2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D55EA
	bra.w	loc_1D5622
loc_1D55EA:
	tst.w	(FourWayPlay).w
	beq.w	loc_1D561E
	jsr	(Joypad_Read3).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D5608
	bra.w	loc_1D5622
loc_1D5608:
	jsr	(Joypad_Read4).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D561E
	bra.w	loc_1D5622
loc_1D561E:
	dbra	d6,loc_1D55AA
loc_1D5622:
	rts


; ----------------------------------------------------------------------
; called from $1D5420
sub_1D5624:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_BF5A).w
	beq.w	loc_1D5640
	jsr	(Text_PrintFont).l
inl_1D5636:
	dc.w	loc_1D563C-inl_1D5636
	dc.b	$BF,$02,$0B,$7B
loc_1D563C:
	bra.w	loc_1D564C
loc_1D5640:
	jsr	(Text_PrintFont).l
inl_1D5646:
	dc.w	loc_1D564C-inl_1D5646
	dc.b	$BF,$02,$0B,$20
loc_1D564C:
	move.w	(ram_BF5C).w,d1
	cmp.w	(ram_BF60).w,d1
	bge.w	loc_1D5668
	jsr	(Text_PrintFont).l
inl_1D565E:
	dc.w	loc_1D5664-inl_1D565E
	dc.b	$BF,$02,$17,$7D
loc_1D5664:
	bra.w	loc_1D5674
loc_1D5668:
	jsr	(Text_PrintFont).l
inl_1D566E:
	dc.w	loc_1D5674-inl_1D566E
	dc.b	$BF,$02,$17,$20
loc_1D5674:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D53EA, $1E0664
sub_1D567A:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$24,d0
	move.w	#$D,d1
	move.w	#$7FF,d2
	ori.w	#$8000,d2
	jsr	(Text_Print).l
inl_1D5694:
	dc.w	loc_1D569A-inl_1D5694
	dc.b	$BF,$02,$0B,$00
loc_1D569A:
	jsr	(Text_FillRect).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D5372
sub_1D56A6:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D5724:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D572C:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D5754:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D575C:
	bset	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_2712).l
	addi.w	#$20,d4
	jsr	(Text_PrintCmd).l
inl_1D577A:
	dc.w	loc_1D5782-inl_1D577A
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D5782:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	bsr.w	sub_1D5890
	jsr	(Text_Print).l
inl_1D579A:
	dc.w	loc_1D57A0-inl_1D579A
	dc.b	$FE,$00,$00,$00
loc_1D57A0:
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
	bset	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_1D57CA:
	dc.w	loc_1D57DC-inl_1D57CA
	dc.b	$BF,$09,$01
	dc.b	"SEASON STATS",0
loc_1D57DC:
	bsr.w	sub_1D5824
	bsr.w	sub_1D5940
	bsr.w	sub_1D57F2
	bsr.w	sub_1D5E5E
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $1D53FC, $1D57E4
sub_1D57F2:
	move.w	d7,-(sp)
	jsr	(Text_Print).l
inl_1D57FA:
	dc.w	loc_1D5800-inl_1D57FA
	dc.b	$BF,$01,$05,$00
loc_1D5800:
	move.w	(ram_2712).l,d4
	move.w	(ram_2720).l,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D581C
	jsr	(sub_0188CA).l
loc_1D581C:
	jsr	(sub_016EB8).l
	move.w	(sp)+,d7

; ----------------------------------------------------------------------
; called from $1D5404, $1D57DC
sub_1D5824:
	cmpi.w	#$4,(ram_BF58).w
	bge.w	loc_1D5860
	jsr	(Text_PrintNarrow).l
inl_1D5834:
	dc.w	loc_1D585C-inl_1D5834
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  PLAYER         g   a   p   pim"
loc_1D585C:
	bra.w	loc_1D588E
loc_1D5860:
	jsr	(Text_PrintNarrow).l
inl_1D5866:
	dc.w	loc_1D588E-inl_1D5866
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  GOALIE        s     sh    sp  "
loc_1D588E:
	rts


; ----------------------------------------------------------------------
; called from $1D5400, $1D5790
sub_1D5890:
	cmpi.w	#$4,(ram_BF58).w
	bge.w	loc_1D58EE
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D58AA:
	dc.w	loc_1D58E6-inl_1D58AA
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST   A/C-TEAMS"
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-GOALIES"
loc_1D58E6:
	move.w	(sp)+,(FontTileBase).w
	bra.w	loc_1D593E
loc_1D58EE:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D58FE:
	dc.w	loc_1D593A-inl_1D58FE
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST   A/C-TEAMS"
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-PLAYERS"
loc_1D593A:
	move.w	(sp)+,(FontTileBase).w
loc_1D593E:
	rts


; ----------------------------------------------------------------------
; called from $1D53F8, $1D57E0
sub_1D5940:
	jsr	(Text_Print).l
inl_1D5946:
	dc.w	loc_1D594C-inl_1D5946
	dc.b	$BF,$15,$05,$00
loc_1D594C:
	movea.l	#dat_1D5964,a1
	move.w	(ram_BF58).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintNarrow_Worker).l
	rts
dat_1D5964:
	dc.b	$00,$12
	dc.b	"     goals     ",0
	dc.b	$00,$12
	dc.b	"    assists    ",0
	dc.b	$00,$12
	dc.b	"     points    ",0
	dc.b	$00,$12
	dc.b	"penalty minutes",0
	dc.b	$00,$12
	dc.b	"     saves     ",0
	dc.b	$00,$12
	dc.b	"     shots     ",0
	dc.b	$00,$12
	dc.b	"save percentage",0


; ----------------------------------------------------------------------
; called from $1D53DC
sub_1D59E2:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_2720).l,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D59FC
	jsr	(sub_0188CA).l
loc_1D59FC:
	cmpi.w	#$4,(ram_BF58).w
	bge.w	loc_1D5B14
	jsr	(sub_01A278).l
	move.w	d0,-(sp)
	jsr	(sub_01A20E).l
	move.w	d0,d1
	sub.w	(sp)+,d0
	neg.w	d0
	move.w	d0,(ram_2714).l
	movea.l	#ram_1388,a0
	bra.w	loc_1D5A2E
loc_1D5A2A:
	move.w	d1,(a0)+
	addq.w	#1,d1
loc_1D5A2E:
	dbra	d0,loc_1D5A2A
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5A42
	jsr	(sub_0188B6).l
loc_1D5A42:
	move.w	(ram_2714).l,d3
	movea.l	#ram_193A,a0
	move.l	#loc_000278,d1
	moveq	#$C,d2
	move.l	#$120,d4
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5A74
	move.l	#loc_000458,d1
	moveq	#$A,d2
	move.l	#$FA,d4
loc_1D5A74:
	jsr	(sub_014A42).l
	movea.l	#ram_1A02,a0
	move.l	#dat_001FB8,d1
	moveq	#$C,d2
	move.w	(ram_2714).l,d3
	move.l	#$120,d4
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5AAC
	move.l	#dat_0013F8,d1
	moveq	#$A,d2
	move.l	#$FA,d4
loc_1D5AAC:
	jsr	(sub_014A42).l
	movea.l	#ram_193A,a1
	movea.l	#ram_1A02,a2
	movea.l	#ram_1ACA,a0
	move.w	(ram_2714).l,d3
	bra.w	loc_1D5AD4
loc_1D5ACE:
	move.w	(a1)+,d0
	add.w	(a2)+,d0
	move.w	d0,(a0)+
loc_1D5AD4:
	dbra	d3,loc_1D5ACE
	movea.l	#ram_1B92,a0
	move.l	#dat_003CF8,d1
	moveq	#$A,d2
	move.w	(ram_2714).l,d3
	move.l	#$F0,d4
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5B0A
	move.l	#dat_002398,d1
	moveq	#$9,d2
	move.l	#$E1,d4
loc_1D5B0A:
	jsr	(sub_014A42).l
	bra.w	loc_1D5BDA
loc_1D5B14:
	jsr	(sub_01A20E).l
	move.w	d0,(ram_2714).l
	movea.l	#ram_1388,a0
	clr.w	d1
	bra.w	loc_1D5B30
loc_1D5B2C:
	move.w	d1,(a0)+
	addq.w	#1,d1
loc_1D5B30:
	dbra	d0,loc_1D5B2C
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5B44
	jsr	(sub_0188B6).l
loc_1D5B44:
	movea.l	#ram_1C5A,a0
	move.w	(ram_2714).l,d3
	move.l	#dat_00599C,d1
	moveq	#$E,d2
	moveq	#$2A,d4
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5B6E
	move.l	#dat_003448,d1
	moveq	#$E,d2
	moveq	#$2A,d4
loc_1D5B6E:
	jsr	(sub_014A42).l
	movea.l	#ram_1D22,a0
	move.l	#dat_005558,d1
	moveq	#$E,d2
	move.w	(ram_2714).l,d3
	moveq	#$2A,d4
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5B9E
	move.l	#dat_0031A8,d1
	moveq	#$E,d2
	moveq	#$2A,d4
loc_1D5B9E:
	jsr	(sub_014A42).l
	movea.l	#ram_1C5A,a0
	movea.l	#ram_1D22,a1
	movea.l	#ram_1DEA,a2
	move.w	(ram_2714).l,d3
	bra.w	loc_1D5BD6
loc_1D5BC0:
	move.w	(a1)+,d0
	sub.w	(a0),d0
	move.w	d0,(a0)+
	move.w	-$2(a1),d1
	beq.w	loc_1D5BD4
	mulu.w	#$64,d0
	divu.w	d1,d0
loc_1D5BD4:
	move.w	d0,(a2)+
loc_1D5BD6:
	dbra	d3,loc_1D5BC0
loc_1D5BDA:
	movea.l	#dat_1D5C46,a0
	move.w	(ram_BF58).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	movea.l	#ram_1388,a1
	move.w	(a1),d0
	add.w	d0,d0
	suba.w	d0,a0
loc_1D5BF6:
	clr.w	(ram_BF48).w
	clr.w	d0
	move.w	(ram_2714).l,d5
	subq.w	#2,d5
loc_1D5C04:
	move.w	d0,d1
	add.w	d1,d1
	move.w	$0(a1,d1.w),d2
	move.w	$2(a1,d1.w),d3
	add.w	d2,d2
	add.w	d3,d3
	move.w	$0(a0,d2.w),d4
	cmp.w	$0(a0,d3.w),d4
	bge.w	loc_1D5C34
	st	(ram_BF48).w
	move.w	$0(a1,d1.w),d2
	move.w	$2(a1,d1.w),d3
	move.w	d2,$2(a1,d1.w)
	move.w	d3,$0(a1,d1.w)
loc_1D5C34:
	addq.w	#1,d0
	dbra	d5,loc_1D5C04
	tst.w	(ram_BF48).w
	bne.s	loc_1D5BF6
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D5C46:
	dc.w	$FFFF,$193A,$FFFF,$1A02,$FFFF,$1ACA,$FFFF,$1B92
	dc.w	$FFFF,$1C5A,$FFFF,$1D22,$FFFF,$1DEA


; ----------------------------------------------------------------------
; called from $1D5418
sub_1D5C62:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1D5C6C:
	dc.w	loc_1D5C72-inl_1D5C6C
	dc.b	$BF,$00,$00,$00
loc_1D5C72:
	clr.w	d6
	move.w	#$B,(TextY).w
loc_1D5C7A:
	clr.w	(ram_1EB2).l
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5C92
	move.w	#$4,(ram_1EB2).l
loc_1D5C92:
	movea.l	#dat_1D5C46,a5
	move.w	(ram_1EB2).l,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a5
	move.w	#$4,(TextX).w
	movea.l	#dat_1D51A8,a1
	jsr	(Text_PrintFont_Worker).l
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	cmp.w	(ram_2714).l,d0
	blt.w	loc_1D5CDC
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	cmp.w	(ram_BF60).w,d0
	bge.w	loc_1D5DC0
	move.w	d0,(ram_BF60).w
	bra.w	loc_1D5DC0
loc_1D5CDC:
	move.w	#$4,(TextX).w
	movea.l	#ram_1388,a0
	move.w	d6,d0
	add.w	(ram_BF5A).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	ext.l	d0
	move.w	d0,-(sp)
	move.w	(ram_2720).l,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5D0E
	jsr	(sub_0188CA).l
loc_1D5D0E:
	jsr	(sub_013C0A).l
	jsr	(Text_PrintFont_Worker).l
	cmpi.w	#$4,(ram_BF58).w
	bge.w	loc_1D5D42
	move.w	(ram_2720).l,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D5D3A
	jsr	(sub_0188CA).l
loc_1D5D3A:
	jsr	(sub_01A20E).l
	sub.w	d0,(sp)
loc_1D5D42:
	move.w	#$15,(TextX).w
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5D58
	move.w	#$14,(TextX).w
loc_1D5D58:
	move.w	(sp),d0
	bsr.w	sub_1D5DD4
	beq.w	loc_1D5DBE
	move.w	#$19,(TextX).w
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5D78
	move.w	#$1A,(TextX).w
loc_1D5D78:
	move.w	(sp),d0
	bsr.w	sub_1D5DD4
	beq.w	loc_1D5DBE
	move.w	#$1D,(TextX).w
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5D98
	move.w	#$20,(TextX).w
loc_1D5D98:
	move.w	(sp),d0
	bsr.w	sub_1D5DD4
	beq.w	loc_1D5DBE
	move.w	#$21,(TextX).w
	cmpi.w	#$4,(ram_BF58).w
	blt.w	loc_1D5DB8
	move.w	#$0,(TextX).w
loc_1D5DB8:
	move.w	(sp),d0
	bsr.w	sub_1D5DD4
loc_1D5DBE:
	tst.w	(sp)+
loc_1D5DC0:
	addq.w	#1,(TextY).w
	addq.w	#1,d6
	cmp.w	(ram_BF5E).w,d6
	blt.w	loc_1D5C7A
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D5D5A, $1D5D7A, $1D5D9A, $1D5DBA
sub_1D5DD4:
	move.w	d0,-(sp)
	move.w	(ram_1EB2).l,d0
	asl.w	#2,d0
	movea.l	#dat_1D5C46,a0
	movea.l	$0(a0,d0.w),a0
	move.w	(sp)+,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	move.w	#$3,d1
	cmpi.w	#$4,(ram_1EB2).l
	blt.w	loc_1D5E10
	cmpi.w	#$6,(ram_1EB2).l
	beq.w	loc_1D5E10
	move.w	#$4,d1
loc_1D5E10:
	jsr	(Num_ToDecimal).l
	bsr.w	sub_1D5E36
	addq.w	#1,(ram_1EB2).l
	cmpi.w	#$4,(ram_1EB2).l
	beq.w	loc_1D5E34
	cmpi.w	#$7,(ram_1EB2).l
loc_1D5E34:
	rts


; ----------------------------------------------------------------------
; called from $1D5E16
sub_1D5E36:
	move.w	(TextAttr).w,-(sp)
	move.w	(ram_BF58).w,d0
	cmp.w	(ram_1EB2).l,d0
	bne.w	loc_1D5E52
	jsr	(Text_PrintCmd).l
inl_1D5E4E:
	dc.w	loc_1D5E52-inl_1D5E4E
	dc.b	$FE,$07
loc_1D5E52:
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp)+,(TextAttr).w
	rts


; ----------------------------------------------------------------------
; called from $015456, $1D43A0, $1D4AB4, $1D57E8, $1D5EEA, $1D7CF2, $1D8E88, $1DE0BA (+2 more)
sub_1D5E5E:
	movem.l	a0/a1,-(sp)
	movea.l	#dat_1AD3E8,a0
	movea.l	#ram_BD60,a1
	move.w	#$7,d0
loc_1D5E72:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_1D5E72
	movem.l	(sp)+,a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1DB236
sub_1D5E7E:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,(ram_DDE2).w
	move.w	(SysFlags).w,-(sp)
	bclr	#7,(SysFlags).w
	jsr	(sub_0279E6).l
	move.w	(sp)+,(SysFlags).w
	movea.l	#ram_D2B4,a3
	jsr	(sub_027834).l
	move.w	(ram_CFD6).w,d0
	or.w	(ram_CFD4).w,d0
	beq.w	loc_1D5EDE
	move.w	(SysFlags).w,-(sp)
	bclr	#7,(SysFlags).w
	jsr	(sub_027354).l
	move.w	(sp)+,(SysFlags).w
	movea.l	#ram_CFDE,a0
	move.w	(ram_CFD8).w,d2
	move.b	$0(a0,d2.w),d2
	clr.w	(ram_DDE2).w
	move.b	d2,(ram_DDE3).w
loc_1D5EDE:
	clr.w	(ram_D330).w
	bsr.w	sub_1D60EC
	bsr.w	sub_1D6112
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	(ram_D01A).w,d0
	jsr	(sub_1D2FEE).l
loc_1D5F06:
	bsr.w	sub_1D60DC
loc_1D5F0A:
	move.w	(FrameCounter).w,d0
loc_1D5F0E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D5F0E
	movem.l	d0-d7/a0-a6,-(sp)
	cmpi.l	#dat_1D639E,(ram_D01E).l
	beq.s	loc_1D5F2E
	jsr	(sub_1D304E).l
	bra.w	loc_1D5F34
loc_1D5F2E:
	jsr	(sub_1D2FE2).l
loc_1D5F34:
	movem.l	(sp)+,d0-d7/a0-a6
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D5F4E
	clr.w	(ram_D330).w
loc_1D5F4E:
	btst	#7,d1
	bne.w	loc_1D5F86
	btst	#5,d1
	bne.w	loc_1D5F86
	btst	#1,d1
	beq.w	loc_1D5F74
	cmpi.w	#$6,(ram_D01A).w
	beq.s	loc_1D5F0A
	addq.w	#1,(ram_D01A).w
	bra.s	loc_1D5F06
loc_1D5F74:
	btst	#0,d1
	beq.s	loc_1D5F06
	tst.w	(ram_D01A).w
	beq.s	loc_1D5F0A
	subq.w	#1,(ram_D01A).w
	bra.s	loc_1D5F06
loc_1D5F86:
	cmpi.l	#dat_1D639E,(ram_D01E).l
	beq.w	loc_1D5FFE
	tst.w	(ram_D01A).w
	bne.w	loc_1D5FA0
	bsr.w	sub_1D62A4
loc_1D5FA0:
	move.l	#NullEntry,(ram_DDD0).w
	move.l	#dat_1D639E,(ram_D01E).l
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$6,(ram_D026).w
	move.w	#$D,(ram_B03E).w
	move.w	#$6,(ram_B040).w
	jsr	(Text_PrintCmd).l
inl_1D5FD2:
	dc.w	loc_1D5FDA-inl_1D5FD2
	dc.b	$FF,$01,$FD,$0C,$FC,$0B
loc_1D5FDA:
	move.w	#$11,d0
	move.w	#$D,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	bsr.w	sub_1D60EC
	move.w	(ram_D01A).w,d0
	jsr	(sub_1D2FEE).l
	bra.w	loc_1D5F06
loc_1D5FFE:
	movea.l	#ptrs_1D60C0,a0
	move.w	(ram_D01A).w,d0
	asl.w	#2,d0
	move.l	$0(a0,d0.w),(ram_DDD0).w
	cmpi.l	#sub_016614,(ram_DDD0).w
	beq.w	loc_1D60BA
	cmpi.l	#sub_1D62A4,(ram_DDD0).l
	bne.w	loc_1D6098
	move.l	#dat_1D64B8,(ram_D01E).l
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$2,(ram_D026).w
	move.w	#$12,(ram_B03E).w
	move.w	#$F,(ram_B040).w
	jsr	(Text_PrintCmd).l
inl_1D6054:
	dc.w	loc_1D605C-inl_1D6054
	dc.b	$FF,$01,$FD,$00,$FC,$05
loc_1D605C:
	moveq	#$28,d0
	moveq	#$14,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	jsr	(Text_PrintCmd).l
inl_1D607C:
	dc.w	loc_1D6094-inl_1D607C
	dc.w	$FE04,$F900,$FD0E,$FC0B
	dc.b	"Reset Rosters",0
loc_1D6094:
	bra.w	loc_1D5F06
loc_1D6098:
	cmpi.l	#NullEntry,(ram_DDD0).w
	beq.w	loc_1D5F06
	movea.l	(ram_DDD0).w,a0
	bset	#6,(ram_C356).w
	jsr	(a0)
	bclr	#6,(ram_C356).w
	bra.w	loc_1D5EDE
loc_1D60BA:
	movem.l	(sp)+,d0-d7/a0-a6
	rts

ptrs_1D60C0:
	dc.l	dat_1D6518
	dc.l	dat_1D6500
	dc.l	dat_1D6508
	dc.l	dat_1D6510

ptrtbl_1D60D0:
	dc.l	sub_1D62A4
	dc.l	sub_1DD778
	dc.l	sub_016614


; ----------------------------------------------------------------------
; called from $1D5F06
sub_1D60DC:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_018A68).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D5EE2, $1D5FEC
sub_1D60EC:
	move.l	#dat_1D639E,(ram_D01E).l
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$7,(ram_D026).w
	move.w	#$C,(ram_B03E).w
	move.w	#$6,(ram_B040).w
	rts


; ----------------------------------------------------------------------
; called from $1D5EE6
sub_1D6112:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_DEDA).w
	move.l	#Art_1A861E,(ram_DEDE).w
	movea.l	#Art_1A861E_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEE2).w
	move.l	#Art_1A8F2C,(ram_DEE6).w
	movea.l	#Art_1A8F2C_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEEA).w
	move.l	#Font_Menu,(ram_DEEE).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D61C4:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D61CC:
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D61DC:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D61E4:
	bclr	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1D6208:
	dc.w	loc_1D6210-inl_1D6208
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D6210:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1D6224:
	dc.w	loc_1D622A-inl_1D6224
	dc.b	$FE,$00,$00,$00
loc_1D622A:
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
	move.w	#$400,d4
	movea.l	#Art_1A7990_Tiles,a2
	jsr	(sub_020780).l
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_1D6264:
	dc.w	loc_1D6276-inl_1D6264
	dc.b	$BF,$09,$01
	dc.b	"TRANSACTIONS",0
loc_1D6276:
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D6288:
	dc.w	loc_1D629E-inl_1D6288
	dc.b	$BF,$0B,$1A
	dc.b	"{}-SELECTS OPTION"
loc_1D629E:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $1D5F9C, $1D60D0
sub_1D62A4:
	bset	#6,(SysFlags).w
	move.l	#$E8E,d0
	move.l	#$A7,d1
	jsr	(sub_029D2A).l
	move.l	#dat_000DCA,d0
	moveq	#$32,d1
	jsr	(sub_029D2A).l
	movem.l	d0/a0,-(sp)
	move.w	#$13,d0
	movea.l	#$201B94,a0
loc_1D62D8:
	move.b	#$80,$1(a0)
	addq.w	#4,a0
	dbra	d0,loc_1D62D8
	movem.l	(sp)+,d0/a0
	movem.l	a0-a2,-(sp)
	movea.l	#$201B94,a1
	clr.w	d1
	clr.w	d0
	move.b	($202F43).l,d0
	bra.w	loc_1D6314
loc_1D6300:
	move.b	d1,$3(a1)
	move.b	#$28,$1(a1)
	addq.b	#1,($201BE5).l
	addq.l	#4,a1
	addq.w	#1,d1
loc_1D6314:
	dbra	d0,loc_1D6300
	move.b	#$80,$1(a1)
	move.b	#$0,$3(a1)
	movem.l	(sp)+,a0-a2
	jsr	(sub_013B34).l
	move.l	#dat_0017A2,d0
	move.l	#$86E,d1
	movea.l	#ram_17A2,a0
	jsr	(SRAM_Write).l
	jsr	(sub_0150D2).l
	btst	#7,(SysFlags).w
	beq.w	loc_1D6360
	jsr	(sub_1DB216).l
	bra.w	loc_1D6390
loc_1D6360:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1D637A
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1D637A
	cmpi.w	#$3,(ram_D270).w
loc_1D637A:
	nop
	bne.w	loc_1D638A
	jsr	(sub_1DB1FE).l
	bra.w	loc_1D6390
loc_1D638A:
	jsr	(sub_1DB20C).l
loc_1D6390:
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	rts
dat_1D639E:
	dc.w	$0006,$FE04,$F900,$0006,$FE04,$F900

ptrtbl_1D63AA:
	dc.l	sub_1D63CA
	dc.l	sub_1D63EC
	dc.l	sub_1D640E
	dc.l	sub_1D6430
	dc.l	sub_1D6452
	dc.l	sub_1D6474
	dc.l	sub_1D6496
	dc.b	$FF,$FF,$FF,$FF


; ----------------------------------------------------------------------
; called from $1D63AA
sub_1D63CA:
	moveq	#$0,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D63DA,a1
	rts
dat_1D63DA:
	dc.b	$00,$12
	dc.b	" Trade Players  "


; ----------------------------------------------------------------------
; called from $1D63AE
sub_1D63EC:
	moveq	#$1,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D63FC,a1
	rts
dat_1D63FC:
	dc.b	$00,$12
	dc.b	" Create Players "


; ----------------------------------------------------------------------
; called from $1D63B2
sub_1D640E:
	moveq	#$2,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D641E,a1
	rts
dat_1D641E:
	dc.b	$00,$12
	dc.b	"Sign Free Agents"


; ----------------------------------------------------------------------
; called from $1D63B6
sub_1D6430:
	moveq	#$3,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D6440,a1
	rts
dat_1D6440:
	dc.b	$00,$12
	dc.b	" Release Player "


; ----------------------------------------------------------------------
; called from $1D63BA
sub_1D6452:
	moveq	#$4,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D6462,a1
	rts
dat_1D6462:
	dc.b	$00,$12
	dc.b	"  Reset Rosters "


; ----------------------------------------------------------------------
; called from $1D63BE
sub_1D6474:
	moveq	#$5,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D6484,a1
	rts
dat_1D6484:
	dc.b	$00,$12
	dc.b	"  Team Rosters  "


; ----------------------------------------------------------------------
; called from $1D63C2
sub_1D6496:
	moveq	#$6,d5
	jsr	(sub_1D2F54).l
	movea.l	#dat_1D64A6,a1
	rts
dat_1D64A6:
	dc.b	$00,$12
	dc.b	"      Exit      "
dat_1D64B8:
	dc.w	$0006,$FE04,$F900,$0006,$FE04,$F900,$001D,$64D0
	dc.w	$001D,$64E8,$FFFF,$FFFF,$7A00,$4EB9,$001D,$2F54
	dc.w	$227C,$001D,$64E0,$4E75,$0008,$2059,$6573,$2000
	dc.w	$7A01,$4EB9,$001D,$2F54,$227C,$001D,$64F8,$4E75
	dc.w	$0008,$204E,$6F20,$2000
dat_1D6500:
	dc.w	$4EB9,$001D,$7CBC,$4E75
dat_1D6508:
	dc.w	$4EB9,$001D,$A06A,$4E75
dat_1D6510:
	dc.w	$4EB9,$001D,$A9A4,$4E75
dat_1D6518:
	incbin	"data/bin/data_1D6518.bin"	; 2870 bytes


; ----------------------------------------------------------------------
sub_1D704E:
	move.w	d0,-(sp)
	move.w	(FrameCounter).w,d0
loc_1D7054:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D7054
	move.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
sub_1D705E:
	move.w	d7,(a1)+
	move.w	#$FFFF,(a1)
	move.w	#$FFFF,$2(a1)
	move.w	#$FFFF,$4(a1)
	subq.w	#1,d6
loc_1D7072:
	tst.b	(a2)
	beq.w	loc_1D7080
	clr.w	d0
	move.b	$2(a2),d0
	move.w	d0,(a1)+
loc_1D7080:
	tst.l	(a2)+
	dbra	d6,loc_1D7072
	rts

	dc.w	$08F8,$0005,$C358,$21FC,$0001,$728E,$D260,$08B8
	dc.w	$0000,$BFB4,$08F8,$0002,$BFB4,$08B8,$0001,$BFB4
	dc.w	$31FC,$0000,$B000,$31FC,$BC00,$B002,$31FC,$BC00
	dc.w	$B00C,$31FC,$0005,$B00E,$31FC,$C000,$B008,$31FC
	dc.w	$0006,$B00A,$31FC,$E000,$B004,$31FC,$0006,$B006
	dc.w	$303C,$0000,$4EB9,$0002,$05CE,$08B8,$0005,$BFB4
	dc.w	$4EB9,$0002,$0314,$383C,$0001,$31C4,$B01C,$31C4
	dc.w	$B01E,$247C,$001A,$9842,$4EB9,$0002,$0774,$0123
	dc.w	$4567,$89DE,$EEEF,$21FC,$001A,$983A,$BF8C,$31C4
	dc.w	$B020,$247C,$001A,$AD9E,$4EB9,$0002,$0780,$31C4
	dc.w	$B018,$247C,$001A,$A150,$4EB9,$0002,$0774,$0123
	dc.w	$4567,$89DE,$EEEF,$21FC,$001A,$A148,$B010,$4EB9
	dc.w	$0002,$0A7E,$0008,$FF01,$FD00,$FC00,$7028,$721C
	dc.w	$343C,$87FF,$4EB9,$0002,$09C6,$6100,$01DA,$4EB9
	dc.w	$0002,$0BDE,$0006,$FE00,$0000,$207C,$001A,$41D4
	dc.w	$2248,$2448,$D1DA,$D3DA,$4240,$4241,$7428,$761C
	dc.w	$7A09,$4EB9,$0002,$06E2,$08F8,$0002,$C356,$4EB9
	dc.w	$0002,$0F14,$0012,$BF08,$0154,$5241,$4445,$2050
	dc.w	$4C41,$5945,$5253,$323C,$0019,$4242,$207C,$FFFF
	dc.w	$271E,$227C,$0001,$6FA6,$4A78,$DEA8,$6700,$0008
	dc.w	$227C,$0001,$7022,$30C4,$3002,$E540,$2471,$0000
	dc.w	$504A,$4EB9,$0002,$0780,$5242,$51C9,$FFEA,$08F8
	dc.w	$0002,$C356,$4EB9,$0002,$0F38,$0012,$F807,$0115
	dc.w	$0470,$6F73,$F807,$0115,$0E70,$6F73,$08B8,$0002
	dc.w	$C356,$4E75


; ----------------------------------------------------------------------
sub_1D720C:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d0
	asl.w	#2,d1
	movea.l	#TeamArtTable,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1D7228
	movea.l	#dat_017022,a0
loc_1D7228:
	movea.l	$0(a0,d1.w),a0
	lsr.w	#1,d1
	movea.l	#ram_271E,a1
	move.w	$0(a1,d1.w),d4
	movea.l	a0,a1
	adda.l	(a0),a0
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	move.w	(a1),d2
	moveq	#$2,d3
	clr.w	d0
	clr.w	d1
	moveq	#$4,d5
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D725A:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01A20E).l
	move.w	d0,(a1)
	jsr	(sub_01A278).l
	move.w	d0,$4(a1)
	subq.w	#1,d0
	movea.l	a0,a2
	clr.w	d1
loc_1D7276:
	clr.l	(a2)
	move.b	d1,$2(a2)
	movem.l	d0,-(sp)
	move.w	d1,d0
	jsr	(sub_013E80).l
	move.b	d0,$1(a2)
	move.b	d0,d3
	movem.l	(sp)+,d0
	movem.l	d0/d1/d4,-(sp)
	move.l	a2,-(sp)
	clr.w	d0
	move.b	$2(a2),d0
	move.w	d0,(ram_C454).w
	movea.l	#ram_C732,a2
	cmp.w	(ram_C3AC).w,d7
	beq.w	loc_1D72B6
	movea.l	#ram_CAD0,a2
loc_1D72B6:
	move.l	(dat_028AC0).l,d4
	tst.b	d3
	bne.w	loc_1D72C8
	move.l	(dat_028C22).l,d4
loc_1D72C8:
	jsr	(sub_1D07D4).l
	mulu.w	#$64,d0
	divu.w	d1,d0
	movem.l	d0,-(sp)
	move.w	(ram_C454).w,d0
	jsr	(sub_013E44).l
	movem.l	(sp)+,d0
	beq.w	loc_1D72EA
loc_1D72EA:
	movea.l	(sp)+,a2
	move.b	d0,$3(a2)
	movem.l	(sp)+,d0/d1/d4
	tst.l	(a2)+
	addq.w	#1,d1
	dbra	d0,loc_1D7276
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D7302:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01A278).l
	subq.w	#2,d0
loc_1D730E:
	movea.l	a0,a2
	move.w	d0,d1
	st	d6
loc_1D7314:
	move.b	$1(a2),d2
	cmp.b	$5(a2),d2
	ble.w	loc_1D732E
	move.l	(a2),d2
	move.l	$4(a2),d3
	move.l	d3,(a2)
	move.l	d2,$4(a2)
	clr.w	d6
loc_1D732E:
	addq.w	#4,a2
	dbra	d1,loc_1D7314
	tst.w	d6
	beq.s	loc_1D730E
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$3F38,$B01C,$31F8,$B01E,$B01C,$4EB9,$0002,$0CC2
	dc.w	$003A,$8F07,$1961,$2D53,$7769,$7463,$6820,$5465
	dc.w	$616D,$8F07,$1A42,$2D43,$616E,$6365,$6C8F,$1519
	dc.w	$432D,$506C,$6179,$6572,$8F11,$1A53,$7461,$7274
	dc.w	$2D45,$7661,$6C75,$6174,$6500,$31DF,$B01C,$4E75


; ----------------------------------------------------------------------
sub_1D738E:
	movem.l	d0-d4/a0/a1,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	(sp)+,(VideoFlags).w
	movem.l	(sp)+,d0-d4/a0/a1
	rts


; ----------------------------------------------------------------------
sub_1D73B0:
	move.l	#dat_005460,d6
loc_1D73B6:
	move.w	(FrameCounter).w,d1
	sub.w	(ram_B056).w,d1
	beq.s	loc_1D73B6
	move.w	(FrameCounter).w,(ram_B056).w
	jsr	(Joypad_Read1).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D73DC
	bra.w	loc_1D742A
loc_1D73DC:
	jsr	(Joypad_Read2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D73F2
	bra.w	loc_1D742A
loc_1D73F2:
	tst.w	(FourWayPlay).w
	beq.w	loc_1D7426
	jsr	(Joypad_Read3).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D7410
	bra.w	loc_1D742A
loc_1D7410:
	jsr	(Joypad_Read4).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1D7426
	bra.w	loc_1D742A
loc_1D7426:
	dbra	d6,loc_1D73B6
loc_1D742A:
	rts


; ----------------------------------------------------------------------
sub_1D742C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D032).w,d7
	jsr	(sub_1DB1A8).l
	move.w	(ram_D03A).w,d7
	jsr	(sub_1DB1A8).l
	movea.l	#ram_D032,a0
	bsr.w	sub_1D7544
	movea.l	#ram_D03A,a0
	bsr.w	sub_1D7544
	movea.w	#$D032,a0
	movea.w	#$D03A,a1
	move.w	#$2,d6
loc_1D7464:
	movea.l	#ram_D3E6,a2
	move.w	(a0),(ram_BF4C).w
	move.w	$0(a0,d6.w),d0
	bmi.w	loc_1D7482
	move.w	d0,(ram_BF48).w
	bsr.w	sub_1D75B8
	bsr.w	sub_1D7588
loc_1D7482:
	movea.l	#ram_D3FA,a2
	move.w	(a1),(ram_BF4C).w
	move.w	$0(a1,d6.w),d0
	bmi.w	loc_1D74A4
	move.w	d0,(ram_BF48).w
	bsr.w	sub_1D75B8
	exg	a1,a0
	bsr.w	sub_1D7588
	exg	a1,a0
loc_1D74A4:
	movea.l	#ram_D3E6,a2
	move.w	(a1),(ram_BF4E).w
	move.w	$0(a0,d6.w),d5
	bmi.w	loc_1D74EE
	andi.w	#$FF00,d5
	move.w	(a1),d7
	cmp.w	#$0,d5	; general form
	bne.w	loc_1D74CE
	jsr	(sub_01A20E).l
	bra.w	loc_1D74D4
loc_1D74CE:
	jsr	(sub_01A278).l
loc_1D74D4:
	or.w	d0,d5
	move.w	d5,(ram_BF4A).w
	bsr.w	sub_1D78BC
	movem.l	d0-d7/a0-a6,-(sp)
	exg	a0,a1
	bsr.w	sub_1D7566
	exg	a0,a1
	movem.l	(sp)+,d0-d7/a0-a6
loc_1D74EE:
	movea.l	#ram_D3FA,a2
	move.w	(a0),(ram_BF4E).w
	move.w	$0(a1,d6.w),d5
	bmi.w	loc_1D7534
	andi.w	#$FF00,d5
	move.w	(a0),d7
	cmp.w	#$0,d5	; general form
	bne.w	loc_1D7518
	jsr	(sub_01A20E).l
	bra.w	loc_1D751E
loc_1D7518:
	jsr	(sub_01A278).l
loc_1D751E:
	or.w	d0,d5
	move.w	d5,(ram_BF4A).w
	bsr.w	sub_1D78BC
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D7566
	movem.l	(sp)+,d0-d7/a0-a6
loc_1D7534:
	addq.w	#2,d6
	cmp.w	#$8,d6	; general form
	blt.w	loc_1D7464
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D744A, $1D7454
sub_1D7544:
	move.w	(a0)+,d7
	move.w	#$2,d6
loc_1D754A:
	move.w	(a0)+,d0
	bmi.w	loc_1D7560
	andi.w	#$FF,d0
	jsr	(sub_013E80).l
	move.w	d0,d2
	move.b	d2,-$2(a0)
loc_1D7560:
	dbra	d6,loc_1D754A
	rts


; ----------------------------------------------------------------------
; called from $1D74E4, $1D752C
sub_1D7566:
	move.b	(ram_BF4B).w,d0
loc_1D756A:
	tst.w	$0(a0,d6.w)
	bmi.w	loc_1D7586
	cmp.b	$1(a0,d6.w),d0
	bgt.w	loc_1D757E
	addq.b	#1,$1(a0,d6.w)
loc_1D757E:
	addq.w	#2,d6
	cmp.w	#$8,d6	; general form
	blt.s	loc_1D756A
loc_1D7586:
	rts


; ----------------------------------------------------------------------
; called from $1D747E, $1D749E
sub_1D7588:
	movem.l	d0-d7/a0-a6,-(sp)
	addq.w	#2,d6
	cmp.w	#$8,d6	; general form
	bge.w	loc_1D75B2
loc_1D7596:
	tst.w	$0(a0,d6.w)
	bmi.w	loc_1D75B2
	cmp.b	$1(a0,d6.w),d0
	bgt.w	loc_1D75AA
	subq.b	#1,$1(a0,d6.w)
loc_1D75AA:
	addq.w	#2,d6
	cmp.w	#$8,d6	; general form
	blt.s	loc_1D7596
loc_1D75B2:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D747A, $1D7498
sub_1D75B8:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	a2,-(sp)
	move.w	(ram_BF4C).w,d7
	jsr	(sub_01A20E).l
	move.w	d0,(ram_D4A6).w
	bset	#6,(SysFlags).w
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	move.w	(ram_BF4C).w,d7
	movem.w	d0/d7,-(sp)
	jsr	(sub_1D7C64).l
	move.w	d0,(a2)+
	movem.w	(sp)+,d0/d7
	jsr	(sub_013D6E).l
	move.w	(ram_DDCE).w,(a2)+
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D14C,a0
	move.w	d7,d0
	mulu.w	#$1B,d0
	addi.l	#dat_001D52,d0
	moveq	#$1B,d1
	movem.l	d0/d1/a0,-(sp)
	jsr	(SRAM_Read).l
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	move.w	#$1B,d1
	sub.w	d0,d1
	beq.w	loc_1D763A
loc_1D762C:
	move.b	$1(a0,d0.w),d2
	move.b	d2,$0(a0,d0.w)
	addq.w	#1,d0
	dbra	d1,loc_1D762C
loc_1D763A:
	movem.l	(sp)+,d0/d1/a0
	jsr	(SRAM_Write).l
	movem.l	(sp)+,d0-d7/a0-a6
	movea.l	#ram_D14C,a0
	jsr	(sub_013FA8).l
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	add.w	d0,d0
	move.w	#$36,d3
loc_1D7662:
	move.w	$2(a0,d0.w),d1
	move.w	d1,$0(a0,d0.w)
	addq.w	#2,d0
	cmp.w	d3,d0
	blt.s	loc_1D7662
	jsr	(sub_013FC6).l
	movea.l	#$200000,a0
	move.w	d7,d0
	asl.w	#2,d0
	ext.l	d0
	addi.l	#$3A3C,d0
	move.b	$1(a0,d0.w),d1
	subq.b	#1,d1
	move.b	d1,$1(a0,d0.w)
	tst.b	(ram_BF48).w
	bne.w	loc_1D76A4
	move.b	$3(a0,d0.w),d1
	subq.b	#1,d1
	move.b	d1,$3(a0,d0.w)
loc_1D76A4:
	cmp.w	#$19,d7	; general form
	bgt.w	loc_1D7854
	jsr	(sub_014FEE).l
	tst.b	(ram_BF48).w
	bne.w	loc_1D776C
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$2A,d4
	move.l	#dat_005558,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D76DC
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$19,d4
	move.l	#dat_0031A8,d1
loc_1D76DC:
	bsr.w	sub_1D785C
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$2A,d4
	move.l	#dat_00599C,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7702
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$19,d4
	move.l	#dat_003448,d1
loc_1D7702:
	bsr.w	sub_1D785C
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$27,d4
	move.l	#dat_005DE0,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7728
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$18,d4
	move.l	#dat_0036E8,d1
loc_1D7728:
	bsr.w	sub_1D785C
	move.w	(ram_DDE2).w,d2
	cmp.w	(ram_BF4C).w,d2
	bne.w	loc_1D7836
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#dat_007728,d1
	bsr.w	sub_1D785C
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#$774F,d1
	bsr.w	sub_1D785C
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#dat_007776,d1
	bsr.w	sub_1D785C
	bra.w	loc_1D7838
loc_1D776C:
	moveq	#$C,d2
	moveq	#$19,d3
	move.l	#$120,d4
	move.l	#loc_000278,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7796
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$99,d4
	move.l	#loc_000458,d1
loc_1D7796:
	bsr.w	sub_1D785C
	moveq	#$C,d2
	moveq	#$19,d3
	move.l	#$120,d4
	move.l	#dat_001FB8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D77C4
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$99,d4
	move.l	#dat_0013F8,d1
loc_1D77C4:
	bsr.w	sub_1D785C
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$F0,d4
	move.l	#dat_003CF8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D77F2
	moveq	#$9,d2
	moveq	#$19,d3
	move.l	#$8A,d4
	move.l	#dat_002398,d1
loc_1D77F2:
	bsr.w	sub_1D785C
	move.w	(ram_DDE2).w,d2
	cmp.w	(ram_BF4C).w,d2
	bne.w	loc_1D7836
	moveq	#$A,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007470,d1
	bsr.w	sub_1D785C
	moveq	#$A,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007560,d1
	bsr.w	sub_1D785C
	moveq	#$9,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007650,d1
	bsr.w	sub_1D785C
	bra.w	loc_1D7838
loc_1D7836:
	addq.w	#6,a2
loc_1D7838:
	moveq	#$3,d2
	moveq	#$1B,d3
	moveq	#$51,d4
	move.l	#$10080,d1
	bset	#5,(ram_C35A).w
	bsr.w	sub_1D785C
	bclr	#5,(ram_C35A).w
loc_1D7854:
	movea.l	(sp)+,a2
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D76DC, $1D7702, $1D7728, $1D7744, $1D7754, $1D7764, $1D7796, $1D77C4 (+6 more)
sub_1D785C:
	movea.l	#ram_D14C,a0
	movem.l	d1-d4/a0,-(sp)
	jsr	(sub_014A42).l
	movea.l	#ram_D14C,a3
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	cmp.b	(ram_D4A7).w,d0
	blt.w	loc_1D7890
	btst	#5,(ram_C35A).w
	bne.w	loc_1D7890
	sub.b	(ram_D4A7).w,d0
loc_1D7890:
	add.w	d0,d0
	move.l	d3,-(sp)
	move.w	$0(a3,d0.w),d3
	move.w	d3,(a2)+
	move.l	(sp)+,d3
	subq.w	#1,d3
	add.w	d3,d3
loc_1D78A0:
	move.w	$2(a3,d0.w),d1
	move.w	d1,$0(a3,d0.w)
	addq.w	#2,d0
	cmp.w	d3,d0
	blt.s	loc_1D78A0
	clr.w	$0(a3,d0.w)
	movem.l	(sp)+,d1-d4/a0
	jmp	(sub_014A62).l


; ----------------------------------------------------------------------
; called from $1D74DA, $1D7524
sub_1D78BC:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	a2,-(sp)
	bset	#6,(SysFlags).w
	move.w	(ram_BF4E).w,d7
	move.w	(ram_BF4A).w,d0
	andi.w	#$FF,d0
	movea.l	#ram_D14C,a0
	jsr	(sub_013FA8).l
	add.w	d0,d0
	move.w	#$38,d3
	bra.w	loc_1D78F2
loc_1D78EA:
	move.w	-$2(a0,d3.w),d1
	move.w	d1,$0(a0,d3.w)
loc_1D78F2:
	subq.w	#2,d3
	cmp.w	d0,d3
	ble.w	loc_1D78FC
	bra.s	loc_1D78EA
loc_1D78FC:
	move.w	(a2)+,$0(a0,d0.w)
	move.w	(a2)+,(ram_DDCE).w
	move.l	a0,-(sp)
	movea.l	#$200000,a0
	move.w	d7,d0
	asl.w	#2,d0
	ext.l	d0
	addi.l	#$3A3C,d0
	move.b	$1(a0,d0.w),d1
	addq.b	#1,d1
	move.b	d1,$1(a0,d0.w)
	tst.b	(ram_BF4A).w
	bne.w	loc_1D7934
	move.b	$3(a0,d0.w),d1
	addq.b	#1,d1
	move.b	d1,$3(a0,d0.w)
loc_1D7934:
	movea.l	(sp)+,a0
	jsr	(sub_013FC6).l
	jsr	(sub_01A20E).l
	move.w	d0,(ram_D4A6).w
	cmp.w	#$19,d7	; general form
	bgt.w	loc_1D7B6C
	jsr	(sub_014FEE).l
	tst.b	(ram_BF4A).w
	bne.w	loc_1D7A14
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$2A,d4
	move.l	#dat_005558,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D797E
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$19,d4
	move.l	#dat_0031A8,d1
loc_1D797E:
	bsr.w	sub_1D7B7A
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$2A,d4
	move.l	#dat_00599C,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D79A4
	moveq	#$E,d2
	moveq	#$3,d3
	moveq	#$19,d4
	move.l	#dat_003448,d1
loc_1D79A4:
	bsr.w	sub_1D7B7A
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$27,d4
	move.l	#dat_005DE0,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D79CA
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$18,d4
	move.l	#dat_0036E8,d1
loc_1D79CA:
	bsr.w	sub_1D7B7A
	move.w	(ram_DDE2).w,d2
	cmp.w	(ram_BF4E).w,d2
	bne.w	loc_1D7AE4
	clr.w	(a2)
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#dat_007728,d1
	bsr.w	sub_1D7B7A
	clr.w	(a2)
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#$774F,d1
	bsr.w	sub_1D7B7A
	clr.w	(a2)
	moveq	#$D,d2
	moveq	#$3,d3
	moveq	#$0,d4
	move.l	#dat_007776,d1
	bsr.w	sub_1D7B7A
	bra.w	loc_1D7AE6
loc_1D7A14:
	moveq	#$C,d2
	moveq	#$19,d3
	move.l	#$120,d4
	move.l	#loc_000278,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7A3E
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$99,d4
	move.l	#loc_000458,d1
loc_1D7A3E:
	bsr.w	sub_1D7B7A
	moveq	#$C,d2
	moveq	#$19,d3
	move.l	#$120,d4
	move.l	#dat_001FB8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7A6C
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$99,d4
	move.l	#dat_0013F8,d1
loc_1D7A6C:
	bsr.w	sub_1D7B7A
	moveq	#$A,d2
	moveq	#$19,d3
	move.l	#$F0,d4
	move.l	#dat_003CF8,d1
	btst	#2,(ram_DD9E).w
	beq.w	loc_1D7A9A
	moveq	#$9,d2
	moveq	#$19,d3
	move.l	#$8A,d4
	move.l	#dat_002398,d1
loc_1D7A9A:
	bsr.w	sub_1D7B7A
	move.w	(ram_DDE2).w,d2
	cmp.w	(ram_BF4E).w,d2
	bne.w	loc_1D7AE4
	moveq	#$A,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007470,d1
	clr.w	(a2)
	bsr.w	sub_1D7B7A
	moveq	#$A,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007560,d1
	clr.w	(a2)
	bsr.w	sub_1D7B7A
	moveq	#$9,d2
	moveq	#$19,d3
	moveq	#$0,d4
	move.l	#dat_007650,d1
	clr.w	(a2)
	bsr.w	sub_1D7B7A
	bra.w	loc_1D7AE6
loc_1D7AE4:
	addq.w	#6,a2
loc_1D7AE6:
	moveq	#$3,d2
	moveq	#$1B,d3
	moveq	#$51,d4
	move.l	#$10080,d1
	bset	#5,(ram_C35A).w
	bsr.w	sub_1D7B7A
	bclr	#5,(ram_C35A).w
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D14C,a0
	move.w	(ram_BF4E).w,d7
	move.w	d7,d0
	mulu.w	#$1B,d0
	addi.l	#dat_001D52,d0
	moveq	#$1B,d1
	movem.l	d0/d1/a0,-(sp)
	jsr	(SRAM_Read).l
	move.w	(ram_BF4A).w,d0
	andi.w	#$FF,d0
	move.w	#$1B,d1
loc_1D7B34:
	cmp.w	d0,d1
	beq.w	loc_1D7B46
	move.b	-$1(a0,d1.w),d2
	move.b	d2,$0(a0,d1.w)
	dbra	d1,loc_1D7B34
loc_1D7B46:
	move.b	(ram_DDCF).w,$0(a0,d1.w)
	movem.l	(sp)+,d0/d1/a0
	jsr	(SRAM_Write).l
	movem.l	(sp)+,d0-d7/a0-a6
	move.w	(ram_BF4A).w,d0
	andi.w	#$FF,d0
	move.w	(ram_BF4E).w,d7
	jsr	(sub_1D7BD8).l
loc_1D7B6C:
	movea.l	(sp)+,a2
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D797E, $1D79A4, $1D79CA, $1D79E8, $1D79FA, $1D7A0C, $1D7A3E, $1D7A6C (+5 more)
sub_1D7B7A:
	movea.l	#ram_D14C,a0
	movem.l	d1-d4/a0,-(sp)
	jsr	(sub_014A42).l
	movea.l	#ram_D14C,a3
	move.w	(ram_BF4A).w,d0
	andi.w	#$FF,d0
	cmp.b	(ram_D4A7).w,d0
	blt.w	loc_1D7BAE
	btst	#5,(ram_C35A).w
	bne.w	loc_1D7BAE
	sub.b	(ram_D4A7).w,d0
loc_1D7BAE:
	add.w	d0,d0
	add.w	d3,d3
	bra.w	loc_1D7BBE
loc_1D7BB6:
	move.w	-$2(a3,d3.w),d1
	move.w	d1,$0(a3,d3.w)
loc_1D7BBE:
	subq.w	#2,d3
	cmp.w	d0,d3
	ble.w	loc_1D7BC8
	bra.s	loc_1D7BB6
loc_1D7BC8:
	move.w	(a2)+,d1
	move.w	d1,$0(a3,d3.w)
	movem.l	(sp)+,d1-d4/a0
	jmp	(sub_014A62).l


; ----------------------------------------------------------------------
; called from $1D7B66
sub_1D7BD8:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	d0,d2
	jsr	(sub_01A278).l
	move.w	d0,d3
	movea.l	#ram_D14C,a0
	mulu.w	#$1B,d7
	ext.l	d7
	addi.l	#dat_001D52,d7
	move.l	d7,d0
	moveq	#$1B,d1
	movem.l	d0/d1/a0,-(sp)
	jsr	(SRAM_Read).l
loc_1D7C06:
	move.b	$0(a0,d2.w),d4
	move.w	d3,d5
	subq.w	#1,d5
	clr.w	d0
loc_1D7C10:
	cmp.w	d0,d2
	beq.w	loc_1D7C48
	cmp.b	$0(a0,d0.w),d4
	bne.w	loc_1D7C48
	addq.b	#1,d4
	move.b	d4,d6
	andi.w	#$F,d6
	cmp.b	#$A,d6	; general form
	bne.w	loc_1D7C42
	addi.b	#$10,d4
	andi.w	#$F0,d4
	cmp.b	#$A0,d4	; general form
	bne.w	loc_1D7C42
	move.b	#$1,d4
loc_1D7C42:
	move.b	d4,$0(a0,d2.w)
	bra.s	loc_1D7C06
loc_1D7C48:
	addq.w	#1,d0
	dbra	d5,loc_1D7C10
	movem.l	(sp)+,d0/d1/a0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D75E2
sub_1D7C64:
	movem.l	d1/d6/d7/a0,-(sp)
	btst	#4,(ram_C356).w
	beq.w	loc_1D7C7E
	asl.w	#8,d7
	andi.w	#$FF,d0
	or.w	d7,d0
	bra.w	loc_1D7C9E
loc_1D7C7E:
	mulu.w	#$36,d7
	add.w	d0,d0
	ext.l	d0
	add.l	d7,d0
	addi.l	#dat_0017A2,d0
	moveq	#$2,d1
	movea.l	#ram_BF82,a0
	jsr	(SRAM_Read).l
	move.w	(a0),d0
loc_1D7C9E:
	movem.l	(sp)+,d1/d6/d7/a0
	rts

	dc.w	$0004,$4700,$0004,$4C44,$0004,$5244,$0004,$4C57
	dc.w	$0004,$4320,$0004,$5257,$48E7,$FFFE,$08B8,$0006
	dc.w	$C358,$08B8,$0007,$C35A,$4240,$1039,$0020,$1BE5
	dc.w	$B07C,$0014,$6D00,$0008,$08F8,$0007,$C35A
loc_1D7CE2:
	clr.w	(ram_D4A2).w
	clr.w	(ram_D4A4).w
	clr.w	(ram_D330).w
	bsr.w	sub_1D86C0
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	bsr.w	sub_1D884E
	tst.w	(ram_55F0).l
	bne.w	loc_1D7D24
	bset	#6,(ram_C358).w
	move.w	#$1,(ram_55F0).l
	bra.w	loc_1D7D64
loc_1D7D24:
	clr.w	(ram_D3E2).w
	move.w	#$1,(ram_D3E0).w
	move.w	(ram_55F0).l,d0
	subq.w	#1,d0
	move.w	d0,(ram_55F8).l
	subq.w	#2,d0
	bpl.w	loc_1D7D44
	clr.w	d0
loc_1D7D44:
	move.w	d0,(ram_55F4).l
	move.w	(ram_55F8).l,d0
	addq.w	#1,d0
	move.w	d0,(ram_D3E0).w
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1D866A
	bsr.w	sub_1D85F0
loc_1D7D64:
	bsr.w	sub_1D8354
	clr.w	d4
	clr.w	(ram_D4A2).w
	clr.w	(ram_D4A4).w
	clr.w	d0
	bra.w	loc_1D810E
loc_1D7D78:
	bsr.w	sub_1D8958
	move.w	#$2500,sr
loc_1D7D80:
	move.w	(FrameCounter).w,d0
loc_1D7D84:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D7D84
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1D7D80
	btst	#7,(ram_C35A).w
	bne.w	loc_1D7DAE
	btst	#6,(ram_C358).w
	beq.w	loc_1D7DB8
loc_1D7DAE:
	btst	#7,d1
	beq.s	loc_1D7D80
	bra.w	loc_1D81BA
loc_1D7DB8:
	tst.w	(ram_D4A2).w
	bne.w	loc_1D7DF8
	move.w	#$1,d0
	btst	#1,d1
	bne.w	loc_1D8072
	move.w	#$FFFF,d0
	btst	#0,d1
	bne.w	loc_1D8072
	btst	#6,d1
	beq.w	loc_1D7DEE
	clr.w	d4
	clr.w	d5
	bsr.w	sub_1D81C0
	clr.w	d0
	bra.w	loc_1D8072
loc_1D7DEE:
	btst	#4,d1
	bne.w	loc_1D81BA
	bra.s	loc_1D7D78
loc_1D7DF8:
	movea.l	#dat_1D7E0A,a0
	move.w	(ram_D4A4).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	jmp	(a0)
dat_1D7E0A:
	dc.b	$00,$1D,$7F,$88

ptrtbl_1D7E0E:
	dc.l	sub_1D7E32
	dc.l	sub_1D7E84
	dc.l	sub_1D7EB0
	dc.l	sub_1D7F12
loc_1D7E1E:
	addq.w	#1,(ram_D4A4).w
	cmpi.w	#$5,(ram_D4A4).w
	blt.w	loc_1D7D78
	jmp	(loc_1D8182).l


; ----------------------------------------------------------------------
; called from $1D7E0E
sub_1D7E32:
	btst	#7,d1
	bne.s	loc_1D7E1E
	btst	#4,d1
	bne.w	loc_1D81BA
	btst	#2,d1
	beq.w	loc_1D7E60
	move.b	(ram_5608).l,d0
	ext.w	d0
	subq.w	#1,d0
	bmi.w	loc_1D7D80
	move.b	d0,(ram_5608).l
	bra.w	loc_1D7D78
loc_1D7E60:
	btst	#3,d1
	beq.w	loc_1D7D80
	move.b	(ram_5608).l,d0
	ext.w	d0
	addq.w	#1,d0
	cmp.w	#$5,d0	; general form
	bgt.w	loc_1D7D80
	move.b	d0,(ram_5608).l
	bra.w	loc_1D7D78


; ----------------------------------------------------------------------
; called from $1D7E12
sub_1D7E84:
	btst	#7,d1
	bne.s	loc_1D7E1E
	btst	#4,d1
	bne.w	loc_1D81BA
	btst	#2,d1
	beq.w	loc_1D7EA6
loc_1D7E9A:
	eori.b	#$1,(ram_5604).l
	bra.w	loc_1D7D78
loc_1D7EA6:
	btst	#3,d1
	beq.w	loc_1D7D80
	bra.s	loc_1D7E9A


; ----------------------------------------------------------------------
; called from $1D7E16
sub_1D7EB0:
	btst	#7,d1
	bne.w	loc_1D7E1E
	btst	#4,d1
	bne.w	loc_1D81BA
	btst	#2,d1
	beq.w	loc_1D7EF2
	move.b	(ram_5601).l,d0
	lsr.w	#4,d0
	andi.w	#$F,d0
	beq.w	loc_1D7D80
	subq.b	#1,d0
loc_1D7EDA:
	lsl.b	#4,d0
	andi.w	#$F0,d0
	andi.b	#$F,(ram_5601).l
	or.b	d0,(ram_5601).l
	bra.w	loc_1D7D78
loc_1D7EF2:
	btst	#3,d1
	beq.w	loc_1D7D80
	move.b	(ram_5601).l,d0
	lsr.w	#4,d0
	andi.w	#$F,d0
	cmp.w	#$F,d0	; general form
	beq.w	loc_1D7D80
	addq.b	#1,d0
	bra.s	loc_1D7EDA


; ----------------------------------------------------------------------
; called from $1D7E1A
sub_1D7F12:
	btst	#7,d1
	bne.w	loc_1D7E1E
	btst	#4,d1
	bne.w	loc_1D81BA
	btst	#2,d1
	beq.w	loc_1D7F56
	move.b	(ram_5600).l,d0
	beq.w	loc_1D7D80
	move.b	d0,d1
	andi.w	#$F,d1
	bne.w	loc_1D7F4A
	subi.b	#$10,d0
	ori.b	#$9,d0
	bra.w	loc_1D7F4C
loc_1D7F4A:
	subq.b	#1,d0
loc_1D7F4C:
	move.b	d0,(ram_5600).l
	bra.w	loc_1D7D78
loc_1D7F56:
	btst	#3,d1
	beq.w	loc_1D7D80
	move.b	(ram_5600).l,d0
	cmp.b	#$99,d0	; general form
	beq.w	loc_1D7D80
	move.b	d0,d1
	andi.w	#$F,d1
	cmp.b	#$9,d1	; general form
	bne.w	loc_1D7F84
	addi.b	#$10,d0
	andi.b	#$F0,d0
	bra.s	loc_1D7F4C
loc_1D7F84:
	addq.b	#1,d0
	bra.s	loc_1D7F4C

	dc.w	$70FF,$0801,$0007,$6700,$009E,$6100,$0D4A,$6B00
	dc.w	$0034,$6100,$030E,$4EB9,$0002,$0A7E,$0024,$FE04
	dc.w	$FF01,$FD18,$FC13,$5B5D,$2D73,$656C,$6563,$7469
	dc.w	$6F6E,$FD18,$FA01,$7374,$6172,$743D,$6E65,$7874
	dc.w	$6000,$FE54,$6100,$02BC,$4EB9,$0002,$0A7E,$0038
	dc.w	$FE04,$FF01,$FD18,$FC13,$6261,$6420,$6E61,$6D65
	dc.w	$2065,$6E74,$7279,$2EFD,$18FA,$0161,$6E79,$2062
	dc.w	$7574,$746F,$6EFD,$18FA,$0174,$6F20,$636F,$6E74
	dc.w	$696E,$7565,$2E00,$6100,$F03E,$4EB9,$0002,$02D2
	dc.w	$4EB9,$0002,$0370,$4A41,$67EC,$6100


; ----------------------------------------------------------------------
sub_1D8024:
	andi.w	#$6100,-(a6)
	andi.l	#$6000FD4C,-(a2)
	btst	#6,d1
	bne.w	loc_1D810E
	neg.w	d0
	btst	#5,d1
	bne.w	loc_1D810E
	btst	#3,d1
	bne.w	loc_1D8138
	neg.w	d0
	btst	#2,d1
	bne.w	loc_1D8138
	moveq	#$A,d0
	btst	#1,d1
	bne.w	loc_1D8138
	neg.w	d0
	btst	#0,d1
	bne.w	loc_1D8138
	btst	#4,d1
	beq.w	loc_1D7D78
	bra.w	loc_1D81BA
loc_1D8072:
	add.w	d0,(ram_D3E0).w
	move.w	(ram_D3E0).w,d1
	cmp.w	(ram_55F0).l,d1
	ble.w	loc_1D8088
	sub.w	d0,(ram_D3E0).w
loc_1D8088:
	tst.w	(ram_D3E0).w
	bne.w	loc_1D8094
	sub.w	d0,(ram_D3E0).w
loc_1D8094:
	move.w	(ram_D3E0).w,d0
	subq.w	#1,d0
	cmp.w	(ram_55F4).l,d0
	bge.w	loc_1D80B4
	subq.w	#1,(ram_55F4).l
	subq.w	#1,(ram_55F8).l
	bsr.w	sub_1D8354
loc_1D80B4:
	cmp.w	(ram_55F8).l,d0
	ble.w	loc_1D80CE
	addq.w	#1,(ram_55F4).l
	addq.w	#1,(ram_55F8).l
	bsr.w	sub_1D8354
loc_1D80CE:
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1D866A
	bsr.w	sub_1D85F0
	tst.w	(ram_D4A2).w
	bne.w	loc_1D80E8
	bra.w	loc_1D7D78
loc_1D80E8:
	jsr	(Text_PrintFont).l
inl_1D80EE:
	dc.w	loc_1D80F4-inl_1D80EE
	dc.b	$BF,$01,$0C,$00
loc_1D80F4:
	add.w	d4,(TextX).w
	jsr	(Text_PrintFont).l
inl_1D80FE:
	dc.w	loc_1D8102-inl_1D80FE
	dc.b	$20,$00
loc_1D8102:
	bsr.w	sub_1D8232
	move.w	d4,d0
	neg.w	d0
	bra.w	loc_1D810E
loc_1D810E:
	add.w	d4,d0
	cmp.w	#$11,d0	; general form
	bhi.w	loc_1D7D78
	move.w	d0,d4
	movea.l	#ram_D3CA,a0
	clr.w	d0
	cmpi.b	#$2D,$0(a0,d4.w)
	beq.w	loc_1D8138
	move.b	$0(a0,d4.w),d0
	ext.w	d0
	bsr.w	sub_1D8260
	sub.w	d5,d0
loc_1D8138:
	add.w	d5,d0
	cmp.w	#$1D,d0	; general form
	bhi.w	loc_1D7D78
	move.w	d0,-(sp)
	bsr.w	sub_1D820E
	jsr	(Text_PrintCmd).l
inl_1D814E:
	dc.w	loc_1D8152-inl_1D814E
	dc.b	$FE,$04
loc_1D8152:
	moveq	#$1,d2
	bsr.w	sub_1D81E4
	move.w	(sp)+,d5
	bsr.w	sub_1D820E
	tst.w	(ram_D4A2).w
	beq.w	loc_1D8166
loc_1D8166:
	bsr.w	sub_1D81E4
	movea.l	#ram_D3CA,a0
	movea.l	#dat_1E1AB6,a1
	move.b	$0(a1,d5.w),d0
	move.b	d0,$0(a0,d4.w)
	bra.w	loc_1D7D78
loc_1D8182:
	clr.w	(ram_DDEA).w
	bsr.w	sub_1D8B12
	bmi.w	loc_1D81B4
	move.w	#$4,d0
loc_1D8192:
	addq.w	#1,(ram_DDEA).w
	bsr.w	sub_1D8B12
	dbra	d0,loc_1D8192
	bsr.w	sub_1D8DB6
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	jmp	(loc_1D8E84).l
loc_1D81B4:
	jmp	(loc_1D7CE2).l
loc_1D81BA:
	movem.l	(sp)+,d0-d7/a0-a6
loc_1D81BE:
	rts


; ----------------------------------------------------------------------
; called from $1D7DE4
sub_1D81C0:
	movem.l	d0-d7/a0-a6,-(sp)
	bchg	#0,(ram_D4A3).w
	bne.w	loc_1D81D8
	bsr.w	sub_1D8312
loc_1D81D2:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_1D81D8:
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1D866A
	bra.s	loc_1D81D2


; ----------------------------------------------------------------------
; called from $1D8154, $1D8166
sub_1D81E4:
	tst.w	(ram_D4A2).w
	beq.s	loc_1D81BE
	movea.l	#ram_D14C,a1
	move.w	#$4,(a1)
	move.b	#$0,$3(a1)
	movea.l	#dat_1E1AB6,a0
	move.b	$0(a0,d5.w),d0
	move.b	d0,$2(a1)
	jmp	(Text_PrintFont_Worker).l


; ----------------------------------------------------------------------
; called from $1D8144, $1D815A
sub_1D820E:
	jsr	(Text_PrintFont).l
inl_1D8214:
	dc.w	loc_1D821A-inl_1D8214
	dc.b	$8F,$1A,$0F,$00
loc_1D821A:
	move.w	d5,d0
	ext.l	d0
	divu.w	#$A,d0
	add.w	d0,(TextY).w
	swap	d0
	add.w	d0,(TextX).w
	moveq	#$1,d0
	moveq	#$1,d1
	rts


; ----------------------------------------------------------------------
; called from $1D8102
sub_1D8232:
	movem.l	d0-d4/a0-a6,-(sp)
	move.b	(ram_D3CA).w,d0
	bsr.w	sub_1D8260
	cmp.w	#$1E,d0	; general form
	blt.w	loc_1D824C
	clr.w	d5
	bra.w	loc_1D825A
loc_1D824C:
	move.w	d0,d5
	movea.l	#dat_1E1AB6,a0
	move.b	$0(a0,d5.w),(ram_D3CA).w
loc_1D825A:
	movem.l	(sp)+,d0-d4/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8132, $1D823A
sub_1D8260:
	movem.l	d1-d3/a0-a6,-(sp)
	movea.l	#dat_1E1AB6,a0
	move.b	d0,d1
	clr.w	d0
	move.w	#$1E,d3
loc_1D8272:
	cmp.b	$0(a0,d0.w),d1
	beq.w	loc_1D8284
	addq.w	#1,d0
	dbra	d3,loc_1D8272
	move.w	#$1E,d0
loc_1D8284:
	movem.l	(sp)+,d1-d3/a0-a6
	rts

	dc.w	$4EB9,$0002,$0BDE,$0006


; ----------------------------------------------------------------------
sub_1D8292:
	or.b	d7,(sp)
	move.b	d0,-(a1)
	move.w	#$10,d0
	move.w	#$4,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	rts

	dc.w	$4EB9,$0002,$0BDE,$0006,$8F17,$0D00,$303C,$0010
	dc.w	$323C,$000A,$343C,$87FF,$4EB9,$0002,$09C6,$4E75


; ----------------------------------------------------------------------
; called from $1D8312
sub_1D82CA:
	jsr	(Text_PrintCmd).l
inl_1D82D0:
	dc.w	loc_1D8310-inl_1D82D0
	dc.w	$FE04,$FF01,$FD18,$FC13
	dc.b	"a=go back"
	dc.b	$FD,$18,$FA,$01
	dc.b	"b=cancel"
	dc.b	$FD,$18,$FA,$01
	dc.b	"c=enter letter"
	dc.b	$FD,$18,$FA,$01
	dc.b	"start=done",0
loc_1D8310:
	rts


; ----------------------------------------------------------------------
; called from $1D81CE
sub_1D8312:
	bsr.s	sub_1D82CA
	jsr	(Text_PrintFont).l
inl_1D831A:
	dc.w	loc_1D8320-inl_1D831A
	dc.b	$BF,$1A,$0F,$00
loc_1D8320:
	movea.l	#dat_1E1AB6,a0
	moveq	#$2,d0
loc_1D8328:
	moveq	#$9,d1
	movea.l	#ram_BFF4,a1
	move.w	#$C,(a1)+
loc_1D8334:
	move.b	(a0)+,(a1)+
	dbra	d1,loc_1D8334
	movea.w	#$BFF4,a1
	jsr	(Text_PrintFont_Worker).l
	addq.w	#1,(TextY).w
	subi.w	#$A,(TextX).w
	dbra	d0,loc_1D8328
	rts


; ----------------------------------------------------------------------
; called from $1D7D64, $1D80B0, $1D80CA
sub_1D8354:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#7,(ram_C35A).w
	bne.w	loc_1D83B6
	btst	#6,(ram_C358).w
	beq.w	loc_1D8400
	jsr	(Text_PrintFont).l
inl_1D8372:
	dc.w	loc_1D83B2-inl_1D8372
	dc.b	$BF,$13,$06
	dc.b	"maximum number of"
	dc.b	$BF,$12,$07
	dc.b	"created players."
	dc.b	$BF,$11,$08
	dc.b	"press start to exit."
loc_1D83B2:
	bra.w	loc_1D8460
loc_1D83B6:
	jsr	(Text_PrintFont).l
inl_1D83BC:
	dc.w	loc_1D83FC-inl_1D83BC
	dc.b	$BF,$13,$06
	dc.b	"maximum number of"
	dc.b	$BF,$12,$07
	dc.b	"free agents.    "
	dc.b	$BF,$11,$08
	dc.b	"press start to exit."
loc_1D83FC:
	bra.w	loc_1D8460
loc_1D8400:
	move.w	(ram_D3DE).w,-(sp)
	move.w	(ram_D3E0).w,-(sp)
	jsr	(Text_PrintFont).l
inl_1D840E:
	dc.w	loc_1D8414-inl_1D840E
	dc.b	$BF,$13,$06,$00
loc_1D8414:
	move.w	#$3,d7
	cmp.w	(ram_55F0).l,d7
	blt.w	loc_1D8428
	move.w	(ram_55F0).l,d7
loc_1D8428:
	subq.w	#1,d7
	move.w	(ram_55F4).l,(ram_D3E0).w
	addq.w	#1,(ram_D3E0).w
	movea.l	#ram_BF56,a1
loc_1D843C:
	bsr.w	sub_1D866A
	move.w	(TextX).w,-(sp)
	bsr.w	sub_1D8526
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	addq.w	#1,(ram_D3E0).w
	dbra	d7,loc_1D843C
	move.w	(sp)+,(ram_D3E0).w
	move.w	(sp)+,(ram_D3DE).w
loc_1D8460:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8AE4
sub_1D8466:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#6,(ram_C358).w
	bne.w	loc_1D849E
	btst	#7,(ram_C35A).w
	bne.w	loc_1D849E
	move.w	(ram_D3E0).w,d0
	cmp.w	(ram_D3E2).w,d0
	beq.w	loc_1D849E
	movea.l	#dat_1D84EA,a1
	bsr.w	sub_1D84A4
	movea.l	#ptrs_1D84E2,a1
	bsr.w	sub_1D84A4
loc_1D849E:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8490, $1D849A
sub_1D84A4:
	tst.w	(ram_D3E2).w
	beq.w	loc_1D84DA
	jsr	(Text_PrintFont).l
inl_1D84B2:
	dc.w	loc_1D84B8-inl_1D84B2
	dc.b	$8F,$13,$06,$00
loc_1D84B8:
	move.w	(ram_D3E2).w,d0
	subq.w	#1,d0
	sub.w	(ram_55F4).l,d0
	add.w	d0,(TextY).w
	move.l	a1,-(sp)
	movea.l	(sp)+,a1
	adda.w	(a1),a1
	move.w	#$26,(TextX).w
	jsr	(Text_PrintFont_Worker).l
loc_1D84DA:
	move.w	(ram_D3E0).w,(ram_D3E2).w
	rts

ptrs_1D84E2:
	dc.l	dat_045D00
	dc.l	dat_045B00

dat_1D84EA:
	dc.l	dat_042000
	dc.l	dat_042000


; ----------------------------------------------------------------------
; called from $1D8958
sub_1D84F2:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$11,d3
	movea.l	#ram_D3CA,a0
	clr.w	(ram_D3DE).w
loc_1D8504:
	cmpi.b	#$2D,(a0)
	bne.w	loc_1D8512
	tst.b	(a0)+
	bra.w	loc_1D851C
loc_1D8512:
	tst.b	(a0)+
	beq.w	loc_1D8520
	addq.w	#1,(ram_D3DE).w
loc_1D851C:
	dbra	d3,loc_1D8504
loc_1D8520:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8444, $1D89A6
sub_1D8526:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D3DE).w,-(sp)
	move.w	#$12,(ram_D3DE).w
	movea.l	#ram_D14C,a0
	move.w	(ram_D3DE).w,d0
	move.w	#$0,d3
	move.w	#$16,(a0)+
loc_1D8546:
	cmp.w	#$8,d3	; general form
	bne.w	loc_1D8552
	move.b	#$20,(a0)+
loc_1D8552:
	move.b	$0(a1,d3.w),d1
	cmp.w	(ram_D3DE).w,d3
	blt.w	loc_1D8562
	move.b	#$2D,d1
loc_1D8562:
	cmp.b	#$20,d1	; general form
	bne.w	loc_1D856E
	move.b	#$2D,d1
loc_1D856E:
	move.b	d1,(a0)+
	addq.w	#1,d3
	cmp.w	#$12,d3	; general form
	blt.s	loc_1D8546
	movea.l	#ram_D14C,a1
	move.b	#$20,$15(a1)
	move.w	(TextX).w,d7
	move.l	a1,-(sp)
	jsr	(Text_PrintFont_Worker).l
	movea.l	(sp)+,a1
	tst.w	(ram_D4A2).w
	beq.w	loc_1D85E6
	adda.w	d4,a1
	cmp.w	#$8,d4	; general form
	blt.w	loc_1D85A6
	addq.w	#1,a1
loc_1D85A6:
	addq.w	#2,a1
	movea.l	#ram_BF56,a0
	move.w	#$4,(a0)
	move.b	(a1),$2(a0)
	clr.b	$3(a0)
	movea.l	a0,a1
	jsr	(Text_PrintCmd).l
inl_1D85C2:
	dc.w	loc_1D85C6-inl_1D85C2
	dc.b	$FE,$04
loc_1D85C6:
	add.w	d4,d7
	cmp.w	#$8,d4	; general form
	blt.w	loc_1D85D2
	addq.w	#1,d7
loc_1D85D2:
	move.w	d7,(TextX).w
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1D85E2:
	dc.w	loc_1D85E6-inl_1D85E2
	dc.b	$FE,$07
loc_1D85E6:
	move.w	(sp)+,(ram_D3DE).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D7D60, $1D80D8
sub_1D85F0:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D3E0).w,d1
	subq.w	#1,d1
	add.w	d1,d1
	movea.l	#ram_4E20,a0
	move.w	$0(a0,d1.w),d1
	bmi.w	loc_1D8656
	andi.w	#$FF,d1
	asl.w	#5,d1
	ext.l	d1
	move.l	#$1521,d0
	add.l	d1,d0
	moveq	#$20,d1
	movea.l	#ram_5600,a0
	jsr	(SRAM_Read).l
	movea.l	#ram_5600,a0
	adda.w	(a0),a0
	cmpa.l	#ram_5600,a0
	beq.w	loc_1D8650
	move.l	(a0),(ram_5600).l
	move.l	$4(a0),(ram_5604).l
	move.b	$8(a0),(ram_5608).l
loc_1D8650:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_1D8656:
	clr.l	(ram_5600).l
	clr.l	(ram_5604).l
	clr.b	(ram_5608).l
	bra.s	loc_1D8650


; ----------------------------------------------------------------------
; called from $1D7D5C, $1D80D4, $1D81DE, $1D843C
sub_1D866A:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#SaveDataMirror,a0
	move.w	(ram_D3E0).w,d2
	subq.w	#1,d2
	mulu.w	#$12,d2
	move.w	#$0,(ram_D3DE).w
	move.w	#$11,d3
loc_1D8688:
	move.b	$0(a0,d2.w),d0
	beq.w	loc_1D8694
	bra.w	loc_1D86A2
loc_1D8694:
	move.b	#$2D,d0
	subq.w	#1,(ram_D3DE).w
	move.b	d0,(a1)+
	bra.w	loc_1D86B0
loc_1D86A2:
	cmp.b	#$2D,d0	; general form
	bne.w	loc_1D86AE
	move.b	#$20,d0
loc_1D86AE:
	move.b	d0,(a1)+
loc_1D86B0:
	addq.w	#1,(ram_D3DE).w
	addq.w	#1,d2
	dbra	d3,loc_1D8688
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D7CEE
sub_1D86C0:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D873E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D8746:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D875E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D8766:
	bclr	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1D878A:
	dc.w	loc_1D8792-inl_1D878A
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D8792:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintFont).l
inl_1D87A6:
	dc.w	loc_1D87AC-inl_1D87A6
	dc.b	$FE,$00,$00,$00
loc_1D87AC:
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
inl_1D87D6:
	dc.w	loc_1D87EA-inl_1D87D6
	dc.b	$BF,$07,$01
	dc.b	"CREATE PLAYERS",0
loc_1D87EA:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	btst	#7,(ram_C35A).w
	bne.w	loc_1D8808
	btst	#6,(ram_C358).w
	beq.w	loc_1D8822
loc_1D8808:
	jsr	(Text_PrintFont).l
inl_1D880E:
	dc.w	loc_1D881E-inl_1D880E
	dc.b	$8F,$03,$07
	dc.b	"START-EXIT",0
loc_1D881E:
	bra.w	loc_1D8844
loc_1D8822:
	jsr	(Text_PrintFont).l
inl_1D8828:
	dc.w	loc_1D8844-inl_1D8828
	dc.b	$8F,$03,$07
	dc.b	"A-edit slot"
	dc.b	$8F,$03,$08
	dc.b	"B-cancel",0
loc_1D8844:
	move.w	(sp)+,(FontTileBase).w
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $1D7D04
sub_1D884E:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_55F0).l
	movea.l	#ram_1388,a0
	move.l	#dat_000DCA,d0
	moveq	#$28,d1
	jsr	(SRAM_Read).l
	move.w	#$14,d6
	movea.l	#ram_4E20,a3
	movea.l	#SaveDataMirror,a2
	move.w	#$FFFF,d5
	bra.w	loc_1D88C6
loc_1D8884:
	tst.w	(a0)+
	bmi.w	loc_1D88C6
	move.w	-$2(a0),d0
	andi.w	#$3F00,d0
	cmp.w	#$2800,d0	; general form
	bne.w	loc_1D88C6
	move.w	-$2(a0),d0
	jsr	(sub_1D9E20).l
	beq.w	loc_1D88C6
	move.w	-$2(a0),d0
	jsr	(sub_013C6C).l
	bsr.w	sub_1D8906
	adda.w	#$12,a2
	move.w	-$2(a0),d0
	move.w	d0,(a3)+
	addq.w	#1,(ram_55F0).l
loc_1D88C6:
	addq.w	#1,d5
	dbra	d6,loc_1D8884
	cmpi.w	#$14,(ram_55F0).l
	bge.w	loc_1D8900
	move.w	($202F42).l,d0
	andi.w	#$FF,d0
	cmp.b	#$13,d0	; general form
	bge.w	loc_1D8900
	move.w	#$11,d0
loc_1D88EE:
	move.b	#$0,(a2)+
	dbra	d0,loc_1D88EE
	move.w	#$8000,(a3)
	addq.w	#1,(ram_55F0).l
loc_1D8900:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D88B2
sub_1D8906:
	movem.l	d0-d7/a1/a2,-(sp)
	move.w	(a1)+,d7
	subq.w	#3,d7
	move.w	#$7,d6
loc_1D8912:
	cmpi.b	#$20,(a1)
	beq.w	loc_1D8924
	move.b	(a1)+,d0
	move.b	d0,(a2)+
	subq.w	#1,d7
	dbra	d6,loc_1D8912
loc_1D8924:
	tst.w	d6
	bmi.w	loc_1D8932
loc_1D892A:
	move.b	#$2D,(a2)+
	dbra	d6,loc_1D892A
loc_1D8932:
	addq.w	#1,a1
	subq.w	#1,d7
	move.w	#$9,d6
loc_1D893A:
	move.b	(a1)+,d0
	move.b	d0,(a2)+
	subq.w	#1,d6
	dbra	d7,loc_1D893A
	tst.w	d6
	bmi.w	loc_1D8952
loc_1D894A:
	move.b	#$2D,(a2)+
	dbra	d6,loc_1D894A
loc_1D8952:
	movem.l	(sp)+,d0-d7/a1/a2
	rts


; ----------------------------------------------------------------------
; called from $1D7D78
sub_1D8958:
	bsr.w	sub_1D84F2
	jsr	(Text_PrintFont).l
inl_1D8962:
	dc.w	loc_1D8968-inl_1D8962
	dc.b	$8F,$14,$05,$00
loc_1D8968:
	tst.w	(ram_D4A2).w
	beq.w	loc_1D8AE4
	jsr	(Text_PrintFont).l
inl_1D8976:
	dc.w	loc_1D897C-inl_1D8976
	dc.b	$8F,$01,$0C,$00
loc_1D897C:
	move.w	#$0,d0
	bsr.w	sub_1D8AC8
	jsr	(Text_PrintFont).l
inl_1D898A:
	dc.w	loc_1D8996-inl_1D898A
	dc.b	"Full Name:"
loc_1D8996:
	move.w	#$1,(TextX).w
	addq.w	#1,(TextY).w
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1D8526
	move.w	#$1,(TextX).w
	addq.w	#2,(TextY).w
	move.w	#$1,d0
	bsr.w	sub_1D8AC8
	jsr	(Text_PrintCmd).l
inl_1D89C2:
	dc.w	loc_1D89D2-inl_1D89C2
	dc.b	$F9,$00
	dc.b	"position:"
	dc.b	$FD,$0E,$00
loc_1D89D2:
	move.b	(ram_5608).l,d0
	ext.w	d0
	movea.l	#ptrs_1D8AEA,a1
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$1,(TextX).w
	addq.w	#2,(TextY).w
	move.w	#$2,d0
	bsr.w	sub_1D8AC8
	jsr	(Text_PrintCmd).l
inl_1D8A04:
	dc.w	loc_1D8A14-inl_1D8A04
	dc.b	"handedness:"
	dc.b	$FD,$0E,$00
loc_1D8A14:
	move.b	(ram_5604).l,d0
	andi.w	#$1,d0
	movea.l	#dat_1D8B02,a1
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$1,(TextX).w
	addq.w	#2,(TextY).w
	move.w	#$3,d0
	bsr.w	sub_1D8AC8
	jsr	(Text_PrintCmd).l
inl_1D8A48:
	dc.w	loc_1D8A58-inl_1D8A48
	dc.b	"weight:"
	dc.b	$FD,$0E,$20,$20,$20,$FD,$0E
loc_1D8A58:
	move.b	(ram_5601).l,d0
	lsr.w	#4,d0
	andi.w	#$F,d0
	jsr	(sub_019E6A).l
	jsr	(sub_020E38).l
	jsr	(Text_PrintFont_Worker).l
	move.w	#$1,(TextX).w
	addq.w	#2,(TextY).w
	move.w	#$4,d0
	bsr.w	sub_1D8AC8
	jsr	(Text_PrintCmd).l
inl_1D8A8E:
	dc.w	loc_1D8AA0-inl_1D8A8E
	dc.b	"Uniform #:"
	dc.b	$FD,$0E,$20,$20,$FD,$0E
loc_1D8AA0:
	move.b	(ram_5600).l,d0
	move.w	d0,d1
	andi.w	#$F,d1
	move.w	d1,-(sp)
	lsr.w	#4,d0
	andi.w	#$F,d0
	mulu.w	#$A,d0
	add.w	(sp)+,d0
	jsr	(sub_020E38).l
	jsr	(Text_PrintFont_Worker).l
	rts


; ----------------------------------------------------------------------
; called from $1D8980, $1D89B8, $1D89FA, $1D8A3E, $1D8A84
sub_1D8AC8:
	jsr	(Text_PrintCmd).l
inl_1D8ACE:
	dc.w	loc_1D8AD2-inl_1D8ACE
	dc.b	$FE,$04
loc_1D8AD2:
	cmp.w	(ram_D4A4).w,d0
	bne.w	loc_1D8AE4
	jsr	(Text_PrintCmd).l
inl_1D8AE0:
	dc.w	loc_1D8AE4-inl_1D8AE0
	dc.b	$FE,$07
loc_1D8AE4:
	bsr.w	sub_1D8466
	rts

ptrs_1D8AEA:
	dc.l	dat_044720
	dc.l	dat_044C44
	dc.l	dat_045244
	dc.w	$0004,$4C57,$0004,$4320,$0004,$5257
dat_1D8B02:
	dc.b	$00,$08
	dc.b	"LEFT ",0
	dc.b	$00,$08
	dc.b	"RIGHT",0


; ----------------------------------------------------------------------
; called from $1D8186, $1D8196
sub_1D8B12:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D8CDE
	bmi.w	loc_1D8CC4
	move.w	(ram_D3E0).w,d0
	subq.w	#1,d0
	add.w	d0,d0
	movea.l	#ram_4E20,a0
	tst.w	$0(a0,d0.w)
	bmi.w	loc_1D8BEC
	movem.l	d1-d3/a1,-(sp)
	movea.l	#dat_1D8B80,a1
	move.w	(ram_DDEA).w,d2
	asl.w	#2,d2
	movea.l	$0(a1,d2.w),a1
	move.w	#$0,d2
loc_1D8B4C:
	move.w	$0(a1,d2.w),d3
	andi.w	#$FF,d3
	lsl.w	#8,d3
	move.w	$2(a1,d2.w),d1
	andi.w	#$FF,d1
	or.w	d1,d3
	cmp.w	$0(a0,d0.w),d3
	beq.w	loc_1D8B98
	addq.w	#4,d2
	cmp.w	#$50,d2	; general form
	blt.s	loc_1D8B4C
	clr.w	d2
	move.w	d2,(ram_55FC).l
	movem.l	(sp)+,d1-d3/a1
	bra.w	loc_1D8CC4
dat_1D8B80:
	dc.w	$0020,$1B94,$0020,$9394,$0020,$94E8,$0020,$963C
	dc.w	$0020,$9790,$0020,$98E4
loc_1D8B98:
	tst.w	(ram_DDEA).w
	beq.w	loc_1D8BA8
	movem.l	(sp)+,d1-d3/a1
	bra.w	loc_1D8CB8
loc_1D8BA8:
	asr.w	#2,d2
	move.w	d2,(ram_55FC).l
	movem.l	(sp)+,d1-d3/a1
	move.w	$0(a0,d0.w),d1
	andi.w	#$FF,d1
	move.w	d1,(ram_55FE).l
	asl.w	#5,d1
	add.w	d1,d1
	movea.l	#$202A42,a0
	adda.w	d1,a0
	bsr.w	sub_1D8BD6
	bra.w	loc_1D8CB8


; ----------------------------------------------------------------------
; called from $1D8BCE, $1D8C34
sub_1D8BD6:
	movea.l	#ram_BF56,a1
	move.w	(a1),d0
	subq.w	#1,d0
	clr.w	d1
loc_1D8BE2:
	move.b	(a1)+,d1
	move.w	d1,(a0)+
	dbra	d0,loc_1D8BE2
	rts
loc_1D8BEC:
	tst.w	(ram_DDEA).w
	beq.w	loc_1D8BFC
	move.w	(ram_DDEC).w,d6
	bra.w	loc_1D8C3C
loc_1D8BFC:
	bsr.w	sub_1D8D86
	bmi.w	loc_1D8CC0
	movea.l	#$202A42,a0
	clr.w	d6
	move.w	#$13,d5
loc_1D8C10:
	tst.b	$1(a0)
	bne.w	loc_1D8C20
	tst.b	$3(a0)
	beq.w	loc_1D8C30
loc_1D8C20:
	adda.l	#$40,a0
	addq.w	#1,d6
	dbra	d5,loc_1D8C10
	bra.w	loc_1D8CC0
loc_1D8C30:
	move.w	d6,(ram_DDEC).w
	bsr.s	sub_1D8BD6
	addq.b	#1,($202F43).l
loc_1D8C3C:
	movea.l	#dat_1D8C76,a0
	move.w	(ram_DDEA).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	moveq	#$50,d0
	move.w	$0(a0,d0.l),d0
	andi.w	#$FF,d0
	cmp.b	#$14,d0	; general form
	bge.w	loc_1D8CBC
	clr.w	(ram_55FC).l
loc_1D8C64:
	tst.b	$1(a0)
	bmi.w	loc_1D8C8E
	addq.l	#4,a0
	addq.w	#1,(ram_55FC).l
	bra.s	loc_1D8C64
dat_1D8C76:
	dc.w	$0020,$1B94,$0020,$9394,$0020,$94E8,$0020,$963C
	dc.w	$0020,$9790,$0020,$98E4
loc_1D8C8E:
	move.b	d6,$3(a0)
	andi.w	#$FF,d6
	move.w	d6,(ram_55FE).l
	move.b	#$28,$1(a0)
	movea.l	#dat_1D8C76,a0
	move.w	(ram_DDEA).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	moveq	#$50,d0
	addq.w	#1,$0(a0,d0.l)
loc_1D8CB8:
	bra.w	loc_1D8CD6
loc_1D8CBC:
	bra.w	loc_1D8CC4
loc_1D8CC0:
	bra.w	loc_1D8CC4
loc_1D8CC4:
	jsr	(Text_PrintCmd).l
inl_1D8CCA:
	dc.w	loc_1D8CCE-inl_1D8CCA
	dc.b	$F9,$00
loc_1D8CCE:
	move.w	#$FFFF,d0
	bra.w	loc_1D8CD8
loc_1D8CD6:
	clr.w	d0
loc_1D8CD8:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8B16
sub_1D8CDE:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_BF58,a0
	movea.l	#ram_D3CA,a1
	move.w	(ram_D3DE).w,d0
	subq.w	#1,d0
	clr.w	d5
	clr.w	d6
loc_1D8CF8:
	cmp.w	#$8,d6	; general form
	bne.w	loc_1D8D0C
	tst.w	d5
	beq.w	loc_1D8D7C
	move.b	#$20,(a0)+
	addq.w	#1,d5
loc_1D8D0C:
	move.b	(a1)+,d1
	cmp.b	#$20,d1	; general form
	beq.w	loc_1D8D22
	cmp.b	#$2D,d1	; general form
	beq.w	loc_1D8D22
	move.b	d1,(a0)+
	addq.w	#1,d5
loc_1D8D22:
	addq.w	#1,d6
	dbra	d0,loc_1D8CF8
	btst	#0,d5
	beq.w	loc_1D8D36
	move.b	#$0,(a0)
	addq.w	#1,d5
loc_1D8D36:
	addq.w	#2,d5
	move.w	d5,(ram_BF56).w
	cmp.w	#$6,d5	; general form
	blt.w	loc_1D8D7C
	movea.l	#ram_BF56,a0
	adda.w	(a0),a0
	move.b	-(a0),d0
	tst.b	d0
	bne.w	loc_1D8D56
	move.b	-(a0),d0
loc_1D8D56:
	cmp.b	#$20,d0	; general form
	beq.w	loc_1D8D7C
	movea.w	#$BF56,a0
	move.w	(a0)+,d0
	subq.w	#1,d0
loc_1D8D66:
	cmpi.b	#$20,(a0)+
	beq.w	loc_1D8D76
	dbra	d0,loc_1D8D66
	bra.w	loc_1D8D7C
loc_1D8D76:
	clr.w	d0
	bra.w	loc_1D8D80
loc_1D8D7C:
	move.w	#$FFFF,d0
loc_1D8D80:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8BFC
sub_1D8D86:
	movem.w	d0,-(sp)
	clr.w	d0
	move.b	($202F43).l,d0
	cmp.b	#$14,d0	; general form
	blt.w	loc_1D8DA2
	move.w	#$FFFF,d0
	bra.w	loc_1D8DA6
loc_1D8DA2:
	move.w	#$1,d0
loc_1D8DA6:
	movem.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
sub_1D8DAC:
	bset	#2,(ram_C34E).w
	bra.w	loc_1D8DBC


; ----------------------------------------------------------------------
; called from $1D819E
sub_1D8DB6:
	bclr	#2,(ram_C34E).w
loc_1D8DBC:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_7538,a0
	clr.l	d0
	move.w	(ram_55FE).l,d0
	asl.w	#5,d0
	ext.l	d0
	addi.l	#$1521,d0
	moveq	#$20,d1
	movem.l	d0/d1/a0,-(sp)
	btst	#2,(ram_C34E).w
	bne.w	loc_1D8DEE
	jsr	(SRAM_Read).l
loc_1D8DEE:
	movea.l	#sub_1D8E7C,a1
	tst.b	(ram_5608).l
	bne.w	loc_1D8E04
	movea.l	#dat_1D8E74,a1
loc_1D8E04:
	adda.w	(a0),a0
	move.w	#$7,d0
loc_1D8E0A:
	move.b	(a1)+,(a0)+
	dbra	d0,loc_1D8E0A
	tst.b	(ram_5608).l
	beq.w	loc_1D8E26
	move.w	#$5,d0
	jsr	(Random).l
	add.b	d0,-(a0)
loc_1D8E26:
	movea.l	#ram_7538,a0
	adda.w	(a0),a0
	move.b	(ram_5600).l,(a0)
	move.b	(ram_5601).l,d0
	andi.w	#$F0,d0
	andi.b	#$F,$1(a0)
	or.b	d0,$1(a0)
	move.b	(ram_5608).l,$8(a0)
	move.b	(ram_5604).l,d0
	andi.w	#$1,d0
	andi.b	#$FE,$4(a0)
	or.b	d0,$4(a0)
	movem.l	(sp)+,d0/d1/a0
	jsr	(SRAM_Write).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1D8E74:
	dc.w	$2082,$2222,$0000,$2222


; ----------------------------------------------------------------------
; called from $1D8DEE
sub_1D8E7C:
	move.l	d2,(a0)
	move.l	-(a2),d1
	move.l	-(a2),d1
	move.l	-(sp),d1
loc_1D8E84:
	bsr.w	sub_1D9B22
	jsr	(sub_1D5E5E).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	bsr.w	sub_1D9988
	bsr.w	sub_1D99A2
	bsr.w	sub_1D99E6
	bsr.w	sub_1D8F62
	clr.w	(ram_7532).l
loc_1D8EB0:
	bsr.w	sub_1D90E4
	move.w	#$2500,sr
loc_1D8EB8:
	move.w	(FrameCounter).w,d0
loc_1D8EBC:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1D8EBC
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1D8EB8
	btst	#7,d1
	beq.w	loc_1D8EE4
	jsr	(sub_1D9A0A).l
	bra.w	loc_1D8F5C
loc_1D8EE4:
	btst	#0,d1
	beq.w	loc_1D8F0A
	tst.w	(ram_7532).l
	bne.w	loc_1D8F02
	bsr.w	sub_1D9762
	move.w	d4,(ram_7532).l
	bra.s	loc_1D8EB0
loc_1D8F02:
	subq.w	#1,(ram_7532).l
	bra.s	loc_1D8EB0
loc_1D8F0A:
	btst	#1,d1
	beq.w	loc_1D8F30
	bsr.w	sub_1D9762
	cmp.w	(ram_7532).l,d4
	ble.w	loc_1D8F28
	addq.w	#1,(ram_7532).l
	bra.s	loc_1D8EB0
loc_1D8F28:
	clr.w	(ram_7532).l
	bra.s	loc_1D8EB0
loc_1D8F30:
	btst	#6,d1
	beq.w	loc_1D8F44
	move.w	#$FFFF,d0
	bsr.w	sub_1D977E
	bra.w	loc_1D8EB0
loc_1D8F44:
	btst	#4,d1
	beq.w	loc_1D8F58
	move.w	#$1,d0
	bsr.w	sub_1D977E
	bra.w	loc_1D8EB0
loc_1D8F58:
	bra.w	loc_1D8EB8
loc_1D8F5C:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8EA6
sub_1D8F62:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_PrintFont).l
inl_1D8F6C:
	dc.w	loc_1D8F80-inl_1D8F6C
	dc.b	$8F,$07,$06
	dc.b	"First:"
	dc.b	$8F,$08,$07
	dc.b	"Last:",0
loc_1D8F80:
	movea.l	#ram_BFF6,a0
	movea.l	#ram_753A,a1
	move.w	#$2,(ram_BFF4).w
loc_1D8F92:
	move.b	(a1)+,d0
	cmp.b	#$20,d0	; general form
	beq.w	loc_1D8FA4
	move.b	d0,(a0)+
	addq.w	#1,(ram_BFF4).w
	bra.s	loc_1D8F92
loc_1D8FA4:
	clr.b	(a0)
	addq.w	#1,(ram_BFF4).w
	andi.w	#$FFFE,(ram_BFF4).w
	movea.l	#ram_BFF4,a1
	jsr	(Text_PrintFont).l
inl_1D8FBC:
	dc.w	loc_1D8FC2-inl_1D8FBC
	dc.b	$8F,$0D,$06,$00
loc_1D8FC2:
	jsr	(Text_PrintFont_Worker).l
	movea.l	#ram_BFF6,a0
	movea.l	#ram_753A,a1
	move.w	#$2,(ram_BFF4).w
	move.w	(ram_7538).l,d6
	subq.w	#3,d6
loc_1D8FE2:
	move.b	(a1)+,d0
	subq.w	#1,d6
	cmp.b	#$20,d0	; general form
	bne.s	loc_1D8FE2
loc_1D8FEC:
	move.b	(a1)+,(a0)+
	addq.w	#1,(ram_BFF4).w
	dbra	d6,loc_1D8FEC
	clr.b	(a0)
	addq.w	#1,(ram_BFF4).w
	andi.w	#$FFFE,(ram_BFF4).w
	movea.l	#ram_BFF4,a1
	jsr	(Text_PrintFont).l
inl_1D900E:
	dc.w	loc_1D9014-inl_1D900E
	dc.b	$8F,$0D,$07,$00
loc_1D9014:
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_1D9020:
	dc.w	loc_1D902A-inl_1D9020
	dc.b	$8F,$09,$08
	dc.b	"pos:",0
loc_1D902A:
	movea.l	#ram_7538,a1
	adda.w	(a1),a1
	move.b	$8(a1),d0
	ext.w	d0
	move.l	a1,-(sp)
	movea.l	#ptrs_1D8AEA,a1
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_1D9052:
	dc.w	loc_1D905C-inl_1D9052
	dc.b	$8F,$1C,$08
	dc.b	"hand:"
loc_1D905C:
	movea.l	(sp),a1
	move.b	$4(a1),d0
	andi.w	#$1,d0
	movea.l	#dat_1D8B02,a1
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_1D907E:
	dc.w	loc_1D908A-inl_1D907E
	dc.b	$8F,$1A,$07
	dc.b	"weight:"
loc_1D908A:
	movea.l	(sp),a1
	move.b	$1(a1),d0
	lsr.w	#4,d0
	andi.w	#$F,d0
	jsr	(sub_019E6A).l
	jsr	(sub_020E38).l
	jsr	(Text_PrintFont_Worker).l
	jsr	(Text_PrintFont).l
inl_1D90AE:
	dc.w	loc_1D90BA-inl_1D90AE
	dc.b	$8F,$1A,$06
	dc.b	"number:"
loc_1D90BA:
	movea.l	(sp)+,a1
	move.b	(a1),d0
	move.w	d0,d1
	andi.w	#$F,d1
	move.w	d1,-(sp)
	lsr.w	#4,d0
	andi.w	#$F,d0
	mulu.w	#$A,d0
	add.w	(sp)+,d0
	jsr	(sub_020E38).l
	jsr	(Text_PrintFont_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8EB0
sub_1D90E4:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d7
	bsr.w	sub_1D9762
loc_1D90EE:
	bsr.w	sub_1D958A
	addq.w	#1,d7
	cmp.w	d4,d7
	ble.s	loc_1D90EE
	bsr.w	sub_1D9106
	bsr.w	sub_1D9176
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D90F8
sub_1D9106:
	jsr	(Text_PrintCmd).l
inl_1D910C:
	dc.w	loc_1D9120-inl_1D910C
	dc.b	$FE,$07,$FD,$1B,$FC,$10
	dc.b	"OVERALL"
	dc.b	$FD,$1D,$FC,$11,$00
loc_1D9120:
	movea.l	#ram_7538,a0
	adda.w	(a0),a0
	addq.w	#8,a0
	movea.l	#ram_C8FE,a4
	movea.l	#dat_1D9E00,a6
	move.l	(dat_028C22).l,d4
	tst.w	(ram_7534).l
	beq.w	loc_1D9152
	movea.l	#dat_1D9DF0,a6
	move.l	(dat_028AC0).l,d4
loc_1D9152:
	jsr	(sub_1D9CB0).l
	mulu.w	#$64,d0
	divu.w	d1,d0
	jsr	(sub_1D1D90).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	rts


; ----------------------------------------------------------------------
; called from $1D90FC
sub_1D9176:
	jsr	(Text_PrintCmd).l
inl_1D917C:
	dc.w	loc_1D9198-inl_1D917C
	dc.b	$FE,$07,$FD,$17,$FC,$0D
	dc.b	"Points remaining"
	dc.b	$FD,$1D,$FC,$0E
loc_1D9198:
	move.w	(ram_7536).l,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	rts


; ----------------------------------------------------------------------
; called from $1D9592
sub_1D91B0:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ptrtbl_1D953E,a0
	tst.w	(ram_7534).l
	bne.w	loc_1D91CA
	movea.l	#dat_1D9566,a0
loc_1D91CA:
	move.w	d7,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	movea.l	#ram_7538,a2
	adda.w	(a2),a2
	jsr	(a0)
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D9542, $1D956A
sub_1D91E2:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B02).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D91E6, $1D9220, $1D9246, $1D926C, $1D9292, $1D92BA, $1D92E2, $1D9310 (+10 more)
sub_1D920A:
	movea.l	#ram_C8FE,a4
	movea.l	a2,a0
	addq.w	#8,a0
	movea.l	#dat_1D9E10,a6
	rts


; ----------------------------------------------------------------------
; called from $1D953E
sub_1D921C:
	bsr.w	sub_1D951E
	bsr.s	sub_1D920A
	move.l	(dat_028AEC).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D955E
sub_1D9242:
	bsr.w	sub_1D951E
	bsr.s	sub_1D920A
	move.l	(dat_028BC8).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9546, $1D956E
sub_1D9268:
	bsr.w	sub_1D951E
	bsr.s	sub_1D920A
	move.l	(dat_028B2E).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D954A
sub_1D928E:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B44).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9556
sub_1D92B6:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B9C).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
sub_1D92DE:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028BB2).l,d4
	jsr	(sub_1D9CB0).l
	asl.w	#3,d0
	addi.w	#$8C,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D954E
sub_1D930C:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B5A).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D955A
sub_1D9334:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B70).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9562
sub_1D935C:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028B86).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9552
sub_1D9384:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028BF4).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
sub_1D93AC:
	bsr.w	sub_1D951E
	clr.w	d4
	move.b	(a2),d4
	lsr.w	#4,d4
	mulu.w	#$A,d4
	move.b	(a2),d0
	andi.b	#$F,d0
	add.b	d4,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9566
sub_1D93D6:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028C38).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9572
sub_1D93FE:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028C7A).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9576
sub_1D9426:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028CA6).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D957A
sub_1D944E:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028CBC).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D957E
sub_1D9476:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028CD2).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9582
sub_1D949E:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028CE8).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
; called from $1D9586
sub_1D94C6:
	bsr.w	sub_1D951E
	bsr.w	sub_1D920A
	move.l	(dat_028CFE).l,d4
	jsr	(sub_1D9CB0).l
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	bra.w	loc_1D9512


; ----------------------------------------------------------------------
sub_1D94EE:
	bsr.w	sub_1D951E
	move.b	$4(a2),d0
	andi.w	#$1,d0
	movea.l	#dat_1D950A,a1
	jsr	(sub_022A6E).l
	bra.w	loc_1D9512
dat_1D950A:
	dc.w	$0004,$4C00,$0004,$5200
loc_1D9512:
	jsr	(Text_PrintCmd).l
inl_1D9518:
	dc.w	loc_1D951C-inl_1D9518
	dc.b	$FE,$04
loc_1D951C:
	rts


; ----------------------------------------------------------------------
; called from $1D91E2, $1D921C, $1D9242, $1D9268, $1D928E, $1D92B6, $1D92DE, $1D930C (+12 more)
sub_1D951E:
	jsr	(Text_PrintCmd).l
inl_1D9524:
	dc.w	loc_1D9528-inl_1D9524
	dc.b	$FE,$04
loc_1D9528:
	cmp.w	(ram_7532).l,d7
	bne.w	loc_1D953C
	jsr	(Text_PrintCmd).l
inl_1D9538:
	dc.w	loc_1D953C-inl_1D9538
	dc.b	$FE,$07
loc_1D953C:
	rts

ptrtbl_1D953E:
	dc.l	sub_1D921C
	dc.l	sub_1D91E2
	dc.l	sub_1D9268
	dc.l	sub_1D928E
	dc.l	sub_1D930C
	dc.l	sub_1D9384
	dc.l	sub_1D92B6
	dc.l	sub_1D9334
	dc.l	sub_1D9242
	dc.l	sub_1D935C
dat_1D9566:
	dc.l	sub_1D93D6
	dc.l	sub_1D91E2
	dc.l	sub_1D9268
	dc.l	sub_1D93FE
	dc.l	sub_1D9426
	dc.l	sub_1D944E
	dc.l	sub_1D9476
	dc.l	sub_1D949E
	dc.l	sub_1D94C6


; ----------------------------------------------------------------------
; called from $1D90EE
sub_1D958A:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1D959C
	bsr.w	sub_1D91B0
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D958E
sub_1D959C:
	movem.l	d0/d1/a0/a1,-(sp)
	movea.l	#dat_1D95F0,a1
	tst.w	(ram_7534).l
	bne.w	loc_1D95B6
	movea.l	#dat_1D96B8,a1
loc_1D95B6:
	move.w	d7,d0
	movem.l	d0/a1,-(sp)
	jsr	(Text_PrintCmd).l
inl_1D95C2:
	dc.w	loc_1D95C6-inl_1D95C2
	dc.b	$FE,$04
loc_1D95C6:
	cmp.w	(ram_7532).l,d7
	bne.w	loc_1D95DA
	jsr	(Text_PrintCmd).l
inl_1D95D6:
	dc.w	loc_1D95DA-inl_1D95D6
	dc.b	$FE,$07
loc_1D95DA:
	movem.l	(sp)+,d0/a1
	jsr	(List_Skip).l
	jsr	(Text_PrintCmd_Worker).l
	movem.l	(sp)+,d0/d1/a0/a1
	rts
dat_1D95F0:
	dc.w	$0010,$FD02,$FC0D,$4167,$696C,$6974,$79FD,$1300
	dc.w	$000E,$FD02,$FC0E,$5370,$6565,$64FD,$1300,$0016
	dc.w	$FD02,$FC0F,$4F66,$662E,$4177,$6172,$656E,$6573
	dc.w	$73FD,$1300,$0016,$FD02,$FC10,$4465,$662E,$4177
	dc.w	$6172,$656E,$6573,$73FD,$1300,$0012,$FD02,$FC11
	dc.w	$5368,$6F74,$2050,$6F77,$6572,$FD13,$0018,$FD02
	dc.w	$FC12,$4368,$6563,$6B69,$6E67,$2041,$6269,$6C69
	dc.w	$7479,$FD13,$0016,$FD02,$FC13,$5374,$6963,$6B20
	dc.w	$4861,$6E64,$6C69,$6E67,$FD13,$0016,$FD02,$FC14
	dc.w	$5368,$6F74,$2041,$6363,$7572,$6163,$79FD,$1300
	dc.w	$0012,$FD02,$FC15,$456E,$6475,$7261,$6E63,$65FD
	dc.w	$1300,$0016,$FD02,$FC16,$5061,$7373,$2041,$6363
	dc.w	$7572,$6163,$79FD,$1300
dat_1D96B8:
	dc.w	$0010,$FD02,$FC0D,$4167,$696C,$6974,$79FD,$1300
	dc.w	$000E,$FD02,$FC0E,$5370,$6565,$64FD,$1300,$0016
	dc.w	$FD02,$FC0F,$4F66,$662E,$4177,$6172,$656E,$6573
	dc.w	$73FD,$1300,$0016,$FD02,$FC10,$4465,$662E,$4177
	dc.w	$6172,$656E,$6573,$73FD,$1300,$0014,$FD02,$FC11
	dc.w	$5075,$636B,$2043,$6F6E,$7472,$6F6C,$FD13,$0014
	dc.w	$FD02,$FC12,$5374,$6963,$6B20,$5269,$6768,$74FD
	dc.w	$1300,$0012,$FD02,$FC13,$5374,$6963,$6B20,$4C65
	dc.w	$6674,$FD13,$0014,$FD02,$FC14,$476C,$6F76,$6520
	dc.w	$5269,$6768,$74FD,$1300,$0012,$FD02,$FC15,$476C
	dc.w	$6F76,$6520,$4C65,$6674,$FD13


; ----------------------------------------------------------------------
; called from $1D8EF6, $1D8F12, $1D90EA
sub_1D9762:
	movem.l	d6/a0,-(sp)
	move.w	#$8,d4
	tst.w	(ram_7534).l
	beq.w	loc_1D9778
	move.w	#$9,d4
loc_1D9778:
	movem.l	(sp)+,d6/a0
	rts


; ----------------------------------------------------------------------
; called from $1D8F3C, $1D8F50
sub_1D977E:
	movea.l	#ptrtbl_1D97A4,a0
	tst.w	(ram_7534).l
	beq.w	loc_1D9794
	movea.l	#ptrtbl_1D97C8,a0
loc_1D9794:
	move.w	(ram_7532).l,d1
	asl.w	#2,d1
	movea.l	$0(a0,d1.w),a0
	jsr	(a0)
	rts

ptrtbl_1D97A4:
	dc.l	sub_1D97F0
	dc.l	sub_1D9922
	dc.l	sub_1D9940
	dc.l	sub_1D984E
	dc.l	sub_1D9856
	dc.l	sub_1D988E
	dc.l	sub_1D9898
	dc.l	sub_1D98A2
	dc.l	sub_1D98AC

ptrtbl_1D97C8:
	dc.l	sub_1D992C
	dc.l	sub_1D9922
	dc.l	sub_1D9940
	dc.l	sub_1D994A
	dc.l	sub_1D995E
	dc.l	sub_1D997C
	dc.l	sub_1D9954
	dc.l	sub_1D9968
	dc.l	sub_1D9936
	dc.l	sub_1D9972


; ----------------------------------------------------------------------
; called from $1D97A4
sub_1D97F0:
	move.l	(dat_028C38).l,d4
loc_1D97F6:
	move.w	(ram_7536).l,d1
	move.w	d1,(ram_C4D4).w
	move.w	d0,d2
	neg.w	d2
	add.w	d2,d1
	bmi.w	loc_1D984C
	move.w	d1,(ram_7536).l
	movea.l	#ram_C8EE,a0
	swap	d4
loc_1D9818:
	btst	#15,d4
	bne.w	loc_1D9826
	addq.w	#1,a0
	asl.w	#1,d4
	bra.s	loc_1D9818
loc_1D9826:
	tst.w	d0
	bpl.w	loc_1D983E
	movem.w	d2/d3,-(sp)
	move.b	(a0),d2
	cmp.b	#$0,d2	; general form
	movem.w	(sp)+,d2/d3
	ble.w	loc_1D9844
loc_1D983E:
	add.b	d0,(a0)
	bra.w	loc_1D984C
loc_1D9844:
	move.w	(ram_C4D4).w,(ram_7536).l
loc_1D984C:
	rts


; ----------------------------------------------------------------------
; called from $1D97B0
sub_1D984E:
	move.l	(dat_028C7A).l,d4
	bra.s	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97B4
sub_1D9856:
	move.l	(dat_028CA6).l,d4
	bra.s	loc_1D97F6


; ----------------------------------------------------------------------
sub_1D985E:
	movea.l	#ram_7538,a0
	adda.w	(a0),a0
	clr.w	d1
	move.b	$1(a0),d1
	lsr.w	#4,d1
	andi.w	#$F,d1
	add.w	d0,d1
	bmi.s	loc_1D984C
	cmp.w	#$F,d1	; general form
	bgt.s	loc_1D984C
	lsl.w	#4,d1
	move.b	$1(a0),d0
	andi.w	#$F,d0
	or.w	d1,d0
	move.b	d0,$1(a0)
	rts


; ----------------------------------------------------------------------
; called from $1D97B8
sub_1D988E:
	move.l	(dat_028CBC).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97BC
sub_1D9898:
	move.l	(dat_028CD2).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97C0
sub_1D98A2:
	move.l	(dat_028CE8).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97C4
sub_1D98AC:
	move.l	(dat_028CFE).l,d4
	bra.w	loc_1D97F6

	dc.w	$207C,$FFFF,$7538,$D0D0,$0A28,$0001,$0004,$4E75
	dc.w	$207C,$FFFF,$7538,$D0D0,$4241,$1210,$0241,$000F
	dc.w	$4242,$1410,$E84A,$C4FC,$000A,$D242,$D001,$6A00
	dc.w	$0006,$303C,$0063,$4A00,$6600,$0006,$303C,$0063
	dc.w	$B03C,$0063,$6F00,$0006,$303C,$0001,$4A00,$6600
	dc.w	$0006,$303C,$0001,$0280,$0000,$00FF,$80FC,$000A


; ----------------------------------------------------------------------
sub_1D9916:
	move.w	d0,d1
	lsl.w	#4,d1
	swap	d0
	or.b	d0,d1
	move.b	d1,(a0)
	rts


; ----------------------------------------------------------------------
; called from $1D97A0, $1D97A8
sub_1D9922:
	move.l	(dat_028B02).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D992C:
	move.l	(dat_028AEC).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D9936:
	move.l	(dat_028BC8).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0, $1D97AC
sub_1D9940:
	move.l	(dat_028B2E).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D994A:
	move.l	(dat_028B44).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D9954:
	move.l	(dat_028B9C).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D995E:
	move.l	(dat_028B5A).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D9968:
	move.l	(dat_028B70).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D9972:
	move.l	(dat_028B86).l,d4
	bra.w	loc_1D97F6


; ----------------------------------------------------------------------
; called from $1D97A0
sub_1D997C:
	move.l	(dat_028BF4).l,d4
	bra.w	loc_1D97F6

	dc.b	$4E,$75


; ----------------------------------------------------------------------
; called from $1D8E9A, $1DDD40
sub_1D9988:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C8EE,a0
	move.w	#$3,d0
loc_1D9996:
	clr.l	(a0)+
	dbra	d0,loc_1D9996
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8E9E
sub_1D99A2:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$1F,d0
	movea.l	#$202A42,a0
	move.w	(ram_55FE).l,d1
	asl.w	#5,d1
	add.w	d1,d1
	adda.w	d1,a0
	movea.l	#ram_7538,a1
loc_1D99C2:
	move.w	(a0)+,d2
	move.b	d2,(a1)+
	dbra	d0,loc_1D99C2
	clr.w	(ram_7534).l
	movea.l	#ram_7538,a1
	adda.w	(a1),a1
	move.b	$8(a1),(ram_7535).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8EA2
sub_1D99E6:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$1E0,(ram_7536).l
	tst.w	(ram_7534).l
	beq.w	loc_1D9A04
	move.w	#$1C2,(ram_7536).l
loc_1D9A04:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D8EDA
sub_1D9A0A:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_7538,a0
	adda.w	(a0),a0
	movea.l	#ram_C8EE,a2
	move.w	#$F,d0
loc_1D9A20:
	move.w	d0,d1
	lsr.w	#1,d1
	movem.l	d1/a0,-(sp)
	clr.w	d2
	clr.w	d3
	move.b	$0(a0,d1.w),d3
	move.b	$0(a2,d0.w),d2
	btst	#0,d0
	bne.w	loc_1D9A3E
	lsr.w	#4,d3
loc_1D9A3E:
	andi.w	#$F,d3
	movea.l	#ptrtbl_1D9AB4,a1
	move.w	d0,d1
	asl.w	#2,d1
	movea.l	$0(a1,d1.w),a1
	jsr	(a1)
	movem.l	(sp)+,d1/a0
	move.b	$0(a0,d1.w),d2
	btst	#0,d0
	bne.w	loc_1D9A70
	andi.w	#$F,d2
	lsl.w	#4,d3
	andi.w	#$F0,d3
	bra.w	loc_1D9A78
loc_1D9A70:
	andi.w	#$F0,d2
	andi.w	#$F,d3
loc_1D9A78:
	or.w	d3,d2
	move.b	d2,$0(a0,d1.w)
	dbra	d0,loc_1D9A20
	movea.l	#ram_7538,a0
	clr.l	d0
	move.w	(ram_55FE).l,d0
	asl.w	#5,d0
	ext.l	d0
	addi.l	#$1521,d0
	moveq	#$20,d1
	jsr	(SRAM_Write).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts

ptrtbl_1D9AB4:
	dc.l	sub_1D9AFE
	dc.l	sub_1D9AFE
	dc.l	sub_1D9B00
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9B02
	dc.l	sub_1D9B1E
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4
	dc.l	sub_1D9AF4


; ----------------------------------------------------------------------
; called from $1D9A50, $1D9B08, $1D9B1E
sub_1D9AF4:
	ext.l	d2
	divs.w	#$E,d2
	add.w	d2,d3
	rts


; ----------------------------------------------------------------------
; called from $1D9A50
sub_1D9AFE:
	rts


; ----------------------------------------------------------------------
; called from $1D9A50
sub_1D9B00:
	rts


; ----------------------------------------------------------------------
; called from $1D9A50
sub_1D9B02:
	move.w	d3,-(sp)
	andi.w	#$FE,d3
	jsr	(sub_1D9AF4).l
	move.w	d3,d2
	move.w	(sp)+,d3
	andi.w	#$1,d3
	andi.w	#$FE,d2
	or.w	d2,d3
	rts


; ----------------------------------------------------------------------
; called from $1D9A50
sub_1D9B1E:
	bsr.s	sub_1D9AF4
	rts


; ----------------------------------------------------------------------
; called from $1D8E84
sub_1D9B22:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	bset	#5,(VideoFlags).w
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D9BA6:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D9BAE:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1D9BC6:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1D9BCE:
	bclr	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1D9BF2:
	dc.w	loc_1D9BFA-inl_1D9BF2
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1D9BFA:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintFont).l
inl_1D9C0E:
	dc.w	loc_1D9C14-inl_1D9C0E
	dc.b	$FE,$00,$00,$00
loc_1D9C14:
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
inl_1D9C3E:
	dc.w	loc_1D9C50-inl_1D9C3E
	dc.b	$BF,$08,$01
	dc.b	"CREATE PLAYER"
loc_1D9C50:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D9C60:
	dc.w	loc_1D9C76-inl_1D9C60
	dc.b	$8F,$0C,$1A
	dc.b	"{}-select rating",0
loc_1D9C76:
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1D9C80:
	dc.w	loc_1D9CAA-inl_1D9C80
	dc.b	$8F,$1A,$13
	dc.b	"a=decrease"
	dc.b	$8F,$1A,$14
	dc.b	"b=increase"
	dc.b	$8F,$1A,$15
	dc.b	"start=done",0
loc_1D9CAA:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $012C16, $1D9152, $1D91F0, $1D9228, $1D924E, $1D9274, $1D929C, $1D92C4 (+12 more)
sub_1D9CB0:
	clr.w	(ram_D4AE).w
	clr.w	(ram_D4B0).w
	clr.w	d0
	clr.w	d1
	moveq	#$F,d2
	swap	d4
loc_1D9CC0:
	btst	d2,d4
	beq.w	loc_1D9D8E
	move.w	d2,d3
	lsr.w	#1,d3
	neg.w	d3
	move.b	-$1(a0,d3.w),d3
	btst	#0,d2
	beq.w	loc_1D9CDA
	lsr.w	#4,d3
loc_1D9CDA:
	andi.w	#$F,d3
	cmp.w	#$D,d2	; general form
	bne.w	loc_1D9CEA
	bra.w	loc_1D9D88
loc_1D9CEA:
	tst.w	d2
	bne.w	loc_1D9CFA
	cmp.b	#$6,d3	; general form
	ble.w	loc_1D9CFA
	subq.b	#6,d3
loc_1D9CFA:
	cmp.w	#$5,d2	; general form
	bne.w	loc_1D9D02
loc_1D9D02:
	cmp.w	#$6,d2	; general form
	beq.w	loc_1D9D88
	movem.l	d5-d7,-(sp)
	move.b	$0(a6,d2.w),d5
	ext.w	d5
	cmp.w	#$2,d5	; general form
	beq.w	loc_1D9D2A
	move.w	d3,-(sp)
	subq.w	#2,d5
loc_1D9D20:
	add.w	(sp),d3
	dbra	d5,loc_1D9D20
	asr.w	#1,d3
	tst.w	(sp)+
loc_1D9D2A:
	movem.l	(sp)+,d5-d7
	cmpa.l	#dat_1D9E10,a6
	beq.w	loc_1D9D52
	neg.w	d2
	move.w	d7,-(sp)
	move.b	-$1(a4,d2.w),d7
	ext.w	d7
	add.w	d7,(ram_D4AE).w
	addq.w	#1,(ram_D4B0).w
	move.w	(sp)+,d7
	neg.w	d2
	bra.w	loc_1D9D88
loc_1D9D52:
	move.w	d3,-(sp)
	asl.w	#4,d3
	add.w	(sp),d3
	add.w	(sp)+,d3
	neg.w	d2
	add.b	-$1(a4,d2.w),d3
	bpl.w	loc_1D9D70
	clr.b	d3
	addq.b	#1,-$1(a4,d2.w)
	subq.w	#1,(ram_7536).l
loc_1D9D70:
	cmp.b	#$63,d3	; general form
	ble.w	loc_1D9D86
	move.b	#$63,d3
	subq.b	#1,-$1(a4,d2.w)
	addq.w	#1,(ram_7536).l
loc_1D9D86:
	neg.w	d2
loc_1D9D88:
	add.w	d3,d0
	addi.w	#$64,d1
loc_1D9D8E:
	dbra	d2,loc_1D9CC0
	cmpa.l	#dat_1D9E10,a6
	beq.w	loc_1D9DB6
	move.w	#$64,d1
	movem.l	d6/d7,-(sp)
	move.w	(ram_D4AE).w,d6
	ext.l	d6
	move.w	(ram_D4B0).w,d7
	divs.w	d7,d6
	add.w	d6,d0
	movem.l	(sp)+,d6/d7
loc_1D9DB6:
	cmp.w	d1,d0
	blt.w	loc_1D9DC0
	move.w	d0,d1
	subq.w	#1,d0
loc_1D9DC0:
	bsr.w	sub_1D9DC6
	rts


; ----------------------------------------------------------------------
; called from $1D0922, $1D9DC0
sub_1D9DC6:
	cmp.l	(dat_028AC0).l,d4
	beq.w	loc_1D9DDA
	cmp.l	(dat_028C22).l,d4
	bne.w	loc_1D9DEE
loc_1D9DDA:
	movem.l	d1,-(sp)
	addq.w	#3,d1
	asr.w	#2,d1
	cmp.w	d1,d0
	bge.w	loc_1D9DEA
	move.w	d1,d0
loc_1D9DEA:
	movem.l	(sp)+,d1
loc_1D9DEE:
	rts
dat_1D9DF0:
	dc.w	$0202,$0202,$0406,$0204,$0204,$0606,$0402,$0202
dat_1D9E00:
	dc.w	$0202,$0202,$0202,$0202,$0909,$0202,$0902,$0202
dat_1D9E10:
	dc.w	$0202,$0202,$0202,$0202,$0202,$0202,$0202,$0202


; ----------------------------------------------------------------------
; called from $1D889E
sub_1D9E20:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	d0,d3
	move.l	#dat_0049CA,d0
	bsr.w	sub_1D9EA4
	bne.w	loc_1D9E70
	move.l	#dat_004A74,d0
	bsr.w	sub_1D9EA4
	bne.w	loc_1D9E70
	move.l	#dat_004B1E,d0
	bsr.w	sub_1D9EA4
	bne.w	loc_1D9E70
	move.l	#dat_004BC8,d0
	bsr.w	sub_1D9EA4
	bne.w	loc_1D9E70
	move.l	#dat_004C72,d0
	bsr.w	sub_1D9EA4
	bne.w	loc_1D9E70
	bra.w	loc_1D9E82
loc_1D9E70:
	move.l	#dat_000DCA,d0
	bsr.w	sub_1D9E96
	move.w	#$0,d0
	bra.w	loc_1D9E90
loc_1D9E82:
	move.l	#dat_000DCA,d0
	bsr.w	sub_1D9E96
	move.w	#$1,d0
loc_1D9E90:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D9E76, $1D9E88, $1D9EA4
sub_1D9E96:
	movea.l	#ram_1388,a0
	moveq	#$28,d1
	jmp	(SRAM_Read).l


; ----------------------------------------------------------------------
; called from $1D9E2C, $1D9E3A, $1D9E48, $1D9E56, $1D9E64
sub_1D9EA4:
	bsr.s	sub_1D9E96
	move.w	#$14,d6
	movea.l	#ram_4E20,a3
	movea.l	#SaveDataMirror,a2
	move.w	#$FFFF,d5
	bra.w	loc_1D9ECE
loc_1D9EBE:
	tst.w	(a0)+
	bmi.w	loc_1D9ECE
	move.w	-$2(a0),d0
	cmp.w	d3,d0
	beq.w	loc_1D9ED8
loc_1D9ECE:
	addq.w	#1,d5
	dbra	d6,loc_1D9EBE
	move.w	#$1,d6
loc_1D9ED8:
	rts


; ----------------------------------------------------------------------
; called from $018860
sub_1D9EDA:
	movem.l	d0/d1/a0,-(sp)
	move.l	#$DFC,d0
	moveq	#$78,d1
	jsr	(sub_029D2A).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $029BD4
sub_1D9EF2:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_0DCA,a0
	move.w	#$13,d6
loc_1D9F00:
	move.w	#$8000,(a0)+
	dbra	d6,loc_1D9F00
	move.b	#$0,(ram_0DF2).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1D9F16:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$26,d7
	bset	#6,(SysFlags).w
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	movem.w	d0/d7,-(sp)
	jsr	(sub_1DA012).l
	move.w	d0,(a2)+
	movem.w	(sp)+,d0/d7
	jsr	(sub_013D6E).l
	move.w	(ram_DDCE).w,(a2)+
	movea.l	#ram_D14C,a0
	jsr	(sub_1DA03A).l
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	add.w	d0,d0
	cmp.w	#$26,d0	; general form
	bne.w	loc_1D9F6E
	move.w	#$8000,(ram_D172).w
	bra.w	loc_1D9F86
loc_1D9F6E:
	move.w	#$26,d3
loc_1D9F72:
	move.w	$2(a0,d0.w),d1
	move.w	d1,$0(a0,d0.w)
	addq.w	#2,d0
	cmp.w	d3,d0
	blt.s	loc_1D9F72
	move.w	#$8000,$0(a0,d0.w)
loc_1D9F86:
	move.w	d0,-(sp)
	move.w	#$28,d0
	subq.b	#1,$0(a0,d0.w)
	move.w	(sp)+,d0
	jsr	(sub_1DA052).l
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#$201BF8,a0
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
	mulu.w	#$C,d0
	adda.l	d0,a0
	move.l	a0,-(sp)
	move.w	#$2,d2
loc_1D9FB6:
	move.b	$1(a0),(a2)+
	move.b	$3(a0),(a2)+
	addq.w	#4,a0
	dbra	d2,loc_1D9FB6
	movea.l	(sp)+,a0
	move.w	(ram_BF48).w,d0
	andi.w	#$FF,d0
loc_1D9FCE:
	cmp.w	#$13,d0	; general form
	beq.w	loc_1D9FEE
	move.l	$C(a0),(a0)
	move.l	$10(a0),$4(a0)
	move.l	$14(a0),$8(a0)
	adda.w	#$C,a0
	addq.w	#1,d0
	bra.s	loc_1D9FCE
loc_1D9FEE:
	addq.w	#6,a2
	clr.w	d7
	moveq	#$3,d2
	moveq	#$14,d3
	move.l	#dat_006F98,d1
	jsr	(sub_1D785C).l
	movem.l	(sp)+,d0-d7/a0-a6
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D9F30
sub_1DA012:
	movem.l	d1-d7/a0-a6,-(sp)
	movea.l	#$201B94,a0
	add.w	d0,d0
	add.w	d0,d0
	adda.w	d0,a0
	move.w	$2(a0),d0
	andi.w	#$FF,d0
	move.w	(a0),d7
	lsl.w	#8,d7
	andi.w	#$FF00,d7
	or.w	d7,d0
	movem.l	(sp)+,d1-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D9F4C
sub_1DA03A:
	movem.l	d0/d1,-(sp)
	move.l	#dat_000DCA,d0
	moveq	#$29,d1
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $1D9F92
sub_1DA052:
	movem.l	d0/d1,-(sp)
	move.l	#dat_000DCA,d0
	moveq	#$29,d1
	jsr	(SRAM_Write).l
	movem.l	(sp)+,d0/d1
	rts

	incbin	"data/bin/data_1DA06A.bin"	; 3878 bytes


; ----------------------------------------------------------------------
sub_1DAF90:
	move.l	d0,d7
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01A278).l
	subq.w	#2,d0
	move.w	d0,d5
loc_1DAFA0:
	movea.l	#ram_3A98,a0
	move.w	d5,d4
	clr.w	d6
loc_1DAFAA:
	move.b	$1(a0),d0
	cmp.b	$5(a0),d0
	ble.w	loc_1DAFC4
	st	d6
	move.l	(a0),d0
	move.l	$4(a0),d2
	move.l	d0,$4(a0)
	move.l	d2,(a0)
loc_1DAFC4:
	addq.w	#4,a0
	dbra	d4,loc_1DAFAA
	tst.w	d6
	bne.s	loc_1DAFA0
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$08F8,$0005,$C358,$21FC,$0001,$728E,$D260,$08B8
	dc.w	$0000,$BFB4,$08F8,$0002,$BFB4,$08B8,$0001,$BFB4
	dc.w	$31FC,$0000,$B000,$31FC,$B800,$B002,$31FC,$B800
	dc.w	$B00C,$31FC,$0005,$B00E,$31FC,$C000,$B008,$31FC
	dc.w	$0006,$B00A,$31FC,$E000,$B004,$31FC,$0006,$B006
	dc.w	$303C,$0000,$4EB9,$0002,$05CE,$08B8,$0005,$BFB4
	dc.w	$4EB9,$0002,$0314,$383C,$0001,$31C4,$B01C,$31C4
	dc.w	$B01E,$247C,$001A,$9842,$4EB9,$0002,$0774,$0123
	dc.w	$4567,$89DE,$EEEF,$21FC,$001A,$983A,$BF8C,$31C4
	dc.w	$B018,$31C4,$B014,$247C,$001A,$A150,$4EB9,$0002
	dc.w	$0774,$0123,$4567,$89DE,$EEEF,$31C4,$B020,$247C
	dc.w	$001A,$AD9E,$4EB9,$0002,$0780,$4EB9,$0002,$0A7E
	dc.w	$0008,$FF01,$FD00,$FC00,$7028,$721C,$343C,$87FF
	dc.w	$4EB9,$0002,$09C6,$4EB9,$0002,$0BDE,$0006,$FE00
	dc.w	$0000,$207C,$001A,$41D4,$2248,$2448,$D1DA,$D3DA
	dc.w	$4240,$4241,$7428,$761C,$7A09,$4EB9,$0002,$06E2
	dc.w	$08F8,$0002,$C356,$4EB9,$0002,$0F14,$0014,$BF06
	dc.w	$0152,$454C,$4541,$5345,$2050,$4C41,$5945,$5253
	dc.w	$33C4,$FFFF,$2328,$0644,$00C8,$4EB9,$0002,$0F38
	dc.w	$0016,$F804,$0115,$0C70,$6F73,$F804,$011C,$0C6F
	dc.w	$7665,$7261,$6C6C,$46FC,$2500,$4E75,$48E7,$FFFE
	dc.w	$6100,$F778,$4EB9,$0002,$0CC2,$0006,$BF18,$0600
	dc.w	$4EB9,$0002,$0A7E,$0048,$7374,$6172,$742D,$6578
	dc.w	$6974,$FD17,$FA01,$632D,$7265,$6C65,$6173,$6520
	dc.w	$706C,$6179,$6572,$FD16,$FA01,$7B7D,$7365,$6C65
	dc.w	$6374,$2070,$6C61,$7965,$72FD,$15FA,$0161,$2F62
	dc.w	$2D73,$7769,$7463,$6820,$7465,$616D,$7300,$4CDF
	dc.w	$7FFF,$4E75


; ----------------------------------------------------------------------
sub_1DB188:
	movem.l	a0/a1,-(sp)
	movea.l	#dat_1AD3E8,a0
	movea.l	#ram_BD80,a1
	move.w	#$7,d0
loc_1DB19C:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_1DB19C
	movem.l	(sp)+,a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1D7434, $1D743E
sub_1DB1A8:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	($200000).l,d0
	subq.b	#1,d0
	cmp.b	d7,d0
	bne.w	loc_1DB1BE
	bsr.w	sub_1DB20C
loc_1DB1BE:
	move.w	($201876).l,d0
	subq.b	#1,d0
	cmp.b	d7,d0
	bne.w	loc_1DB1D0
	bsr.w	sub_1DB216
loc_1DB1D0:
	move.w	($201DE6).l,d0

; ----------------------------------------------------------------------
sub_1DB1D6:
	subq.b	#1,d0
	cmp.b	d7,d0
	bne.w	loc_1DB1E2
	bsr.w	sub_1DB1FE
loc_1DB1E2:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1DB1E8:
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_1DB20C
	bsr.w	sub_1DB1FE
	bsr.w	sub_1DB216
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1D6380, $1DB1DE, $1DB1F0
sub_1DB1FE:
	move.l	#$EF3,d0
	moveq	#$41,d1
	jmp	(sub_029D2A).l


; ----------------------------------------------------------------------
; called from $1D638A, $1DB1BA, $1DB1EC
sub_1DB20C:
	moveq	#$0,d0
	moveq	#$41,d1
	jmp	(sub_029D2A).l


; ----------------------------------------------------------------------
; called from $1D6356, $1DB1CC, $1DB1F4
sub_1DB216:
	move.l	#$C3B,d0
	moveq	#$41,d1
	jmp	(sub_029D2A).l


; ----------------------------------------------------------------------
; called from $026E56, $1DB23C
sub_1DB224:
	jsr	(sub_1D2B14).l
	cmpi.w	#$7,(ram_DEF4).w
	bne.s	loc_1DB23E
	clr.w	(ram_DEA8).w
	jsr	(sub_1D5E7E).l
	bra.s	sub_1DB224
loc_1DB23E:
	move.w	#$15,(ram_D2A2).w
	move.w	#$1D,(ram_D2A4).w
	move.w	(VDP_HVCOUNTER).l,(RandomSeed).w
	move.w	(VDP_HVCOUNTER).l,(ram_D298).w
	bclr	#3,(ram_C350).w
	bclr	#7,(ram_C350).w
	clr.w	(ram_B8C8).w
	clr.w	(ram_B8CA).w
	st	(ram_D294).w
	jsr	(sub_0279E6).l
	movea.l	#ram_D2B4,a3
	jsr	(sub_027834).l
	move.w	(ram_CFD6).w,d0
	or.w	(ram_CFD4).w,d0
	beq.w	loc_1DB296
	jsr	(sub_027354).l
loc_1DB296:
	jsr	(sub_014FEE).l
	bclr	#1,(ram_C35A).w
	btst	#1,(ram_DD9E).w
	beq.w	loc_1DB2BC
	btst	#3,(ram_DD9E).w
	bne.w	loc_1DB2BC
	bset	#1,(ram_C35A).w
loc_1DB2BC:
	bclr	#7,(SysFlags).w
	jsr	(sub_00BD98).l
	bsr.w	sub_1DC0F4
	move.w	(ram_DEF4).w,(ram_D270).w
	cmpi.w	#$4,(ram_D270).w
	bne.w	loc_1DB2F2
	btst	#1,(ram_C35A).w
	bne.w	loc_1DB2F2
	tst.b	(ram_DDA2).w
	bpl.w	loc_1DB2F2
	clr.w	(ram_D270).w
loc_1DB2F2:
	cmpi.w	#$1,(ram_D270).w
	bne.w	loc_1DB30C
	move.w	(ram_CFD6).w,d0
	or.w	(ram_CFD4).w,d0
	bne.w	loc_1DB30C
	clr.w	(ram_D270).w
loc_1DB30C:
	bclr	#1,(ram_C34C).w
	bsr.w	sub_1DBA2E
	clr.w	(ram_D330).w
	bsr.w	sub_1DBA7C
	bsr.w	sub_1DB6F8
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DB61E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DB61E
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	(ram_D270).w,d0
	asl.w	#1,d0
	move.w	dat_1DB35E(pc,d0.w),(ram_D01A).l
	move.w	(ram_D01A).w,d0
	jsr	(sub_1D2EF4).l
	bra.w	loc_1DB372
dat_1DB35E:
	dc.w	$0000,$0001,$0001,$0001,$0001,$0008,$0000,$0001
	dc.w	$0000,$0000
loc_1DB372:
	bsr.w	sub_1DB6E8
	move.w	#$2500,sr
loc_1DB37A:
	move.w	(FrameCounter).w,d0
loc_1DB37E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1DB37E
	jsr	(sub_1D2EE8).l
	addq.w	#1,(ram_D330).w
	cmpi.w	#$2A30,(ram_D330).w
	bge.w	loc_1DB5EA
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1DB3AE
	clr.w	(ram_D330).w
loc_1DB3AE:
	move.b	d1,(ram_DCC4).w
	btst	#7,d1
	bne.w	loc_1DB61E
	btst	#1,d1
	beq.w	loc_1DB4C4
	cmpi.w	#$9,(ram_D270).w
	bne.s	loc_1DB3D8
	tst.w	(ram_D01A).w
	bne.s	loc_1DB3D8
	move.w	#$8,(ram_D01A).w
	bra.s	loc_1DB372
loc_1DB3D8:
	cmpi.w	#$9,(ram_D01A).w
	beq.s	loc_1DB37A
	cmpi.w	#$4,(ram_D270).w
	beq.s	loc_1DB37A
	cmpi.w	#$5,(ram_D270).w
	beq.s	loc_1DB37A
loc_1DB3F0:
	addq.w	#1,(ram_D01A).w
	cmpi.w	#$0,(ram_D01A).w
	bne.w	loc_1DB446
	cmpi.w	#$1,(ram_D270).w
	beq.s	loc_1DB3F0
	cmpi.w	#$2,(ram_D270).w
	beq.s	loc_1DB3F0
	cmpi.w	#$3,(ram_D270).w
	beq.s	loc_1DB3F0
	cmpi.w	#$3,(ram_D01A).w
	bne.w	loc_1DB42E
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB42E
	addq.w	#1,(ram_D01A).w
loc_1DB42E:
	cmpi.w	#$6,(ram_D01A).w
	bne.w	loc_1DB446
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB446
	addq.w	#1,(ram_D01A).w
loc_1DB446:
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB488
	cmpi.w	#$3,(ram_D01A).w
	bne.w	loc_1DB45E
	addq.w	#1,(ram_D01A).w
loc_1DB45E:
	cmpi.w	#$4,(ram_D01A).w
	bne.w	loc_1DB46C
	addq.w	#1,(ram_D01A).w
loc_1DB46C:
	cmpi.w	#$5,(ram_D01A).w
	bne.w	loc_1DB47A
	addq.w	#1,(ram_D01A).w
loc_1DB47A:
	cmpi.w	#$6,(ram_D01A).w
	bne.w	loc_1DB488
	addq.w	#1,(ram_D01A).w
loc_1DB488:
	cmpi.w	#$6,(ram_D270).w
	bne.w	loc_1DB372
	cmpi.w	#$2,(ram_D01A).w
	bne.w	loc_1DB4A4
	addq.w	#5,(ram_D01A).w
	bra.w	loc_1DB372
loc_1DB4A4:
	cmpi.w	#$1,(ram_D01A).w
	bne.w	loc_1DB4B2
	addq.w	#1,(ram_D01A).w
loc_1DB4B2:
	cmpi.w	#$3,(ram_D01A).w
	bne.w	loc_1DB372
	addq.w	#4,(ram_D01A).w
	bra.w	loc_1DB372
loc_1DB4C4:
	btst	#0,d1
	beq.w	loc_1DB5AE
	cmpi.w	#$9,(ram_D270).w
	bne.s	loc_1DB4E4
	cmpi.w	#$8,(ram_D01A).w
	bne.s	loc_1DB4E4
	clr.w	(ram_D01A).w
	bra.w	loc_1DB372
loc_1DB4E4:
	tst.w	(ram_D01A).w
	beq.w	loc_1DB37A
	subq.w	#1,(ram_D01A).w
	cmpi.w	#$0,(ram_D01A).w
	bne.w	loc_1DB51E
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1DB518
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DB518
	cmpi.w	#$3,(ram_D270).w
	bne.w	loc_1DB51E
loc_1DB518:
	move.w	#$1,(ram_D01A).w
loc_1DB51E:
	cmpi.w	#$7,(ram_D01A).w
	beq.w	loc_1DB372
	cmpi.w	#$6,(ram_D01A).w
	bne.w	loc_1DB540
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB540
	subq.w	#1,(ram_D01A).w
loc_1DB540:
	cmpi.w	#$5,(ram_D01A).w
	bne.w	loc_1DB558
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB558
	subq.w	#1,(ram_D01A).w
loc_1DB558:
	cmpi.w	#$4,(ram_D01A).w
	bne.w	loc_1DB570
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB570
	subq.w	#1,(ram_D01A).w
loc_1DB570:
	cmpi.w	#$3,(ram_D01A).w
	bne.w	loc_1DB588
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DB588
	subq.w	#1,(ram_D01A).w
loc_1DB588:
	cmpi.w	#$6,(ram_D270).w
	bne.w	loc_1DB372
loc_1DB592:
	cmpi.w	#$2,(ram_D01A).w
	bne.w	loc_1DB5A0
	bra.w	loc_1DB372
loc_1DB5A0:
	tst.w	(ram_D01A).w
	beq.w	loc_1DB372
	subq.w	#1,(ram_D01A).w
	bra.s	loc_1DB592
loc_1DB5AE:
	btst	#2,d1
	beq.w	loc_1DB5CC
	movea.l	#dat_1DB6C4,a0
	move.w	(ram_D01A).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	subq.w	#1,(a0)
	bra.w	loc_1DB372
loc_1DB5CC:
	btst	#3,d1
	beq.w	loc_1DB37A
	movea.l	#dat_1DB6C4,a0
	move.w	(ram_D01A).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	addq.w	#1,(a0)
	bra.w	loc_1DB372
loc_1DB5EA:
	clr.w	(ram_D294).w
	clr.w	(ram_D270).w
	clr.w	(ram_D286).w
	clr.w	(ram_D278).w
	move.w	#$1,(ram_D27A).w
	clr.w	(ram_D27C).w
	move.w	#$2,(ram_D27E).w
	clr.w	(ram_D280).w
	move.w	#$1,(ram_D282).w
	move.w	#$1,(ram_D284).w
	bra.w	loc_1DB650
loc_1DB61E:
	clr.w	(ram_DEA8).w
	btst	#6,d3
	beq.w	loc_1DB646
	btst	#4,d3
	beq.w	loc_1DB646
	btst	#5,d3
	beq.w	loc_1DB646
	move.w	#$1,(ram_DEA8).w
	move.w	#$1,(ram_D286).w
loc_1DB646:
	move.w	#$4,(ram_D272).w
	bsr.w	sub_1DC118
loc_1DB650:
	bsr.w	sub_1DC13C
	btst	#7,(ram_C350).w
	beq.w	loc_1DB664
	jsr	(sub_1E495A).l
loc_1DB664:
	btst	#7,(SysFlags).w
	beq.w	loc_1DB6BC
	jsr	(sub_015340).l
	jsr	(sub_00BD98).l
	jsr	(sub_014FEE).l
	btst	#1,(ram_DD9E).w
	beq.w	loc_1DB690
	bset	#1,(ram_C35A).w
loc_1DB690:
	btst	#2,(ram_DD9E).w
	beq.w	loc_1DB6BC
	jsr	(sub_0279E6).l
	jsr	(sub_027834).l
	tst.w	(ram_CFDC).w
	bne.w	loc_1DB6BC
	tst.w	(ram_CFD4).w
	bne.w	loc_1DB6BC
	jmp	(sub_027276).l
loc_1DB6BC:
	jsr	(sub_027354).l
	rts
dat_1DB6C4:
	dc.w	$FFFF,$D286,$FFFF,$D278,$FFFF,$D27A,$FFFF,$D27C
	dc.w	$FFFF,$D27E,$FFFF,$D280,$FFFF,$D282,$FFFF,$D284
	dc.w	$FFFF,$D288


; ----------------------------------------------------------------------
; called from $1DB372
sub_1DB6E8:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_018A68).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DB31E
sub_1DB6F8:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_DEDA).w
	move.l	#Art_1A861E,(ram_DEDE).w
	movea.l	#Art_1A861E_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEE2).w
	move.l	#Art_1A8F2C,(ram_DEE6).w
	movea.l	#Art_1A8F2C_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_DEEA).w
	move.l	#Font_Menu,(ram_DEEE).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DB7AA:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DB7B2:
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DB7C2:
	dc.w	$0123,$4567,$89AB,$CDEF
loc_1DB7CA:
	jsr	(Text_PrintCmd).l
inl_1DB7D0:
	dc.w	loc_1DB7D8-inl_1DB7D0
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DB7D8:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DB7EC:
	dc.w	loc_1DB7F2-inl_1DB7EC
	dc.b	$FE,$00,$00,$00
loc_1DB7F2:
	movea.l	#Art_PlayoffLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	move.w	#$400,d4
	movea.l	#Art_1A7990_Tiles,a2
	jsr	(sub_020780).l
	move.w	(FrameCounter).w,d0
loc_1DB824:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1DB824
	move.l	(ram_DEEE).w,(FontPtr).w
	move.l	(ram_DEEA).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1DB83C:
	dc.w	loc_1DB8BC-inl_1DB83C
	dc.b	$BF,$04,$06
	dc.b	"rosters:"
	dc.b	$BF,$04,$08
	dc.b	"period length:"
	dc.b	$BF,$04,$0A
	dc.b	"goalies:"
	dc.b	$BF,$04,$0C
	dc.b	"user records:"
	dc.b	$BF,$04,$0E
	dc.b	"penalties:"
	dc.b	$BF,$04,$10
	dc.b	"line changes:"
	dc.b	$BF,$04,$12
	dc.b	"fighting:"
	dc.b	$BF,$04,$14
	dc.b	"skill level:"
	dc.b	$BF,$04,$16
	dc.b	"game speed:",0
loc_1DB8BC:
	tst.w	(ram_D270).w
	bne.s	loc_1DB8DE
	jsr	(Text_PrintBig).l
inl_1DB8C8:
	dc.w	loc_1DB8DA-inl_1DB8C8
	dc.b	$FF,$09,$01
	dc.b	"REGULAR GAME",0
loc_1DB8DA:
	bra.w	loc_1DB9FC
loc_1DB8DE:
	cmpi.w	#$1,(ram_D270).w
	bne.s	loc_1DB906
	jsr	(Text_PrintBig).l
inl_1DB8EC:
	dc.w	loc_1DB902-inl_1DB8EC
	dc.b	$FF,$05,$01
	dc.b	"CONTINUE PLAYOFF",0
loc_1DB902:
	bra.w	loc_1DB9FC
loc_1DB906:
	cmpi.w	#$2,(ram_D270).w
	bne.s	loc_1DB92A
	jsr	(Text_PrintBig).l
inl_1DB914:
	dc.w	loc_1DB926-inl_1DB914
	dc.b	$FF,$09,$01
	dc.b	"NEW PLAYOFFS",0
loc_1DB926:
	bra.w	loc_1DB9FC
loc_1DB92A:
	cmpi.w	#$3,(ram_D270).w
	bne.s	loc_1DB950
	jsr	(Text_PrintBig).l
inl_1DB938:
	dc.w	loc_1DB94C-inl_1DB938
	dc.b	$FF,$06,$01
	dc.b	"PLAYOFFS BEST/7"
loc_1DB94C:
	bra.w	loc_1DB9FC
loc_1DB950:
	cmpi.w	#$4,(ram_D270).w
	bne.s	loc_1DB976
	jsr	(Text_PrintBig).l
inl_1DB95E:
	dc.w	loc_1DB972-inl_1DB95E
	dc.b	$FF,$06,$01
	dc.b	"CONTINUE SEASON"
loc_1DB972:
	bra.w	loc_1DB9FC
loc_1DB976:
	cmpi.w	#$5,(ram_D270).w
	bne.s	loc_1DB998
	jsr	(Text_PrintBig).l
inl_1DB984:
	dc.w	loc_1DB994-inl_1DB984
	dc.b	$FF,$0B,$01
	dc.b	"NEW SEASON",0
loc_1DB994:
	bra.w	loc_1DB9FC
loc_1DB998:
	cmpi.w	#$6,(ram_D270).w
	bne.s	loc_1DB9B8
	jsr	(Text_PrintBig).l
inl_1DB9A6:
	dc.w	loc_1DB9B4-inl_1DB9A6
	dc.b	$FF,$0D,$01
	dc.b	"SHOOTOUT",0
loc_1DB9B4:
	bra.w	loc_1DB9FC
loc_1DB9B8:
	cmpi.w	#$8,(ram_D270).w
	bne.s	loc_1DB9D8
	jsr	(Text_PrintBig).l
inl_1DB9C6:
	dc.w	loc_1DB9D4-inl_1DB9C6
	dc.b	$FF,$0D,$01
	dc.b	"PRACTICE",0
loc_1DB9D4:
	bra.w	loc_1DB9FC
loc_1DB9D8:
	cmpi.w	#$9,(ram_D270).w
	bne.s	loc_1DB9FC
	jsr	(Text_PrintBig).l
inl_1DB9E6:
	dc.w	loc_1DB9FC-inl_1DB9E6
	dc.b	$FF,$06,$01
	dc.b	"SKILLS CHALLENGE",0
loc_1DB9FC:
	jsr	(Text_PrintFont).l
inl_1DBA02:
	dc.w	loc_1DBA28-inl_1DBA02
	dc.b	$BF,$06,$1A
	dc.b	"{}selects option []changes option"
loc_1DBA28:
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $1DB312
sub_1DBA2E:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D450,a0
	moveq	#$12,d0
loc_1DBA3A:
	clr.w	(a0)+
	dbra	d0,loc_1DBA3A
	movea.l	#ram_C732,a0
	move.w	#$39D,d0
loc_1DBA4A:
	clr.w	(a0)+
	dbra	d0,loc_1DBA4A
	movea.l	#ram_C3B2,a0
	moveq	#$4E,d0
loc_1DBA58:
	clr.w	(a0)+
	dbra	d0,loc_1DBA58
	clr.w	(ram_C342).w
	clr.w	(ram_C344).w
	clr.w	(TextFlags).w
	clr.w	(ram_C34A).w
	clr.w	(ram_D31E).w
	clr.w	(ram_D32E).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DB31A
sub_1DBA7C:
	move.l	#dat_1DBAA2,(ram_D01E).l
	clr.w	(ram_D01A).w
	clr.w	(ram_D01C).w
	move.w	#$9,(ram_D026).w
	move.w	#$16,(ram_B03E).w
	move.w	#$6,(ram_B040).w
	rts
dat_1DBAA2:
	dc.w	$0006,$FE04,$F900,$0006,$FE04,$F900

ptrtbl_1DBAAE:
	dc.l	sub_1DBD8C
	dc.l	sub_1DBD1A
	dc.l	sub_1DBCC0
	dc.l	sub_1DBC66
	dc.l	sub_1DBC0C
	dc.l	sub_1DBBB2
	dc.l	sub_1DBB62
	dc.l	sub_1DBB08
	dc.l	sub_1DBAD6
	dc.b	$FF,$FF,$FF,$FF


; ----------------------------------------------------------------------
; called from $1DBACE
sub_1DBAD6:
	move.w	(ram_D288).w,d0
	cmp.w	#$2,d0	; general form
	ble.w	loc_1DBAE4
	clr.w	d0
loc_1DBAE4:
	tst.w	d0
	bpl.w	loc_1DBAEE
	move.w	#$2,d0
loc_1DBAEE:
	move.w	d0,(ram_D288).w
	movea.l	#dat_1DC0BE,a1
	moveq	#$8,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBACA
sub_1DBB08:
	cmpi.w	#$8,(ram_D270).w
	beq.w	loc_1DBB30
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$7,(ram_D270).w
	bge.w	loc_1DBD2E
loc_1DBB30:
	move.w	(ram_D284).w,d0
	cmp.w	#$2,d0	; general form
	ble.w	loc_1DBB3E
	clr.w	d0
loc_1DBB3E:
	tst.w	d0
	bpl.w	loc_1DBB48
	move.w	#$2,d0
loc_1DBB48:
	move.w	d0,(ram_D284).w
	movea.l	#dat_1DBFD4,a1
	moveq	#$7,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBAC6
sub_1DBB62:
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$6,(ram_D270).w
	bge.w	loc_1DBD2E
	move.w	(ram_D282).w,d0
	cmp.w	#$1,d0	; general form
	ble.w	loc_1DBB8E
	clr.w	d0
loc_1DBB8E:
	tst.w	d0
	bpl.w	loc_1DBB98
	move.w	#$1,d0
loc_1DBB98:
	move.w	d0,(ram_D282).w
	movea.l	#dat_1DBFB0,a1
	moveq	#$6,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBAC2
sub_1DBBB2:
	cmpi.w	#$8,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$6,(ram_D270).w
	bge.w	loc_1DBD2E
	move.w	(ram_D280).w,d0
	cmp.w	#$2,d0	; general form
	ble.w	loc_1DBBE8
	clr.w	d0
loc_1DBBE8:
	tst.w	d0
	bpl.w	loc_1DBBF2
	move.w	#$2,d0
loc_1DBBF2:
	move.w	d0,(ram_D280).w
	movea.l	#dat_1DBF7A,a1
	moveq	#$5,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBABE
sub_1DBC0C:
	cmpi.w	#$8,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$6,(ram_D270).w
	bge.w	loc_1DBD2E
	move.w	(ram_D27E).w,d0
	cmp.w	#$2,d0	; general form
	ble.w	loc_1DBC42
	clr.w	d0
loc_1DBC42:
	tst.w	d0
	bpl.w	loc_1DBC4C
	move.w	#$2,d0
loc_1DBC4C:
	move.w	d0,(ram_D27E).w
	movea.l	#dat_1DBF44,a1
	moveq	#$4,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBABA
sub_1DBC66:
	cmpi.w	#$8,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$6,(ram_D270).w
	bge.w	loc_1DBD2E
	move.w	(ram_D27C).w,d0
	cmp.w	#$1,d0	; general form
	ble.w	loc_1DBC9C
	clr.w	d0
loc_1DBC9C:
	tst.w	d0
	bpl.w	loc_1DBCA6
	move.w	#$1,d0
loc_1DBCA6:
	move.w	d0,(ram_D27C).w
	movea.l	#dat_1DBF20,a1
	moveq	#$3,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBAB6
sub_1DBCC0:
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$7,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$9,(ram_D270).w
	beq.w	loc_1DBD2E
	move.w	(ram_D27A).w,d0
	cmp.w	#$1,d0	; general form
	ble.w	loc_1DBCF6
	clr.w	d0
loc_1DBCF6:
	tst.w	d0
	bpl.w	loc_1DBD00
	move.w	#$1,d0
loc_1DBD00:
	move.w	d0,(ram_D27A).w
	movea.l	#dat_1DBEFC,a1
	moveq	#$2,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBAB2
sub_1DBD1A:
	cmpi.w	#$8,(ram_D270).w
	beq.w	loc_1DBD5A
	cmpi.w	#$6,(ram_D270).w
	blt.w	loc_1DBD42
loc_1DBD2E:
	move.l	(ram_DEE6).w,(FontPtr).w
	move.l	(ram_DEE2).w,(FontTileBase).w
	movea.l	#dat_1DBE8E,a1
	rts
loc_1DBD42:
	cmpi.w	#$4,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$4,(ram_D270).w
	beq.s	loc_1DBD2E
loc_1DBD5A:
	move.w	(ram_D278).w,d0
	cmp.w	#$3,d0	; general form
	blt.w	loc_1DBD68
	clr.w	d0
loc_1DBD68:
	tst.w	d0
	bpl.w	loc_1DBD72
	move.w	#$2,d0
loc_1DBD72:
	move.w	d0,(ram_D278).w
	movea.l	#dat_1DBEC6,a1
	moveq	#$1,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBAAE
sub_1DBD8C:
	cmpi.w	#$7,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$5,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$4,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$1,(ram_D270).w
	beq.s	loc_1DBD2E
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DBD2E
	cmpi.w	#$3,(ram_D270).w
	beq.w	loc_1DBD2E
	move.w	(ram_D286).w,d0
	cmp.w	#$1,d0	; general form
	ble.w	loc_1DBDCE
	clr.w	d0
loc_1DBDCE:
	tst.w	d0
	bpl.w	loc_1DBDD8
	move.w	#$1,d0
loc_1DBDD8:
	move.w	d0,(ram_D286).w
	movea.l	#dat_1DBEA2,a1
	moveq	#$0,d5
	jsr	(sub_1D2F54).l
	jsr	(List_Skip).l
	rts


; ----------------------------------------------------------------------
; called from $1DBE2A
sub_1DBDF2:
	move.w	(ram_D270).w,d0
	bpl.w	loc_1DBDFE
	move.w	#$9,d0
loc_1DBDFE:
	cmp.w	#$9,d0	; general form
	ble.w	loc_1DBE08
	clr.w	d0
loc_1DBE08:
	cmp.w	#$7,d0	; general form
	bne.w	loc_1DBE34
	btst	#2,(ram_DD9E).w
	beq.w	loc_1DBE34
	btst	#2,(ram_DCC4).w
	beq.w	loc_1DBE2C
	move.w	#$6,(ram_D270).w
	bra.s	sub_1DBDF2
loc_1DBE2C:
	move.w	#$8,d0
	bra.w	loc_1DBE7C
loc_1DBE34:
	cmp.w	#$1,d0	; general form
	bne.w	loc_1DBE5A
	move.w	(ram_CFD6).w,d1
	or.w	(ram_CFD4).w,d1
	bne.w	loc_1DBE5A
	move.w	#$2,d0
	btst	#2,(ram_DCC4).w
	beq.w	loc_1DBE5A
	move.w	#$0,d0
loc_1DBE5A:
	cmp.w	#$4,d0	; general form
	bne.w	loc_1DBE7C
	tst.b	(ram_DDA2).w
	bpl.w	loc_1DBE7C
	move.w	#$5,d0
	btst	#2,(ram_DCC4).w
	beq.w	loc_1DBE7C
	move.w	#$3,d0
loc_1DBE7C:
	move.w	d0,(ram_D270).w
	movea.l	#dat_1DC00A,a1
	jsr	(List_Skip).l
	rts
dat_1DBE8E:
	dc.b	$00,$14,$FE,$04
	dc.b	"                "
dat_1DBEA2:
	dc.b	$00,$12
	dc.b	"  with trades   ",0
	dc.b	$12
	dc.b	"    Regular     "
dat_1DBEC6:
	dc.b	$00,$12
	dc.b	"   5 minutes    ",0
	dc.b	$12
	dc.b	"   10 minutes   ",0
	dc.b	$12
	dc.b	"   20 minutes   "
dat_1DBEFC:
	dc.b	$00,$12
	dc.b	" Manual Control ",0
	dc.b	$12
	dc.b	"  Auto control  "
dat_1DBF20:
	dc.b	$00,$12
	dc.b	"      off       ",0
	dc.b	$12
	dc.b	"      on        "
dat_1DBF44:
	dc.b	$00,$12
	dc.b	"      off       ",0
	dc.b	$12
	dc.b	"on, no offsides ",0
	dc.b	$12
	dc.b	"      on        "
dat_1DBF7A:
	dc.b	$00,$12
	dc.b	"      off       ",0
	dc.b	$12
	dc.b	"      auto      ",0
	dc.b	$12
	dc.b	"      on        "
dat_1DBFB0:
	dc.b	$00,$12
	dc.b	"      on        ",0
	dc.b	$12
	dc.b	"      off       "
dat_1DBFD4:
	dc.b	$00,$12
	dc.b	"      pro       ",0
	dc.b	$12
	dc.b	"    all-star    ",0
	dc.b	$12
	dc.b	"     rookie     "
dat_1DC00A:
	dc.b	$00,$12
	dc.b	"regular game    ",0
	dc.b	$12
	dc.b	"continue playoff",0
	dc.b	$12
	dc.b	"new playoffs    ",0
	dc.b	$12
	dc.b	"new poffs best/7",0
	dc.b	$12
	dc.b	"continue season ",0
	dc.b	$12
	dc.b	"new season      ",0
	dc.b	$12
	dc.b	"shootout        ",0
	dc.b	$12
	dc.b	"transactions    ",0
	dc.b	$12
	dc.b	"practice        ",0
	dc.b	$12
	dc.b	"skills challenge"
dat_1DC0BE:
	dc.b	$00,$12
	dc.b	"     normal     ",0
	dc.b	$12
	dc.b	"      high      ",0
	dc.b	$12
	dc.b	"      low       "


; ----------------------------------------------------------------------
; called from $1DB2C8
sub_1DC0F4:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D270,a0
	move.l	#dat_002118,d0
	moveq	#$1A,d1
	jsr	(SRAM_Read).l
	move.w	(ram_DED8).w,(ram_D270).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DB64C
sub_1DC118:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D270,a0
	move.l	#dat_002118,d0
	moveq	#$1A,d1
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DB650
sub_1DC13C:
	movem.l	d0-d7/a0-a6,-(sp)
	bclr	#7,(SysFlags).w
	bclr	#6,(ram_C354).w
	bclr	#3,(ram_C350).w
	cmpi.w	#$8,(ram_D270).w
	bne.w	loc_1DC182
	bset	#3,(ram_C350).w
	move.w	#$2,(ram_C3A4).w
	move.w	#$2,(ram_C3A6).w
	clr.w	(ram_D27E).w
	clr.w	(ram_D270).w
	move.w	#$0,(ram_D27C).w
	move.w	#$0,(ram_D280).w
loc_1DC182:
	cmpi.w	#$9,(ram_D270).w
	bne.w	loc_1DC1A2
	bset	#7,(ram_C350).w
	clr.w	(ram_D270).w
	move.w	#$0,(ram_D27C).w
	move.w	#$0,(ram_D27A).w
loc_1DC1A2:
	cmpi.w	#$7,(ram_D270).w
	beq.w	loc_1DC1DE
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DC1DE
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1DC1E6
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DC1E6
	cmpi.w	#$3,(ram_D270).w
	beq.w	loc_1DC1E6
	cmpi.w	#$5,(ram_D270).w
	bne.w	loc_1DC1EC
loc_1DC1DE:
	clr.w	(ram_D286).w
	bra.w	loc_1DC1EC
loc_1DC1E6:
	move.w	#$1,(ram_D286).w
loc_1DC1EC:
	bclr	#4,(ram_C356).w
	tst.w	(ram_D286).w
	beq.w	loc_1DC200
	bset	#4,(ram_C356).w
loc_1DC200:
	bsr.w	sub_1DC2AA
	bsr.w	sub_1DC288
	cmpi.w	#$4,(ram_D270).w
	bne.w	loc_1DC220
	clr.w	(ram_D270).w
	bset	#7,(SysFlags).w
	bra.w	loc_1DC282
loc_1DC220:
	cmpi.w	#$5,(ram_D270).w
	bne.w	loc_1DC23E
	clr.w	(ram_D270).w
	bset	#7,(SysFlags).w
	bset	#6,(ram_C354).w
	bra.w	loc_1DC282
loc_1DC23E:
	cmpi.w	#$6,(ram_D270).w
	bne.w	loc_1DC26E
	move.w	#$0,(ram_D270).w
	move.w	#$1,(ram_D27C).w
	move.w	#$1,(ram_D280).w
	clr.w	(ram_D27E).w
	bset	#0,(ram_C34A).w
	jsr	(sub_1D0B5C).l
	bra.w	loc_1DC282
loc_1DC26E:
	bsr.w	sub_1DC2B2
	bsr.w	sub_1DC2DA
	jsr	(sub_1DC2F4).l
	jsr	(sub_1D2A08).l
loc_1DC282:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $015028, $1DC204
sub_1DC288:
	cmpi.w	#$4,(ram_D270).w
	beq.w	loc_1DC2A8
	cmpi.w	#$5,(ram_D270).w
	beq.w	loc_1DC2A8
	move.w	(ram_D27A).w,(ram_D28A).w
	move.w	(ram_D27A).w,(ram_D28C).w
loc_1DC2A8:
	rts


; ----------------------------------------------------------------------
; called from $015010, $1DC200
sub_1DC2AA:
	eori.w	#$1,(ram_D27C).w
	rts


; ----------------------------------------------------------------------
; called from $015016, $1DC26E
sub_1DC2B2:
	movea.l	#dat_1DC2EE,a0
	move.w	(ram_D280).w,d0
	bclr	#4,(ram_C34C).w
	cmp.w	#$1,d0	; general form
	bne.w	loc_1DC2D0
	bset	#4,(ram_C34C).w
loc_1DC2D0:
	move.b	$0(a0,d0.w),d0
	move.w	d0,(ram_D280).w
	rts


; ----------------------------------------------------------------------
; called from $01501C, $1DC272
sub_1DC2DA:
	movea.l	#dat_1DC2F1,a0
	move.w	(ram_D27E).w,d0
	move.b	$0(a0,d0.w),d0
	move.w	d0,(ram_D27E).w
	rts
dat_1DC2EE:
	dc.b	$01,$00,$00
dat_1DC2F1:
	dc.b	$00,$02,$01


; ----------------------------------------------------------------------
; called from $015022, $1DC276
sub_1DC2F4:
	movea.l	#dat_1DC314,a0
	movea.l	#dat_1DC31A,a1
	move.w	(ram_D284).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),(ram_D2A2).w
	move.w	$0(a1,d0.w),(ram_D2A4).w
	rts
dat_1DC314:
	dc.b	$00,$15,$00,$17,$00,$13
dat_1DC31A:
	incbin	"data/bin/data_1DC31A.bin"	; 752 bytes


; ----------------------------------------------------------------------
sub_1DC60A:
	move.w	d6,d0
	jsr	(sub_02861C).l
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	rts

	incbin	"data/bin/data_1DC622.bin"	; 1134 bytes


; ----------------------------------------------------------------------
sub_1DCA90:
	suba.w	-(a4),sp
	movem.l	d0-d2/a0/a1,-(sp)
	lea	$184(a2),a0
	move.w	d2,d1
	andi.w	#$FFF8,d1
	lea	$0(a0,d1.w),a1
	moveq	#$5,d1
loc_1DCAA6:
	cmp.b	$1(a1,d1.w),d0
	dbeq	d1,loc_1DCAA6
	bne.w	loc_1DCAB8
	move.b	$0(a0,d2.w),$1(a1,d1.w)
loc_1DCAB8:
	move.b	d0,$0(a0,d2.w)
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
sub_1DCAC2:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_D280).w
	beq.w	loc_1DCB56
	movea.l	#$200000,a0
	btst	#7,(SysFlags).w
	beq.w	loc_1DCAE4
	movea.l	#$201876,a0
loc_1DCAE4:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1DCAFE
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DCAFE
	cmpi.w	#$3,(ram_D270).w
loc_1DCAFE:
	nop
	bne.w	loc_1DCB0A
	movea.l	#$201DE6,a0
loc_1DCB0A:
	addq.w	#2,a0
	lea	$184(a2),a1
	move.b	$1(a0),(a1)+
	move.b	$3(a0),(a1)+
	move.b	$5(a0),(a1)+
	move.b	$7(a0),(a1)+
	move.b	$9(a0),(a1)+
	move.b	$B(a0),(a1)+
	move.b	$D(a0),(a1)+
	move.b	$F(a0),(a1)+
	adda.w	#$10,a0
	adda.w	#$10,a0
	move.w	#$B,d0
loc_1DCB3C:
	move.b	$1(a0),(a1)+
	move.b	$3(a0),(a1)+
	move.b	$5(a0),(a1)+
	move.b	$7(a0),(a1)+
	addq.w	#8,a0
	dbra	d0,loc_1DCB3C
	bra.w	loc_1DCBB6
loc_1DCB56:
	move.w	#$D,d0
	movea.l	#$200000,a0
	btst	#7,(SysFlags).w
	beq.w	loc_1DCB70
	movea.l	#$201876,a0
loc_1DCB70:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1DCB8A
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DCB8A
	cmpi.w	#$3,(ram_D270).w
loc_1DCB8A:
	nop
	bne.w	loc_1DCB96
	movea.l	#$201DE6,a0
loc_1DCB96:
	addq.w	#2,a0
	adda.w	#$10,a0
	lea	$184(a2),a1
loc_1DCBA0:
	move.b	$1(a0),(a1)+
	move.b	$3(a0),(a1)+
	move.b	$5(a0),(a1)+
	move.b	$7(a0),(a1)+
	addq.w	#8,a0
	dbra	d0,loc_1DCBA0
loc_1DCBB6:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1DCBBC:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#$200000,a0
	btst	#7,(SysFlags).w
	beq.w	loc_1DCBD6
	movea.l	#$201876,a0
loc_1DCBD6:
	cmpi.w	#$1,(ram_D270).w
	beq.w	loc_1DCBF0
	cmpi.w	#$2,(ram_D270).w
	beq.w	loc_1DCBF0
	cmpi.w	#$3,(ram_D270).w
loc_1DCBF0:
	nop
	bne.w	loc_1DCBFC
	movea.l	#$201DE6,a0
loc_1DCBFC:
	move.w	$28(a2),d7
	addq.w	#1,d7
	move.w	d7,(a0)+
	lea	$184(a2),a1
	move.b	(a1)+,$1(a0)
	move.b	(a1)+,$3(a0)
	move.b	(a1)+,$5(a0)
	move.b	(a1)+,$7(a0)
	move.b	(a1)+,$9(a0)
	move.b	(a1)+,$B(a0)
	move.b	(a1)+,$D(a0)
	move.b	(a1)+,$F(a0)
	adda.w	#$10,a0
	lea	$184(a2),a1
	move.w	#$D,d0
loc_1DCC34:
	move.b	(a1)+,$1(a0)
	move.b	(a1)+,$3(a0)
	move.b	(a1)+,$5(a0)
	move.b	(a1)+,$7(a0)
	addq.w	#8,a0
	dbra	d0,loc_1DCC34
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts

	dc.w	$4E75,$0102,$0304,$0509,$0A0B,$0C0D,$1112,$1314
	dc.w	$1519,$1A1B,$1C1D,$2122,$2324,$2529,$2A2B,$2C31
	dc.w	$3233,$34FF,$2F0A,$08F8,$0005,$C358,$21FC,$0001
	dc.w	$728E,$D260,$08B8,$0000,$BFB4,$08F8,$0002,$BFB4
	dc.w	$08B8,$0001,$BFB4,$31FC,$0000,$B000,$31FC,$B800
	dc.w	$B002,$31FC,$B800,$B00C,$31FC,$0005,$B00E,$31FC
	dc.w	$C000,$B008,$31FC,$0006,$B00A,$31FC,$E000,$B004
	dc.w	$31FC,$0006,$B006,$303C,$0000,$4EB9,$0002,$05CE
	dc.w	$08B8,$0005,$BFB4,$4EB9,$0002,$0314,$383C,$0001
	dc.w	$31C4,$B01C,$247C,$001A,$9842,$4EB9,$0002,$0774
	dc.w	$0123,$4567,$89DE,$EEEF,$31C4,$B01E,$247C,$001A
	dc.w	$9842,$4EB9,$0002,$0774,$E123,$4567,$89DE,$EEEF
	dc.w	$21FC,$001A,$983A,$BF8C,$31C4,$B018,$45F9,$001A
	dc.w	$A150,$4EB9,$0002,$0774,$0123,$4567,$89DE,$EEEF
	dc.w	$08F8,$0002,$C356,$21FC,$001A,$A148,$B010,$4EB9
	dc.w	$0002,$0A7E,$0008,$FF01,$FD00,$FC00,$7028,$721C
	dc.w	$343C,$87FF,$4EB9,$0002,$09C6,$31C4,$B02E,$4EB9
	dc.w	$0002,$0BDE,$0006,$BF01,$0400,$2457,$3E2A,$0028
	dc.w	$7A02,$4EB9,$0001,$6EF4,$6100,$0044,$4EB9,$0002
	dc.w	$0BDE,$0006,$FE00,$0000


; ----------------------------------------------------------------------
sub_1DCD94:
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
	move.w	d4,(ram_B020).w
	lea	(Art_1AAD96_Tiles).l,a2
	jsr	(sub_020780).l
	move.w	#$2500,sr
	movea.l	(sp)+,a2
	rts

	dc.b	$4E,$B9,$00,$02,$0C,$C2,$00,$34,$CF,$04,$19
	dc.b	"{}[]-highlight player"
	dc.b	$CF,$07,$1A
	dc.b	"c-select player to editNu"


; ----------------------------------------------------------------------
; called from $1DDCEE, $1DF352, $1E5220
sub_1DCE06:
	movem.l	a0/a1,-(sp)
	movea.l	#dat_1AD3E8,a0
	movea.l	#ram_BD80,a1
	move.w	#$7,d0
loc_1DCE1A:
	move.l	(a0)+,(a1)+
	dbra	d0,loc_1DCE1A
	movem.l	(sp)+,a0/a1
	rts


; ----------------------------------------------------------------------
sub_1DCE26:
	movem.l	d0-d3/a0/a2,-(sp)
	jsr	(sub_013C56).l
	movea.w	#$BFF6,a1
	move.b	#$20,(a1)+
	move.w	(a0)+,d0
	lea	-$2(a0,d0.w),a2
loc_1DCE3E:
	cmpi.b	#$20,(a0)+
	bne.s	loc_1DCE3E
loc_1DCE44:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	beq.w	loc_1DCE58
	tst.b	(a0)
	bne.s	loc_1DCE44
	bra.w	loc_1DCE58
loc_1DCE54:
	move.b	#$20,(a1)+
loc_1DCE58:
	cmpa.w	#$C001,a1
	blt.s	loc_1DCE54
	jsr	(sub_028714).l
	movem.l	(sp)+,d0-d3/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $01988C, $026CA2
sub_1DCE6A:
	jsr	(sub_01FFA2).l
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
	move.w	#$2700,sr
	jsr	(sub_1DCF24).l
	movea.l	#VDP_DATA,a0
	move.w	#$9100,$4(a0)
	move.w	#$9200,$4(a0)
	bclr	#0,(ram_C33C).w
	jsr	(sub_025926).l
	movea.l	#ram_C762,a0
	btst	#1,(a0)
	beq.w	loc_1DCEEE
	bset	#0,(a0)
loc_1DCEEE:
	adda.l	#loc_00039E,a0
	btst	#1,(a0)
	beq.w	loc_1DCF00
	bset	#0,(a0)
loc_1DCF00:
	move.w	#$18,(FadeCounter).w
	bclr	#5,(ram_C356).w
	beq.w	loc_1DCF16
	move.w	#$FFFF,(FadeCounter).w
loc_1DCF16:
	tst.w	(FadeCounter).w
	bpl.s	loc_1DCF16
	move.w	(FrameCounter).w,(ram_B056).w
	rts


; ----------------------------------------------------------------------
; called from $01A356, $1DCEB8
sub_1DCF24:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$FFFFFFFF,(ram_BEB0).w
	move.l	#$FFFFFFFF,(ram_BEB4).w
	move.l	#$FFFFFFFF,(ram_BEB8).w
	clr.w	(ram_B04A).w
	move.l	#VBlank_InGame,(VBlankVector).w
	bset	#1,(VideoFlags).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$DC00,(HScrollTableAddr).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$F000,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$FC00,(ram_B000).w
	movea.w	#$BD40,a0
	moveq	#$1F,d1
loc_1DCF88:
	clr.l	(a0)+
	dbra	d1,loc_1DCF88
	jsr	(sub_026B9C).l
	jsr	(sub_026676).l
	jsr	(VDP_Init).l
	jsr	(sub_1DD100).l
	move.w	#$800,d0
	move.w	(PlaneAAddr).w,d1
	move.w	#$7FF,d2
	jsr	(sub_02057E).l
	move.w	(ram_B02A).w,d4
	jsr	(sub_021310).l
	move.w	(ram_B03A).w,d4
	jsr	(sub_029EE6).l
	jsr	(sub_029F00).l
	move.w	(ram_B022).w,d4
	movea.l	#Art_16CE5C_Tiles,a2
	jsr	(sub_020780).l
	move.w	(ram_B026).w,d4
	movea.l	#Art_16A662_Tiles,a2
	jsr	(sub_020780).l
	jsr	(sub_02668C).l
	jsr	(sub_026622).l
	btst	#4,(VideoFlags).w
	beq.w	loc_1DD03C
	btst	#3,(ram_C33E).w
	bne.w	loc_1DD03C
	move.w	(ram_B03C).w,d4
	movea.l	#Art_09E52A_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B028).w
	movea.l	#Art_IngameMisc_Tiles,a2
	jsr	(sub_020780).l
	jsr	(sub_00C7EC).l
	bra.w	loc_1DD070
loc_1DD03C:
	move.w	(ram_B03C).w,d4
	btst	#3,(ram_C33E).w
	beq.w	loc_1DD054
	movea.l	#Art_170DF4_Tiles,a2
	bra.w	loc_1DD06A
loc_1DD054:
	movea.l	#Art_RefereeCutscene_Tiles,a2
	btst	#4,(ram_C350).w
	beq.w	loc_1DD06A
	movea.l	#Art_0A5714_Tiles,a2
loc_1DD06A:
	jsr	(sub_020780).l
loc_1DD070:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	move.w	#$7D0,(ram_BD32).w
	clr.w	d4
	move.w	d4,(ram_B024).w
	movea.l	#Art_Rink_Tiles,a2
	jsr	(sub_020780).l
	jsr	(sub_1D1856).l
	btst	#3,(ram_C33E).w
	beq.w	loc_1DD0A8
	jsr	(sub_1D1846).l
loc_1DD0A8:
	jsr	(sub_026B9C).l
	jsr	(sub_026676).l
	move.w	(sp)+,(VideoFlags).w
	bclr	#0,(VideoFlags).w
	bclr	#2,(VideoFlags).w
	move.w	#$2300,sr
	jsr	(sub_02698A).l
	move.w	(FrameCounter).w,d0
loc_1DD0D2:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1DD0D2
	bset	#3,(VideoFlags).w
	jsr	(sub_022296).l
	bset	#7,(ram_C356).w
	btst	#3,(ram_C33E).w
	bne.w	loc_1DD0FA
	move.w	#$64,(FadeCounter).w
loc_1DD0FA:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DCFA0
sub_1DD100:
	movem.l	d0/d1/a0-a3,-(sp)
	movea.l	#ram_B060,a0
	move.w	#$80,d0
	move.w	#$F,d1
loc_1DD112:
	st	$8(a0)
	adda.w	d0,a0
	dbra	d1,loc_1DD112
	movea.l	#ram_BEBC,a0
	move.w	#$14,d0
	move.w	#$3,d1
loc_1DD12A:
	st	$8(a0)
	adda.w	d0,a0
	dbra	d1,loc_1DD12A
	movea.l	#ram_BDCC,a0
	move.w	#$1C,d0
	move.w	#$7,d1
loc_1DD142:
	st	$8(a0)
	adda.w	d0,a0
	dbra	d1,loc_1DD142
	movem.l	(sp)+,d0/d1/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $019924
sub_1DD152:
	move.l	a2,-(sp)
	jsr	(sub_0921E8).l
	move.w	#$2700,sr
	move.l	#VBlank_Main2,(VBlankVector).l
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	bset	#5,(VideoFlags).w
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$0,(a0)
	move.w	#$0,d0
	move.w	d0,(a0)
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	movea.l	#Art_1B92C2,a1
	jsr	(sub_0164EA).l
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Cmd_Tiles,a2
	jsr	(sub_020780).l
	move.l	#Font_Cmd,(FontPtr).w
	move.w	d4,(ram_B016).w
	movea.l	#Font_Scoreboard_Tiles,a2
	jsr	(sub_020780).l
	bclr	#2,(ram_C356).w
	move.w	d4,(ram_B018).w
	movea.l	#Art_1B5AEA_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B01A).w
	movea.l	#Art_1B65AC_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1DD23E:
	dc.w	loc_1DD246-inl_1DD23E
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DD246:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DD25A:
	dc.w	loc_1DD260-inl_1DD25A
	dc.b	$BF,$00,$00,$00
loc_1DD260:
	movea.l	#Art_1B7A54,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$8,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1DD284:
	dc.w	loc_1DD28A-inl_1DD284
	dc.b	$FE,$00,$00,$00
loc_1DD28A:
	movea.l	#Art_1B6BE6,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$3,d5
	jsr	(TileMap_Draw).l
	move.w	(ram_DEFA).w,d0
	asl.w	#2,d0
	movea.l	ptrs_1DD2B6(pc,d0.w),a0
	bra.w	loc_1DD2C6

ptrs_1DD2B6:
	dc.l	Art_1B9640
	dc.l	Art_1B9CC2
	dc.l	Art_1BA504
	dc.l	Art_1BAA86
loc_1DD2C6:
	jsr	(Text_Print).l
inl_1DD2CC:
	dc.w	loc_1DD2D2-inl_1DD2CC
	dc.b	$BF,$0B,$16,$00
loc_1DD2D2:
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$12,d2
	moveq	#$4,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	bra.w	loc_1DD312

	dc.w	$4EB9,$0002,$0BDE,$0006,$BF0C,$1700,$2248,$2448
	dc.w	$D1DA,$D3DA,$4240,$4241,$7410,$7603,$7A00,$4EB9
	dc.w	$0002,$06E2
loc_1DD312:
	addq.w	#1,(ram_DEFA).w
	andi.w	#$3,(ram_DEFA).w
	jsr	(Text_PrintHud).l
inl_1DD322:
	dc.w	loc_1DD32C-inl_1DD322
	dc.w	$F804,$0111,$02F9,$0100
loc_1DD32C:
	move.w	(ram_C4CA).w,d0
	btst	#7,(ram_C350).w
	beq.w	loc_1DD33E
	move.w	(ram_D344).w,d0
loc_1DD33E:
	ext.l	d0
	divu.w	#$258,d0
	move.l	d0,-(sp)
	tst.w	d0
	bne.w	loc_1DD354
	addq.w	#1,(TextX).w
	bra.w	loc_1DD358
loc_1DD354:
	bsr.w	sub_1DD6FA
loc_1DD358:
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	divu.w	#$3C,d0
	move.l	d0,-(sp)
	bsr.w	sub_1DD6FA
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	addq.w	#1,(TextX).w
	divu.w	#$A,d0
	move.l	d0,-(sp)
	bsr.w	sub_1DD6FA
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	bsr.w	sub_1DD6FA
	jsr	(Text_Print).l
inl_1DD38C:
	dc.w	loc_1DD392-inl_1DD38C
	dc.b	$BF,$08,$02,$00
loc_1DD392:
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1DD3A6
	movea.l	#RosterTable,a1
loc_1DD3A6:
	move.w	(ram_C3AE).w,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	sub.w	d0,(TextX).w
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Scoreboard,(FontPtr2).w
	jsr	(sub_020F4A).l
	jsr	(Text_Print).l
inl_1DD3DC:
	dc.w	loc_1DD3E2-inl_1DD3DC
	dc.b	$BF,$1F,$02,$00
loc_1DD3E2:
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1DD3F6
	movea.l	#RosterTable,a1
loc_1DD3F6:
	move.w	(ram_C3AC).w,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	sub.w	d0,(TextX).w
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Scoreboard,(FontPtr2).w
	jsr	(sub_020F4A).l
	btst	#7,(ram_C350).w
	bne.w	loc_1DD4F8
	jsr	(Text_PrintHud).l
inl_1DD436:
	dc.w	loc_1DD440-inl_1DD436
	dc.w	$F804,$0105,$04F9,$0300
loc_1DD440:
	movea.l	#ram_CADC,a1
	move.w	(a1),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(sub_020F4A).l
	jsr	(Text_PrintHud).l
inl_1DD45E:
	dc.w	loc_1DD468-inl_1DD45E
	dc.w	$F804,$0121,$04F9,$0300
loc_1DD468:
	movea.l	#ram_C73E,a1
	move.w	(a1),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(sub_020F4A).l
	jsr	(Text_PrintHud).l
inl_1DD486:
	dc.w	loc_1DD490-inl_1DD486
	dc.w	$F804,$0105,$12F9,$0300
loc_1DD490:
	movea.l	#ram_CAD0,a1
	move.w	(a1),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(sub_020F4A).l
	jsr	(Text_PrintHud).l
inl_1DD4AE:
	dc.w	loc_1DD4B8-inl_1DD4AE
	dc.w	$F804,$0121,$12F9,$0300
loc_1DD4B8:
	movea.l	#ram_C732,a1
	move.w	(a1),d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(sub_020F4A).l
	jsr	(Text_Print).l
inl_1DD4D6:
	dc.w	loc_1DD4DC-inl_1DD4D6
	dc.b	$8F,$1F,$08,$00
loc_1DD4DC:
	movea.w	#$C732,a2
	bsr.w	sub_1DD5EE
	jsr	(Text_Print).l
inl_1DD4EA:
	dc.w	loc_1DD4F0-inl_1DD4EA
	dc.b	$8F,$03,$08,$00
loc_1DD4F0:
	movea.w	#$CAD0,a2
	bsr.w	sub_1DD5EE
loc_1DD4F8:
	tst.w	(ram_C4C8).w
	beq.s	loc_1DD516
	cmpi.w	#$1,(ram_C4C8).w
	beq.s	loc_1DD50E
	move.w	#$18,d0
	bra.w	loc_1DD51A
loc_1DD50E:
	move.w	#$14,d0
	bra.w	loc_1DD51A
loc_1DD516:
	move.w	#$10,d0
loc_1DD51A:
	moveq	#$4,d1
	jsr	(sub_1D32F0).l
	move.w	(ram_B01A).w,d4
	addi.w	#$8002,d4
	move.w	d4,(VDP_DATA).l
	addq.w	#1,d4
	move.w	d4,(VDP_DATA).l
	addq.w	#1,d1
	jsr	(sub_1D32F0).l
	addi.w	#$C,d4
	move.w	d4,(VDP_DATA).l
	addq.w	#1,d4
	move.w	d4,(VDP_DATA).l
	movea.l	#ram_C732,a2
	btst	#2,$30(a2)
	bne.s	loc_1DD58C
	moveq	#$23,d0
	move.w	#$14,d1
	jsr	(sub_1D32F0).l
	move.w	(ram_B01A).w,d4
	addi.w	#$8005,d4
	move.w	d4,(VDP_DATA).l
	addq.w	#1,d1
	jsr	(sub_1D32F0).l
	addi.w	#$C,d4
	move.w	d4,(VDP_DATA).l
loc_1DD58C:
	adda.l	#loc_00039E,a2
	btst	#2,$30(a2)
	bne.s	loc_1DD5C6
	move.w	#$7,d0
	moveq	#$14,d1
	jsr	(sub_1D32F0).l
	move.w	(ram_B01A).w,d4
	addi.w	#$8005,d4
	move.w	d4,(VDP_DATA).l
	addq.w	#1,d1
	jsr	(sub_1D32F0).l
	addi.w	#$D,d4
	move.w	d4,(VDP_DATA).l
loc_1DD5C6:
	bsr.w	sub_1DD740
	movea.l	#Art_1B92C2,a0
	jsr	(sub_0164FA).l
	bclr	#2,(VideoFlags).w
	move.w	#$2500,sr
	move.w	#$1,-(sp)
	jsr	(sub_092172).l
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1DD4E0, $1DD4F4
sub_1DD5EE:
	lea	$A4(a2),a0
loc_1DD5F2:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	loc_1DD608
	btst	#6,$6C(a2,d0.w)
	bne.s	loc_1DD5F2
	bsr.w	sub_1DD622
	bra.s	loc_1DD5F2
loc_1DD608:
	lea	$A4(a2),a0
loc_1DD60C:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	loc_1DD67C
	btst	#6,$6C(a2,d0.w)
	beq.s	loc_1DD60C
	bsr.w	sub_1DD622
	bra.s	loc_1DD60C


; ----------------------------------------------------------------------
; called from $1DD602, $1DD61C
sub_1DD622:
	cmpi.w	#$10,(TextY).w
	bhi.w	loc_1DD67C
	move.w	$6C(a2,d0.w),d2
	andi.w	#$7FF,d2
	move.w	$28(a2),d7
	lsr.w	#1,d0
	jsr	(sub_013C76).l
	adda.w	(a1),a1
	addq.w	#8,a1
	clr.w	d0
	move.b	-$8(a1),d0
	move.w	(TextX).w,-(sp)
	movea.w	#$BFF6,a1
	jsr	(sub_02872E).l
	movea.w	#$BFF4,a1
	move.w	#$4,(a1)
	jsr	(Text_PrintFont_Worker).l
	move.w	d2,d0
	jsr	(sub_020DD4).l
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
loc_1DD67C:
	rts

	dc.b	$00,$0C
	dc.b	"1st period",0
	dc.b	$0C
	dc.b	"2nd period",0
	dc.b	$0C
	dc.b	"3rd period",0
	dc.b	$0C
	dc.b	" overtime ",0
	dc.b	$0C
	dc.b	"          ",0
	dc.b	$0C
	dc.b	"          ",0
	dc.b	$0C
	dc.b	"          "

ptrs_1DD6D2:
	dc.l	dat_043000
	dc.l	dat_043100
	dc.l	dat_043200
	dc.l	dat_043300
	dc.l	dat_043400
	dc.l	dat_043500
	dc.l	dat_043600
	dc.l	dat_043700
	dc.l	dat_043800
	dc.l	dat_043900


; ----------------------------------------------------------------------
; called from $1DD354, $1DD364, $1DD378, $1DD382
sub_1DD6FA:
	movea.l	#ptrs_1DD6D2,a1
	jsr	(List_Skip).l
	jmp	(sub_020F4A).l


; ----------------------------------------------------------------------
; copy of VBlank_Main used by the front end
; called from $00E2D4, $1E3E68, $1E4768
VBlank_Main2:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_1DD730
	bclr	#0,(VideoFlags).w
	beq.w	loc_1DD72A
	jsr	(VBlank_DMATransfers).l
loc_1DD72A:
	jsr	(Palette_FadeStep).l
loc_1DD730:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $1DD5C6
sub_1DD740:
	jsr	(Text_PrintHud).l
inl_1DD746:
	dc.w	loc_1DD750-inl_1DD746
	dc.w	$F804,$010B,$06F9,$0100
loc_1DD750:
	move.w	#$7,d0
loc_1DD754:
	jsr	(Text_PrintHud).l
inl_1DD75A:
	dc.w	loc_1DD772-inl_1DD75A
	dc.b	"                  "
	dc.b	$FD,$0B,$FA,$02
loc_1DD772:
	dbra	d0,loc_1DD754
	rts


; ----------------------------------------------------------------------
; called from $1D60D4
sub_1DD778:
	move.l	a2,-(sp)
	move.w	(ram_C3AC).w,-(sp)
	move.w	(ram_C3AE).w,-(sp)
	btst	#6,(ram_C356).w
	beq.w	loc_1DD798
	clr.w	(ram_C3AC).w
	bsr.w	sub_1DDD12
	bra.w	loc_1DD7BA
loc_1DD798:
	btst	#7,(SysFlags).w
	beq.w	loc_1DD7BA
	btst	#4,(ram_C358).w
	bne.w	loc_1DD7BA
	clr.w	(ram_C3AC).w
	move.b	(ram_DDA2).w,(ram_C3AD).w
	bsr.w	sub_1DDD12
loc_1DD7BA:
	bsr.w	sub_1DDAEE
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D04C).w
	clr.w	(ram_D052).w
loc_1DD7D2:
	bsr.w	sub_1DDCF6
	move.w	#$64,(FadeCounter).w
	move.w	#$2500,sr
loc_1DD7E0:
	jsr	(Text_PrintCmd).l
inl_1DD7E6:
	dc.w	loc_1DD7EE-inl_1DD7E6
	dc.b	$FF,$01,$FD,$02,$FC,$11
loc_1DD7EE:
	moveq	#$24,d0
	moveq	#$9,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	bsr.w	sub_1DD91C
	bsr.w	sub_1DD9C4
	bsr.w	sub_1DDA48
	move.w	#$2500,sr
loc_1DD80C:
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	move.w	#$1,d0
	btst	#1,d1
	bne.w	loc_1DDA04
	btst	#3,d1
	bne.w	loc_1DDA30
	btst	#6,(ram_C356).w
	beq.w	loc_1DD85E
	btst	#4,d1
	beq.w	loc_1DD85E
	addq.w	#1,(ram_C3AC).w
	cmpi.w	#$1A,(ram_C3AC).w
	bne.w	loc_1DD856
	clr.w	(ram_C3AC).w
loc_1DD856:
	bsr.w	sub_1DDD12
	bra.w	loc_1DD7D2
loc_1DD85E:
	move.w	#$FFFF,d0
	btst	#0,d1
	bne.w	loc_1DDA04
	btst	#2,d1
	bne.w	loc_1DDA30
	btst	#5,d1
	bne.w	loc_1DD8C6
	btst	#6,d1
	beq.w	loc_1DD8BA
	btst	#6,(ram_C356).w
	beq.w	loc_1DD8A2
	subq.w	#1,(ram_C3AC).w
	bpl.w	loc_1DD89A
	move.w	#$19,(ram_C3AC).w
loc_1DD89A:
	bsr.w	sub_1DDD12
	bra.w	loc_1DD7D2
loc_1DD8A2:
	btst	#4,(ram_C358).w
	bne.w	loc_1DD8B6
	btst	#7,(SysFlags).w
	bne.w	loc_1DD80C
loc_1DD8B6:
	bra.w	loc_1DD8D0
loc_1DD8BA:
	btst	#7,d1
	bne.w	loc_1DD8EA
	bra.w	loc_1DD80C
loc_1DD8C6:
	eori.w	#$1,(ram_D052).w
	bra.w	loc_1DD7E0
loc_1DD8D0:
	cmpa.l	#ram_C732,a2
	beq.w	loc_1DD8E2
	suba.w	#$39E,a2
	bra.w	loc_1DD7D2
loc_1DD8E2:
	adda.w	#$39E,a2
	bra.w	loc_1DD7D2
loc_1DD8EA:
	move.w	(sp)+,(ram_C3AE).w
	move.w	(sp)+,(ram_C3AC).w
	movea.l	(sp)+,a2
	btst	#7,(SysFlags).w
	beq.w	loc_1DD90A
	move.l	#sub_016614,(ram_DDD0).w
	bra.w	loc_1DD914
loc_1DD90A:
	btst	#6,(ram_C356).w
	bne.w	loc_1DD914
loc_1DD914:
	bclr	#5,(ram_C358).w
	rts


; ----------------------------------------------------------------------
; called from $1DD7FC
sub_1DD91C:
	tst.w	(ram_D052).w
	beq.w	loc_1DD93E
	jsr	(sub_01A268).l
	subq.w	#1,d0
	clr.w	d1
	movea.l	#ram_D14C,a0
loc_1DD934:
	move.b	d1,(a0)+
	addq.w	#1,d1
	dbra	d0,loc_1DD934
	rts
loc_1DD93E:
	move.w	$28(a2),d7
	movea.l	#ram_D14C,a0
	movea.l	#ram_D17E,a1
	jsr	(sub_01A2D0).l
	move.w	d0,d2
	jsr	(sub_01A268).l
	sub.w	d0,d2
	subq.w	#1,d2
	movem.l	d2/a0/a1,-(sp)
	move.w	d0,d1
loc_1DD966:
	move.w	d1,d0
	jsr	(sub_013E80).l
	tst.w	d0
	beq.w	loc_1DD978
	move.b	d0,(a1)+
	move.b	d1,(a0)+
loc_1DD978:
	addq.w	#1,d1
	dbra	d2,loc_1DD966
	movem.l	(sp)+,d2/a0/a1
loc_1DD982:
	move.w	d2,d3
	subq.w	#1,d3
	movea.l	#ram_D14C,a0
	movea.l	#ram_D17E,a1
	st	d6
loc_1DD994:
	move.b	(a1),d0
	cmp.b	$1(a1),d0
	ble.w	loc_1DD9B6
	clr.w	d6
	move.b	$1(a1),d1
	move.b	d0,$1(a1)
	move.b	d1,(a1)
	move.b	(a0),d0
	move.b	$1(a0),d1
	move.b	d1,(a0)
	move.b	d0,$1(a0)
loc_1DD9B6:
	addq.w	#1,a0
	addq.w	#1,a1
	dbra	d3,loc_1DD994
	tst.w	d6
	beq.s	loc_1DD982
	rts


; ----------------------------------------------------------------------
; called from $1DD800
sub_1DD9C4:
	tst.w	(ram_D052).w
	beq.w	loc_1DD9E2
	jsr	(sub_01A268).l
	subq.w	#1,d0
	move.w	d0,(ram_D056).w
	move.w	d0,(ram_D04E).w
	clr.w	(ram_D04C).w
	rts
loc_1DD9E2:
	jsr	(sub_01A268).l
	move.w	d0,d1
	jsr	(sub_01A2D0).l
	sub.w	d1,d0
	subq.w	#1,d0
	move.w	d0,(ram_D056).w
	move.w	#$8,(ram_D04E).w
	clr.w	(ram_D04C).w
	rts
loc_1DDA04:
	bsr.w	sub_1DDA0C
	bra.w	loc_1DD80C


; ----------------------------------------------------------------------
; called from $1DDA04
sub_1DDA0C:
	add.w	(ram_D04E).w,d0
	cmp.w	#$8,d0	; general form
	blt.w	loc_1DDA2E
	cmp.w	(ram_D056).w,d0
	bgt.w	loc_1DDA2E
	move.w	d0,(ram_D04E).w
	subq.w	#8,d0
	bsr.w	sub_1DDA48
	move.w	#$2500,sr
loc_1DDA2E:
	rts
loc_1DDA30:
	add.w	(ram_D04C).w,d0
	bmi.w	loc_1DD80C
	move.w	d0,(ram_D04C).w
	bsr.w	sub_1DDA48
	move.w	#$2500,sr
	bra.w	loc_1DD80C


; ----------------------------------------------------------------------
; called from $1DD804, $1DDA26, $1DDA3C
sub_1DDA48:
	jsr	(Text_Print).l
inl_1DDA4E:
	dc.w	loc_1DDA54-inl_1DDA4E
	dc.b	$BF,$17,$0E,$00
loc_1DDA54:
	movea.l	#dat_028A98,a1
	tst.w	(ram_D052).w
	beq.w	loc_1DDA68
	movea.l	#dat_028BFA,a1
loc_1DDA68:
	move.w	(ram_D04C).w,d0
	bra.w	loc_1DDA74
loc_1DDA70:
	adda.w	(a1),a1
	addq.w	#4,a1
loc_1DDA74:
	tst.w	(a1)
	dbmi	d0,loc_1DDA70
	bpl.w	loc_1DDA84
	subq.w	#1,(ram_D04C).w
	bra.s	loc_1DDA54
loc_1DDA84:
	jsr	(Text_PrintNarrow_Worker).l
	move.l	(a1),d4
	movea.w	#$D14C,a3
	move.w	(ram_D04E).w,d2
	subq.w	#8,d2
	bpl.w	loc_1DDA9C
	clr.w	d2
loc_1DDA9C:
	move.w	(ram_D056).w,d1
	cmp.w	#$8,d1	; general form
	bls.w	loc_1DDAAA
	moveq	#$8,d1
loc_1DDAAA:
	move.w	#$10,(TextY).w
loc_1DDAB0:
	jsr	(Text_PrintCmd).l
inl_1DDAB6:
	dc.w	loc_1DDADA-inl_1DDAB6
	dc.b	$FE,$04,$FD,$02,$FA,$01
	dc.b	"                         "
	dc.b	$FD,$02,$00
loc_1DDADA:
	clr.w	d0
	move.b	$0(a3,d2.w),d0
	jsr	(sub_019C0A).l
	addq.w	#1,d2
	dbra	d1,loc_1DDAB0
	rts


; ----------------------------------------------------------------------
; called from $1DD7BA
sub_1DDAEE:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$0,(a0)
	move.w	#$0,(a0)
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DDB80:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DDB88:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DDBB0:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DDBB8:
	bset	#2,(ram_C356).w
	jsr	(Text_PrintCmd).l
inl_1DDBC4:
	dc.w	loc_1DDBCC-inl_1DDBC4
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DDBCC:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	movea.l	(sp),a2
	move.w	d4,(ram_B02E).w
	bsr.w	sub_1DDCF6
	move.w	(ram_B02E).w,d4
	addi.w	#$A0,d4
	jsr	(Text_PrintFont).l
inl_1DDBF2:
	dc.w	loc_1DDC3C-inl_1DDBF2
	dc.b	$BF,$18,$07
	dc.b	"start-exit"
	dc.b	$BF,$16,$08
	dc.b	"c-goalie/player"
	dc.b	$BF,$15,$09
	dc.b	"[]-scroll ratings"
	dc.b	$BF,$15,$09
	dc.b	"{}-scroll players",0
loc_1DDC3C:
	btst	#6,(ram_C356).w
	bne.w	loc_1DDC5E
	btst	#4,(ram_C358).w
	bne.w	loc_1DDC7E
	btst	#7,(SysFlags).w
	bne.w	loc_1DDC98
	bra.w	loc_1DDC7E
loc_1DDC5E:
	jsr	(Text_PrintFont).l
inl_1DDC64:
	dc.w	loc_1DDC7A-inl_1DDC64
	dc.b	$BF,$14,$0A
	dc.b	"a/b-change teams",0
loc_1DDC7A:
	bra.w	loc_1DDC98
loc_1DDC7E:
	jsr	(Text_PrintFont).l
inl_1DDC84:
	dc.w	loc_1DDC98-inl_1DDC84
	dc.b	$BF,$16,$0A
	dc.b	"a-change teams",0
loc_1DDC98:
	jsr	(Text_PrintNarrow).l
inl_1DDC9E:
	dc.w	loc_1DDCAE-inl_1DDC9E
	dc.b	$F8,$04,$01,$03,$0E
	dc.b	"#  player"
loc_1DDCAE:
	jsr	(Text_Print).l
inl_1DDCB4:
	dc.w	loc_1DDCBA-inl_1DDCB4
	dc.b	$FE,$00,$00,$00
loc_1DDCBA:
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
	jsr	(Text_PrintBig).l
inl_1DDCDE:
	dc.w	loc_1DDCEE-inl_1DDCDE
	dc.b	$BF,$0A,$01
	dc.b	"TEAM ROSTER"
loc_1DDCEE:
	bsr.w	sub_1DCE06
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1DD7D2, $1DDBE0
sub_1DDCF6:
	move.w	(ram_B02E).w,d4
	jsr	(Text_Print).l
inl_1DDD00:
	dc.w	loc_1DDD06-inl_1DDD00
	dc.b	$BF,$01,$04,$00
loc_1DDD06:
	move.w	$28(a2),d7
	moveq	#$2,d5
	jmp	(sub_016EF4).l


; ----------------------------------------------------------------------
; called from $1DD790, $1DD7B6, $1DD856, $1DD89A
sub_1DDD12:
	movea.l	#ram_C732,a2
	move.w	(ram_C3AC).w,$28(a2)
	movea.l	#dat_0007FA,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1DDD32
	movea.l	#RosterTable,a0
loc_1DDD32:
	move.w	(ram_C3AC).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	move.l	a0,$1E(a2)
	jsr	(sub_1D9988).l
	move.l	a2,-(sp)
	jsr	(sub_01914E).l
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
sub_1DDD52:
	clr.w	(ram_D04E).w
	bsr.w	sub_1DDF10
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
loc_1DDD66:
	bsr.w	sub_1DDDC0
	move.w	#$2500,sr
loc_1DDD6E:
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	btst	#7,d1
	bne.w	loc_1DDDBE
	btst	#0,d1
	beq.w	loc_1DDD9C
	tst.w	(ram_D04E).w
	beq.s	loc_1DDD6E
	subq.w	#6,(ram_D04E).w
	bra.s	loc_1DDD66
loc_1DDD9C:
	btst	#1,d1
	beq.s	loc_1DDD6E
	cmpi.w	#$18,(ram_C4D6).w
	blt.s	loc_1DDD6E
	move.w	(ram_D04E).w,d3
	addi.w	#$18,d3
	cmp.w	(ram_C4D6).w,d3
	bge.s	loc_1DDD6E
	addq.w	#6,(ram_D04E).w
	bra.s	loc_1DDD66
loc_1DDDBE:
	rts


; ----------------------------------------------------------------------
; called from $1DDD66
sub_1DDDC0:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1DDDCA:
	dc.w	loc_1DDDD0-inl_1DDDCA
	dc.b	$8F,$02,$0A,$00
loc_1DDDD0:
	move.w	#$24,d0
	move.w	#$F,d1
	move.l	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	(ram_D04E).w,d3
	jsr	(Text_PrintCmd).l
inl_1DDDEE:
	dc.w	loc_1DDDF6-inl_1DDDEE
	dc.b	$F8,$07,$01,$04,$0A,$00
loc_1DDDF6:
	cmp.w	(ram_C4D6).w,d3
	bge.w	loc_1DDEC2
	jsr	(Text_PrintCmd).l
inl_1DDE04:
	dc.w	loc_1DDE0A-inl_1DDE04
	dc.b	$FE,$07,$FD,$03
loc_1DDE0A:
	movea.w	#$C4D8,a0
	move.w	$0(a0,d3.w),d0
	jsr	(sub_020DA4).l
	movea.w	#$C732,a2
	btst	#7,$2(a0,d3.w)
	beq.w	loc_1DDE2A
	adda.w	#$39E,a2
loc_1DDE2A:
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	move.w	#$E,(TextX).w
	jsr	(Text_PrintCmd_Worker).l
	move.w	#$23,(TextX).w
	lea	dat_1DDEF8(pc),a1
	move.b	$2(a0,d3.w),d0
	andi.w	#$7F,d0
	jsr	(sub_022A6E).l
	move.w	#$12,(TextX).w
	move.b	$3(a0,d3.w),d0
	move.w	(TextY).w,-(sp)
	bsr.w	sub_1DDEAA
	jsr	(Text_PrintCmd).l
inl_1DDE70:
	dc.w	loc_1DDE76-inl_1DDE70
	dc.b	$FE,$04,$FD,$13
loc_1DDE76:
	move.b	$4(a0,d3.w),d0
	bsr.w	sub_1DDEAA
	move.w	#$13,(TextX).w
	move.b	$5(a0,d3.w),d0
	move.w	d0,-(sp)
	bsr.w	sub_1DDEAA
	move.w	(sp)+,d0
	tst.w	d0
	move.w	(sp)+,(TextY).w
	addq.w	#4,(TextY).w
	addq.w	#6,d3
	cmpi.w	#$17,(TextY).w
	bgt.w	loc_1DDEC2
	bra.w	loc_1DDDF6


; ----------------------------------------------------------------------
; called from $1DDE66, $1DDE7A, $1DDE8A
sub_1DDEAA:
	ext.w	d0
	bmi.w	loc_1DDEBC
	jsr	(sub_0285AE).l
	jsr	(Text_PrintFont_Worker).l
loc_1DDEBC:
	addq.w	#1,(TextY).w
	rts
loc_1DDEC2:
	tst.w	(ram_D04E).w
	beq.w	loc_1DDED6
	jsr	(Text_PrintFont).l
inl_1DDED0:
	dc.w	loc_1DDED6-inl_1DDED0
	dc.b	$8F,$02,$0B,$7B
loc_1DDED6:
	move.w	(ram_D04E).w,d3
	addi.w	#$18,d3
	cmp.w	(ram_C4D6).w,d3
	bge.w	loc_1DDEF2
	jsr	(Text_PrintFont).l
inl_1DDEEC:
	dc.w	loc_1DDEF2-inl_1DDEEC
	dc.b	$8F,$02,$18,$7D
loc_1DDEF2:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1DDEF8:
	dc.w	$0006,$5348,$3200,$0004,$5348,$0004,$2000,$0004
	dc.w	$5050,$0006,$5050,$3200


; ----------------------------------------------------------------------
; called from $1DDD56
sub_1DDF10:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DDF90:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DDF98:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DDFC0:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DDFC8:
	bset	#2,(ram_C356).w
	jsr	(Text_PrintCmd).l
inl_1DDFD4:
	dc.w	loc_1DDFDC-inl_1DDFD4
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DDFDC:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DDFF0:
	dc.w	loc_1DDFF6-inl_1DDFF0
	dc.b	$FE,$00,$00,$00
loc_1DDFF6:
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
	move.w	(ram_C3AE).w,d7
	jsr	(Text_Print).l
inl_1DE01E:
	dc.w	loc_1DE024-inl_1DE01E
	dc.b	$BF,$01,$05,$00
loc_1DE024:
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	(ram_C3AC).w,d7
	jsr	(Text_Print).l
inl_1DE038:
	dc.w	loc_1DE03E-inl_1DE038
	dc.b	$BF,$17,$05,$00
loc_1DE03E:
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1DE058:
	dc.w	loc_1DE06C-inl_1DE058
	dc.b	$8F,$0C,$1A
	dc.b	"{}-scroll list",0
loc_1DE06C:
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_PrintNarrow).l
inl_1DE076:
	dc.w	loc_1DE0A0-inl_1DE076
	dc.b	$F8,$04,$01,$03,$08
	dc.b	"per time  team  goals/assist   p/s",0
loc_1DE0A0:
	jsr	(Text_PrintBig).l
inl_1DE0A6:
	dc.w	loc_1DE0BA-inl_1DE0A6
	dc.b	$BF,$05,$01
	dc.b	"SCORING SUMMARY"
loc_1DE0BA:
	jsr	(sub_1D5E5E).l
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
sub_1DE0C4:
	clr.w	(ram_D04E).w
	bsr.w	sub_1DE132
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
loc_1DE0D8:
	bsr.w	sub_1DE2E6
	move.w	#$2500,sr
loc_1DE0E0:
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	btst	#7,d1
	bne.w	loc_1DE130
	btst	#0,d1
	beq.w	loc_1DE10E
	tst.w	(ram_D04E).w
	beq.s	loc_1DE0E0
	subq.w	#4,(ram_D04E).w
	bra.s	loc_1DE0D8
loc_1DE10E:
	btst	#1,d1
	beq.s	loc_1DE0E0
	cmpi.w	#$14,(ram_C640).w
	blt.s	loc_1DE0E0
	move.w	(ram_D04E).w,d3
	addi.w	#$14,d3
	cmp.w	(ram_C640).w,d3
	bge.s	loc_1DE0E0
	addq.w	#4,(ram_D04E).w
	bra.s	loc_1DE0D8
loc_1DE130:
	rts


; ----------------------------------------------------------------------
; called from $1DE0C8
sub_1DE132:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DE1B2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DE1BA:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1DE1D2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DE1DA:
	bset	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1DE1F6:
	dc.w	loc_1DE1FE-inl_1DE1F6
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DE1FE:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DE212:
	dc.w	loc_1DE218-inl_1DE212
	dc.b	$FE,$00,$00,$00
loc_1DE218:
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
	move.w	(ram_C3AE).w,d7
	jsr	(Text_Print).l
inl_1DE240:
	dc.w	loc_1DE246-inl_1DE240
	dc.b	$BF,$01,$05,$00
loc_1DE246:
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	(ram_C3AC).w,d7
	jsr	(Text_Print).l
inl_1DE25A:
	dc.w	loc_1DE260-inl_1DE25A
	dc.b	$BF,$17,$05,$00
loc_1DE260:
	jsr	(sub_016EB8).l
	addi.w	#$20,d4
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	jsr	(Text_PrintFont).l
inl_1DE27A:
	dc.w	loc_1DE28E-inl_1DE27A
	dc.b	$8F,$0C,$1A
	dc.b	"{}-scroll list",0
loc_1DE28E:
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_PrintNarrow).l
inl_1DE298:
	dc.w	loc_1DE2C2-inl_1DE298
	dc.b	$F8,$04,$01,$03,$08
	dc.b	"per time  team player/penalty  mins"
loc_1DE2C2:
	jsr	(Text_PrintBig).l
inl_1DE2C8:
	dc.w	loc_1DE2DC-inl_1DE2C8
	dc.b	$BF,$06,$01
	dc.b	"PENALTY SUMMARY"
loc_1DE2DC:
	jsr	(sub_1D5E5E).l
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1DE0D8
sub_1DE2E6:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1DE2F0:
	dc.w	loc_1DE2F6-inl_1DE2F0
	dc.b	$8F,$02,$0B,$00
loc_1DE2F6:
	move.w	#$24,d0
	move.w	#$E,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	move.w	(ram_D04E).w,d3
	jsr	(Text_PrintCmd).l
inl_1DE314:
	dc.w	loc_1DE31C-inl_1DE314
	dc.b	$F8,$07,$01,$03,$0B,$00
loc_1DE31C:
	cmp.w	(ram_C640).w,d3
	bge.w	loc_1DE3DA
	jsr	(Text_PrintCmd).l
inl_1DE32A:
	dc.w	loc_1DE330-inl_1DE32A
	dc.b	$FE,$07,$FD,$03
loc_1DE330:
	movea.w	#$C642,a0
	move.w	$0(a0,d3.w),d0
	jsr	(sub_020DA4).l
	movea.w	#$C732,a2
	btst	#7,$2(a0,d3.w)
	beq.w	loc_1DE350
	adda.w	#$39E,a2
loc_1DE350:
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	move.w	#$F,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	move.b	$2(a0,d3.w),d0
	andi.w	#$7F,d0
	movea.l	#dat_012158,a3
	adda.w	$0(a3,d0.w),a3
	clr.w	d0
	move.b	$1(a3),d0
	jsr	(sub_020E38).l
	move.w	#$23,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	move.w	#$13,(TextX).w
	clr.w	d0
	move.b	$3(a0,d3.w),d0
	jsr	(sub_028562).l
	jsr	(Text_PrintFont_Worker).l
	addq.w	#1,(TextY).w
	move.w	#$13,(TextX).w
	jsr	(Text_PrintCmd).l
inl_1DE3B8:
	dc.w	loc_1DE3BC-inl_1DE3B8
	dc.b	$FE,$04
loc_1DE3BC:
	lea	$2(a3),a1
	jsr	(Text_PrintFont_Worker).l
	addq.w	#2,(TextY).w
	addq.w	#4,d3
	cmpi.w	#$18,(TextY).w
	bgt.w	loc_1DE3DA
	bra.w	loc_1DE31C
loc_1DE3DA:
	tst.w	(ram_D04E).w
	beq.w	loc_1DE3EE
	jsr	(Text_PrintFont).l
inl_1DE3E8:
	dc.w	loc_1DE3EE-inl_1DE3E8
	dc.b	$8F,$02,$0B,$7B
loc_1DE3EE:
	move.w	(ram_D04E).w,d3
	addi.w	#$14,d3
	cmp.w	(ram_C640).w,d3
	bge.w	loc_1DE40A
	jsr	(Text_PrintFont).l
inl_1DE404:
	dc.w	loc_1DE40A-inl_1DE404
	dc.b	$8F,$02,$18,$7D
loc_1DE40A:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
sub_1DE410:
	clr.w	(ram_D476).w
	bsr.w	sub_1DE5A0
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
loc_1DE424:
	bsr.w	sub_1DE462
	move.w	#$2500,sr
loc_1DE42C:
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	btst	#7,d1
	bne.w	loc_1DE460
	btst	#3,d1
	bne.w	loc_1DE458
	btst	#2,d1
	bne.w	loc_1DE458
	bra.s	loc_1DE42C
loc_1DE458:
	eori.w	#$1,(ram_D476).w
	bra.s	loc_1DE424
loc_1DE460:
	rts


; ----------------------------------------------------------------------
; called from $1DE424
sub_1DE462:
	jsr	(Text_PrintNarrow).l
inl_1DE468:
	dc.w	loc_1DE470-inl_1DE468
	dc.b	$F8,$04,$01,$12,$0E,$00
loc_1DE470:
	bset	#2,(ram_C356).w
	movea.l	#dat_1DE4BA,a1
	btst	#0,(ram_D477).w
	beq.w	loc_1DE48C
	movea.l	#dat_1DE4C2,a1
loc_1DE48C:
	jsr	(Text_PrintNarrow_Worker).l
	bclr	#2,(ram_C356).w
	movea.l	#ram_CAD0,a2
	move.w	#$7,(TextX).w
	bsr.w	sub_1DE4CA
	movea.l	#ram_C732,a2
	move.w	#$1E,(TextX).w
	bsr.w	sub_1DE4CA
	rts
dat_1DE4BA:
	dc.b	$00,$08
	dc.b	"goals",0
dat_1DE4C2:
	dc.b	$00,$08
	dc.b	"shots",0


; ----------------------------------------------------------------------
; called from $1DE4A4, $1DE4B4
sub_1DE4CA:
	lea	$37C(a2),a0
	tst.w	(ram_D476).w
	beq.w	loc_1DE4DA
	lea	$384(a2),a0
loc_1DE4DA:
	clr.w	(ram_D486).w
	move.w	#$10,(TextY).w
	bsr.w	sub_1DE564
	cmpi.w	#$1,(ram_C4C8).w
	blt.w	loc_1DE52E
	move.w	#$12,(TextY).w
	bsr.w	sub_1DE564
	cmpi.w	#$2,(ram_C4C8).w
	blt.w	loc_1DE52E
	move.w	#$14,(TextY).w
	bsr.w	sub_1DE564
	cmpi.w	#$3,(ram_C4C8).w
	blt.w	loc_1DE52E
	btst	#1,(ram_C34C).w
	beq.w	loc_1DE52E
	move.w	#$16,(TextY).w
	bsr.w	sub_1DE564
loc_1DE52E:
	move.w	#$18,(TextY).w
	jsr	(Text_PrintNarrow).l
inl_1DE53A:
	dc.w	loc_1DE540-inl_1DE53A
	dc.b	$20,$20,$20,$00
loc_1DE540:
	subq.w	#3,(TextX).w
	move.w	(ram_D486).w,d0
	move.w	#$2,d1
	cmp.w	#$64,d0	; general form
	blt.w	loc_1DE558
	move.w	#$3,d1
loc_1DE558:
	jsr	(Num_ToDecimal).l
	jmp	(Text_PrintNarrow_Worker).l


; ----------------------------------------------------------------------
; called from $1DE4E4, $1DE4F8, $1DE50C, $1DE52A
sub_1DE564:
	move.w	(TextX).w,-(sp)
	move.w	(a0)+,d0
	add.w	d0,(ram_D486).w
	jsr	(Text_PrintNarrow).l
inl_1DE574:
	dc.w	loc_1DE57A-inl_1DE574
	dc.b	$20,$20,$20,$00
loc_1DE57A:
	subq.w	#3,(TextX).w
	move.w	#$2,d1
	cmp.w	#$64,d0	; general form
	blt.w	loc_1DE58E
	move.w	#$3,d1
loc_1DE58E:
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintNarrow_Worker).l
	move.w	(sp)+,(TextX).w
	rts


; ----------------------------------------------------------------------
; called from $1DE414
sub_1DE5A0:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
inl_1DE620:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DE628:
	bclr	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	jsr	(Text_PrintCmd).l
inl_1DE63C:
	dc.w	loc_1DE644-inl_1DE63C
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DE644:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DE658:
	dc.w	loc_1DE65E-inl_1DE658
	dc.b	$FE,$00,$00,$00
loc_1DE65E:
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
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintBig).l
inl_1DE692:
	dc.w	loc_1DE6A4-inl_1DE692
	dc.b	$BF,$09,$01
	dc.b	"PERIOD STATS",0
loc_1DE6A4:
	move.w	(ram_C3AE).w,d7
	move.w	#$2,d5
	jsr	(Text_Print).l
inl_1DE6B2:
	dc.w	loc_1DE6B8-inl_1DE6B2
	dc.b	$BF,$02,$04,$00
loc_1DE6B8:
	jsr	(sub_016EF4).l
	move.w	(ram_C3AC).w,d7
	clr.w	d5
	jsr	(Text_Print).l
inl_1DE6CA:
	dc.w	loc_1DE6D0-inl_1DE6CA
	dc.b	$8F,$16,$04,$00
loc_1DE6D0:
	jsr	(sub_016EF4).l
	jsr	(Text_PrintNarrow).l
inl_1DE6DC:
	dc.w	loc_1DE720-inl_1DE6DC
	dc.b	$F8,$04,$01,$0F,$10
	dc.b	"1st period"
	dc.b	$FD,$0F,$FC,$12
	dc.b	"2nd period"
	dc.b	$FD,$0F,$FC,$14
	dc.b	"3rd period"
	dc.b	$FD,$10,$FC,$16
	dc.b	"overtime"
	dc.b	$FD,$11,$FC,$18
	dc.b	"totals",0
loc_1DE720:
	movea.l	(sp)+,a2
	rts

	dc.w	$4278,$D04E,$31FC,$0010,$D04C,$4A78,$D27E,$6600
	dc.w	$0008,$31FC,$000C,$D04C,$08F8,$0005,$C358,$6100
	dc.w	$03E6,$4EB9,$0002,$0F14,$0010,$BF0C,$0147,$414D
	dc.w	$4520,$5354,$4154,$5300,$08B8,$0002,$C356,$31FC
	dc.w	$0018,$BD3E,$08B8,$0002,$BFB4,$6100,$004E,$46FC
	dc.w	$2500,$4EB9,$0001,$9BF0,$4EB9,$0001,$A7B4,$4EB9
	dc.w	$0002,$0370,$0801,$0007,$6600,$002E,$0801,$0000
	dc.w	$6700,$000E,$4A78,$D04E,$67D8,$5378,$D04E,$60CA
	dc.w	$0801,$0001,$67CC,$3638,$D04E,$5E43,$B678,$D04C
	dc.w	$6CC0,$5278,$D04E,$60B2,$4E75,$40E7,$4EB9,$0002
	dc.w	$0BDE,$0006,$8F02,$0900,$303C,$0024,$323C,$000E
	dc.w	$343C,$87FF,$4EB9,$0002,$09C6,$4A78,$D04E,$6700
	dc.w	$0010,$4EB9,$0002,$0F38,$0008,$F804,$0102,$0928
	dc.w	$3638,$D04E,$5E43,$B678,$D04C,$6C00,$0010,$4EB9
	dc.w	$0002,$0F38,$0008,$F804,$0102,$1529,$4EB9,$0002
	dc.w	$0F38,$0008,$F804,$0100,$0900


; ----------------------------------------------------------------------
sub_1DE81E:
	move.w	#$6,d6
	lea	dat_1DE966(pc),a1
	tst.w	(ram_D27E).w
	bne.w	loc_1DE832
	lea	dat_1DEA66(pc),a1
loc_1DE832:
	move.w	(ram_D04E).w,d3
	bra.w	loc_1DE83E


; ----------------------------------------------------------------------
; called from $1DE83E
sub_1DE83A:
	adda.w	(a1),a1
	addq.w	#4,a1
loc_1DE83E:
	dbra	d3,sub_1DE83A
loc_1DE842:
	move.w	(a1),d0
	lsr.w	#1,d0
	neg.w	d0
	addi.w	#$15,d0
	move.w	d0,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	movea.l	a1,a0
	move.w	#$21,(TextX).w
	movea.w	#$C732,a2
	bsr.w	sub_1DE88A
	move.w	#$9,(TextX).w
	lea	$39E(a2),a2
	bsr.w	sub_1DE88A
	lea	$4(a0),a1
	addq.w	#2,(TextY).w
loc_1DE87C:
	dbra	d6,loc_1DE842
	move.w	(sp)+,sr
	rts


; ----------------------------------------------------------------------
sub_1DE884:
	adda.w	(a1),a1
	addq.w	#4,a1
	bra.s	loc_1DE87C


; ----------------------------------------------------------------------
; called from $1DE862, $1DE870
sub_1DE88A:
	movea.w	#$BFF4,a3
	move.w	#$2,(a3)
	cmpi.w	#$FFFE,(a0)
	bne.w	loc_1DE8B8
	move.w	#$14,d0
	move.w	$0(a2,d0.w),d0
	mulu.w	#$64,d0
	move.w	#$12,d1
	move.w	$0(a2,d1.w),d1
	beq.w	loc_1DE8DA
	divu.w	d1,d0
	bra.w	loc_1DE8DA
loc_1DE8B8:
	cmpi.w	#$FFFF,(a0)
	bne.w	loc_1DE8F4
	move.w	#$C,d0
	move.w	$0(a2,d0.w),d0
	mulu.w	#$64,d0
	move.w	#$0,d1
	move.w	$0(a2,d1.w),d1
	beq.w	loc_1DE8DA
	divu.w	d1,d0
loc_1DE8DA:
	jsr	(sub_020E38).l
	jsr	(Text_AppendInline_Worker).l
	jsr	(Text_AppendInline).l
inl_1DE8EC:
	dc.w	loc_1DE8F0-inl_1DE8EC
	dc.b	$25,$00
loc_1DE8F0:
	bra.w	loc_1DE94A
loc_1DE8F4:
	move.w	(a0),d0
	move.w	$0(a2,d0.w),d0
	cmpi.w	#$38C,(a0)
	bne.w	loc_1DE90A
	bsr.w	sub_1DE960
	bra.w	loc_1DE922
loc_1DE90A:
	cmpi.w	#$A,(a0)
	beq.w	loc_1DE916
	bsr.w	sub_1DE95A
loc_1DE916:
	cmpi.w	#$A,(a0)
	bne.w	loc_1DE922
	bsr.w	sub_1DE960
loc_1DE922:
	jsr	(Text_AppendInline_Worker).l
	move.w	$2(a0),d0
	bmi.w	loc_1DE94A
	jsr	(Text_AppendInline).l
inl_1DE936:
	dc.w	loc_1DE93A-inl_1DE936
	dc.b	$2F,$00
loc_1DE93A:
	move.w	$0(a2,d0.w),d0
	jsr	(sub_020E38).l
	jsr	(Text_AppendInline_Worker).l
loc_1DE94A:
	movea.w	a3,a1
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	jmp	(Text_PrintNarrow_Worker).l


; ----------------------------------------------------------------------
; called from $1DE912
sub_1DE95A:
	jmp	(sub_020E38).l


; ----------------------------------------------------------------------
; called from $1DE902, $1DE91E
sub_1DE960:
	jmp	(sub_020DD4).l
dat_1DE966:
	dc.w	$0008,$5363,$6F72,$6500,$000C,$FFFF,$0008,$5368
	dc.w	$6F74,$7300,$0000,$FFFF,$000E,$5368,$6F6F,$7469
	dc.w	$6E67,$2050,$6374,$FFFF,$FFFF,$000C,$506F,$7765
	dc.w	$7220,$506C,$6179,$0002,$0004,$000C,$5050,$204D
	dc.w	$696E,$7574,$6573,$038C,$FFFF,$000A,$5050,$2053
	dc.w	$686F,$7473,$038E,$FFFF,$000A,$5348,$2047,$6F61
	dc.w	$6C73,$0390,$FFFF,$000C,$4272,$6561,$6B61,$7761
	dc.w	$7973,$0394,$0392,$000C,$4F6E,$652D,$5469,$6D65
	dc.w	$7273,$0398,$0396,$0010,$5065,$6E61,$6C74,$7920
	dc.w	$5368,$6F74,$7300,$039C,$039A,$000E,$4661,$6365
	dc.w	$6F66,$6673,$2057,$6F6E,$000E,$FFFF,$000E,$426F
	dc.w	$6479,$2043,$6865,$636B,$7300,$0010,$FFFF,$000C
	dc.w	$5065,$6E61,$6C74,$6965,$7300,$0006,$0008,$000E
	dc.w	$4174,$7461,$636B,$205A,$6F6E,$6500,$000A,$FFFF
	dc.w	$000A,$5061,$7373,$696E,$6700,$0014,$0012,$000E
	dc.w	$7061,$7373,$696E,$6720,$7063,$7400,$FFFE,$FFFE
dat_1DEA66:
	incbin	"data/bin/data_1DEA66.bin"	; 1748 bytes


; ----------------------------------------------------------------------
sub_1DF13A:
	movea.l	#ram_D458,a1
	cmpa.l	#ram_C732,a2
	beq.w	loc_1DF150
	movea.l	#ram_D466,a1
loc_1DF150:
	move.w	(ram_D058).w,d0
	asl.w	#1,d0
	move.w	$0(a1,d0.w),d0
	jsr	(sub_02861C).l
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	bclr	#2,(ram_C356).w
	rts

	dc.w	$48E7,$FFFE,$4EB9,$0002,$0A7E,$0008,$FD06,$FC12
	dc.w	$FE04,$323C,$0000,$207C,$FFFF,$D458,$B5FC,$FFFF
	dc.w	$C732,$6700,$0008,$207C,$FFFF,$D466,$3001,$E340
	dc.w	$3030,$0000,$4EB9,$0002,$8674,$3F38,$B042,$B278
	dc.w	$D058,$6600,$000C,$4EB9,$0002,$0A7E,$0004,$FE07
	dc.w	$B27C,$0005,$6600,$000E,$31FC,$0018,$B042,$31FC
	dc.w	$0012,$B044,$4EB9,$0002,$0A90,$4EB9,$0002,$0A7E
	dc.w	$0004,$FE04,$31DF,$B042,$5278,$B044,$5241,$B27C
	dc.w	$0006,$6DA8,$4CDF,$7FFF,$4E75,$2F0A,$08F8,$0005
	dc.w	$C358,$21FC,$0001,$728E,$D260,$08B8,$0000,$BFB4
	dc.w	$08F8,$0002,$BFB4,$08B8,$0001,$BFB4,$31FC,$0000
	dc.w	$B000,$31FC,$B800,$B002,$31FC,$B800,$B00C,$31FC
	dc.w	$0005,$B00E,$31FC,$C000,$B008,$31FC,$0006,$B00A
	dc.w	$31FC,$E000,$B004,$31FC,$0006,$B006,$303C,$0000
	dc.w	$4EB9,$0002,$05CE,$08B8,$0005,$BFB4,$4EB9,$0002
	dc.w	$0314,$383C,$0001,$31C4,$B01C,$31C4,$B01E,$247C
	dc.w	$001A,$9842,$4EB9,$0002,$0774,$0123,$4567,$89DE
	dc.w	$EEEF,$21FC,$001A,$983A,$BF8C,$31C4,$B018,$31C4
	dc.w	$B014,$247C,$001A,$A150,$4EB9,$0002,$0774,$0123
	dc.w	$4567,$89DE,$EEEF,$08F8,$0002,$C356,$21FC,$001A
	dc.w	$A148,$B010,$31C4,$B020,$247C,$001A,$AD9E,$4EB9
	dc.w	$0002,$0780,$4EB9,$0002,$0A7E,$0008,$FF01,$FD00
	dc.w	$FC00,$7028,$721C,$343C,$87FF,$4EB9,$0002,$09C6
	dc.w	$31C4,$B02E,$4EB9,$0002,$0BDE,$0006,$BF01,$0400
	dc.w	$2457,$3E2A,$0028,$7A02,$4EB9,$0001,$6EF4,$6100
	dc.w	$0054,$4EB9,$0002,$0BDE,$0006,$FE00,$0000,$207C
	dc.w	$001A,$41D4,$2248,$2448,$D1DA,$D3DA,$4240,$4241
	dc.w	$7428,$761C,$7A09,$4EB9,$0002,$06E2,$08F8,$0002
	dc.w	$C356,$4EB9,$0002,$0F14,$0014,$BF07,$0153,$484F
	dc.w	$4F54,$4F55


; ----------------------------------------------------------------------
sub_1DF34A:
	addq.b	#2,-(a0)
	subq.w	#1,d5
	addq.w	#2,(a5)
	addq.b	#8,d0
	bsr.w	sub_1DCE06
	movea.l	(sp)+,a2
	rts

	dc.w	$3F38,$B01C,$31F8,$B01E,$B01C,$4EB9,$0002,$0CC2
	dc.w	$002C,$8F07,$197B,$7D5B,$5D2D,$6869,$6768,$6C69
	dc.w	$6768,$7420,$706C,$6179,$6572,$8F0A,$1A63,$2D73
	dc.w	$656C,$6563,$7420,$706C,$6179,$6572,$31DF,$B01C
	dc.w	$4E75
dat_1DF39C:
	dc.b	$99,$A8,$20,$00,$A8,$F8,$10,$08,$9A,$88,$20,$00,$9D,$28,$20,$00
	dc.b	$9E,$08,$20,$00,$9E,$E8,$20,$00,$A1,$88,$20,$00,$A2,$68,$20,$00
	dc.b	$A3,$48,$20,$00,$A8,$88,$10,$04,$A4,$28,$20,$00,$A5,$08,$20,$00
	dc.b	$A5,$E8,$20,$00,$A6,$C8,$20,$00,$A7,$A8,$20,$00,$9B,$68,$20,$00
	dc.b	$9C,$48,$20,$00,$9F,$C8,$20,$00,$A0,$A8,$20,$00

ptrtbl_1DF3E8:
	dc.l	sub_1DF3F4
	dc.l	sub_1DF412
	dc.l	sub_1DF410


; ----------------------------------------------------------------------
; called from $1DF7C4
sub_1DF3F4:
	movem.l	d0/a0/a1,-(sp)
	adda.l	#$20,a1
	lea	-$4(a1),a0
	move.w	#$6,d0
loc_1DF406:
	move.l	-(a0),-(a1)
	dbra	d0,loc_1DF406
	movem.l	(sp)+,d0/a0/a1

; ----------------------------------------------------------------------
; called from $1DF7C4
sub_1DF410:
	rts


; ----------------------------------------------------------------------
; called from $1DF7C4
sub_1DF412:
	movem.l	d0/d1/a0/a1,-(sp)
	adda.l	#$20,a1
	lea	-$12(a1),a0
	move.w	#$6,d0
	clr.l	d1
loc_1DF426:
	move.w	-(a0),d1
	move.l	d1,-(a1)
	dbra	d0,loc_1DF426
	movem.l	(sp)+,d0/d1/a0/a1
	rts
dat_1DF434:
	dc.b	$00,$1D,$F4,$6C,$00,$1D,$F4,$7F,$00,$1D,$F4,$9D,$00,$1D,$F4,$B0
	dc.b	$00,$1D,$F4,$C3,$00,$1D,$F4,$D8,$00,$1D,$F4,$F6,$00,$1D,$F5,$16
	dc.b	$00,$1D,$F5,$2F,$00,$1D,$F5,$43,$00,$1D,$F5,$5E,$00,$1D,$F5,$77
	dc.b	$00,$1D,$F5,$91,$00,$1D,$F5,$A3,$01
	dc.b	"MOST GOALS",0
	dc.b	$00
	dc.b	"goals",0
	dc.b	$03
	dc.b	"FASTEST GOAL "
	dc.b	$01
	dc.b	"(from faceoff)",0
	dc.b	$01
	dc.b	"MOST SHOTS",0
	dc.b	$02
	dc.b	"shots",0
	dc.b	$02
	dc.b	"BEST SHOOTING %",0
	dc.b	$0F,$10,$02
	dc.b	"BEST POWER PLAY %",0
	dc.b	$11,$12,$01
	dc.b	"MOST POWER PLAY SHOTS",0
	dc.b	$04
	dc.b	"shots",0
	dc.b	$01
	dc.b	"MOST SHORT HANDED GOALS",0
	dc.b	$05
	dc.b	"goals",0
	dc.b	$01
	dc.b	"MOST BREAKAWAYS",0
	dc.b	$06
	dc.b	"breaks",0
	dc.b	$02
	dc.b	"BEST ONE TIMER %",0
	dc.b	$07,$08,$01
	dc.b	"MOST PENALTY SHOTS",0
	dc.b	$09
	dc.b	"shots",0
	dc.b	$01
	dc.b	"MOST FACEOFFS WON",0
	dc.b	$0A
	dc.b	"wins",0
	dc.b	$01
	dc.b	"MOST BODY CHECKS",0
	dc.b	$0B
	dc.b	"checks",0
	dc.b	$02
	dc.b	"BEST PASSING %",0
	dc.b	$0E,$0D,$00,$00,$FF

ptrtbl_1DF5A6:
	dc.l	sub_1DF5B6

ptrtbl_1DF5AA:
	dc.l	sub_1DF5B8
	dc.l	sub_1DF76C
	dc.l	sub_1DF664


; ----------------------------------------------------------------------
; called from $1DFAC2
sub_1DF5B6:
	rts


; ----------------------------------------------------------------------
; called from $1DF5AA
sub_1DF5B8:
	move.b	(a0)+,d0
	movea.l	a0,a2
	ext.w	d0
	lsl.w	#2,d0
	lea	(dat_1DF39C).l,a1
	lea	$0(a1,d0.w),a1
	move.w	(a1),d1
	move.b	$2(a1),d0
	move.b	$3(a1),d2
	ext.w	d2
	mulu.w	#$7,d0
	suba.l	#$24,sp
	movea.l	sp,a1
	move.w	d2,-(sp)
	lea	($200000).l,a0
	jsr	(sub_1DFF52).l
	move.w	(sp)+,d0
	lea	(ptrtbl_1DF3E8).l,a0
	movea.l	$0(a0,d0.w),a0
	movea.l	sp,a1
	jsr	(a0)
	jsr	(sub_1E04EC).l
	adda.l	#$24,sp
	tst.w	d0
	ble.w	loc_1DF860
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E05B6).l
	move.w	#$B,d0
	jsr	(sub_1E0458).l
	lea	(ram_DE1C).w,a0
	move.l	d1,d0
	jsr	(sub_1E0286).l
	move.w	#$C,d0
	jsr	(sub_1E040C).l
	movea.l	a0,a1
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E04A8).l
	lea	(dat_1E0200).l,a1
	jsr	(sub_1E04A8).l
	movea.l	a2,a1
	jsr	(sub_1E04A8).l
	jsr	(sub_1E0196).l
	rts


; ----------------------------------------------------------------------
; called from $1DF5B2
sub_1DF664:
	lea	($200000).l,a0
	move.l	#dat_00A8F8,d1
	move.w	#$10,d0
	jsr	(sub_1DFEF0).l
	move.w	d1,d0
	andi.w	#$1FFF,d1
	rol.w	#3,d0
	andi.w	#$7,d0
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E05B6).l
	move.w	#$B,d0
	jsr	(sub_1E0458).l
	clr.w	d3
	divu.w	#$3C,d1
	move.w	d1,d2
	clr.w	d1
	swap	d1
	cmp.w	#$3B,d2	; general form
	blt.w	loc_1DF6B8
	divu.w	#$3C,d2
	move.w	d2,d3
	clr.w	d2
	swap	d2
loc_1DF6B8:
	clr.b	(ram_DE1C).w
	clr.b	(ram_DE2C).w
	clr.b	(ram_DE34).w
	move.w	d3,d4
	or.w	d2,d4
	or.w	d1,d4
	beq.w	loc_1DF74A
	move.w	d1,d0
	lea	(ram_DE34).w,a0
	jsr	(sub_1E0222).l
	move.w	d2,d0
	or.w	d3,d0
	beq.w	loc_1DF710
	tst.w	d3
	beq.w	loc_1DF704
	move.w	d2,d0
	lea	(ram_DE2C).w,a0
	jsr	(sub_1E0222).l
	lea	(ram_DE1C).w,a0
	move.w	d3,d0
	jsr	(sub_1E0286).l
	bra.w	loc_1DF710
loc_1DF704:
	move.w	d2,d0
	lea	(ram_DE2C).w,a0
	jsr	(sub_1E0286).l
loc_1DF710:
	lea	(ram_DE1C).w,a0
	tst.b	(a0)
	beq.w	loc_1DF728
	move.w	#$3A00,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
loc_1DF728:
	lea	(ram_DE2C).w,a1
	jsr	(sub_1E04A8).l
	move.w	#$3A00,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
	lea	(ram_DE34).w,a1
	jsr	(sub_1E04A8).l
loc_1DF74A:
	lea	(ram_DE1C).w,a0
	move.w	#$C,d0
	jsr	(sub_1E040C).l
	movea.l	a0,a1
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E04A8).l
	jsr	(sub_1E0196).l
	rts


; ----------------------------------------------------------------------
; called from $1DF5AE
sub_1DF76C:
	move.b	(a0)+,d0
	move.b	(a0)+,d1
	ext.w	d0
	lsl.w	#2,d0
	ext.w	d1
	lsl.w	#2,d1
	lea	(dat_1DF39C).l,a0
	lea	$0(a0,d0.w),a1
	lea	$0(a0,d1.w),a2
	suba.l	#$24,sp
	movea.l	sp,a3
	suba.l	#$24,sp
	movea.l	sp,a4
	move.w	(a1),d1
	move.b	$2(a1),d0
	move.b	$3(a1),d2
	ext.w	d2
	move.w	d2,-(sp)
	mulu.w	#$7,d0
	lea	($200000).l,a0
	movea.l	a3,a1
	jsr	(sub_1DFF52).l
	move.w	(sp)+,d0
	lea	(ptrtbl_1DF3E8).l,a0
	movea.l	$0(a0,d0.w),a0
	movea.l	a3,a1
	jsr	(a0)
	move.w	(a2),d1
	move.b	$2(a2),d0
	move.b	$3(a2),d2
	ext.w	d2
	move.w	d2,-(sp)
	mulu.w	#$7,d0
	lea	($200000).l,a0
	movea.l	a4,a1
	jsr	(sub_1DFF52).l
	move.w	(sp)+,d0
	lea	(ptrtbl_1DF3E8).l,a0
	movea.l	$0(a0,d0.w),a0
	movea.l	a4,a1
	jsr	(a0)
	jsr	(sub_1E0522).l
	adda.l	#$48,sp
	tst.w	d0
	ble.w	loc_1DF860
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E05B6).l
	move.w	#$B,d0
	jsr	(sub_1E0458).l
	lea	(ram_DE1C).w,a0
	move.l	d1,d0
	jsr	(sub_1E02C4).l
	move.w	#$C,d0
	jsr	(sub_1E040C).l
	movea.l	a0,a1
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E04A8).l
	lea	(dat_1E0200).l,a1
	jsr	(sub_1E04A8).l
	move.w	#$2500,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
	jsr	(sub_1E0196).l
	rts
loc_1DF860:
	lea	(ram_DDFC).w,a0
	clr.w	(a0)
	move.w	#$24,d0
	jsr	(sub_1E0458).l
	jsr	(sub_1E0196).l
	rts


; ----------------------------------------------------------------------
sub_1DF878:
	bsr.w	sub_1DFD8E
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	jsr	(sub_1D02AE).l
	bsr.w	sub_1E04BE
	bsr.w	sub_1DF960
	clr.w	(ram_BF48).w
	bsr.w	sub_1DFA0A
	bclr	#6,(TextFlags).w
	bsr.w	sub_1DFC18
	bsr.w	sub_1DFB1A
	bsr.w	sub_1DFCB6
loc_1DF8B0:
	move.w	#$2500,sr
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	btst	#7,d3
	beq.w	loc_1DF8D0
	rts
loc_1DF8D0:
	btst	#1,d1
	beq.w	loc_1DF8F4
	move.w	(ram_BF48).w,d0
	cmpi.w	#$A,(ram_BF48).w
	bge.s	loc_1DF8B0
	bsr.w	sub_1DF9DC
	addq.w	#1,d0
	move.w	d0,(ram_BF48).w
	bsr.w	sub_1DFA0A
	bra.s	loc_1DF8B0
loc_1DF8F4:
	btst	#0,d1
	beq.w	loc_1DF910
	move.w	(ram_BF48).w,d0
	ble.s	loc_1DF8B0
	bsr.w	sub_1DF9DC
	subq.w	#1,d0
	move.w	d0,(ram_BF48).w
	bsr.w	sub_1DFA0A
loc_1DF910:
	bra.s	loc_1DF8B0

	dc.b	$00,$01,$00,$0D,$02
	dc.b	"ALL TIME RECORDS",0
dat_1DF928:
	dc.b	$01,$01,$04,$07,$05
	dc.b	"TOTAL GAMES        W   L   T",0
dat_1DF94A:
	dc.w	$0101,$070C,$1A7B,$7D20,$5669,$6577,$2052,$6563
	dc.w	$6F72,$6473,$00FF


; ----------------------------------------------------------------------
; called from $1DF892
sub_1DF960:
	clr.w	d0
	clr.w	d1
	clr.w	d2
	clr.w	d3
	clr.w	d4
	jsr	(Text_PrintBig).l
inl_1DF970:
	dc.w	loc_1DF986-inl_1DF970
	dc.b	$BF,$05,$01
	dc.b	"ALL TIME RECORDS",0
loc_1DF986:
	lea	(dat_1DF928).l,a0
	move.b	(a0)+,d0
	move.b	(a0)+,d1
	move.b	(a0)+,d2
	move.b	(a0)+,d3
	move.b	(a0)+,d4
	move.w	d0,(ram_DDF2).w
	move.w	d1,(ram_DDF6).w
	move.w	d2,(ram_DDF4).w
	move.w	d3,(ram_DDF8).w
	move.w	d4,(ram_DDFA).w
	jsr	(sub_1E0196).l
	lea	(dat_1DF94A).l,a0
	move.b	(a0)+,d0
	move.b	(a0)+,d1
	move.b	(a0)+,d2
	move.b	(a0)+,d3
	move.b	(a0)+,d4
	move.w	d0,(ram_DDF2).w
	move.w	d1,(ram_DDF6).w
	move.w	d2,(ram_DDF4).w
	move.w	d3,(ram_DDF8).w
	move.w	d4,(ram_DDFA).w
	jsr	(sub_1E0196).l
	rts


; ----------------------------------------------------------------------
; called from $1DF8E4, $1DF902
sub_1DF9DC:
	movem.l	d0-d2/a0,-(sp)
	move.w	#$E,d1
loc_1DF9E4:
	move.w	#$E58E,d0
	move.w	d1,d2
	lsl.w	#7,d2
	add.w	d2,d0
	move.w	#$1D,d2
	jsr	(VDP_SetWriteAddr).l
loc_1DF9F8:
	move.w	#$8000,(a0)
	dbra	d2,loc_1DF9F8
	dbra	d1,loc_1DF9E4
	movem.l	(sp)+,d0-d2/a0
	rts


; ----------------------------------------------------------------------
; called from $1DF89A, $1DF8EE, $1DF90C
sub_1DFA0A:
	move.w	#$3,d1
loc_1DFA0E:
	move.w	(ram_BF48).w,d0
	addq.w	#3,d0
	sub.w	d1,d0
	lsl.w	#2,d0
	lea	(dat_1DF434).l,a0
	movea.l	$0(a0,d0.w),a0
	clr.w	(ram_DDF2).w
	move.w	#$7,(ram_DDF4).w
	move.w	#$1,(ram_DDF6).w
	move.w	#$7,(ram_DDF8).w
	move.w	#$3,d0
	sub.w	d1,d0
	lsl.w	#2,d0
	addi.w	#$B,d0
	move.w	d0,(ram_DDFA).w
	move.b	(a0)+,d2
	movea.l	a0,a2
	lea	(ram_DDFC).w,a1
loc_1DFA50:
	move.b	(a2)+,(a1)
	beq.w	loc_1DFA80
	cmpi.b	#$20,(a1)+
	bge.s	loc_1DFA50
	move.b	-$1(a1),d0
	clr.b	-$1(a1)
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E0196).l
	ext.w	d0
	move.w	d0,(ram_DDF2).w
	andi.w	#$1,d0
	add.w	d0,(ram_DDFA).w
	movea.l	a0,a1
	bra.s	loc_1DFA50
loc_1DFA80:
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E0196).l
	move.w	d1,-(sp)
	beq.w	loc_1DFAC4
	lea	(ptrtbl_1DF5A6).l,a0
	ext.w	d2
	lsl.w	#2,d2
	movea.l	$0(a0,d2.w),a1
	movea.l	a2,a0
	move.w	#$1,(ram_DDF2).w
	move.w	#$7,(ram_DDF4).w
	move.w	#$7,(ram_DDF8).w
	move.w	#$3,d0
	sub.w	d1,d0
	lsl.w	#2,d0
	addi.w	#$D,d0
	move.w	d0,(ram_DDFA).w
	jsr	(a1)
loc_1DFAC4:
	move.w	(sp)+,d1
	dbra	d1,loc_1DFA0E
	tst.w	(ram_BF48).w
	ble.w	loc_1DFAE2
	jsr	(Text_PrintFont).l
inl_1DFAD8:
	dc.w	loc_1DFADE-inl_1DFAD8
	dc.b	$FF,$25,$0B,$7B
loc_1DFADE:
	bra.w	loc_1DFAEE
loc_1DFAE2:
	jsr	(Text_PrintFont).l
inl_1DFAE8:
	dc.w	loc_1DFAEE-inl_1DFAE8
	dc.b	$FF,$25,$0B,$20
loc_1DFAEE:
	cmpi.w	#$A,(ram_BF48).w
	bge.w	loc_1DFB08
	jsr	(Text_PrintFont).l
inl_1DFAFE:
	dc.w	loc_1DFB04-inl_1DFAFE
	dc.b	$FF,$25,$18,$7D
loc_1DFB04:
	bra.w	loc_1DFB18
loc_1DFB08:
	jsr	(Text_PrintFont).l
inl_1DFB0E:
	dc.w	loc_1DFB14-inl_1DFB0E
	dc.b	$FF,$25,$18,$20
loc_1DFB14:
	bra.w	loc_1DFB18
loc_1DFB18:
	rts


; ----------------------------------------------------------------------
; called from $1DF8A8
sub_1DFB1A:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D14C,a0
	movea.l	#ram_D428,a1
	movea.l	#ram_D430,a6
	movea.l	#ram_D440,a5
	move.w	#$7,d7
loc_1DFB3A:
	move.b	$8(a0),d0
	lsl.w	#8,d0
	move.b	$9(a0),d0
	move.b	$A(a0),d1
	lsl.w	#8,d1
	move.b	$B(a0),d1
	move.w	d1,(a5)+
	tst.w	d1
	bne.w	loc_1DFB5C
	clr.w	d0
	bra.w	loc_1DFB62
loc_1DFB5C:
	mulu.w	#$64,d0
	divu.w	d1,d0
loc_1DFB62:
	move.b	d0,(a1)+
	move.b	$C(a0),(a6)+
	move.b	$D(a0),(a6)+
	adda.w	#$10,a0
	dbra	d7,loc_1DFB3A
	movea.l	#ram_D420,a1
	move.l	a1,-(sp)
	move.w	#$1,d0
	move.w	#$6,d7
loc_1DFB84:
	move.b	d0,(a1)+
	addq.w	#1,d0
	dbra	d7,loc_1DFB84
	movea.l	(sp),a1
	movea.l	#ram_D428,a0
	movea.l	#ram_D430,a6
	movea.l	#ram_D440,a5
loc_1DFBA0:
	movea.l	(sp),a1
	move.w	#$5,d7
	clr.w	d6
loc_1DFBA8:
	move.b	(a1)+,d1
	ext.w	d1
	move.b	(a1),d2
	ext.w	d2
	move.b	$0(a0,d1.w),d0
	move.b	$0(a0,d2.w),d3
	cmp.b	d3,d0
	bgt.w	loc_1DFC08
	blt.w	loc_1DFBFA
	movem.l	d1-d3,-(sp)
	add.w	d1,d1
	add.w	d2,d2
	move.w	$0(a6,d1.w),d0
	move.w	$0(a6,d2.w),d3
	cmp.w	d3,d0
	movem.l	(sp)+,d1-d3
	bgt.w	loc_1DFC08
	blt.w	loc_1DFBFA
	movem.l	d1-d3,-(sp)
	add.w	d1,d1
	add.w	d2,d2
	move.w	$0(a5,d1.w),d0
	move.w	$0(a5,d2.w),d3
	cmp.w	d3,d0
	movem.l	(sp)+,d1-d3
	bge.w	loc_1DFC08
loc_1DFBFA:
	move.b	(a1),d0
	move.b	-$1(a1),d1
	move.b	d0,-$1(a1)
	move.b	d1,(a1)
	st	d6
loc_1DFC08:
	dbra	d7,loc_1DFBA8
	tst.w	d6
	bne.s	loc_1DFBA0
	movea.l	(sp)+,a1
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DF8A4
sub_1DFC18:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$F35,d0
	move.l	#$80,d1
	movea.l	#ram_D14C,a0
	jsr	(SRAM_Read).l
	movea.l	#ram_D410,a1
	btst	#6,(TextFlags).w
	beq.w	loc_1DFC4A
	movea.l	#ram_D418,a1
loc_1DFC4A:
	move.l	a1,-(sp)
	move.w	#$1,d0
	move.w	#$6,d7
loc_1DFC54:
	move.b	d0,(a1)+
	addq.w	#1,d0
	dbra	d7,loc_1DFC54
	movea.l	(sp),a1
	movea.l	#ram_D14C,a0
loc_1DFC64:
	movea.l	(sp),a1
	move.w	#$5,d7
	clr.w	d6
loc_1DFC6C:
	move.b	(a1)+,d1
	ext.w	d1
	move.b	(a1),d2
	ext.w	d2
	asl.w	#4,d1
	asl.w	#4,d2
	move.b	$0(a0,d1.w),d0
	move.b	$0(a0,d2.w),d3
	btst	#6,(TextFlags).w
	beq.w	loc_1DFC92
	move.b	$4(a0,d1.w),d0
	move.b	$4(a0,d2.w),d3
loc_1DFC92:
	cmp.b	d3,d0
	bge.w	loc_1DFCA6
	move.b	(a1),d0
	move.b	-$1(a1),d1
	move.b	d0,-$1(a1)
	move.b	d1,(a1)
	st	d6
loc_1DFCA6:
	dbra	d7,loc_1DFC6C
	tst.w	d6
	bne.s	loc_1DFC64
	movea.l	(sp)+,a1
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1DF8AC
sub_1DFCB6:
	movem.l	d0-d7/a0-a3,-(sp)
	lea	(ram_D420).w,a2
	lea	(ram_D14C).w,a3
	move.w	#$1,(ram_DDF2).w
	move.w	#$7,(ram_DDF4).w
	move.w	#$1,(ram_DDF6).w
	move.w	#$7,(ram_DDF8).w
	move.w	#$6,(ram_DDFA).w
	move.w	(ram_DDF0).w,d7
	move.w	#$7,d6
	move.w	#$4,d5
loc_1DFCEC:
	move.b	(a2)+,d1
	ext.w	d1
	btst	d1,d7
	beq.w	loc_1DFD84
	subq.w	#1,d5
	blt.w	loc_1DFD84
	move.w	d1,d0
	lsl.w	#4,d1
	move.b	$A(a3,d1.w),d2
	lsl.w	#8,d2
	move.b	$B(a3,d1.w),d2
	move.b	$C(a3,d1.w),d3
	lsl.w	#8,d3
	move.b	$D(a3,d1.w),d3
	move.b	$8(a3,d1.w),d4
	lsl.w	#8,d4
	move.b	$9(a3,d1.w),d4
	sub.w	d4,d2
	sub.w	d3,d2
	lea	(ram_DDFC).w,a0
	jsr	(sub_1E05B6).l
	move.w	#$11,d0
	jsr	(sub_1E0458).l
	lea	(ram_DE1C).w,a0
	move.w	d4,d0
	jsr	(sub_1E0242).l
	move.b	#$20,(ram_DE1F).w
	lea	(ram_DE20).w,a0
	move.w	d2,d0
	jsr	(sub_1E0242).l
	move.b	#$20,(ram_DE23).w
	lea	(ram_DE24).w,a0
	move.w	d3,d0
	jsr	(sub_1E0242).l
	lea	(ram_DDFC).w,a0
	lea	(ram_DE1C).w,a1
	jsr	(sub_1E04A8).l
	jsr	(sub_1E0196).l
	move.w	#$7,(ram_DDF8).w
	addq.w	#1,(ram_DDFA).w
loc_1DFD84:
	dbra	d6,loc_1DFCEC
	movem.l	(sp)+,d0-d7/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $1DF878
sub_1DFD8E:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
	lea	(Font_Menu_Tiles).l,a2
	jsr	(Draw_RunScript).l
inl_1DFE0A:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DFE12:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B016).w
	lea	(Font_Narrow_Tiles).l,a2
	jsr	(Draw_RunScript).l
inl_1DFE2A:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1DFE32:
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1DFE56:
	dc.w	loc_1DFE5E-inl_1DFE56
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1DFE5E:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1DFE72:
	dc.w	loc_1DFE78-inl_1DFE72
	dc.b	$FE,$00,$00,$00
loc_1DFE78:
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
	move.w	#$1,(ram_C338).w
	clr.l	(ram_C068).w
	clr.l	(ram_C06C).w
	clr.l	(ram_C070).w
	clr.l	(ram_C074).w
	move.w	#$B800,d0
	move.w	#$0,(VDP_DATA).l
	move.w	#$0,(VDP_DATA).l
	move.w	(FrameCounter).w,d0
loc_1DFEC4:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1DFEC4
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1DFF08
sub_1DFECE:
	subi.w	#$10,d0
	bgt.w	loc_1DFEE2
	clr.w	d1
	movep.w	$0(a0),d1
	neg.w	d0
	lsr.w	d0,d1
	rts
loc_1DFEE2:
	movep.l	$0(a0),d1
	subi.w	#$10,d0
	neg.w	d0
	lsr.l	d0,d1
	rts


; ----------------------------------------------------------------------
; called from $1D04D2, $1D0508, $1D055E, $1D059C, $1D05AA, $1DF674
sub_1DFEF0:
	movem.l	d0/d2-d4/a0,-(sp)
	move.w	d1,d2
	lsr.w	#2,d1
	ori.w	#$1,d1
	lea	$0(a0,d1.w),a0
	andi.w	#$7,d2
	bne.w	loc_1DFF0E
	bsr.s	sub_1DFECE
	bra.w	loc_1DFF34
loc_1DFF0E:
	moveq	#$1,d3
	lsl.w	d2,d3
	subq.w	#1,d3
	move.b	(a0),d1
	and.l	d3,d1
	sub.w	d2,d0
	subi.w	#$10,d0
	ble.w	loc_1DFF2A
	bsr.w	sub_1DFF3A
	bra.w	loc_1DFF34
loc_1DFF2A:
	swap	d1
	movep.w	$2(a0),d1
	neg.w	d0
	lsr.l	d0,d1
loc_1DFF34:
	movem.l	(sp)+,d0/d2-d4/a0
	rts


; ----------------------------------------------------------------------
; called from $1DFF22
sub_1DFF3A:
	movep.l	$2(a0),d4
	neg.l	d3
	and.l	d3,d4
	or.l	d4,d1
	ror.l	d2,d1
	neg.w	d0
	sub.w	d2,d0
	addi.w	#$10,d0
	lsr.l	d0,d1
	rts


; ----------------------------------------------------------------------
; called from $1DF5EA, $1DF7B0, $1DF7E0
sub_1DFF52:
	clr.l	d3
	moveq	#-$1,d4
	move.w	d1,d2
	lsr.w	#2,d1
	ori.w	#$1,d1
	lea	$0(a0,d1.w),a0
	andi.w	#$7,d2
	beq.w	loc_1DFF7A
	move.b	(a0),d3
	move.w	#$1,d4
	ror.l	d2,d4
	subq.l	#1,d4
	and.l	d4,d3
	ror.l	d2,d3
	addq.l	#2,a0
loc_1DFF7A:
	sub.w	d2,d0
	move.w	d0,d1
	lsr.w	#5,d1
	beq.w	loc_1DFF9E
	subq.w	#1,d1
loc_1DFF86:
	movep.l	$0(a0),d5
	addq.l	#8,a0
	ror.l	d2,d5
	move.l	d5,d6
	and.l	d4,d6
	sub.l	d6,d5
	or.l	d6,d2
	move.l	d2,(a1)+
	move.l	d5,d2
	dbra	d1,loc_1DFF86
loc_1DFF9E:
	andi.w	#$1F,d0
	beq.w	loc_1DFFD2
	movep.l	$0(a0),d1
	neg.w	d0
	addi.w	#$20,d0
	moveq	#-$1,d5
	lsl.l	d0,d5
	and.l	d5,d1
	ror.l	d2,d1
	move.l	d1,d5
	and.l	d4,d1
	or.l	d1,d3
	sub.w	d2,d0
	ble.w	loc_1DFFD0
	move.l	d2,(a1)+
	eori.l	#$FFFFFFFF,d4
	and.l	d4,d5
	move.l	d5,d3
loc_1DFFD0:
	move.l	d3,(a1)+
loc_1DFFD2:
	rts


; ----------------------------------------------------------------------
; called from $1E002A
sub_1DFFD4:
	subi.w	#$10,d0
	bgt.w	loc_1DFFF6
	neg.w	d0
	lsl.w	d0,d1
	move.w	#$1,d2
	lsl.w	d0,d2
	subq.w	#1,d2
	movep.w	$0(a0),d3
	and.w	d2,d3
	or.w	d1,d3
	movep.w	d3,$0(a0)
	rts
loc_1DFFF6:
	neg.w	d0
	addi.w	#$10,d0
	lsl.l	d0,d1
	moveq	#$1,d2
	lsl.w	d0,d2
	subq.w	#1,d2
	movep.l	$0(a0),d3
	and.l	d2,d3
	or.l	d1,d3
	movep.l	d3,$0(a0)
	rts


; ----------------------------------------------------------------------
; called from $1D04F4, $1D0544, $1D057C, $1D05E0, $1D05F8
sub_1E0012:
	movem.l	d0-d4/a0,-(sp)
	move.w	d2,d3
	lsr.w	#2,d2
	ori.w	#$1,d2
	lea	$0(a0,d2.w),a0
	andi.w	#$7,d3
	bne.w	loc_1E0030
	bsr.s	sub_1DFFD4
	bra.w	loc_1E005E
loc_1E0030:
	subi.w	#$10,d0
	ble.w	loc_1E0040
	bsr.w	sub_1E0064
	bra.w	loc_1E005E
loc_1E0040:
	neg.w	d0
	lsl.w	d0,d1
	lsl.l	d3,d1
	move.l	#$FFFF,d4
	lsl.w	d0,d4
	lsl.l	d3,d4
	neg.l	d4
	movep.l	-$2(a0),d2
	and.l	d4,d2
	or.l	d1,d2
	movep.l	d2,-$2(a0)
loc_1E005E:
	movem.l	(sp)+,d0-d4/a0
	rts


; ----------------------------------------------------------------------
; called from $1E0038
sub_1E0064:
	neg.w	d0
	addi.w	#$10,d0
	lsl.l	d0,d1
	rol.l	d3,d1
	move.b	d1,(a0)
	moveq	#-$1,d4
	lsl.l	d0,d4
	lsl.l	d3,d4
	and.l	d4,d1
	neg.l	d4
	movep.l	$2(a0),d2
	and.l	d4,d2
	or.l	d1,d2
	movep.l	d2,$2(a0)
	rts


; ----------------------------------------------------------------------
sub_1E0088:
	move.l	(a1)+,d3
	moveq	#-$1,d4
	move.w	d2,d5
	lsr.w	#2,d2
	ori.w	#$1,d2
	lea	$0(a0,d2.w),a0
	andi.w	#$7,d5
	beq.w	loc_1E00B6
	rol.l	d5,d3
	lsl.l	d5,d4
	move.l	d3,d6
	and.l	d4,d6
	sub.l	d6,d3
	move.b	(a0),d1
	and.w	d4,d1
	or.w	d3,d1
	move.b	d1,(a0)
	addq.l	#2,a0
	move.l	d6,d3
loc_1E00B6:
	sub.w	d5,d0
	move.w	d0,d1
	lsr.w	#5,d1
	beq.w	loc_1E00DA
	subq.w	#1,d1
loc_1E00C2:
	move.l	(a1)+,d6
	rol.l	d5,d6
	move.l	d6,d7
	and.l	d4,d7
	sub.l	d7,d6
	or.w	d6,d3
	movep.l	d3,$0(a0)
	addq.l	#8,a0
	move.l	d7,d3
	dbra	d1,loc_1E00C2
loc_1E00DA:
	andi.w	#$1F,d0
	beq.w	loc_1E0116
	add.w	d5,d0
	subi.w	#$20,d0
	ble.w	loc_1E00F6
	move.w	(a1),d6
	rol.l	d5,d6
	neg.w	d4
	and.w	d4,d6
	or.w	d6,d3
loc_1E00F6:
	subi.w	#$10,d0
	bgt.w	loc_1E0118
	neg.w	d0
	swap	d3
	move.w	#$FFFF,d4
	lsl.w	d0,d4
	neg.w	d4
	movep.w	$0(a0),d5
	or.w	d4,d5
	or.w	d3,d5
	movep.w	d5,$0(a0)
loc_1E0116:
	rts
loc_1E0118:
	neg.w	d0
	addi.w	#$10,d0
	moveq	#-$1,d4
	lsl.l	d0,d4
	neg.l	d4
	movep.l	$0(a0),d5
	and.l	d4,d5
	or.l	d3,d5
	movep.l	d5,$0(a0)
	rts

ptrtbl_1E0132:
	dc.l	sub_1E0142
	dc.l	sub_1E0158
	dc.l	sub_1E016C
	dc.l	sub_1E0182


; ----------------------------------------------------------------------
; called from $1E01C0
sub_1E0142:
	bclr	#3,(TextFlags).w
	bclr	#2,(ram_C356).w
	lea	(sub_020F4A).l,a2
	addq.w	#1,d2
	rts


; ----------------------------------------------------------------------
; called from $1E01C0
sub_1E0158:
	bclr	#3,(TextFlags).w
	bclr	#2,(ram_C356).w
	lea	(Text_PrintCmd_Worker).l,a2
	rts


; ----------------------------------------------------------------------
; called from $1E01C0
sub_1E016C:
	bclr	#3,(TextFlags).w
	bset	#2,(ram_C356).w
	lea	(sub_020F4A).l,a2
	addq.w	#1,d2
	rts


; ----------------------------------------------------------------------
; called from $1E01C0
sub_1E0182:
	bset	#3,(TextFlags).w
	bclr	#2,(ram_C356).w
	lea	(Text_PrintCmd_Worker).l,a2
	rts


; ----------------------------------------------------------------------
; called from $00E660, $00E676, $1DF65C, $1DF764, $1DF858, $1DF870, $1DF9AA, $1DF9D4 (+4 more)
sub_1E0196:
	movem.l	d0-d6/a0-a2,-(sp)
	jsr	(sub_1E0496).l
	move.w	(ram_DDF2).w,d1
	move.w	(ram_DDF4).w,d2
	move.w	(ram_DDF6).w,d3
	move.w	(ram_DDF8).w,d4
	move.w	(ram_DDFA).w,d5
	lsl.w	#2,d1
	lea	(ptrtbl_1E0132).l,a1
	movea.l	$0(a1,d1.w),a1
	jsr	(a1)
	move.w	d0,d6
	add.w	d4,d0
	move.w	d0,(ram_DDF8).w
	addq.w	#8,d6
	andi.l	#$FFFE,d6
	suba.l	d6,sp
	movea.l	sp,a1
	move.w	d6,(a1)+
	move.b	#$F8,(a1)+
	move.b	d2,(a1)+
	move.b	d3,(a1)+
	move.b	d4,(a1)+
	move.b	d5,(a1)+
	clr.b	(a1)
	exg	a1,a0
	jsr	(sub_1E04A8).l
	subq.l	#7,a0
	movea.l	a0,a1
	jsr	(a2)
	adda.l	d6,sp
	movem.l	(sp)+,d0-d6/a0-a2
	rts


; ----------------------------------------------------------------------
sub_1E01FC:
	move.l	-(a0),d0
	move.l	-(a0),d0
dat_1E0200:
	move.l	d0,d0

; ----------------------------------------------------------------------
; called from $1E031C
sub_1E0202:
	jsr	(sub_1E0286).l
	cmpi.b	#$0,$1(a0)
	bne.w	loc_1E0220
	move.b	(a0),$1(a0)
	move.b	#$20,(a0)
	move.b	#$0,$2(a0)
loc_1E0220:
	rts


; ----------------------------------------------------------------------
; called from $1DF6D4, $1DF6EE
sub_1E0222:
	jsr	(sub_1E0286).l
	cmpi.b	#$0,$1(a0)
	bne.w	loc_1E0240
	move.b	(a0),$1(a0)
	move.b	#$30,(a0)
	move.b	#$0,$2(a0)
loc_1E0240:
	rts


; ----------------------------------------------------------------------
; called from $1DFD3C, $1DFD4E, $1DFD60, $1E0366
sub_1E0242:
	jsr	(sub_1E0286).l
	cmpi.b	#$0,$1(a0)
	bne.w	loc_1E0268
	move.b	(a0),$2(a0)
	move.b	#$20,$1(a0)
	move.b	#$20,(a0)
	clr.b	$3(a0)
	bra.w	loc_1E0284
loc_1E0268:
	cmpi.b	#$0,$2(a0)
	bne.w	loc_1E0284
	move.b	$1(a0),$2(a0)
	move.b	(a0),$1(a0)
	move.b	#$20,(a0)
	clr.b	$3(a0)
loc_1E0284:
	rts


; ----------------------------------------------------------------------
; called from $00E65A, $00E670, $1DF62C, $1DF6FA, $1DF70A, $1E0202, $1E0222, $1E0242 (+4 more)
sub_1E0286:
	movem.l	d0-d2/a1,-(sp)
	movea.l	a0,a1
	cmp.w	#$0,d0	; general form
	bpl.w	loc_1E029A
	neg.w	d0
	move.b	#$2D,(a0)+
loc_1E029A:
	clr.w	d1
loc_1E029C:
	ext.l	d0
	divu.w	#$A,d0
	move.l	d0,d2
	swap	d2
	addi.b	#$30,d2
	move.b	d2,-(sp)
	addq.w	#1,d1
	and.w	d0,d0
	bne.s	loc_1E029C
	subq.w	#1,d1
loc_1E02B4:
	move.b	(sp)+,(a0)+
	dbra	d1,loc_1E02B4
	clr.b	(a0)+
	movea.l	a1,a0
	movem.l	(sp)+,d0-d2/a1
	rts


; ----------------------------------------------------------------------
; called from $1DF822
sub_1E02C4:
	movem.l	d0/a0-a2,-(sp)
	movea.l	a0,a2
	subq.l	#6,sp
	movea.l	sp,a0
	subq.l	#6,sp
	movea.l	sp,a1
	jsr	(sub_1E0286).l
	exg	a0,a1
	swap	d0
	jsr	(sub_1E0286).l
	exg	a0,a2
	clr.b	(a0)
	jsr	(sub_1E04A8).l
	move.w	#$2E00,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
	movea.l	a2,a1
	jsr	(sub_1E04A8).l
	adda.l	#$C,sp
	movem.l	(sp)+,d0/a0-a2
	rts


; ----------------------------------------------------------------------
sub_1E030E:
	movem.l	d0/a0-a2,-(sp)
	movea.l	a0,a2
	subq.l	#6,sp
	movea.l	sp,a0
	subq.l	#6,sp
	movea.l	sp,a1
	jsr	(sub_1E0202).l
	exg	a0,a1
	swap	d0
	jsr	(sub_1E0286).l
	exg	a0,a2
	clr.b	(a0)
	jsr	(sub_1E04A8).l
	move.w	#$2E00,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
	movea.l	a2,a1
	jsr	(sub_1E04A8).l
	adda.l	#$C,sp
	movem.l	(sp)+,d0/a0-a2
	rts


; ----------------------------------------------------------------------
sub_1E0358:
	movem.l	d0/a0-a2,-(sp)
	movea.l	a0,a2
	subq.l	#6,sp
	movea.l	sp,a0
	subq.l	#6,sp
	movea.l	sp,a1
	jsr	(sub_1E0242).l
	exg	a0,a1
	swap	d0
	jsr	(sub_1E0286).l
	exg	a0,a2
	clr.b	(a0)
	jsr	(sub_1E04A8).l
	move.w	#$2E00,-(sp)
	movea.l	sp,a1
	jsr	(sub_1E04A8).l
	addq.l	#2,sp
	movea.l	a2,a1
	jsr	(sub_1E04A8).l
	adda.l	#$C,sp
	movem.l	(sp)+,d0/a0-a2
	rts


; ----------------------------------------------------------------------
sub_1E03A2:
	movem.l	d0-d3/a0-a2,-(sp)
	move.w	d0,d3
	addq.w	#1,d3
	andi.w	#$FFFE,d3
	suba.l	d3,sp
	movea.l	sp,a1
	movea.l	a0,a2
	move.w	d0,d1
	jsr	(sub_1E0496).l
	move.w	d1,d2
	sub.w	d0,d2
	ble.w	loc_1E03D4
	lsr.w	#1,d2
	subq.w	#1,d2
	ble.w	loc_1E03D4
loc_1E03CC:
	move.b	#$20,(a1)+
	dbra	d2,loc_1E03CC
loc_1E03D4:
	move.w	d0,d2
	beq.w	loc_1E03E2
	subq.w	#1,d2
loc_1E03DC:
	move.b	(a0)+,(a1)+
	dbra	d2,loc_1E03DC
loc_1E03E2:
	move.w	d1,d2
	sub.w	d0,d1
	lsr.w	#1,d1
	sub.w	d1,d2
	sub.w	d0,d2
	ble.w	loc_1E03FA
	subq.w	#1,d2
loc_1E03F2:
	move.b	#$20,(a1)+
	dbra	d2,loc_1E03F2
loc_1E03FA:
	move.b	#$0,(a1)+
	movea.l	sp,a1
loc_1E0400:
	move.b	(a1)+,(a2)+
	bne.s	loc_1E0400
	adda.l	d3,sp
	movem.l	(sp)+,d0-d3/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $1DF636, $1DF752, $1DF82C
sub_1E040C:
	movem.l	d0-d3/a0-a2,-(sp)
	move.w	d0,d3
	addq.w	#1,d3
	andi.w	#$FFFE,d3
	suba.l	d3,sp
	movea.l	sp,a1
	movea.l	a0,a2
	move.w	d0,d1
	jsr	(sub_1E0496).l
	move.w	d1,d2
	sub.w	d0,d2
	ble.w	loc_1E0438
	subq.w	#1,d2
loc_1E0430:
	move.b	#$20,(a1)+
	dbra	d2,loc_1E0430
loc_1E0438:
	move.w	d0,d2
	beq.w	loc_1E0446
	subq.w	#1,d2
loc_1E0440:
	move.b	(a0)+,(a1)+
	dbra	d2,loc_1E0440
loc_1E0446:
	move.b	#$0,(a1)+
	movea.l	sp,a1
loc_1E044C:
	move.b	(a1)+,(a2)+
	bne.s	loc_1E044C
	adda.l	d3,sp
	movem.l	(sp)+,d0-d3/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $1DF620, $1DF694, $1DF816, $1DF86A, $1DFD30
sub_1E0458:
	movem.l	d0-d3/a0-a2,-(sp)
	move.w	d0,d3
	addq.w	#1,d3
	andi.w	#$FFFE,d3
	suba.l	d3,sp
	movea.l	sp,a1
	movea.l	a0,a2
loc_1E046A:
	subq.w	#1,d0
	move.b	(a0)+,(a1)+
	bne.s	loc_1E046A
	lea	-$1(a1),a1
	cmp.w	#$0,d0	; general form
	blt.w	loc_1E0488
loc_1E047C:
	move.b	#$20,(a1)+
	dbra	d0,loc_1E047C
	move.b	#$0,(a1)+
loc_1E0488:
	movea.l	sp,a1
loc_1E048A:
	move.b	(a1)+,(a2)+
	bne.s	loc_1E048A
	adda.l	d3,sp
	movem.l	(sp)+,d0-d3/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $1E019A, $1E03B6, $1E0420
sub_1E0496:
	move.l	a1,-(sp)
	movea.l	a0,a1
loc_1E049A:
	tst.b	(a1)+
	bne.s	loc_1E049A
	suba.l	a0,a1
	move.w	a1,d0
	subq.w	#1,d0
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $1DF642, $1DF64E, $1DF656, $1DF720, $1DF72C, $1DF738, $1DF744, $1DF75E (+14 more)
sub_1E04A8:
	movem.l	a0/a1,-(sp)
loc_1E04AC:
	tst.b	(a0)+
	bne.s	loc_1E04AC
	lea	-$1(a0),a0
loc_1E04B4:
	move.b	(a1)+,(a0)+
	bne.s	loc_1E04B4
	movem.l	(sp)+,a0/a1
	rts


; ----------------------------------------------------------------------
; called from $1DF88E
sub_1E04BE:
	move.w	#$7,d0
	clr.w	d2
loc_1E04C4:
	move.w	d0,d1
	mulu.w	#$A,d1
	lea	(ram_D34A).w,a0
	tst.b	$0(a0,d1.w)
	beq.w	loc_1E04DE
	move.w	#$1,d1
	lsl.w	d0,d1
	or.w	d1,d2
loc_1E04DE:
	dbra	d0,loc_1E04C4
	andi.w	#$FFFE,d2
	move.w	d2,(ram_DDF0).w
	rts


; ----------------------------------------------------------------------
; called from $1DF600
sub_1E04EC:
	movem.l	d2-d4/a1,-(sp)
	move.w	#$FFFF,d0
	clr.l	d1
	move.w	(ram_DDF0).w,d2
	beq.w	loc_1E051C
	move.w	#$FFFF,d3
loc_1E0502:
	addq.w	#1,d3
	move.l	(a1)+,d4
	btst	#0,d2
	beq.w	loc_1E0518
	cmp.l	d1,d4
	blt.w	loc_1E0518
	move.w	d3,d0
	move.l	d4,d1
loc_1E0518:
	lsr.w	#1,d2
	bne.s	loc_1E0502
loc_1E051C:
	movem.l	(sp)+,d2-d4/a1
	rts


; ----------------------------------------------------------------------
; called from $1DF7F6
sub_1E0522:
	movem.l	d2-d5/a3/a4,-(sp)
	move.w	#$FFFF,d0
	clr.l	d1
	move.w	(ram_DDF0).w,d2
	beq.w	loc_1E0562
	move.w	#$FFFF,d3
loc_1E0538:
	addq.w	#1,d3
	move.l	(a3)+,d4
	move.l	(a4)+,d5
	btst	#0,d2
	beq.w	loc_1E055E
	jsr	(sub_1E057A).l
	lsr.l	#1,d4
	mulu.w	#$64,d4
	lsl.l	#1,d4
	cmp.l	d1,d4
	blt.w	loc_1E055E
	move.w	d3,d0
	move.l	d4,d1
loc_1E055E:
	lsr.w	#1,d2
	bne.s	loc_1E0538
loc_1E0562:
	addi.l	#$CCD,d1
	move.w	d1,d4
	mulu.w	#$A,d4
	swap	d4
	move.w	d4,d1
	swap	d1
	movem.l	(sp)+,d2-d5/a3/a4
	rts


; ----------------------------------------------------------------------
; called from $1D05B4, $1D05C0, $1E0546
sub_1E057A:
	movem.l	d0/d1/d5,-(sp)
	andi.l	#$FFFF,d4
	andi.l	#$FFFF,d5
	beq.w	loc_1E05B0
	clr.w	d1
loc_1E0590:
	move.w	d5,d0
	andi.w	#$FF00,d0
	beq.w	loc_1E05A0
	lsr.w	#1,d5
	addq.w	#1,d1
	bra.s	loc_1E0590
loc_1E05A0:
	neg.w	d1
	addq.w	#8,d1
	lsl.w	d1,d4
	divu.w	d5,d4
	andi.l	#$FFFF,d4
	lsl.l	#8,d4
loc_1E05B0:
	movem.l	(sp)+,d0/d1/d5
	rts


; ----------------------------------------------------------------------
; called from $1DF616, $1DF68A, $1DF80C, $1DFD26
sub_1E05B6:
	movem.l	d0/a0/a1,-(sp)
	lea	(ram_D34A).w,a1
	mulu.w	#$A,d0
	lea	$0(a1,d0.w),a1
loc_1E05C6:
	move.b	(a1)+,(a0)+
	bne.s	loc_1E05C6
	movem.l	(sp)+,d0/a0/a1
	rts

	dc.b	$42,$47


; ----------------------------------------------------------------------
; called from $019ED8
sub_1E05D2:
	move.w	d7,(ram_CF4E).w
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	(ram_D330).w
	clr.w	(ram_D04C).w
	move.w	$28(a2),(ram_D05A).w
	bsr.w	sub_1E0948
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D04E).w
	move.w	#$D,(ram_D052).w
	move.w	#$C,(ram_D050).w
	clr.w	(ram_D04C).w
loc_1E060C:
	move.w	(ram_D05A).w,d7
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0626
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E0640
	bra.w	loc_1E0630
loc_1E0626:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E0640
loc_1E0630:
	jsr	(sub_01A20E).l
	subq.w	#1,d0
	move.w	d0,(ram_D054).w
	bra.w	loc_1E0656
loc_1E0640:
	jsr	(sub_01A20E).l
	move.w	d0,-(sp)
	jsr	(sub_01A278).l
	sub.w	(sp)+,d0
	subq.w	#1,d0
	move.w	d0,(ram_D054).w
loc_1E0656:
	bsr.w	sub_1E0E3C
	move.w	(FrameCounter).w,d0
loc_1E065E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E065E
	jsr	(sub_1D567A).l
loc_1E066A:
	move.w	(FrameCounter).w,d0
loc_1E066E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E066E
	bsr.w	sub_1E0CFC
	bsr.w	sub_1E0A9A
	bsr.w	sub_1E0B96
	bsr.w	sub_1E0AB8
	move.w	#$2500,sr
	move.w	(FrameCounter).w,d0
loc_1E068C:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E068C
	bset	#2,(VideoFlags).w
	bsr.w	sub_1E111E
	bsr.w	sub_1E08F2
	move.w	#$2500,sr
	bclr	#2,(VideoFlags).w
loc_1E06AA:
	bsr.w	sub_1E0872
	tst.w	d1
	beq.w	loc_1E085E
	btst	#7,d1
	bne.w	loc_1E0864
	btst	#2,d1
	beq.w	loc_1E073E
	tst.w	(ram_CF4E).w
	bne.w	loc_1E06EE
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E0710
	subq.w	#1,(ram_D04C).w
	cmpi.w	#$5,(ram_D04C).w
	bge.w	loc_1E0730
	move.w	#$7,(ram_D04C).w
	bra.w	loc_1E0730
loc_1E06EE:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E0722
	subq.w	#1,(ram_D04C).w
	cmpi.w	#$4,(ram_D04C).w
	bge.w	loc_1E0730
	move.w	#$6,(ram_D04C).w
	bra.w	loc_1E0730
loc_1E0710:
	subq.w	#1,(ram_D04C).w
	bpl.w	loc_1E0730
	move.w	#$4,(ram_D04C).w
	bra.w	loc_1E0730
loc_1E0722:
	subq.w	#1,(ram_D04C).w
	bpl.w	loc_1E0730
	move.w	#$3,(ram_D04C).w
loc_1E0730:
	clr.w	(ram_D04E).w
	move.w	#$C,(ram_D050).w
	bra.w	loc_1E060C
loc_1E073E:
	btst	#0,d1
	beq.w	loc_1E075A
	tst.w	(ram_D04E).w
	beq.w	loc_1E06AA
	subq.w	#1,(ram_D04E).w
	subq.w	#1,(ram_D050).w
	bra.w	loc_1E066A
loc_1E075A:
	btst	#1,d1
	beq.w	loc_1E077A
	move.w	(ram_D050).w,d0
	cmp.w	(ram_D054).w,d0
	bge.w	loc_1E06AA
	addq.w	#1,(ram_D04E).w
	addq.w	#1,(ram_D050).w
	bra.w	loc_1E066A
loc_1E077A:
	btst	#6,d1
	beq.w	loc_1E07AE
	tst.w	(ram_CF4E).w
	bne.w	loc_1E07AE
	cmpa.l	#ram_C732,a2
	beq.w	loc_1E079E
	movea.l	#ram_C732,a2
	bra.w	loc_1E07A4
loc_1E079E:
	movea.l	#ram_CAD0,a2
loc_1E07A4:
	move.w	$28(a2),(ram_D05A).w
	bra.w	loc_1E060C
loc_1E07AE:
	btst	#4,d1
	beq.w	loc_1E07F6
	tst.w	(ram_CF4E).w
	bne.w	loc_1E07D0
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E07EC
	clr.w	(ram_D04C).w
	bra.w	loc_1E060C
loc_1E07D0:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E07E2
	clr.w	(ram_D04C).w
	bra.w	loc_1E060C
loc_1E07E2:
	move.w	#$4,(ram_D04C).w
	bra.w	loc_1E060C
loc_1E07EC:
	move.w	#$5,(ram_D04C).w
	bra.w	loc_1E060C
loc_1E07F6:
	btst	#3,d1
	beq.w	loc_1E06AA
	addq.w	#1,(ram_D04C).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0834
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E0730
	bgt.w	loc_1E0820
	clr.w	(ram_D04C).w
	bra.w	loc_1E0730
loc_1E0820:
	cmpi.w	#$7,(ram_D04C).w
	ble.w	loc_1E0730
	move.w	#$5,(ram_D04C).w
	bra.w	loc_1E0730
loc_1E0834:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E0730
	bgt.w	loc_1E084A
	clr.w	(ram_D04C).w
	bra.w	loc_1E0730
loc_1E084A:
	cmpi.w	#$6,(ram_D04C).w
	ble.w	loc_1E0730
	move.w	#$4,(ram_D04C).w
	bra.w	loc_1E0730
loc_1E085E:
	jmp	(loc_026D3E).l
loc_1E0864:
	move.l	#sub_016614,(ram_DDD0).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E06AA
sub_1E0872:
	move.l	#dat_005460,d6
loc_1E0878:
	move.w	#$64,d6
	move.w	(FrameCounter).w,d1
	sub.w	(ram_B056).w,d1
	beq.s	loc_1E0878
	move.w	(FrameCounter).w,(ram_B056).w
	jsr	(Joypad_Read1).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1E08A2
	bra.w	loc_1E08F0
loc_1E08A2:
	jsr	(Joypad_Read2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1E08B8
	bra.w	loc_1E08F0
loc_1E08B8:
	tst.w	(FourWayPlay).w
	beq.w	loc_1E08EC
	jsr	(Joypad_Read3).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1E08D6
	bra.w	loc_1E08F0
loc_1E08D6:
	jsr	(Joypad_Read4).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.w	loc_1E08EC
	bra.w	loc_1E08F0
loc_1E08EC:
	dbra	d6,loc_1E0878
loc_1E08F0:
	rts


; ----------------------------------------------------------------------
; called from $1E069C
sub_1E08F2:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_D04E).w
	beq.w	loc_1E090E
	jsr	(Text_PrintFont).l
inl_1E0904:
	dc.w	loc_1E090A-inl_1E0904
	dc.b	$8F,$02,$0B,$7B
loc_1E090A:
	bra.w	loc_1E091A
loc_1E090E:
	jsr	(Text_PrintFont).l
inl_1E0914:
	dc.w	loc_1E091A-inl_1E0914
	dc.b	$8F,$02,$0B,$20
loc_1E091A:
	move.w	(ram_D050).w,d1
	cmp.w	(ram_D054).w,d1
	bge.w	loc_1E0936
	jsr	(Text_PrintFont).l
inl_1E092C:
	dc.w	loc_1E0932-inl_1E092C
	dc.b	$8F,$02,$17,$7D
loc_1E0932:
	bra.w	loc_1E0942
loc_1E0936:
	jsr	(Text_PrintFont).l
inl_1E093C:
	dc.w	loc_1E0942-inl_1E093C
	dc.b	$8F,$02,$17,$20
loc_1E0942:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E05E8
sub_1E0948:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E09C8:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E09D0:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E09E8:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E09F0:
	bset	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_D058).w
	addi.w	#$20,d4
	jsr	(Text_PrintCmd).l
inl_1E0A1C:
	dc.w	loc_1E0A24-inl_1E0A1C
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E0A24:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(sub_1E0B96).l
	jsr	(Text_Print).l
inl_1E0A3E:
	dc.w	loc_1E0A44-inl_1E0A3E
	dc.b	$FE,$00,$00,$00
loc_1E0A44:
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
	bset	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_1E0A6E:
	dc.w	loc_1E0A80-inl_1E0A6E
	dc.b	$BF,$09,$01
	dc.b	"PLAYER STATS",0
loc_1E0A80:
	bsr.w	sub_1E0AB8
	bsr.w	sub_1E0CFC
	bsr.w	sub_1E0A9A
	jsr	(sub_1D5E5E).l
	move.w	#$2500,sr
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1E0678, $1E0A88
sub_1E0A9A:
	move.w	d7,-(sp)
	jsr	(Text_Print).l
inl_1E0AA2:
	dc.w	loc_1E0AA8-inl_1E0AA2
	dc.b	$BF,$01,$05,$00
loc_1E0AA8:
	move.w	(ram_D058).w,d4
	move.w	(ram_D05A).w,d7
	jsr	(sub_016EB8).l
	move.w	(sp)+,d7

; ----------------------------------------------------------------------
; called from $1E0680, $1E0A80
sub_1E0AB8:
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0B2A
	cmpi.w	#$5,(ram_D04C).w
	bge.w	loc_1E0AFC
	jsr	(Text_PrintNarrow).l
inl_1E0AD0:
	dc.w	loc_1E0AF8-inl_1E0AD0
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  PLAYER     g   a   p  sh   pim"
loc_1E0AF8:
	bra.w	loc_1E0B94
loc_1E0AFC:
	jsr	(Text_PrintNarrow).l
inl_1E0B02:
	dc.w	loc_1E0B2A-inl_1E0B02
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  GOALIE        s     sh    sp  "
loc_1E0B2A:
	cmpi.w	#$4,(ram_D04C).w
	bge.w	loc_1E0B66
	jsr	(Text_PrintNarrow).l
inl_1E0B3A:
	dc.w	loc_1E0B62-inl_1E0B3A
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  PLAYER         g   a   p   pim"
loc_1E0B62:
	bra.w	loc_1E0B94
loc_1E0B66:
	jsr	(Text_PrintNarrow).l
inl_1E0B6C:
	dc.w	loc_1E0B94-inl_1E0B6C
	dc.b	$F8,$04,$01,$04,$08
	dc.b	"#  GOALIE        s     sh    sp  "
loc_1E0B94:
	rts


; ----------------------------------------------------------------------
; called from $1E067C, $1E0A32
sub_1E0B96:
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0BAC
	cmpi.w	#$5,(ram_D04C).w
	bge.w	loc_1E0C58
	bra.w	loc_1E0BB6
loc_1E0BAC:
	cmpi.w	#$4,(ram_D04C).w
	bge.w	loc_1E0C58
loc_1E0BB6:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0C0E
	jsr	(Text_PrintFont).l
inl_1E0BCE:
	dc.w	loc_1E0C0A-inl_1E0BCE
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST            "
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-GOALIES"
loc_1E0C0A:
	bra.w	loc_1E0C50
loc_1E0C0E:
	jsr	(Text_PrintFont).l
inl_1E0C14:
	dc.w	loc_1E0C50-inl_1E0C14
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST   A-TEAMS  "
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-GOALIES"
loc_1E0C50:
	move.w	(sp)+,(FontTileBase).w
	bra.w	loc_1E0CFA
loc_1E0C58:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0CB4
	jsr	(Text_PrintFont).l
inl_1E0C70:
	dc.w	loc_1E0CAC-inl_1E0C70
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST            "
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-PLAYERS"
loc_1E0CAC:
	move.w	(sp)+,(FontTileBase).w
	bra.w	loc_1E0CFA
loc_1E0CB4:
	jsr	(Text_PrintFont).l
inl_1E0CBA:
	dc.w	loc_1E0CF6-inl_1E0CBA
	dc.b	$8F,$04,$19
	dc.b	"{}-SCROLL LIST   A-TEAMS  "
	dc.b	$8F,$04,$1A
	dc.b	"[]-CATEGORY      B-PLAYERS"
loc_1E0CF6:
	move.w	(sp)+,(FontTileBase).w
loc_1E0CFA:
	rts


; ----------------------------------------------------------------------
; called from $1E0674, $1E0A84
sub_1E0CFC:
	jsr	(Text_Print).l
inl_1E0D02:
	dc.w	loc_1E0D08-inl_1E0D02
	dc.b	$BF,$15,$05,$00
loc_1E0D08:
	movea.l	#dat_1E0D2E,a1
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0D1C
	movea.l	#dat_1E0DAC,a1
loc_1E0D1C:
	move.w	(ram_D04C).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintNarrow_Worker).l
	rts
dat_1E0D2E:
	dc.b	$00,$12
	dc.b	"     goals     ",0
	dc.b	$00,$12
	dc.b	"    assists    ",0
	dc.b	$00,$12
	dc.b	"     points    ",0
	dc.b	$00,$12
	dc.b	"penalty minutes",0
	dc.b	$00,$12
	dc.b	"     saves     ",0
	dc.b	$00,$12
	dc.b	"     shots     ",0
	dc.b	$00,$12
	dc.b	"save percentage",0
dat_1E0DAC:
	dc.b	$00,$12
	dc.b	"     goals     ",0
	dc.b	$00,$12
	dc.b	"    assists    ",0
	dc.b	$00,$12
	dc.b	"     points    ",0
	dc.b	$00,$12
	dc.b	"     shots     ",0
	dc.b	$00,$12
	dc.b	"penalty minutes",0
	dc.b	$00,$12
	dc.b	"     saves     ",0
	dc.b	$00,$12
	dc.b	"     shots     ",0
	dc.b	$00,$12
	dc.b	"save percentage",0


; ----------------------------------------------------------------------
; called from $1E0656
sub_1E0E3C:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D05A).w,d7
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0E5A
	cmpi.w	#$5,(ram_D04C).w
	bge.w	loc_1E0F84
	bra.w	loc_1E0E64
loc_1E0E5A:
	cmpi.w	#$4,(ram_D04C).w
	bge.w	loc_1E0F84
loc_1E0E64:
	jsr	(sub_01A278).l
	move.w	d0,-(sp)
	jsr	(sub_01A20E).l
	move.w	d0,(SaveChecksum).w
	add.w	d0,(SaveChecksum).w
	move.w	d0,d1
	adda.w	d1,a2
	sub.w	(sp)+,d0
	neg.w	d0
	move.w	d0,(ram_D056).w
	movea.l	#ram_D05C,a0
	bra.w	loc_1E0E94
loc_1E0E90:
	move.w	d1,(a0)+
	addq.w	#1,d1
loc_1E0E94:
	dbra	d0,loc_1E0E90
	move.w	(ram_D056).w,d3
	movea.l	#ram_D094,a0
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0EC0
	move.l	a2,-(sp)
	movea.l	#ram_CE6E,a2
	move.w	(SaveChecksum).w,d2
	bsr.w	sub_1E10E8
	movea.l	(sp)+,a2
	bra.w	loc_1E0EC8
loc_1E0EC0:
	move.w	#$C0,d2
	bsr.w	sub_1E10D2
loc_1E0EC8:
	move.w	(ram_D056).w,d3
	movea.l	#ram_D0CC,a0
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0EF0
	move.l	a2,-(sp)
	movea.l	#ram_CEA6,a2
	move.w	(SaveChecksum).w,d2
	bsr.w	sub_1E10E8
	movea.l	(sp)+,a2
	bra.w	loc_1E0EF8
loc_1E0EF0:
	move.w	#$DC,d2
	bsr.w	sub_1E10D2
loc_1E0EF8:
	move.l	a2,-(sp)
	movea.l	#ram_D094,a1
	movea.l	#ram_D0CC,a2
	movea.l	#ram_D104,a0
	move.w	(ram_D056).w,d3
	bra.w	loc_1E0F1A
loc_1E0F14:
	move.w	(a1)+,d0
	add.w	(a2)+,d0
	move.w	d0,(a0)+
loc_1E0F1A:
	dbra	d3,loc_1E0F14
	movea.l	(sp)+,a2
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0F50
	movea.l	#ram_D13C,a0
	move.w	(ram_D056).w,d3
	move.w	#$F8,d2
	bsr.w	sub_1E10D2
	movea.l	#ram_D174,a0
	move.w	(ram_D056).w,d3
	move.w	#$114,d2
	bsr.w	sub_1E10D2
	bra.w	loc_1E1068
loc_1E0F50:
	movea.l	#ram_D13C,a0
	move.w	(ram_D056).w,d3
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0F78
	move.l	a2,-(sp)
	movea.l	#ram_CF16,a2
	move.w	(SaveChecksum).w,d2
	bsr.w	sub_1E10E8
	movea.l	(sp)+,a2
	bra.w	loc_1E0F80
loc_1E0F78:
	move.w	#$114,d2
	bsr.w	sub_1E10D2
loc_1E0F80:
	bra.w	loc_1E1068
loc_1E0F84:
	jsr	(sub_01A20E).l
	move.w	d0,(ram_D056).w
	movea.l	#ram_D05C,a0
	clr.w	d1
	bra.w	loc_1E0F9E
loc_1E0F9A:
	move.w	d1,(a0)+
	addq.w	#1,d1
loc_1E0F9E:
	dbra	d0,loc_1E0F9A
	movea.l	#ram_D174,a0
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0FB6
	movea.l	#ram_D1AC,a0
loc_1E0FB6:
	move.w	(ram_D056).w,d3
	tst.w	(ram_CF4E).w
	beq.w	loc_1E0FD6
	move.l	a2,-(sp)
	movea.l	#ram_CE6E,a2
	clr.w	d2
	bsr.w	sub_1E10E8
	movea.l	(sp)+,a2
	bra.w	loc_1E0FDE
loc_1E0FD6:
	move.w	#$C0,d2
	bsr.w	sub_1E10D2
loc_1E0FDE:
	movea.l	#ram_D1AC,a0
	tst.w	(ram_CF4E).w
	bne.w	loc_1E0FF2
	movea.l	#ram_D1E4,a0
loc_1E0FF2:
	move.w	(ram_D056).w,d3
	tst.w	(ram_CF4E).w
	beq.w	loc_1E1012
	move.l	a2,-(sp)
	movea.l	#ram_CEDE,a2
	clr.w	d2
	bsr.w	sub_1E10E8
	movea.l	(sp)+,a2
	bra.w	loc_1E101A
loc_1E1012:
	move.w	#$F8,d2
	bsr.w	sub_1E10D2
loc_1E101A:
	movea.l	#ram_D174,a0
	movea.l	#ram_D1AC,a1
	movea.l	#ram_D1E4,a2
	tst.w	(ram_CF4E).w
	bne.w	loc_1E1046
	movea.l	#ram_D1AC,a0
	movea.l	#ram_D1E4,a1
	movea.l	#ram_D21C,a2
loc_1E1046:
	move.w	(ram_D056).w,d3
	bra.w	loc_1E1064
loc_1E104E:
	move.w	(a1)+,d0
	sub.w	(a0),d0
	move.w	d0,(a0)+
	move.w	-$2(a1),d1
	beq.w	loc_1E1062
	mulu.w	#$64,d0
	divu.w	d1,d0
loc_1E1062:
	move.w	d0,(a2)+
loc_1E1064:
	dbra	d3,loc_1E104E
loc_1E1068:
	movea.l	#dat_1E10FE,a0
	move.w	(ram_D04C).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	movea.l	#ram_D05C,a1
	move.w	(a1),d0
	add.w	d0,d0
	suba.w	d0,a0
loc_1E1084:
	clr.w	(ram_BF48).w
	clr.w	d0
	move.w	(ram_D056).w,d5
	subq.w	#2,d5
loc_1E1090:
	move.w	d0,d1
	add.w	d1,d1
	move.w	$0(a1,d1.w),d2
	move.w	$2(a1,d1.w),d3
	add.w	d2,d2
	add.w	d3,d3
	move.w	$0(a0,d2.w),d4
	cmp.w	$0(a0,d3.w),d4
	bge.w	loc_1E10C0
	st	(ram_BF48).w
	move.w	$0(a1,d1.w),d2
	move.w	$2(a1,d1.w),d3
	move.w	d2,$2(a1,d1.w)
	move.w	d3,$0(a1,d1.w)
loc_1E10C0:
	addq.w	#1,d0
	dbra	d5,loc_1E1090
	tst.w	(ram_BF48).w
	bne.s	loc_1E1084
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E0EC4, $1E0EF4, $1E0F36, $1E0F48, $1E0F7C, $1E0FDA, $1E1016
sub_1E10D2:
	move.l	a2,-(sp)
	subq.w	#1,d3
	clr.w	d4
loc_1E10D8:
	move.b	$0(a2,d2.w),d4
	addq.w	#1,a2
	move.w	d4,(a0)+
	dbra	d3,loc_1E10D8
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1E0EB6, $1E0EE6, $1E0F6E, $1E0FCC, $1E1008
sub_1E10E8:
	move.l	a2,-(sp)
	subq.w	#1,d3
	clr.w	d4
loc_1E10EE:
	move.w	$0(a2,d2.w),d4
	addq.w	#2,a2
	move.w	d4,(a0)+
	dbra	d3,loc_1E10EE
	movea.l	(sp)+,a2
	rts
dat_1E10FE:
	dc.w	$FFFF,$D094,$FFFF,$D0CC,$FFFF,$D104,$FFFF,$D13C
	dc.w	$FFFF,$D174,$FFFF,$D1AC,$FFFF,$D1E4,$FFFF,$D21C


; ----------------------------------------------------------------------
; called from $1E0698
sub_1E111E:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1E1128:
	dc.w	loc_1E112E-inl_1E1128
	dc.b	$BF,$00,$00,$00
loc_1E112E:
	clr.w	d6
	move.w	#$B,(TextY).w
loc_1E1136:
	clr.w	(ram_D254).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E1156
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E1166
	move.w	#$5,(ram_D254).w
	bra.w	loc_1E1166
loc_1E1156:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E1166
	move.w	#$4,(ram_D254).w
loc_1E1166:
	movea.l	#dat_1E10FE,a5
	move.w	(ram_D254).w,d0
	asl.w	#2,d0
	movea.l	$0(a5,d0.w),a5
	move.w	#$4,(TextX).w
	movea.l	#dat_1D51A8,a1
	jsr	(Text_PrintFont_Worker).l
	move.w	d6,d0
	add.w	(ram_D04E).w,d0
	cmp.w	(ram_D056).w,d0
	blt.w	loc_1E11AC
	move.w	d6,d0
	add.w	(ram_D04E).w,d0
	cmp.w	(ram_D054).w,d0
	bge.w	loc_1E135E
	move.w	d0,(ram_D054).w
	bra.w	loc_1E135E
loc_1E11AC:
	move.w	#$4,(TextX).w
	movea.l	#ram_D05C,a0
	move.w	d6,d0
	add.w	(ram_D04E).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	ext.l	d0
	move.w	d0,-(sp)
	move.w	(ram_D05A).w,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1E11D6
loc_1E11D6:
	jsr	(sub_013C0A).l
	jsr	(Text_PrintFont_Worker).l
	tst.w	(ram_CF4E).w
	bne.w	loc_1E11F8
	cmpi.w	#$5,(ram_D04C).w
	bge.w	loc_1E1218
	bra.w	loc_1E1202
loc_1E11F8:
	cmpi.w	#$4,(ram_D04C).w
	bge.w	loc_1E1218
loc_1E1202:
	move.w	(ram_D05A).w,d7
	btst	#2,(ram_DD9E).w
	beq.w	loc_1E1210
loc_1E1210:
	jsr	(sub_01A20E).l
	sub.w	d0,(sp)
loc_1E1218:
	move.w	#$11,(TextX).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E123A
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E1250
	move.w	#$14,(TextX).w
	bra.w	loc_1E1250
loc_1E123A:
	move.w	#$15,(TextX).w
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E1250
	move.w	#$14,(TextX).w
loc_1E1250:
	move.w	(sp),d0
	bsr.w	sub_1E1372
	beq.w	loc_1E135C
	move.w	#$15,(TextX).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E127C
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E1292
	move.w	#$1A,(TextX).w
	bra.w	loc_1E1292
loc_1E127C:
	move.w	#$19,(TextX).w
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E1292
	move.w	#$1A,(TextX).w
loc_1E1292:
	move.w	(sp),d0
	bsr.w	sub_1E1372
	beq.w	loc_1E135C
	move.w	#$19,(TextX).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E12BE
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E12D4
	move.w	#$20,(TextX).w
	bra.w	loc_1E12D4
loc_1E12BE:
	move.w	#$1D,(TextX).w
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E12D4
	move.w	#$20,(TextX).w
loc_1E12D4:
	move.w	(sp),d0
	bsr.w	sub_1E1372
	beq.w	loc_1E135C
	move.w	#$1D,(TextX).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E1300
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E1316
	move.w	#$0,(TextX).w
	bra.w	loc_1E1316
loc_1E1300:
	move.w	#$21,(TextX).w
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E1316
	move.w	#$0,(TextX).w
loc_1E1316:
	move.w	(sp),d0
	bsr.w	sub_1E1372
	tst.w	(ram_CF4E).w
	bne.w	loc_1E135C
	move.w	#$21,(TextX).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E1346
	cmpi.w	#$5,(ram_D04C).w
	blt.w	loc_1E1356
	move.w	#$0,(TextX).w
	bra.w	loc_1E1356
loc_1E1346:
	cmpi.w	#$4,(ram_D04C).w
	blt.w	loc_1E1356
	move.w	#$0,(TextX).w
loc_1E1356:
	move.w	(sp),d0
	bsr.w	sub_1E1372
loc_1E135C:
	tst.w	(sp)+
loc_1E135E:
	addq.w	#1,(TextY).w
	addq.w	#1,d6
	cmp.w	(ram_D052).w,d6
	blt.w	loc_1E1136
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E1252, $1E1294, $1E12D6, $1E1318, $1E1358
sub_1E1372:
	move.w	d0,-(sp)
	move.w	(ram_D254).w,d0
	asl.w	#2,d0
	movea.l	#dat_1E10FE,a0
	movea.l	$0(a0,d0.w),a0
	move.w	(sp)+,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	move.w	#$3,d1
	tst.w	(ram_CF4E).w
	bne.w	loc_1E13B0
	cmpi.w	#$5,(ram_D254).w
	blt.w	loc_1E13C8
	cmpi.w	#$7,(ram_D254).w
	beq.w	loc_1E13C8
	bra.w	loc_1E13C4
loc_1E13B0:
	cmpi.w	#$4,(ram_D254).w
	blt.w	loc_1E13C8
	cmpi.w	#$6,(ram_D254).w
	beq.w	loc_1E13C8
loc_1E13C4:
	move.w	#$4,d1
loc_1E13C8:
	jsr	(Num_ToDecimal).l
	bsr.w	sub_1E1402
	addq.w	#1,(ram_D254).w
	tst.w	(ram_CF4E).w
	bne.w	loc_1E13F0
	cmpi.w	#$5,(ram_D254).w
	beq.w	loc_1E1400
	cmpi.w	#$8,(ram_D254).w
	rts
loc_1E13F0:
	cmpi.w	#$4,(ram_D254).w
	beq.w	loc_1E1400
	cmpi.w	#$7,(ram_D254).w
loc_1E1400:
	rts


; ----------------------------------------------------------------------
; called from $1E13CE
sub_1E1402:
	move.w	(TextAttr).w,-(sp)
	move.w	(ram_D04C).w,d0
	cmp.w	(ram_D254).w,d0
	bne.w	loc_1E141C
	jsr	(Text_PrintCmd).l
inl_1E1418:
	dc.w	loc_1E141C-inl_1E1418
	dc.b	$FE,$07
loc_1E141C:
	jsr	(Text_PrintFont_Worker).l
	move.w	(sp)+,(TextAttr).w
	rts


; ----------------------------------------------------------------------
; called from $1E1C2E, $1E1C4C, $1E1C6A, $1E1C88
sub_1E1428:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$F45,d0
	moveq	#$70,d1
	movea.l	#ram_D058,a0
	jsr	(SRAM_Read).l
	bsr.w	sub_1E1D24
	bsr.w	sub_1E1EC4
	jsr	(sub_1D02AE).l
	clr.w	(ram_D3E2).w
	move.w	#$1,(ram_D3E0).w
	clr.w	d0
	bsr.w	sub_1E1CEE
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1E1AD6
	bsr.w	sub_1E19BA
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	d4
	bsr.w	sub_1E18C2
	bsr.w	sub_1E191A
	bsr.w	sub_1E196A
	move.w	#$1,(ram_D4A2).w
	bsr.w	sub_1E16D2
	clr.w	d0
	bra.w	loc_1E1640
loc_1E1496:
	bsr.w	sub_1E1A34
	jsr	(Text_Print).l
inl_1E14A0:
	dc.w	loc_1E14A6-inl_1E14A0
	dc.b	$FF,$04,$14,$00
loc_1E14A6:
	tst.w	(ram_D4A2).w
	beq.w	loc_1E14C0
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1E1A62
	bsr.w	sub_1E1890
	bra.w	loc_1E14D0
loc_1E14C0:
	move.w	(ram_D3E0).w,d0
	cmp.w	(ram_D3E2).w,d0
	beq.w	loc_1E14D0
	bsr.w	sub_1E19BA
loc_1E14D0:
	move.w	#$2500,sr
loc_1E14D4:
	move.w	(FrameCounter).w,d0
loc_1E14D8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E14D8
	cmpa.l	#ram_D264,a5
	beq.w	loc_1E1538
	cmpa.l	#ram_D266,a5
	beq.w	loc_1E1524
	cmpa.l	#ram_D268,a5
	beq.w	loc_1E1510
	jsr	(Joypad_Read4).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1E14D4
	bra.w	loc_1E1548
loc_1E1510:
	jsr	(Joypad_Read3).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1E14D4
	bra.w	loc_1E1548
loc_1E1524:
	jsr	(Joypad_Read2).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1E14D4
	bra.w	loc_1E1548
loc_1E1538:
	jsr	(Joypad_Read1).l
	jsr	(Joypad_Repeat).l
	tst.w	d1
	beq.s	loc_1E14D4
loc_1E1548:
	btst	#7,d1
	bne.w	loc_1E16C8
	tst.w	(ram_D4A2).w
	bne.w	loc_1E1582
	move.w	#$1,d0
	btst	#1,d1
	bne.w	loc_1E15CC
	move.w	#$FFFF,d0
	btst	#0,d1
	bne.w	loc_1E15CC
	btst	#4,d1
	beq.w	loc_1E1496
	bsr.w	sub_1E16D2
	clr.w	d0
	bra.w	loc_1E15CC
loc_1E1582:
	moveq	#-$1,d0
	btst	#6,d1
	bne.w	loc_1E1640
	neg.w	d0
	btst	#5,d1
	bne.w	loc_1E1640
	btst	#3,d1
	bne.w	loc_1E166E
	neg.w	d0
	btst	#2,d1
	bne.w	loc_1E166E
	moveq	#$A,d0
	btst	#1,d1
	bne.w	loc_1E166E
	neg.w	d0
	btst	#0,d1
	bne.w	loc_1E166E
	btst	#4,d1
	beq.w	loc_1E1496
	bsr.w	sub_1E16D2
	bra.w	loc_1E1496
loc_1E15CC:
	add.w	d0,(ram_D3E0).w
loc_1E15D0:
	cmpi.w	#$7,(ram_D3E0).w
	ble.w	loc_1E15E0
	move.w	#$1,(ram_D3E0).w
loc_1E15E0:
	tst.w	(ram_D3E0).w
	bne.w	loc_1E15EE
	move.w	#$7,(ram_D3E0).w
loc_1E15EE:
	bsr.w	sub_1E1CEE
	beq.s	loc_1E15D0
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1E1AD6
	tst.w	(ram_D4A2).w
	bne.w	loc_1E1610
	jsr	(sub_1E1836).l
	bra.w	loc_1E1496
loc_1E1610:
	jsr	(Text_PrintFont).l
inl_1E1616:
	dc.w	loc_1E161C-inl_1E1616
	dc.b	$FF,$03,$15,$00
loc_1E161C:
	add.w	d4,(TextX).w
	jsr	(Text_PrintFont).l
inl_1E1626:
	dc.w	loc_1E162C-inl_1E1626
	dc.b	$20,$20,$20,$00
loc_1E162C:
	bsr.w	sub_1E196A
	bsr.w	sub_1E1940
	bsr.w	sub_1E18C2
	move.w	d4,d0
	neg.w	d0
	bra.w	loc_1E1640
loc_1E1640:
	add.w	d4,d0
	cmp.w	#$8,d0	; general form
	bhi.w	loc_1E1496
	move.w	d0,d4
	bsr.w	sub_1E191A
	movea.l	#ram_D3CA,a0
	clr.w	d0
	cmpi.b	#$2D,$0(a0,d4.w)
	beq.w	loc_1E166E
	move.b	$0(a0,d4.w),d0
	ext.w	d0
	bsr.w	sub_1E18F0
	sub.w	d5,d0
loc_1E166E:
	add.w	d5,d0
	cmp.w	#$1D,d0	; general form
	bhi.w	loc_1E1496
	move.w	d0,-(sp)
	bsr.w	sub_1E196A
	bsr.w	sub_1E1940
	move.w	(sp)+,d5
	bsr.w	sub_1E196A
	move.w	(FontTileBase).w,-(sp)
	tst.w	(ram_D4A2).w
	beq.w	loc_1E169E
	jsr	(Text_PrintCmd).l
inl_1E169A:
	dc.w	loc_1E169E-inl_1E169A
	dc.b	$FE,$07
loc_1E169E:
	bsr.w	sub_1E1940
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_PrintCmd).l
inl_1E16AC:
	dc.w	loc_1E16B0-inl_1E16AC
	dc.b	$FE,$00
loc_1E16B0:
	movea.l	#ram_D3CA,a0
	movea.l	#dat_1E1AB6,a1
	move.b	$0(a1,d5.w),d0
	move.b	d0,$0(a0,d4.w)
	bra.w	loc_1E1496
loc_1E16C8:
	bsr.w	sub_1E1B18
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E148C, $1E1578, $1E15C4
sub_1E16D2:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_Print).l
inl_1E16DC:
	dc.w	loc_1E16E2-inl_1E16DC
	dc.b	$8F,$01,$11,$00
loc_1E16E2:
	move.w	#$15,d0
	move.w	#$7,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E16FA:
	dc.w	loc_1E1700-inl_1E16FA
	dc.b	$8F,$17,$0D,$00
loc_1E1700:
	move.w	#$10,d0
	move.w	#$B,d1
	move.w	#$273F,d2
	jsr	(Text_FillRect).l
	bchg	#0,(ram_D4A3).w
	bne.w	loc_1E17EA
	jsr	(Text_Print).l
inl_1E1722:
	dc.w	loc_1E1728-inl_1E1722
	dc.b	$FF,$1A,$0F,$00
loc_1E1728:
	movea.l	#dat_1E1AB6,a0
	moveq	#$2,d0
loc_1E1730:
	moveq	#$9,d1
	movea.l	#ram_BFF4,a1
	move.w	#$C,(a1)+
loc_1E173C:
	move.b	(a0)+,(a1)+
	dbra	d1,loc_1E173C
	movea.w	#$BFF4,a1
	jsr	(Text_PrintFont_Worker).l
	addq.w	#1,(TextY).w
	subi.w	#$A,(TextX).w
	dbra	d0,loc_1E1730
	jsr	(Text_PrintFont).l
inl_1E1760:
	dc.w	loc_1E1774-inl_1E1760
	dc.b	$FF,$17,$13
	dc.b	"{}[]=new letter"
loc_1E1774:
	move.w	#$17,(TextX).w
	addq.w	#1,(TextY).w
	move.w	(TextX).w,-(sp)
	jsr	(Text_PrintFont).l
inl_1E1788:
	dc.w	loc_1E1798-inl_1E1788
	dc.b	"C=enter letter"
loc_1E1798:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_PrintFont).l
inl_1E17A6:
	dc.w	loc_1E17B2-inl_1E17A6
	dc.b	"A=go back",0
loc_1E17B2:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_PrintFont).l
inl_1E17C0:
	dc.w	loc_1E17CA-inl_1E17C0
	dc.b	"B=cancel"
loc_1E17CA:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_PrintFont).l
inl_1E17D8:
	dc.w	loc_1E17E4-inl_1E17D8
	dc.b	"START=done"
loc_1E17E4:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_1E17EA:
	movea.l	#ram_D3CA,a1
	bsr.w	sub_1E1AD6
	jsr	(Text_Print).l
inl_1E17FA:
	dc.w	loc_1E1800-inl_1E17FA
	dc.b	$BF,$01,$11,$00
loc_1E1800:
	move.w	#$15,d0
	move.w	#$7,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E1818:
	dc.w	loc_1E181E-inl_1E1818
	dc.b	$BF,$1A,$0F,$00
loc_1E181E:
	move.w	#$A,d0
	move.w	#$3,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	bsr.w	sub_1E1836
	bra.s	loc_1E17E4


; ----------------------------------------------------------------------
; called from $1E1606, $1E1830
sub_1E1836:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(Text_PrintFont).l
inl_1E1840:
	dc.w	loc_1E1854-inl_1E1840
	dc.b	$FF,$03,$13
	dc.b	"{}=select name",0
loc_1E1854:
	jsr	(Text_PrintFont).l
inl_1E185A:
	dc.w	loc_1E1870-inl_1E185A
	dc.b	$FF,$03,$14
	dc.b	"b=enter/edit name"
loc_1E1870:
	jsr	(Text_PrintFont).l
inl_1E1876:
	dc.w	loc_1E188A-inl_1E1876
	dc.b	$FF,$03,$15
	dc.b	"start=use name",0
loc_1E188A:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E14B8
sub_1E1890:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D3E0).w,d0
	mulu.w	#$A,d0
	movea.l	#ram_D34A,a0
	movea.l	#dat_1E198A,a1
	tst.b	$0(a0,d0.w)
	beq.w	loc_1E18B6
	movea.l	#dat_1E19A2,a1
loc_1E18B6:
	jsr	(Text_PrintFont_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E147A, $1E1634
sub_1E18C2:
	movem.l	d0-d4/a0-a6,-(sp)
	move.b	(ram_D3CA).w,d0
	bsr.w	sub_1E18F0
	cmp.w	#$1E,d0	; general form
	blt.w	loc_1E18DC
	clr.w	d5
	bra.w	loc_1E18EA
loc_1E18DC:
	move.w	d0,d5
	movea.l	#dat_1E1AB6,a0
	move.b	$0(a0,d5.w),(ram_D3CA).w
loc_1E18EA:
	movem.l	(sp)+,d0-d4/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E1668, $1E18CA
sub_1E18F0:
	movem.l	d1-d3/a0-a6,-(sp)
	movea.l	#dat_1E1AB6,a0
	move.b	d0,d1
	clr.w	d0
	move.w	#$1E,d3
loc_1E1902:
	cmp.b	$0(a0,d0.w),d1
	beq.w	loc_1E1914
	addq.w	#1,d0
	dbra	d3,loc_1E1902
	move.w	#$1E,d0
loc_1E1914:
	movem.l	(sp)+,d1-d3/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E147E, $1E164C
sub_1E191A:
	jsr	(Text_Print).l
inl_1E1920:
	dc.w	loc_1E1926-inl_1E1920
	dc.b	$FF,$03,$15,$00
loc_1E1926:
	add.w	d4,(TextX).w
	tst.w	(ram_D4A2).w
	beq.w	loc_1E193E
	jsr	(Text_PrintFont).l
inl_1E1938:
	dc.w	loc_1E193E-inl_1E1938
	dc.b	$20,$3C,$20,$00
loc_1E193E:
	rts


; ----------------------------------------------------------------------
; called from $1E1630, $1E167E, $1E169E
sub_1E1940:
	tst.w	(ram_D4A2).w
	beq.s	loc_1E193E
	movea.l	#ram_D14C,a1
	move.w	#$4,(a1)
	move.b	#$0,$3(a1)
	movea.l	#dat_1E1AB6,a0
	move.b	$0(a0,d5.w),d0
	move.b	d0,$2(a1)
	jmp	(Text_PrintFont_Worker).l


; ----------------------------------------------------------------------
; called from $1E1482, $1E162C, $1E167A, $1E1684
sub_1E196A:
	jsr	(Text_Print).l
inl_1E1970:
	dc.w	loc_1E1976-inl_1E1970
	dc.b	$FF,$1A,$0F,$00
loc_1E1976:
	move.w	d5,d0
	ext.l	d0
	divu.w	#$A,d0
	add.w	d0,(TextY).w
	swap	d0
	add.w	d0,(TextX).w
	rts
dat_1E198A:
	dc.b	$00,$18,$FF,$01,$12
	dc.b	"  Enter new name: ",0
dat_1E19A2:
	dc.b	$00,$18,$FF,$01,$12
	dc.b	"Select or replace:",0


; ----------------------------------------------------------------------
; called from $1E1468, $1E14CC
sub_1E19BA:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(ram_D3DE).w,-(sp)
	move.w	(ram_D3E0).w,-(sp)
	move.w	(ram_D3E0).w,d6
	jsr	(Text_PrintFont).l
inl_1E19D0:
	dc.w	loc_1E19D6-inl_1E19D0
	dc.b	$FF,$01,$0A,$00
loc_1E19D6:
	move.w	#$6,d7
	move.w	#$1,(ram_D3E0).w
	movea.l	#ram_BF56,a1
loc_1E19E6:
	bsr.w	sub_1E1AD6
	move.w	(TextX).w,-(sp)
	move.w	(FontTileBase).w,-(sp)
	cmp.w	(ram_D3E0).w,d6
	bne.w	loc_1E1A04
	jsr	(Text_PrintCmd).l
inl_1E1A00:
	dc.w	loc_1E1A04-inl_1E1A00
	dc.b	$FE,$07
loc_1E1A04:
	bsr.w	sub_1E1A62
	move.w	(sp)+,(FontTileBase).w
	jsr	(Text_PrintCmd).l
inl_1E1A12:
	dc.w	loc_1E1A16-inl_1E1A12
	dc.b	$FE,$00
loc_1E1A16:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	addq.w	#1,(ram_D3E0).w
	dbra	d7,loc_1E19E6
	move.w	(sp)+,(ram_D3E0).w
	move.w	(sp)+,(ram_D3DE).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E1496
sub_1E1A34:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$9,d3
	movea.l	#ram_D3CA,a0
	clr.w	(ram_D3DE).w
loc_1E1A46:
	cmpi.b	#$2D,(a0)
	beq.w	loc_1E1A5C
	tst.b	(a0)+
	beq.w	loc_1E1A5C
	addq.w	#1,(ram_D3DE).w
	dbra	d3,loc_1E1A46
loc_1E1A5C:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E14B4, $1E1A04
sub_1E1A62:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D14C,a0
	move.w	(ram_D3DE).w,d0
	move.w	#$0,d3
	move.w	#$C,(a0)+
loc_1E1A78:
	move.b	$0(a1,d3.w),d1
	cmp.w	(ram_D3DE).w,d3
	blt.w	loc_1E1A94
	move.b	#$2D,d1
	cmp.w	#$9,d3	; general form
	bne.w	loc_1E1A94
	move.b	#$20,d1
loc_1E1A94:
	move.b	d1,(a0)+
	addq.w	#1,d3
	cmp.w	#$9,d3	; general form
	blt.s	loc_1E1A78
	movea.l	#ram_D14C,a1
	move.b	#$20,$B(a1)
	jsr	(Text_PrintFont_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1E1AB6:
	dc.b	"ABCDEFGHIJKLMNOPQRSTUVWXYZ.12 -"
	dc.b	$FF


; ----------------------------------------------------------------------
; called from $1D1CBA, $1E1464, $1E15FA, $1E17F0, $1E19E6
sub_1E1AD6:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D34A,a0
	move.w	(ram_D3E0).w,d2
	mulu.w	#$A,d2
	move.w	#$0,(ram_D3DE).w
	move.w	#$9,d3
loc_1E1AF2:
	move.b	$0(a0,d2.w),d0
	beq.w	loc_1E1AFE
	bra.w	loc_1E1B06
loc_1E1AFE:
	move.b	#$2D,d0
	subq.w	#1,(ram_D3DE).w
loc_1E1B06:
	move.b	d0,(a1)+
	addq.w	#1,(ram_D3DE).w
	addq.w	#1,d2
	dbra	d3,loc_1E1AF2
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E16C8
sub_1E1B18:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D34A,a0
	move.w	(ram_D3E0).w,d0
	mulu.w	#$A,d0
	adda.w	d0,a0
	movea.l	#ram_D3CA,a1
	move.w	#$9,d4
loc_1E1B36:
	cmpi.b	#$2D,(a1)
	bne.w	loc_1E1B42
	move.b	#$0,(a1)
loc_1E1B42:
	move.b	(a1)+,d1
	cmp.b	(a0)+,d1
	bne.w	loc_1E1B52
	dbra	d4,loc_1E1B36
	bra.w	loc_1E1B92
loc_1E1B52:
	movea.l	#ram_D34A,a0
	move.w	(ram_D3E0).w,d0
	mulu.w	#$A,d0
	adda.w	d0,a0
	movea.l	#ram_D3CA,a1
	move.w	#$9,d4
loc_1E1B6C:
	move.b	(a1)+,d1
	cmp.b	#$2D,d1	; general form
	bne.w	loc_1E1B7A
	move.b	#$0,d1
loc_1E1B7A:
	move.b	d1,(a0)+
	dbra	d4,loc_1E1B6C
	jsr	(sub_1D02A4).l
	jsr	(sub_1E1BBC).l
	jsr	(SRAM_UpdateChecksum).l
loc_1E1B92:
	movea.l	#ram_D264,a5
	tst.w	(ram_D3E4).w
	beq.w	loc_1E1BA6
	movea.l	#ram_D266,a5
loc_1E1BA6:
	tst.b	(ram_D3CA).w
	bne.w	loc_1E1BB2
	clr.w	(ram_D3E0).w
loc_1E1BB2:
	move.w	(ram_D3E0).w,(a5)
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E1B86
sub_1E1BBC:
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#$F35,d0
	move.w	(ram_D3E0).w,d3
	asl.w	#4,d3
	ext.l	d3
	add.l	d3,d0
	moveq	#$10,d1
	movea.l	#ram_D14C,a0
	jsr	(SRAM_Read).l
	move.l	a0,-(sp)
	move.w	#$F,d3
loc_1E1BE4:
	clr.b	(a0)+
	dbra	d3,loc_1E1BE4
	movea.l	(sp)+,a0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $026FC8
sub_1E1BFE:
	tst.w	(ram_D27C).w
	bne.w	loc_1E1CC0
	clr.w	(ram_D264).w
	clr.w	(ram_D266).w
	clr.w	(ram_D268).w
	clr.w	(ram_D26A).w
	tst.w	(ram_C394).w
	beq.w	loc_1E1C34
	move.w	(ram_C394).w,(ram_D3E4).w
	subq.w	#1,(ram_D3E4).w
	movea.l	#ram_D264,a5
	jsr	(sub_1E1428).l
loc_1E1C34:
	tst.w	(ram_C396).w
	beq.w	loc_1E1C52
	move.w	(ram_C396).w,(ram_D3E4).w
	subq.w	#1,(ram_D3E4).w
	movea.l	#ram_D266,a5
	jsr	(sub_1E1428).l
loc_1E1C52:
	tst.w	(ram_C398).w
	beq.w	loc_1E1C70
	move.w	(ram_C398).w,(ram_D3E4).w
	subq.w	#1,(ram_D3E4).w
	movea.l	#ram_D268,a5
	jsr	(sub_1E1428).l
loc_1E1C70:
	tst.w	(ram_C39A).w
	beq.w	loc_1E1C8E
	move.w	(ram_C39A).w,(ram_D3E4).w
	subq.w	#1,(ram_D3E4).w
	movea.l	#ram_D26A,a5
	jsr	(sub_1E1428).l
loc_1E1C8E:
	bset	#0,(ram_C354).w
	move.w	#$1,d0
	bsr.w	sub_1E1CC2
	cmp.w	#$1,d2	; general form
	ble.w	loc_1E1CAA
	bclr	#0,(ram_C354).w
loc_1E1CAA:
	move.w	#$2,d0
	bsr.w	sub_1E1CC2
	cmp.w	#$1,d2	; general form
	ble.w	loc_1E1CC0
	bclr	#0,(ram_C354).w
loc_1E1CC0:
	rts


; ----------------------------------------------------------------------
; called from $1E1C98, $1E1CAE
sub_1E1CC2:
	clr.w	d2
	cmp.w	(ram_C394).w,d0
	bne.w	loc_1E1CCE
	addq.w	#1,d2
loc_1E1CCE:
	cmp.w	(ram_C396).w,d0
	bne.w	loc_1E1CD8
	addq.w	#1,d2
loc_1E1CD8:
	cmp.w	(ram_C398).w,d0
	bne.w	loc_1E1CE2
	addq.w	#1,d2
loc_1E1CE2:
	cmp.w	(ram_C39A).w,d0
	bne.w	loc_1E1CEC
	addq.w	#1,d2
loc_1E1CEC:
	rts


; ----------------------------------------------------------------------
; called from $1E145A, $1E15EE
sub_1E1CEE:
	movem.w	d0,-(sp)
	move.w	(ram_D266).w,d0
	tst.w	(ram_D3E4).w
	beq.w	loc_1E1D02
	move.w	(ram_D264).w,d0
loc_1E1D02:
	cmp.w	(ram_D3E0).w,d0
	bne.w	loc_1E1D1E
	move.w	#$1,d0
	tst.w	(sp)
	bpl.w	loc_1E1D18
	move.w	#$FFFF,d0
loc_1E1D18:
	add.w	d0,(ram_D3E0).w
	clr.w	d0
loc_1E1D1E:
	movem.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $1E1440
sub_1E1D24:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
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
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E1DA2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E1DAA:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B018).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E1DC2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E1DCA:
	bset	#2,(ram_C356).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	jsr	(Text_PrintCmd).l
inl_1E1DE6:
	dc.w	loc_1E1DEE-inl_1E1DE6
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E1DEE:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_PrintBig).l
inl_1E1E02:
	dc.w	loc_1E1E12-inl_1E1E02
	dc.b	$BF,$0B,$01
	dc.b	"USER ENTRY",0
loc_1E1E12:
	jsr	(Text_PrintFont).l
inl_1E1E18:
	dc.w	loc_1E1E1E-inl_1E1E18
	dc.b	$FE,$00,$00,$00
loc_1E1E1E:
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
	movea.l	a5,a0
	suba.w	#$D264,a0
	move.l	a0,d0
	movea.l	#ptrs_1E1EB4,a0
	add.w	d0,d0
	movea.l	$0(a0,d0.w),a0
	jsr	(Text_Print).l
inl_1E1E56:
	dc.w	loc_1E1E5C-inl_1E1E56
	dc.b	$BF,$1A,$09,$00
loc_1E1E5C:
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$A,d2
	moveq	#$4,d3
	moveq	#$2,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E1E7A:
	dc.w	loc_1E1E80-inl_1E1E7A
	dc.b	$BF,$17,$05,$00
loc_1E1E80:
	move.w	(ram_C3AC).w,d7
	tst.w	(ram_D3E4).w
	beq.w	loc_1E1E90
	move.w	(ram_C3AE).w,d7
loc_1E1E90:
	jsr	(sub_016EB8).l
	jsr	(Text_PrintNarrow).l
inl_1E1E9C:
	dc.w	loc_1E1EB2-inl_1E1E9C
	dc.b	$F8,$04,$01,$04,$05
	dc.b	"name"
	dc.b	$FD,$0C
	dc.b	"w   l   t"
loc_1E1EB2:
	rts

ptrs_1E1EB4:
	dc.l	Art_1B3486
	dc.l	Art_1B3A24
	dc.l	Art_1B3FC2
	dc.l	Art_1B4560


; ----------------------------------------------------------------------
; called from $1E1444
sub_1E1EC4:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_D058,a0
	move.w	#$6,d7
	jsr	(Text_Print).l
inl_1E1ED8:
	dc.w	loc_1E1EDE-inl_1E1ED8
	dc.b	$FF,$0B,$0A,$00
loc_1E1EDE:
	move.w	$8(a0),d0
loc_1E1EE2:
	cmp.w	#$3E8,d0	; general form
	blt.w	loc_1E1EF0
	subi.w	#$3E8,d0
	bra.s	loc_1E1EE2
loc_1E1EF0:
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	move.w	#$B,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	move.w	$C(a0),d0
loc_1E1F0A:
	cmp.w	#$3E8,d0	; general form
	blt.w	loc_1E1F18
	subi.w	#$3E8,d0
	bra.s	loc_1E1F0A
loc_1E1F18:
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	move.w	#$13,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	move.w	$A(a0),d0
	sub.w	$C(a0),d0
	sub.w	$8(a0),d0
	bpl.w	loc_1E1F40
	clr.w	d0
loc_1E1F40:
	cmp.w	#$3E8,d0	; general form
	blt.w	loc_1E1F4E
	subi.w	#$3E8,d0
	bra.s	loc_1E1F40
loc_1E1F4E:
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	move.w	#$F,(TextX).w
	jsr	(Text_PrintFont_Worker).l
	adda.w	#$10,a0
	addq.w	#1,(TextY).w
	dbra	d7,loc_1E1EDE
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $026CD6, $026FCE, $027034
sub_1E1F76:
	tst.w	(ram_D270).w
	beq.w	loc_1E248A
	clr.w	(ram_DEA4).w
	clr.w	(ram_BF48).w
	move.w	#$FFFF,(ram_BF4A).w
	move.w	#$1,(ram_BF4C).w
	clr.w	(ram_BF52).w
	clr.w	(ram_BF4E).w
	clr.w	(ram_BF80).w
	btst	#7,(SysFlags).w
	beq.w	loc_1E1FEC
	cmpi.w	#$4,(ram_CFD6).w
	bne.w	loc_1E1FEC
	btst	#3,(ram_DD9E).w
	beq.w	loc_1E1FD4
	move.b	(ram_CFFA).w,d0
	move.b	(ram_CFFB).w,d1
	move.b	d0,d2
	cmp.b	(ram_DDA2).w,d2
	beq.w	loc_1E1FE8
	move.b	d1,d2
	bra.w	loc_1E1FE8
loc_1E1FD4:
	move.b	(ram_CFFA).w,d0
	move.b	(ram_CFFB).w,d1
	move.b	d0,d2
	cmp.b	(ram_DDA2).w,d2
	bne.w	loc_1E1FE8
	move.b	d1,d2
loc_1E1FE8:
	move.b	d2,(ram_CFFC).w
loc_1E1FEC:
	jsr	(sub_01FFA2).l
	move.l	#sub_016614,(ram_DDD0).w
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	clr.w	d0
	move.w	d0,(a0)
	move.w	d0,$2(a0)
	move.l	#sub_1E24E0,(VBlankVector).l
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$BC00,(HScrollTableAddr).w
	move.w	#$B000,(PlaneBAddr).w
	move.w	#$6,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$7,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$7,(PlaneSize).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	bclr	#5,(VideoFlags).w
	jsr	(Text_Print).l
inl_1E2062:
	dc.w	loc_1E2068-inl_1E2062
	dc.b	$FF,$00,$00,$00
loc_1E2068:
	move.l	#$80,d0
	moveq	#$1C,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	move.w	#$2,d4
	move.w	#$19,d1
	clr.w	d2
	movea.l	#ram_D058,a0
	movea.l	#TeamArtTable,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E209E
	movea.l	#dat_017022,a1
loc_1E209E:
	move.w	d4,(a0)+
	move.w	d2,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a2
	addq.w	#8,a2
	jsr	(sub_020780).l
	addq.w	#1,d2
	dbra	d1,loc_1E209E
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E20C6:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E20CE:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_BF7E).w
	suba.l	#$22,sp
	movea.l	sp,a0
	move.w	#$1,(a0)+
	move.w	#$7,d0
loc_1E20EA:
	move.l	#$FFFFFFFF,(a0)+
	dbra	d0,loc_1E20EA
	movea.l	sp,a2
	jsr	(sub_020780).l
	adda.l	#$22,sp
	move.w	d4,(ram_BF58).w
	jsr	(Text_Print).l
inl_1E210C:
	dc.w	loc_1E2112-inl_1E210C
	dc.b	$BF,$01,$00,$00
loc_1E2112:
	movea.l	#Art_1BB268,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$9,d5
	jsr	(TileMap_Draw).l
	move.w	d4,(ram_B03C).w
	movea.l	#Art_1C10E4_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_BF56).w
	jsr	(Text_Print).l
inl_1E214C:
	dc.w	loc_1E2152-inl_1E214C
	dc.b	$FE,$00,$00,$00
loc_1E2152:
	movea.l	#Art_PlayoffBackground,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	move.w	(a1),d2
	clr.w	d0
	clr.w	d1
	move.w	$2(a1),d3
	moveq	#$6,d5
	jsr	(TileMap_Draw).l
	move.w	(ram_BDAE).w,(PaletteBuffer).w
	movea.l	#VDP_CTRL,a0
	move.w	#$9200,(a0)
	movea.l	#ram_CFDE,a1
	movea.l	#dat_1E2B14,a0
	move.w	(ram_CFD6).w,d0
	asl.w	#1,d0
	adda.w	$0(a0,d0.w),a0
	clr.w	d4
	move.b	(a0)+,d4
loc_1E219C:
	jsr	(Text_Print).l
inl_1E21A2:
	dc.w	loc_1E21A8-inl_1E21A2
	dc.b	$8F,$00,$00,$00
loc_1E21A8:
	move.b	(a0)+,(ram_B043).w
	move.b	(a0)+,(ram_B045).w
	clr.w	d1
	move.b	(a1)+,d1
	add.w	d1,d1
	bsr.w	sub_1E251C
	dbra	d4,loc_1E219C
	clr.w	d4
	move.b	(a0)+,d4
loc_1E21C2:
	jsr	(Text_Print).l
inl_1E21C8:
	dc.w	loc_1E21CE-inl_1E21C8
	dc.b	$BF,$00,$02,$00
loc_1E21CE:
	move.b	(a0)+,(ram_B043).w
	clr.w	d0
	move.b	(a0)+,d0
	bsr.w	sub_1E24DE
	dbra	d4,loc_1E21C2
	jsr	(Text_Print).l
inl_1E21E4:
	dc.w	loc_1E21EA-inl_1E21E4
	dc.b	$BF,$00,$00,$00
loc_1E21EA:
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_1E2214
	clr.w	d4
	move.b	(a0)+,d4
	bmi.w	loc_1E2214
	movea.w	#$CF50,a2
loc_1E2200:
	move.b	(a0)+,(ram_B043).w
	move.b	(a0)+,(ram_B045).w
	bsr.w	sub_1E24B2
	adda.w	#$10,a2
	dbra	d4,loc_1E2200
loc_1E2214:
	tst.w	(ram_CFD6).w
	beq.w	loc_1E221C
loc_1E221C:
	move.w	#$18,(FadeCounter).w
	movem.l	d0/a0,-(sp)
	movea.l	#dat_1E2C88,a0
	move.w	(ram_CFD6).w,d0
	add.w	d0,d0
	move.w	$0(a0,d0.w),d0
	cmpi.w	#$3C,(ram_D4A6).w
	blt.w	loc_1E2242
	neg.w	d0
loc_1E2242:
	move.w	d0,(ram_D04C).w
	movem.l	(sp)+,d0/a0
	move.w	#$2500,sr
	clr.w	d0
	clr.w	d4
	clr.w	(ram_D050).w
	bsr.w	sub_1E23D4
	move.w	#$2D,(ram_BF4C).w
loc_1E2260:
	bsr.w	sub_1E248C
	movea.l	#NullSub,a0
	bsr.w	sub_1E2270
	bra.s	loc_1E2260


; ----------------------------------------------------------------------
; called from $1E226A
sub_1E2270:
	bsr.w	sub_1E2616
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	btst	#7,d1
	bne.w	loc_1E2466
	btst	#3,d3
	beq.w	loc_1E229A
	move.w	#$FFFC,(ram_D050).w
	bra.w	sub_1E23D4
loc_1E229A:
	btst	#2,d3
	beq.w	loc_1E22AC
	move.w	#$4,(ram_D050).w
	bra.w	sub_1E23D4
loc_1E22AC:
	btst	#7,(ram_C35C).w
	beq.w	sub_1E23D4
	btst	#6,d1
	beq.w	loc_1E2328
	bsr.w	sub_1E2606
	add.w	(ram_BF48).w,d0
	lea	(ram_CFFE).w,a1
	move.b	$0(a1,d0.w),d1
	subq.b	#1,d1
	bge.w	loc_1E22D8
	move.w	#$19,d1
loc_1E22D8:
	move.b	d1,$0(a1,d0.w)
	cmpi.w	#$1E,(ram_BF4C).w
	ble.w	loc_1E22F6
	jsr	(Text_Print).l
inl_1E22EC:
	dc.w	loc_1E22F2-inl_1E22EC
	dc.b	$FF,$00,$00,$00
loc_1E22F2:
	bra.w	loc_1E2302
loc_1E22F6:
	jsr	(Text_Print).l
inl_1E22FC:
	dc.w	loc_1E2302-inl_1E22FC
	dc.b	$8F,$00,$00,$00
loc_1E2302:
	lea	(dat_1E2B14).l,a1
	move.w	(a1),d2
	lea	$1(a1,d2.w),a1
	lsl.w	#1,d1
	lsl.w	#1,d0
	move.b	$0(a1,d0.w),(ram_B043).w
	move.b	$1(a1,d0.w),(ram_B045).w
	jsr	(sub_1E251C).l
	bra.w	sub_1E23D4
loc_1E2328:
	btst	#5,d1
	beq.w	loc_1E239C
	bsr.w	sub_1E2606
	add.w	(ram_BF48).w,d0
	lea	(ram_CFFE).w,a1
	move.b	$0(a1,d0.w),d1
	addq.b	#1,d1
	cmp.w	#$1A,d1	; general form
	blt.w	loc_1E234C
	clr.w	d1
loc_1E234C:
	move.b	d1,$0(a1,d0.w)
	cmpi.w	#$1E,(ram_BF4C).w
	ble.w	loc_1E236A
	jsr	(Text_Print).l
inl_1E2360:
	dc.w	loc_1E2366-inl_1E2360
	dc.b	$FF,$00,$00,$00
loc_1E2366:
	bra.w	loc_1E2376
loc_1E236A:
	jsr	(Text_Print).l
inl_1E2370:
	dc.w	loc_1E2376-inl_1E2370
	dc.b	$8F,$00,$00,$00
loc_1E2376:
	lea	(dat_1E2B14).l,a1
	move.w	(a1),d2
	lea	$1(a1,d2.w),a1
	lsl.w	#1,d1
	lsl.w	#1,d0
	move.b	$0(a1,d0.w),(ram_B043).w
	move.b	$1(a1,d0.w),(ram_B045).w
	jsr	(sub_1E251C).l
	bra.w	sub_1E23D4
loc_1E239C:
	btst	#0,d1
	beq.w	loc_1E23B4
	tst.w	(ram_BF48).w
	beq.w	sub_1E23D4
	subq.w	#1,(ram_BF48).w
	bra.w	sub_1E23D4
loc_1E23B4:
	btst	#1,d1
	beq.w	sub_1E23D4
	cmpi.w	#$7,(ram_BF48).w
	beq.w	sub_1E23D4
	addq.w	#1,(ram_BF48).w
	move.w	#$1,(ram_BF52).w
	bra.w	sub_1E23D4


; ----------------------------------------------------------------------
; called from $1E2256, $1E2296, $1E22A8, $1E22B2, $1E2324, $1E2398, $1E23A8, $1E23B0 (+3 more)
sub_1E23D4:
	move.w	(ram_D050).w,d0
	beq.w	loc_1E248A
	add.w	(ram_D04C).w,d0
	move.w	(ram_CFD6).w,d1
	cmp.w	#$3,d1	; general form
	bls.w	loc_1E23EE
	moveq	#$3,d1
loc_1E23EE:
	move.w	#$3,d1
	movem.l	a0,-(sp)
	movea.l	#dat_1E2C7E,a0
	add.w	d1,d1
	move.w	$0(a0,d1.w),d1
	move.w	d1,(ram_DDCE).w
	movem.l	(sp)+,a0
	cmp.w	d1,d0
	bgt.w	loc_1E248A
	neg.w	d1
	cmp.w	d1,d0
	blt.w	loc_1E248A
	move.w	d0,(ram_D04C).w
	clr.w	(ram_B8C6).w
	move.w	d0,d1
	addi.w	#$100,d1
	cmp.w	#$40,d1	; general form
	blt.w	loc_1E243A
	cmp.w	#$200,d1	; general form
	bgt.w	loc_1E243A
	move.w	d1,(ram_B8C6).w
loc_1E243A:
	ext.l	d0
	movea.l	#dat_1E2C7E,a0
loc_1E2442:
	move.w	(a0)+,d0
	cmp.w	(ram_D04C).w,d0
	beq.w	loc_1E2460
	neg.w	d0
	cmp.w	(ram_D04C).w,d0
	beq.w	loc_1E2460
	cmpa.l	#dat_1E2C86,a0
	blt.s	loc_1E2442
	rts
loc_1E2460:
	clr.w	(ram_D050).w
	rts
loc_1E2466:
	btst	#7,(ram_C35C).w
	beq.w	loc_1E2482
	jsr	(sub_1E2AA2).l
	btst	#7,(ram_C35C).w
	beq.w	loc_1E2482
	rts
loc_1E2482:
	jsr	(sub_01FFA2).l
	addq.w	#4,sp
loc_1E248A:
	rts


; ----------------------------------------------------------------------
; called from $1E2260
sub_1E248C:
	tst.w	(FadeCounter).w
	bpl.w	loc_1E24A2
	movem.l	d0/a0,-(sp)
	movem.l	(sp)+,d0/a0
	move.w	#$3,(FadeCounter).w
loc_1E24A2:
	move.w	(FrameCounter).w,d0
	cmp.w	(ram_B056).w,d0
	beq.s	loc_1E24A2
	move.w	d0,(ram_B056).w
	rts


; ----------------------------------------------------------------------
; called from $1E2208
sub_1E24B2:
	movea.w	#$BFF4,a1
	move.w	#$6,(a1)+
	move.w	$4(a2),d0
	addi.w	#$30,d0
	move.b	d0,(a1)+
	move.b	#$2D,(a1)+
	move.w	$6(a2),d0
	addi.w	#$30,d0
	move.b	d0,(a1)+
	clr.b	(a1)+
	movea.w	#$BFF4,a1
	jmp	(Text_PrintFont_Worker).l


; ----------------------------------------------------------------------
; called from $1E21D6
sub_1E24DE:
	rts


; ----------------------------------------------------------------------
; called from $1E200C
sub_1E24E0:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_1E250C
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$FEC0,d0
	add.w	(ram_D04C).w,d0
	move.w	d0,(a0)
	move.w	d0,$2(a0)
	jsr	(Palette_FadeStep).l
loc_1E250C:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $1E21B6, $1E231E, $1E2392, $1E2678, $1E26DA, $1E271A, $1E2A70
sub_1E251C:
	movem.l	d0-d7/a0-a3,-(sp)
	movea.l	#ram_CFDE,a0
	move.w	(ram_CFD8).w,d0
	move.b	$0(a0,d0.w),d0
	add.b	d0,d0
	cmp.b	d0,d1
	bne.w	loc_1E25BC
	tst.w	(ram_DEA4).w
	bne.w	loc_1E25BC
	move.w	(TextX).w,(ram_D4A6).w
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	(TextX).w,-(sp)
	move.w	(TextY).w,-(sp)
	move.w	(TextAttr).w,-(sp)
	move.w	(TextPlaneOffset).w,-(sp)
	move.w	(TextX).w,(ram_BF4E).w
	move.w	(TextY).w,(ram_BF50).w
	ori.w	#$8000,(ram_BF4E).w
	move.w	(ram_B03C).w,d4
	jsr	(Text_PrintCmd).l
inl_1E2574:
	dc.w	loc_1E257A-inl_1E2574
	dc.b	$FE,$03,$FF,$02
loc_1E257A:
	movea.l	#Art_1C10E4,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	movea.l	#NullEntry,a2
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	clr.w	d5
	jsr	(TileMap_Draw).l
	st	(ram_DEA4).w
	move.w	(sp)+,(TextPlaneOffset).w
	move.w	(sp)+,(TextAttr).w
	move.w	(sp)+,(TextY).w
	move.w	(sp)+,(TextX).w
	movem.l	(sp)+,d0-d7/a0-a6
	bra.w	loc_1E25BC
loc_1E25BC:
	movea.l	#ram_D058,a0
	move.w	$0(a0,d1.w),d4
	add.w	d1,d1
	movea.l	#TeamArtTable,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1E25DC
	movea.l	#dat_017022,a0
loc_1E25DC:
	movea.l	$0(a0,d1.w),a0
	asr.w	#1,d1
	movea.l	a0,a1
	adda.l	(a0),a0
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	moveq	#$2,d3
	move.w	#$0,d5
	jsr	(TileMap_Draw).l
	movem.l	(sp)+,d0-d7/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $1E22BE, $1E2330, $1E2620, $1E2A26
sub_1E2606:
	clr.w	d0
	tst.w	(ram_D04C).w
	bge.w	loc_1E2614
	move.w	#$8,d0
loc_1E2614:
	rts


; ----------------------------------------------------------------------
; called from $1E2270
sub_1E2616:
	btst	#7,(ram_C35C).w
	beq.w	loc_1E2724
	jsr	(sub_1E2606).l
	add.w	(ram_BF48).w,d0
	cmp.w	(ram_BF4A).w,d0
	beq.w	loc_1E268C
	move.w	d0,-(sp)
	jsr	(Text_Print).l
inl_1E263A:
	dc.w	loc_1E2640-inl_1E263A
	dc.b	$8F,$00,$00,$00
loc_1E2640:
	move.w	(sp)+,d0
	move.w	(ram_BF4A).w,d4
	blt.w	loc_1E268C
	lsl.w	#1,d4
	lea	(dat_1E2B14).l,a0
	move.w	(a0),d2
	lea	$1(a0,d2.w),a0
	move.b	$0(a0,d4.w),d1
	move.b	$1(a0,d4.w),d2
	move.b	d1,(ram_B043).w
	move.b	d2,(ram_B045).w
	lea	(ram_CFFE).w,a0
	lsr.w	#1,d4
	move.b	$0(a0,d4.w),d1
	ext.w	d1
	lsl.w	#1,d1
	move.w	d0,-(sp)
	bsr.w	sub_1E251C
	move.w	(sp)+,d0
	move.w	d0,(ram_BF4A).w
	cmpi.w	#$1E,(ram_BF4C).w
	bra.w	loc_1E26E2
loc_1E268C:
	move.w	d0,(ram_BF4A).w
	subq.w	#1,(ram_BF4C).w
	beq.w	loc_1E26E2
	cmpi.w	#$1E,(ram_BF4C).w
	bne.w	loc_1E2724
	jsr	(Text_Print).l
inl_1E26A8:
	dc.w	loc_1E26AE-inl_1E26A8
	dc.b	$8F,$00,$00,$00
loc_1E26AE:
	lsl.w	#1,d0
	lea	(dat_1E2B14).l,a0
	move.w	(a0),d2
	lea	$1(a0,d2.w),a0
	move.b	$0(a0,d0.w),d1
	move.b	$1(a0,d0.w),d2
	move.b	d1,(ram_B043).w
	move.b	d2,(ram_B045).w
	lea	(ram_CFFE).w,a0
	lsr.w	#1,d0
	move.b	$0(a0,d0.w),d1
	ext.w	d1
	lsl.w	#1,d1
	bsr.w	sub_1E251C
	bra.w	loc_1E2724
loc_1E26E2:
	jsr	(Text_Print).l
inl_1E26E8:
	dc.w	loc_1E26EE-inl_1E26E8
	dc.b	$FF,$00,$00,$00
loc_1E26EE:
	lsl.w	#1,d0
	lea	(dat_1E2B14).l,a0
	move.w	(a0),d2
	lea	$1(a0,d2.w),a0
	move.b	$0(a0,d0.w),d1
	move.b	$1(a0,d0.w),d2
	move.b	d1,(ram_B043).w
	move.b	d2,(ram_B045).w
	lea	(ram_CFFE).w,a0
	lsr.w	#1,d0
	move.b	$0(a0,d0.w),d1
	ext.w	d1
	lsl.w	#1,d1
	bsr.w	sub_1E251C
	move.w	#$2D,(ram_BF4C).w
loc_1E2724:
	rts


; ----------------------------------------------------------------------
; called from $1E2AA2
sub_1E2726:
	move.w	#$19,d0
	suba.l	#$1A,sp
	movea.l	sp,a0
loc_1E2732:
	move.b	#$1,(a0)+
	dbra	d0,loc_1E2732
	move.w	#$1,d2
	movea.l	sp,a0
	lea	(ram_CFFE).w,a1
	move.w	#$F,d0
	clr.w	d1
loc_1E274A:
	move.b	(a1)+,d1
	subq.b	#1,$0(a0,d1.w)
	blt.w	loc_1E275A
	dbra	d0,loc_1E274A
	clr.w	d2
loc_1E275A:
	adda.l	#$1A,sp
	rts
dat_1E2762:
	dc.b	$00,$0A,$00,$1D,$00,$31,$00,$46,$00
	dc.b	"ZDuplicate teams have",0
	dc.b	"been detected in your",0
	dc.b	"playoff tree. You must",0
	dc.b	"have unique teams for",0
	dc.b	"playoffs.",0


; ----------------------------------------------------------------------
; called from $1E2AAE
sub_1E27CE:
	jsr	(Text_Print).l
inl_1E27D4:
	dc.w	loc_1E27DA-inl_1E27D4
	dc.b	$CE,$00,$00,$00
loc_1E27DA:
	move.w	(ram_D04C).w,d0
	neg.w	d0
	addi.w	#$140,d0
	lsr.w	#3,d0
	addq.w	#8,d0
	move.w	d0,(TextX).w
	move.w	#$A,(TextY).w
	move.w	d0,-(sp)
	moveq	#$18,d0
	moveq	#$7,d1
	move.w	(ram_BF7E).w,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E2808:
	dc.w	loc_1E280E-inl_1E2808
	dc.b	$8F,$00,$00,$00
loc_1E280E:
	move.w	(sp),(TextX).w
	move.w	#$A,(TextY).w
	moveq	#$18,d0
	moveq	#$7,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	lea	(dat_1E2762).l,a2
	move.w	(a2),d2
	lsr.w	#1,d2
	subq.w	#1,d2
	move.w	#$A,(ram_DDFA).w
	move.w	(sp),d1
	addq.w	#1,d1
	move.w	#$4,(ram_DDF4).w
	move.w	#$1,(ram_DDF6).w
	move.w	#$1,(ram_DDF2).w
loc_1E284E:
	move.w	(a2)+,d0
	lea	-$2(a2,d0.w),a0
	addq.w	#1,(ram_DDFA).w
	move.w	d1,(ram_DDF8).w
	jsr	(sub_1E0196).l
	dbra	d2,loc_1E284E
loc_1E2866:
	jsr	(sub_0202D2).l
	tst.w	d3
	bne.s	loc_1E2866
loc_1E2870:
	jsr	(sub_0202D2).l
	tst.w	d3
	beq.s	loc_1E2870
	jsr	(Text_Print).l
inl_1E2880:
	dc.w	loc_1E2886-inl_1E2880
	dc.b	$FE,$00,$00,$00
loc_1E2886:
	move.w	(sp),(TextX).w
	move.w	#$A,(TextY).w
	lea	(Art_PlayoffBackground).l,a0
	movea.l	a0,a1
	adda.l	(a1),a0
	adda.l	$4(a1),a1
	movea.l	#NullEntry,a2
	move.w	(TextX).w,d0
	move.w	(TextY).w,d1
	move.w	#$18,d2
	move.w	#$7,d3
	move.w	(ram_BF56).w,d4
	clr.w	d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E28C6:
	dc.w	loc_1E28CC-inl_1E28C6
	dc.b	$BF,$01,$00,$00
loc_1E28CC:
	move.w	(sp),(TextX).w
	move.w	#$A,(TextY).w
	lea	(Art_1BB268).l,a0
	movea.l	a0,a1
	adda.l	(a1),a0
	adda.l	$4(a1),a1
	movea.l	#NullEntry,a2
	move.w	(TextX).w,d0
	subq.w	#1,d0
	move.w	(TextY).w,d1
	move.w	#$18,d2
	move.w	#$7,d3
	move.w	(ram_BF58).w,d4
	clr.w	d5
	jsr	(TileMap_Draw).l
	move.w	(sp)+,d0
	move.w	#$A,d1
	move.w	#$F,d2
loc_1E2912:
	bsr.w	sub_1E29EA
	dbra	d2,loc_1E2912
	move.w	#$18,d2
	move.w	#$7,d3
	move.w	(ram_BF4E).w,d4
	move.w	(ram_BF50).w,d5
	andi.w	#$7FFF,d4
	move.w	#$10,d6
	move.w	#$4,d7
	bsr.w	sub_1E2A7A
	tst.w	d7
	bne.w	loc_1E297E
	move.w	d4,(TextX).w
	move.w	d5,(TextY).w
	move.w	(ram_B03C).w,d4
	jsr	(Text_PrintCmd).l
inl_1E2952:
	dc.w	loc_1E2958-inl_1E2952
	dc.b	$FE,$03,$FF,$02
loc_1E2958:
	movea.l	#Art_1C10E4,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	movea.l	#NullEntry,a2
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	clr.w	d5
	jsr	(TileMap_Draw).l
loc_1E297E:
	lea	(dat_1E2B14).l,a0
	move.w	(a0),d4
	lea	$27(a0,d4.w),a0
	jsr	(Text_Print).l
inl_1E2990:
	dc.w	loc_1E2996-inl_1E2990
	dc.b	$BF,$00,$00,$00
loc_1E2996:
	cmpi.w	#$7,(ram_CFD4).w
	beq.w	loc_1E29BC
	move.w	#$7,d4
	movea.w	#$CF50,a2
loc_1E29A8:
	move.b	(a0)+,(ram_B043).w
	move.b	(a0)+,(ram_B045).w
	bsr.w	sub_1E29BE
	adda.w	#$10,a2
	dbra	d4,loc_1E29A8
loc_1E29BC:
	rts


; ----------------------------------------------------------------------
; called from $1E29B0
sub_1E29BE:
	movea.w	#$BFF4,a1
	move.w	#$6,(a1)+
	move.w	$4(a2),d0
	addi.w	#$30,d0
	move.b	d0,(a1)+
	move.b	#$2D,(a1)+
	move.w	$6(a2),d0
	addi.w	#$30,d0
	move.b	d0,(a1)+
	clr.b	(a1)+
	movea.w	#$BFF4,a1
	jmp	(Text_PrintFont_Worker).l


; ----------------------------------------------------------------------
; called from $1E2912
sub_1E29EA:
	movem.l	d0-d7/a0-a6,-(sp)
	lea	(dat_1E2B14).l,a0
	move.w	(a0),d3
	lea	$1(a0,d3.w),a0
	lsl.w	#1,d2
	clr.w	d4
	clr.w	d5
	move.b	$0(a0,d2.w),d4
	move.b	$1(a0,d2.w),d5
	move.w	d2,-(sp)
	move.w	#$18,d2
	move.w	#$7,d3
	move.w	#$E,d6
	move.w	#$2,d7
	bsr.w	sub_1E2A7A
	move.w	(sp)+,d2
	tst.w	d7
	bne.w	loc_1E2A74
	jsr	(sub_1E2606).l
	add.w	(ram_BF48).w,d0
	lsr.w	#1,d2
	cmp.w	d0,d2
	bne.w	loc_1E2A52
	cmpi.w	#$1E,(ram_BF4C).w
	ble.w	loc_1E2A52
	jsr	(Text_Print).l
inl_1E2A48:
	dc.w	loc_1E2A4E-inl_1E2A48
	dc.b	$FF,$00,$00,$00
loc_1E2A4E:
	bra.w	loc_1E2A5E
loc_1E2A52:
	jsr	(Text_Print).l
inl_1E2A58:
	dc.w	loc_1E2A5E-inl_1E2A58
	dc.b	$8F,$00,$00,$00
loc_1E2A5E:
	move.w	d4,(TextX).w
	move.w	d5,(TextY).w
	lea	(ram_CFFE).w,a0
	move.b	$0(a0,d2.w),d1
	lsl.w	#1,d1
	bsr.w	sub_1E251C
loc_1E2A74:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E2936, $1E2A1A
sub_1E2A7A:
	movem.w	d0-d6,-(sp)
	sub.w	d4,d0
	move.w	d0,d4
	sub.w	d6,d0
	add.w	d2,d4
	eor.w	d0,d4
	bge.w	loc_1E2A9C
	sub.w	d5,d1
	move.w	d1,d5
	sub.w	d7,d1
	add.w	d3,d5
	eor.w	d1,d5
	bge.w	loc_1E2A9C
	clr.w	d7
loc_1E2A9C:
	movem.w	(sp)+,d0-d6
	rts


; ----------------------------------------------------------------------
; called from $1E2470
sub_1E2AA2:
	jsr	(sub_1E2726).l
	tst.w	d2
	beq.w	loc_1E2AB4
	bsr.w	sub_1E27CE
	rts
loc_1E2AB4:
	jsr	(sub_02A012).l
	jsr	(SRAM_UpdateChecksum).l
	jsr	(sub_027354).l
	move.l	(ram_C39C).w,(ram_C394).w
	move.l	(ram_C3A0).w,(ram_C398).w
	bclr	#7,(ram_C35C).w
	rts

	dc.b	$00,$0A
	dc.b	"Playoffs",0
	dc.b	$10
	dc.b	"Quarterfinals",0
	dc.b	$00,$0C
	dc.b	"Semifinals",0
	dc.b	$08
	dc.b	"Finals",0
	dc.b	$0C
	dc.b	"Champions",0
dat_1E2B14:
	dc.w	$000A,$0041,$0084,$00CF,$011C,$0F02,$0202,$0402
	dc.w	$0802,$0A02,$0E02,$1002,$1402,$1667,$0267,$0467
	dc.w	$0867,$0A67,$0E67,$1067,$1467,$1601,$3900,$450A
	dc.w	$0707,$0607,$0C07,$1207,$186C,$066C,$0C6C,$126C
	dc.w	$1817,$0202,$0204,$0208,$020A,$020E,$0210,$0214
	dc.w	$0216,$6702,$6704,$6708,$670A,$670E,$6710,$6714
	dc.w	$6716,$1305,$1307,$1311,$1313,$5605,$5607,$5611
	dc.w	$5613,$032B,$0039,$0245,$0853,$0A03,$1809,$1815
	dc.w	$5B09,$5B15,$1B02,$0202,$0402,$0802,$0A02,$0E02
	dc.w	$1002,$1402,$1667,$0267,$0467,$0867,$0A67,$0E67
	dc.w	$1067,$1467,$1613,$0513,$0713,$1113,$1356,$0556
	dc.w	$0756,$1156,$1322,$0B22,$0D48,$0B48,$0D05,$1D00
	dc.w	$2B02,$3904,$4506,$5308,$610A,$0127,$0F4D,$0F1D
	dc.w	$0202,$0204,$0208,$020A,$020E,$0210,$0214,$0216
	dc.w	$6702,$6704,$6708,$670A,$670E,$6710,$6714,$6716
	dc.w	$1305,$1307,$1311,$1313,$5605,$5607,$5611,$5613
	dc.w	$220B,$220D,$480B,$480D,$2A18,$4118,$050F,$001D
	dc.w	$022B,$0453,$0661,$086F,$0A00,$3B1A,$1E02,$0202
	dc.w	$0402,$0802,$0A02,$0E02,$1002,$1402,$1667,$0267
	dc.w	$0467,$0867,$0A67,$0E67,$1067,$1467,$1613,$0513
	dc.w	$0713,$1113,$1356,$0556,$0756,$1156,$1322,$0B22
	dc.w	$0D48,$0B48,$0D2A,$1841,$1835,$1105,$0F00,$1D02
	dc.w	$2B04,$5306,$6108,$6F0A,$FFFF
dat_1E2C7E:
	dc.w	$0000,$0088,$0088,$0140
dat_1E2C86:
	dc.b	$01,$40
dat_1E2C88:
	dc.w	$0140,$0140,$0088,$0000,$0000
loc_1E2C92:
	btst	#7,(ram_C33C).w
	beq.w	loc_1E2D52
	btst	#0,(ram_C34A).w
	bne.w	loc_1E2D16
	move.l	a1,-(sp)
	jsr	(Text_Print).l
inl_1E2CAE:
	dc.w	loc_1E2CB4-inl_1E2CAE
	dc.b	$BE,$0D,$05,$00
loc_1E2CB4:
	move.w	(ram_C4CA).w,d0
	ext.l	d0
	divu.w	#$258,d0
	move.l	d0,-(sp)
	tst.w	d0
	bne.w	loc_1E2CCE
	addq.w	#1,(TextX).w
	bra.w	loc_1E2CD4
loc_1E2CCE:
	jsr	(sub_1E2D18).l
loc_1E2CD4:
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	divu.w	#$3C,d0
	move.l	d0,-(sp)
	jsr	(sub_1E2D18).l
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	addq.w	#2,(TextX).w
	divu.w	#$A,d0
	move.l	d0,-(sp)
	jsr	(sub_1E2D18).l
	move.l	(sp)+,d0
	swap	d0
	ext.l	d0
	jsr	(sub_1E2D18).l
	movea.l	(sp)+,a1
	jsr	(Text_Print).l
inl_1E2D10:
	dc.w	loc_1E2D16-inl_1E2D10
	dc.b	$BD,$0D,$05,$00
loc_1E2D16:
	rts


; ----------------------------------------------------------------------
; called from $1E2CCE, $1E2CE0, $1E2CF6, $1E2D02
sub_1E2D18:
	movea.l	#ptrs_1E2D2A,a1
	asl.w	#2,d0
	adda.w	d0,a1
	jsr	(Text_Print_Worker).l
	rts

ptrs_1E2D2A:
	dc.l	dat_043000
	dc.l	dat_043100
	dc.l	dat_043200
	dc.l	dat_043300
	dc.l	dat_043400
	dc.l	dat_043500
	dc.l	dat_043600
	dc.l	dat_043700
	dc.l	dat_043800
	dc.l	dat_043900
loc_1E2D52:
	bclr	#3,(VideoFlags).w
	beq.w	loc_1E2EE8
	btst	#3,(ram_C33E).w
	bne.w	loc_1E2EE8
	cmpi.w	#$4,(ram_C4C8).w
	beq.w	loc_1E2EE8
	btst	#7,(ram_C350).w
	beq.w	loc_1E2D84
	btst	#0,(ram_DEA2).w
	beq.w	loc_1E2EE8
loc_1E2D84:
	movea.w	#$BFCC,a0
	movea.l	#Font_Scoreboard,a1
	adda.l	$4(a1),a1
	move.w	$50(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,(ram_BFC4).w
	move.w	$4E(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	move.w	(ram_C4CA).w,d0
	btst	#1,(ram_C34A).w
	beq.w	loc_1E2DC2
	move.w	(ram_D344).w,d0
loc_1E2DC2:
	ext.l	d0
	divu.w	#$A,d0
	bsr.w	sub_1E2ED2
	divu.w	#$6,d0
	bsr.w	sub_1E2ED2
	subq.w	#2,a0
	divu.w	#$A,d0
	bsr.w	sub_1E2ED2
	swap	d0
	tst.l	d0
	bne.w	loc_1E2DEA
	moveq	#-$1,d0
	swap	d0
loc_1E2DEA:
	bsr.w	sub_1E2ED2
	move.w	$52(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	move.l	a0,(a5)+
	move.w	#$7,(a5)+
	movea.w	#$B004,a1
	moveq	#$19,d0
	moveq	#$1,d2
	btst	#7,(ram_C33C).w
	beq.w	loc_1E2E1C
	movea.w	#$B008,a1
	moveq	#$5,d0
	moveq	#$D,d2
loc_1E2E1C:
	move.w	$2(a1),d1
	asl.w	d1,d0
	add.w	d2,d0
	asl.w	#1,d0
	add.w	(a1),d0
	move.w	d0,(a5)+
	movea.w	#$BFDA,a0
	movea.l	#Font_Scoreboard,a1
	adda.l	$4(a1),a1
	move.w	$B0(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,(ram_BFD2).w
	move.w	$AE(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	move.w	(ram_C4CA).w,d0
	btst	#1,(ram_C34A).w
	beq.w	loc_1E2E68
	move.w	(ram_D344).w,d0
loc_1E2E68:
	ext.l	d0
	divu.w	#$A,d0
	bsr.w	sub_1E2EEA
	divu.w	#$6,d0
	bsr.w	sub_1E2EEA
	subq.w	#2,a0
	divu.w	#$A,d0
	bsr.w	sub_1E2EEA
	swap	d0
	tst.l	d0
	bne.w	loc_1E2E90
	moveq	#-$1,d0
	swap	d0
loc_1E2E90:
	bsr.w	sub_1E2EEA
	move.w	$B2(a1),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	move.l	a0,(a5)+
	move.w	#$7,(a5)+
	movea.w	#$B004,a1
	moveq	#$1A,d0
	moveq	#$1,d2
	btst	#7,(ram_C33C).w
	beq.w	loc_1E2EC2
	movea.w	#$B008,a1
	moveq	#$5,d0
	moveq	#$D,d2
loc_1E2EC2:
	move.w	$2(a1),d1
	asl.w	d1,d0
	add.w	d2,d0
	asl.w	#1,d0
	add.w	(a1),d0
	move.w	d0,(a5)+
	rts


; ----------------------------------------------------------------------
; called from $1E2DC8, $1E2DD0, $1E2DDA, $1E2DEA
sub_1E2ED2:
	swap	d0
	asl.w	#1,d0
	move.w	$38(a1,d0.w),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	swap	d0
	ext.l	d0
loc_1E2EE8:
	rts


; ----------------------------------------------------------------------
; called from $1E2E6E, $1E2E76, $1E2E80, $1E2E90
sub_1E2EEA:
	swap	d0
	asl.w	#1,d0
	addi.w	#$98,d0
	move.w	$0(a1,d0.w),d0
	add.w	(ram_B016).w,d0
	ori.w	#$8000,d0
	move.w	d0,-(a0)
	swap	d0
	ext.l	d0
	rts


; ----------------------------------------------------------------------
; called from $00C770, $0282F0
sub_1E2F06:
	movem.l	d0-d7/a0-a6,-(sp)
	bset	#2,(ram_C358).w
	bset	#0,(ram_C35C).w
	jsr	(sub_022218).l
	jsr	(sub_022298).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2F28:
	dc.w	loc_1E2F32-inl_1E2F28
	dc.w	$F804,$0106,$1520,$FB0F
loc_1E2F32:
	move.w	(ram_CADC).w,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2F4C:
	dc.w	loc_1E2F50-inl_1E2F4C
	dc.b	$3E,$00
loc_1E2F50:
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2F56:
	dc.w	loc_1E2F60-inl_1E2F56
	dc.w	$F804,$0106,$1720,$FB0F
loc_1E2F60:
	move.w	(ram_C73E).w,d0
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2F7A:
	dc.w	loc_1E2F7E-inl_1E2F7A
	dc.b	$3E,$00
loc_1E2F7E:
	btst	#0,(ram_C34A).w
	beq.w	loc_1E2FBA
	jsr	(Text_Print).l
inl_1E2F8E:
	dc.w	loc_1E2F94-inl_1E2F8E
	dc.b	$BF,$08,$19,$00
loc_1E2F94:
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2F9A:
	dc.w	loc_1E2FAC-inl_1E2F9A
	dc.b	"    shootout    "
loc_1E2FAC:
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2FB2:
	dc.w	loc_1E2FB6-inl_1E2FB2
	dc.b	$3E,$00
loc_1E2FB6:
	bra.w	loc_1E2FE6
loc_1E2FBA:
	jsr	(Text_Print).l
inl_1E2FC0:
	dc.w	loc_1E2FC6-inl_1E2FC0
	dc.b	$BF,$08,$19,$00
loc_1E2FC6:
	movea.l	#dat_1E307C,a1
	move.w	(ram_C4C8).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1E2FE2:
	dc.w	loc_1E2FE6-inl_1E2FE2
	dc.b	$3E,$00
loc_1E2FE6:
	jsr	(Text_PrintScoreboard).l
inl_1E2FEC:
	dc.w	loc_1E3004-inl_1E2FEC
	dc.b	$F8,$04,$01,$07,$15
	dc.b	"<            >"
	dc.b	$FD,$08,$00
loc_1E3004:
	move.w	(ram_CAF8).w,d0
	movea.w	#$7FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E301A
	movea.l	#RosterTable,a1
loc_1E301A:
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	jsr	(Text_PrintScoreboard_Worker).l
	jsr	(Text_PrintScoreboard).l
inl_1E3034:
	dc.w	loc_1E304C-inl_1E3034
	dc.b	$F8,$04,$01,$07,$17
	dc.b	"<            >"
	dc.b	$FD,$08,$00
loc_1E304C:
	move.w	(ram_C75A).w,d0
	movea.w	#$7FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E3062
	movea.l	#RosterTable,a1
loc_1E3062:
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	jsr	(Text_PrintScoreboard_Worker).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1E307C:
	dc.b	$00,$12
	dc.b	"  1st period    ",0
	dc.b	$12
	dc.b	"  2nd period    ",0
	dc.b	$12
	dc.b	"  3rd period    ",0
	dc.b	$12
	dc.b	"   overtime     ",0
	dc.b	$12
	dc.b	"     final      "


; ----------------------------------------------------------------------
; called from $00C78C, $0125FC, $027E9E
sub_1E30D6:
	movem.l	d0-d7/a0-a6,-(sp)
	bclr	#0,(ram_C35C).w
	jsr	(Text_Print).l
inl_1E30E6:
	dc.w	loc_1E30EC-inl_1E30E6
	dc.b	$BF,$01,$15,$00
loc_1E30EC:
	move.w	#$1B,d0
	move.w	#$4,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E3104:
	dc.w	loc_1E310A-inl_1E3104
	dc.b	$BF,$08,$19,$00
loc_1E310A:
	move.w	#$14,d0
	move.w	#$2,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $026FEA, $027054
sub_1E3122:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01FFA2).l
	bsr.w	sub_1E3CFC
	bsr.w	sub_1E3900
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D050).w
loc_1E3144:
	jsr	(sub_1E31BC).l
	jsr	(sub_1E31DA).l
	jsr	(sub_1E3248).l
	jsr	(sub_1E339A).l
	jsr	(sub_1E3834).l
	move.w	#$64,(FadeCounter).w
	move.w	#$2500,sr
loc_1E316C:
	move.w	(FrameCounter).w,d0
loc_1E3170:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E3170
	jsr	(Joypad_ReadAll).l
	btst	#7,d1
	bne.w	loc_1E31B6
	btst	#2,d1
	beq.w	loc_1E31A0
	move.w	(ram_D050).w,d0
	subq.w	#1,d0
	bpl.w	loc_1E319A
	move.w	#$C,d0
loc_1E319A:
	move.w	d0,(ram_D050).w
	bra.s	loc_1E3144
loc_1E31A0:
	btst	#3,d1
	beq.s	loc_1E316C
	move.w	(ram_D050).w,d0
	addq.w	#1,d0
	cmp.w	#$C,d0	; general form
	ble.s	loc_1E319A
	clr.w	d0
	bra.s	loc_1E319A
loc_1E31B6:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E3144
sub_1E31BC:
	jsr	(Text_Print).l
inl_1E31C2:
	dc.w	loc_1E31C8-inl_1E31C2
	dc.b	$8F,$03,$08,$00
loc_1E31C8:
	bsr.w	sub_1E3A30
	move.w	(ram_B02E).w,d4
	clr.w	d5
	jsr	(sub_016EF4).l
	rts


; ----------------------------------------------------------------------
; called from $1E314A
sub_1E31DA:
	jsr	(Text_Print).l
inl_1E31E0:
	dc.w	loc_1E31E6-inl_1E31E0
	dc.b	$BF,$19,$09,$00
loc_1E31E6:
	move.w	(ram_D050).w,d0
	movea.l	#ptrs_1E3214,a0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$A,d2
	moveq	#$A,d3
	moveq	#$2,d5
	move.w	(ram_D04C).w,d4
	jsr	(TileMap_Draw).l
	rts

ptrs_1E3214:
	dc.l	Art_1AFEAC
	dc.l	Art_1ADA5E
	dc.l	Art_1AE374
	dc.l	Art_1AEAEA
	dc.l	Art_1B0462
	dc.l	Art_1AD408
	dc.l	Art_1AF936
	dc.l	Art_1AF1E0
	dc.l	Art_1B0C78
	dc.l	Art_1B12EE
	dc.l	Art_1B1D64
	dc.l	Art_1B26FA
	dc.l	Art_1B2EB0


; ----------------------------------------------------------------------
; called from $1E3150
sub_1E3248:
	jsr	(Text_Print).l
inl_1E324E:
	dc.w	loc_1E3254-inl_1E324E
	dc.b	$BF,$13,$05,$00
loc_1E3254:
	movea.l	#dat_1E327C,a1
	move.w	(ram_D050).w,d0
	jsr	(List_Skip).l
	move.w	(a1),d0
	subq.w	#2,d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow_Worker).l
	rts
dat_1E327C:
	dc.b	$00,$16
	dc.b	"hart memorial trophy",0
	dc.b	$16
	dc.b	"  art ross trophy   ",0
	dc.b	$16
	dc.b	"james norris trophy ",0
	dc.b	$16
	dc.b	"   vezina trophy    ",0
	dc.b	$16
	dc.b	" conn smythe trophy ",0
	dc.b	$16
	dc.b	" presidents trophy  ",0
	dc.b	$16
	dc.b	"  prince of wales   ",0
	dc.b	$16
	dc.b	" clarence campbell  ",0
	dc.b	$16
	dc.b	" lester b. pearson  ",0
	dc.b	$16
	dc.b	"   frank j. selke   ",0
	dc.b	$16
	dc.b	"william m. jennings ",0
	dc.b	$16
	dc.b	"  calder memorial   ",0
	dc.b	$16
	dc.b	"  ea sports trophy  "


; ----------------------------------------------------------------------
; called from $1E3156
sub_1E339A:
	jsr	(Text_PrintFont).l
inl_1E33A0:
	dc.w	loc_1E3428-inl_1E33A0
	dc.b	$BF,$02,$13
	dc.b	"                "
	dc.b	$BF,$02,$14
	dc.b	"                "
	dc.b	$BF,$02,$15
	dc.b	"                "
	dc.b	$8F,$02,$16
	dc.b	"                "
	dc.b	$8F,$02,$17
	dc.b	"                "
	dc.b	$8F,$02,$18
	dc.b	"                "
	dc.b	$8F,$02,$19
	dc.b	"                ",0
loc_1E3428:
	movea.l	#dat_1E3440,a1
	move.w	(ram_D050).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintFont_Worker).l
	rts
dat_1E3440:
	dc.b	$00,$48,$BF,$02,$14
	dc.b	"to the player"
	dc.b	$BF,$02,$15
	dc.b	"adjudged to be"
	dc.b	$BF,$02,$16
	dc.b	"the most"
	dc.b	$BF,$02,$17
	dc.b	"valuable to"
	dc.b	$BF,$02,$18
	dc.b	"his team",0
	dc.b	$00,$58,$BF,$02,$14
	dc.b	"to the player"
	dc.b	$BF,$02,$15
	dc.b	"who leads the"
	dc.b	$BF,$02,$16
	dc.b	"league in points"
	dc.b	$BF,$02,$17
	dc.b	"at the end of"
	dc.b	$BF,$02,$18
	dc.b	"the reg. season",0
	dc.b	$00,$5C,$BF,$02,$14
	dc.b	"to the defensive"
	dc.b	$BF,$02,$15
	dc.b	"player showing"
	dc.b	$BF,$02,$16
	dc.b	"the greatest all"
	dc.b	$BF,$02,$17
	dc.b	"around ability"
	dc.b	$BF,$02,$18
	dc.b	"in the position",0
	dc.b	$40,$BF,$02,$14
	dc.b	"to the goalie"
	dc.b	$BF,$02,$15
	dc.b	"adjudged to be"
	dc.b	$BF,$02,$16
	dc.b	"the best at"
	dc.b	$BF,$02,$17
	dc.b	"his position",0
	dc.b	$44,$BF,$02,$14
	dc.b	"to the most"
	dc.b	$BF,$02,$15
	dc.b	"valuable player"
	dc.b	$BF,$02,$16
	dc.b	"for his team"
	dc.b	$BF,$02,$17
	dc.b	"in the playoffs",0
	dc.b	$00,$4A,$BF,$02,$14
	dc.b	"to the club"
	dc.b	$BF,$02,$15
	dc.b	"finishing the"
	dc.b	$BF,$02,$16
	dc.b	"regular season"
	dc.b	$BF,$02,$17
	dc.b	"with the best"
	dc.b	$BF,$02,$18
	dc.b	"record",0
	dc.b	$40,$BF,$02,$14
	dc.b	"to the winners"
	dc.b	$BF,$02,$15
	dc.b	"of the eastern"
	dc.b	$BF,$02,$16
	dc.b	"Conference"
	dc.b	$BF,$02,$17
	dc.b	"Championship",0
	dc.b	$40,$BF,$02,$14
	dc.b	"to the winners"
	dc.b	$BF,$02,$15
	dc.b	"of the western"
	dc.b	$BF,$02,$16
	dc.b	"Conference"
	dc.b	$BF,$02,$17
	dc.b	"Championship",0
	dc.b	$52,$BF,$02,$14
	dc.b	"to the nhl's"
	dc.b	$BF,$02,$15
	dc.b	"outstanding"
	dc.b	$BF,$02,$16
	dc.b	"player chosen by"
	dc.b	$BF,$02,$17
	dc.b	"player members"
	dc.b	$BF,$02,$18
	dc.b	"of the nhlpa",0
	dc.b	$50,$BF,$02,$14
	dc.b	"to the forward"
	dc.b	$BF,$02,$15
	dc.b	"who best excels"
	dc.b	$BF,$02,$16
	dc.b	"in the defensive"
	dc.b	$BF,$02,$17
	dc.b	"aspect of the"
	dc.b	$BF,$02,$18
	dc.b	"game",0
	dc.b	$00,$74,$BF,$02,$13
	dc.b	"to the goalie"
	dc.b	$BF,$02,$14
	dc.b	"having played a"
	dc.b	$BF,$02,$15
	dc.b	"min of 25 games"
	dc.b	$BF,$02,$16
	dc.b	"for the team"
	dc.b	$BF,$02,$17
	dc.b	"with the fewest"
	dc.b	$BF,$02,$18
	dc.b	"goals scored"
	dc.b	$BF,$02,$19
	dc.b	"against it",0
	dc.b	$00,$6C,$BF,$02,$14
	dc.b	"to the player"
	dc.b	$BF,$02,$15
	dc.b	"selected as the"
	dc.b	$BF,$02,$16
	dc.b	"most proficient"
	dc.b	$BF,$02,$17
	dc.b	"in his first"
	dc.b	$BF,$02,$18
	dc.b	"year of competi-"
	dc.b	$BF,$02,$19
	dc.b	"-tion in the nhl",0
	dc.b	$00,$28,$BF,$02,$14
	dc.b	"to the nhl's"
	dc.b	$BF,$02,$15
	dc.b	"outstanding"
	dc.b	$BF,$02,$16
	dc.b	"player"


; ----------------------------------------------------------------------
; called from $1E315C
sub_1E3834:
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow).l
inl_1E3840:
	dc.w	loc_1E3856-inl_1E3840
	dc.b	$F8,$04,$01,$17,$15
	dc.b	"              ",0
loc_1E3856:
	bsr.w	sub_1E3A6A
	movea.l	#dat_1E38F2,a0
	move.w	(ram_D050).w,d1
	tst.b	$0(a0,d1.w)
	beq.w	loc_1E3890
	move.w	d0,d7
	asl.w	#2,d7
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E3884
	movea.l	#RosterTable,a1
loc_1E3884:
	movea.l	$0(a1,d7.w),a1
	adda.w	$4(a1),a1
	bra.w	loc_1E38CE
loc_1E3890:
	swap	d0
	jsr	(sub_013C6C).l
	movea.l	a1,a0
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
loc_1E38B6:
	cmpi.b	#$20,(a0)+
	bne.s	loc_1E38B6
loc_1E38BC:
	move.b	(a0)+,(a1)+
	cmpa.l	a0,a2
	bne.s	loc_1E38BC
	jsr	(sub_028714).l
	movea.l	#ram_BFF4,a1
loc_1E38CE:
	jsr	(Text_Print).l
inl_1E38D4:
	dc.w	loc_1E38DA-inl_1E38D4
	dc.b	$BF,$1E,$15,$00
loc_1E38DA:
	move.w	(a1),d0
	subq.w	#2,d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow_Worker).l
	rts
dat_1E38F2:
	dc.w	$0000,$0000,$0001,$0101,$0000,$0000,$00FF


; ----------------------------------------------------------------------
; called from $1E3130
sub_1E3900:
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
inl_1E397A:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E3982:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B016).w
	lea	(Font_Narrow_Tiles).l,a2
	jsr	(Draw_RunScript).l
inl_1E39AA:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E39B2:
	move.w	(ram_B016).w,(ram_B014).w
	move.w	(ram_B016).w,(ram_B018).w
	move.l	#Font_Narrow,(FontPtr2).w
	jsr	(Text_PrintCmd).l
inl_1E39CC:
	dc.w	loc_1E39D4-inl_1E39CC
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E39D4:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	d4,(ram_B02E).w
	addi.w	#$A0,d4
	move.w	d4,(ram_D04C).w
	addi.w	#$64,d4
	jsr	(Text_Print).l
inl_1E39F8:
	dc.w	loc_1E39FE-inl_1E39F8
	dc.b	$FE,$00,$00,$00
loc_1E39FE:
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
	jsr	(Text_PrintBig).l
inl_1E3A22:
	dc.w	loc_1E3A2E-inl_1E3A22
	dc.b	$BF,$0E,$01
	dc.b	"AWARDS",0
loc_1E3A2E:
	rts


; ----------------------------------------------------------------------
; called from $1E31C8
sub_1E3A30:
	movea.l	#ram_D14C,a0
	move.l	#$D98,d0
	move.w	(ram_D050).w,d1
	cmp.w	#$8,d1	; general form
	bne.w	loc_1E3A4A
	clr.w	d1
loc_1E3A4A:
	cmp.w	#$C,d1	; general form
	bne.w	loc_1E3A54
	clr.w	d1
loc_1E3A54:
	mulu.w	#$4,d1
	add.l	d1,d0
	move.w	#$4,d1
	jsr	(SRAM_Read).l
	move.w	$2(a0),d7
	rts


; ----------------------------------------------------------------------
; called from $1E3856
sub_1E3A6A:
	movea.l	#ram_D14C,a0
	move.l	#$D98,d0
	move.w	(ram_D050).w,d1
	cmp.w	#$8,d1	; general form
	bne.w	loc_1E3A84
	clr.w	d1
loc_1E3A84:
	cmp.w	#$C,d1	; general form
	bne.w	loc_1E3A8E
	clr.w	d1
loc_1E3A8E:
	mulu.w	#$4,d1
	add.l	d1,d0
	move.w	#$4,d1
	jsr	(SRAM_Read).l
	move.l	(a0),d0
	rts


; ----------------------------------------------------------------------
; called from $026F42
sub_1E3AA2:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$2,(ram_BF58).w
	jsr	(sub_1D4D52).l
	movea.l	#$201B30,a6
	move.w	(ram_1388).l,d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	addq.l	#8,a6
	move.w	(ram_1388).l,d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	addq.l	#8,a6
	movea.l	#ram_1388,a5
loc_1E3B22:
	move.w	(a5),d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	movem.w	d0,-(sp)
	jsr	(sub_013E80).l
	move.w	d0,d1
	movem.w	(sp)+,d0
	cmp.w	#$1,d1	; general form
	beq.w	loc_1E3B52
	cmp.w	#$2,d1	; general form
	beq.w	loc_1E3B52
	addq.l	#2,a5
	bra.s	loc_1E3B22
loc_1E3B52:
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	addq.l	#8,a6
	move.w	#$3,(ram_BF58).w
	jsr	(sub_1D4D52).l
	move.w	(ram_1388).l,d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	adda.l	#$10,a6
	move.l	a6,-(sp)
	movea.l	#ram_D184,a0
	jsr	(sub_015176).l
	jsr	(sub_1D3FE8).l
	movea.l	(sp)+,a6
	move.w	#$19,d6
	clr.w	d7
	clr.w	d5
	movea.l	#ram_D14E,a0
loc_1E3BDA:
	clr.w	d0
	move.b	(a0)+,d0
	cmp.w	d0,d5
	bge.w	loc_1E3BEC
	move.b	-$1(a0),d5
	move.b	d7,(ram_DDCF).w
loc_1E3BEC:
	addq.w	#1,d7
	dbra	d6,loc_1E3BDA
	move.b	(ram_DDCF).w,$7(a6)
	clr.b	$5(a6)
	move.w	#$2,(ram_BF58).w
	jsr	(sub_1D4D52).l
	movea.l	#$201B78,a6
	movea.l	#ram_1388,a5
loc_1E3C14:
	move.w	(a5),d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	movem.w	d0,-(sp)
	jsr	(sub_013E80).l
	move.w	d0,d1
	movem.w	(sp)+,d0
	cmp.w	#$4,d1	; general form
	beq.w	loc_1E3C3C
	addq.l	#2,a5
	bra.s	loc_1E3C14
loc_1E3C3C:
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	addq.l	#8,a6
	move.w	#$3,(ram_BF58).w
	jsr	(sub_1D4D52).l
	move.w	(ram_1388).l,d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	move.w	#$2,(ram_BF58).w
	jsr	(sub_1D4D52).l
	addq.l	#8,a6
	movea.l	#ram_1388,a5
	move.w	(a5),d0
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
	movem.w	d0,-(sp)
	jsr	(sub_013E80).l
	move.w	d0,d1
	movem.w	(sp)+,d0
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E312C
sub_1E3CFC:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$2,(ram_BF58).w
	jsr	(sub_1D4D52).l
	movea.l	#$201B50,a6
	move.w	(ram_1388).l,d0
	btst	#1,(ram_C356).w
	beq.w	loc_1E3D44
	move.w	($201B5E).l,d7
	andi.w	#$FF,d7
	jsr	(sub_01A20E).l
	move.w	d0,d1
	move.w	#$3,d0
	jsr	(Random).l
	add.w	d1,d0
	bra.w	loc_1E3D4E
loc_1E3D44:
	ext.l	d0
	divu.w	#$1B,d0
	move.w	d0,d7
	swap	d0
loc_1E3D4E:
	clr.w	$4(a6)
	move.w	d7,$6(a6)
	movea.l	#ram_DDCE,a0
	jsr	(sub_013FEA).l
	move.b	(ram_DDCE).w,$1(a6)
	move.b	(ram_DDCF).w,$3(a6)
	btst	#1,(ram_C356).w
	beq.w	loc_1E3DF4
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$5,(ram_D168).w
	jsr	(sub_1D4034).l
	movea.l	#ram_D184,a0
	jsr	(sub_015176).l
	jsr	(sub_1D3FE8).l
	jsr	(sub_1D40B4).l
	clr.w	d7
	move.b	(ram_D1D2).w,d7
	movea.l	#$201B60,a6
	move.b	d7,$7(a6)
	clr.b	$5(a6)
	move.w	#$4,(ram_D168).w
	jsr	(sub_1D4034).l
	movea.l	#ram_D184,a0
	jsr	(sub_015176).l
	jsr	(sub_1D3FE8).l
	jsr	(sub_1D40B4).l
	clr.w	d7
	move.b	(ram_D1D2).w,d7
	movea.l	#$201B60,a6
	move.b	d7,$F(a6)
	clr.b	$D(a6)
	movem.l	(sp)+,d0-d7/a0-a6
	bra.w	loc_1E3E48
loc_1E3DF4:
	jsr	(sub_027354).l
	movea.l	#$201B60,a6
	movea.l	#ram_CFFA,a0
	movea.l	#dat_1D4098,a1
	move.b	(a1)+,d1
	subq.w	#1,d1
loc_1E3E10:
	move.b	(a1)+,d0
	cmp.b	(a0),d0
	beq.w	loc_1E3E20
	dbra	d1,loc_1E3E10
	bra.w	loc_1E3E36
loc_1E3E20:
	move.b	$1(a0),$7(a6)
	clr.b	$5(a6)
	move.b	(a0),$F(a6)
	clr.b	$D(a6)
	bra.w	loc_1E3E48
loc_1E3E36:
	move.b	(a0),$7(a6)
	clr.b	$5(a6)
	move.b	$1(a0),$F(a6)
	clr.b	$D(a6)
loc_1E3E48:
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $02704E
sub_1E3E5A:
	btst	#3,(ram_DD9E).w
	beq.w	loc_1E40D4
	movem.l	d0-d7/a0-a6,-(sp)
	move.l	#VBlank_Main2,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	bclr	#5,(VideoFlags).w
	jsr	(Palette_SetAll).l
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$0,(a0)
	move.w	#$0,d0
	move.w	d0,(a0)
	jsr	(Joypad_ReadAll).l
	move.w	#$1,d4
	move.w	d4,(ram_B016).w
	movea.l	#Font_Scoreboard_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E3EF0:
	dc.w	$04F3,$4567,$89CB,$CA9F
loc_1E3EF8:
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintCmd).l
inl_1E3F04:
	dc.w	loc_1E3F0C-inl_1E3F04
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E3F0C:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E3F20:
	dc.w	loc_1E3F26-inl_1E3F20
	dc.b	$BF,$00,$00,$00
loc_1E3F26:
	movea.l	#Art_ChampionsFaces,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	movea.l	#dat_1C718E,a0
	clr.l	d0
	move.b	(ram_DDA2).w,d0
	asl.w	#5,d0
	adda.l	d0,a0
	move.w	#$7,d1
	movea.l	#PaletteBuffer,a1
loc_1E3F5E:
	move.l	(a0)+,(a1)+
	dbra	d1,loc_1E3F5E
	jsr	(Text_Print).l
inl_1E3F6A:
	dc.w	loc_1E3F70-inl_1E3F6A
	dc.b	$AF,$1D,$15,$00
loc_1E3F70:
	movea.l	#dat_017196,a0
	tst.w	(ram_DEA8).w
	beq.w	loc_1E3F84
	movea.l	#dat_017212,a0
loc_1E3F84:
	clr.w	d0
	move.b	(ram_DDA2).w,d0
	asl.w	#2,d0
	movea.l	$0(a0,d0.w),a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$5,d2
	moveq	#$5,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E3FAE:
	dc.w	loc_1E3FB4-inl_1E3FAE
	dc.b	$FE,$00,$00,$00
loc_1E3FB4:
	movea.l	#Art_ChampionsPhoto,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E3FD8:
	dc.w	loc_1E3FDE-inl_1E3FD8
	dc.b	$AF,$14,$16,$00
loc_1E3FDE:
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E3FF2
	movea.l	#RosterTable,a1
loc_1E3FF2:
	clr.w	d0
	move.b	(ram_DDA2).w,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	cmp.w	#$0,d0	; general form
	bne.w	loc_1E4010
	movea.l	#dat_1E40D6,a1
loc_1E4010:
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	sub.w	d0,(TextX).w
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Scoreboard,(FontPtr2).w
	jsr	(sub_020F4A).l
	jsr	(Text_Print).l
inl_1E4034:
	dc.w	loc_1E403A-inl_1E4034
	dc.b	$AF,$14,$18,$00
loc_1E403A:
	movea.l	#dat_0007FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_1E404E
	movea.l	#RosterTable,a1
loc_1E404E:
	clr.w	d0
	move.b	(ram_DDA2).w,d0
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	adda.w	(a1),a1
	cmp.w	#$0,d0	; general form
	bne.w	loc_1E4070
	movea.l	#dat_1E40E4,a1
loc_1E4070:
	cmp.w	#$48,d0	; general form
	bne.w	loc_1E407E
	movea.l	#dat_1E40F0,a1
loc_1E407E:
	cmp.w	#$18,d0	; general form
	bne.w	loc_1E408C
	movea.l	#dat_1E40FA,a1
loc_1E408C:
	move.w	(a1),d0
	subq.w	#2,d0
	asr.w	#1,d0
	sub.w	d0,(TextX).w
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Scoreboard,(FontPtr2).w
	jsr	(sub_020F4A).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	#$2500,sr
	move.w	(FrameCounter).w,d0
loc_1E40BE:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E40BE
	jsr	(Joypad_ReadAll).l
	btst	#7,d1
	beq.s	loc_1E40BE
	movem.l	(sp)+,d0-d7/a0-a6
loc_1E40D4:
	rts
dat_1E40D6:
	dc.b	$00,$0E
	dc.b	"mighty ducks"
dat_1E40E4:
	dc.b	$00,$0C
	dc.b	"of anaheim"
dat_1E40F0:
	dc.b	$00,$0A
	dc.b	"coyotes",0
dat_1E40FA:
	dc.b	$00,$0C
	dc.b	" avalanche"


; ----------------------------------------------------------------------
; called from $023A98
sub_1E4106:
	btst	#2,(ram_C35A).w
	bne.w	loc_1E4176
	move.w	#$64,d0
	jsr	(Random).l
	cmp.w	#$1E,d0	; general form
	blt.w	loc_1E4176
	movem.w	d1,-(sp)
	clr.w	d0
	move.b	#$50,d0
	clr.w	d1
	move.b	(ram_DD9C).w,d1
	sub.w	d1,d0
	movem.w	(sp)+,d1
	cmp.w	#$2,d0	; general form
	blt.w	loc_1E4176
	subq.w	#1,d0
	cmp.w	#$5,d0	; general form
	ble.w	loc_1E414E
	move.w	#$5,d0
loc_1E414E:
	jsr	(Random).l
	addq.w	#1,d0
	movem.l	d1/d7,-(sp)
	move.w	$28(a0),d7
	move.w	(ram_C4D4).w,d1
	andi.w	#$FF,d1
	bset	#2,(ram_C35A).w
	jsr	(sub_1E4178).l
	movem.l	(sp)+,d1/d7
loc_1E4176:
	rts


; ----------------------------------------------------------------------
; called from $1E416C
sub_1E4178:
	movem.l	d0-d7/a0-a7,-(sp)
	bset	#3,(ram_C35A).w
	move.w	d0,(ram_DDDC).w
	ext.l	d0
	mulu.w	#$51,d7
	mulu.w	#$3,d1
	addi.l	#$10080,d1
	add.l	d7,d1
	moveq	#$3,d2
	jsr	(sub_00B8DE).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0-d7/a0-a7
	rts


; ----------------------------------------------------------------------
; called from $01449E, $0144AA, $025130
sub_1E41B2:
	movem.l	d0-d4/a0/a2,-(sp)
	move.w	$28(a2),d1
	mulu.w	#$51,d1
	addi.l	#$10080,d1
	moveq	#$3,d2
	adda.w	#$6C,a2
	move.w	#$1A,d3
loc_1E41CE:
	jsr	(sub_00B952).l
	tst.w	d0
	beq.w	loc_1E41DE
	move.w	#$FFFC,(a2)
loc_1E41DE:
	addq.w	#2,a2
	addq.l	#3,d1
	dbra	d3,loc_1E41CE
	movem.l	(sp)+,d0-d4/a0/a2
	rts


; ----------------------------------------------------------------------
; called from $019CF2
sub_1E41EC:
	movem.l	d1/d2/d7,-(sp)
	mulu.w	#$51,d7
	mulu.w	#$3,d1
	addi.l	#$10080,d1
	add.l	d7,d1
	moveq	#$3,d2
	jsr	(sub_00B952).l
	movem.l	(sp)+,d1/d2/d7
	rts


; ----------------------------------------------------------------------
; called from $026D34
sub_1E420E:
	move.w	#$2700,sr
	clr.w	(ram_D338).w
	clr.w	(ram_D33A).w
	move.w	(VDP_HVCOUNTER).l,(RandomSeed).w
	move.w	(VDP_HVCOUNTER).l,(ram_D298).w
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#1,(VideoFlags).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$B800,(HScrollTableAddr).w
	move.w	#$0,(ram_B000).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	jsr	(Text_Print).l
inl_1E4284:
	dc.w	loc_1E428A-inl_1E4284
	dc.b	$FF,$00,$00,$00
loc_1E428A:
	move.l	#$80,d0
	moveq	#$1C,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E42A4:
	dc.w	loc_1E42AA-inl_1E42A4
	dc.b	$FE,$00,$00,$00
loc_1E42AA:
	moveq	#$40,d0
	moveq	#$1C,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	move.w	#$1,d4
	jsr	(Text_Print).l
inl_1E42C4:
	dc.w	loc_1E42CA-inl_1E42C4
	dc.b	$FE,$00,$00,$00
loc_1E42CA:
	movea.l	#Art_IceTexture,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	move.w	#$0,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E42F2:
	dc.w	loc_1E42F8-inl_1E42F2
	dc.b	$FF,$00,$FF,$00
loc_1E42F8:
	movea.l	#Art_TitleScreen,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	subq.w	#1,d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$0,(a0)
	move.w	#$0,(a0)
	move.w	#$2500,sr
	bclr	#2,(VideoFlags).w
	move.w	#$0,-(sp)
	jsr	(sub_092172).l
	move.w	#$64,(FadeCounter).w
	move.w	#$384,(ram_D330).w
	jsr	(sub_1D24EC).l
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
	bsr.w	sub_1E43C4
loc_1E436E:
	jsr	(sub_1D2604).l
	bsr.w	sub_1E43C4
	subq.w	#1,(ram_D330).w
	bmi.w	loc_1E438C
	jsr	(sub_0202D2).l
	btst	#7,d1
	beq.s	loc_1E436E
loc_1E438C:
	rts


; ----------------------------------------------------------------------
sub_1E438E:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_1E43B4
	movea.w	#$B060,a0
	move.w	(ram_B000).w,d1
	move.w	#$1C0,d0
	jsr	(VDP_DMASafe).l
	jsr	(Palette_FadeStep).l
loc_1E43B4:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $1E4352, $1E4356, $1E435A, $1E435E, $1E4362, $1E4366, $1E436A, $1E4374
sub_1E43C4:
	move.w	(FrameCounter).w,d0
loc_1E43C8:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E43C8
	rts


; ----------------------------------------------------------------------
; called from $026D2E
sub_1E43D0:
	move.w	#$2700,sr
	move.w	(VDP_HVCOUNTER).l,(RandomSeed).w
	move.w	(VDP_HVCOUNTER).l,(ram_D298).w
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$5,(ram_B00E).w
	move.w	#$A000,(SpriteTableAddr).w
	move.w	#$7,(ram_B00A).w
	move.w	#$C000,(PlaneAAddr).w
	move.w	#$7,(PlaneSize).w
	move.w	#$F000,(PlaneBAddr).w
	move.w	#$F800,(HScrollTableAddr).w
	move.w	#$FC00,(ram_B000).w
	move.w	#$0,d0
	jsr	(Palette_SetAll).l
	jsr	(Text_Print).l
inl_1E443E:
	dc.w	loc_1E4444-inl_1E443E
	dc.b	$FF,$00,$00,$00
loc_1E4444:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	jsr	(Text_Print).l
inl_1E445A:
	dc.w	loc_1E4460-inl_1E445A
	dc.b	$FE,$00,$00,$00
loc_1E4460:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	move.w	#$1,d4
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Cmd_Tiles,a2
	jsr	(sub_020780).l
	move.l	#Font_Cmd,(FontPtr).w
	jsr	(Text_Print).l
inl_1E4492:
	dc.w	loc_1E4498-inl_1E4492
	dc.b	$FE,$00,$00,$00
loc_1E4498:
	movea.l	#Art_09D99C,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E44BE:
	dc.w	loc_1E44C4-inl_1E44BE
	dc.b	$FF,$01,$0E,$00
loc_1E44C4:
	movea.l	#Art_NHLLicensedLogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	jsr	(Text_Print).l
inl_1E44EA:
	dc.w	loc_1E44F0-inl_1E44EA
	dc.b	$FF,$02,$00,$00
loc_1E44F0:
	movea.l	#Art_NHLPALogo,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	moveq	#$0,d5
	jsr	(TileMap_Draw).l
	move.w	#$2500,sr
	bclr	#2,(VideoFlags).w
	move.w	#$18,(FadeCounter).w
	clr.w	(ram_D04C).w
	clr.w	(ram_D04E).w
	move.l	#dat_006FB6,(ram_D058).w
	bsr.w	sub_1E458C
loc_1E4534:
	bsr.w	sub_1E4626
	jsr	(sub_0202D2).l
	tst.w	(ram_D04C).w
	beq.w	loc_1E454E
	btst	#7,d1
	bne.w	loc_1E458A
loc_1E454E:
	addq.w	#1,(ram_D04E).w
	tst.w	(ram_D04C).w
	bne.w	loc_1E4568
	cmpi.w	#$B4,(ram_D04E).w
	blt.w	loc_1E4588
	bra.w	loc_1E4572
loc_1E4568:
	cmpi.w	#$258,(ram_D04E).w
	blt.w	loc_1E4588
loc_1E4572:
	clr.w	(ram_D04E).w
	addq.w	#1,(ram_D04C).w
	cmpi.w	#$6,(ram_D04C).w
	beq.w	loc_1E458A
	bsr.w	sub_1E458C
loc_1E4588:
	bra.s	loc_1E4534
loc_1E458A:
	rts


; ----------------------------------------------------------------------
; called from $1E4530, $1E4584
sub_1E458C:
	jsr	(Text_Print).l
inl_1E4592:
	dc.w	loc_1E4598-inl_1E4592
	dc.b	$AF,$10,$01,$00
loc_1E4598:
	moveq	#$18,d0
	moveq	#$1B,d1
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	movea.l	(ram_D058).w,a1
	jsr	(Text_PrintCmd).l
inl_1E45B2:
	dc.w	loc_1E45BA-inl_1E45B2
	dc.b	$F8,$05,$01,$10,$01,$00
loc_1E45BA:
	cmpi.w	#$2,(a1)
	beq.w	loc_1E45D6
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1E45CE:
	dc.w	loc_1E45D4-inl_1E45CE
	dc.b	$FD,$10,$FA,$01
loc_1E45D4:
	bra.s	loc_1E45BA
loc_1E45D6:
	addq.l	#2,a1
	move.l	a1,(ram_D058).w
	rts


; ----------------------------------------------------------------------
sub_1E45DE:
	movem.l	d0-d7/a0-a6,-(sp)
	btst	#2,(VideoFlags).w
	bne.w	loc_1E4616
	movea.w	#$B060,a0
	move.w	(ram_B000).w,d1
	move.w	#$1C0,d0
	jsr	(VDP_DMASafe).l
	movea.l	#VDP_DATA,a0
	move.l	#$40000010,$4(a0)
	move.w	(ram_BD38).w,(a0)
	jsr	(Palette_FadeStep).l
loc_1E4616:
	addq.w	#1,(FrameCounter).w
	jsr	(Sound_VBlankUpdate).l
	movem.l	(sp)+,d0-d7/a0-a6
	rte


; ----------------------------------------------------------------------
; called from $1E4534
sub_1E4626:
	move.w	(FrameCounter).w,d0
loc_1E462A:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E462A
	rts


; ----------------------------------------------------------------------
; called from $027024
sub_1E4632:
	movem.l	d0-d7/a0-a6,-(sp)
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
	move.w	#$1,d1
	jsr	(Sound_Call).l
	jsr	(sub_1E4768).l
	move.w	#$B,-(sp)
	jsr	(sub_09205A).l
loc_1E468A:
	move.w	(FrameCounter).w,d0
loc_1E468E:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E468E
	jsr	(sub_0202D2).l
	btst	#7,d1
	bne.w	loc_1E46FE
	addq.w	#1,(ram_D04C).w
	cmpi.w	#$A,(ram_D04C).w
	blt.w	loc_1E46C8
	clr.w	(ram_D04C).w
	addq.w	#1,(ram_B8B2).w
	cmpi.w	#$22,(ram_B8B2).w
	blt.w	loc_1E46C8
	move.w	#$11,(ram_B8B2).w
loc_1E46C8:
	subq.w	#1,(ram_D04E).w
	bpl.w	loc_1E46F2
	move.w	#$A,d0
	jsr	(Random).l
	movea.l	#dat_1E4754,a0
	add.w	d0,d0
	move.w	$0(a0,d0.w),(ram_D04E).w
	move.w	#$B,-(sp)
	jsr	(sub_09205A).l
loc_1E46F2:
	addq.w	#1,(ram_B8B4).w
	jsr	(sub_091FBE).l
	bra.s	loc_1E468A
loc_1E46FE:
	jsr	(sub_01FFA2).l
	jsr	(sub_026404).l
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
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1E4754:
	dc.w	$00E6,$00E1,$00EB,$00D7,$00DC,$00F0,$00FA,$00D2
	dc.w	$00F0,$00F0


; ----------------------------------------------------------------------
; called from $1E467A
sub_1E4768:
	move.l	#VBlank_Main2,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
	move.w	#$B800,(PlaneBAddr).w
	move.w	#$5,(ram_B00E).w
	move.w	#$C000,(SpriteTableAddr).w
	move.w	#$6,(ram_B00A).w
	move.w	#$E000,(PlaneAAddr).w
	move.w	#$6,(PlaneSize).w
	move.w	#$0,d0
	bclr	#5,(VideoFlags).w
	jsr	(Palette_SetAll).l
	move.w	(ram_B000).w,d0
	jsr	(VDP_SetWriteAddr).l
	move.w	#$0,(a0)
	move.w	#$0,d0
	move.w	d0,(a0)
	jsr	(Joypad_ReadAll).l
	jsr	(Text_PrintCmd).l
inl_1E47E2:
	dc.w	loc_1E47EA-inl_1E47E2
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E47EA:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	move.w	#$1,d4
	jsr	(Text_Print).l
inl_1E4802:
	dc.w	loc_1E4808-inl_1E4802
	dc.b	$BF,$00,$00,$00
loc_1E4808:
	movea.l	#Art_StanleyCupWon,a0
	movea.l	a0,a1
	movea.l	a0,a2
	adda.l	(a2)+,a0
	adda.l	(a2)+,a1
	clr.w	d0
	clr.w	d1
	moveq	#$28,d2
	moveq	#$1C,d3
	moveq	#$F,d5
	jsr	(TileMap_Draw).l
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	move.w	#$2500,sr
	rts


; ----------------------------------------------------------------------
; called from $00C506
sub_1E4838:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_C3A4).w,d0
	bsr.w	sub_1E485E
	movea.l	#ram_B360,a0
	move.w	(ram_C3A6).w,d0
	bsr.w	sub_1E485E
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E4846, $1E4854
sub_1E485E:
	move.w	#$5,d1
	movea.l	#dat_1E48B8,a1
loc_1E4868:
	move.w	d1,d2
	asl.w	#7,d2
	move.w	$34(a0,d2.w),d3
	bmi.w	loc_1E4888
	move.b	$0(a1,d3.w),d3
	andi.w	#$FF,d3
	cmp.w	d0,d3
	bgt.w	loc_1E4888
loc_1E4882:
	dbra	d1,loc_1E4868
	rts
loc_1E4888:
	move.w	#$FFFF,$34(a0,d2.w)
	bset	#2,$63(a0,d2.w)
	bset	#2,$62(a0,d2.w)
	move.w	#$FFFF,$18(a0,d2.w)
	movem.l	d0/a3,-(sp)
	move.w	#$30,d0
	lea	$0(a0,d2.w),a3
	jsr	(sub_01F172).l
	movem.l	(sp)+,d0/a3
	bra.s	loc_1E4882
dat_1E48B8:
	dc.b	$00,$04,$05,$02,$01,$03


; ----------------------------------------------------------------------
; called from $1E490E, $1E4946
sub_1E48BE:
	movem.l	a0,-(sp)
	movea.l	#ram_C3A4,a0
	cmp.w	#$1,d0	; general form
	beq.w	loc_1E48D6
	movea.l	#ram_C3A6,a0
loc_1E48D6:
	tst.w	(a0)
	movem.l	(sp)+,a0
	rts


; ----------------------------------------------------------------------
; called from $01983E, $026E66, $026FC2
sub_1E48DE:
	movem.l	d0/d1,-(sp)
	cmpi.w	#$1,(ram_C394).w
	beq.w	loc_1E490A
	cmpi.w	#$1,(ram_C396).w
	beq.w	loc_1E490A
	cmpi.w	#$1,(ram_C398).w
	beq.w	loc_1E490A
	cmpi.w	#$1,(ram_C39A).w
	bne.w	loc_1E491A
loc_1E490A:
	move.w	#$1,d0
	bsr.s	sub_1E48BE
	bne.w	loc_1E491A
	move.w	#$0,(ram_D28A).w
loc_1E491A:
	cmpi.w	#$2,(ram_C394).w
	beq.w	loc_1E4942
	cmpi.w	#$2,(ram_C396).w
	beq.w	loc_1E4942
	cmpi.w	#$2,(ram_C398).w
	beq.w	loc_1E4942
	cmpi.w	#$2,(ram_C39A).w
	bne.w	loc_1E4954
loc_1E4942:
	move.w	#$2,d0
	bsr.w	sub_1E48BE
	bne.w	loc_1E4954
	move.w	#$0,(ram_D28C).w
loc_1E4954:
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $1DB65E
sub_1E495A:
	btst	#7,(ram_C350).w
	beq.w	loc_1E4A1E
	clr.w	(ram_DE8E).w
	clr.w	(ram_D344).w
	clr.w	(ram_D058).w
	jsr	(sub_015A7C).l
	jsr	(sub_026A5E).l
	move.w	(ram_C3AC).w,d7
	jsr	(sub_01A20E).l
	move.w	d0,(ram_DE86).w
	addq.w	#1,d0
	move.w	d0,(ram_DE88).w
	addq.w	#1,d0
	move.w	d0,(ram_DE8A).w
	move.w	#$0,(ram_DE8C).w
	bsr.w	sub_1E50EA
	move.w	#$18,(FadeCounter).w
	bclr	#2,(VideoFlags).w
	clr.w	(ram_D04C).w
	clr.w	(ram_D050).w
loc_1E49B4:
	bsr.w	sub_1E4E02
	move.w	#$0,(ram_D058).w
loc_1E49BE:
	bsr.w	sub_1E4D5C
	bsr.w	sub_1E4FA8
	bsr.w	sub_1E4F32
	move.w	#$2500,sr
loc_1E49CE:
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	tst.w	(ram_DE8E).w
	bne.w	loc_1E49F4
	btst	#7,d1
	beq.w	loc_1E49F4
	bne.w	loc_1E4A5C
loc_1E49F4:
	btst	#7,d1
	bne.w	loc_1E4A1E
	move.w	#$1,d0
	btst	#1,d1
	bne.w	loc_1E4CF8
	move.w	#$FFFF,d0
	btst	#0,d1
	bne.w	loc_1E4CF8
	btst	#5,d1
	bne.w	loc_1E4A5C
	bra.s	loc_1E49CE
loc_1E4A1E:
	clr.w	(ram_DE92).w
	clr.w	(ram_DE94).w
	clr.w	(ram_DE8E).w
	clr.w	(ram_DE90).w
	clr.w	(ram_DE98).w
	clr.w	(ram_DE9A).w
	clr.w	(ram_DE9C).w
	clr.w	(ram_DE9E).w
	clr.w	(ram_DEA0).w
	clr.w	(ram_DEA2).w
	bclr	#4,(ram_C33C).w
	move.w	#$FFFF,(ram_C066).w
	move.l	#SaveDataMirror,(ram_B050).w
	rts
loc_1E4A5C:
	movea.l	#ram_C732,a2
	tst.w	(ram_DE8E).w
	bne.w	loc_1E4A7C
	move.w	#$1,(ram_DE8E).w
	bsr.w	sub_1E52C2
	bsr.w	sub_1E522A
	bra.w	loc_1E49B4
loc_1E4A7C:
	movea.l	#ram_DE86,a0
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E4A92
	movea.l	#ram_DE8C,a0
loc_1E4A92:
	move.w	(ram_D058).w,d0
	asl.w	#1,d0
	move.w	$0(a0,d0.w),d6
	jsr	(sub_01A268).l
	move.w	d0,d1
	jsr	(sub_01A2D0).l
	sub.w	d1,d0
	subq.w	#1,d0
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E4ABE
	move.w	d1,d0
	subq.w	#1,d0
	clr.w	d1
loc_1E4ABE:
	move.w	d0,(ram_D056).w
	clr.w	(ram_D050).w
	clr.w	(ram_D04E).w
	movea.w	#$D14C,a0
	clr.w	d2
loc_1E4AD0:
	move.b	d1,$0(a0,d2.w)
	cmp.w	d1,d6
	bne.w	loc_1E4ADE
	move.w	d2,(ram_D04E).w
loc_1E4ADE:
	addq.w	#1,d1
	addq.w	#1,d2
	dbra	d0,loc_1E4AD0
	move.w	sr,-(sp)
	move.l	a2,-(sp)
	bsr.w	sub_1E4DE8
	move.w	#$1,d4
	movea.l	(sp)+,a2
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow).l
inl_1E4B00:
	dc.w	loc_1E4B16-inl_1E4B00
	dc.b	$F8,$04,$01,$03,$01
	dc.b	"(select player)"
loc_1E4B16:
	clr.w	d0
	bsr.w	sub_1E4B80
	move.w	(sp)+,sr
loc_1E4B1E:
	move.w	#$2500,sr
	jsr	(sub_019BF0).l
	jsr	(sub_01A7B4).l
	jsr	(Joypad_Repeat).l
	btst	#7,d1
	bne.w	loc_1E49BE
	btst	#5,d1
	bne.w	loc_1E4BB4
	moveq	#$1,d0
	btst	#1,d1
	bne.w	loc_1E4B7A
	btst	#3,d1
	bne.w	loc_1E4B6A
	moveq	#-$1,d0
	btst	#0,d1
	bne.w	loc_1E4B7A
	btst	#2,d1
	bne.w	loc_1E4B6A
	bra.s	loc_1E4B1E
loc_1E4B6A:
	add.w	(ram_D04C).w,d0
	bmi.s	loc_1E4B1E
	move.w	d0,(ram_D04C).w
	bsr.w	sub_1E4BE4
	bra.s	loc_1E4B1E
loc_1E4B7A:
	bsr.w	sub_1E4B80
	bra.s	loc_1E4B1E


; ----------------------------------------------------------------------
; called from $1E4B18, $1E4B7A
sub_1E4B80:
	add.w	(ram_D04E).w,d0
	bmi.w	loc_1E4BB2
	cmp.w	(ram_D056).w,d0
	bgt.w	loc_1E4BB2
	move.w	d0,(ram_D04E).w
	cmp.w	(ram_D050).w,d0
	bgt.w	loc_1E4BA0
	move.w	d0,(ram_D050).w
loc_1E4BA0:
	subq.w	#4,d0
	cmp.w	(ram_D050).w,d0
	ble.w	loc_1E4BAE
	move.w	d0,(ram_D050).w
loc_1E4BAE:
	bsr.w	sub_1E4BE4
loc_1E4BB2:
	rts
loc_1E4BB4:
	movea.w	#$D14C,a3
	adda.w	(ram_D04E).w,a3
	clr.w	d0
	move.b	(a3),d0
	move.w	(ram_D058).w,d2
	movea.l	#ram_DE86,a0
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E4BDA
	movea.l	#ram_DE8C,a0
loc_1E4BDA:
	asl.w	#1,d2
	move.w	d0,$0(a0,d2.w)
	bra.w	loc_1E49BE


; ----------------------------------------------------------------------
; called from $1E4B74, $1E4BAE
sub_1E4BE4:
	jsr	(Text_Print).l
inl_1E4BEA:
	dc.w	loc_1E4BF0-inl_1E4BEA
	dc.b	$BF,$17,$01,$00
loc_1E4BF0:
	movea.l	#dat_028AAE,a1
	cmpi.w	#$5,(ram_D058).w
	bne.w	loc_1E4C06
	movea.l	#dat_028C10,a1
loc_1E4C06:
	move.w	(ram_D04C).w,d0
	bra.w	loc_1E4C12
loc_1E4C0E:
	adda.w	(a1),a1
	addq.w	#4,a1
loc_1E4C12:
	tst.w	(a1)
	dbmi	d0,loc_1E4C0E
	bpl.w	loc_1E4C22
	subq.w	#1,(ram_D04C).w
	bra.s	loc_1E4BF0
loc_1E4C22:
	cmpa.l	#dat_028AAE,a1
	bne.w	loc_1E4C32
	movea.l	#dat_1E4CB8,a1
loc_1E4C32:
	cmpa.l	#dat_028C10,a1
	bne.w	loc_1E4C42
	movea.l	#dat_1E4CCE,a1
loc_1E4C42:
	jsr	(Text_PrintNarrow_Worker).l
	move.l	(a1),d4
	movea.w	#$D14C,a3
	move.w	(ram_D050).w,d2
	move.w	(ram_D056).w,d1
	sub.w	d2,d1
	cmp.w	#$4,d1	; general form
	bls.w	loc_1E4C62
	moveq	#$4,d1
loc_1E4C62:
	move.w	#$4,(TextY).w
loc_1E4C68:
	jsr	(Text_PrintCmd).l
inl_1E4C6E:
	dc.w	loc_1E4C92-inl_1E4C6E
	dc.b	$FE,$04,$FD,$02,$FA,$01
	dc.b	"                         "
	dc.b	$FD,$02,$00
loc_1E4C92:
	cmp.w	(ram_D04E).w,d2
	bne.w	loc_1E4CA4
	jsr	(Text_PrintCmd).l
inl_1E4CA0:
	dc.w	loc_1E4CA4-inl_1E4CA0
	dc.b	$FE,$07
loc_1E4CA4:
	clr.w	d0
	move.b	$0(a3,d2.w),d0
	jsr	(sub_019C0A).l
	addq.w	#1,d2
	dbra	d1,loc_1E4C68
	rts
dat_1E4CB8:
	dc.b	$00,$12
	dc.b	"    Overall    ]"
	dc.b	$1F,$3A,$00,$0A
dat_1E4CCE:
	dc.w	$0012,$2020,$2020,$4F76,$6572,$616C,$6C20,$2020
	dc.w	$205D,$1B0F,$000A,$4A78,$DE8E,$6700,$FCE4,$B078
	dc.w	$D058,$6700,$FCDC,$6000,$0056
loc_1E4CF8:
	tst.w	(ram_DE8E).w
	bne.w	loc_1E4D2A
	add.w	(ram_DE84).w,d0
	bmi.w	loc_1E4D16
	cmp.w	#$4,d0	; general form
	blt.w	loc_1E4D1A
	clr.w	d0
	bra.w	loc_1E4D1A
loc_1E4D16:
	move.w	#$3,d0
loc_1E4D1A:
	move.w	d0,(ram_DE84).w
	bsr.w	sub_1E4FA8
	bsr.w	sub_1E4F32
	bra.w	loc_1E49CE
loc_1E4D2A:
	move.w	d0,-(sp)
	bsr.w	sub_1E52A4
	move.w	d0,d1
	subq.w	#1,d1
	move.w	(sp)+,d0
	add.w	(ram_D058).w,d0
	bmi.w	loc_1E4D4A
	cmp.w	d1,d0
	ble.w	loc_1E4D4C
	clr.w	d0
	bra.w	loc_1E4D4C
loc_1E4D4A:
	move.w	d1,d0
loc_1E4D4C:
	move.w	d0,(ram_D058).w
	bsr.w	sub_1E4FA8
	bsr.w	sub_1E4F32
	bra.w	loc_1E49CE


; ----------------------------------------------------------------------
; called from $1E49BE
sub_1E4D5C:
	bsr.w	sub_1E4DE8
	movem.l	d0-d5/a0-a2,-(sp)
	move.l	a2,-(sp)
	bset	#2,(ram_C356).w
	jsr	(Text_PrintBig).l
inl_1E4D72:
	dc.w	loc_1E4D84-inl_1E4D72
	dc.b	$BF,$09,$01
	dc.b	"SKILLS SETUP",0
loc_1E4D84:
	move.w	(ram_B02E).w,d4
	jsr	(Text_Print).l
inl_1E4D8E:
	dc.w	loc_1E4D94-inl_1E4D8E
	dc.b	$BF,$01,$04,$00
loc_1E4D94:
	movea.l	(sp),a2
	move.w	(ram_C3AC).w,d7
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	move.w	#$1,d4
	tst.w	(ram_DE8E).w
	bne.w	loc_1E4DCA
	jsr	(Text_PrintFont).l
inl_1E4DB4:
	dc.w	loc_1E4DC6-inl_1E4DB4
	dc.b	$8F,$18,$07
	dc.b	"start-select",0
loc_1E4DC6:
	bra.w	loc_1E4DE0
loc_1E4DCA:
	jsr	(Text_PrintFont).l
inl_1E4DD0:
	dc.w	loc_1E4DE0-inl_1E4DD0
	dc.b	$8F,$18,$07
	dc.b	"start-exit",0
loc_1E4DE0:
	movea.l	(sp)+,a2
	movem.l	(sp)+,d0-d5/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $1E4AEA, $1E4D5C
sub_1E4DE8:
	jsr	(Text_Print).l
inl_1E4DEE:
	dc.w	loc_1E4DF4-inl_1E4DEE
	dc.b	$BF,$00,$00,$00
loc_1E4DF4:
	moveq	#$28,d0
	moveq	#$E,d1
	move.w	#$87FF,d2
	jmp	(Text_FillRect).l


; ----------------------------------------------------------------------
; called from $1E49B4
sub_1E4E02:
	tst.w	(ram_DE8E).w
	beq.w	loc_1E4EB4
	jsr	(Text_PrintCmd).l
inl_1E4E10:
	dc.w	loc_1E4E1A-inl_1E4E10
	dc.w	$FE04,$FF01,$FD00,$FC0A
loc_1E4E1A:
	bset	#2,(ram_C356).w
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E4E42
	jsr	(Text_PrintNarrow).l
inl_1E4E30:
	dc.w	loc_1E4E3E-inl_1E4E30
	dc.b	$FD,$11,$FC,$0F
	dc.b	"Goalie"
	dc.b	$FE,$04
loc_1E4E3E:
	bra.w	loc_1E4E58
loc_1E4E42:
	jsr	(Text_PrintNarrow).l
inl_1E4E48:
	dc.w	loc_1E4E58-inl_1E4E48
	dc.b	$FD,$11,$FC,$0F
	dc.b	"Players"
	dc.b	$FE,$04,$00
loc_1E4E58:
	bclr	#2,(ram_C356).w
	movem.l	d0-d2,-(sp)
	bsr.w	sub_1E52A4
	move.w	d0,d2
	subq.w	#1,d2
	move.w	#$1,d0
	move.w	#$1,d1
	jsr	(Text_PrintCmd).l
inl_1E4E78:
	dc.w	loc_1E4E7E-inl_1E4E78
	dc.b	$FD,$0D,$FC,$12
loc_1E4E7E:
	jsr	(Num_ToDecimal).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1E4E94:
	dc.w	loc_1E4E9A-inl_1E4E94
	dc.b	$2E,$20,$20,$00
loc_1E4E9A:
	addq.w	#1,(TextY).w
	move.w	(sp)+,(TextX).w
	addq.w	#1,d0
	dbra	d2,loc_1E4E7E
	movem.l	(sp)+,d0-d2
	bclr	#2,(ram_C356).w
	rts
loc_1E4EB4:
	jsr	(Text_PrintCmd).l
inl_1E4EBA:
	dc.w	loc_1E4EC4-inl_1E4EBA
	dc.w	$FE04,$FF01,$FD00,$FC0A
loc_1E4EC4:
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow).l
inl_1E4ED0:
	dc.w	loc_1E4EDE-inl_1E4ED0
	dc.b	$FD,$11,$FC,$0F
	dc.b	"Events"
	dc.b	$FE,$04
loc_1E4EDE:
	bclr	#2,(ram_C356).w
	jsr	(Text_PrintCmd).l
inl_1E4EEA:
	dc.w	loc_1E4EF4-inl_1E4EEA
	dc.w	$FD0E,$FC12,$312E,$2000
loc_1E4EF4:
	jsr	(Text_PrintCmd).l
inl_1E4EFA:
	dc.w	loc_1E4F04-inl_1E4EFA
	dc.w	$FD0E,$FC13,$322E,$2000
loc_1E4F04:
	jsr	(Text_PrintCmd).l
inl_1E4F0A:
	dc.w	loc_1E4F14-inl_1E4F0A
	dc.w	$FD0E,$FC14,$332E,$2000
loc_1E4F14:
	jsr	(Text_PrintCmd).l
inl_1E4F1A:
	dc.w	loc_1E4F24-inl_1E4F1A
	dc.w	$FD0E,$FC15,$342E,$2000
loc_1E4F24:
	bset	#2,(ram_C356).w
	bclr	#2,(ram_C356).w
	rts


; ----------------------------------------------------------------------
; called from $1E49C6, $1E4D22, $1E4D54
sub_1E4F32:
	tst.w	(ram_DE8E).w
	beq.w	loc_1E4FA6
	bset	#2,(ram_C356).w
	jsr	(Text_PrintNarrow).l
inl_1E4F46:
	dc.w	loc_1E4F5E-inl_1E4F46
	dc.b	$F8,$04,$01,$15,$0C
	dc.b	"                ",0
loc_1E4F5E:
	jsr	(Text_PrintCmd).l
inl_1E4F64:
	dc.w	loc_1E4F6C-inl_1E4F64
	dc.b	$F8,$04,$01,$1E,$0C,$00
loc_1E4F6C:
	movea.l	#ram_DE86,a1
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E4F82
	movea.l	#ram_DE8C,a1
loc_1E4F82:
	move.w	(ram_D058).w,d0
	asl.w	#1,d0
	move.w	$0(a1,d0.w),d0
	jsr	(sub_02861C).l
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	jsr	(Text_PrintNarrow_Worker).l
	bclr	#2,(ram_C356).w
loc_1E4FA6:
	rts


; ----------------------------------------------------------------------
; called from $1E49C2, $1E4D1E, $1E4D50
sub_1E4FA8:
	movem.l	d0-d7/a0-a6,-(sp)
	tst.w	(ram_DE8E).w
	bne.w	loc_1E5052
	jsr	(Text_PrintCmd).l
inl_1E4FBA:
	dc.w	loc_1E4FC2-inl_1E4FBA
	dc.b	$FD,$11,$FC,$12,$FE,$04
loc_1E4FC2:
	move.w	#$0,d1
	movea.l	#dat_1E5012,a0
loc_1E4FCC:
	move.w	d1,d0
	movea.l	a0,a1
	jsr	(List_Skip).l
	move.w	(TextX).w,-(sp)
	cmp.w	(ram_DE84).w,d1
	bne.w	loc_1E4FEC
	jsr	(Text_PrintCmd).l
inl_1E4FE8:
	dc.w	loc_1E4FEC-inl_1E4FE8
	dc.b	$FE,$07
loc_1E4FEC:
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1E4FF8:
	dc.w	loc_1E4FFC-inl_1E4FF8
	dc.b	$FE,$04
loc_1E4FFC:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	addq.w	#1,d1
	cmp.w	#$4,d1	; general form
	blt.s	loc_1E4FCC
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1E5012:
	dc.b	$00,$14
	dc.b	"puck control relay",0
	dc.b	$0C
	dc.b	"puck blast",0
	dc.b	$0C
	dc.b	"rapid fire",0
	dc.b	$14
	dc.b	"accuracy shooting",0
loc_1E5052:
	jsr	(Text_PrintCmd).l
inl_1E5058:
	dc.w	loc_1E5060-inl_1E5058
	dc.b	$FD,$0D,$FC,$12,$FE,$04
loc_1E5060:
	move.w	#$0,d1
	movea.l	#ram_DE86,a0
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E507A
	movea.l	#ram_DE8C,a0
loc_1E507A:
	move.w	(TextX).w,-(sp)
	move.w	d1,d0
	addq.w	#1,d0
	move.w	d1,-(sp)
	move.w	#$1,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1E509A:
	dc.w	loc_1E50A0-inl_1E509A
	dc.b	$2E,$20,$20,$00
loc_1E50A0:
	move.w	(sp)+,d1
	move.w	d1,d0
	asl.w	#1,d0
	move.w	$0(a0,d0.w),d0
	jsr	(sub_028674).l
	cmp.w	(ram_D058).w,d1
	bne.w	loc_1E50C2
	jsr	(Text_PrintCmd).l
inl_1E50BE:
	dc.w	loc_1E50C2-inl_1E50BE
	dc.b	$FE,$07
loc_1E50C2:
	jsr	(Text_PrintCmd_Worker).l
	jsr	(Text_PrintCmd).l
inl_1E50CE:
	dc.w	loc_1E50D2-inl_1E50CE
	dc.b	$FE,$04
loc_1E50D2:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	addq.w	#1,d1
	bsr.w	sub_1E52A4
	cmp.w	d0,d1
	blt.s	loc_1E507A
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E499C
sub_1E50EA:
	move.l	a2,-(sp)
	bset	#5,(ram_C358).w
	move.l	#VBlank_Main,(VBlankVector).w
	bclr	#0,(VideoFlags).w
	bset	#2,(VideoFlags).w
	bclr	#1,(VideoFlags).w
	move.w	#$0,(ram_B000).w
	move.w	#$B800,(HScrollTableAddr).w
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
	move.w	#$1E,d4
	move.w	d4,(FontTileBase).w
	move.w	d4,(ram_B01E).w
	movea.l	#Font_Menu_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E516E:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E5176:
	move.l	#Font_Menu,(FontPtr).w
	move.w	d4,(ram_B020).w
	movea.l	#Art_1AAD96_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B018).w
	move.w	d4,(ram_B014).w
	movea.l	#Font_Narrow_Tiles,a2
	jsr	(Draw_RunScript).l
inl_1E51A2:
	dc.w	$0123,$4567,$89DE,$EEEF
loc_1E51AA:
	bset	#2,(ram_C356).w
	move.l	#Font_Narrow,(FontPtr2).w
	jsr	(Text_PrintCmd).l
inl_1E51BE:
	dc.w	loc_1E51C6-inl_1E51BE
	dc.b	$FF,$01,$FD,$00,$FC,$00
loc_1E51C6:
	moveq	#$28,d0
	moveq	#$1C,d1
	move.w	#$87FF,d2
	jsr	(Text_FillRect).l
	move.w	d4,(ram_B02E).w
	jsr	(Text_Print).l
inl_1E51DE:
	dc.w	loc_1E51E4-inl_1E51DE
	dc.b	$BF,$01,$04,$00
loc_1E51E4:
	movea.l	(sp),a2
	move.w	(ram_C3AC).w,d7
	moveq	#$2,d5
	jsr	(sub_016EF4).l
	bsr.w	sub_1E522A
	jsr	(Text_Print).l
inl_1E51FC:
	dc.w	loc_1E5202-inl_1E51FC
	dc.b	$FE,$00,$00,$00
loc_1E5202:
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
	jsr	(sub_1DCE06).l
	movea.l	(sp)+,a2
	rts


; ----------------------------------------------------------------------
; called from $1E4A74, $1E51F2
sub_1E522A:
	move.w	(FontTileBase).w,-(sp)
	move.w	(ram_B01E).w,(FontTileBase).w
	tst.w	(ram_DE8E).w
	bne.w	loc_1E526E
	jsr	(Text_PrintFont).l
inl_1E5242:
	dc.w	loc_1E526A-inl_1E5242
	dc.b	$8F,$09,$19
	dc.b	"{}-highlight event"
	dc.b	$8F,$0A,$1A
	dc.b	"c-select event"
loc_1E526A:
	bra.w	loc_1E529E
loc_1E526E:
	jsr	(Text_PrintFont).l
inl_1E5274:
	dc.w	loc_1E529E-inl_1E5274
	dc.b	$8F,$09,$19
	dc.b	"{}-highlight player"
	dc.b	$8F,$0A,$1A
	dc.b	"c-select player"
loc_1E529E:
	move.w	(sp)+,(FontTileBase).w
	rts


; ----------------------------------------------------------------------
; called from $1E4D2C, $1E4E62, $1E50DC
sub_1E52A4:
	move.l	a0,-(sp)
	move.w	(ram_DE84).w,d0
	add.w	d0,d0
	movea.l	#dat_1E52BA,a0
	move.w	$0(a0,d0.w),d0
	movea.l	(sp)+,a0
	rts
dat_1E52BA:
	dc.w	$0003,$0003,$0001,$0001


; ----------------------------------------------------------------------
; called from $1E4A70
sub_1E52C2:
	jsr	(Text_Print).l
inl_1E52C8:
	dc.w	loc_1E52CE-inl_1E52C8
	dc.b	$BF,$00,$0F,$00
loc_1E52CE:
	moveq	#$28,d0
	moveq	#$C,d1
	move.w	#$87FF,d2
	jmp	(Text_FillRect).l


; ----------------------------------------------------------------------
; called from $00F6C2
sub_1E52DC:
	bclr	#1,$62(a3)
	beq.w	loc_1E5330
	bclr	#4,(ram_C350).w
	bset	#7,(ram_C34C).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	bclr	#7,(ram_C34A).w
	bclr	#2,(ram_B7C2).w
	bclr	#1,$62(a3)
	bset	#0,(ram_C33A).w
	bset	#1,(ram_C34A).w
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	clr.w	(ram_DE8E).w
	st	$40(a3)
	st	$42(a3)
loc_1E5330:
	movea.w	#$C732,a2
	move.w	#$32,d0
	jmp	(sub_01F172).l


; ----------------------------------------------------------------------
; called from $00F6C6
sub_1E533E:
	bclr	#1,$62(a3)
	beq.w	loc_1E551C
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	(sub_01FFA2).l
loc_1E5352:
	btst	#0,(VideoFlags).w
	bne.s	loc_1E5352
	cmpi.w	#$258,(ram_B8B4).w
	bls.w	loc_1E5370
	move.w	#$258,(ram_B8B4).w
	addi.w	#$14,(ram_B8BA).w
loc_1E5370:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_RefereeCutscene_Tiles,a2
	jsr	(sub_020780).l
	bset	#1,(ram_DEA2).w
	bset	#0,(ram_DEA2).w
	bclr	#2,(ram_C34A).w
	cmpi.w	#$0,(ram_DE84).w
	bne.w	loc_1E53A6
	move.w	#$F0,(ram_D344).w
	bra.w	loc_1E53C4
loc_1E53A6:
	cmpi.w	#$3,(ram_DE84).w
	bne.w	loc_1E53BE
	clr.w	(ram_DEA6).w
	move.w	#$32,(ram_D344).w
	bra.w	loc_1E53C4
loc_1E53BE:
	bclr	#0,(ram_DEA2).w
loc_1E53C4:
	bset	#3,(VideoFlags).w
	bclr	#0,(ram_C33C).w
	bclr	#0,(ram_C340).w
	move.w	#$3E8,(ram_BF18).w
	move.w	#$3E8,(ram_BF16).w
	clr.b	(ram_BFBC).w
	st	(ram_C452).w
	bclr	#1,(ram_C33E).w
	st	(ram_BF14).w
	jsr	(sub_022252).l
	clr.w	(ram_BD30).w
	clr.w	(ram_BD34).w
	jsr	(sub_1E5530).l
	clr.w	(ram_B778).w
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
	cmpi.w	#$1,(ram_DE84).w
	bne.w	loc_1E5480
	bset	#6,(ram_C33C).w
	move.w	(ram_B760).w,(ram_BFDE).w
	move.w	(ram_B774).w,(ram_BFE0).w
	addi.w	#$A,(ram_BFE0).w
	bra.w	loc_1E54C6
loc_1E5480:
	cmpi.w	#$3,(ram_DE84).w
	bne.w	loc_1E54A0
	bset	#6,(ram_C33C).w
	move.w	#$0,(ram_BFDE).w
	move.w	(ram_B774).w,(ram_BFE0).w
	bra.w	loc_1E54C6
loc_1E54A0:
	cmpi.w	#$0,(ram_DE84).w
	bne.w	loc_1E54C0
	bset	#6,(ram_C33C).w
	move.w	#$51,(ram_BFDE).w
	move.w	#$FF9E,(ram_BFE0).w
	bra.w	loc_1E54C6
loc_1E54C0:
	bclr	#6,(ram_C33C).w
loc_1E54C6:
	moveq	#$64,d4
loc_1E54C8:
	jsr	(sub_01B29A).l
	dbra	d4,loc_1E54C8
	move.w	#$3C,(ram_BFE2).w
	jsr	(sub_0253C4).l
	movea.w	#$C732,a2
	jsr	(sub_025122).l
	jsr	(sub_1E5562).l
	adda.w	#$39E,a2
	jsr	(sub_025122).l
	jsr	(sub_1E5562).l
	jsr	(sub_026A0C).l
	jsr	(sub_1E5976).l
	bset	#2,(ram_C33E).w
	move.w	#$18,(FadeCounter).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_1E551C:
	move.w	#$18,d0
	jsr	(sub_01F172).l
	clr.w	$28(a3)
	clr.w	$2A(a3)
	rts


; ----------------------------------------------------------------------
; called from $011C84, $1E5402, $1E6642
sub_1E5530:
	movem.l	d0/a0,-(sp)
	move.w	(ram_DE84).w,d0
	asl.w	#2,d0
	movea.l	#dat_1E5552,a0
	move.w	$0(a0,d0.w),(ram_B760).w
	move.w	$2(a0,d0.w),(ram_B774).w
	movem.l	(sp)+,d0/a0
	rts
dat_1E5552:
	dc.w	$0051,$00F4,$0000,$00CA,$0033,$00E6,$0051,$011E


; ----------------------------------------------------------------------
; called from $1E54E8, $1E54F8
sub_1E5562:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.w	$22(a2),a3
	moveq	#$0,d4
loc_1E556C:
	cmpa.l	#ram_C732,a2
	beq.w	loc_1E5766
	cmpi.w	#$2,(ram_DE84).w
	beq.w	loc_1E56F4
	cmpi.w	#$0,(ram_DE84).w
	beq.w	loc_1E5680
	cmpi.w	#$3,(ram_DE84).w
	bne.w	loc_1E5946
	cmp.w	#$0,d4	; general form
	bne.w	loc_1E55D0
	move.w	#$36,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.w	#$51,(a3)
	move.w	#$11E,$14(a3)
	move.w	#$5,$54(a3)
	move.b	(ram_DE89).w,$61(a3)
	move.w	#$870,d1
	move.w	$52(a3),(ram_B7C0).w
	bra.w	loc_1E5926
loc_1E55D0:
	cmp.w	#$1,d4	; general form
	bne.w	loc_1E5606
	move.w	#$36,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.w	#$FFAF,(a3)
	move.w	#$11E,$14(a3)
	move.w	#$3,$54(a3)
	move.b	(ram_DE8B).w,$61(a3)
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E5606:
	cmp.w	#$2,d4	; general form
	bne.w	loc_1E5644
	move.w	#$FFEE,(a3)
	move.w	#$8,$18(a3)
loc_1E5618:
	move.w	#$37,d0
	jsr	(sub_01F172).l
	move.w	#$0,$34(a3)
	move.w	#$11E,$14(a3)
	clr.w	$54(a3)
	clr.b	$61(a3)
	bset	#7,$64(a3)
	move.w	#$3886,d1
	bra.w	loc_1E5926
loc_1E5644:
	cmp.w	#$3,d4	; general form
	bne.w	loc_1E5658
	move.w	#$FFEE,(a3)
	move.w	#$0,$18(a3)
	bra.s	loc_1E5618
loc_1E5658:
	cmp.w	#$4,d4	; general form
	bne.w	loc_1E566C
	move.w	#$12,(a3)
	move.w	#$8,$18(a3)
	bra.s	loc_1E5618
loc_1E566C:
	cmp.w	#$5,d4	; general form
	bne.w	loc_1E5946
	move.w	#$12,(a3)
	move.w	#$0,$18(a3)
	bra.s	loc_1E5618
loc_1E5680:
	movem.l	d4/a0,-(sp)
	movea.l	#dat_1E56C4,a0
	asl.w	#3,d4
	move.w	$0(a0,d4.w),(a3)
	move.w	$2(a0,d4.w),$14(a3)
	move.w	$6(a0,d4.w),d0
	jsr	(sub_01F172).l
	move.w	#$0,$34(a3)
	move.w	$4(a0,d4.w),$54(a3)
	clr.b	$61(a3)
	move.w	#$0,d1
	asr.w	#3,d4
	addq.w	#2,d4
	move.w	d4,$44(a3)
	movem.l	(sp)+,d4/a0
	bra.w	loc_1E5926
dat_1E56C4:
	dc.w	$0033,$00A3,$0004,$003A,$006F,$008F,$0002,$0039
	dc.w	$0051,$005D,$0004,$003A,$006F,$0028,$0002,$0039
	dc.w	$0033,$0014,$0004,$003A,$0051,$FFDD,$0004,$0039
loc_1E56F4:
	cmp.w	#$0,d4	; general form
	beq.w	loc_1E5738
	cmp.w	#$1,d4	; general form
	bne.w	loc_1E5946
	move.w	#$33,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.w	#$3B,(a3)
	move.w	#$E6,$14(a3)
	move.w	#$7,$54(a3)
	move.b	(ram_DE87).w,$61(a3)
	move.w	$52(a3),(ram_B7C0).w
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E5738:
	move.w	#$30,d0
	jsr	(sub_01F172).l
	move.w	#$3,$34(a3)
	move.w	#$FFC5,(a3)
	move.w	#$E6,$14(a3)
	move.w	#$1,$54(a3)
	move.b	(ram_DE87).w,$61(a3)
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E5766:
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_1E57A6
	cmp.w	#$5,d4	; general form
	bne.w	loc_1E5946
	move.w	#$E,d0
	jsr	(sub_01F172).l
	move.w	#$0,$34(a3)
	move.b	(ram_DE8D).w,$61(a3)
	move.w	#$0,(a3)
	move.w	#$116,$14(a3)
	move.w	#$4,$54(a3)
	move.w	#$5D4,d1
	bra.w	loc_1E5926
loc_1E57A6:
	cmpi.w	#$3,(ram_DE84).w
	bne.w	loc_1E57E6
	cmp.w	#$0,d4	; general form
	bne.w	loc_1E57E6
	move.w	#$35,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.w	#$0,(a3)
	move.w	#$CA,$14(a3)
	move.w	#$0,$54(a3)
	move.b	(ram_DE87).w,$61(a3)
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E57E6:
	cmpi.w	#$1,(ram_DE84).w
	bne.w	loc_1E583E
	tst.w	d4
	bne.w	loc_1E5946
	move.w	#$34,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	movem.l	d1/a6,-(sp)
	movea.l	#ram_DE86,a6
	move.w	(ram_DE92).w,d1
	add.w	d1,d1
	move.w	$0(a6,d1.w),d0
	move.b	d0,$61(a3)
	movem.l	(sp)+,d1/a6
	move.w	#$0,(a3)
	move.w	#$6C,$14(a3)
	move.w	#$0,$54(a3)
	st	(ram_B7C0).w
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E583E:
	cmpi.w	#$0,(ram_DE84).w
	bne.w	loc_1E595A
	tst.w	d4
	bne.w	loc_1E5880
	move.w	#$38,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.b	(ram_DE87).w,$61(a3)
	move.w	#$FF85,$14(a3)
	move.w	#$51,(a3)
	move.w	#$0,$54(a3)
	st	(ram_B7C0).w
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E5880:
	cmp.w	#$1,d4	; general form
	bne.w	loc_1E58B6
	move.w	#$30,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.b	(ram_DE89).w,$61(a3)
	move.w	#$FF67,$14(a3)
	move.w	#$51,(a3)
	move.w	#$0,$54(a3)
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E58B6:
	cmp.w	#$2,d4	; general form
	bne.w	loc_1E58EC
	move.w	#$30,d0
	jsr	(sub_01F172).l
	move.w	#$4,$34(a3)
	move.b	(ram_DE8B).w,$61(a3)
	move.w	#$FF49,$14(a3)
	move.w	#$51,(a3)
	move.w	#$0,$54(a3)
	move.w	#$870,d1
	bra.w	loc_1E5926
loc_1E58EC:
	cmp.w	#$3,d4	; general form
	bne.w	loc_1E5946
	move.w	#$51,(a3)
	move.w	#$DB,$14(a3)
	move.w	#$39,d0
	jsr	(sub_01F172).l
	move.w	#$1,$44(a3)
	move.w	#$0,$34(a3)
	move.w	#$6,$54(a3)
	clr.b	$61(a3)
	move.w	#$38E8,d1
	bra.w	loc_1E5926
loc_1E5926:
	jsr	(sub_01F3B2).l
	clr.w	d3
	move.b	$61(a3),d3
	add.w	d3,d3
	move.w	#$FFFF,$6C(a2,d3.w)
	lsr.w	#1,d3
	jsr	(sub_025470).l
	bra.w	loc_1E595A
loc_1E5946:
	st	$34(a3)
	bset	#2,$63(a3)
	move.w	#$30,d0
	jsr	(sub_01F172).l
loc_1E595A:
	st	$61(a3)
	st	$60(a3)
	adda.w	#$80,a3
	addq.w	#1,d4
	cmp.w	#$6,d4	; general form
	blt.w	loc_1E556C
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $1E5504
sub_1E5976:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,(ram_C38A).w
	move.w	#$FFFF,(ram_C38C).w
	move.w	#$FFFF,(ram_C38E).w
	cmpi.w	#$2,(ram_DE84).w
	beq.w	loc_1E5A22
	cmpi.w	#$1,(ram_DE84).w
	beq.w	loc_1E59FA
	cmpi.w	#$3,(ram_DE84).w
	beq.w	loc_1E59D2
	move.w	#$0,(ram_C388).w
	move.w	#$1,(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	movea.l	#ram_B060,a3
	bset	#3,$62(a3)
	bra.w	loc_1E5A4A
loc_1E59D2:
	move.w	#$0,(ram_C388).w
	move.w	#$1,(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	movea.l	#ram_B060,a3
	bset	#3,$62(a3)
	bra.w	loc_1E5A4A
loc_1E59FA:
	move.w	#$0,(ram_C388).w
	move.w	#$1,(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	movea.l	#ram_B060,a3
	bset	#3,$62(a3)
	bra.w	loc_1E5A4A
loc_1E5A22:
	move.w	#$5,(ram_C388).w
	move.w	#$1,(ram_C394).w
	clr.w	(ram_C396).w
	clr.w	(ram_C398).w
	clr.w	(ram_C39A).w
	movea.l	#ram_B2E0,a3
	bset	#3,$62(a3)
	bra.w	loc_1E5A4A
loc_1E5A4A:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_1E5A50:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,d0
	jsr	(sub_021BF4).l
	jsr	(Text_Print).l
inl_1E5A64:
	dc.w	loc_1E5A6A-inl_1E5A64
	dc.b	$BF,$03,$02,$00
loc_1E5A6A:
	moveq	#$1B,d0
	moveq	#$C,d1
	jsr	(Text_PrintDigitsBig).l
	lea	dat_1E5D2C(pc),a1
	move.w	(ram_DE84).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	cmpi.w	#$2,(ram_DE84).w
	beq.w	loc_1E5CBC
	cmpi.w	#$1,(ram_DE84).w
	beq.w	loc_1E5B32
	cmpi.w	#$3,(ram_DE84).w
	beq.w	loc_1E5C42
	bsr.w	sub_1E66A6
	move.w	(TextX).w,-(sp)
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E5AB8:
	dc.w	loc_1E5ACE-inl_1E5AB8
	dc.b	"Skate north to puck",0
loc_1E5ACE:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5ADC:
	dc.w	loc_1E5AF2-inl_1E5ADC
	dc.b	"then carry puck back"
loc_1E5AF2:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5B00:
	dc.w	loc_1E5B16-inl_1E5B00
	dc.b	"following cones and",0
loc_1E5B16:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5B24:
	dc.w	loc_1E5B2E-inl_1E5B24
	dc.b	"arrows.",0
loc_1E5B2E:
	bra.w	loc_1E5D26
loc_1E5B32:
	movea.l	#ram_DE86,a6
	move.w	(ram_DE92).w,d1
	add.w	d1,d1
	move.w	$0(a6,d1.w),d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5B5E:
	dc.w	loc_1E5B6A-inl_1E5B5E
	dc.b	" - Shooter"
loc_1E5B6A:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5B78:
	dc.w	loc_1E5B86-inl_1E5B78
	dc.b	"Turn number "
loc_1E5B86:
	move.w	#$1,d1
	move.w	(ram_DE94).w,d0
	addq.w	#1,d0
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5BA2:
	dc.w	loc_1E5BAE-inl_1E5BA2
	dc.b	" out of 3",0
loc_1E5BAE:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E5BBC:
	dc.w	loc_1E5BD6-inl_1E5BBC
	dc.b	"Skate to puck and shoot",0
loc_1E5BD6:
	addq.w	#1,(TextY).w
	move.w	(sp),(TextX).w
	jsr	(Text_Print).l
inl_1E5BE4:
	dc.w	loc_1E5BFA-inl_1E5BE4
	dc.b	"with maximum force.",0
loc_1E5BFA:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5C08:
	dc.w	loc_1E5C1E-inl_1E5C08
	dc.b	"You are allowed one",0
loc_1E5C1E:
	addq.w	#1,(TextY).w
	move.w	(sp)+,(TextX).w
	jsr	(Text_Print).l
inl_1E5C2C:
	dc.w	loc_1E5C3E-inl_1E5C2C
	dc.b	"swing per turn.",0
loc_1E5C3E:
	bra.w	loc_1E5D26
loc_1E5C42:
	move.w	(ram_DE86).w,d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5C62:
	dc.w	loc_1E5C6E-inl_1E5C62
	dc.b	" - Shooter"
loc_1E5C6E:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E5C7C:
	dc.w	loc_1E5C92-inl_1E5C7C
	dc.b	"Hit as many targets",0
loc_1E5C92:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5CA0:
	dc.w	loc_1E5CB8-inl_1E5CA0
	dc.b	"with puck as you can.",0
loc_1E5CB8:
	bra.w	loc_1E5D26
loc_1E5CBC:
	move.w	(ram_DE8C).w,d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5CDC:
	dc.w	loc_1E5CE8-inl_1E5CDC
	dc.b	" - Goalie",0
loc_1E5CE8:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E5CF6:
	dc.w	loc_1E5D0A-inl_1E5CF6
	dc.b	"Make as many saves"
loc_1E5D0A:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E5D18:
	dc.w	loc_1E5D26-inl_1E5D18
	dc.b	"as you can.",0
loc_1E5D26:
	movem.l	(sp)+,d0-d7/a0-a6
	rts
dat_1E5D2C:
	dc.w	$0026,$F804,$0104,$0320,$2020,$5055,$434B,$2043
	dc.w	$4F4E,$5452,$4F4C,$2052,$454C,$4159,$2020,$2020
	dc.w	$F804,$0104,$0500,$0026,$F804,$0104,$0320,$2020
	dc.w	$2020,$2020,$5055,$434B,$2042,$4C41,$5354,$2020
	dc.w	$2020,$2020,$2020,$F804,$0104,$0500,$0026,$F804
	dc.w	$0104,$0320,$2020,$2020,$2020,$5241,$5049,$4420
	dc.w	$4649,$5245,$2020,$2020,$2020,$2020,$F804,$0104
	dc.w	$0500,$0026,$F804,$0104,$0320,$2020,$2041,$4343
	dc.w	$5552,$4143,$5920,$5348,$4F4F,$5449,$4E47,$2020
	dc.w	$2020,$F804,$0104,$0500


; ----------------------------------------------------------------------
; called from $023D3C
sub_1E5DC4:
	move.w	(ram_DE84).w,d0
	cmp.w	#$2,d0	; general form
	beq.w	loc_1E5E74
	cmp.w	#$1,d0	; general form
	beq.w	loc_1E5E42
	cmp.w	#$3,d0	; general form
	beq.w	loc_1E5DE2
	rts
loc_1E5DE2:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_B460,a0
	move.w	#$3,d1
loc_1E5DF0:
	move.w	(ram_B760).w,d0
	sub.w	(a0),d0
	bpl.w	loc_1E5DFC
	neg.w	d0
loc_1E5DFC:
	cmp.w	#$6,d0	; general form
	bgt.w	loc_1E5E2C
	move.w	(ram_B778).w,d0
	sub.w	$18(a0),d0
	bpl.w	loc_1E5E12
	neg.w	d0
loc_1E5E12:
	cmp.w	#$4,d0	; general form
	bgt.w	loc_1E5E2C
	tst.w	$40(a0)
	bne.w	loc_1E5E2C
	move.w	#$1,$40(a0)
	addq.w	#1,(ram_DE9A).w
loc_1E5E2C:
	adda.l	#$80,a0
	dbra	d1,loc_1E5DF0
	movem.l	(sp)+,d0/d1/a0
	move.w	#$3C,(ram_DE98).w
	rts
loc_1E5E42:
	move.w	(ram_B788).w,d0
	move.w	(ram_B78A).w,d1
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	jsr	(ISqrt).l
	move.w	(ram_D2A2).w,d1
	muls.w	#$13,d1
	muls.w	d1,d0
	swap	d0
	move.w	d0,(ram_DE9A).w
	bset	#2,(ram_DEA2).w
	jsr	(sub_01B286).l
	rts
loc_1E5E74:
	addq.w	#1,(ram_DE8E).w
	bset	#2,(ram_DEA2).w
	jsr	(sub_01B286).l
	rts


; ----------------------------------------------------------------------
; called from $011C1E, $011D5C, $011DB6, $011FEC, $1E6638
sub_1E5E86:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,d0
	jsr	(sub_021BF4).l
	jsr	(Text_Print).l
inl_1E5E9A:
	dc.w	loc_1E5EA0-inl_1E5E9A
	dc.b	$BF,$03,$02,$00
loc_1E5EA0:
	moveq	#$1B,d0
	moveq	#$16,d1
	jsr	(Text_PrintDigitsBig).l
	lea	dat_1E612A(pc),a1
	move.w	(ram_DE84).w,d0
	jsr	(List_Skip).l
	jsr	(Text_PrintScoreboardAlt_Worker).l
	move.w	(ram_DE84).w,d0
	cmp.w	#$2,d0	; general form
	beq.w	loc_1E607A
	cmp.w	#$1,d0	; general form
	beq.w	loc_1E5F72
	cmp.w	#$3,d0	; general form
	beq.w	loc_1E5EE6
	cmp.w	#$0,d0	; general form
	beq.w	loc_1E6004
	bra.w	loc_1E610A
loc_1E5EE6:
	addq.w	#5,(TextY).w
	move.w	(ram_DE86).w,d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5F0A:
	dc.w	loc_1E5F16-inl_1E5F0A
	dc.b	" - Shooter"
loc_1E5F16:
	move.w	(sp),(TextX).w
	addq.w	#5,(TextY).w
	jsr	(Text_Print).l
inl_1E5F24:
	dc.w	loc_1E5F2E-inl_1E5F24
	dc.b	"SCORE = "
loc_1E5F2E:
	move.w	(ram_DE9A).w,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	move.w	(sp)+,(TextX).w
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E5F50:
	dc.w	loc_1E5F5A-inl_1E5F50
	dc.b	"SHOTS = "
loc_1E5F5A:
	move.w	(ram_DEA6).w,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	bra.w	loc_1E610A
loc_1E5F72:
	addq.w	#5,(TextY).w
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print).l
inl_1E5F80:
	dc.w	loc_1E5F9A-inl_1E5F80
	dc.b	"Fastest shot per player:"
loc_1E5F9A:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	clr.w	d2
	move.w	#$3,d1
	movea.l	#ram_DE86,a5
	movea.l	#ram_DE9C,a6
	movea.l	#ram_C732,a2
loc_1E5FBA:
	move.w	$0(a5,d2.w),d0
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	move.w	#$14,(TextX).w
	move.w	$0(a6,d2.w),d0
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E5FE6:
	dc.w	loc_1E5FEC-inl_1E5FE6
	dc.b	" MPH"
loc_1E5FEC:
	addq.w	#1,(TextY).w
	move.w	(sp),(TextX).w
	addq.w	#2,d2
	cmp.w	#$4,d2	; general form
	ble.s	loc_1E5FBA
	move.w	(sp)+,(TextX).w
	bra.w	loc_1E610A
loc_1E6004:
	addq.w	#5,(TextY).w
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print).l
inl_1E6012:
	dc.w	loc_1E602A-inl_1E6012
	dc.b	"The more time left on",0
loc_1E602A:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E6038:
	dc.w	loc_1E604E-inl_1E6038
	dc.b	"clock the better the"
loc_1E604E:
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E605C:
	dc.w	loc_1E606A-inl_1E605C
	dc.b	"performance."
loc_1E606A:
	addq.w	#1,(TextY).w
	move.w	(sp)+,(TextX).w
	bsr.w	sub_1E66A6
	bra.w	loc_1E610A
loc_1E607A:
	addq.w	#5,(TextY).w
	move.w	(ram_DE8C).w,d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E609E:
	dc.w	loc_1E60AA-inl_1E609E
	dc.b	" - Goalie",0
loc_1E60AA:
	move.w	(sp),(TextX).w
	addq.w	#2,(TextY).w
	jsr	(Text_Print).l
inl_1E60B8:
	dc.w	loc_1E60C4-inl_1E60B8
	dc.b	"  SHOTS = "
loc_1E60C4:
	move.w	(ram_DE90).w,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E60E6:
	dc.w	loc_1E60F2-inl_1E60E6
	dc.b	"  SAVES = "
loc_1E60F2:
	move.w	(ram_DE90).w,d0
	sub.w	(ram_DE8E).w,d0
	move.w	#$2,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
loc_1E610A:
	movem.l	(sp)+,d0-d7/a0-a6
	move.w	#$F0,(ram_DE98).w
loc_1E6114:
	move.w	(FrameCounter).w,d0
loc_1E6118:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_1E6118
	subq.w	#1,(ram_DE98).w
	bpl.s	loc_1E6114
	jmp	(loc_026D3E).l
dat_1E612A:
	dc.w	$0026,$F804,$0104,$0320,$5055,$434B,$2043,$4F4E
	dc.w	$5452,$4F4C,$2052,$454C,$4159,$204F,$5645,$5220
	dc.w	$F804,$0104,$0500,$0026,$F804,$0104,$0320,$2020
	dc.w	$2020,$5055,$434B,$2042,$4C41,$5354,$204F,$5645
	dc.w	$5220,$2020,$2020,$F804,$0104,$0500,$0026,$F804
	dc.w	$0104,$0320,$2020,$2020,$5241,$5049,$4420,$4649
	dc.w	$5245,$204F,$5645,$5220,$2020,$2020,$F804,$0104
	dc.w	$0500,$0026,$F804,$0104,$0320,$4143,$4355,$5241
	dc.w	$4359,$2053,$484F,$4F54,$494E,$4720,$4F56,$4552
	dc.w	$2020,$F804,$0104,$0500
loc_1E61C2:
	cmpi.w	#$1,(ram_DE96).w
	ble.w	loc_1E61D8
	tst.w	d1
	beq.w	loc_1E61D8
	move.w	#$1,(ram_DE96).w
loc_1E61D8:
	btst	#2,(ram_C34A).w
	beq.w	loc_1E6300
	cmpi.w	#$1,(ram_DE84).w
	beq.w	loc_1E62A6
	cmpi.w	#$3,(ram_DE84).w
	beq.w	loc_1E6242
	cmpi.w	#$0,(ram_DE84).w
	beq.w	loc_1E6208
	jmp	(loc_00CB0E).l

	dc.b	$4E,$75
loc_1E6208:
	move.w	d0,(ram_BF48).w
	andi.w	#$F,(ram_BF48).w
	jsr	(sub_01B86A).l
	btst	#7,d1
	beq.w	loc_1E6226
	jmp	(loc_019720).l
loc_1E6226:
	btst	#5,d1
	beq.w	loc_1E623C
	tst.w	(ram_B7C0).w
	bpl.w	loc_1E623C
	jsr	(sub_01B3EC).l
loc_1E623C:
	jmp	(loc_01F3C8).l
loc_1E6242:
	move.w	d0,(ram_BF48).w
	andi.w	#$F,(ram_BF48).w
	jsr	(sub_01B86A).l
	btst	#7,d1
	beq.w	loc_1E6260
	jmp	(loc_019720).l
loc_1E6260:
	btst	#5,$62(a3)
	beq.w	loc_1E6270
	jmp	(loc_01F3C8).l
loc_1E6270:
	btst	#3,(ram_C33C).w
	beq.w	loc_1E6282
	jsr	(sub_012EDA).l
	rts
loc_1E6282:
	btst	#5,d1
	beq.w	loc_1E6302
	btst	#3,$62(a3)
	beq.w	loc_1E6302
	addq.w	#1,(ram_DEA6).w
	move.w	#$B4,(ram_DE98).w
	jsr	(sub_012E40).l
	rts
loc_1E62A6:
	move.w	d0,(ram_BF48).w
	andi.w	#$F,(ram_BF48).w
	jsr	(sub_01B86A).l
	btst	#7,d1
	beq.w	loc_1E62C4
	jmp	(loc_019720).l
loc_1E62C4:
	btst	#5,$62(a3)
	beq.w	loc_1E62D4
loc_1E62CE:
	jmp	(loc_01F3C8).l
loc_1E62D4:
	btst	#3,(ram_C33C).w
	beq.w	loc_1E62E6
	jsr	(sub_1E6308).l
	rts
loc_1E62E6:
	btst	#5,d1
	beq.w	loc_1E6302
	tst.w	$42(a3)
	bne.s	loc_1E62CE
	move.w	#$A,$42(a3)
	jsr	(sub_012E40).l
loc_1E6300:
	rts
loc_1E6302:
	jmp	(loc_01F3C8).l


; ----------------------------------------------------------------------
; called from $1E62DE
sub_1E6308:
	tst.w	$58(a3)
	bne.w	loc_1E6318
	bclr	#3,(ram_C33C).w
	rts
loc_1E6318:
	cmpi.w	#$18,$5A(a3)
	bge.w	loc_1E6362
	btst	#3,d0
	bne.w	loc_1E6332
	andi.w	#$7,d0
	move.w	d0,(ram_BF10).w
loc_1E6332:
	cmpi.w	#$C,$5A(a3)
	bge.w	loc_1E6360
	add.w	d7,(ram_BF12).w
	cmpi.w	#$C,$5A(a3)
	bne.w	loc_1E634E
	addq.w	#1,(ram_BF12).w
loc_1E634E:
	btst	#5,d2
	beq.w	loc_1E6360
	neg.w	$5A(a3)
	addi.w	#$18,$5A(a3)
loc_1E6360:
	rts
loc_1E6362:
	cmpi.w	#$18,$5A(a3)
	beq.w	loc_1E6384
	cmpi.w	#$1C,$5A(a3)
	beq.w	loc_1E6384
	tst.w	$58(a3)
	bne.s	loc_1E6360
	bclr	#3,(ram_C33C).w
	rts
loc_1E6384:
	movem.l	d0/d1,-(sp)
	move.l	a3,-(sp)
	jsr	(sub_01F1F0).l
	add.w	(a3),d0
	add.w	$14(a3),d1
	sub.w	(ram_B760).w,d0
	sub.w	(ram_B774).w,d1
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	move.w	d0,(ram_BF4E).w
	cmp.l	#$40,d0	; general form
	movem.l	(sp)+,d0/d1
	ble.w	loc_1E63B8
	rts
loc_1E63B8:
	movem.l	d0-d7/a0-a3,-(sp)
	move.b	$62(a3),(ram_C368).w
	bclr	#4,(ram_C34A).w
	jsr	(sub_012D0E).l
	move.w	#$5,-(sp)
	move.w	$52(a3),(ram_BF0C).w
	bclr	#3,(ram_C33C).w
	bset	#5,$62(a3)
	move.w	#$18,(sp)
	bset	#4,(ram_C33E).w
	cmpi.w	#$F90,$58(a3)
	bne.w	loc_1E6406
	move.w	#$14,(sp)
	move.w	(ram_BF12).w,d0
	lsr.w	#2,d0
	sub.w	d0,(ram_BF12).w
loc_1E6406:
	clr.w	d0
	move.b	$6D(a3),d0
	lsr.b	#1,d0
	move.w	d0,-(sp)
	movea.l	a3,a0
	move.w	$2A(a3),d0
	bpl.w	loc_1E641C
	clr.w	d0
loc_1E641C:
	muls.w	#$1000,d0
	divs.w	#$2599,d0
	muls.w	(sp)+,d0
	asl.l	#4,d0
	swap	d0
	ext.l	d0
	addi.w	#$14,d0
	mulu.w	(ram_BF12).w,d0
	mulu.w	#$5249,d0
	swap	d0
	move.w	d0,(ram_BF12).w
	btst	#0,$6D(a3)
	beq.w	loc_1E644E
	asr.w	#4,d0
	add.w	(ram_BF12).w,d0
loc_1E644E:
	lsr.w	#4,d0
	neg.w	d0
	addq.w	#3,d0
	bpl.w	loc_1E645A
	clr.w	d0
loc_1E645A:
	add.w	d0,(sp)
	st	(ram_B7C0).w
	move.b	#$10,$5E(a3)
	move.w	$52(a3),(ram_BF0E).w
	move.w	#$11E,d1
	btst	#7,$62(a3)
	bne.w	loc_1E647C
	neg.w	d1
loc_1E647C:
	move.w	(ram_BF10).w,d2
	asl.w	#2,d2
	lea	dat_1E6532(pc),a0
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
	bne.w	loc_1E64AE
	addq.w	#1,d0
loc_1E64AE:
	move.w	d0,d3
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
	beq.w	loc_1E64E0
	clr.w	d1
loc_1E64E0:
	eor.w	d2,d1
	bpl.w	loc_1E64FC
	move.w	#$3810,(ram_B78A).w
	btst	#7,$62(a3)
	bne.w	loc_1E64FC
	move.w	#$C7F0,(ram_B78A).w
loc_1E64FC:
	move.w	(sp)+,d1
	beq.w	loc_1E6526
	mulu.w	(ram_BF12).w,d1
	mulu.w	#$44,d1
	divu.w	d3,d1
	mulu.w	#$B33,d3
	divu.w	(ram_BF12).w,d3
	add.w	d1,d3
	cmp.w	#$1800,d3	; general form
	bls.w	loc_1E6522
	move.w	#$1800,d3
loc_1E6522:
	move.w	d3,(ram_B78C).w
loc_1E6526:
	jsr	(sub_09205A).l
	movem.l	(sp)+,d0-d7/a0-a3
	rts
dat_1E6532:
	dc.w	$0000,$000C,$0010,$000C,$0010,$0006,$0010,$0000
	dc.w	$0000,$0000,$FFF0,$0000,$FFF0,$0006,$FFF0,$000C
	dc.w	$0000,$0006
loc_1E6556:
	movem.l	d0-d7/a0-a6,-(sp)
	move.w	#$FFFF,d0
	jsr	(sub_021BF4).l
	jsr	(Text_Print).l
inl_1E656A:
	dc.w	loc_1E6570-inl_1E656A
	dc.b	$BF,$03,$02,$00
loc_1E6570:
	moveq	#$1B,d0
	moveq	#$C,d1
	jsr	(Text_PrintDigitsBig).l
	jsr	(Text_PrintScoreboardAlt).l
inl_1E6580:
	dc.w	loc_1E65A6-inl_1E6580
	dc.b	$F8,$04,$01,$04,$03
	dc.b	"  PUCK BLAST SHOT SPEED  "
	dc.b	$F8,$04,$01,$04,$05,$00
loc_1E65A6:
	move.w	(TextX).w,-(sp)
	move.w	(ram_DE9A).w,d0
	movea.l	#ram_DE9C,a6
	move.w	(ram_DE92).w,d1
	add.w	d1,d1
	cmp.w	$0(a6,d1.w),d0
	ble.w	loc_1E65C6
	move.w	d0,$0(a6,d1.w)
loc_1E65C6:
	move.w	#$3,d1
	jsr	(Num_ToDecimal).l
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E65DC:
	dc.w	loc_1E65E2-inl_1E65DC
	dc.b	" MPH"
loc_1E65E2:
	addq.w	#2,(TextY).w
	move.w	(sp)+,(TextX).w
	movea.l	#ram_DE86,a6
	move.w	(ram_DE92).w,d1
	add.w	d1,d1
	move.w	$0(a6,d1.w),d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_1E6616:
	dc.w	loc_1E6622-inl_1E6616
	dc.b	" - Shooter"
loc_1E6622:
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $011E24
sub_1E6630:
	tst.w	(ram_D344).w
	bne.w	loc_1E663E
	jmp	(sub_1E5E86).l
loc_1E663E:
	addq.w	#1,(ram_DE92).w
	jsr	(sub_1E5530).l
	move.w	#$6,(ram_B7C0).w
	btst	#0,(ram_DE93).w
	beq.w	loc_1E6662
	neg.w	(ram_B760).w
	move.w	#$7,(ram_B7C0).w
loc_1E6662:
	clr.w	(ram_DE98).w
	bclr	#0,(ram_C344).w
	beq.w	loc_1E668A
	move.l	a3,-(sp)
	movea.l	#ram_B760,a3
	bclr	#2,$62(a3)
	move.w	#$18,d0
	jsr	(sub_01F172).l
	movea.l	(sp)+,a3
loc_1E668A:
	bset	#1,(ram_B0C2).w
	bset	#1,(ram_B3C2).w
	bset	#1,(ram_B442).w
	clr.w	(ram_B3A0).w
	clr.w	(ram_B420).w
	rts


; ----------------------------------------------------------------------
; called from $1E5AA6, $1E6072
sub_1E66A6:
	movea.l	#ram_DE86,a6
	move.w	(TextX).w,-(sp)
	jsr	(Text_Print).l
inl_1E66B6:
	dc.w	loc_1E66C2-inl_1E66B6
	dc.b	"First  - ",0
loc_1E66C2:
	move.w	(a6),d0
	movea.l	#ram_C732,a2
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E66E4:
	dc.w	loc_1E66F0-inl_1E66E4
	dc.b	"Second - ",0
loc_1E66F0:
	addq.l	#2,a6
	move.w	(a6),d0
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	move.w	(sp),(TextX).w
	addq.w	#1,(TextY).w
	jsr	(Text_Print).l
inl_1E670E:
	dc.w	loc_1E671A-inl_1E670E
	dc.b	"Third  - ",0
loc_1E671A:
	addq.l	#2,a6
	move.w	(a6),d0
	jsr	(sub_0285AE).l
	jsr	(Text_Print_Worker).l
	move.w	(sp)+,(TextX).w
	rts

