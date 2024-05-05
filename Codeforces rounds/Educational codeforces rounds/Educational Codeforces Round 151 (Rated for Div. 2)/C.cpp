// https://codeforces.com/contest/1845/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool solve1(const string& ss, const string& ls, const string& rs) {
  ull n = ss.size(), m = ls.size();

  if (m > n) {
    return true;
  }

  ull val = 0;
  fore(j, 0, m) {
    ull l = ls[j] - '0', r = rs[j] - '0';
    vector<bool> found(r - l + 1, false);
    ull count_found = 0;
    for (; val < n; val++) {
      ull d = ss[val] - '0';
      if (l <= d && d <= r) {
        if (!found[d - l]) {
          count_found++;
          found[d - l] = true;
          if (count_found == r - l + 1) {
            val++;
            break;
          }
        }
      }
    }
    if (val == n && count_found < r - l + 1) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s, l, r;
    ull m;
    cin >> s >> m >> l >> r;

    bool ans = solve1(s, l, r);
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
