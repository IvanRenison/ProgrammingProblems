# https://codeforces.com/contest/1731/problem/B

def solve1(n: int) -> int:
    ans: int = n*(n+1)*(2*n+1)//6 + (n-1)*(n)*(2*n-1)//6 + (n-1)*n//2
    return ans * 2022 % 1000000007


def parse1() -> int:
    return (int(input()))


def main():
    t: int = int(input())
    for _ in range(t):
        print(solve1(parse1()))


if __name__ == '__main__':
    main()
