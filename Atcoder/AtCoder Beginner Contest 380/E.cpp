// https://atcoder.jp/contests/abc380/tasks/abc380_e

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

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
typedef ii T; typedef ll L; // T: data type, L: lazy type
const T tneut = {-1, inf}; const L lneut = 0; // neutrals
T f(T a, T b) {
  return {max(a.first, b.first), min(a.second, b.second)};
} // associative
T apply(T v, L l, ll s, ll e) { // new st according to lazy
  return {v.first + l, v.second + l}; }
L comb(L a, L b) { return a + b; } // cumulative effect of lazy

struct Tree { // example: range sum with range addition
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

ull binSearchUp(Tree& t, ull i) {
  ull l = i, r = t.n;

  ull c = t.query(i, i + 1).first;

  ii q = t.query(i, r);
  if (q.first == c && q.second == c) {
    return r;
  }

  while (l + 1 < r) {
    ull m = (l + r) / 2;

    ii q = t.query(i, m);
    if (q.first == c && q.second == c) {
      l = m;
    } else {
      r = m;
    }
  }

  return l;
}

ull binSearchDown(Tree& t, ull i) {
  ull l = 0, r = i;

  ull c = t.query(i, i + 1).first;

  ii q = t.query(0, i + 1);
  if (q.first == c && q.second == c) {
    return 0;
  }

  while (l + 1 < r) {
    ull m = (l + r) / 2;

    ii q = t.query(m, i + 1);

    if (q.first == c && q.second == c) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

void solve(ull N, ull Q) {
  vii vals(N);
  fore(i, 0, N) {
    vals[i] = {i, i};
  }

  Tree t(vals);

  vu with_color(N, 1);

  while (Q--) {
    ull type;
    cin >> type;
    if (type == 1) {
      ull x, c;
      cin >> x >> c;
      x--, c--;
      ull old_c = t.query(x, x + 1).first;

      ull r = binSearchUp(t, x);
      ull l = binSearchDown(t, x);

      t.upd(l, r, (ll)c - (ll)old_c);

      with_color[old_c] -= r - l;
      with_color[c] += r - l;

    } else {
      ull c;
      cin >> c;
      c--;
      cout << with_color[c] << '\n';
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, Q;
  cin >> N >> Q;
  solve(N, Q);

}
