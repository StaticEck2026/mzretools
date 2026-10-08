class_name NameSort
## The roster lists' comparators, ported literally (the original has two copies of the same code):
## cmp_player_names_b (0x76a93, the line editor's entries, with qsort) and cmp_key_names (0x6d78b,
## the registry's lists, with shellsort_records). An entry is [position ("" for an empty slot),
## number, slot or key offset, shown name, last name]. L, C, R, D come first in that order, then the
## others, empty slots last; the same position goes by last name (strcmp). Two other positions that
## differ answer 1 both ways, as in the original.

static func cmp_player_names_b(a: Array, b: Array) -> int:
	var pa: int = (a[0] as String).unicode_at(0) if a[0] != "" else 0
	var pb: int = (b[0] as String).unicode_at(0) if b[0] != "" else 0
	if pa == pb:
		return 0 if pa == 0 else Clib.strcmp(a[4], b[4])
	if pa == 0:
		return 1
	if pb == 0:
		return -1
	for c in [0x4c, 0x43, 0x52]:
		if pa == c:
			return -1
		if pb == c:
			return 1
	return -1 if pa == 0x44 else 1

static func cmp_key_names(a: Array, b: Array) -> int:
	var pa: int = (a[0] as String).unicode_at(0) if a[0] != "" else 0
	var pb: int = (b[0] as String).unicode_at(0) if b[0] != "" else 0
	if pa == pb:
		return 0 if pa == 0 else Clib.strcmp(a[4], b[4])
	if pa == 0:
		return 1
	if pb == 0:
		return -1
	for c in [0x4c, 0x43, 0x52]:
		if pa == c:
			return -1
		if pb == c:
			return 1
	return -1 if pa == 0x44 else 1
