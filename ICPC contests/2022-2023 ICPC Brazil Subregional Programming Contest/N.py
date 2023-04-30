# https://codeforces.com/gym/103960/problem/N


from heapq import nlargest
from typing import List, Tuple


def solve(As: List[int], Bs: List[int], K: int, L: int) -> int:
    N: int = len(As)
    highest_score_possible: int = 0

    for i in range(K+1):
        # Peak the 0..i-1 and K-i..K-1 cards

        score: int = 0
        for j in range(i):
            score += As[j]
        for j in range(N-(K-i), N):
            score += As[j]

        peaked_Bs: List[int] = Bs[:i] + Bs[N-(K-i):]

        # Get L highest cards from peaked_Bs
        highest: List[int] = nlargest(L, peaked_Bs)

        for x in highest:
            score += x

        highest_score_possible = max(highest_score_possible, score)

    return highest_score_possible


def parse() -> Tuple[List[int], List[int], int, int]:
    _: int = int(input())
    As: List[int] = list(map(int, input().split()))
    Bs: List[int] = list(map(int, input().split()))

    K, L = map(int, input().split())

    return As, Bs, K, L


def main():
    As, Bs, K, L = parse()
    print(solve(As, Bs, K, L))


if __name__ == '__main__':
    main()
