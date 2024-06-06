// https://cses.fi/problemset/task/1143

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  typedef ull T;
  static constexpr T neut = 0;
  T f(T a, T b) { return max(a, b); } // (any associative fn)
  vector<T> s; ull n;
  Tree(ull n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

// min i such than t[i] ≥ x
ull min_with_more(ull x, Tree& t) {
  if (t.query(0, 1) >= x) {
    return 0;
  }

  ull l = 0, r = t.n;

  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (t.query(0, m + 1) >= x) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

vu solve(const vu& hs, const vu& rs) {
  ull n = hs.size(), m = rs.size();

  Tree t(n);
  fore(i, 0, n) {
    t.upd(i, hs[i]);
  }

  vu ans(m);

  fore(j, 0, m) {
    ull r = rs[j];

    ull i = min_with_more(r, t);
    if (i == n) {
      ans[j] = inf;
    } else {
      ans[j] = i;
      ull h = t.query(i, i + 1);
      assert(h >= r);
      t.upd(i, h - r);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  vu hs(n), rs(m);
  for (ull& h : hs) {
    cin >> h;
  }
  for (ull& r : rs) {
    cin >> r;
  }


  vu ans = solve(hs, rs);
  for (ull a : ans) {
    if (a == inf) {
      cout << "0 ";
    } else {
      cout << a + 1 << ' ';
    }
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
