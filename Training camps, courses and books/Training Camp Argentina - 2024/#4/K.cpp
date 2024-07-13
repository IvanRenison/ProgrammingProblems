// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/K
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

struct TreeMin {
  typedef ll T;
  static constexpr T neut = 5e5+10;
  T f(T a, T b) { return min(a,b);}
  vector<T> s; ll n;
  TreeMin(ll n = 0, T def = neut) : s(2*n,def), n(n) {}
  void upd(ll pos, T val){
    for(s[pos += n]=val; pos/=2;)
      s[pos] = f(s[pos*2], s[pos*2+1]);
  }
  T query(ll b,ll e){
    T ra = neut, rb = neut;
    for(b+= n, e+=n;b<e;b/=2,e/=2){
      if(b&1)ra=f(ra,s[b++]);
      if(e&1)rb=f(s[--e],rb);
    }
    return f(ra,rb);
  }
};

struct TreeMax {
  typedef ll T;
  static constexpr T neut = -1;
  T f(T a, T b) { return max(a,b);}
  vector<T> s; ll n;
  TreeMax(ll n = 0, T def = neut) : s(2*n,def), n(n) {}
  void upd(ll pos, T val){
    for(s[pos += n]=val; pos/=2;)
      s[pos] = f(s[pos*2], s[pos*2+1]);
  }
  T query(ll b,ll e){
    T ra = neut, rb = neut;
    for(b+= n, e+=n;b<e;b/=2,e/=2){
      if(b&1)ra=f(ra,s[b++]);
      if(e&1)rb=f(s[--e],rb);
    }
    return f(ra,rb);
  }
};

ll n,m;


bool can(ll mid, TreeMax &st_maxi, TreeMin &st_min){
  fore(i,0,n-mid){
    ll l = i, r = i+mid;
    if(((st_maxi.query(0,l)>=l && st_maxi.query(0,l)<r) || st_maxi.query(0,l)<0) && st_maxi.query(r,n)<0){
      if(st_min.query(0,l)>n && ((st_min.query(r,n)>=l && st_min.query(r,n)<r)||(st_min.query(r,n)>n)))return true;
    }
  }
  return false;
}




int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll t;cin>>t;
  while(t--){
    cin>>n>>m;
    vector<ll> a(n);
    map<ll,vector<ll>> occ;
    fore(i,0,n){
      cin>>a[i];
      occ[a[i]].pb(i);
    }
    vector<vector<ll>> queries_l(n);
    vector<vector<ll>> queries_r(n);
    vector<ll> cierro(n+1);
    fore(i,0,m){
      ll l,r;cin>>l>>r;--l;
      queries_l[l].pb(r);
      queries_r[r-1].pb(l);
      cierro[r]++;
    }
    multiset<ll> ms;
    vector<ll> maxi_r(n);
    fore(i,0,n){
      if(cierro[i])ms.erase(i);
      for(auto j:queries_l[i]){
        ms.insert(j);
      }
      maxi_r[i]=i;
      if(SZ(ms))maxi_r[i] = max(maxi_r[i],*ms.rbegin());
    }
    ms.clear();
    vector<ll> mini_l(n);
    for(int i = n-1;i>=0;--i){
      for(auto i:queries_r[i]){
        ms.insert(i);
      }
      mini_l[i]=i;
      if(SZ(ms))mini_l[i]=min(mini_l[i],*ms.begin());
    }
    TreeMax st_max(n);
    TreeMin st_min(n);
    fore(i,0,n){
      ll pos_maxi = lower_bound(ALL(occ[a[i]]),maxi_r[i])-occ[a[i]].begin();
      ll pos_mini = lower_bound(ALL(occ[a[i]]),mini_l[i])-occ[a[i]].begin();
      --pos_maxi;
      if(pos_maxi>=0 && occ[a[i]][pos_maxi]>i){
        st_max.upd(i,occ[a[i]][pos_maxi]);
      }
      if(occ[a[i]][pos_mini]<i)st_min.upd(i,occ[a[i]][pos_mini]);
    }
    // fore(i,0,n){
    //   cout << st_max.query(i,i+1) << ' ';
    // }
    // cout << '\n';
    if(st_max.query(0,n)<0){
      cout << "0\n";
      continue;
    }
    ll l = 1, r = n-1;
    while(l<=r){
      ll mid = (l+r)/2;
      if(can(mid,st_max,st_min))r=mid-1;
      else l=mid+1;
    }
    cout << l << "\n";
  }
}