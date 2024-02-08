// https://codeforces.com/contest/1919/problem/F2

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

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
  struct T {
    array<ull, 4> costs;
    ull con;
    T() {
      costs[0b00] = costs[0b11] = 0;
      costs[0b01] = costs[0b10] = inf;
      con = 0;
    }
    T(ull a, ull b, ull c) {
      costs[0b00] = a;
      costs[0b11] = b;
      costs[0b01] = costs[0b10] = inf;
      con = c;
    }
    ull min() {
      return *min_element(costs.begin(), costs.end());
    }
  };
  T f(T a, T b) {
    T ans;
    ans.con = b.con;
    ans.costs[0b00] = min({
      a.costs[0b00] + b.costs[0b00],
      a.costs[0b00] + b.costs[0b10],
      a.costs[0b01] + b.costs[0b00] + a.con,
      a.costs[0b01] + b.costs[0b10],
    });
    ans.costs[0b01] = min({
      a.costs[0b00] + b.costs[0b01],
      a.costs[0b00] + b.costs[0b11],
      a.costs[0b01] + b.costs[0b01] + a.con,
      a.costs[0b01] + b.costs[0b11],
    });
    ans.costs[0b10] = min({
      a.costs[0b10] + b.costs[0b00],
      a.costs[0b10] + b.costs[0b10],
      a.costs[0b11] + b.costs[0b00] + a.con,
      a.costs[0b11] + b.costs[0b10],
    });
    ans.costs[0b11] = min({
      a.costs[0b10] + b.costs[0b01],
      a.costs[0b10] + b.costs[0b11],
      a.costs[0b11] + b.costs[0b01] + a.con,
      a.costs[0b11] + b.costs[0b11],
    });

    return ans;
  } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = T()) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    T ra = T(), rb = T();
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};


vu solve(vu& as, vu& bs, vu& cs, const vuuuu& querys) {
  ull n = as.size(), q = querys.size();

  cs.push_back(0);

  Tree t(n);

  fore(i, 0, n) {
    t.update(i, {as[i], bs[i], cs[i]});
  }

  vu ans(q);

  fore(i, 0, q) {
    auto [p, x, y, z] = querys[i];

    t.update(p, Tree::T(x, y, z));

    Tree::T this_ans = t.query(0, n);

    ans[i] = this_ans.min();
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vu as(n), bs(n), cs(n - 1);
  fore(i, 0, n) {
    cin >> as[i];
  }
  fore(i, 0, n) {
    cin >> bs[i];
  }
  fore(i, 0, n - 1) {
    cin >> cs[i];
  }
  vuuuu querys(q);
  fore(i, 0, q) {
    ull p, x, y, z;
    cin >> p >> x >> y >> z;
    p--;
    querys[i] = {p, x, y, z};
  }

  auto ans = solve(as, bs, cs, querys);
  for (ull a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
