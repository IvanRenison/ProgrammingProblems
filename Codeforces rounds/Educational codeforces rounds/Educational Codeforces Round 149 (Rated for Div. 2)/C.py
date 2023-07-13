# https://codeforces.com/contest/1837/problem/C

from typing import List


def parse1() -> List[str]:
    return list(input())


def solve1(s: List[str]) -> List[str]:
    n = len(s)
    i = 0
    while i < n and s[i] == '?':
        s[i] = '0'
        i += 1
    if i == n:
        return s

    j = n-1
    while s[j] == '?':
        s[j] = '1'
        j -= 1

    while i < j:
        if s[i] == '?':
            k = i
            while s[k] == '?':
                k += 1
            if s[i-1] == s[k]:
                for l in range(i, k):
                    s[l] = s[i-1]
            else:
                for l in range(i, k):
                    s[l] = '0'
            i = k
        else:
            i += 1

    return s




def main():
    t: int = int(input())
    for _ in range(t):
        print(*solve1(parse1()), sep='')


if __name__ == '__main__':
    main()
