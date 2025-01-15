// https://codeforces.com/gym/105544
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

bool check(const vi& acc) {
  ll dp = 1;

  for (ll a : views::reverse(acc)) {
    if (a > 9) break;

    dp |= dp << a;
  }

  return (dp & (1 << 9)) == 0;
}

ll force(ll N) {
  ll ans = 1;

  auto rec = [&](ll n, ll mx, vi& acc, auto&& rec) {
    if (n == 0) {
      if (check(acc)) {
        ans = max(ans, (ll)acc.size());
      }
      return;
    }

    fore(tam, 1, min(n + 1, mx + 1)) if (tam != 9) {
      acc.push_back(tam);
      rec(n - tam, tam, acc, rec);
      acc.pop_back();
    }
  };

  vi acc;
  rec(N, N, acc, rec);

  return ans;
}

ll solveBig(ll N) {
  if (N % 2 == 0) {
    return N / 2;
  } else {
    return (N - 11) / 2 + 1;
  }
}

ll solve(ll N) {
  if (N <= 51) {
    return force(N);
  } else {
    return solveBig(N);
  }
}

const ll mod = 1e9 + 7;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

/*   fore(N, 1, 50) {
    cout << solveBig(N) << ' ' << force(N) << '\n';
  }
  return 0; */

  ll N;
  cin >> N;

  ll ans = solve(N);
  ans %= mod;

  cout << ans << '\n';

}
