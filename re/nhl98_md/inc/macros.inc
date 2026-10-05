; Helper macros.
;
; The C compiled parts of the game use the "general" encodings of
; CMP/ADD/SUB/AND/OR with an immediate source and a data register destination
; (opcode $B07C etc.) instead of CMPI/ADDI/SUBI/ANDI/ORI.  SNASM68K and vasm
; keep "cmp.w #n,d0" in that general form, which is what the main source
; uses.  Should an assembler fold them into the I-forms, regenerate the
; source with --imm-macros to use the macros below, which emit the exact
; words.

REGNO_d0	equ	0
REGNO_d1	equ	1
REGNO_d2	equ	2
REGNO_d3	equ	3
REGNO_d4	equ	4
REGNO_d5	equ	5
REGNO_d6	equ	6
REGNO_d7	equ	7

cmp_imm	macro
	if "\0"="l"
	dc.w	$B0BC|(REGNO_\2<<9)
	dc.l	\1
	elseif "\0"="w"
	dc.w	$B07C|(REGNO_\2<<9),\1
	else
	dc.w	$B03C|(REGNO_\2<<9),\1
	endif
	endm

add_imm	macro
	if "\0"="l"
	dc.w	$D0BC|(REGNO_\2<<9)
	dc.l	\1
	elseif "\0"="w"
	dc.w	$D07C|(REGNO_\2<<9),\1
	else
	dc.w	$D03C|(REGNO_\2<<9),\1
	endif
	endm

sub_imm	macro
	if "\0"="l"
	dc.w	$90BC|(REGNO_\2<<9)
	dc.l	\1
	elseif "\0"="w"
	dc.w	$907C|(REGNO_\2<<9),\1
	else
	dc.w	$903C|(REGNO_\2<<9),\1
	endif
	endm

and_imm	macro
	if "\0"="l"
	dc.w	$C0BC|(REGNO_\2<<9)
	dc.l	\1
	elseif "\0"="w"
	dc.w	$C07C|(REGNO_\2<<9),\1
	else
	dc.w	$C03C|(REGNO_\2<<9),\1
	endif
	endm

or_imm	macro
	if "\0"="l"
	dc.w	$80BC|(REGNO_\2<<9)
	dc.l	\1
	elseif "\0"="w"
	dc.w	$807C|(REGNO_\2<<9),\1
	else
	dc.w	$803C|(REGNO_\2<<9),\1
	endif
	endm
