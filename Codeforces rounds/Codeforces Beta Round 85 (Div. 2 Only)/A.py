# https://codeforces.com/contest/112/problem/A

def solve(s: str, t: str) -> int:
    s = s.lower()
    t = t.lower()

    if s < t:
        return -1
    elif s > t:
        return 1
    else:
        return 0


def main():
    s: str = input()
    t: str = input()

    ans: int = solve(s, t)
    print(ans)


if __name__ == '__main__':
    main()
