# https://codeforces.com/contest/282/problem/A


def main():

    n: int = int(input())

    x: int = 0

    for _ in range(n):
        s: str = input()
        if s[1] == '+':
            x += 1
        else:
            x -= 1

    print(x)


if __name__ == '__main__':
    main()
