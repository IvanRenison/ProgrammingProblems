# https://codeforces.com/contest/4/problem/C

def main():

    n: int = int(input())

    m: dict[str, int] = {}

    for _ in range(n):
        name: str = input()
        if name in m:
            print(name + str(m[name]))
            m[name] += 1
        else:
            print('OK')
            m[name] = 1

if __name__ == '__main__':
    main()
