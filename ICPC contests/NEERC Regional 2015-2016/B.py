# https://codeforces.com/gym/100851

import sys

def solve(n: int) -> int:
  s: list[tuple[int, int]] = [(0, 0)]
  ten_pow = 1
  i = 1
  while len(s) <= n:
    new_s: list[tuple[int, int]] = []

    for x, l in s:
      valid: bool = True
      for j in range(l, i):
        if x & (1 << j):
          valid = False
          break

      if valid:
        new_s.append((x + ten_pow, i))

    for x in new_s:
      s.append(x)

    ten_pow *= 10
    i += 1

  return s[n][0]

# for n in range(30):
#   ans = solve(n)
#   print(f"{n = }, {ans = }, {ans:b}")

sys.stdin = open('binary.in', 'r')
sys.stdout = open('binary.out', 'w')

n = int(input())
ans = solve(n)
print(ans)
