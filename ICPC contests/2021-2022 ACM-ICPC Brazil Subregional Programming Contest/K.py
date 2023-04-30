# https://codeforces.com/gym/103388/problem/K

from typing import List, Tuple


def solve(T: int, D: int, ys: List[int]) -> bool:

    ys = [0] + ys + [D]

    intervals: List[int] = []
    for j in range(len(ys)-1):
        intervals.append(ys[j+1] - ys[j])
    intervals.append(D - ys[-1])

    res: bool = False
    for interval in intervals:
        if interval >= T:
            res = True
            break
    return res


def parse() -> Tuple[int, int, List[int]]:
    T, D, M = map(int, input().split())
    ys = [int(input()) for _ in range(M)]
    return T, D, ys


def main():
    T, D, ys = parse()
    res = solve(T, D, ys)
    print('Y' if res else 'N')


if __name__ == '__main__':
    main()
