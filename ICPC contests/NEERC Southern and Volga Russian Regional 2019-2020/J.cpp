// https://codeforces.com/contest/1250/problem/J
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ll solve(ll k, const vi& cs) {
  ll n = cs.size();

  ll sum = 0;
  for (ll c : cs) {
    sum += c;
  }

  ll l = 0, u = sum / k + 1;

  while (l + 1 < u) {
    ll m = (l + u) / 2;

    ll this_rows = 0;

    ll cnt = cs[0];

    this_rows += cnt / m;
    cnt %= m;

    fore(i, 1, n) {
      ll c = cs[i];

      if (cnt + c >= m) {
        this_rows++;
        cnt = cnt + c - m;
      } else {
        cnt = c;
      }

      this_rows += cnt / m;
      cnt %= m;
    }

    if (this_rows >= k) {
      l = m;
    } else {
      u = m;
    }
  }

  return l * k;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll t;
  cin >> t;
  while(t--) {
    ll n, k;
    cin >> n >> k;

    vi cs(n);
    for (ll& c : cs) {
      cin >> c;
    }

    ll ans = solve(k, cs);

    cout << ans << '\n';
  }

  return 0;
}