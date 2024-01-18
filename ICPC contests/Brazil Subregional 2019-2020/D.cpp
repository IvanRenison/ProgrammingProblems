// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll NMAX = 1e5+10;

ll dis[NMAX],pa[NMAX];
pair<ll,ll> times[NMAX];
vector<ll> g[NMAX];
ll vis[NMAX];
ll ti;

void dfs(ll x){
  times[x].fst = ti;
  ++ti;
  fore(i,0,SZ(g[x])){
    dis[g[x][i]]=dis[x]+1;
    dfs(g[x][i]);
  }
  times[x].snd = ti;
}

#define NEUT -10000
#define LNEUT 0
struct STree
{
  vector<ll> st,lazy;
  ll n;
  STree(ll n): st(4*n+5,0),lazy(4*n*5,LNEUT), n(n){}
  void _init(ll k, ll s, ll e, vector<ll> &a){
    lazy[k]=LNEUT;
    if(s+1==e){
      st[k]=a[s];
      return;
    }
    ll m=(s+e)/2;
    _init(2*k,s,m,a);
    _init(2*k+1,m,e,a);
    st[k]=max(st[2*k],st[2*k+1]);
  }
  void push(ll k, ll s, ll e){
    if(lazy[k]==LNEUT)return;
    st[k]+=lazy[k];
    if(s+1<e){
      lazy[2*k] += lazy[k];
      lazy[2*k+1] += lazy[k];
    }
    lazy[k]=LNEUT;
  }
  void _upd(ll k, ll s, ll e, ll a, ll b, ll v){
    push(k,s,e);
    if(s>=b || e <= a) return;
    if(s>=a && e<= b){
      lazy[k]+= v;
      push(k,s,e);
      return;
    }
    ll m=(s+e)/2;
    _upd(2*k,s,m,a,b,v);
    _upd(2*k+1,m,e,a,b,v);
    st[k]=max(st[2*k],st[2*k+1]);
  }
  ll _query(ll k, ll s, ll e, ll a, ll b){
    if(s>=b || e<=a) return NEUT;
    push(k,s,e);
    if(s>=a && e<= b)return st[k];
    ll m=(s+e)/2;
    return max(_query(2*k,s,m,a,b),_query(2*k+1,m,e,a,b));
  }
  void init(vector<ll> &a){_init(1,0,n,a);}
  void upd(ll a, ll b, ll v){_upd(1,0,n,a,b,v);}
  ll query(ll a, ll b){return _query(1,0,n,a,b);}
};


int main(){FIN;
  ll n,k;cin>>n>>k;
  ti=0;
  pa[0]=-1;
  fore(i,0,n-1){
    ll p;cin>>p;--p;
    g[p].pb(i+1);
    pa[i+1]=p;
  }
  dis[0]=1;
  dfs(0);
  STree st(n);
  vector<ll> ini(n);
  vector<ll> inv(n);
  fore(i,0,n){
    ini[times[i].fst]=dis[i];
    inv[times[i].fst]=i;
  }
  st.init(ini);
  ll res = 0; ll it = 0;
  while(it<k && res < n){
    it++; res += st.query(0,n);
    ll maxi = st.query(0,n);
    // cout << maxi << "\n";
    ll l = 0, r = n-1;
    while(l<=r){
      ll me=(l+r)/2;
      if(st.query(l,me+1)>=maxi)r=me-1;
      else l =me+1;
    }
    ll x = inv[l];
    // cout << x << "\n";
    st.upd(times[x].fst,times[x].fst+1,-100000);
    // cout << st.query(times[x].fst, times[x].fst+1) << " queryy\n";
    vis[x]=1;
    while(pa[x]>=0 && !vis[pa[x]]){
      vis[pa[x]]=1;
      x=pa[x];
      st.upd(times[x].fst+1, times[x].snd, -1);
      st.upd(times[x].fst,times[x].fst+1,-100000);
    }
  }
  cout << res << "\n";
  return 0;
}