// https://codeforces.com/gym/104505/problem/M
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef long double ld;

const ld eps = 1e-7;

struct P {
  typedef ld T;
  T x, y;
  explicit P(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator==(P p) const { return abs(x - p.x) < eps && abs(y - p.y) < eps; }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const {return P(x - p.x, y - p.y); }
  P operator*(T d) const {return P(x * d, y * d); }
  P operator/(T d) const {return P(x / d, y / d); }

  T dist2() const { return x*x + y*y; }
  T dist() const { return sqrt(dist2()); }
  P unit() const { return *this/dist(); }
  P perp() const { return P(-y, x); }
};

ld gss(ld a, ld b, function<ld(ld)> f) {
  ld r = (sqrt(5)-1)/2, eps = 1e-16;
  ld x1 = b - r*(b-a), x2 = a + r*(b-a);
  ld f1 = f(x1), f2 = f(x2);
  while (b-a > min(abs(a), abs(b)) * 1e-7)
    if (f1 > f2) { //change to > to find maximum
      b = x2; x2 = x1; f2 = f1;
      x1 = b - r*(b-a); f1 = f(x1);
    } else {
      a = x1; x1 = x2; f1 = f2;
      x2 = a + r*(b-a); f2 = f(x2);
    }
  return a;
}

pair<ld, ld> gss2D(ld x0, ld x1, ld y0, ld y1, function<ld(ld, ld)> f) {

  function<ld(ld)> fx = [&](ld x) {

    function<ld(ld)> fy = [&](ld y) {
      return f(x, y);
    };

    ld ans = gss(y0, y1, fy);

    return fy(ans);
  };


  ld ans_x = gss(x0, x1, fx);

  function<ld(ld)> fy = [&](ld y) {
    return f(ans_x, y);
  };

  ld ans_y = gss(y0, y1, fy);

  return {ans_x, ans_y};
}


ld solve(ld R, P p0, P p1) {
  ld r0 = p0.dist(), r1 = p1.dist();

  function<ld(ld, ld)> f = [&](ld x, ld y) {
    P c = P(x, y);

    ld ans = R - c.dist();

    ans = min(ans, r0 - (p0 - c).dist());
    ans = min(ans, r1 - (p1 - c).dist());

    return ans;
  };

  auto [ans_x, ans_y] = gss2D(-1e6, 1e6, -1e6, 1e6, f);

  ld ans = f(ans_x, ans_y);

  return ans;
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ld R;
  P p0, p1;
  cin >> R >> p0.x >> p0.y >> p1.x >> p1.y;
  //cerr << setprecision(5) << fixed;

  ld ans = solve(R, p0, p1);

  cout << setprecision(20) << fixed;
  cout << ans << '\n';

  return 0;
}
