// https://codeforces.com/gym/101309

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#pragma GCC optimize("Ofast")
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
typedef vector<double> vd;
typedef pair<double, double> dd;
typedef vector<dd> vdd;
typedef tuple<double, double, double> ddd;
typedef vector<ddd> vddd;
typedef tuple<double, double, double, double> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const double eps = 1e-11;


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
template<class P>
pair<ll, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

/**
 * Author: chilli and Iván Renison
 * Date: 2019-05-05
 * License: CC0
 * Source: https://github.com/zimpha/algorithmic-library/blob/master/computational-geometry/polygon.cc
 * Description: Computes the intersection of a set of half-planes. Input is given as a set of planes, facing left.
 * The intersection must form a convex polygon or be empty. Output is the convex polygon representing the intersection.
 * The points may have duplicates and be collinear. Will not fail catastrophically if `eps > sqrt(2)(line intersection error)`.
 * Likely to work for more ranges if 3 half planes are guaranteed to never intersect at the same point.
 * Time: O(n \log n)
 * Status: stress-tested
 */
typedef Point<double> P;
struct Line {
  P first, second;
  double alfa;
  Line() {}
  Line(P a, P b) : first(a), second(b), alfa((b - a).angle()) {}
};
#define L(a) a.first, a.second

ll angDiff(Line a, Line b) {
	return sgn((a.second-a.first).angle() - (b.second-b.first).angle());
}
vector<P> halfPlaneIntersection(vector<Line>& v) {
	const double eps = sqrt(2) * 1e-8;
	sort(ALL(v), [&](Line a, Line b) {
    return a.alfa < b.alfa;
	});
	ll ah = 0, at = 0, n = SZ(v);
	vector<Line> deq(n + 1);
	vector<P> ans(n);
	deq[0] = v[0];
	fore(i, 1, n + 1) {
		if (i == n) v.push_back(deq[ah]);
		if (angDiff(v[i], v[i - 1])) {
			while (ah < at && sideOf(L(v[i]), ans[at-1], eps) < 0)
				at--;
			while (i < n && ah < at && sideOf(L(v[i]),ans[ah],eps)<0)
				ah++;
			auto [r, p] = lineInter(L(v[i]), L(deq[at]));
			if (r == 1) ans[at++] = p, deq[at] = v[i];
		}
	}
	if (at - ah < 3) return {};
	return {ans.begin() + ah, ans.begin() + at};
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


ull solve(vector<P>& points) {
  ull n = points.size();

  ll l = 0, r = n - 2;
  while (l + 1 < r) {
    ll m = (l + r) / 2;

    vector<Line> lines(n);
    fore(i, 0, n) {
      lines[i] = {points[(i + m + 1) % n], points[i]};
    }

    vector<P> poly = halfPlaneIntersection(lines);

    double area = poly.size() <= 2 ? 0 : polygonArea2(poly);

    if (area <= eps) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

int main(void) {
  ios::sync_with_stdio(0), cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("jungle.in","r",stdin);
  freopen("jungle.out","w",stdout);
#endif

  ull n;
  cin >> n;
  vector<P> points(n);
  for (auto& [x, y] : points) {
    ll X, Y;
    cin >> X >> Y;
    x = X, y = Y;
  }

  auto ans = solve(points);
  cout << ans << '\n';

}
