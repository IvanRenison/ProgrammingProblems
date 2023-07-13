# https://codeforces.com/contest/1766/problem/A

import math


def solve1(n: int) -> int:
    n_digits: int = math.floor(math.log10(n)) + 1
    first_n_digit: int = n // 10**(n_digits - 1)
    return first_n_digit + 9 * (n_digits - 1)


def parse1() -> int:
    return int(input())


def main():
    t: int = parse1()
    for _ in range(t):
        n: int = parse1()
        print(solve1(n))


if __name__ == '__main__':
    main()
