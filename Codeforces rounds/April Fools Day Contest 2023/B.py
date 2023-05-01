# https://codeforces.com/contest/1812/problem/B



def main():
    x: int = int(input())
    res = [
        "",     # 0
        "YES",  # 1  # Test 1
        "YES",  # 2  # Test 6
        "YES",  # 3  # Test 7
        "YES",  # 4  # Test 8
        "YES",  # 5  # Test 9
        "YES",  # 6  # Test 3
        "YES",  # 7  # Test 10
        "YES",  # 8  # Test 11
        "YES",  # 9  # Test 12
        "YES",  # 10 # Test 13
        "YES",  # 11 # Test 14
        "YES",  # 12 # Test 15
        "YES",  # 13 # Test 16
        "YES",  # 14 # Test 17
        "NO",   # 15 # Test 2
        "YES",  # 16 # Test 18
        "YES",  # 17 # Test 19
        "YES",  # 18 # Test 20
        "YES",  # 19 # Test 21
        "NO",   # 20 # Test 4

        "NO",   # 21 # Test 22
        "YES",  # 22 # Test 23
        "YES",  # 23 # Test 24
        "YES",  # 24 # Test 25
        "YES",  # 25 # Test 5
    ][x]
    print(res)


if __name__ == '__main__':
    main()
