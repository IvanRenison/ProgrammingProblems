# https://codeforces.com/gym/103960/problem/F

from typing import List, Tuple


def solve(words: List[str]) -> Tuple[str, int]:
    N: int = len(words)

    indexes: List[int] = [word.find('*') for word in words]
    candidates: List[str] = [
        words[i][:indexes[i]] + c + words[i][indexes[i]+1:] for i in range(N) for c in "abcdefghijklmnopqrstuvwxyz"]

    # Count compatibilities
    compatibilities: List[int] = [0] * len(candidates)
    for i, candidate in enumerate(candidates):
        for j in range(N):
            if candidate[:indexes[j]] == words[j][:indexes[j]] and candidate[indexes[j]+1:] == words[j][indexes[j]+1:]:
                compatibilities[i] += 1

    max_compatibilities: int = max(compatibilities)
    max_compatibilities_candidates: List[str] = [
        candidates[i] for i in range(len(candidates)) if compatibilities[i] == max_compatibilities]

    max_compatibilities_candidates.sort()
    return max_compatibilities_candidates[0], max_compatibilities

def parse() -> List[str]:
    N, _ = map(int, input().split())
    return [input() for _ in range(N)]


def main():
    words = parse()
    res = solve(words)
    print(*res)


if __name__ == '__main__':
    main()
