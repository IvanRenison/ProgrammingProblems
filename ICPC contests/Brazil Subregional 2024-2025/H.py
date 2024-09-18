# https://codeforces.com/gym/105327/problem/H

"""
import random


M: list[str] = []
for _ in range(500):
  if random.randint(0, 1) == 0:
    M.append('1')
  else:
    M.append('0')

print(*M, sep='')
exit(0)

 """

def solve(M: list[str], N: list[str]) -> int:

  M_missing: list[int] = []
  for i, c in enumerate(M):
    if c == '*':
      M_missing.append(i)
  N_missing: list[int] = []
  for i, c in enumerate(N):
    if c == '*':
      N_missing.append(i)

  for x in range(1 << len(M_missing)):
    M_ = M
    for i in range(len(M_missing)):
      if x & (1 << i):
        M_[M_missing[i]] = '1'
      else:
        M_[M_missing[i]] = '0'
    M_int: int = 0
    for i, c in enumerate(M_):
      M_int <<= 1
      if c == '1':
        M_int += 1

    for x in range(1 << len(N_missing)):
      N_ = N
      for i in range(len(N_missing)):
        if x & (1 << i):
          N_[N_missing[i]] = '1'
        else:
          N_[N_missing[i]] = '0'
      N_int: int = 0
      for i, c in enumerate(N_):
        N_int <<= 1
        if c == '1':
          N_int += 1

      if M_int % N_int == 0:
        return M_int

  assert(False)


M = input()
N = input()


ans = solve(list(M), list(N))
ans_s = ""
for _ in range(len(M)):
  if ans & 1:
    ans_s += "1"
  else:
    ans_s += '0'
  ans >>= 1


for c in reversed(ans_s):
  print(c, end='')
print()


