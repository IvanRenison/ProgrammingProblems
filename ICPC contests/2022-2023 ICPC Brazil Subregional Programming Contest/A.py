# https://codeforces.com/gym/103960/problem/A


def solve(str: str):
    res: int = 0

    bs: list[str] = str.split(sep='b')

    bs = list(filter(lambda b: b != '' and b != 'a', bs))
    for b in bs:
        res += len(b)

    return res


def main():
    N = input()
    str = input()
    print(solve(str))


if __name__ == '__main__':
    main()
