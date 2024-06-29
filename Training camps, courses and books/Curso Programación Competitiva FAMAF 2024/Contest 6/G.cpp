// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/G

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

constexpr ull bits = 21;

struct T {
  array<ull, bits> cnt;
  T(ull x = 0) {
    fill(cnt.begin(), cnt.end(), 0);
    fore(i, 0, bits) if (x & (1 << i)) {
      cnt[i] = 1;
    }
  }
  ull operator()() {
    ull ans = 0;
    fore(i, 0, bits) {
      ans += (1 << i) * cnt[i];
    }
    return ans;
  }
};
typedef ull L; // T: data type, L: lazy type
// neutrals
const T tneut;
const L lneut = 0;
T f(T a, const T& b) {
  fore(i, 0, bits) a.cnt[i] += b.cnt[i];
  return a;
} // operation
// new st according to lazy
T apply(T v, L l, ull s, ull e) {
  ull sz = e - s;
  fore(i, 0, bits) if (l & (1 << i)) {
    v.cnt[i] = sz - v.cnt[i];
  }
  return v;
}
// cumulative effect of lazy
L comb(L a, L b) { return a ^ b; }
struct Tree {
  ull n;
  vector<T> st;
  vector<L> lazy;
  Tree(ull n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(vector<T> &a) : n(a.size()), st(4*n), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ull k, ull s, ull e, vector<T> &a) {
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vector<T> as(n);
  fore(i, 0, n) {
    ull a;
    cin >> a;
    as[i] = T(a);
  }

  Tree st(as);

  ull m;
  cin >> m;

  while (m--) {
    ull ty;
    cin >> ty;
    if (ty == 1) {
      ull l, r;
      cin >> l >> r;
      l--;
      T ansT = st.query(l, r);
      ull ans = ansT();
      cout << ans << '\n';
    } else {
      ull l, r, x;
      cin >> l >> r >> x;
      l--;
      st.upd(l, r, x);
    }
  }
}
