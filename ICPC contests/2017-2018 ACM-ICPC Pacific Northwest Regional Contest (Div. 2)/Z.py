# https://codeforces.com/gym/101652

from typing import List


def parse() -> List[int]:
    ns = list(input())
    return [int(n) for n in ns]


def solve(n: List[int]) -> List[int]:

    for i in range(len(n) - 1, -1, -1):
        if n[i] != 9:
            n[i] += 1
            break
        else:
            n[i] = 1
            if i == 0:
                n.insert(0, 1)

    return n


def main():
    print(*solve(parse()), sep='')


if __name__ == '__main__':
    main()
