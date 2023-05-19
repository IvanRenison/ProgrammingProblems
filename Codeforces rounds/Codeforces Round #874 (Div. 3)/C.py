# https://codeforces.com/contest/1833/problem/C

from typing import List


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))


def solve1(As: List[int]) -> bool:
    n: int = len(As)
    even_amount: int = sum(1 for a in As if a % 2 == 0)
    odd_amount: int = n - even_amount
    if odd_amount > 0:
        min_odd: int = min(a for a in As if a % 2 == 1)

    # Can bs be of odds?
    can_be_odds: bool = True
    for i in range(n):
        if As[i] % 2 == 1:
            continue
        if odd_amount >= 1 and min_odd < As[i]:
            continue
        can_be_odds = False
        break

    if can_be_odds:
        return True

    # Can bs be of evens?
    can_be_evens: bool = True
    for i in range(n):
        if As[i] % 2 == 0:
            continue
        if odd_amount > 1 and min_odd < As[i]:
            continue
        can_be_evens = False
        break

    return can_be_evens


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
