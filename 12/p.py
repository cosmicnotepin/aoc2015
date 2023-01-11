from timeit import default_timer as timer
import re
from json import loads

def  main1(filename):
    pat = re.compile(r'-?\d+')
    with open(filename, "r") as f:
        line = f.read()

    return str(sum(int(x) for x in pat.findall(line)))


def dfs(v):
    if type(v) == int:
        return v
    if type(v) == dict:
        if "red" in v.keys() or "red" in v.values():
            return 0
        return sum(dfs(e) for e in v.values())
    if type(v) == list:
        return sum(dfs(e) for e in v)
    return 0


def  main2(filename):
    with open(filename, "r") as f:
        line = f.read()

    return str(dfs(loads(line)))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
