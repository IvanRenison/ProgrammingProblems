# https://codeforces.com/contest/1775/problem/E

import io, os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def solve1(As: list[int]) -> int:
    n: int = len(As)

    pre_sums: list[int] = [0] * (n + 1)

    for i in range(n):
        pre_sums[i + 1] = pre_sums[i] + As[i]

    ans: int = max(pre_sums) - min(pre_sums)

    return ans

def main():
    t: int = int(input())
    for _ in range(t):
        input()

        As: list[int] = list(map(int, input().split()))

        ans = solve1(As)
        print(ans)


if __name__ == '__main__':
    main()
