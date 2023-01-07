from timeit import default_timer as timer

def  main1(filename):
    with open(filename, "r") as f:
        line = f.read()

    return str(line.count('(') - line.count(')'))

def  main2(filename):
    with open(filename, "r") as f:
        line = f.read()
    floor = 0
    for i, c in enumerate(line):
        if c == '(':
            floor += 1
        elif c == ')':
            floor -= 1
        if floor == -1:
            return str(i+1)


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
