# https://open.kattis.com/problems/bela

from typing import List, Literal, Tuple

Suit = Literal['S', 'H', 'D', 'C']
Value = Literal['A', 'K', 'Q', 'J', 'T', '9', '8', '7']


def parse() -> Tuple[Suit, List[Tuple[Value, Suit]]]:
    N, suit = input().split()
    N: int = int(N)
    return suit, [tuple(input()) for _ in range(4*N)]


def solve(dominant_suit: Suit, cards: List[Tuple[Value, Suit]]) -> int:
    def points(card: Tuple[Value, Suit]) -> int:
        value, card_suit = card
        if dominant_suit == card_suit:
            if value == 'A':
                return 11
            elif value == 'K':
                return 4
            elif value == 'Q':
                return 3
            elif value == 'J':
                return 20
            elif value == 'T':
                return 10
            elif value == '9':
                return 14
            else:
                return 0
        else:
            if value == 'A':
                return 11
            elif value == 'K':
                return 4
            elif value == 'Q':
                return 3
            elif value == 'J':
                return 2
            elif value == 'T':
                return 10
            else:
                return 0

    return sum(points(card) for card in cards)


def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
