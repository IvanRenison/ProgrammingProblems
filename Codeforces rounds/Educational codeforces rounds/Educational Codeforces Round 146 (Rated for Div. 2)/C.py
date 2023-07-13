#

from typing import Dict, List, Tuple


def parse1() -> Tuple[int, int, int, List[int]]:
    n, s0, s1 = map(int, input().split())
    rs = list(map(int, input().split()))
    return n, s0, s1, rs

def solve1(n: int, s0: int, s1: int, rs: List[int]) -> Tuple[List[int], List[int]]:
    s0_times: List[int] = [s0 * i for i in range(1, n + 1)]
    s1_times: List[int] = [s1 * i for i in range(1, n + 1)]

    # merge s0_times and s1_times
    s01_order: List[int] = []
    i1, i2 = 0, 0
    while i1 < n and i2 < n:
        if s0_times[i1] < s1_times[i2]:
            s01_order.append(0)
            i1 += 1
        else:
            s01_order.append(1)
            i2 += 1

    rs_: Dict[int, List[int]] = {}
    for i in range(n):
        if rs[i] not in rs_:
            rs_[rs[i]] = []
        rs_[rs[i]].append(i)

    As: List[int] = []
    Bs: List[int] = []

    rs_order: List[int] = sorted(rs_.keys())
    rs_order.reverse()

    i: int = 0
    for r in rs_order:
        for j in rs_[r]:
            if s01_order[i] == 0:
                As.append(j + 1)
            else:
                Bs.append(j + 1)
            i += 1

    return As, Bs




def main():
    t: int = int(input())
    for _ in range(t):
        As, BS = solve1(*parse1())
        print(len(As), *As, sep=' ')
        print(len(BS), *BS, sep=' ')


if __name__ == '__main__':
    main()
