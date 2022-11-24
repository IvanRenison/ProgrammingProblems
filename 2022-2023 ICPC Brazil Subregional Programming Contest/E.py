# https://codeforces.com/gym/103960/problem/E

def solve(Hs):
    flechas: list[int] = [0 for _ in range(1,10**6 + 1)]

    res = 0
    for H in Hs:
        if flechas[H-1] >= 1:
            flechas[H-1] -= 1


            if H-1 != 0:
                flechas[H-2] += 1
        else:
            flechas[H-2] += 1
            res += 1

    return res





def main():
    N = int(input())
    line = input()
    Hs = list(map(int, line.split(' ')))

    print(solve(Hs))




if __name__ == '__main__':
    main()


