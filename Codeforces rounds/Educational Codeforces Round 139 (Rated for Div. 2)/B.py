# https://codeforces.com/contest/1766/problem/B

from typing import Optional, Set


def solve(s: str) -> bool:
    n: int = len(s)

    existing: Set[str] = set()

    last: Optional[str] = None

    for i in range(n-1):
        cc: str = s[i:i+2]
        if cc in existing:
            return True
        if last is not None:
            existing.add(last)
        last = cc

    return False


def parse1() -> str:
    _ = input()
    return input()


def main():
    t: int = int(input())
    for _ in range(t):
        s: str = parse1()
        print('YES' if solve(s) else 'NO')


if __name__ == '__main__':
    main()
