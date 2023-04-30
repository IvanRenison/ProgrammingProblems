# https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/C

from typing import Tuple


def parse1() -> Tuple[int, int]:
    return map(int, input().split())


def solve1(h: int, m: int):
    return (24 - h) * 60 - (m)


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(*parse1()))


if __name__ == '__main__':
    main()
