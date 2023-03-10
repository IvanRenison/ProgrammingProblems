#

from operator import concat
from random import randint, random, seed
from typing import List, Set, Tuple


def parse1() -> Tuple[int, int]:
    return tuple(map(int, input().split()))

def solve1(n: int, m: int) -> Tuple[int, List[List[int]]]:
    Bss: List[List[int]] = [[0] * m for _ in range(n)]

    assigned: Set[int] = set()

    def assign_xor_right_bottom_to(i: int, j: int):
        new = (
            Bss[i - 3][j - 3]
            ^ Bss[i - 3][j - 2]
            ^ Bss[i - 2][j - 3]
            ^ Bss[i - 2][j - 2]
            ^ Bss[i - 1][j - 1]
            ^ Bss[i - 1][j]
            ^ Bss[i][j - 1]
        )
        Bss[i][j] = new
        if new in assigned:
            print(f"{i=}, {j=}, {new=}")
            for Bs in Bss:
                print(*Bs, sep=' ')
            assert False
        assigned.add(new)

    def assign_xor_left_bottom_to(i: int, j: int):
        new = (
            Bss[i - 3][j + 1]
            ^ Bss[i - 3][j + 2]
            ^ Bss[i - 2][j + 1]
            ^ Bss[i - 2][j + 2]
            ^ Bss[i - 1][j - 1]
            ^ Bss[i - 1][j]
            ^ Bss[i][j - 1]
        )
        Bss[i][j] = new
        if new in assigned:
            print(f"{i=}, {j=}, {new=}")
            for Bs in Bss:
                print(*Bs, sep=' ')
            assert False
        assigned.add(new)

    def assign_xor_top_right_to(i: int, j: int):
        new = (
            Bss[i - 1][j - 1]
            ^ Bss[i - 1][j]
            ^ Bss[i][j - 1]
            ^ Bss[i + 1][j - 3]
            ^ Bss[i + 1][j - 2]
            ^ Bss[i + 2][j - 3]
            ^ Bss[i + 2][j - 2]
        )
        Bss[i][j] = new
        if new in assigned:
            print(f"{i=}, {j=}, {new=}")
            for Bs in Bss:
                print(*Bs, sep=' ')
            assert False
        assigned.add(new)

    next: int = 1

    def assign_next_to(i: int, j: int):
        # options: List[int] = []
        # for x in range(1, 2**63+1):
        #     if x not in assigned:
        #         options.append(x)
        #     if len(options) > 1000:
        #         break

        # x = options[randint(0, len(options)-1)]
        # Bss[i][j] = x
        # assigned.add(x)

        nonlocal next
        while next in assigned:
            next = (next << 1) % (2**63 - 1) + 1
        Bss[i][j] = next
        assigned.add(next)
        next = ((next << 1) - 1) % 2**63 + 1

        # new: int = randint(0, 2**63)
        # while new in assigned:
        #     new = randint(0, 2**63)
        # Bss[i][j] = new
        # assigned.add(new)


    assign_next_to(0, 0)
    assign_next_to(0, 1)
    assign_next_to(0, 2)
    assign_next_to(0, 3)
    assign_next_to(1, 0)
    assign_next_to(1, 1)
    assign_next_to(1, 2)
    assign_next_to(1, 3)
    assign_next_to(2, 0)
    assign_next_to(2, 1)
    assign_next_to(2, 2)
    assign_next_to(2, 3)
    assign_next_to(3, 0)
    assign_xor_left_bottom_to(3, 1)
    assign_next_to(3, 2)

    assign_xor_right_bottom_to(3, 3)

    for j in range(4, m):
        assign_next_to(0, j)
        assign_xor_top_right_to(1, j)

        assign_next_to(2, j)
        assign_xor_right_bottom_to(3, j)

    for i in range(4, n):
        assign_next_to(i, 0)
        assign_xor_left_bottom_to(i, 1)
        assign_next_to(i, 2)

        assign_xor_right_bottom_to(i, 3)

    for j in range(4, m):
        for i in range(4, n):
            assign_xor_right_bottom_to(i, j)

    return n*m, Bss

def main():
    t: int = int(input())
    for _ in range(t):
        cnt, Bss = solve1(*parse1())
        print(cnt)
        for Bs in Bss:
            print(*Bs, sep=' ')


if __name__ == '__main__':
    main()

