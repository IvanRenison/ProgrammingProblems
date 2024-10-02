# https://codeforces.com/gym/101190
import re

def remp(match: re.Match[str]) -> str:
  s = match.group(0)
  words = s.split()
  ans = ""
  for w in words:
    ans += w[0]
  ans += " (" + s + ")"
  return ans

with open("abbreviation.in", "r") as f:
  l = f.read()

l = re.sub(r"\b[A-Z][a-z]+( [A-Z][a-z]+\b)+", remp, l)
print(l, file=open("abbreviation.out", "w"))
