# https://open.kattis.com/problems/pivot

from typing import List


def parse() -> List[int]:
    input()
    return list(map(int, input().split()))


def solve(As: List[int]) -> int:
    n: int = len(As)
    maxs: List[int] = [0 for _ in range(n)]
    mins: List[int] = [0 for _ in range(n)]

    maxs[0] = As[0]
    for i in range(1, n):
        maxs[i] = max(maxs[i - 1], As[i])

    mins[n - 1] = As[n - 1]
    for i in range(n - 2, -1, -1):
        mins[i] = min(mins[i + 1], As[i])

    count: int = 0
    for i in range(n):
        if maxs[i] <= As[i] and As[i] <= mins[i]:
            count += 1

    return count


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
