// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/K
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n;cin>>n;
  vector<vector<ll>> posis(n+1);
  fore(i,0,2*n){
    ll x;cin>>x;
    posis[x].pb(i);
  }
  ll ulti_0 = 0, ulti_1 = 0;
  ll res = 0;
  fore(i,1,n+1){
    ll nue_0 = posis[i][0], nue_1 = posis[i][1];
    ll aux = min(abs(ulti_0-nue_0)+abs(ulti_1-nue_1),abs(ulti_0-nue_1)+abs(ulti_1-nue_0));
    // cout << aux << " ";
    res += aux;
    ulti_0 = nue_0, ulti_1 = nue_1;
  }
  cout << res << '\n';
}