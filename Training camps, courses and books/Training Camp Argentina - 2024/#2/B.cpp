// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/B
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

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, d, e;
  cin >> n >> d >> e;
  e *= 5;

  ll ans = n;

  swap(d, e);

  fore(k, 0, n + 1) {
    ll md = k * d;
    if (md > n) {
      break;
    }
    ll r = (n - md) % e;
    ans = min(ans, r);
  }

  cout << ans << '\n';

}