// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/H
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
typedef vector<ld> vd;


struct RMQMin{
  typedef pair<ll,ll> T;
  vector<vector<T>> jmp;
  RMQMin(const vector<T> &V):jmp(1,V){
    for(ll pw = 1,k=1;pw*2<=SZ(V);pw*=2,++k){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k-1][j],jmp[k-1][j+pw]);
    }
  }
  T query(ll a, ll b){
    assert(a<b);
    ll dep = 63-__builtin_clzll(b-a);
    return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};

struct RMQMax{
  typedef pair<ll,ll> T;
  vector<vector<T>> jmp;
  RMQMax(const vector<T> &V):jmp(1,V){
    for(ll pw = 1,k=1;pw*2<=SZ(V);pw*=2,++k){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k-1][j],jmp[k-1][j+pw]);
    }
  }
  T query(ll a, ll b){
    assert(a<b);
    ll dep = 63-__builtin_clzll(b-a);
    return max(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};

ll grid[1010][1010];

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m;cin>>n>>m;
  fore(i,0,n){
    fore(j,0,m){
      char c;cin>>c;
      grid[i][j]=c-'a';
    }
  }
  vector<vector<ll>> cuanto(n,vector<ll>(m));
  fore(i,0,n){
    ll l = 0, r = 1;
    while(l<m && r<m){
      if(grid[i][r]==grid[i][l])++r;
      else {
        while(l<r){
          cuanto[i][l]=r-l;
          ++l;
        }
        ++r;
      }
    }
    while(l<r){
      cuanto[i][l]=r-l;
      ++l;
    }
    // fore(j,0,m){
    //   cout << cuanto[i][j] << " ";
    // }
    // cout << "\n";
  }
  // cout << "\n\n";
  vector<vector<pair<ll,ll>>> pongo(m,vector<pair<ll,ll>>(n));
  vector<RMQMin> minis;
  vector<RMQMax> maxis;
  fore(j,0,m){
    fore(i,0,n){
      pongo[j][i]={grid[i][j],cuanto[i][j]};
    }
    minis.pb(RMQMin(pongo[j]));
    maxis.pb(RMQMax(pongo[j]));
  }
  vector<vector<pair<ll,ll>>> hasta(n,vector<pair<ll,ll>>(m));
  fore(i,0,n){
    fore(j,0,m){
      ll l = i+1,r=n;
      while(l<=r){
        ll mid = (l+r)/2;
        ll maxi = minis[j].query(i,mid).fst;
        ll mini = maxis[j].query(i,mid).fst;
        if(maxi==mini)l=mid+1;
        else r=mid-1;
      }
      hasta[i][j]={r,minis[j].query(i,r).snd};
      // cout << i << " " << j << " " << hasta[i][j].fst << " " << hasta[i][j].snd << "\n";
    }
  }

  ll res = 0;
  fore(i,0,n){
    fore(j,0,m){
      pair<ll,ll> a = {i,hasta[i][j].snd};
      if(hasta[a.fst][j].fst==n)continue;
      pair<ll,ll> b = {hasta[a.fst][j].fst,hasta[hasta[a.fst][j].fst][j].snd};
      if(hasta[b.fst][j].fst==n)continue;
      pair<ll,ll> c = {hasta[b.fst][j].fst,hasta[hasta[b.fst][j].fst][j].snd};
      if(c.fst==n)continue;
      ll hasta_c = hasta[c.fst][j].fst;
      ll tiene = b.fst-a.fst;
      if(hasta_c-c.fst>tiene){
        hasta_c -= hasta_c-c.fst-tiene;
        c.snd = minis[j].query(c.fst,hasta_c).snd;
      }
      if(!(((b.fst-a.fst)==(c.fst-b.fst)) && (c.fst-b.fst)==(hasta_c-c.fst)))continue;
      res += min({a.snd,b.snd,c.snd});
    }
  }

  cout << res << "\n";

}