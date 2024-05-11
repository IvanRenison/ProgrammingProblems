# https://open.kattis.com/problems/imageprocessing

from typing import List, Tuple


def parse() -> Tuple[List[List[int]], List[List[int]]]:
    H, _, N, _ = map(int, input().split())
    image: List[List[int]] = [
        [int(x) for x in input().split()] for _ in range(H)]
    kernel: List[List[int]] = [
        [int(x) for x in input().split()] for _ in range(N)]
    return image, kernel


def inner_product(A: List[List[int]], B: List[List[int]]) -> int:
    N: int = len(A)
    M: int = len(A[0])
    ans: int = 0
    for i in range(N):
        for j in range(M):
            ans += A[i][j] * B[i][j]
    return ans


def solve(image: List[List[int]], kernel: List[List[int]]) -> List[List[int]]:
    H: int = len(image)
    W: int = len(image[0])
    N: int = len(kernel)
    M: int = len(kernel[0])

    ans: List[List[int]] = [
        [0 for _ in range(W - M + 1)] for _ in range(H - N + 1)]
    c_kernel: List[List[int]] = [
        [kernel[i][j] for j in range(M-1, -1, -1)] for i in range(N-1, -1, -1)]

    for i in range(H - N + 1):
        for j in range(W - M + 1):
            ans[i][j] = inner_product(
                [image[i + k][j:j + M] for k in range(N)], c_kernel)

    return ans


def main():
    ans: List[List[int]] = solve(*parse())
    for row in ans:
        print(*row)


if __name__ == '__main__':
    main()
