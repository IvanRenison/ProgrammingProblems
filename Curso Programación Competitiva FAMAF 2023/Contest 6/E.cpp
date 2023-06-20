// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

pair<ull, vector<ull>> compress(vector<ull> xs) {
  ull n = xs.size();

  map<ull, vector<ull>> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vector<ull> compressed_xs(n);

  ull i = 0;
  for (auto [x, ks] : xs_map) {
    for (ull k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return {i - 1, compressed_xs};
}

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
  // max sum, pos
  typedef ull T;
  static constexpr T unit = 0;
  T f(T a, T b) {
    if (a > b) {
      return a;
    } else {
      return b;
    }
  } // (any associative fn)
  vector<T> s;
  ull n;
  Tree(ull n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
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

double solve(vector<ull> ps, vector<ull> rs) {
  ull n = ps.size();

  vector<ull> vs(n);

  fore(i, 0, n) {
    ull p = ps[i], r = rs[i];
    vs[i] = r * r * p;
  }

  auto [max_y, ys] = compress(vs);

  Tree t(max_y + 1); // Longest sequence starting with

  ull max_sum = 0;

  for (ull i = n - 1; i < n; i--) {
    ull y = ys[i];

    ull this_max_sum = t.query(y + 1, max_y + 1);
    this_max_sum += vs[i];

    // It will always be better or equal than last max_sum for same y
    t.update(y, this_max_sum);

    if (this_max_sum > max_sum) {
      max_sum = this_max_sum;
    }
  }

  return double(max_sum) * M_PI;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << fixed << setprecision(10);

  ull n;
  cin >> n;

  vector<ull> ps(n), rs(n);
  fore(i, 0, n) {
    cin >> rs[i] >> ps[i];
  }

  cout << solve(ps, rs) << '\n';

  return EXIT_SUCCESS;
}
