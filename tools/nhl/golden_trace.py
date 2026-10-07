#!/usr/bin/env python3
'''golden_trace.py GROUP CASES SLOT OUT.json

A per step trace of the original for runs of the steps groups (GROUP: steps or runs), to find the
first step where the port departs from it in a long run: the whole golden generation runs again
(so the random cases are the same as in tests/golden) and for the listed cases (comma separated
indices) the record of entity SLOT, its previous position, the random seed and the puck carrier
are kept after every step. tests/run_tests.gd compares them step by step with
RUNS_TRACE=OUT.json RUNS_TRACE_SLOT=SLOT RUNS_TRACE_GROUP=GROUP AI_STATE=sim_steps.'''
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import golden  # noqa: E402


def main():
    if len(sys.argv) != 5:
        print(__doc__)
        sys.exit(1)
    group, cases, slot, out = sys.argv[1], {int(x) for x in sys.argv[2].split(',')}, int(sys.argv[3]), sys.argv[4]
    count = {'steps': 1000, 'runs': 150}[group]
    src = open(golden.__file__).read()
    a = src.index('def steps_cases(')
    b = src.index('\nCONTROL_PLAYER = ', a)
    fn = src[a:b]
    old = "            emu.call(SIM_TICK)\n"
    assert old in fn
    fn = fn.replace(old, old + (
        "            if count == TRACE['count'] and k in TRACE['cases']:\n"
        "                s_ = TRACE['slot']\n"
        "                case.setdefault('trace', []).append(dict(entity_fields(emu, s_),\n"
        "                    prev=list(struct.unpack('<iii', emu.read(ENTITIES + s_ * 0x80 + 0x74, 12))),\n"
        "                    seed=struct.unpack('<I', emu.read(SEED, 4))[0],\n"
        "                    carrier=struct.unpack('<b', emu.read(PUCK + 0x42, 1))[0]))\n"))
    golden.TRACE = {'count': count, 'cases': cases, 'slot': slot}
    exec(compile(fn, 'steps_cases (traced)', 'exec'), golden.__dict__)
    exe = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 're', 'nhl_hockey', 'HOCKEY.EXE')
    data = golden.ai_cases(exe)
    with open(out, 'w') as f:
        json.dump({str(i): data[group][i].get('trace', []) for i in sorted(cases)}, f)
    print('wrote', out)


if __name__ == '__main__':
    main()
