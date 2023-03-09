# https://open.kattis.com/problems/downtime

from typing import List, Tuple


def parse() -> Tuple[int, List[int]]:
    n, k = map(int, input().split())
    return k, [int(input()) for _ in range(n)]


def solve(k: int, ts: List[int]) -> int:
    active_requests: int = 0
    max_active_requests: int = 0
    unqueue: List[int] = []
    for t in ts:
        while unqueue != [] and unqueue[0] <= t:
            unqueue.pop(0)
            active_requests -= 1
        active_requests += 1
        max_active_requests = max(max_active_requests, active_requests)
        unqueue.append(t + 1000)

    return (max_active_requests + k - 1) // k


def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
