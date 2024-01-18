# https://codeforces.com/gym/101652

def parse():
    return input()


def solve(s: str):
    for i in range(1, len(s)):
        if (s[i] == s[i-1]):
            return "Or not."

    return "Odd."


def main():
    print(solve(parse()))


if __name__ == '__main__':
    main()
