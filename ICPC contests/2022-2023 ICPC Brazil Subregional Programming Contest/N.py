# https://codeforces.com/gym/103960/problem/N


from typing import Dict, List, Tuple


def multiset_remove(ms: Dict[int, int], x: int):
    ms[x] -= 1
    if ms[x] == 0:
        del ms[x]


def multiset_add(ms: Dict[int, int], x: int):
    ms[x] = ms.get(x, 0) + 1


def solve(As: List[int], Bs: List[int], K: int, L: int) -> int:
    N: int = len(As)

    as_sum: int = 0

    # multisets
    bs_values_used: Dict[int, int] = {}
    bs_values_unused: Dict[int, int] = {}

    for i in range(K):
        as_sum += As[i]
        multiset_add(bs_values_used, Bs[i])

    # Keep only L in bs_values_used
    while len(bs_values_used) > L:
        min_bs_value: int = min(bs_values_used.keys())
        multiset_remove(bs_values_used, min_bs_value)
        multiset_add(bs_values_unused, min_bs_value)

    bs_used_sum: int = 0
    for k, v in bs_values_used.items():
        bs_used_sum += k * v

    max_sum: int = as_sum + bs_used_sum

    for i in range(1, K + 1):
        a_old: int = As[K - i]
        b_old: int = Bs[K - i]
        a_new: int = As[N - i]
        b_new: int = Bs[N - i]

        as_sum -= a_old
        as_sum += a_new

        if b_old in bs_values_used:
            multiset_add(bs_values_unused, b_new)

            multiset_remove(bs_values_used, b_old)
            bs_used_sum -= b_old

            b_used_new: int = max(bs_values_unused.keys())

            multiset_add(bs_values_used, b_used_new)
            bs_used_sum += b_used_new
            multiset_remove(bs_values_unused, b_used_new)

        elif b_new > min(bs_values_used.keys()):
            b_used_new: int = min(bs_values_used.keys())
            multiset_add(bs_values_unused, b_used_new)
            multiset_remove(bs_values_used, b_used_new)
            bs_used_sum -= b_used_new

            multiset_add(bs_values_used, b_new)
            bs_used_sum += b_new

        else:
            multiset_remove(bs_values_unused, b_old)
            multiset_add(bs_values_unused, b_new)

        max_sum = max(max_sum, as_sum + bs_used_sum)

    return max_sum


def parse() -> Tuple[List[int], List[int], int, int]:
    _: int = int(input())
    As: List[int] = list(map(int, input().split()))
    Bs: List[int] = list(map(int, input().split()))

    K, L = map(int, input().split())

    return As, Bs, K, L


def main():
    As, Bs, K, L = parse()
    print(solve(As, Bs, K, L))


if __name__ == '__main__':
    main()
