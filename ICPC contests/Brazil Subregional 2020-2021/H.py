# https://codeforces.com/gym/102861/problem/H


from math import comb


N, K = map(int, input().split())
Ps = list(map(int, input().split()))
A, B = map(int, input().split())

Ps.sort()

def solve(i: int, a: int, b: int, k: int) -> int:
  if k == 0 and a == 0:
    return 1
  elif k == 0 or i == 0 or i < k:
    return 0
  P = Ps[i - 1]
  if (P < a): # Tengo que poner a P
    a -= P
    b -= P
    return solve(i - 1, a, b, k - 1)
  elif P > b: # No puedo poner a P
    return solve(i - 1, a, b, k)
  elif 2 * P < b: # puedo o no ponerlo
    ans = 0
    # Si lo pongo después es libre
    ans += comb(i - 1, k - 1)
    # Si no lo pongo
    ans += solve(i - 1, a, b, k)
    return ans
  else:  # puedo o no ponerlo
    ans = 0
    ans += solve(i - 1, 0, b - P, k - 1) # lo pongo
    ans += solve(i - 1, a, b, k) # no lo pongo
    return ans

ans = solve(N, A, B, K)

print(ans)