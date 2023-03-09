# https://codeforces.com/contest/1795/problem/C

from typing import List, Tuple


def parse1() -> Tuple[List[int], List[int]]:
    input()
    return list(map(int, input().split())), list(map(int, input().split()))


def binary_search(x: int, it: List[int]) -> int:
    lower: int = 0
    upper: int = len(it)
    while lower + 1 < upper:
        m: int = (lower + upper) // 2
        if it[m] <= x:
            lower = m
        else:
            upper = m
    return lower


def solve1(a: List[int], b: List[int]) -> List[int]:
    n: int = len(a)

    res: List[int] = [0] * n

    sums_b: List[int] = [0] * (n+1)
    sums_b[0] = 0
    for i in range(n):
        sums_b[i+1] = sums_b[i] + b[i]

    counts_prefixed_sum: List[int] = [0] * (n+2)

    for i in range(n):
        a_i = a[i]

        # Find the last index j such that sums_b[j] <= a_i
        j: int = binary_search(a_i + sums_b[i], sums_b)

        counts_prefixed_sum[i] += 1
        counts_prefixed_sum[j] -= 1

        if sums_b[j] - sums_b[i] < a_i and j < n:
            res[j] += a_i - sums_b[j] + sums_b[i]

    counts: List[int] = [0] * n
    counts[0] = counts_prefixed_sum[0]
    for i in range(1, n):
        counts[i] = counts_prefixed_sum[i] + counts[i-1]

    for i in range(n):
        res[i] += counts[i] * b[i]

    return res


def main():
    t: int = int(input())
    for _ in range(t):
        print(*solve1(*parse1()))


if __name__ == '__main__':
    main()
