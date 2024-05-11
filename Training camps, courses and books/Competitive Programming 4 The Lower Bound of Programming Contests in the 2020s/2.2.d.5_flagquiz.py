# https://open.kattis.com/problems/flagquiz

from typing import List


def parse() -> List[List[str]]:
    input()
    N: int = int(input())
    return [list(input().split(', ')) for _ in range(N)]


def incongruousity(a1: List[str], a2: List[str]) -> int:
    n: int = len(a1)
    return sum(1 for i in range(n) if a1[i] != a2[i])


def solve(alternatives: List[List[str]]) -> List[int]:
    N: int = len(alternatives)
    incongruousitys: List[List[int]] = [[0] * N for _ in range(N)]
    for i in range(N):
        for j in range(i):
            incongruousitys[i][j] = incongruousity(
                alternatives[i], alternatives[j])
            incongruousitys[j][i] = incongruousitys[i][j]

    incongruousitys_1D: List[int] = [max(i) for i in incongruousitys]

    min_incongruousity = min(incongruousitys_1D)

    return [i for i in range(N) if incongruousitys_1D[i] == min_incongruousity]


def main():
    alternatives: List[List[str]] = parse()
    ans: List[int] = solve(alternatives)
    for i in ans:
        print(*alternatives[i], sep=', ')


if __name__ == '__main__':
    main()
