# https://redprogramacioncompetitiva.com/contests/2023/13

z, y, x = input().split()


options = [
  x + y + z,
  x + z + y,
  y + x + z,
  y + z + x,
  z + x + y,
  z + y + x
]

nums = [(int(i), i) for i in options]

ans = max(nums)

print(ans[1])

