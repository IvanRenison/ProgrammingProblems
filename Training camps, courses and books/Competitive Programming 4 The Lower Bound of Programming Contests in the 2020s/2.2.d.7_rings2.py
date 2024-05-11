# https://open.kattis.com/problems/rings2

from typing import List, Literal, Set, Tuple


InChars = Literal['T', '.']


def parse() -> List[List[InChars]]:
    n, _ = map(int, input().split())
    return [list(input()) for _ in range(n)]


def solve(tree: List[List[InChars]]) -> List[List[int]]:
    n = len(tree)
    m = len(tree[0])

    def get_neighbors(i: int, j: int) -> Set[Tuple[int, int]]:
        return {(i + di, j + dj) for di, dj in ((-1, 0), (1, 0), (0, -1), (0, 1)) if 0 <= i + di < n and 0 <= j + dj < m}

    outlines = [[0 for _ in range(m)] for _ in range(n)]

    indexes: Set[Tuple[int, int]] = {(i, j) for i in range(
        n) for j in range(m) if tree[i][j] == 'T'}
    for i, j in indexes.copy():
        neighbors = get_neighbors(i, j)
        if len(neighbors) != 4:
            outlines[i][j] = 1
            indexes.remove((i, j))
            continue
        for ni, nj in neighbors:
            if tree[ni][nj] == '.':
                outlines[i][j] = 1
                indexes.remove((i, j))
                break

    ring: int = 2
    while len(indexes) > 0:
        for i, j in indexes.copy():
            for ni, nj in get_neighbors(i, j):
                if outlines[ni][nj] == ring - 1:
                    outlines[i][j] = ring
                    indexes.remove((i, j))
                    break
        ring += 1

    return outlines


def output(outlines: List[List[int]]):
    max_ring = max(max(row) for row in outlines)

    if max_ring < 10:
        def format(n: int) -> str:
            if n == 0:
                return ".."
            else:
                return f".{n}"
    else:
        def format(n: int) -> str:
            if n == 0:
                return "..."
            elif n < 10:
                return f"..{n}"
            else:
                return f".{n}"

    for row in outlines:
        print(*map(format, row), sep="")


def main():
    output(solve(parse()))


if __name__ == '__main__':
    main()
