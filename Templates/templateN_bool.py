#

def parse1():
    pass

def solve1() -> bool:
    pass

def main():
    t: int = int(input())
    for _ in range(t):
        if solve1(*parse1()):
            print("Yes")
        else:
            print("No")


if __name__ == '__main__':
    main()
