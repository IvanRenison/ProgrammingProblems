#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef pair<ll,ll> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;
typedef long double ld;

struct P {
  ld x, y, z;

  P operator-(P o) {
    return P{x - o.x, y - o.y, z - o.z};
  }
  ld dist() {
    return sqrtl(x*x + y*y + z*z);
  }
  ld dist(P o) {
    return (*this - o).dist();
  }

};

ld solve(P xyz, P t, ld r0) {
  auto [x, y, z] = xyz;

  t.x = max(t.x, x - t.x);
  t.y = max(t.y, y - t.y);
  t.z = max(t.z, z - t.z);

  auto can = [&](ld r1) -> bool {
    ld d = t.dist(P{r1, r1, r1});
    return d >= r1 + r0;
  };


  ld l = 0, r = min(min(x, y), z) / 2;
  fore(_, 0, 50) {
    ld m = (l + r) / 2;
    if (can(m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return l;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll x, y, z;
  ld tx, ty, tz;
  ld r;
  cin >> x >> y >> z >> tx >> ty >> tz >> r;

  ld ans = solve(P{x, y, z}, P{tx, ty, tz}, r);
  cout << setprecision(15) << fixed << ans << '\n';

}