from timeit import default_timer as timer
import re

def  main1(filename):
    grd = [[0]*1000 for i in range(1000)]
    pat = re.compile('\d+')
    with open(filename, "r") as f:
        for line in f:
            xm, ym, xM, yM = [int(x) for x in pat.findall(line)]
            for x in range(xm, xM+1):
                for y in range(ym, yM+1):
                    if line[6] == ' ':
                        grd[y][x] = (grd[y][x] + 1) % 2
                    elif line[6] == 'f':
                        grd[y][x] = 0
                    elif line[6] == 'n':
                        grd[y][x] = 1

    return str(sum(sum(x) for x in grd))


def  main2(filename):
    grd = [[0]*1000 for i in range(1000)]
    pat = re.compile('\d+')
    with open(filename, "r") as f:
        for line in f:
            xm, ym, xM, yM = [int(x) for x in pat.findall(line)]
            for x in range(xm, xM+1):
                for y in range(ym, yM+1):
                    if line[6] == ' ':
                        grd[y][x] += 2
                    elif line[6] == 'f':
                        grd[y][x] = max(0, grd[y][x] - 1)
                    elif line[6] == 'n':
                        grd[y][x] += 1

    return str(sum(sum(x) for x in grd))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
