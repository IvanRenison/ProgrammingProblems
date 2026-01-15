// https://codeforces.com/gym/106129/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


ll force(ll l, ll r) {
  set<ii> ps;

  queue<ll> ql, qr;
  fore(i, 0, l) {
    ql.push(i);
  }
  fore(i, 0, r) {
    qr.push(l + i);
  }

  fore(t, 0, 100000) {
    ll il = ql.front();
    ll ir = qr.front();
    ps.insert(minmax(il, ir));
    if (t % 2 == 0) {
      ql.pop();
      qr.push(il);
    } else {
      qr.pop();
      ql.push(ir);
    }
  }

  ll ans = ps.size();

  return ans;
}

ll solve(ll l, ll r) {
  if (r + 1 == l) {
    return l + r;
  }
  if (r + 2 == l) {
    return l + r + (l + r) / 2;
  }
  if (r != l) {
    return 2 * l + 2 * r;
  }
  else {
    return l * 3;
  }
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll l, r;
  cin >> l >> r;
  auto ans = solve(l, r);
  cout << ans << '\n';

/*   fore(l, 2, 20) {

    fore(r, 2, 20) {
      if (solve(l, r) != force(l, r))
      cout << l << ' ' << r << ' ' << force(l, r) << ' ' << solve(l, r) << endl;
    }
  } */

}
