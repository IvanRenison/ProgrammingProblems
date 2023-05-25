# https://codeforces.com/contest/1837/problem/D

from typing import List, Optional, Tuple


def parse1() -> List[str]:
    input()
    return list(input())


def solve1(s: List[str]) -> Optional[Tuple[int, List[int]]]:
    n = len(s)

    n_open = 0
    n_close = 0
    for c in s:
        if c == '(':
            n_open += 1
        else:
            n_close += 1

    if n_open != n_close:
        return None

    colors: List[Optional[int]] = [None] * n
    n_colors = 0

    for i in range(n):
        if colors[i] == None:
            start: str = s[i]
            n_start = 0
            for j in range(i, n):
                if colors[j] == None:
                    if s[j] == start:
                        n_start += 1
                        colors[j] = n_colors + 1
                    elif n_start > 0:
                        n_start -= 1
                        colors[j] = n_colors + 1
            j = n-1
            while n_start > 0:
                if colors[j] == n_colors + 1 and s[j] == start:
                    n_start -= 1
                    colors[j] = None
                j -= 1

            n_colors += 1

    return n_colors, colors


def main():
    t: int = int(input())
    for _ in range(t):
        ans = solve1(parse1())
        if ans is None:
            print('-1')
        else:
            print(ans[0])
            print(*ans[1])


if __name__ == '__main__':
    main()
