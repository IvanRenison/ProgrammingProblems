// https://www.spoj.com/problems/KQUERY/

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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const ull inf = 1ull << 60;

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  typedef ll T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a + b; } // (any associative fn)
  vector<T> s; ll n;
  Tree(ll n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

vu solve(const vu& as, const vuuu& queries) {
  ull n = as.size(), q = queries.size();

  vuu ais(n);
  fore(i, 0, n) {
    ais[i] = {as[i], i};
  }
  sort(ALL(ais), greater<uu>());

  vuuuu klujs(q);
  fore(j, 0, q) {
    //auto [l, u, k] = queries[j];
    ull l = get<0>(queries[j]), u = get<1>(queries[j]), k = get<2>(queries[j]);
    klujs[j] = {k, l, u, j};
  }
  sort(ALL(klujs), greater<uuuu>());

  Tree t(n);

  ull i = 0;

  vu ans(q);

  fore(j, 0, q) {
    //auto [k, l, u, j_] = klujs[j];
    ull k = get<0>(klujs[j]), l = get<1>(klujs[j]), u = get<2>(klujs[j]), j_ = get<3>(klujs[j]);
    while (i < n && ais[i].first > k) {
      t.update(ais[i].second, 1);
      i++;
    }

    ans[j_] = t.query(l, u);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }
  ull q;
  cin >> q;
  vuuu queries(q);
  /* for (auto& [i, j, k] : queries) {
    cin >> i >> j >> k;
    i--;
  } */
  fore(i, 0, q) {
    cin >> get<0>(queries[i]) >> get<1>(queries[i]) >> get<2>(queries[i]);
    get<0>(queries[i])--;
  }

  auto ans = solve(as, queries);
  for (ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
