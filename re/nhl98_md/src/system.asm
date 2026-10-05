; ============================================================================
; System library: VDP, DMA, palettes, text rendering, joypads, random numbers
; ROM range $01FF24-$022A81
; ============================================================================

loc_01FF24:
	movem.l	d1/a1,-(sp)
	movea.w	#$D24C,a1
	clr.w	d1
	bra.w	loc_01FF34
loc_01FF32:
	add.w	(a1)+,d1
loc_01FF34:
	dbra	d0,loc_01FF32
	move.w	d1,d0
	bsr.w	Random
loc_01FF3E:
	sub.w	-(a1),d0
	bpl.s	loc_01FF3E
	suba.w	#$D24C,a1
	move.w	a1,d0
	lsr.w	#1,d0
	movem.l	(sp)+,d1/a1
	rts
loc_01FF50:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d4/a0-a2,-(sp)
	exg	d1,d0
	movea.l	a0,a2
	bsr.w	VDP_SetWriteAddr
	subq.w	#1,d1
loc_01FF68:
	moveq	#$3,d0
	move.w	(a2)+,d2
	clr.w	d3
loc_01FF6E:
	move.w	d2,d4
	andi.w	#$F,d4
	lsr.w	#1,d4
	move.b	$0(a1,d4.w),d4
	btst	#0,d2
	bne.w	loc_01FF84
	lsr.w	#4,d4
loc_01FF84:
	andi.w	#$F,d4
	or.b	d4,d3
	ror.w	#4,d3
	ror.w	#4,d2
	dbra	d0,loc_01FF6E
	move.w	d3,(a0)
	dbra	d1,loc_01FF68
	movem.l	(sp)+,d0-d4/a0-a2
	move.w	(sp)+,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $00C10E, $00C360, $01973E, $01982E, $01A2FE, $01A6FE, $01E05C, $0226F6 (+11 more)
sub_01FFA2:
	movem.l	d0/a0,-(sp)
	movea.w	#$BD40,a0
	moveq	#$1F,d0
loc_01FFAC:
	move.l	(a0),-(sp)
	clr.l	(a0)+
	dbra	d0,loc_01FFAC
	move.w	#$18,(FadeCounter).w
	bsr.w	Palette_WaitFade
	moveq	#$1F,d0
loc_01FFC0:
	move.l	(sp)+,-(a0)
	dbra	d0,loc_01FFC0
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
; called from $01A90A
sub_01FFCC:
	movem.l	d0/a0,-(sp)
	movea.w	#$BD40,a0
	moveq	#$1F,d0
loc_01FFD6:
	move.l	(a0),-(sp)
	clr.l	(a0)+
	dbra	d0,loc_01FFD6
	move.w	#$64,(FadeCounter).w
	bsr.w	Palette_WaitFade
	moveq	#$1F,d0
loc_01FFEA:
	move.l	(sp)+,-(a0)
	dbra	d0,loc_01FFEA
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
; installs VBlank_Simple and waits until the fade finished
; called from $01FFBA, $01FFE4, $0205E0
Palette_WaitFade:
	move.w	sr,-(sp)
	move.l	(VBlankVector).w,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bclr	#2,(VideoFlags).w
	move.l	#VBlank_Simple,(VBlankVector).l
	move.w	#$2500,sr
loc_020014:
	tst.w	(FadeCounter).w
	bpl.s	loc_020014
	move.w	(sp)+,(VideoFlags).w
	move.l	(sp)+,(VBlankVector).w
	move.w	(sp)+,sr
	rts


; ----------------------------------------------------------------------
; called every VBlank while ram_FadeCounter >= 0: steps CRAM towards ram_PaletteBuffer
; called from $0172AC, $0257CA, $0258AE, $0271BC, $1DD72A, $1E2506, $1E43AE, $1E4610
Palette_FadeStep:
	tst.w	(FadeCounter).w
	bmi.w	NullSub
	cmpi.w	#$64,(FadeCounter).w
	beq.w	Palette_LoadImmediate
	subq.w	#1,(FadeCounter).w
	bmi.w	NullSub
	clr.l	d0
	move.w	(FadeCounter).w,d0
	cmp.w	#$18,d0	; general form
	bgt.w	NullSub
	divu.w	#$3,d0
	swap	d0
	asl.w	#2,d0
	moveq	#$2,d3
	asl.w	d0,d3
	moveq	#$E,d5
	asl.w	d0,d5
	move.w	d5,d4
	not.w	d4
	movea.l	#PaletteBuffer,a1
	movea.l	#VDP_DATA,a0
	clr.w	d6
loc_020070:
	move.w	d3,d2
	move.w	d6,d0
	swap	d0
	move.w	#$20,d0
	move.l	d0,$4(a0)
	move.w	(a0),d7
	move.w	d7,d0
	and.w	d5,d0
	move.w	(a1)+,d1
	and.w	d5,d1
	cmp.w	d1,d0
	beq.w	loc_0200AA
	blt.w	loc_020094
	neg.w	d2
loc_020094:
	add.w	d2,d0
	and.w	d4,d7
	or.w	d0,d7
	move.l	#$C000,d0
	move.b	d6,d0
	swap	d0
	move.l	d0,$4(a0)
	move.w	d7,(a0)
loc_0200AA:
	addq.w	#2,d6
	cmp.w	#$80,d6	; general form
	bne.s	loc_020070
	rts


; ----------------------------------------------------------------------
; called from $020034, $0270E4
Palette_LoadImmediate:
	movem.l	d0/a0/a1,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movea.w	#$BD40,a1
	movea.l	#VDP_DATA,a0
	move.l	#$C0000000,$4(a0)
	moveq	#$1F,d0
loc_0200D6:
	move.l	(a1)+,(a0)
	dbra	d0,loc_0200D6
	st	(FadeCounter).w
	move.w	(sp)+,(VideoFlags).w
	movem.l	(sp)+,d0/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $00FA1A, $00FA2C, $00FD6A, $00FFB2, $00FFC4, $010198, $011826, $011838 (+10 more)
sub_0200EA:
	move.w	d0,-(sp)
	asl.w	#1,d0
	bsr.w	Random
	sub.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; d0 = random number below the word pushed on the stack (seed in ram_RandomSeed)
; called from $00BF5A, $00C68A, $00C98E, $00C9CA, $00CA1C, $00EB5A, $00EB66, $00EB80 (+66 more)
Random:
	movem.l	d0-d2,-(sp)
	move.w	(ram_D298).w,d0
	move.w	d0,d1
	move.w	(RandomSeed).w,d2
	mulu.w	#$E62D,d0
	mulu.w	#$BB40,d1
	mulu.w	#$E62D,d2
	add.w	d2,d1
	swap	d0
	add.w	d1,d0
	swap	d0
	addq.l	#1,d0
	move.l	d0,(RandomSeed).w
	asr.l	#8,d0
	mulu.w	$2(sp),d0
	swap	d0
	addq.w	#4,sp
	movem.l	(sp)+,d1/d2
	rts


; ----------------------------------------------------------------------
; d0 = integer square root of d0
; called from $00D1E4, $00F2C6, $012D72, $0130C6, $013662, $01C6D4, $023B26, $024132 (+6 more)
ISqrt:
	tst.l	d0
	beq.w	NullSub
	cmp.l	#$640,d0	; general form
	bhi.w	loc_020150
	move.l	d1,-(sp)
	moveq	#-$1,d1
loc_020142:
	addq.w	#2,d1
	sub.w	d1,d0
	bcc.s	loc_020142
	lsr.w	#1,d1
	move.w	d1,d0
	move.l	(sp)+,d1
	rts
loc_020150:
	movem.l	d1-d4,-(sp)
	moveq	#$9,d3
	move.w	#$8000,d1
	cmp.l	#$F00000,d0	; general form
	bhi.w	loc_020182
	move.l	d0,d1
	lsr.l	#8,d1
	addq.w	#2,d1
loc_02016A:
	move.w	d1,d2
	move.l	d0,d1
	divu.w	d2,d1
	add.w	d2,d1
	lsr.w	#1,d1
	cmp.w	d1,d2
	dbeq	d3,loc_02016A
loc_02017A:
	move.w	d1,d0
	movem.l	(sp)+,d1-d4
	rts
loc_020182:
	moveq	#$0,d1
	moveq	#-$1,d2
loc_020186:
	move.w	d1,d3
	add.w	d2,d3
	roxr.w	#1,d3
	cmp.w	d3,d1
	beq.s	loc_02017A
	move.w	d3,d4
	mulu.w	d3,d3
	cmp.l	d3,d0
	bcc.w	loc_02019E
	move.w	d4,d2
	bra.s	loc_020186
loc_02019E:
	move.w	d4,d1
	bra.s	loc_020186


; ----------------------------------------------------------------------
; called from $01A022, $027134, $1D1C6A
sub_0201A2:
	clr.w	(ram_DCE6).w
	neg.w	d0
	move.w	d0,(FrameCounter).w
loc_0201AC:
	bsr.w	Joypad_Read1
	move.w	d3,(ram_DCE6).w
	tst.w	d1
	bne.w	NullSub
	bsr.w	Joypad_Read2
	or.w	d3,(ram_DCE6).w
	tst.w	d1
	bne.w	NullSub
	tst.w	(FourWayPlay).w
	beq.w	loc_0201EC
	bsr.w	Joypad_Read3
	or.w	d3,(ram_DCE6).w
	tst.w	d1
	bne.w	NullSub
	bsr.w	Joypad_Read4
	or.w	d3,(ram_DCE6).w
	tst.w	d1
	bne.w	NullSub
loc_0201EC:
	move.w	(FrameCounter).w,d0
loc_0201F0:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_0201F0
	tst.w	d0
	bmi.s	loc_0201AC
	rts


; ----------------------------------------------------------------------
sub_0201FC:
	movem.l	d4-d7/a0-a3,-(sp)
	neg.w	d0
	move.w	d0,(FrameCounter).w
loc_020206:
	moveq	#$1,d7
	clr.w	(ram_C37E).w
	bclr	#1,(ram_C33C).w
	bsr.w	Joypad_Read1
	bsr.w	Joypad_Repeat
	tst.w	d1
	bne.w	loc_02027C
	clr.w	(ram_C37E).w
	bset	#1,(ram_C33C).w
	bsr.w	Joypad_Read2
	bsr.w	Joypad_Repeat
	tst.w	d1
	bne.w	loc_02027C
	tst.w	(FourWayPlay).w
	beq.w	loc_0202A6
	bclr	#1,(ram_C33C).w
	move.w	#$3,(ram_C37E).w
	bsr.w	Joypad_Read3
	bsr.w	Joypad_Repeat
	tst.w	d1
	bne.w	loc_02027C
	tst.w	(FourWayPlay).w
	beq.w	loc_0202A6
	bset	#1,(ram_C33C).w
	move.w	#$4,(ram_C37E).w
	bsr.w	Joypad_Read4
	bsr.w	Joypad_Repeat
	tst.w	d1
	beq.w	loc_0202A6
loc_02027C:
	move.w	(FrameCounter).w,d0
	cmp.w	#$FF88,d0	; general form
	blt.w	loc_02028A
	moveq	#-$78,d0
loc_02028A:
	movem.w	d0,-(sp)
	jsr	(sub_0199B8).l
	bne.w	loc_0202A2
	addq.w	#2,sp
	bset	#7,d1
	bra.w	loc_0202BA
loc_0202A2:
	move.w	(sp)+,(FrameCounter).w
loc_0202A6:
	bsr.w	sub_025926
	move.w	(FrameCounter).w,d0
loc_0202AE:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_0202AE
	tst.w	d0
	bmi.w	loc_020206
loc_0202BA:
	movem.l	(sp)+,d4-d7/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $0202CE
sub_0202C0:
	move.w	(FrameCounter).w,d0
loc_0202C4:
	cmp.w	(FrameCounter).w,d0
	beq.s	loc_0202C4
	bsr.w	Joypad_ReadAll
	beq.s	sub_0202C0
	rts


; ----------------------------------------------------------------------
; called from $015482, $0155F0, $015C00, $0166AE, $0226E2, $1D43DC, $1D5F38, $1D7D8A (+8 more)
sub_0202D2:
	clr.w	(ram_D26E).w
	bsr.w	Joypad_Read1
	tst.w	d3
	bne.w	loc_020312
	move.w	#$1,(ram_D26E).w
	bsr.w	Joypad_Read2
	tst.w	d3
	bne.w	loc_020312
	tst.w	(FourWayPlay).w
	beq.w	loc_020312
	move.w	#$2,(ram_D26E).w
	bsr.w	Joypad_Read3
	tst.w	d3
	bne.w	loc_020312
	move.w	#$3,(ram_D26E).w
	bsr.w	Joypad_Read4
loc_020312:
	rts


; ----------------------------------------------------------------------
; ORs the new presses of all pads (4 with a 4-Way Play)
; called from $00E334, $01574E, $015F94, $0169CE, $018FE6, $0202CA, $1D2710, $1D2B72 (+24 more)
Joypad_ReadAll:
	tst.w	(FourWayPlay).w
	bne.w	loc_02032A
	bsr.w	Joypad_Read1
	move.w	d1,-(sp)
	bsr.w	Joypad_Read2
	or.w	(sp)+,d1
	rts
loc_02032A:
	bsr.w	Joypad_Read1
	move.w	d1,-(sp)
	bsr.w	Joypad_Read2
	move.w	d1,-(sp)
	bsr.w	Joypad_Read3
	move.w	d1,-(sp)
	bsr.w	Joypad_Read4
	or.w	(sp)+,d1
	or.w	(sp)+,d1
	or.w	(sp)+,d1
	rts


; ----------------------------------------------------------------------
; called from $00E5A0, $00E5B0, $00E5C8, $00E5D8, $01A2EE, $020370
Joypad_DpadFilter:
	movem.l	d0/d4/d5,-(sp)
	moveq	#$3,d4
	move.w	d3,d0
	andi.w	#$F,d0
	beq.w	loc_02036A
loc_020358:
	clr.w	d5
	bset	d4,d5
	cmp.w	d5,d0
	dbeq	d4,loc_020358
	beq.w	loc_02036A
	andi.w	#$FFF0,d1
loc_02036A:
	movem.l	(sp)+,d0/d4/d5
	rts


; ----------------------------------------------------------------------
; auto repeat of held directions (ram_JoypadRepeat)
; called from $015488, $015C06, $0166B4, $019822, $020216, $02022E, $020250, $020272 (+35 more)
Joypad_Repeat:
	bsr.s	Joypad_DpadFilter
	tst.w	d3
	beq.w	NullSub
	tst.w	d2
	bne.w	loc_020390
	subq.w	#1,(JoypadRepeat).w
	bpl.w	NullSub
	move.w	#$4,(JoypadRepeat).w
	move.w	d3,d1
	rts
loc_020390:
	move.w	#$F,(JoypadRepeat).w
	rts


; ----------------------------------------------------------------------
; returns d1 = newly pressed buttons, d3 = held buttons
; called from $00CA4A, $00E59A, $00E6F4, $00E710, $00E72C, $00E748, $01900A, $01969A (+14 more)
Joypad_Read1:
	move.b	(JoypadPort1).w,d0
	bsr.w	Joypad_Remap
	move.w	(JoypadHeld1).w,d2
	move.w	d1,(JoypadHeld1).w
	move.w	d1,d3
	eor.w	d1,d2
	and.w	d2,d1
	rts


; ----------------------------------------------------------------------
; called from $00CA6A, $00E5AA, $0196B2, $01A7C2, $0201BA, $02022A, $0202E6, $020322 (+7 more)
Joypad_Read2:
	move.b	(JoypadPort2).w,d0
	bsr.w	Joypad_Remap
	move.w	(JoypadHeld2).w,d2
	move.w	d1,(JoypadHeld2).w
	move.w	d1,d3
	eor.w	d1,d2
	and.w	d2,d1
	rts


; ----------------------------------------------------------------------
; called from $00CA88, $00E5C2, $0196CE, $01A7CC, $0201D0, $02024C, $0202FE, $020336 (+6 more)
Joypad_Read3:
	move.b	(JoypadPort3).w,d0
	bsr.w	Joypad_Remap
	move.w	(JoypadHeld3).w,d2
	move.w	d1,(JoypadHeld3).w
	move.w	d1,d3
	eor.w	d1,d2
	and.w	d2,d1
	rts


; ----------------------------------------------------------------------
; called from $00CAA6, $00E5D2, $0196E6, $01A7D0, $0201DE, $02026E, $02030E, $02033C (+6 more)
Joypad_Read4:
	move.b	(JoypadPort4).w,d0
	bsr.w	Joypad_Remap
	move.w	(JoypadHeld4).w,d2
	move.w	d1,(JoypadHeld4).w
	move.w	d1,d3
	eor.w	d1,d2
	and.w	d2,d1
	rts


; ----------------------------------------------------------------------
; remaps the direction nibble through Joypad_RemapTable
; called from $02039C, $0203B4, $0203CC, $0203E4
Joypad_Remap:
	not.b	d0
	clr.w	d1
	move.b	d0,d1
	move.w	d1,-(sp)
	andi.w	#$F0,d0
	andi.w	#$F,d1
	movea.l	#Joypad_RemapTable,a0
	move.b	$0(a0,d1.w),d1
	or.w	d1,d0
	move.w	(sp)+,d1
	rts
Joypad_RemapTable:
	dc.w	$0800,$0408,$0607,$0508,$0201,$0308,$0808,$0808
; VDP_DMASafe with the video lock flag set
VDP_DMALocked:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	bsr.w	VDP_DMASafe
	move.w	(sp)+,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; like VDP_DMA but splits transfers crossing a 128K boundary
; called from $020432, $0258D2, $0258EA, $025904, $1E43A8, $1E45F8
VDP_DMASafe:
	movem.l	d2/a1,-(sp)
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.w	d0,d2
	add.w	d2,d2
	add.w	a0,d2
	bcc.w	loc_020478
	beq.w	loc_020478
	lsr.w	#1,d2
	sub.w	d2,d0
	move.w	d0,-(sp)
	bsr.w	VDP_DMA
	move.w	(sp)+,d0
	add.w	d0,d0
	add.w	d0,d1
	adda.w	d0,a0
	move.w	d2,d0
	bra.w	loc_020478


; ----------------------------------------------------------------------
; a0 = source, d0 = length in words, d1 = VRAM destination (pauses the Z80 around the transfer)
; called from $020462
VDP_DMA:
	movem.l	d2/a1,-(sp)
loc_020478:
	lea	(VDP_CTRL).l,a1
	move.w	#$8154,(a1)
	move.w	#$8F02,(a1)
	move.w	#$9300,d2
	move.b	d0,d2
	move.w	d2,(a1)
	move.w	#$9400,d2
	lsr.w	#8,d0
	move.b	d0,d2
	move.w	d2,(a1)
	move.l	a0,d0
	lsr.l	#1,d0
	move.w	#$9500,d2
	move.b	d0,d2
	move.w	d2,(a1)
	lsr.l	#8,d0
	move.w	#$9600,d2
	move.b	d0,d2
	move.w	d2,(a1)
	lsr.l	#8,d0
	andi.b	#$7F,d0
	move.w	#$9700,d2
	move.b	d0,d2
	move.w	d2,(a1)
	clr.l	d0
	move.w	d1,d0
	asl.l	#2,d0
	lsr.w	#2,d0
	ori.l	#$804000,d0
	move.l	d0,(DMACommand).w
	move.w	(ram_D29C).w,(a1)
	move.w	(DMACommand).w,(a1)
	bsr.w	VDP_WaitDMA
	move.w	#$8164,(a1)
	move.w	d0,-(sp)
	move.w	#$E,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	movem.l	(sp)+,d2/a1
	rts


; ----------------------------------------------------------------------
sub_0204F2:
	movem.l	d0-d3/a1,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	lea	(VDP_CTRL).l,a1
	move.w	#$8154,(a1)
	move.w	#$8F01,(a1)
	move.w	#$9300,d3
	move.b	d0,d3
	move.w	d3,(a1)
	move.w	#$9400,d3
	lsr.w	#8,d0
	move.b	d0,d3
	move.w	d3,(a1)
	move.w	#$9500,d3
	move.b	d2,d3
	move.w	d3,(a1)
	move.w	#$9600,d3
	lsr.w	#8,d2
	move.b	d2,d3
	move.w	d3,(a1)
	move.w	#$97C0,(a1)
	clr.l	d0
	move.w	d1,d0
	asl.l	#2,d0
	lsr.w	#2,d0
	swap	d0
	ori.w	#$C0,d0
	move.l	d0,(DMACommand).w
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.w	(DMACommand).w,(a1)
	move.w	(ram_D29C).w,(a1)
	bsr.w	VDP_WaitDMA
	move.w	#$8164,(a1)
	move.w	#$8F02,(a1)
	move.w	#$E,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,(VideoFlags).w
	movem.l	(sp)+,d0-d3/a1
	rts


; ----------------------------------------------------------------------
; called from $02649C, $1DCFB2
sub_02057E:
	movem.l	d3/a1,-(sp)
	movea.l	#VDP_DATA,a1
	andi.l	#$FFFF,d1
	asl.l	#2,d1
	lsr.w	#2,d1
	ori.w	#$4000,d1
	swap	d1
	move.l	d1,$4(a1)
	move.w	d2,d3
	swap	d3
	move.w	d2,d3
	lsr.w	#1,d0
	subq.w	#1,d0
loc_0205A6:
	move.l	d3,(DMACommand).w
	move.w	(DMACommand).w,(a1)
	move.w	(ram_D29C).w,(a1)
	dbra	d0,loc_0205A6
	movem.l	(sp)+,d3/a1
	rts


; ----------------------------------------------------------------------
; called from $0204D6, $02055E, $0205CA
VDP_WaitDMA:
	move.w	(VDP_CTRL).l,-(sp)
	btst	#1,$1(sp)
	addq.w	#2,sp
	bne.s	VDP_WaitDMA
	rts


; ----------------------------------------------------------------------
; fills the palette buffer with d0 and starts a fade
; called from $00E328, $015742, $015F88, $0169C2, $02646A, $1D2704, $1D2B66, $1D3386 (+23 more)
Palette_SetAll:
	movea.w	#$BD40,a0
	moveq	#$3F,d1
loc_0205D4:
	move.w	d0,(a0)+
	dbra	d1,loc_0205D4
	move.w	#$18,(FadeCounter).w
	bsr.w	Palette_WaitFade

; ----------------------------------------------------------------------
; clears VRAM and programs the VDP registers from the ram_Plane* variables
; called from $0270E8, $1D1C14, $1DCF9A
VDP_Init:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	move.w	#$8F02,(VDP_CTRL).l
	clr.w	d0
	bsr.w	VDP_SetWriteAddr
	move.w	#$3FFF,d0
	clr.l	d1
loc_020602:
	move.l	d1,(a0)
	dbra	d0,loc_020602
	move.w	#$8C00,d0
	btst	#5,(VideoFlags).w
	beq.w	loc_02061A
	move.w	#$8C08,d0
loc_02061A:
	btst	#1,(VideoFlags).w
	bne.w	loc_020628
	ori.w	#$81,d0
loc_020628:
	move.w	d0,$4(a0)
	move.w	#$8004,$4(a0)
	move.w	#$8164,$4(a0)
	move.w	#$9001,d0
	cmpi.w	#$6,(PlaneSize).w
	beq.w	loc_02064A
	move.w	#$9003,d0
loc_02064A:
	move.w	d0,$4(a0)
	move.w	#$8200,d0
	move.b	(PlaneAAddr).w,d0
	lsr.b	#2,d0
	andi.b	#$38,d0
	move.w	d0,$4(a0)
	move.w	#$8400,d0
	move.b	(SpriteTableAddr).w,d0
	lsr.b	#5,d0
	move.w	d0,$4(a0)
	move.w	#$8300,d0
	move.b	(PlaneBAddr).w,d0
	lsr.b	#2,d0
	andi.b	#$3E,d0
	move.w	d0,$4(a0)
	move.w	#$8500,d0
	move.b	(HScrollTableAddr).w,d0
	lsr.b	#1,d0
	move.w	d0,$4(a0)
	move.w	#$8D00,d0
	move.b	(ram_B000).w,d0
	lsr.b	#2,d0
	move.w	d0,$4(a0)
	move.w	#$9100,$4(a0)
	move.w	#$9200,$4(a0)
	move.w	#$8700,$4(a0)
	move.w	#$8B00,$4(a0)
	move.l	#$40000010,$4(a0)
	move.l	#$0,(a0)
	move.w	(sp)+,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; d0 = VRAM address; returns a0 = VDP_DATA with the write address set
; called from $019EF6, $01FF62, $0205F8, $0209BC, $021072, $0212E8, $025910, $1D1C4A (+8 more)
VDP_SetWriteAddr:
	movea.l	#VDP_DATA,a0
	asl.l	#2,d0
	lsr.w	#2,d0
	ori.w	#$4000,d0
	swap	d0
	andi.w	#$3,d0
	move.l	d0,$4(a0)
	rts


; ----------------------------------------------------------------------
; draws a tile map (a1) of d1 rows at the text cursor, loading its palettes (mask d5) into the palette buffer
; called from $00C846, $00E274, $00E3E2, $00E46A, $015850, $016024, $016B86, $016BB0 (+56 more)
TileMap_Draw:
	move.w	(TextY).w,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d3/d5/d6/a0-a3,-(sp)
	move.w	d1,d6
	movea.w	#$BD40,a3
	bra.w	loc_020714
loc_0206FE:
	move.b	$0(a0,d0.w),$0(a3,d0.w)
	dbra	d0,loc_0206FE
loc_020708:
	adda.l	#$20,a0
	adda.l	#$20,a3
loc_020714:
	moveq	#$1F,d0
	lsr.w	#1,d5
	bcs.s	loc_0206FE
	bne.s	loc_020708
	move.w	(TextAttr).w,d5
	andi.w	#$F800,d5
	move.w	$E(sp),d2
	subq.w	#1,d2
loc_02072A:
	bsr.w	Text_CursorToVRAM
	move.w	d6,d0
	mulu.w	(a1),d0
	add.w	$2(sp),d0
	asl.w	#1,d0
	move.w	$A(sp),d1
	subq.w	#1,d1
loc_02073E:
	move.w	$4(a1,d0.w),d3
	add.w	d4,d3
	eor.w	d5,d3
	move.w	d3,(a0)
	addq.w	#2,d0
	dbra	d1,loc_02073E
	addq.w	#1,(TextY).w
	addq.w	#1,d6
	dbra	d2,loc_02072A
	btst	#0,(TextFlags).w
	bne.w	loc_020766
	bsr.w	sub_020780
loc_020766:
	movem.l	(sp)+,d0-d3/d5/d6/a0-a3
	move.w	(sp)+,(VideoFlags).w
	move.w	(sp)+,(TextY).w
	rts


; ----------------------------------------------------------------------
; runs the 8 byte drawing script placed after the call (see jmptbl_0207FA for the commands)
; called from $00E348, $00E36A, $015762, $01577A, $015792, $0157B4, $015FAC, $0169E2 (+43 more)
Draw_RunScript:
	move.l	(sp),(DrawScriptPtr).w
	bsr.w	Draw_RunScript_Worker
	addq.l	#8,(sp)
	rts


; ----------------------------------------------------------------------
; called from $00C644, $00C654, $00C948, $00E392, $00E3A2, $00E3F4, $00E404, $00E414 (+75 more)
sub_020780:
	clr.l	(DrawScriptPtr).w

; ----------------------------------------------------------------------
; called from $020778
Draw_RunScript_Worker:
	movem.l	d0/d1/a0-a6,-(sp)
	movea.l	a2,a0
	move.w	d4,d1
	asl.w	#5,d1
	move.w	(a0)+,d0
	beq.w	loc_0207BC
	bmi.w	loc_0207B2
	add.w	d0,d4
	asl.w	#4,d0
	pea	(loc_0207BC).l
	tst.l	(DrawScriptPtr).w
	beq.w	VDP_DMALocked
	movea.l	(DrawScriptPtr).w,a1
	bra.w	loc_01FF50
loc_0207B2:
	andi.w	#$7FFF,d0
	add.w	d0,d4
	bsr.w	Draw_Interpreter
loc_0207BC:
	movem.l	(sp)+,d0/d1/a0-a6
	rts


; ----------------------------------------------------------------------
; nibble coded tile row commands: copy, clear, fill, repeat
; called from $0207B8
Draw_Interpreter:
	movea.w	#$D14C,a1
	movea.w	#$D14C,a3
	movea.w	#$D048,a4
	movea.l	#loc_01FF50,a5
	movea.l	#VDP_DMALocked,a6
	movem.l	d0-d3/a0-a2,-(sp)
	move.w	d1,d3
	clr.w	d1
	clr.w	d2
loc_0207E4:
	move.b	(a0)+,d0
	andi.w	#$F0,d0
	lsr.w	#3,d0
	lea	Draw_CommandTable(pc),a2
	move.w	$0(a2,d0.w),d0
	jsr	$0(a2,d0.w)
	bra.s	loc_0207E4

Draw_CommandTable:
	dc.w	loc_02081A-Draw_CommandTable
	dc.w	loc_02081A-Draw_CommandTable
	dc.w	loc_020836-Draw_CommandTable
	dc.w	loc_020852-Draw_CommandTable
	dc.w	loc_020872-Draw_CommandTable
	dc.w	loc_020872-Draw_CommandTable
	dc.w	loc_020872-Draw_CommandTable
	dc.w	loc_020872-Draw_CommandTable
	dc.w	loc_0208A4-Draw_CommandTable
	dc.w	loc_0208B2-Draw_CommandTable
	dc.w	loc_0208CC-Draw_CommandTable
	dc.w	loc_0208E6-Draw_CommandTable
	dc.w	loc_020900-Draw_CommandTable
	dc.w	loc_020900-Draw_CommandTable
	dc.w	loc_020932-Draw_CommandTable
	dc.w	loc_020952-Draw_CommandTable
loc_02081A:
	move.b	-$1(a0),d0
	andi.w	#$1F,d0
loc_020822:
	move.b	(a0)+,$0(a1,d1.w)
	addq.b	#1,d1
	bne.w	loc_020830
	bsr.w	sub_02096C
loc_020830:
	dbra	d0,loc_020822
	rts
loc_020836:
	move.b	-$1(a0),d0
	andi.w	#$F,d0
loc_02083E:
	clr.b	$0(a1,d1.w)
	addq.b	#1,d1
	bne.w	loc_02084C
	bsr.w	sub_02096C
loc_02084C:
	dbra	d0,loc_02083E
	rts
loc_020852:
	move.b	-$1(a0),d0
	andi.w	#$F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
loc_02085E:
	move.b	d2,$0(a1,d1.w)
	addq.b	#1,d1
	bne.w	loc_02086C
	bsr.w	sub_02096C
loc_02086C:
	dbra	d0,loc_02085E
	rts
loc_020872:
	move.b	-$1(a0),d0
	andi.w	#$7,d0
	addq.w	#1,d0
	move.b	-$1(a0),d2
	lsr.w	#3,d2
	andi.w	#$7,d2
	addq.w	#1,d2
loc_020888:
	neg.b	d2
	add.b	d1,d2
loc_02088C:
	move.b	$0(a1,d2.w),$0(a1,d1.w)
	addq.b	#1,d2
	addq.b	#1,d1
	bne.w	loc_02089E
	bsr.w	sub_02096C
loc_02089E:
	dbra	d0,loc_02088C
	rts
loc_0208A4:
	move.b	-$1(a0),d0
	andi.w	#$F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	bra.s	loc_020888
loc_0208B2:
	move.b	(a0),d0
	asl.b	#1,d0
	move.b	-$1(a0),d0
	roxl.b	#1,d0
	andi.w	#$1F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	andi.w	#$7F,d2
	addq.w	#1,d2
	bra.s	loc_020888
loc_0208CC:
	move.b	-$1(a0),d0
	asl.w	#8,d0
	move.b	(a0),d0
	lsr.w	#6,d0
	andi.w	#$3F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	andi.w	#$3F,d2
	addq.w	#1,d2
	bra.s	loc_020888
loc_0208E6:
	move.b	-$1(a0),d0
	asl.w	#8,d0
	move.b	(a0),d0
	lsr.w	#5,d0
	andi.w	#$7F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	andi.w	#$1F,d2
	addq.w	#1,d2
	bra.s	loc_020888
loc_020900:
	move.b	-$1(a0),d0
	andi.w	#$3,d0
	addq.w	#1,d0
	move.b	-$1(a0),d2
	lsr.w	#2,d2
	andi.w	#$7,d2
	addq.w	#1,d2
loc_020916:
	neg.b	d2
	add.b	d1,d2
loc_02091A:
	move.b	$0(a1,d2.w),$0(a1,d1.w)
	subq.b	#1,d2
	addq.b	#1,d1
	bne.w	loc_02092C
	bsr.w	sub_02096C
loc_02092C:
	dbra	d0,loc_02091A
	rts
loc_020932:
	move.b	-$1(a0),d0
	andi.w	#$F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	bne.s	loc_020916
	tst.w	d1
	beq.w	loc_02094A
	bsr.w	sub_02096C
loc_02094A:
	addq.w	#4,sp
	movem.l	(sp)+,d0-d3/a0-a2
	rts
loc_020952:
	move.b	(a0),d0
	asl.b	#1,d0
	move.b	-$1(a0),d0
	roxl.b	#1,d0
	andi.w	#$1F,d0
	addq.w	#2,d0
	move.b	(a0)+,d2
	andi.w	#$7F,d2
	addq.w	#1,d2
	bra.s	loc_020916


; ----------------------------------------------------------------------
; called from $02082C, $020848, $020868, $02089A, $020928, $020946
sub_02096C:
	movem.l	d0/d1/a0/a1,-(sp)
	move.w	d1,d0
	bne.w	loc_02097A
	move.w	#$100,d0
loc_02097A:
	lsr.w	#1,d0
	move.w	d3,d1
	add.w	d0,d3
	add.w	d0,d3
	movea.l	a1,a0
	tst.l	(a4)
	beq.w	loc_020992
	movea.l	(a4),a1
	jsr	(a5)
	bra.w	loc_020994
loc_020992:
	jsr	(a6)
loc_020994:
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; sets the VDP write address for ram_TextX / ram_TextY on the current plane
; called from $02072A, $0209D8, $020A4E, $020AB0, $020B3A, $020B84, $020BA2, $020BB0 (+12 more)
Text_CursorToVRAM:
	movem.l	d0-d2,-(sp)
	move.w	(TextX).w,d0
	move.w	(TextY).w,d1
	movea.l	#PlaneAAddr,a0
	adda.w	(TextPlaneOffset).w,a0
	move.w	$2(a0),d2
	asl.w	d2,d1
	add.w	d1,d0
	asl.w	#1,d0
	add.w	(a0),d0
	bsr.w	VDP_SetWriteAddr
	movem.l	(sp)+,d0-d2
	rts


; ----------------------------------------------------------------------
; d0 = width, d1 = rows, d2 = tile
; called from $00E440, $00F170, $01285E, $0157F8, $015FFA, $016B1A, $016EAC, $01A81E (+63 more)
Text_FillRect:
	movem.l	d0-d2/a0,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.w	d0/d1,-(sp)
loc_0209D8:
	bsr.s	Text_CursorToVRAM
	move.w	(sp),d0
	subq.w	#1,d0
loc_0209DE:
	move.w	d2,(a0)
	dbra	d0,loc_0209DE
	addq.w	#1,(TextY).w
	andi.w	#$1F,(TextY).w
	subq.w	#1,$2(sp)
	bne.s	loc_0209D8
	addq.w	#4,sp
	move.w	(sp)+,(VideoFlags).w
	movem.l	(sp)+,d0-d2/a0
	rts


; ----------------------------------------------------------------------
; called from $00C86A, $00F1CE, $01263A, $021C66, $021CB0, $02224C, $027ED4, $0280A8 (+7 more)
Text_PrintDigitsBig:
	movem.l	d0-d4/a0/a1,-(sp)
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.w	d0/d1,-(sp)
	move.w	(TextAttr).w,d2
	add.w	(ram_B02A).w,d2
	movea.l	#Art_09E36A,a1
	adda.l	$4(a1),a1
	addq.w	#4,a1
	clr.w	d4
	bsr.w	sub_020A4E
	subq.w	#3,$2(sp)
loc_020A30:
	bsr.w	sub_020A4E
	subq.w	#6,d4
	subq.w	#1,$2(sp)
	bpl.s	loc_020A30
	addq.w	#6,d4
	bsr.w	sub_020A4E
	addq.w	#4,sp
	move.w	(sp)+,(VideoFlags).w
	movem.l	(sp)+,d0-d4/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $020A28, $020A30, $020A3E
sub_020A4E:
	bsr.w	Text_CursorToVRAM
	addq.w	#1,(TextY).w
	bsr.w	sub_020A74
	addq.w	#2,d4
	move.w	$4(sp),d0
	subq.w	#3,d0
loc_020A62:
	bsr.w	sub_020A74
	dbra	d0,loc_020A62
	addq.w	#2,d4
	bsr.w	sub_020A74
	addq.w	#2,d4
	rts


; ----------------------------------------------------------------------
; called from $020A56, $020A62, $020A6C
sub_020A74:
	move.w	$0(a1,d4.w),d3
	add.w	d2,d3
	move.w	d3,(a0)
	rts


; ----------------------------------------------------------------------
; inline text with escape commands dispatched through Text_CmdTable
; called from $00C85A, $00C884, $00E42A, $00E55C, $0157E2, $0158BA, $015FE4, $016B04 (+89 more)
Text_PrintCmd:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintCmd_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $00E56C, $0189CC, $0189D4, $018A12, $018A4A, $018B18, $018B2A, $020A84 (+33 more)
Text_PrintCmd_Worker:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d3/a0/a2/a3,-(sp)
	movea.w	#$B01C,a3
	btst	#3,(TextFlags).w
	beq.w	loc_020AB0
	movea.w	#$BF8A,a3
loc_020AB0:
	bsr.w	Text_CursorToVRAM
	move.w	(TextAttr).w,d2
	move.w	(a1)+,d3
	subq.w	#2,d3
	bra.w	loc_020B28
loc_020AC0:
	move.b	(a1)+,d0
	ext.w	d0
	bgt.w	loc_020ADC
	neg.w	d0
	asl.w	#2,d0
	movea.l	#Text_CmdTable,a2
	movea.l	$0(a2,d0.w),a2
	jsr	(a2)
	bra.w	loc_020B28
loc_020ADC:
	cmp.b	#$40,d0	; general form
	bne.w	loc_020AEC
	move.w	#$7FF,d0
	bra.w	loc_020B20
loc_020AEC:
	cmp.b	#$5E,d0	; general form
	beq.w	loc_020B36
	cmp.b	#$61,d0	; general form
	blt.w	loc_020B08
	cmp.b	#$7A,d0	; general form
	bgt.w	loc_020B08
	addi.b	#$E0,d0
loc_020B08:
	asl.w	#1,d0
	movea.l	#Font_Cmd,a2
	adda.l	$4(a2),a2
	move.w	$4(a2,d0.w),d0
	move.w	(ram_B04A).w,d1
	add.w	$0(a3,d1.w),d0
loc_020B20:
	add.w	d2,d0
	move.w	d0,(a0)
	addq.w	#1,(TextX).w
loc_020B28:
	dbra	d3,loc_020AC0
	movem.l	(sp)+,d0-d3/a0/a2/a3
	move.w	(sp)+,(VideoFlags).w
	rts
loc_020B36:
	addq.w	#1,(TextX).w
	bsr.w	Text_CursorToVRAM
	bra.s	loc_020B28

; escape command handlers for Text_PrintCmd
Text_CmdTable:
	dc.l	NullSub
	dc.l	sub_020B74
	dc.l	sub_020B88
	dc.l	sub_020B98
	dc.l	sub_020BA6
	dc.l	sub_020BB4
	dc.l	sub_020BC2
	dc.l	sub_020BD0
	dc.l	sub_020B64


; ----------------------------------------------------------------------
; called from $020AD6
sub_020B64:
	bsr.w	sub_020B88
	bsr.w	sub_020B74
	bsr.w	sub_020B98
	bra.w	sub_020BA6


; ----------------------------------------------------------------------
; called from $020AD6, $020B68
sub_020B74:
	move.b	(a1)+,d0
	subq.w	#1,d3
	andi.w	#$3,d0
	asl.w	#2,d0
	subq.w	#4,d0
	move.w	d0,(TextPlaneOffset).w
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020AD6, $020B64
sub_020B88:
	move.b	(a1)+,d2
	andi.w	#$7,d2
	subq.w	#1,d3
	ror.w	#3,d2
	move.w	d2,(TextAttr).w
	rts


; ----------------------------------------------------------------------
; called from $020AD6, $020B6C
sub_020B98:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	move.w	d0,(TextX).w
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020AD6, $020B70
sub_020BA6:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	move.w	d0,(TextY).w
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020AD6
sub_020BB4:
	move.b	(a1)+,d0
	ext.w	d0
	subq.w	#1,d3
	add.w	d0,(TextX).w
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020AD6
sub_020BC2:
	move.b	(a1)+,d0
	ext.w	d0
	subq.w	#1,d3
	add.w	d0,(TextY).w
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020AD6
sub_020BD0:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	asl.w	#1,d0
	move.w	d0,(ram_B04A).w
	rts


; ----------------------------------------------------------------------
; inline text using Font_Small; negative bytes set palette/plane, then x and y
; called from $00C7EC, $00E1E2, $00E3AA, $00E446, $00E4A0, $00E4BA, $00F15C, $00F1B8 (+222 more)
Text_Print:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_Print_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $00C89C, $00C8B4, $00F1EE, $00F202, $01267A, $01268E, $0126B6, $020BE4 (+43 more)
Text_Print_Worker:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d3/a0/a2,-(sp)
	bsr.w	Text_CursorToVRAM
	move.w	(TextAttr).w,d2
	move.w	(a1)+,d3
	subq.w	#2,d3
	bra.w	loc_020CAA
loc_020C0E:
	move.b	(a1)+,d0
	beq.w	loc_020CAA
	ext.w	d0
	bpl.w	loc_020C50
	neg.w	d0
	move.w	d0,d2
	asl.w	#8,d2
	asl.w	#1,d2
	andi.w	#$F800,d2
	move.w	d2,(TextAttr).w
	andi.w	#$3,d0
	asl.w	#2,d0
	subq.w	#4,d0
	move.w	d0,(TextPlaneOffset).w
	move.b	(a1)+,d0
	ext.w	d0
	move.w	d0,(TextX).w
	move.b	(a1)+,d1
	ext.w	d1
	move.w	d1,(TextY).w
	bsr.w	Text_CursorToVRAM
	subq.w	#2,d3
	bra.w	loc_020CAA
loc_020C50:
	cmp.b	#$40,d0	; general form
	bne.w	loc_020C60
	move.w	#$7FF,d0
	bra.w	loc_020CA2
loc_020C60:
	cmp.b	#$5E,d0	; general form
	beq.w	loc_020CB8
	cmp.b	#$61,d0	; general form
	blt.w	loc_020C7C
	cmp.b	#$7A,d0	; general form
	bgt.w	loc_020C7C
	addi.b	#$E0,d0
loc_020C7C:
	asl.w	#1,d0
	movea.l	#Font_Small,a2
	adda.l	$4(a2),a2
	move.w	$4(a2,d0.w),d0
	btst	#3,(TextFlags).w
	beq.w	loc_020C9E
	add.w	(FontTileBaseAlt).w,d0
	bra.w	loc_020CA2
loc_020C9E:
	add.w	(FontTileBase).w,d0
loc_020CA2:
	add.w	d2,d0
	move.w	d0,(a0)
	addq.w	#1,(TextX).w
loc_020CAA:
	dbra	d3,loc_020C0E
	movem.l	(sp)+,d0-d3/a0/a2
	move.w	(sp)+,(VideoFlags).w
	rts
loc_020CB8:
	addq.w	#1,(TextX).w
	bsr.w	Text_CursorToVRAM
	bra.s	loc_020CAA


; ----------------------------------------------------------------------
; inline text using the font in ram_FontPtr
; called from $00E50A, $00E528, $01551A, $015542, $01556A, $015592, $0155BA, $015608 (+137 more)
Text_PrintFont:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintFont_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $0158AC, $015944, $0159D2, $0159EC, $015A06, $018C1C, $019C1C, $019C44 (+48 more)
Text_PrintFont_Worker:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d3/a0/a2,-(sp)
	bsr.w	Text_CursorToVRAM
	move.w	(TextAttr).w,d2
	move.w	(a1)+,d3
	subq.w	#2,d3
	bra.w	loc_020D8C
loc_020CF2:
	move.b	(a1)+,d0
	beq.w	loc_020D8C
	ext.w	d0
	bpl.w	loc_020D34
	neg.w	d0
	move.w	d0,d2
	asl.w	#8,d2
	asl.w	#1,d2
	andi.w	#$F800,d2
	move.w	d2,(TextAttr).w
	andi.w	#$3,d0
	asl.w	#2,d0
	subq.w	#4,d0
	move.w	d0,(TextPlaneOffset).w
	move.b	(a1)+,d0
	ext.w	d0
	move.w	d0,(TextX).w
	move.b	(a1)+,d1
	ext.w	d1
	move.w	d1,(TextY).w
	bsr.w	Text_CursorToVRAM
	subq.w	#2,d3
	bra.w	loc_020D8C
loc_020D34:
	cmp.b	#$40,d0	; general form
	bne.w	loc_020D44
	move.w	#$7FF,d0
	bra.w	loc_020D84
loc_020D44:
	cmp.b	#$5E,d0	; general form
	beq.w	loc_020D9A
	cmp.b	#$61,d0	; general form
	blt.w	loc_020D60
	cmp.b	#$7A,d0	; general form
	bgt.w	loc_020D60
	addi.b	#$E0,d0
loc_020D60:
	asl.w	#1,d0
	movea.l	(FontPtr).w,a2
	adda.l	$4(a2),a2
	move.w	$4(a2,d0.w),d0
	btst	#3,(TextFlags).w
	beq.w	loc_020D80
	add.w	(FontTileBaseAlt).w,d0
	bra.w	loc_020D84
loc_020D80:
	add.w	(FontTileBase).w,d0
loc_020D84:
	add.w	d2,d0
	move.w	d0,(a0)
	addq.w	#1,(TextX).w
loc_020D8C:
	dbra	d3,loc_020CF2
	movem.l	(sp)+,d0-d3/a0/a2
	move.w	(sp)+,(VideoFlags).w
	rts
loc_020D9A:
	addq.w	#1,(TextX).w
	bsr.w	Text_CursorToVRAM
	bra.s	loc_020D8C


; ----------------------------------------------------------------------
; called from $1DDE12, $1DE338
sub_020DA4:
	swap	d0
	clr.w	d0
	rol.l	#2,d0
	movea.l	#dat_020DC4,a1
	bsr.w	sub_022A6E
	addq.w	#2,(TextX).w
	swap	d0
	lsr.w	#2,d0
	bsr.w	sub_020DD4
	bra.w	Text_PrintCmd_Worker
dat_020DC4:
	dc.w	$0004,$2031,$0004,$2032,$0004,$2033,$0004,$4F54


; ----------------------------------------------------------------------
; called from $019D22, $020DBC, $0221A4, $022370, $1DD668, $1DE960
sub_020DD4:
	movea.w	#$C012,a1
	move.l	d0,-(sp)
	move.l	a1,-(sp)
	ext.l	d0
	divu.w	#$A,d0
	swap	d0
	addi.w	#$30,d0
	move.b	d0,-(a1)
	swap	d0
	ext.l	d0
	divu.w	#$6,d0
	swap	d0
	addi.w	#$30,d0
	move.b	d0,-(a1)
	swap	d0
	move.b	#$3A,-(a1)
	ext.l	d0
	divu.w	#$A,d0
	swap	d0
	addi.w	#$30,d0
	move.b	d0,-(a1)
	swap	d0
	move.b	#$20,-(a1)
	tst.w	d0
	beq.w	loc_020E20
	addi.w	#$30,d0
	move.b	d0,(a1)
loc_020E20:
	move.l	(sp)+,d0
	sub.l	a1,d0
	addq.w	#2,d0
	btst	#0,d0
	beq.w	loc_020E32
	clr.b	-(a1)
	addq.w	#1,d0
loc_020E32:
	move.w	d0,-(a1)
	move.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; called from $1D8A6A, $1D8ABA, $1D909C, $1D90D2, $1DE37E, $1DE8DA, $1DE93E, $1DE95A
sub_020E38:
	movea.w	#$C060,a1
	move.l	d0,-(sp)
	move.l	a1,-(sp)
loc_020E40:
	ext.l	d0
	divu.w	#$A,d0
	swap	d0
	addi.w	#$30,d0
	move.b	d0,-(a1)
	swap	d0
	tst.w	d0
	bne.s	loc_020E40
	move.l	(sp)+,d0
	sub.l	a1,d0
	addq.w	#2,d0
	btst	#0,d0
	beq.w	loc_020E66
	clr.b	-(a1)
	addq.w	#1,d0
loc_020E66:
	move.w	d0,-(a1)
	move.l	(sp)+,d0
	rts


; ----------------------------------------------------------------------
; d0 = value, d1 = digits; writes the ASCII digits to ram_NumStr
; called from $015274, $0159CC, $0159E6, $015A00, $0161BA, $016256, $0162C8, $016C96 (+58 more)
Num_ToDecimal:
	movem.l	d0-d3,-(sp)
	movea.w	#$C05A,a1
	moveq	#$1,d2
	sub.w	d2,d1
	bra.w	loc_020E80
loc_020E7C:
	mulu.w	#$A,d2
loc_020E80:
	dbra	d1,loc_020E7C
	moveq	#$20,d3
loc_020E86:
	ext.l	d0
	divu.w	d2,d0
	bne.w	loc_020E9C
	cmp.w	#$1,d2	; general form
	beq.w	loc_020E9C
	move.w	d3,d0
	bra.w	loc_020EA0
loc_020E9C:
	moveq	#$30,d3
	add.w	d3,d0
loc_020EA0:
	move.b	d0,(a1)+
	swap	d0
	divu.w	#$A,d2
	bne.s	loc_020E86
	move.l	a1,d0
	subi.w	#$C058,d0
	btst	#0,d0
	beq.w	loc_020EBC
	clr.b	(a1)+
	addq.w	#1,d0
loc_020EBC:
	movea.w	#$C058,a1
	move.w	d0,(a1)
	movem.l	(sp)+,d0-d3
	rts


; ----------------------------------------------------------------------
; appends the inline string to the length prefixed buffer at (a3)
; called from $00F24A, $0221D2, $028528, $1DE8E6, $1DE930
Text_AppendInline:
	movea.l	(sp)+,a1
	bsr.w	Text_AppendInline_Worker
	jmp	(a1)


; ----------------------------------------------------------------------
; called from $00F25E, $015280, $0152D8, $020ECA, $0221E4, $028532, $1D07C8, $1DE8E0 (+2 more)
Text_AppendInline_Worker:
	movem.l	d0/a0,-(sp)
	lea	$2(a3),a0
	move.w	(a3),d0
	subq.w	#3,d0
	bmi.w	loc_020EE8
loc_020EE0:
	addq.w	#1,a0
	tst.b	(a0)
	dbeq	d0,loc_020EE0
loc_020EE8:
	move.w	(a1)+,d0
	subq.w	#3,d0
	bmi.w	loc_020F0E
loc_020EF0:
	move.b	(a1)+,(a0)+
	bne.w	loc_020EF8
	subq.w	#1,a0
loc_020EF8:
	dbra	d0,loc_020EF0
	move.l	a0,d0
	btst	#0,d0
	beq.w	loc_020F0A
	clr.b	(a0)+
	addq.l	#1,d0
loc_020F0A:
	sub.l	a3,d0
	move.w	d0,(a3)
loc_020F0E:
	movem.l	(sp)+,d0/a0
	rts


; ----------------------------------------------------------------------
; inline text, large font with per character tile pairs
; called from $00E4E4, $01585C, $015874, $016036, $016056, $016BBC, $1D27AC, $1D2C5C (+26 more)
Text_PrintBig:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintBig_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; inline text using the font in ram_FontPtr2 (scoreboard / HUD)
; called from $1DD31C, $1DD430, $1DD458, $1DD480, $1DD4A8, $1DD740, $1DD754
Text_PrintHud:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	sub_020F4A
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; inline text using Font_Narrow
; called from $00E47A, $01609A, $0160F8, $0161CC, $016268, $016BEA, $016C02, $016C10 (+28 more)
Text_PrintNarrow:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintNarrow_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $019ABA, $019B26, $019B34, $019BB2, $019BC0, $019FEC, $020F2C, $0211B6 (+12 more)
sub_020F4A:
	bra.w	loc_020F6C


; ----------------------------------------------------------------------
; called from $0161C0, $01625C, $0162CE, $016308, $016320, $016C3E, $016CA8, $016CCC (+26 more)
Text_PrintNarrow_Worker:
	move.l	#Font_Narrow,(FontPtr2).l
	btst	#2,(ram_C356).w
	beq.w	loc_020F6C
	move.l	#Font_Narrow,(FontPtr2).l
loc_020F6C:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d7/a0/a2,-(sp)
	move.w	(TextX).w,d4
	move.w	(TextY).w,d5
	move.w	(TextAttr).w,d6
	btst	#2,(ram_C356).w
	bne.w	loc_020F98
	add.w	(ram_B014).w,d6
	bra.w	loc_020F9C
loc_020F98:
	add.w	(ram_B018).w,d6
loc_020F9C:
	move.w	(a1)+,d3
	subq.w	#2,d3
	bra.w	loc_020FE0
loc_020FA4:
	move.b	(a1)+,d0
	beq.w	loc_020FE0
	ext.w	d0
	bpl.w	loc_020FC4
	neg.w	d0
	asl.w	#2,d0
	movea.l	#ptrtbl_02107E,a2
	movea.l	$0(a2,d0.w),a2
	jsr	(a2)
	bra.w	loc_020FE0
loc_020FC4:
	cmp.b	#$61,d0	; general form
	blt.w	loc_020FD8
	cmp.b	#$7A,d0	; general form
	bgt.w	loc_020FD8
	addi.b	#$E0,d0
loc_020FD8:
	move.w	d3,-(sp)
	bsr.w	sub_020FF6
	move.w	(sp)+,d3
loc_020FE0:
	dbra	d3,loc_020FA4
	move.w	d4,(TextX).w
	move.w	d5,(TextY).w
	movem.l	(sp)+,d0-d7/a0/a2
	move.w	(sp)+,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $020FDA
sub_020FF6:
	subi.w	#$20,d0
	btst	#6,(ram_C35A).w
	beq.w	loc_021016
	cmp.b	#$3A,d0	; general form
	bne.w	loc_021016
	move.b	#$2E,d1
	clr.w	d2
	bra.w	loc_021022
loc_021016:
	movea.l	#dat_028932,a0
	clr.w	d2
	move.b	$0(a0,d0.w),d1
loc_021022:
	ext.w	d1
	asl.w	#1,d1
	movea.l	(FontPtr2).w,a0
	adda.l	$4(a0),a0
loc_02102E:
	move.w	$4(a0,d1.w),d3
	bsr.w	sub_021054
	move.w	(a0),d7
	asl.w	#1,d7
	add.w	d7,d1
	move.w	$4(a0,d1.w),d3
	sub.w	d7,d1
	addq.w	#1,d5
	bsr.w	sub_021054
	subq.w	#1,d5
	addq.w	#1,d4
	addq.w	#2,d1
	dbra	d2,loc_02102E
	rts


; ----------------------------------------------------------------------
; called from $021032, $021044
sub_021054:
	add.w	d6,d3
	movem.l	d1/a0,-(sp)
	move.w	d5,d0
	movea.l	#PlaneAAddr,a0
	adda.w	(TextPlaneOffset).w,a0
	move.w	$2(a0),d1
	asl.w	d1,d0
	add.w	d4,d0
	asl.w	#1,d0
	add.w	(a0),d0
	bsr.w	VDP_SetWriteAddr
	move.w	d3,(a0)
	movem.l	(sp)+,d1/a0
	rts

ptrtbl_02107E:
	dc.l	NullSub
	dc.l	sub_0210B2
	dc.l	sub_0210C4
	dc.l	sub_0210EA
	dc.l	sub_0210FC
	dc.l	sub_02110E
	dc.l	sub_021120
	dc.l	sub_021132
	dc.l	sub_0210A2


; ----------------------------------------------------------------------
; called from $020FBE
sub_0210A2:
	bsr.w	sub_0210C4
	bsr.w	sub_0210B2
	bsr.w	sub_0210EA
	bra.w	sub_0210FC


; ----------------------------------------------------------------------
; called from $020FBE, $0210A6
sub_0210B2:
	move.b	(a1)+,d0
	subq.w	#1,d3
	andi.w	#$3,d0
	asl.w	#2,d0
	subq.w	#4,d0
	move.w	d0,(TextPlaneOffset).w
	rts


; ----------------------------------------------------------------------
; called from $020FBE, $0210A2
sub_0210C4:
	move.b	(a1)+,d6
	andi.w	#$7,d6
	subq.w	#1,d3
	ror.w	#3,d6
	move.w	d6,(TextAttr).w
	btst	#2,(ram_C356).w
	bne.w	loc_0210E4
	add.w	(ram_B014).w,d6
	bra.w	loc_0210E8
loc_0210E4:
	add.w	(ram_B018).w,d6
loc_0210E8:
	rts


; ----------------------------------------------------------------------
; called from $020FBE, $0210AA
sub_0210EA:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	move.w	d0,(TextX).w
	move.w	(TextX).w,d4
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020FBE, $0210AE
sub_0210FC:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	move.w	d0,(TextY).w
	move.w	(TextY).w,d5
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020FBE
sub_02110E:
	move.b	(a1)+,d0
	ext.w	d0
	subq.w	#1,d3
	add.w	d0,(TextX).w
	move.w	(TextX).w,d4
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020FBE
sub_021120:
	move.b	(a1)+,d0
	ext.w	d0
	subq.w	#1,d3
	add.w	d0,(TextY).w
	move.w	(TextY).w,d5
	bra.w	Text_CursorToVRAM


; ----------------------------------------------------------------------
; called from $020FBE
sub_021132:
	clr.w	d0
	move.b	(a1)+,d0
	subq.w	#1,d3
	move.w	(ram_B016).w,(ram_B014).w
	move.l	#Font_Scoreboard,(FontPtr2).l
	cmp.w	#$2,d0	; general form
	beq.w	loc_02116A
	cmp.w	#$3,d0	; general form
	bne.w	loc_021168
	move.w	(ram_B01A).w,(ram_B014).w
	move.l	#Art_1B65AC,(FontPtr2).l
loc_021168:
	rts
loc_02116A:
	move.w	(ram_B018).w,(ram_B014).w
	move.l	#Art_1B5AEA,(FontPtr2).l
	rts


; ----------------------------------------------------------------------
; inline text using Font_Scoreboard
; called from $01A85A, $022196, $0221BC, $1D0A6C, $1D0AB8, $1D0D10, $1D0D20, $1D25CA (+2 more)
Text_PrintScoreboard:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintScoreboard_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; inline text using Art_1B5AEA
; called from $01A880, $021CB6, $027ED8, $0280C0, $0280FC, $028136, $1D0A28, $1D0C9C (+8 more)
Text_PrintScoreboardAlt:
	move.l	a1,-(sp)
	movea.l	$4(sp),a1
	bsr.w	Text_PrintScoreboardAlt_Worker
	move.l	a1,$4(sp)
	movea.l	(sp)+,a1
	rts


; ----------------------------------------------------------------------
; called from $021182, $0221B8, $1D0A98, $1D0AE4, $1D0D1A, $1E3028, $1E3070
Text_PrintScoreboard_Worker:
	bclr	#2,(ram_C356).w
	move.l	#Font_Scoreboard,(FontPtr2).l
	move.w	(ram_B016).w,(ram_B014).w
	jmp	(sub_020F4A).l


; ----------------------------------------------------------------------
; called from $021194, $021CF8, $028214, $0283A2, $1D09AA, $1D0AB2, $1D0AFE, $1E2F40 (+4 more)
Text_PrintScoreboardAlt_Worker:
	bclr	#2,(ram_C356).w
	move.l	#Art_1B5AEA,(FontPtr2).l
	move.w	(ram_B018).w,(ram_B014).w
	jmp	(sub_020F4A).l


; ----------------------------------------------------------------------
; called from $020F1A
Text_PrintBig_Worker:
	move.w	(VideoFlags).w,-(sp)
	bset	#2,(VideoFlags).w
	movem.l	d0-d7/a0/a2,-(sp)
	move.w	(TextX).w,d4
	move.w	(TextY).w,d5
	move.w	(TextAttr).w,d6
	add.w	(ram_B020).w,d6
	move.w	(a1)+,d3
	subq.w	#2,d3
	bra.w	loc_02125C
loc_0211FE:
	move.b	(a1)+,d0
	beq.w	loc_02125C
	ext.w	d0
	bpl.w	loc_021240
	neg.w	d0
	move.w	d0,d6
	asl.w	#8,d6
	asl.w	#1,d6
	andi.w	#$F800,d6
	move.w	d6,(TextAttr).w
	add.w	(ram_B020).w,d6
	andi.w	#$3,d0
	asl.w	#2,d0
	subq.w	#4,d0
	move.w	d0,(TextPlaneOffset).w
	move.b	(a1)+,d4
	ext.w	d4
	move.w	d4,(TextX).w
	move.b	(a1)+,d5
	ext.w	d5
	move.w	d5,(TextY).w
	subq.w	#2,d3
	bra.w	loc_02125C
loc_021240:
	cmp.b	#$61,d0	; general form
	blt.w	loc_021254
	cmp.b	#$7A,d0	; general form
	bgt.w	loc_021254
	addi.b	#$E0,d0
loc_021254:
	move.w	d3,-(sp)
	bsr.w	sub_021272
	move.w	(sp)+,d3
loc_02125C:
	dbra	d3,loc_0211FE
	move.w	d4,(TextX).w
	move.w	d5,(TextY).w
	movem.l	(sp)+,d0-d7/a0/a2
	move.w	(sp)+,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $021256
sub_021272:
	subi.w	#$20,d0
	beq.w	loc_0212F4
	cmp.w	#$F,d0	; general form
	bne.s	loc_021282
	nop
loc_021282:
	movea.l	#dat_028970,a0
	moveq	#$1,d2
	move.b	$0(a0,d0.w),d1
	ext.w	d1
	bpl.w	loc_021298
	neg.w	d1
	clr.w	d2
loc_021298:
	asl.w	#1,d1
	movea.l	#Art_1AAD96,a0
	adda.l	$4(a0),a0
loc_0212A4:
	move.w	$4(a0,d1.w),d3
	bsr.w	sub_0212CA
	move.w	(a0),d7
	asl.w	#1,d7
	add.w	d7,d1
	move.w	$4(a0,d1.w),d3
	sub.w	d7,d1
	addq.w	#1,d5
	bsr.w	sub_0212CA
	subq.w	#1,d5
	addq.w	#1,d4
	addq.w	#2,d1
	dbra	d2,loc_0212A4
	rts


; ----------------------------------------------------------------------
; called from $0212A8, $0212BA
sub_0212CA:
	add.w	d6,d3

; ----------------------------------------------------------------------
; called from $0212F6, $0212FA
sub_0212CC:
	movem.l	d1/a0,-(sp)
	move.w	d5,d0
	movea.l	#PlaneAAddr,a0
	adda.w	(TextPlaneOffset).w,a0
	move.w	$2(a0),d1
	asl.w	d1,d0
	add.w	d4,d0
	asl.w	#1,d0
	add.w	(a0),d0
	bsr.w	VDP_SetWriteAddr
	move.w	d3,(a0)
	movem.l	(sp)+,d1/a0
	rts
loc_0212F4:
	moveq	#$0,d3
	bsr.s	sub_0212CC
	addq.w	#1,d5
	bsr.s	sub_0212CC
	subq.w	#1,d5
	addq.w	#1,d4
	rts


; ----------------------------------------------------------------------
sub_021302:
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Small_Tiles,a2
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $019F56, $0264F2, $1DCFBC
sub_021310:
	movea.l	#Art_09E36A_Tiles,a2
	move.w	d4,(ram_B02A).w
	bra.w	sub_020780


; ----------------------------------------------------------------------
; called from $01EAD6, $01EB94, $022FC0, $02315A, $023166, $0231B4, $0233C6, $023476 (+1 more)
sub_02131E:
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	cmp.w	#$C,d0	; general form
	beq.w	sub_02135E
	cmpi.w	#$3,(ram_C4C8).w
	nop
	nop
	tst.w	(ram_D27E).w
	beq.w	NullSub
	btst	#2,$63(a3)
	bne.w	NullSub
	btst	#5,(ram_C33A).w
	bne.w	sub_02135E
	cmp.w	#$10,d0	; general form
	beq.w	NullSub

; ----------------------------------------------------------------------
; called from $00E91E, $00EA28, $019652, $019674, $01A01A, $01BFB8, $01C14C, $01C438 (+10 more)
sub_02135E:
	btst	#4,(ram_C350).w
	bne.w	NullSub
	btst	#7,(ram_C33C).w
	bne.w	NullSub
	movem.l	d1/a0/a1,-(sp)
	cmp.w	#$E,d0	; general form
	blt.w	loc_0213A6
	addi.w	#$12C,(ram_B8B4).w
	addq.w	#5,(ram_C4D0).w
	move.w	#$C,-(sp)
	btst	#6,$62(a3)
	beq.w	loc_0213A0
	addi.w	#$1E,(ram_B8BA).w
	move.w	#$B,(sp)
loc_0213A0:
	jsr	(sub_092172).l
loc_0213A6:
	movea.w	#$C3B2,a1
	moveq	#$1F,d1
loc_0213AC:
	tst.w	(a1)+
	dbeq	d1,loc_0213AC
	bne.w	loc_0213F8
	move.b	$53(a3),-(a1)
	move.b	d0,-(a1)
	movea.l	#dat_012158,a0
	adda.w	$0(a0,d0.w),a0
	tst.b	$1(a0)
	beq.w	loc_0213F8
	bmi.w	loc_0213F8
	btst	#6,$62(a3)
	bne.w	loc_0213E6
	bset	#1,(ram_C350).w
	bra.w	loc_0213EC
loc_0213E6:
	bset	#2,(ram_C350).w
loc_0213EC:
	bset	#4,$63(a3)
	beq.w	loc_0213F8
	clr.w	(a1)
loc_0213F8:
	movem.l	(sp)+,d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $01942E
sub_0213FE:
	bsr.w	sub_021ED4
	bsr.w	sub_0218E0
	bsr.w	sub_02140E
	bra.w	sub_021A5A


; ----------------------------------------------------------------------
; called from $021406
sub_02140E:
	btst	#7,(ram_C350).w
	beq.w	loc_021448
	tst.w	(ram_DE96).w
	bmi.w	loc_021448
	subq.w	#1,(ram_DE96).w
	bpl.w	loc_021438
	bset	#1,(ram_C34A).w
	bset	#2,(ram_C34A).w
	bra.w	loc_02146C
loc_021438:
	bclr	#1,(ram_DEA2).w
	beq.w	loc_021448
	jmp	(loc_1E5A50).l
loc_021448:
	btst	#2,(ram_C342).w
	beq.w	loc_0214C8
	btst	#7,(ram_C342).w
	bne.w	loc_0214BA
	tst.w	(ram_C382).w
	bmi.w	loc_0214C8
	subq.w	#1,(ram_C382).w
	bpl.w	loc_0214C6
loc_02146C:
	movem.l	d0-d7/a0-a6,-(sp)
	bclr	#2,(ram_C33E).w
	bclr	#7,(ram_C34A).w
	bsr.w	Text_Print
inl_021480:
	dc.w	loc_021486-inl_021480
	dc.b	$FF,$03,$02,$00
loc_021486:
	moveq	#$1B,d0
	moveq	#$8,d1
	btst	#0,(ram_C34A).w
	beq.w	loc_021498
	move.w	#$C,d1
loc_021498:
	btst	#7,(ram_C350).w
	beq.w	loc_0214A6
	move.w	#$C,d1
loc_0214A6:
	move.l	#$7FF,d2
	jsr	(Text_FillRect).l
	movem.l	(sp)+,d0-d7/a0-a6
	bra.w	loc_0214C6
loc_0214BA:
	jsr	(sub_0281DA).l
	bclr	#7,(ram_C342).w
loc_0214C6:
	rts
loc_0214C8:
	btst	#2,(ram_C33A).w
	beq.w	NullSub
	tst.w	(ram_C3F4).w
	bmi.w	loc_0216DA
	sub.w	d7,(ram_C3F4).w
	bpl.w	NullSub
	movea.l	#ram_C3B2,a0
loc_0214E8:
	tst.w	(a0)+
	bne.s	loc_0214E8
	subq.l	#4,a0
	cmpa.l	#ram_C3B2,a0
	blt.w	loc_021506
	cmpi.b	#$2E,(a0)
	bne.w	loc_021506
	jsr	(sub_00F158).l
loc_021506:
	bclr	#3,(ram_C33A).w
	movea.w	#$C3B2,a0
loc_021510:
	tst.w	(a0)+
	beq.w	NullSub
	clr.w	d0
	move.b	-$2(a0),d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	tst.b	$1(a1)
	beq.s	loc_021510
	bmi.s	loc_021510
	bset	#2,(ram_C33E).w
	bset	#4,(ram_C350).w
	btst	#6,(ram_C33C).w
	bne.w	loc_021556
	move.w	#$96,(ram_BFDE).w
	move.w	#$0,(ram_BFE0).w
	bset	#6,(ram_C33C).w
loc_021556:
	move.w	(ram_B03C).w,d4
	movea.l	#Art_0A5714_Tiles,a2
	bsr.w	sub_020780
	st	(ram_B7C0).w
	movea.w	#$B760,a3
	moveq	#$1A,d0
	bsr.w	sub_01F168
	move.w	#$1C20,$40(a3)
	st	(ram_C454).w
	clr.w	(ram_C452).w
	bsr.w	sub_021A5A
	move.w	#$32,(ram_C452).w
	move.w	#$5,d0
	bsr.w	sub_021B72
	move.w	#$18,(FadeCounter).w
	rts


; ----------------------------------------------------------------------
; called from $0231AE
sub_02159A:
	movem.l	d1-d3/a0,-(sp)
	movea.l	#dat_01256A,a0
	move.w	$0(a0,d0.w),d1
	bmi.w	loc_0215AE
	move.w	d1,d0
loc_0215AE:
	movem.l	(sp)+,d1-d3/a0
	rts


; ----------------------------------------------------------------------
; called from $023160, $0231A4, $0233C0, $023470
sub_0215B4:
	movem.l	d1-d3/a0,-(sp)
	btst	#1,$64(a2)
	beq.w	loc_0215F0
	movem.l	d0,-(sp)
	move.w	#$64,d0
	jsr	(Random).l
	cmp.w	#$32,d0	; general form
	movem.l	(sp)+,d0
	bgt.w	loc_0215F0
	btst	#0,(ram_C33A).w
	bne.w	loc_0215F0
	btst	#3,(ram_C342).w
	beq.w	loc_0215F8
loc_0215F0:
	move.w	#$FFFF,d1
	bra.w	loc_02162C
loc_0215F8:
	movea.l	#dat_012530,a0
	move.w	$0(a0,d0.w),d1
	bmi.w	loc_02162C
	move.w	$52(a2),d2
	movem.w	d0/d1,-(sp)
	move.w	d2,d0
	jsr	(sub_021632).l
	movem.w	(sp)+,d0/d1
	bpl.w	loc_021626
	bclr	#3,(ram_C342).w
	bra.s	loc_0215F0
loc_021626:
	move.w	d1,(ram_D2FC).w
	move.w	d1,d0
loc_02162C:
	movem.l	(sp)+,d1-d3/a0
	rts


; ----------------------------------------------------------------------
; called from $021610
sub_021632:
	movem.l	d1-d3/a1,-(sp)
	tst.w	(ram_D27E).w
	beq.w	loc_0216D4
	bset	#3,(ram_C342).w
	movem.w	d0,-(sp)
	move.w	#$5,d1
	move.w	#$0,d2
	cmp.w	#$5,d0	; general form
	bgt.w	loc_021660
	move.w	#$B,d1
	move.w	#$1,d2
loc_021660:
	move.w	d1,d0
	jsr	(sub_01B3B8).l
	tst.w	d0
	bpl.w	loc_02167C
	movem.w	(sp)+,d0
	bclr	#3,(ram_C342).w
	bra.w	loc_0216CE
loc_02167C:
	move.w	d0,d1
	move.w	(sp)+,d0
	move.w	d0,(ram_D2F2).w
	movea.l	#ram_B060,a1
	move.w	d0,d3
	asl.w	#7,d3
	move.w	#$0,(ram_D2F0).w
	btst	#6,$62(a1,d3.w)
	beq.w	loc_0216A4
	move.w	#$1,(ram_D2F0).w
loc_0216A4:
	move.w	#$0,(ram_D2F6).w
	move.b	$67(a1,d3.w),(ram_D2F7).w
	move.w	d1,(ram_D2F4).w
	asl.w	#7,d1
	move.w	#$0,(ram_D2F8).w
	move.b	$67(a1,d1.w),(ram_D2F9).w
	move.w	#$0,(ram_D2FA).w
	move.b	$67(a3),(ram_D2FB).w
loc_0216CE:
	movem.l	(sp)+,d1-d3/a1
	rts
loc_0216D4:
	move.w	#$FFFF,d1
	bra.s	loc_0216CE
loc_0216DA:
	tst.w	(ram_C452).w
	bpl.w	NullSub
	tst.w	(ram_C454).w
	bpl.w	NullSub
	movem.l	d0/a0-a3,-(sp)
loc_0216EE:
	movea.w	#$C3B2,a0
	tst.w	(a0)+
	beq.w	loc_02186A
loc_0216F8:
	tst.w	(a0)+
	bne.s	loc_0216F8
	subq.w	#4,a0
	bclr	#7,$1(a0)
	bne.w	loc_02172C
	movem.l	a3,-(sp)
	clr.w	d1
	move.b	$1(a0),d1
	asl.w	#7,d1
	movea.w	#$B060,a3
	adda.w	d1,a3
	tst.w	$34(a3)
	movem.l	(sp)+,a3
	bpl.w	loc_0218A0
	clr.w	(a0)
	bra.w	loc_0218A0
loc_02172C:
	clr.w	d0
	move.b	(a0),d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	bclr	#5,(ram_C346).w
	clr.w	d2
	move.b	$1(a1),d2
	beq.w	loc_02184C
	bmi.w	loc_02184C
	cmp.b	#$5,d2	; general form
	bne.w	loc_02175C
	bset	#5,(ram_C346).w
loc_02175C:
	movem.l	d0/d1/a1-a4,-(sp)
	bsr.w	sub_0240B0
	movea.w	#$C642,a4
	adda.w	(ram_C640).w,a4
	cmpi.w	#$EC,(ram_C640).w
	beq.w	loc_02177A
	addq.w	#4,(ram_C640).w
loc_02177A:
	move.w	d0,(a4)+
	move.b	(a0),(a4)+
	clr.w	d1
	move.b	$1(a0),d1
	asl.w	#7,d1
	movea.w	#$B060,a3
	adda.w	d1,a3
	clr.w	d0
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	btst	#6,$62(a3)
	beq.w	loc_0217AC
	bset	#7,-$1(a4)
	move.w	#$8000,d0
	exg	a1,a2
loc_0217AC:
	addq.w	#1,$6(a2)
	add.w	d2,$8(a2)
	move.b	$67(a3),d0
	move.b	d0,(a4)
	move.w	d0,(ram_C4D4).w
	ext.w	d0
	addi.w	#$114,d0
	add.b	d2,$0(a2,d0.w)
	subi.w	#$114,d0
	asl.w	#1,d0
	ext.w	d2
	mulu.w	#$3C,d2
	bset	#13,d2
	tst.w	$6C(a2,d0.w)
	bmi.w	loc_0217EE
	btst	#4,$6C(a2,d0.w)
	beq.w	loc_0217EE
	bset	#12,d2
loc_0217EE:
	cmp.b	#$F0,d2	; general form
	bne.w	loc_0217FA
	bset	#11,d2
loc_0217FA:
	move.w	d2,$6C(a2,d0.w)
	andi.w	#$EFFF,d2
	moveq	#$38,d1
loc_021804:
	subq.w	#2,d1
	bmi.w	loc_02181E
	move.w	$6C(a1,d1.w),d3
	andi.w	#$EFFF,d3
	cmp.w	d3,d2
	bne.s	loc_021804
	btst	#5,(ram_C346).w
	beq.s	loc_021804
loc_02181E:
	movem.l	a0,-(sp)
	lea	$A4(a2),a0
	moveq	#$1A,d1
loc_021828:
	tst.b	(a0)+
	dbmi	d1,loc_021828
	move.b	d0,-$1(a0)
	st	(a0)
	movem.l	(sp)+,a0
	move.w	#$C,d0
	bsr.w	sub_01F172
	movem.l	(sp)+,d0/d1/a1-a4
	bsr.w	sub_021AA8
	bra.w	loc_0218A0
loc_02184C:
	clr.w	(a0)
	btst	#4,(ram_C350).w
	bne.w	loc_0216EE
	btst	#7,(ram_C33C).w
	bne.w	loc_0216EE
	bsr.w	sub_021AA8
	bra.w	loc_0218A0
loc_02186A:
	movea.w	#$C732,a2
	bsr.w	sub_0218A6
	adda.w	#$39E,a2
	bsr.w	sub_0218A6
	bclr	#2,(ram_C33A).w
	movea.w	#$B760,a3
	bclr	#6,(ram_C342).w
	move.w	#$1B,d0
	btst	#3,(ram_C342).w
	beq.w	loc_02189C
	move.w	#$1E,d0
loc_02189C:
	bsr.w	sub_01F172
loc_0218A0:
	movem.l	(sp)+,d0/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $02186E, $021876
sub_0218A6:
	moveq	#$6,d1
	moveq	#$36,d0
loc_0218AA:
	tst.w	$6C(a2,d0.w)
	ble.w	loc_0218D6
	bclr	#5,$6C(a2,d0.w)
	btst	#6,$6C(a2,d0.w)
	bne.w	loc_0218D6
	btst	#4,$6C(a2,d0.w)
	bne.w	loc_0218D6
	cmp.w	#$4,d1	; general form
	beq.w	loc_0218D6
	subq.w	#1,d1
loc_0218D6:
	subq.w	#2,d0
	bpl.s	loc_0218AA
	move.w	d1,$24(a2)
	rts


; ----------------------------------------------------------------------
; called from $021402
sub_0218E0:
	btst	#7,(ram_C33C).w
	bne.w	NullSub
	btst	#4,(ram_C350).w
	bne.w	NullSub
	movea.w	#$C3B2,a0
loc_0218F8:
	tst.w	(a0)+
	beq.w	NullSub
	btst	#2,(ram_C33A).w
	bne.w	loc_02193C
	clr.w	d0
	move.b	-$2(a0),d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	tst.b	$1(a1)
	beq.w	loc_021938
	move.w	(ram_B7C0).w,d0
	bmi.w	loc_021966
	subq.w	#6,d0
	move.b	-$1(a0),d1
	ext.w	d1
	subq.w	#6,d1
	eor.w	d1,d0
	bmi.w	loc_021966
loc_021938:
	bsr.w	sub_02197E
loc_02193C:
	bset	#7,-$1(a0)
	bne.s	loc_0218F8
	clr.w	d0
	move.b	-$2(a0),d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	clr.w	d1
	move.b	(a1),d1
	asl.w	#5,d1
	cmp.w	(ram_C3F4).w,d1
	ble.s	loc_0218F8
	move.w	d1,(ram_C3F4).w
	bra.s	loc_0218F8
loc_021966:
	bset	#3,(ram_C33A).w
	bne.s	loc_0218F8
	addq.w	#4,(ram_C4D0).w
	move.w	#$2C,d0
	bsr.w	sub_021AA8
	bra.w	loc_0218F8


; ----------------------------------------------------------------------
; called from $00C31C, $01DDC6, $021938, $02396A
sub_02197E:
	bset	#0,(ram_C33A).w
	bne.w	loc_021A38
	clr.w	d0
	clr.w	d1
	cmpi.b	#$E,-$2(a0)
	beq.w	loc_0219DC
	move.w	(ram_BFB8).w,d0
	move.w	(ram_BFBA).w,d1
	cmpi.b	#$6,-$2(a0)
	beq.w	loc_0219DC
	move.w	(ram_B760).w,d0
	move.w	(ram_B774).w,d1
	cmpi.b	#$C,-$2(a0)
	bne.w	loc_0219DC
	move.l	a3,-(sp)
	movea.w	#$B060,a3
	move.b	-$1(a0),d1
	ext.w	d1
	asl.w	#7,d1
	adda.w	d1,a3
	move.w	#$258,d1
	btst	#7,$62(a3)
	movea.l	(sp)+,a3
	beq.w	loc_0219DC
	neg.w	d1
loc_0219DC:
	movem.w	d0/d1,-(sp)
	cmp.w	#$51,d0	; general form
	blt.w	loc_0219EC
	move.w	#$51,d0
loc_0219EC:
	cmp.w	#$FFAF,d0	; general form
	bgt.w	loc_0219F8
	move.w	#$FFAF,d0
loc_0219F8:
	cmp.w	#$B0,d1	; general form
	blt.w	loc_021A10
	move.w	#$D8,d1
	move.w	#$51,d0
	tst.w	(sp)
	bpl.w	loc_021A10
	neg.w	d0
loc_021A10:
	cmp.w	#$FF50,d1	; general form
	bgt.w	loc_021A28
	move.w	#$FF28,d1
	move.w	#$51,d0
	tst.w	(sp)
	bpl.w	loc_021A28
	neg.w	d0
loc_021A28:
	move.w	d0,(ram_BFE4).w
	move.w	d1,(ram_BFE6).w
	addq.w	#4,sp
	jsr	(sub_00C8BC).l
loc_021A38:
	clr.w	(ram_C3F4).w
	bset	#2,(ram_C33A).w
	jsr	(sub_0921E8).l
	move.w	#$3,-(sp)
	jsr	(sub_09205A).l
	move.w	#$A,d0
	bra.w	sub_021AA8


; ----------------------------------------------------------------------
; called from $02140A, $021580
sub_021A5A:
	tst.w	(ram_C452).w
	bmi.w	NullSub
	sub.w	d7,(ram_C452).w
	bpl.w	loc_021A6E
	bsr.w	sub_021B04
loc_021A6E:
	cmpi.w	#$4,(ram_C456).w
	bne.w	loc_021A7C
	bsr.w	sub_027E80
loc_021A7C:
	sub.w	d7,(ram_C450).w
	bpl.w	NullSub
	move.w	#$7FFF,(ram_C450).w
	bsr.w	sub_021E2C
	bsr.w	Text_Print
inl_021A92:
	dc.w	loc_021A98-inl_021A92
	dc.b	$BF,$11,$0B,$00
loc_021A98:
	bsr.w	sub_0284DA
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bra.w	Text_Print_Worker


; ----------------------------------------------------------------------
; called from $021844, $021862, $021976, $021A56
sub_021AA8:
	move.w	d0,(ram_C456).w
	cmp.w	#$3C,d0	; general form
	blt.w	loc_021AB6
	rts
loc_021AB6:
	clr.w	(ram_C454).w
	bsr.w	sub_021BF4
	cmp.w	#$E,d0	; general form
	bne.w	loc_021ACA
	bsr.w	sub_0282C8
loc_021ACA:
	btst	#0,(ram_C34A).w
	beq.w	loc_021AE4
	btst	#3,(ram_C34A).w
	beq.w	loc_021AE4
	jsr	(sub_1D0C7E).l
loc_021AE4:
	move.w	#$7FFF,(ram_C450).w
	btst	#7,(ram_C33C).w
	beq.w	sub_021B04
	btst	#4,(ram_C350).w
	beq.w	sub_021B04
	move.w	#$3C,(ram_C450).w

; ----------------------------------------------------------------------
; called from $021A6A, $021AF0, $021AFA
sub_021B04:
	movem.l	d0-d2/a0/a1,-(sp)
	moveq	#$40,d0
	tst.w	(ram_C454).w
	bmi.w	loc_021B68
	move.w	(ram_C454).w,d0
	addq.w	#2,(ram_C454).w
	move.w	(ram_C456).w,d1
	movea.l	#dat_012158,a0
	adda.w	$0(a0,d1.w),a0
	addq.w	#2,a0
	adda.w	(a0),a0
	move.w	$0(a0,d0.w),d0
	bpl.w	loc_021B3A
	neg.w	d0
	st	(ram_C454).w
loc_021B3A:
	clr.w	d1
	move.b	d0,d1
	asl.w	#3,d1
	move.w	d1,(ram_C452).w
	btst	#0,(ram_C34A).w
	beq.w	loc_021B66
	btst	#3,(ram_C34A).w
	beq.w	loc_021B66
	move.w	d0,-(sp)
	move.w	(ram_C452).w,d0
	add.w	d0,d0
	move.w	d0,(ram_C452).w
	move.w	(sp)+,d0
loc_021B66:
	lsr.w	#8,d0
loc_021B68:
	bsr.w	sub_021B72
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $01D544, $02158E, $021B68
sub_021B72:
	movem.l	d0-d2/a0/a1,-(sp)
	cmp.w	#$40,d0	; general form
	beq.w	loc_021BC0
	mulu.w	#$70,d0
	movea.l	#Art_RefereeCutscene,a0
	btst	#4,(ram_C350).w
	beq.w	loc_021B98
	movea.l	#Art_0A5714,a0
loc_021B98:
	adda.l	$4(a0),a0
	addq.w	#4,a0
	adda.w	d0,a0
	movea.w	#$C458,a1
	move.w	(ram_B03C).w,d2
	ori.w	#$8000,d2
	moveq	#$37,d0
loc_021BAE:
	move.w	(a0)+,(a1)
	add.w	d2,(a1)+
	dbra	d0,loc_021BAE
	bset	#1,(ram_C33E).w
	bra.w	loc_021BEE
loc_021BC0:
	btst	#7,(ram_C33C).w
	bne.w	loc_021BE8
	btst	#4,(ram_C350).w
	bne.w	loc_021BE8
	movea.w	#$C458,a1
	moveq	#$37,d0
loc_021BDA:
	move.w	#$7FF,(a1)+
	dbra	d0,loc_021BDA
	bset	#1,(ram_C33E).w
loc_021BE8:
	moveq	#-$1,d0
	bsr.w	sub_021BF4
loc_021BEE:
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $021ABA, $021BEA, $0281F8, $1D098A, $1E5A58, $1E5E8E, $1E655E
sub_021BF4:
	movem.l	d0-d2/a1/a2,-(sp)
	btst	#7,(ram_C33C).w
	bne.w	loc_021C7A
	btst	#4,(ram_C350).w
	bne.w	loc_021C7A
	tst.w	d0
	bpl.w	loc_021C2C
	bsr.w	Text_Print
inl_021C16:
	dc.w	loc_021C1C-inl_021C16
	dc.b	$BF,$00,$0A,$00
loc_021C1C:
	moveq	#$D,d0
	moveq	#$3,d1
	move.w	#$7FF,d2
	bsr.w	Text_FillRect
	bra.w	loc_021DC2
loc_021C2C:
	bsr.w	Text_Print
inl_021C30:
	dc.w	loc_021C36-inl_021C30
	dc.b	$BF,$05,$0A,$00
loc_021C36:
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	addq.w	#2,a1
	move.w	(a1),d0
	subq.w	#2,d0
	beq.w	loc_021DC2
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bpl.w	loc_021C58
	clr.w	(TextX).w
loc_021C58:
	move.w	(a1),d0
	tst.b	-$1(a1,d0.w)
	bne.w	loc_021C64
	subq.w	#1,d0
loc_021C64:
	moveq	#$3,d1
	bsr.w	Text_PrintDigitsBig
	subq.w	#2,(TextY).w
	addq.w	#1,(TextX).w
	bsr.w	Text_Print_Worker
	bra.w	loc_021DC2
loc_021C7A:
	tst.w	d0
	bmi.w	loc_021DC2
	cmpi.w	#$3E8,(ram_BF16).w
	bne.w	loc_021C94
	cmpi.w	#$3E8,(ram_BF18).w
	beq.w	loc_021C9A
loc_021C94:
	jsr	(sub_00F158).l
loc_021C9A:
	move.w	d0,-(sp)
	jsr	(Text_Print).l
inl_021CA2:
	dc.w	loc_021CA8-inl_021CA2
	dc.b	$BF,$0B,$02,$00
loc_021CA8:
	move.w	#$14,d0
	move.w	#$8,d1
	jsr	(Text_PrintDigitsBig).l
	jsr	(Text_PrintScoreboardAlt).l
inl_021CBC:
	dc.w	loc_021CD6-inl_021CBC
	dc.b	$F8,$04,$01,$0C,$03
	dc.b	"                  ",0
loc_021CD6:
	move.w	#$15,(TextX).w
	move.w	#$3,(TextY).w
	move.w	(sp)+,d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	addq.w	#2,a1
	move.w	(a1),d0
	lsr.w	#1,d0
	sub.w	d0,(TextX).w
	bsr.w	Text_PrintScoreboardAlt_Worker
	movea.l	#ram_C3B2,a1
loc_021D02:
	tst.w	(a1)+
	bne.s	loc_021D02
	move.w	-$4(a1),d0
	move.w	d0,-(sp)
	andi.w	#$7F,d0
	movea.l	#ram_C732,a2
	cmp.w	#$6,d0	; general form
	blt.w	loc_021D24
	movea.l	#ram_CAD0,a2
loc_021D24:
	asl.w	#7,d0
	movea.l	#ram_B060,a1
	adda.w	d0,a1
	clr.w	d0
	move.b	$67(a1),d0
	jsr	(sub_028540).l
	jsr	(Text_Print).l
inl_021D40:
	dc.w	loc_021D46-inl_021D40
	dc.b	$BF,$0C,$06,$00
loc_021D46:
	cmpi.b	#$20,$2(a1)
	beq.w	loc_021D54
	addq.w	#1,(TextX).w
loc_021D54:
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_021D60:
	dc.w	loc_021D6C-inl_021D60
	dc.b	$BF,$11,$05
	dc.b	"penalty"
loc_021D6C:
	move.w	#$D,(TextX).w
	movea.l	$1E(a2),a1
	adda.w	$4(a1),a1
	adda.w	(a1),a1
	jsr	(Text_Print_Worker).l
	jsr	(Text_Print).l
inl_021D88:
	dc.w	loc_021D8C-inl_021D88
	dc.b	$2E,$00
loc_021D8C:
	jsr	(Text_Print).l
inl_021D92:
	dc.w	loc_021D98-inl_021D92
	dc.b	$BF,$0D,$07,$00
loc_021D98:
	move.w	(sp)+,d0
	lsr.w	#8,d0
	andi.w	#$FF,d0
	movea.l	#dat_012158,a1
	adda.w	$0(a1,d0.w),a1
	move.w	(a1),d0
	andi.w	#$FF,d0
	movea.l	#dat_021DC8,a1
	jsr	(List_Skip).l
	jsr	(Text_Print_Worker).l
loc_021DC2:
	movem.l	(sp)+,d0-d2/a1/a2
	rts
dat_021DC8:
	dc.b	$00,$10
	dc.b	"penalty error ",0
	dc.b	$10
	dc.b	"1 minute minor",0
	dc.b	$10
	dc.b	"2 minute minor",0
	dc.b	$10
	dc.b	"3 minute minor",0
	dc.b	$14
	dc.b	"4 minute db minor",0
	dc.b	$00,$10
	dc.b	"5 minute major"


; ----------------------------------------------------------------------
; called from $021A8A
sub_021E2C:
	jsr	(Text_Print).l
inl_021E32:
	dc.w	loc_021E38-inl_021E32
	dc.b	$BF,$0B,$02,$00
loc_021E38:
	move.w	#$14,d0
	move.w	#$8,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	rts


; ----------------------------------------------------------------------
; called from $023FCA
sub_021E4C:
	movem.l	d0-d2/a0,-(sp)
	cmpi.w	#$6,$24(a1)
	bne.w	loc_021E60
	jsr	(sub_021EC6).l
loc_021E60:
	move.w	$24(a2),d2
	cmp.w	$24(a1),d2
	ble.w	loc_021EC0
	lea	$A4(a1),a0
loc_021E70:
	clr.w	d2
	move.b	(a0)+,d2
	bmi.w	loc_021EC0
	btst	#6,$6C(a1,d2.w)
	bne.s	loc_021E70
	btst	#3,$6C(a1,d2.w)
	beq.w	loc_021E9C
	cmpi.b	#$78,$6D(a1,d2.w)
	bcs.w	loc_021E9C
	move.b	#$78,$6D(a1,d2.w)
	bra.s	loc_021E70
loc_021E9C:
	clr.w	$6C(a1,d2.w)
	jsr	(sub_021FCA).l
	bset	#0,(ram_C350).w
	addq.w	#1,$24(a1)
	addq.w	#1,$2(a2)
	bset	#0,(ram_C762).w
	bset	#0,(ram_CB00).w
loc_021EC0:
	movem.l	(sp)+,d0-d2/a0
	rts


; ----------------------------------------------------------------------
; called from $019630, $021E5A
sub_021EC6:
	moveq	#$1F,d0
	movea.w	#$C3B2,a0
loc_021ECC:
	clr.w	(a0)+
	dbra	d0,loc_021ECC
	rts


; ----------------------------------------------------------------------
; called from $0213FE
sub_021ED4:
	bclr	#6,(ram_C340).w
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	sub.w	d7,(ram_C3F6).w
	bpl.w	NullSub
	addi.w	#$18,(ram_C3F6).w
	bset	#6,(ram_C340).w
	bsr.w	sub_021FDA
	jsr	(sub_1D1002).l
	movea.w	#$C732,a2
	bsr.w	sub_021F0E
	adda.w	#$39E,a2

; ----------------------------------------------------------------------
; called from $021F06
sub_021F0E:
	lea	$A4(a2),a0
	movea.w	#$BFF4,a1
	moveq	#$2,d1
	moveq	#$2,d3
loc_021F1A:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	loc_021F50
	btst	#6,$6C(a2,d0.w)
	bne.w	loc_021FA4
	subq.w	#1,d1
	bmi.s	loc_021F1A
	move.w	d0,(a1)+
	movem.w	d1,-(sp)
	subq.w	#1,$6C(a2,d0.w)
	move.w	$6C(a2,d0.w),d1
	andi.w	#$7FF,d1
	movem.w	(sp)+,d1
	bne.w	loc_021F4E
	bsr.w	sub_021FCA
loc_021F4E:
	bra.s	loc_021F1A
loc_021F50:
	move.w	(ram_BFF4).w,d0
	cmp.w	#$1,d1	; general form
	beq.w	sub_021F76
	tst.w	d1
	bne.w	loc_021F6A
	bsr.w	sub_021F76
	bra.w	loc_021F72
loc_021F6A:
	cmp.w	#$FFFF,d1	; general form
	bne.w	NullSub
loc_021F72:
	move.w	(ram_BFF6).w,d0

; ----------------------------------------------------------------------
; called from $021F58, $021F62
sub_021F76:
	move.w	$6C(a2,d0.w),d1
	bmi.w	NullSub
	andi.w	#$7FF,d1
	cmp.w	#$5,d1	; general form
	bgt.w	NullSub
	move.w	#$1,-(sp)
	tst.w	d1
	bne.w	loc_021F9C
	bsr.w	sub_022010
	move.w	#$2,(sp)
loc_021F9C:
	jsr	(sub_09205A).l
	rts
loc_021FA4:
	subq.w	#1,$6C(a2,d0.w)
	btst	#3,$6C(a2,d0.w)
	beq.w	loc_021F1A
	btst	#4,$6C(a2,d0.w)
	bne.w	loc_021FC6
	move.w	#$1000,$6C(a2,d0.w)
	bra.w	sub_021FCA
loc_021FC6:
	clr.w	$6C(a2,d0.w)

; ----------------------------------------------------------------------
; called from $021EA0, $021F4A, $021FC2
sub_021FCA:
	moveq	#-$1,d2
loc_021FCC:
	addq.w	#1,d2
	move.b	$0(a0,d2.w),-$1(a0,d2.w)
	bpl.s	loc_021FCC
	subq.w	#1,a0
	rts


; ----------------------------------------------------------------------
; called from $021EF8
sub_021FDA:
	moveq	#$0,d1
	move.w	(ram_B774).w,d0
	cmp.w	#$76,d0	; general form
	bgt.w	loc_021FF8
	move.l	#loc_00039E,d1
	neg.w	d0
	cmp.w	#$76,d0	; general form
	blt.w	NullSub
loc_021FF8:
	btst	#1,(ram_C33A).w
	beq.w	loc_022006
	eori.w	#$39E,d1
loc_022006:
	movea.w	#$C732,a2
	addq.w	#1,$A(a2,d1.w)
	rts


; ----------------------------------------------------------------------
; called from $021F94
sub_022010:
	movem.l	d0-d3/a0-a3,-(sp)
	movea.w	$22(a2),a3
	suba.w	#$80,a3
loc_02201C:
	adda.w	#$80,a3
	tst.w	$34(a3)
	bpl.s	loc_02201C
	move.w	d0,d3
	lsr.w	#1,d3
	move.w	$24(a2),d1
	addq.w	#1,$24(a2)
	bset	#0,(ram_C762).w
	bset	#0,(ram_CB00).w
	movea.l	#dat_028A90,a0
	tst.w	$26(a2)
	bpl.w	loc_02204E
	addq.w	#1,a0
loc_02204E:
	clr.w	$34(a3)
	move.b	$0(a0,d1.w),$35(a3)
	bsr.w	sub_025428
	bsr.w	sub_025470
	bset	#2,$63(a3)
	movem.l	(sp)+,d0-d3/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $0221A0
sub_02206C:
	clr.w	d0
	clr.w	d3
	lea	$A4(a2),a0
loc_022074:
	clr.w	d2
	move.b	(a0)+,d2
	bmi.w	loc_022092
	move.w	$6C(a2,d2.w),d2
	btst	#14,d2
	bne.s	loc_022074
	andi.w	#$FF,d2
	sub.w	d3,d2
	add.w	d2,d0
	move.w	d2,d3
	bra.s	loc_022074
loc_022092:
	cmpi.w	#$6,$24(a3)
	beq.w	NullSub
	sub.w	d3,d0
	lea	$A4(a3),a0
	clr.w	d2
loc_0220A4:
	move.b	(a0)+,d2
	bmi.w	NullSub
	btst	#6,$6C(a3,d2.w)
	bne.s	loc_0220A4
	cmp.w	$6C(a3,d2.w),d0
	blt.w	NullSub
	add.w	d3,d0
	rts
loc_0220BE:
	btst	#7,(ram_C33A).w
	bne.w	NullSub
	btst	#1,(ram_C34A).w
	bne.w	NullSub
	btst	#4,(ram_C350).w
	bne.w	NullSub
	btst	#2,(ram_C358).w
	bne.w	NullSub
	btst	#1,(ram_C762).w
	bne.w	NullSub
	btst	#1,(ram_CB00).w
	bne.w	NullSub
	movea.w	#$C732,a2
	lea	$39E(a2),a3
	move.w	$24(a2),d0
	sub.w	$24(a3),d0
	beq.w	sub_022202
	bpl.w	loc_02212A
	btst	#6,(ram_C33E).w
	bne.w	loc_022140
	bsr.w	sub_022202
	bset	#6,(ram_C33E).w
	bra.w	loc_022140
loc_02212A:
	exg	a2,a3
	btst	#6,(ram_C33E).w
	beq.w	loc_022140
	bsr.w	sub_022202
	bclr	#6,(ram_C33E).w
loc_022140:
	btst	#5,(ram_C33E).w
	beq.w	loc_022154
	bclr	#3,(ram_C358).w
	bne.w	loc_022162
loc_022154:
	bset	#5,(ram_C33E).w
	bne.w	loc_02217C
	addq.w	#1,$4(a3)
loc_022162:
	movem.l	d0/d1/a3,-(sp)
	bsr.w	sub_022238
	movem.l	(sp)+,d0/d1/a3
	cmpa.w	#$C732,a3
	bne.w	loc_02217A
loc_022176:
	bra.w	loc_02217C
loc_02217A:
	bra.s	loc_022176
loc_02217C:
	bclr	#7,(ram_C356).w
	beq.w	loc_02218A
	bsr.w	sub_022238
loc_02218A:
	jsr	(Text_Print).l
inl_022190:
	dc.w	loc_022196-inl_022190
	dc.b	$BF,$17,$19,$00
loc_022196:
	jsr	(Text_PrintScoreboard).l
inl_02219C:
	dc.w	loc_0221A0-inl_02219C
	dc.b	$2B,$00
loc_0221A0:
	bsr.w	sub_02206C
	bsr.w	sub_020DD4
	cmpi.b	#$20,$3(a1)
	bne.w	loc_0221B8
	move.b	#$7A,$3(a1)
loc_0221B8:
	bsr.w	Text_PrintScoreboard_Worker
	jsr	(Text_PrintScoreboard).l
inl_0221C2:
	dc.w	loc_0221C6-inl_0221C2
	dc.b	$2A,$00
loc_0221C6:
	movea.l	$1E(a3),a0
	movea.w	#$BFF4,a3
	move.w	#$2,(a3)
	bsr.w	Text_AppendInline
inl_0221D6:
	dc.w	loc_0221DC-inl_0221D6
	dc.b	$BF,$14,$19,$00
loc_0221DC:
	adda.w	$4(a0),a0
	adda.w	(a0),a0
	movea.l	a0,a1
	bsr.w	Text_AppendInline_Worker
	movea.w	a3,a1
	bsr.w	Text_Print_Worker
	bsr.w	Text_Print
inl_0221F2:
	dc.w	loc_0221FA-inl_0221F2
	dc.b	$BF,$14,$1A,$50,$50,$00
loc_0221FA:
	bset	#3,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $02210A, $02211C, $022136
sub_022202:
	bclr	#5,(ram_C33E).w
	beq.w	NullSub
	bsr.w	sub_022218
	bset	#3,(VideoFlags).w
	rts


; ----------------------------------------------------------------------
; called from $012612, $02220C, $027EA4, $1E2F16
sub_022218:
	jsr	(Text_Print).l
inl_02221E:
	dc.w	loc_022224-inl_02221E
	dc.b	$BF,$13,$18,$00
loc_022224:
	move.w	#$C,d0
	move.w	#$4,d1
	move.w	#$7FF,d2
	jsr	(Text_FillRect).l
	rts


; ----------------------------------------------------------------------
; called from $022166, $022186
sub_022238:
	jsr	(Text_Print).l
inl_02223E:
	dc.w	loc_022244-inl_02223E
	dc.b	$BF,$13,$18,$00
loc_022244:
	move.w	#$C,d0
	move.w	#$4,d1
	jmp	(Text_PrintDigitsBig).l


; ----------------------------------------------------------------------
; called from $00C11A, $00C408, $019892, $01E0BE, $1E53F4
sub_022252:
	movem.l	d0-d7/a0-a6,-(sp)
	bclr	#7,(ram_C33C).w
	move.w	#$3E8,(ram_BD32).w
	jsr	(sub_019EE8).l
	bsr.w	sub_02698A
	btst	#0,(ram_C33C).w
	bne.w	loc_022290
	bsr.w	Text_Print
inl_02227A:
	dc.w	loc_022280-inl_02227A
	dc.b	$FF,$00,$00,$00
loc_022280:
	moveq	#$20,d0
	moveq	#$1C,d1
	move.w	#$7FF,d2
	bsr.w	Text_FillRect
	bsr.w	sub_022296
loc_022290:
	movem.l	(sp)+,d0-d7/a0-a6
	rts


; ----------------------------------------------------------------------
; called from $00C20E, $012870, $019904, $01D0E0, $01E8A8, $02228C, $023FD4, $1DD0DE
sub_022296:
	rts


; ----------------------------------------------------------------------
; called from $1E2F1C
sub_022298:
	bsr.w	Text_Print
inl_02229C:
	dc.w	loc_0222A2-inl_02229C
	dc.b	$BF,$01,$15,$00
loc_0222A2:
	movea.l	#Art_16D16A,a1
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	clr.w	d0
	clr.w	d1
	move.w	(a1),d2
	move.w	$2(a1),d3
	move.w	(ram_B02C).w,d4
	clr.w	d5
	bra.w	TileMap_Draw

	dc.w	$48E7,$FFF0,$08F8,$0003,$BFB4,$61C6,$6100,$E90C
	dc.w	$0006,$BE14,$0800,$347C,$C732,$6100,$001A,$6100
	dc.w	$E8FA,$0006,$BE05,$0800,$347C,$CAD0,$6100,$0008
	dc.w	$4CDF,$0FFF,$4E75


; ----------------------------------------------------------------------
sub_0222FA:
	lea	$A4(a2),a0
loc_0222FE:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	sub_022314
	btst	#6,$6C(a2,d0.w)
	bne.s	loc_0222FE
	bsr.w	sub_02232E
	bra.s	loc_0222FE


; ----------------------------------------------------------------------
; called from $022302
sub_022314:
	lea	$A4(a2),a0
loc_022318:
	clr.w	d0
	move.b	(a0)+,d0
	bmi.w	NullSub
	btst	#6,$6C(a2,d0.w)
	beq.s	loc_022318
	bsr.w	sub_02232E
	bra.s	loc_022318


; ----------------------------------------------------------------------
; called from $02230E, $022328
sub_02232E:
	cmpi.w	#$A,(TextY).w
	bhi.w	NullSub
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
	bsr.w	sub_02872E
	movea.w	#$BFF4,a1
	move.w	#$4,(a1)
	bsr.w	Text_Print_Worker
	move.w	d2,d0
	bsr.w	sub_020DD4
	bsr.w	Text_Print_Worker
	move.w	(sp)+,(TextX).w
	addq.w	#1,(TextY).w
	rts


; ----------------------------------------------------------------------
; called from $012696
sub_022382:
	movem.l	d0-d5/a0-a2,-(sp)
	bsr.w	sub_0223D0
	move.w	(TextAttr).w,-(sp)
	move.w	#$8000,(TextAttr).w
	ext.l	d0
	divu.w	#$100,d0
	cmp.w	#$F,d0	; general form
	bls.w	loc_0223A4
	moveq	#$F,d0
loc_0223A4:
	moveq	#$F,d1
	sub.w	d0,d1
	clr.w	d0
	movea.l	#Art_16CE5C,a1
	adda.l	$4(a1),a1
	movea.w	#$772,a2
	move.w	(a1),d2
	moveq	#$1,d3
	move.w	(ram_B022).w,d4
	moveq	#$0,d5
	bsr.w	TileMap_Draw
	move.w	(sp)+,(TextAttr).w
	movem.l	(sp)+,d0-d5/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $01E5AA, $01E5B4, $01E604, $01E668, $022386
sub_0223D0:
	movem.l	d1-d5/a0-a3,-(sp)
	lea	$184(a2),a1
	asl.w	#3,d0
	adda.w	d0,a1
	clr.l	d0
	clr.w	d1
	movea.l	#dat_028A90,a0
	move.w	$24(a2),d4
	bra.w	loc_022406
loc_0223EE:
	clr.w	d5
	move.b	$0(a0,d4.w),d5
	beq.w	loc_022406
	clr.w	d3
	move.b	$0(a1,d5.w),d3
	asl.w	#1,d3
	addq.w	#1,d1
	add.w	$32(a2,d3.w),d0
loc_022406:
	dbra	d4,loc_0223EE
	divu.w	d1,d0
	movem.l	(sp)+,d1-d5/a0-a3
	rts


; ----------------------------------------------------------------------
; called from $01D0CA
sub_022412:
	movem.l	d1-d3/a0,-(sp)
	clr.l	d0
	clr.w	d1
	moveq	#$5,d2
	movea.w	$22(a2),a0
loc_022420:
	tst.w	$34(a0)
	ble.w	loc_022436
	clr.w	d3
	move.b	$67(a0),d3
	add.w	d3,d3
	add.w	$34(a2,d3.w),d0
	addq.w	#1,d1
loc_022436:
	adda.w	#$80,a0
	dbra	d2,loc_022420
	tst.w	d1
	beq.w	loc_022446
	divu.w	d1,d0
loc_022446:
	movem.l	(sp)+,d1-d3/a0
	rts


; ----------------------------------------------------------------------
; called from $023CAC, $023DE4, $023FC6, $024B90, $024E02
sub_02244C:
	btst	#0,(ram_C33A).w
	bne.w	NullSub
	btst	#4,(ram_C33A).w
	bne.w	NullSub
	bclr	#4,(ram_C33E).w
	bne.w	loc_0224E2
	btst	#0,(ram_C344).w
	beq.w	NullSub
	btst	#7,(ram_C350).w
	bne.w	NullSub
	bclr	#3,(ram_C34E).w
	bne.w	loc_022492
	bset	#3,(ram_C34E).w
	bra.w	NullSub
loc_022492:
	movem.l	d0/d1/a1-a3,-(sp)
	move.l	a4,-(sp)
	movea.l	#ram_C4D2,a4
	adda.w	(ram_C4D6).w,a4
	movea.l	#ram_C732,a2
	btst	#7,$2(a4)
	beq.w	loc_0224B6
	adda.w	#$39E,a2
loc_0224B6:
	clr.w	d0
	move.b	$3(a4),d0
	movea.l	(sp)+,a4
	movea.w	$22(a2),a2
	move.w	#$5,d1
loc_0224C6:
	cmp.b	$67(a2),d0
	beq.w	loc_0224DA
	adda.w	#$80,a2
	dbra	d1,loc_0224C6
	bra.w	loc_022560
loc_0224DA:
	move.w	$52(a2),d0
	bra.w	loc_0224F6
loc_0224E2:
	movem.l	d0/d1/a1-a3,-(sp)
	addi.w	#$C8,(ram_B8B4).w
	addi.w	#$14,(ram_B8BA).w
	move.w	(ram_BF0C).w,d0
loc_0224F6:
	asl.w	#7,d0
	movea.w	#$B060,a3
	adda.w	d0,a3
	bsr.w	sub_022566
	addq.w	#1,(a2)
	btst	#5,(ram_C33E).w
	beq.w	loc_022532
	btst	#6,(ram_C33E).w
	bne.w	loc_02252A
	btst	#6,$62(a3)
	bne.w	loc_022532
loc_022522:
	addq.w	#1,$38E(a2)
	bra.w	loc_022532
loc_02252A:
	btst	#6,$62(a3)
	bne.s	loc_022522
loc_022532:
	move.l	a2,-(sp)
	move.w	(ram_C4C8).w,d0
	add.w	d0,d0
	adda.w	d0,a2
	addq.w	#1,$384(a2)
	movea.l	(sp)+,a2
	clr.w	d0
	move.b	$67(a3),d0
	addi.w	#$F8,d0
	addq.b	#1,$0(a2,d0.w)
	move.w	$26(a1),d0
	bmi.w	loc_022560
	addi.w	#$F8,d0
	addq.b	#1,$0(a1,d0.w)
loc_022560:
	movem.l	(sp)+,d0/d1/a1-a3
	rts


; ----------------------------------------------------------------------
; called from $0125B8, $012824, $0135BE, $01AFD0, $0224FE, $029EDC
sub_022566:
	movea.w	#$C732,a2
	lea	$39E(a2),a1
	btst	#6,$62(a3)
	beq.w	NullSub
	exg	a1,a2
	rts


; ----------------------------------------------------------------------
; called from $022668
sub_02257C:
	bsr.w	sub_0253C4
	movea.w	#$C732,a2
	lea	$39E(a2),a3
	bsr.w	sub_02258E
	exg	a2,a3

; ----------------------------------------------------------------------
; called from $022588
sub_02258E:
	bsr.w	sub_0225E4
	clr.w	$16(a3)
	tst.w	(ram_D280).w
	bne.w	NullSub
	move.w	$24(a3),d0
	sub.w	$24(a2),d0
	beq.w	NullSub
	move.w	#$3,$16(a3)
	tst.w	d0
	bpl.w	NullSub
	move.w	#$5,$16(a3)
	rts


; ----------------------------------------------------------------------
; called from $019FF4, $019FFE
sub_0225BE:
	moveq	#$36,d0
loc_0225C0:
	cmpi.w	#$FFFD,$6C(a2,d0.w)
	bne.w	loc_0225D8
	cmpi.w	#$FFFC,$6C(a2,d0.w)
	bne.w	loc_0225D8
	bra.w	loc_0225DE
loc_0225D8:
	move.w	#$1000,$34(a2,d0.w)
loc_0225DE:
	subq.w	#2,d0
	bpl.s	loc_0225C0
	rts


; ----------------------------------------------------------------------
; called from $02258E
sub_0225E4:
	moveq	#$36,d0
loc_0225E6:
	cmpi.w	#$FFFC,$6C(a2,d0.w)
	beq.w	loc_022606
	move.w	#$1000,$34(a2,d0.w)
	cmpi.w	#$FFFD,$6C(a2,d0.w)
	bne.w	loc_022606
	move.w	#$FFFE,$6C(a2,d0.w)
loc_022606:
	subq.w	#2,d0
	bpl.s	loc_0225E6
	rts


; ----------------------------------------------------------------------
; called from $026C8E
sub_02260C:
	cmpi.w	#$4,(ram_C4C8).w
	bne.w	loc_022668
	move.w	#$0,(ram_C4CA).w
	jsr	(sub_1D0324).l
	btst	#7,(SysFlags).w
	beq.w	loc_022668
	movem.l	a2,-(sp)
	jsr	(sub_015060).l
	cmpa.l	#$0,a2
	beq.w	loc_022664
	move.b	(ram_C73F).w,$2(a2)
	move.b	(ram_CADD).w,$3(a2)
	jsr	(sub_014E2A).l
	jsr	(sub_014832).l
	bclr	#6,(SysFlags).w
	jsr	(SRAM_UpdateChecksum).l
loc_022664:
	movem.l	(sp)+,a2
loc_022668:
	bsr.w	sub_02257C
	moveq	#$F,d0
	movea.w	#$B060,a0
loc_022672:
	clr.w	(a0)
	adda.w	#$80,a0
	dbra	d0,loc_022672
	move.w	(ram_C4C8).w,d0
	tst.w	(ram_D270).w
	beq.w	loc_02268A
	addq.w	#5,d0
loc_02268A:
	asl.w	#2,d0
	lea	ptrs_022700(pc),a0
	movea.l	$0(a0,d0.w),a0
	btst	#0,(ram_C34A).w
	beq.w	loc_0226A4
	movea.l	#dat_0293AA,a0
loc_0226A4:
	btst	#7,(ram_C350).w
	beq.w	loc_0226B4
	movea.l	#dat_028D1A,a0
loc_0226B4:
	bset	#0,(ram_C33C).w
	movea.l	#sub_019924,a1
	jsr	(sub_019980).l
	move.w	#$A8C,(ram_DDE8).w
loc_0226CC:
	tst.w	(ram_D294).w
	bne.w	loc_0226DC
	subq.w	#1,(ram_DDE8).w
	bmi.w	loc_0226F6
loc_0226DC:
	jsr	(sub_019BF0).l
	jsr	(sub_0202D2).l
	jsr	(Joypad_Repeat).l
	jsr	(sub_0199B8).l
	bne.s	loc_0226CC
loc_0226F6:
	jsr	(sub_01FFA2).l
	rts

	dc.b	$4E,$75

ptrs_022700:
	dc.l	dat_02942E
	dc.l	dat_0295AE
	dc.l	dat_0295AE
	dc.l	dat_0295AE
	dc.l	dat_0296DA
	dc.l	dat_0294E2
	dc.l	dat_0295AE
	dc.l	dat_0295AE
	dc.l	dat_0295AE
	dc.l	dat_0297A6


; ----------------------------------------------------------------------
; called from $01911C
sub_022728:
	cmpi.w	#$1,(ram_CFD6).w
	bgt.w	NullSub
	bsr.w	sub_027B42
	movea.w	#$CF50,a0
	moveq	#$10,d0
	mulu.w	d1,d0
	adda.w	d0,a0
loc_022740:
	cmp.w	(ram_CFD0).w,d1
	beq.w	loc_022768
	btst	#2,$E(a0)
	bne.w	loc_022768
	clr.w	$8(a0)
	moveq	#$3,d0
	bsr.w	Random
	bra.w	loc_022764
loc_022760:
	bsr.w	sub_0227AA
loc_022764:
	dbra	d0,loc_022760
loc_022768:
	suba.w	#$10,a0
	dbra	d1,loc_022740
	rts


; ----------------------------------------------------------------------
; called from $026C7C
sub_022772:
	bsr.w	sub_027B42
	move.w	d1,(ram_D042).w
	movea.w	#$CF50,a0
	moveq	#$10,d0
	mulu.w	d1,d0
	adda.w	d0,a0
loc_022784:
	cmp.w	(ram_CFD0).w,d1
	beq.w	loc_0227A0
	bclr	#1,$E(a0)
	btst	#2,$E(a0)
	bne.w	loc_0227A0
	bsr.w	sub_0227AA
loc_0227A0:
	suba.w	#$10,a0
	dbra	d1,loc_022784
	rts


; ----------------------------------------------------------------------
; called from $022760, $02279C
sub_0227AA:
	cmpi.w	#$4,$8(a0)
	bge.w	NullSub
	movem.l	d0/d1/a0/a1,-(sp)
	cmpi.w	#$3,$8(a0)
	bne.w	loc_0227F0
	move.w	#$5,$8(a0)
	move.w	$A(a0),d0
	sub.w	$C(a0),d0
	cmp.w	#$1,d0	; general form
	bgt.w	loc_022810
	cmp.w	#$FFFF,d0	; general form
	blt.w	loc_022810
	move.w	#$3,$8(a0)
	bset	#1,$E(a0)
	bra.w	loc_022810
loc_0227F0:
	addq.w	#1,$8(a0)
	move.w	(a0),d0
	move.w	$2(a0),d1
	bsr.w	sub_022816
	add.w	d0,$A(a0)
	move.w	$2(a0),d0
	move.w	(a0),d1
	bsr.w	sub_022816
	add.w	d0,$C(a0)
loc_022810:
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $0227FA, $022808
sub_022816:
	asl.w	#2,d0
	movea.w	#$7FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_02282A
	movea.l	#RosterTable,a1
loc_02282A:
	movea.l	$0(a1,d0.w),a1
	adda.w	$8(a1),a1
	move.b	(a1),d0
	andi.w	#$70,d0
	lsr.w	#1,d0
	lea	dat_022888(pc),a1
	move.l	$0(a1,d0.w),(ram_D24C).w
	move.l	$4(a1,d0.w),(ram_D250).w
	asl.w	#2,d1
	movea.w	#$7FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_02285E
	movea.l	#RosterTable,a1
loc_02285E:
	movea.l	$0(a1,d1.w),a1
	adda.w	$8(a1),a1
	move.b	(a1),d0
	andi.w	#$7,d0
	asl.w	#3,d0
	lea	dat_022888(pc),a1
	move.l	$0(a1,d0.w),d1
	add.l	d1,(ram_D24C).w
	move.l	$4(a1,d0.w),d1
	add.l	d1,(ram_D250).w
	moveq	#$4,d0
	bra.w	loc_01FF24
dat_022888:
	dc.w	$002B,$001E,$0017,$0004,$0027,$0020,$0018,$0005
	dc.w	$0023,$0021,$001A,$0006,$001E,$0022,$001E,$0006
	dc.w	$001A,$0024,$001E,$0008,$0016,$0025,$001F,$000A
	dc.w	$0013,$0026,$001F,$000C,$000F,$0026,$0020,$000F


; ----------------------------------------------------------------------
sub_0228C8:
	moveq	#-$1,d3
	cmpi.w	#$1E0,(ram_C4CA).w
	bgt.w	NullSub
loc_0228D4:
	move.w	(ram_D042).w,d3
	bmi.w	NullSub
	subq.w	#1,(ram_D042).w
	cmp.w	(ram_CFD0).w,d3
	beq.s	loc_0228D4
	moveq	#$10,d0
	mulu.w	d3,d0
	movea.w	#$CF50,a0
	adda.w	d0,a0
	btst	#1,$E(a0)
	bne.s	loc_0228D4
	btst	#2,$E(a0)
	bne.s	loc_0228D4
	rts

	dc.w	$4A43,$6B00,$248C,$6100,$0138,$6100,$E0F2,$5278
	dc.w	$B042,$5978,$B044,$3F38,$B042,$6100,$5224,$31FC
	dc.w	$A000,$B046,$6100,$E2B6,$001A


; ----------------------------------------------------------------------
sub_02292C:
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.l	-(a0),d0
	move.w	(sp),(TextX).w
	moveq	#$1,d0
	add.w	(ram_CFD6).w,d0
	tst.w	(ram_D270).w
	bne.w	loc_022958
	clr.w	d0
loc_022958:
	lea	dat_0229E6(pc),a1
	bsr.w	sub_022A6E
	move.w	$8(a0),d0
	subq.w	#1,d0
	movea.l	#dat_0289EE,a1
	bsr.w	List_Skip
	move.w	(a1),d0
	lsr.w	#1,d0
	neg.w	d0
	add.w	(sp),d0
	addi.w	#$17,d0
	move.w	d0,(TextX).w
	bsr.w	Text_Print_Worker
	move.w	#$8000,(TextAttr).w
	move.w	$2(a0),d0
	move.w	$C(a0),d1
	bsr.w	sub_0229A4
	move.w	(a0),d0
	move.w	$A(a0),d1
	bsr.w	sub_0229A4
	addq.w	#2,sp
	rts


; ----------------------------------------------------------------------
; called from $022992, $02299C
sub_0229A4:
	move.w	$4(sp),(TextX).w
	addq.w	#1,(TextY).w
	movea.w	#$7FA,a1
	tst.w	(ram_DEA8).w
	beq.w	loc_0229C0
	movea.l	#RosterTable,a1
loc_0229C0:
	asl.w	#2,d0
	movea.l	$0(a1,d0.w),a1
	adda.w	$4(a1),a1
	bsr.w	Text_Print_Worker
	move.w	$4(sp),(TextX).w
	addi.w	#$15,(TextX).w
	move.w	d1,d0
	moveq	#$2,d1
	bsr.w	Num_ToDecimal
	bra.w	Text_Print_Worker
dat_0229E6:
	dc.b	$00,$12
	dc.b	"EA Hockey Night",0
	dc.b	$00,$18
	dc.b	"Stanley Cup Qualifier",0
	dc.b	$00,$0E
	dc.b	"Quarterfinal",0
	dc.b	$18
	dc.b	"Stanley Cup Semifinal",0
	dc.w	$6100,$000A,$343C,$07FF,$6000,$DF86,$6100,$E19A
	dc.w	$0006,$BD03,$1700,$0838,$0000,$C33C,$6600,$000C
	dc.w	$6100,$E186,$0006,$BF03,$1700,$701A,$7205,$4E75


; ----------------------------------------------------------------------
; called from $1D4C3A
sub_022A66:
	bsr.w	List_Skip
	bra.w	Text_PrintNarrow_Worker


; ----------------------------------------------------------------------
; called from $019CFC, $019D0C, $019D3E, $019E30, $020DB0, $02295C, $1D9500, $1DDE52
sub_022A6E:
	bsr.w	List_Skip
	bra.w	Text_PrintCmd_Worker


; ----------------------------------------------------------------------
; skips d0 entries of a list of word length prefixed records at a1
; called from $00C896, $00C8AE, $012688, $0158A6, $018C7A, $019C3E, $021DB6, $02296C (+35 more)
List_Skip:
	bra.w	loc_022A7C
loc_022A7A:
	adda.w	(a1),a1
loc_022A7C:
	dbra	d0,loc_022A7A
	rts

