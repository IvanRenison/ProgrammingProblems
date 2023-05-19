# https://codeforces.com/contest/1833/problem/A

from typing import Dict, Set


def parse1() -> str:
    input()
    return input()


def solve1(ss: str) -> int:
    d: Set[str] = set()
    for i in range(len(ss)-1):
        d.add(ss[i:i+2])
    return len(d)


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
