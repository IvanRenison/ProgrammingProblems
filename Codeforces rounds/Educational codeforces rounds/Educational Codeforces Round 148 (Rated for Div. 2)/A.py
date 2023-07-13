# https://codeforces.com/contest/1832/problem/A

def parse1():
    return input()


def solve1(s: str) -> bool:
    if len(s) % 2 == 0:
        c: str = s[0]
        for x in s:
            if x != c:
                return True
        return False
    else:
        n = len(s)
        c: str = s[0]
        for i in range(n):
            x = s[i]
            if (i != (n)//2) and x != c:
                return True
        return False


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
