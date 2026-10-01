// https://codeforces.com/gym/106682/problem/G
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef vector<ull> vu;
typedef vector<uu> vuu;
typedef long double ld;
ld eps = 1e-9;


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

	P pendiente() {
		if (x == 0 && y == 0) {
			return P(0, 0);
		}
		if (x == 0) {
			return P(0, 1);
		}
		if (y == 0) {
			return P(1, 0);
		}
		ll sig = sgn(x) * sgn(y);
		ll num = abs(x);
		ll dem = abs(y);

		ll g = gcd(num, dem);

		num /= g;
		dem /= g;
		num *= sig;

		return P(num, dem);
	}
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
ll sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

ull solve(vector<P> ps) {
	for (auto& [X, Y] : ps) {
		X *= 2, Y *= 2;
	}
	sort(ALL(ps));
	ull N = ps.size();

	auto search_same_pend = [&](const vu& is, P s, P t) -> uu {
		// Calcula cuantos puntos de is están a la derecha, izquierda de la linea s, t

		P x = (s + t) / 2;

		ull l = 0, r = is.size();

		if (x < ps[is[l]]) {
			return {0, is.size()};
		}
		while (l + 1 < r) {
			ull m = (l + r) / 2;

			if (ps[is[m]] < x || ps[is[m]] == x) {
				l = m;
			} else {
				r = m;
			}
		}

		if (ps[is[l]] == x) {
			return {l, is.size() - l - 1};
		}

		return {l + 1, is.size() - l - 1};
	};

	map<ull, vu> radios;
	map<P, vu> pendientes;
	fore(i, 0, N) {
		P p = ps[i];

		radios[p.dist2()].push_back(i);
		pendientes[p.pendiente()].push_back(i);
	}

	fore(i, 0, N) {
		P p = ps[i];

		if (p == P(0, 0)) {
			for (auto& [pend, is] : pendientes) {
				is.push_back(i);
				sort(ALL(is));
			}

			break;
		}
	}

	ull ans = 0;
	ull ans2 = 0;

	for (auto& [r, is] : radios) {
		for (ull i : is) for (ull j : is) if (i < j) {
			P p = ps[i], q = ps[j];
			//assert(!(p == q));

			P pend = (p + q).pendiente();

			if (pend == P(0, 0)) {
				P p_perp = p.perp();
				if (p_perp.y >= 0) {
					pend = p_perp;
				} else {
					pend = q.perp();
				}
				pend = pend.pendiente();
			}

			if (pendientes.count(pend)) {
				vu& ks = pendientes[pend];

				auto [count_neg, count_pos] = search_same_pend(ks, p, q);

				ans += count_neg * count_pos;
			}
		}
	}

	map<P, ull> ops;
	for (P p : ps) {
		if (binary_search(ALL(ps), p.perp().perp())) {
			ops[p.pendiente()]++;
		}
	}
	for (auto [p, c] : ops) {
		if (ops.count(p.perp())) {
			ans2 += c * ops[p.perp()];
		}
	}

	//cerr << "ans: " << ans << endl;
	//cerr << "ans2: " << ans2 << endl;
	ans -= ans2 / 4;

	return ans;
}

void prueba() {
	vu counts(2e8 + 1);
	fore(x, 1, 1001) fore(y, 1, 1001) {
		counts[x * x + y * y]++;
	}

	ull M = *max_element(ALL(counts));

	cerr << M << endl;
}

void genWorstCase() {
	// Gen case
	ull N = 1e5;

	vector<vuu> apps(2e8 + 1);

	set<ii> set_ps;
	fore(x, 1, 1001) fore(y, 1, 1001) {
		apps[x * x + y * y].push_back({x, y});
	}

	sort(ALL(apps), [](const vuu& a, const vuu& b) {
		return a.size() > b.size();
	});

	fore(r, 0, apps.size()) {
		for (auto [X, Y] : apps[r]) {
			if (set_ps.size() < N) {
				set_ps.insert({X, Y});
			}
		}
	}

	cout << N << '\n';
	for (auto [X, Y] : set_ps) {
		cout << X << ' ' << Y << '\n';
	}
	exit(0);
}


/** Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Status:
 */
bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

/** Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:
 * \descriptionimage{content/geometry/SegmentIntersection}
 * If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
 * If no intersection point exists an empty vector is returned.
 * If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
 * The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
 * Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (SZ(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */
vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
			 oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {ALL(s)};
}

bool segPerp(P p, P q, P s, P t) {
	P pq = q - p;
	P st = t - s;
	return pq.dot(st) == 0;
}

bool colinear(P a, P b, P c) {
	return a.cross(b, c) == 0;
}

bool segPerpInMiddle(P p, P q, P s, P t) { // st corta a pq en la mitad
	P pq = q - p;
	P st = t - s;
	if (pq.dot(st) != 0) {
		return false;
	}

	P x2 = (p + q);

	if (colinear(s * 2, t * 2, x2)) {
		return true;
	}

	return false;
}

bool esCruz(P A, P B, P C, P D) {
/*
  A
	|
C-+-D
	|
	B

With 0 in AB
*/
	if (colinear(A, B, C) || colinear(A, B, D) || colinear(A, C, D) || colinear(B, C, D)) {
		return false;
	}

	P p, q, s, t;

	if (segPerp(A, B, C, D)) {
		p = A, q = B, s = C, t = D;
	} else if (segPerp(A, C, B, D)) {
		p = A, q = C, s = B, t = D;
	} else if (segPerp(A, D, B, C)) {
		p = A, q = D, s = B, t = C;
	} else {
		return false;
	}

	vector<P> xs = segInter(p, q, s, t);
	if (xs.size() != 1) {
		return false;
	}

	if (segPerpInMiddle(p, q, s, t)) { // st corta a pq en la mitad
		if (colinear(s, t, P(0, 0))) {
			return true;
		}
	}
	if (segPerpInMiddle(s, t, p, q)) { // pq corta a st en la mitad
		if (colinear(p, q, P(0, 0))) {
			return true;
		}
	}

	return false;
}

ull force(vector<P> ps) {
	ull N = ps.size();

	ull ans = 0;
	fore(i, 0, N) fore(j, 0, i) fore(k, 0, j) fore(l, 0, k) {
		if (esCruz(ps[i], ps[j], ps[k], ps[l])) {
			ans++;
		}
	}

	return ans;
}

void test() {
	fore(_, 0, 100000) {
		ull N = rand() % 10 + 1;

		set<P> set_ps;
		fore(i, 0, N) {
			set_ps.insert(P(rand() % 10 - 5, rand() % 10 - 5));
		}

		vector<P> ps(ALL(set_ps));

		ull ans = solve(ps);
		ull ansf = force(ps);

		if (ans != ansf) {
			cerr << "ERROR:\n";
			cerr << ps.size() << '\n';
			for (auto [X, Y] : ps) {
				cout << X << ' ' << Y << '\n';
			}
			cerr << "ans: " << ans << "\nansf: " << ansf << endl;
			exit(1);
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	//prueba();
#ifdef DEBUG
	test();
	exit(0);
#else

	// Gen case
	// {
	// 	ull N = 1e5;
	// 	ull maxCoord = 1e4;

	// 	set<ii> set_ps;
	// 	while (set_ps.size() < N) {
	// 		set_ps.insert({rand() % (2 * maxCoord + 1) - maxCoord, rand() % (2 * maxCoord + 1) - maxCoord});
	// 	}

	// 	cout << N << '\n';
	// 	for (auto [X, Y] : set_ps) {
	// 		cout << X << ' ' << Y << '\n';
	// 	}
	// 	exit(0);
	// }

	//genWorstCase();


	ull N;
	cin >> N;
	vector<P> ps(N);
	for (auto& [X, Y] : ps) {
		cin >> X >> Y;
	}


	auto ans = solve(ps);
	cout << ans << '\n';
#endif

}

