from timeit import default_timer as timer
from math import prod

def  main1(filename):
    res = 0
    with open(filename, "r") as f:
        for line in f:
            l, w, h = [int(x) for x in line.strip().split('x')]
            sides = [l*w, l*h, w*h]
            res += sum([2*x for x in sides]) + min(sides)

    return str(res) 


def  main2(filename):
    res = 0
    with open(filename, "r") as f:
        for line in f:
            s_lens = [int(x) for x in line.strip().split('x')]
            res += sum(2*x for x in sorted(s_lens)[:2]) + prod(s_lens)

    return str(res)


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
