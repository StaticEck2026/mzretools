; ============================================================================
; Remaining data
; ROM range $1E6730-$1F5119
; ============================================================================

	incbin	"data/bin/data_1E6730.bin"	; 4004 bytes

ptrtbl_1E76D4:
	dc.l	sub_00DC00
	dc.l	sub_00DC00
	dc.l	sub_00DC00
	incbin	"data/bin/data_1E76E0.bin"	; 55866 bytes
