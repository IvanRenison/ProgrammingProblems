# https://codeforces.com/contest/231/problem/A


def main():

    n: int = int(input())

    ans: int = 0

    for _ in range(n):
        a, b, c = map(int, input().split())
        if a + b + c >= 2:
            ans += 1

    print(ans)


if __name__ == '__main__':
    main()
