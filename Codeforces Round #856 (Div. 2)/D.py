# https://codeforces.com/contest/1794/problem/D

from math import factorial, prod
from typing import Dict, List, Tuple

mod: int = 998244353

def parse() -> Tuple[int, List[int]]:
    n = int(input())
    return n, list(map(int, input().split()))

def primes_until(n: int) -> List[bool]:
    res: List[bool] = [True] * (n + 1)
    res[0] = False
    res[1] = False
    for i in range(2, n + 1):
        if res[i]:
            for j in range(i * i, n + 1, i):
                res[j] = False

    return res

def factorial_mod(n: int) -> int:
    res: int = 1
    for i in range(2, n + 1):
        res = (res * i) % mod
    return res

def pow_mod(x: int, y: int) -> int:
    res: int = 1
    while y > 0:
        if y % 2 == 1:
            res = (res * x) % mod
        y = y // 2
        x = (x * x) % mod
    return res

def inverse_mod(x: int) -> int:
    return pow_mod(x, mod - 2)

def div_mod(x: int, y: int) -> int:
    res = ((x % mod) * (inverse_mod(y % mod))) % mod
    return res

def prod_mod(it: List[int]) -> int:
    res: int = 1
    for i in it:
        res = (res * i) % mod
    return res

def solve(n: int, As: List[int]) -> int:
    primes: List[bool] = primes_until(10 ** 6)

    As_primes: Dict[int, int] = {}
    As_non_primes: Dict[int, int] = {}
    for a in As:
        if primes[a]:
            if a in As_primes.keys():
                As_primes[a] += 1
            else:
                As_primes[a] = 1
        else:
            if a in As_non_primes.keys():
                As_non_primes[a] += 1
            else:
                As_non_primes[a] = 1

    amount_primes: int = len(As_primes)

    if amount_primes < n:
        return 0

    As_primes_combinations: List[List[float]] = [[0] * (n + 1) for _ in range(amount_primes + 1)]

    factorial_mod_n: int = factorial_mod(n)
    as_primes_amounts: List[int] = list(As_primes.values())
    prod_facts_amounts_non_primes: int = prod_mod([factorial_mod(v) for v in As_non_primes.values()])

    As_primes_combinations[0][0] = div_mod(factorial_mod_n, prod_facts_amounts_non_primes)
    for available_primes in range(1, amount_primes + 1):
        As_primes_combinations[available_primes][0] = div_mod(
            factorial_mod_n,
            prod_facts_amounts_non_primes * factorial_mod(as_primes_amounts[available_primes - 1])
        )

    for needed_primes in range(1, n + 1):
        As_primes_combinations[0][needed_primes] = 0

    for available_primes in range(1, amount_primes + 1):
        for needed_primes in range(1, min(n + 1, available_primes + 1)):
            As_primes_combinations[available_primes][needed_primes] = (
                (div_mod(
                    As_primes_combinations[available_primes - 1][needed_primes - 1],
                    factorial_mod(list(As_primes.values())[available_primes - 1] - 1)
                ) + div_mod(
                    As_primes_combinations[available_primes - 1][needed_primes],
                    factorial_mod(list(As_primes.values())[available_primes - 1])
                )) % mod
            )

    res = As_primes_combinations[amount_primes][n]

    return res



def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
