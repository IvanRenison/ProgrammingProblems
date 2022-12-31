
from typing import Callable, List, TypeVar


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
    