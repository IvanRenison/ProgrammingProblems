# https://codeforces.com/contest/1795/problem/B

from typing import List, Tuple


def parse1() -> Tuple[int, List[Tuple[int, int]]]:
    n, k = map(int, input().split())
    lrs = [tuple(map(int, input().split())) for _ in range(n)]
    return k, lrs


def solve1(k: int, lrs: List[Tuple[int, int]]) -> bool:
    lrs_filter = [(l, r) for (l, r) in lrs if l <= k <= r]
    return len([1 for (l, r) in lrs_filter if l == k]) and len([1 for (l, r) in lrs_filter if r == k])


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print('YES')
        else:
            print('NO')


if __name__ == '__main__':
    main()
