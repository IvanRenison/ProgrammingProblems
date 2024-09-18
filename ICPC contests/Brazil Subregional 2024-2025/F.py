# https://codeforces.com/gym/105327/problem/F
from fractions import Fraction


n = int(input())

p = Fraction(1)
for _ in range(n):
    p = Fraction(1) / (Fraction(1) + p)

print(p.numerator)

