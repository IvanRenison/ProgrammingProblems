# https://codeforces.com/gym/103388/problem/E

from typing import List, Optional, Tuple


def solve(tds: List[Tuple[int, int]]) -> int:
    direction: Optional[int] = None
    queue_in_sides: List[bool] = [False, False]

    stopping_time: int = 0

    for td in tds:
        t, d = td
        if stopping_time < t and (queue_in_sides[0] or queue_in_sides[1]):
            direction = 0 if queue_in_sides[0] else 1
            stopping_time += 10
            queue_in_sides[direction] = False

        if direction is None:
            direction = d
            stopping_time = t + 10
        elif direction == d:
            stopping_time = t + 10
        elif stopping_time > t:
            queue_in_sides[d] = True
        else:
            direction = d
            stopping_time = t + 10

    if queue_in_sides[0] or queue_in_sides[1]:
        stopping_time += 10

    return stopping_time


def parse() -> List[Tuple[int, int]]:
    N: int = int(input())
    tds: List[Tuple[int, int]] = [
        tuple(map(int, input().split())) for _ in range(N)]
    return tds


def main():
    tds = parse()
    res = solve(tds)
    print(res)


if __name__ == '__main__':
    main()
