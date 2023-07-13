# https://codeforces.com/contest/1744/problem/C

from typing import List, Literal, Optional, Tuple


def solve1(ss: List[Literal['r', 'g', 'y']], c: Literal['r', 'g', 'y']) -> int:
    if c == 'g':
        return 0

    first_c: int = ss.index('g')
    local_max: Optional[int] = None
    global_max: int = 0
    for i in list(range(first_c+1, len(ss))) + list(range(0, first_c+1)):
        s: Literal['r', 'g', 'y'] = ss[i]
        if s == 'g' and local_max is not None:
            global_max = max(global_max, local_max+1)
            local_max = None
        elif s == c and local_max is None:
            local_max = 0
        elif local_max is not None:
            local_max += 1

    return global_max


def parse1() -> Tuple[List[Literal['r', 'g', 'y']], Literal['r', 'g', 'y']]:
    _, c = input().split()
    ss = list(input())
    return ss, c


def main():
    t = int(input())
    for _ in range(t):
        ss, c = parse1()
        print(solve1(ss, c))


if __name__ == '__main__':
    main()
