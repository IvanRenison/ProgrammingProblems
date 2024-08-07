// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/D
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;

const ld eps = 1e-9;
#define M_PI 3.14159265358979323846

template<class T>
struct Point {
  typedef Point P;
  T x, y;
  Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator!=(P p) const {
    return tie(x, y) != tie(p.x, p.y);
  }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }

  T dist2() const { return x*x + y*y; }
  ld dist() const { return sqrtl((ld)dist2()); }
  P rotate(ld a) const {
    return P(x*cosl(a)-y*sinl(a), x*sinl(a)+y*cosl(a));
  }
  T dot(P p) const {
    return x*p.x + y*p.y;
  }
  P perp() const { return P(-y, x); }
};

bool circleInter(Point<ld> a, Point<ld> b, ld r1, ld r2, pair<Point<ld>,Point<ld>>& out) {
  assert(a != b);
  Point<ld> vec = b - a;
  ld d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2,
    p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
  if (sum*sum < d2 || dif*dif > d2) return false;
  Point<ld> mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
  out = {mid + per, mid - per};
  return true;
}

typedef Point<ll> P;
// acos(a * b / |a| |b|)
ld angleDiff(Point<ld> a, Point<ld> b) {
  return acosl(max((ld)(-1), min((ld)1, a.dot(b) / (a.dist() * b.dist()))));
}

bool isint(ld x) {
  return abs(x + eps - floorl(x + eps)) < 2*eps;
}

ll ldtoll(ld x) {
  if (x > 0) {
    return (ll)(x + eps);
  } else {
    return -((ll)(-x + eps));
  }
}

bool iso(P A, P B, P C) {
  P AB = B - A, BC = C - B, AC = C - A;
  ll ab = AB.dist2(), bc = BC.dist2(), ac = AC.dist2();
  return ab == bc || ab == ac || bc == ac;
}

ll solve_(P A, P B, P C, const vector<P>& points) {
  ll N = points.size();

  set<P> p_s(ALL(points));

  ll ans = 0;

  P AB = B - A, BC = C - B, AC = C - A;
  Point<ld> pab((ld)AB.x, (ld)AB.y);
  Point<ld> pa((ld)A.x, (ld)B.x);
  ld ab = AB.dist(), bc = BC.dist(), ac = AC.dist();


  fore(i, 0, N) {
    P Pi = points[i];
    Point<ld> pi((ld)Pi.x, (ld)Pi.y);
    fore(j, 0, i) {
      P Pj = points[j];
      Point<ld> pj((ld)Pj.x, (ld)Pj.y);
      // A, B, C

      ld prop = (pj - pi).dist() / ab;
      ld r0 = bc * prop, r1 = ac * prop;

      vector<Point<ld>> cs;
      pair<Point<ld>,Point<ld>> out;
      bool bool_ = circleInter(pi, pj, r0, r1, out);
      assert(bool_);
      auto [c0, c1] = out;
      cs.push_back(c0), cs.push_back(c1);
      bool_ = circleInter(pi, pj, r1, r0, out);
      assert(bool_);
      tie(c0, c1) = out;
      cs.push_back(c0), cs.push_back(c1);

      set<P> Cs;

      for (auto c_ : cs) {
        if (isint(c_.x) && isint(c_.y)) {
          P C_(ldtoll(c_.x), ldtoll(c_.y));
          Cs.insert(C_);
        }
      }
      for (P C_ : Cs) {
        if (p_s.count(C_)) {
          //cerr << i << ' ' << j << ' ' << C_.x << ' ' << C_.y << endl;
          ans++;
        }
      }
    }
  }

  return ans;
}

ll solve(vector<P>& points) {
  vector<P> vals = {points[0], points[1], points[2]};

  vector<vi> perms = {
    {0, 1, 2},
    {0, 2, 1},
    {1, 2, 0}
  };
  ll ans = 0;

  for (vi perm : perms) {
    //fore(i, 0, 3) {
    //  cerr << perm[i] << ' ';
    //}
    //cerr << "---" << endl;
    ans += solve_(vals[perm[0]], vals[perm[1]], vals[perm[2]], points);
  };


  if (iso(points[0], points[1], points[2])) {
    ans /= 5;
  } else
    ans /= 3;

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vector<P> points(N);
  for (auto& [x, y] : points) {
    ll X, Y;
    cin >> X >> Y;
    x = X, y = Y;
  }

  ll ans = solve(points);
  cout << ans << '\n';

}
