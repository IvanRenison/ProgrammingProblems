// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/K
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
const ll NMAX =2e5+10;

vector<ll> g[NMAX];
ll co[NMAX];
ll vis[NMAX];

void dfs(ll x){
  // cout << x << " " << co[x] << "\n";
  for(auto i:g[x]){
    if(vis[i])continue;
    vis[i]=1;
    co[i]=co[x]^1;
    dfs(i);
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m;cin>>n>>m;
  vector<pair<ll,ll>> edges(m);
  fore(i,0,m){
    ll x,y;cin>>x>>y;--x;--y;
    g[x].pb(y), g[y].pb(x);
    edges[i]={x,y};
  }
  fore(i,0,n){
    if(!vis[i]){
      vis[i]=1;
      dfs(i);
    }
  }

  bool bi = true;
  fore(i,0,n){
    for(auto j:g[i]){
      if(co[i]==co[j]){bi=false;break;}
    }
  }
  if(!bi){
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  vector<ll> ans(m);
  fore(i,0,m){
    ll x = edges[i].fst, y = edges[i].snd;
    // cout << x << " " << y << " " << co[x] << " " << co[y] << "\n";
    if(co[x]==1){
      ans[i] = 1;
    } else {
      ans[i] = 0;
    }
  }
  for(auto i:ans)cout << i;
  cout << "\n";
}