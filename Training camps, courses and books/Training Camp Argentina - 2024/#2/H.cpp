// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/H
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

const ll inf = 1ll << 60;

ll solve(ll m, ll k, const vi& as) {
  ll n = as.size();

  ll ans = -1;

  if (m <= k) {
    fore(i, 0, m + 1) {
      ans = max(ans, as[i]);
    }
    fore(i, n - 1 - m, n) {
      ans = max(ans, as[i]);
    }

    return ans;
  }

  fore(i, 0, k + 1) {
    ll ni = k - i;

    ll this_ans = inf;

    fore(j, 0, m - k + 1) {
      ll nj = m - k - j;
      this_ans = min(this_ans, max(as[i + j], as[n - 1 - ni - nj]));
    }

    ans = max(this_ans, ans);
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n, m, k;
    cin >> n >> m >> k;
    m--;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    ll ans = solve(m, k, as);
    cout << ans << '\n';
  }

}