#!/bin/bash
#
# Full pipeline for a 32-bit LE/LX (DOS/4GW) executable:
#   1. ledisasm.py: find routines/variables, write the editable map, listing, JSON, strings, symbols and an ELF image
#   2. optionally Ghidra (headless): import the ELF, apply names and Watcom calling conventions, decompile to C
#
# usage: lede.sh game.exe outdir [name]
#   The map file outdir/name.map is read if it exists (names, comments and annotations are kept) and updated.
#   Set GHIDRA_HOME to a Ghidra installation directory (11.x, needs JDK 21) to also produce outdir/decomp/*.c
#   Requires python3 with the capstone module (pip install capstone).
#
set -e
script_dir=$(cd "$(dirname "$BASH_SOURCE")" && pwd)
exe=$1
outdir=$2
name=${3:-$(basename "${exe%.*}" | tr 'A-Z' 'a-z')}
[ -f "$exe" ] && [ -n "$outdir" ] || { echo "usage: lede.sh game.exe outdir [name]"; exit 1; }
mkdir -p "$outdir/asm"
python3 "$script_dir/ledisasm.py" "$exe" --map "$outdir/$name.map" \
    --asm "$outdir/asm/$name.asm" --split 0x8000 --json "$outdir/$name.json" \
    --strings "$outdir/strings.txt" --symbols "$outdir/$name.sym" --elf "$outdir/$name.elf"
if [ -n "$GHIDRA_HOME" ]; then
    proj=$(mktemp -d)
    mkdir -p "$outdir/decomp"
    "$GHIDRA_HOME/support/analyzeHeadless" "$proj" "$name" -import "$outdir/$name.elf" -overwrite \
        -scriptPath "$script_dir/ghidra" -postScript LEDecompile.java "$outdir/decomp" "$outdir/$name.sym" 0x8000 \
        -deleteProject -analysisTimeoutPerFile 7200 2>&1 | grep -E "LEDecompile|ERROR|Exception" || true
    rm -rf "$proj"
else
    echo "GHIDRA_HOME not set, skipping decompilation"
fi
