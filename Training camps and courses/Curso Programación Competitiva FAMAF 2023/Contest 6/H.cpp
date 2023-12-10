// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Elem {
  array<ull, 4> amounts;
  ull left, right;

  Elem() : amounts({0, 0, 0, 0}), left(0), right(0) {}
  Elem(ull x) {
    amounts[0b00] = 0;
    amounts[0b10] = 0;
    amounts[0b01] = 0;
    amounts[0b11] = 1;
    left = x;
    right = x;
  }
};

struct Tree {
  typedef optional<Elem> T;
  static constexpr T unit = {};
  T f(T o_a, T o_b) {
    if (!o_a.has_value()) {
      return o_b;
    } else if (!o_b.has_value()) {
      return o_a;
    }
    Elem a = o_a.value(), b = o_b.value();
    Elem ans;

    ans.amounts[0b00] =
        a.amounts[0b00] + b.amounts[0b00] + a.amounts[0b01] + b.amounts[0b10];
    ans.amounts[0b10] = a.amounts[0b10] + a.amounts[0b11];
    ans.amounts[0b01] = b.amounts[0b01] + b.amounts[0b11];
    if (a.right <= b.left) {
      ans.amounts[0b00] += a.amounts[0b01] * b.amounts[0b10];
      ans.amounts[0b10] += a.amounts[0b11] * b.amounts[0b10];
      ans.amounts[0b01] += a.amounts[0b01] * b.amounts[0b11];
      ans.amounts[0b11] = a.amounts[0b11] * b.amounts[0b11];
    }

    ans.left = a.left;
    ans.right = b.right;

    return ans;
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

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;

  Tree t(n);
  fore(i, 0, n) {
    ull a;
    cin >> a;

    t.update(i, Elem(a));
  }

  fore(i, 0, q) {
    ull k, x, y;
    cin >> k >> x >> y;
    if (k == 1) {
      t.update(x - 1, Elem(y));
    } else {
      Elem eans = t.query(x - 1, y).value();
      ull ans = eans.amounts[0b00] + eans.amounts[0b01] + eans.amounts[0b10] +
                eans.amounts[0b11];
      cout << ans << '\n';
    }
  }

  return EXIT_SUCCESS;
}
