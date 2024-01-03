// https://codeforces.com/gym/100861

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define DBG(x) cerr << #x << " = " << x << endl

#define M_PI 3.14159265358979323846
const ld eps = 1e-8;

template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
/*   bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z); } */
  P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
  P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
  P operator*(T d) const { return P(x*d, y*d, z*d); }
  P operator/(T d) const { return P(x/d, y/d, z/d); }
  T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
  P cross(R p) const {
    return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
  }
  T dist2() const { return x*x + y*y + z*z; }
  double dist() const { return sqrt((double)dist2()); }
  //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
  double phi() const { return atan2(y, x); }
  //Zenith angle (latitude) to the z-axis in interval [0, pi]
  double theta() const { return atan2(sqrt(x*x+y*y),z); }
  P unit() const { return *this/(T)dist(); } //makes dist()=1
  //returns unit vector normal to *this and p
  P normal(P p) const { return cross(p).unit(); }
  //returns point rotated 'angle' radians ccw around axis
  P rotate(double angle, P axis) const {
    double s = sin(angle), c = cos(angle); P u = axis.unit();
    return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
  }
};

typedef Point3D<ld> P;


// Returns the position on the sphere of radius R in witch the line r + tv intersects the sphere
optional<P> Rposition(ull R, P r, P v) {
  ld c = r.x * r.x + r.y * r.y + r.z * r.z - R * R;
  ld b = 2 * (r.x * v.x + r.y * v.y + r.z * v.z);
  ld a = v.x * v.x + v.y * v.y + v.z * v.z;
  assert(a > eps);

  ld disc = b * b - 4 * a * c;
  if (disc < -eps) {
    return {};
  }
  disc = max(disc, (ld)0.0);
  ld t = (-b - sqrt(disc)) / (2.0 * a);

  if (t <= eps) {
    ld t_ = (-b + sqrt(disc)) / (2.0 * a);
    assert(t_ < -eps);
    return {};
  } else {
    return r + v * t;
  }
}
/*
  R = |r + tv|
  R² = (r + tv).x² + (r + tv).y² + (r + tv).z²
  R² = (r.x + tv.x)² + (r.y + tv.y)² + (r.z + tv.z)²
  R² = r.x² + 2 r.x tv.x + t²v.x² + r.y² + 2 r.y tv.y + t²v.y² + r.z² + 2 r.z tv.z + t²v.z²
  R² = r.x² + r.y² + r.z² + 2 r.x tv.x + 2 r.y tv.y + 2 r.z tv.z + t²v.x² + t²v.y² + t²v.z²
  R² = r.x² + r.y² + r.z² + 2t(r.x v.x + r.y v.y + r.z v.z) + t²(v.x² + v.y² + v.z²)
*/

struct plane {
	P a,n; // n: normal unit vector
	plane(P a, P b, P c):a(a),n(((b-a).cross(c-a)).unit()){}
	plane(){}
/*	bool has(P p){return abs((p-a).dot(n))<=eps;}
 	ld angle(plane w){return acos(n.dot(w.n));}
	ld dist(P p){return abs((p-a).dot(n));} */
  ld signDist(P p){return (p-a).dot(n);}
  bool side(P p) {
    return (p - a).dot(n) > 0.0;
  }
/*	P proj(P p){inter(ln(p,p+n),p);return p;}
	bool inter(ln l, P& r){
		ld x=n.dot(l.p+l.pq-a),y=n.dot(l.p-a);
		if(abs(x-y)<=eps)return false;
		r=(l.p*x-(l.p+l.pq)*y)/(x-y);
		return true;
	}
 	bool inter(plane w, ln& r){
		P nn=n^w.n;P v=n^nn;ld d=w.n*v;
		if(abs(d)<=eps)return false;
		P p=a+v*(w.n*(w.a-a)/d);
		r=ln(p,p+nn);
		return true;
	} */
};

bool inSphereTriangle(P p0, P p1, P p2, P p) {
  plane pl(p0, p1, p2);
  plane pl0(p0, p1, P{0, 0});
  plane pl1(p1, p2, P{0, 0});
  plane pl2(p2, p0, P{0, 0});

  ld d0 = pl.signDist(P(0, 0, 0));
  assert(abs(d0) > eps);
  ld dp = pl.signDist(p);

  ld dp0 = pl0.signDist(p);
  ld dp1 = pl1.signDist(p);
  ld dp2 = pl2.signDist(p);

  if (abs(dp0) < eps || abs(dp1) < eps || abs(dp2) < eps) {
    return abs(dp) <= eps || d0 * dp < 0.0;
  }

  bool side0 = pl0.side(p);
  bool side1 = pl1.side(p);
  bool side2 = pl2.side(p);

  return (abs(dp) <= eps || d0 * dp < 0.0) && (side0 == side1 && side1 == side2);
}

// solve assuming that the sphere is centered at the origin
bool solve(ull R, vdd triangle, P r, P v) {
  optional<P> r1_ = Rposition(R, r, v);
  if (!r1_.has_value()) {
    return false;
  }
  P r1 = *r1_;

  auto [d0, l0] = triangle[0];
  auto [d1, l1] = triangle[1];
  auto [d2, l2] = triangle[2];

  P p0 = P(cos(d0) * cos(l0), cos(d0) * sin(l0), sin(d0)) * R;
  P p1 = P(cos(d1) * cos(l1), cos(d1) * sin(l1), sin(d1)) * R;
  P p2 = P(cos(d2) * cos(l2), cos(d2) * sin(l2), sin(d2)) * R;

  return inSphereTriangle(p0, p1, p2, r1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  P r0; ull R;
  cin >> r0.x >> r0.y >> r0.z >> R;
  vdd triangle(3);
  for (auto& [d, l] : triangle) {
    cin >> d >> l;
    d *= M_PI / 180.0;
    l *= M_PI / 180.0;
  }
  P r1, v;
  cin >> r1.x >> r1.y >> r1.z >> v.x >> v.y >> v.z;
  r1 = r1 - r0;

  if (solve(R, triangle, r1, v)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

  return EXIT_SUCCESS;
}
