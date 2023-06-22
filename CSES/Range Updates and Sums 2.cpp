// https://cses.fi/problemset/task/1735

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Lazy {
  optional<ull> set;
  ull add;

  Lazy() : set(), add(0) {}
  Lazy(optional<ull> set, ull add) : set(set), add(add) {}
  bool hasOp() {
    return set.has_value() || add != 0;
  }

  // accumulate lazy (with priority to the new one)
  void operator+=(Lazy lazy) {
    if (lazy.set.has_value()) {
      set = lazy.set;
      add = lazy.add;
    } else {
      add += lazy.add;
    }
  }
};

ull updateWithLazy(ull val, Lazy lazy, ull s, ull e) {
  assert(e >= s);
  if (lazy.set.has_value()) {
    return (e - s) * (lazy.set.value() + lazy.add);
  } else {
    return val + (e - s) * lazy.add;
  }
}

struct STree { // example: range sum with range addition
  vector<ull> st;
  vector<Lazy> lazy;
  ull n;
  STree(ull n) : st(4 * n + 5, 0), lazy(4 * n + 5), n(n) { assert(n > 0);}
  void init(ull k, ull s, ull e, const vector<ull>& a) {
    assert(e != s);
    assert(e > s);
    assert(k < st.size());
    lazy[k] = Lazy(); // lazy neutral element
    if (s + 1 == e) {
      st[k] = a[s];
      return;
    }
    assert(2 * k + 1 < st.size());
    ull m = (s + e) / 2;
    init(2 * k, s, m, a);
    init(2 * k + 1, m, e, a);
    st[k] = st[2 * k] + st[2 * k + 1]; // operation
  }
  void push(ull k, ull s, ull e) {
    if (!lazy[k].hasOp())
      return;                                     // if neutral, nothing to do
    st[k] = updateWithLazy(st[k], lazy[k], s, e); // update st according to lazy
    if (s + 1 < e) {                              // propagate to children
      lazy[2 * k] += lazy[k];
      lazy[2 * k + 1] += lazy[k];
    }
    lazy[k] = Lazy(); // clear node lazy
  }
  void upd(ull k, ull s, ull e, ull a, ull b, Lazy v) {
    push(k, s, e);
    if (s >= b || e <= a)
      return;
    if (s >= a && e <= b) {
      lazy[k] += v; // accumulate lazy
      push(k, s, e);
      return;
    }
    ull m = (s + e) / 2;
    upd(2 * k, s, m, a, b, v);
    upd(2 * k + 1, m, e, a, b, v);
    st[k] = st[2 * k] + st[2 * k + 1]; // operation
  }
  ull query(ull k, ull s, ull e, ull a, ull b) {
    if (s >= b || e <= a)
      return 0; // operation neutral
    push(k, s, e);
    if (s >= a && e <= b)
      return st[k];
    ull m = (s + e) / 2;
    return query(2 * k, s, m, a, b) + query(2 * k + 1, m, e, a, b); // operation
  }
  void init(const vector<ull>& a) {
    init(1, 0, n, a);
  }
  void upd(ull a, ull b, Lazy v) {
    upd(1, 0, n, a, b, v);
  }
  ull query(ull a, ull b) {
    return query(1, 0, n, a, b);
  }
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;

  assert(n > 0);
  vector<ull> ts(n);
  fore(i, 0, n) {
    cin >> ts[i];
  }
  STree t(n);
  t.init(ts);
  fore(i, 0, q) {
    ull ty, a, b;
    cin >> ty >> a >> b;

    if (ty == 1) {
      ull x;
      cin >> x;
      t.upd(a - 1, b, {{}, x});
    } else if (ty == 2) {
      ull x;
      cin >> x;
      t.upd(a - 1, b, {x, 0});
    } else {
      cout << t.query(a - 1, b) << '\n';
    }
  }

  return EXIT_SUCCESS;
}
