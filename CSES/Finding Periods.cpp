// https://cses.fi/problemset/task/1733

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define sz(x) ((x).size())

/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
  ull x;
  H(ull x = 0) : x(x) {}
  H operator+(H o) {
    return x + o.x + (x + o.x < x);
  }
  H operator-(H o) {
    return *this + ~o.x;
  }
  H operator*(H o) {
    auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64);
  }
  ull get() const {
    return x + !~x;
  }
  bool operator==(H o) const {
    return get() == o.get();
  }
  bool operator<(H o) const {
    return get() < o.get();
  }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(sz(str) + 1), pw(ha) {
    pw[0] = 1;
    fore(i, 0, sz(str)) ha[i + 1] = ha[i] * C + str[i], pw[i + 1] = pw[i] * C;
  }
  H hashInterval(int a, int b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<ull> solve(string s) {
  HashInterval h(s);
  ull n = s.size();

  vector<ull> ans;

  fore(i, 1, n + 1) {
    if (h.hashInterval(0, n - i) == h.hashInterval(i, n)) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;

  vector<ull> ans = solve(s);
  for (ull x : ans) {
    cout << x << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
