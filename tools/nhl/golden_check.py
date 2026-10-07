#!/usr/bin/env python3
#
# golden_check.py A B: the golden data in directory A is the same as in B (the contents of the
# .json and .json.gz files; the compressed bytes may differ between zlib versions)
#
import gzip
import os
import sys


def contents(d):
    out = {}
    for n in sorted(os.listdir(d)):
        p = os.path.join(d, n)
        if n.endswith('.json.gz'):
            with gzip.open(p, 'rb') as f:
                out[n[:-3]] = f.read()
        elif n.endswith('.json'):
            with open(p, 'rb') as f:
                out[n] = f.read()
    return out


def main():
    a, b = contents(sys.argv[1]), contents(sys.argv[2])
    bad = sorted(n for n in set(a) | set(b) if a.get(n) != b.get(n))
    for n in bad:
        print('differs:', n)
    print('golden data', 'differs' if bad else 'is the same', '(%d files)' % len(set(a) | set(b)))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
