# https://codeforces.com/contest/1762/problem/A

from typing import List


def divs_needed(a: int) -> int:
    actual_sign: int = a & 1
    pos: int = 0
    while a & (1 << pos) == (actual_sign << pos):
        pos += 1
    return pos


def solve1(aa: List[int]) -> int:
    sum_aa: int = sum(aa)
    if sum_aa % 2 == 0:
        return 0
    else:
        return min(map(divs_needed, aa))


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
