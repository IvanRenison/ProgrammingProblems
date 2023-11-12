// https://codeforces.com/gym/100623

#include <bits/stdc++.h>

typedef unsigned long long ull;
using namespace std;

#define fore(i, a, b) for (ull i = a; i < b; i++)

/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  typedef ull T;
  static constexpr T unit = 0;
  T f(T a, T b) const {
    return max(a, b);
  } // (any associative fn)
  vector<T> s;
  ull n;
  Tree(ull n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) const { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = f(ra, s[b++]);
      if (e % 2)
        rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

/* Find the minimum index for witch f is true or or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

ull first_with_space(const Tree& t, ull w) {
  return binary_search([&](ull i) { return w <= t.query(0, i + 1); }, 0, t.n);
}

vector<optional<ull>> solve(ull h, ull width, vector<ull> ws) {
  ull n = ws.size();

  h = min(n, h);

  Tree t(h, width);

  vector<optional<ull>> ans(n);

  fore(i, 0, n) {
    ull w = ws[i];

    ull j = first_with_space(t, w);

    if (j < h) {
      ans[i] = j;
      t.update(j, t.query(j, j + 1) - w);
    }
  }

  return ans;
}

int main(void) {
#ifdef ONLINE_JUDGE
  freopen("billboard.in", "r", stdin);
  freopen("billboard.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull h, w, n;

  cin >> h >> w >> n;

  vector<ull> ws(n);
  fore(i, 0, n) {
    cin >> ws[i];
  }

  vector<optional<ull>> ans = solve(h, w, ws);

  for (optional<ull> a : ans) {
    if (a.has_value()) {
      cout << a.value() + 1 << '\n';
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
