// https://codeforces.com/contest/1100/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
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
  static constexpr T unit = ULLONG_MAX;
  T f(T a, T b) {
    return min(a, b);
  } // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
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

vector<ull> solve(ull n, vector<ull> as) {
  ull m = as.size();

  Tree t(n, 0);

  vector<ull> ans(m);

  ull last_min = 0;
  fore(i, 0, m) {
    ull a = as[i];
    ull old_a = t.query(a, a + 1);
    t.update(a, old_a + 1);

    ull new_min = t.query(0, n);
    if (new_min > last_min) {
      ans[i] = 1;
      last_min++;
    } else {
      ans[i] = 0;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;

  cin >> n >> m;

  vector<ull> as(m);
  fore(i, 0, m) {
    ull a;
    cin >> a;
    as[i] = a - 1;
  }

  vector<ull> ans = solve(n, as);
  for (ull as : ans) {
    cout << as;
  }
  cout << "\n";

  return EXIT_SUCCESS;
}
