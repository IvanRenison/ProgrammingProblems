# https://codeforces.com/contest/1761/problem/B

from typing import Callable, Final, List, TypeVar


T = TypeVar('T')


def list_func_index(lst: list[T], func: Callable[[T], bool]) -> int | None:
    for i in range(len(lst)):
        if func(lst[i]):
            return i
    return None


def solve1(a: List[int]) -> int:
    n: int = len(a)
    res: int = 0
    while n > 1:
        for i in range(n):
            if a[(i-1) % n] == a[(i+1) % n]:
                i = (i+1) % n
            else:
                break
        else:
            min_lost: int = n+1
            min_lost_i: int | None = None
            for i in range(n):
                amount_lost: int = list_func_index(
                    list(reversed(a[i:])) + list(reversed([]
                                                          if i == 0 else a[:(i-1) % n])),
                    (lambda x: x == a[i])
                ) + list_func_index(
                    (a[:(i-1) % n] + ([] if i == 0 else a[i:])),
                    (lambda x: x == a[i])
                )
                if amount_lost < min_lost:
                    min_lost = amount_lost
                    min_lost_i = i
            i = min_lost_i
        a.pop(i)
        n -= 1
        i = i % n
        while n > 1 and a[(i-1) % n] == a[i]:
            a.pop(i)
            n -= 1
            i = (i-1) % n
        while n > 1 and a[(i-2) % n] == a[(i-1) % n]:
            a.pop((i-1) % n)
            n -= 1
            i = (i-1) % n
        res += 1

    return res + 1


def parse1() -> List[int]:
    _ = input()
    return list(map(int, input().split()))


def main():
    t = int(input())
    for _ in range(t):
        a = parse1()
        res: int = solve1(a)
        print(res)


if __name__ == '__main__':
    main()
