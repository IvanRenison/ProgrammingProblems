#

from typing import List


def parse1():
    n = int(input())
    ls = list(map(int, input().split()))
    return ls

def solve1(ls: List[int]) -> bool:
    n = len(ls)

    amounts = [0] * 100
    for i in ls:
        amounts[i] += 1

    for i in range(1, 100):
        if amounts[i] > amounts[i-1]:
            return False

    return True


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
