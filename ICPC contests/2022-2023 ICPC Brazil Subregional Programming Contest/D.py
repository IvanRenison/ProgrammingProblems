# https://codeforces.com/gym/103960/problem/D

def solve(n: int, x: int, y: int) -> int:
    res: int = 0
    while x != 2**(n-1):
        if x < 2**(n-1):
            res += 1
            x = 2*x
        else:
            x = 2**n - x
    return res


def main():
    n, x, y = map(int, input().split(' '))
    print(solve(n, x, y))


if __name__ == '__main__':
    main()
