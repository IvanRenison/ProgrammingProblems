
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


def factorial_mod(n: int, mod: int) -> int:
    res: int = 1
    for i in range(2, n + 1):
        res = (res * i) % mod
    return res

def pow_mod(x: int, y: int, mod: int) -> int:
    res: int = 1
    while y > 0:
        if y % 2 == 1:
            res = (res * x) % mod
        y = y // 2
        x = (x * x) % mod
    return res

def inverse_mod_p(x: int, mod: int) -> int:
    return pow_mod(x, mod - 2)

def div_mod_p(x: int, y: int, mod: int) -> int:
    res = ((x % mod) * (inverse_mod_p(y % mod))) % mod
    return res

def prod_mod(it: List[int], mod: int) -> int:
    res: int = 1
    for i in it:
        res = (res * i) % mod
    return res


# define a class of multiset, using a dict of ints
T = TypeVar('T')
class Multiset:
    def __init__(self, it: List[T] = []):
        self._ms: Dict[T, int] = {}
        for i in it:
            self.add(i)

    def add(self, x: T):
        self._ms[x] = self._ms.get(x, 0) + 1

    def remove(self, x: T):
        self._ms[x] -= 1
        if self._ms[x] == 0:
            del self._ms[x]

    def __len__(self) -> int:
        return sum(self._ms.values())

    def __iter__(self):
        list: List[T] = []
        for i in self._ms:
            list += [i] * self._ms[i]

    def __contains__(self, x: T) -> bool:
        return x in self._ms

    def __str__(self) -> str:
        return str(self._ms)

    def __repr__(self) -> str:
        return repr(self._ms)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Multiset):
            return False
        return self._ms == other._ms

    def __hash__(self) -> int:
        return hash(self._ms)

    def __delitem__(self, x: T):
        self.remove(x)
