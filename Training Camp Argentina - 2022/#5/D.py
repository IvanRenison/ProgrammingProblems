

ss = [
"""    0
  0 1 0
0 1 2 1 0
  0 1 0
    0
""",
"""      0
    0 1 0
  0 1 2 1 0
0 1 2 3 2 1 0
  0 1 2 1 0
    0 1 0
      0
""",
"""        0
      0 1 0
    0 1 2 1 0
  0 1 2 3 2 1 0
0 1 2 3 4 3 2 1 0
  0 1 2 3 2 1 0
    0 1 2 1 0
      0 1 0
        0
""",
"""          0
        0 1 0
      0 1 2 1 0
    0 1 2 3 2 1 0
  0 1 2 3 4 3 2 1 0
0 1 2 3 4 5 4 3 2 1 0
  0 1 2 3 4 3 2 1 0
    0 1 2 3 2 1 0
      0 1 2 1 0
        0 1 0
          0
""",
"""            0
          0 1 0
        0 1 2 1 0
      0 1 2 3 2 1 0
    0 1 2 3 4 3 2 1 0
  0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 4 5 6 5 4 3 2 1 0
  0 1 2 3 4 5 4 3 2 1 0
    0 1 2 3 4 3 2 1 0
      0 1 2 3 2 1 0
        0 1 2 1 0
          0 1 0
            0
""",
"""              0
            0 1 0
          0 1 2 1 0
        0 1 2 3 2 1 0
      0 1 2 3 4 3 2 1 0
    0 1 2 3 4 5 4 3 2 1 0
  0 1 2 3 4 5 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
  0 1 2 3 4 5 6 5 4 3 2 1 0
    0 1 2 3 4 5 4 3 2 1 0
      0 1 2 3 4 3 2 1 0
        0 1 2 3 2 1 0
          0 1 2 1 0
            0 1 0
              0
""",
"""                0
              0 1 0
            0 1 2 1 0
          0 1 2 3 2 1 0
        0 1 2 3 4 3 2 1 0
      0 1 2 3 4 5 4 3 2 1 0
    0 1 2 3 4 5 6 5 4 3 2 1 0
  0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 7 6 5 4 3 2 1 0
  0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
    0 1 2 3 4 5 6 5 4 3 2 1 0
      0 1 2 3 4 5 4 3 2 1 0
        0 1 2 3 4 3 2 1 0
          0 1 2 3 2 1 0
            0 1 2 1 0
              0 1 0
                0
""",
"""                  0
                0 1 0
              0 1 2 1 0
            0 1 2 3 2 1 0
          0 1 2 3 4 3 2 1 0
        0 1 2 3 4 5 4 3 2 1 0
      0 1 2 3 4 5 6 5 4 3 2 1 0
    0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
  0 1 2 3 4 5 6 7 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 0
  0 1 2 3 4 5 6 7 8 7 6 5 4 3 2 1 0
    0 1 2 3 4 5 6 7 6 5 4 3 2 1 0
      0 1 2 3 4 5 6 5 4 3 2 1 0
        0 1 2 3 4 5 4 3 2 1 0
          0 1 2 3 4 3 2 1 0
            0 1 2 3 2 1 0
              0 1 2 1 0
                0 1 0
                  0
"""
]


x = int(input())

print(ss[x-2])


