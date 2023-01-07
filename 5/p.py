from timeit import default_timer as timer

def  main1(filename):
    res = 0
    vowels = 'aeiou'
    forb = ('ab', 'cd', 'pq', 'xy')
    with open(filename, "r") as f:
        for line in f:
            vow_cnt = 0;
            for v in vowels:
                    vow_cnt += line.count(v) 
            if vow_cnt < 3:
                continue

            for fb in forb:
                if fb in line:
                    break
            else:
                for a,b in zip(line[1:], line):
                    if a==b:
                        res += 1
                        break

    return str(res)


def  main2(filename):
    res = 0
    with open(filename, "r") as f:
        for line in f:
            for a,b in zip(line, line[1:]):
                if line.count(a+b) >= 2: 
                    break
            else:
                continue

            for a,b in zip(line[2:], line):
                if a == b:
                    break
            else:
                continue
            res += 1

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
