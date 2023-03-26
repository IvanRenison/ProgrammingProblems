# https://codeforces.com/gym/101652

from typing import List, Optional


def parse1() -> Optional[List[List[str]]]:
    try:
        n = int(input())
        return [list(input()) for _ in range(n)]
    except:
        return None


def solve1(arr: List[List[str]]):
    n = len(arr)
    for i in range(n):
        if len(set(arr[i])) != n:
            return 'No'

    for j in range(n):
        if len(set(arr[i][j] for i in range(n))) != n:
            return 'No'

    if (arr[0] == list("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")[:n]
            and [arr[i][0] for i in range(n)] == list("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")[:n]):
        return "Reduced"

    return "Not Reduced"


def main():
    while True:
        x = parse1()
        if x is None:
            break
        else:
            print(solve1(x))


if __name__ == '__main__':
    main()
