// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/K
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
  ll n,m;cin>>n;
  vector<ll> a(n);
  map<ll,vector<ll>> posis;
  fore(i,0,n){
    ll x;cin>>x;
    posis[x].pb(i);
  }
  cin>>m;
  while(m--){
    ll k,j;cin>>k>>j;--j;
    vector<pair<ll,ll>> seq;
    auto it = posis.rbegin();
    while(SZ(seq)!=k){
      for(auto z:it->snd){
        if(SZ(seq)==k)break;
        seq.pb({z,it->fst});
      }
      it++;
    }
    sort(ALL(seq));
    cout << seq[j].snd << "\n";
  }
}