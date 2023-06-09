// https://atcoder.jp/contests/arc126/tasks/arc126_b

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
  static constexpr T unit = 0;
  T f(T a, T b) {
    return max(a, b);
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

// Size of longest increasing subsequence of ys
ull increasingSubsequence(ull max_y, vector<ull> ys) {
  ull n = ys.size();

  Tree t(max_y + 1); // Longest sequence starting with

  ull ans = 0;

  for (ull i = n - 1; i < n; i--) {
    ull y = ys[i];

    ull this_ans = 1 + t.query(y + 1, max_y + 1);

    // It will always be better or equal than last ans for same y
    t.update(y, this_ans);

    ans = max(ans, this_ans);
  }

  return ans;
}

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

ull solve(vector<ull> as, vector<ull> bs) {
  ull M = as.size();

  vector<pair<ull, ull>> abs(M);
  fore(i, 0, M) {
    abs[i] = {as[i], bs[i]};
  }

  sort(abs.begin(), abs.end(), [](pair<ull, ull> ab0, pair<ull, ull> ab1) {
    auto [a0, b0] = ab0;
    auto [a1, b1] = ab1;
    return a0 < a1 || (a0 == a1 && b0 > b1);
  });

  vector<ull> xs(M);
  fore(i, 0, M) {
    xs[i] = abs[i].second;
  }

  auto [y_max, ys] = compress(xs);

  return increasingSubsequence(y_max, ys);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, M;
  cin >> N >> M;

  vector<ull> as(M), bs(M);
  fore(i, 0, M) {
    cin >> as[i] >> bs[i];
  }

  cout << solve(as, bs) << '\n';

  return EXIT_SUCCESS;
}
