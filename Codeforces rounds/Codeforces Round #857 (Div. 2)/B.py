# https://codeforces.com/contest/1802/problem/B

from typing import List, Literal


def parse1() -> List[Literal[1, 2]]:
    input()
    return list(map(int, input().split()))


def solve1(bs: List[Literal[1, 2]]) -> int:
    aviarys_needed: int = 0
    aviarys_used: int = 0
    guinea_pigs: int = 0

    for b in bs:
        if b == 1:
            guinea_pigs += 1
            if aviarys_used == aviarys_needed:
                aviarys_needed += 1
            aviarys_used += 1
        elif guinea_pigs > 0:
            aviarys_used = guinea_pigs // 2 + 1 if guinea_pigs % 2 == 0 else (guinea_pigs + 1) // 2

    return aviarys_needed


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
