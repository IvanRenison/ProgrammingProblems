# https://codeforces.com/gym/103960/problem/N

from typing import Dict, List, Set, Tuple


def parse() -> Tuple[List[int], List[int], int, int]:
    input()
    As = list(map(int, input().split()))
    Bs = list(map(int, input().split()))
    K, L = map(int, input().split())
    return As, Bs, K, L


def insert_in_index(d: Dict[int, Set[int]], key: int, value: int):
    if key not in d:
        d[key] = set()
    d[key].add(value)

def remove_from_index(d: Dict[int, Set[int]], key: int, value: int):
    d[key].remove(value)
    if len(d[key]) == 0:
        d.pop(key)

def solve(As: List[int], Bs: List[int], K: int, L: int) -> int:
    N: int = len(As)

    selected_firsts: int = K
    selected_points: int = sum(As[:K])

    K_flipped_indexes: Set[int] = set()
    K_flipped_values_indexes: Dict[int, Set[int]] = {}
    K_flipped_points: int = 0
    min_flipped_index: int = 0
    min_flipped_value: int = 1000000001
    # K_non_flipped_indexes: Set[int] = {}
    K_non_flipped_values_indexes: Dict[int, Set[int]] = {}

    for i in range(K):
        B: int = Bs[i]
        if i < L:
            K_flipped_indexes.add(i)

            insert_in_index(K_flipped_values_indexes, B, i)
            K_flipped_points += B

            if B < min_flipped_value:
                min_flipped_index = i
                min_flipped_value = B
        else:
            if B > min_flipped_value:
                K_flipped_indexes.remove(min_flipped_index)
                # K_non_flipped_indexes.add(min_flipped_index)
                insert_in_index(K_non_flipped_values_indexes, Bs[min_flipped_index], min_flipped_index)

                K_flipped_indexes.add(i)
                insert_in_index(K_flipped_values_indexes, B, i)

                K_flipped_points += B

                K_flipped_values_indexes[min_flipped_value].remove(min_flipped_index)
                K_flipped_points -= min_flipped_value
                if len(K_flipped_values_indexes[min_flipped_value]) == 0:
                    K_flipped_values_indexes.pop(min_flipped_value)
                    min_flipped_value = min(K_flipped_values_indexes.keys())
                    min_flipped_index = min(K_flipped_values_indexes[min_flipped_value])
            else:
                insert_in_index(K_non_flipped_values_indexes, B, i)

    res: int = selected_points + K_flipped_points
    while selected_firsts > 0:
        selected_firsts -= 1
        old = selected_firsts
        new = N - K + selected_firsts
        A_old = As[old]
        B_old = Bs[old]
        A_new: int = As[new]
        B_new: int = Bs[new]

        selected_points = selected_points - A_old + A_new

        if old in K_flipped_indexes:
            insert_in_index(K_non_flipped_values_indexes, B_new, new)

            K_flipped_indexes.remove(old)
            remove_from_index(K_flipped_values_indexes, B_old, old)

            new_flipped_value = max(K_non_flipped_values_indexes.keys())
            new_flipped_index = min(K_non_flipped_values_indexes[new_flipped_value])

            remove_from_index(K_non_flipped_values_indexes, new_flipped_value, new_flipped_index)

            K_flipped_indexes.add(new_flipped_index)
            insert_in_index(K_flipped_values_indexes, new_flipped_value, new_flipped_index)

            if new_flipped_value < min_flipped_value:
                min_flipped_value = new_flipped_value
                min_flipped_index = new_flipped_index
            elif B_old == min_flipped_value:
                min_flipped_value = min(K_flipped_values_indexes.keys())
                min_flipped_index = min(K_flipped_values_indexes[min_flipped_value])

            K_flipped_points = K_flipped_points - B_old + new_flipped_value
        else:
            if B_old in K_non_flipped_values_indexes.keys():
                remove_from_index(K_non_flipped_values_indexes, B_old, old)

            if B_new > min_flipped_value:
                K_flipped_indexes.remove(min_flipped_index)
                remove_from_index(K_flipped_values_indexes, min_flipped_value, min_flipped_index)

                K_flipped_points -= min_flipped_value

                K_flipped_indexes.add(new)
                insert_in_index(K_flipped_values_indexes, B_new, new)

                K_flipped_points += B_new

                min_flipped_value = min(K_flipped_values_indexes.keys())
                min_flipped_index = min(K_flipped_values_indexes[min_flipped_value])
            else:
                insert_in_index(K_non_flipped_values_indexes, B_new, new)

        res = max(res, selected_points + K_flipped_points)

    return res



def main():
    print(solve(*parse()))



if __name__ == '__main__':
    main()
