; NHL98 - Sega Mega Drive / Genesis
; Disassembly, reassembles byte-exact with SNASM68K / asm68k (and vasm -m68000 -no-opt -Fbin).

	include	"inc/genesis.inc"
	include	"inc/ram.inc"
	include	"inc/macros.inc"

	org	0
ROM_Start:
	include	"src/boot.asm"	; Vector table, ROM header, entry point, region lockout check, VBlank stub
	include	"data/rosters.asm"	; Team pointer table and roster records (players, team names, arenas)
	include	"src/season.asm"	; Season mode: menus, standings, player stats, transactions, simulation (partly compiled C)
	include	"src/game.asm"	; Game engine: play, penalties, injuries, play-by-play text, exception handlers
	include	"src/system.asm"	; System library: VDP, DMA, palettes, text rendering, joypads, random numbers
	include	"src/game2.asm"	; Game engine, second part: AI, animation, in-game screens
	include	"data/game_tables.asm"	; Tables used by the game engine
	include	"src/sound.asm"	; Sound interface: Z80 driver upload, command queue, SRAM access
	include	"data/sound_data.asm"	; Z80 sound driver and sound bank
	include	"src/sound_glue.asm"	; Sound call wrapper and sound effect helpers
	include	"data/art.asm"	; Graphics: tile sets with palettes and tile maps (title, menus, rink, team logos, fonts)
	include	"src/frontend.asm"	; Front end: team select, playoffs, rosters and trades, options, shootout, stats screens, awards, skills challenge
	include	"data/misc_data.asm"	; Remaining data

ROM_Padding:
	dcb.b	$200000-ROM_Padding,$FF
ROM_End:
	end
