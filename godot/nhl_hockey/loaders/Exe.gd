class_name Exe
## The data object of HOCKEY.EXE (the LE image behind the DOS/4GW stub, tools/le.py) loaded at its
## linear address with the internal 32 bit fixups applied, so the front end can read the original
## tables (menu records, button lists, team order, screen coordinates, strings) at the addresses the
## decompiled code uses: Exe.str_at(0xc35f3), Exe.i32(0xd227c + 16 * i), Exe.str_ptr(0xd21c0 + 4 * k).
## Code objects are not loaded. Everything is static and read on first use from GameFiles.

static var _objects: Array = []        # [base, PackedByteArray] of the data objects
static var _loaded := false
static var ok := false

## loads the executable from given bytes (the tests; otherwise the GameFiles autoload is asked)
static func load_from(raw: PackedByteArray) -> void:
	_objects.clear()
	_loaded = false
	_parse(raw)
	_loaded = true

static func _load() -> void:
	if _loaded:
		return
	_loaded = true
	var raw := PackedByteArray()
	var tree := Engine.get_main_loop() as SceneTree
	var gf: Node = tree.root.get_node_or_null("GameFiles") if tree != null else null
	if gf != null:
		raw = gf.read_raw("hockey.exe")
	_parse(raw)

static func _parse(raw: PackedByteArray) -> void:
	if raw.size() < 0x40:
		return
	# the MZ stub whose e_lfanew points at the LE header (the last one: bound extenders come first)
	var le := -1
	var stub := 0
	var pos := 0
	while true:
		pos = _find(raw, "MZ", pos)
		if pos < 0 or pos + 0x40 > raw.size():
			break
		var lfanew := raw.decode_u32(pos + 0x3c)
		var at := pos + lfanew
		if lfanew > 0 and at + 4 <= raw.size() and raw[at] == 0x4c and raw[at + 1] == 0x45 and raw[at + 2] == 0 and raw[at + 3] == 0:
			le = at
			stub = pos
		pos += 2
	if le < 0:
		return
	var num_pages := raw.decode_u32(le + 0x14)
	var page_size := raw.decode_u32(le + 0x28)
	var last_page := raw.decode_u32(le + 0x2c)
	var obj_table := le + raw.decode_u32(le + 0x40)
	var num_objects := raw.decode_u32(le + 0x44)
	var page_table := le + raw.decode_u32(le + 0x48)
	var fixup_pages := le + raw.decode_u32(le + 0x68)
	var fixup_records := le + raw.decode_u32(le + 0x6c)
	var data_pages := stub + raw.decode_u32(le + 0x80)
	var owners: Dictionary = {}       # logical page -> [object index, page within the object]
	var objs: Array = []
	for i in num_objects:
		var o := obj_table + i * 24
		var vsize := raw.decode_u32(o)
		var base := raw.decode_u32(o + 4)
		var flags := raw.decode_u32(o + 8)
		var pidx := raw.decode_u32(o + 12)
		var npages := raw.decode_u32(o + 16)
		var data := PackedByteArray()
		if flags & 4 == 0:            # not executable: load it
			for p in npages:
				var lp := pidx + p
				var e := page_table + (lp - 1) * 4
				var num := (raw[e] << 16) | (raw[e + 1] << 8) | raw[e + 2]
				var chunk := PackedByteArray()
				if raw[e + 3] == 0:
					var fofs := data_pages + (num - 1) * page_size
					var size := last_page if lp == num_pages else page_size
					chunk = raw.slice(fofs, mini(fofs + size, raw.size()))
				chunk.resize(page_size)
				data.append_array(chunk)
				owners[lp] = [i, p]
			if data.size() < vsize:
				data.resize(vsize)
		objs.append([base, data, flags])
	# internal fixups of the loaded pages: offset 32 (source type 7) to object base + offset
	for lp in owners:
		var start := raw.decode_u32(fixup_pages + (lp - 1) * 4)
		var stop := raw.decode_u32(fixup_pages + lp * 4)
		var obj: Array = objs[owners[lp][0]]
		var page_off: int = owners[lp][1] * page_size
		var p := fixup_records + start
		var end := fixup_records + stop
		while p < end:
			var src := raw[p]
			var flags := raw[p + 1]
			p += 2
			var srcoffs: Array = []
			var count := 0
			if src & 0x20:
				count = raw[p]
				p += 1
			else:
				srcoffs.append(raw.decode_s16(p))
				p += 2
			var tobj := 0
			var toff := 0
			var internal := (flags & 3) == 0
			if internal:
				if flags & 0x40:
					tobj = raw.decode_u16(p)
					p += 2
				else:
					tobj = raw[p]
					p += 1
				if (src & 0x0f) != 2:
					if flags & 0x10:
						toff = raw.decode_u32(p)
						p += 4
					else:
						toff = raw.decode_u16(p)
						p += 2
			else:
				p += 2 if flags & 0x40 else 1
				if (flags & 3) == 1:
					p += 1 if flags & 0x80 else (4 if flags & 0x10 else 2)
				elif (flags & 3) == 2:
					p += 4 if flags & 0x10 else 2
			if flags & 4:
				var add := raw.decode_u32(p) if flags & 0x20 else raw.decode_u16(p)
				p += 4 if flags & 0x20 else 2
				toff += add
			if src & 0x20:
				for k in count:
					srcoffs.append(raw.decode_s16(p + 2 * k))
				p += 2 * count
			if not internal or (src & 0x0f) != 7 or tobj < 1 or tobj > objs.size():
				continue
			var target: int = objs[tobj - 1][0] + toff
			var data: PackedByteArray = obj[1]
			for so in srcoffs:
				var at: int = page_off + so
				if at >= 0 and at + 4 <= data.size():
					data.encode_u32(at, target)
	for o in objs:
		if (o[2] & 4) == 0:
			_objects.append([o[0], o[1]])
	ok = not _objects.is_empty()

static func _find(raw: PackedByteArray, s: String, from: int) -> int:
	var a := s.unicode_at(0)
	var b := s.unicode_at(1)
	var i := raw.find(a, from)
	while i >= 0 and i + 1 < raw.size():
		if raw[i + 1] == b:
			return i
		i = raw.find(a, i + 1)
	return -1

static func _at(addr: int) -> Array:
	_load()
	for o in _objects:
		var d: PackedByteArray = o[1]
		if addr >= o[0] and addr < o[0] + d.size():
			return [d, addr - o[0]]
	return []

static func u8(addr: int) -> int:
	var r := _at(addr)
	return r[0][r[1]] if not r.is_empty() else 0

static func i8(addr: int) -> int:
	var v := u8(addr)
	return v - 256 if v >= 128 else v

static func u16(addr: int) -> int:
	var r := _at(addr)
	return r[0].decode_u16(r[1]) if not r.is_empty() and r[1] + 2 <= r[0].size() else 0

static func i16(addr: int) -> int:
	var r := _at(addr)
	return r[0].decode_s16(r[1]) if not r.is_empty() and r[1] + 2 <= r[0].size() else 0

static func u32(addr: int) -> int:
	var r := _at(addr)
	return r[0].decode_u32(r[1]) if not r.is_empty() and r[1] + 4 <= r[0].size() else 0

static func i32(addr: int) -> int:
	var r := _at(addr)
	return r[0].decode_s32(r[1]) if not r.is_empty() and r[1] + 4 <= r[0].size() else 0

static func bytes(addr: int, n: int) -> PackedByteArray:
	var r := _at(addr)
	if r.is_empty():
		return PackedByteArray()
	return (r[0] as PackedByteArray).slice(r[1], r[1] + n)

## the zero terminated (latin-1) string at addr
static func str_at(addr: int, maxlen: int = 256) -> String:
	var r := _at(addr)
	if r.is_empty():
		return ""
	var d: PackedByteArray = r[0]
	var e: int = r[1]
	while e < d.size() and d[e] != 0 and e - r[1] < maxlen:
		e += 1
	return d.slice(r[1], e).get_string_from_ascii() if _ascii(d, r[1], e) else _latin1(d.slice(r[1], e))

static func _ascii(d: PackedByteArray, a: int, b: int) -> bool:
	for i in range(a, b):
		if d[i] >= 0x80:
			return false
	return true

static func _latin1(b: PackedByteArray) -> String:
	var s := ""
	for c in b:
		s += char(c)
	return s

## the string a pointer at addr points to
static func str_ptr(addr: int) -> String:
	var p := u32(addr)
	return str_at(p) if p != 0 else ""

## count pointers to strings from addr
static func str_table(addr: int, count: int) -> PackedStringArray:
	var out := PackedStringArray()
	for i in count:
		out.append(str_ptr(addr + 4 * i))
	return out
