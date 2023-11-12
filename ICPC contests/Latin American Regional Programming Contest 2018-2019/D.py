# https://matcomgrader.com/problem/9545/database-of-clients/

N = int(input())

ss = []
for _ in range(N):
    s = input()
    ss.append(s)


pairs = set()
for s in ss:
    name, addr = s.split('@')
    if ('+' in name):
        name, _ = name.split('+')

    realname = ""
    for n in name.split('.'):
        realname += n


    pairs.add((realname, addr))

#print(pairs)


print(len(pairs))


