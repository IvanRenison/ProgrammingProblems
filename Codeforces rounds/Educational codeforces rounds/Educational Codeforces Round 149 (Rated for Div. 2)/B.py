# https://codeforces.com/contest/1837/problem/B

def parse1() -> str:
    input()
    return input()


def solve1(s: str) -> int:
    n = len(s)
    last = s[0]
    this_ans = 1
    ans = 0
    for i in range(1, n):
        if s[i] == last:
            this_ans += 1
        else:
            ans = max(ans, this_ans)
            this_ans = 1
        last = s[i]
    ans = max(ans, this_ans)

    return ans + 1


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
