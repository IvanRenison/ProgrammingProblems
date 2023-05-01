# https://open.kattis.com/problems/empleh

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

def parse_piece(pci: str) -> ChessNotationPiece:
    if len(pci) == 2:
        piece: Piece = 'P'
        char_index: CharIndex = pci[0]
        index: Index = int(pci[1])
    else:
        piece: Piece = pci[0]
        char_index: CharIndex = pci[1]
        index: Index = int(pci[2])
    return piece, char_index, index

def parse() -> Tuple[List[ChessNotationPiece], List[ChessNotationPiece]]:
    in_w: List[str] = input()[7:].split(',')
    in_b: List[str] = input()[7:].split(',')

    if in_w == ['']:
        in_w = []

    if in_b == ['']:
        in_b = []

    w: List[ChessNotationPiece] = [
        parse_piece(pci) for pci in in_w
    ]
    b: List[ChessNotationPiece] = [
        parse_piece(pci) for pci in in_b
    ]
    return w, b

def solve(w: List[ChessNotationPiece], b: List[ChessNotationPiece]) -> List[List[Optional[Tuple[Piece, Color]]]]:
    ans: List[List[Optional[Tuple[Piece, Color]]]] = [[None for _ in range(8)] for _ in range(8)]
    for piece, char_index, index in w:
        ans[8 - index][CharIndex_to_Index(char_index) - 1] = (piece, 'W')
    for piece, char_index, index in b:
        ans[8 - index][CharIndex_to_Index(char_index) - 1] = (piece, 'B')

    return ans

def main():
    ans: List[List[Optional[Tuple[Piece, Color]]]] = solve(*parse())
    print("+---+---+---+---+---+---+---+---+")
    for i, row in enumerate(ans):
        for j, square in enumerate(row):
            print("|", end='')
            back: Literal['.', ':'] = '.' if (i + j) % 2 == 0 else ':'
            print(back, end='')
            if square is None:
                print(back, end='')
            else:
                piece, color = square
                print(piece.lower() if color == 'B' else piece, end='')
            print(back, end='')
        print("|")
        print("+---+---+---+---+---+---+---+---+")


if __name__ == '__main__':
    main()
