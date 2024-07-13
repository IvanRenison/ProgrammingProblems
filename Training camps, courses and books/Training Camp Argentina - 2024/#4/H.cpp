// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/H
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ll pa[110][110];
ll sz[110][110];

ll find(ll x, ll c){
  if(pa[c][x]==x)return x;
  pa[c][x]=find(pa[c][x],c);
  return pa[c][x];
}

ll join(ll x, ll y, ll c){
  ll pax = find(x,c), pay = find(y,c);
  if(pax==pay)return false;
  if(sz[c][pax]>sz[c][pay])swap(pax,pay);
  sz[c][pay]+=sz[c][pax];
  pa[c][pax]=pay;
  return true;
}



int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m;cin>>n>>m;
  fore(i,0,110){
    fore(j,0,110){
      pa[j][i]=i, sz[j][i]=1;
    }
  }
  fore(i,0,m){
    ll x,y,c;cin>>x>>y>>c;--x;--y;--c;
    join(x,y,c);
  }
  ll q;cin>>q;
  while(q--){
    ll u,v;cin>>u>>v;--u,--v;
    ll res = 0;
    fore(i,0,m){
      res += find(u,i)==find(v,i);
    }
    cout << res << '\n';
  }

}