// https://codeforces.com/gym/101081/problem/E
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, pluton = b; i < pluton; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

struct P {
  ld x, y;
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return abs(x - p.x) < eps && abs(y - p.y < eps); }
  P operator-(P p) const { return P{x-p.x, y-p.y}; }
  P operator+(P p) const { return P{x+p.x, y+p.y}; }
  P operator*(ld d) const { return P{x*d, y*d}; }
  P operator/(ld d) const { return P{x/d, y/d}; }
  ld angle() const { return atan2(y, x); }
  ld dot(P p) const { return x*p.x + y*p.y; }
  ld cross(P p) const { return x*p.y - y*p.x; }
  ld cross(P a, P b) const { return (a-*this).cross(b-*this); }
  ld dist2() const { return x*x + y*y; }
  ld dist() const { return sqrt((ld)dist2()); }
};

ld lineDist(const P& a, const P& b, const P& p) {
  return (ld)(b-a).cross(p-a)/(b-a).dist();
}

bool onSegment(P s, P e, P p) {
  return abs(p.cross(s, e)) < eps && (s - p).dot(e - p) <= eps;
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

pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P{0, 0}};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

ull solve(const vector<P>& XYs) {
  ull N = XYs.size();
  ull ans0 = 0;
  ull ans = 0;
  fore(i, 0, N) {
    P p1 = XYs[i];
    P p0 = XYs[(i + N - 1) % N];
    P p2 = XYs[(i + 1) % N];

    ld d = lineDist(p0, p2, p1);
    if (d > 0.0) {
      ans++;
      if (i == 0) {
        ans0++;
      }
    }
  }

  P l0 = XYs[0];
  P l1 = (XYs[1] + XYs.back()) / 2;
  l1 = l0 + (l1 - l0) * 1e6;
  l1.x += 0.1;

  ull count = 0;
  P last = XYs[0];
  fore(i, 1, N - 1) {
    P p1 = XYs[i];
    P p2 = XYs[i + 1];

    vector<P> inter = segInter(l0, l1, p1, p2);
    if (inter.size() == 1) {
      //if (!(inter[0] == last)) {
        count++;
        last = inter[0];
/*       } else {
        P p0 = XYs[i - 1];
        vector<P> inter_ = segInter(l0, l1, p0, p2);
        if (inter_.size() != 1) {
          count--;
        }
      }
    } else if (inter.size() == 2) {
      P p0 = XYs[i - 1];
      assert(i + 2 < N);
      P p3 = XYs[i + 2];
      vector<P> inter_ = segInter(l0, l1, p0, p3);
      if (inter_.size() != 1) {
        count -= 2;
        last = XYs[0];
      } */
    }
  }

  if ((count % 2 == 0) == (ans0 == 0)) {
    ans = N - ans;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<P> XYs(N);
  for (auto& [X, Y] : XYs) {
    cin >> X >> Y;
  }

  auto ans = solve(XYs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
