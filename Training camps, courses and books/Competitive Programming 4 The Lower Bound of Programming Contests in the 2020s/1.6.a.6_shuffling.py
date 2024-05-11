# https://open.kattis.com/problems/shuffling

import math
from typing import List, Literal, Tuple, TypeVar

ShuffleType = Literal["in", "out"]


def parse() -> Tuple[int, ShuffleType]:
    N, shuffle_type = input().split()
    N: int = int(N)
    return N, shuffle_type


T = TypeVar('T')
def shuffle(shuffle_type: ShuffleType, xs: List[T]) -> List[T]:
    n: int = len(xs)
    middle: int = n // 2 if shuffle_type == "in" else math.ceil(n / 2)
    first_half: List[T] = xs[:middle]
    last_half: List[T] = xs[middle:]

    if shuffle_type == "in":
        shuffle_zip: List[Tuple[T, T]] = list(zip(last_half, first_half))
        ans: List[T] = [card for pair in shuffle_zip for card in pair]
        if n % 2 == 1:
            ans.append(last_half[-1])
    else:
        shuffle_zip: List[Tuple[T, T]] = list(zip(first_half, last_half))
        ans: List[T] = [card for pair in shuffle_zip for card in pair]
        if n % 2 == 1:
            ans.append(first_half[-1])
    return ans


def solve(N: int, shuffle_type: ShuffleType) -> int:
    original: List[int] = list(range(N))
    new: List[int] = shuffle(shuffle_type, original)

    ans: int = 1

    while new != original:
        new = shuffle(shuffle_type, new)
        ans += 1

    return ans


def main():
    print(solve(*parse()))


if __name__ == '__main__':
    main()
