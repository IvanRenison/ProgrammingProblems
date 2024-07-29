// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;

const ld eps = 1e-12;

/** Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> ll sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  ld dist() const { return sqrt((ld)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  ld angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(ld a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }

  // automatic cast from Point<ll> to Point<ld>
  template<class S> Point(const Point<S>& p) : x(p.x), y(p.y) {}
};

/** Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\
\begin{minipage}{75mm}
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point} is returned.
If no intersection point exists \{0, (0,0)} is returned and if infinitely many exists \{-1, (0,0)} is returned.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 * Status: stress-tested, and tested through half-plane tests
 */
pair<ll, Point<ld>> lineInter(Point<ld> s1, Point<ld> e1, Point<ld> s2, Point<ld> e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), Point<ld>(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

typedef Point<ll> P;

optional<vector<P>> solve(ll n, P d0, P d1) {
  {
    auto [x0, y0] = d0;
    auto [x1, y1] = d1;
    if (x0 == 0 && y0 == 0) {
      return {};
    }
    if (x1 == 0 && y1 == 0) {
      return {};
    }
    ll g0 = gcd(abs(x0), abs(y0));
    ll g1 = gcd(abs(x1), abs(y1));
    x0 /= g0;
    y0 /= g0;
    x1 /= g1;
    y1 /= g1;
    if (x0 == x1 && y0 == y1) {
      return {};
    }
    x0 *= -1, y0 *= -1;
    if (x0 == x1 && y0 == y1) {
      return {};
    }
  }

  vector<P> ans = {P{0, 0}};

  {
    auto [x, y] = d0;
    ll g = gcd(abs(x), abs(y));
    for (ll x0 = x / g, y0 = y / g; abs(x0) < abs(x) || abs(y0) < abs(y); x0 += x / g, y0 += y / g) {
      ans.push_back(P{x0, y0});
    }
  }
  {
    auto [x, y] = d1;
    ll g = gcd(abs(x), abs(y));
    for (ll x0 = x / g, y0 = y / g; abs(x0) < abs(x) || abs(y0) < abs(y); x0 += x / g, y0 += y / g) {
      ans.push_back(P{x0, y0});
    }
  }

  P p = d0 + d1;

  vector<P> points = {P(0, 0), d0, p, d1};

  ll minyi = min_element(ALL(points), [](P a, P b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }) - points.begin();
  ll maxyi = max_element(ALL(points), [](P a, P b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }) - points.begin();

  ll minxi;
  ll maxxi;
  {
    set<ll> idx = {0, 1, 2, 3};
    idx.erase(minyi);
    idx.erase(maxyi);
    minxi = *min_element(ALL(idx), [&](ll a, ll b) {
      return (points[a] - points[minyi]).angle() > (points[b] - points[minyi]).angle();
    });
    maxxi = *max_element(ALL(idx), [&](ll a, ll b) {
      return (points[a] - points[minyi]).angle() > (points[b] - points[minyi]).angle();
    });
  }

  ll miny = points[minyi].y;
  ll maxy = points[maxyi].y;
  ll minx = points[minxi].x;
  ll maxx = points[maxxi].x;

  ll yleft = points[minxi].y;
  ll yright = points[maxxi].y;

  auto getMinx = [&] (ll y) -> ll {
    assert(miny < y && y < maxy);

    if (y == yleft) {
      return minx + 1;
    } else if (y > yleft) {
      // line from minx to maxy
      if ((points[maxyi] - points[minxi]).x == 0) {
        return minx + 1;
      }
      auto [ok, p] = lineInter(points[minxi], points[maxyi], P(minx, y), P(maxx, y));
      return (ll)floorl(p.x + 1 + eps);
    } else {
      // line from minx to miny
      if ((points[minyi] - points[minxi]).x == 0) {
        return minx + 1;
      }
      auto [ok, p] = lineInter(points[minxi], points[minyi], P(minx, y), P(maxx, y));
      return (ll)floorl(p.x + 1 + eps);
    }
  };

  auto getMaxx = [&] (ll y) -> ll {
    assert(miny < y && y < maxy);

    if (y == yright) {
      return maxx - 1;
    } else if (y > yright) {
      // line from maxx to maxy
      if ((points[maxyi] - points[maxxi]).x == 0) {
        return maxx - 1;
      }
      auto [ok, p] = lineInter(points[maxxi], points[maxyi], P(minx, y), P(maxx, y));
      return (ll)floorl(p.x - eps);
    } else {
      // line from maxx to miny
      if ((points[minyi] - points[maxxi]).x == 0) {
        return maxx - 1;
      }
      auto [ok, p] = lineInter(points[maxxi], points[minyi], P(minx, y), P(maxx, y));
      return (ll)floorl(p.x - eps);
    }
  };

  fore(y, miny + 1, maxy) {
    ll min_x = getMinx(y);
    ll max_x = getMaxx(y);
    fore(x, min_x, max_x + 1) {
      ans.push_back(P{x, y});
    }
    if (ans.size() > n) {
      return {};
    }
  }

  if (ans.size() != n) {
    return {};
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, dx0, dy0, dx1, dy1;
  cin >> n >> dx0 >> dy0 >> dx1 >> dy1;

  optional<vector<P>> ans = solve(n, P(dx0, dy0), P(dx1, dy1));
  if (ans) {
    cout << "YES\n";
    for (auto [x, y] : *ans) {
      cout << x << ' ' << y << '\n';
    }
  } else {
    cout << "NO\n";
  }

}