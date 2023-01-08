from timeit import default_timer as timer

def  main1(filename):
    wrs = {}
    mask = 2 ** 16 - 1
    with open(filename, "r") as f:
        lines = [l.strip() for l in f]

    for line in lines:
        elms = line.split(' -> ')
        wrs[elms[1]] = elms[0]

    def dfs(wr):
        if type(wrs[wr]) == int:
            return wrs[wr]

        elms = wrs[wr].split()

        res = 0
        if len(elms) == 1:
            if elms[0].isdigit():
                res = int(elms[0])
            else:
                res = dfs(elms[0])

        if len(elms) == 2:
            res = ~dfs(elms[1]) & mask

        if len(elms) == 3:
            if elms[1] == 'AND':
                if elms[0].isdigit():
                    res = (int(elms[0]) & dfs(elms[2])) & mask
                else:
                    res = (dfs(elms[0]) & dfs(elms[2])) & mask
            if elms[1] == 'OR':
                res = (dfs(elms[0]) | dfs(elms[2])) & mask
            if elms[1] == 'LSHIFT':
                res = (dfs(elms[0]) << int(elms[2])) & mask
            if elms[1] == 'RSHIFT':
                res = (dfs(elms[0]) >> int(elms[2])) & mask

        wrs[wr] = res
        return res

    return str(dfs('a')) 


def  main2(filename):
    wrs = {}
    mask = 2 ** 16 - 1
    with open(filename, "r") as f:
        lines = [l.strip() for l in f]

    for line in lines:
        elms = line.split(' -> ')
        wrs[elms[1]] = elms[0]

    wrs['b'] = '46065'
    def dfs(wr):
        if type(wrs[wr]) == int:
            return wrs[wr]

        elms = wrs[wr].split()

        res = 0
        if len(elms) == 1:
            if elms[0].isdigit():
                res = int(elms[0])
            else:
                res = dfs(elms[0])

        if len(elms) == 2:
            res = ~dfs(elms[1]) & mask

        if len(elms) == 3:
            if elms[1] == 'AND':
                if elms[0].isdigit():
                    res = (int(elms[0]) & dfs(elms[2])) & mask
                else:
                    res = (dfs(elms[0]) & dfs(elms[2])) & mask
            if elms[1] == 'OR':
                res = (dfs(elms[0]) | dfs(elms[2])) & mask
            if elms[1] == 'LSHIFT':
                res = (dfs(elms[0]) << int(elms[2])) & mask
            if elms[1] == 'RSHIFT':
                res = (dfs(elms[0]) >> int(elms[2])) & mask

        wrs[wr] = res
        return res

    return str(dfs('a')) 


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
