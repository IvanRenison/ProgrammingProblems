# https://codeforces.com/gym/103640/problem/J

from random import randint
from typing import List, Tuple


def parse() -> Tuple[int, int, List[Tuple[int, int, int, int]]]:
    W, H = map(int, input().split())
    N = int(input())
    res: List[Tuple[int, int, int, int]] = [tuple(map(int, input().split())) for _ in range(N)]

    return W, H, res

def intersect(L1: Tuple[int, int], L2: Tuple[int, int]) -> bool:
    """
        Check if two segments intersect
    """
    L1_A1, L1_A2 = L1
    L2_A1, L2_A2 = L2

    if L1_A1 > L1_A2:
        L1_A1, L1_A2 = L1_A2, L1_A1

    if L2_A1 > L2_A2:
        L2_A1, L2_A2 = L2_A2, L2_A1


    if L1_A1 < L2_A1 < L1_A2:
        return L2_A2 > L1_A2 or L2_A2 < L1_A1

    if L1_A1 < L2_A2 < L1_A2:
        return L2_A1 > L1_A2 or L1_A2 < L1_A1

    else:
        return False



def solve_only_borders(points: List[Tuple[int, int]]) -> bool:
    if len(points) == 0:
        return True

    L1_A1, L1_A2 = points.pop(randint(0, len(points) - 1))

    points_part1: List[Tuple[int, int]] = []
    points_part2: List[Tuple[int, int]] = []

    for L_A1, L_A2 in points:
        if intersect((L1_A1, L1_A2), (L_A1, L_A2)):
            return False
        elif L1_A1 < L_A1 < L1_A2:
            points_part1.append((L_A1, L_A2))
        else:
            points_part2.append((L_A1, L_A2))

    return solve_only_borders(points_part1) and solve_only_borders(points_part2)




def solve(W: int, H: int, points: List[Tuple[int, int, int, int]]) -> bool:

    def in_border(X: int, Y: int) -> bool:
        return X == 0 or X == W or Y == 0 or Y == H

    def convert_to_border(X: int, Y: int) -> int:
        if Y == 0:
            return X
        elif X == W:
            return W + Y
        elif Y == H:
            return W + H + (W - X)
        else:
            return W + H + W + (H - Y)

    border_points: List[Tuple[int, int]] = [
        (convert_to_border(X1, Y1), convert_to_border(X2, Y2))
        for X1, Y1, X2, Y2 in points if in_border(X1, Y1) and in_border(X2, Y2)
    ]

    return solve_only_borders(border_points)



def main():
    print('Y' if solve(*parse()) else 'N')


if __name__ == '__main__':
    main()
