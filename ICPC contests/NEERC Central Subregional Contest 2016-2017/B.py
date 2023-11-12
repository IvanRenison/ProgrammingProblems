# https://codeforces.com/gym/101243

from typing import Tuple
import sys

sys.stdin = open("input.txt", "r")
sys.stdout = open("output.txt", "w")


N = int(input())
assert(N % 3 == 0)
cants = [N, 0, 0]


# for i in {3..300..3}; do echo $i; echo $i | python3 B.py; done


def other(i: int, j: int) -> int:
    if min(i, j) == 0 and max(i, j) == 1:
        return 2
    if min(i, j) == 1 and max(i, j) == 2:
        return 0
    if min(i, j) == 0 and max(i, j) == 2:
        return 1


def rec(x: int, fro: int, to: int) -> Tuple[bool, int]:
    if x == 1:
        cants[fro] -= 1
        cants[to] += 1
        return cants[0] == cants[1] == cants[2], 1


    if (cants[fro] < N/3 or cants[fro] - x > N/3 or cants[to] > N/3 or cants[to] + x < N/3):
        cants[fro] -= x
        cants[to] += x
        return False, 2**x - 1

    b, r = rec(x-1, fro, other(fro, to))

    if b:
        return True, r

    if cants[0] == cants[1] == cants[2]:
        return True, r

    cants[fro] -= 1
    cants[to] += 1
    r += 1

    if cants[0] == cants[1] == cants[2]:
        return True, r

    b2, r2 = rec(x-1, other(fro, to), to)

    return b2, r + r2


print(rec(N,0,1)[1])
