// https://codeforces.com/contest/1845/problem/C

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

bool solve(const string& s, const string& l, const string& r) {
  uint n = s.size(), m = l.size();

  uint x = 0;
  fore(i, 0, m) {
    uint last_x = x;
    fore(j, l[i] - '0', r[i] - '0' + 1) {
      uint k = last_x;
      while (k < n && s[k] - '0' != j) k++;
      if (k == n) return true;
      x = max(x, k + 1);
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    string s, l, r;
    uint m;
    cin >> s >> m >> l >> r;

    bool ans = solve(s, l, r);
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
