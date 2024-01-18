// https://matcomgrader.com/problem/9546/escape-polygon/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef __int128_t ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

istream& operator>>(istream& is, __int128_t& value) {
  long long x;
  is >> x;
  value = x;
  return is;
}

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
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

typedef Point<ll> P;

bool ordered_strait_line(P p0, P p1, P p2) {
  if (p0.x == p1.x) {
    return (p0.y <= p1.y && p1.y <= p2.y) || (p2.y <= p1.y && p1.y <= p0.y);
  } else {
    return (p0.x <= p1.x && p1.x <= p2.x) || (p2.x <= p1.x && p1.x <= p0.x);
  }
}

bool intersect_out(const vector<P>& XYs, ull i, ull j) {
  ull N = XYs.size();

  auto ap = lineInter(XYs[i % N], XYs[(i + 1) % N], XYs[j % N], XYs[(j + 1) % N]);
  int a = ap.first;
  P p = ap.second;
  if (a != 1) {
    return true;
  }

  return ordered_strait_line(XYs[i % N], XYs[(i + 1) % N], p);
}

ull solve(const vector<P>& XYs) {
  ull N = XYs.size();

  ull ans = N * (N - 1) * (N - 2) / 6;

  ull i = 0, j = 1;

  for(; i < N; i++) {
    while(intersect_out(XYs, i, j + 1)) {
      j++;
    }

    ans -= (j - i) * (j - i - 1) / 2;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<P> XYs(N);
  for(auto& p : XYs) {
    cin >> p.x >> p.y;
  }

  auto ans = solve(XYs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
