# https://codeforces.com/contest/1761/problem/B

from collections import defaultdict
from typing import DefaultDict, Dict, List

def delete_from_dict(d: Dict[int, int], k: int):
    d[k] -= 1
    if d[k] == 0:
        d.pop(k)

def solve1(As: List[int]) -> int:

    n: int = len(As)
    res: int = 0
    numbers_amounts: DefaultDict[int, int] = defaultdict(int)
    for a in As:
        numbers_amounts[a] += 1

    while n > 1:

        index_to_delete: int | None = None
        for i in range(n):
            value = As[i]
            if As[i-1] != As[(i+1) % n] and (numbers_amounts[value] > 1 or len(numbers_amounts) > 3):
                index_to_delete = i
                As.pop(index_to_delete)
                n -= 1
                res += 1
                delete_from_dict(numbers_amounts, value)
                break

        if index_to_delete is None:
            for i in range(n):
                if As[i-1] != As[(i+1) % n]:
                    index_to_delete = i
                    value: int = As.pop(index_to_delete)
                    n -= 1
                    res += 1
                    delete_from_dict(numbers_amounts, value)
                    break

        if index_to_delete is None:
            # index_to_delete = 0
            value: int = As.pop(0)
            n -= 1
            res += 1
            delete_from_dict(numbers_amounts, value)

            if n > 1 and As[0] == As[-1]:
                value = As.pop()
                n -= 1
                delete_from_dict(numbers_amounts, value)

    return res + 1





def parse1() -> List[int]:
    _ = input()
    return list(map(int, input().split()))


def main():
    t = int(input())
    for _ in range(t):
        a = parse1()
        res: int = solve1(a)
        print(res)


if __name__ == '__main__':
    main()
