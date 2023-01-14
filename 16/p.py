from timeit import default_timer as timer
import re

def  main1(filename):
    pat = re.compile(' (\S+?): (\d+)')
    sues = []
    with open(filename, "r") as f:
        for line in f:
            sues.append(set((feat,nr) for feat,nr in pat.findall(line)))

        for i,s in enumerate(sues[1:]):
            if s & sues[0] == s:
                return str(i+1)
    return ""


def  main2(filename):
    pat = re.compile(' (\S+?): (\d+)')
    sues = []
    with open(filename, "r") as f:
        for line in f:
            sues.append({feat : int(nr) for feat,nr in pat.findall(line)})

        for i,s in enumerate(sues[1:]):
            for key,value in s.items():
                if key in ('cats', 'trees'):
                    if sues[0][key] < value:
                        continue
                    else:
                        break
                if key in ('pomeranians', 'goldfish'):
                    if sues[0][key] > value:
                        continue
                    else:
                        break
                if sues[0][key] != value:
                    break
            else:
                return str(i+1)
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
