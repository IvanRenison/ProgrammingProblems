# https://codeforces.com/gym/103960/problem/F

from typing import Dict, List, Tuple


def parse() -> List[str]:
    N, C = map(int, input().split())
    return [input()[:C] for _ in range(N)]


def solve(qss: List[str]) -> Tuple[str, int]:
    C: int = len(qss[0])

    words: Dict[str, int] = {}
    for qs in qss:
        j: int = 0
        while j < C and qs[j] != '*':
            j += 1

        for c_ in range(26):
            c: str = chr(ord('a') + c_)

            qs_: str = qs[:j] + c + qs[j+1:]
            if qs_ not in words:
                words[qs_] = 0
            words[qs_] += 1

    max_value: int = max(words.values())
    words_max: List[str] = [w for w, v in words.items() if v == max_value]

    return min(words_max), max_value


def main():
    print(*solve(parse()), sep=' ')


if __name__ == '__main__':
    main()
