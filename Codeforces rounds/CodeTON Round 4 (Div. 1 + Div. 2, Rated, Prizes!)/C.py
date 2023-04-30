#

from typing import List, Set, Tuple


def parse1() -> Tuple[int, int, List[int]]:
    _, c, d = map(int, input().split())
    As: List[int] = list(map(int, input().split()))
    return c, d, As

def solve1(c: int, d: int, As: List[int]) -> int:
    As_set: Set[int] = set(As)

    base_ans: int = c*(len(As) - len(As_set))
    if 1 not in As_set:
        base_ans += d
        As_set.add(1)

    len_As: int = len(As_set)

    if len_As == 1:
        return base_ans

    As_list: List[int] = list(As_set)
    As_list.sort()

    amount_added: int = 0

    min_new_ans: int = c*(len_As - 1)

    for i in range(1, len_As):
        amount_added += As_list[i] - As_list[i-1] - 1
        min_new_ans = min(min_new_ans, d*amount_added + c*(len_As - 1 - i))

    return base_ans + min_new_ans

def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(*parse1()))


if __name__ == '__main__':
    main()
