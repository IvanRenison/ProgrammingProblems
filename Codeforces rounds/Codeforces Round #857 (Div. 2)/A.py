# https://codeforces.com/contest/1802/problem/A

from typing import List, Tuple


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))

def solve1(bs: List[int]) -> Tuple[List[int], List[int]]:
    n: int = len(bs)

    positives: int = 0
    negatives: int = 0
    for b in bs:
        if b > 0:
            positives += 1
        else:
            negatives += 1

    total: int = positives - negatives

    maximums: List[int] = list(range(1, positives + 1)) + list(range(positives - 1, total - 1, -1))
    minimums: List[int] = [1, 0] * ((n-total)//2) + list(range(1, total + 1))

    return maximums, minimums

def main():
    t: int = int(input())
    for _ in range(t):
        res = solve1(parse1())
        print(*res[0], sep=' ')
        print(*res[1], sep=' ')


if __name__ == '__main__':
    main()
