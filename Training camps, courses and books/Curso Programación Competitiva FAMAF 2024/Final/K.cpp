// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/K

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Iván Renison
 * Date: 2024-03-05
 * License: CC0
 * Source: notebook el vasito
 * Description: Segment tree with ability to add values of large intervals, and compute the sum of intervals.
 * Ranges are [s, e).
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: Tree st(n);
 *  st.init(x);
 *  st.upd(s, e, v);
 *  st.query(s, e);
 * Status: Tested on SPOJ HORRIBLE, stress-tested a bit
 */
struct Tree { // example: range sum with range addition
  typedef ull T; typedef ull L; // T: data type, L: lazy type
  // neutrals
  constexpr static T tneut = 0; constexpr static L lneut = 0;
  T f(T a, T b) { return a + b; } // operation
  // new st according to lazy
  T apply(T v, L l, ull s, ull e) { return v + l * (e - s); }
  // cumulative effect of lazy
  L comb(L a, L b) { return a + b; }
  ull n;
  vector<T> st;
  vector<L> lazy;
  Tree(ull n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(const vector<T> &a) : n(a.size()), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ull k, ull s, ull e, const vector<T> &a) {
    lazy[k] = lneut;
    if (s + 1 == e) { st[k] = a[s]; return; }
    ull m = (s + e) / 2;
    init(2*k, s, m, a), init(2*k+1, m, e, a);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  void push(ull k, ull s, ull e) {
    if (lazy[k] == lneut) return; // if neutral, nothing to do
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) { // propagate to children
      lazy[2*k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut; // clear node lazy
  }
  void upd(ull k, ull s, ull e, ull a, ull b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v); // accumulate lazy
      push(k, s, e);
      return;
    }
    ull m = (s + e) / 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ull k, ull s, ull e, ull a, ull b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ull m = (s + e) / 2;
    return f(query(2*k, s, m, a, b),query(2*k+1, m, e, a, b));
  }
  void upd(ull a, ull b, L v) { upd(1, 0, n, a, b, v); }
  T query(ull a, ull b) { return query(1, 0, n, a, b); }
};

ull solve(ull m, ull w, const vu& as) {
  ull n = as.size();

  auto can = [&](ull k) -> bool {
    Tree st(as);
    ull cnt = 0;
    fore(i, 0, n) {
      ull a = st.query(i, i + 1);
      if (a < k) {
        ull d = k - a;
        st.upd(i, min(n, i + w), d);
        cnt += d;
      }
    }

    return cnt <= m;
  };

  ull min_a = *min_element(as.begin(), as.end());

  ull l = min_a - 1, r = min_a + m + 1;

  while (l + 1 < r) {
    ull k = (l + r) / 2;
    if (can(k)) {
      l = k;
    } else {
      r = k;
    }
  }

  return l;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m, w;
  cin >> n >> m >> w;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  ull ans = solve(m, w, as);
  cout << ans << '\n';
}
