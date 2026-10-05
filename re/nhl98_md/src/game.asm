; ============================================================================
; Game engine: play, penalties, injuries, play-by-play text, exception handlers
; ROM range $01B8B8-$01FF23
; ============================================================================


; ----------------------------------------------------------------------
; called from $00F734, $00F916, $00FB42, $00FCB0, $0100DE, $0102D6, $010596, $010856 (+11 more)
sub_01B8B8:
	btst	#2,(ram_C342).w
	bne.s	loc_01B8B6
	btst	#3,$62(a3)
	bne.s	loc_01B8B6
	btst	#4,$63(a3)
	bne.s	loc_01B8B6
	tst.b	$60(a3)
	bpl.w	loc_01B8DE
	tst.b	$61(a3)
	bmi.s	loc_01B8B6
loc_01B8DE:
	move.b	$61(a3),d0
	cmp.b	$67(a3),d0
	beq.w	loc_01B912
	move.w	$36(a3),d0
	cmpi.b	#$B,$38(a3,d0.w)
	beq.s	loc_01B8B6
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.s	loc_01B8B6
	addq.w	#4,sp
	bset	#2,$63(a3)
	clr.w	$40(a3)
	moveq	#$B,d0
	bra.w	sub_01F172
loc_01B912:
	addq.w	#4,sp
	bclr	#2,$63(a3)
	bclr	#2,$62(a3)
	st	$61(a3)
	st	$60(a3)
	move.w	$34(a3),d0
	tst.b	$60(a3)
	bpl.w	loc_01B93A
	jmp	(sub_025428).l
loc_01B93A:
	move.b	$60(a3),d0
	ext.w	d0
	move.w	d0,$34(a3)
	jmp	(sub_025428).l


; ----------------------------------------------------------------------
; called from $029EE2
sub_01B94A:
	btst	#5,$62(a3)
	bne.w	loc_01B8B6
	cmpi.w	#$64,$40(a3)
	beq.w	loc_01BA6A
	bsr.w	sub_01B8B8
	btst	#4,$63(a3)
	bne.w	sub_01F156
	bclr	#1,$62(a3)
	beq.w	loc_01B9A0
	move.w	#$8,$42(a3)
	moveq	#$50,d0
	btst	#6,$62(a3)
	bne.w	loc_01B98A
	neg.w	d0
loc_01B98A:
	move.w	d0,$46(a3)
	move.w	#$96,$44(a3)
	neg.w	$44(a3)
	subq.w	#8,$44(a3)
	clr.w	$40(a3)
loc_01B9A0:
	move.b	$61(a3),d0
	cmp.b	$67(a3),d0
	beq.w	loc_01BACA
	sub.w	d7,$40(a3)
	bpl.w	loc_01BAB0
	addq.w	#8,$40(a3)
	move.w	$14(a3),d0
	sub.w	$46(a3),d0
	cmp.w	#$28,d0	; general form
	bgt.w	loc_01BAB0
	cmp.w	#$FFD8,d0	; general form
	blt.w	loc_01BAB0
	move.w	(a3),d0
	sub.w	$44(a3),d0
	cmp.w	#$20,d0	; general form
	bgt.w	loc_01BAB0
	move.w	#$870,d1
	tst.w	$34(a3)
	bne.w	loc_01B9EE
	move.w	#$65A,d1
loc_01B9EE:
	bsr.w	sub_01F3B2
	bset	#2,$62(a3)
	cmpi.w	#$4,$54(a3)
	beq.w	loc_01BA0C
	addq.w	#1,$54(a3)
	andi.w	#$7,$54(a3)
loc_01BA0C:
	clr.w	$2A(a3)
	move.w	#$F800,$28(a3)
	cmp.w	#$10,d0	; general form
	bgt.w	loc_01BA68
	clr.w	$28(a3)
	cmpi.w	#$4,$54(a3)
	bne.w	loc_01BA68
	move.w	#$F800,$28(a3)
	move.w	#$2,$54(a3)
	move.w	#$DD6,d1
	move.w	#$FF62,(a3)
	clr.w	$28(a3)
	tst.w	$34(a3)
	bne.w	loc_01BA58
	move.w	#$E5A,d1
	move.w	#$FF62,(a3)
	clr.w	$28(a3)
loc_01BA58:
	bsr.w	sub_01F3B2
	bset	#5,$62(a3)
	move.w	#$64,$40(a3)
loc_01BA68:
	rts
loc_01BA6A:
	clr.w	$6(a3)
	clr.w	d0
	move.b	$67(a3),d0
	add.w	d0,d0
	movea.l	#ram_C732,a0
	btst	#6,$62(a3)
	beq.w	loc_01BA8A
	adda.w	#$39E,a0
loc_01BA8A:
	tst.w	$34(a3)
	bne.w	loc_01BA9C
	cmpi.w	#$FFFD,$6C(a0,d0.w)
	ble.w	loc_01BAA2
loc_01BA9C:
	move.w	#$FFFE,$6C(a0,d0.w)
loc_01BAA2:
	move.b	$61(a3),d3
	bsr.w	sub_01BAD0
	jmp	(sub_025470).l
loc_01BAB0:
	btst	#2,$62(a3)
	bne.s	loc_01BA68
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#sub_01D42E,a0
	bra.w	sub_01EDE8
loc_01BACA:
	bclr	#2,$63(a3)

; ----------------------------------------------------------------------
; called from $01BAA6
sub_01BAD0:
	move.b	$60(a3),d0
	ext.w	d0
	move.w	d0,$34(a3)
	jsr	(sub_025428).l
	st	$61(a3)
	st	$60(a3)
loc_01BAE8:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BAEA:
	btst	#5,$62(a3)
	bne.s	loc_01BAE8
	bclr	#1,$62(a3)
	beq.w	loc_01BB4E
	clr.w	$28(a3)
	clr.w	$2A(a3)
	move.w	$52(a3),d0
	subq.w	#6,d0
	bmi.w	loc_01BB10
	addq.w	#1,d0
loc_01BB10:
	muls.w	#$E,d0
	move.w	d0,$14(a3)
	move.w	#$96,(a3)
	neg.w	(a3)
	move.w	#$2,$54(a3)
	bset	#5,$62(a3)
	move.w	#$D94,d1
	move.w	#$FF62,(a3)
	clr.w	$28(a3)
	tst.w	$34(a3)
	bne.w	loc_01BB4A
	move.w	#$E18,d1
	move.w	#$FF62,(a3)
	clr.w	$28(a3)
loc_01BB4A:
	bra.w	sub_01F3B2
loc_01BB4E:
	move.w	#$4,$54(a3)
	bclr	#2,$62(a3)
	bclr	#5,$63(a3)
	bclr	#2,$63(a3)
	clr.w	$58(a3)
	move.w	#$1000,$28(a3)
	bra.w	sub_01F156


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BB74:
	btst	#5,$62(a3)
	bne.w	loc_01BAE8
	bclr	#1,$62(a3)
	beq.w	loc_01BBF6
	bset	#2,$63(a3)
	bsr.w	sub_01BCC6
	moveq	#-$2,d4
	bsr.w	sub_01B86A
	move.w	#$8,$42(a3)
	moveq	#$B,d0
	move.b	(ram_C3F8).w,d1
	btst	#6,$62(a3)
	bne.w	loc_01BBB2
	lsr.w	#4,d1
	neg.w	d0
loc_01BBB2:
	andi.w	#$F,d1
	cmp.w	#$2,d1	; general form
	bls.w	loc_01BBC0
	moveq	#$2,d1
loc_01BBC0:
	addq.w	#3,d1
	muls.w	d0,d1
	move.w	d1,$46(a3)
	move.w	#$26,d1
	btst	#6,$62(a3)
	bne.w	loc_01BBDA
	move.w	#$FFBE,d1
loc_01BBDA:
	move.w	d1,$46(a3)
	move.w	#$8E,$44(a3)
	clr.w	$40(a3)
	bset	#5,$63(a3)
	clr.w	$4E(a3)
	clr.w	$50(a3)
loc_01BBF6:
	move.w	$14(a3),d0
	sub.w	$46(a3),d0
	cmp.w	#$C,d0	; general form
	bgt.w	loc_01BCB4
	cmp.w	#$FFF4,d0	; general form
	blt.w	loc_01BCB4
	move.w	(a3),d0
	sub.w	$44(a3),d0
	cmp.w	#$FFE8,d0	; general form
	blt.w	loc_01BCB4
	sub.w	d7,$40(a3)
	bpl.w	loc_01BAE8
	addq.w	#8,$40(a3)
	bset	#2,$62(a3)
	move.w	#$870,d1
	bsr.w	sub_01F3B2
	moveq	#$6,d2
	btst	#0,$77(a3)
	beq.w	loc_01BC44
	moveq	#$2,d2
loc_01BC44:
	cmp.w	$54(a3),d2
	beq.w	loc_01BC56
	addq.w	#1,$54(a3)
	andi.w	#$7,$54(a3)
loc_01BC56:
	clr.w	$2A(a3)
	move.w	#$1000,$28(a3)
	cmp.w	#$FFF8,d0	; general form
	blt.w	loc_01BAE8
	clr.w	$28(a3)
	cmp.w	$54(a3),d2
	bne.w	loc_01BAE8
	bset	#5,$62(a3)
	move.w	#$2,$54(a3)
	move.w	#$8E,(a3)
	move.w	#$26,$14(a3)
	btst	#6,$62(a3)
	bne.w	loc_01BC9A
	move.w	#$FFBE,$14(a3)
loc_01BC9A:
	bclr	#3,$4(a3)
	move.w	#$ABC,d1
	bsr.w	sub_01F3B2
	bclr	#4,$63(a3)
	moveq	#$D,d0
	bra.w	sub_01F172
loc_01BCB4:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	movea.l	#NullSub,a0
	bra.w	sub_01EDE8


; ----------------------------------------------------------------------
; called from $01BB8E
sub_01BCC6:
	btst	#3,$62(a3)
	beq.w	loc_01BAE8
	clr.w	d4
	move.w	$52(a3),d0
	cmp.w	(ram_C388).w,d0
	beq.w	sub_01B546
	moveq	#$2,d4
	cmp.w	(ram_C38A).w,d0
	beq.w	sub_01B546
	move.w	#$4,d4
	cmp.w	(ram_C38C).w,d0
	beq.w	sub_01B546
	move.w	#$6,d4
	bra.w	sub_01B546


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BCFC:
	btst	#5,$62(a3)
	bne.w	loc_01BD2A
	bclr	#1,$62(a3)
	beq.w	loc_01BD2A
	moveq	#$10,d0
	btst	#6,$62(a3)
	beq.w	loc_01BD1E
	moveq	#$1,d0
loc_01BD1E:
	add.b	d0,(ram_C3F8).w
	st	$34(a3)
	clr.w	$6(a3)
loc_01BD2A:
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BD2C:
	btst	#5,$62(a3)
	bne.w	loc_01BAE8
	bclr	#1,$62(a3)
	beq.w	loc_01BDA6
	bset	#2,$62(a3)
	bset	#2,$63(a3)
	moveq	#$10,d0
	moveq	#-$3C,d1
	btst	#6,$62(a3)
	beq.w	loc_01BD5E
	moveq	#$1,d0
	neg.w	d1
loc_01BD5E:
	sub.b	d0,(ram_C3F8).w
	move.w	d1,$14(a3)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	move.w	#$94,(a3)
	move.w	#$8E,(a3)
	move.w	#$26,$14(a3)
	btst	#6,$62(a3)
	bne.w	loc_01BD8C
	move.w	#$FFBE,$14(a3)
loc_01BD8C:
	move.w	#$4,$54(a3)
	bset	#5,$62(a3)
	move.w	#$B0E,d1
	bsr.w	sub_01F3B2
	jmp	(sub_02698A).l
loc_01BDA6:
	move.w	#$870,d1
	bsr.w	sub_01F3B2
	move.w	#$4,$54(a3)
	st	$61(a3)
	st	$60(a3)
	bclr	#3,$62(a3)
	bclr	#2,$62(a3)
	bclr	#5,$63(a3)
	bclr	#2,$63(a3)
	move.w	#$F000,$28(a3)
	bra.w	sub_01F156


; ----------------------------------------------------------------------
; called from $00F67E
sub_01BDDE:
	btst	#5,$62(a3)
	bne.w	loc_01BE36
	btst	#2,(ram_C342).w
	bne.w	loc_01BE02
	btst	#0,(ram_C34A).w
	bne.w	loc_01BE02
	nop
	bra.w	sub_01F156
loc_01BE02:
	clr.w	$28(a3)
	clr.w	$2A(a3)
	movem.l	d0/a0,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_D2F4).w,d0
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	#$191,$14(a3)
	btst	#7,$62(a0)
	bne.w	loc_01BE32
	move.w	#$FE6F,$14(a3)
loc_01BE32:
	movem.l	(sp)+,d0/a0
loc_01BE36:
	rts
loc_01BE38:
	rts
loc_01BE3A:
	btst	#5,$62(a3)
	bne.s	loc_01BE38
	btst	#3,$62(a3)
	bne.s	loc_01BE38
	moveq	#$8,d0
	bra.w	loc_01F3C8


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BE50:
	btst	#5,$62(a3)
	bne.s	loc_01BE38
	bclr	#1,$62(a3)
	beq.w	loc_01BE82
	move.w	#$5A,$44(a3)
	tst.w	(ram_BD34).w
	bpl.w	loc_01BE74
	neg.w	$44(a3)
loc_01BE74:
	move.w	(ram_BD30).w,$46(a3)
	move.w	#$CBA,d1
	bsr.w	sub_01F3B2
loc_01BE82:
	move.w	$44(a3),d0
	sub.w	(a3),d0
	move.w	$46(a3),d1
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	cmp.w	#$7,d0	; general form
	bgt.s	loc_01BE38
	move.w	d0,d2
	move.w	d2,$54(a3)
	bra.w	sub_01FBA6


; ----------------------------------------------------------------------
; called from $029EE2
sub_01BEA4:
	btst	#5,$62(a3)
	bne.s	loc_01BE38
	bclr	#1,$62(a3)
	beq.w	loc_01BED8
	bsr.w	sub_01BF5A
	move.w	#$8,$42(a3)
	move.w	#$5A,$44(a3)
	tst.w	(ram_BD34).w
	bpl.w	loc_01BED2
	neg.w	$44(a3)
loc_01BED2:
	move.w	(ram_BD30).w,$46(a3)
loc_01BED8:
	movea.l	#NullSub,a0
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	btst	#0,(ram_C34A).w
	beq.w	loc_01BF18
	tst.w	(ram_DCE2).w
	beq.w	loc_01BF06
	subq.w	#1,(ram_DCE2).w
	bne.w	loc_01BF06
	bset	#2,(ram_C33E).w
loc_01BF06:
	cmpi.w	#$96,(a3)
	bgt.w	loc_01BF16
	cmpi.w	#$FF6A,(a3)
	bgt.w	loc_01BF18
loc_01BF16:
	clr.w	d1
loc_01BF18:
	sub.w	d7,$40(a3)
	bpl.w	loc_01BF66
	bset	#5,$62(a3)
	move.w	#$C98,d1
	btst	#0,(ram_D297).w
	beq.w	loc_01BF38
	move.w	#$D28,d1
loc_01BF38:
	move.w	(ram_BF0C).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_01BF56
	move.w	#$C4A,d1
	btst	#3,(ram_D297).w
	bne.w	loc_01BF56
	move.w	#$D42,d1
loc_01BF56:
	bsr.w	sub_01F3B2

; ----------------------------------------------------------------------
; called from $01BEB6
sub_01BF5A:
	moveq	#$78,d0
	bsr.w	Random
	move.w	d0,$40(a3)
	rts
loc_01BF66:
	btst	#3,$62(a3)
	beq.w	sub_01EDE8
	rts

	dc.b	"NuNu"


; ----------------------------------------------------------------------
; called from $00F672, $01C188
sub_01BF76:
	btst	#3,$62(a3)
	bne.w	loc_01BF84
	bra.w	sub_01F156
loc_01BF84:
	btst	#1,$62(a3)
	bne.w	loc_01C020
	movem.w	d0/d1,-(sp)
	move.w	(a3),d0
	move.w	$14(a3),d1
	cmp.w	#$AA,d1	; general form
	bgt.w	loc_01BFC0
	cmp.w	#$FF56,d1	; general form
	blt.w	loc_01BFC0
	btst	#0,(ram_C33A).w
	bne.w	loc_01BFC0
	move.w	d0,-(sp)
	move.w	#$8,d0
	jsr	(sub_02135E).l
	move.w	(sp)+,d0
loc_01BFC0:
	sub.w	(ram_BD34).w,d0
	sub.w	(ram_BD30).w,d1
	bclr	#2,$64(a3)
	cmp.w	#$74,d0	; general form
	blt.w	loc_01BFE0
	bset	#2,$64(a3)
	bra.w	loc_01C012
loc_01BFE0:
	cmp.w	#$FF8C,d0	; general form
	bgt.w	loc_01BFF2
	bset	#2,$64(a3)
	bra.w	loc_01C012
loc_01BFF2:
	cmp.w	#$64,d1	; general form
	blt.w	loc_01C004
	bset	#2,$64(a3)
	bra.w	loc_01C012
loc_01C004:
	cmp.w	#$FF9C,d1	; general form
	bgt.w	loc_01C012
	bset	#2,$64(a3)
loc_01C012:
	movem.w	(sp)+,d0/d1
	btst	#2,$64(a3)
	bne.w	loc_01C18C
loc_01C020:
	btst	#5,$62(a3)
	bne.w	loc_01C180
	bsr.w	sub_01B8B8
	bclr	#1,$62(a3)
	beq.w	loc_01C046
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
	st	$46(a3)
loc_01C046:
	jsr	(sub_029F64).l
	bne.w	loc_01C056
	jsr	(sub_029F20).l
loc_01C056:
	btst	#1,$63(a3)
	bne.w	loc_01C180
	btst	#0,(ram_C33A).w
	beq.w	loc_01C0D4
	btst	#0,(ram_C33E).w
	bne.w	loc_01C180
	btst	#1,(ram_C34A).w
	bne.w	loc_01C180
	jsr	(sub_029F64).l
	bne.w	loc_01C180
	btst	#6,$62(a3)
	beq.w	loc_01C0A0
	bset	#5,(ram_C35C).w
	bne.w	loc_01C180
	bra.w	loc_01C0AA
loc_01C0A0:
	bset	#4,(ram_C35C).w
	bne.w	loc_01C180
loc_01C0AA:
	cmpi.w	#$8,(a3)
	bgt.w	loc_01C0CE
	cmpi.w	#$FFF8,(a3)
	blt.w	loc_01C0CE
	move.w	#$EC,d1
loc_01C0BE:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	bra.w	loc_01C180
loc_01C0CE:
	move.w	#$5D4,d1
	bra.s	loc_01C0BE
loc_01C0D4:
	tst.w	$48(a3)
	bmi.w	loc_01C152
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01C0F0
	st	$48(a3)
	bra.w	loc_01C152
loc_01C0F0:
	sub.w	d7,$48(a3)
	btst	#2,(ram_C342).w
	bne.w	loc_01C12E
	tst.w	$48(a3)
	bmi.w	loc_01C12E
	cmpi.w	#$2,$48(a3)
	bgt.w	loc_01C12E
	movem.w	d1,-(sp)
	move.w	#$368,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	move.w	#$FFFF,$48(a3)
	movem.w	(sp)+,d1
loc_01C12E:
	tst.w	$48(a3)
	bpl.w	loc_01C152
	btst	#2,(ram_C342).w
	beq.w	loc_01C14A
	bset	#4,(ram_C342).w
	bra.w	loc_01C152
loc_01C14A:
	moveq	#$8,d0
	jsr	(sub_02135E).l
loc_01C152:
	sub.b	d7,$40(a3)
	bpl.w	loc_01C180
	move.b	$6C(a3),d0
	beq.w	loc_01C16E
	btst	#6,(ram_C34C).w
	beq.w	loc_01C16E
	subq.b	#1,d0
loc_01C16E:
	lsr.b	#2,d0
	move.b	d0,$40(a3)
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01C180
loc_01C180:
	rts


; ----------------------------------------------------------------------
; called from $01D68C, $029EE2
sub_01C182:
	btst	#3,$62(a3)
	bne.w	sub_01BF76
loc_01C18C:
	move.w	(ram_B760).w,(ram_DCC8).w
	btst	#0,(ram_C344).w
	beq.w	loc_01C1FA
	btst	#1,$63(a3)
	bne.w	loc_01C1FA
	btst	#1,(ram_C344).w
	beq.w	loc_01C1E2
	btst	#3,(ram_C344).w
	bne.w	loc_01C1FA
	cmpi.w	#$89,$6(a3)
	bne.w	loc_01C1FA
	cmpi.w	#$8D,$6(a3)
	bne.w	loc_01C1FA
	bset	#3,(ram_C344).w
	move.w	#$1C,-(sp)
	jsr	(sub_09205A).l
	bra.w	loc_01C1FA
loc_01C1E2:
	move.w	#$39E,d1
	btst	#1,(ram_C358).w
	bne.w	loc_01C1FA
	bsr.w	sub_01F3B2
	bset	#1,$63(a3)
loc_01C1FA:
	btst	#5,$62(a3)
	bne.w	loc_01C27A
	bsr.w	sub_01B8B8
	bclr	#1,$62(a3)
	beq.w	loc_01C220
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
	st	$46(a3)
loc_01C220:
	cmpi.w	#$34,(a3)
	bgt.w	loc_01C258
	cmpi.w	#$FFCC,(a3)
	blt.w	loc_01C258
	cmpi.w	#$124,$14(a3)
	bgt.w	loc_01C258
	cmpi.w	#$FEDC,$14(a3)
	blt.w	loc_01C258
	cmpi.w	#$E8,$14(a3)
	bgt.w	loc_01C27C
	cmpi.w	#$FF18,$14(a3)
	blt.w	loc_01C27C
loc_01C258:
	lea	loc_01C27A(pc),a0
	moveq	#$4,d0
	tst.w	(a3)
	bpl.w	loc_01C266
	neg.w	d0
loc_01C266:
	move.w	#$FA,d1
	btst	#7,$62(a3)
	beq.w	sub_01EDE8
	neg.w	d1
	bra.w	sub_01EDE8
loc_01C27A:
	rts
loc_01C27C:
	btst	#1,$63(a3)
	bne.s	loc_01C27A
	btst	#0,(ram_C344).w
	beq.w	loc_01C2B2
	cmpi.w	#$8A,$6(a3)
	beq.w	loc_01C2AC
	cmpi.w	#$8E,$6(a3)
	bne.w	loc_01C2B2
	move.w	#$4,$54(a3)
	bra.w	loc_01C2B2
loc_01C2AC:
	move.w	#$0,$54(a3)
loc_01C2B2:
	move.w	#$72C,d1
	movem.w	d0,-(sp)
	move.w	(ram_B774).w,d0
	sub.w	$14(a3),d0
	bpl.w	loc_01C2C8
	neg.w	d0
loc_01C2C8:
	cmp.w	#$194,d0	; general form
	bgt.w	loc_01C2E4
	cmp.w	#$A8,d0	; general form
	bgt.w	loc_01C2DC
	bra.w	loc_01C2E8
loc_01C2DC:
	move.w	#$5A2,d1
	bra.w	loc_01C2E8
loc_01C2E4:
	move.w	#$CE,d1
loc_01C2E8:
	move.w	$28(a3),d0
	bpl.w	loc_01C2F2
	neg.w	d0
loc_01C2F2:
	cmp.w	#$700,d0	; general form
	blt.w	loc_01C31C
	tst.w	$54(a3)
	beq.w	loc_01C30C
	cmpi.w	#$4,$54(a3)
	bne.w	loc_01C31C
loc_01C30C:
	move.w	#$616,d1
	tst.w	$28(a3)
	bpl.w	loc_01C31C
	move.w	#$638,d1
loc_01C31C:
	movem.w	(sp)+,d0
	cmpi.w	#$616,$58(a3)
	beq.w	loc_01C338
	cmpi.w	#$638,$58(a3)
	beq.w	loc_01C338
	bsr.w	sub_01F3B2
loc_01C338:
	btst	#2,(ram_C342).w
	bne.w	loc_01C3C0
	btst	#0,(ram_C33A).w
	beq.w	loc_01C3C0
	btst	#1,(ram_C34A).w
	bne.w	loc_01C27A
	btst	#0,(ram_C33E).w
	bne.w	loc_01C27A
	btst	#1,$63(a3)
	bne.w	loc_01C27A
	jsr	(sub_029F64).l
	bne.w	loc_01C27A
	btst	#6,$62(a3)
	beq.w	loc_01C38C
	bset	#5,(ram_C35C).w
	bne.w	loc_01C27A
	bra.w	loc_01C396
loc_01C38C:
	bset	#4,(ram_C35C).w
	bne.w	loc_01C27A
loc_01C396:
	cmpi.w	#$8,(a3)
	bgt.w	loc_01C3BA
	cmpi.w	#$FFF8,(a3)
	blt.w	loc_01C3BA
	move.w	#$EC,d1
loc_01C3AA:
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	bra.w	loc_01C27A
loc_01C3BA:
	move.w	#$5D4,d1
	bra.s	loc_01C3AA
loc_01C3C0:
	tst.w	$48(a3)
	bmi.w	loc_01C43E
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01C3DC
	st	$48(a3)
	bra.w	loc_01C43E
loc_01C3DC:
	sub.w	d7,$48(a3)
	btst	#2,(ram_C342).w
	bne.w	loc_01C41A
	tst.w	$48(a3)
	bmi.w	loc_01C41A
	cmpi.w	#$2,$48(a3)
	bgt.w	loc_01C41A
	movem.w	d1,-(sp)
	move.w	#$FFFF,$48(a3)
	move.w	#$368,d1
	jsr	(sub_01F3B2).l
	bset	#1,$63(a3)
	movem.w	(sp)+,d1
loc_01C41A:
	tst.w	$48(a3)
	bpl.w	loc_01C43E
	btst	#2,(ram_C342).w
	beq.w	loc_01C436
	bset	#4,(ram_C342).w
	bra.w	loc_01C43E
loc_01C436:
	moveq	#$8,d0
	jsr	(sub_02135E).l
loc_01C43E:
	sub.b	d7,$40(a3)
	bpl.w	loc_01C80A
	move.b	$6C(a3),d0
	beq.w	loc_01C45A
	btst	#6,(ram_C34C).w
	beq.w	loc_01C45A
	subq.b	#1,d0
loc_01C45A:
	lsr.b	#2,d0
	move.b	d0,$40(a3)
	btst	#3,$62(a3)
	beq.w	loc_01C47A
	btst	#2,$64(a3)
	bne.w	loc_01C47A
	moveq	#$1D,d0
	bra.w	sub_01F168
loc_01C47A:
	move.w	(ram_B774).w,d0
	move.w	$14(a3),d1
	eor.w	d0,d1
	bpl.w	loc_01C49E
	clr.w	d0
	move.w	#$10A,d2
	btst	#7,$62(a3)
	beq.w	loc_01C7BE
	neg.w	d2
	bra.w	loc_01C7BE
loc_01C49E:
	subq.w	#1,$46(a3)
	bpl.w	loc_01C4AC
	move.w	#$FFFF,$46(a3)
loc_01C4AC:
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_01C544
	tst.w	$48(a3)
	bpl.w	loc_01C4C6
	move.w	#$5A,$48(a3)
loc_01C4C6:
	st	$46(a3)
	cmpi.w	#$5A,$48(a3)
	bgt.w	loc_01C5E2
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	bne.w	loc_01C5E2
	moveq	#$5,d0
	movea.w	#$B060,a0
	btst	#6,$62(a3)
	bne.w	loc_01C4F6
	adda.w	#$300,a0
loc_01C4F6:
	btst	#2,$63(a0)
	bne.w	loc_01C52E
	move.w	(ram_B774).w,d1
	sub.w	$14(a0),d1
	cmp.w	#$1C,d1	; general form
	bgt.w	loc_01C52E
	cmp.w	#$FFE4,d1	; general form
	blt.w	loc_01C52E
	move.w	(ram_B760).w,d1
	sub.w	(a0),d1
	cmp.w	#$19,d1	; general form
	bgt.w	loc_01C52E
	cmp.w	#$FFE7,d1	; general form
	bgt.w	loc_01C5E2
loc_01C52E:
	adda.w	#$80,a0
	dbra	d0,loc_01C4F6
	move.w	#$1,(ram_BF1A).w
	bsr.w	sub_01D2DC
	bra.w	loc_01C5E2
loc_01C544:
	tst.w	$46(a3)
	bne.w	loc_01C5E2
	tst.w	(ram_B7C0).w
	bpl.w	loc_01C5E2
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	cmp.w	#$14,d0	; general form
	bgt.w	loc_01C5E2
	cmp.w	#$FFEC,d0	; general form
	blt.w	loc_01C5E2
	move.w	(ram_B774).w,d1
	cmp.w	#$11E,d1	; general form
	bgt.w	loc_01C5E2
	cmp.w	#$FEE2,d1	; general form
	blt.w	loc_01C5E2
	sub.w	$14(a3),d1
	cmp.w	#$1E,d1	; general form
	bgt.w	loc_01C5E2
	cmp.w	#$FFE2,d1	; general form
	blt.w	loc_01C5E2
	movem.w	d0/d1,-(sp)
	move.w	(ram_B788).w,d0
	bpl.w	loc_01C5A0
	neg.w	d0
loc_01C5A0:
	move.w	(ram_B78A).w,d1
	bpl.w	loc_01C5AA
	neg.w	d1
loc_01C5AA:
	add.w	d1,d0
	cmp.w	#$1000,d0	; general form
	movem.w	(sp)+,d0/d1
	bgt.w	loc_01C5E2
	bsr.w	sub_01F186
	move.w	d0,$54(a3)
	move.b	#$8,$5E(a3)
	move.w	#$4BE,d1
	bsr.w	sub_01F3B2
	bset	#1,$63(a3)
	addi.w	#$C8,(ram_B8B4).w
	addi.w	#$A,(ram_B8BA).w
	rts
loc_01C5E2:
	movea.w	#$BF1C,a0
	move.w	#$11A,d3
	btst	#7,$62(a3)
	beq.w	loc_01C5F8
	addq.w	#4,a0
	neg.w	d3
loc_01C5F8:
	cmpi.w	#$11A,$14(a3)
	bgt.w	loc_01C60C
	cmpi.w	#$FEE6,$14(a3)
	bgt.w	loc_01C630
loc_01C60C:
	clr.w	d2
	clr.w	d0
	cmpi.w	#$2C,(a3)
	bgt.w	loc_01C7BE
	cmpi.w	#$FFD4,(a3)
	blt.w	loc_01C7BE
	move.w	#$96,d0
	tst.w	(a3)
	bpl.w	loc_01C7BE
	neg.w	d0
	bra.w	loc_01C7BE
loc_01C630:
	tst.w	(ram_B7C0).w
	bmi.w	loc_01C664
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01C664
	move.l	a0,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	adda.w	d0,a0
	move.w	(ram_B760).w,d0
	sub.w	(a0),d0
	asr.w	#1,d0
	add.w	(a0),d0
	move.w	d0,(ram_DCC8).w
	movea.l	(sp)+,a0
loc_01C664:
	move.w	(ram_DCC8).w,d0
	move.w	(ram_B774).w,d1
	bsr.w	sub_01C8A0
	bsr.w	sub_01F186
	bsr.w	sub_01C8CA
	move.w	(ram_C4CA).w,d0
	andi.w	#$7,d0
	asl.w	#4,d0
	addi.w	#$A0,d0
	cmpi.w	#$F1,(ram_B774).w
	bgt.w	loc_01C69A
	cmpi.w	#$FF0F,(ram_B774).w
	bgt.w	loc_01C69E
loc_01C69A:
	subi.w	#$40,d0
loc_01C69E:
	move.w	d0,d1
	muls.w	(ram_B788).w,d0
	swap	d0
	add.w	(ram_DCC8).w,d0
	muls.w	(ram_B78A).w,d1
	swap	d1
	add.w	(ram_B774).w,d1
	bsr.w	sub_01C8A0
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	#$384,d0	; general form
	bhi.w	loc_01C6D4
	movem.w	(sp)+,d0/d1
	bra.w	loc_01C6F8
loc_01C6D4:
	bsr.w	ISqrt
	moveq	#$1,d2
	add.w	d0,d2
	moveq	#$12,d4
	btst	#3,(ram_C33C).w
	beq.w	loc_01C6EA
	addq.w	#8,d4
loc_01C6EA:
	movem.w	(sp)+,d0/d1
	muls.w	d4,d1
	addq.w	#8,d4
	muls.w	d4,d0
	divs.w	d2,d0
	divs.w	d2,d1
loc_01C6F8:
	add.w	d3,d1
	move.w	d1,d2
	btst	#0,(ram_C34A).w
	bne.w	loc_01C754
	btst	#2,(ram_C342).w
	bne.w	loc_01C754
	bra.w	loc_01C754


; ----------------------------------------------------------------------
sub_01C714:
	btst	#3,(ram_C33C).w
	beq.w	loc_01C754
	cmpi.w	#$D0,(ram_B774).w
	bgt.w	loc_01C736
	cmpi.w	#$FF30,(ram_B774).w
	blt.w	loc_01C736
	bra.w	loc_01C754
loc_01C736:
	cmpi.w	#$14,(a3)
	bgt.w	loc_01C754
	cmpi.w	#$FFEC,(a3)
	blt.w	loc_01C754
	btst	#1,(ram_C4CB).w
	bne.w	loc_01C754
	bra.w	loc_01C778
loc_01C754:
	cmpi.w	#$22,$2(a0)
	bhi.w	loc_01C7BE
	cmpi.w	#$18,(a0)
	bgt.w	loc_01C81C
	cmpi.w	#$FFE8,(a0)
	blt.w	loc_01C81C
	cmpi.w	#$C,$2(a0)
	bhi.w	loc_01C79C
loc_01C778:
	cmpi.w	#$11E,(ram_B774).w
	bgt.w	loc_01C79C
	cmpi.w	#$FEE2,(ram_B774).w
	blt.w	loc_01C79C
	bset	#1,$63(a3)
	bne.w	loc_01C79C
	jsr	(sub_01C91C).l
loc_01C79C:
	move.w	(a0),d0
	cmpi.w	#$112,(ram_B774).w
	bgt.w	loc_01C7B2
	cmpi.w	#$FEEE,(ram_B774).w
	bgt.w	loc_01C7BE
loc_01C7B2:
	moveq	#$18,d0
	tst.w	(ram_DCC8).w
	bpl.w	loc_01C7BE
	neg.w	d0
loc_01C7BE:
	move.w	d2,d1
	movem.w	d0/d1,-(sp)
	move.b	$28(a3),d0
	ext.w	d0
	neg.w	d0
	add.w	(sp)+,d0
	sub.w	(a3),d0
	move.b	$2A(a3),d1
	ext.w	d1
	neg.w	d1
	add.w	(sp)+,d1
	sub.w	$14(a3),d1
	cmp.w	#$4,d0	; general form
	bgt.w	loc_01C802
	cmp.w	#$FFFC,d0	; general form
	blt.w	loc_01C802
	cmp.w	#$4,d1	; general form
	bgt.w	loc_01C802
	cmp.w	#$FFFC,d1	; general form
	blt.w	loc_01C802
	clr.w	d0
	clr.w	d1
loc_01C802:
	bsr.w	sub_01F186
	move.b	d0,$43(a3)
loc_01C80A:
	move.b	$43(a3),d2
	ext.w	d2
	cmp.w	#$7,d2	; general form
	ble.w	sub_01FBA6
	bra.w	sub_01FE66
loc_01C81C:
	tst.w	(ram_B7C0).w
	bpl.s	loc_01C7BE
	btst	#2,(ram_BFBC).w
	bne.s	loc_01C7BE
	movea.w	#$C732,a1
	lea	$39E(a1),a2
	btst	#6,$62(a3)
	beq.w	loc_01C83E
	exg	a1,a2
loc_01C83E:
	cmpi.l	#dat_001324,$2A(a1)
	blt.w	loc_01C7BE
	cmpi.l	#$9C4,$2A(a2)
	blt.w	loc_01C7BE
	cmpi.w	#$F6,(ram_B774).w
	bgt.w	loc_01C86A
	cmpi.w	#$FF0A,(ram_B774).w
	bgt.w	loc_01C7BE
loc_01C86A:
	tst.w	(ram_B78A).w
	btst	#7,$62(a3)
	beq.w	loc_01C87C
	eori	#$8,ccr
loc_01C87C:
	bmi.w	loc_01C7BE
	move.w	(ram_B788).w,d0
	bpl.w	loc_01C88A
	neg.w	d0
loc_01C88A:
	move.w	(ram_B78A).w,d1
	bpl.w	loc_01C894
	neg.w	d1
loc_01C894:
	cmp.w	d0,d1
	blt.w	loc_01C7BE
	moveq	#$F,d0
	bra.w	sub_01F168


; ----------------------------------------------------------------------
; called from $01C66C, $01C6B4
sub_01C8A0:
	move.w	(ram_B7C0).w,d2
	cmp.w	$52(a3),d2
	bne.w	loc_01C8AE
	clr.w	d0
loc_01C8AE:
	cmp.w	#$119,d1	; general form
	blt.w	loc_01C8BA
	move.w	#$119,d1
loc_01C8BA:
	cmp.w	#$FEE7,d1	; general form
	bgt.w	loc_01C8C6
	move.w	#$FEE7,d1
loc_01C8C6:
	sub.w	d3,d1
	rts


; ----------------------------------------------------------------------
; called from $01C674, $01F922, $01F93E
sub_01C8CA:
	move.w	$54(a3),d1
	sub.w	d1,d0
	beq.w	loc_01C91A
	neg.w	d0
	andi.w	#$4,d0
	lsr.w	#1,d0
	subq.w	#1,d0
	btst	#3,$62(a3)
	bne.w	loc_01C910
	btst	d1,#$42
	beq.w	loc_01C910
	add.w	d0,d1
	btst	#7,$62(a3)
	bne.w	loc_01C904
	btst	d1,#$83
	bra.w	loc_01C908
loc_01C904:
	btst	d1,#$38
loc_01C908:
	beq.w	loc_01C912
	neg.w	d0
	add.w	d0,d1
loc_01C910:
	add.w	d0,d1
loc_01C912:
	andi.w	#$7,d1
	move.w	d1,$54(a3)
loc_01C91A:
	rts


; ----------------------------------------------------------------------
; called from $00D254, $01C796
sub_01C91C:
	btst	#7,(ram_C350).w
	beq.w	loc_01C936
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_01C936
	addi.w	#$1E,(ram_DE98).w
loc_01C936:
	addq.w	#1,(ram_C4D0).w
	move.w	(a0),d0
	sub.w	(a3),d0
	move.w	d3,d1
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	sub.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,d3
	lsr.w	#2,d0
	btst	#3,$4(a3)
	beq.w	loc_01C962
	eori.w	#$1,d0
loc_01C962:
	move.w	d0,(ram_DDCE).w
	cmpi.w	#$8,(ram_B778).w
	bgt.w	loc_01C97E
	cmpi.w	#$800,(ram_B78C).w
	bgt.w	loc_01C97E
	bra.w	loc_01C9A8
loc_01C97E:
	movem.l	d0,-(sp)
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$10,d0	; general form
	bgt.w	loc_01C9A0
	cmp.w	#$FFF0,d0	; general form
	blt.w	loc_01C9A0
	movem.l	(sp)+,d0
	addq.w	#6,d0
	bra.w	loc_01CA54
loc_01C9A0:
	movem.l	(sp)+,d0
	bra.w	loc_01CA54
loc_01C9A8:
	addq.w	#4,d0
	cmpi.w	#$8,$2(a0)
	bls.w	loc_01CA2E
	cmpi.w	#$2,$54(a3)
	beq.w	loc_01CA54
	cmpi.w	#$6,$54(a3)
	beq.w	loc_01CA54
	tst.w	(ram_B7C0).w
	bmi.w	loc_01CA54
	subq.w	#2,d0
	move.w	d1,-(sp)
	move.w	#$1000,d1
	move.w	d1,$28(a3)
	ori.w	#$1,d0
	btst	#7,$62(a3)
	bne.w	loc_01C9EE
	eori.w	#$1,d0
loc_01C9EE:
	move.w	#$FFFA,d1
	tst.w	$28(a3)
	bmi.w	loc_01C9FE
	neg.w	$28(a3)
loc_01C9FE:
	tst.w	(a3)
	bpl.w	loc_01CA18
	tst.w	$28(a3)
	bpl.w	loc_01CA10
	neg.w	$28(a3)
loc_01CA10:
	move.w	#$6,d1
	eori.w	#$1,d0
loc_01CA18:
	add.w	d1,(a3)
	btst	#0,$77(a3)
	beq.w	loc_01CA28
	eori.w	#$1,d0
loc_01CA28:
	move.w	(sp)+,d1
	bra.w	loc_01CA54
loc_01CA2E:
	movem.l	d0,-(sp)
	move.w	(a3),d0
	sub.w	(a0),d0
	cmp.w	#$10,d0	; general form
	ble.w	loc_01CA46
	movem.l	(sp)+,d0
	bra.w	loc_01CA52
loc_01CA46:
	cmp.w	#$FFF0,d0	; general form
	movem.l	(sp)+,d0
	bgt.w	loc_01CA54
loc_01CA52:
	addq.w	#4,d0
loc_01CA54:
	add.w	d0,d0
	lea	dat_01CB44(pc),a1
	move.w	$0(a1,d0.w),d1
	move.w	(a3),d0
	sub.w	(a0),d0
	bpl.w	loc_01CA68
	neg.w	d0
loc_01CA68:
	cmp.w	#$2,d0	; general form
	bgt.w	loc_01CA90
	cmpi.w	#$C00,(ram_B78C).w
	bgt.w	loc_01CA90
	move.w	#$33E,d1
	cmpi.w	#$600,(ram_B78C).w
	bgt.w	loc_01CAE0
	move.w	#$194,d1
	bra.w	loc_01CAE0
loc_01CA90:
	cmpi.w	#$400,(ram_B78C).w
	bgt.w	loc_01CAC2
	move.w	(a3),d0
	sub.w	(a0),d0
	bpl.w	loc_01CAA4
	neg.w	d0
loc_01CAA4:
	cmp.w	#$A,d0	; general form
	blt.w	loc_01CAC2
	move.w	#$74,d1
	btst	#0,(ram_DDCF).w
	beq.w	loc_01CABE
	move.w	#$2E4,d1
loc_01CABE:
	bra.w	loc_01CAE0
loc_01CAC2:
	cmp.w	#$1EE,d1	; general form
	bne.w	loc_01CAE0
	andi.w	#$3,d3
	beq.w	loc_01CAE0
	cmpi.b	#$B,$74(a3)
	blt.w	loc_01CAE0
	move.w	#$2E4,d1
loc_01CAE0:
	bsr.w	sub_01F3B2
	addi.w	#$C8,(ram_B8B4).w
	addi.w	#$A,(ram_B8BA).w
	asr.w	$28(a3)
	asr.w	$28(a3)
	asr.w	$2A(a3)
	asr.w	$2A(a3)
	btst	#7,$62(a3)
	beq.w	loc_01CB32
	cmpi.w	#$3,$54(a3)
	beq.w	loc_01CB22
	cmpi.w	#$5,$54(a3)
	beq.w	loc_01CB2A
	bra.w	loc_01CB42
loc_01CB22:
	subq.w	#1,$54(a3)
	bra.w	loc_01CB42
loc_01CB2A:
	addq.w	#1,$54(a3)
	bra.w	loc_01CB42
loc_01CB32:
	cmpi.w	#$7,$54(a3)
	beq.s	loc_01CB22
	cmpi.w	#$1,$54(a3)
	beq.s	loc_01CB2A
loc_01CB42:
	rts
dat_01CB44:
	dc.w	$0152,$01EE,$0464,$040A,$028A,$0230,$0152,$01EE
	dc.w	$028A,$0230,$0074,$02E4


; ----------------------------------------------------------------------
; called from $029EE2
sub_01CB5C:
	btst	#3,$62(a3)
	bne.w	sub_01F156
	btst	#0,(ram_C33A).w
	bne.w	sub_01F156
	bsr.w	sub_01B8B8
	bclr	#1,$62(a3)
	beq.w	loc_01CB82
	clr.w	$40(a3)
loc_01CB82:
	sub.b	d7,$40(a3)
	bpl.w	loc_01CBEE
	move.b	$6C(a3),d0
	beq.w	loc_01CB9E
	btst	#6,(ram_C34C).w
	beq.w	loc_01CB9E
	subq.b	#1,d0
loc_01CB9E:
	lsr.b	#2,d0
	move.b	d0,$40(a3)
	tst.w	(ram_B7C0).w
	bpl.w	sub_01F156
	tst.w	(ram_B78A).w
	btst	#7,$62(a3)
	beq.w	loc_01CBBE
	eori	#$8,ccr
loc_01CBBE:
	bmi.w	sub_01F156
	movea.w	#$C732,a1
	lea	$39E(a1),a2
	btst	#6,$62(a3)
	beq.w	loc_01CBD6
	exg	a1,a2
loc_01CBD6:
	cmpi.l	#$E10,$2A(a1)
	blt.w	sub_01F156
	cmpi.l	#$640,$2A(a2)
	blt.w	sub_01F156
loc_01CBEE:
	bra.w	sub_01EFE2


; ----------------------------------------------------------------------
; called from $01CD5A, $01D586
sub_01CBF2:
	bset	#2,(ram_C346).w
	bclr	#1,$62(a3)
	beq.w	loc_01CC3A
	move.w	#$1,-(sp)
	jsr	(sub_09205A).l
	movem.l	a2,-(sp)
	movea.l	#ram_C732,a2
	btst	#6,$62(a3)
	beq.w	loc_01CC26
	movea.l	#ram_CAD0,a2
loc_01CC26:
	addq.w	#1,$392(a2)
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$1E,(ram_B8BA).w
	movem.l	(sp)+,a2
loc_01CC3A:
	movem.w	d1,-(sp)
	move.w	$14(a3),d0
	move.w	$2A(a3),d1
	beq.w	loc_01CC52
	eor.w	d1,d0
loc_01CC4C:
	movem.w	(sp)+,d1
	rts
loc_01CC52:
	move.w	#$FFFF,d1
	bra.s	loc_01CC4C


; ----------------------------------------------------------------------
; called from $01CDBE, $01D5BE
sub_01CC58:
	btst	#1,$62(a3)
	beq.w	loc_01CC6E
	bclr	#0,$64(a3)
	bclr	#1,$64(a3)
loc_01CC6E:
	movem.w	d0/d1/a0,-(sp)
	move.w	#$11E,d0
	move.w	$14(a3),d1
	bpl.w	loc_01CC80
	neg.w	d1
loc_01CC80:
	cmp.w	d0,d1
	bge.w	loc_01CD24
	move.w	#$76,d0
	move.w	$14(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_01CCA4
	neg.w	d1
	cmp.w	d1,d0
	bgt.w	loc_01CCAA
	bra.w	loc_01CCB4
loc_01CCA4:
	cmp.w	d1,d0
	blt.w	loc_01CCB4
loc_01CCAA:
	bset	#0,$64(a3)
	bra.w	loc_01CD24
loc_01CCB4:
	bclr	#0,$64(a3)
	beq.w	loc_01CD24
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	bne.w	loc_01CCCE
	neg.w	d0
loc_01CCCE:
	subi.w	#$76,d0
	bpl.w	loc_01CCD8
	neg.w	d0
loc_01CCD8:
	cmp.w	#$23,d0	; general form
	blt.w	loc_01CCE4
	bra.w	loc_01CD24
loc_01CCE4:
	move.w	$14(a3),d1
	movea.l	#ram_B5E0,a0
	move.w	#$B,d0
	tst.w	d1
	bmi.w	loc_01CD2A
loc_01CCF8:
	cmp.w	$14(a0),d1
	bge.w	loc_01CD0C
	tst.w	$34(a0)
	beq.w	loc_01CD0C
	bra.w	loc_01CD24
loc_01CD0C:
	suba.w	#$80,a0
	dbra	d0,loc_01CCF8
loc_01CD14:
	bset	#1,$64(a3)
	move.w	#$1,d0
loc_01CD1E:
	movem.w	(sp)+,d0/d1/a0
	rts
loc_01CD24:
	move.w	#$0,d0
	bra.s	loc_01CD1E
loc_01CD2A:
	cmp.w	$14(a0),d1
	ble.w	loc_01CD3C
	tst.w	$34(a0)
	beq.w	loc_01CD3C
	bra.s	loc_01CD24
loc_01CD3C:
	suba.w	#$80,a0
	dbra	d0,loc_01CD2A
	bra.s	loc_01CD14


; ----------------------------------------------------------------------
; called from $00F682
sub_01CD46:
	btst	#0,(ram_C34A).w
	bne.w	loc_01CD62
	btst	#2,(ram_C342).w
	bne.w	loc_01CD62
	bsr.w	sub_01CBF2
	bpl.w	sub_01CD70
loc_01CD62:
	bclr	#1,$64(a3)
	move.w	#$10,d0
	bsr.w	sub_01F172

; ----------------------------------------------------------------------
; called from $01CD5E, $029EE2
sub_01CD70:
	bclr	#2,(ram_C346).w
	bne.w	loc_01CD80
	bclr	#1,$64(a3)
loc_01CD80:
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	sub_01F156
	btst	#2,(ram_C342).w
	beq.w	loc_01CDA0
	cmpi.w	#$1,(ram_C382).w
	bgt.w	loc_01D04C
loc_01CDA0:
	btst	#1,$64(a3)
	bne.w	loc_01CDD4
	btst	#2,(ram_C342).w
	bne.w	loc_01CDD4
	btst	#3,(ram_C350).w
	bne.w	loc_01CDC8
	jsr	(sub_01CC58).l
	beq.w	loc_01CDD4
loc_01CDC8:
	move.w	#$21,d0
	bsr.w	sub_01F172
	bra.w	loc_01CDD4
loc_01CDD4:
	btst	#5,$62(a3)
	bne.w	NullSub
	btst	#2,(ram_C342).w
	bne.w	loc_01CDF2
	btst	#0,(ram_C33A).w
	bne.w	loc_01BE3A
loc_01CDF2:
	btst	#3,$62(a3)
	bne.w	sub_01F156
	bclr	#1,$62(a3)
	beq.w	loc_01CE88
	move.l	a0,-(sp)
	movea.l	#ram_D256,a0
	btst	#6,$62(a3)
	beq.w	loc_01CE1E
	movea.l	#ram_D258,a0
loc_01CE1E:
	move.w	$52(a3),(a0)
	movea.l	(sp)+,a0
	btst	#1,$64(a3)
	beq.w	loc_01CE38
	move.w	#$1,-(sp)
	jsr	(sub_09205A).l
loc_01CE38:
	btst	#1,$64(a3)
	beq.w	loc_01CE70
	movem.l	a2,-(sp)
	movea.l	#ram_C732,a2
	btst	#6,$62(a3)
	beq.w	loc_01CE5C
	movea.l	#ram_CAD0,a2
loc_01CE5C:
	addq.w	#1,$392(a2)
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$1E,(ram_B8BA).w
	movem.l	(sp)+,a2
loc_01CE70:
	clr.w	$40(a3)
	move.w	#$8,$42(a3)
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	move.w	d0,$44(a3)
loc_01CE88:
	sub.b	d7,$40(a3)
	bpl.w	loc_01CF3A
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_01CEB2
	btst	#6,(ram_C34C).w
	beq.w	loc_01CEB6
	tst.b	$40(a3)
	beq.w	loc_01CEB6
loc_01CEB2:
	subq.b	#1,$40(a3)
loc_01CEB6:
	btst	#2,(ram_C342).w
	bne.w	loc_01CF26
	btst	#0,(ram_C34A).w
	bne.w	loc_01CF26
	jsr	(sub_01D4C8).l
	bsr.w	sub_01D076
	btst	#0,(ram_C34A).w
	bne.w	loc_01CF26
	btst	#2,(ram_C342).w
	bne.w	loc_01CF26
	btst	#1,$64(a3)
	bne.w	loc_01CF1E
	move.w	#$1,d0
	btst	#6,$62(a3)
	beq.w	loc_01CF04
	move.w	#$2,d0
loc_01CF04:
	cmp.w	(ram_C394).w,d0
	beq.w	loc_01CF1E
	cmp.w	(ram_C396).w,d0
	beq.w	loc_01CF1E
	btst	#1,(ram_B055).w
	bne.w	loc_01CF36
loc_01CF1E:
	bsr.w	sub_01D118
	bra.w	loc_01CF36
loc_01CF26:
	jsr	(sub_1D16E0).l
	bne.w	loc_01CF3A
	jsr	(sub_012E00).l
loc_01CF36:
	bsr.w	sub_01D2DC
loc_01CF3A:
	moveq	#$6,d0
	add.w	$44(a3),d0
	lea	dat_01D04E(pc),a0
	btst	#7,(ram_C33E).w
	beq.w	loc_01CF52
	move.w	$34(a3),d0
loc_01CF52:
	asl.w	#2,d0
	move.w	$2(a0,d0.w),d1
	move.w	$0(a0,d0.w),d0
	btst	#2,(ram_C342).w
	bne.w	loc_01CF70
	btst	#0,(ram_C34A).w
	beq.w	loc_01CF80
loc_01CF70:
	jsr	(sub_1D1658).l
	cmpi.b	#$80,(ram_D836).w
	beq.w	loc_01D04C
loc_01CF80:
	btst	#7,$62(a3)
	bne.w	loc_01CF8E
	neg.w	d0
	neg.w	d1
loc_01CF8E:
	lea	sub_01CFAE(pc),a0
	btst	#2,(ram_C342).w
	bne.w	loc_01CFA6
	btst	#0,(ram_C34A).w
	beq.w	loc_01CFAA
loc_01CFA6:
	lea	loc_01D04C(pc),a0
loc_01CFAA:
	bra.w	sub_01EDE8


; ----------------------------------------------------------------------
; called from $01CF8E
sub_01CFAE:
	ext.w	d0
	move.b	$28(a3),d2
	ext.w	d2
	add.w	(ram_B760).w,d2
	move.b	$2A(a3),d3
	ext.w	d3
	add.w	(ram_B774).w,d3
	clr.w	(ram_BF1A).w
	moveq	#$5,d4
	movea.w	#$B060,a0
	cmpi.w	#$6,$52(a3)
	bge.w	loc_01CFDC
	adda.w	#$300,a0
loc_01CFDC:
	move.b	$28(a0),d1
	ext.w	d1
	add.w	(a0),d1
	sub.w	d2,d1
	cmp.w	#$14,d1	; general form
	bgt.w	loc_01D044
	cmp.w	#$FFEC,d1	; general form
	blt.w	loc_01D044
	move.b	$2A(a0),d1
	ext.w	d1
	add.w	$14(a0),d1
	sub.w	d3,d1
	cmp.w	#$14,d1	; general form
	bgt.w	loc_01D044
	cmp.w	#$FFEC,d1	; general form
	blt.w	loc_01D044
	addq.w	#1,(ram_BF1A).w
	move.w	(a3),d0
	sub.w	(a0),d0
	move.w	$14(a3),d1
	sub.w	$14(a0),d1
	bsr.w	sub_01F186
	move.w	$54(a3),d1
	eori.w	#$4,d1
	cmp.w	d0,d1
	bne.w	loc_01D044
	move.w	(VDP_HVCOUNTER).l,d1
	andi.w	#$1,d1
	add.w	d1,d0
	andi.w	#$7,d0
loc_01D044:
	adda.w	#$80,a0
	dbra	d4,loc_01CFDC
loc_01D04C:
	rts
dat_01D04E:
	dc.w	$FF9C,$FFEC,$0064,$FFEC,$FF88,$0028,$0014,$0028
	dc.w	$0078,$0028,$FFEC,$0028,$FFD8,$0106,$0000,$00F2
	dc.w	$0014,$00FC,$001E,$00FC


; ----------------------------------------------------------------------
; called from $01CED0
sub_01D076:
	btst	#4,(ram_C34C).w
	bne.w	NullSub
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_01D090
	neg.w	d0
loc_01D090:
	tst.w	d0
	bmi.w	NullSub
	cmp.w	#$76,d0	; general form
	bgt.w	NullSub
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	bne.w	NullSub
	btst	#3,$63(a3)
	bne.w	NullSub
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	btst	#6,$62(a3)
	beq.w	loc_01D0CA
	exg	a2,a1
loc_01D0CA:
	bsr.w	sub_022412
	cmp.w	#$C00,d0	; general form
	bhi.w	NullSub
	bsr.w	sub_01E590
	jsr	(sub_025122).l
	bsr.w	sub_022296
	jmp	(sub_012E00).l


; ----------------------------------------------------------------------
; called from $01D118
sub_01D0EA:
	btst	#5,(ram_C33E).w
	bne.w	sub_01D0FA
	eori	#$4,ccr
	rts


; ----------------------------------------------------------------------
; called from $01D0F0, $01D81A, $0254DE
sub_01D0FA:
	movem.l	d0/d1,-(sp)
	btst	#6,(ram_C33E).w
	move.w	sr,d0
	btst	#6,$62(a3)
	move.w	sr,d1
	eor.w	d1,d0
	move.w	d0,ccr
	movem.l	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $01CF1E
sub_01D118:
	bsr.s	sub_01D0EA
	bne.w	loc_01D16C
	tst.w	(ram_BF1A).w
	beq.w	loc_01D16C
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	bne.w	loc_01D16C
	move.w	#$76,d0
	btst	#7,$62(a3)
	beq.w	loc_01D152
	move.w	#$FF8A,d0
	cmp.w	$14(a3),d0
	blt.w	loc_01D166
	bra.w	loc_01D15A
loc_01D152:
	cmp.w	$14(a3),d0
	bgt.w	loc_01D166
loc_01D15A:
	bset	#3,(ram_C346).w
	jmp	(sub_0132A0).l
loc_01D166:
	jmp	(sub_012E00).l
loc_01D16C:
	btst	#3,(ram_C350).w
	bne.w	loc_01D180
	btst	#1,$64(a3)
	beq.w	loc_01D1C0
loc_01D180:
	move.w	#$1E,d0
	jsr	(Random).l
	addi.w	#$82,d0
	cmp.w	(ram_B774).w,d0
	blt.w	loc_01D1A4
	neg.w	d0
	cmp.w	(ram_B774).w,d0
	bgt.w	loc_01D1A4
	bra.w	loc_01D1C0
loc_01D1A4:
	move.w	#$2,d0
	jsr	(sub_0200EA).l
	add.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,$54(a3)
	jmp	(sub_012E00).l
loc_01D1C0:
	moveq	#$20,d4
	clr.w	d1
	move.b	$71(a3),d1
	lsr.w	#1,d1
	sub.b	d1,d4
	asl.w	#4,d4
	move.w	#$11E,d1
	btst	#7,$62(a3)
	bne.w	loc_01D1DE
	neg.w	d1
loc_01D1DE:
	sub.w	(ram_B774).w,d1
	move.w	(ram_B760).w,d0
	neg.w	d0
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d0,d1
	cmp.l	#dat_002710,d1	; general form
	movem.w	(sp)+,d0/d1
	bhi.w	loc_01D272
	lsr.w	#4,d4
	bsr.w	sub_01F186
	move.w	d0,d5
	moveq	#$5,d3
	movea.w	#$B060,a1
	cmpi.w	#$6,$52(a3)
	bge.w	loc_01D21C
	adda.w	#$300,a1
loc_01D21C:
	tst.w	$34(a1)
	beq.w	loc_01D24C
	btst	#5,$62(a1)
	bne.w	loc_01D24C
	move.w	(a1),d0
	sub.w	(ram_B760).w,d0
	move.w	$14(a1),d1
	sub.w	(ram_B774).w,d1
	bsr.w	sub_01F186
	cmp.w	d5,d0
	bne.w	loc_01D26A
	asl.w	#1,d4
	bra.w	loc_01D26A
loc_01D24C:
	cmpi.w	#$13,(a1)
	bgt.w	loc_01D268
	cmpi.w	#$FFED,(a1)
	blt.w	loc_01D268
	btst	#1,$63(a1)
	beq.w	loc_01D26A
	clr.w	d3
loc_01D268:
	moveq	#$1,d4
loc_01D26A:
	adda.w	#$80,a1
	dbra	d3,loc_01D21C
loc_01D272:
	move.w	d4,d0
	bsr.w	Random
	btst	#0,$71(a3)
	beq.w	loc_01D28E
	cmp.w	#$7,d0	; general form
	bgt.w	NullSub
	bra.w	loc_01D2AE
loc_01D28E:
	cmpi.w	#$51,(ram_B760).w
	bgt.w	loc_01D2A6
	cmpi.w	#$FFAF,(ram_B760).w
	blt.w	loc_01D2A6
	subi.w	#$A,d0
loc_01D2A6:
	cmp.w	#$8,d0	; general form
	bgt.w	NullSub
loc_01D2AE:
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_01D2BE
	neg.w	d0
loc_01D2BE:
	tst.w	d0
	bmi.w	NullSub
	move.w	#$11E,d1
	sub.w	d0,d1
	bmi.w	NullSub
	btst	#7,(ram_C33E).w
	bne.w	NullSub
	bra.w	loc_01D1A4


; ----------------------------------------------------------------------
; called from $01C53C, $01CF36
sub_01D2DC:
	tst.w	(ram_BF1A).w
	bne.w	loc_01D2F6
	moveq	#$10,d0
	add.b	$71(a3),d0
	bsr.w	Random
	cmp.w	#$C,d0	; general form
	bgt.w	NullSub
loc_01D2F6:
	moveq	#$6,d0
	bsr.w	Random
	cmpi.w	#$6,$52(a3)
	blt.w	loc_01D308
	addq.w	#6,d0
loc_01D308:
	tst.w	$34(a3)
	beq.w	loc_01D338
	cmpi.w	#$28,(ram_B760).w
	bgt.w	loc_01D338
	cmpi.w	#$FFD8,(ram_B760).w
	blt.w	loc_01D338
	cmpi.w	#$E2,(ram_B774).w
	bgt.w	NullSub
	cmpi.w	#$FF1E,(ram_B774).w
	blt.w	NullSub
loc_01D338:
	cmp.w	$52(a3),d0
	beq.w	NullSub
	asl.w	#7,d0
	movea.w	#$B060,a0
	adda.w	d0,a0
	tst.w	$34(a0)
	ble.w	NullSub
	btst	#2,$63(a0)
	bne.w	NullSub
	btst	#5,$62(a0)
	bne.w	NullSub
	move.w	$14(a0),d0
	move.w	$14(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_01D37A
	neg.w	d0
	neg.w	d1
loc_01D37A:
	btst	#5,(ram_C33A).w
	beq.w	loc_01D39A
	movem.w	d0/d1,-(sp)
	subi.w	#$76,d0
	subi.w	#$76,d1
	eor.w	d0,d1
	movem.w	(sp)+,d0/d1
	bmi.w	NullSub
loc_01D39A:
	cmp.w	#$76,d0	; general form
	bgt.w	loc_01D3AC
	sub.w	d1,d0
	cmp.w	#$FFF1,d0	; general form
	blt.w	NullSub
loc_01D3AC:
	move.w	(a0),d0
	sub.w	(ram_B760).w,d0
	move.w	$14(a0),d1
	sub.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	bsr.w	sub_01F186
	move.w	d0,(ram_BF10).w
	movem.w	(sp)+,d1/d2
	muls.w	d1,d1
	muls.w	d2,d2
	add.l	d1,d2
	moveq	#$5,d3
	movea.w	#$B060,a1
	cmpi.w	#$6,$52(a3)
	bge.w	loc_01D3E4
	adda.w	#$300,a1
loc_01D3E4:
	move.w	(a1),d0
	sub.w	(ram_B760).w,d0
	move.w	$14(a1),d1
	sub.w	(ram_B774).w,d1
	movem.w	d0/d1,-(sp)
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d0,d1
	cmp.l	d2,d1
	movem.w	(sp)+,d0/d1
	bhi.w	loc_01D412
	bsr.w	sub_01F186
	cmp.w	(ram_BF10).w,d0
	beq.w	NullSub
loc_01D412:
	adda.w	#$80,a1
	dbra	d3,loc_01D3E4
	jsr	(sub_0132A0).l
	tst.w	$34(a3)
	beq.w	NullSub
	addq.w	#4,sp
	bra.w	sub_01F156


; ----------------------------------------------------------------------
; called from $010EAA, $010EDA, $0114F0, $0116E0, $0118FE, $011B3E, $01BAC0
sub_01D42E:
	tst.w	(ram_B7C0).w
	bmi.w	NullSub
	move.b	$28(a3),d2
	sub.b	(ram_B788).w,d2
	ext.w	d2
	add.w	(a3),d2
	sub.w	(ram_B760).w,d2
	cmp.w	#$28,d2	; general form
	bgt.w	NullSub
	cmp.w	#$FFD8,d2	; general form
	blt.w	NullSub
	move.b	$2A(a3),d1
	sub.b	(ram_B78A).w,d1
	ext.w	d1
	add.w	$14(a3),d1
	sub.w	(ram_B774).w,d1
	cmp.w	#$28,d1	; general form
	bgt.w	NullSub
	cmp.w	#$FFD8,d1	; general form
	blt.w	NullSub
	move.w	(a3),d0
	sub.w	(ram_B760).w,d0
	move.w	$14(a3),d1
	sub.w	(ram_B774).w,d1
	bsr.w	sub_01F186
	btst	#5,(ram_C33A).w
	beq.w	loc_01D4C6
	move.w	$14(a3),d1
	btst	#7,$62(a3)
	bne.w	loc_01D4A4
	neg.w	d1
loc_01D4A4:
	subi.w	#$76,d1
	cmp.w	#$A,d1	; general form
	bgt.w	loc_01D4C6
	cmp.w	#$FFCE,d1	; general form
	blt.w	loc_01D4C6
	moveq	#$2,d0
	move.w	(a3),d1
	cmp.w	(ram_B760).w,d1
	bgt.w	loc_01D4C6
	moveq	#$6,d0
loc_01D4C6:
	rts


; ----------------------------------------------------------------------
; called from $00D3C6, $01CECA
sub_01D4C8:
	btst	#5,(ram_C33A).w
	beq.w	NullSub
	btst	#2,(ram_C342).w
	bne.w	NullSub
	movem.l	d0/d1/a0,-(sp)
	moveq	#$5,d0
	movea.w	#$B060,a0
	cmpi.w	#$6,$52(a3)
	blt.w	loc_01D4F4
	adda.w	#$300,a0
loc_01D4F4:
	moveq	#$7A,d1
	btst	#7,$62(a3)
	bne.w	loc_01D54A
	neg.w	d1
	cmp.w	(ram_B774).w,d1
	bgt.w	loc_01D522
loc_01D50A:
	tst.w	$34(a0)
	bmi.w	loc_01D51A
	cmp.w	$14(a0),d1
	bgt.w	loc_01D534
loc_01D51A:
	adda.w	#$80,a0
	dbra	d0,loc_01D50A
loc_01D522:
	moveq	#$40,d0
	bclr	#7,(ram_C33E).w
	bne.w	loc_01D53E
loc_01D52E:
	movem.l	(sp)+,d0/d1/a0
	rts
loc_01D534:
	moveq	#$6,d0
	bset	#7,(ram_C33E).w
	bne.s	loc_01D52E
loc_01D53E:
	tst.w	(ram_C452).w
	bpl.s	loc_01D52E
	bsr.w	sub_021B72
	bra.s	loc_01D52E
loc_01D54A:
	cmp.w	(ram_B774).w,d1
	blt.s	loc_01D522
loc_01D550:
	tst.w	$34(a0)
	bmi.w	loc_01D55E
	cmp.w	$14(a0),d1
	blt.s	loc_01D534
loc_01D55E:
	adda.w	#$80,a0
	dbra	d0,loc_01D550
	bra.s	loc_01D522


; ----------------------------------------------------------------------
; called from $00F686
sub_01D568:
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01D586
loc_01D574:
	bclr	#1,$64(a3)
	move.w	#$11,d0
	bsr.w	sub_01F172
	bra.w	sub_01D58E
loc_01D586:
	jsr	(sub_01CBF2).l
	bmi.s	loc_01D574

; ----------------------------------------------------------------------
; called from $01D582, $029EE2
sub_01D58E:
	bclr	#2,(ram_C346).w
	bne.w	loc_01D59E
	bclr	#1,$64(a3)
loc_01D59E:
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	bne.w	loc_01D5D4
	btst	#1,$64(a3)
	bne.w	loc_01D5D4
	btst	#2,(ram_C342).w
	bne.w	loc_01D5D4
	jsr	(sub_01CC58).l
	beq.w	loc_01D5D4
	move.w	#$22,d0
	bsr.w	sub_01F172
	bra.w	loc_01D5D4
loc_01D5D4:
	bclr	#1,$62(a3)
	beq.w	loc_01D656
	move.l	a0,-(sp)
	movea.l	#ram_D256,a0
	btst	#6,$62(a3)
	beq.w	loc_01D5F6
	movea.l	#ram_D258,a0
loc_01D5F6:
	move.w	$52(a3),(a0)
	movea.l	(sp)+,a0
	btst	#1,$64(a3)
	beq.w	loc_01D610
	move.w	#$1,-(sp)
	jsr	(sub_09205A).l
loc_01D610:
	btst	#1,$64(a3)
	beq.w	loc_01D648
	movem.l	a2,-(sp)
	movea.l	#ram_C732,a2
	btst	#6,$62(a3)
	beq.w	loc_01D634
	movea.l	#ram_CAD0,a2
loc_01D634:
	addq.w	#1,$392(a2)
	addi.w	#$12C,(ram_B8B4).w
	addi.w	#$1E,(ram_B8BA).w
	movem.l	(sp)+,a2
loc_01D648:
	clr.w	$44(a3)
	move.w	#$8,$42(a3)
	clr.w	$40(a3)
loc_01D656:
	tst.w	(ram_B7C0).w
	bmi.w	loc_01D67C
	move.l	a0,-(sp)
	movea.l	#ram_D256,a0
	cmpi.w	#$5,(ram_B7C0).w
	ble.w	loc_01D676
	movea.l	#ram_D258,a0
loc_01D676:
	move.w	(ram_B7C0).w,(a0)
	movea.l	(sp)+,a0
loc_01D67C:
	move.w	$52(a3),d1
	cmp.w	(ram_B7C0).w,d1
	bne.w	loc_01D69E
	tst.w	$34(a3)
	beq.w	sub_01C182
	moveq	#$10,d0
	btst	#3,$62(a3)
	beq.w	sub_01F168
	rts
loc_01D69E:
	sub.b	d7,$40(a3)
	bpl.w	loc_01D840
	move.b	$6B(a3),$40(a3)
	jsr	(sub_1D1DE0).l
	bmi.w	loc_01D6C8
	btst	#6,(ram_C34C).w
	beq.w	loc_01D6CC
	tst.b	$40(a3)
	beq.w	loc_01D6CC
loc_01D6C8:
	subq.b	#1,$40(a3)
loc_01D6CC:
	btst	#5,(TextFlags).w
	beq.w	loc_01D70E
	move.w	(ram_B7C0).w,d1
	cmp.w	#$5,d1	; general form
	bgt.w	loc_01D706
	btst	#6,$62(a3)
	beq.w	loc_01D70E
loc_01D6EC:
	move.b	$40(a3),d1
	ext.w	d1
	asr.w	#1,d1
	move.b	d1,$40(a3)
	bne.w	loc_01D70E
	move.b	#$1,$40(a3)
	bra.w	loc_01D70E
loc_01D706:
	btst	#6,$62(a3)
	beq.s	loc_01D6EC
loc_01D70E:
	clr.l	$2A(a2)
	move.w	(ram_B7C0).w,d1
	bmi.w	loc_01D734
	asl.w	#7,d1
	movea.w	#$B060,a1
	adda.w	d1,a1
	move.b	$62(a1),d0
	move.b	$62(a3),d1
	eor.b	d0,d1
	btst	#6,d1
	beq.w	loc_01D7B6
loc_01D734:
	moveq	#-$1,d2
	moveq	#$5,d4
	movea.w	$22(a2),a0
loc_01D73C:
	tst.w	$34(a0)
	ble.w	loc_01D7A4
	tst.b	$5E(a0)
	bne.w	loc_01D7A4
	btst	#2,$63(a0)
	bne.w	loc_01D7A4
	move.w	$52(a0),d0
	cmp.w	(ram_D25A).w,d0
	beq.w	loc_01D7A4
	move.w	$36(a0),d0
	cmpi.b	#$13,$38(a0,d0.w)
	beq.w	loc_01D7A4
	move.l	a0,-(sp)
	bsr.w	sub_01F1F0
	add.w	(a0),d0
	sub.w	(ram_B760).w,d0
	add.w	$14(a0),d1
	sub.w	(ram_B774).w,d1
	move.w	(ram_B788).w,d3
	asr.w	#6,d3
	sub.w	d3,d0
	move.w	(ram_B78A).w,d3
	asr.w	#6,d3
	sub.w	d3,d1
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	d2,d0
	bhi.w	loc_01D7A4
	move.l	d0,d2
	movea.w	a0,a1
loc_01D7A4:
	adda.w	#$80,a0
	dbra	d4,loc_01D73C
	tst.l	d2
	bmi.w	loc_01D7EE
	move.l	d2,$2A(a2)
loc_01D7B6:
	cmpa.w	a1,a3
	beq.w	loc_01D7EE
	btst	#0,(ram_C33A).w
	bne.w	loc_01D7EE
	btst	#2,$63(a1)
	bne.w	loc_01D7EE
	btst	#3,$64(a1)
	bne.w	loc_01D7EE
	exg	a1,a3
	bclr	#0,$62(a3)
	moveq	#$11,d0
	bsr.w	sub_01F168
	exg	a1,a3
	bra.w	sub_01F156
loc_01D7EE:
	btst	#5,$62(a3)
	bne.w	NullSub
	moveq	#$2,d1
	cmp.w	#$190,d2	; general form
	bhi.w	loc_01D80E
	subq.w	#2,d1
	cmpi.w	#$2,$34(a3)
	bls.w	loc_01D840
loc_01D80E:
	btst	#5,(ram_C33E).w
	beq.w	loc_01D824
	subq.w	#2,d1
	bsr.w	sub_01D0FA
	bne.w	loc_01D824
	addq.w	#4,d1
loc_01D824:
	move.w	#$28,d0
	sub.b	$76(a3),d0
	asl.w	d1,d0
	bsr.w	Random
	cmp.w	#$2,d0	; general form
	bhi.w	loc_01D840
	move.w	#$F0,$44(a3)
loc_01D840:
	btst	#5,$62(a3)
	bne.w	NullSub
	btst	#2,(ram_C342).w
	beq.w	loc_01D85E
	btst	#5,(ram_C342).w
	beq.w	loc_01D868
loc_01D85E:
	btst	#0,(ram_C33A).w
	bne.w	loc_01BE3A
loc_01D868:
	btst	#3,$62(a3)
	bne.w	NullSub
	btst	#2,$30(a2)
	bne.w	loc_01D91A
	tst.w	(ram_B7C0).w
	bmi.w	loc_01DA22
	tst.w	$34(a3)
	beq.w	loc_01D90E
	movem.l	d0/a0,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_B7C0).w,d0
	asl.w	#7,d0
	adda.w	d0,a0
	tst.w	$34(a0)
	bne.w	loc_01D8BC
	movem.l	(sp)+,d0/a0
	clr.w	d0
	clr.w	d1
	lea	NullSub(pc),a0
	jmp	(sub_01EDE8).l

	dc.b	$60,$00,$00,$1A
loc_01D8BC:
	move.w	(ram_B788).w,d0
	or.w	(ram_B78A).w,d0
	movem.l	(sp)+,d0/a0
	bne.w	loc_01D8D4
	bsr.w	sub_01DA26
	bra.w	loc_01DA22
loc_01D8D4:
	movem.w	d0,-(sp)
	move.w	(a3),d0
	sub.w	(ram_B760).w,d0
	bpl.w	loc_01D8E4
	neg.w	d0
loc_01D8E4:
	cmp.w	#$3C,d0	; general form
	movem.w	(sp)+,d0
	bgt.w	loc_01DA22
	movem.w	d0,-(sp)
	move.w	$14(a3),d0
	sub.w	(ram_B774).w,d0
	bpl.w	loc_01D902
	neg.w	d0
loc_01D902:
	cmp.w	#$3C,d0	; general form
	movem.w	(sp)+,d0
	bgt.w	loc_01DA22
loc_01D90E:
	sub.w	d7,$44(a3)
	bpl.w	loc_01DA22
	clr.w	$44(a3)
loc_01D91A:
	bsr.w	sub_01EFA8
	movem.w	d0/d1,-(sp)
	neg.w	d0
	neg.w	d1
	addi.w	#$10A,d1
	btst	#7,$62(a3)
	beq.w	loc_01D938
	subi.w	#$214,d1
loc_01D938:
	asr.w	#1,d0
	asr.w	#1,d1
	add.w	(sp)+,d0
	add.w	(sp)+,d1
	btst	#2,$30(a2)
	beq.w	loc_01D970
	btst	#7,$62(a3)
	beq.w	loc_01D964
	cmp.w	#$71,d1	; general form
	blt.w	loc_01D970
	move.w	#$62,d1
	bra.w	loc_01D970
loc_01D964:
	cmp.w	#$FF8F,d1	; general form
	bgt.w	loc_01D970
	move.w	#$FF9E,d1
loc_01D970:
	btst	#5,(TextFlags).w
	beq.w	loc_01D9AA
	move.b	$6A(a3),(ram_BF54).w
	addq.b	#6,$6A(a3)
	addq.b	#2,$6A(a3)
	cmpi.b	#$1E,$6A(a3)
	ble.w	loc_01D998
	move.b	#$1E,$6A(a3)
loc_01D998:
	lea	NullSub(pc),a0
	bsr.w	sub_01EDE8
	move.b	(ram_BF54).w,$6A(a3)
	bra.w	loc_01D9B2
loc_01D9AA:
	lea	NullSub(pc),a0
	bsr.w	sub_01EDE8
loc_01D9B2:
	btst	#5,(TextFlags).w
	beq.w	loc_01D9EE
	move.w	(ram_B774).w,d0
	move.w	$14(a3),d2
	tst.w	d0
	bpl.w	loc_01D9CE
	neg.w	d0
	neg.w	d2
loc_01D9CE:
	sub.w	d0,d2
	cmp.w	#$A,d2	; general form
	blt.w	loc_01D9EC
	move.w	(a3),d0
	sub.w	(ram_B760).w,d0
	bpl.w	loc_01D9E4
	neg.w	d0
loc_01D9E4:
	cmp.w	#$F,d0	; general form
	blt.w	loc_01D9EE
loc_01D9EC:
	rts
loc_01D9EE:
	btst	#5,(TextFlags).w
	beq.w	sub_01DA26
	move.b	$76(a3),d0
	ext.w	d0
	movem.l	d0/a3,-(sp)
	add.b	d0,d0
	cmp.b	#$1E,d0	; general form
	blt.w	loc_01DA10
	move.b	#$1E,d0
loc_01DA10:
	move.b	d0,$76(a3)
	bsr.w	sub_01DA26
	movem.l	(sp)+,d0/a3
	move.b	d0,$76(a3)
	rts
loc_01DA22:
	bsr.w	sub_01EFE2

; ----------------------------------------------------------------------
; called from $00F31C, $0109C6, $010B78, $010F00, $01D8CC, $01D9F4, $01DA14
sub_01DA26:
	tst.w	$34(a3)
	bne.w	loc_01DA30
	rts
loc_01DA30:
	btst	#3,$62(a3)
	bne.w	loc_01DA5C
	jsr	(sub_1D237C).l
	beq.w	loc_01DA5C
	move.w	#$9B4,d1
	bset	#3,(ram_C354).w
	jsr	(sub_01F3B2).l
	bset	#5,$62(a3)
	rts
loc_01DA5C:
	cmpi.w	#$6,$24(a2)
	beq.w	loc_01DA80
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_01DA76
	neg.w	d0
loc_01DA76:
	cmp.w	#$76,d0	; general form
	bge.w	loc_01DA80
loc_01DA7E:
	rts
loc_01DA80:
	move.w	#$28,d0
	tst.w	(ram_B7C0).w
	bmi.w	loc_01DAD6
	lea	$36(a3),a0
	adda.w	(a0),a0
	addq.w	#2,a0
	cmpi.b	#$25,(a0)
	beq.s	loc_01DA7E
	cmpi.b	#$27,(a0)
	beq.s	loc_01DA7E
	cmpi.b	#$2,(a0)
	bne.w	loc_01DAD6
	move.w	(a3),d0
	sub.w	(ram_B760).w,d0
	bpl.w	loc_01DAB4
	neg.w	d0
loc_01DAB4:
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_01DAD6
	move.w	$14(a3),d0
	sub.w	(ram_B774).w,d0
	bpl.w	loc_01DACA
	neg.w	d0
loc_01DACA:
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_01DAD6
	bra.w	loc_01DADA
loc_01DAD6:
	move.w	#$28,d0
loc_01DADA:
	sub.b	$76(a3),d0
	tst.w	(ram_D27E).w
	beq.w	loc_01DAE8
	asl.w	#1,d0
loc_01DAE8:
	bsr.w	Random
	move.w	#$6,d2
	cmpi.w	#$1,(ram_D284).w
	beq.w	loc_01DB0C
	move.w	#$3,d2
	cmpi.w	#$0,(ram_D284).w
	beq.w	loc_01DB0C
	move.w	#$1,d2
loc_01DB0C:
	cmp.w	d2,d0
	bhi.w	NullSub
	moveq	#$5,d2
	movea.w	#$B060,a0
	cmpi.w	#$6,$52(a3)
	bge.w	loc_01DB26
	adda.w	#$300,a0
loc_01DB26:
	tst.w	$34(a0)
	beq.w	loc_01DBB4
	btst	#5,$62(a0)
	bne.w	loc_01DBB4
	btst	#0,$63(a0)
	bne.w	loc_01DBB4
	move.w	(a0),d0
	sub.w	(a3),d0
	cmp.w	#$1E,d0	; general form
	bgt.w	loc_01DBB4
	cmp.w	#$FFE2,d0	; general form
	blt.w	loc_01DBB4
	move.w	$14(a0),d1
	sub.w	$14(a3),d1
	cmp.w	#$1E,d1	; general form
	bgt.w	loc_01DBB4
	cmp.w	#$FFE2,d1	; general form
	blt.w	loc_01DBB4
	bsr.w	sub_01F186
	move.w	$54(a3),d1
	cmp.w	d1,d0
	beq.w	loc_01DB98
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	d1,d0
	beq.w	loc_01DB94
	subq.w	#2,d0
	andi.w	#$7,d0
	cmp.w	d1,d0
	bne.w	loc_01DBB4
loc_01DB94:
	bra.w	loc_01B4A6
loc_01DB98:
	btst	#5,(TextFlags).w
	bne.w	loc_01B4A6
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$3,d0
	bne.w	loc_01B434
	bra.w	loc_01B4A6
loc_01DBB4:
	adda.w	#$80,a0
	dbra	d2,loc_01DB26
	rts


; ----------------------------------------------------------------------
; called from $029EE2
sub_01DBBE:
	btst	#5,$62(a3)
	bne.w	NullSub
	btst	#0,(ram_C33A).w
	bne.w	loc_01BE3A
	btst	#3,$62(a3)
	bne.w	sub_01F156
	bclr	#1,$62(a3)
	beq.w	loc_01DBFC
	bset	#0,$62(a3)
	move.b	#$8,$43(a3)
	clr.b	$42(a3)
	move.w	#$FFFE,$46(a3)
loc_01DBFC:
	tst.w	(ram_B7C0).w
	bpl.w	loc_01DCBA
	addq.w	#1,$46(a3)
	beq.w	loc_01DC10
	bpl.w	loc_01DCB2
loc_01DC10:
	tst.w	(ram_BFA8).w
	bpl.w	loc_01DCB2
	tst.w	$34(a3)
	beq.w	loc_01DCB2
	move.w	d0,-(sp)
	clr.w	$46(a3)
	move.w	#$1,d0
	btst	#6,$62(a3)
	beq.w	loc_01DC38
	move.w	#$2,d0
loc_01DC38:
	cmp.w	(ram_C394).w,d0
	beq.w	loc_01DCB0
	cmp.w	(ram_C396).w,d0
	beq.w	loc_01DCB0
	cmp.w	(ram_C398).w,d0
	beq.w	loc_01DCB0
	cmp.w	(ram_C39A).w,d0
	beq.w	loc_01DCB0
	jsr	(sub_1CF2C4).l
	beq.w	loc_01DCB0
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	bne.w	loc_01DC72
	neg.w	d0
loc_01DC72:
	cmp.w	#$76,d0	; general form
	blt.w	loc_01DC86
	cmp.w	#$11E,d0	; general form
	bgt.w	loc_01DC86
	bra.w	loc_01DC98
loc_01DC86:
	move.w	#$64,d0
	jsr	(Random).l
	cmp.w	#$32,d0	; general form
	bgt.w	loc_01DCB0
loc_01DC98:
	move.w	(sp)+,d0
	move.w	#$FFFF,(ram_DCEA).w
	bclr	#3,(SysFlags).w
	move.w	#$23,d0
	jmp	(sub_01F172).l
loc_01DCB0:
	move.w	(sp)+,d0
loc_01DCB2:
	sub.b	d7,$40(a3)
	bpl.w	NullSub
loc_01DCBA:
	bclr	#0,$62(a3)
	bra.w	sub_01F156


; ----------------------------------------------------------------------
sub_01DCC4:
	move.w	$44(a3),d0
	move.w	$46(a3),d1
	lea	NullSub(pc),a0
	bra.w	sub_01EDE8


; ----------------------------------------------------------------------
; called from $029EE2
sub_01DCD4:
	btst	#5,$62(a3)
	bne.w	NullSub
	bclr	#1,$62(a3)
	beq.w	loc_01DCEE
	jmp	(sub_012E40).l
loc_01DCEE:
	btst	#3,(ram_C33C).w
	beq.w	sub_01F156
	clr.w	d2
	sub.w	d7,$42(a3)
	bpl.w	loc_01DD06
	bset	#5,d2
loc_01DD06:
	btst	#7,(ram_C350).w
	beq.w	loc_01DD3A
	cmpi.w	#$2,(ram_DE84).w
	bne.w	loc_01DD3A
loc_01DD1A:
	move.w	#$64,d0
	jsr	(Random).l
	andi.w	#$7,d0
	cmp.w	#$0,d0	; general form
	beq.s	loc_01DD1A
	cmp.w	#$1,d0	; general form
	beq.s	loc_01DD1A
	cmp.w	#$7,d0	; general form
	beq.s	loc_01DD1A
loc_01DD3A:
	jmp	(sub_012EDA).l


; ----------------------------------------------------------------------
; called from $00F676
sub_01DD40:
	bclr	#1,$62(a3)
	beq.w	loc_01DE48
	bclr	#4,(ram_C350).w
	bset	#7,(ram_C34C).w
	clr.l	(ram_BEB0).w
	clr.l	(ram_BEB4).w
	clr.l	(ram_BEB8).w
	bclr	#7,(ram_C34A).w
	btst	#0,(ram_C34A).w
	beq.w	loc_01DD7C
	jsr	(sub_1D0B8E).l
	bra.w	loc_01DD9E
loc_01DD7C:
	jsr	(sub_1D154A).l
	move.l	a2,-(sp)
	movea.l	#ram_C732,a2
	tst.w	(ram_D2F0).w
	beq.w	loc_01DD98
	movea.l	#ram_CAD0,a2
loc_01DD98:
	addq.w	#1,$39A(a2)
	movea.l	(sp)+,a2
loc_01DD9E:
	bclr	#2,(ram_C342).w
	bclr	#4,(ram_C342).w
	bclr	#5,(ram_C342).w
	bclr	#6,(ram_C342).w
	bset	#1,(TextFlags).w
	btst	#3,(ram_C33A).w
	beq.w	loc_01DDCC
	jmp	(sub_02197E).l
loc_01DDCC:
	bclr	#1,$62(a3)
	btst	#0,(ram_C34A).w
	beq.w	loc_01DE06
	tst.w	(ram_D472).w
	bne.w	loc_01DE22
	tst.w	(ram_D464).w
	bne.w	loc_01DE22
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$3,(ram_D4AC).w
	jsr	(sub_092274).l
	move.w	(ram_D4A8).w,-(sp)
	bra.w	loc_01DE1C
loc_01DE06:
	move.w	(ram_C3AC).w,(ram_D4AA).w
	move.w	#$3,(ram_D4AC).w
	jsr	(sub_092274).l
	move.w	(ram_D4A8).w,-(sp)
loc_01DE1C:
	jsr	(sub_092172).l
loc_01DE22:
	bset	#0,(ram_C33A).w
	bset	#1,(ram_C34A).w
	clr.w	(ram_B788).w
	clr.w	(ram_B78A).w
	move.w	#$F,(ram_D344).w
	bsr.w	sub_01E512
	st	$40(a3)
	st	$42(a3)
loc_01DE48:
	bset	#2,(ram_C342).w
	movem.w	d1/d2,-(sp)
	btst	#0,(ram_C34A).w
	beq.w	loc_01DE66
	jsr	(sub_01DEFA).l
	bmi.w	loc_01DE6E
loc_01DE66:
	movem.w	(sp)+,d1/d2
	bra.w	loc_01DE82
loc_01DE6E:
	movem.w	(sp)+,d1/d2
	bclr	#2,(ram_C342).w
	move.w	#$1B,d0
	bsr.w	sub_01F172
	rts
loc_01DE82:
	movem.w	d1/d2,-(sp)
	move.w	(ram_D2F4).w,d0
	movea.l	#ram_B060,a2
	asl.w	#7,d0
	adda.w	d0,a2
	tst.w	$34(a2)
	bne.w	loc_01DEA6
	btst	#2,$63(a2)
	beq.w	loc_01DEEA
loc_01DEA6:
	move.w	(ram_D2F4).w,d0
	move.w	#$6,d2
loc_01DEAE:
	subq.w	#1,d2
	bmi.s	loc_01DE6E
	subq.w	#1,d0
	bpl.w	loc_01DEC0
	move.w	#$5,d0
	bra.w	loc_01DECC
loc_01DEC0:
	cmp.w	#$5,d0	; general form
	bne.w	loc_01DECC
	move.w	#$B,d0
loc_01DECC:
	movea.l	#ram_B060,a2
	move.w	d0,d1
	asl.w	#7,d1
	adda.w	d1,a2
	tst.w	$34(a2)
	bne.s	loc_01DEAE
	btst	#2,$63(a2)
	bne.s	loc_01DEAE
	move.w	d0,(ram_D2F4).w
loc_01DEEA:
	movem.w	(sp)+,d1/d2
	movea.w	#$C732,a2
	move.w	#$1F,d0
	bra.w	sub_01F172


; ----------------------------------------------------------------------
; called from $01DE5C
sub_01DEFA:
	movem.l	d0-d7/a0-a6,-(sp)
	movea.l	#ram_C732,a0
	tst.w	(ram_D2F0).w
	beq.w	loc_01DF12
	movea.l	#ram_CAD0,a0
loc_01DF12:
	move.w	#$0,d1
	move.w	#$FFFF,d6
	move.w	#$FFFF,d5
	move.w	$28(a0),d7
	jsr	(sub_01A278).l
	subq.w	#1,d0
	move.w	d0,(ram_B8C6).w
loc_01DF2E:
	tst.w	(ram_B8C6).w
	bmi.w	loc_01E008
	movem.l	d0/d1/a1,-(sp)
	move.w	$28(a0),d7
	move.w	d1,d0
	jsr	(sub_013C76).l
	movea.l	a1,a2
	movem.l	(sp)+,d0/d1/a1
	adda.w	(a2),a2
	move.w	d1,d7
	asl.w	#1,d7
	move.b	$4(a2),d0
	andi.w	#$F0,d0
	beq.w	loc_01DFFE
	btst	#0,(ram_C34A).w
	bne.w	loc_01E012
	cmpi.w	#$FFFE,$6C(a0,d7.w)
	beq.w	loc_01DF7C
	cmpi.w	#$FFFF,$6C(a0,d7.w)
	bne.w	loc_01DFFE
loc_01DF7C:
	clr.w	d3
	clr.w	d0
	move.b	$1(a2),d0
	andi.w	#$F,d0
	add.w	d0,d3
	move.b	$2(a2),d0
	andi.w	#$F,d0
	add.w	d0,d3
	move.b	$2(a2),d0
	andi.w	#$F0,d0
	lsr.w	#4,d0
	add.w	d0,d3
	move.b	$3(a2),d0
	andi.w	#$F,d0
	add.w	d0,d3
	move.b	$3(a2),d0
	andi.w	#$F0,d0
	lsr.w	#4,d0
	add.w	d0,d3
	move.b	$5(a2),d0
	andi.w	#$F,d0
	add.w	d0,d3
	move.b	$5(a2),d0
	andi.w	#$F0,d0
	lsr.w	#4,d0
	add.w	d0,d3
	move.b	$6(a2),d0
	andi.w	#$F0,d0
	lsr.w	#4,d0
	add.w	d0,d3
	move.b	$7(a2),d0
	andi.w	#$F0,d0
	lsr.w	#4,d0
	add.w	d0,d3
	cmp.w	(ram_D2F6).w,d1
	bne.w	loc_01DFF0
	move.w	#$7FFF,d3
loc_01DFF0:
	cmp.w	d6,d3
	blt.w	loc_01DFFE
	move.w	d3,d6
	move.w	d1,d5
	bra.w	loc_01DFFE
loc_01DFFE:
	addq.w	#1,d1
	subq.w	#1,(ram_B8C6).w
	bra.w	loc_01DF2E
loc_01E008:
	tst.w	d5
	bmi.w	loc_01E03C
	move.w	d5,(ram_D2F6).w
loc_01E012:
	move.w	#$0,(ram_D2F2).w
	tst.w	(ram_D2F0).w
	beq.w	loc_01E026
	move.w	#$6,(ram_D2F2).w
loc_01E026:
	move.w	(ram_D2F2).w,d0
	asl.w	#7,d0
	movea.l	#ram_B060,a3
	adda.w	d0,a3
	move.w	(ram_D2F6).w,d3
	bra.w	loc_01E044
loc_01E03C:
	move.w	#$FFFF,d0
	bra.w	loc_01E048
loc_01E044:
	move.w	#$1,d0
loc_01E048:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00F67A
sub_01E04E:
	bclr	#1,$62(a3)
	beq.w	loc_01E36E
	movem.l	d0-d7/a0-a6,-(sp)
	bsr.w	sub_01FFA2
loc_01E060:
	btst	#0,(VideoFlags).w
	bne.s	loc_01E060
	cmpi.w	#$258,(ram_B8B4).w
	bls.w	loc_01E07E
	move.w	#$258,(ram_B8B4).w
	addi.w	#$14,(ram_B8BA).w
loc_01E07E:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_RefereeCutscene_Tiles,a2
	jsr	(sub_020780).l
	bset	#3,(VideoFlags).w
	bclr	#0,(ram_C33C).w
	bclr	#0,(ram_C340).w
	move.w	#$3E8,(ram_BF18).w
	move.w	#$3E8,(ram_BF16).w
	clr.b	(ram_BFBC).w
	st	(ram_C452).w
	bclr	#1,(ram_C33E).w
	st	(ram_BF14).w
	bsr.w	sub_022252
	clr.w	(ram_BD30).w
	clr.w	(ram_BD34).w
	move.w	#$0,(ram_B760).w
	move.w	#$0,(ram_B774).w
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
	bclr	#6,(ram_C33C).w
	moveq	#$64,d4
loc_01E130:
	bsr.w	sub_01B29A
	dbra	d4,loc_01E130
	move.w	#$3C,(ram_BFE2).w
	bsr.w	sub_0253C4
	movea.w	#$C732,a2
	bsr.w	sub_025122
	bsr.w	sub_0252D6
	adda.w	#$39E,a2
	bsr.w	sub_025122
	bsr.w	sub_0252D6
	jsr	(sub_026A0C).l
	move.l	a3,-(sp)
	movea.l	#ram_B5E0,a3
	move.w	#$B,d2
loc_01E16C:
	cmp.w	(ram_D2F2).w,d2
	beq.w	loc_01E194
	cmp.w	(ram_D2F4).w,d2
	beq.w	loc_01E214
	move.w	#$FF10,(a3)
	clr.w	$14(a3)
	clr.w	$6(a3)
	move.w	#$20,d0
	bsr.w	sub_01F168
	bra.w	loc_01E2C0
loc_01E194:
	tst.w	$34(a3)
	bpl.w	loc_01E1C8
	bclr	#2,$63(a3)
	beq.w	loc_01E1C8
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d3
	move.b	$67(a3),d3
	jsr	(sub_025470).l
	movem.l	(sp)+,d0-d7/a0-a6
	tst.w	$34(a3)
	beq.w	loc_01E1C6
	bpl.w	loc_01E1C8
loc_01E1C6:
	nop
loc_01E1C8:
	move.w	(ram_B760).w,d0
	subi.w	#$0,d0
	move.w	d0,(a3)
	move.w	(ram_B774).w,d0
	btst	#7,$62(a3)
	bne.w	loc_01E1EE
	addi.w	#$10,d0
	move.w	#$4,$54(a3)
	bra.w	loc_01E1F8
loc_01E1EE:
	addi.w	#$FFF0,d0
	move.w	#$0,$54(a3)
loc_01E1F8:
	move.w	d0,$14(a3)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	clr.w	$2C(a3)
	move.w	#$11,d0
	bsr.w	sub_01F168
	bra.w	loc_01E2C0
loc_01E214:
	btst	#0,(ram_C34A).w
	beq.w	loc_01E236
	move.b	(ram_D471).w,$67(a3)
	tst.w	(ram_D472).w
	beq.w	loc_01E248
	move.b	(ram_D463).w,$67(a3)
	bra.w	loc_01E248
loc_01E236:
	tst.w	$34(a3)
	bpl.w	loc_01E26A
	bclr	#2,$63(a3)
	beq.w	loc_01E26A
loc_01E248:
	movem.l	d0-d7/a0-a6,-(sp)
	clr.w	d3
	move.b	$67(a3),d3
	jsr	(sub_025470).l
	movem.l	(sp)+,d0-d7/a0-a6
	tst.w	$34(a3)
	bne.w	loc_01E268
	bpl.w	loc_01E26A
loc_01E268:
	nop
loc_01E26A:
	bclr	#2,$63(a3)
	move.w	#$0,d0
	move.w	#$E5,d1
	btst	#7,$62(a3)
	bne.w	loc_01E286
	move.w	#$FF1B,d1
loc_01E286:
	move.w	d0,(a3)
	move.w	d1,$14(a3)
	clr.w	$28(a3)
	clr.w	$2A(a3)
	clr.w	$18(a3)
	sub.w	(ram_B760).w,d0
	sub.w	(ram_B774).w,d1
	neg.w	d0
	neg.w	d1
	bsr.w	sub_01F186
	move.w	d0,$54(a3)
	bclr	#2,$63(a3)
	bclr	#5,$62(a3)
	move.w	#$870,d1
	bsr.w	sub_01F3B2
loc_01E2C0:
	suba.l	#$80,a3
	dbra	d2,loc_01E16C
	jsr	(sub_02698A).l
	movea.l	(sp)+,a3
	bsr.w	sub_01E68E
	move.w	(ram_D2F4).w,d0
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	move.w	#$0,(a3)
	move.w	#$FF06,$14(a3)
	btst	#7,$62(a3)
	bne.w	loc_01E2FC
	move.w	#$FA,$14(a3)
loc_01E2FC:
	move.w	(ram_D2F4).w,d0
	move.w	#$1,d1
	btst	#6,$62(a3)
	beq.w	loc_01E312
	move.w	#$2,d1
loc_01E312:
	cmp.w	(ram_C394).w,d1
	bne.w	loc_01E324
	jsr	(sub_01B752).l
	bra.w	loc_01E332
loc_01E324:
	cmp.w	(ram_C396).w,d1
	bne.w	loc_01E332
	jsr	(sub_01B75C).l
loc_01E332:
	move.w	#$E,d0
	bsr.w	sub_01F172
	bset	#7,(ram_C342).w
	bset	#2,(ram_C33E).w
	move.w	#$190,(ram_C382).w
	tst.w	(ram_C394).w
	bne.w	loc_01E362
	tst.w	(ram_C396).w
	bne.w	loc_01E362
	move.w	#$64,(ram_C382).w
loc_01E362:
	move.w	#$18,(FadeCounter).w
	movem.l	(sp)+,d0-d7/a0-a6
	rts
loc_01E36E:
	bset	#2,(ram_C34A).w
	move.w	#$18,d0
	bsr.w	sub_01F172
	clr.w	$28(a3)
	clr.w	$2A(a3)
	rts

	dc.w	$0001,$0203,$0405,$0600,$0001,$0503,$0402,$0000
	dc.w	$0003,$0501,$0400,$0000,$0000,$FF06,$FFDD,$FFCE
	dc.w	$0023,$FFCE,$FFCE,$FFF6,$0000,$FFF1,$0032,$FFF6
	dc.w	$0000,$FFC4


; ----------------------------------------------------------------------
; called from $01E8B8
sub_01E3BA:
	movem.w	d0,-(sp)
	move.w	(ram_B7C0).w,d0
	cmp.w	(ram_D2F4).w,d0
	movem.w	(sp)+,d0
	beq.w	loc_01E408
	btst	#5,(ram_C342).w
	beq.w	loc_01E40E
	btst	#5,(ram_C34A).w
	bne.w	loc_01E3F0
	tst.w	(ram_B7C0).w
	bpl.w	loc_01E3F8
	bset	#5,(ram_C34A).w
loc_01E3F0:
	tst.w	(ram_B7C0).w
	bpl.w	loc_01E408
loc_01E3F8:
	tst.w	(ram_C384).w
	bmi.w	loc_01E408
	subq.w	#1,(ram_C384).w
	bra.w	loc_01E40E
loc_01E408:
	bset	#4,(ram_C342).w
loc_01E40E:
	tst.w	(ram_D344).w
	bne.w	loc_01E41C
	bset	#4,(ram_C342).w
loc_01E41C:
	btst	#4,(ram_C342).w
	bne.w	loc_01E428
	rts
loc_01E428:
	btst	#6,(ram_C342).w
	bne.w	loc_01E4A8
	bset	#6,(ram_C342).w
	move.w	#$A,d0
	jsr	(sub_02135E).l

; ----------------------------------------------------------------------
; called from $023DBA
sub_01E442:
	jsr	(sub_01B286).l
	btst	#0,(ram_C34A).w
	bne.w	loc_01E45E
	move.w	#$A,(ram_DD10).w
	bset	#2,(ram_C33E).w
loc_01E45E:
	bset	#0,(ram_C33A).w
	bclr	#2,(ram_C34A).w
	bclr	#2,(ram_C342).w
	bclr	#3,(ram_C342).w
	bclr	#5,(ram_C342).w
	bclr	#4,(ram_C342).w
	bclr	#6,(ram_C342).w
	movem.l	d0/a0,-(sp)
	movea.l	#ram_B060,a0
	move.w	(ram_D2F2).w,d0
	asl.w	#7,d0
	move.b	(ram_C386).w,$61(a0,d0.w)
	movem.l	(sp)+,d0/a0
	jsr	(sub_1D0BE4).l
loc_01E4A8:
	rts


; ----------------------------------------------------------------------
; called from $019460
sub_01E4AA:
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	moveq	#$1,d0
	bsr.w	sub_01E4C6
	moveq	#$2,d0
	exg	a1,a2

; ----------------------------------------------------------------------
; called from $01E4BE
sub_01E4C6:
	tst.w	$26(a2)
	bmi.w	NullSub
	move.w	(ram_B7C0).w,d1
	bmi.w	NullSub
	subq.w	#6,d1
	cmpa.w	#$C732,a2
	beq.w	loc_01E4E2
	not.w	d1
loc_01E4E2:
	tst.w	d1
	bpl.w	NullSub
	btst	#3,(ram_C33A).w
	beq.w	loc_01E4FA
	st	$26(a2)
	bra.w	sub_025122
loc_01E4FA:
	cmp.w	(ram_C394).w,d0
	beq.w	NullSub
	cmp.w	(ram_C396).w,d0
	beq.w	NullSub
	move.w	(ram_B774).w,d1
	bra.w	loc_01E546


; ----------------------------------------------------------------------
; called from $00C0C2, $01DE3C
sub_01E512:
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	moveq	#$1,d0
	bsr.w	sub_01E524
	moveq	#$2,d0
	exg	a1,a2

; ----------------------------------------------------------------------
; called from $01E51C
sub_01E524:
	cmpi.w	#$FFFF,$26(a2)
	beq.w	NullSub
	clr.b	$26(a2)
	cmp.w	(ram_C394).w,d0
	beq.w	NullSub
	cmp.w	(ram_C396).w,d0
	beq.w	NullSub
	move.w	(ram_BFE6).w,d1
loc_01E546:
	cmpi.w	#$2,(ram_C4C8).w
	bne.w	NullSub
	move.w	$C(a1),d0
	sub.w	$C(a2),d0
	bmi.w	NullSub
	cmp.w	#$1,d0	; general form
	bne.w	NullSub
	cmpi.w	#$3C,(ram_C4CA).w
	bgt.w	NullSub
	move.l	a0,-(sp)
	movea.w	$22(a2),a0
	btst	#7,$62(a0)
	movea.l	(sp)+,a0
	bne.w	loc_01E582
	neg.w	d1
loc_01E582:
	tst.w	d1
	bmi.w	NullSub
	st	$26(a2)
	bra.w	sub_025122


; ----------------------------------------------------------------------
; called from $00C202, $01D0D6
sub_01E590:
	movem.l	d0-d2/a0,-(sp)
	moveq	#$3,d0
	move.w	$24(a2),d1
	sub.w	$24(a1),d1
	beq.w	loc_01E5CA
	bpl.w	loc_01E5A8
	addq.w	#2,d0
loc_01E5A8:
	move.w	d0,-(sp)
	bsr.w	sub_0223D0
	move.w	d0,d1
	move.w	(sp),d0
	addq.w	#1,d0
	bsr.w	sub_0223D0
	cmp.w	d0,d1
	bge.w	loc_01E5C0
	addq.w	#1,(sp)
loc_01E5C0:
	move.w	(sp)+,$16(a2)
loc_01E5C4:
	movem.l	(sp)+,d0-d2/a0
	rts
loc_01E5CA:
	cmpa.w	#$C732,a2
	bne.w	loc_01E642
	moveq	#$2,d1
	lea	dat_01E618(pc),a0
	cmpi.w	#$2,(ram_C4C8).w
	bne.w	loc_01E5FA
	move.w	$C(a2),d2
	cmp.w	$C(a1),d2
	beq.w	loc_01E5FA
	adda.w	#$E,a0
	bgt.w	loc_01E5FA
	adda.w	#$E,a0
loc_01E5FA:
	move.w	$16(a1),d1
	asl.w	#1,d1
	move.w	$0(a0,d1.w),d0
	bsr.w	sub_0223D0
	cmp.w	#$C00,d0	; general form
	bls.w	loc_01E642
	move.w	$0(a0,d1.w),$16(a2)
	bra.s	loc_01E5C4
dat_01E618:
	dc.w	$0000,$0001,$0002,$0000,$0001,$0000,$0001,$0002
	dc.w	$0000,$0001,$0002,$0000,$0002,$0000,$0000,$0001
	dc.w	$0000,$0000,$0001,$0000,$0001
loc_01E642:
	moveq	#$2,d1
	lea	dat_01E67C(pc),a0
	cmpi.w	#$2,(ram_C4C8).w
	bne.w	loc_01E666
	move.w	$C(a2),d2
	cmp.w	$C(a1),d2
	beq.w	loc_01E666
	addq.w	#6,a0
	bgt.w	loc_01E666
	addq.w	#6,a0
loc_01E666:
	move.w	(a0)+,d0
	bsr.w	sub_0223D0
	cmp.w	#$C00,d0	; general form
	dbhi	d1,loc_01E666
	move.w	-(a0),$16(a2)
	bra.w	loc_01E5C4
dat_01E67C:
	dc.w	$0000,$0001,$0002,$0000,$0002,$0001,$0000,$0001
	dc.w	$0000


; ----------------------------------------------------------------------
; called from $00C634, $01E2D2
sub_01E68E:
	move.w	#$FFFF,(ram_C388).w
	move.w	#$FFFF,(ram_C38A).w
	move.w	#$FFFF,(ram_C38C).w
	move.w	#$FFFF,(ram_C38E).w
	tst.w	(ram_C394).w
	beq.w	loc_01E70A
	btst	#3,(ram_C350).w
	beq.w	loc_01E702
	cmpi.w	#$1,(ram_C394).w
	beq.w	loc_01E6CE
	tst.w	(ram_C3A6).w
	bne.w	loc_01E702
	beq.w	loc_01E6D6
loc_01E6CE:
	tst.w	(ram_C3A4).w
	bne.w	loc_01E702
loc_01E6D6:
	movem.l	d0/a0/a3,-(sp)
	move.w	#$5,d0
	cmpi.w	#$1,(ram_C394).w
	beq.w	loc_01E6EC
	move.w	#$B,d0
loc_01E6EC:
	jsr	(sub_01B3B8).l
	clr.w	d4
	jsr	(sub_01B752).l
	movem.l	(sp)+,d0/a0/a3
	bra.w	loc_01E70A
loc_01E702:
	clr.w	d4
	jsr	(sub_01B546).l
loc_01E70A:
	tst.w	(ram_C396).w
	beq.w	loc_01E770
	btst	#3,(ram_C350).w
	beq.w	loc_01E768
	cmpi.w	#$2,(ram_C396).w
	beq.w	loc_01E732
	tst.w	(ram_C3A4).w
	bne.w	loc_01E768
	bra.w	loc_01E73A
loc_01E732:
	tst.w	(ram_C3A6).w
	bne.w	loc_01E768
loc_01E73A:
	movem.l	d0/a0/a3,-(sp)
	move.w	#$B,d0
	cmpi.w	#$2,(ram_C396).w
	beq.w	loc_01E750
	move.w	#$5,d0
loc_01E750:
	jsr	(sub_01B3B8).l
	move.w	#$2,d4
	jsr	(sub_01B75C).l
	movem.l	(sp)+,d0/a0/a3
	bra.w	loc_01E770
loc_01E768:
	moveq	#$2,d4
	jsr	(sub_01B546).l
loc_01E770:
	tst.w	(ram_C398).w
	beq.w	loc_01E7D6
	btst	#3,(ram_C350).w
	beq.w	loc_01E7CE
	cmpi.w	#$2,(ram_C398).w
	beq.w	loc_01E798
	tst.w	(ram_C3A4).w
	bne.w	loc_01E7CE
	bra.w	loc_01E7A0
loc_01E798:
	tst.w	(ram_C3A6).w
	bne.w	loc_01E7CE
loc_01E7A0:
	movem.l	d0/a0/a3,-(sp)
	move.w	#$B,d0
	cmpi.w	#$2,(ram_C398).w
	beq.w	loc_01E7B6
	move.w	#$5,d0
loc_01E7B6:
	jsr	(sub_01B3B8).l
	move.w	#$4,d4
	jsr	(sub_01B768).l
	movem.l	(sp)+,d0/a0/a3
	bra.w	loc_01E7D6
loc_01E7CE:
	moveq	#$4,d4
	jsr	(sub_01B546).l
loc_01E7D6:
	tst.w	(ram_C39A).w
	beq.w	loc_01E83C
	btst	#3,(ram_C350).w
	beq.w	loc_01E834
	cmpi.w	#$2,(ram_C39A).w
	beq.w	loc_01E7FE
	tst.w	(ram_C3A4).w
	bne.w	loc_01E834
	bra.w	loc_01E806
loc_01E7FE:
	tst.w	(ram_C3A6).w
	bne.w	loc_01E834
loc_01E806:
	movem.l	d0/a0/a3,-(sp)
	move.w	#$B,d0
	cmpi.w	#$2,(ram_C39A).w
	beq.w	loc_01E81C
	move.w	#$5,d0
loc_01E81C:
	jsr	(sub_01B3B8).l
	move.w	#$6,d4
	jsr	(sub_01B774).l
	movem.l	(sp)+,d0/a0/a3
	bra.w	loc_01E83C
loc_01E834:
	moveq	#$6,d4
	jsr	(sub_01B546).l
loc_01E83C:
	rts
loc_01E83E:
	move.w	$40(a3),d0
	beq.w	loc_01E85E
	addq.w	#6,d0
	lsr.w	#3,d0
	cmp.w	#$2,d0	; general form
	bgt.w	NullSub
	neg.w	d0
	addi.w	#$A,d0
	move.w	d0,(ram_BDC8).w
	rts
loc_01E85E:
	bclr	#4,(VideoFlags).w
	bsr.w	Text_Print
inl_01E868:
	dc.w	loc_01E86E-inl_01E868
	dc.b	$BF,$00,$00,$00
loc_01E86E:
	move.w	(ram_B04C).w,d0
	subi.w	#$2E,d0
	asr.w	#3,d0
	move.w	d0,(TextX).w
	moveq	#$64,d0
	move.w	(ram_B04E).w,d0
	subi.w	#$44,d0
	asr.w	#3,d0
	move.w	d0,(TextY).w
	moveq	#$C,d0
	moveq	#$D,d1
	move.w	#$7FF,d2
	btst	#3,(ram_C350).w
	bne.w	loc_01E8A2
	bra.w	Text_FillRect
loc_01E8A2:
	bset	#3,(VideoFlags).w
	jmp	(sub_022296).l


; ----------------------------------------------------------------------
; called from $00F65E
sub_01E8AE:
	btst	#2,(ram_C342).w
	beq.w	loc_01E8BC
	bsr.w	sub_01E3BA
loc_01E8BC:
	bclr	#1,$62(a3)
	beq.w	loc_01E8D0
	clr.w	$40(a3)
	move.w	#$78,$42(a3)
loc_01E8D0:
	movea.w	#$BF1C,a1
	sub.w	d7,$2(a1)
	sub.w	d7,$6(a1)
	sub.w	d7,$40(a3)
	bpl.w	loc_01E8EC
	addq.w	#5,$40(a3)
	bsr.w	sub_01ED66
loc_01E8EC:
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_01E928
	asl.w	#7,d0
	movea.w	#$B060,a2
	adda.w	d0,a2
	bsr.w	sub_01EAE0
	move.l	a2,-(sp)
	bsr.w	sub_01F1F0
	add.w	(a2),d0
	sub.w	(a3),d0
	asr.w	#2,d0
	add.w	d0,(a3)
	add.w	$14(a2),d1
	sub.w	$14(a3),d1
	asr.w	#2,d1
	add.w	d1,$14(a3)
	move.w	$28(a2),$28(a3)
	move.w	$2A(a2),$2A(a3)
loc_01E928:
	jsr	(sub_01EBFA).l
	jsr	(sub_01E98E).l
	btst	#0,(ram_C33A).w
	bne.w	loc_01E976
	tst.w	(ram_B7C0).w
	bpl.w	loc_01E970
	move.w	(a3),d0
	cmp.w	$1C(a3),d0
	bne.w	loc_01E970
	move.w	$14(a3),d0
	cmp.w	$20(a3),d0
	bne.w	loc_01E970
	moveq	#$6,d0
	subq.w	#1,$42(a3)
	bpl.w	loc_01E96C
	jsr	(sub_02135E).l
loc_01E96C:
	bra.w	loc_01E976
loc_01E970:
	move.w	#$78,$42(a3)
loc_01E976:
	tst.b	$2C(a3)
	bne.w	loc_024530
	tst.w	$18(a3)
	bne.w	loc_024530
	bsr.w	sub_01EC5C
	bra.w	loc_024530


; ----------------------------------------------------------------------
; called from $01E92E
sub_01E98E:
	btst	#5,(ram_C33A).w
	beq.w	NullSub
	btst	#2,(ram_C342).w
	bne.w	NullSub
	movea.w	#$C732,a1
	lea	$39E(a1),a2
	bsr.w	sub_01EA4A
	exg	a1,a2
	bsr.w	sub_01EA4A
	move.w	#$72,d0
	cmp.w	$14(a3),d0
	bgt.w	loc_01EA00
	cmp.w	$20(a3),d0
	ble.w	NullSub
	addi.w	#$A,d0
	btst	#1,(ram_C33A).w
	beq.w	loc_01E9D8
	exg	a2,a1
loc_01E9D8:
	moveq	#$5,d2
	movea.w	$22(a2),a0
loc_01E9DE:
	tst.w	$34(a0)
	bmi.w	loc_01E9F6
	cmp.w	$14(a0),d0
	bge.w	loc_01E9F6
	bset	#4,$30(a2)
	rts
loc_01E9F6:
	adda.w	#$80,a0
	dbra	d2,loc_01E9DE
	rts
loc_01EA00:
	neg.w	d0
	cmp.w	$14(a3),d0
	blt.w	NullSub
	cmp.w	$20(a3),d0
	bge.w	NullSub
	subi.w	#$A,d0
	btst	#1,(ram_C33A).w
	bne.w	loc_01EA22
	exg	a2,a1
loc_01EA22:
	moveq	#$5,d2
	movea.w	$22(a2),a0
loc_01EA28:
	tst.w	$34(a0)
	bmi.w	loc_01EA40
	cmp.w	$14(a0),d0
	ble.w	loc_01EA40
	bset	#4,$30(a2)
	rts
loc_01EA40:
	adda.w	#$80,a0
	dbra	d2,loc_01EA28
	rts


; ----------------------------------------------------------------------
; called from $01E9AA, $01E9B0
sub_01EA4A:
	btst	#4,$30(a2)
	beq.w	NullSub
	movea.w	$22(a2),a0
	moveq	#$5,d1
loc_01EA5A:
	tst.w	$34(a0)
	bmi.w	loc_01EA72
	move.w	$14(a0),d0
	btst	#7,$62(a0)
	bne.w	loc_01EA72
	neg.w	d0
loc_01EA72:
	adda.w	#$80,a0
	cmp.w	#$76,d0	; general form
	dbgt	d1,loc_01EA5A
	bgt.w	NullSub
	bclr	#4,$30(a2)
	rts


; ----------------------------------------------------------------------
; called from $01EB4C, $1CF3FE
sub_01EA8A:
	btst	#5,(ram_C33A).w
	beq.w	NullSub
	move.w	(ram_B774).w,d0
	btst	#7,$62(a2)
	bne.w	loc_01EAA4
	neg.w	d0
loc_01EAA4:
	cmp.w	#$86,d0	; general form
	blt.w	NullSub
	movea.w	#$C732,a0
	btst	#6,$62(a2)
	beq.w	loc_01EABE
	adda.w	#$39E,a0
loc_01EABE:
	btst	#4,$30(a0)
	beq.w	NullSub
	btst	#4,(ram_C33A).w
	bne.w	NullSub
	exg	a2,a3
	moveq	#$10,d0
	jsr	(sub_02131E).l
	exg	a2,a3
	rts


; ----------------------------------------------------------------------
; called from $01E8FC, $024A16, $024D14, $024E06
sub_01EAE0:
	move.w	(a2),(ram_BFB8).w
	move.w	$14(a2),(ram_BFBA).w
	move.w	$52(a2),(ram_BFB6).w
	movea.w	#$C732,a0
	btst	#6,$62(a2)
	beq.w	loc_01EB02
	lea	$39E(a0),a0
loc_01EB02:
	clr.w	d0
	move.b	$67(a2),d0
	btst	#3,$64(a2)
	beq.w	loc_01EB18
	bset	#7,(ram_C34E).w
loc_01EB18:
	cmp.w	$18(a0),d0
	beq.w	loc_01EB46
	bclr	#3,$30(a0)
	bne.w	loc_01EB36
	move.w	$1A(a0),$1C(a0)
	move.w	$18(a0),$1A(a0)
loc_01EB36:
	move.w	d0,$18(a0)
	cmp.w	$1C(a0),d0
	bne.w	loc_01EB46
	st	$1C(a0)
loc_01EB46:
	bclr	#4,(ram_C33E).w
	bsr.w	sub_01EA8A
	btst	#2,(ram_BFBC).w
	beq.w	loc_01EBA6
	btst	#0,(ram_BFBC).w
	beq.w	loc_01EBA6
	tst.w	$34(a2)
	beq.w	loc_01EBA6
	btst	#1,(ram_BFBC).w
	bne.w	loc_01EB9E
	btst	#7,$62(a2)
	beq.w	loc_01EBA6
loc_01EB80:
	clr.w	d0
	move.b	(ram_BFBD).w,d0
	asl.w	#7,d0
	move.l	a3,-(sp)
	movea.w	#$B060,a3
	adda.w	d0,a3
	move.w	#$C,d0
	jsr	(sub_02131E).l
	movea.l	(sp)+,a3
	rts
loc_01EB9E:
	btst	#7,$62(a2)
	beq.s	loc_01EB80
loc_01EBA6:
	bsr.w	sub_01EBAC
	rts


; ----------------------------------------------------------------------
; called from $01EBA6, $1CF40A
sub_01EBAC:
	clr.b	(ram_BFBC).w
	move.b	$53(a2),(ram_BFBD).w
	move.w	(ram_B774).w,d0
	btst	#7,$62(a2)
	beq.w	loc_01EBCC
	bset	#1,(ram_BFBC).w
	neg.w	d0
loc_01EBCC:
	bmi.w	NullSub
	move.w	(ram_C756).w,d0
	sub.w	(ram_CAF4).w,d0
	btst	#6,$62(a2)
	beq.w	loc_01EBE4
	neg.w	d0
loc_01EBE4:
	bmi.w	NullSub
	btst	#3,(ram_C350).w
	bne.w	loc_01EBF8
	bset	#2,(ram_BFBC).w
loc_01EBF8:
	rts


; ----------------------------------------------------------------------
; called from $01E928
sub_01EBFA:
	btst	#2,(ram_BFBC).w
	beq.w	NullSub
	btst	#0,(ram_BFBC).w
	bne.w	NullSub
	tst.w	(ram_B7C0).w
	bpl.w	NullSub
	move.w	#$11E,d0
	btst	#1,(ram_BFBC).w
	bne.w	loc_01EC30
	neg.w	d0
	cmp.w	(ram_B774).w,d0
	bgt.w	loc_01EC38
	rts
loc_01EC30:
	cmp.w	(ram_B774).w,d0
	bgt.w	NullSub
loc_01EC38:
	cmpi.w	#$2C,(ram_B760).w
	bgt.w	loc_01EC54
	cmpi.w	#$FFD4,(ram_B760).w
	blt.w	loc_01EC54
	bclr	#2,(ram_BFBC).w
	rts
loc_01EC54:
	bset	#0,(ram_BFBC).w
	rts


; ----------------------------------------------------------------------
; called from $00F666, $01E986
sub_01EC5C:
	cmpi.w	#$8,$5A(a3)
	blt.w	loc_01EC76
	cmpi.w	#$18,$5A(a3)
	bge.w	loc_01EC76
	eori.w	#$2,$54(a3)
loc_01EC76:
	ori.w	#$4,$54(a3)
	clr.w	$5A(a3)
	st	$5C(a3)
	rts


; ----------------------------------------------------------------------
; called from $023D02, $02440E, $024D52, $024F16, $0250C6, $1CEE6A
sub_01EC86:
	andi.w	#$1,d0
	eor.w	d0,$54(a3)
	andi.w	#$3,$54(a3)
	st	$5C(a3)
	move.w	#$2CEE,d1
	bra.w	sub_01F3B2


; ----------------------------------------------------------------------
; called from $00F662
sub_01ECA0:
	cmpi.w	#$2C46,$58(a3)
	beq.w	loc_01ED24
	tst.w	(ram_DDEE).w
	beq.w	loc_01ECFA
	subq.w	#1,(ram_DDEE).w
	bne.w	loc_01ECC8
	clr.w	$58(a3)
	move.w	#$299,$6(a3)
	bra.w	loc_01ED04
loc_01ECC8:
	cmpi.w	#$2C78,$58(a3)
	beq.w	loc_01ED24
	clr.w	$28(a3)
	clr.w	$2A(a3)
	clr.w	$28(a3)
	move.w	#$48,(a3)
	move.w	#$146,$14(a3)
	move.w	#$18,$18(a3)
	move.w	#$2C78,d1
	jsr	(sub_01F3B2).l
	rts
loc_01ECFA:
	cmpi.w	#$299,$6(a3)
	bne.w	loc_01ED26
loc_01ED04:
	move.w	-$80(a3),(a3)
	move.w	-$6C(a3),$14(a3)
	clr.w	$18(a3)
	moveq	#$14,d0
	btst	#7,(ram_C33C).w
	beq.w	loc_01ED20
	moveq	#$0,d0
loc_01ED20:
	addq.w	#1,$0(a3,d0.w)
loc_01ED24:
	rts
loc_01ED26:
	tst.w	$6(a3)
	beq.w	NullSub
	clr.w	(a3)
	move.w	#$14B,$14(a3)
	move.w	#$E,$18(a3)
	tst.w	-$6C(a3)
	bpl.w	loc_01ED64
	move.w	#$8000,$4(a3)
	btst	#0,(ram_C35C).w
	beq.w	loc_01ED5A
	move.w	#$0,$4(a3)
loc_01ED5A:
	move.w	#$FEB1,$14(a3)
	subq.w	#1,$18(a3)
loc_01ED64:
	rts


; ----------------------------------------------------------------------
; called from $01E8E8
sub_01ED66:
	movem.l	d0-d4/a1/a2,-(sp)
	movea.w	#$BF1C,a1
	move.w	#$96,d1
	move.w	#$11E,d4
	bsr.w	sub_01ED86
	neg.w	d4
	bsr.w	sub_01ED86
	movem.l	(sp)+,d0-d4/a1/a2
	rts


; ----------------------------------------------------------------------
; called from $01ED76, $01ED7C
sub_01ED86:
	move.w	d4,d0
	sub.w	(ram_B774).w,d0
	tst.w	(ram_B78A).w
	beq.w	loc_01EDDE
	move.w	d0,d2
	swap	d2
	clr.w	d2
	asr.l	#4,d2
	divs.w	(ram_B78A).w,d2
	bmi.w	loc_01EDDE
	move.w	d2,$2(a1)
	muls.w	(ram_B788).w,d0
	divs.w	(ram_B78A).w,d0
	bvs.w	loc_01EDDE
	add.w	(ram_B760).w,d0
	cmp.w	d1,d0
	blt.w	loc_01EDC6
	neg.w	d0
	add.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
loc_01EDC6:
	neg.w	d1
	cmp.w	d1,d0
	bgt.w	loc_01EDD6
	neg.w	d0
	add.w	d1,d0
	add.w	d1,d0
	add.w	d1,d0
loc_01EDD6:
	neg.w	d1
	move.w	d0,(a1)
	bra.w	loc_01EDE4
loc_01EDDE:
	move.w	#$FFFF,$2(a1)
loc_01EDE4:
	addq.w	#4,a1
	rts


; ----------------------------------------------------------------------
; called from $00F316, $00F8C6, $00FAF8, $00FC62, $00FE5E, $010092, $01028C, $01054C (+20 more)
sub_01EDE8:
	sub.b	d7,$42(a3)
	bpl.w	loc_01EE9E
	addi.b	#$C,$42(a3)
	bsr.w	sub_01EEA8
	movem.w	d0/d1,-(sp)
	move.w	$28(a3),d0
	asr.w	#8,d0
	neg.w	d0
	add.w	(sp)+,d0
	sub.w	(a3),d0
	move.w	$2A(a3),d1
	asr.w	#8,d1
	neg.w	d1
	add.w	(sp)+,d1
	sub.w	$14(a3),d1
	cmp.w	#$C,d0	; general form
	bgt.w	loc_01EE3E
	cmp.w	#$FFF4,d0	; general form
	blt.w	loc_01EE3E
	cmp.w	#$C,d1	; general form
	bgt.w	loc_01EE3E
	cmp.w	#$FFF4,d1	; general form
	blt.w	loc_01EE3E
	moveq	#$9,d0
	bra.w	loc_01EE42
loc_01EE3E:
	bsr.w	sub_01F186
loc_01EE42:
	jsr	(a0)
	move.b	d0,$43(a3)
	cmp.w	#$7,d0	; general form
	ble.w	loc_01EE9E
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	bne.w	loc_01EE9E
	move.w	(ram_B760).w,d0
	move.w	(ram_B774).w,d1
	btst	#0,(ram_B7C3).w
	beq.w	loc_01EE76
	move.w	(ram_BFDE).w,d0
	move.w	(ram_BFE0).w,d1
loc_01EE76:
	sub.w	(a3),d0
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	sub.w	$54(a3),d0
	beq.w	loc_01EE9E
	neg.w	d0
	andi.w	#$4,d0
	lsr.w	#1,d0
	subq.w	#1,d0
	add.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,$54(a3)
loc_01EE9E:
	clr.w	d0
	move.b	$43(a3),d0
	bra.w	loc_01F3C8


; ----------------------------------------------------------------------
; called from $01EDF6, $01EFFC
sub_01EEA8:
	clr.w	(ram_BFEC).w
	clr.w	(ram_BFEE).w
	tst.w	$34(a3)
	beq.w	NullSub
	move.w	(a3),d2
	eor.w	d0,d2
	bpl.w	loc_01EF3E
	move.w	d1,d2
	sub.w	$14(a3),d2
	move.w	(a3),d3
	muls.w	d3,d2
	sub.w	d0,d3
	divs.w	d3,d2
	add.w	$14(a3),d2
	cmp.w	#$137,d2	; general form
	bgt.w	loc_01EF3E
	cmp.w	#$F1,d2	; general form
	blt.w	loc_01EF0A
	move.w	#$15A,d3
	cmp.w	#$114,d2	; general form
	bgt.w	loc_01EF00
	blt.w	loc_01EEFC
	cmpi.w	#$114,$14(a3)
	bgt.w	loc_01EF00
loc_01EEFC:
	move.w	#$CE,d3
loc_01EF00:
	sub.w	d2,d3
	move.w	d3,(ram_BFEE).w
	bra.w	loc_01EF3E
loc_01EF0A:
	cmp.w	#$FF0F,d2	; general form
	bgt.w	loc_01EF3E
	cmp.w	#$FEC9,d2	; general form
	blt.w	loc_01EF3E
	move.w	#$FF32,d3
	cmp.w	#$FEEC,d2	; general form
	bgt.w	loc_01EF38
	blt.w	loc_01EF34
	cmpi.w	#$FEEC,$14(a3)
	bgt.w	loc_01EF38
loc_01EF34:
	move.w	#$FEA6,d3
loc_01EF38:
	sub.w	d2,d3
	move.w	d3,(ram_BFEE).w
loc_01EF3E:
	move.w	d1,d3
	subi.w	#$114,d3
	move.w	$14(a3),d2
	subi.w	#$114,d2
	bsr.w	sub_01EF6C
	move.w	d1,d3
	addi.w	#$114,d3
	move.w	$14(a3),d2
	addi.w	#$114,d2
	bsr.w	sub_01EF6C
	add.w	(ram_BFEC).w,d0
	add.w	(ram_BFEE).w,d1
	rts


; ----------------------------------------------------------------------
; called from $01EF4C, $01EF5E
sub_01EF6C:
	move.w	d3,d4
	eor.w	d2,d4
	bpl.w	NullSub
	move.w	d0,d4
	sub.w	(a3),d4
	muls.w	d2,d4
	sub.w	d3,d2
	divs.w	d2,d4
	add.w	(a3),d4
	cmp.w	#$50,d4	; general form
	bgt.w	NullSub
	cmp.w	#$FFB0,d4	; general form
	blt.w	NullSub
	moveq	#$50,d3
	tst.w	d4
	bne.w	loc_01EF9A
	tst.w	(a3)
loc_01EF9A:
	bpl.w	loc_01EFA0
	neg.w	d3
loc_01EFA0:
	sub.w	d4,d3
	move.w	d3,(ram_BFEC).w
	rts


; ----------------------------------------------------------------------
; called from $01D91A, $01EFEC
sub_01EFA8:
	btst	#4,$62(a3)
	bne.w	loc_01EFC8
	move.w	(ram_B788).w,d0
	asr.w	#8,d0
	add.w	(ram_B760).w,d0
	move.w	(ram_B78A).w,d1
	asr.w	#8,d1
	add.w	(ram_B774).w,d1
	rts
loc_01EFC8:
	move.b	(ram_B788).w,d0
	asr.b	#1,d0
	ext.w	d0
	add.w	(ram_B760).w,d0
	move.b	(ram_B78A).w,d1
	asr.b	#1,d1
	ext.w	d1
	add.w	(ram_B774).w,d1
	rts


; ----------------------------------------------------------------------
; called from $01CBEE, $01DA22
sub_01EFE2:
	tst.w	$34(a3)
	bne.w	loc_01EFEC
	nop
loc_01EFEC:
	bsr.s	sub_01EFA8
	sub.b	d7,$42(a3)
	bpl.w	loc_01F0F6
	addi.b	#$A,$42(a3)
	bsr.w	sub_01EEA8
	movem.w	d0/d1,-(sp)
	move.l	a3,-(sp)
	bsr.w	sub_01F1F0
	neg.b	d0
	neg.b	d1
	sub.b	$28(a3),d0
	ext.w	d0
	add.w	(sp)+,d0
	sub.w	(a3),d0
	sub.b	$2A(a3),d1
	ext.w	d1
	add.w	(sp)+,d1
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	move.b	d0,$43(a3)
	tst.w	$34(a3)
	beq.w	loc_01F0F6
	move.w	(ram_B788).w,d0
	move.w	(ram_B78A).w,d1
	bsr.w	sub_01F186
	eori.w	#$4,d0
	cmp.w	$54(a3),d0
	beq.w	loc_01F0F6
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	move.w	(ram_B774).w,d1
	sub.w	$14(a3),d1
	movem.w	d0/d1,-(sp)
	bsr.w	sub_01F186
	cmp.w	$54(a3),d0
	movem.w	(sp)+,d0/d1
	bne.w	loc_01F0F6
	muls.w	d0,d0
	muls.w	d1,d1
	add.l	d1,d0
	cmp.l	#loc_000400,d0	; general form
	bls.w	loc_01F0F6
	tst.w	$34(a3)
	beq.w	loc_01F0EC
	movem.w	d0,-(sp)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_01F09A
	neg.w	d0
loc_01F09A:
	cmp.w	#$76,d0	; general form
	blt.w	loc_01F0C0
	move.w	$2A(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_01F0B2
	neg.w	d0
loc_01F0B2:
	tst.w	d0
	bpl.w	loc_01F0C0
	movem.w	(sp)+,d0
	bra.w	loc_01F0EC
loc_01F0C0:
	move.w	#$64,d0
	bsr.w	Random
	cmp.w	#$4B,d0	; general form
	movem.w	(sp)+,d0
	blt.w	loc_01F0EC
	cmp.l	#$9C4,d0	; general form
	bls.w	loc_01F0EC
	btst	#5,$62(a3)
	bne.w	loc_01F0EC
	bsr.w	sub_01B3EC
loc_01F0EC:
	cmp.l	#$5A4,d0	; general form
	bls.w	loc_01B782
loc_01F0F6:
	move.b	$43(a3),d0
	ext.w	d0
	cmp.w	#$7,d0	; general form
	bgt.w	loc_01F118
	cmp.w	$54(a3),d0
	beq.w	loc_01F118
	tst.w	$34(a3)
	beq.w	loc_01F118
	bsr.w	sub_01F11C
loc_01F118:
	bra.w	loc_01F3C8


; ----------------------------------------------------------------------
; called from $010CC8, $010DAE, $01F114
sub_01F11C:
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	move.w	(ram_B774).w,d1
	sub.w	(a3),d0
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	sub.w	$54(a3),d0
	beq.w	loc_01F150
	neg.w	d0
	andi.w	#$4,d0
	lsr.w	#1,d0
	subq.w	#1,d0
	add.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,$54(a3)
loc_01F150:
	movem.w	(sp)+,d0/d1
	rts


; ----------------------------------------------------------------------
; called from $00BEE6, $01B968, $01BB70, $01BDDA, $01BDFE, $01BF80, $01CB62, $01CB6C (+12 more)
sub_01F156:
	addq.w	#1,$36(a3)
	andi.w	#$7,$36(a3)
	bset	#1,$62(a3)
	rts


; ----------------------------------------------------------------------
; called from $00C570, $00E8E4, $00E902, $00E93E, $012E3A, $0135D8, $01958C, $019620 (+11 more)
sub_01F168:
	subq.w	#1,$36(a3)
	andi.w	#$7,$36(a3)

; ----------------------------------------------------------------------
; called from $00BFAA, $00C2B0, $00CA36, $00CD16, $00CE6E, $00D3BC, $00F6EA, $011C42 (+43 more)
sub_01F172:
	move.l	d1,-(sp)
	move.w	$36(a3),d1
	move.b	d0,$38(a3,d1.w)
	bset	#1,$62(a3)
	move.l	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $00C604, $00D170, $011DC4, $012E94, $013392, $013502, $01A4A6, $01BE90 (+32 more)
sub_01F186:
	movem.l	d2/a0,-(sp)
	move.w	d0,d2
	or.w	d1,d2
	beq.w	loc_01F1D8
	clr.w	d2
	tst.w	d0
	bpl.w	loc_01F1A0
	neg.w	d0
	bset	#0,d2
loc_01F1A0:
	tst.w	d1
	bpl.w	loc_01F1AC
	neg.w	d1
	bset	#1,d2
loc_01F1AC:
	asl.w	#1,d1
	cmp.w	d1,d0
	bhi.w	loc_01F1B8
	bset	#2,d2
loc_01F1B8:
	lsr.w	#1,d1
	asl.w	#1,d0
	cmp.w	d0,d1
	bhi.w	loc_01F1C6
	bset	#3,d2
loc_01F1C6:
	movea.l	#dat_01F1E0,a0
	clr.w	d0
	move.b	$0(a0,d2.w),d0
	movem.l	(sp)+,d2/a0
	rts
loc_01F1D8:
	moveq	#$8,d0
	movem.l	(sp)+,d2/a0
	rts
dat_01F1E0:
	dc.w	$0107,$0305,$0000,$0404,$0206,$0206,$0107,$0305


; ----------------------------------------------------------------------
; called from $013600, $01D772, $01E902, $01F006, $022AD2, $024620, $024D3E, $024F0A (+1 more)
sub_01F1F0:
	movem.l	a0/a1,-(sp)
	movea.l	$C(sp),a0
	clr.w	d0
	clr.w	d1
	tst.w	$6(a0)
	ble.w	loc_01F242
	movea.l	#dat_168E0A,a1
	move.w	$6(a0),d0
	add.w	d0,d0
	move.b	$1(a1,d0.w),d1
	ext.w	d1
	move.b	$0(a1,d0.w),d0
	ext.w	d0
	btst	#3,$4(a0)
	beq.w	loc_01F228
	neg.w	d0
loc_01F228:
	btst	#4,$4(a0)
	bne.w	loc_01F234
	neg.w	d1
loc_01F234:
	btst	#7,(ram_C33C).w
	beq.w	loc_01F242
	exg	d0,d1
	neg.w	d1
loc_01F242:
	movem.l	(sp)+,a0/a1
	move.l	(sp)+,(sp)
	rts


; ----------------------------------------------------------------------
; called from $02487C
sub_01F24A:
	movem.l	a0/a1,-(sp)
	movea.l	$C(sp),a0
	clr.w	d0
	clr.w	d1
	tst.w	$6(a0)
	ble.w	loc_01F2B4
	movea.l	#dat_169DDE,a1
	move.w	$6(a0),d0
	move.w	(a1)+,d1
	subq.w	#1,d1
	sub.w	d1,d0
	bmi.w	loc_01F2BC
	asl.w	#2,d0
	add.w	$6(a0),d0
	add.w	$6(a0),d0
	move.b	$1(a1,d0.w),d1
	ext.w	d1
	move.b	$0(a1,d0.w),d0
	ext.w	d0
	btst	#3,$4(a0)
	beq.w	loc_01F294
	neg.w	d0
loc_01F294:
	btst	#4,$4(a0)
	bne.w	loc_01F2A0
	neg.w	d1
loc_01F2A0:
	btst	#7,(ram_C33C).w
	beq.w	loc_01F2AE
	exg	d0,d1
	neg.w	d1
loc_01F2AE:
	add.w	$14(a0),d1
	add.w	(a0),d0
loc_01F2B4:
	movem.l	(sp)+,a0/a1
	move.l	(sp)+,(sp)
	rts
loc_01F2BC:
	clr.w	d0
	clr.w	d1
	bra.s	loc_01F2B4


; ----------------------------------------------------------------------
; called from $024896
sub_01F2C2:
	movem.l	a0/a1,-(sp)
	movea.l	$C(sp),a0
	clr.w	d0
	clr.w	d1
	tst.w	$6(a0)
	ble.w	loc_01F32C
	movea.l	#dat_169DDE,a1
	move.w	$6(a0),d0
	move.w	(a1)+,d1
	subq.w	#1,d1
	sub.w	d1,d0
	bmi.w	loc_01F334
	asl.w	#2,d0
	add.w	$6(a0),d0
	add.w	$6(a0),d0
	move.b	$3(a1,d0.w),d1
	ext.w	d1
	move.b	$2(a1,d0.w),d0
	ext.w	d0
	btst	#3,$4(a0)
	beq.w	loc_01F30C
	neg.w	d0
loc_01F30C:
	btst	#4,$4(a0)
	bne.w	loc_01F318
	neg.w	d1
loc_01F318:
	btst	#7,(ram_C33C).w
	beq.w	loc_01F326
	exg	d0,d1
	neg.w	d1
loc_01F326:
	add.w	$14(a0),d1
	add.w	(a0),d0
loc_01F32C:
	movem.l	(sp)+,a0/a1
	move.l	(sp)+,(sp)
	rts
loc_01F334:
	clr.w	d0
	clr.w	d1
	bra.s	loc_01F32C


; ----------------------------------------------------------------------
; called from $0248B0
sub_01F33A:
	movem.l	a0/a1,-(sp)
	movea.l	$C(sp),a0
	clr.w	d0
	clr.w	d1
	tst.w	$6(a0)
	ble.w	loc_01F3A4
	movea.l	#dat_169DDE,a1
	move.w	$6(a0),d0
	move.w	(a1)+,d1
	subq.w	#1,d1
	sub.w	d1,d0
	bmi.w	loc_01F3AC
	asl.w	#2,d0
	add.w	$6(a0),d0
	add.w	$6(a0),d0
	move.b	$5(a1,d0.w),d1
	ext.w	d1
	move.b	$4(a1,d0.w),d0
	ext.w	d0
	btst	#3,$4(a0)
	beq.w	loc_01F384
	neg.w	d0
loc_01F384:
	btst	#4,$4(a0)
	bne.w	loc_01F390
	neg.w	d1
loc_01F390:
	btst	#7,(ram_C33C).w
	beq.w	loc_01F39E
	exg	d0,d1
	neg.w	d1
loc_01F39E:
	add.w	$14(a0),d1
	add.w	(a0),d0
loc_01F3A4:
	movem.l	(sp)+,a0/a1
	move.l	(sp)+,(sp)
	rts
loc_01F3AC:
	clr.w	d0
	clr.w	d1
	bra.s	loc_01F3A4


; ----------------------------------------------------------------------
; called from $00BEC0, $00BECA, $00BF70, $00C61E, $00CD4C, $00D0DA, $00D5FC, $00D9B2 (+92 more)
sub_01F3B2:
	cmp.w	$58(a3),d1
	beq.w	NullSub
	clr.w	$5A(a3)
	move.w	d1,$58(a3)
	st	$5C(a3)
	rts
loc_01F3C8:
	tst.w	$34(a3)
	beq.w	loc_01F880
	cmpi.w	#$3B1E,$58(a3)
	beq.w	loc_01F3E4
	cmpi.w	#$3B50,$58(a3)
	bne.w	loc_01F3F4
loc_01F3E4:
	cmpi.w	#$C,$5A(a3)
	blt.w	loc_01F418
	jmp	(loc_01B434).l
loc_01F3F4:
	cmpi.w	#$3ABA,$58(a3)
	beq.w	loc_01F408
	cmpi.w	#$3AEC,$58(a3)
	bne.w	loc_01F43A
loc_01F408:
	cmpi.w	#$C,$5A(a3)
	blt.w	loc_01F418
	jmp	(loc_01B434).l
loc_01F418:
	move.w	$2A(a3),d1
	asr.w	#3,d1
	sub.w	d1,$2A(a3)
	tst.w	$28(a3)
	bpl.w	loc_01F432
	move.w	#$EB00,$28(a3)
	rts
loc_01F432:
	move.w	#$1500,$28(a3)
	rts
loc_01F43A:
	btst	#1,$63(a3)
	beq.w	loc_01F676
	cmpi.w	#$3E22,$58(a3)
	beq.w	loc_01F4F2
	cmpi.w	#$3EB4,$58(a3)
	beq.w	loc_01F4F2
	cmpi.w	#$3F46,$58(a3)
	beq.w	loc_01F4C0
	cmpi.w	#$3FB8,$58(a3)
	beq.w	loc_01F4C0
	cmpi.w	#$3C98,$58(a3)
	beq.w	loc_01F4F8
	cmpi.w	#$3C34,$58(a3)
	beq.w	loc_01F4F8
	cmpi.w	#$3CCA,$58(a3)
	beq.w	loc_01F4F8
	cmpi.w	#$3C66,$58(a3)
	beq.w	loc_01F4F8
	cmpi.w	#$39B6,$58(a3)
	beq.w	loc_01F53C
	cmpi.w	#$E9C,$58(a3)
	beq.w	loc_01F512
	cmpi.w	#$3D3E,$58(a3)
	beq.w	loc_01F60A
	cmpi.w	#$3DB0,$58(a3)
	beq.w	loc_01F630
	bra.w	loc_01F676
loc_01F4C0:
	movem.w	d1,-(sp)
	cmpi.w	#$8,$5A(a3)
	blt.w	loc_01F4E6
	move.w	#$3E22,d1
	cmpi.w	#$3F46,$58(a3)
	beq.w	loc_01F4E0
	move.w	#$3EB4,d1
loc_01F4E0:
	jsr	(sub_01F3B2).l
loc_01F4E6:
	jsr	(sub_00DCA8).l
	movem.w	(sp)+,d1
	rts
loc_01F4F2:
	jmp	(sub_00DCA8).l
loc_01F4F8:
	cmpi.w	#$C,$5A(a3)
	blt.w	loc_01F608
	cmp.w	#$8,d0	; general form
	bge.w	loc_01F608
	bclr	#1,$63(a3)
	rts
loc_01F512:
	cmpi.w	#$0,$5A(a3)
	bne.w	loc_01F532
	move.w	$28(a3),d0
	asr.w	#1,d0
	move.w	d0,$28(a3)
	move.w	$2A(a3),d0
	asr.w	#1,d0
	move.w	d0,$2A(a3)
	rts
loc_01F532:
	clr.w	$28(a3)
	clr.w	$2A(a3)
	rts
loc_01F53C:
	cmpi.w	#$0,$5A(a3)
	bne.w	loc_01F55C
	move.w	$28(a3),d1
	asr.w	#1,d1
	move.w	d1,$28(a3)
	move.w	$2A(a3),d1
	asr.w	#1,d1
	move.w	d1,$2A(a3)
	rts
loc_01F55C:
	cmpi.w	#$C,$5A(a3)
	bgt.w	loc_01F590
	move.w	$54(a3),d1
	andi.w	#$7,d1
	movem.l	d0/a0,-(sp)
	movea.l	#dat_01F656,a0
	asl.w	#2,d1
	move.w	$0(a0,d1.w),d0
	add.w	d0,$28(a3)
	move.w	$2(a0,d1.w),d0
	add.w	d0,$2A(a3)
	movem.l	(sp)+,d0/a0
	rts
loc_01F590:
	cmpi.w	#$10,$5A(a3)
	blt.w	loc_01F608
	move.w	$54(a3),d1
	addq.w	#4,d1
	andi.w	#$7,d1
	move.w	d1,$54(a3)
	move.w	#$75E,d1
	jmp	(sub_01F3B2).l

	dc.w	$0C6B,$0014,$005A,$6D00,$00BC,$0C6B,$0020,$005A
	dc.w	$6C00,$0016,$322B,$0028,$E241,$3741,$0028,$322B
	dc.w	$002A,$E241,$3741,$002A,$0C6B,$000C,$005A,$6600
	dc.w	$0026,$322B,$0054,$0241,$0007,$48E7,$0080,$207C
	dc.w	$0001,$F656,$E541,$3770,$1000,$0028,$3770,$1002
	dc.w	$002A,$4CDF,$0100
loc_01F608:
	rts
loc_01F60A:
	cmpi.w	#$8,$5A(a3)
	bne.s	loc_01F608
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.s	loc_01F608
	move.w	#$1F,(ram_BF12).l
	move.w	#$8,(ram_BF10).w
	jmp	(sub_012FA2).l
loc_01F630:
	cmpi.w	#$8,$5A(a3)
	bne.s	loc_01F608
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.s	loc_01F608
	move.w	#$1F,(ram_BF12).l
	move.w	#$8,(ram_BF10).w
	jmp	(sub_012FA2).l
dat_01F656:
	dc.w	$0000,$FF00,$FF80,$FF80,$FF00,$0000,$FF80,$0080
	dc.w	$0000,$0100,$0080,$0080,$0100,$0000,$0080,$FF80
loc_01F676:
	move.w	(ram_B7C0).w,d1
	cmp.w	$52(a3),d1
	bne.w	loc_01F68A
	move.w	#$870,d1
	bra.w	loc_01F69C
loc_01F68A:
	move.w	#$870,d1
	btst	#4,$62(a3)
	beq.w	loc_01F69C
	move.w	#$870,d1
loc_01F69C:
	andi.w	#$F,d0
	cmp.w	#$7,d0	; general form
	ble.w	loc_01F6C8
	cmp.w	#$9,d0	; general form
	bne.w	loc_01F6BC
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	bne.w	loc_01FDBC
loc_01F6BC:
	btst	#1,$63(a3)
	beq.w	sub_01F3B2
	rts
loc_01F6C8:
	movem.w	d0/d1,-(sp)
	move.w	d0,d2
	move.w	$52(a3),d0
	cmp.w	(ram_B7C0).w,d0
	beq.w	loc_01F7D0
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	move.w	$14(a3),d3
	move.b	(ram_B78A).w,d1
	ext.w	d1
	add.w	(ram_B774).w,d1
	sub.w	d3,d1
	btst	#7,$62(a3)
	bne.w	loc_01F704
	neg.w	d0
	neg.w	d1
	neg.w	d3
	eori.w	#$4,d2
loc_01F704:
	btst	#4,$62(a3)
	bne.w	loc_01F73C
	tst.w	d3
	bpl.w	loc_01F7D0
	cmp.w	#$4,d2	; general form
	bne.w	loc_01F7D0
	bsr.w	sub_01F186
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bhi.w	loc_01F7D0
	btst	#7,(ram_C350).w
	bne.w	loc_01F7D0
	bra.w	loc_01F75C
loc_01F73C:
	subq.w	#3,d2
	andi.w	#$7,d2
	cmp.w	#$2,d2	; general form
	bhi.w	loc_01F798
	bsr.w	sub_01F186
	addq.w	#2,d0
	andi.w	#$7,d0
	cmp.w	#$4,d0	; general form
	bhi.w	loc_01F798
loc_01F75C:
	btst	#4,$62(a3)
	bne.w	loc_01F7D6
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	beq.w	loc_01F78E
	move.w	$28(a3),d0
	move.w	$2A(a3),d1
	bsr.w	sub_01F186
	sub.w	(sp),d0
	addq.w	#1,d0
	andi.w	#$7,d0
	cmp.w	#$2,d0	; general form
	bhi.w	loc_01F7D6
loc_01F78E:
	bset	#4,$62(a3)
	bra.w	loc_01F7D6
loc_01F798:
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	move.w	(ram_B774).w,d1
	sub.w	(a3),d0
	sub.w	$14(a3),d1
	bsr.w	sub_01F186
	sub.w	$54(a3),d0
	beq.w	loc_01F7CC
	neg.w	d0
	andi.w	#$4,d0
	lsr.w	#1,d0
	subq.w	#1,d0
	add.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,$54(a3)
loc_01F7CC:
	movem.w	(sp)+,d0/d1
loc_01F7D0:
	bclr	#4,$62(a3)
loc_01F7D6:
	movem.w	(sp)+,d0/d1
	move.w	$54(a3),d2
	sub.w	d2,d0
	andi.w	#$7,d0
	movea.l	#dat_01F870,a0
	asl.w	#1,d0
	tst.w	$0(a0,d0.w)
	beq.w	loc_01FADA
	move.w	$28(a3),d4
	muls.w	d4,d4
	move.w	$2A(a3),d3
	muls.w	d3,d3
	add.l	d4,d3
	swap	d3
	move.w	#$300,d4
	sub.w	d3,d4
	cmp.w	#$180,d4	; general form
	bge.w	loc_01F816
	move.w	#$180,d4
loc_01F816:
	muls.w	$0(a0,d0.w),d4
	btst	#4,$62(a3)
	beq.w	loc_01F826
	neg.l	d4
loc_01F826:
	add.l	d4,$54(a3)
	andi.w	#$7,$54(a3)
	move.w	$54(a3),d2
	cmp.w	#$14,d3	; general form
	bls.w	loc_01F862
	clr.w	d1
	tst.w	$0(a0,d0.w)
	bpl.w	loc_01F84A
	eori.w	#$FFCE,d1
loc_01F84A:
	btst	#3,$4(a3)
	beq.w	loc_01F858
	eori.w	#$FFCE,d1
loc_01F858:
	addi.w	#$2110,d1
	bset	#1,$63(a3)
loc_01F862:
	bsr.w	sub_01F3B2
	cmp.w	#$2,d3	; general form
	bhi.w	loc_01FB98
	rts
dat_01F870:
	dc.w	$0000,$0010,$0010,$0010,$0000,$FFF0,$FFF0,$FFF0
loc_01F880:
	btst	#3,$62(a3)
	beq.w	loc_01FA12
	movem.w	d0,-(sp)
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	movem.w	(sp)+,d0
	beq.w	loc_01FA12
	jsr	(sub_029F64).l
	bne.w	loc_01FA12
	movem.w	d0/d1,-(sp)
	move.w	(ram_B760).w,d0
	sub.w	(a3),d0
	move.w	(ram_B774).w,d1
	cmp.w	#$11E,d1	; general form
	bgt.w	loc_01F8C6
	cmp.w	#$FEE2,d1	; general form
	bgt.w	loc_01F8E8
loc_01F8C6:
	cmpi.w	#$11E,$14(a3)
	bgt.w	loc_01F8E8
	cmpi.w	#$FEE2,$14(a3)
	blt.w	loc_01F8E8
	move.w	#$11E,d1
	tst.w	(ram_B774).w
	bpl.w	loc_01F8E8
	neg.w	d1
loc_01F8E8:
	sub.w	$14(a3),d1
	cmp.w	#$10,d0	; general form
	bgt.w	loc_01F914
	cmp.w	#$FFF0,d0	; general form
	blt.w	loc_01F914
	cmp.w	#$10,d1	; general form
	bgt.w	loc_01F914
	cmp.w	#$FFF0,d1	; general form
	blt.w	loc_01F914
	move.w	$54(a3),d0
	bra.w	loc_01F918
loc_01F914:
	bsr.w	sub_01F186
loc_01F918:
	btst	#0,(ram_C344).w
	bne.w	loc_01F92E
	bsr.w	sub_01C8CA
	movem.w	(sp)+,d0/d1
	bra.w	loc_01F946
loc_01F92E:
	movem.w	(sp)+,d0/d1
	cmp.w	#$8,d0	; general form
	beq.w	loc_01F946
	movem.w	d0/d1,-(sp)
	bsr.w	sub_01C8CA
	movem.w	(sp)+,d0/d1
loc_01F946:
	move.w	#$72C,d1
	btst	#1,$63(a3)
	bne.w	loc_01FAAA
	bsr.w	sub_01F3B2
	cmp.w	#$8,d0	; general form
	bne.w	loc_01F9B2
	tst.w	$34(a3)
	bne.w	loc_01F9B2
	btst	#3,$62(a3)
	beq.w	loc_01F9B2
	move.w	d0,-(sp)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_01F984
	neg.w	d0
loc_01F984:
	cmp.w	#$D8,d0	; general form
	blt.w	loc_01F9AA
	move.w	(a3),d0
	cmp.w	#$20,d0	; general form
	bgt.w	loc_01F9AA
	cmp.w	#$FFE0,d0	; general form
	blt.w	loc_01F9AA
	move.w	(sp)+,d0
	jsr	(sub_1CF56C).l
	bra.w	loc_01F9B2
loc_01F9AA:
	jsr	(sub_1CF56C).l
	move.w	(sp)+,d0
loc_01F9B2:
	move.w	d0,d2
	jsr	(sub_029F64).l
	bne.w	loc_01FA0E
	btst	#7,$62(a3)
	bne.w	loc_01F9EA
	cmpi.w	#$11E,$14(a3)
	blt.w	sub_01FBA6
	tst.w	d2
	beq.w	loc_01FA0C
	cmp.w	#$1,d2	; general form
	beq.w	loc_01FA0C
	cmp.w	#$7,d2	; general form
	bne.w	sub_01FBA6
	rts
loc_01F9EA:
	cmpi.w	#$FEE2,$14(a3)
	bgt.w	sub_01FBA6
	cmp.w	#$4,d2	; general form
	beq.w	loc_01FA0C
	cmp.w	#$3,d2	; general form
	beq.w	loc_01FA0C
	cmp.w	#$5,d2	; general form
	bne.w	sub_01FBA6
loc_01FA0C:
	rts
loc_01FA0E:
	bra.w	sub_01FBA6
loc_01FA12:
	move.w	#$72C,d1
	btst	#3,$62(a3)
	beq.w	loc_01FA7A
	btst	#2,$64(a3)
	bne.w	loc_01FAA0
	cmp.w	#$8,d0	; general form
	bne.w	loc_01FA76
	tst.w	$34(a3)
	bne.w	loc_01FAA0
	move.w	d0,-(sp)
	move.w	$14(a3),d0
	btst	#7,$62(a3)
	beq.w	loc_01FA4C
	neg.w	d0
loc_01FA4C:
	cmp.w	#$D8,d0	; general form
	blt.w	loc_01FA70
	move.w	(a3),d0
	cmp.w	#$20,d0	; general form
	bgt.w	loc_01FA70
	cmp.w	#$FFE0,d0	; general form
	blt.w	loc_01FA70
	move.w	(sp)+,d0
	bsr.w	sub_01FE66
	bra.w	loc_01FAA0
loc_01FA70:
	move.w	(sp)+,d0
	bra.w	loc_01FAA0
loc_01FA76:
	bra.w	loc_01FAAC
loc_01FA7A:
	andi.w	#$F,d0
	cmp.w	#$7,d0	; general form
	ble.w	loc_01FAAC
	cmp.w	#$9,d0	; general form
	bne.w	loc_01FAA0
	move.w	$28(a3),d0
	or.w	$2A(a3),d0
	beq.w	loc_01FAA0
	jmp	(sub_1CF56C).l
loc_01FAA0:
	btst	#1,$63(a3)
	beq.w	sub_01F3B2
loc_01FAAA:
	rts
loc_01FAAC:
	sub.w	$54(a3),d0
	beq.w	loc_01FACA
	neg.w	d0
	andi.w	#$4,d0
	lsr.w	#1,d0
	subq.w	#1,d0
	add.w	$54(a3),d0
	andi.w	#$7,d0
	move.w	d0,$54(a3)
loc_01FACA:
	move.w	#$65A,d1
	bsr.w	sub_01F3B2
	move.w	$54(a3),d2
	bra.w	sub_01FBA6
loc_01FADA:
	moveq	#$2,d4
	btst	#4,$62(a3)
	beq.w	loc_01FAEC
	addq.w	#4,d4
	eori.w	#$8,d0
loc_01FAEC:
	tst.w	d0
	beq.w	loc_01FB5A
	move.w	$28(a3),d0
	move.w	$2A(a3),d1
	bsr.w	sub_01F186
	btst	#3,d0
	bne.w	loc_01FB18
	sub.w	$54(a3),d0
	add.w	d4,d0
	andi.w	#$7,d0
	cmp.w	#$4,d0	; general form
	blt.w	loc_01FDBC
loc_01FB18:
	addq.w	#1,$54(a3)
	btst	#3,$4(a3)
	beq.w	loc_01FB2A
	subq.w	#2,$54(a3)
loc_01FB2A:
	andi.w	#$7,$54(a3)
	move.w	(ram_B7C0).w,d1
	cmp.w	$52(a3),d1
	bne.w	loc_01FB44
	move.w	#$870,d1
	bra.w	loc_01FB56
loc_01FB44:
	move.w	#$870,d1
	btst	#4,$62(a3)
	beq.w	sub_01F3B2
	move.w	#$870,d1
loc_01FB56:
	bra.w	sub_01F3B2
loc_01FB5A:
	move.w	#$8A2,d1
	btst	#4,$62(a3)
	bne.w	loc_01FB8A
	move.w	#$2A10,d1
	btst	#6,$63(a3)
	beq.w	loc_01FB7A
	move.w	#$12C6,d1
loc_01FB7A:
	move.w	(ram_B7C0).w,d4
	cmp.w	$52(a3),d4
	bne.w	loc_01FB8A
	move.w	#$75E,d1
loc_01FB8A:
	btst	#1,$63(a3)
	bne.w	loc_01FB98
	bsr.w	sub_01F3B2
loc_01FB98:
	btst	#4,$62(a3)
	beq.w	sub_01FBA6
	eori.w	#$4,d2

; ----------------------------------------------------------------------
; called from $00F470, $01BEA0, $01C814, $01F9CE, $01F9E4, $01F9F0, $01FA08, $01FA0E (+2 more)
sub_01FBA6:
	asl.w	#2,d2
	lea	dat_01FEB0(pc),a0
	cmpi.w	#$2110,$58(a3)
	beq.w	loc_01FBC0
	cmpi.w	#$20DE,$58(a3)
	bne.w	loc_01FBDC
loc_01FBC0:
	lea	dat_01FED4(pc),a0
	move.w	$28(a3),d0
	move.w	#$4,d1
	asr.w	d1,d0
	sub.w	d0,$28(a3)
	move.w	$2A(a3),d0
	asr.w	d1,d0
	sub.w	d0,$2A(a3)
loc_01FBDC:
	move.w	$2(a0,d2.w),d1
	move.w	$0(a0,d2.w),d0
	move.w	$50(a3),d2
	beq.w	loc_01FBF4
	eor.w	d0,d2
	bpl.w	loc_01FBF4
	clr.w	d0
loc_01FBF4:
	move.w	$4E(a3),d2
	beq.w	loc_01FC04
	eor.w	d1,d2
	bmi.w	loc_01FC04
	clr.w	d1
loc_01FC04:
	clr.w	d2
	move.b	$68(a3),d2
	lsr.w	#2,d2
	neg.w	d2
	addi.w	#$40,d2
	add.b	$69(a3),d2
	addq.b	#2,d2
	tst.w	$34(a3)
	bne.w	loc_01FC28
	add.b	$69(a3),d2
	addi.w	#$10,d2
loc_01FC28:
	asr.w	#1,d2
	muls.w	d2,d0
	muls.w	d2,d1
	asr.l	#5,d0
	asr.l	#5,d1
	muls.w	d7,d0
	muls.w	d7,d1
	tst.w	$34(a3)
	bne.w	loc_01FC58
	btst	#3,$62(a3)
	beq.w	loc_01FC58
	move.w	(ram_B7C0).w,d2
	cmp.w	$52(a3),d2
	bne.w	loc_01FC58
	asr.w	#1,d0
	asr.w	#1,d1
loc_01FC58:
	add.w	$28(a3),d0
	add.w	$2A(a3),d1
	move.w	d0,d2
	move.w	d1,d3
	muls.w	d2,d2
	muls.w	d3,d3
	add.l	d2,d3
	movem.w	d0/d1,-(sp)
	bsr.w	sub_0250F4
	btst	#4,(ram_C34C).w
	beq.w	loc_01FC80
	move.w	#$1000,d0
loc_01FC80:
	clr.w	d2
	move.b	$6A(a3),d2
	movem.l	a0,-(sp)
	lea	$36(a3),a0
	adda.w	(a0),a0
	addq.w	#2,a0
	cmpi.b	#$2,(a0)
	movem.l	(sp)+,a0
	bne.w	loc_01FCA0
	addq.b	#6,d2
loc_01FCA0:
	addq.b	#2,d2
	cmp.b	#$1E,d2	; general form
	ble.w	loc_01FCAE
	move.b	#$1E,d2
loc_01FCAE:
	move.w	d2,(ram_BF4C).w
	lsr.w	#1,d2
	mulu.w	d0,d2
	asl.l	#4,d2
	swap	d2
	asl.w	#2,d2
	andi.w	#$3F,d2
	lea	dat_01FD7C(pc),a2
	move.w	d2,(ram_BF52).w
	move.l	$0(a2,d2.w),d2
	move.l	d2,(ram_BF4E).w
	cmpi.w	#$3C,(ram_BF52).w
	bge.w	loc_01FCF8
	btst	#0,(ram_BF4D).w
	beq.w	loc_01FCF8
	move.w	(ram_BF52).w,d2
	addq.w	#4,d2
	move.l	$0(a2,d2.w),d2
	sub.l	(ram_BF4E).w,d2
	asr.l	#1,d2
	add.l	(ram_BF4E).w,d2
loc_01FCF8:
	btst	#6,$63(a3)
	beq.w	loc_01FD04
	lsr.l	#3,d2
loc_01FD04:
	tst.w	$34(a3)
	bne.w	loc_01FD1A
	move.w	(ram_B7C0).w,d0
	cmp.w	$52(a3),d0
	bne.w	loc_01FD1A
	asr.l	#1,d2
loc_01FD1A:
	movem.w	(sp)+,d0/d1
	cmp.l	d2,d3
	bhi.w	loc_01FD2C
	move.w	d0,$28(a3)
	move.w	d1,$2A(a3)
loc_01FD2C:
	tst.w	(ram_D280).w
	bne.w	NullSub
	move.w	(VDP_HVCOUNTER).l,d0
	andi.w	#$7F,d0
	bne.w	NullSub
	bsr.w	sub_0250F4
	subi.w	#$1E,d0
	cmp.w	#$C00,d0	; general form
	blt.w	sub_025114
	move.b	$73(a3),d2
	ext.w	d2
	lsr.w	#1,d2
	add.w	d2,d0
	bsr.w	sub_025114
	btst	#0,$73(a3)
	beq.w	loc_01FD7A
	btst	#0,(ram_B055).w
	beq.w	loc_01FD7A
	addq.w	#1,d0
	bra.w	sub_025114
loc_01FD7A:
	rts
dat_01FD7C:
	dc.w	$01CD,$9410,$01FC,$E3E1,$022E,$8284,$0262,$6FF9
	dc.w	$0298,$AC40,$02D1,$3759,$030C,$1144,$0349,$3A01
	dc.w	$0388,$B190,$03CA,$77F1,$040E,$8D24,$0454,$F129
	dc.w	$049D,$A400,$04E8,$A5A9,$0535,$F624,$0585,$9571
loc_01FDBC:
	btst	#3,$62(a3)
	beq.w	loc_01FDF2
	cmpi.w	#$1000,$28(a3)
	bgt.w	loc_01FE28
	cmpi.w	#$F000,$28(a3)
	blt.w	loc_01FE28
	cmpi.w	#$1000,$2A(a3)
	bgt.w	loc_01FE28
	cmpi.w	#$F000,$2A(a3)
	blt.w	loc_01FE28
	bra.w	loc_01FE1A
loc_01FDF2:
	cmpi.w	#$2000,$28(a3)
	bgt.w	loc_01FE28
	cmpi.w	#$E000,$28(a3)
	blt.w	loc_01FE28
	cmpi.w	#$2000,$2A(a3)
	bgt.w	loc_01FE28
	cmpi.w	#$E000,$2A(a3)
	blt.w	loc_01FE28
loc_01FE1A:
	tst.w	$34(a3)
	bne.w	sub_01FE66
	jmp	(sub_1CF56C).l
loc_01FE28:
	move.w	(ram_B7C0).w,d1
	cmp.w	$52(a3),d1
	bne.w	loc_01FE3C
	move.w	#$870,d1
	bra.w	loc_01FE40
loc_01FE3C:
	move.w	#$870,d1
loc_01FE40:
	btst	#4,$62(a3)
	bne.w	loc_01FE54
	bset	#1,$63(a3)
	move.w	#$28D8,d1
loc_01FE54:
	bsr.w	sub_01F3B2
	tst.w	$34(a3)
	bne.w	sub_01FE66
	jmp	(sub_1CF56C).l


; ----------------------------------------------------------------------
; called from $01C818, $01FA68, $01FE1E, $01FE5C
sub_01FE66:
	tst.w	$28(a3)
	bpl.w	loc_01FE7C
	addi.w	#$B4,$28(a3)
	bmi.w	loc_01FE8A
	clr.w	$28(a3)
loc_01FE7C:
	subi.w	#$B4,$28(a3)
	bpl.w	loc_01FE8A
	clr.w	$28(a3)
loc_01FE8A:
	tst.w	$2A(a3)
	bpl.w	loc_01FEA0
	addi.w	#$B4,$2A(a3)
	bmi.w	NullSub
	clr.w	$2A(a3)
loc_01FEA0:
	subi.w	#$B4,$2A(a3)
	bpl.w	NullSub
	clr.w	$2A(a3)
	rts
dat_01FEB0:
	dc.w	$0000,$00C8,$008D,$008D,$00C8,$0000,$008D,$FF73
	dc.w	$0000,$FF38,$FF73,$FF73,$FF38,$0000,$FF73,$008D
	dc.w	$0000,$0000
dat_01FED4:
	dc.w	$0000,$01C2,$013E,$013E,$01C2,$0000,$013E,$FEC2
	dc.w	$0000,$FE3E,$FEC2,$FEC2,$FE3E,$0000,$FEC2,$013E
	dc.w	$0000,$0000,$48E7,$E0C0,$327C,$D24C,$4242,$6000
	dc.w	$0016


; ----------------------------------------------------------------------
; called from $01FF1A
sub_01FF06:
	move.b	(a0)+,d1
	bchg	#0,d2
	bne.w	loc_01FF14
	subq.w	#1,a0
	lsr.w	#4,d1
loc_01FF14:
	andi.w	#$F,d1
	move.w	d1,(a1)+
	dbra	d0,sub_01FF06
	movem.l	(sp)+,d0-d2/a0/a1
	rts
