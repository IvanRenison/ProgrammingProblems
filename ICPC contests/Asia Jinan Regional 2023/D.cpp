// https://codeforces.com/gym/104901/problem/D
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

ll solve(ll la, ll ra, ll lb, ll rb) {

  if (ra - la > 9 || rb - lb > 9) {
    return 9;
  }

  ll ans = 0;

  fore(a, la, ra + 1) {
    fore(b, lb, rb + 1) {
      ll s = a + b;

      while (s > 0) {
        ans = max(ans, s % 10);
        s /= 10;
      }

    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll la, ra, lb, rb;
    cin >> la >> ra >> lb >> rb;

    ll ans = solve(la, ra, lb, rb);

    cout << ans << '\n';

  }

}