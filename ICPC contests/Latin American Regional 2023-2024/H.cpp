// https://codeforces.com/gym/104736/problem/H
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long double ld;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ld eps = 1e-8;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
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
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(ld a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<ld> P;

pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(abs(s1.cross(e1, s2)) < eps), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  vector<P> res;
  fore(i,0,poly.size()) {
    P cur = poly[i], prev = i ? poly[i-1] : poly.back();
    bool side = s.cross(e, cur) < -eps;
    if (side != (s.cross(e, prev) < -eps))
      res.push_back(lineInter(s, e, cur, prev).second);
    if (side)
      res.push_back(cur);
  }
  return res;
}

ld lineDist(const P& a, const P& b, const P& p) {
  return (ld)(b-a).cross(p-a)/(b-a).dist();
}

optional<ull> solve(ld D, const vector<pair<P, P>>& lines) {
  ull N = lines.size();

  vector<P> poly;
  poly.push_back(P(D + 1.0, D + 1.0));
  poly.push_back(P(-D - 1.0, D + 1.0));
  poly.push_back(P(-D - 1.0, -D - 1.0));
  poly.push_back(P(D + 1.0, - D - 1.0));

  fore(i, 0, N) {
    auto [p0, p1] = lines[i];
    ld d = lineDist(p0, p1, P(0, 0));
    if (d > 0) {
      swap(p0, p1);
    }
    poly = polygonCut(poly, p0, p1);

    ld dist = 0;
    for (auto& p : poly) {
      dist = max(dist, p.dist());
    }

    if (dist < D) {
      return i;
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  ld D;
  cin >> N >> D;
  vector<pair<P, P>> lines(N);
  for (auto& [p0, p1] : lines) {
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
  }

  auto ans = solve(D, lines);
  if (ans.has_value()) {
    cout << *ans + 1;
  } else {
    cout << '*';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
