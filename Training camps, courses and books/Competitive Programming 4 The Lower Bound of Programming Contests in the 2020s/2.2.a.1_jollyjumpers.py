# https://open.kattis.com/problems/jollyjumpers

from typing import List, Optional, Set


def parse1() -> Optional[List[int]]:
    try:
        n, *xs = input().split()
        return [int(x) for x in xs]
    except:
        return None


def solve1(xs: List[int]):
    n = len(xs)
    diffs: Set[int] = set()
    for i in range(0, n - 1):
        diffs.add(abs(xs[i] - xs[i + 1]))

    return diffs == set(range(1, n))


def main():
    while True:
        xs = parse1()
        if xs is None:
            break
        else:
            print("Jolly" if solve1(xs) else "Not jolly")


if __name__ == '__main__':
    main()
