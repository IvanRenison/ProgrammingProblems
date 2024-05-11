# https://open.kattis.com/problems/mastermind

from typing import List, Tuple


def parse() -> Tuple[str, str]:
    _, code, guess = input().split()
    return code, guess


def solve(code: str, guess: str) -> Tuple[int, int]:
    n: int = len(code)
    corrects: List[int] = []

    for i in range(n):
        if code[i] == guess[i]:
            corrects.append(i)

    code_ = [c for i, c in enumerate(code) if i not in corrects]
    guess_ = [g for i, g in enumerate(guess) if i not in corrects]

    r: int = len(corrects)
    s: int = 0
    for c in code_:
        if c in guess_:
            s += 1
            guess_.remove(c)

    return r, s


def main():
    print(*solve(*parse()))


if __name__ == '__main__':
    main()
