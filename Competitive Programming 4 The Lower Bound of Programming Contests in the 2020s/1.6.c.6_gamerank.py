# https://open.kattis.com/problems/gamerank

from typing import Dict, List, Literal, Tuple

MatchResult = Literal['L', 'W']


def parse() -> List[MatchResult]:
    return list(input())


Legend = 0

Rank = Literal[0,
               1, 2, 3, 4, 5, 6, 7, 8, 9,
               10, 11, 12, 13, 14, 15, 16, 17, 18,
               19, 20, 21, 22, 23, 24, 25
               ]

rank_stars: Dict[Rank, int] = {
    25: 2, 24: 2, 23: 2, 22: 2, 21: 2,
    20: 3, 19: 3, 18: 3, 17: 3, 16: 3,
    15: 4, 14: 4, 13: 4, 12: 4, 11: 4,
    10: 5, 9: 5, 8: 5, 7: 5, 6: 5, 5: 5, 4: 5, 3: 5, 2: 5, 1: 5,
    0: 20000
}


class GameStatus:
    rank: Rank
    stars: int
    streak: int

    def __init__(self):
        self.rank = 25
        self.stars = 0
        self.streak = 0

    def win(self):
        self.stars += 1
        self.streak += 1
        if self.streak >= 3 and self.rank > 5:
            self.stars += 1

        if self.stars > rank_stars[self.rank]:
            self.stars -= rank_stars[self.rank]
            self.rank -= 1

    def lose(self):
        self.streak = 0

        if 0 < self.rank and self.rank <= 20:
            self.stars -= 1
            if self.stars < 0:
                if self.rank < 20:
                    self.rank += 1
                    self.stars = rank_stars[self.rank] - 1
                else:
                    self.stars = 0

    def update(self, mr: MatchResult):
        if mr == 'W':
            self.win()
        else:
            self.lose()


def solve(mrs: List[MatchResult]) -> Rank:
    game_status = GameStatus()

    for mr in mrs:
        game_status.update(mr)

    return game_status.rank


def main():
    res: Rank = solve(parse())
    if res == Legend:
        print('Legend')
    else:
        print(res)


if __name__ == '__main__':
    main()
