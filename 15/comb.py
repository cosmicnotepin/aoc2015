print('blah')
#import re
#import itertools
#
#def  main2(filename):
#    pat = re.compile('-?\d+')
#    spoons = 100
#    ill = []
#    with open(filename, "r") as f:
#        smth = { name: {attr: int(val) for attr, val in map(str.split, values.split(","))} for name, values in map(lambda l: l.split(":"), f.read().splitlines()) }
#
#    #print(f'smth : {smth }')
#
#    wtf = [c for c in itertools.combinations(range(spoons + len(smth) - 1), len(smth) - 1)]
#    print(f'(-1,) + wtf[0]: {(-1,) + wtf[0]}')
#    print(f'wtf[0] + (spoons + len(smth) - 1,): {wtf[0] + (spoons + len(smth) - 1,)}')
#    wtf2 = [ (a,b) for a,b in zip((-1,) + wtf[0], wtf[0] + (spoons + len(smth) - 1,))][:5]
#    print(f'wtf2 : {wtf2 }')
#    bleh = lambda ingredients: ({ i: b - a - 1 \
#            for i, a, b in \
#            zip(ingredients, (-1,) + c, c + (spoons + len(ingredients) - 1,)) } \
#            for c in itertools.combinations(range(spoons + len(ingredients) - 1), len(ingredients) - 1))
#
#    blah = bleh(smth)
#    print(next(blah))
#    print(next(blah))
#    print(next(blah))

def product(*args, repeat=1):
    print('wtf')
    # product('ABCD', 'xy') --> Ax Ay Bx By Cx Cy Dx Dy
    # product(range(2), repeat=3) --> 000 001 010 011 100 101 110 111
    pools = [tuple(pool) for pool in args] * repeat
    print(f'pools : {pools }')
    result = [[]]
    for pool in pools:
        result = [x+[y] for x in result for y in pool]
        print(f'result : {result }')
        input()
    for prod in result:
        yield tuple(prod)

b = product([1,2,3],[1,2,3])
next(b)
next(b)
next(b)
next(b)
next(b)
print('bleh')

#main2('input')

