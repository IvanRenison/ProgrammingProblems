// https://codeforces.com/gym/102299/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

/**
 * Author: Ulf Lundstrom
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

/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * Status: tested
 */
typedef Point<double> P;
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: stress-tested
 */
pair<P, double> mec(vector<P> ps) {
	shuffle(ps.begin(), ps.end(), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	fore(i,0,ps.size()) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		fore(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			fore(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}

tuple<double, double, double> solve(vector<pair<double, double>> ctis) {
  ull n = ctis.size();

  vector<P> ps(n);
  fore(i, 0, n) {
    auto [ct, ci] = ctis[i];
    ps[i] = P(ct, ci);
  }

  auto [p, r] = mec(ps);
  auto [pt, pi] = p;
  double t = r * r / 2.0;

  return {pt, pi, t};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  cout << setprecision(9);

  ull n;
  cin >> n;
  vector<pair<double, double>> ctis(n);
  for(auto& [x, y] : ctis) {
    cin >> x >> y;
  }

  auto [pt, pi, t] = solve(ctis);
  cout << pt << ' ' << pi << ' ' << t << '\n';

  return EXIT_SUCCESS;
}

/*

T(c, p) = (pt² + pi² + ct² + ci²)/2
I(c, p) = ct * pt + ci * pi


    T(c, p) - I(c, p) ≤ t
⇔
    (pt² + pi² + ct² + ci²)/2 - (ct * pt + ci * pi) ≤ t
⇔
    pt² + pi² + ct² + ci² - 2ct * pt - 2ci * pi ≤ 2t
⇔
    pt² - 2ct * pt + ct² + pi² - 2ci * pi + ci² ≤ 2t
⇔
    (pt - ct)² + (pi - ci)² ≤ 2t
⇔
    √((pt - ct)² + (pi - ci)²) ≤ √(2t)
⇔
    √((ct - pt)² + (ci - pi)²) ≤ √(2t)




x = √(2t)
t = x²/2

*/
