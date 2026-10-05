# md68k – Mega Drive / Genesis ROM disassembler

Produces a byte-exact, SNASM68K / asm68k compatible source tree from a Mega Drive ROM.

```
python3 tools/md68k/mddisasm.py rom.bin outdir --name game [--ea] [--segments segments.txt]
        [--names game.names] [--map-cache map.pkl] [--blob-min 0x200] [--max-code 0x10000]
        [--imm-macros]
```

* `m68k.py` – strict 68000 decoder. Rejects everything that is not a legal 68000 instruction and prints
  every operand with an explicit size, so that a non-optimising assembler reproduces the original words.
* `mdmap.py` – code/data mapping: recursive descent from the vector table, word offset jump tables
  (`jmp tbl(pc,d0.w)`, `lea tbl(pc),aN / adda.w (aN,dM.w),aN / jmp (aN)`), longword pointer tables,
  `bra.w` branch tables, address immediates, routines that take inline arguments after the call, and a
  validated sweep for unreferenced routines.
* `mdasm.py` – emitter: labels, hardware and RAM equates, data items (strings, pointer tables, jump tables,
  inline blocks, `incbin` blobs), module files, symbol and names files.
* `mdart.py` – exports the EA tile sets as PNG: pictures through their tile maps, raw tiles, palettes,
  and for sprite sets every frame plus a numbered character sheet (`mdart.py rom.bin outdir --names x.names`).
* `mdextract.py` – one-shot asset ripper: `mdextract.py rom.bin outdir [--names x.names]` writes every
  graphic asset as raw files to `outdir/extracted/` (whole container, tiles, palettes, map) and converts all
  of them to PNG in `outdir/png/` (pictures, tile grids, palettes, sprite frames and sheets), plus a manifest.
* `mdassets.py` – EA specific structures (`--ea`): tile set containers (tiles + 4 palettes + tile map) and
  roster records.

Verification: assemble with `vasmm68k_mot -m68000 -no-opt -Fbin -o out.bin main.asm` (or SNASM68K with
`-o ae-`) and `cmp` the result with the ROM. The `<name>.names` file in the output directory is read back on
every run, so symbol names and comments can be edited there.
