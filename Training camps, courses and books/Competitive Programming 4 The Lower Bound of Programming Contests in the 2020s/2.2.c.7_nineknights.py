# https://open.kattis.com/problems/nineknights

from typing import List, Literal


Box = Literal['.', 'k']


def parse() -> List[List[Box]]:
    return [list(input()) for _ in range(5)]


def solve(board: List[List[Box]]) -> bool:
    amount_k: int = 0

    for i in range(5):
        for j in range(5):
            if board[i][j] == 'k':
                amount_k += 1
                for di, dj in [(1, 2), (2, 1), (-1, 2), (-2, 1), (1, -2), (2, -1), (-1, -2), (-2, -1)]:
                    i_: int = i + di
                    j_: int = j + dj
                    if i_ in range(5) and j_ in range(5) and board[i_][j_] == 'k':
                        return False

    return amount_k == 9


def main():
    ans: bool = solve(parse())
    if ans:
        print("valid")
    else:
        print("invalid")


if __name__ == '__main__':
    main()
