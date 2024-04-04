# https://codeforces.com/contest/166/problem/A

from functools import cmp_to_key

def cmp(a: tuple[int, int], b: tuple[int, int]) -> int:
    pa, ta = a
    pb, tb = b

    if pa > pb or (pa == pb and ta < tb):
        return -1
    elif pa == pb and ta == tb:
        return 0
    else:
        return 1


def solve(pts: list[tuple[int, int]], k: int) -> int:
    pts = sorted(pts, key=cmp_to_key(cmp))

    pk, tk = pts[k - 1]

    ans: int = 0

    for p, t in pts:
        if p == pk and t == tk:
            ans += 1

    return ans


def main():

    n, k = map(int, input().split())
    pts: list[tuple[int, int]] = []
    for _ in range(n):
        pts.append(tuple(map(int, input().split())))

    ans: int = solve(pts, k)
    print(ans)


if __name__ == '__main__':
    main()
