# https://open.kattis.com/problems/greedilyincreasing

from typing import List


def parse() -> List[int]:
    input()
    return list(map(int, input().split()))


def solve(As: List[int]) -> List[int]:
    Bs: List[int] = [As[0]]
    for A in As[1:]:
        if A > Bs[-1]:
            Bs.append(A)

    return Bs


def main():
    ans: List[int] = solve(parse())
    print(len(ans))
    print(*ans)


if __name__ == '__main__':
    main()
