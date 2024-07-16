// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/K
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
const ll MOD =1e9+7;


ll mul(ll x, ll y){
  return (x*y)%MOD;
}
ll add(ll x, ll y){
  // ll res = x+y;
  // if(res>=MOD)res-=MOD;
  return x+y-((x+y>=MOD)*MOD);
  // return (x+y)%MOD;
}

ll fpow(ll b, ll e){
  ll ans = 1;
  for(;e;b=mul(b,b),e/=2)
    if(e&1) ans=mul(ans,b);
  return ans;
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n;cin>>n;
  vector<vector<ll>> divs(n+1);
  fore(i,1,n+1){
    for(ll j = i;j<n+1;j+=i){
      divs[j].pb(i);
    }
  }

  vector<ll> inv(n+1);
  fore(i,1,n+1){
    inv[i]=fpow(i,MOD-2);
  }


  ll res = 0;
  ll canti = 0;
  fore(i,1,n-1){
    ll c = i, ab = n-i;
    // sort(ALL(divs[ab]));
    vector<ll> dp(SZ(divs[ab]), -1);
    for(ll i = SZ(divs[ab])-1;i>=0;--i){
      dp[i]=ab/divs[ab][i] - 1;
      for(ll j = i+1;j<SZ(divs[ab]);++j){
        if(divs[ab][j]%divs[ab][i]==0)dp[i]-=dp[j];
      }
    }


    fore(z,0,SZ(divs[ab])){
      ll j = divs[ab][z];
      ll cuenta = mul(c,j);
      cuenta = mul(cuenta,inv[gcd(c,j)]);
      res = (mul(cuenta,dp[z]) + res)%MOD;
      // cout << i << " " << j << " " << cuenta << "\n";
    }
  }
  cout << res << "\n";
}