# https://codeforces.com/group/5GNF7zti59/contest/534272/problem/K

class myNum:
  x: int
  flag: bool

  def __init__(self, x: int, f: bool = False):
    self.x = x
    self.flag = f

  def __add__(self, o):
    return myNum(self.x + o.x, self.flag or o.flag)

  def __sub__(self, o):
    return myNum(self.x - o.x, self.flag or o.flag)

  def __mul__(self, o):
    return myNum(self.x * o.x, self.flag or o.flag)

  def __floordiv__(self, o):
    if o.x == 0 or self.x % o.x != 0:
      return myNum(self.x, True)
    return myNum(self.x // o.x, self.flag or o.flag)


def valor(s: str) -> int:
  return s.count('(') - 4

def calc(s: str) -> int | None:
  v = eval(s)
  if (not v.flag) and v.x == 24:
    return valor(s)
  return None

def pars(xs: list[int], ops: list[str]):
  x0, x1, x2, x3 = xs
  op0, op1, op2 = ops
  return [
    f"myNum({x0}) {op0} myNum({x1}) {op1} myNum({x2}) {op2} myNum({x3})",
    f"(myNum({x0}) {op0} myNum({x1})) {op1} myNum({x2}) {op2} myNum({x3})",
    f"myNum({x0}) {op0} (myNum({x1}) {op1} myNum({x2})) {op2} myNum({x3})",
    f"myNum({x0}) {op0} myNum({x1}) {op1} (myNum({x2}) {op2} myNum({x3}))",
    f"(myNum({x0}) {op0} myNum({x1}) {op1} myNum({x2})) {op2} myNum({x3})",
    f"myNum({x0}) {op0} (myNum({x1}) {op1} myNum({x2}) {op2} myNum({x3}))",
    f"(myNum({x0}) {op0} myNum({x1})) {op1} (myNum({x2}) {op2} myNum({x3}))",
    f"((myNum({x0}) {op0} myNum({x1})) {op1} myNum({x2})) {op2} myNum({x3})",
    f"(myNum({x0}) {op0} (myNum({x1}) {op1} myNum({x2}))) {op2} myNum({x3})",
    f"myNum({x0}) {op0} ((myNum({x1}) {op1} myNum({x2})) {op2} myNum({x3}))",
    f"myNum({x0}) {op0} (myNum({x1}) {op1} (myNum({x2}) {op2} myNum({x3})))",
  ]

perms = [
  [3, 2, 0, 1],
  [3, 2, 1, 0],
  [3, 0, 2, 1],
  [3, 1, 2, 0],
  [3, 0, 1, 2],
  [3, 1, 0, 2],
  [2, 3, 0, 1],
  [2, 3, 1, 0],
  [0, 3, 2, 1],
  [1, 3, 2, 0],
  [0, 3, 1, 2],
  [1, 3, 0, 2],
  [2, 0, 3, 1],
  [2, 1, 3, 0],
  [0, 2, 3, 1],
  [1, 2, 3, 0],
  [0, 1, 3, 2],
  [1, 0, 3, 2],
  [2, 0, 1, 3],
  [2, 1, 0, 3],
  [0, 2, 1, 3],
  [1, 2, 0, 3],
  [0, 1, 2, 3],
  [1, 0, 2, 3]
]

ops = ["+", "-", "*", "//"]

def perm_val(ps: list[int]):
  ans = 0
  for i in range(4):
    for j in range(i):
      if ps[i] < ps[j]:
        ans += 1
  return ans

xs = list(map(int, input().split()))


ans = 10000000

for ps in perms:
  ps_val = perm_val(ps) * 2
  #print(ps, ps_val)
  for op0 in ops:
    for op1 in ops:
      for op2 in ops:
        ys = [xs[ps[0]], xs[ps[1]], xs[ps[2]], xs[ps[3]]]
        tpars = pars(ys, [op0, op1, op2])
        for s in tpars:
          v = calc(s)
          if not v is None:
            ans = min(v + ps_val, ans)

if ans == 10000000:
  print("impossible")
else:
  print(ans)
