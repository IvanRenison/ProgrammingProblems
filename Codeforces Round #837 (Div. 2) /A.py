# https://codeforces.com/contest/1771/problem/A

from typing import List


def solve1(As: List[int]) -> int:
    maxa = max(As)
    mina = min(As)

    if maxa == mina:
        n = len(As)
        return n * (n - 1)

    # count amount of element equal to maxa ans mina
    cnt_max = 0
    cnt_min = 0
    for a in As:
        if a == maxa:
            cnt_max += 1
        if a == mina:
            cnt_min += 1

    return 2 * cnt_max * cnt_min

def parse1() -> List[int]:
    _ = input()
    return [int(x) for x in input().split()]

def main():
    t = int(input())
    for _ in range(t):
        print(solve1(parse1()))
    pass


if __name__ == '__main__':
    main()
