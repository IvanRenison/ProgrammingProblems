# https://codeforces.com/contest/1837/problem/A

from typing import List, Tuple


def parse1() -> Tuple[int, int]:
    return tuple(map(int, input().split()))

def solve1(x: int, k: int) -> List[int]:
    if x % k != 0:
        return [x]
    elif (x - 1) % k != 0:
        return [x-1, 1]
    elif k != 2:
        return [x-2, 2]
    else:
        return [x-3, 3]

def main():
    t: int = int(input())
    for _ in range(t):
        ans = solve1(*parse1())
        print(len(ans))
        print(*ans)


if __name__ == '__main__':
    main()
