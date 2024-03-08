// https://codeforces.com/contest/1250/problem/A
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

vii solve(ll n, const vi& as) {

  vi mins(n), maxs(n), poss(n), arr(n);

  fore(i, 0, n) {
    mins[i] = maxs[i] = poss[i] = arr[i] = i;
  }

  for (ll a : as) {
    if (poss[a] > 0) {
      ll b = arr[poss[a] - 1];

      poss[a]--;
      poss[b]++;

      mins[a] = min(mins[a], poss[a]);
      maxs[b] = max(maxs[b], poss[b]);

      arr[poss[a]] = a;
      arr[poss[b]] = b;
    }
  }

  vii ans(n);
  fore(i, 0, n) {
    ans[i] = {mins[i], maxs[i]};
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll n, m;
  cin >> n >> m;
  vi as(m);
  for (ll& a : as) {
    cin >> a;
    a--;
  }

  vii ans = solve(n, as);
  for (auto [i, j] : ans) {
    cout << i + 1 << ' ' << j + 1 << '\n';
  }

  return 0;
}