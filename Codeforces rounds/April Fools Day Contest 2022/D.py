# https://codeforces.com/contest/1663/problem/D
s = input()
n = int(input())

ans = False
if s == "ABC":
    ans = n <= 1999
elif s == "ARC":
    ans = n <= 2799
else:
    ans = 1200 <= n

if ans:
    print("YES")
else:
    print("NO")
