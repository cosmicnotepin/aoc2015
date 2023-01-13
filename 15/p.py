from timeit import default_timer as timer
import re
from functools import reduce
from itertools import combinations_with_replacement as cwr

def main1(filename):
    pat = re.compile('-?\d+')
    ill = []
    with open(filename, "r") as f:
        for line in f:
            ill.append([int(prop) for prop in pat.findall(line)])

    def score(partition, rest):
        if len(partition) == len(ill) - 1:
            part = partition + [rest]
            ill_mul_sps = [list(map(lambda x: p*x, il)) \
                    for il,p in zip(ill, part)]
            props = [sum(l) for l in zip(*ill_mul_sps)]
            total = reduce(lambda acc,v: acc * max(0,v), props[:-1])
            return total

        mx = 0
        for sps in range(rest + 1):
            mx = max(mx, score(partition + [sps], rest-sps))
        return mx


    return str(score([], 100))


def main2_old(filename):
    pat = re.compile('-?\d+')
    ill = []
    with open(filename, "r") as f:
        for line in f:
            ill.append([int(prop) for prop in pat.findall(line)])

    def score(partition, rest):
        if len(partition) == len(ill) - 1:
            part = partition + [rest]
            ill_mul_sps = [list(map(lambda x: p*x, il)) \
                    for il,p in zip(ill, part)]
            props = [sum(l) for l in zip(*ill_mul_sps)]
            if (props[-1] != 500):
                return 0;
            total = reduce(lambda acc,v: acc * max(0,v), props[:-1])
            return total

        mx = 0
        for sps in range(rest + 1):
            mx = max(mx, score(partition + [sps], rest-sps))
        return mx

    return str(score([], 100))

def main2(filename):
    pat = re.compile('-?\d+')
    ill = []
    with open(filename, "r") as f:
        for line in f:
            ill.append([int(prop) for prop in pat.findall(line)])

    spns = 100
    mx = 0
    for cmbn in cwr(range(spns+1), len(ill) - 1):
        part = (b-a for a,b in zip((0,) + cmbn, cmbn + (spns,)))
        ill_mul_sps = [[p*x for x in il] for il,p in zip(ill, part)]
        props = [sum(l) for l in zip(*ill_mul_sps)]
        total = reduce(lambda acc,v: acc * max(0,v), props[:-1])
        mx = max(mx, total)

    return str(mx)


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
