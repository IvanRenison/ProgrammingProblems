// https://codeforces.com/gym/105321/problem/C
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) (ll)x.size()
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef double ld;

const ld eps = 1e-9;

template<class T> ll sgn(T x) { return (x > eps) - (x < -eps); }
struct P {
  ld x, y;
  P(ld x = 0, ld y = 0) : x(x), y(y) {}

  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }

  ld dist2() const {return x*x+y*y; }
  ld dist() const {return sqrt(dist2());}
  ld dot(P p) const { return x*p.x + y*p.y; }
  ld cross(P p) const { return x*p.y - y*p.x; }
  ld cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

P cuenta(ld X_cus, ld Y_cus, ld Z_cus, ld X_sol, ld Y_sol, ld Z_sol) {
  ld x = X_sol + Z_sol / (Z_sol - Z_cus) * (X_cus - X_sol);
  ld y = Y_sol + Z_sol / (Z_sol - Z_cus) * (Y_cus - Y_sol);
  return P(x, y);
}

ll sideOf(P s, P e, P p) {
  //return sgn(s.cross(e, p));
  auto a = (e-s).cross(p-s);
  ld l = (e-s).dist()*eps;
  return (a > l) - (a < -l);
}

ld rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }
ld polyUnion(vector<vector<P>>& poly) {
  ld ret = 0;
  fore(i, 0, SZ(poly)) fore(v,0,SZ(poly[i])) {
    P A = poly[i][v], B = poly[i][(v+1) % SZ(poly[i])];
    vector<pair<ld, ll>> segs = {{0,0},{1,0}};
    fore(j,0,SZ(poly)) if (i != j) {
      fore(u, 0, SZ(poly[j])) {
        P C = poly[j][u], D = poly[j][(u+1) % SZ(poly[j])];
        ll sc = sideOf(A, B, C), sd = sideOf(A, B, D);
        if (sc != sd) {
          ld sa = C.cross(D, A), sb = C.cross(D, B);
          if (min(sc, sd) < 0)
            segs.pb({sa / (sa - sb), sgn(sc - sd)});
        } else if (!sc && !sd && j<i && sgn((B-A).dot(D-C))>0) {
          segs.pb({rat(C-A, B-A), 1});
          segs.pb({rat(D-A, B-A), -1});
        }
      }
    }
    sort(ALL(segs));
    for (auto& s : segs) s.fst = min(max(s.fst, (ld)0.0), (ld)1.0);
    ld sum = 0;
    ll cnt = segs[0].snd;
    fore(j,1,SZ(segs)) {
      if (!cnt) sum += segs[j].fst - segs[j-1].fst;
      cnt += segs[j].snd;
    }
    ret += A.cross(B) * sum;
  }
  return ret / 2;
}

ld polygonArea2(vector<P>& v) {
  ld a = v.back().cross(v[0]);
  fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
  return a;
}

bool solve(ll X_cus, ll Y_cus, ll Z_cus, ll X_sol, ll Y_sol, ll Z_sol, vector<P>& poly) {
  ll N = poly.size();

  reverse(ALL(poly));

  ld poly_area = abs(polygonArea2(poly));
  poly_area = poly_area / 2.0;

  P cus = cuenta(X_cus, Y_cus, Z_cus, X_sol, Y_sol, Z_sol);

  vector<vector<P>> polys = {poly};
  polys.reserve(N + 1);
  fore(i, 0, N) {
    vector<P> p = {cus, poly[i], poly[(i+1) % N]};
    ld area = polygonArea2(p);
    if (area < 0) {
      reverse(ALL(p));
    }
    polys.push_back(p);
  }

  ld un = polyUnion(polys);

  //cerr << un << ' ' << poly_area << '\n';

  bool ans = poly_area + eps < un;

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  //cerr << setprecision(10);

  ll N;
  cin >> N;

  ll X_cus, Y_cus, Z_cus, X_sol, Y_sol, Z_sol;
  cin >> X_cus >> Y_cus >> Z_cus >> X_sol >> Y_sol >> Z_sol;

  vector<P> poly(N);
  for (auto& [x, y] : poly) {
    ll X, Y;
    cin >> X >> Y;
    x = X, y = Y;
  }

  bool ans = solve(X_cus, Y_cus, Z_cus, X_sol, Y_sol, Z_sol, poly);

  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }
}
