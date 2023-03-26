# https://codeforces.com/contest/1728/problem/A

from typing import Dict, List


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))


def solve1(balls: List[int]) -> int:
    return balls.index(max(balls)) + 1


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
