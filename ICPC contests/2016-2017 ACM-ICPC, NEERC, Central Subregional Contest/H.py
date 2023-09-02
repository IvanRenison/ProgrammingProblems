# https://codeforces.com/gym/101243

import sys
sys.stdin = open("input.txt", "r")
sys.stdout = open("output.txt", "w")


n = int(input())

ans = 8

for i in range(2, min(n+1,10)):
    ans *= 9

if (n >= 10):
    for i in range(10, n+1):
        ans *= 10

print(ans)
