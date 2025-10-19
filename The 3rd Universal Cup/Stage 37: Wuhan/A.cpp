// https://contest.ucup.ac/contest/2025/problem/10736
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

ll solve(vi& as, viii& plrs) {
  ll n = as.size(), q = plrs.size();

  vii lims(n, {0, (ll)1e9});
  fore(_, 0, q) {
    auto [p, l, r] = plrs[_];

    lims[p].first = max(lims[p].first, l);
    lims[p].second = min(lims[p].second, r);
  }

  ll ans = 0;
  fore(i, 0, n) {
    if (lims[i].first >= lims[i].second) {
      return -1;
    }
    if (as[i] < lims[i].first) {
      ans += lims[i].first - as[i];
    }
    if (as[i] > lims[i].second - 1) {
      ans += as[i] - lims[i].second + 1;
    }

  }

  return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    ll n, q;
    cin >> n >> q;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
      a--;
    }

    viii plrs(q);
    for (auto& [p, l, r] : plrs) {
      cin >> p >> l >> r;
      p--, l--;
    }

    ll ans = solve(as, plrs);
    cout << ans << '\n';
  }

}