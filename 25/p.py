from timeit import default_timer as timer

def count(j,i):
    #return 1 + sum(x for x in range(1,j)) + sum(x for x in range(j+1, j+1+(i-1)))
    return 1 + sum(x for x in range(1, j+i)) - j

def main1(filename):
    code = 20151125
    for _ in range(1, count(3010, 3019)):
        code = (code*252533) % 33554393

    return str(code)


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
