# https://codeforces.com/contest/1762/problem/B

from math import ceil, log2
from typing import List, Tuple


def solve1(aa: List[int]) -> List[Tuple[int, int]]:
    return [(i+1, 2**(ceil(log2(a)))-a) for i, a in enumerate(aa)]


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))


def main():
    t: int = int(input())
    for _ in range(t):
        res: List[Tuple[int, int]] = solve1(parse1())
        print(len(res))
        for a, b in res:
            print(a, b)


if __name__ == '__main__':
    main()
