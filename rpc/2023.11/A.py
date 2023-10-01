# https://redprogramacioncompetitiva.com/contests/2023/11

s = input()

tiene7 = '7' in s
dividible7 = int(s) % 7 == 0

if not tiene7 and not dividible7:
    print(0)
elif not tiene7 and dividible7:
    print(1)
elif tiene7 and not dividible7:
    print(2)
elif tiene7 and dividible7:
    print(3)

