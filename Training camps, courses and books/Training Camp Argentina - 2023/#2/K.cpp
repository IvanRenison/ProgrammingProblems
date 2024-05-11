// https://codeforces.com/group/hzSLIARNBN/contest/465113/problem/K

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
//typedef long double ld;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/*
  Linea que pasa por (ax, ay), (bx, by):
  y = (by - ay) / (bx - ax) * (x - ax) + ay
  y = (by - ay) / (bx - ax) * x + ay - (by - ay) / (bx - ax) * ax

  y = m*x + d

  m = (by - ay) / (bx - ax)
  d = ay - (by - ay) / (bx - ax) * ax


  Linea perpendicular a esta que pasa por (cx, cy):

  y = -1/m*(x - cx) + cy
  y = -1/m*x + cx/m + cy

  y = m2*x + d2
  m2 = -1/m
  d2 = cx/m + cy


  Intersección de las lineas:
  m*x + d = m2*x + d2
  m*x - m2*x = d2 - d
  x*(m - m2) = d2 - d
  x = (d2 - d) / (m - m2)

*/

double dist(pair<double, double> a, pair<double, double> b) {
  double ax = a.first, ay = a.second, bx = b.first, by = b.second;
  return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

double minFor3(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
  double ax = a.first, ay = a.second, bx = b.first, by = b.second, cx = c.first,
         cy = c.second;

  if (cx == ax) {
    return abs(cx - bx) / 2.0;
  }
  if (cy == ay) {
    return abs(cy - by) / 2.0;
  }

  double m = (cy - ay) / (cx - ax);
  double d = ay - m * ax;
  // Linea que pasa por (ax, ay), (cx, cy): y = m*x + d

  double m2 = -1.0 / m;
  double d2 = bx / m + by;
  // Linea perpendicular a la última que pasa por (bx, by): y = m2*x + d2

  double x = (d2 - d) / (m - m2);
  double y = m * x + d;
  // Intersección de las lineas: (x, y)

  double xy_b = dist({x, y}, {bx, by});

  return xy_b / 2.0;
}

double solve(vector<pair<ll, ll>> xys) {
  ull n = xys.size();

  double ans = 1e12;
  double this_ans;

  fore(i, 0, n) {
    this_ans = minFor3(xys[i], xys[(i + 1) % n], xys[(i + 2) % n]);
    ans = min(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << setprecision(10);

  ull n;
  cin >> n;

  vector<pair<ll, ll>> xys(n);
  for (auto& [x, y] : xys) {
    cin >> x >> y;
  }

  auto ans = solve(xys);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
