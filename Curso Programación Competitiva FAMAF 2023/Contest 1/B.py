# https://codeforces.com/group/id8eYTCwzg/contest/437948/problem/B

def parse1():
    input()
    return input(), input()


def solve1(xs, ys) -> bool:
    n = len(xs)
    for i in range(n):
        x = xs[i]
        y = ys[i]
        if (x == 'R' and y != 'R') or (x != 'R' and y == 'R'):
            return False

    return True


def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
