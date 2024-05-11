# https://open.kattis.com/problems/baloni

from typing import List


def parse() -> List[int]:
    input()
    return [int(H) for H in input().split()]


def solve(Hs: List[int]) -> int:
    N: int = len(Hs)

    amount_arrows: List[int] = [0 for _ in range(0, max(Hs) + 1)]
    for H in Hs:
        if amount_arrows[H] >= 1:
            amount_arrows[H] -= 1
            amount_arrows[H-1] += 1
        else:
            amount_arrows[H-1] += 1

    return sum(amount_arrows)


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
