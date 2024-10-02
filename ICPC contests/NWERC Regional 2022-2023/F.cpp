// https://codeforces.com/gym/104875

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ll inf = 1ull << 30;

/** Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
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
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
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
typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P> h(sz(pts)+1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(all(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

/** Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Status:
 */
template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where p$ is as seen from s$ towards e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
 * If the optional argument eps$ is given 0 is returned if p$ is within distance eps$ from the line.
 * P is supposed to be Point<T> where T is e.g. double or long long.
 * It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
  auto a = (e-s).cross(p-s);
  double l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
}

/** Author: chilli
 * Date: 2019-05-17
 * License: CC0
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
 * Description: Determine whether a point t lies inside a convex hull (CCW
 * order, with no collinear points). Returns true if point lies within
 * the hull. If strict is true, points on the boundary aren't included.
 * Usage:
 * Status: stress-tested
 * Time: O(\log N)
 */
typedef Point<ll> P;

bool inHull(const vector<P>& l, P p, bool strict = true) {
  int a = 1, b = sz(l) - 1, r = !strict;
  if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}




bool polyIncide(vector<P>& a, vector<P>& b) {
  for (P p : a) {
    if (inHull(b, p)) {
      return true;
    }
  }
  for (P p : b) {
    if (inHull(a, p)) {
      return true;
    }
  }
  return false;
}

bool solve(vector<pair<P, P>>& points) {
  ull n = points.size();

  for (auto [p0, p1] : points) {
    if (p0.x > p1.x) {
      swap(p0, p1);
    }
    if (p0.y > p1.y) {
      swap(p0.y, p1.y);
    }
  }

  { // Negative diagonals
    vector<P> upper(n), lower(n);

    fore(i, 0, n) {
      upper[i] = points[i].second;
      lower[i] = points[i].first;
    }

    ll min_x_upper = inf, min_y_upper = inf;
    ll max_x_lower = -inf, max_y_lower = -inf;

    for (P p : upper) {
      min_x_upper = min(min_x_upper, p.x);
      min_y_upper = min(min_y_upper, p.y);
    }
    for (P p : lower) {
      max_x_lower = max(max_x_lower, p.x);
      max_y_lower = max(max_y_lower, p.y);
    }

    upper.push_back(P{min_x_upper, inf});
    upper.push_back(P{inf, min_y_upper});
    lower.push_back(P{max_x_lower, -inf});
    lower.push_back(P{-inf, max_y_lower});


    upper = convexHull(upper);
    lower = convexHull(lower);

    if (!polyIncide(upper, lower)) {
      return true;
    }
  }

  { // Positive diagonals
    vector<P> upper(n), lower(n);
    fore(i, 0, n) {
      upper[i] = points[i].first;
      lower[i] = points[i].second;
      swap(upper[i].y, lower[i].y);
    }

    ll max_x_upper = -inf, min_y_upper = inf;
    ll min_x_lower = inf, max_y_lower = -inf;

    for (P p : upper) {
      max_x_upper = max(max_x_upper, p.x);
      min_y_upper = min(min_y_upper, p.y);
    }
    for (P p : lower) {
      min_x_lower = min(min_x_lower, p.x);
      max_y_lower = max(max_y_lower, p.y);
    }

    upper.push_back(P{max_x_upper, inf});
    upper.push_back(P{-inf, min_y_upper});
    lower.push_back(P{min_x_lower, -inf});
    lower.push_back(P{inf, max_y_lower});

    upper = convexHull(upper);
    lower = convexHull(lower);

    if (!polyIncide(upper, lower)) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;

  vector<pair<P, P>> points(n);
  for (auto& [p0, p1] : points) {
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
  }

  bool ans = solve(points);
  if (ans) {
    cout << "possible\n";
  } else {
    cout << "impossible\n";
  }

  return EXIT_SUCCESS;
}
