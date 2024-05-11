# https://open.kattis.com/problems/2048

from typing import List, Literal, Optional, Tuple


Move = Literal[0, 1, 2, 3]

Left = 0
Up = 1
Right = 2
Down = 3


def parse() -> Tuple[List[List[int]], Move]:
    board: List[List[int]] = [
        list(map(int, input().split())) for _ in range(4)]
    move: Move = int(input())
    return board, move


def get_next(row: List[int], i: int) -> Optional[int]:
    for k in range(i+1, len(row)):
        if row[k] != 0:
            return k
    return None


def move_left(board: List[List[int]]) -> List[List[int]]:
    for row in board:
        for i in range(4):
            next: Optional[int] = get_next(row, i)
            if next is None:
                break
            if row[i] == 0:
                row[i] = row[next]
                row[next] = 0
                next = get_next(row, i)
                if next is None:
                    break

            if row[i] == row[next]:
                row[i] += row[next]
                row[next] = 0

    return board


def rotate_clockwise(board: List[List[int]]) -> List[List[int]]:
    return list(map(list, (zip(*board[::-1]))))


def rotate_counterclockwise(board: List[List[int]]) -> List[List[int]]:
    return list(map(list, (zip(*board))))[::-1]


def rotate_180(board: List[List[int]]) -> List[List[int]]:
    return [row[::-1] for row in board[::-1]]


def solve(board: List[List[int]], move: Move) -> List[List[int]]:
    # Rotate board so that the move is left
    if move == Up:
        board = rotate_counterclockwise(board)
    elif move == Right:
        board = rotate_180(board)
    elif move == Down:
        board = rotate_clockwise(board)

    # Move tiles left
    board = move_left(board)

    # Rotate board back
    if move == Up:
        board = rotate_clockwise(board)
    elif move == Right:
        board = rotate_180(board)
    elif move == Down:
        board = rotate_counterclockwise(board)

    return board


def main():
    ans: List[List[int]] = solve(*parse())
    for row in ans:
        print(*row)


if __name__ == '__main__':
    main()
