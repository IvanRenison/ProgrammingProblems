#

# Function that determines if a number has an odd or even amount of divisors
from typing import List


def has_even_divisors(n: int) -> bool:
    sqrt_n = n**0.5
    return n != 0 and sqrt_n != int(sqrt_n)

def solve1(As: List[int]) -> int:
    n: int = len(As)
    ans: int = n*(n+1)//2

    partial_XORs: List[int] = [0]
    amount_XORs: List[int] = [0] * (2*n+1)
    amount_XORs[0] += 1

    for i in range(n):
        a: int = As[i]
        new_XOR: int = partial_XORs[-1] ^ a
        partial_XORs.append(new_XOR)

        amount_XORs[new_XOR] += 1

    for i in range(2*n+1):
        j: int = 0
        while j*j < 2*n+1:
            if i ^ j*j < 2*n+1:
                if i < i ^ j*j:
                    ans -= amount_XORs[i] * amount_XORs[i ^ j*j]
                elif i == i ^ j*j:
                    ans -= amount_XORs[i] * (amount_XORs[i] - 1)//2

            j += 1

    return ans

def parse1() -> List[int]:
    input()
    return (list(map(int, input().split())))

def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()


