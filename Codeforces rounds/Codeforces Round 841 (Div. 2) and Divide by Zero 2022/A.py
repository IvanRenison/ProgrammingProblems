# https://codeforces.com/contest/1731/problem/0

from math import prod
from typing import List


def solve1(As: List[int]) -> int:
    return (prod(As) + (len(As) - 1)) * 2022

def parse1() -> List[int]:
    input()
    As: List[int] = list(map(int, input().split()))
    return As

def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
