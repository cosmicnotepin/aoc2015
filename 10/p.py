from timeit import default_timer as timer
from itertools import groupby

def main1(line):

    for _ in range(40):
        line = ''.join(str(len(list(lst))) + e for e, lst in groupby(line))

    return str(len(line))


def  main2(line):

    for _ in range(50):
        line = ''.join(str(len(list(lst))) + e for e, lst in groupby(line))

    return str(len(line))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('111', '1113222113'):
            start = timer()
            res = fun(str(inp))
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
