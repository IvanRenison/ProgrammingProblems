# https://codeforces.com/gym/103640/problem/I

from typing import List, Literal, Tuple


WDay = Literal[0, 1, 2, 3, 4, 5, 6]

def parse() -> Tuple[WDay, List[int]]:
    wday, _ = input().split()
    wday = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"].index(wday)
    return wday, [int(x) for x in input().split()]

def solve(wday: WDay, Ds: List[int]) -> int:

    def amount_day_to_get(D: int) -> int:
        D_wday: WDay = (wday - D) % 7

        while D_wday != 0 and D > 30 and (D_wday != 4 or D > 31) and (D_wday != 3 or D > 32):
            D -= 30
            D_wday = (D_wday + 30) % 7
            if D_wday == 5:
                D_wday = 0
                D -= 2
            elif D_wday == 6:
                D_wday == 0
                D -= 1

        D = D % 91

        while D > 30 and (D_wday != 4 or D > 31) and (D_wday != 3 or D > 32):
            D -= 30
            D_wday = (D_wday + 30) % 7
            if D_wday == 5:
                D_wday = 0
                D -= 2
            elif D_wday == 6:
                D_wday == 0
                D -= 1

        ans = 30 - D

        r_wday = (D_wday + 30) % 7
        if r_wday == 5:
            ans += 2
        elif r_wday == 6:
            ans += 1

        assert 0 <= ans <= 32

        return ans

    Ts = [amount_day_to_get(D) for D in Ds]

    return min(Ts)

def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
