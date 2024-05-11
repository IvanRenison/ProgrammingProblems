# https://open.kattis.com/problems/rockpaperscissors

from typing import List, Literal, Optional, Tuple


Play = Literal["rock", "paper", "scissors"]
Game = Tuple[int, Play, int, Play]


def parseGame() -> Game:
    p1, pl1, p2, pl2 = input().split()
    return (int(p1), pl1, int(p2), pl2)


def parse1() -> Optional[Tuple[int, int, List[Game]]]:
    line: str = input()
    if line == "0":
        return None

    n, k = map(int, line.split())
    return n, k, [parseGame() for _ in range(k*n*(n-1)//2)]


def winsTo(pl1: Play, pl2: Play) -> bool:
    return \
        (pl1 == "rock" and pl2 == "scissors") or \
        (pl1 == "paper" and pl2 == "rock") or \
        (pl1 == "scissors" and pl2 == "paper")


def solve1(n: int, k: int, plays: List[Game]) -> List[Optional[float]]:
    wins: List[int] = [0 for _ in range(n)]
    loses: List[int] = [0 for _ in range(n)]
    for p1, pl1, p2, pl2 in plays:
        if winsTo(pl1, pl2):
            wins[p1-1] += 1
            loses[p2-1] += 1
        elif winsTo(pl2, pl1):
            wins[p2-1] += 1
            loses[p1-1] += 1

    return [w/(w+l) if w+l != 0 else None for w, l in zip(wins, loses)]


def main():
    first: bool = True
    while True:
        games = parse1()
        if games is None:
            break
        ans: List[Optional[float]] = solve1(*games)
        if not first:
            print()
        first = False
        for a in ans:
            if a is None:
                print("-")
            else:
                print(f"{a:.3f}")


if __name__ == '__main__':
    main()
