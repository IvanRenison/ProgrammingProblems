// https://codeforces.com/gym/103049/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

typedef long double ld;

const ld eps = 1e-9;

ll interact(ll x, ll y) {
  cout << x << ' ' << y << endl;
  ll d;
  cin >> d;
  return d;
}

template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {};
  P operator+(P p) const {return P(x+p.x, y+p.y);}
  P operator-(P p) const {return P(x-p.x, y-p.y);}
  P operator*(T d) const { return P(x*d, y*d); }
  T dist2() const { return x*x + y*y; }
  P perp() const { return P(-y, x); }
};

typedef Point<ld> P;

optional<pair<P,P>> circleInter(P a, P b, ld r1, ld r2) {
  P vec = b - a;
  ld d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
    p = (d2 + r1*r1 - r2*r2)/(d2*2),
    h2 = r1*r1 - p*p*d2;
  if (sum*sum < d2 || dif*dif > d2) return {};
  P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
  pair<P,P> out = {mid + per, mid - per};
  return out;
}


void solve(ull n) {
  if (n == 0) {
    return;
  }

  vector<tuple<ll, ll, ll>> querys(n+1);

  fore(i, 0, n+1) {
    ll x = i*10000;
    ll y = 5*10000;
    ll d = interact(x, y);
    querys[i] = {x, y, d};
  }

  fore(i, 0, n+1) {
    fore(j, i+1, n+1) {
      auto [xi, yi, di] = querys[i];
      auto [xj, yj, dj] = querys[j];

      auto in = circleInter(P(xi, yi), P(xj, yj), sqrt((ld)di + eps*eps), sqrt((ld)dj) + eps*eps);
      if (!in.has_value()) {
        continue;
      }

      auto [p1, p2] = *in;

      if (p1.x + eps - floor(p1.x + eps) < 2*eps && p1.y + eps - floor(p1.y + eps) < 2*eps) {
        ll x = (ll)floor(p1.x + eps);
        ll y = (ll)floor(p1.y + eps);

        if (x >= 0 && y >= 0 && x <= 1000000 && y <= 1000000) {
          ll d = interact(x, y);
          if (d == 0) {
            solve(n-1);
            return;
          }
        }
      }

      if (p2.x + eps - floor(p2.x + eps) < 2*eps && p2.y + eps - floor(p2.y + eps) < 2*eps) {
        ll x = (ll)floor(p2.x + eps);
        ll y = (ll)floor(p2.y + eps);

        if (x >= 0 && y >= 0 && x <= 1000000 && y <= 1000000) {
          ll d = interact(x, y);
          if (d == 0) {
            solve(n-1);
            return;
          }
        }
      }

    }
  }

}


int main(){FIN;

  ull n;
  cin >> n;

  solve(n);

	return 0;
}
