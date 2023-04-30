# https://codeforces.com/gym/101652

from typing import List
from math import ceil


def parse():
    return input()


def solve(S: int) -> List:
    res: List = []
    x = ceil(S/2) + 1

    for i in range(2, x):
        if S % (i + i-1) == 0:
            res.append((i, i-1))
        elif S % (i + i-1) == i:
            res.append((i, i-1))
        if S % i == 0:
            res.append((i, i))

    return res


def main():
    S = parse()
    res: List = solve(int(S))
    print(S + ":")

    for t in res:
        print(*t, sep=",")


if __name__ == '__main__':
    main()

# S = x * r + y * g

# x = (S - y * g)/r
# y =(S - x * r)/g

# S = (Estrellas en primer fila + Estrellas en la segunda fila) * Numero de filas/2
