# https://codeforces.com/contest/1728/problem/B

from typing import List


def parse1() -> int:
    return int(input())


def value(ps: List[int]) -> int:
    x: int = 0
    for p in ps:
        if x < p:
            x += p
        else:
            x = 0
    return x


def solve1(n: int) -> List[int]:
    ps: List[int] = [i for i in range(1, n + 1)]
    if n % 3 != 2:
        ps[0], ps[-3] = ps[-3], ps[0]

    return ps


def main():
    t: int = int(input())
    for _ in range(t):
        ps: List[int] = solve1(parse1())
        print(*ps, sep=' ')


if __name__ == '__main__':
    main()
