; ============================================================================
; Sound interface: Z80 driver upload, command queue, SRAM access
; ROM range $02993A-$02B0AF
; ============================================================================


; ----------------------------------------------------------------------
; called from $018FC8
sub_02993A:
	move.l	#VBlank_CountOnly,(VBlankVector).l
	move.w	#$2500,sr
	clr.w	(ram_D348).w
	jsr	(Joypad_Read1).l
	move.w	d3,d0
	movea.l	#$200000,a0
	move.w	#$E,d3
	move.w	#$2,d4
	cmp.b	#$E0,d0	; general form
	beq.w	loc_0299AC
	cmp.b	#$B0,d0	; general form
	beq.w	loc_029A08
	moveq	#$0,d0
	move.l	#dat_008000,d1
	movea.l	#SaveDataMirror,a0
	bsr.w	SRAM_Read
	bsr.w	SaveData_Verify
	tst.w	(ram_D348).w
	bpl.w	loc_0299AA
	bsr.w	sub_029A86
	moveq	#$0,d0
	move.l	#dat_008000,d1
	movea.l	#SaveDataMirror,a0
	bsr.w	SRAM_Read
	bsr.w	SaveData_Verify
loc_0299AA:
	rts
loc_0299AC:
	move.w	#$7FFF,d2
loc_0299B0:
	move.w	#$1,d1
	move.w	#$7,d0
loc_0299B8:
	move.w	d1,(a0)
	cmp.b	$1(a0),d1
	bne.w	loc_0299EA
	lsl.w	#1,d1
	dbra	d0,loc_0299B8
	adda.w	#$2,a0
	dbra	d2,loc_0299B0
	movea.l	#$200000,a0
	move.l	#dat_120034,(a0)+
	move.l	#$560078,(a0)+
	move.w	#$E0,d3
	move.w	#$20,d4
loc_0299EA:
	move.w	d3,d0
loc_0299EC:
	move.l	#$C0000000,(VDP_CTRL).l
	move.w	d0,d1
	and.w	d3,d1
	move.w	d1,(VDP_DATA).l
	bsr.w	sub_029A2A
	sub.w	d4,d0
	bra.s	loc_0299EC
loc_029A08:
	move.w	#$3,d1
loc_029A0C:
	adda.w	#$1,a0
	lsl.l	#8,d0
	move.b	(a0)+,d0
	dbra	d1,loc_029A0C
	cmp.l	#$12345678,d0	; general form
	bne.s	loc_0299EA
	move.w	#$E0,d3
	move.w	#$20,d4
	bra.s	loc_0299EA


; ----------------------------------------------------------------------
; called from $029A00
sub_029A2A:
	jsr	(sub_019BF0).l
	rts


; ----------------------------------------------------------------------
; only increments ram_FrameCounter
VBlank_CountOnly:
	addq.w	#1,(FrameCounter).w
	rte


; ----------------------------------------------------------------------
; checks the checksum of the save data mirror in RAM
; called from $029984, $0299A6
SaveData_Verify:
	move.w	#$7FFD,d1
	clr.w	d0
	lea	(SaveDataMirror).l,a0
loc_029A44:
	add.b	(a0)+,d0
	dbra	d1,loc_029A44
	clr.w	d1
	cmp.b	$1(a0),d0
	beq.w	loc_029A56
	addq.w	#1,d1
loc_029A56:
	not.w	d0
	cmp.b	(a0),d0
	beq.w	loc_029A60
	addq.w	#1,d1
loc_029A60:
	swap	d0
	move.b	(a0),d0
	not.b	d0
	cmp.b	$1(a0),d0
	beq.w	loc_029A70
	addq.w	#1,d1
loc_029A70:
	swap	d0
	tst.w	d1
	bne.w	loc_029A80
	clr.w	(ram_D348).w
	bra.w	loc_029A84
loc_029A80:
	st	(ram_D348).w
loc_029A84:
	rts


; ----------------------------------------------------------------------
; called from $029990
sub_029A86:
	bset	#6,(SysFlags).w
	lea	(SaveDataMirror).l,a0
	move.l	#$1FFF,d0
	clr.l	d1
loc_029A9A:
	move.l	d1,(a0)+
	dbra	d0,loc_029A9A
	moveq	#$0,d0
	move.l	#dat_008000,d1
	movea.l	#SaveDataMirror,a0
	bsr.w	SRAM_Write
	clr.w	(ram_D270).w
	clr.w	(ram_D272).w
	move.w	#$11,(ram_D274).w
	move.w	#$8,(ram_D276).w
	clr.w	(ram_D278).w
	clr.w	(ram_D27A).w
	clr.w	(ram_D27C).w
	move.w	#$1,(ram_D27E).w
	clr.w	(ram_D280).w
	clr.w	(ram_D282).w
	move.w	#$1,(ram_D284).w
	clr.w	(ram_D286).w
	movea.l	#ram_D270,a0
	move.l	#dat_002118,d0
	moveq	#$1A,d1
	jsr	(SRAM_Write).l
	jsr	(sub_013B34).l
	move.l	#$57C,d1
	move.l	#dat_0017A2,d0
	movea.l	#ram_17A2,a0
	bsr.w	SRAM_Write
	moveq	#$34,d1
	move.l	#dat_001D1E,d0
	movea.l	#ram_1D1E,a0
	bsr.w	SRAM_Write
	move.l	#$2BE,d1
	move.l	#dat_001D52,d0
	movea.l	#ram_1D52,a0
	bsr.w	SRAM_Write
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	#dat_004D1C,d2
	bsr.w	sub_029D48
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	#dat_005692,d2
	bsr.w	sub_029D48
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	#dat_006008,d2
	bsr.w	sub_029D48
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	#dat_00697E,d2
	bsr.w	sub_029D48
	move.l	#$976,d1
	move.l	#dat_0017A2,d0
	move.l	#dat_0072F4,d2
	bsr.w	sub_029D48
	move.l	#loc_00F8D4,d1
	movea.l	#$200000,a0
	move.w	#$5,d0
	clr.w	d2
loc_029BC2:
	move.w	d2,$0(a0,d1.l)
	addq.w	#1,d2
	addq.l	#2,d1
	dbra	d0,loc_029BC2
	jsr	(sub_012876).l
	jsr	(sub_1D9EF2).l
	move.l	#dat_000DCA,d0
	moveq	#$28,d1
	movea.l	#ram_0DCA,a0
	bsr.w	SRAM_Write
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	#dat_0049CA,d2
	bsr.w	sub_029D48
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	#dat_004A74,d2
	bsr.w	sub_029D48
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	#dat_004B1E,d2
	bsr.w	sub_029D48
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	#dat_004BC8,d2
	bsr.w	sub_029D48
	move.l	#$AA,d1
	move.l	#dat_000DCA,d0
	move.l	#dat_004C72,d2
	bsr.w	sub_029D48
	clr.l	(ram_DD9C).w
	clr.l	(ram_DDA0).w
	clr.w	(ram_DDA4).w
	move.b	#$FF,(ram_DDA2).w
	bset	#6,(SysFlags).w
	jsr	(sub_014FCE).l
	bclr	#6,(SysFlags).w
	move.l	#$AB,d0
	move.l	#$109A0,d1
	move.w	#$8,d2
	jsr	(sub_00B8DE).l
	bclr	#6,(SysFlags).w
	bsr.w	SRAM_UpdateChecksum
	rts


; ----------------------------------------------------------------------
; a0 = source, d0 = SRAM byte offset, d1 = byte count
; called from $013E32, $013FD8, $014FDC, $027A38, $029AAE, $029AF8, $029B16, $029B28 (+17 more)
SRAM_Write:
	movem.l	d0-d2/a0/a1,-(sp)
	movea.l	#$200000,a1
	add.l	d0,d0
	subq.l	#1,d1
	clr.w	d2
loc_029CB0:
	move.b	(a0)+,d2
	move.w	d2,$0(a1,d0.l)
	addq.l	#2,d0
	dbra	d1,loc_029CB0
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; sums the save area and stores the checksum (skipped when ram_SysFlags bit 6 is set)
; called from $00B946, $00BD56, $00BD86, $00BE3A, $013E38, $013FDE, $014AE8, $014B6C (+37 more)
SRAM_UpdateChecksum:
	btst	#6,(SysFlags).w
	bne.w	loc_029D08
	movem.l	d0-d2/a0/a1,-(sp)
	movea.l	#$200000,a1
	move.l	#$7FFD,d1
	clr.l	d0
	clr.l	d2
loc_029CE0:
	add.b	$1(a1,d0.l),d2
	addq.l	#2,d0
	dbra	d1,loc_029CE0
	move.w	d2,d0
	movea.l	#SaveChecksum,a0
	move.b	d0,$1(a0)
	not.w	d0
	move.b	d0,(a0)
	moveq	#$2,d1
	move.l	#dat_007FFE,d0
	bsr.s	SRAM_Write
	movem.l	(sp)+,d0-d2/a0/a1
loc_029D08:
	rts


; ----------------------------------------------------------------------
; a0 = destination, d0 = SRAM byte offset, d1 = byte count
; called from $013D26, $013E16, $013F42, $013FBA, $014FFC, $0272AE, $027376, $027A04 (+20 more)
SRAM_Read:
	movem.l	d0-d2/a0/a1,-(sp)
	movea.l	#$200000,a1
	add.l	d0,d0
	subq.l	#1,d1
loc_029D18:
	move.b	$1(a1,d0.l),d2
	move.b	d2,(a0)+
	addq.l	#2,d0
	dbra	d1,loc_029D18
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $0150AE, $0150C0, $0150FA, $015108, $01511A, $015128, $018818, $018828 (+12 more)
sub_029D2A:
	movem.l	d0-d2/a0/a1,-(sp)
	movea.l	#$200000,a1
	add.l	d0,d0
	subq.l	#1,d1
loc_029D38:
	clr.w	$0(a1,d0.l)
	addq.l	#2,d0
	dbra	d1,loc_029D38
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $029B54, $029B6A, $029B80, $029B96, $029BAC, $029BFE, $029C14, $029C2A (+2 more)
sub_029D48:
	movem.l	d0-d3/a0/a1,-(sp)
	movea.l	#$200000,a1
	add.l	d0,d0
	add.l	d2,d2
	subq.l	#1,d1
loc_029D58:
	move.w	$0(a1,d0.l),d3
	move.w	d3,$0(a1,d2.l)
	addq.l	#2,a1
	dbra	d1,loc_029D58
	movem.l	(sp)+,d0-d3/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $02A036
sub_029D6C:
	movem.l	d1/a0,-(sp)
	tst.w	(FourWayPlay).w
	beq.w	loc_029DA0
	jsr	(sub_029DB6).l
	move.b	d0,(JoypadPort1).w
	jsr	(sub_029DD0).l
	move.b	d0,(JoypadPort2).w
	bsr.w	sub_029DEA
	move.b	d0,(JoypadPort3).w
	bsr.w	sub_029E04
	move.b	d0,(JoypadPort4).w
	bra.w	loc_029DB0
loc_029DA0:
	bsr.w	sub_029E36
	move.b	d0,(JoypadPort1).w
	bsr.w	sub_029E28
	move.b	d0,(JoypadPort2).w
loc_029DB0:
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $029D78
sub_029DB6:
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.b	#$C,(IO_DATA2).l
	bra.w	loc_029E1A


; ----------------------------------------------------------------------
; called from $029D82
sub_029DD0:
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.b	#$1C,(IO_DATA2).l
	bra.w	loc_029E1A


; ----------------------------------------------------------------------
; called from $029D8C
sub_029DEA:
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.b	#$2C,(IO_DATA2).l
	bra.w	loc_029E1A


; ----------------------------------------------------------------------
; called from $029D94
sub_029E04:
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	move.b	#$3C,(IO_DATA2).l
loc_029E1A:
	movem.l	d1/a0,-(sp)
	lea	(IO_DATA1).l,a0
	bra.w	loc_029E4E


; ----------------------------------------------------------------------
; called from $029DA8
sub_029E28:
	movem.l	d1/a0,-(sp)
	lea	(IO_DATA2).l,a0
	bra.w	loc_029E40


; ----------------------------------------------------------------------
; called from $029DA0
sub_029E36:
	movem.l	d1/a0,-(sp)
	lea	(IO_DATA1).l,a0
loc_029E40:
	move.w	d0,-(sp)
	move.w	#$D,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
loc_029E4E:
	moveq	#$0,d0
	move.b	#$0,(a0)
	nop
	nop
	move.b	(a0),d0
	move.b	#$40,(a0)
	nop
	nop
	move.b	(a0),d1
	move.w	d0,-(sp)
	move.w	#$E,d0
	jsr	(Sound_Call).l
	move.w	(sp)+,d0
	asl.b	#2,d0
	andi.b	#$C0,d0
	andi.b	#$3F,d1
	or.b	d1,d0
	not.b	d0
	not.b	d1
	andi.w	#$F,d1
	lea	dat_029E9A(pc),a0
	andi.b	#$F0,d0
	or.b	$0(a0,d1.w),d0
	not.b	d0
	movem.l	(sp)+,d1/a0
	rts
dat_029E9A:
	dc.w	$0001,$0201,$0405,$0606,$0809,$0A0A,$0809,$0A00
	dc.w	$33FC,$0100,$00A1,$1200,$33FC,$0100,$00A1,$1100
	dc.w	$0839,$0000,$00A1,$1100,$66F6,$4E75


; ----------------------------------------------------------------------
; called from $00CABC
sub_029EC6:
	move.w	$36(a3),d0
	clr.w	d1
	move.b	$38(a3,d0.w),d1
	asl.w	#2,d1
	movea.l	#ptrtbl_00F5FE,a0
	movea.l	$0(a0,d1.w),a0
	jsr	(sub_022566).l
	jsr	(a0)
	rts


; ----------------------------------------------------------------------
; called from $019F4C, $0264FA, $1DCFC6
sub_029EE6:
	move.w	d4,(FontTileBase).w
	movea.l	#Font_Small_Tiles,a2
	jsr	(Draw_RunScript).l
inl_029EF6:
	dc.w	$A123,$2FAB,$D1AA,$CDEF
loc_029EFE:
	rts


; ----------------------------------------------------------------------
; called from $026500, $1DCFCC
sub_029F00:
	move.w	d4,(ram_B016).w
	movea.l	#Font_Scoreboard_Tiles,a2
	jsr	(sub_020780).l
	move.w	d4,(ram_B018).w
	movea.l	#Art_1B5AEA_Tiles,a2
	jmp	(sub_020780).l


; ----------------------------------------------------------------------
; called from $01C050
sub_029F20:
	btst	#7,$62(a3)
	beq.w	loc_029F52
	cmpi.w	#$3,$54(a3)
	beq.w	loc_029F42
	cmpi.w	#$5,$54(a3)
	beq.w	loc_029F4A
	bra.w	loc_029F62
loc_029F42:
	subq.w	#1,$54(a3)
	bra.w	loc_029F62
loc_029F4A:
	addq.w	#1,$54(a3)
	bra.w	loc_029F62
loc_029F52:
	cmpi.w	#$7,$54(a3)
	beq.s	loc_029F42
	cmpi.w	#$1,$54(a3)
	beq.s	loc_029F4A
loc_029F62:
	rts


; ----------------------------------------------------------------------
; called from $01C046, $01C07E, $01C36A, $01F89E, $01F9B4
sub_029F64:
	cmpi.w	#$17,(a3)
	bgt.w	loc_029FB6
	cmpi.w	#$FFE9,(a3)
	blt.w	loc_029FB6
	btst	#7,$62(a3)
	bne.w	loc_029F96
	cmpi.w	#$126,$14(a3)
	bgt.w	loc_029FB6
	cmpi.w	#$100,$14(a3)
	blt.w	loc_029FB6
	bra.w	loc_029FAA
loc_029F96:
	cmpi.w	#$FEDA,$14(a3)
	blt.w	loc_029FB6
	cmpi.w	#$FF00,$14(a3)
	bgt.w	loc_029FB6
loc_029FAA:
	movem.w	d0,-(sp)
	move.w	#$0,d0
	bra.w	loc_029FBE
loc_029FB6:
	movem.w	d0,-(sp)
	move.w	#$1,d0
loc_029FBE:
	movem.w	(sp)+,d0
	rts


; ----------------------------------------------------------------------
sub_029FC4:
	bset	#1,(ram_C346).w
	rts


; ----------------------------------------------------------------------
; called from $02731A
sub_029FCC:
	movem.l	d0/d1/a0,-(sp)
	move.w	(ram_CFD2).w,d0
	asl.w	#4,d0
	ext.l	d0
	movea.l	#dat_006D74,a0
	adda.l	d0,a0
	moveq	#$10,d1
	move.l	#$E7E,d0
	jsr	(SRAM_Write).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $02737C
sub_029FF4:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_CFFE,a0
	moveq	#$10,d1
	move.l	#$E7E,d0
	jsr	(SRAM_Read).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $1E2AB4
sub_02A012:
	movem.l	d0/d1/a0,-(sp)
	movea.l	#ram_CFFE,a0
	moveq	#$10,d1
	move.l	#$E7E,d0
	jsr	(SRAM_Write).l
	jsr	(SRAM_UpdateChecksum).l
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $0172B6, $025872, $0258B6, $0271C4, $1DD734, $1E2510, $1E43B8, $1E461A
Sound_VBlankUpdate:
	bsr.w	sub_029D6C
	move.w	#$1,d0
	jsr	(Sound_Call).l
	rts


; ----------------------------------------------------------------------
; called from $091F88, $0920EA
Sound_Dispatch:
	cmpi.w	#$13,d0
	bcc.s	loc_02A062
	move.l	a6,-(sp)
	lea	Sound_FuncTable(pc),a6
	andi.l	#$FFFF,d0
	lsl.l	#2,d0
	adda.l	d0,a6
	jsr	(a6)
	movea.l	(sp)+,a6
	rts
loc_02A062:
	move.w	#$1,d0
	ori	#$1,ccr
	rts


; ----------------------------------------------------------------------
; branch table of the 19 sound functions
; called from $02A04E, $02A05C
Sound_FuncTable:
	bra.w	Snd_LoadDriver
loc_02A070:
	bra.w	Snd_Update
loc_02A074:
	bra.w	Snd_Enable
loc_02A078:
	bra.w	Snd_Disable
loc_02A07C:
	bra.w	Snd_Func04
loc_02A080:
	bra.w	Snd_Func05
loc_02A084:
	bra.w	Snd_SetSoundBank
loc_02A088:
	bra.w	Snd_Func07
loc_02A08C:
	bra.w	Snd_Func08
loc_02A090:
	bra.w	Snd_ResetQueue
loc_02A094:
	bra.w	Snd_Func0A
loc_02A098:
	bra.w	Snd_Func0B
loc_02A09C:
	bra.w	Snd_Func0C
loc_02A0A0:
	bra.w	Snd_PauseZ80
loc_02A0A4:
	bra.w	Snd_ResumeZ80
loc_02A0A8:
	bra.w	Snd_StopAll
loc_02A0AC:
	bra.w	Snd_Func10
loc_02A0B0:
	bra.w	Snd_Func11
loc_02A0B4:
	bra.w	Snd_Func12
; function 3: sets ram_SoundLock to $1234
Snd_Disable:
	move.l	a0,-(sp)
	lea	(SoundLock).l,a0
	move.w	#$1234,(a0)
	movea.l	(sp)+,a0
	clr.w	d0
	rts
; function 2: clears ram_SoundLock
Snd_Enable:
	move.l	a0,-(sp)
	lea	(SoundLock).l,a0
	clr.w	(a0)
	movea.l	(sp)+,a0
	clr.w	d0
	rts
; function 0: a0 = Z80 driver, d1 = length; resets the Z80 and uploads the driver
Snd_LoadDriver:
	movem.l	d1/a0-a2,-(sp)
	move.w	sr,-(sp)
	move.w	#$2700,sr
	move.w	#$100,(Z80_BUSREQ).l
	move.w	#$100,(Z80_RESET).l
	cmpi.b	#$C3,(a0)
	bne.s	loc_02A10C
	lea	(Z80_RAM).l,a1
	subi.w	#$1,d1
loc_02A104:
	move.b	(a0)+,(a1)+
	dbra	d1,loc_02A104
	bra.s	loc_02A114
loc_02A10C:
	move.w	#$6,d0
	bra.w	loc_02A1F4
loc_02A114:
	move.w	#$0,(Z80_RESET).l
	move.w	#$0,(Z80_BUSREQ).l
	move.w	#$1F4,d0
loc_02A128:
	dbra	d0,loc_02A128
	move.w	#$100,(Z80_RESET).l
loc_02A134:
	bsr.w	Z80_BusRequest
	cmpi.b	#$FF,(Z80_RAM+$4F).l
	beq.s	loc_02A150
	bsr.w	Z80_BusRelease
	move.w	#$1388,d0
loc_02A14A:
	dbra	d0,loc_02A14A
	bra.s	loc_02A134
loc_02A150:
	bsr.w	Z80_BusRelease
	lea	(ram_FFDC).l,a0
	move.w	#$3,d0
loc_02A15E:
	move.l	#$FFFFFFFF,(a0)+
	dbra	d0,loc_02A15E
	lea	(ram_FDFE).l,a0
	move.w	#$7,d0
loc_02A172:
	move.l	#$FFFFFFFF,(a0)+
	dbra	d0,loc_02A172
	lea	(ram_FE1E).l,a0
	move.w	#$7,d0
loc_02A186:
	move.l	#$0,(a0)+
	dbra	d0,loc_02A186
	lea	(ram_FE3E).l,a0
	move.w	#$7,d0
loc_02A19A:
	move.w	#$FFFF,(a0)+
	dbra	d0,loc_02A19A
	lea	(ram_FE7E).l,a0
	move.w	#$7,d0
loc_02A1AC:
	move.l	#$0,(a0)+
	dbra	d0,loc_02A1AC
	bsr.w	sub_02AAD0
	lea	(ram_FF4E).l,a0
	move.w	#$1F,d0
loc_02A1C4:
	clr.l	(a0)+
	dbra	d0,loc_02A1C4
	lea	(ram_FFCE).l,a0
	clr.w	(a0)
	lea	(ram_FFD0).l,a0
	clr.w	(a0)
	lea	(SoundLock).l,a0
	move.w	#$1234,(a0)
	lea	(SoundTick).l,a0
	clr.w	(a0)
	andi	#$FE,ccr
	clr.w	d0
	bra.s	loc_02A1F8
loc_02A1F4:
	ori	#$1,ccr
loc_02A1F8:
	move.w	(sp)+,sr
	movem.l	(sp)+,d1/a0-a2
	rts
; function 1: per frame update called from the VBlank handlers
Snd_Update:
	movem.l	d0-d7/a0-a6,-(sp)
	lea	(SoundTick).l,a0
	addi.w	#$1,(a0)
	cmpi.w	#$1,(a0)
	bne.w	loc_02A560
	lea	(SoundLock).l,a0
	cmpi.w	#$1234,(a0)
	bne.w	loc_02A560
	bsr.w	sub_02B046
	bsr.w	sub_02AB82
	bsr.w	sub_02ABFE
	lea	(ram_FF40).l,a0
	move.w	#$0,(a0)
	lea	(ram_FDFE).l,a6
	lea	(ram_FE1E).l,a5
	lea	(ram_FE4E).l,a4
	lea	(ram_FE5E).l,a3
	lea	(ram_FE6E).l,a2
	lea	(ram_FE7E).l,a1
loc_02A25E:
	move.w	(ram_FF40).l,d6
	lsl.w	#1,d6
	move.w	d6,d7
	lsl.w	#1,d7
	cmpi.l	#$FFFFFFFF,$0(a6,d7.w)
	beq.w	loc_02A54E
	tst.w	$0(a4,d6.w)
	beq.s	loc_02A2BE
	move.w	$0(a3,d6.w),d1
	add.w	$0(a2,d6.w),d1
	move.w	d1,d2
	andi.w	#$FF,d2
	lsr.w	#8,d1
	add.w	$0(a1,d7.w),d1
	move.w	#$0,$0(a1,d7.w)
	cmp.w	$0(a4,d6.w),d1
	bcc.s	loc_02A2AE
	move.w	$0(a4,d6.w),d3
	sub.w	d1,d3
	move.w	d3,$0(a4,d6.w)
	move.w	d2,$0(a2,d6.w)
	bra.w	loc_02A54E
loc_02A2AE:
	sub.w	$0(a4,d6.w),d1
	lsl.w	#8,d1
	or.w	d2,d1
	move.w	d1,$0(a2,d6.w)
	clr.w	$0(a4,d6.w)
loc_02A2BE:
	movea.l	$0(a6,d7.w),a0
	move.l	$0(a5,d7.w),d5
loc_02A2C6:
	tst.b	$0(a0,d5.l)
	bpl.s	loc_02A2D4
	addi.l	#$1,d5
	bra.s	loc_02A2C6
loc_02A2D4:
	addi.l	#$1,d5
	tst.b	$0(a0,d5.l)
	bpl.s	loc_02A2EC
	move.b	$0(a0,d5.l),$2(a1,d7.w)
	addi.l	#$1,d5
loc_02A2EC:
	move.b	$2(a1,d7.w),d0
	andi.b	#$F0,d0
	cmpi.b	#$90,d0
	bne.w	loc_02A386
	move.w	(ram_FF40).l,d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	move.b	$1(a0,d5.l),d0
	swap	d0
	move.b	$0(a0,d5.l),d0
	lsl.w	#8,d0
	move.b	$2(a1,d7.w),d0
	bsr.w	Snd_QueueCommand
	tst.w	d0
	beq.s	loc_02A328
	addi.w	#$1,$0(a1,d7.w)
	bra.w	loc_02A54E
loc_02A328:
	move.b	$0(a0,d5.l),d2
	lsl.w	#8,d2
	clr.l	d0
	addi.l	#$1,d5
loc_02A336:
	addi.l	#$1,d5
	lsl.l	#7,d0
	move.b	$0(a0,d5.l),d1
	andi.b	#$7F,d1
	or.b	d1,d0
	btst	#7,$0(a0,d5.l)
	bne.s	loc_02A336
	addi.l	#$1,d5
	lsl.l	#8,d0
	move.w	$0(a3,d6.w),d3
	cmp.w	d3,d0
	bcc.s	loc_02A366
	move.w	#$1,d0
	bra.s	loc_02A368
loc_02A366:
	divu.w	d3,d0
loc_02A368:
	swap	d0
	move.w	d2,d0
	move.w	(ram_FF40).l,d1
	lsl.w	#4,d1
	move.b	$2(a1,d7.w),d0
	andi.b	#$F,d0
	or.b	d1,d0
	bsr.w	sub_02AB54
	bra.w	loc_02A520
loc_02A386:
	cmpi.b	#$B0,d0
	bne.w	loc_02A4A4
	cmpi.b	#$12,$0(a0,d5.l)
	bne.s	loc_02A39A
	bra.w	loc_02A46E
loc_02A39A:
	cmpi.b	#$75,$0(a0,d5.l)
	bne.s	loc_02A3D8
	clr.l	d0
	move.b	$1(a0,d5.l),d0
	lsl.l	#1,d0
	addi.l	#$2,d0
	clr.l	d1
	move.b	$0(a0,d0.l),d1
	lsl.l	#8,d1
	move.b	$1(a0,d0.l),d1
	clr.l	d0
	move.b	(a0),d0
	lsl.l	#8,d0
	move.b	$1(a0),d0
	lsl.l	#1,d0
	addi.l	#$2,d0
	add.l	d0,d1
	move.l	d1,$0(a5,d7.w)
	bra.w	loc_02A25E
loc_02A3D8:
	cmpi.b	#$77,$0(a0,d5.l)
	bne.s	loc_02A436
	lea	(ram_FE9E).l,a0
	clr.l	d0
	move.w	(ram_FF40).l,d0
	lsl.l	#2,d0
	adda.l	d0,a0
	move.l	d5,d0
	addi.l	#$2,d0
	move.l	d0,(a0)
	clr.l	d0
	movea.l	$0(a6,d7.w),a0
	move.b	$1(a0,d5.l),d0
	lsl.l	#1,d0
	addi.l	#$2,d0
	clr.l	d1
	move.b	$0(a0,d0.l),d1
	lsl.l	#8,d1
	move.b	$1(a0,d0.l),d1
	clr.l	d0
	move.b	(a0),d0
	lsl.l	#8,d0
	move.b	$1(a0),d0
	lsl.l	#1,d0
	addi.l	#$2,d0
	add.l	d0,d1
	move.l	d1,$0(a5,d7.w)
	bra.w	loc_02A25E
loc_02A436:
	cmpi.b	#$78,$0(a0,d5.l)
	bne.s	loc_02A46E
	lea	(ram_FE9E).l,a0
	clr.l	d0
	move.w	(ram_FF40).l,d0
	lsl.l	#2,d0
	adda.l	d0,a0
	cmpi.l	#$FFFFFFFF,(a0)
	bne.s	loc_02A464
	move.l	#$FFFFFFFF,$0(a6,d7.w)
	bra.w	loc_02A54E
loc_02A464:
	move.l	(a0),d5
	movea.l	$0(a6,d7.w),a0
	bra.w	loc_02A520
loc_02A46E:
	move.w	(ram_FF40).l,d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	move.b	$1(a0,d5.l),d0
	swap	d0
	move.b	$0(a0,d5.l),d0
	lsl.w	#8,d0
	move.b	$2(a1,d7.w),d0
	bsr.w	Snd_QueueCommand
	tst.w	d0
	beq.s	loc_02A49A
	addi.w	#$1,$0(a1,d7.w)
	bra.w	loc_02A54E
loc_02A49A:
	addi.l	#$2,d5
	bra.w	loc_02A520
loc_02A4A4:
	cmpi.b	#$C0,d0
	bne.s	loc_02A4DA
	move.w	(ram_FF40).l,d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	swap	d0
	move.b	$0(a0,d5.l),d0
	lsl.w	#8,d0
	move.b	$2(a1,d7.w),d0
	bsr.w	Snd_QueueCommand
	tst.w	d0
	beq.s	loc_02A4D2
	addi.w	#$1,$0(a1,d7.w)
	bra.w	loc_02A54E
loc_02A4D2:
	addi.l	#$1,d5
	bra.s	loc_02A520
loc_02A4DA:
	cmpi.b	#$E0,d0
	bne.s	loc_02A50E
	move.w	(ram_FF40).l,d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	swap	d0
	move.b	$0(a0,d5.l),d0
	lsl.w	#8,d0
	move.b	$2(a1,d7.w),d0
	bsr.w	Snd_QueueCommand
	tst.w	d0
	beq.s	loc_02A506
	addi.w	#$1,$0(a1,d7.w)
	bra.s	loc_02A54E
loc_02A506:
	addi.l	#$1,d5
	bra.s	loc_02A520
loc_02A50E:
	cmpi.b	#$FF,$2(a1,d7.w)
	bne.s	loc_02A520
	move.l	#$FFFFFFFF,$0(a6,d7.w)
	bra.s	loc_02A54E
loc_02A520:
	move.l	d5,$0(a5,d7.w)
	clr.l	d2
loc_02A526:
	lsl.l	#7,d2
	move.b	$0(a0,d5.l),d1
	andi.b	#$7F,d1
	or.b	d1,d2
	btst	#7,$0(a0,d5.l)
	beq.s	loc_02A542
	addi.l	#$1,d5
	bra.s	loc_02A526
loc_02A542:
	move.w	d2,$0(a4,d6.w)
	tst.w	d2
	bne.s	loc_02A54E
	bra.w	loc_02A25E
loc_02A54E:
	lea	(ram_FF40).l,a0
	addi.w	#$1,(a0)
	cmpi.w	#$7,(a0)
	blt.w	loc_02A25E
loc_02A560:
	lea	(SoundTick).l,a0
	subi.w	#$1,(a0)
	andi	#$FE,ccr
	movem.l	(sp)+,d0-d7/a0-a6
	rts
Snd_Func04:
	movem.l	d1-d4/a0/a1,-(sp)
	lea	(SoundLock).l,a0
	move.w	d1,$1D8(a0)
	move.w	d2,$1DA(a0)
	move.w	d3,$1DC(a0)
	move.w	d4,$1DE(a0)
	cmpi.w	#$0,d4
	bne.s	loc_02A59C
	move.w	#$5,d0
	bra.w	loc_02A66A
loc_02A59C:
	lea	(ram_FDFE).l,a1
	clr.w	d0
loc_02A5A4:
	cmpi.l	#$FFFFFFFF,(a1)+
	beq.s	loc_02A5BE
	addi.w	#$1,d0
	cmpi.w	#$7,d0
	bne.s	loc_02A5A4
	move.w	#$7,d0
	bra.w	loc_02A66A
loc_02A5BE:
	move.w	d0,$1D6(a0)
	move.w	d1,-(sp)
	lsl.w	#8,d0
	lsl.w	#4,d0
	swap	d0
	move.w	#$1FF,d0
	move.l	d0,d1
	bsr.w	Snd_Func0A
	move.w	(sp)+,d1
	move.w	#$3,d0
	bsr.w	sub_02AD5E
	bcs.w	loc_02A66A
	clr.l	d1
	move.b	(a0),d1
	lsl.w	#8,d1
	move.b	$1(a0),d1
	lsl.w	#1,d1
	addi.w	#$2,d1
	lea	(SoundLock).l,a1
	move.w	$0(a1),-(sp)
	move.w	#$0,$0(a1)
	move.w	$1D6(a1),d0
	lsl.w	#2,d0
	move.l	a0,$2(a1,d0.w)
	move.l	d1,$22(a1,d0.w)
	lea	(ram_FE7E).l,a0
	move.l	#$0,$0(a0,d0.w)
	lea	(ram_FE9E).l,a0
	move.l	#$FFFFFFFF,$0(a0,d0.w)
	move.w	$1D6(a1),d0
	lsl.w	#1,d0
	move.w	$1DE(a1),$62(a1,d0.w)
	move.w	#$0,$52(a1,d0.w)
	move.w	#$0,$72(a1,d0.w)
	move.w	$1D8(a1),$42(a1,d0.w)
	move.w	$1D6(a1),d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	or.w	$1DC(a1),d0
	swap	d0
	move.w	#$10B0,d0
	move.l	d0,d1
	bsr.w	Snd_Func0A
	move.w	(sp)+,$0(a1)
	clr.w	d0
	bra.s	loc_02A66E
loc_02A66A:
	ori	#$1,ccr
loc_02A66E:
	movem.l	(sp)+,d1-d4/a0/a1
	rts
Snd_Func05:
	movem.l	d1/d2/a0,-(sp)
	lea	(ram_FE3E).l,a0
	clr.w	d0
loc_02A680:
	cmp.w	(a0)+,d1
	beq.s	loc_02A698
	addi.w	#$1,d0
	cmpi.w	#$7,d0
	bne.s	loc_02A680
	move.w	#$3,d0
	ori	#$1,ccr
	bra.s	loc_02A6D0
loc_02A698:
	lea	(SoundLock).l,a0
	move.w	d0,$1D6(a0)
	lsl.w	#1,d0
	lea	(ram_FE3E).l,a0
	move.w	#$FFFF,$0(a0,d0.w)
	lsl.w	#1,d0
	lea	(ram_FDFE).l,a0
	move.l	#$FFFFFFFF,$0(a0,d0.w)
	lea	(SoundLock).l,a0
	move.w	$1D6(a0),d0
	bsr.w	sub_02AB0A
	clr.w	d0
loc_02A6D0:
	movem.l	(sp)+,d1/d2/a0
	rts


; ----------------------------------------------------------------------
; d0 = 32 bit command, appended to the queue in Z80 RAM
; called from $02A316, $02A488, $02A4C0, $02A4F6, $02AA28, $02AA64, $02ABBE, $02AFF4 (+1 more)
Snd_QueueCommand:
	movem.l	d1/a0,-(sp)
	lea	(SoundLock).l,a0
	move.w	$0(a0),-(sp)
	move.w	#$0,$0(a0)
loc_02A6EA:
	bsr.w	Z80_BusRequest
	lea	(Z80_RAM+$B).l,a0
	tst.b	(a0)
	beq.s	loc_02A70C
	move.w	#$0,(Z80_BUSREQ).l
	move.w	#$64,d1
loc_02A704:
	subi.w	#$1,d1
	bne.s	loc_02A704
	bra.s	loc_02A6EA
loc_02A70C:
	adda.l	#$1,a0
	cmpi.b	#$10,(a0)
	blt.s	loc_02A71E
	move.w	#$FFFF,d0
	bra.s	loc_02A744
loc_02A71E:
	clr.w	d1
	move.b	(a0),d1
	lsl.w	#2,d1
	move.b	d0,$1(a0,d1.w)
	lsr.w	#8,d0
	move.b	d0,$2(a0,d1.w)
	swap	d0
	move.b	d0,$3(a0,d1.w)
	lsr.w	#8,d0
	move.b	d0,$4(a0,d1.w)
	move.b	(a0),d1
	addi.b	#$1,d1
	move.b	d1,(a0)
	clr.w	d0
loc_02A744:
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a0
	move.w	(sp)+,$0(a0)
	movem.l	(sp)+,d1/a0
	rts


; ----------------------------------------------------------------------
; called from $02AE78
Snd_QueueTransfer:
	movem.l	d1/d2/a0/a1,-(sp)
	lea	(SoundLock).l,a1
	move.w	(a1),-(sp)
	move.w	#$0,(a1)
	bsr.w	Z80_BusRequest
	move.b	(Z80_RAM+$5).l,d2
	lsl.w	#8,d2
	move.b	(Z80_RAM+$6).l,d2
	add.w	d1,d2
	cmpi.w	#$1F00,d2
	bcs.s	loc_02A79A
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	move.w	#$4,d0
	ori	#$1,ccr
	bra.w	loc_02A86E
loc_02A79A:
	lea	(Z80_RAM+$100).l,a1
	move.w	#$29,d2
loc_02A7A4:
	cmpi.b	#$0,(a1)
	bne.s	loc_02A7C8
	cmp.b	$1(a1),d0
	bne.s	loc_02A7C8
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	move.w	#$3,d0
	ori	#$1,ccr
	bra.w	loc_02A86E
loc_02A7C8:
	adda.l	#$6,a1
	dbra	d2,loc_02A7A4
	lea	(Z80_RAM+$100).l,a1
	move.w	#$29,d2
loc_02A7DC:
	cmpi.b	#$FF,(a1)
	beq.s	loc_02A804
	adda.l	#$6,a1
	dbra	d2,loc_02A7DC
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	move.w	#$7,d0
	ori	#$1,ccr
	bra.w	loc_02A86E
loc_02A804:
	move.b	#$0,(a1)
	move.b	d0,$1(a1)
	move.w	d1,d2
	move.b	d2,$3(a1)
	lsr.w	#8,d2
	move.b	d2,$2(a1)
	move.b	(Z80_RAM+$5).l,d2
	move.b	d2,$4(a1)
	move.b	(Z80_RAM+$6).l,d2
	move.b	d2,$5(a1)
	lea	(Z80_RAM).l,a1
	clr.l	d2
	move.b	(Z80_RAM+$5).l,d2
	lsl.w	#8,d2
	move.b	(Z80_RAM+$6).l,d2
	subi.w	#$1,d1
loc_02A846:
	move.b	(a0)+,$0(a1,d2.w)
	addi.w	#$1,d2
	dbra	d1,loc_02A846
	move.b	d2,(Z80_RAM+$6).l
	lsr.w	#8,d2
	move.b	d2,(Z80_RAM+$5).l
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	clr.w	d0
loc_02A86E:
	movem.l	(sp)+,d1/d2/a0/a1
	rts
Snd_Func0B:
	movem.l	d1-d3/a0/a1,-(sp)
	lea	(SoundLock).l,a1
	move.w	(a1),-(sp)
	move.w	#$0,(a1)
	bsr.w	Z80_BusRequest
	lea	(Z80_RAM+$100).l,a1
	move.w	#$29,d2
loc_02A892:
	cmpi.b	#$0,(a1)
	bne.s	loc_02A89E
	cmp.b	$1(a1),d1
	beq.s	loc_02A8C0
loc_02A89E:
	adda.l	#$6,a1
	dbra	d2,loc_02A892
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	move.w	#$3,d0
	ori	#$1,ccr
	bra.w	loc_02A8F8
loc_02A8C0:
	move.b	$3(a1),d2
	lsl.w	#8,d2
	move.b	$2(a1),d2
	subi.w	#$1,d2
	move.b	$4(a1),d3
	lsl.w	#8,d3
	move.b	$5(a1),d3
	lea	(Z80_RAM).l,a1
loc_02A8DE:
	move.b	$0(a1,d3.w),(a0)+
	addi.w	#$1,d3
	dbra	d2,loc_02A8DE
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	clr.w	d0
loc_02A8F8:
	movem.l	(sp)+,d1-d3/a0/a1
	rts
Snd_Func0C:
	movem.l	d1-d3/a0/a1,-(sp)
	lea	(SoundLock).l,a1
	move.w	(a1),-(sp)
	move.w	#$0,(a1)
	bsr.w	Z80_BusRequest
	lea	(Z80_RAM+$100).l,a1
	move.w	#$29,d2
loc_02A91C:
	cmpi.b	#$0,(a1)
	bne.s	loc_02A928
	cmp.b	$1(a1),d1
	beq.s	loc_02A94A
loc_02A928:
	adda.l	#$6,a1
	dbra	d2,loc_02A91C
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	move.w	#$3,d0
	ori	#$1,ccr
	bra.w	loc_02A982
loc_02A94A:
	move.b	$3(a1),d2
	lsl.w	#8,d2
	move.b	$2(a1),d2
	subi.w	#$1,d2
	move.b	$4(a1),d3
	lsl.w	#8,d3
	move.b	$5(a1),d3
	lea	(Z80_RAM).l,a1
loc_02A968:
	move.b	(a0)+,$0(a1,d3.w)
	addi.w	#$1,d3
	dbra	d2,loc_02A968
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	clr.w	d0
loc_02A982:
	movem.l	(sp)+,d1-d3/a0/a1
	rts
; function 13: tells the driver to stop (before DMA)
Snd_PauseZ80:
	move.l	a0,-(sp)
	lea	(SoundLock).l,a0
	move.w	(a0),-(sp)
	move.w	#$0,(a0)
	btst	#8,(Z80_BUSREQ).l
	bne.s	loc_02A9AE
	move.b	#$FF,(Z80_RAM+$50).l
	move.w	(sp)+,(a0)
	movea.l	(sp)+,a0
	rts
loc_02A9AE:
	bsr.w	Z80_BusRequest
	move.b	#$FF,(Z80_RAM+$50).l
	bsr.w	Z80_BusRelease
	move.w	(sp)+,(a0)
	movea.l	(sp)+,a0
	rts
; function 14: lets the driver run again (after DMA)
Snd_ResumeZ80:
	move.l	a0,-(sp)
	lea	(SoundLock).l,a0
	move.w	(a0),-(sp)
	move.w	#$0,(a0)
	btst	#8,(Z80_BUSREQ).l
	bne.s	loc_02A9EA
	move.b	#$0,(Z80_RAM+$50).l
	move.w	(sp)+,(a0)
	movea.l	(sp)+,a0
	rts
loc_02A9EA:
	bsr.w	Z80_BusRequest
	move.b	#$0,(Z80_RAM+$50).l
	bsr.w	Z80_BusRelease
	move.w	(sp)+,(a0)
	movea.l	(sp)+,a0
	rts
; function 15
Snd_StopAll:
	movem.l	d0/a0/a1,-(sp)
	lea	(SoundLock).l,a0
	move.w	(a0),-(sp)
	move.w	#$0,(a0)
	lea	(ram_FDFE).l,a1
	move.w	#$7,d0
loc_02AA1A:
	move.l	#$FFFFFFFF,(a1)+
	dbra	d0,loc_02AA1A
	move.w	#$FF,d0
	bsr.w	Snd_QueueCommand
	bsr.w	sub_02AAD0
	move.w	(sp)+,(a0)
	movem.l	(sp)+,d0/a0/a1
	rts
Snd_Func10:
	movem.l	d1-d3/a0/a1,-(sp)
	lea	(ram_FE3E).l,a0
	lea	(ram_FDFE).l,a1
	clr.w	d3
loc_02AA4A:
	cmpi.l	#$FFFFFFFF,(a1)
	beq.s	loc_02AA68
	cmp.w	(a0),d1
	bne.s	loc_02AA68
	move.w	d3,d0
	lsl.w	#8,d0
	lsl.w	#4,d0
	move.b	d2,d0
	swap	d0
	move.w	#$10B0,d0
	bsr.w	Snd_QueueCommand
loc_02AA68:
	adda.l	#$2,a0
	adda.l	#$4,a1
	addi.w	#$1,d3
	cmpi.w	#$7,d3
	bne.s	loc_02AA4A
	clr.w	d0
	movem.l	(sp)+,d1-d3/a0/a1
	rts
Snd_Func11:
	movem.l	d1/d2/a0/a1,-(sp)
	lea	(ram_FE3E).l,a0
	lea	(ram_FDFE).l,a1
	clr.w	d2
loc_02AA98:
	cmpi.l	#$FFFFFFFF,(a1)
	bne.s	loc_02AAAC
	cmp.w	(a0),d1
	bne.s	loc_02AAAC
	move.w	d2,d0
	andi	#$FE,ccr
	bra.s	loc_02AACA
loc_02AAAC:
	adda.l	#$2,a0
	adda.l	#$4,a1
	addi.w	#$1,d2
	cmpi.w	#$7,d2
	bne.s	loc_02AA98
	move.w	#$3,d0
	ori	#$1,ccr
loc_02AACA:
	movem.l	(sp)+,d1/d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $02A1B6, $02AA2C
sub_02AAD0:
	movem.l	d0/d1/a0/a1,-(sp)
	lea	(SoundLock).l,a0
	move.w	$0(a0),-(sp)
	move.w	#$0,$0(a0)
	move.w	#$0,$142(a0)
	lea	(ram_FEBE).l,a1
	move.w	#$1F,d1
	move.l	#$FFFFFFFF,d0
loc_02AAFA:
	move.l	d0,(a1)+
	dbra	d1,loc_02AAFA
	move.w	(sp)+,$0(a0)
	movem.l	(sp)+,d0/d1/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $02A6CA
sub_02AB0A:
	movem.l	d0-d2/a0/a1,-(sp)
	lea	(SoundLock).l,a0
	move.w	$0(a0),-(sp)
	move.w	#$0,$0(a0)
	lea	(ram_FEBE).l,a1
	move.w	$142(a0),d1
	clr.w	d2
loc_02AB2A:
	cmpi.w	#$0,d1
	beq.s	loc_02AB4A
	move.b	$3(a1),d2
	lsr.b	#4,d2
	cmp.w	d0,d2
	bne.s	loc_02AB3E
	move.w	#$1,(a1)
loc_02AB3E:
	adda.l	#$4,a1
	subi.w	#$1,d1
	bra.s	loc_02AB2A
loc_02AB4A:
	move.w	(sp)+,$0(a0)
	movem.l	(sp)+,d0-d2/a0/a1
	rts


; ----------------------------------------------------------------------
; called from $02A37E
sub_02AB54:
	movem.l	d0/d1/a0,-(sp)
	lea	(SoundLock).l,a0
	move.w	$142(a0),d1
	lsl.w	#2,d1
	lea	(ram_FEBE).l,a0
	move.l	d0,$0(a0,d1.w)
	lea	(SoundLock).l,a0
	addi.w	#$1,$142(a0)
	clr.w	d0
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $02A228
sub_02AB82:
	movem.l	d0/d1/a0-a2,-(sp)
	lea	(SoundLock).l,a2
	cmpi.w	#$0,$142(a2)
	beq.s	loc_02ABF8
	lea	(ram_FEBE).l,a0
loc_02AB9A:
	cmpi.w	#$FFFF,(a0)
	beq.s	loc_02ABF8
	subi.w	#$1,(a0)
	bne.s	loc_02ABF2
	move.b	$3(a0),d0
	andi.b	#$F0,d0
	lsl.w	#8,d0
	swap	d0
	move.w	$2(a0),d0
	andi.b	#$F,d0
	ori.b	#$80,d0
	bsr.w	Snd_QueueCommand
	tst.w	d0
	beq.s	loc_02ABCC
	addi.w	#$1,(a0)
	bra.s	loc_02ABF2
loc_02ABCC:
	lea	(ram_FEBE).l,a1
	move.w	(ram_FF3E).l,d0
	subi.w	#$1,d0
	lsl.w	#2,d0
	move.l	$0(a1,d0.w),(a0)
	move.l	#$FFFFFFFF,$0(a1,d0.w)
	subi.w	#$1,$142(a2)
	bra.s	loc_02AB9A
loc_02ABF2:
	adda.w	#$4,a0
	bra.s	loc_02AB9A
loc_02ABF8:
	movem.l	(sp)+,d0/d1/a0-a2
	rts


; ----------------------------------------------------------------------
; called from $02A22C
sub_02ABFE:
	movem.l	d1/d2/a0,-(sp)
	bsr.w	Z80_BusRequest
	tst.b	(Z80_RAM+$4D).l
	beq.w	loc_02AD4C
	cmpi.b	#$1,(Z80_RAM+$4D).l
	bne.s	loc_02AC8A
	clr.w	d1
	move.b	(Z80_RAM+$4E).l,d1
	move.w	#$1,d0
	bsr.w	sub_02AD5E
	bcs.w	loc_02AD4C
	cmpa.l	#ram_FFFF,a0
	beq.w	loc_02AD4C
	lea	(SoundLock).l,a1
	move.l	a0,$146(a1)
loc_02AC42:
	move.b	(a0),d0
	cmp.b	(a0),d0
	bne.s	loc_02AC42
	lsl.w	#8,d0
	adda.l	#$1,a0
loc_02AC50:
	move.b	(a0),d0
	cmp.b	(a0),d0
	bne.s	loc_02AC50
	move.w	d0,$14E(a1)
	adda.l	#$1,a0
	movea.l	$146(a1),a0
	adda.l	#$2,a0
	move.l	a0,$14A(a1)
	clr.l	d0
	move.b	(Z80_RAM+$7).l,d0
	lsl.w	#8,d0
	move.b	(Z80_RAM+$8).l,d0
	addi.l	#Z80_RAM,d0
	movea.l	d0,a1
	bra.w	loc_02ACF2
loc_02AC8A:
	cmpi.b	#$2,(Z80_RAM+$4D).l
	bne.s	loc_02ACBE
	movea.l	(ram_FF46).l,a0
	cmpa.l	#$0,a0
	beq.w	loc_02AD4C
	clr.l	d0
	move.b	(Z80_RAM+$7).l,d0
	lsl.w	#8,d0
	move.b	(Z80_RAM+$8).l,d0
	addi.l	#Z80_RAM,d0
	movea.l	d0,a1
	bra.s	loc_02ACF2
loc_02ACBE:
	cmpi.b	#$3,(Z80_RAM+$4D).l
	bne.w	loc_02AD4C
	movea.l	(ram_FF46).l,a0
	cmpa.l	#$0,a0
	beq.w	loc_02AD4C
	clr.l	d0
	move.b	(Z80_RAM+$9).l,d0
	lsl.w	#8,d0
	move.b	(Z80_RAM+$A).l,d0
	addi.l	#Z80_RAM,d0
	movea.l	d0,a1
loc_02ACF2:
	move.w	#$FF,d1
loc_02ACF6:
	move.b	(a0)+,(a1)+
	dbeq	d1,loc_02ACF6
	beq.s	loc_02AD0E
	lea	(SoundLock).l,a1
	addi.l	#$100,$14A(a1)
	bra.s	loc_02AD4C
loc_02AD0E:
	suba.l	#$1,a1
	clr.l	d0
	move.w	(ram_FF4A).l,d0
	cmpi.w	#$FFFF,d0
	beq.s	loc_02AD3E
	move.b	#$FF,(a1)
	lea	(SoundLock).l,a1
	movea.l	$146(a1),a0
	adda.l	#$2,a0
	adda.l	d0,a0
	move.l	a0,$14A(a1)
	bra.s	loc_02AD4C
loc_02AD3E:
	lea	(SoundLock).l,a1
	move.l	#$0,$14A(a1)
loc_02AD4C:
	move.b	#$0,(Z80_RAM+$4D).l
	bsr.w	Z80_BusRelease
	movem.l	(sp)+,d1/d2/a0
	rts


; ----------------------------------------------------------------------
; called from $02A5DA, $02AC26, $02AE40, $02AE5E
sub_02AD5E:
	movem.l	d1-d4/a1/a2,-(sp)
	lea	(ram_FFDC).l,a1
	move.w	#$3,d2
loc_02AD6C:
	cmpi.l	#$FFFFFFFF,(a1)
	beq.w	loc_02ADC4
	movea.l	(a1),a0
	movea.l	a0,a2
	clr.l	d3
	move.b	(a0)+,d3
	lsl.w	#8,d3
	move.b	(a0)+,d3
	move.l	d3,d4
	lsl.w	#2,d4
	adda.l	d4,a2
	adda.l	#$2,a2
loc_02AD8E:
	cmp.b	(a0),d0
	bne.s	loc_02ADAA
	cmp.b	$1(a0),d1
	bne.s	loc_02ADAA
	move.b	$2(a0),d0
	lsl.w	#8,d0
	move.b	$3(a0),d0
	movea.l	a2,a0
	andi	#$FE,ccr
	bra.s	loc_02ADD6
loc_02ADAA:
	clr.l	d4
	move.b	$2(a0),d4
	lsl.w	#8,d4
	move.b	$3(a0),d4
	adda.l	d4,a2
	adda.l	#$4,a0
	subi.w	#$1,d3
	bne.s	loc_02AD8E
loc_02ADC4:
	adda.l	#$4,a1
	dbra	d2,loc_02AD6C
	move.w	#$3,d0
	ori	#$1,ccr
loc_02ADD6:
	movem.l	(sp)+,d1-d4/a1/a2
	rts
; function 6: a0 = sound bank data
Snd_SetSoundBank:
	movem.l	d1/a1/a2,-(sp)
	cmpi.w	#$4,d1
	bcs.s	loc_02ADF0
	move.w	#$3,d0
	ori	#$1,ccr
	bra.s	loc_02AE32
loc_02ADF0:
	lsl.w	#2,d1
	lea	(ram_FFDC).l,a1
	move.l	a0,$0(a1,d1.w)
	lea	(SoundLock).l,a1
	move.w	(a1),-(sp)
	move.w	#$0,(a1)
	bsr.w	Z80_BusRequest
	lea	(Z80_RAM+$51).l,a2
	move.l	a0,d0
	move.b	d0,$0(a2,d1.w)
	lsr.l	#8,d0
	move.b	d0,$1(a2,d1.w)
	lsr.l	#8,d0
	move.b	d0,$2(a2,d1.w)
	lsr.l	#8,d0
	move.b	d0,$3(a2,d1.w)
	bsr.w	Z80_BusRelease
	move.w	(sp)+,(a1)
	clr.w	d0
loc_02AE32:
	movem.l	(sp)+,d1/a1/a2
	rts
Snd_Func07:
	movem.l	d1/a0/a1,-(sp)
	move.w	#$B,d0
	bsr.w	sub_02AD5E
	bcs.w	loc_02AE86
	movea.l	a0,a1
loc_02AE4A:
	cmpi.b	#$FF,(a1)
	bne.s	loc_02AE54
	clr.w	d0
	bra.s	loc_02AE86
loc_02AE54:
	clr.w	d0
	move.b	(a1),d0
	clr.w	d1
	move.b	$1(a1),d1
	bsr.w	sub_02AD5E
	bcs.s	loc_02AE86
	cmpi.b	#$0,(a1)
	beq.s	loc_02AE70
	cmpi.b	#$4,(a1)
	bne.s	loc_02AE7E
loc_02AE70:
	move.w	d0,d1
	clr.w	d0
	move.b	$1(a1),d0
	bsr.w	Snd_QueueTransfer
	bcs.s	loc_02AE86
loc_02AE7E:
	adda.l	#$2,a1
	bra.s	loc_02AE4A
loc_02AE86:
	movem.l	(sp)+,d1/a0/a1
	rts
Snd_Func08:
	movem.l	d1-d3/a0-a2,-(sp)
	lea	(SoundLock).l,a1
	move.w	(a1),-(sp)
	move.w	#$0,(a1)
	bsr.w	Z80_BusRequest
loc_02AEA0:
	cmpi.w	#$FFFF,(a0)
	beq.w	loc_02AF8E
	lea	(Z80_RAM+$100).l,a1
	move.w	(a0),d0
	move.w	$2(a0),d1
	move.w	#$29,d2
loc_02AEB8:
	cmp.b	(a1),d0
	bne.s	loc_02AEC2
	cmp.b	$1(a1),d1
	beq.s	loc_02AED0
loc_02AEC2:
	adda.l	#$6,a1
	dbra	d2,loc_02AEB8
	bra.w	loc_02AF84
loc_02AED0:
	move.b	$2(a1),d0
	lsl.w	#8,d0
	move.b	$3(a1),d0
	clr.w	d1
	move.b	$4(a1),d1
	lsl.w	#8,d1
	move.b	$5(a1),d1
	move.w	d1,d2
	add.w	d0,d2
	lea	(Z80_RAM).l,a2
loc_02AEF0:
	cmpi.w	#$1F00,d2
	beq.s	loc_02AF06
	move.b	$0(a2,d2.w),$0(a2,d1.w)
	addi.w	#$1,d2
	addi.w	#$1,d1
	bra.s	loc_02AEF0
loc_02AF06:
	clr.w	d1
	move.b	$4(a1),d1
	lsl.w	#8,d1
	move.b	$5(a1),d1
	move.b	#$FF,(a1)
	move.b	#$FF,$1(a1)
	move.b	#$FF,$2(a1)
	move.b	#$FF,$3(a1)
	move.b	#$FF,$4(a1)
	move.b	#$FF,$5(a1)
	lea	(Z80_RAM+$100).l,a1
	move.w	#$29,d2
loc_02AF3E:
	cmpi.b	#$FF,(a1)
	beq.s	loc_02AF60
	clr.w	d3
	move.b	$4(a1),d3
	lsl.w	#8,d3
	move.b	$5(a1),d3
	cmp.w	d1,d3
	bcs.s	loc_02AF60
	sub.w	d0,d3
	move.b	d3,$5(a1)
	lsr.w	#8,d3
	move.b	d3,$4(a1)
loc_02AF60:
	adda.l	#$6,a1
	dbra	d2,loc_02AF3E
	lea	(Z80_RAM+$5).l,a1
	clr.w	d1
	move.b	(a1),d1
	lsl.w	#8,d1
	move.b	$1(a1),d1
	sub.w	d0,d1
	move.b	d1,$1(a1)
	lsr.w	#8,d1
	move.b	d1,(a1)
loc_02AF84:
	adda.l	#$4,a0
	bra.w	loc_02AEA0
loc_02AF8E:
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a1
	move.w	(sp)+,(a1)
	clr.w	d0
	movem.l	(sp)+,d1-d3/a0-a2
	rts
; function 9: clears the command queue in Z80 RAM
Snd_ResetQueue:
	movem.l	a0/a1,-(sp)
	lea	(SoundLock).l,a0
	move.w	(a0),-(sp)
	move.w	#$0,(a0)
	bsr.w	Z80_BusRequest
	lea	(Z80_RAM+$100).l,a0
	move.w	#$FB,d0
loc_02AFC0:
	move.b	#$FF,(a0)+
	dbra	d0,loc_02AFC0
	lea	(Z80_RAM+$3).l,a0
	lea	(Z80_RAM+$5).l,a1
	move.b	(a0)+,(a1)+
	move.b	(a0),(a1)
	bsr.w	Z80_BusRelease
	lea	(SoundLock).l,a0
	move.w	(sp)+,(a0)
	clr.w	d0
	movem.l	(sp)+,a0/a1
	rts
Snd_Func12:
	move.w	sr,-(sp)
	move.w	#$2700,sr
	move.l	d1,d0
	bsr.w	Snd_QueueCommand
	move.w	(sp)+,sr
	rts


; ----------------------------------------------------------------------
; called from $02A094, $02A5D0, $02A65E
Snd_Func0A:
	movem.l	d1/d2/a0,-(sp)
	lea	(ram_FF4E).l,a0
	move.w	(ram_FFCE).l,d0
	move.w	#$1F,d2
loc_02B010:
	bset	#7,$3(a0,d0.w)
	bne.s	loc_02B028
	move.l	d1,$0(a0,d0.w)
	lea	(ram_FFCE).l,a0
	move.w	d0,(a0)
	clr.w	d0
	bra.s	loc_02B040
loc_02B028:
	addi.w	#$4,d0
	cmpi.w	#$80,d0
	bcs.s	loc_02B034
	clr.w	d0
loc_02B034:
	dbra	d2,loc_02B010
	move.w	#$7,d0
	ori	#$1,ccr
loc_02B040:
	movem.l	(sp)+,d1/d2/a0
	rts


; ----------------------------------------------------------------------
; called from $02A224
sub_02B046:
	movem.l	d0/d1/a0,-(sp)
	lea	(ram_FF4E).l,a0
	move.w	(ram_FFD0).l,d1
loc_02B056:
	cmpi.l	#$0,$0(a0,d1.w)
	beq.s	loc_02B084
	cmpi.l	#$80,$0(a0,d1.w)
	beq.s	loc_02B084
	move.l	$0(a0,d1.w),d0
	bsr.w	Snd_QueueCommand
	clr.l	$0(a0,d1.w)
	addi.w	#$4,d1
	cmpi.w	#$80,d1
	bcs.s	loc_02B056
	clr.w	d1
	bra.s	loc_02B056
loc_02B084:
	lea	(ram_FFD0).l,a0
	move.w	d1,(a0)
	movem.l	(sp)+,d0/d1/a0
	rts


; ----------------------------------------------------------------------
; called from $02A134, $02A6EA, $02A768, $02A884, $02A90E, $02A9AE, $02A9EA, $02AC02 (+3 more)
Z80_BusRequest:
	move.w	#$100,(Z80_BUSREQ).l
loc_02B09A:
	btst	#0,(Z80_BUSREQ).l
	bne.s	loc_02B09A
	rts


; ----------------------------------------------------------------------
; called from $02A142, $02A150, $02A744, $02A782, $02A7B0, $02A7EC, $02A860, $02A8A8 (+9 more)
Z80_BusRelease:
	move.w	#$0,(Z80_BUSREQ).l
	rts
