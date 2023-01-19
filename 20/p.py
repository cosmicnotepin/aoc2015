from timeit import default_timer as timer
from itertools import combinations, chain
from functools import reduce
import sys
from operator import mul
from math import sqrt

def prime_factors(n):
    i = 2
    factors = []
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return set(chain.from_iterable(combinations(s, r) for r in range(1, len(s)+1)))

def presents_lazy(house):
    pfs = prime_factors(house)
    res = 10 
    for elf in powerset(pfs):
        real_elf = reduce(mul,elf)
        if real_elf * 50 < house:
            continue
        res +=  real_elf * 11
    return res

def divisors(n):
    small_d = [d for d in range(1, int(sqrt(n)) + 1) if n % d == 0]
    big_d = [int(n/d) for d in small_d if n != d*d]
    return small_d + big_d

def presents_direct(house):
    dvrs = divisors(house)
    pres = sum(d*10 for d in dvrs)
    return pres

def presents(house):
    pfs = prime_factors(house)
    res = 10 
    for elf in powerset(pfs):
        res += reduce(mul,elf) * 10
    return res

def main1(filename):
    min_pres = 29000000
    for house in range(1,int(sys.maxsize)):
        if sum(d*10 for d in divisors(house)) > min_pres:
            return str(house)
    return ""


def main2(filename):
    min_pres = 29000000
    for house in range(1,int(sys.maxsize)):
        if presents_lazy(house) > min_pres:
            return str(house)
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
