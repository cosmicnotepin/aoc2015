from timeit import default_timer as timer
from collections import defaultdict
from itertools import permutations
import re

def  main1(filename):
    happy = defaultdict(dict)
    pat = re.compile(r'(?P<person>.+) would (?P<gainloose>.+) (?P<happy>\d+) happiness units by sitting next to (?P<neigh>.+).')
    with open(filename, "r") as f:
        for line in f:
            m = re.match(pat,line.strip())
            sign = 1 if m.group('gainloose') == 'gain' else -1
            happy[m.group('person')][m.group('neigh')] = \
                    sign * int(m.group('happy')) 

    mx = 0
    for perm in permutations(happy.keys()):
        mx = max(mx, sum(happy[p][n] + happy[n][p] for p,n in zip(perm, perm[1:] + perm[0:1])))

    return str(mx)


def  main2(filename):
    happy = defaultdict(dict)
    with open(filename, "r") as f:
        for line in f:
            dat = line.strip('.\n').split()
            sign = 1 if dat[2] == 'gain' else -1
            happy[dat[0]][dat[-1]] = sign * int(dat[3]) 

    for k in list(happy.keys()):
        happy['me'][k] = 0
        happy[k]['me'] = 0

    mmx = 0
    for perm in permutations(happy.keys()):
        mmx = max(mmx, sum(happy[p][n] + happy[n][p] for p,n in zip(perm, perm[1:] + perm[0:1])))

    return str(mmx)

if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('input',):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
