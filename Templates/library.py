
from typing import Callable, List, Optional, TypeVar

def my_input() -> Optional[str]:
    try:
        return input()
    except:
        return None

T = TypeVar('T')
def binary_search(f: Callable[[T], bool], it: List[T]) -> int:
    lower: int = 0
    upper: int = len(it)
    while lower + 1 < upper:
        m: int = (lower + upper) // 2
        if f(it[m]):
            lower = m
        else:
            upper = m
    return lower

def primes_until(n: int) -> List[bool]:
    res: List[bool] = [True] * (n + 1)
    res[0] = False
    res[1] = False
    for i in range(2, n + 1):
        if res[i]:
            for j in range(i * i, n + 1, i):
                res[j] = False

    return res