// https://codeforces.com/gym/105053/problem/A

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<double> vd;
typedef pair<double, double> dd;
typedef vector<dd> vdd;
typedef tuple<double, double, double> ddd;
typedef vector<ddd> vddd;
typedef tuple<double, double, double, double> dddd;
typedef vector<dddd> vdddd;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/** Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Line {
  mutable double k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(double x) const { return p < x; }
};

const double inf = 1./.0;
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  double div(double a, double b) { return a / b; }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(double k, double m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  double query(double x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};


double solve(const vdddd& meteors) {
  ull N = meteors.size();

  if (N == 1) {
    return 0;
  }

  LineContainer max_X, min_X, max_Y, min_Y;

  for (auto [X, Y, VX, VY] : meteors) {
    max_X.add(VX, X);
    min_X.add(-VX, -X);
    max_Y.add(VY, Y);
    min_Y.add(-VY, -Y);
  }

  vd ts;

  for (const LineContainer& lc : {max_X, min_X, max_Y, min_Y}) {
    for (const Line& l : lc) {
      if (l.p != inf && l.p > 0) {
        ts.push_back(l.p);
      }
    }
  }

  auto area = [&](double t) {
    double min_x = -min_X.query(t);
    double max_x = max_X.query(t);
    double min_y = -min_Y.query(t);
    double max_y = max_Y.query(t);
    return (max_x - min_x) * (max_y - min_y);
  };

  double ans = area(0);

  for (double t : ts) {
    ans = min(ans, area(t));
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vdddd movs(N);
  fore(i, 0, N) {
    ll X, Y, VX, VT;
    cin >> X >> Y >> VX >> VT;
    movs[i] = {X, Y, VX, VT};
  }

  auto ans = solve(movs);
  cout << setprecision(10) << fixed;
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
