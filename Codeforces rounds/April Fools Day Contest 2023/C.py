# https://codeforces.com/contest/1812/problem/C

from math import prod


pi = "31415926535897932384626433832795028841971693993751"

t = int(input())

for i in range(t):
    n = int(pi[i])
    xs = [int(input()) for _ in range(n)]
    ans = prod(xs)
    print(ans)

