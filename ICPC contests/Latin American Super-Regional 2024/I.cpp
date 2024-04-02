// https://codeforces.com/gym/105053/problem/I

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

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
};

/** Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
 */
typedef Point<ld> P;
vector<P> convexHull(vector<P> pts) {
  if (SZ(pts) <= 1) return pts;
  sort(ALL(pts));
  vector<P> h(SZ(pts)+1);
  ll s = 0, t = 0;
  for (ll it = 2; it--; s = --t, reverse(ALL(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Stress-tested and tested on kattis:polygonarea
 */
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
  return a;
}

/** Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Finds the intersection between a circle and a line.
 * Returns a vector of either 0, 1, or 2 intersection points.
 * P is intended to be Point<double>.
 * Status: unit tested
 */
template<class P>
vector<P> circleLine(P c, ld r, P a, P b) {
  P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
  ld s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
  if (h2 < 0) return {};
  if (h2 == 0) return {p};
  P h = ab.unit() * sqrt(h2);
  return {p - h, p + h};
}

/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b.
Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
P is supposed to be Point<T> or Point3D<T> where T is e.g. double or ll.
It uses products in intermediate steps so watch out for overflow if using int or ll.
Using Point3D will always give a non-negative distance. For Point3D, call .dist on the result of the cross product.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
template<class P>
ld lineDist(const P& a, const P& b, const P& p) {
  return (ld)(b-a).cross(p-a)/(b-a).dist();
}

ld solve(ld R, vector<P> points) {
  R += 1e-14;
  points = convexHull(points);

  ull N = points.size();

  if (N == 1) {
    return 0.;
  }
  if (N == 2) {
    P p0 = points[0], p1 = points[1];

    ld ans = (p0 - p1).dist() * (lineDist(p0, p1, P(0, 0)) + R) / 2.;

    return ans;
  }

  vector<tuple<ld, P, bool, ull>> poss;
  // angle, point in circle, is start, index

  fore(i, 0, N) {
    P a = points[i], b = points[(i + 1) % N];

    vector<P> p01 = circleLine(P(0, 0), R, a, b);
    assert(p01.size() == 2);
    P p0 = p01[0], p1 = p01[1];

    assert((p0 - a).dist2() < (p0 - b).dist2());
    assert((p1 - b).dist2() < (p1 - a).dist2());

    ld α0 = p0.angle(), α1 = p1.angle();

    poss.push_back({α0, p0, true, (i + 1) % N});
    poss.push_back({α1, p1, false, i});
  }

  sort(ALL(poss));

  ld base_ans = polygonArea2(points) / 2.;
  ld ans = base_ans;

  vector<P> now;
  set<ull> closed;
  for (ull i = 2 * N - 1; i < 2 * N; i--) {
    auto [α, p, is_start, j] = poss[i];
    if (is_start && !closed.count(j)) {
      now.push_back(points[j]);
    } else if (!is_start) {
      closed.insert(j);
    }
  }

  reverse(ALL(now));

  fore(i, 0, 2 * N) {
    auto [α, p, is_start, j] = poss[i];

    if (is_start) {
      now.push_back(points[j]);
    } else {
      assert(now[0] == points[j]);
      now.erase(now.begin());
    }

    assert(now.size() >= 2);

    P a = now[0], b = now.back();

    ld d = lineDist(a, b, P(0, 0));

    ld this_ans = base_ans - polygonArea2(now) / 2. + (a - b).dist() * ((ld)R - d) / 2;

    ans = max(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, R;
  cin >> N >> R;

  vector<P> points(N);
  for (auto& [X, Y] : points) {
    cin >> X >> Y;
  }

  auto ans = solve(R, points);
  cout << setprecision(10) << fixed;
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
