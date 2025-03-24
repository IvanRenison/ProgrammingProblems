// https://codeforces.com/gym/105789/problem/J
#include <bits/stdc++.h>
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i, a, b) for(ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

const double pi = acos(-1);


/** Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or ll.
 * Usage:
 * Status: tested, except for phi and theta
 */
template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
  bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z); }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z); }
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

/** Author: Johan Sannemo
 * Date: 2017-04-18
 * Source: derived from https://gist.github.com/msg555/4963794 by Mark Gordon
 * Description: Computes all faces of the 3-dimension hull of a point set.
 *  *No four points must be coplanar*, or else random results will be returned.
 *  All faces will point outwards.
 * Time: O(n^2)
 * Status: tested on SPOJ CH3D
 */
typedef Point3D<double> P3;

struct PR {
  void ins(ll x) { (a == -1 ? a : b) = x; }
  void rem(ll x) { (a == x ? a : b) = -1; }
  ll cnt() { return (a != -1) + (b != -1); }
  ll a, b;
};

struct F { P3 q; ll a, b, c; };

vector<F> hull3d(const vector<P3>& A) {
  assert(SZ(A) >= 4);
  vector<vector<PR>> E(SZ(A), vector<PR>(SZ(A), {-1, -1}));
#define E(x,y) E[f.x][f.y]
  vector<F> FS;
  auto mf = [&](ll i, ll j, ll k, ll l) {
    P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
    if (q.dot(A[l]) > q.dot(A[i]))
      q = q * -1;
    F f{q, i, j, k};
    E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
    FS.pb(f);
  };
  fore(i,0,4) fore(j,i+1,4) fore(k,j+1,4)
    mf(i, j, k, 6 - i - j - k);

  fore(i,4,SZ(A)) {
    for (ll j = 0; j < SZ(FS); j++) {
      F f = FS[j];
      if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
        E(a,b).rem(f.c);
        E(a,c).rem(f.b);
        E(b,c).rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    ll nw = SZ(FS);
    fore(j,0,nw) {
      F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
      C(a, b, c); C(a, c, b); C(b, c, a);
    }
  }
  for (F& it : FS) if ((A[it.b] - A[it.a]).cross(
    A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
  return FS;
};



double max_angle(P3 p, vector<P3>& points) {
  double ans = pi / 2;
  for (P3& q : points) {
    ans = min(ans, acos(p.dot(q)));
  }
  return ans;
}

double solve(vector<P3>& points) {
  ll N = points.size();

  if (N <= 3) {
    return pi / 2;
  }

  for (auto& [x, y, z] : points) {
    x = x + 1e-9 * (double)(rand() % 1000 - 500);
    y = y + 1e-9 * (double)(rand() % 1000 - 500);
    z = z + 1e-9 * (double)(rand() % 1000 - 500);
  }

  for (P3& p : points) {
    p = p / p.dist();
  }

  vector<F> faces = hull3d(points);

  vector<P3> cands;
  for (auto& [p, a, b, c] : faces) {
    p = p / p.dist();
    cands.push_back(p);
  }

  double ans = 0;
  for (P3 p : cands) {
    ans = max(ans, max_angle(p, points));
  }

  return ans;
}


int main() {
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  vector<P3> points(N);
  for (auto& [X, Y, Z] : points) {
    ll x, y, z;
    cin >> x >> y >> z;
    X = x, Y = y, Z = z ;
  }

  double ans = solve(points);
  ans = ans * 180 / pi;
  cout << setprecision(8) << ans << '\n';

}
