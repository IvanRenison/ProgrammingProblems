# https://open.kattis.com/problems/epigdanceoff

from typing import List, Literal


GridElement = Literal['$', '_']
Grid = List[List[GridElement]]


def parse() -> Grid:
    N, _ = map(int, input().split())
    return [list(input()) for _ in range(N)]


def solve(grid: Grid) -> int:
    N: int = len(grid)
    M: int = len(grid[0])

    return sum(
        1 for j in range(M) if all([grid[i][j] == '_' for i in range(N)])
    ) + 1


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
