# https://codeforces.com/gym/100623

from typing import List


def parse() -> List[str]:
    with open("important.in", "r") as f:
        n = int(f.readline())
        formulas = [""] * n
        for i in range(n):
            formulas[i] = f.readline()
        return formulas


def solve(formulas: List[str]) -> str:
    n = len(formulas)
    pins: List[str] = [''] * n

    for i in range(n):
        pins[i] = [c for c in formulas[i] if c != ' '][0]

    ans: str = "~" + pins[0]
    for i in range(n):
        ans += "|" + pins[i]

    return ans


def main():
    ans = solve(parse())
    with open("important.out", "w") as f:
        f.write("Yes\n")
        f.write(ans + "\n")


if __name__ == '__main__':
    main()
