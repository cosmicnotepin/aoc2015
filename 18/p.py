from timeit import default_timer as timer
from collections import defaultdict

def main1(filename):

    mp = defaultdict(lambda:'.')
    with open(filename, "r") as f:
        for y, line in enumerate(f):
            for x, c in enumerate(line.strip()):
                mp[complex(y,x)] = c

    neigh_offs = [complex(y,x) for y in range(-1,2) for x in range(-1,2) \
            if not (x==0 and y==0)]
    corners = [0+0j,0+99j,99+0j,99+99j]
    for c in corners:
        mp[c] = '#'

    for _ in range(100):
        swapper = defaultdict(lambda:'.')
        for key,value in list(mp.items()):
            n_cnt = sum(mp[n]=='#' for n in (key + no for no in neigh_offs))
            if value == '#' and 2<=n_cnt<=3 or value=='.' and n_cnt==3 or \
                    key in corners:
                swapper[key] = '#'
            else:
                swapper[key] = '.'
        mp = swapper.copy()

    return str(sum([c=='#' for c in mp.values()])) 


def main2(filename):
    with open(filename, "r") as f:
        line = f.read()

    return ""


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
