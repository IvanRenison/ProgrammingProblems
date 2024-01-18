# https://codeforces.com/gym/103960/problem/I

def solve(xs):
    res = 'S'
    for x in xs:
        if x == 9:
            res = 'F'
            break
    return res


def main():
    line = input()
    xs = list(map(int, line.split(' ')))
    print(solve(xs))


if __name__ == '__main__':
    main()
