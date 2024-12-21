# https://codeforces.com/contest/1663/problem/E
n = int(input())

l: list[list[str]] = []
for _ in range(n):
    l.append([])
    s = input()
    for c in s:
        l[-1].append(c)

word = "theseus"
w = len(word)

ans = False

for i in range(n - w + 1):
    for j in range(n - w + 1):
        wo0 = ""
        wo1 = ""
        wo2 = ""
        for k in range(w):
            wo0 += l[i + k][j]
            wo1 += l[i][j + k]
            wo2 += l[i + k][j + k]

        if wo0 == word or wo1 == word or wo2 == word:
            ans = True
            break


print("YES" if ans else "NO")
