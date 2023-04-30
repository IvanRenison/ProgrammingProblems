# https://codeforces.com/contest/1795/problem/D

from math import factorial
from typing import List, Tuple


def parse() -> List[Tuple[int, int, int]]:
    n = int(input())
    xs: List[int] = list(map(int, input().split()))

    ws: List[Tuple[int, int, int]] = []
    for i in range(n // 3):
        ws.append((xs[3 * i], xs[3 * i + 1], xs[3 * i + 2]))

    return ws


def solve(ws: List[Tuple[int, int, int]]) -> int:

    n_: int = len(ws)

    res: int = factorial(n_) // (factorial(n_ // 2) ** 2)

    for w in ws:
        wi, wj, wk = w
        if wi == wj == wk:
            res = (res * 3) % 998244353
        elif (wi == wj and wk > wi) or (wi == wk and wj > wi) or (wj == wk and wi > wj):
            res = (res * 2) % 998244353

    return res


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
