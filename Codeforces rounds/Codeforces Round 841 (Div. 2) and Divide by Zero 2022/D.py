# https://codeforces.com/contest/1731/problem/D

from typing import Callable, List, TypeVar

def has_for_l(ass: List[List[int]], l: int) -> bool:
    n: int = len(ass)
    m: int = len(ass[0])

    B: List[List[bool]] = [[a >= l for a in As] for As in ass]

    prefixes_B = [[0 for _ in range(m+1)] for _ in range(n+1)]

    for i in range(n):
        for j in range(m):
            prefixes_B[i+1][j+1] = prefixes_B[i][j+1] + prefixes_B[i+1][j] - prefixes_B[i][j] + B[i][j]

    for i in range(n-l+1):
        for j in range(m-l+1):
            if prefixes_B[i+l][j+l] - prefixes_B[i][j+l] - prefixes_B[i+l][j] + prefixes_B[i][j] == l*l:
                return True

    return False

T = TypeVar('T')
def binary_search(f: Callable[[T], bool], it: List[T]) -> int:
    lower: int = 0
    upper: int = len(it)
    while lower + 1 < upper:
        m: int = (lower + upper) // 2
        if f(it[m]):
            lower = m
        else:
            upper = m
    return lower


def solve1(ass: List[List[int]]) -> int:
    n: int = len(ass)
    m: int = len(ass[0])

    max_l: int = min(n, m)

    res: int = binary_search(lambda l: has_for_l(ass, l), list(range(1, max_l+1)))
    return res + 1

def parse1() -> List[List[int]]:
    n, _ = map(int, input().split())
    return [list(map(int, input().split())) for _ in range(n)]

def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
