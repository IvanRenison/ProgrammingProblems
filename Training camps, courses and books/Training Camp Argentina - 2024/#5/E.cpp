// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/E
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
const ll NMAX = 1e5+10;
const ll INF = 1e10;


struct Tree {
  typedef pair<ll,ll> T;
  static constexpr T neut = {INF,INF};
  T f(T a, T b){ return min(a,b);}
  vector<T> s;ll n;
  Tree(ll n = 0, T def = neut) : s(2*n,def), n(n) {}
  void upd(ll pos, T val){
    for(s[pos += n]=val;pos/=2; )
      s[pos] =f(s[pos*2],s[pos*2+1]);
  }
  T query(ll b, ll e){
    T ra = neut, rb = neut;
    for(b += n, e+=n;b<e;b/=2,e/=2){
      if(b&1) ra = f(ra,s[b++]);
      if(e&1) rb = f(s[--e],rb);
    }
    return f(ra,rb);
  }
};

set<ll> g[NMAX];

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
ll n,m;cin>>n>>m;
  fore(i,0,m){
    ll x,y;cin>>x>>y;--x;--y;
    g[x].insert(y);
    g[y].insert(x);
  }
  ll res = 0;
  Tree st(n);
  fore(i,0,n){
    st.upd(i,{0,i});
  }
  ll flag = 0;
  while(st.query(0,n).fst==0){
    res++;
    ll priti = st.query(0,n).snd;
    // cout << priti << " priti ";
    st.upd(priti,{1,priti});
    set<ll> infs;
    for(auto i:g[priti]){
      if(st.query(i,i+1).fst==1)continue;
      st.upd(i,{INF,i});
      infs.insert(i);
    }
    // if(!flag){
    //   cout << "ACA" << endl;
    //   cout << SZ(infs) << endl;
    //   fore(i,0,n){
    //     cout << st.query(i,i+1).fst << " ";
    //   }
    //   cout << endl;
    //   // flag = 1;
    // }
    while(st.query(0,n).fst==0){
      ll nue = st.query(0,n).snd;
      // if(!flag){
      //   cout << nue << " aca" << endl;
      //   flag  =1;
      // }
      st.upd(nue,{1,nue});
      set<ll> nueinf = infs;
      for(auto i:infs){
        if(!g[nue].count(i)){
          nueinf.erase(i);
          st.upd(i,{0,i});
        }
      }
      infs = nueinf;
    }
    // cout << "\n";
    for(auto i:infs){
      st.upd(i,{0,i});
    }
  }
  cout << res-1 << "\n";
}