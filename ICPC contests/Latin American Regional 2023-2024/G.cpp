// https://codeforces.com/gym/104736/problem/G
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

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

typedef Point<ll> P;

bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

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
  return {all(s)};
}

struct Ans {
  vector<pair<P, P>> lines;
  vector<P> points;
};

Ans join(const Ans& a, const Ans& b) {
  Ans ans;
  for (auto [pa0, pa1] : a.lines) {
    for (auto [pb0, pb1] : b.lines) {
      auto inter = segInter(pa0, pa1, pb0, pb1);
      if (inter.size() == 1) {
        ans.points.push_back(inter[0]);
      } else if (inter.size() == 2) {
        ans.lines.push_back({inter[0], inter[1]});
      }
    }
  }
  for (auto pa : a.points) {
    for (auto [pb0, pb1] : b.lines) {
      if (onSegment(pb0, pb1, pa)) {
        ans.points.push_back(pa);
      }
    }
  }
  for (auto pb : b.points) {
    for (auto [pa0, pa1] : a.lines) {
      if (onSegment(pa0, pa1, pb)) {
        ans.points.push_back(pb);
      }
    }
  }
  for (auto pa : a.points) {
    for (auto pb : b.points) {
      if (pa == pb) {
        ans.points.push_back(pa);
      }
    }
  }
  sort(all(ans.lines));
  sort(all(ans.points));
  ans.lines.erase(unique(all(ans.lines)), ans.lines.end());
  ans.points.erase(unique(all(ans.points)), ans.points.end());
  //assert(ans.lines.size() <= 4);
  //assert(ans.points.size() <= 2);
  return ans;
}

Ans newAns(P p, ll D) {
  auto [x, y] = p;
  Ans ans;
  ans.lines.push_back({P{x + D, y}, P{x, y + D}});
  ans.lines.push_back({P{x, y + D}, P{x - D, y}});
  ans.lines.push_back({P{x - D, y}, P{x, y - D}});
  ans.lines.push_back({P{x, y - D}, P{x + D, y}});
  return ans;
}

vector<P> calcPoints(const Ans& ans) {
  vector<P> res = ans.points;
  for (auto [p0, p1] : ans.lines) {
    if (p1 < p0) {
      swap(p0, p1);
    }
    ll dx = p1.x - p0.x;
    ll dy = p1.y - p0.y;
    //assert(dx == abs(dy));
    for (ll i = (p1.x % 2 != 0); i <= dx; i += 2) {
      res.push_back(p0 + P{i, i * sgn(dy)});
    }
  }
  return res;
}

vector<P> solve(const vector<pair<P, ull>>& towers) {
  ull N = towers.size();

  Ans ans = newAns(towers[0].first, towers[0].second);
  fore(i, 1, N) {
    ans = join(ans, newAns(towers[i].first, towers[i].second));
  }

  vector<P> res = calcPoints(ans);
  sort(all(res));

  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<pair<P, ull>> towers(N);
  for (auto& [P, D] : towers) {
    cin >> P.x >> P.y >> D;
    P.x *= 2, P.y *= 2;
    D *= 2;
  }

  auto ans = solve(towers);
  ll lastx = 1ll << 60;
  ll lasty = lastx;
  for (auto [X, Y] : ans) {
    if (X != lastx || Y != lasty) {
      cout << X/2 << ' ' << Y/2 << '\n';
      lastx = X, lasty = Y;
    }
  }

  return EXIT_SUCCESS;
}
