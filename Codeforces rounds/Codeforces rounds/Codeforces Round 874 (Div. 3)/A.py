# https://codeforces.com/contest/1833/problem/A

def solve1(s: str) -> int:
    d: set[str] = set()
    for i in range(len(s)-1):
        d.add(s[i:i+2])
    return len(d)


def main():
    t: int = int(input())
    for _ in range(t):
        input()
        s: str = input()
        print(solve1(s))


if __name__ == '__main__':
    main()
