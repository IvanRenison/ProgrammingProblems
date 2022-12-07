# https://codeforces.com/contest/1761/problem/A

def solve1(n: int, a: int, b: int) -> bool:
    return (a == b and b == n) or (a + b + 1 < n)


def main():
    t = int(input())
    for _ in range(t):
        n, a, b = map(int, input().split())
        res: bool = solve1(n, a, b)
        print('Yes' if res else 'No')


if __name__ == '__main__':
    main()
