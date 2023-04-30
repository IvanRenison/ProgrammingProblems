# https://codeforces.com/contest/1798/problem/A

from typing import List, Tuple


def parse1() -> Tuple[List[int], List[int]]:
    input()
    return list(map(int, input().split())), list(map(int, input().split()))

def solve1(As: List[int], Bs: List[int]) -> bool:
    N: int = len(As)
    a_N = As[N-1]
    b_N = Bs[N-1]

    last_max: int = max(a_N, b_N)
    last_min: int = min(a_N, b_N)

    for i in range(N-1):
        a = As[i]
        b = Bs[i]

        if max(a, b) > last_max or min(a, b) > last_min:
            return False

    return True

def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print('Yes')
        else:
            print('No')


if __name__ == '__main__':
    main()
