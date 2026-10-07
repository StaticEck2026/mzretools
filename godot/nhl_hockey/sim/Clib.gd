class_name Clib
## Routines of the Watcom C library the game's logic depends on, ported literally where their exact
## behaviour shows: qsort (0x9244c), whose order of equal elements decides the three stars.

## qsort (0x9244c, with __qsort_med3 0x923f4) on an array of elements: below 16 elements an
## insertion sort with the gaps 3 and 1 (the gap 3 pass steps by 3); otherwise the pivot is the
## middle element, from 30 elements on the median of the first, middle and last, from 43 on the
## median of three medians of three; a three way partition keeps the elements equal to the pivot at
## both ends and swaps them to the middle, the larger part waits on a stack. `cmp(a, b)` > 0 when a
## sorts after b.
static func qsort(a: Array, cmp: Callable) -> void:
	var stack_base: Array = []
	var stack_n: Array = []
	var b := 0
	var n := a.size()
	while true:
		if n > 1 and n < 16:
			var gap := 3
			var end := b + n
			while gap > 0:
				var p := b + gap
				while p < end:
					var q := p
					while q > b:
						var r := q - gap
						if int(cmp.call(a[r], a[q])) <= 0:
							break
						var t = a[r]
						a[r] = a[q]
						a[q] = t
						q -= gap
					p += gap
				gap -= 2
		elif n >= 16:
			var m := b + (n >> 1)
			if n > 0x1d:
				var lo := b
				var hi := b + n - 1
				if n > 0x2a:
					var d := n >> 3
					lo = _med3(a, b, b + d, b + 2 * d, cmp)
					m = _med3(a, m - d, m, m + d, cmp)
					hi = _med3(a, hi - 2 * d, hi - d, hi, cmp)
				m = _med3(a, lo, m, hi, cmp)
			var pv = a[m]
			var pa := b
			var pb := b
			var pc := b + n - 1
			var pd := pc
			while true:
				while pb <= pc:
					var r := int(cmp.call(a[pb], pv))
					if r > 0:
						break
					if r == 0:
						_swap(a, pa, pb)
						pa += 1
					pb += 1
				while pb <= pc:
					var r := int(cmp.call(a[pc], pv))
					if r < 0:
						break
					if r == 0:
						_swap(a, pc, pd)
						pd -= 1
					pc -= 1
				if pb > pc:
					break
				_swap(a, pb, pc)
				pb += 1
				pc -= 1
			var pn := b + n
			var s := mini(pa - b, pb - pa)
			_vecswap(a, b, pb - s, s)
			s = mini(pd - pc, pn - pd - 1)
			_vecswap(a, pb, pn - s, s)
			var r_size := pd - pc
			var l_size := pb - pa
			if r_size >= l_size:
				stack_base.append(pn - r_size)
				stack_n.append(r_size)
				n = l_size
				continue
			if l_size > 1:
				stack_base.append(b)
				stack_n.append(l_size)
				n = r_size
				b = pn - r_size
				continue
		if stack_n.is_empty():
			return
		b = stack_base.pop_back()
		n = stack_n.pop_back()

## __qsort_med3: the median of three elements (by index)
static func _med3(a: Array, x: int, y: int, z: int, cmp: Callable) -> int:
	if int(cmp.call(a[x], a[y])) > 0:
		if int(cmp.call(a[x], a[z])) <= 0:
			return x
		return y if int(cmp.call(a[y], a[z])) > 0 else z
	if int(cmp.call(a[x], a[z])) >= 0:
		return x
	return z if int(cmp.call(a[y], a[z])) > 0 else y

static func _swap(a: Array, i: int, j: int) -> void:
	var t = a[i]
	a[i] = a[j]
	a[j] = t

## the byte swap of two ranges of the same length
static func _vecswap(a: Array, i: int, j: int, count: int) -> void:
	for k in count:
		_swap(a, i + k, j + k)
