# https://codeforces.com/contest/1794/problem/B

from typing import List


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))

def solve1(As: List[int]) -> List[int]:
    n: int = len(As)
    if As[0] == 1:
        As[0] = 2
    for i in range(1, n):
        if As[i] % As[i-1] == 0:
            As[i] += 1
        elif As[i] == 1 and As[i-1] == 2:
            As[i] = 3
        elif As[i] == 1:
            As[i] = 2

    return As


def main():
    t: int = int(input())
    for _ in range(t):
        print(*solve1(parse1()), sep=' ')


if __name__ == '__main__':
    main()
