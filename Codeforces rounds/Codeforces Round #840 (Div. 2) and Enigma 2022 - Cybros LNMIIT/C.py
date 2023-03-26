# https://codeforces.com/contest/1763/problem/C

from typing import List


def solve1(As: List[int]) -> int:
    n: int = len(As)
    if n == 2:
        maxa: int = max(As)
        mina: int = min(As)

        return max(maxa + mina, 2 * (maxa - mina))
    elif n == 3:
        a0: int = As[0]
        a1: int = As[1]
        a2: int = As[2]

        return max(
            a0 + a1 + a2,
            3 * abs(a0 - a1),
            3 * abs(a1 - a2),
            3 * abs(a0 - a2),
            3 * a0,
            3 * a2
        )
    else:
        max_a: int = max(As)
        return n * max_a

def parse1() -> List[int]:
    _ = input()
    return list(map(int, input().split()))

def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
