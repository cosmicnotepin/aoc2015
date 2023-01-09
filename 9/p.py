from timeit import default_timer as timer
from collections import defaultdict
from itertools import permutations

def  main1(filename):
    dists = defaultdict(dict)
    with open(filename, "r") as f:
        for line in f:
            fr, to, d  = line.split()[::2]
            dists[fr][to] = int(d)
            dists[to][fr] = int(d)

    res = 999999999
    for p in permutations(dists.keys()):
        res = min(res, sum(dists[f][t] for f,t in zip(p, p[1:])))

    return str(res)


def  main2(filename):
    dists = defaultdict(dict)
    with open(filename, "r") as f:
        for line in f:
            fr, _, to, _, d  = line.split()
            dists[fr][to] = int(d)
            dists[to][fr] = int(d)

    for dest in [*(dists.keys())]:
        dists["start"][dest] = 0

    def dfs(pos, visited):
        mn = 0
        for dest in dists["start"].keys():
            if dest in visited:
                continue
            mn = max(mn, dfs(dest, visited | set([dest])) + dists[pos][dest])
        return mn


    visited = set()
    return str(dfs("start", visited))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
