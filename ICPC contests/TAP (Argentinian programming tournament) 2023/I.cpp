// https://codeforces.com/gym/104603/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef tuple<ll, ll, ll, ll, ll, ll> iiiiii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

#define M_PI 3.14159265358979323846
#define SQRT2 (sqrt(2.0))

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> int sgn(T x) {
  return (x > 0) - (x < 0);
}
template <class T> struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator==(P p) const {
    return tie(x, y) == tie(p.x, p.y);
  }
  P operator+(P p) const {
    return P(x + p.x, y + p.y);
  }
  P operator-(P p) const {
    return P(x - p.x, y - p.y);
  }
  P operator*(T d) const {
    return P(x * d, y * d);
  }
  P operator/(T d) const {
    return P(x / d, y / d);
  }
  T dot(P p) const {
    return x * p.x + y * p.y;
  }
  T cross(P p) const {
    return x * p.y - y * p.x;
  }
  T cross(P a, P b) const {
    return (a - *this).cross(b - *this);
  }
  T dist2() const {
    return x * x + y * y;
  }
  double adj() const {
    return sqrt((double)dist2());
  }
  // angle to x-axis in interval [-pi, pi]
  double angle() const {
    return atan2(y, x);
  }
  P unit() const {
    return *this / adj();
  } // makes adj()=1
  P perp() const {
    return P(-y, x);
  } // rotates +90 degrees
  P normal() const {
    return perp().unit();
  }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
  if (s == e)
    return (p - s).adj();
  auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).adj() / d;
}

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

typedef pair<P, ull> Circle;
typedef pair<P, P> Square;
typedef tuple<P, P, P> Triangle;

double distTriPt(Triangle t, P p) {
  auto [p0, p1, p2] = t;

  double ans = 1e30;
  ans = min(ans, segDist(p0, p1, p));
  ans = min(ans, segDist(p1, p2, p));
  ans = min(ans, segDist(p2, p0, p));

  return ans;
}

double distSquaPt(Square s, P p) {
  auto [p0, p2] = s;

  P d = (p2 - p0)/SQRT2;
  P p1 = p0 + d.rotate(M_PI / 4.0);
  P p3 = p0 + d.rotate(-M_PI / 4.0);

  double ans = 1e30;
  ans = min(ans, segDist(p0, p1, p));
  ans = min(ans, segDist(p1, p2, p));
  ans = min(ans, segDist(p2, p3, p));
  ans = min(ans, segDist(p3, p0, p));

  return ans;
}

double distCircCirc(Circle c0, Circle c1) {
  auto [p0, r0] = c0;
  auto [p1, r1] = c1;

  double ans = (p0 - p1).adj() - r0 - r1;
  return max(ans, 0.0);
}

double distCircSqua(Circle c, Square s) {
  auto [p, r] = c;

  double ans = distSquaPt(s, p);

  ans -= r;

  return max(ans, 0.0);
}

double distCircTri(Circle c, Triangle t) {
  auto [p, r] = c;

  double ans = distTriPt(t, p);

  ans -= r;

  return max(ans, 0.0);
}

double distSquaTri(Square s, Triangle t) {
  auto [ps0, ps2] = s;
  auto [pt0, pt1, pt2] = t;

  P ds = (ps2 - ps0)/SQRT2;
  P ps1 = ps0 + ds.rotate(M_PI / 4.0);
  P ps3 = ps0 + ds.rotate(-M_PI / 4.0);

  double ans = 1e30;
  ans = min(ans, distSquaPt(s, pt0));
  ans = min(ans, distSquaPt(s, pt1));
  ans = min(ans, distSquaPt(s, pt2));

  ans = min(ans, distTriPt(t, ps0));
  ans = min(ans, distTriPt(t, ps1));
  ans = min(ans, distTriPt(t, ps2));
  ans = min(ans, distTriPt(t, ps3));

  return max(ans, 0.0);
}

double solve(
    const vector<Circle>& circles, const vector<Square>& squares,
    const vector<Triangle>& triangles
) {
  ull C = circles.size(), Q = squares.size(), T = triangles.size();

  ull N = C + Q + T;

  vector<vector<pair<ull, double>>> adj(N);

  // Build graph
  fore(i, 0, C) {
    fore(j, i + 1, C) {
      double d = distCircCirc(circles[i], circles[j]);
      adj[i].push_back({j, d});
      adj[j].push_back({i, d});
    }
    fore(j, 0, Q) {
      double d = distCircSqua(circles[i], squares[j]);
      adj[C + j].push_back({i, d});
      adj[i].push_back({C + j, d});
    }
    fore(j, 0, T) {
      double d = distCircTri(circles[i], triangles[j]);
      adj[C + Q + j].push_back({i, d});
      adj[i].push_back({C + Q + j, d});
    }
  }
  fore(i, 0, Q) {
    fore(j, 0, T) {
      double d = distSquaTri(squares[i], triangles[j]);
      adj[C + Q + j].push_back({C + i, d});
      adj[C + i].push_back({C + Q + j, d});
    }
  }

  // Dijkstra from squares
  //vector<double> dist(N, 1e30);
  vector<bool> vis(N, false);
  rpriority_queue<pair<double, ull>> q;

  fore(i, 0, Q) {
    q.push({0.0, C + i});
  }

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();

    if (vis[u]) {
      continue;
    }
    vis[u] = true;

    if (u >= C + Q) {
      return d;
    }

    for(auto [v, dv] : adj[u]) {
      if (!vis[v]) {
        q.push({d + dv, v});
      }
    }
  }

  assert(false);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull C, Q, T;
  cin >> C >> Q >> T;

  vector<Circle> circles(C);
  for (auto& [c, r] : circles) {
    cin >> c.x >> c.y >> r;
  }
  vector<Square> squares(Q);
  for (auto& [p0, p1] : squares) {
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
  }
  vector<Triangle> triangles(T);
  for (auto& [p0, p1, p2] : triangles) {
    cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y;
  }

  auto ans = solve(circles, squares, triangles);
  cout << setprecision(10);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
