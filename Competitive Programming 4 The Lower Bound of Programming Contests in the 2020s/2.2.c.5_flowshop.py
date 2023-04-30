# https://open.kattis.com/problems/flowshop

from typing import List


def parse() -> List[List[int]]:
    N, _ = map(int, input().split())
    return [[int(x) for x in input().split()] for _ in range(N)]


def solve(Pss: List[List[int]]) -> List[int]:
    N: int = len(Pss)
    M: int = len(Pss[0])

    intermediate_times: List[List[int]] = [
        [0 for _ in range(M)] for _ in range(N)]
    intermediate_times[0][0] = Pss[0][0]
    for j in range(1, M):
        intermediate_times[0][j] = intermediate_times[0][j-1] + Pss[0][j]
    for i in range(1, N):
        intermediate_times[i][0] = intermediate_times[i-1][0] + Pss[i][0]
        for j in range(1, M):
            intermediate_times[i][j] = \
                max(intermediate_times[i-1][j],
                    intermediate_times[i][j-1]) + Pss[i][j]

    return [Ts[-1] for Ts in intermediate_times]


def main():
    print(*solve(parse()))


if __name__ == '__main__':
    main()
