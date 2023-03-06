# https://codeforces.com/gym/101652

from math import floor, sqrt
from typing import Tuple


def parse() -> Tuple[int, int]:
    return tuple(map(int, input().split()))

def factorsum(x: int):
    res: int = 0
    for i in range(1, floor(sqrt(x)) + 1):
        if x % i == 0:
            res += i + x // i
    return res

def triangle(x: int, y: int) -> int:
    return y*(y+1)//2 - (x-1)*x//2

def solve(a: int, b: int) -> int:
    res: int = 0
    m: int = floor(sqrt(b))

    for i in range(1, m + 1):
        res += i * (b // i - (a - 1) // i) + triangle(max(m, (a-1)//i)+1, b//i)

    return res

def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
