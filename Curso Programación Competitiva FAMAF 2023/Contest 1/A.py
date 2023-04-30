# https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/A

def parse():
    return int(input())


def solve(x):
    ans = "I hate that I love that " * ((x - 1) // 2)
    if x % 2 == 0:
        ans += "I hate that I love it"
    else:
        ans += "I hate it"
    return ans


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
