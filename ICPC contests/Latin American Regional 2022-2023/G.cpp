// https://codeforces.com/gym/104252/problem/G

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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

typedef Point<ll> P;

/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where p$ is as seen from s$ towards e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
 * If the optional argument eps$ is given 0 is returned if p$ is within distance eps$ from the line.
 * P is supposed to be Point<T> where T is e.g. double or ll.
 * It uses products in intermediate steps so watch out for overflow if using int or ll.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
template<class P>
ll sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
ll sideOf(const P& s, const P& e, const P& p, double eps) {
  auto a = (e-s).cross(p-s);
  double l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
}

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

/**
 * Author: Iván Renison
 * Date: 2024-07-30
 * License: CC0
 * Source: notebook el vasito
 * Description: Compute Minkowski sum of two strictly convex non empty polygons (i.e. two hulls).
 * Returns answer in CCW order.
 * The Minkowski sum of two polygons $$P$$ and $$Q$$ viewed as sets of $\mathbb{R}^2$ is defined as
 * $\{p + q : p \in P, q \in Q\}$
 * Time: O(n \log n + m \log m)
 * Status: stress-tested
*/
void reorder(vector<P> &p){
	if (sideOf(p[0], p[1], p[2]) < 0) reverse(ALL(p));
	rotate(p.begin(), min_element(ALL(p)), p.end());
}
vector<P> minkowskiSum(vector<P> p, vector<P> q) {
	if (min(SZ(p), SZ(q)) < 3) {
		vector<P> v;
		for (P pp : p) for (P qq : q) v.push_back(pp + qq);
		return convexHull(v);
	}
	reorder(p), reorder(q);
	fore(i, 0, 2) p.push_back(p[i]), q.push_back(q[i]);
	vector<P> r;
	ll i = 0, j = 0;
	while (i + 2 < SZ(p) || j + 2 < SZ(q)) {
		r.push_back(p[i] + q[j]);
		ll cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
		i += cross >= 0, j += cross <= 0;
	}
	return r;
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
  ll a = 1, b = SZ(l) - 1, r = !strict;
  if (SZ(l) < 3) return r && onSegment(l[0], l.back(), p);
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
    return false;
  while (abs(a - b) > 1) {
    ll c = (a + b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}

vb solve(const vector<P>& p, const vector<P>& q, const vector<P>& ps) {
  ull N = ps.size();

  vb ans(N, false);

  vector<P> sum = minkowskiSum(p, q); // (p + q)
  fore(i, 0, N) {
    if (inHull(sum, ps[i] * 2, false)) {
      ans[i] = true;
    }
  }

  // q + (q - p) = 2q - p
  vector<P> q2 = q;
  for (P& p : q2) {
    p = p * 2;
  }
  vector<P> notp = p;
  for (P& p : notp) {
    p = p * -1;
  }
  vector<P> diff = minkowskiSum(q2, notp);
  fore(i, 0, N) {
    if (inHull(diff, ps[i], false)) {
      ans[i] = true;
    }
  }

  // p + (p - q) = 2p - q
  vector<P> p2 = p;
  for (P& p : p2) {
    p = p * 2;
  }
  vector<P> notq = q;
  for (P& p : notq) {
    p = p * -1;
  }
  diff = minkowskiSum(p2, notq);
  fore(i, 0, N) {
    if (inHull(diff, ps[i], false)) {
      ans[i] = true;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull M0;
  cin >> M0;
  vector<P> p(M0);
  for (auto& [x, y] : p) {
    cin >> x >> y;
  }
  ull M1;
  cin >> M1;
  vector<P> q(M1);
  for (auto& [x, y] : q) {
    cin >> x >> y;
  }
  ull N;
  cin >> N;
  vector<P> ps(N);
  for (auto& [x, y] : ps) {
    cin >> x >> y;
  }

  vb ans = solve(p, q, ps);
  for (bool b : ans) {
    cout << (b ? 'Y' : 'N');
  }
  cout << '\n';

}
