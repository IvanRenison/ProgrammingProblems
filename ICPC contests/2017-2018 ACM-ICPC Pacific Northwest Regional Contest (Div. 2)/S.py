# https://codeforces.com/gym/101652

from typing import Tuple


def parse() -> str:
    return input()


def solve(rains: str) -> Tuple[int, int]:
    n = len(rains)

    partial_weights = [0] * (n + 1)

    for i in range(n):
        if rains[i] == 'B':
            partial_weights[i + 1] = partial_weights[i] + 1
        else:
            partial_weights[i + 1] = partial_weights[i] - 1

    index_min = 0
    index_max = 0

    for i in range(n + 1):
        if partial_weights[i] < partial_weights[index_min]:
            index_min = i
        if partial_weights[i] > partial_weights[index_max]:
            index_max = i

    return min(index_min, index_max) + 1, max(index_min, index_max)


def main():
    print(*solve(parse()), sep=' ')


if __name__ == '__main__':
    main()
