"""
Recognition of the data structures used by EA's Mega Drive sports games.

Tile sets ("art"):
    +0  dc.l  offset of the palette block (4 palettes = 128 bytes)
    +4  dc.l  offset of the tile map / metadata block
    +8  dc.w  number of 8x8 4bpp tiles
    +10       tiles (32 bytes each)
    +pal      64 colour words
    +map      dc.w width, dc.w height, width*height name table entries
              (the player sprite set uses this block differently)

Roster data: a table of longword pointers to one record per team; each
record ends with the city, nickname and arena strings.
"""

import re
import struct


def find_tilesets(mapper):
    """Return {addr: (count, pal_off, map_off, end)} for every tile set in the
    unclassified parts of the ROM."""
    rom = mapper.rom
    end = mapper.rom_end
    kind = mapper.kind
    found = {}
    a = 0x200
    while a + 10 <= end:
        if kind[a] != 0 or a & 1:
            a += 1
            continue
        offA, offB = struct.unpack('>II', rom[a:a + 8])
        cnt = struct.unpack('>H', rom[a + 8:a + 10])[0]
        if cnt > 0 and offA == 10 + 32 * cnt and offA < offB and a + offB + 4 <= end \
                and offB - offA == 128 and all(kind[x] == 0 for x in range(a, a + offB, 64)):
            w, h = struct.unpack('>HH', rom[a + offB:a + offB + 4])
            aend = None
            if 0 < w <= 128 and 0 < h <= 128 and a + offB + 4 + 2 * w * h <= end:
                aend = a + offB + 4 + 2 * w * h
            found[a] = (cnt, offA, offB, aend)
            a += offB + 4
        else:
            a += 2
    return found


def find_teams(mapper, table=0x77E, count=62):
    """Roster records: {addr: (end, city, nickname, arena)}."""
    rom = mapper.rom
    ptrs = [struct.unpack('>I', rom[table + i * 4:table + i * 4 + 4])[0] for i in range(count)]
    uniq = sorted(set(ptrs))
    teams = {}
    for i, p in enumerate(uniq):
        e = uniq[i + 1] if i + 1 < len(uniq) else None
        if e is None:
            # last record: ends where the next classified byte or a label is
            e = p
            while e < mapper.rom_end and mapper.kind[e] == 0 and e - p < 0x2000:
                e += 1
        # word length prefixed, NUL terminated strings: city, abbreviation, nickname, arena
        recs = []
        # word length (including itself), text padded with a NUL to an even length
        for m in re.finditer(rb'\x00([\x04-\x40])([\x20-\x7e]{1,60})', rom[p:e]):
            n = len(m.group(2))
            if m.group(1)[0] == 2 + n + (n & 1):
                recs.append(m.group(2).decode())
        # the record ends with city, abbreviation (2-3 letters), nickname, arena
        city = nick = arena = ''
        abbr = re.compile(r'^[A-Za-z]{2,3}$')
        if len(recs) >= 4 and abbr.match(recs[-3]):
            city, nick, arena = recs[-4], recs[-2], recs[-1]
        elif len(recs) >= 3 and abbr.match(recs[-2]):
            city, nick = recs[-3], recs[-1]
        teams[p] = (e, city, nick, arena)
    return ptrs, teams


def ident(s):
    """Turn a display string into a label friendly identifier."""
    s = re.sub(r'[^A-Za-z0-9]+', '', s.title())
    return s or 'Unknown'
