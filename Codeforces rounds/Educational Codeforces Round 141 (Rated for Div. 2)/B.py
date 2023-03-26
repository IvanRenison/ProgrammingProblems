# https://codeforces.com/contest/1783/problem/B

from typing import List


def parse1() -> int:
    return int(input())

def solve1(n: int) -> List[List[int]]:
    xss: List[List[int]] = [[0] * n for _ in range(n)]

    def number_k(k: int) -> int:
        if k % 2 == 0:
            return n**2 - k // 2
        else:
            return (k + 1) // 2

    k: int = 0
    for i in range(n):
        for j in (range(n) if i % 2 == 0 else range(n - 1, -1, -1)):
            xss[i][j] = number_k(k)
            k += 1

    return xss

def main():
    t: int = int(input())
    for _ in range(t):
        xss = solve1(parse1())
        for xs in xss:
            print(*xs, sep=' ')


if __name__ == '__main__':
    main()
