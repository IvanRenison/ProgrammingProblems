# https://codeforces.com/gym/101652

from math import floor, sqrt
from typing import Tuple


def parse() -> Tuple[int, int, int]:
    K, P, X = map(int, input().split())
    return K, P, X


def solve(K: int, P: int, X: int) -> float:

    M1: float = floor(sqrt(K*P/X))
    M2: float = M1 + 1

    def cost(M: int) -> float:
        return X*M + K/M * P

    def costprime(M: int) -> float:
        return X - K/(M**2) * P

        """"
            X == K/(M**2) * P
            X/P * M**2 == K
            M**2 == K*P/X
            M == sqrt(K*P/X)
        """

    def costprime2(M: int) -> float:
        return 1 + 2*K/(M**3) * P

    return min(cost(M1), cost(M2))


def main():
    res = solve(*parse())
    print(f"{res:.3f}")


if __name__ == '__main__':
    main()
