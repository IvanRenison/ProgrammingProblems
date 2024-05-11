# https://open.kattis.com/problems/helpme

from functools import cmp_to_key
from typing import List, Literal, Optional, Tuple


Piece = Literal['K', 'Q', 'R', 'B', 'N', 'P']
Color = Literal['W', 'B']

Index = Literal[1, 2, 3, 4, 5, 6, 7, 8]
CharIndex = Literal['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

ChessNotationPiece = Tuple[Piece, CharIndex, Index]


def Index_to_CharIndex(index: Index) -> CharIndex:
    return chr(ord('a') + index - 1)


def CharIndex_to_Index(char_index: CharIndex) -> Index:
    return ord(char_index) - ord('a') + 1


def ChessNotationPiece_cmp(color: Color, cnp1: ChessNotationPiece, cnp2: ChessNotationPiece) -> Literal[-1, 0, 1]:
    piece1, char_index1, index1 = cnp1
    piece2, char_index2, index2 = cnp2

    piece_order = ['K', 'Q', 'R', 'B', 'N', 'P']

    if piece1 != piece2:
        return -1 if piece_order.index(piece1) < piece_order.index(piece2) else 1
    elif index1 != index2:
        if color == 'W':
            return -1 if index1 < index2 else 1
        else:
            return -1 if index1 > index2 else 1
    elif char_index1 != char_index2:
        return -1 if char_index1 < char_index2 else 1
    else:
        return 0


def parse() -> List[List[Optional[Tuple[Piece, Color]]]]:
    board: List[List[Optional[Tuple[Piece, Color]]]] = []
    for _ in range(8):
        input()
        line: str = input()
        squares: List[str] = [square[1:-1] for square in line.split('|')[1:-1]]
        row: List[Optional[Tuple[Piece, Color]]] = []
        for square in squares:
            if square in ['.', ':']:
                row.append(None)
            elif square.islower():
                row.append((square.upper(), 'B'))
            else:
                row.append((square, 'W'))
        board.append(row)
    input()
    return board


def solve(board: List[List[Optional[Tuple[Piece, Color]]]]) -> Tuple[List[ChessNotationPiece], List[ChessNotationPiece]]:
    ans: Tuple[List[ChessNotationPiece], List[ChessNotationPiece]] = ([], [])
    for i, row in enumerate(board):
        for j, square in enumerate(row):
            if square is not None:
                piece, color = square
                ans[color == 'B'].append(
                    (piece, Index_to_CharIndex(j + 1), 8 - i))

    ans[0].sort(key=cmp_to_key(
        lambda cnp1, cnp2: ChessNotationPiece_cmp('W', cnp1, cnp2)))
    ans[1].sort(key=cmp_to_key(
        lambda cnp1, cnp2: ChessNotationPiece_cmp('B', cnp1, cnp2)))

    return ans


def main():
    ans: Tuple[ChessNotationPiece, ChessNotationPiece] = solve(parse())
    White: List[str] = [(piece if piece != 'P' else '') + char_index + str(index)
                        for piece, char_index, index in ans[0]]
    Black: List[str] = [(piece if piece != 'P' else '') + char_index + str(index)
                        for piece, char_index, index in ans[1]]
    print('White:', ','.join(White))
    print('Black:', ','.join(Black))


if __name__ == '__main__':
    main()
