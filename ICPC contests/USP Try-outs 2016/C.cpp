#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll).x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,aei=b;i<aei;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define imp(v) for(auto messi:v) cout << messi << " ";cout << "\n";
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;


  ll H, W;
  cin >> H >> W;

  ll ans = 1ll << 60;

  vi as(H), bs(H);
  for(ll & a : as) {
    cin >> a;
  }
  for (ll& b : bs) {
    cin >> b;
  }

  fore(i, 0, H) {
    ans = min(ans, W - as[i] - bs[i]);
  }

  cout << (ld)ans / 2.0 << '\n';


	return 0;
}