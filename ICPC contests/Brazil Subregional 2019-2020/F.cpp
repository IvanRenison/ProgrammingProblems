// https://codeforces.com/gym/102346

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define SZ(v) (a.size())

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
  struct T {
    ull m, m_count;
  };
  typedef ll L; // T: data type, L: lazy type
  // neutrals
  constexpr static T tneut = {0, 0}; constexpr static L lneut = 0;
  T f(T a, T b) {
    if (a.m < b.m) {
      return a;
    } else if (a.m == b.m) {
      return {a.m, a.m_count + b.m_count};
    } else {
      return b;
    }
  } // operation
  // new st according to lazy
  T apply(T v, L l, ll s, ll e) {
    v.m += l;
    return v;
  }
  // cumulative effect of lazy
  L comb(L a, L b) { return a + b; }
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(vector<T> &a) : n(SZ(a)), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ll k, ll s, ll e, vector<T> &a) {
    lazy[k] = lneut;
    if (s + 1 == e) { st[k] = a[s]; return; }
    ll m = (s + e) / 2;
    init(2*k, s, m, a), init(2*k+1, m, e, a);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return; // if neutral, nothing to do
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) { // propagate to children
      lazy[2*k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut; // clear node lazy
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v); // accumulate lazy
      push(k, s, e);
      return;
    }
    ll m = (s + e) / 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) / 2;
    return f(query(2*k, s, m, a, b),query(2*k+1, m, e, a, b));
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  T query(ll a, ll b) { return query(1, 0, n, a, b); }
};

ull solve(const viiii& lines, ull P, ll X, ll Y) {
  ull N = lines.size();

  auto area = [&](ll r) -> ull {
    viiii rectangles(N);
    fore(i, 0, N) {
      auto [x0, y0, x1, y1] = lines[i];
      rectangles[i] = {max(x0 - r, 0ll), max(y0 - r, 0ll), min(x1 + r, X), min(y1 + r, Y)};
    }

    vector<vii> starts(X), ends(X + 1);

    fore(i, 0, N) {
      auto [x0, y0, x1, y1] = rectangles[i];
      starts[x0].push_back({y0, y1});
      ends[x1].push_back({y0, y1});
    }

    ull ans = 0;

    vector<Tree::T> vals(Y, {0, 1});
    Tree t(vals);

    fore(x, 0, X) {
      for (auto [y0, y1] : ends[x]) {
        t.upd(y0, y1, -1);
      }
      for (auto [y0, y1] : starts[x]) {
        t.upd(y0, y1, 1);
      }

      Tree::T q = t.query(0, Y);

      ans += Y - (q.m == 0) * (q.m_count);
    }

    return ans;
  };

  auto can = [&](ull r) -> bool {
    ull a = area(r);
    return X * Y * P <= a * 100;
  };

  ull lo = 0, up = max(X, Y);
  while (lo + 1 < up) {
    ull m = (lo + up) / 2;
    if (can(m)) {
      up = m;
    } else {
      lo = m;
    }
  }

  return lo + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  viiii lines(N);
  for (auto& [x0, y0, x1, y1] : lines) {
    cin >> x0 >> y0 >> x1 >> y1;
  }
  ull P;
  ll X0, Y0, X, Y;
  cin >> P >> X0 >> Y0 >> X >> Y;

  for (auto& [x0, y0, x1, y1] : lines) {
    x0 -= X0, y0 -= Y0, x1 -= X0, y1 -= Y0;
    if (x0 > x1 || y0 > y1) {
      swap(x0, x1), swap(y0, y1);
    }
  }

  X -= X0, Y -= Y0;

  auto ans = solve(lines, P, X, Y);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
