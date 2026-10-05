; ============================================================================
; Team pointer table and roster records (players, team names, arenas)
; ROM range $00077E-$00B8DD
; ============================================================================


; 62 pointers to the team roster records (two orderings of 31 teams)
RosterTable:
	dc.l	Roster_Anaheim
	dc.l	Roster_Boston
	dc.l	Roster_Buffalo
	dc.l	Roster_Calgary
	dc.l	Roster_Carolina
	dc.l	Roster_Chicago
	dc.l	Roster_Colorado
	dc.l	Roster_Dallas
	dc.l	Roster_Detroit
	dc.l	Roster_Edmonton
	dc.l	Roster_Florida
	dc.l	Roster_LosAngeles
	dc.l	Roster_Montreal
	dc.l	Roster_NewJersey
	dc.l	Roster_NewYorkIslanders
	dc.l	Roster_NewYorkRangers
	dc.l	Roster_Ottawa
	dc.l	Roster_Philadelphia
	dc.l	Roster_Phoenix
	dc.l	Roster_Pittsburgh
	dc.l	Roster_SanJose
	dc.l	Roster_StLouis
	dc.l	Roster_TampaBay
	dc.l	Roster_Toronto
	dc.l	Roster_Vancouver
	dc.l	Roster_Washington
	dc.l	Roster_EaSports
	dc.l	Roster_Credits
	dc.l	Roster_TeamCanada
	dc.l	Roster_TeamUsa
	dc.l	Roster_TeamEurope

dat_0007FA:
	dc.l	Roster_Anaheim
	dc.l	Roster_Boston
	dc.l	Roster_Buffalo
	dc.l	Roster_Calgary
	dc.l	Roster_Carolina
	dc.l	Roster_Chicago
	dc.l	Roster_Colorado
	dc.l	Roster_Dallas
	dc.l	Roster_Detroit
	dc.l	Roster_Edmonton
	dc.l	Roster_Florida
	dc.l	Roster_LosAngeles
	dc.l	Roster_Montreal
	dc.l	Roster_NewJersey
	dc.l	Roster_NewYorkIslanders
	dc.l	Roster_NewYorkRangers
	dc.l	Roster_Ottawa
	dc.l	Roster_Philadelphia
	dc.l	Roster_Phoenix
	dc.l	Roster_Pittsburgh
	dc.l	Roster_SanJose
	dc.l	Roster_StLouis
	dc.l	Roster_TampaBay
	dc.l	Roster_Toronto
	dc.l	Roster_Vancouver
	dc.l	Roster_Washington
	dc.l	Roster_AllStarsEast
	dc.l	Roster_AllStarsWest
	dc.l	Roster_TeamCanada
	dc.l	Roster_TeamUsa
	dc.l	Roster_TeamEurope
; roster: Anaheim Mighty Ducks (Arrowhead Pond Of Anaheim)
Roster_Anaheim:
	dc.w	$0092,$000C,$02EA,$0052,$004C,$0050,$0ECA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0444,$0220,$0EEE,$0440
	dc.w	$0426,$0888,$0202,$0404,$008C,$0C86,$0ECA,$0200
	dc.w	$0402,$0404,$0426,$066A,$0E0E,$0440,$0EEE,$0662
	dc.w	$0CCC,$0888,$0404,$0426,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0103,$060A,$1017,$1100,$0103,$060A,$1017
	dc.w	$1100,$0105,$070C,$1419,$1500,$0104,$080E,$1218
	dc.w	$1A00,$0103,$060A,$1017,$1100,$0105,$070C,$1419
	dc.w	$1500,$0103,$060A,$1017,$1100,$0105,$070C,$1419
	dc.w	$1500,$000C
	dc.b	"Guy Hebert1dCT",0
	dc.b	$30,$54,$44,$00,$14
	dc.b	"Mikhail Shtalenkov5c23",0
	dc.b	$20,$44,$33,$00,$10
	dc.b	"Dmitri Mironov"
	dc.b	$15
	dc.b	"tDD%2&A",0
	dc.b	$10
	dc.b	"Darren VanImpe)"
	dc.b	$83
	dc.b	"",$22,"",$22,"$",$22,"C3",0
	dc.b	$0E
	dc.b	"Bobby Dollas"
	dc.b	$02,$A3
	dc.b	"#S2244",0
	dc.b	$12
	dc.b	"J.J. Daigneault",0
	dc.b	"6d33624D",0
	dc.b	$10
	dc.b	"Daniel Trebil",0
	dc.b	"4t3$2444",0
	dc.b	$0C
	dc.b	"Dave Karpa3"
	dc.b	$82
	dc.b	"",$22,"27",$22,"3&",0
	dc.b	$10
	dc.b	"Jason Marshall(s!2C",$22,"2&",0
	dc.b	$0E
	dc.b	"Paul Kariya",0
	dc.b	$09
	dc.b	"FfE",$22,"fU`",0
	dc.b	$10
	dc.b	"Warren Rychel",0
	dc.b	$16
	dc.b	"s",$22,"29",$22,"!*",0
	dc.b	$10
	dc.b	"Brian Bellows",0
	dc.w	$2383,$2414,$1744,$4141,$0010
	dc.b	"Shawn Antoski",0
	dc.w	$08C1,$2222,$4611,$221A,$000E
	dc.b	"Mike Leclerc'"
	dc.b	$92
	dc.b	"3",$22,"2#3#",0
	dc.b	$10
	dc.b	"Ken Baumgartnr",$22,""
	dc.b	$92
	dc.b	"!",$22,"J",$22,"#+",0
	dc.b	$10
	dc.b	"Steve Rucchin",0
	dc.b	$20,$93
	dc.b	"33B441",0
	dc.b	$0E
	dc.b	"Richard Park2sR#%2",$22,"2",0
	dc.b	$0C
	dc.b	"Kevin Todd"
	dc.b	$12
	dc.b	"R336",$22,"32",0
	dc.b	$10
	dc.b	"Mark Janssens",0
	dc.b	$24,$B1
	dc.b	"",$22,"CF",$22,"C&",0
	dc.b	$0C
	dc.b	"Jari Kurri"
	dc.b	$17,$83
	dc.b	"4D'CTA",0
	dc.b	$0C
	dc.b	"Ted Drury",0
	dc.b	$13
	dc.b	"sC26252",0
	dc.b	$0E
	dc.b	"Sean ProngerT"
	dc.b	$83
	dc.b	"",$22,"3D33#",0
	dc.b	$10
	dc.b	"Teemu Selanne",0
	dc.b	$08
	dc.b	"ffD%fUa",0
	dc.b	$0C
	dc.b	"Joe Sacco",0
	dc.b	$14,$84
	dc.b	"C#%2C#",0
	dc.b	$0E
	dc.b	"J.F. Jomphe",0
	dc.b	"FsC3C333",0
	dc.b	$14
	dc.b	"Peter LeboutillierR"
	dc.b	$84
	dc.b	"3#3#3#",0
	dc.b	$02,$00,$0A
	dc.b	"Anaheim",0
	dc.w	$0006,$414E,$4800,$000E
	dc.b	"Mighty Ducks",0
	dc.b	$1C
	dc.b	"Arrowhead Pond Of Anaheim",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"#334DDDUU"
	dc.b	$FF
; roster: Boston Bruins (Boston Garden)
Roster_Boston:
	dc.w	$0092,$000C,$02E2,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0222,$0EEE,$0200
	dc.w	$00AE,$0888,$0222,$0444,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0AAA,$0EEE,$0EEE
	dc.w	$00AE,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0104,$070C,$0E13,$1A00,$0104,$070C,$0E13
	dc.w	$1A00,$0106,$090F,$1215,$1000,$0105,$0810,$1119
	dc.w	$1800,$0104,$070C,$0E13,$1A00,$0106,$090F,$1215
	dc.w	$1000,$0104,$070C,$0E13,$1A00,$0106,$090F,$1215
	dc.w	$1000,$000C
	dc.b	"Jim Carey",0
	dc.b	"0EDD"
	dc.b	$01,$30,$44,$55,$00,$10
	dc.b	"Robbie Tallas",0
	dc.b	"5C23"
	dc.b	$01,$33,$32,$33,$00,$10
	dc.b	"Anders Myrvold"
	dc.w	$1483,$2322,$0120,$2329,$000E
	dc.b	"Don Sweeney",0
	dc.b	"2DCSD2DB",0
	dc.b	$0E
	dc.b	"Dean Malkoc",0
	dc.b	$44,$B3
	dc.b	"36L22C",0
	dc.b	$0E
	dc.b	"Kyle McLaren"
	dc.b	$18,$93
	dc.b	"2D4222",0
	dc.b	$0E
	dc.b	"Ray Bourque",0
	dc.b	"wd4d$6Eb",0
	dc.b	$10
	dc.b	"Dean Chynoweth(TR"
	dc.b	$12,$14,$32,$24,$22,$00,$0E
	dc.b	"Jon Rohloff",0
	dc.b	"8r",$22,"27",$22,"$)",0
	dc.b	$0C
	dc.b	"Bob Beers",0
	dc.b	$34,$82
	dc.b	"!35!2)",0
	dc.b	$10
	dc.b	"Troy Mallette",0
	dc.b	")r!$9!",$22,""
	dc.b	$19,$00,$0E
	dc.b	"Tim Sweeney",0
	dc.b	"Bs#3"
	dc.b	$18,$33,$22,$21,$00,$0E
	dc.b	"Davis Payne",0
	dc.b	$17
	dc.b	"s2##33",$22,"",0
	dc.b	$0C
	dc.b	"Ted Donato!DDC$4C1",0
	dc.b	$10
	dc.b	"Jozef Stumpel",0
	dc.w	$1653,$3423,$1533,$3541,$0012
	dc.b	"Randy RobitailleH33333",$22,"",$22,"",0
	dc.b	$10
	dc.b	"Trent McCleary%S2",$22,"E",$22,"3&",0
	dc.b	$0E
	dc.b	"Anson Carter"
	dc.b	$11,$63
dat_000DCA:
	dc.b	"2CC33D",0
	dc.b	$0E
	dc.b	"Steve Heinze#cCC72B2",0
	dc.b	$0E
	dc.b	"Sandy Moger",0
	dc.b	$45,$A3,$33,$13
	dc.b	"#322",0
	dc.b	$0C
	dc.b	"Rob Dimaio"
	dc.b	$19
	dc.b	"t22I24$",0
	dc.b	$10
	dc.b	"Landon Wilson",0
	dc.b	$27,$A4
	dc.b	"33D",$22,"33",0
	dc.b	$12
	dc.b	"Sheldon Kennedy",0
	dc.b	"3CR",$22,""
	dc.b	$19,$33,$23,$21,$00,$0E
	dc.b	"Jeff Odgers",0
	dc.b	$36,$92
	dc.b	"",$22,"#8",$22,"A)",0
	dc.b	$10
	dc.b	"Jason Allison",0
	dc.b	"A3",$22,"333DD",0
	dc.b	$10
	dc.b	"Jean-Yves Roy",0
	dc.b	"C333",$22,"",$22,"33",0
	dc.b	$02,$00,$08
	dc.b	"Boston",0
	dc.b	$06,$42,$4F,$53,$00,$00,$08
	dc.b	"Bruins",0
	dc.b	$10
	dc.b	"Boston Garden",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"33DDUUUU"
	dc.b	$FF
; roster: Buffalo Sabres (Memorial Auditorium)
Roster_Buffalo:
	dc.w	$0092,$000C,$02E4,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0000,$0EEE,$0444
	dc.w	$000A,$0888,$0000,$0222,$008C,$0C86,$0EC6,$0000
	dc.w	$0000,$0222,$0444,$066A,$0666,$0888,$0EEE,$0CAA
	dc.w	$000A,$0888,$0000,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0104,$080D,$1319,$0C00,$0104,$080D,$1319
	dc.w	$0C00,$0106,$090B,$1418,$1600,$0105,$070F,$1310
	dc.w	$1500,$0104,$080D,$1219,$0C00,$0106,$090B,$1418
	dc.w	$1600,$0104,$080D,$1319,$0C00,$0106,$090B,$1418
	dc.w	$1600,$0010
	dc.b	"Dominik Hasek",0
	dc.b	"9FCf"
	dc.b	$01,$40,$66,$66,$00,$10
	dc.b	"Steve Shields",0
	dc.w	$3194,$4043,$0130,$3333,$0012
	dc.b	"Andrei Trefilov",0
	dc.b	"0S23"
	dc.b	$01,$10,$33,$33,$00,$0E
	dc.b	"Garry Galley"
	dc.b	$03
	dc.b	"s42$2%A",0
	dc.b	$0E
	dc.b	"Bob Boughner"
	dc.w	$0682,$2122,$3211,$2318,$0010
	dc.b	"Darryl Shannon"
	dc.b	$08,$92
	dc.b	"",$22,"C4",$22,"2#",0
	dc.b	$0E
	dc.b	"Mike Wilson",0
	dc.b	$04
	dc.b	"S32$2$1",0
	dc.b	$10
	dc.b	"Alexei Zhi"
dat_001000:
	dc.b	"tnikDeD#6BEA",0
	dc.b	$0C
	dc.b	"Jay McKee",0
	dc.b	"ts333324",0
	dc.b	$12
	dc.b	"Richard Smehlik",0
	dc.b	$42,$A3
	dc.b	"#DF236",0
	dc.b	$0A
	dc.b	"Brad May"
	dc.b	$10,$93
	dc.b	"34T",$22,"B&",0
	dc.b	$10
	dc.b	"Randy Burridge"
	dc.b	$12
	dc.b	"s#38432",0
	dc.b	$10
	dc.b	"Miroslav Satan"
	dc.b	$81
	dc.b	"dT3$43A",0
	dc.b	$10
	dc.b	"Michal Grosek",0
	dc.b	$18
	dc.b	"S3#'2#4",0
	dc.b	$10
	dc.b	"Pat LaFontaine"
	dc.b	$16
	dc.b	"UED'TDR",0
	dc.b	$12
	dc.b	"Brian Holzinger",0
	dc.b	$19,$54,$43,$12
	dc.b	"",$22,"DDA",0
	dc.b	$0E
	dc.b	"Derek Plante&ET3$CDA",0
	dc.b	$0C
	dc.b	"Mike Peca",0
	dc.b	"'S4C)331",0
	dc.b	$12
	dc.b	"Anatoli Semenov",0
	dc.b	$93
	dc.b	"sD3&2C3",0
	dc.b	$10
	dc.b	"Wayn"
dat_001110:
	dc.b	"e Primeau",0
	dc.b	"vs33332#",0
	dc.b	$0A
	dc.b	"Rob Ray",0
	dc.b	$32,$A2,$22,$12
	dc.b	"=",$22,"2-",0
	dc.b	$12
	dc.b	"Matthew Barnaby",0
	dc.b	"6C3$J33;",0
	dc.b	$0C
	dc.b	"Jason Dawe"
	dc.b	$17,$84
	dc.b	"S#B4C1",0
	dc.b	$0C
	dc.b	"Dixon Ward"
	dc.b	$15,$83,$23,$13
	dc.b	"5#",$22,"!",0
	dc.b	$10
	dc.b	"Donald Audette(TD4+4C2",0
	dc.b	$0A
	dc.b	"Ed Ronan"
	dc.b	$05
	dc.b	"c33C33",$22,"",0
	dc.b	$02,$00,$0A
	dc.b	"Buffalo",0
	dc.w	$0006,$4255,$4600,$0008
	dc.b	"Sabres",0
	dc.b	$16
	dc.b	"Memorial Auditorium",0
	dc.b	$00,$01,$11
	dc.b	"",$22,"",$22,"33DDDUUU"
	dc.b	$FF
; roster: Calgary Flames (Olympic Saddledome)
Roster_Calgary:
	dc.w	$0092,$000C,$02F0,$0052,$004C,$0050,$0CCA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$000E,$0006,$0EEE,$000A
	dc.w	$008C,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0006,$000A,$000E,$046A,$0E0E,$0888,$0EEE,$0EEE
	dc.w	$00AE,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0104,$0B0D,$1417,$1100,$0104,$0B0D,$1417
	dc.w	$1100,$0106,$090F,$1618,$0E00,$0103,$050D,$1319
	dc.w	$1A00,$0104,$0B0D,$1417,$1100,$0106,$090F,$1618
	dc.w	$0E00,$0104,$0B0D,$1417,$1100,$0106,$090F,$1618
	dc.w	$0E00,$000E
	dc.b	"Trevor Kidd",0
	dc.b	"74CC"
	dc.b	$02,$00,$44,$44,$00,$10
	dc.b	"Dwayne Roloson0C33"
	dc.b	$01,$00,$33,$33,$00,$10
	dc.b	"Tommy Albelin",0
	dc.b	$05
	dc.b	"s3B",$22,"1C1",0
	dc.b	$0E
	dc.b	"Yves Racine",0
	dc.b	"6dB461D2",0
	dc.b	$12
	dc.b	"Glen Featherstn",0
	dc.b	$04,$B2
	dc.b	"",$22,"2D",$22,"$(",0
	dc.b	$10
	dc.b	"James Patrick",0
	dc.b	$03,$94
	dc.b	"33'25A",0
	dc.b	$10
	dc.b	"Jamie Allison",0
	dc.b	$02
	dc.b	"s33$3",$22,"",$22,"",0
	dc.b	$10
	dc.b	"Joel Bouchar"
dat_001324:
	dc.b	$64,$00,$06
	dc.b	"C333333",0
	dc.b	$0E
	dc.b	"Todd Simpson'C433333",0
	dc.b	$0C
	dc.b	"Cale Hulse)S333333",0
	dc.b	$12
	dc.b	"Zarley Zalapski",0
	dc.b	$33,$A5
	dc.b	"D44CT1",0
	dc.b	$10
	dc.b	"Mike Sullivan",0
	dc.b	"2cC",$22,""
	dc.b	$16,$32,$34,$31,$00,$0E
	dc.b	"German Titov"
	dc.b	$13
	dc.b	"tE4",$22,"D3A",0
	dc.b	$14
	dc.b	"Hnat Domenichelli",0
	dc.b	$17
	dc.b	"c333333",0
	dc.b	$10
	dc.b	"Marty McInnis",0
	dc.b	$18
	dc.b	"DSB%331",0
	dc.b	$0E
	dc.b	"Todd Hlushko DSB%321",0
	dc.b	$0A
	dc.b	"Ed Ward",0
	dc.b	"B333"
dat_0013F8:
	dc.b	"#331",0
	dc.b	$10
	dc.b	"Jonas Hoglund",0
	dc.b	"DcD4BDDC",0
	dc.b	$10
	dc.b	"Cory Stillman",0
	dc.b	$16
	dc.b	"T3",$22,"$351",0
	dc.b	$0E
	dc.b	"Dave Gagner",0
	dc.b	"Qd43$3BB",0
	dc.b	$0E
	dc.b	"Corey Millen4CS",$22,""
	dc.b	$19,$33,$34,$31,$00,$0E
	dc.b	"Aaron Gavey",0
	dc.b	"#TBC4#43",0
	dc.b	$10
	dc.b	"Theoren Fleury"
	dc.b	$14
	dc.b	"%UDEUDE",0
	dc.b	$10
	dc.b	"Jarome Iginla",0
	dc.b	$12
	dc.b	"dDER4DB",0
	dc.b	$10
	dc.b	"Sandy McCarthy"
	dc.b	$15
	dc.b	"r",$22,"",$22,"J32+",0
	dc.b	$0E
	dc.b	"Ronnie Stern",$22,""
	dc.b	$82
	dc.b	"",$22,"",$22,"7##&",0
	dc.b	$02,$00,$0A
	dc.b	"Calgary",0
	dc.w	$0006,$4347,$5900,$0008
	dc.b	"Flames",0
	dc.b	$14
	dc.b	"Olympic Saddledome",0
	dc.b	$11,$11
	dc.b	"",$22,"",$22,"#333DDUU"
	dc.b	$FF
; roster: Chicago Blackhawks (United Center)
Roster_Chicago:
	dc.w	$0092,$000C,$02E4,$0052,$004C,$0050,$0CCA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0262,$0000,$0EEE,$0222
	dc.w	$000A,$0888,$0222,$0444,$008C,$0C86,$0ECA,$0200
	dc.w	$0004,$0008,$000C,$046A,$0E0E,$0200,$0EEE,$0222
	dc.w	$0CCC,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0108,$0A0C,$1116,$1000,$0108,$0A0C,$1116
	dc.w	$1000,$0105,$090E,$1419,$1500,$0106,$070F,$121A
	dc.w	$1800,$0108,$0A0C,$1116,$1000,$0105,$090E,$1419
	dc.w	$1500,$0108,$0A0C,$1116,$1000,$0105,$090E,$1419
	dc.w	$1500,$000E
	dc.b	"Jeff Hackett1UCE"
	dc.b	$01,$10,$44,$55,$00,$10
	dc.b	"Chris Terreri",0
	dc.b	"@$C3"
	dc.b	$01,$30,$44,$44,$00,$10
	dc.b	"Michal Sykora",0
	dc.b	$08,$B3
	dc.b	"24$",$22,"11",0
	dc.b	$0E
	dc.b	"Keith Carney"
	dc.b	$04,$92
	dc.b	"32$241",0
	dc.b	$0E
	dc.b	"Steve Smith",0
	dc.b	$05,$B4
	dc.b	"CSV",$22,"RF",0
	dc.b	$10
	dc.b	"Enrico Ciccone9"
	dc.b	$92
	dc.b	"",$22,"3J",$22,"2*",0
	dc.b	$0E
	dc.b	"Cam Russell",0
	dc.b	$08
	dc.b	"R!2X!2&",0
	dc.b	$0C
	dc.b	"Gary Suter uDDFCTA",0
	dc.b	$10
	dc.b	"Eric Weinrich",0
	dc.b	$02,$A3
	dc.b	"C362C1",0
	dc.b	$10
	dc.b	"Chris Chelios",0
	dc.b	$07
	dc.b	"tEegDdE",0
	dc.b	$0C
	dc.b	"Eric Daze",0
	dc.b	$55,$A3
	dc.b	"DD",$22,"DDA",0
	dc.b	$0E
	dc.b	"James Black",0
	dc.b	"8c31",$22,"c",$22,"Y",0
	dc.b	$0E
	dc.b	"Ethan Moreau"
	dc.b	$19,$83
	dc.b	"$3C344",0
	dc.b	$0E
	dc.b	"Bob Probert",0
	dc.b	$24,$B2
	dc.b	"33F#",$22,";",0
	dc.b	$12
	dc.b	"Jean-Yves Leroux73332333",0
	dc.b	$10
	dc.b	"Murray Craven",0
	dc.b	"2c3C6432",0
	dc.b	$10
	dc.b	"Alexei Zhamnov&uU4$TUQ",0
	dc.b	$0E
	dc.b	"Jeff Shantz",0
	dc.b	$11
	dc.b	"sCB7253",0
	dc.b	$0E
	dc.b	"Brent Sutter"
	dc.b	$12
	dc.b	"b#SI3D5",0
	dc.b	$0E
	dc.b	"Denis Savard"
	dc.w	$1855,$3433,$1543,$3641,$0010
	dc.b	"Steve Dubinsky"
	dc.b	$14
	dc.b	"s3#&3#1",0
	dc.b	$0E
	dc.b	"Tony Amonte",0
	dc.w	$1064,$5634,$1245,$4551,$000E
	dc.b	"Jim Cummins",0
	dc.b	$15,$91,$21,$21,$35,$12
dat_0017A2:
	dc.b	$22,$2A,$00,$0E
	dc.b	"Kevin Miller"
	dc.b	$16
	dc.b	"tDC%3C1",0
	dc.b	$0C
	dc.b	"Ulf Dahlen",$22,""
	dc.b	$84
	dc.b	"4464TB",0
	dc.b	$14
	dc.b	"Sergei Krivokrasv",0
	dc.b	"%DD$"
	dc.w	$1442,$2231,$0002,$000A
	dc.b	"Chicago",0
	dc.w	$0006,$4348,$4900,$000C
	dc.b	"Blackhawks",0
	dc.b	$10
	dc.b	"United Center",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"334DDEUU"
	dc.b	$FF
; roster: Colorado Colorado (Nichols Arena)
Roster_Colorado:
	dc.w	$0092,$000C,$02B4,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$000A,$0226,$0EEE,$0228
	dc.w	$0842,$0888,$0000,$0222,$008C,$0C86,$0EC6,$0000
	dc.w	$0004,$0226,$0228,$066A,$0666,$0620,$0EEE,$0A42
	dc.w	$0CAA,$0888,$0000,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0104,$090C,$1116,$1200,$0104,$090C,$1116
	dc.w	$1200,$0103,$060F,$1215,$1300,$0105,$080D,$1018
	dc.w	$1400,$0104,$090C,$1116,$1200,$0103,$060F,$1215
	dc.w	$1300,$0104,$090C,$1116,$1200,$0103,$060F,$1215
	dc.w	$1300,$000E
	dc.b	"Patrick Roy",0
	dc.b	"3fDe",0
	dc.b	$40,$66,$55,$00,$12
	dc.b	"Craig Billington"
	dc.w	$0145,$3333,$0130,$4444,$0010
	dc.b	"Alexei Gusarov"
	dc.b	$05
	dc.b	"dC3$24A",0
	dc.b	$12
	dc.b	"Sandis Ozolinsh",0
	dc.b	$08
	dc.b	"uTd",$22,"DUR",0
	dc.b	$12
	dc.b	"Sylvain Lefebvre"
	dc.b	$02,$93
	dc.b	"2B2!E1",0
	dc.b	$0C
	dc.b	"Uwe Krupp",0
	dc.b	$04,$C3
	dc.b	"#492B2",0
	dc.b	$10
	dc.b	"Brent Severyn",0
	dc.b	$23,$A2
	dc.b	"!36",$22,"2&",0
	dc.b	$0C
	dc.b	"Jon Klemm",0
	dc.b	$24,$82
	dc.b	"#27!21",0
	dc.b	$0C
	dc.b	"Adam FooteR"
	dc.b	$84
	dc.b	"4B9146",0
	dc.b	$0E
	dc.b	"Aaron Miller"
	dc.b	$03
	dc.b	"TC3DD44",0
	dc.b	$0E
	dc.b	"Eric Messier)S332333",0
	dc.b	$12
	dc.b	"Valeri Kamensky",0
	dc.b	$13,$85
	dc.b	"T%7UDQ",0
	dc.b	$0E
	dc.b	"Yves Sarault"
	dc.b	$15
	dc.b	"S334331",0
	dc.b	$0E
	dc.b	"Rene Corbet",0
	dc.w	$2064,$3413,$1433,$2231,$000C
	dc.b	"Mike Ricci"
	dc.b	$09
	dc.b	"tCCDDDE",0
	dc.b	$0C
	dc.b	"Joe Sakic",0
	dc.b	$19
	dc.b	"dFD$UUa",0
	dc.b	$10
	dc.b	"Peter Forsberg!dFDDT5e",0
	dc.b	$10
	dc.b	"Stephane Yelle&33#"
	dc.b	$16,$33,$24,$41,$00,$0E
	dc.b	"Eric Lacroix("
	dc.b	$83
	dc.b	"3#D32%",0
	dc.b	$0E
	dc.b	"Keith Jones",0
	dc.b	$11
	dc.b	"s4CT3A5",0
	dc.b	$10
	dc.b	"Adam Deadmarsh"
	dc.b	$18
	dc.b	"s43CD4E",0
	dc.b	$10
	dc.b	"Claude Lemieux",$22,""
	dc.b	$B3
	dc.b	"DDC4C9",0
	dc.b	$0C
	dc.b	"Mike Keane%SCBE2B5",0
	dc.b	$0E
	dc.b	"Scott Young",0
	dc.b	"HsT5"
	dc.w	$1533,$3342,$0002,$000A
	dc.b	"Colorado",0
	dc.b	$06,$43,$4F,$4C,$00,$00,$0A
	dc.b	"Colorado",0
	dc.b	$10
	dc.b	"Nichols Arena",0
	dc.b	$00,$11,$11,$12
	dc.b	"",$22,"#3DDUUU"
	dc.b	$FF,$FF
; roster: Dallas Stars (Reunion Arena)
Roster_Dallas:
	dc.w	$0092,$000C,$02DE,$0052,$004C,$0050,$0ECA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0068,$0200,$0EEE,$0222
	dc.w	$0260,$0888,$0222,$0444,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0AAA,$0EEE,$0EEE
	dc.w	$0260,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0103,$070E,$0F17,$1A00,$0103,$070E,$0F17
	dc.w	$1A00,$0105,$0A0D,$1516,$1300,$0104,$090C,$1219
	dc.w	$1800,$0103,$070E,$0F17,$1A00,$0105,$0A0D,$1516
	dc.w	$1300,$0103,$070E,$0F17,$1A00,$0105,$0A0D,$1516
	dc.w	$1300,$000C
	dc.b	"Andy Moog",0
	dc.b	"5C3T"
	dc.b	$01,$40,$44,$44,$00,$0E
	dc.b	"Arturs Irbe",0
	dc.b	"2S33"
	dc.b	$01,$20,$33,$44,$00,$10
	dc.b	"Derian Hatcher"
	dc.b	$02,$93
	dc.b	"",$22,"4F2C'",0
	dc.b	$0E
	dc.b	"Craig Ludwig"
	dc.b	$03,$C2
	dc.b	"!BB 3&",0
	dc.b	$10
	dc.b	"Grant Ledyard",0
	dc.b	$12,$93
	dc.b	"3",$22,"&2$1",0
	dc.b	$0C
	dc.b	"Mike Lalor"
	dc.b	$18
	dc.b	"r!28!3F",0
	dc.b	$0E
	dc.b	"Sergei ZubovVuUE#TEa",0
	dc.b	$14
	dc.b	"Richard Matvichuk",0
	dc.b	"$s3",$22,"&242",0
	dc.b	$0E
	dc.b	"Dan Keczmer",0
	dc.b	"",$22,"C4C3334",0
	dc.b	$0E
	dc.b	"Darryl Sydor"
	dc.w	$0594,$3323,$1432,$3441,$000C
	dc.b	"Bill Huard"
	dc.b	$17,$A2
	dc.b	"2#F",$22,"29",0
	dc.b	$0C
	dc.b	"Dave Reid",0
	dc.b	$14,$93
	dc.b	"2S6$D#",0
	dc.b	$0C
	dc.b	"Greg Adams#tD#(DDA",0
	dc.b	$0E
	dc.b	"Benoit Hogue3tT3"
	dc.b	$14,$44,$45,$41,$00,$0E
	dc.b	"Mike Modano",0
	dc.w	$0976,$6645,$1455,$5561,$000E
	dc.b	"Todd Harvey",0
	dc.b	$10
	dc.b	"cB#E#",$22,"5",0
	dc.b	$10
	dc.b	"Guy Carbonneau!c",$22,"B72C1",0
	dc.b	$0E
dat_001D1E:
	dc.b	"Neal Broten",0
	dc.b	$07
	dc.b	"D3S(24B",0
	dc.b	$0C
	dc.b	"Bob Bassen(D224#3#",0
	dc.b	$12
	dc.b	"Brent Gilc"
dat_001D52:
	dc.b	"hrist",0
	dc.b	"Ac4CF#21",0
	dc.b	$10
	dc.b	"Joe Nieuwendyk%"
	dc.b	$84
	dc.b	"5D&SBA",0
	dc.b	$12
	dc.b	"Jamie Langenbrnr"
	dc.w	$1554,$4424,$1544,$2441,$000E
	dc.b	"Pat Verbeek "
	dc.b	$16
	dc.b	"tE4C5DD",0
	dc.b	$0E
	dc.b	"Mike Kennedy9B#",$22,"432",$22,"",0
	dc.b	$10
	dc.b	"Jere Lehtinen",0
	dc.b	"&d42%B4A",0
	dc.b	$10
	dc.b	"Grant Marshall)dB2E234",0
	dc.b	$02,$00,$08
	dc.b	"Dallas",0
	dc.b	$06,$44,$41,$4C,$00,$00,$08
	dc.b	"Stars",0
	dc.b	$00,$10
	dc.b	"Reunion Arena",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"33DDDDUU"
	dc.b	$FF
; roster: Detroit Red Wings (Joe Louis Sports Arena)
Roster_Detroit:
	dc.w	$0092,$000C,$02FA,$0052,$004C,$0050,$0CCA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0006,$0EEE,$000A
	dc.w	$000A,$0888,$0004,$0006,$008C,$0C86,$0ECA,$0200
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0AAA,$0EEE,$0EEE
	dc.w	$0CCC,$0888,$0004,$0008,$008A,$0C86,$0000,$0000
	dc.w	$C100,$0103,$050C,$1317,$1000,$0103,$050C,$1317
	dc.w	$1100,$0104,$090D,$1014,$1500,$0106,$0A0E,$1218
	dc.w	$1A00,$0103,$050C,$1317,$1000,$0104,$090D,$1014
	dc.w	$1500,$0103,$050C,$1317,$1000,$0104,$090D,$1014
	dc.w	$1500,$000E
	dc.b	"Chris Osgood04CT"
	dc.b	$01,$30,$55,$44,$00,$0E
	dc.b	"Mike Vernon",0
	dc.b	")DCT"
	dc.b	$01,$30,$55,$44,$00,$0E
	dc.b	"Larry MurphyU"
	dc.b	$A4
	dc.b	"ET#CUa",0
	dc.b	$12
	dc.b	"Viachslv Fetisov"
	dc.b	$02,$A3
	dc.b	"3C$24Q",0
	dc.b	$12
	dc.b	"Niklas Lidstrom",0
	dc.b	$05
	dc.b	"UDE",$22,"5EA",0
	dc.b	$0E
	dc.b	"Jamie Pushor"
	dc.b	$04
	dc.b	"TC33336",0
	dc.b	$0E
	dc.b	"Mike Ramsey",0
	dc.b	"#r",$22,"B6",$22,"32",0
	dc.b	$0C
	dc.b	"Aaron Ward'C33D332",0
	dc.b	$0C
	dc.b	"Bob Rouse",0
	dc.b	$03,$A3
	dc.b	"!BK!B$",0
	dc.b	$16
	dc.b	"Vladimir Kostantinv",0
	dc.b	$16
	dc.b	"dCSc3TX",0
	dc.b	$12
	dc.b	"Brendan Shanahan"
	dc.b	$14,$A4
	dc.b	"FFf5dF"
dat_001FB8:
	dc.b	$00,$12
	dc.b	"Vyachslv Kozlov",0
	dc.w	$1355,$5434,$1244,$3351,$000E
	dc.b	"Kirk Maltby",0
	dc.b	$18
	dc.b	"s227",$22,"C&",0
	dc.b	$12
	dc.b	"Tomas Holmstrom",0
	dc.b	$15
	dc.b	"dC34C33",0
	dc.b	$10
	dc.b	"Igor Lariono"
dat_002010:
	dc.w	$7600,$0844,$4533,$1243,$3561,$0010
	dc.b	"Steve Yzerman",0
	dc.w	$1965,$5644,$1455,$6561,$000E
	dc.b	"Kris Draper",0
	dc.b	"3sB2",$22,"241",0
	dc.b	$0C
	dc.b	"Tim Taylor7c32$35A",0
	dc.b	$10
	dc.b	"Sergei Fedorov"
	dc.b	$91
	dc.b	"vfT$eTa",0
	dc.b	$14
	dc.b	"Mathieu Dandenault"
	dc.b	$11
	dc.b	"TC3D334",0
	dc.b	$0C
	dc.b	"Doug Brown"
	dc.b	$17
	dc.b	"c2B73C2",0
	dc.b	$12
	dc.b	"Martin Lapointe",0
	dc.b	$20,$92
	dc.b	"#",$22,"%##",$22,"",0
	dc.b	$12
	dc.b	"Tomas Sandstrom",0
	dc.b	$28,$94
	dc.b	"E6&4AD",0
	dc.b	$10
	dc.b	"Darren McCarty%"
	dc.b	$A4
	dc.b	"33U3CK",0
	dc.b	$10
	dc.b	"Michael Knuble",$22,"c33D334",0
	dc.b	$0C
	dc.b	"Joey Kocur&"
	dc.b	$82,$11,$32
dat_002118:
	dc.b	":!#*",0
	dc.b	$02,$00,$0A
	dc.b	"Detroit",0
	dc.w	$0006,$4445,$5400,$000C
	dc.b	"Red Wings",0
	dc.b	$00,$18
	dc.b	"Joe Louis Sports Arena",0
	dc.b	$11,$11
	dc.b	"",$22,"",$22,"33DDEUUU"
	dc.b	$FF
; roster: Edmonton Oilers (Northlands Coliseum)
Roster_Edmonton:
	dc.w	$0092,$000C,$02E0,$0052,$004C,$0050,$0EC6,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0600,$0EEE,$0C00
	dc.w	$0068,$0888,$0600,$0C00,$008C,$0C86,$0EC6,$0200
	dc.w	$0400,$0A00,$0E20,$066A,$0E0E,$0068,$0EEE,$028A
	dc.w	$0CCC,$0888,$0600,$0C00,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0109,$040C,$1216,$1400,$0109,$040C,$1216
	dc.w	$1400,$0105,$060D,$1117,$1800,$0103,$070F,$1319
	dc.w	$1500,$0109,$040C,$1216,$1400,$0105,$060D,$1117
	dc.w	$1800,$0109,$040C,$1216,$1400,$0105,$060E,$1117
	dc.w	$1800,$0010
	dc.b	"Curtis Joseph",0
	dc.b	"1e4T"
	dc.b	$01,$30,$55,$55,$00,$0E
	dc.b	"Bob Essensa",0
	dc.b	"0C33"
	dc.b	$01,$10,$33,$33,$00,$12
	dc.b	"Luke Richardson",0
	dc.b	$22,$B3
	dc.b	"12H!3(",0
	dc.b	$12
	dc.b	"Bryan Marchment",0
	dc.b	$24,$83
	dc.b	"2BV",$22,"46",0
	dc.b	$0C
	dc.b	"Kevin Lowe"
	dc.b	$04,$82
	dc.b	"",$22,"B42DD",0
	dc.b	$12
	dc.b	"Daniel McGillis",0
	dc.b	"#c43D333",0
	dc.b	$12
	dc.b	"Donald Dufresne",0
	dc.w	$3492,$2132,$3612,$2321,$000E
	dc.b	"Greg Devries"
	dc.b	$05,$A2
	dc.b	"!",$22,"",$22,"!3",$22,"",0
	dc.b	$10
	dc.b	"Boris Mironov",0
	dc.w	$0275,$4312,$1532,$3533,$0010
	dc.b	"Drew BannisterUC334333",0
	dc.b	$10
	dc.b	"Todd Marchant",0
	dc.b	"&tS#"
	dc.b	$14,$33,$33,$31,$00,$10
	dc.b	"Louie Debrusk",0
	dc.w	$29C2,$1212,$3622,$2218,$0012
	dc.b	"Andrei KovalenkoQ4D46DDB",0
	dc.b	$10
	dc.b	"Dean McAmmond",0
	dc.b	"7tS3",$22,"#41",0
	dc.b	$0C
	dc.b	"Rem Murray"
	dc.b	$17
	dc.b	"TD44DDB",0
	dc.b	$0C
	dc.b	"Ryan Smyth"
	dc.b	$94
	dc.b	"sD2D",$22,"4B",0
	dc.b	$10
	dc.b	"Mats Lindgren",0
	dc.b	$14
	dc.b	"TC33334",0
	dc.b	$0E
	dc.b	"Jason Arnott"
	dc.b	$07,$84
	dc.b	"E45D"
dat_002398:
	dc.b	$44,$43,$00,$0E
	dc.b	"Doug Weight",0
	dc.b	"9dE4",$22,"DEQ",0
	dc.b	$0E
	dc.b	"Steve Kelly",0
	dc.b	$10
	dc.b	"DD33333",0
	dc.b	$12
	dc.b	"Ralph Intranuovo"
	dc.b	$09
	dc.b	"3333333",0
	dc.b	$0C
	dc.b	"Mike Grier%dD4443D",0
	dc.b	$0C
	dc.b	"Petr Klima"
	dc.w	$8575,$4414,$1544,$4241,$0012
	dc.b	"Kelly Buchberger"
	dc.b	$16,$A3
	dc.b	"2BB#36",0
	dc.b	$14
	dc.b	"Mariusz Czerkawski!sD"
	dc.b	$12,$03,$43,$33,$41,$00,$02,$00,$0A
	dc.b	"Edmonton",0
	dc.b	$06,$45,$44,$4D,$00,$00,$08
	dc.b	"Oilers",0
	dc.b	$16
	dc.b	"Northlands Coliseum",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"#334DEU_"
	dc.b	$FF
; roster: Florida Panthers (Miami Arena)
Roster_Florida:
	dc.w	$0092,$000C,$02F0,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$026A,$0008,$0EEE,$000E
	dc.w	$008E,$0888,$0800,$0C20,$008C,$0C86,$0ECA,$0200
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0800,$0EEE,$0C00
	dc.w	$00AE,$0888,$0C00,$0E20,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0107,$080B,$1318,$1600,$0107,$080B,$1318
	dc.w	$1600,$0104,$060E,$0F19,$1A00,$0105,$0A0D,$1517
	dc.w	$1300,$0107,$080E,$1318,$1600,$0104,$060B,$0F19
	dc.w	$1A00,$0107,$080E,$1318,$1600,$0104,$060B,$0F19
	dc.w	$1A00,$0012
	dc.b	"John Vanbsbrouk",0
	dc.b	"444T"
	dc.b	$01,$30,$55,$55,$00,$12
	dc.b	"Mark Fitzpatrik",0
	dc.b	"0s24"
	dc.b	$01,$10,$44,$44,$00,$10
	dc.b	"Terry Carkner",0
	dc.b	$02,$A3
	dc.b	"",$22,"2F",$22,"56",0
	dc.b	$10
	dc.b	"Robert Svehla",0
	dc.b	"$s$C",$22,"C5B",0
	dc.b	$0E
	dc.b	"Geoff Smith",0
	dc.b	$25,$93
	dc.b	"22624%",0
	dc.b	$10
	dc.b	"Rhett Warrener"
	dc.b	$07
	dc.b	"DC34D3$",0
	dc.b	$10
	dc.b	"Per Gustafsson"
	dc.b	$04
	dc.b	"TCD$336",0
	dc.b	$10
	dc.b	"Ed Jovanovski",0
	dc.b	$55,$94
	dc.b	"DSh#35",0
	dc.b	$0C
	dc.b	"Paul Laus",0
	dc.b	$03,$92
	dc.b	"!2U!4*",0
	dc.b	$0E
	dc.b	"Gord Murphy",0
	dc.w	$0585,$4334,$1532,$3441,$000C
	dc.b	"Dave Lowry"
	dc.b	$10,$82
	dc.b	"336",$22,"21",0
	dc.b	$0E
	dc.b	"Bill Lindsay"
	dc.b	$11
	dc.b	"b#C$#22",0
	dc.b	$0C
	dc.b	"Mike Hough"
	dc.b	$18
	dc.b	"r#CF",$22,"36",0
	dc.b	$12
	dc.b	"Johan Garpenlov",0
	dc.b	")dC#"
	dc.b	$02,$33,$34,$41,$00,$0E
	dc.b	"Kirk Muller",0
	dc.b	$09,$93
	dc.b	"3D43EC",0
	dc.b	$0E
	dc.b	"Chris Wells",0
	dc.b	$23,$A1
	dc.b	"##4",$22,"",$22,"$",0
	dc.b	$10
	dc.b	"Steve Washburn",$22,"3333333",0
	dc.b	$12
	dc.b	"Brian Skrudland",0
	dc.b	$20,$82
	dc.b	"",$22,"bF2D6",0
	dc.b	$10
	dc.b	"Rob NeidermayrD"
	dc.b	$94
	dc.b	"T$43DT",0
	dc.b	$10
	dc.b	"Martin Straka",0
	dc.w	$2854,$5413,$0443,$3341,$000E
	dc.b	"Radek Dvorak"
	dc.b	$19
	dc.b	"eD3#4DA",0
	dc.b	$0C
	dc.b	"Jody Hull "
	dc.b	$12,$92
	dc.b	"#3'421",0
	dc.b	$10
	dc.b	"Tom "
dat_002710:
	dc.b	"Fitzgerald!"
	dc.b	$84
	dc.b	"BC52D3",0
	dc.b	$0E
	dc.b	"Ray Sheppard&d54"
	dc.b	$15,$35,$44,$41,$00,$10
	dc.b	"Scott Mellanby'"
	dc.b	$92
	dc.b	"44I$DD",0
	dc.b	$12
	dc.b	"David Nemirovsky"
	dc.b	$15
	dc.b	"3333333",0
	dc.b	$02,$00,$0A
	dc.b	"Florida",0
	dc.w	$0006,$464C,$4100,$000A
	dc.b	"Panthers",0
	dc.b	$0E
	dc.b	"Miami Arena",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"33DDDUUU"
	dc.b	$FF
; roster: Carolina Hurricanes (NC)
Roster_Carolina:
	dc.w	$0092,$000C,$02BA,$0052,$004C,$0050,$0EC6,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$000A,$0EEE,$000E
	dc.w	$0000,$0222,$000A,$000E,$008C,$0EA6,$0EC6,$0200
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0000,$0EEE,$0222
	dc.w	$0CCC,$0888,$0000,$0222,$008C,$0EA6,$0000,$0000
	dc.w	$C100,$0104,$0A0B,$1015,$1800,$0104,$0A0B,$1015
	dc.w	$1800,$0105,$070C,$0F14,$0E00,$0103,$080D,$1218
	dc.w	$1300,$0104,$0A0B,$1015,$1800,$0105,$070C,$0F14
	dc.w	$0E00,$0104,$0A0B,$1015,$1800,$0105,$070C,$0F14
	dc.w	$0E00,$000C
	dc.b	"Sean Burke"
	dc.w	$01A4,$3443,$0120,$4444,$0010
	dc.b	"Jason Muzzatti)s33"
	dc.b	$01,$10,$33,$33,$00,$0C
	dc.b	"Adam Burt",0
	dc.b	$06
	dc.b	"r24F",$22,"C5",0
	dc.b	$10
	dc.b	"Steve Chiasson"
	dc.b	$03,$92
	dc.b	"$E42DA",0
	dc.b	$14
	dc.b	"Curtis Leschyshyn",0
	dc.b	$07,$93
	dc.b	"CB63T1",0
	dc.b	$0E
	dc.b	"Kevin Haller"
	dc.b	$14
	dc.b	"S",$22,"C4",$22,"2$",0
	dc.b	$14
	dc.b	"Alexander Godynyuk"
	dc.b	$05
	dc.b	"DC3D333",0
	dc.b	$0E
	dc.b	"Glen Wesley",0
	dc.b	$20,$85
	dc.b	"C34BD1",0
	dc.b	$0E
	dc.b	"Marek Malik",0
	dc.b	"#r",$22,"36!3",$22,"",0
	dc.b	$12
	dc.b	"Geoff Sanderson",0
	dc.b	$08
	dc.b	"eU4",$22,"EDR",0
	dc.b	$0C
	dc.b	"Derek King'"
	dc.b	$93,$24,$14,$14,$33,$33,$31,$00,$0E
	dc.b	"Paul Ranheim("
	dc.b	$84,$53,$22,$15,$32,$31,$31,$00,$0E
	dc.b	"Stu Grimson",0
	dc.w	$32B1,$2112,$3A11,$322B,$0010
	dc.b	"Keith Primeau",0
	dc.b	$55,$B2
	dc.b	"44H43H",0
	dc.b	$10
	dc.b	"Andrew Cassels!tE3$CFQ",0
	dc.b	$12
	dc.b	"Kent Mandervill",0
	dc.b	$19,$83
	dc.b	"22&",$22,"3",$22,"",0
	dc.b	$0E
	dc.b	"Jeff ONeill",0
	dc.b	$92
	dc.b	"TC27B$B",0
	dc.b	$0C
	dc.b	"Jeff Brown%"
	dc.b	$94
	dc.b	"DE'23A",0
	dc.b	$0E
	dc.b	"Kevin Dineen"
	dc.b	$11
	dc.b	"s3C)223",0
	dc.b	$0E
	dc.b	"Steven Rice",0
	dc.b	$12,$B2
	dc.b	"$",$22,"G#35",0
	dc.b	$10
	dc.b	"Nelson Emerson"
	dc.w	$1644,$5433,$1344,$4442,$000E
	dc.b	"Robert Kron",0
	dc.b	$18
	dc.b	"US#&221",0
	dc.b	$0E
	dc.b	"Chris Murray"
	dc.b	$17,$92
	dc.b	"",$22,"#3",$22,"#*",0
	dc.b	$0E
	dc.b	"Sami Kapanen$DC34333",0
	dc.b	$02,$00,$0A
	dc.b	"Carolina",0
	dc.b	$06,$43,$61,$72,$00,$00,$0C
	dc.b	"Hurricanes",0
	dc.b	$04,$4E,$43,$00,$11,$12
	dc.b	"",$22,"#34DEUUU"
	dc.b	$FF,$FF
; roster: Los Angeles Kings (Great Western Forum)
Roster_LosAngeles:
	dc.w	$0092,$000C,$02F2,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0000,$0EEE,$0222
	dc.w	$0222,$0888,$0222,$0444,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0666,$0EEE,$0AAA
	dc.w	$0CCC,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C110,$010C,$0A0D,$1718,$1A00,$010C,$0A0D,$1718
	dc.w	$1A00,$0108,$0B12,$0419,$1400,$0104,$050E,$1514
	dc.w	$1000,$010C,$0A0D,$1718,$1A00,$0108,$0B12,$0419
	dc.w	$1400,$010C,$0A0D,$1718,$1A00,$0108,$0B12,$0419
	dc.w	$1400,$0010
	dc.b	"Stephane Fiset5T34"
	dc.b	$01,$10,$44,$33,$00,$0E
	dc.b	"Byron Dafoe",0
	dc.b	"4S#3"
	dc.b	$01,$10,$44,$33,$00,$0E
	dc.b	"Jamie Storr",0
	dc.w	$0144,$4233,$0120,$3333,$000A
	dc.b	"Aki Berg"
	dc.b	$05,$83
	dc.b	"22D2$3",0
	dc.b	$10
	dc.b	"Sean ODonnell",0
	dc.b	$06,$B2
	dc.b	"",$22,"34",$22,"#4",0
	dc.b	$10
	dc.b	"Steve McKenna",0
	dc.w	$07C1,$1233,$3A11,$311A,$000C
	dc.b	"Jan Vopat",0
	dc.b	"3b#3",$22,"",$22,"",$22,"",$22,"",0
	dc.b	$12
	dc.b	"Mattias Norstrom"
	dc.b	$14,$83
	dc.b	"23F2#4",0
	dc.b	$0E
	dc.b	"Steven Finn",0
	dc.b	$29,$82
	dc.b	"!3D",$22,"46",0
	dc.b	$0C
	dc.b	"Rob Blake",0
	dc.b	$04,$A4
	dc.b	"Ddf2DC",0
	dc.b	$0E
	dc.b	"Doug Zmolek",0
	dc.b	$02,$84
	dc.b	"B22133",0
	dc.b	$12
	dc.b	"Philippe Boucher(t3"
	dc.b	$14
	dc.b	"'231",0
	dc.b	$14
	dc.b	"Dimitri Khristich",0
	dc.b	$08
	dc.b	"tE4%DDR",0
	dc.b	$14
	dc.b	"Vladmir Tsyplakov",0
	dc.b	$09,$72,$23,$12
	dc.b	"&2$1",0
	dc.b	$10
	dc.b	"Craig Johnson",0
	dc.b	$23,$82
	dc.b	"##D",$22,"23",0
	dc.b	$0E
	dc.b	"Kai Nurminen!S334333",0
	dc.b	$0E
	dc.b	"Matt Johnson"
	dc.b	$17,$A2
	dc.b	"#3I",$22,"",$22,"*",0
	dc.b	$10
	dc.b	"Kevin Stevens",0
	dc.b	$25,$B4
	dc.b	"D%834F",0
	dc.b	$10
	dc.b	"Ian Laperriere",$22,"c3#f23H",0
	dc.b	$0E
	dc.b	"Roman Vopat",0
	dc.b	$12
	dc.b	"S332333",0
	dc.b	$12
	dc.b	"Nathan Lafayette$s22'",$22,"41",0
	dc.b	$12
	dc.b	"Yanic Perreault",0
	dc.w	$4463,$3313,$1434,$2341,$000E
	dc.b	"Ray Ferraro",0
	dc.b	" cD$",$22,"4B3",0
	dc.b	$0E
	dc.b	"Glen Murray",0
	dc.b	$27,$04
	dc.b	"D3#DDD",0
	dc.b	$12
	dc.b	"Vitali YachmenevCTC#$C$B",0
	dc.b	$0C
	dc.b	"Brad Smyth"
	dc.b	$11
	dc.b	"S333333",0
	dc.b	$02,$00,$0E
	dc.b	"Los Angeles",0
	dc.b	$00,$04,$4C,$41,$00,$08
	dc.b	"Kings",0
	dc.b	$00,$16
	dc.b	"Great Western Forum",0
	dc.b	$00,$01,$11,$11
	dc.b	"",$22,"",$22,"333DDEU"
	dc.b	$FF
; roster: Montreal Canadiens (Montreal Forum)
Roster_Montreal:
	dc.w	$0092,$000C,$02BE,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0008,$0EEE,$000E
	dc.w	$0CCC,$0888,$0400,$0C00,$008C,$0C86,$0ECA,$0200
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0600,$0EEE,$0C20
	dc.w	$0CCC,$0888,$0A00,$0E20,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0107,$080D,$1015,$0B00,$0107,$080D,$1015
	dc.w	$0B00,$0103,$050E,$0F14,$0A00,$0104,$090B,$1211
	dc.w	$1300,$0107,$080D,$1015,$0B00,$0103,$050E,$0F14
	dc.w	$0A00,$0107,$080D,$1015,$0B00,$0103,$050E,$0F14
	dc.w	$0A00,$0012
	dc.b	"Jocelyn ThibaultAUCD"
	dc.b	$01,$30,$44,$55,$00,$10
	dc.b	"Jose Theodore",0
	dc.b	"`DBC"
	dc.b	$02,$20,$44,$44,$00,$0E
	dc.b	"David Wilkie"
	dc.b	$03,$93
	dc.b	"32'241",0
	dc.b	$12
	dc.b	"Stephane Quintal"
	dc.b	$05,$B2
	dc.b	"",$22,"2D",$22,"C6",0
	dc.b	$12
	dc.b	"Jassen Cullimore5T33D333",0
	dc.b	$10
	dc.b	"Peter Popovic",0
	dc.b	$34,$A2
	dc.b	"",$22,"C'1#1",0
	dc.b	$12
	dc.b	"Vladmir Malakhov8"
	dc.b	$A5
	dc.b	"C5&C%A",0
	dc.b	$14
	dc.b	"Patrice Brisebois",0
	dc.b	"CTD%)313",0
	dc.b	$0E
	dc.b	"Dave Manson",0
	dc.b	$37,$93
	dc.b	"B5Z",$22,"D;",0
	dc.b	$0E
	dc.b	"Craig Rivet",0
	dc.b	"RS#33334",0
	dc.b	$10
	dc.b	"Benoit Brunet",0
	dc.b	$17
	dc.b	"d3",$22,"*3$1",0
	dc.b	$12
	dc.b	"Martin Rucinsky",0
	dc.b	"&TC#"
	dc.b	$16,$43,$35,$41,$00,$10
	dc.b	"Shayne Corson",0
	dc.b	$27,$93
	dc.b	"4DF3DF",0
	dc.b	$0E
	dc.b	"Brian SavageIcC#$431",0
	dc.b	$0C
	dc.b	"Saku Koivu"
	dc.b	$11
	dc.b	"TE#$D5Q",0
	dc.b	$14
	dc.b	"Vincent Damphousse%dE$"
	dc.b	$10,$54,$45,$51,$00,$10
	dc.b	"Scott Thornton$"
	dc.b	$93
	dc.b	"226",$22,"4&",0
	dc.b	$0E
	dc.b	"Darcy TuckerBdC33336",0
	dc.b	$0E
	dc.b	"Marc Bureau",0
	dc.b	"(r",$22,"27",$22,"34",0
	dc.b	$12
	dc.b	"Stephane Richer",0
	dc.b	$44,$94
	dc.b	"TF'CDQ",0
	dc.b	$0E
	dc.b	"Mark Recchi",0
	dc.b	$08
	dc.b	"c54",$22,"DDR",0
	dc.b	$0E
	dc.b	"Valeri Bure",0
	dc.w	$1834,$5323,$0533,$2231,$0012
	dc.b	"Turner Stevenson0"
	dc.b	$82
	dc.b	"",$22,"$5",$22,"2)",0
	dc.b	$02,$00,$0A
	dc.b	"Montreal",0
	dc.b	$06,$4D,$54,$4C,$00,$00,$0C
	dc.b	"Canadiens",0
	dc.b	$00,$10
	dc.b	"Montreal Forum",0
	dc.b	$11,$11
	dc.b	"",$22,"",$22,"33DDEU_"
	dc.b	$FF,$FF
; roster: New Jersey Devils (Byrne Meadowlands Arena)
Roster_NewJersey:
	dc.w	$0092,$000C,$02A4,$0052,$004C,$0050,$0ECA,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$000A,$0000,$0EEE,$0222
	dc.w	$000C,$0888,$0222,$0444,$008C,$0C86,$0ECA,$0000
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0000,$0EEE,$0222
	dc.w	$0CCC,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0103,$090D,$1016,$1100,$0103,$090D,$1016
	dc.w	$1100,$0105,$060C,$1217,$0E00,$0104,$070B,$1315
	dc.w	$0800,$0103,$090D,$1016,$1100,$0105,$060C,$1217
	dc.w	$0E00,$0103,$090D,$1016,$1100,$0105,$060C,$1217
	dc.w	$0E00,$0010
	dc.b	"Martin Brodeur0uFf"
	dc.b	$01,$50,$66,$66,$00,$0E
	dc.b	"Mike Dunham",0
	dc.w	$0162,$3234,$0130,$4444,$0010
	dc.b	"Scott Stevens",0
	dc.b	$04,$B3
	dc.b	"DdT3TF",0
	dc.b	$0C
	dc.b	"Kevin Dean(s2B2",$22,"41",0
	dc.b	$10
	dc.b	"Shawn Ch"
dat_0031A8:
	dc.b	"ambers)"
	dc.b	$93
	dc.b	"3B&231",0
	dc.b	$0E
	dc.b	"Dave Ellett",0
	dc.b	$02,$94
	dc.b	"DT62DB",0
	dc.b	$0E
	dc.b	"Ken Daneyko",0
	dc.b	$03,$A3
	dc.b	"!RT!A&",0
	dc.b	$0E
	dc.b	"Lyle Odelein$"
	dc.b	$93
	dc.b	"",$22,"CI",$22,"2+",0
	dc.b	$12
	dc.b	"Scott Niedermayr'"
	dc.b	$95
	dc.b	"TS$CEB",0
	dc.b	$10
	dc.b	"Brian Rolston",0
	dc.b	$14
	dc.b	"dC3&C41",0
	dc.b	$12
	dc.b	"Valeri Zelepukin%e4#"
	dc.b	$16,$43,$34,$31,$00,$0E
	dc.b	"Steve Thomas2dD5D4B6",0
	dc.b	$12
	dc.b	"Dave Andreychuk",0
	dc.b	$23,$B3
	dc.b	"%4'3DA",0
	dc.b	$0E
	dc.b	"Reid Simpson3c43D336",0
	dc.b	$0E
	dc.b	"Jay Pandolfo D3DC3",$22,"",$22,"",0
	dc.b	$0E
	dc.b	"Doug Gilmour"
	dc.b	$93
	dc.b	"EETFEUf",0
	dc.b	$0E
	dc.b	"Peter Zezel",0
	dc.b	$22,$93
	dc.b	"3CF3C5",0
	dc.b	$0E
	dc.b	"Bobby Holik",0
	dc.b	$16,$A2
	dc.b	"35E333",0
	dc.b	$10
	dc.b	"Bob Carpenter",0
	dc.b	$19
	dc.b	"r",$22,"B*143",0
	dc.b	$10
	dc.b	"Denis Pederson"
	dc.b	$10
	dc.b	"s3532C2",0
	dc.b	$0E
	dc.b	"Bill Guerin",0
	dc.b	$12,$94
	dc.b	"T5C426",0
	dc.b	$0E
	dc.b	"John Maclean"
	dc.b	$15,$93
	dc.b	"5E53B3",0
	dc.b	$0E
	dc.b	"Randy McKay",0
	dc.b	"!c33G#26",0
	dc.b	$02,$00,$0C
	dc.b	"New Jersey",0
	dc.b	$04,$4E,$4A,$00,$08
	dc.b	"Devils",0
	dc.b	$1A
	dc.b	"Byrne Meadowlands Arena",0
	dc.b	$00,$11,$12
	dc.b	"",$22,"#334DDU_"
	dc.b	$FF,$FF
; roster: New York Islanders (Nassau Coliseum)
Roster_NewYorkIslanders:
	dc.w	$0092,$000C,$0284,$0052,$004C,$0050,$0EC6,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0A00,$0EEE,$0E00
	dc.w	$002E,$0888,$0600,$0A00,$008C,$0EA6,$0EC6,$0200
	dc.w	$0402,$0602,$0A04,$0668,$0E0E,$0640,$0EEE,$0860
	dc.w	$004E,$0888,$0402,$0602,$008C,$0EA6,$0000,$0000
	dc.w	$C100,$0106,$090B,$0E12,$1300,$0106,$090B,$0E12
	dc.w	$1300,$0104,$0516,$0F15,$1400,$0103,$080C,$1013
	dc.w	$0A00,$0106,$090B,$0E12,$1300,$0104,$0516,$0F15
	dc.w	$1400,$0106,$090B,$0E12,$1300,$0104,$0516,$0F15
	dc.w	$1400,$000C
	dc.b	"Tommy Salo5T2B"
	dc.b	$01,$30,$44,$43,$00,$0E
	dc.b	"Eric Ficha"
dat_003448:
	dc.w	$7564,$0134,$3242,$0130,$4433,$000E
	dc.b	"Bryan McCabe"
	dc.b	$04,$83
	dc.b	"3#22$3",0
	dc.b	$10
	dc.b	"Scott Lachance"
	dc.b	$07,$83
	dc.b	"CC6351",0
	dc.b	$0C
	dc.b	"Doug Houda"
	dc.b	$06
	dc.b	"r22I",$22,"$5",0
	dc.b	$0E
	dc.b	"Brian Berard4TDDDDDD",0
	dc.b	$0E
	dc.b	"Dennis Vaske("
	dc.b	$A3
	dc.b	"",$22,"",$22,"F",$22,"$3",0
	dc.b	$10
	dc.b	"Richard Pilon",0
	dc.b	$02,$94
	dc.b	"!#H",$22,"!#",0
	dc.b	$10
	dc.b	"Kenny Jonsson",0
	dc.b	$03
	dc.b	"tC442D2",0
	dc.b	$0E
	dc.b	"Ken Belanger3"
	dc.b	$A2,$22,$12,$34,$11,$23,$29,$00,$12
	dc.b	"Niklas Andersson2S3",$22,""
	dc.b	$14,$33,$32,$31,$00,$0C
	dc.b	"Paul Kruse$"
	dc.b	$92
	dc.b	"",$22,"",$22,"4",$22,"2&",0
	dc.b	$0E
	dc.b	"Brent Hughes b",$22,"",$22,"42A9",0
	dc.b	$12
	dc.b	"Bryan Smolinski",0
	dc.b	$15,$03
	dc.b	"D4#3DD",0
	dc.b	$0E
	dc.b	"Travis Green9"
	dc.b	$82
	dc.b	"3#535B",0
	dc.b	$12
	dc.b	"Claude Lapointe",0
	dc.b	$13
	dc.b	"SC2823#",0
	dc.b	$10
	dc.b	"Robert Reichel!DD4",$22,"D3D",0
	dc.b	$10
	dc.b	"Zigmund Palffy"
	dc.w	$1644,$4534,$1444,$4451,$000C
	dc.b	"Dan PlanteB"
	dc.b	$83
	dc.b	"225#",$22,"%",0
	dc.b	$0C
	dc.b	"Randy Wood"
	dc.b	$11,$82
	dc.b	"C342C3",0
	dc.b	$10
	dc.b	"Todd Bertuzzi",0
	dc.b	"DdD4DDCB",0
	dc.b	$0C
	dc.b	"Steve WebbbS3#",$22,"334",0
	dc.b	$02,$00,$0A
	dc.b	"New York",0
	dc.b	$06,$4E,$59,$49,$00,$00,$0C
	dc.b	"Islanders",0
	dc.b	$00,$12
	dc.b	"Nassau Coliseum",0
	dc.b	$00,$11,$12
	dc.b	"",$22,"#34DEUU"
	dc.b	$FF,$FF,$FF
; roster: New York Rangers (Madison Square Garden)
Roster_NewYorkRangers:
	dc.w	$0092,$000C,$02F4,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0444,$0800,$0EEE,$0E20
	dc.w	$000C,$0888,$0006,$000A,$008C,$0C86,$0ECA,$0200
	dc.w	$0800,$0A20,$0E40,$066A,$0E0E,$000A,$0EEE,$000E
	dc.w	$0CCC,$0888,$0006,$000A,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0103,$060C,$1115,$1600,$0103,$060C,$1115
	dc.w	$1600,$0104,$0B0D,$1217,$1000,$010A,$0514,$1318
	dc.w	$1900,$0103,$060C,$1115,$1600,$0104,$0B0D,$1217
	dc.w	$1000,$0103,$060C,$1115,$1600,$0104,$0B0D,$1217
	dc.w	$1000
dat_0036E8:
	dc.b	$00,$0E
	dc.b	"Mike Richter5vCD"
	dc.b	$01,$30,$56,$56,$00,$0E
	dc.b	"Glenn Healy",0
	dc.b	"0S",$22,"C"
	dc.b	$01,$00,$33,$44,$00,$0E
	dc.b	"Brian Leetch"
	dc.b	$02
	dc.b	"fTcBTda",0
	dc.b	$10
	dc.b	"Ulf Samuelsson"
	dc.b	$05,$84
	dc.b	"BRH1T2",0
	dc.b	$14
	dc.b	"Alexandr Karpotsev%c3571#1",0
	dc.b	$0E
	dc.b	"Bruce Driver3c4B&4DA",0
	dc.b	$10
	dc.b	"Dallas Eakins",0
	dc.b	"(q!",$22,"6!",$22,"(",0
	dc.b	$0E
	dc.b	"Eric Cairns",0
	dc.b	")s333334",0
	dc.b	$0E
	dc.b	"Doug Lidster"
	dc.b	$06,$93
	dc.b	"",$22,"252S2",0
	dc.b	$10
	dc.b	"Jeff Beukeboom#"
	dc.b	$B2
	dc.b	"2Cc!B6",0
	dc.b	$0E
	dc.b	"Esa Tikkanen"
	dc.b	$10,$93
	dc.b	"E5424U",0
	dc.b	$0E
	dc.b	"Adam Graves",0
	dc.b	$09,$93
	dc.b	"D5R#DF",0
	dc.b	$0C
	dc.b	"Bill Berg",0
	dc.b	$18
	dc.b	"s2BF",$22,"B4",0
	dc.b	$10
	dc.b	"Darren Langdon"
	dc.b	$15,$82
	dc.b	"",$22,"3J##:",0
	dc.b	$10
	dc.b	"Luc Robitaille s$%",$22,"E2Q",0
	dc.b	$12
	dc.b	"Niklas Sundstrom$S3B 35A",0
	dc.b	$10
	dc.b	"Wayne Gretzky",0
	dc.w	$9946,$4644,$1264,$6660,$000E
	dc.b	"Mark Messier"
	dc.b	$11,$95
	dc.b	"f4VUUW",0
	dc.b	$10
	dc.b	"Mike Eastwood",0
	dc.b	"2sC",$22,"#242",0
	dc.b	$10
	dc.b	"Chris Ferraro",0
	dc.b	$14
	dc.b	"cC#%24B",0
	dc.b	$10
	dc.b	"Alexei Kovalev'vT%2cSQ",0
	dc.b	$12
	dc.b	"Patrick Flatley",0
	dc.b	$08,$83
	dc.b	"#BK2EC",0
	dc.b	$10
	dc.b	"Russ Courtnall!ed4%3TA",0
	dc.b	$0E
	dc.b	"David Oliver&dD#"
	dc.b	$03,$34,$33,$41,$00,$0E
	dc.b	"Shane Churla",$22,""
	dc.b	$92
	dc.b	"",$22,"2X",$22,"2<",0
	dc.b	$12
	dc.b	"Ryan Vandenbsch",0
	dc.b	"7DD3",$22,"",$22,"",$22,"",$22,"",0
	dc.b	$02,$00,$0A
	dc.b	"New York",0
	dc.b	$06,$4E,$59,$52,$00,$00,$0A
	dc.b	"Rangers",0
	dc.b	$00,$18
	dc.b	"Madison Square Garden",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"333DEUUU"
	dc.b	$FF
; roster: Ottawa Senators (Ottawa Civic Center)
Roster_Ottawa:
	dc.w	$0092,$000C,$02FE,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0044,$0008,$0EEE,$000A
	dc.w	$0068,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0006,$0EEE,$000A
	dc.w	$008A,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0103,$0C10,$1218,$1500,$0103,$0C10,$1218
	dc.w	$1500,$0106,$0B0F,$1417,$1900,$0105,$070E,$131A
	dc.w	$1600,$0103,$0C10,$1218,$1500,$0106,$0B0F,$1417
	dc.w	$1900,$0103,$0C10,$1218,$1500,$0106,$0B0F,$1417
	dc.w	$1900,$0010
	dc.b	"Damian Rhodes",0
	dc.w	$0153,$3244,$0120,$4444,$000E
	dc.b	"Ron Tugnutt",0
	dc.b	"1D2C"
	dc.b	$01,$10,$44,$44,$00,$0E
	dc.b	"Frank Musil",0
	dc.b	$03,$93
	dc.b	"AB8!4",$22,"",0
	dc.b	$12
	dc.b	"Stanislv Neckar",0
	dc.b	$94
	dc.b	"t2",$22,"$242",0
	dc.b	$0E
	dc.b	"Wade Redden",0
	dc.b	$06
	dc.b	"DSD3C4C",0
	dc.b	$12
	dc.b	"Janne Laukkanen",0
	dc.w	$2754,$4312,$0642,$2431,$000C
	dc.b	"Jason York3s3$"
	dc.b	$13,$32,$32,$31,$00,$12
	dc.b	"Christer Olsson",0
	dc.b	"#tC",$22,"&242",0
	dc.b	$10
	dc.b	"Lance Pitlick",0
	dc.b	$02,$83
	dc.b	"225",$22,"$1",0
	dc.b	$0C
	dc.b	"Sean Hill",0
	dc.b	$04,$83
	dc.b	"3",$22,"5",$22,"42",0
	dc.b	$10
	dc.b	"Radim Bicanek",0
	dc.b	"DS333332",0
	dc.b	$10
	dc.b	"Steve Duchense("
	dc.b	$84,$45,$24,$14,$33,$44,$41,$00,$0E
	dc.b	"Dennis Vial",0
	dc.w	$2192,$1122,$4811,$342A,$0012
	dc.b	"Randy Cunneywrth"
	dc.b	$07
	dc.b	"R2",$22,"6#46",0
	dc.b	$12
	dc.b	"Shawn McEachern",0
	dc.w	$1574,$5424,$1234,$4241,$000E
	dc.b	"Tom Chorske",0
	dc.b	$17,$94
	dc.b	"R252C#",0
	dc.b	$10
	dc.b	"Denny Lambert",0
	dc.b	"BB43",$22,"",$22,"32",0
	dc.b	$10
	dc.b	"Alexei Yashin",0
	dc.b	$19,$95
	dc.b	"U$",$22,"d4Q",0
	dc.b	$0C
	dc.b	"Radek Bonkv"
	dc.b	$92
	dc.b	"#$$C22",0
	dc.b	$10
	dc.b	"Sergei Zholtok"
	dc.w	$1644,$5433,$1244,$3332,$0010
	dc.b	"Shaun VanAllen",$22,""
	dc.b	$92
	dc.b	"#",$22,"&B6B",0
	dc.b	$10
	dc.b	"Bruce Gardiner%r3#",$22,"3",$22,"",$22,"",0
	dc.b	$12
	dc.b	"Alexndre Daigle",0
	dc.b	$91
	dc.b	"TD4",$22,"DDA",0
	dc.b	$14
	dc.b	"Daniel Alfredsson",0
	dc.w	$1163,$4524,$1144,$3351,$000E
	dc.b	"Philip Crowe&RC333B",$22,"",0
	dc.b	$12
	dc.b	"Andreas Dackell",0
	dc.b	$10,$84
	dc.b	"C3433D",0
	dc.b	$02,$00,$08
	dc.b	"Ottawa",0
	dc.b	$06,$4F,$54,$57,$00,$00,$0A
	dc.b	"Senators",0
	dc.b	$16
	dc.b	"Ottawa Civic Center",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"333DEUUU"
	dc.b	$FF
; roster: Philadelphia Flyers (Spectrum)
Roster_Philadelphia:
	dc.w	$0092,$000C,$02CA,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0444,$0008,$0EEE,$004E
	dc.w	$0000,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0008,$002C
dat_003CF8:
	dc.w	$004E,$066A,$0E0E,$0AAA,$0EEE,$0EEE,$0000,$0888
	dc.w	$0000,$0222,$008C,$0C86,$0000,$0000,$C100,$0103
	dc.w	$0A0B,$1116,$1800,$0103,$0A0B,$1116,$1800,$0105
	dc.w	$070E,$1317,$0F00,$0106,$080C,$1019,$0D00,$0103
	dc.w	$0A0B,$1116,$1800,$0105,$070E,$1317,$0F00,$0103
	dc.w	$0A0B,$1116,$1800,$0105,$070E,$1317,$0F00,$000E
	dc.w	$526F,$6E20,$4865,$7874,$616C,$6C00,$2773,$4154
	dc.w	$0130,$4444,$000C,$4761,$7274,$6820,$536E,$6F77
	dc.w	$3093,$3143,$0120,$4444,$000E,$5061,$756C,$2043
	dc.w	$6F66,$6665,$7900,$7796,$5464,$2654,$5562,$0010
	dc.w	$4368,$7269,$7320,$5468,$6572,$6965,$6E00,$06B3
	dc.w	$3332,$2432,$3431,$000E,$5065,$7472,$2053,$766F
	dc.w	$626F,$6461,$2355,$3243,$3821,$4534,$000E,$4D69
	dc.w	$6368,$656C,$2050,$6574,$6974,$0883,$3223,$3732
	dc.w	$2434,$0010,$4A61,$6E6E,$6520,$4E69,$696E,$696D
	dc.w	$6161,$4474,$4434,$4444,$3452,$000E,$4B61,$726C
	dc.w	$2044,$796B,$6875,$6973,$2493,$2322,$2432,$3432
	dc.w	$0012,$4B6A,$656C,$6C20,$5361,$6D75,$656C,$7373
	dc.w	$6F6E,$28E1,$2143,$4731,$3233
dat_003E22:
	dc.b	$00,$12
	dc.b	"Eric Desjardins",0
	dc.b	$37,$94
	dc.b	"DTG3CA",0
	dc.b	$0E
	dc.b	"John LeClair"
	dc.b	$10,$B4
	dc.b	"FEDEfS",0
	dc.b	$0E
	dc.b	"Shjon Podein%"
	dc.b	$84
	dc.b	"C2&2#1",0
	dc.b	$10
	dc.b	"Scott Daniels",0
	dc.w	$2282,$2212,$3412,$3228,$0010
	dc.b	"Rod BrindAmour"
	dc.b	$17,$94
	dc.b	"DD",$22,"DeB",0
	dc.b	$0C
	dc.b	"Dan Kordic!"
	dc.b	$82
	dc.b	"2#6",$22,"#6",0
	dc.b	$0C
	dc.b	"Joel O"
dat_003EB4:
	dc.b	$74,$74,$6F,$00,$29,$B2
	dc.b	"#3W#D%",0
	dc.b	$0E
	dc.b	"Eric Lindros"
	dc.b	$88,$C4
	dc.b	"FVfFTF",0
	dc.b	$0E
	dc.b	"Dan Lacroix",0
	dc.b	$32,$82
	dc.b	"",$22,"3B",$22,"36",0
	dc.b	$10
	dc.b	"Dale Hawerchuk"
	dc.b	$18
	dc.b	"dEC&CEQ",0
	dc.b	$10
	dc.b	"Vaclav ProspalEcC3",$22,"334",0
	dc.b	$0E
	dc.b	"Pat Falloon",0
	dc.w	$1574,$4323,$1733,$3241,$0010
	dc.b	"Mikael Renberg"
	dc.b	$19
	dc.b	"t54FETB",0
	dc.b	$0E
	dc.b	"Trent Klatt",0
	dc.b	$20,$93
	dc.b	"54%44D",0
	dc.b	$0C
	dc.b	"John Druce&"
	dc.b	$92
	dc.b	"##'311",0
	dc.b	$10
	dc.b	"Dainius Zubrus"
	dc.b	$09
	dc.b	"dD4$DTB",0
	dc.b	$02,$00,$0E
	dc.b	"Philadelphia",0
	dc.b	$06,$50,$48,$49,$00,$00,$08
	dc.b	"Flyers",0
	dc.b	$0A
	dc.b	"Spectrum",0
	dc.b	$11,$11
	dc.b	"",$22,"",$22,"334DDUU_"
	dc.b	$FF
; roster: Phoenix Phoenix (America West Arena)
Roster_Phoenix:
	dc.w	$0092,$000C,$02EE,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0006,$0EEE,$0204
	dc.w	$0A88,$0888,$0020,$0020,$008C,$0C86,$0EC6,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0006,$0EEE,$0060
	dc.w	$0006,$0888,$0000,$0000,$008C,$0C86,$0000,$0000
	dc.w	$C110,$010C,$0410,$1216,$1A00,$010C,$0410,$1216
	dc.w	$1A00,$0105,$060F,$1519,$1400,$0107,$0B0D,$1317
	dc.w	$1800,$010C,$0410,$1216,$1A00,$0105,$060F,$1519
	dc.w	$1400,$010C,$0410,$1216,$1A00,$0105,$060F,$1519
	dc.w	$1400,$0014
	dc.b	"Nikolai Khabibulin5U2C"
	dc.b	$01,$30,$55,$55,$00,$10
	dc.b	"Darcy Wakaluk",0
	dc.b	"Cc23"
	dc.b	$01,$10,$33,$33,$00,$10
	dc.b	"Pat Jablonski",0
	dc.b	"9S23",0
	dc.b	$10,$32,$33,$00,$12
	dc.b	"Oleg Tverdovsky",0
	dc.b	" UT3&B5Q",0
	dc.b	$10
	dc.b	"Gerald Diduck",0
	dc.b	$04,$94
	dc.b	"12E!43",0
	dc.b	$0E
	dc.b	"Jayson More",0
	dc.b	$06
	dc.b	"s!#I",$22,"2*",0
	dc.b	$10
	dc.b	"James Johnson",0
	dc.b	$08
	dc.b	"s",$22,"CF",$22,"D5",0
	dc.b	$10
	dc.b	"Brad McCrimmon"
	dc.b	$10,$82
	dc.b	"",$22,"B41$2",0
	dc.b	$0E
	dc.b	"Murray Baron6"
	dc.b	$A3
	dc.b	"1BF!",$22,"&",0
	dc.b	$0E
	dc.b	"Jeff Finley",0
	dc.w	$2684,$3222,$1632,$2431,$0010
	dc.b	"Teppo Numminen'u4C52EA",0
	dc.b	$0E
	dc.b	"Norm MaciverDS4#&B5A",0
	dc.b	$0C
	dc.b	"Kris King",0
	dc.b	$17,$A3
	dc.b	"2CD",$22,"C:",0
	dc.b	$0E
	dc.b	"Jim McKenzie3"
	dc.b	$82,$22,$22,$34,$11,$34,$1A,$00,$10
	dc.b	"Darrin Shannon4"
	dc.b	$93
	dc.b	"#38",$22,"34",0
	dc.b	$10
	dc.b	"Keith Tkachuk",0
	dc.b	$07,$94
	dc.b	"FFfEeV",0
	dc.b	$10
	dc.b	"Mike Stapleton"
	dc.b	$14
	dc.b	"cC",$22,"%",$22,"31",0
	dc.b	$10
	dc.b	"Jeremy Roenick"
	dc.b	$97
	dc.b	"EUETDTU",0
	dc.b	$10
	dc.b	"Cliff Ronning",0
	dc.b	"wUT4$4EB",0
	dc.b	$0C
	dc.b	"Bob Corkum!"
	dc.b	$A3
	dc.b	"33534",$22,"",0
	dc.b	$0E
	dc.b	"Craig Janney"
	dc.w	$1574,$3533,$1453,$4661,$000E
	dc.b	"Mike Gartner",$22,"vd%%DRA",0
	dc.b	$0E
	dc.b	"Dallas Drake"
	dc.b	$11
	dc.b	"ET3$3D2",0
	dc.b	$0C
	dc.b	"Shane Doan"
	dc.b	$19,$A4,$43,$13
	dc.b	"5233",0
	dc.b	$0E
	dc.b	"Igor Korolev#tD3"
	dc.b	$12,$43,$35,$41,$00,$12
	dc.b	"Jocelyn Lemieux",0
	dc.b	$32,$94
	dc.b	"2DD2C&",0
	dc.b	$02,$00,$0A
	dc.b	"Phoenix",0
	dc.w	$0006,$5048,$5800,$000A
	dc.b	"Phoenix",0
	dc.b	$00,$14
	dc.b	"America West Arena",0
	dc.b	$01,$11,$12
	dc.b	"",$22,"",$22,"33DDEUU"
	dc.b	$FF
; roster: Pittsburgh Penguins (Civic Arena)
Roster_Pittsburgh:
	dc.w	$0092,$000C,$02E0,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0444,$006A,$0EEE,$00AE
	dc.w	$0000,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$006A,$0EEE,$00AE
	dc.w	$0CCC,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0106,$0410,$1317,$1500,$0106,$0410,$1317
	dc.w	$1500,$0107,$050F,$1219,$1A00,$0109,$080D,$1118
	dc.w	$0E00,$0106,$0413,$1217,$1500,$0107,$0511,$1519
	dc.w	$1A00,$0106,$0410,$1317,$1500,$0107,$050F,$1219
	dc.w	$1A00,$000E
	dc.b	"Ken Wregget",0
	dc.w	$3184,$4244,$0130,$4444,$0010
	dc.b	"Patrick Lalime@4AD"
	dc.b	$01,$20,$44,$44,$00,$0E
	dc.b	"Tom Barrasso5"
	dc.b	$A3,$32,$44,$00,$20,$44,$33,$00,$10
	dc.b	"Kevin Hatcher",0
	dc.b	$04,$B3
	dc.b	"4EU3BF",0
	dc.b	$10
	dc.b	"Jason Woolley",0
	dc.b	"",$22,"c3#&241",0
	dc.b	$12
	dc.b	"Fredrik Olausson#"
	dc.b	$95,$44,$24,$17,$42,$35,$41,$00,$14
	dc.b	"Darius Kasparaits",0
	dc.b	$11
	dc.b	"t2Cf2#7",0
	dc.b	$0C
	dc.b	"Craig Muni("
	dc.b	$92
	dc.b	"!BD!D4",0
	dc.b	$0E
	dc.b	"Chris Tamer",0
	dc.b	$02,$93
	dc.b	"2B:",$22,"4*",0
	dc.b	$10
	dc.b	"Neil Wilkinson"
	dc.b	$06
	dc.b	"s1CH!56",0
	dc.b	$12
	dc.b	"Francois Leroux",0
	dc.b	$18,$B2
	dc.b	"!BL!2*",0
	dc.b	$0C
	dc.b	"Ian Moran",0
	dc.b	"$s32"
	dc.b	$17,$32,$24,$36,$00,$0E
	dc.b	"Joe Dziedzic"
	dc.b	$16,$B2
	dc.b	"$#6",$22,"36",0
	dc.b	$0C
	dc.b	"Garry Valk"
	dc.b	$08
	dc.b	"r#363C3",0
	dc.b	$10
	dc.b	"Josef Beranek",0
	dc.w	$1563,$3424,$1632,$3232,$000C
	dc.b	"Ed Olczyk",0
	dc.b	$27,$94
	dc.b	"D$$DDB",0
	dc.b	$0E
	dc.b	"Petr Nedved",0
	dc.w	$9355,$5534,$1444,$4451,$000E
	dc.b	"Ron Francis",0
	dc.w	$1093,$3552,$1243,$3551,$0010
	dc.b	"Mario Lemieux",0
	dc.w	$66A5,$4644,$1066,$6661,$000E
	dc.b	"Greg Johnson"
	dc.w	$0964,$3423,$1433,$3431,$000C
	dc.b	"Stu Barnes"
	dc.w	$1453,$4424,$1434,$4431,$000C
	dc.b	"Alex Hicks3s##&3#8",0
	dc.b	$0E
	dc.b	"Jaromir Jagrh"
	dc.b	$A5,$56,$45,$10,$66,$66,$61,$00,$10
	dc.b	"Alek Stojanov",0
	dc.b	$25,$A2
	dc.b	"3",$22,"D",$22,"#)",0
	dc.b	$0C
	dc.b	"Joe Mullen"
	dc.b	$07
	dc.b	"c43",$22,"4CA",0
	dc.b	$10
	dc.b	"Roman Oksiuta",0
	dc.b	$20,$83,$33,$04
	dc.b	"&4",$22,"2",0
	dc.b	$02,$00,$0C
	dc.b	"Pittsburgh",0
	dc.b	$06,$50,$49,$54,$00,$00,$0A
	dc.b	"Penguins",0
	dc.b	$0E
	dc.b	"Civic Arena",0
	dc.b	$00,$01,$11,$11
	dc.b	"",$22,"",$22,"33DDDUU"
	dc.b	$FF
; roster: San Jose Sharks (San Jose Arena)
Roster_SanJose:
	dc.w	$0092,$000C,$02DE,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0640,$0EEE,$0A60
	dc.w	$0666,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0420,$0640,$0860,$066A,$0E0E,$0000,$0EEE,$0222
	dc.w	$0CCC,$0888,$0222,$0444,$008C,$0EA8,$0000,$0000
	dc.w	$C110,$0106,$0B0E,$1316,$1200,$0106,$0B0E,$1316
	dc.w	$1200,$0107,$090C,$1419,$1100,$0105,$0A0F,$1018
	dc.w	$1700,$0106,$0B0E,$1316,$1200,$0107,$090C,$1419
	dc.w	$1100,$0106,$0B0E,$1316,$1200,$0107,$090C,$1419
	dc.w	$1100,$000C
	dc.b	"Ed Belfour0fBD"
	dc.b	$01,$20,$44,$55,$00,$0E
	dc.b	"Kelly Hrudey2d13"
	dc.b	$01,$20,$33,$33,$00,$10
	dc.b	"Wade Flaherty",0
	dc.b	"1C12"
	dc.b	$01,$10,$22,$32,$00,$0E
	dc.b	"Greg Hawgood"
	dc.b	$04
	dc.b	"r",$22,"3D",$22,"",$22,"$",0
	dc.b	$0C
	dc.b	"Al IafrateC"
	dc.b	$A3
	dc.b	"",$22,"6F$",$22,"(",0
	dc.b	$0E
	dc.b	"Doug Bodger",0
	dc.b	$03,$A4
	dc.b	"32&2E1",0
	dc.b	$0C
	dc.b	"Todd Gill",0
	dc.b	"#dC262B3",0
	dc.b	$14
	dc.b	"Marcus Ragnarsson",0
	dc.b	$10,$A4
	dc.b	"D",$22,"$B%B",0
	dc.b	$10
	dc.b	"Marty McSorley3"
	dc.b	$C1
	dc.b	"#4K#SL",0
	dc.b	$0E
	dc.b	"Mike Rathje",0
	dc.b	$40,$83
	dc.b	"",$22,"",$22,"4",$22,"#2",0
	dc.b	$12
	dc.b	"Vlastiml Kroupa",0
	dc.w	$4463,$3312,$1432,$2331,$0010
	dc.b	"Viktor Kozlov",0
	dc.b	$25,$B2
	dc.b	"3#'B3A",0
	dc.b	$10
	dc.b	"Stephen Guolla"
	dc.b	$17
	dc.b	"R",$22,"33334",0
	dc.b	$0E
	dc.b	"Tony Granato!dTC6334",0
	dc.b	$0C
	dc.b	"Bob Errey",0
	dc.b	"",$22,"eBBF2D2",0
	dc.b	$10
	dc.b	"Ville Peltonen"
	dc.w	$0755,$4322,$0642,$2441,$000E
	dc.b	"Jeff Friesen9cD3",$22,"C4A",0
	dc.b	$0C
	dc.b	"Dody Wood",0
	dc.w	$1682,$3222,$4612,$2229,$0012
	dc.b	"Bernie Nicholls",0
	dc.b	$09
	dc.b	"c5C$CER",0
	dc.b	$12
	dc.b	"Darren Turcotte",0
	dc.w	$0864,$5445,$1843,$4231,$000C
	dc.b	"Ron Sutter"
	dc.b	$12
	dc.b	"R",$22,"CI",$22,"45",0
	dc.b	$0C
	dc.b	"Owen Nolan"
	dc.b	$11,$83
	dc.b	"E5G5DF",0
	dc.b	$0C
	dc.b	"Todd Ewen",0
	dc.w	$36B1,$2223,$4712,$232A,$0010
	dc.b	"Andrei Nazarovb"
	dc.b	$92
	dc.b	"2DI",$22,"",$22,")",0
	dc.b	$10
	dc.b	"Shean Donovan",0
	dc.b	"BdC#5#31",0
	dc.b	$0C
	dc.b	"Tim Hunter"
	dc.w	$1992,$1222,$3912,$222A,$0002,$000A
	dc.b	"San Jose",0
	dc.b	$04,$53,$4A,$00,$08
	dc.b	"Sharks",0
	dc.b	$10
	dc.b	"San Jose Arena",0
	dc.b	$01,$11,$11
	dc.b	"",$22,"#33DDEUU"
	dc.b	$FF
; roster: St. Louis Blues (Kiel Center)
Roster_StLouis:
	dc.w	$0092,$000C,$02BE,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$00AE,$0800,$0EEE,$0E20
	dc.w	$000C,$0888,$0400,$0A00,$008C,$0C86,$0ECA,$0200
	dc.w	$0400,$0A00,$0E20,$066A,$0E0E,$0008,$0EEE,$000E
	dc.w	$00AE,$0888,$0800,$0E20,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0104,$070A,$0F14,$1200,$0104,$070A,$0F14
	dc.w	$1200,$0105,$080E,$1315,$1800,$0103,$060C,$1017
	dc.w	$0B00,$0104,$070A,$0F14,$1200,$0105,$080E,$1315
	dc.w	$1800,$0104,$070A,$0F14,$1200,$0105,$080E,$1315
	dc.w	$1800,$000C
	dc.b	"Grant Fuhr1u2D",0
	dc.b	$40,$54,$44,$00,$0C
	dc.b	"Jon Casey 02"
dat_0049CA:
	dc.w	$2233,$0120,$3232,$0010
	dc.b	"Marc Bergevin",0
	dc.b	$04
	dc.b	"d12D",$22,"3#",0
	dc.b	$12
	dc.b	"Chris Macalpine",0
	dc.b	$19
	dc.b	"c2B$334",0
	dc.b	$10
	dc.b	"Chris Pronger",0
	dc.b	"Ds34I247",0
	dc.b	$10
	dc.b	"Ricard Persson("
	dc.b	$94
	dc.b	"C$$23B",0
	dc.b	$0E
	dc.b	"Al MacInnis",0
	dc.b	$02,$84
	dc.b	"DJ12RA",0
	dc.b	$10
	dc.b	"Igor Kravchuk",0
	dc.b	$05,$95
	dc.b	"C462C1",0
	dc.b	$0E
	dc.b	"Trent Yawney3s1281"
dat_004A74:
	dc.b	$35,$33,$00,$12
	dc.b	"Geoff Courtnall",0
	dc.w	$1475,$5434,$1634,$3243,$000E
	dc.b	"Mike Peluso",0
	dc.b	$20,$A2
	dc.b	"23Y",$22,"C,",0
	dc.b	$0C
	dc.b	"Tony Twist"
	dc.w	$18A1,$2222,$4B12,$322C,$0012
	dc.b	"Stephane Matteau2"
	dc.b	$83
	dc.b	"2C22$C",0
	dc.b	$10
	dc.b	"Sergio Momesso&"
	dc.b	$A3
	dc.b	"34D328",0
	dc.b	$10
	dc.b	"Pierre Turgeonw"
	dc.b	$95,$45,$34,$04,$55,$45,$51,$00,$12
	dc.b	"Craig MacTavish",0
	dc.b	$23,$83
	dc.b	"#R4233"
dat_004B1E:
	dc.b	$00,$0E
	dc.b	"Craig Conroy",$22,"TC33332",0
	dc.b	$14
	dc.b	"Robert Petrovicky",0
	dc.b	"6c3#",$22,"334",0
	dc.b	$0C
	dc.b	"Harry York7s4324D1",0
	dc.b	$0C
	dc.b	"Brett Hull"
	dc.b	$16,$94
	dc.b	"E6$EDA",0
	dc.b	$0C
	dc.b	"Joe Murphy"
	dc.b	$17
	dc.b	"tT424BB",0
	dc.b	$10
	dc.b	"Stephen Leach",0
	dc.b	"'c#4I3B5",0
	dc.b	$0E
	dc.b	"Jim Campbell"
	dc.b	$10
	dc.b	"d44",$22,"D4B",0
	dc.b	$10
	dc.b	"Pavol Demitr"
dat_004BC8:
	dc.w	$6100,$3853,$2313,$0433,$2231,$0002,$000C
	dc.b	"St. Louis",0
	dc.w	$0006,$5354,$4C00,$0008
	dc.b	"Blues",0
	dc.b	$00,$0E
	dc.b	"Kiel Center",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"#34DDEUU"
	dc.b	$FF,$FF
; roster: Tampa Bay Lightning (Thunderdome)
Roster_TampaBay:
	dc.w	$0092,$000C,$02EA,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0222,$0EEE,$0444
	dc.w	$0E00,$0888,$0000,$0222,$008C,$0C86,$0ECA,$0200
	dc.w	$0000,$0000,$0222,$066A,$0E0E,$0888,$0EEE,$0CCC
	dc.w	$0E20,$0888,$0222,$0444,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0109,$060D,$1617,$1900,$0109,$060D,$1617
	dc.w	$1900,$0104,$080F,$1318
dat_004C72:
	dc.w	$0B00,$0105,$070E,$151A,$1400,$0109,$060D,$1617
	dc.w	$1900,$0104,$080F,$1318,$0B00,$0109,$060D,$1617
	dc.w	$1900,$0104,$080F,$1318,$0B00,$000E,$4461,$7272
	dc.w	$656E,$2050,$7570,$7061,$9394,$3343,$0020,$4444
	dc.w	$0010,$5269,$636B,$2054,$6162,$6172,$6163,$6369
	dc.w	$3163,$3243,$0130,$4433,$000E,$436F,$7265,$7920
	dc.w	$5363,$6877,$6162,$3253,$2233,$0110,$3333,$000E
	dc.w	$4269,$6C6C,$2048,$6F75,$6C64,$6572,$02B2,$2323
	dc.w	$2233,$3341,$000C,$436F,$7279,$2043,$726F,$7373
	dc.w	$0493,$2124,$3221,$3332,$0010,$526F,$6D61,$6E20
	dc.w	$4861,$6D72,$6C69,$6B00,$4474
dat_004D1C:
	dc.b	"4DDC4C",0
	dc.b	$0C
	dc.b	"Jay Wells",0
	dc.b	$26,$A2,$11
	dc.b	"2D!4&",0
	dc.b	$0E
	dc.b	"Igor Ulanov",0
	dc.b	$05,$92
	dc.b	"!2E!E$",0
	dc.b	$0E
	dc.b	"Jeff Norton",0
	dc.b	$06
	dc.b	"eD2&BEA",0
	dc.b	$10
	dc.b	"James Huscroft"
	dc.w	$0881,$2232,$3712,$322A,$000C
	dc.b	"David Shaw'"
	dc.b	$92
	dc.b	"",$22,"B7",$22,"B5",0
	dc.b	$0C
	dc.b	"Jeff Toms",0
	dc.b	$09
	dc.b	"s33$33"
	dc.b	$13,$00,$0E
	dc.b	"Rob Zamuner",0
	dc.b	$07,$92
	dc.b	"#3$3T2",0
	dc.b	$0C
	dc.b	"Shawn Burr"
	dc.b	$11
	dc.b	"b#B6344",0
	dc.b	$10
	dc.b	"Paul Ysebaert",0
	dc.b	$15
	dc.b	"s$#&42!",0
	dc.b	$0E
	dc.b	"Jason Wiemer$"
	dc.b	$94
	dc.b	"3",$22,"4B4B",0
	dc.b	$12
	dc.b	"Mikael Andersson4dR2$2B1",0
	dc.b	$10
	dc.b	"Patrick Poulin("
	dc.b	$A5
	dc.b	"R$6221",0
	dc.b	$0E
	dc.b	"John Cullen",0
	dc.b	$12
	dc.b	"r$4$4FR",0
	dc.b	$12
	dc.b	"Daymond Langkow",0
	dc.b	$18
	dc.b	"DD#C3#2",0
	dc.b	$10
	dc.b	"Brian Bradley",0
	dc.b	$19
	dc.b	"DD4%DBB",0
	dc.b	$10
	dc.b	"Chris Gratton",0
	dc.b	$77,$92
	dc.b	"44@24E",0
	dc.b	$12
	dc.b	"Dino Ciccarelli",0
	dc.b	"",$22,"EE5%4DG",0
	dc.b	$14
	dc.b	"Alexandr Selivanov)eD$&D3A",0
	dc.b	$10
	dc.b	"Rudy Poeschek",0
	dc.b	$20,$A2
	dc.b	"",$22,"2I!C*",0
	dc.b	$10
	dc.b	"Brantt Myhers",0
	dc.b	$74,$82
	dc.b	"3#D",$22,"",$22,"4",0
	dc.b	$02,$00,$0C
	dc.b	"Tampa Bay",0
	dc.b	$00,$04,$54,$42,$00,$0C
	dc.b	"Lightning",0
	dc.b	$00,$0E
	dc.b	"Thunderdome",0
	dc.b	$00,$01,$11,$11
	dc.b	"",$22,"#333DDUU"
	dc.b	$FF
; roster: Toronto Maple Leafs (Maple Leaf Gardens)
Roster_Toronto:
	dc.w	$0092,$000C,$02F2,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$088E,$0A00,$0EEE,$0E20
	dc.w	$0E20,$0888,$0600,$0A00,$008C,$0C86,$0ECA,$0200
	dc.w	$0400,$0800,$0C00,$066A,$0E0E,$0AAA,$0EEE,$0EEE
	dc.w	$0CCC,$0888,$0400,$0C00,$008C,$0C86,$0000,$0000
	dc.w	$C100,$010A,$0B0F,$1119,$0D00,$010A,$0B0F,$1119
	dc.w	$0D00,$0105,$0C0E,$1517,$1300,$0103,$070D,$121A
	dc.w	$1800,$010A,$0B0F,$1119,$0D00,$0105,$0C0E,$1517
	dc.w	$1300,$010A,$0B0F,$1119,$0D00,$0105,$0C0E,$1517
	dc.w	$1300,$000E
	dc.b	"Felix Potvin)eSD"
	dc.b	$01,$30,$55,$55,$00,$12
	dc.b	"Marcel Cousineau1dB3"
	dc.b	$01,$10,$44,$44,$00,$0E
	dc.b	"Rob Zettler",0
	dc.b	$02
	dc.b	"s!",$22,"&!25",0
	dc.b	$0E
	dc.b	"Matt Martin",0
	dc.b	$03,$82
	dc.b	"",$22,"",$22,"4!4$",0
	dc.b	$0E
	dc.b	"Jason Smith",0
	dc.b	"%s1BG2#4",0
	dc.b	$0C
	dc.b	"D.J. Smith"
	dc.b	$04
	dc.b	"c22433$",0
	dc.b	$12
	dc.b	"Yannick Tremblay8b23D332",0
	dc.b	$0E
	dc.b	"David CooperBTC3D334",0
	dc.b	$10
	dc.b	"Craig Wolanin",0
	dc.b	$26,$82
	dc.b	"#2(341",0
	dc.b	$14
	dc.b	"Mathieu Schneider",0
	dc.b	"rtDD43DD",0
	dc.b	$0E
	dc.b	"Jamie Macoun4"
	dc.b	$83
	dc.b	"D4B!BF",0
	dc.b	$14
	dc.b	"Dmitri Yushkevich",0
	dc.b	"6uCC5242",0
	dc.b	$10
	dc.b	"Todd Warriner",0
	dc.b	$08
	dc.b	"dC",$22,"42#2",0
	dc.b	$12
	dc.b	"Frederick Modin",0
	dc.b	$19
	dc.b	"tC2$",$22,"33",0
	dc.b	$0E
	dc.b	"Wendel Clark"
	dc.b	$17,$83
	dc.b	"46I4BH",0
	dc.b	$0E
	dc.b	"Nick Kypreos2"
	dc.b	$82
	dc.b	"",$22,"",$22,"T",$22,"2(",0
	dc.b	$0E
	dc.b	"Mats Sundin",0
	dc.w	$1375,$5644,$1255,$5551,$000E
	dc.b	"Jamie Baker",0
	dc.b	$16
	dc.b	"s3#4331",0
	dc.b	$12
	dc.b	"Darby Hendricksn"
	dc.b	$14
	dc.b	"c22$",$22,"42",0
	dc.b	$10
	dc.b	"Jason Podollan"
	dc.b	$07
	dc.b	"S333332",0
	dc.b	$12
	dc.b	"Brandon Convery",0
	dc.w	$1254,$4422,$1543,$2441,$0010
	dc.b	"Steve Sullivan"
	dc.b	$11
	dc.b	"c32$3",$22,"4",0
	dc.b	$0C
	dc.b	"Mike Craig"
	dc.b	$09,$64,$33,$13
	dc.b	"722",$22,"",0
	dc.b	$0E
	dc.b	"Kelly Chase",0
	dc.w	$3981,$1121,$2711,$321B,$0010
	dc.b	"Sergei Berezin"
	dc.b	$94
	dc.b	"eT44EE@",0
	dc.b	$0A
	dc.b	"Tie Domi("
	dc.b	$93
	dc.b	"3#O22/",0
	dc.b	$02,$00,$0A
	dc.b	"Toronto",0
	dc.w	$0006,$544F,$5200,$000E
	dc.b	"Maple Leafs",0
	dc.b	$00,$14
	dc.b	"Maple Leaf Gardens",0
	dc.b	$11,$11,$11
	dc.b	"",$22,"",$22,"33DDDUU"
	dc.b	$FF
; roster: Vancouver Canucks (General Motors Place)
Roster_Vancouver:
	dc.w	$0092,$000C,$02D2,$0052,$004C,$0050,$0EC6,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0400,$0EEE,$0600
	dc.w	$0888,$0888,$0400,$0600,$008C,$0EA6,$0EC6,$0200
	dc.w	$0402,$0602,$0A04,$0668,$0E0E,$0602,$0EEE,$0A04
	dc.w	$0CCC,$0888,$0602,$0A04,$008C,$0EA6,$0000,$0000
	dc.w	$C100,$0103,$0A13,$1015,$1600,$0103,$0A13,$1015
	dc.w	$1600,$0104,$070C,$1116,$1700,$0106,$0810,$1417
	dc.w	$0F00,$0103,$0A13,$1015,$1600,$0104,$070C,$1117
	dc.w	$1600,$0103,$0A13,$1015,$1600,$0104,$070C,$1117
	dc.w	$1600,$000E
	dc.b	"Kirk McLean",0
	dc.w	$0164,$4244,$0130,$5444,$000E
	dc.b	"Corey Hirsch1423"
	dc.b	$01,$20,$44,$44,$00,$0E
	dc.b	"Bret Hedican"
	dc.b	$03,$85
	dc.b	"cC$14A",0
	dc.b	$0E
	dc.b	"Chris Joseph2"
	dc.b	$A3
	dc.b	"3#324B",0
	dc.b	$0E
	dc.b	"Dana Murzyn",0
	dc.b	$05,$91
	dc.b	"",$22,"E8!B)",0
	dc.b	$0E
	dc.b	"Leif Rohlin",0
	dc.b	$27,$83
	dc.b	"#",$22,"$341",0
	dc.b	$0E
	dc.b	"Dave Babych",0
	dc.b	$44,$A2
	dc.b	"#C6!D2",0
	dc.b	$10
	dc.b	"Adrian Aucoin",0
	dc.b	$06
	dc.b	"s3",$22,"%241",0
	dc.b	$0E
	dc.b	"Jyrki Lumme",0
	dc.b	"!uCC"
	dc.b	$12,$33,$44,$41,$00,$0E
	dc.b	"Steve Staios%"
	dc.b	$83
	dc.b	"333332",0
	dc.b	$10
	dc.b	"Martin Gelinas#"
	dc.b	$83
	dc.b	"44644E",0
	dc.b	$0E
	dc.b	"Gino Odjick",0
	dc.b	$29,$A2
	dc.b	"",$22,"3J",$22,"3+",0
	dc.b	$12
	dc.b	"Donald Brashear",0
	dc.w	$0892,$2122,$3A12,$212A,$0010
	dc.b	"Markus Naslund"
	dc.b	$19
	dc.b	"d32$341",0
	dc.b	$10
	dc.b	"David Roberts",0
	dc.b	$07
	dc.b	"b#",$22,"$2$A",0
	dc.b	$12
	dc.b	"Sergei Nemchinov"
	dc.b	$13
	dc.b	"eSD",$22,"DdQ"
dat_005460:
	dc.b	$00,$0E
	dc.b	"Mike Ridley",0
	dc.w	$1793,$3433,$1833,$4541,$000E
	dc.b	"Scott Walker$R##5",$22,"26",0
	dc.b	$0C
	dc.b	"Pavel Bure"
	dc.w	$9656,$6645,$1465,$6561,$0010
	dc.b	"Trevor Linden",0
	dc.b	$16,$94
	dc.b	"ED!EDE",0
	dc.b	$12
	dc.b	"Alexandr Mogilny"
	dc.w	$8976,$6645,$1266,$5661,$000E
	dc.b	"Brian Noonan(s4C534C",0
	dc.b	$10
	dc.b	"Mike Sillinger&s3",$22,"'2E1",0
	dc.b	$10
	dc.b	"Larry Bohonos",0
	dc.b	$14
	dc.b	"c33$332",0
	dc.b	$0E
	dc.b	"Troy Crowder"
	dc.b	$18
	dc.b	"r#",$22,"53",$22,""
	dc.b	$18,$00,$02,$00,$0C
	dc.b	"Vancouver",0
	dc.w	$0006,$5641,$4E00,$000A
	dc.b	"Canucks",0
	dc.b	$00,$16
	dc.b	"General Mo"
dat_005558:
	dc.b	"tors Place",0
	dc.b	$11,$11,$12
	dc.b	"",$22,"334DUUU_"
	dc.b	$FF
; roster: Washington Capitals (US Air Arena)
Roster_Washington:
	dc.w	$0092,$000C,$02DE,$0052,$004C,$0050,$0ECA,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0048,$0008,$0EEE,$0E20
	dc.w	$0048,$0888,$0600,$0C00,$008C,$0C86,$0ECA,$0200
	dc.w	$0800,$0A22,$0C24,$066A,$0E0E,$0AAA,$0EEE,$0200
	dc.w	$0048,$0888,$0200,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C100,$0104,$050C,$1518,$1900,$0104,$050C,$1518
	dc.w	$1900,$0107,$090F,$161A,$1400,$0103,$060D,$1419
	dc.w	$1300,$0104,$050C,$1518,$1900,$0107,$090F,$161A
	dc.w	$1400,$0104,$050C,$1518,$1900,$0107,$090F,$161A
	dc.w	$1400,$000E
	dc.b	"Bill Ranford0ECD"
	dc.b	$01,$30,$44,$44,$00,$0E
	dc.b	"Olaf Kolzig",0
	dc.w	$3783,$2223,$0110,$3333,$000E
	dc.b	"Sylvain Cote"
	dc.b	$03
	dc.b	"d3D32E3",0
	dc.b	$0E
	dc.b	"Phil Housley"
	dc.w	$9665,$4523,$1843,$4555,$0012
	dc.b	"Calle Johansson",0
	dc.b	$06,$95
	dc.b	"DC$3TA",0
	dc.b	$0E
	dc.b	"Brendan Witt"
	dc.b	$19,$83
	dc.b	"23V245",0
	dc.b	$0E
	dc.b	"Mark T"
dat_005692:
	dc.b	"inordi$"
	dc.b	$93
	dc.b	"3CX2D7",0
	dc.b	$0C
	dc.b	"Joe Reekie)"
	dc.b	$A3
	dc.b	"",$22,"B4",$22,"35",0
	dc.b	$10
	dc.b	"Sergei GoncharU"
	dc.b	$95
	dc.b	"DE2332",0
	dc.b	$0A
	dc.b	"Ken Klee"
	dc.b	$02,$83
	dc.b	"22E",$22,"44",0
	dc.b	$14
	dc.b	"Jaroslav Svejkvsky4b#",$22,"",$22,"",$22,"",$22,"",$22,"",0
	dc.b	$12
	dc.b	"Steve Konowalchk",$22,"d3C4433",0
	dc.b	$0E
	dc.b	"Chris Simon",0
	dc.b	$17,$D2
	dc.b	"#2J",$22,"",$22,":",0
	dc.b	$0E
	dc.b	"Craig Berube'"
	dc.b	$92,$22,$22,$36,$12,$32,$1B,$00,$0E
	dc.b	"Todd Krygier!R238222",0
	dc.b	$0E
	dc.b	"Mike Eagles",0
	dc.b	"6s!BD",$22,"C#",0
	dc.b	$0E
	dc.b	"Kelly Miller"
	dc.b	$10,$84
	dc.b	"CB",$22,"2EB",0
	dc.b	$14
	dc.b	"Andrei Nikolishin",0
	dc.b	$13
	dc.b	"S3B$2SB",0
	dc.b	$10
	dc.b	"Michal Pivonka "
	dc.b	$84,$44,$43,$16,$43,$45,$51,$00,$10
	dc.b	"Kevin Kaminski#B!"
	dc.b	$12,$34,$11,$32,$28,$00,$0E
	dc.b	"Dale Hunter",0
	dc.b	$32,$82
	dc.b	"$SD3DF",0
	dc.b	$0C
	dc.b	"Adam OateswuFC$TVa",0
	dc.b	$0C
	dc.b	"Joe Juneau"
	dc.w	$9054,$5533,$1542,$4651,$000C
	dc.b	"Pat Peake",0
	dc.w	$1484,$4323,$1933,$3431,$000E
	dc.b	"Peter Bondra"
	dc.w	$1266,$6534,$1455,$5551,$000E
	dc.b	"Rick Tocchet",$22,""
	dc.b	$93
	dc.b	"44I42H",0
	dc.b	$02,$00,$0C
	dc.b	"Washington",0
	dc.b	$06,$57,$53,$48,$00,$00,$0A
	dc.b	"Capitals",0
	dc.b	$0E
	dc.b	"US Air Arena",0
	dc.b	$11,$11,$12
	dc.b	"",$22,"#333DDDU"
	dc.b	$FF
; roster: Team Canada Canada (Unknown)
Roster_TeamCanada:
	dc.w	$0092,$000C,$0302,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$000A,$0EEE,$000C
	dc.w	$0000,$0888,$000A,$000C,$008C,$0C86,$0EC6,$0000
	dc.w	$0006,$000A,$000C,$066A,$0666,$0000,$0EEE,$0222
	dc.w	$0EEE,$0888,$0000,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0107,$0812,$0F11,$1300,$0104,$070E,$101A
	dc.w	$1900,$0105,$080F,$1118,$1300,$0106,$0912,$151B
	dc.w	$1400,$0105,$0A10,$1317,$1100,$0107,$0B1A,$1418
	dc.w	$1500,$0107,$0C12,$1319,$1100,$0109,$0D15,$1114
	dc.w	$1800,$000E
	dc.b	"Patrick Roy",0
	dc.b	"3fDU"
	dc.b	$01,$00,$65,$66,$00,$10
	dc.b	"Martin Brodeur1uFe"
	dc.b	$01,$20,$55,$66,$00,$0C
	dc.b	"Ed Belfour0fDe"
	dc.b	$01,$30,$55,$65,$00,$10
	dc.b	"Scott Stevens",0
	dc.b	$04,$B3
	dc.b	"CTR3TF",0
	dc.b	$12
	dc.b	"Scott Niedermyer'"
	dc.b	$95
	dc.b	"T3$B5B",0
	dc.b	$0E
	dc.b	"Garry Galley"
	dc.b	$03,$73
dat_00599C:
	dc.b	"42$2%A",0
	dc.b	$0E
	dc.b	"Ray Bourque",0
	dc.b	$77,$A5
	dc.b	"EUBeba",0
	dc.b	$0E
	dc.b	"Paul Coffey",0
	dc.b	$07,$96
	dc.b	"U4&RUb",0
	dc.b	$0E
	dc.b	"Al MacInnis",0
	dc.b	$02,$84
	dc.b	"DF72RB",0
	dc.b	$0E
	dc.b	"Larry MurphyU"
	dc.b	$A4
	dc.b	"5D#CUQ",0
	dc.b	$0C
	dc.b	"Rob Blake",0
	dc.b	$44,$A4
	dc.b	"DDI2CC",0
	dc.b	$12
	dc.b	"Eric Desjardins",0
	dc.b	$37,$94
	dc.b	"DTG3CA",0
	dc.b	$12
	dc.b	"Brendan Shanahan"
	dc.b	$94,$A3
	dc.b	"6EU5BF",0
	dc.b	$0E
	dc.b	"Paul Kariya",0
	dc.b	$09
	dc.b	"DU$",$22,"UVb",0
	dc.b	$10
	dc.b	"Wayne Gretzky",0
	dc.w	$9946,$4644,$1464,$5561,$000E
	dc.b	"Mark Messier"
	dc.b	$11,$95
	dc.b	"e4DESV",0
	dc.b	$0E
	dc.b	"Eric Lindros"
	dc.b	$88,$C4
	dc.b	"EFeFRF",0
	dc.b	$10
	dc.b	"Mario Lemieux",0
	dc.b	$66,$A5
	dc.b	"FE)ffa",0
	dc.b	$0C
	dc.b	"Joe Sakic",0
	dc.b	$18
	dc.b	"dFD$UTa",0
	dc.b	$0E
	dc.b	"Ron Francis",0
	dc.b	$10,$93
	dc.b	"6c2DUQ",0
	dc.b	$14
	dc.b	"Vincent Damphousse%dE$"
	dc.b	$10,$54,$34,$51,$00,$10
	dc.b	"Rod BrindAmour"
	dc.b	$17,$94
	dc.b	"DD24eB",0
	dc.b	$10
	dc.b	"Steve Yzerman",0
	dc.w	$1965,$5544,$1553,$5551,$000C
	dc.b	"Adam Oates"
	dc.b	$12
	dc.b	"uFS%TVb",0
	dc.b	$10
	dc.b	"Theoren Fleury"
	dc.b	$14
	dc.b	"5TDEDCE",0
	dc.b	$0E
	dc.b	"Pat Verbeek "
	dc.b	$16
	dc.b	"sD4C5BD",0
	dc.b	$12
	dc.b	"Dino Ciccarelli",0
	dc.b	"",$22,"U5%%4BF",0
	dc.b	$02,$00,$0E
	dc.b	"Team Canada",0
	dc.w	$0006,$4341,$4E00,$0008
	dc.b	"Canada",0
	dc.b	$0A
	dc.b	"Unknown",0
	dc.b	$00,$01,$11
	dc.b	"",$22,"",$22,"",$22,"#4DDDDE_"
; roster: Team USA USA (Unknown)
Roster_TeamUsa:
	dc.w	$0092,$000C,$0306,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$0600,$0EEE,$0E00
	dc.w	$000C,$0888,$0004,$0008,$008C,$0C86,$0ECA,$0200
	dc.w	$0200,$0600,$0A00,$066A,$0E0E,$0008,$0EEE,$000E
	dc.w	$0AAA,$0888,$0004,$0008,$008C,$0C86,$0000,$0000
	dc.w	$C110,$010B,$0912,$1311,$1800,$0104,$0D0F,$1219
	dc.w	$1300,$0105,$0C0E,$131A,$1200,$0106,$0911,$141B
	dc.w	$1000,$0107,$0A0F,$151A,$1300,$0108,$0B10,$1619
	dc.w	$1200,$0109,$0C17,$1A13,$1000,$010A,$0D18,$1B12
	dc.w	$1400,$0012
	dc.b	"John Vanbsbrouk",0
	dc.b	"4T4T"
	dc.b	$01,$10,$44,$55,$00,$0C
	dc.b	"Jim Carey",0
	dc.b	"0fCU"
	dc.b	$01,$00,$55,$66,$00,$0E
	dc.b	"Mike Richter5vCC"
	dc.b	$01,$30,$56,$56,$00,$10
	dc.b	"Derian Hatcher"
	dc.b	$12,$93
	dc.b	"",$22,"4F2C&",0
	dc.b	$0E
	dc.b	"Phil Housley"
	dc.w	$0665,$4523,$1643,$4551,$000E
	dc.b	"Jeff Norton",0
	dc.b	$03
	dc.b	"eD2&BEA",0
	dc.b	$10
	dc.b	"Shawn ChambersI"
	dc.b	$93
	dc.b	"32&231",0
	dc.b	$0E
	dc.b	"Brian Leetch"
	dc.b	$02
	dc.b	"fVSBSdQ",0
	dc.b	$0C
	dc.b	"Gary Suter uDDFCTA",0
	dc.b	$14
	dc.b	"Mathieu Schneider",0
	dc.b	"rtDD43CD",0
	dc.b	$10
	dc.b	"Chris Chelios",0
	dc.b	$07
	dc.b	"tEeGCdF",0
	dc.b	$10
	dc.b	"Kevin Hatcher",0
	dc.b	$04,$B3
	dc.b	"4DU3BF",0
	dc.b	$12
	dc.b	"Shawn McEachern",0
	dc.w	$1474,$5424,$1234,$4241,$000E
	dc.b	"John LeClair"
	dc.b	$10,$B3
	dc.b	"D5D523",0
	dc.b	$0E
	dc.b	"Tony Amonte",0
	dc.w	$0164,$5434,$1234,$4231,$0012
	dc.b	"Steve Konowalchk",$22,"d3C4433",0
	dc.b	$10
	dc.b	"Pat LaFontaine"
	dc.b	$96
	dc.b	"UFD'TDR",0
	dc.b	$10,$4A,$65
dat_005DE0:
	dc.b	"remy Roenick'EUEGDSU",0
	dc.b	$0E
	dc.b	"Mike Modano",0
	dc.w	$0975,$6645,$1445,$5241,$000C
	dc.b	"Joel Otto",0
	dc.b	$29,$B2
	dc.b	"",$22,"cW#D%",0
	dc.b	$0E
	dc.b	"Doug Weight",0
	dc.b	"9cD3",$22,"C5Q",0
	dc.b	$12
	dc.b	"Darren Turcotte",0
	dc.w	$1964,$5445,$1843,$4231,$0012
	dc.b	"Bryan Smolinski",0
	dc.b	$21,$03
	dc.b	"D4#3BD",0
	dc.b	$0C
	dc.b	"Brett Hull"
	dc.b	$16,$94
	dc.b	"E&%EBA",0
	dc.b	$10
	dc.b	"Keith Tkachuk",0
	dc.b	$77,$93
	dc.b	"EEb4BF",0
	dc.b	$0E
	dc.b	"Scott Young",0
	dc.b	"HsT5"
	dc.b	$15,$33,$33,$42,$00,$0E
	dc.b	"Kevin Miller"
	dc.b	$08
	dc.b	"tDC%3C1",0
	dc.b	$02,$00,$0A
	dc.b	"Team USA",0
	dc.b	$06,$55,$53,$41,$00,$00,$06,$55,$53,$41,$00,$00,$0A
	dc.b	"Unknown",0
	dc.b	$00,$01,$11,$11,$11,$12
	dc.b	"#3DDDDU_"
; roster: Team Europe Europe (Unknown)
Roster_TeamEurope:
	dc.w	$0092,$000C,$02DA,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0240,$0EEE,$0460
	dc.w	$008A,$0888,$0000,$0222,$008C,$0C86,$0EC6,$0000
	dc.w	$0220,$0240,$0460,$066A,$0666,$0068,$0EEE,$008A
	dc.w	$0EEE,$0888,$0000,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0106,$0A0E,$1216,$1900,$0107,$0A0E,$1216
	dc.w	$1900,$0108,$0D13,$1015,$1700,$0105,$0611,$1718
	dc.w	$1900,$0107,$0A0E,$1216,$1900,$0106,$0C15,$1017
	dc.w	$1300,$010A,$060E,$1216,$1400,$0104,$0719,$1415
	dc.w	$0F00,$0010
	dc.b	"Dominik Hasek",0
	dc.b	"9FCd"
	dc.b	$01,$30,$66,$66,$00,$12
	dc.b	"Tommy Soderstrom0332"
	dc.b	$01,$20,$32,$32,$00,$0E
	dc.b	"Arturs Irbe",0
	dc.b	"2S3",$22,""
	dc.b	$01,$40,$33,$32,$00,$10
	dc.b	"Ulf SamuelssonU"
	dc.b	$84
	dc.b	"BRD1T2",0
	dc.b	$0E
	dc.b	"Jyrki Lumme",0
	dc.b	"!uDC"
	dc.b	$12,$33,$45,$41,$00,$12
	dc.b	"Sandis Ozolins"
dat_006008:
	dc.b	$68,$00,$06
	dc.b	"uD4",$22,"CDB",0
	dc.b	$0E
	dc.b	"Steve Smith",0
	dc.b	$05,$B4
	dc.b	"CSV",$22,"RF",0
	dc.b	$10
	dc.b	"Alexei ZhitnikDeD#&BEA",0
	dc.b	$12
	dc.b	"Niklas Lidstrom",0
	dc.b	$15
	dc.b	"UDD",$22,"3EA",0
	dc.b	$0E
	dc.b	"Sergei ZubovVuE5'R5a",0
	dc.b	$10
	dc.b	"Roman Hamrlik",0
	dc.b	"Et4DDC4C",0
	dc.b	$12
	dc.b	"Kjell Samuelsson("
	dc.b	$E1
	dc.b	"!CG123",0
	dc.b	$0E
	dc.b	"Petr Svoboda#U2C8!E4",0
	dc.b	$0C
	dc.b	"Pavel Bure"
	dc.w	$9656,$6535,$1455,$4251,$000E
	dc.b	"Mats Sundin",0
	dc.w	$1375,$5544,$1554,$4551,$0010
	dc.b	"Alexei Yashin",0
	dc.b	$19,$95
	dc.b	"U$#T3Q",0
	dc.b	$10
	dc.b	"Alexei Zhamnov"
	dc.b	$10
	dc.b	"uU4$SEQ",0
	dc.b	$10
	dc.b	"Sergei Fedorov"
	dc.b	$91
	dc.b	"veT$dTQ",0
	dc.b	$0C
	dc.b	"Jari Kurri"
	dc.b	$17,$83
	dc.b	"4D'CTA",0
	dc.b	$10
	dc.b	"Alexei Kovalev'vS%2cSQ",0
	dc.b	$10
	dc.b	"Teemu Selanne",0
	dc.b	$08
	dc.b	"ee$%URQ",0
	dc.b	$0E
	dc.b	"Jaromir Jagrh"
	dc.b	$A5
	dc.b	"fEBfdb",0
	dc.b	$0C
	dc.b	"Owen Nolan"
	dc.b	$11,$83
	dc.b	"D%G4B6",0
	dc.b	$0E
	dc.b	"Peter Bondra"
	dc.w	$1264,$6534,$1455,$4241,$0012
	dc.b	"Alexandr Mogilny"
	dc.w	$8976,$6635,$1455,$4251,$0002,$000E
	dc.b	"Team Europe",0
dat_0061D8:
	dc.w	$0006,$4555,$5200,$0008
	dc.b	"Europe",0
	dc.b	$0A
	dc.b	"Unknown",0
	dc.b	$00,$01,$11,$11,$12
	dc.b	"",$22,"#DDDUU_"
	dc.b	$FF
; roster: All Stars East All Stars East (Fleet Center)
Roster_AllStarsEast:
	dc.w	$0092,$000C,$02C6,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0860,$0EEE,$0CA0
	dc.w	$0A88,$0888,$0000,$0222,$008C,$0C86,$0EC6,$0000
	dc.w	$0860,$0A80,$0CA0,$066A,$0666,$0000,$0EEE,$0222
	dc.w	$0CAA,$0888,$0000,$0222,$008C,$0C86,$0000,$0000
	dc.w	$C110,$0105,$090B,$0F16,$1000,$0105,$090B,$0F16
	dc.w	$0D00,$0106,$080A,$0C11,$0B00,$0104,$0713,$0D12
	dc.w	$1000,$0104,$0813,$0E14,$0D00,$0107,$0616,$1015
	dc.w	$0B00,$0104,$090D,$0F11,$1600,$0105,$080B,$1610
dat_00628E:
	dc.b	$0A,$00,$00,$10
	dc.b	"Dominik Hasek",0
	dc.b	"9FCf"
	dc.b	$01,$40,$66,$66,$00,$10
	dc.b	"Martin Brodeur0uFf"
	dc.b	$01,$40,$66,$66,$00,$12
	dc.b	"John Vanbsbrouk",0
	dc.b	"444T"
	dc.b	$01,$30,$55,$55,$00,$0E
	dc.b	"Ray Bourque",0
	dc.b	"wd4d$6Eb",0
	dc.b	$0E
	dc.b	"Paul Coffey",0
	dc.b	$77,$96
	dc.b	"Td&TUb",0
	dc.b	$10
	dc.b	"Kevin Hatcher",0
	dc.b	$04,$B3
	dc.b	"4EU3BF",0
	dc.b	$10
	dc.b	"Scott Lachance"
	dc.b	$07,$83
	dc.b	"336251",0
	dc.b	$0E
	dc.b	"Brian Leetch"
dat_006344:
	dc.b	$02
	dc.b	"fTcBTda",0
	dc.b	$10
	dc.b	"Scott Stevens",0
	dc.b	$04,$B3
	dc.b	"DdT3TF",0
	dc.b	$10
	dc.b	"Robert Svehla",0
	dc.b	"$s$3",$22,"B5B",0
	dc.b	$0E
	dc.b	"John LeClair"
	dc.b	$10,$B3
	dc.b	"D5D523",0
	dc.b	$12
	dc.b	"Geoff Sanderson",0
	dc.b	$08
	dc.b	"eU4",$22,"EDR",0
	dc.b	$10
	dc.b	"Mario Lemieux",0
	dc.w	$66A5,$4644,$1066,$6661,$000E
	dc.b	"Mark Messier"
	dc.b	$11,$95
	dc.b	"e4VUUW",0
	dc.b	$0E
	dc.b	"Eric"
dat_0063E0:
	dc.b	" Lindros"
	dc.b	$88,$C4
	dc.b	"EFeFRF",0
	dc.b	$10
	dc.b	"Wayne Gretzky",0
	dc.w	$9946,$4644,$1264,$6660,$000C
	dc.b	"Adam Oates"
	dc.b	$12
	dc.b	"uFS%TVb",0
	dc.b	$10
	dc.b	"Dale Hawerchuk"
	dc.b	$18
	dc.b	"dEC&CEQ",0
	dc.b	$0E
	dc.b	"Dale Hunter",0
	dc.b	$32,$82
	dc.b	"$SD3DF",0
	dc.b	$0E
	dc.b	"Jaromir Jagrh"
	dc.b	$A5,$56,$45,$10,$66,$66,$61,$00,$12
	dc.b	"Dino Ciccarelli",0
	dc.b	"",$22,"EE5%4DG",0
	dc.b	$0E
	dc.b	"Peter Bondra"
	dc.w	$1264,$6534,$1455,$4241,$000E
	dc.b	"Mark"
dat_006496:
	dc.b	" Recchi",0
	dc.b	$08
	dc.b	"c54",$22,"DDR",0
	dc.b	$14
	dc.b	"Daniel Alfredsson",0
	dc.w	$1163,$4524,$1144,$3351,$0002,$0010
	dc.b	"All Stars East",0
	dc.b	$06,$41,$53,$45,$00,$00,$10
	dc.b	"All Stars East",0
	dc.b	$0E
	dc.b	"Fleet Center",0
	dc.b	$01,$11,$12
	dc.b	"",$22,"3DDDUUU"
	dc.b	$FF,$FF
; roster: All Stars West All Stars West (Fleet Center)
Roster_AllStarsWest:
	dc.w	$0092,$000C,$02A6,$0052,$004C,$0050,$0EC6,$0000
	dc.w	$0888,$0CCC,$0EEE,$066A,$0666,$0608,$0EEE,$0A0C
	dc.w	$0A88,$0888,$0000,$0222,$008C,$0C86,$0EC6,$0000
	dc.w	$0404,$0608,$0A0C,$066A,$0666,$0000,$0EEE,$0222
	dc.w	$0CAA,$0888,$0000
dat_00654C:
	dc.w	$0222,$008C,$0C86,$0000,$0000,$C110,$0109,$080B
	dc.w	$1110,$0E00,$0109,$080B,$1115,$1000,$0104,$060A
	dc.w	$0C13,$1000,$0105,$070E,$0D14,$0F00,$0105,$0616
	dc.w	$0F12,$1100,$0104,$080B,$1017,$1400,$0109,$070C
	dc.w	$1410,$1200,$0105,$080D,$1511,$1000,$000E
	dc.b	"Patrick Roy",0
	dc.b	"3fDe",0
	dc.b	$40,$66,$55,$00,$0C
	dc.b	"Andy Moog",0
	dc.b	"5C3T"
	dc.b	$01,$40,$44,$44,$00,$0C
	dc.b	"Guy Hebert1dCD",0
	dc.b	$30,$44,$44,$00,$10
	dc.b	"Chris Chelios",0
	dc.b	$07
	dc.b	"tEegDdE",0
	dc.b	$12
	dc.b	"Viachslv Fetisov"
	dc.b	$02,$A3
	dc.b	"3C$24A",0
	dc.b	$10
	dc.b	"Derian Hatcher"
	dc.b	$02,$93
	dc.b	"",$22,"4F2C'",0
	dc.b	$0E
	dc.b	"Al MacInnis",0
	dc.b	$02,$84
	dc.b	"DJ12RA",0
	dc.b	$12
	dc.b	"Sandis Ozolinsh",0
	dc.b	$08
	dc.b	"uTd",$22,"CUR",0
	dc.b	$12
	dc.b	"Oleg Tverdovsky",0
	dc.b	" UT3&B5Q",0
	dc.b	$0E
	dc.b	"Paul Kariya",0
	dc.b	$09
	dc.b	"Ff%",$22,"fEP",0
	dc.b	$0E
	dc.b	"Tony Granato!dTC6334",0
	dc.b	$14
	dc.b	"Dimitri Khristich",0
	dc.b	$08
	dc.b	"tE4%DDR",0
	dc.b	$12
	dc.b	"Brendan Shanahan"
	dc.b	$14,$A4
	dc.b	"FFf5dF",0
	dc.b	$10
	dc.b	"Keith Tkachuk",0
	dc.b	$07,$93
	dc.b	"FFfDDV",0
	dc.b	$10
	dc.b	"Steve Yzerman",0
	dc.w	$1965,$5644,$1455,$5551,$000E
	dc.b	"Mats Sundin",0
	dc.w	$1375,$5644,$1255,$5551,$000E
	dc.b	"Jason Arnott"
	dc.b	$07,$84
	dc.b	"E45DDC",0
	dc.b	$10
	dc.b	"Teemu Selanne",0
	dc.b	$08
	dc.b	"ff$%fUQ",0
	dc.b	$10
	dc.b	"Theoren Fleury"
	dc.b	$14
	dc.b	"%UDEUDE",0
	dc.b	$0C
	dc.b	"Pavel Bure"
	dc.w	$9656,$6645,$1465,$5551,$000E
	dc.b	"Tony Amonte",0
	dc.w	$1064,$5634,$1245,$4551,$000C
	dc.b	"Brett Hull"
	dc.b	$16,$94
	dc.b	"E6$EDA",0
	dc.b	$0C
	dc.b	"Owen Nolan"
	dc.b	$11,$83
	dc.b	"E5G5DF",0
	dc.b	$02,$00,$10
	dc.b	"All Stars West",0
	dc.b	$06,$41,$53,$57,$00,$00,$10
	dc.b	"All Stars West",0
	dc.b	$0E
	dc.b	"Fleet Center",0
	dc.b	$01,$11,$12
	dc.b	"#33DEUU_"
	dc.b	$FF,$FF
; roster: EA Sports EA Sports (EA Sports Arena)
Roster_EaSports:
	dc.w	$0092,$000C,$029E,$0052,$004C,$0050,$0EC8,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0444,$0800,$0EEE,$0E20
	dc.w	$000C,$0888,$0006,$000A,$008C,$0C86,$0ECA,$0200
	dc.w	$0800,$0A20,$0E40,$066A,$0E0E,$000A,$0EEE,$000E
	dc.w	$0CCC,$0888,$0006,$000A,$008C,$0C86,$0000,$0000
	dc.w	$C100,$010C,$0514,$0B0F,$1100,$010C,$050B,$0F14
	dc.w	$1000,$0107,$040E,$1015,$1100,$0108,$090D,$1117
	dc.w	$1400,$0107,$0A0B,$0F14,$1000,$0105,$060C,$1017
	dc.w	$1500,$0104,$0A0B,$0F12,$1000,$0103,$080C,$100E
	dc.w	$1500,$0012
	dc.b	"Marvin Hirschel",0
	dc.w	$3216,$6666,$0160,$4444,$000E
	dc.b	"Mike Graben",0
	dc.b	"fvff"
	dc.b	$01,$60,$44,$44,$00,$0E
	dc.b	"Ken Zarifes",0
	dc.b	"$vffafda",0
	dc.b	$0E
	dc.b	"Mike Hensley%"
	dc.b	$B6
	dc.b	"ff`fca",0
	dc.b	$0E
	dc.b	"Mark Lesser",0
	dc.b	$01
	dc.b	"fffaffa",0
	dc.b	$0C
	dc.b	"Kyra Woody"
	dc.b	$15,$06
	dc.b	"ffafea",0
	dc.b	$10
	dc.b	"Eric Petersen",0
	dc.b	$06
	dc.b	"vff`fcg",0
	dc.b	$12
	dc.b	"Mitzi McGilvray",0
	dc.b	$13,$06
	dc.b	"ffafea",0
	dc.b	$0C
	dc.b	"Rob Martyn"
	dc.b	$04
	dc.b	"Fff`fcf",0
	dc.b	$0E
	dc.b	"Scott Probin'&ffafca",0
	dc.b	$0E
	dc.b	"Shawn Jacoby"
	dc.b	$19
	dc.b	"fffafcf",0
	dc.b	$0E
	dc.b	"Rich"
dat_00697E:
	dc.b	" Rogers",0
	dc.b	"9vff`fcf",0
	dc.b	$10
	dc.b	"Rick Andrakin",0
	dc.b	$44,$A6
	dc.b	"ffafcl",0
	dc.b	$10
	dc.b	"Bones Johnson",0
	dc.b	$09
	dc.b	"6ff`fca",0
	dc.b	$0E
	dc.b	"Craig Schramw"
	dc.b	$96
	dc.b	"ffafal",0
	dc.b	$12
	dc.b	"Billy DelliGatti36ffafcf",0
	dc.b	$10
	dc.b	"Geronimo Flash"
	dc.b	$91
	dc.b	"fffafba",0
	dc.b	$10
	dc.b	"Daniel Lesser",0
	dc.b	$90
	dc.b	"vffafcf",0
	dc.b	$10
	dc.b	"Nathan Lesser",0
	dc.b	$92
	dc.b	"vffafcf",0
	dc.b	$0C
	dc.b	"Ken RogersqFffafag",0
	dc.b	$0C
	dc.b	"Mike Olsen"
	dc.b	$14
	dc.b	"Vffafca",0
	dc.b	$0E
	dc.b	"Tim Yanuska",0
	dc.b	$21,$06
	dc.b	"ffafca",0
	dc.b	$0E
	dc.b	"Jean Michno",0
	dc.b	"EVffafcf",0
	dc.b	$02,$00,$0C
	dc.b	"EA Sports",0
	dc.b	$00,$04,$45,$41,$00,$0C
	dc.b	"EA Sports",0
	dc.b	$00,$12
	dc.b	"EA Sports Arena",0
	dc.b	$00,$11,$11
	dc.b	"",$22,"",$22,"33DDEU_"
	dc.b	$FF,$FF
; EA staff names and licensing text in roster record format
Roster_Credits:
	dc.w	$0092,$000C,$0268,$0052,$004C,$0050,$0EC6,$0200
	dc.w	$0888,$0CCC,$0EEE,$066A,$0E0E,$000A,$0EEE,$000E
	dc.w	$0000,$0222,$000A,$000E,$008C,$0EA6,$0EC6,$0200
	dc.w	$0006,$000A,$000E,$066A,$0E0E,$0000,$0EEE,$0222
	dc.w	$0CCC,$0888,$0000,$0222,$008C,$0EA6,$0000,$0000
	dc.w	$C110,$0105,$040A,$090B,$0E00,$0105,$040A,$090B
	dc.w	$1300,$0107,$0612,$0E0F,$1100,$010C,$0B08,$090A
	dc.w	$1000,$0105,$040A,$090B,$1300,$0114,$0715,$0E13
	dc.w	$1100,$0114,$040A,$090B,$1300,$010C,$0B08,$1311
	dc.w	$1000,$0012
	dc.b	"Erick Fernandez",0
	dc.w	$0126,$6666,$0160,$6666,$000E
	dc.b	"Jason Lewis",0
	dc.w	$0066,$6666,$0160,$6666,$0010
	dc.b	"Edward Ramiro",0
	dc.b	"1vff"
	dc.b	$01,$60,$66,$66,$00,$10
	dc.b	"Erik van Rooy",0
	dc.b	"wvffafcl",0
	dc.b	$0C
	dc.b	"Steve Ryno"
	dc.b	$16,$86
	dc.b	"ff`fca",0
	dc.b	$0E
	dc.b	"Donn Nauert",0
	dc.b	"!fffafca",0
	dc.b	$0E
	dc.b	"Skot Travis",0
	dc.b	$38,$F6
	dc.b	"ff`fca",0
	dc.b	$10
	dc.b	"Gabriel Jones",0
	dc.b	$66,$86
	dc.b	"ff`fca",0
	dc.b	$0E
	dc.b	"Greg Gibson",0
	dc.b	$97
	dc.b	"Fff`fca",0
	dc.b	$0E
	dc.b	"Sanders Keel"
	dc.b	$96,$F6
	dc.b	"ffoffo",0
	dc.b	$0C
	dc.b	"Jym Killy",0
	dc.b	$67,$F6
	dc.b	"ffoffo",0
	dc.b	$10
	dc.b	"Brian Farrell",0
	dc.b	$94
	dc.b	"Vff`fca",0
	dc.b	$0C
	dc.b	"Jon OsbornUVff`fca",0
	dc.b	$0E
	dc.b	"Eric Larson",0
	dc.b	$19
	dc.b	"6ffafca",0
	dc.b	$0E
	dc.b	"Kirk Somdal",0
	dc.b	$18,$06
	dc.b	"ff`fcg",0
	dc.b	$12
	dc.b	"Christian Kenny",0
	dc.b	"3Fffaf`g",0
	dc.b	$0E
	dc.b	"Scott Ogden",0
	dc.b	$17
	dc.b	"Fffafcl",0
	dc.b	$0E
	dc.b	"Mike Murray",0
	dc.b	"#fffafca",0
	dc.b	$0E
	dc.b	"Mike Haller",0
	dc.b	$91
	dc.b	"vffafca",0
	dc.b	$0C
	dc.b	"Steve KeelD"
	dc.b	$16
	dc.b	"ff`fca",0
	dc.b	$0C
	dc.b	"Jon Ardell Fff`fca",0
	dc.b	$02,$00,$0E
	dc.b	"Angry Legion",0
	dc.b	$04,$41,$4C,$00,$0E
	dc.b	"Angry Legion",0
	dc.b	$16
	dc.b	"Calabasas Angry Dome",0
	dc.b	$01,$11,$11
	dc.b	"",$22,"",$22,"34DE_"
	dc.b	$FF,$FF,$FF
dat_006D74:
	incbin	"data/bin/data_006D74.bin"	; 548 bytes
dat_006F98:
	dc.b	$79,$00,$00,$18
	dc.b	"Sega Enterprises Ltd.",0
	dc.b	$00,$04,$FF,$00
dat_006FB6:
	dc.b	$00,$18
	dc.b	"NHL 98 Software $ 1997",0
	dc.b	$16
	dc.b	"All rights reserved.",0
	dc.b	$16
	dc.b	"EA SPORTS and the EA",0
	dc.b	$12
	dc.b	"SPORTS logo are",0
	dc.b	$00,$14
	dc.b	"trademarks of and",0
	dc.b	$00,$10
	dc.b	"",$22,"If its in the",0
	dc.b	$18
	dc.b	"game, its in the game",$22,"",0
	dc.b	$12
	dc.b	"is a registered",0
	dc.b	$00,$1A
	dc.b	"trademark of Electronic",0
	dc.b	$00,$18
	dc.b	"Arts. National Hockey",0
	dc.b	$00,$16
	dc.b	"League, NHL, the NHL",0
	dc.b	$18
	dc.b	"shield and Stanley Cup",0
	dc.b	$14
	dc.b	"name and logo are",0
	dc.b	$00,$18
	dc.b	"registered trademarks",0
	dc.b	$00,$18
	dc.b	"of the National Hockey",0
	dc.b	$16
	dc.b	"League and are used",0
	dc.b	$00,$12
	dc.b	"under license by",0
	dc.b	$12
	dc.b	"Electronic Arts.",0
	dc.b	$04,$20,$00,$00,$16
	dc.b	"Officially Licensed",0
	dc.b	$00,$10
	dc.b	"Product of the",0
	dc.b	$12
	dc.b	"National Hockey",0
	dc.b	$00,$18
	dc.b	"League. All NHL logos",0
	dc.b	$00,$14
	dc.b	"and marks and team",0
	dc.b	$12
	dc.b	"logos and marks",0
	dc.b	$00,$16
	dc.b	"depicted herein are",0
	dc.b	$00,$02,$00,$16
	dc.b	"the property of the",0
	dc.b	$00,$0E
	dc.b	"NHL and the",0
	dc.b	$00,$16
	dc.b	"respective teams and",0
	dc.b	$18
	dc.b	"may not be reproduced",0
	dc.b	$00,$14
	dc.b	"without the prior",0
	dc.b	$00,$14
	dc.b	"written consent of",0
	dc.b	$18
	dc.b	"NHL Enterprises, L.P.",0
	dc.b	$00,$16
	dc.b	"(c)1997 NHL. NHLPA,",0
	dc.b	$00,$12
	dc.b	"National Hockey",0
	dc.b	$00,$10
	dc.b	"League Players",0
	dc.b	$16
	dc.b	"Association and the",0
	dc.b	$00,$14
	dc.b	"logo of the NHLPA",0
	dc.b	$00,$14
	dc.b	"are trademarks of",0
	dc.b	$00,$14
	dc.b	"the NHLPA and are",0
	dc.b	$00,$14
	dc.b	"used under l"
dat_0072F4:
	dc.b	"icense",0
	dc.b	$16
	dc.b	"by Electronic Arts.",0
	dc.b	$00,$14
	dc.b	"$ NHLPA Officially",0
	dc.b	$16
	dc.b	"Licensed Product of",0
	dc.b	$00,$16
	dc.b	"the National Hockey",0
	dc.b	$00,$10
	dc.b	"League Players",0
	dc.b	$0E
	dc.b	"Association.",0
	dc.b	$02,$00,$04,$20,$00,$00,$04,$20,$00,$00,$10
	dc.b	"Programmed by:",0
	dc.b	$10
	dc.b	"Chris Shrigley",0
	dc.b	$04,$20,$00,$00,$0E
	dc.b	"Directed by:",0
	dc.b	$10
	dc.b	"Thomas Fessler",0
	dc.b	$04,$20,$00,$00,$10
	dc.b	"NHL 98 Art by:",0
	dc.b	$10
	dc.b	"Thomas Fessler",0
	dc.b	$04,$20,$00,$00,$16
	dc.b	"Music and Sound by:",0
	dc.b	$00,$12
	dc.b	"David Whittaker",0
	dc.b	$00,$04,$20,$00,$00,$16
	dc.b	"V.P. of Production:",0
	dc.b	$00,$0C
	dc.b	"Scott Orr",0
	dc.w	$0002,$0004,$2000,$0014
	dc.b	"Vice President of",0
	dc.b	$00,$16
	dc.b	"Product Development:",0
	dc.b	$0C
	dc.b	"Steve Ryno",0
	dc.b	$04,$20,$00
dat_007470:
	dc.b	$00,$16
	dc.b	"Executive Producer:",0
	dc.b	$00,$0E
	dc.b	"Donn Nauert",0
	dc.b	$00,$04,$20,$00,$00,$12
	dc.b	"Senior Producer:",0
	dc.b	$0E
	dc.b	"Greg Gibson",0
	dc.b	$00,$04,$20,$00,$00,$0C
	dc.b	"Producer:",0
	dc.b	$00,$0C
	dc.b	"Jym Killy",0
	dc.b	$00,$04,$20,$00,$00,$0C
	dc.b	"Producers:",0
	dc.b	$0C
	dc.b	"Jon Osborn",0
	dc.b	$10
	dc.b	"Gabriel Jones",0
	dc.b	$00,$04,$20,$00,$00,$14
	dc.b	"Associate Producer",0
	dc.b	$0E
	dc.b	"Sanders Keel",0
	dc.b	$12
	dc.b	"Erick Fernandez",0
	dc.w	$0002,$0004,$2000,$000E
	dc.b	"Lead Tester",0
	dc.b	$00,$10
	dc.b	"Erik van Rooy",0
	dc.b	$00,$04,$20,$20
dat_007560:
	dc.b	$00,$0E
	dc.b	"Testing by:",0
	dc.b	$00,$0E
	dc.b	"Jason Lewis",0
	dc.b	$00,$0E
	dc.b	"Skot Travis",0
	dc.b	$00,$10
	dc.b	"Edward Ramiro",0
	dc.b	$00,$0C
	dc.b	"Mia Haller",0
	dc.b	$0A
	dc.b	"Jekel 1",0
	dc.b	$00,$04,$20,$20,$00,$14
	dc.b	"Player Ratings by:",0
	dc.b	$0E
	dc.b	"Sanders Keel",0
	dc.b	$14
	dc.b	"Erik van Rooy and",0
	dc.b	$00,$10
	dc.b	"Thomas Fessler",0
	dc.b	$04,$20,$00,$00,$14
	dc.b	"Special Thanks to:",0
	dc.b	$12
	dc.b	"Melissa Louviaux",0
	dc.b	$0E
	dc.b	"Kirk Somdal",0
	dc.b	$00,$0E
	dc.b	"Vic Blevons",0
	dc.b	$00,$0E
	dc.b	"Lisa Paulson",0
	dc.b	$0C
dat_007650:
	dc.b	"Steve Keel",0
	dc.b	$10
	dc.b	"Maria Coniglio",0
	dc.b	$02,$00,$16
	dc.b	"",$22,"Get Ready For This",$22,"",0
	dc.b	$0E
	dc.b	"Written By:",0
	dc.b	$00,$16
	dc.b	"Jean Paul De Coster,",0
	dc.b	$14
	dc.b	"Filip De Wilde and",0
	dc.b	$0E
	dc.b	"Simon Harris",0
	dc.b	$16
	dc.b	"Published by: Music",0
	dc.b	$00,$1A
	dc.b	"Corporation of America,",0
	dc.b	$00,$14
	dc.b	"Inc. International",0
	dc.b	$1A
	dc.b	"Rights Secured. Not for",0
	dc.b	$00,$1A
dat_007728:
	dc.b	"broadcast transmission.",0
	dc.b	$00,$16
	dc.b	"All rights reserved.",0
	dc.b	$14
	dc.b	"DO NOT DUPLICATE.",0
	dc.b	$00,$14
	dc.b	"WARNING: ",$22,""
dat_007776:
	dc.b	"It is a",0
	dc.b	$00,$16
	dc.b	"violation of Federal",0
	dc.b	$12
	dc.b	"Copyright Law to",0
	dc.b	$1A
	dc.b	"synchronize the musical",0
	dc.b	$00,$12
	dc.b	"portion of this",0
	dc.b	$00,$1A
	dc.b	"multimedia program with",0
	dc.b	$00,$18
	dc.b	"video tape or film, or",0
	dc.b	$16
	dc.b	"to print the musical",0
	dc.b	$12
	dc.b	"portion of this",0
	dc.b	$00,$18
	dc.b	"MULTIMEDIA program in",0
	dc.b	$00,$18
	dc.b	"the form of standard ",0
	dc.b	$00,$18
	dc.b	"music notation without",0
	dc.b	$16
	dc.b	"the express written",0
	dc.b	$00,$14
	dc.b	"permission of the",0
	dc.b	$00,$14
	dc.b	"copyright owner.",$22,"",0
	dc.b	$00,$02
dat_0078B4:
	incbin	"data/bin/data_0078B4.bin"	; 950 bytes
dat_007C6A:
	incbin	"data/bin/data_007C6A.bin"	; 916 bytes
dat_007FFE:
	dc.b	$01,$66
dat_008000:
	incbin	"data/bin/data_008000.bin"	; 10488 bytes
dat_00A8F8:
	incbin	"data/bin/data_00A8F8.bin"	; 4070 bytes

