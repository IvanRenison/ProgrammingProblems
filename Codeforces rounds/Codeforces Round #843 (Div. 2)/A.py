# https://codeforces.com/contest/1775/problem/A1 https://codeforces.com/contest/1775/problem/A2

from typing import List, Literal, Tuple

Name = List[Literal['a', 'b']]


def parse1() -> Name:
    return list(input())


def solve1(abc: Name) -> Tuple[Name, Name, Name]:
    if 'a' in abc[1:-1]:
        i: int = abc[1:-1].index('a') + 1
        return abc[:i], abc[i:i+1], abc[i+1:]
    else:
        return abc[:1], abc[1:-1], abc[-1:]


def main():
    t: int = int(input())
    for _ in range(t):
        a, b, c = solve1(parse1())
        print(''.join(a), ''.join(b), ''.join(c))


if __name__ == '__main__':
    main()
