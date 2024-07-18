// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/G
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
typedef vector<ld> vd;

const ll xlim = 1001;

vd solve(ll r, const vi& xs) {
  ll n = xs.size();
  vd coords(xlim, (ld)-r);
  vd ans(n);
  fore(i, 0, n) {
    ll xi = xs[i];
    ld pos = r;
    pos = max(pos, coords[xi] + 2*r);
    if (xi >= 2 * r) {
      pos = max(pos, coords[xi - 2*r]);
    }
    if (xi + 2 * r < xlim) {
      pos = max(pos, coords[xi + 2*r]);
    }
    fore(x, max(0ll, xi - 2*r + 1), xi) {
      ld d = xi - x;
      ld this_pos = coords[x] + sqrtl((ld)(-d*d + 4 * r * r));
      pos = max(pos, this_pos);
    }
    fore(x, xi + 1, min(xlim, xi + 2*r)) {
      ld d = x - xi;
      ld this_pos = coords[x] + sqrtl((ld)(-d*d + 4 * r * r));
      pos = max(pos, this_pos);
    }
    ans[i] = pos;
    coords[xi] = pos;

/*     fore(i, 0, 20) {
      cerr << coords[i] << ' ';
    }
    cerr << '\n'; */
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, r;
  cin >> n >> r;
  vi xs(n);
  for (ll& x : xs) {
    cin >> x;
  }

  cerr << setprecision(5);

  vd ans = solve(r, xs);
  cout << setprecision(10) << fixed;
  for (ld a : ans) {
    cout << a << ' ';
  }
  cout << '\n';
}
