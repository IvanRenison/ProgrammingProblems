# https://atcoder.jp/contests/abc309/tasks/abc309_a

def parse():
    return map(int, input().split())

def solve(A: int, B: int) -> bool:
    M = [[1,2,3],[4,5,6],[7,8,9]]

    return (A in M[0] and B in M[0]) or (A in M[1] and B in M[1]) or (A in M[2] and B in M[2])

def main():
    if solve(*parse()):
        print("Yes")
    else:
        print("No")


if __name__ == '__main__':
    main()
