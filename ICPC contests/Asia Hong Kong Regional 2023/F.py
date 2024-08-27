# https://codeforces.com/gym/104172/problem/F

import sys

sys.set_int_max_str_digits(int(2e5 + 1))


def pop_count(x: int) -> int:
  ans = 0
  while x > 0:
    ans += x & 1
    x >>= 1
  return ans

def solve(s: str, k: int) -> int:
  n = len(s)
  sz_ = n // (k + 1)

  dp: list[list[int]] = [[-1] * (k + 2) for _ in range(n + 1)]
  dp[0][0] = 0
  for i in range(1, n + 1):
    for j in range(1, min(i + 1, k + 2)):
      for sz in range(max(sz_ - 1, 1), sz_ + 3):
        if i - sz >= 0 and dp[i - sz][j - 1] != -1:
          this_ans = dp[i - sz][j - 1] + int(s[i - sz:i])
          if dp[i][j] == -1 or this_ans < dp[i][j]:
            dp[i][j] = this_ans

  return dp[n][k + 1]


def force(s: str, k: int) -> int:
  n = len(s)
  ans = int(s)
  for x in range(2**(n - 1)):
    if pop_count(x) == k:
      t: list[str] = ['']
      for i in range(n):
        t[-1] += s[i]
        if (x >> i) & 1:
          t.append('')
      this_ans = sum(map(int, t))
      ans = min(ans, this_ans)
  return ans


T = int(input())

for _ in range(T):
  n, k = map(int, input().split())
  s = input()

  ans = solve(s, k)

  print(ans)


"""
for n in range(2, int(2e5+1)):
  for k in range(1, min(n, 7)):
    s = '1' * n
    print(n, k)
    ans = solve(s, k)
"""

"""
from random import randint

for _ in range(1000):
  n = randint(2,13)
  k = randint(1, min(n - 1, 6))
  s = ''.join([str(randint(1, 9)) for _ in range(n)])

  ans = solve(s, k)
  ansf = force(s, k)
  if ans != ansf:
    print(n, k)
    print(s)
    print(ans, ansf)
    exit(1)
"""





