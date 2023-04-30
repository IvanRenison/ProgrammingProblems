# https://codeforces.com/gym/103388/problem/H

from typing import List, Tuple


def solve(ncs: List[Tuple[int, int]]) -> bool:
    res: bool = True
    for n, c in ncs:
        res = c == ncs[n-1][1]
        if not res:
            break
    return res


def parse() -> List[Tuple[int, int]]:
    N, K = map(int, input().split())
    ncs = [tuple(map(int, input().split())) for _ in range(N)]
    return ncs


def main():
    ncs = parse()
    res = solve(ncs)
    print('Y' if res else 'N')


if __name__ == '__main__':
    main()
