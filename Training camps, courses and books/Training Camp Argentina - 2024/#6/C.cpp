// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, M;
  cin >> n >> M;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  vi on(n + 1), off(n + 1);
  if (n % 2 == 0) {
    on[n-1] = M - as.back();
  } else {
    off[n-1] = M - as.back();
  }
  for (ll j = n - 1; j--; ) {
    ll d = as[j + 1] - as[j];
    if (j % 2 == 0) {
      on[j] = on[j+1];
      off[j] = off[j+1] + d;
    } else {
      off[j] = off[j+1];
      on[j] = on[j+1]+d;
    }
  }

  ll ans = on[0] + as[0];
  ll cumm = as[0];
  as.push_back(M);
  fore(i, 0, n) {
    if (i % 2 == 0) {
      ll this_ans = cumm + (as[i+1] - as[i] - 1) + off[i+1];
      ans = max(ans, this_ans);
    } else {
      cumm += as[i+1] - as[i];
    }

  }

  cout << ans << '\n';
}