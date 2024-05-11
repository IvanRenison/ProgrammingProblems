# https://open.kattis.com/problems/divideby100

from typing import List, Literal, Tuple

Digit = Literal['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']


def parse() -> Tuple[List[Digit], List[Digit]]:
    N: List[Digit] = list(input())
    M: List[Digit] = list(input())
    return N, M


def solve(N: List[Digit], M: List[Digit]) -> Tuple[List[Digit], List[Digit]]:
    K: int = len(M) - 1
    n: int = len(N)
    Hole: List[Digit] = N[:-K]
    Dot: List[Digit] = N[-K:]
    if K > n:
        Dot = ['0'] * (K - n) + Dot

    ending_ceros: int = 0
    for d in reversed(Dot):
        if d == '0':
            ending_ceros += 1
        else:
            break

    if ending_ceros > 0:
        Dot = Dot[:-ending_ceros]

    return Hole, Dot


def main():
    hole, dot = solve(*parse())
    if len(hole) > 0:
        print(*hole, sep='', end='')
    else:
        print(0, end='')
    if len(dot) > 0:
        print('.', *dot, sep='', end='')
    print()


if __name__ == '__main__':
    main()
