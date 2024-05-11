# https://open.kattis.com/problems/memorymatch

from typing import Dict, List, Optional, Set, Tuple


def parse() -> Tuple[int, List[Tuple[int, int, str, str]]]:
    N: int = int(input())
    K: int = int(input())
    pairs: List[Tuple[int, int, str, str]] = []
    for _ in range(K):
        C1, C2, P1, P2 = input().split()
        pairs.append((int(C1), int(C2), P1, P2))
    return N, pairs


def solve(N: int, pairs: List[Tuple[int, int, str, str]]) -> int:
    revealed_cards: Dict[str, Optional[Set[int]]] = {}
    nones: int = 0
    for C1, C2, P1, P2 in pairs:
        if P1 == P2:
            revealed_cards[P1] = None
            nones += 1
        else:
            revealed_cards.setdefault(P1, set()).add(C1)
            revealed_cards.setdefault(P2, set()).add(C2)

    if len(revealed_cards) < N // 2:
        ans: int = 0

        for Cs in revealed_cards.values():
            if Cs is not None and len(Cs) == 2:
                ans += 1

        if nones + ans == N // 2 - 1:
            ans += 1

        return ans
    else:
        return N // 2 - nones


def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
