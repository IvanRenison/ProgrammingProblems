# https://codeforces.com/contest/1794/problem/C

import re
from typing import List


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))

def solve1(As: List[int]) -> List[int]:
    n: int = len(As)
    res: List[int] = [0] * n

    res[0] = 1
    for i in range(1, n):
        if As[i - res[i-1]] >= res[i-1] + 1:
            res[i] = res[i-1] + 1
        else:
            res[i] = res[i-1]

    return res

def main():
    t: int = int(input())
    for _ in range(t):
        print(*solve1(parse1()), sep=' ')


if __name__ == '__main__':
    main()
