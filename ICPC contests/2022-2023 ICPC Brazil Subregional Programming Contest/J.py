# https://codeforces.com/gym/103960/problem/J

def solve(N: int, juan_i_0: int, juan_i_1: int, maria_i_0: int, maria_i_1: int, cartas: 'list[int]'):

    ya_salieron: list[int] = [0 for _ in range(0, 14)]
    ya_salieron[juan_i_0] += 1
    ya_salieron[juan_i_1] += 1
    ya_salieron[maria_i_0] += 1
    ya_salieron[maria_i_1] += 1

    puntaje_comun = 0
    for carta in cartas:
        ya_salieron[carta] += 1
        puntaje_comun += min(carta, 10)

    puntaje_juan = min(juan_i_0, 10) + min(juan_i_1, 10) + puntaje_comun
    puntaje_maria = min(maria_i_0, 10) + min(maria_i_1, 10) + puntaje_comun

    if puntaje_juan == puntaje_maria:
        puntaje_necesitado = 23 - puntaje_juan

        if puntaje_necesitado <= 9 and ya_salieron[puntaje_necesitado] < 4:
            return puntaje_necesitado
        elif puntaje_necesitado == 10:
            if ya_salieron[10] < 4:
                return 10
            elif ya_salieron[11] < 4:
                return 10
            elif ya_salieron[12] < 4:
                return 10
            elif ya_salieron[13] < 4:
                return 10
            else:
                return (-1)

        return (-1)

    elif puntaje_juan > puntaje_maria:
        puntaje_necesitado = 23 - puntaje_juan + 1

        if puntaje_necesitado <= 9:
            while puntaje_maria + puntaje_necesitado <= 23:
                if ya_salieron[puntaje_necesitado] < 4:
                    return puntaje_necesitado
                else:
                    puntaje_necesitado += 1

            return (-1)

        elif puntaje_necesitado == 10:
            if ya_salieron[10] < 4:
                return 10
            elif ya_salieron[11] < 4:
                return 10
            elif ya_salieron[12] < 4:
                return 10
            elif ya_salieron[13] < 4:
                return 10
            else:
                return (-1)
        return (-1)

    else:
        puntaje_necesitado = 23 - puntaje_maria

        if puntaje_necesitado <= 9 and ya_salieron[puntaje_necesitado] < 4:
            return puntaje_necesitado
        elif puntaje_necesitado == 10:
            if ya_salieron[10] < 4:
                return 10
            elif ya_salieron[11] < 4:
                return 10
            elif ya_salieron[12] < 4:
                return 10
            elif ya_salieron[13] < 4:
                return 10
            else:
                return (-1)
        return (-1)

    return (-1)


def main():
    N = int(input())
    juan_i = list(map(int, input().split(' ')))
    juan_i_0: int = juan_i[0]
    juan_i_1: int = juan_i[1]
    maria_i = list(map(int, input().split(' ')))
    maria_i_0: int = maria_i[0]
    maria_i_1: int = maria_i[1]
    cartas: list[int] = list(map(int, input().split(' ')))

    print(solve(N, juan_i_0, juan_i_1, maria_i_0, maria_i_1, cartas))


if __name__ == '__main__':
    main()
