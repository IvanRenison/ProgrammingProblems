# https://codeforces.com/contest/1771/problem/B

from typing import Dict, List, Tuple


def solve1(n: int, As: List[Tuple[int, int]]) -> int:
    d: Dict[int, List[int]] = {}

    for (x, y) in As:
        if x not in d:
            d[x] = []
        d[x].append(y)

        if y not in d:
            d[y] = []
        d[y].append(x)

    res: int = 0
    i: int = 1
    racha_starts_at: int = 1
    while i <= n:
        # print(f"{i=}")
        d_i: List[int] = []
        if i in d:
            d_i = d[i]

        breaks_racha: bool = False
        j: int = i-1
        while j >= racha_starts_at:
            if j in d_i:
                breaks_racha = True
                break
            j -= 1

        if breaks_racha:
            #print("breaks racha")
            racha_starts_at = j + 1
            # print(f"{racha_starts_at=}")
            res -= int((i - racha_starts_at) * (i - racha_starts_at+1)/2)
            i = racha_starts_at
        else:
            res += i - racha_starts_at + 1
            i += 1

        # print(f"{res=}")

    return res


def parse1() -> Tuple[int, List[Tuple[int, int]]]:
    n, m = (int(x) for x in input().split())
    As = [tuple(int(x) for x in input().split()) for _ in range(m)]
    return n, As


def main():
    t = int(input())
    for _ in range(t):
        print(solve1(*parse1()))


if __name__ == '__main__':
    main()
