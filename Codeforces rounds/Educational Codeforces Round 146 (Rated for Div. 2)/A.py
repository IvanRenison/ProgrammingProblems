#

from typing import Tuple


def parse1() -> Tuple[int, int]:
    return map(int, input().split())

def solve1(n: int, k: int) -> bool:
    return n % 2 == 0 or (k % 2 == 1 and k <= n)

def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
