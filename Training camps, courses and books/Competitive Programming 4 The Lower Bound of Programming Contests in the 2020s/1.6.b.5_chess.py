# https://open.kattis.com/problems/chess

from typing import List, Literal, Optional, Tuple

Position1D = Literal[1, 2, 3, 4, 5, 6, 7, 8]
Position = Tuple[Position1D, Position1D]


def parse1() -> Tuple[Position, Position]:
    X1, Y1, X2, Y2 = input().split()
    X1 = ord(X1) - ord('A') + 1
    X2 = ord(X2) - ord('A') + 1
    Y1 = int(Y1)
    Y2 = int(Y2)

    return (X1, Y1), (X2, Y2)


def same_diagonal(pos1: Position, pos2: Position) -> bool:
    X1, Y1 = pos1
    X2, Y2 = pos2

    return abs(X1 - X2) == abs(Y1 - Y2)


def common_position(pos1: Position, pos2: Position) -> Position:
    """
        Find res such than same_diagonal(pos1, res) and same_diagonal(pos2, res)
    """
    assert (pos1 != pos2 and not same_diagonal(pos1, pos2))

    for X_res in range(1, 9):
        for Y_res in range(1, 9):
            res = (X_res, Y_res)
            if same_diagonal(pos1, res) and same_diagonal(pos2, res):
                return res

    return None


"""     X1, Y1 = pos1
    X2, Y2 = pos2

    X_diff = abs(X1 - X2)
    Y_diff = abs(Y1 - Y2)

    diffs_diff = abs(X_diff - Y_diff)

    if Y1 == Y2:
        X_res = (X1 + X2) // 2
        Y_res = Y1 - X_diff // 2
    else:
        if X2 < X1:
            X1, Y1, X2, Y2 = X2, Y2, X1, Y1

        if X_diff > Y_diff:
            if Y1 < Y2:
                X_res = X1 - diffs_diff
                Y_res = Y1 + diffs_diff
            else:
                X_res = X2 - diffs_diff
                Y_res = Y2 - diffs_diff
        else:
            if Y1 < Y2:
                X_res = X2 + diffs_diff
                Y_res = Y2 - diffs_diff
            else:
                X_res = X2 + diffs_diff
                Y_res = Y2 + diffs_diff

    return X_res, Y_res """


def solve1(start: Position, end: Position) -> Optional[List[Position]]:
    X1, Y1 = start
    X2, Y2 = end

    if (X1 % 2 == Y1 % 2) != (X2 % 2 == Y2 % 2):
        return None
    elif start == end:
        return [start]
    elif same_diagonal(start, end):
        return [start, end]
    else:
        return [start, common_position(start, end), end]


def main():
    t: int = int(input())
    for _ in range(t):
        res: Optional[List[Position]] = solve1(*parse1())
        if res is None:
            print("Impossible")
        else:
            print(len(res) - 1, end=' ')
            for X, Y in res:
                print(chr(X - 1 + ord('A')), Y, end=' ')
            print()


if __name__ == '__main__':
    main()
