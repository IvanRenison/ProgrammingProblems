// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct Elem {
  optional<ull> gcd_with_out_min;
  ull min, count_min;
};

struct Tree {
  typedef optional<Elem> T;
  static constexpr T unit = nullopt;
  T f(T o_a, T o_b) {
    if (!o_a.has_value()) {
      return o_b;
    }
    if (!o_b.has_value()) {
      return o_a;
    }
    Elem a = *o_a, b = *o_b;

    if (a.min == b.min) {
      if (!a.gcd_with_out_min.has_value() && !b.gcd_with_out_min.has_value()) {
        return {{{}, a.min, a.count_min + b.count_min}};
      }
      if (a.gcd_with_out_min.has_value() && !b.gcd_with_out_min.has_value()) {
        return {{a.gcd_with_out_min, a.min, a.count_min + b.count_min}};
      }
      if (!a.gcd_with_out_min.has_value() && b.gcd_with_out_min.has_value()) {
        return {{b.gcd_with_out_min, a.min, a.count_min + b.count_min}};
      }
      return {{gcd(*a.gcd_with_out_min, *b.gcd_with_out_min), a.min, a.count_min + b.count_min}};
    }

    if (b.min < a.min) {
      swap(a, b);
    }

    if (!a.gcd_with_out_min.has_value() && !b.gcd_with_out_min.has_value()) {
      return {{b.min, a.min, a.count_min}};
    }
    if (a.gcd_with_out_min.has_value() && !b.gcd_with_out_min.has_value()) {
      return {{gcd(*a.gcd_with_out_min, b.min), a.min, a.count_min}};
    }
    if (!a.gcd_with_out_min.has_value() && b.gcd_with_out_min.has_value()) {
      return {{gcd(*b.gcd_with_out_min, b.min), a.min, a.count_min}};
    }
    return {{gcd(gcd(*a.gcd_with_out_min, *b.gcd_with_out_min), b.min), a.min, a.count_min}};

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

void solve(void) {}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  Tree t(n);
  fore(i, 0, n) {
    ull s;
    cin >> s;
    t.update(i, {{{}, s, 1}});
  }

  ull k;
  cin >> k;
  fore(i, 0, k) {
    ull l, r;
    cin >> l >> r;
    Elem ans = t.query(l-1, r).value();

    if (!ans.gcd_with_out_min.has_value() || *ans.gcd_with_out_min % ans.min == 0) {
      cout << r - l + 1 - ans.count_min << '\n';
    } else {
      cout << r - l + 1 << '\n';
    }
  }

  return EXIT_SUCCESS;
}
