#

from typing import List, Optional


def parse1() -> int:
    return int(input())

def solve1(n: int) -> Optional[List[int]]:
    ans: List[int] = []
    while n > 1:
        if n % 2 == 0:
            return None
        n_1: int = (n+1)//2
        n_2: int = (n-1)//2

        if n_1 % 2 == 0:
            ans.append(2)
            n = n_2
        else:
            ans.append(1)
            n = n_1

    ans.reverse()
    return ans


def main():
    t: int = int(input())
    for _ in range(t):
        ans: Optional[List[int]] = solve1(parse1())
        if ans is None:
            print(-1)
        else:
            print(len(ans))
            print(*ans, sep=' ')


if __name__ == '__main__':
    main()
