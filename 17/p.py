from timeit import default_timer as timer
from itertools import combinations, chain

def count_combinations(container_sizes, target_sum):
    dp = [1] + [0]*(target_sum)
    for cur_num in container_sizes:
        for next_num in range(target_sum, cur_num-1, -1):
            dp[next_num] += dp[next_num - cur_num]
    return dp[target_sum]

def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

def main1(filename):
    with open(filename, "r") as f:
        cntnr = [int(n) for n in f.read().split()]
        
    eggnog = 150
    if len(cntnr) == 5:
        eggnog = 25

    #return str(sum(map(lambda l: sum(l) == eggnog, powerset(cntnr))))
    return str(count_combinations(cntnr, eggnog))

def main1_old(filename):
    with open(filename, "r") as f:
        cntnr = [int(n) for n in f.read().split()]
        
    eggnog = 150
    if len(cntnr) == 5:
        eggnog = 25

    #return str(sum(map(lambda l: sum(l) == eggnog, powerset(cntnr))))
    return str(sum([1 for ss in powerset(cntnr) if sum(ss) == eggnog]))

def main2(filename):
    with open(filename, "r") as f:
        cntnr = [int(n) for n in f.read().split()]
        
    eggnog = 150
    if len(cntnr) == 5:
        eggnog = 25

    minlen = min(len(l) for l in powerset(cntnr) if sum(l) == eggnog)
    return str(sum([1 for ss in combinations(cntnr, minlen) if sum(ss) == eggnog]))
    #def pred(l):
    #    if sum(l) == eggnog:
    #        return len(l)
    #    else:
    #        return len(cntnr) + 1
    #    
    #minlen = min(map(pred, powerset(cntnr)))
    #return str(sum( \
    #        map(lambda l: sum(l) == eggnog, combinations(cntnr, minlen))))


if __name__ == "__main__":
    for p,fun in zip(('p1: ', 'p2: '),(main1,main2)):
        print(p)
        for inp in ('tinput', 'input'):
            start = timer()
            res = fun(inp)
            end = timer()
            print(inp + ': ' + res)
            print("time: " + f'{end - start:3.6f}')
