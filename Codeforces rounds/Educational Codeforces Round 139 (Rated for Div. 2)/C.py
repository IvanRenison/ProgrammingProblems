# https://codeforces.com/contest/1766/problem/C

from typing import List, Tuple


def solve_with_start(c: Tuple[str, str], row: int) -> bool:
    m: int = len(c[0])

    painted: Tuple[List[bool], List[bool]] = ([False] * m, [False] * m)
    col: int = 0
    painted[row][col] = True
    while col < m:
        assert c[row][col] == 'B'
        assert painted[row][col]
        if c[1 - row][col] == 'B' and not painted[1-row][col]:
            row = 1 - row
            painted[row][col] = True
        elif col + 1 < m and c[row][col+1] == 'B':
            col += 1
            painted[row][col] = True
        elif col + 1 < m:
            return False
        else:
            col += 1

    return True


def solve1(c: Tuple[str, str]) -> bool:
    if c[0][0] == 'B' and c[1][0] == 'W':
        return solve_with_start(c, 0)
    elif c[0][0] == 'W' and c[1][0] == 'B':
        return solve_with_start(c, 1)
    else:
        return solve_with_start(c, 0) or solve_with_start(c, 1)


def parse1() -> Tuple[str, str]:
    _ = input()
    return input(), input()


def main():
    t: int = int(input())
    for _ in range(t):
        c: Tuple[str, str] = parse1()
        print('YES' if solve1(c) else 'NO')


if __name__ == '__main__':
    main()
