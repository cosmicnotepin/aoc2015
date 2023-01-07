from timeit import default_timer as timer

def  main1(filename):
    dir2move = {'v': 1j, '<': -1, '>': 1, '^': -1j};
    visited = set()
    pos = 0 + 0j
    visited.add(pos)
    with open(filename, "r") as f:
        line = f.read()
    
    for c in line.strip():
        pos += dir2move[c]
        visited.add(pos)

    return str(len(visited))


def  main2(filename):
    dir2move = {'v': 1j, '<': -1, '>': 1, '^': -1j};
    visited = set()
    pos = [0j, 0j]
    visited.add(pos[0])
    with open(filename, "r") as f:
        line = f.read()
    
    i = 0
    for c in line.strip():
        pos[i] += dir2move[c]
        visited.add(pos[i])
        i = (i+1)%2

    return str(len(visited))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
