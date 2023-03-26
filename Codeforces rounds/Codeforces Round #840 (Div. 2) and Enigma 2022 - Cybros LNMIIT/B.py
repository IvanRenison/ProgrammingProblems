# https://codeforces.com/contest/1763/problem/B

from typing import List, Tuple


def solve1(k: int, hps: List[Tuple[int, int]]) -> bool:
    hps.sort(key=lambda hp: hp[1])
    damage: int = 0
    n: int = len(hps)
    for i in range(n):
        h, p = hps[i]

        if damage >= h:
            continue

        while damage < h:
            if damage > 0:
                k -= p
                if k <= 0:
                    return False
            damage += k

    return damage >= hps[-1][0]


def parse1() -> Tuple[int, List[Tuple[int, int]]]:
    _, k = map(int, input().split())
    hs: List[int] = list(map(int, input().split()))
    ps: List[int] = list(map(int, input().split()))
    return k, list(zip(hs, ps))


def main():
    t: int = int(input())
    for _ in range(t):
        res: bool = solve1(*parse1())
        print('YES' if res else 'NO')


if __name__ == '__main__':
    main()
