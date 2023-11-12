#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;

int main(){FIN;
  ll n;cin>>n;
  ll x;cin>>x;
  vector<pair<ll,ll>> tm(n);
  fore(i,0,n)cin>>tm[i].fst>>tm[i].snd;
  sort(ALL(tm));
  ii res = {ll(1e18),481};
  fore(i,0,481){
    ll cant_act = 0;
    ll mod = i%x;
    fore(j,0,n){
      ll l = tm[j].fst, r = l+tm[j].snd;
      // cout << r << " " << i << "\n";
      if(r<i)continue;
      // if(i==451)cout << r << " " << l << " " << cant_act << "\n";
      l = max(l,i);
      if(l%x<mod){
        l += mod-(l%x);
      } else if(l%x > mod) {
        l += x-(l%x)+mod;
      }
      // if (i==0) cout << l << " " << r << "\n";
      if(l>r)continue;
      // if(i==451) cout << l << " " << r << "\n";
      cant_act += (r-l+x)/x;
    }
    // if(i==451)cout << cant_act << "\n";
    if(cant_act<res.fst){
      res = {cant_act,i};
    }
  }
  cout << res.snd << " " << res.fst << "\n";
  return 0;
}