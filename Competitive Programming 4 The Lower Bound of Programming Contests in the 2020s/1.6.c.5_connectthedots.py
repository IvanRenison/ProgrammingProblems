# https://open.kattis.com/problems/connectthedots

from typing import Dict, List, Literal, Optional, Tuple

Symbol = Literal[
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
]


def my_input() -> Optional[str]:
    try:
        return input()
    except:
        return None


def parse() -> Tuple[List[List[Optional[Symbol]]], bool]:
    last_signal: bool = False
    board: List[List[Optional[Symbol]]] = []
    line: str = input()

    row: List[Optional[Symbol]] = [None if c == '.' else c for c in line]
    board.append(row)
    while True:
        line: Optional[str] = my_input()
        if line == None:
            last_signal = True
            break
        elif line == '':
            break
        row: List[Optional[Symbol]] = [None if c == '.' else c for c in line]
        board.append(row)

    return board, last_signal


NumericSymbol = Literal[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61
]

SolvedSymbol = Literal[
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '|', '-', '+'
]


def Symbol_to_NumericSymbol(s: Symbol) -> NumericSymbol:
    if s.isdigit():
        return int(s)
    elif s.islower():
        return ord(s) - ord('a') + 10
    else:
        return ord(s) - ord('A') + 36


def NumericSymbol_to_Symbol(n: NumericSymbol) -> SolvedSymbol:
    if n < 10:
        return str(n)
    elif n < 36:
        return chr(n - 10 + ord('a'))
    else:
        return chr(n - 36 + ord('A'))


def solve(board: List[List[Optional[Symbol]]]) -> List[List[Optional[SolvedSymbol]]]:
    ans: List[List[Optional[SolvedSymbol]]] = [row.copy() for row in board]
    positions: Dict[NumericSymbol, Tuple[int, int]] = {}
    for i, row in enumerate(board):
        for j, symbol in enumerate(row):
            if symbol is not None:
                positions[Symbol_to_NumericSymbol(symbol)] = (i, j)

    for n, ij in positions.items():
        if n != 0:
            ij_: Tuple[int, int] = positions[n-1]

            i_, j_ = ij_

            i, j = ij

            if i_ == i:
                for k in range(min(j, j_)+1, max(j, j_)):
                    if ans[i][k] is None:
                        ans[i][k] = '-'
                    elif ans[i][k] == '|':
                        ans[i][k] = '+'
            else:
                for k in range(min(i, i_)+1, max(i, i_)):
                    if ans[k][j] is None:
                        ans[k][j] = '|'
                    elif ans[k][j] == '-':
                        ans[k][j] = '+'

    return ans


def main():
    last_signal: bool = False
    while not last_signal:
        board, last_signal = parse()
        ans = solve(board)
        for row in ans:
            line: List[str] = ['.' if c is None else c for c in row]
            print(''.join(line))
        if not last_signal:
            print()


if __name__ == '__main__':
    main()
