// https://atcoder.jp/contests/abc301/tasks/abc301_c

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(string c1, string c2) {
  map<char, ull> chars1;
  map<char, ull> chars2;

  for (char c : c1) {
    chars1[c]++;
  }
  for (char c : c2) {
    chars2[c]++;
  }

  ull unmatched1 = 0;
  ull unmatched2 = 0;

  fore(c, 'a', 'z' + 1) {
    if (c == 'a' || c == 't' || c == 'c' || c == 'o' || c == 'd' || c == 'e' ||
        c == 'r') {
      if (chars1[c] < chars2[c]) {
        unmatched1 += (chars2[c] - chars1[c]);
      } else {
        unmatched2 += (chars1[c] - chars2[c]);
      }
    } else if (chars1[c] != chars2[c]) {
      return false;
    }
  }

  return unmatched1 <= chars1['@'] && unmatched2 <= chars2['@'];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string c1, c2;
  cin >> c1 >> c2;

  if (solve(c1, c2)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
