# https://codeforces.com/contest/1775/problem/B

def solve1(pss: list[list[int]]) -> bool:
    d: dict[int, int] = {}

    for ps in pss:
        for p in ps:
            if p not in d:
                d[p] = 1
            else:
                d[p] += 1

    for ps in pss:
        found_unique: bool = False
        for p in ps:
            if d[p] == 1:
                found_unique = True
                break

        if not found_unique:
            return True

    return False

def main():
    t: int = int(input())
    for _ in range(t):
        n: int = int(input())
        pss: list[list[int]] = [list(map(int, input().split()))[1:] for _ in range(n)]

        if solve1(pss):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
