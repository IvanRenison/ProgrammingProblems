// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/M

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct T {
  ull water_to_wine, water, wine;
};
static constexpr T neut = {0, 0, 0};
T f(T a, T b) {
  if (a.water <= b.water_to_wine) {
    return {
      a.water_to_wine + b.water_to_wine - a.water,
      b.water,
      a.wine + a.water + b.wine
    };
  } else {
    return {
      a.water_to_wine,
      b.water + a.water - b.water_to_wine,
      a.wine + b.wine + b.water_to_wine
    };
  }
} // (any associative fn)
struct Tree {
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

vu solve(const vu& as, const vu& bs, const vuuu& queries) {
  ull n = as.size(), q = queries.size();

  Tree t(n);
  fore(i, 0, n) {
    ull a = as[i], b = bs[i];
    if (b <= a) {
      t.upd(i, {0, a - b, b});
    } else {
      t.upd(i, {b - a, 0, a});
    }
  }

  vu ans(q);
  fore(i, 0, q) {
    auto [p, a, b] = queries[i];
    if (b <= a) {
      t.upd(p, {0, a - b, b});
    } else {
      t.upd(p, {b - a, 0, a});
    }

    T res = t.query(0, n);
    ans[i] = res.wine;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, q;
  cin >> n >> q;
  vu as(n), bs(n);
  for (ull& a : as) {
    cin >> a;
  }
  for (ull& b : bs) {
    cin >> b;
  }
  fore(i, 0, n - 1) {
    ull c;
    cin >> c;
  }

  vuuu queries(q);
  for (auto& [p, x, y] : queries) {
    ull z;
    cin >> p >> x >> y >> z;
    p--;
  }


  vu ans = solve(as, bs, queries);
  for (ull a : ans) {
    cout << a << '\n';
  }
}
