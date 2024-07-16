// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m;cin>>n>>m;
  vector<vector<ll>> posis(m);
  fore(i,0,n){
    ll x,y;cin>>x>>y;--x;
    posis[x].pb(y);
  }
  fore(i,0,m){
    sort(ALL(posis[i]));
    reverse(ALL(posis[i]));
  }
  vector<ll> ans(n+1);
  fore(i,0,m){
    ll it = 0;
    ll acc = 0;
    fore(j,0,SZ(posis[i])){
      it++;
      acc += posis[i][j];
      if(acc<0)break;
      ans[it]+=acc;
    }
  }
  ll res = 0;
  fore(i,1,n+1){
    res = max(res,ans[i]);
  }
  cout << res << "\n";
}