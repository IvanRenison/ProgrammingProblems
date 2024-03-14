// https://redprogramacioncompetitiva.com/contests/2024/02/

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
const ld eps = 1e-15;

/** Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> ll sgn(T x) { return (x > 0) - (x < 0); }
typedef ll T;
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  //bool operator==(P p) const { return abs(x - p.x < eps) && abs(y - p.y) < eps; }
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

typedef Point P;

typedef array<P, 4> A4;

bool equalSides(A4 ps) {
  vi sides2(4);
  fore(i, 0, 4) {
    sides2[i] = (ps[i] - ps[(i + 1) % 4]).dist2();
  }

  fore(i, 0, 4) {
    if (sides2[i] != sides2[(i + 1) % 4]) {
      return false;
    }
  }

  return true;
}

bool equalAngle(A4 ps) {
  vi angles(4);
  fore(i, 0, 4) {
    angles[i] = ps[(i + 1) % 4].cross(ps[i], ps[(i + 2) % 4]);
  }

  fore(i, 0, 4) {
    if (angles[i] != angles[(i + 1) % 4]) {
      return false;
    }
  }

  return true;
}


bool Square(A4 ps) {
  if (!equalSides(ps)) {
    return false;
  }

  vi diags(2);
  diags[0] = (ps[0] - ps[2]).dist2();
  diags[1] = (ps[1] - ps[3]).dist2();

  return diags[0] == diags[1];
}

bool Rectangle(A4 ps) {
  vi diags(2);
  diags[0] = (ps[0] - ps[2]).dist2();
  diags[1] = (ps[1] - ps[3]).dist2();

  if (diags[0] != diags[1]) {
    return false;
  }

  vi sides2(4);
  fore(i, 0, 4) {
    sides2[i] = (ps[i] - ps[(i + 1) % 4]).dist2();
  }

  return sides2[0] == sides2[2] && sides2[1] == sides2[3];
}

bool rhombus(A4 ps) {
  return equalSides(ps);
}

bool paralelLines(P a, P b, P c, P d) {
  return (a - b).cross(c - d) == 0;
}

bool parallelogram(A4 ps) {
  return paralelLines(ps[0], ps[1], ps[3], ps[2]) && paralelLines(ps[1], ps[2], ps[0], ps[3]);
}

bool trapezium(A4 ps) {
  return paralelLines(ps[0], ps[1], ps[3], ps[2]) || paralelLines(ps[1], ps[2], ps[0], ps[3]);
}

// A kite has reflection symmetry across a diagonal
bool kite(A4 ps) {
  ll s0 = (ps[0] - ps[1]).dist2();
  ll s1 = (ps[0] - ps[3]).dist2();

  ll s2 = (ps[2] - ps[1]).dist2();
  ll s3 = (ps[2] - ps[3]).dist2();

  if (s0 == s1 && s2 == s3) {
    return true;
  }

  s0 = (ps[3] - ps[0]).dist2();
  s1 = (ps[3] - ps[2]).dist2();

  s2 = (ps[1] - ps[0]).dist2();
  s3 = (ps[1] - ps[2]).dist2();

  if (s0 == s1 && s2 == s3) {
    return true;
  }

  return false;
}

string solve(A4 ps) {
  if (Square(ps)) {
    return "square";
  }

  if (Rectangle(ps)) {
    return "rectangle";
  }

  if (rhombus(ps)) {
    return "rhombus";
  }

  if (parallelogram(ps)) {
    return "parallelogram";
  }

  if (trapezium(ps)) {
    return "trapezium";
  }

  if (kite(ps)) {
    return "kite";
  }

  return "none";
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  P p0, p1, p2, p3;
  cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

  auto ans = solve({p0, p1, p2, p3});
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
