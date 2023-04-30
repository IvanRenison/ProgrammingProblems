#

from typing import List, Optional, Tuple


def parse1() -> List[Tuple[int, int, int, Optional[int]]]:
    q: int = int(input())
    events: List[Tuple[int, int, int, int]] = []
    for _ in range(q):
        line = input().split()
        if line[0] == '1':
            events.append((1, int(line[1]), int(line[2]), int(line[3])))
        else:
            events.append((2, int(line[1]), int(line[2]), None))

    return events

def min_max_heights(a: int, b: int, n: int) -> Tuple[int, int]:
    if n == 1:
        return 0, a
    day_before = a*(n-1) - b*(n-2)
    day = a*n - b*(n-1)
    return day_before + 1, day

def days_needed(a: int, b: int, h: int) -> int:
    if a >= h:
        return 1
    return (h - b) // (a-b) + ((h - b) % (a-b) != 0)

def solve1(events: List[Tuple[int, int, int, int]]) -> List[int]:
    ans: List[int] = []
    min_possible = 0
    max_possible = float('inf')
    for event in events:
        if event[0] == 1:
            day_before, day = min_max_heights(event[1], event[2], event[3])
            if day < min_possible or day_before > max_possible:
                ans.append(0)
            else:
                ans.append(1)
                min_possible = max(min_possible, day_before)
                max_possible = min(max_possible, day)
        else:
            maybe_min = days_needed(event[1], event[2], min_possible)
            maybe_max = days_needed(event[1], event[2], max_possible)
            if maybe_min == maybe_max:
                ans.append(maybe_min)
            else:
                ans.append(-1)

    return ans


def main():
    t: int = int(input())
    for _ in range(t):
        print(*solve1(parse1()), sep=' ')


if __name__ == '__main__':
    main()
