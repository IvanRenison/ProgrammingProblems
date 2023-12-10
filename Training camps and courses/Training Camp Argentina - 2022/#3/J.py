# https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/J

def solve(s: str) -> int:
    n = len(s)

    best_doubleing = None

    i = 1
    while 2*i <= n:
        if s[0:i] + s[0:i] == s[0:2*i]:
            best_doubleing = i
        i += 1

    if best_doubleing == None:
        return n
    else:
        return n - best_doubleing + 1


def main():
    input()
    s = input()

    print(solve(s))


main()
