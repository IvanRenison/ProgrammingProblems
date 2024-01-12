# https://codeforces.com/contest/1775/problem/C

from math import floor, log2
from typing import Optional


def solve1(n: int, x: int) -> Optional[int]:
    if x & n != x:
        return None

    ans: int = n
    passed_x_on: bool = False
    for i in range(floor(log2(n + 1)) + 1):
        if n & (1 << i) != x & (1 << i):
            if passed_x_on:
                return None
            m: int = n
            for j in range(i + 1):
                m &= ~(1 << j)
            for j in range(i + 1, floor(log2(n + 1)) + 2):
                if m & (1 << j) == 0:
                    ans = m | (1 << j)
                    break
                elif x & (1 << j):
                    return None
                m ^= 1 << j
        if x & (1 << i):
            passed_x_on = True

    return ans

def main():
    t: int = int(input())
    for _ in range(t):
        n, x = map(int, input().split())

        ans: Optional[int] = solve1(n, x)
        if ans == None:
            print(-1)
        else:
            print(ans)


if __name__ == '__main__':
    main()
