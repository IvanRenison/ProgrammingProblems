// https://codeforces.com/group/YjFmW2O15Q/contest/101919

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<uuuu> vuuuu;
typedef vector<uuuuu> vuuuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

typedef long double ld;

constexpr ld inf = numeric_limits<ld>::infinity();
constexpr ld eps = 1e-9;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return x < p.x || (abs(x - p.x) < eps && y < p.y); }
	bool operator==(P p) const { return abs(x - p.x) < eps && ans(y - p.y) < eps; }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
  ld dist(P p) const { return (*this - p).dist(); }
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

typedef Point<ld> P;

P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

ld lineDist(P a, P b, P p) {
	return (ld)(b-a).cross(p-a)/(b-a).dist();
}

bool colinear(P a, P b, P c) {
  return abs(lineDist(a, b, c)) < eps;
}

bool colinear(P a, P b, P c, P d) {
  return colinear(a, b, c) && colinear(a, b, d);
}

bool colinear(P a, P b, P c, P d, P e) {
  return colinear(a, b, c, d) && colinear(a, b, e);
}

typedef vector<P> vP;

// -1.0 means no solutions
ld try3_else(const vP& XYs) {
  if (colinear(XYs[0], XYs[1], XYs[2])) {
    return -1.0;
  }

  ull N = XYs.size();

  P c = ccCenter(XYs[0], XYs[1], XYs[2]);
  ld r0 = c.dist(XYs[0]);
  ld r1 = -1.0;

  fore(i, 3, N) {
    ld r = c.dist(XYs[i]);
    if (abs(r - r0) < eps) {
      continue;
    }

    if (r1 < 0) {
      r1 = r;
    } else if (abs(r - r1) > eps) {
      return -1.0;
    }
  }

  if (r1 < 0) {
    return inf;
  } else {
    return abs(r0 - r1)/2.0;
  }
}

pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (abs(d) < eps) // if parallel
		return {-(abs(s1.cross(e1, s2)) < eps), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

// -1.0 means no solutions
ld try2_2(P a, P b, P c, P d) {
  P m0 = (a + b)/2.0;
  P e0 = (b - m0).perp() + m0;

  P m1 = (c + d)/2.0;
  P e1 = (d - m1).perp() + m1;

  auto [s, p] = lineInter(m0, e0, m1, e1);


  if (s == 1) {
    ld d0 = p.dist(a);
    ld d1 = p.dist(c);

    // cerr << "a: " << a << " b: " << b << " c: " << c << " d: " << d << endl;
    // cerr << "p: " << p << " r: " << min(d0, d1) + abs(d0 - d1)/2.0 << " ans: " << abs(d0 - d1)/2.0 << endl;

    return abs(d0 - d1)/2.0;
  } else if (s == 0) {
    return -1.0;
  } else {
    return m0.dist(m1);
  }
}

// -1.0 means no solutions
ld solve(vP XYs) {
  ull N = XYs.size();

  if (N <= 2) {
    return inf;
  } else if (N == 3) {
    if (colinear(XYs[0], XYs[1], XYs[2])) {
      sort(XYs.begin(), XYs.end());
      ld d01 = XYs[0].dist(XYs[1]);
      ld d12 = XYs[1].dist(XYs[2]);

      return max(d01, d12) / 2.0;
    } else {
      return inf;
    }
  } else if (N == 4) {
    if (colinear(XYs[0], XYs[1], XYs[2], XYs[3])) {
      sort(XYs.begin(), XYs.end());
      ld d01 = XYs[0].dist(XYs[1]);
      ld d23 = XYs[2].dist(XYs[3]);

      if (abs(d01 - d23) < eps) {
        return d01/2.0;
      } else {
        return -1.0;
      }
    } else {
      ld ans = try3_else(XYs);
      fore(i, 0, 3) {
        swap(XYs[3], XYs[i]);
        ld this_ans = try3_else(XYs);
        ans = max(ans, this_ans);
      }

      // Try two in two out
      vuuuu options = {
        {0,1,2,3}, {0,2,1,3}, {0,3,1,2}
      };
      for (auto [i0, i1, j0, j1] : options) {
        ld this_ans = try2_2(XYs[i0], XYs[i1], XYs[j0], XYs[j1]);
        ans = max(ans, this_ans);
      }

      return ans;
    }
  } else {
    if (colinear(XYs[0], XYs[1], XYs[2], XYs[3], XYs[4])) {
      return -1.0;
    } else {
      vuuuuu options = {
        {2,3,4,0,1}, {1,3,4,0,2}, {1,2,4,0,3}, {1,2,3,0,4},
        {0,3,4,1,2}, {0,2,4,1,3}, {0,2,3,1,4}, {0,1,4,2,3}, {0,1,3,2,4}
      };

      ld ans = try3_else(XYs);
      for(auto [i0, i1, i2, j0, j1] : options) {
        P temp0 = XYs[0], temp1 = XYs[1], temp2 = XYs[2], temp3 = XYs[3], temp4 = XYs[4];
        P tempi0 = XYs[i0], tempi1 = XYs[i1], tempi2 = XYs[i2], tempj0 = XYs[j0], tempj1 = XYs[j1];
        XYs[0] = tempi0, XYs[1] = tempi1, XYs[2] = tempi2, XYs[3] = tempj0, XYs[4] = tempj1;

        ld this_ans = try3_else(XYs);
        ans = max(ans, this_ans);

        XYs[0] = temp0, XYs[1] = temp1, XYs[2] = temp2, XYs[3] = temp3, XYs[4] = temp4;
      }

      return ans;
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;

  vP XYs(N);
  for(auto& P : XYs) {
    cin >> P.x >> P.y;
  }

  auto ans = solve(XYs);
  if (ans < 0.0) {
    cout << "NO\n";
  } else if (ans == inf) {
    cout << "INF\n";
  } else {
    cout << setprecision(2) << fixed << ans << '\n';
  }

  return EXIT_SUCCESS;
}
