# https://contest.ucup.ac/contest/1784/problem/9255

def div_techo(x, y):
    return (x + y - 1) // y

def my_calc(a, b, s):
    if a < b and s > 0:
        d = div_techo(b - a, s)
        return a * d + s * d * (d - 1) // 2
    elif a > b and s < 0:
        d = (b - a) // (-s)
        assert(d < 0)
        #print(a, b, s, d)
        return a * (-d) + s * (-d) * (-d - 1) // 2
    return 0


lines: list[str] = []
for _ in range(5):
    lines.append(input())


l2 = lines[2].split()
assert(len(l2) == 4)
assert(l2[0] == "for")
assert(len(l2[1]) == 1)
assert(l2[2] == "in")
assert(l2[3][:6] == "range(")
assert(l2[3][-2:] == "):")
vars: list[str] = (l2[3][6:-2]).split(',')


j = l2[1]
a = vars[0]
b = vars[1]
s = vars[2] if len(vars) == 3 else 1

nl2 = f"    ans += my_calc({a}, {b}, {s})"



code = lines[0] + '\n' + lines[1] + '\n' + nl2 + '\n' + lines[4] + '\n'

#print(code)

exec(code)



"""
ans=0
for a in range(1,3):
    for b in range(5,1,-2):
        ans+=b
print(ans)
"""
"""
ans=0
for q in range(100,50,-1):
    for i in range(q,77,20):
        ans+=i
print(ans)
"""



"""
for j in range(a, b, s):
    ans += j


for j in range(0, b - a, s):
    ans += a + j




"""