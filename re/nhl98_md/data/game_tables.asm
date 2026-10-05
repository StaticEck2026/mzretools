; ============================================================================
; Tables used by the game engine
; ROM range $0288B2-$029939
; ============================================================================

dat_0288B2:
	dc.b	$01,$0C,$02,$0C,$03,$0C,$04,$0C,$05,$0C,$0A,$0C,$09,$0C,$08,$0C
	dc.b	$06,$0C,$07,$0C,$08,$0C,$09,$0C,$0A,$0C,$05,$0C,$04,$0C,$03,$0C
	dc.b	$01,$07,$02,$07,$03,$07,$04,$07,$05,$07,$0B,$07,$0C,$07,$0D,$07
	dc.b	$06,$07,$07,$07,$08,$07,$09,$07,$0A,$07,$0B,$07,$0C,$07,$0D,$07
	dc.b	$0E,$07,$0F,$07,$10,$07,$11,$07,$12,$07,$0B,$07,$0C,$07,$0D,$07
	dc.b	$12,$07,$11,$07,$10,$07,$0F,$07,$0E,$07,$0D,$07,$0C,$07,$0B,$07
	dc.b	$0E,$03,$0F,$03,$10,$03,$11,$03,$12,$03,$0B,$03,$0C,$03,$0D,$03
	dc.b	$12,$03,$11,$03,$10,$03,$0F,$03,$0E,$03,$0D,$03,$0C,$03,$0B,$03
dat_028932:
	dc.w	$2425,$0026,$0027,$0047,$2D2E,$2527,$0028,$2A29
	dc.w	$1A1B,$1C1D,$1E1F,$2021,$2223,$2F00,$2B00,$2C4A
	dc.w	$4A00,$0102,$0304,$0506,$0708,$090A,$0B0C,$0D0E
	dc.w	$0F10,$1112,$1314,$1516,$1718,$192B,$002C
dat_028970:
	dc.w	$CDB7,$0000,$0000,$00B9,$0000,$0000,$0000,$B84F
	dc.w	$33CD,$3537,$393B,$3D3F,$4143,$B900,$0000,$004A
	dc.w	$4A00,$0204,$0608,$0A0C,$0EF0,$1113,$1517,$191B
	dc.w	$1D1F,$2123,$2527,$292B,$2D2F,$31FF
dat_0289AC:
	dc.w	$0006,$5363,$3100,$0006,$5363,$3200,$0006,$4368
	dc.w	$6B00,$0006,$5050,$3100,$0006,$5050,$3200,$0006
	dc.w	$504B,$3100,$0006,$504B,$3200,$0004,$2047,$0004
	dc.w	$4C44,$0004,$5244,$0004,$4C57,$0004,$4300,$0004
	dc.w	$5257
dat_0289EE:
	dc.w	$0004,$3112,$0004,$3213,$0004,$3314,$0004,$4F54
	dc.w	$0004,$2046,$0004,$3112,$0004,$3213,$0004,$3314
	dc.w	$0004,$4F54,$0004,$2020
dat_028A16:
	dc.w	$0102,$0304,$0204,$0608,$0306,$090C,$0408,$0C10
dat_028A26:
	dc.w	$000E,$000E,$001C,$002A,$0054,$003F,$0054,$0109
	dc.w	$1119,$2129,$3102,$0A12,$1A22,$2A32,$020A,$121A
	dc.w	$222A,$3201,$0911,$1921,$2931,$030B,$131B,$232B
	dc.w	$3305,$0D15,$1D25,$2D35,$040C,$141C,$242C,$3405
	dc.w	$0D15,$1D25,$2D35,$030B,$131B,$232B,$3304,$0C14
	dc.w	$1C24,$2C34,$040C,$141C,$242C,$3403,$0B13,$1B23
	dc.w	$2B33,$050D,$151D,$252D,$35FF
dat_028A90:
	dc.w	$0001,$0204,$0305,$06FF
dat_028A98:
	dc.b	$00,$12
	dc.b	"     Status    ]",0
	dc.b	$00,$00,$00
dat_028AAE:
	dc.b	$00,$12
	dc.b	"[   Overall    ]"
dat_028AC0:
	dc.b	$1F,$BA,$00,$0A,$00,$12
	dc.b	"[   Energy     ]",0
	dc.b	$00,$00,$02,$00,$12
	dc.b	"[   Agility    ]"
dat_028AEC:
	dc.b	$10,$00,$00,$0A,$00,$12
	dc.b	"[    Speed     ]"
dat_028B02:
	dc.b	$08,$00,$00,$0A,$00,$12
	dc.b	"[   Handed     ]",0
	dc.b	$40,$00,$04,$00,$12
	dc.b	"[Off. Awareness]"
dat_028B2E:
	dc.b	$04,$00,$00,$0A,$00,$12
	dc.b	"[Def. Awareness]"
dat_028B44:
	dc.b	$02,$00,$00,$0A,$00,$12
	dc.b	"[  Shot Power  ]"
dat_028B5A:
	dc.b	$01,$00,$00,$0A,$00,$12
	dc.b	"[Shot  Accuracy]"
dat_028B70:
	dc.b	$00,$10,$00,$0A,$00,$12
	dc.b	"[Pass  Accuracy]"
dat_028B86:
	dc.b	$00,$02,$00,$0A,$00,$12
	dc.b	"[Stick Handling]"
dat_028B9C:
	dc.b	$00,$20,$00,$0A,$00,$12
	dc.b	"[    Weight    ]"
dat_028BB2:
	dc.b	$20,$00,$00,$06,$00,$12
	dc.b	"[  Endurance   ]"
dat_028BC8:
	dc.b	$00,$08,$00,$0A,$00,$12
	dc.b	"[Aggressiveness]"
dat_028BDE:
	dc.b	$00,$01,$00,$0A,$00,$12
	dc.b	"[   Checking    "
dat_028BF4:
	dc.b	$00,$80,$00,$0A,$FF,$FF
dat_028BFA:
	dc.b	$00,$12
	dc.b	"     Status    ]",0
	dc.b	$00,$00,$00
dat_028C10:
	dc.b	$00,$12
	dc.b	"[   Overall    ]"
dat_028C22:
	dc.b	$13,$0F,$00,$0A,$00,$12
	dc.b	"[   Agility    ]"
dat_028C38:
	dc.b	$10,$00,$00,$0A,$00,$12
	dc.b	"[    Speed     ]"
	dc.b	$08,$00,$00,$0A,$00,$12
	dc.b	"[  Glove Hand  ]",0
	dc.b	$40,$00,$04,$00,$12
	dc.b	"[Def. Awareness]"
dat_028C7A:
	dc.b	$02,$00,$00,$0A,$00,$12
	dc.b	"[Off. Awareness]"
	dc.b	$04,$00,$00,$0A,$00,$12
	dc.b	"[ Puck Control ]"
dat_028CA6:
	dc.b	$01,$00,$00,$0A,$00,$12
	dc.b	"[ Stick  Right ]"
dat_028CBC:
	dc.b	$00,$08,$00,$0A,$00,$12
	dc.b	"[  Stick Left  ]"
dat_028CD2:
	dc.b	$00,$04,$00,$0A,$00,$12
	dc.b	"[ Glove  Right ]"
dat_028CE8:
	dc.b	$00,$02,$00,$0A,$00,$12
	dc.b	"[  Glove Left  ]"
dat_028CFE:
	dc.b	$00,$01,$00,$0A,$00,$12
	dc.b	"[    Weight      ",0
	dc.b	$00,$06,$FF,$FF
dat_028D1A:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"    GO TO EVENT   ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_028D56:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   RESUME GAME    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  INSTANT REPLAY  ",0
	dc.b	$01,$A2,$F8,$00,$14
	dc.b	"   TEAM ROSTER    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_028DDA:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   RESUME GAME    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  INSTANT REPLAY  ",0
	dc.b	$01,$A2,$F8,$00,$14
	dc.b	"  CHANGE GOALIE   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    EDIT LINES    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"    GAME STATS    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   PLAYER STATS   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	"     Timeout      ",0
	dc.b	$01,$9F,$80,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$14
	dc.b	"x Manual Goalie   ",0
	dc.b	$1D,$10,$8E,$00,$14
	dc.b	" CONTROLLER SETUP ",0
	dc.b	$00,$E6,$00,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_028F66:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   RESUME GAME    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  INSTANT REPLAY  ",0
	dc.b	$01,$A2,$F8,$00,$14
	dc.b	"  CHANGE GOALIE   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    EDIT LINES    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"    GAME STATS    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   PLAYER STATS   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	"     Timeout      ",0
	dc.b	$01,$9F,$80,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$14
	dc.b	"x Manual Goalie   ",0
	dc.b	$1D,$10,$8E,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_0290DA:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   Resume Game    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  Instant Replay  ",0
	dc.b	$01,$A2,$F8,$00,$14
	dc.b	"  Change Goalie   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    Edit Lines    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"    Game Stats    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   Player Stats   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$14
	dc.b	"x Manual Goalie   ",0
	dc.b	$1D,$10,$8E,$00,$14
	dc.b	" CONTROLLER SETUP ",0
	dc.b	$00,$E6,$00,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_02924E:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   Resume Game    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  Instant Replay  ",0
	dc.b	$01,$A2,$F8,$00,$14
	dc.b	"  Change Goalie   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    Edit Lines    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"    Game Stats    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   Player Stats   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$14
	dc.b	"x Manual Goalie   ",0
	dc.b	$1D,$10,$8E,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_0293AA:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"  Start Shootout  ",0
	dc.b	$02,$4D,$92,$00,$14
	dc.b	"  Shootout SetUp  ",0
	dc.b	$1D,$EC,$90,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_02942E:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"    Start Game    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  Change Goalie   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    Edit Lines    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_0294E2:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"    Start Game    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"  Change Goalie   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    Edit Lines    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	"  Playoff Stats   ",0
	dc.b	$01,$9E,$A0,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_0295AE:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"   Resume Game    ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"    Game Stats    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   Player Stats   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	"  Change Goalie   ",0
	dc.b	$01,$A0,$26,$00,$14
	dc.b	"    Edit Lines    ",0
	dc.b	$1D,$C3,$22,$00,$14
	dc.b	"  COACHING STYLE  ",0
	dc.b	$1D,$33,$34,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$14
	dc.b	"    ABORT GAME    ",0
	dc.b	$02,$70,$7C,$00,$04,$FF,$00
dat_0296DA:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"    quit Game     ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"    Game Stats    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   Player Stats   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$04,$FF,$00
dat_0297A6:
	dc.w	$0004,$F901,$0004,$F902,$0014
	dc.b	"    quit Game     ",0
	dc.b	$02,$9F,$C4,$00,$14
	dc.b	"    Game Stats    ",0
	dc.b	$1D,$E7,$24,$00,$14
	dc.b	"   Player Stats   ",0
	dc.b	$1E,$05,$D0,$00,$14
	dc.b	" Scoring Summary  ",0
	dc.b	$1D,$DD,$52,$00,$14
	dc.b	" Penalty Summary  ",0
	dc.b	$1D,$E0,$C4,$00,$14
	dc.b	"   Team Roster    ",0
	dc.b	$1D,$D7,$78,$00,$14
	dc.b	" ALL TIME RECORDS ",0
	dc.b	$1D,$F8,$78,$00,$14
	dc.b	"   Period Stats   ",0
	dc.b	$1D,$E4,$10,$00,$04,$FF,$00,$00,$06,$FE,$06,$F9,$01,$00,$06,$FE
	dc.b	$04,$F9,$01,$00,$14
	dc.b	"       Exit       ",0
	dc.b	$02,$4D,$92,$00,$14
	dc.b	"Set Original lines",0
	dc.b	$02,$6B,$38,$00,$14
	dc.b	"  Save Team Line  ",0
	dc.b	$1D,$CB,$BC,$00,$14
	dc.b	"  Load Team Line  ",0
	dc.b	$1D,$CA,$C2,$00,$04,$FF,$00,$00,$06,$FE,$06,$F9,$01,$00,$06,$FE
	dc.b	$04,$F9,$01,$00,$14
	dc.b	"       Exit       ",0
	dc.b	$02,$4D,$92,$00,$14
	dc.b	"Set Original lines",0
	dc.b	$02,$6B,$38,$00,$14
	dc.b	"  Save Team Line  ",0
	dc.b	$1D,$CB,$BC,$00,$04,$FF,$00

