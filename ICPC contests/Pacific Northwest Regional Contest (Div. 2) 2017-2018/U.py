# https://codeforces.com/gym/101652

def parse():
    return tuple(map(float, input().split()))


def solve(vs) -> float:
    avg = sum([(i+1)*vs[i] for i in range(6)])
    diff = abs(3.5 - avg)
    m = max(vs)

    return diff/m


def main():
    res = solve(parse())
    print(f"{res:.3f}")


if __name__ == '__main__':
    main()
