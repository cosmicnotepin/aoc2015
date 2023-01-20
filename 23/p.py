from timeit import default_timer as timer

def main1(filename):
    with open(filename, "r") as f:
        program = []
        for line in f:
            if ',' in line:
                cmd, val, offs = line.split()
                val = val.strip(',')
            else:
                cmd, val = line.split()
                offs = None
            program.append([cmd, val, offs])

    regs = {'a': 1, 'b': 0}
    i = 0
    while i<len(program):
        cmd, val, offs = program[i]
        if cmd == 'hlf':
            regs[val] /= 2
        if cmd == 'tpl':
            regs[val] *= 3
        if cmd == 'inc':
            regs[val] += 1
        if cmd == 'jmp':
            i += int(val)
            continue
        if cmd == 'jie':
            if (regs[val] % 2) == 0 :
                i += int(offs)
                continue
        if cmd == 'jio':
            if (regs[val]) == 1 :
                i += int(offs)
                continue
        i+=1

    return str(regs['b']) 


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
