// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/J
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

const ld eps = 1e-10;
const ld inf = 1e60;

/** Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid ll.)
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
  ld angle(P p) { // redefine acos for values out of range
    return acos(dot(p)/(dist()*p.dist()));
  }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(ld a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  P rot(P r){return P(cross(r),dot(r));}
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;

template<class P>
ll sideOf(const P& s, const P& e, const P& p, double eps) {
  auto a = (e-s).cross(p-s);
  double l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
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
It uses products in intermediate steps so watch out for overflow if using ll or ll.
Using Point3D will always give a non-negative distance. For Point3D, call .dist on the result of the cross product.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
ld lineDist(const P& a, const P& b, const P& p) {
  return (ld)(b-a).cross(p-a)/(b-a).dist();
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
Products of three coordinates are used in intermediate steps so watch out for overflow if using ll or ll.
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
    return {-(abs(s1.cross(e1, s2)) < eps), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

enum TY { BAD, JUST, GOOD };
TY type(P p, P q, P a, P b, P c) {
  auto inter = lineInter(p, q, b, c);
  if (inter.first <= 0) {
    return JUST;
  }

  ld ad = lineDist(p, q, a);
  ld bd = lineDist(p, q, b);
  ld cd = lineDist(p, q, c);

  if (ad >= bd - eps && cd >= bd - eps) {
    return GOOD;
  } else {
    return BAD;
  }
}

/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using ll as T!
 * Status: Stress-tested and tested on kattis:polygonarea
 */
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
  return a;
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

void reorder(vector<P> &p){
	if (sideOf(p[0], p[1], p[2], eps) < 0) reverse(ALL(p));
	rotate(p.begin(), min_element(ALL(p)), p.end());
}
vector<P> minkowskiSum(vector<P> p, vector<P> q) {
	if (min(SZ(p), SZ(q)) < 3) {
		vector<P> v;
		for (P pp : p) for (P qq : q) v.pb(pp + qq);
		return convexHull(v);
	}
	reorder(p), reorder(q);
	fore(i, 0, 2) p.pb(p[i]), q.pb(q[i]);
	vector<P> r;
	ll i = 0, j = 0;
	while (i + 2 < SZ(p) || j + 2 < SZ(q)) {
		r.pb(p[i] + q[j]);
		ld cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
		i += cross >= -eps, j += cross <= eps;
	}
	return r;
}

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
ll sideOf(const P& s, const P& e, const P& p, ld eps) {
  auto a = (e-s).cross(p-s);
  ld l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
}

typedef pair<P, P> Line;
#define L(a) a.fst, a.snd

ll angDiff(Line a, Line b) {
	return sgn((a.snd-a.fst).angle() - (b.snd-b.fst).angle());
}
vector<P> halfPlaneIntersection(vector<Line> v) {
	sort(ALL(v), [&](Line a, Line b) {
		ll s = angDiff(a, b);
		return (s ? s : sideOf(L(a), b.fst)) < 0;
	});
	ll ah = 0, at = 0, n = SZ(v);
	vector<Line> deq(n + 1);
	vector<P> ans(n);
	deq[0] = v[0];
	fore(i, 1, n + 1) {
		if (i == n) v.pb(deq[ah]);
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

ld solve(const vector<P>& A, const vector<P>& B) {
  ll N = A.size(), M = B.size();

  ll j = 0;

  vector<pair<P, P>> planes;
  fore(i, 0, N) {
    P p = A[i], q = A[(i+1)%N];

    while (true) {
      P a = B[j%M], b = B[(j+1)%M], c = B[(j+2)%M];
      TY ty = type(p, q, a, b, c);
      if (ty == GOOD) {
        j = (j + M - 1) % M;
      } else {
        break;
      }
    }

    while (true) {
      P a = B[j%M], b = B[(j+1)%M], c = B[(j+2)%M];
      TY ty = type(p, q, a, b, c);

      if (ty == GOOD || ty == JUST) {
        P d = b - B[0];

        planes.push_back({p - d, q - d});
      }
      if (ty == GOOD) {
        break;
      }
      j++;
    }
  }

  vector<P> poly = halfPlaneIntersection(planes);

  vector<P> poly_ans = minkowskiSum(B, poly);
  ld ans = polygonArea2(poly_ans) / 2.0;

  return ans;
}


signed main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M;
  cin >> N >> M;
  vector<P> A(N), B(M);
  for (auto& [x, y] : A) {
    ll a, b;
    cin >> a >> b;
    x = a, y = b;
  }
  for (auto& [x, y] : B) {
    ll a, b;
    cin >> a >> b;
    x = a, y = b;
  }

  ld ans = solve(A, B);
  cout << setprecision(8) << fixed;
  cout << ans << '\n';
}
