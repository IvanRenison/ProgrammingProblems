# https://codeforces.com/contest/1744/problem/B

from typing import List, Tuple


def solve1(As: List[int], xs: List[Tuple[int, int]]) -> List[int]:
    sum_as: int = 0
    cant_even_as: int = 0
    cant_odd_as: int = 0
    for a in As:
        sum_as += a
        if a % 2 == 0:
            cant_even_as += 1
        else:
            cant_odd_as += 1

    ans: List[int] = []
    for t, x in xs:
        if t == 0:
            sum_as += cant_even_as * x
            if x % 2 != 0:
                cant_odd_as += cant_even_as
                cant_even_as = 0
        else:
            sum_as += cant_odd_as * x
            if x % 2 != 0:
                cant_even_as += cant_odd_as
                cant_odd_as = 0
        ans.append(sum_as)

    return ans



def parse1() -> Tuple[List[int], List[Tuple[int, int]]]:
    n, q = map(int, input().split())
    As: List[int] = list(map(int, input().split()))
    xs: List[Tuple[int, int]] = [tuple(map(int, input().split())) for _ in range(q)]
    return As, xs


def main():
    t: int = int(input())
    for _ in range(t):
        As, xs = parse1()
        ans: List[int] = solve1(As, xs)
        print(*ans, sep='\n')


if __name__ == '__main__':
    main()
