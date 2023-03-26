# https://codeforces.com/contest/1794/problem/A

from typing import List, Tuple


def parse1() -> Tuple[int, List[str]]:
    n: int = int(input())
    return n, list(input().split())


def solve1(n: int, ss: List[str]) -> bool:
    middles: List[str] = [s for s in ss if len(s) == (n+1)//2]
    return list(middles[0]) == list(reversed(middles[1]))


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print('YES')
        else:
            print('NO')


if __name__ == '__main__':
    main()
