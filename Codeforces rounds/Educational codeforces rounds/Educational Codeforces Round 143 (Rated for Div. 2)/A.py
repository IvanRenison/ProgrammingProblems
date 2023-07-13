# https://codeforces.com/contest/1795/problem/A

from typing import List, Literal, Tuple


Block = Literal['R', 'B']


def parse1() -> Tuple[List[Block], List[Block]]:
    input()
    ss = input()
    ts = input()
    return list(ss), list(ts)


def solve1(ss: List[Block], ts: List[Block]) -> bool:
    great_s = ss + list(reversed(ts))

    double: bool = False
    for i in range(len(great_s) - 1):
        if great_s[i] == great_s[i + 1]:
            if double:
                return False
            else:
                double = True

    return True


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print('YES')
        else:
            print('NO')


if __name__ == '__main__':
    main()
