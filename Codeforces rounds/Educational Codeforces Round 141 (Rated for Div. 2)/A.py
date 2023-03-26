# https://codeforces.com/contest/1783/problem/0

from typing import List, Optional


def parse1() -> List[int]:
    input()
    return [int(a) for a in input().split()]


def solve1(As: List[int]) -> Optional[List[int]]:
    n: int = len(As)

    As.sort(reverse=True)

    res: List[int] = []
    res_sum: int = 0

    while n > 0:
        i: int = 0
        while i < n and As[i] == res_sum:
            i += 1

        if i == n:
            return None

        a: int = As.pop(i)
        n -= 1
        res.append(a)

        res_sum += a

    return res


def main():
    t: int = int(input())
    for _ in range(t):
        res: Optional[List[int]] = solve1(parse1())
        if res is None:
            print("NO")
        else:
            print("YES")
            print(" ".join([str(a) for a in res]))


if __name__ == '__main__':
    main()
