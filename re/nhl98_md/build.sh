#!/bin/sh
# Rebuild the ROM with vasm (Motorola syntax, no optimisations) and compare
# it with the original.  vasm's "mot" syntax module accepts the same source
# as SNASM68K/asm68k for everything used here.
#
#   ./build.sh [path/to/original.bin]
#
set -e
cd "$(dirname "$0")"
VASM=${VASM:-vasmm68k_mot}
$VASM -m68000 -no-opt -Fbin -o nhl98.bin -L nhl98.lst nhl98.asm
echo "built nhl98.bin ($(wc -c < nhl98.bin) bytes)"
if [ -n "$1" ]; then
    if cmp "$1" nhl98.bin; then
        echo "OK: byte-exact match with $1"
    else
        echo "MISMATCH"
        exit 1
    fi
fi
