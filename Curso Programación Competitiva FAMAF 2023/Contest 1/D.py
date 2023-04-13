# https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/D

from typing import List, Tuple


def parse() -> Tuple[List[int], List[Tuple[int, int]]]:
    n, q = map(int, input().split())
    s = input()
    ss = [ord(_) - ord('a') for _ in s]
    lrs = [map(int, input().split()) for _ in range(q)]
    return ss, lrs


def solve(ss: List[int], lrs: List[Tuple[int, int]]) -> List[int]:
    n: int = len(ss)
    sums: List[int] = [0] * (n + 1)
    for i in range(n):
        sums[i + 1] = sums[i] + ss[i] + 1

    ans = []
    for l, r in lrs:
        ans.append(sums[r] - sums[l - 1])

    return ans


def main():
    print(*solve(*parse()), sep='\n')


if __name__ == '__main__':
    main()
