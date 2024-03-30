# https://codeforces.com/contest/1812/problem/I

# Fast input # for string input use input().decode()
# import io, os
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

up = set({'b', 'd', 'f', 'h', 'k', 'l', 't'})
down = set({'g', 'j', 'p', 'q', 'y'})

def solve1(s: str) -> bool:
    count = 0
    for c in s:
        if c in up:
            count += 1
        elif c in down:
            if count == 0:
                return False
            else:
                count -= 1

    return count == 0

def main():
    t: int = int(input())
    for _ in range(t):

        s = input()

        if solve1(s):
            print("YES")
        else:
            print("NO")


if __name__ == '__main__':
    main()
