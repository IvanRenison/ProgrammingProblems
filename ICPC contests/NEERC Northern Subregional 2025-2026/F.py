# https://codeforces.com/gym/106193/problem/F
from random import *
import sys

sys.set_int_max_str_digits(10**10)

def solve(s, c):

	n = len(s)

	l = 0
	r = n

	while (l + 1 < r):
		m = (l + r) // 2
		a = int(s[:m])
		b = int(s[m:])
		a2 = b * c
		if (a2 < a):
			r = m
		else:
			l = m

	m = (l + r) // 2

	a = int(s[:m])
	b = int(s[m:])
	a2 = b * c
	assert (a2 == a and s[m] != '0')

	return a, b

c = int(c)

a, b = solve(s, c)

print(a, b)