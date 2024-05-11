# https://open.kattis.com/problems/guessinggame

from typing import List, Literal, Optional, Tuple


Guess = Literal[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Response = Literal["too high", "too low", "right on"]


def parse1() -> Optional[List[Tuple[Guess, Response]]]:
    guess: int = int(input())
    if guess == 0:
        return None
    response: str = input()

    ans = [(guess, response)]
    while response != "right on":
        guess = int(input())
        response = input()
        ans.append((guess, response))

    return ans


Ans = Literal["Stan is dishonest", "Stan may be honest"]


def solve1(round: List[Tuple[Guess, Response]]) -> Ans:
    min_: Guess = 1
    max_: Guess = 10

    for guess, response in round:
        if response == "too high":
            max_ = min(max_, guess - 1)
        elif response == "too low":
            min_ = max(min_, guess + 1)
        elif max_ < guess or min_ > guess:
            return "Stan is dishonest"

        if min_ > max_:
            return "Stan is dishonest"

    return "Stan may be honest"


def main():
    while True:
        round = parse1()
        if round is None:
            break
        else:
            print(solve1(round))


if __name__ == '__main__':
    main()
