# https://atcoder.jp/contests/abc309/tasks/abc309_b

from typing import List


def parse() -> List[List[int]]:
    N = int(input())
    return [[int(i) for i in input()] for _ in range(N)]


def solve(xs: List[List[int]]) -> List[List[int]]:
    N = len(xs)
    ans: List[List[int]] = [[xs[i][j] for j in range(N)] for i in range(N)]
    for i in range(1, N):
        ans[0][i] = xs[0][i-1]
    for j in range(1, N):
        ans[j][N-1] = xs[j-1][N-1]
    for i in range(N-2, -1, -1):
        ans[N-1][i] = xs[N-1][i+1]
    for j in range(N-2, -1, -1):
        ans[j][0] = xs[j+1][0]
    return ans


def main():
    ans = solve(parse())
    for row in ans:
        print(*row, sep='')


if __name__ == '__main__':
    main()
