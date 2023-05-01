#

from typing import List


def parse1() -> List[int]:
    input()
    return list(map(int, input().split()))

def solve1(As: List[int]) -> bool:
    for i, a in enumerate(As):
        if a <= i + 1:
            return True
    return False

def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(parse1()):
            print('YES')
        else:
            print('NO')


if __name__ == '__main__':
    main()
