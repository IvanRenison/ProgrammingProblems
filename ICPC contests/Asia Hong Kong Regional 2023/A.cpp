// https://codeforces.com/gym/104172/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

ll solve(vi& ps) {
  ll n = ps.size() + 1;

  vector<vi> suns(n);
  fore(i, 0, n - 1) {
    suns[ps[i]].push_back(i + 1);
  }

  vi tams(n);
  function<ll(ll)> calc_tams = [&](ll u) {
    ll ans = 0;
    for (ll v : suns[u]) {
      ans = max(ans, calc_tams(v));
    }
    ans++;
    tams[u] = ans;
    return ans;
  };

  calc_tams(0);

/*   fore(i, 0, n) {
    cerr << i << ' ' << tams[i] << '\n';;
  }
 */

  function<ll(ll)> f = [&](ll u) -> ll {
    if (suns[u].size() == 1) {
      return f(suns[u][0]);
    }
    if (suns[u].empty()) {
      return 1;
    }

    vi suns_ans;
    for (ll v : suns[u]) {
      suns_ans.push_back(f(v));
    }

    sort(ALL(suns_ans));
    reverse(ALL(suns_ans));

    ll ans = max(suns_ans[1] + 1, suns_ans[0]);

    //cerr << u << ' ' << ans << '\n';

    return ans;
  };


  ll ans = f(0);

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;

  while (T--) {
    ll n;
    cin >> n;
    vi ps(n - 1);
    cin >> ps[0];
    for (ll& p : ps) {
      cin >> p;
      p--;
    }

    cout << solve(ps) << '\n';
  }

}
