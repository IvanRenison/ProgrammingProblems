# https://open.kattis.com/problems/funhouse

from typing import List, Literal, Optional, Tuple

Alphabet = Literal['*', 'x', '.', '/', '\\', '&']


def parse1() -> Optional[List[List[Alphabet]]]:
    W, L = map(int, input().split())
    if W == 0 and L == 0:
        return None
    else:
        return [list(input()) for _ in range(L)]


def find_start(room: List[List[Alphabet]]) -> Tuple[int, int]:
    L = len(room)
    W = len(room[0])
    for j in range(W):
        if room[0][j] == '*':
            return j, 0
    for i in range(1, L - 1):
        if room[i][0] == '*':
            return 0, i
        elif room[i][W - 1] == '*':
            return W - 1, i
    for j in range(W):
        if room[L - 1][j] == '*':
            return j, L - 1


def solve1(room: List[List[Alphabet]]) -> Tuple[int, int]:
    L = len(room)
    W = len(room[0])

    x_start, y_start = find_start(room)

    x_direction, y_direction = 0, 0
    if x_start == 0:
        x_direction = 1
    elif x_start == L - 1:
        x_direction = -1
    elif y_start == 0:
        y_direction = 1
    elif y_start == W - 1:
        y_direction = -1

    x, y = x_start, y_start

    x += x_direction
    y += y_direction

    while x != 0 and x != W - 1 and y != 0 and y != L - 1:
        if room[y][x] == '/':
            if x_direction == 0:
                x_direction = -y_direction
                y_direction = 0
            else:
                y_direction = -x_direction
                x_direction = 0
        elif room[y][x] == '\\':
            if x_direction == 0:
                x_direction = y_direction
                y_direction = 0
            else:
                y_direction = x_direction
                x_direction = 0
        x += x_direction
        y += y_direction

    return x, y


def output1(room: List[List[Alphabet]], x: int, y: int) -> None:
    room[y][x] = '&'
    for line in room:
        print(''.join(line))


def main():
    for i in range(1, 41):
        room = parse1()
        if room is None:
            break
        else:
            print(f"HOUSE {i}")
            output1(room, *solve1(room))


if __name__ == '__main__':
    main()
