# https://codeforces.com/gym/103388/problem/C

from typing import List, Tuple


def solve(B: int, Ds: List[int]) -> Tuple[int, int]:
    L = len(Ds)
    number: int = 0
    for j, d in enumerate(Ds):
        number += d * B ** (L - 1 - j)

    rem: int = number % (B+1)

    if rem == 0:
        return 0, 0

    for j, d in enumerate(Ds):
        i = L - 1 - j
        if i % 2 == 0:
            new_d: int = d - rem
            if new_d >= 0:
                return j+1, new_d
        else:
            new_d: int = d - (B + 1 - rem)
            if new_d >= 0:
                return j+1, new_d

    return -1, -1


def parse() -> Tuple[int, List[int]]:
    B, _ = map(int, input().split())
    Ds = list(map(int, input().split()))
    return B, Ds


def main():
    B, Ds = parse()
    i, d = solve(B, Ds)
    print(i, d)


if __name__ == '__main__':
    main()
