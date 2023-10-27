// https://matcomgrader.com/problem/9553/looking-for-the-risk-factor/
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
const ll NMAX = 1e5+10;


struct STree{
  vector<int> t;int n;
  STree(int n):n(n),t(2*n+5,0){}
  void upd(int p, int v){
    p+=n;
    for(t[p]=v;p>1;p>>=1) t[p>>1]=t[p]+t[p^1];
  }
  int query(int l,int r){
    int res=0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1) res=res+t[l++];
      if(r&1) res=res+t[--r];
    }
    return res;
  }
};

// #define oper(a,b) (a+b)
// #define NEUT 0

// struct STree{
//   vector<int> st,L,R;int n,sz,rt;
//   STree(int n): st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),sz(1){}
//   int new_node(int v, int l=0, int r=0){
//     int ks=SZ(st);
//     st.pb(v);L.pb(1);R.pb(r);
//     return ks;
//   }
//   int init(int s, int e, vector<int> &a){
//     if(s+1==e)return new_node(a[s]);
//     int m=(s+e)/2, l =init(s,m,a),r=init(m,e,a);
//     return new_node(oper(st[l],st[r]),l,r);
//   }
//   int upd(int k,int s,int e,int p,int v){
//     int ks=new_node(st[k],L[k],R[k]);
//     if(s+1==e){st[ks]=v;return ks;}
//     int m=(s+e)/2,ps;
//     if(p<m)ps=upd(L[ks],s,m,p,v),L[ks]=ps;
//     else ps=upd(R[ks],m,e,p,v),R[ks]=ps;
//     st[ks]=oper(st[L[ks]],st[R[ks]]);
//     return ks;
//   }
//   int query(int k,int s,int e,int a,int b){
//     if(e<=a||b<=s)return NEUT;
//     if(a<=s&&e<=b)return st[k];
//     int m=(s+e)/2;
//     return oper(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
//   }
//   int init(vector<int> &a){return init(0,n,a);}
//   int upd(int k,int p,int v){return rt=upd(k,0,n,p,v);}
//   int upd(int p,int v){return upd(rt,p,v);}
//   int query(int k,int a,int b){return query(k,0,n,a,b);};
// };


int main(){
  ll q;cin>>q;
  vector<ll> ans(q);
  vector<vector<pair<ll,ll>>> qs(NMAX);
  fore(i,0,q){
    ll n,k;cin>>n>>k;
    qs[k].pb({ll(i),n});
  }
  vector<ll> mpf(NMAX,-1);
  vector<int> limpio(NMAX);
  STree st(NMAX);
  fore(i,2,NMAX){
    if(mpf[i]==-1){
      mpf[i]=i;
      for(int j = i+i; j<NMAX; j+=i){
        mpf[j]=i;
      }
    }
  }
  vector<vector<ll>> pfs(NMAX);
  fore(i,2,NMAX){
    pfs[mpf[i]].pb(i);
  }
  vector<ll> roots(NMAX);
  fore(i,2,NMAX){
    fore(j,0,SZ(pfs[i])){
      st.upd(pfs[i][j],1);
    }
    fore(j,0,SZ(qs[i])){
      ll n= qs[i][j].snd, ind = qs[i][j].fst;
      ans[ind]=st.query(0,n+1);
    }
  }
  for(auto i:ans)cout << i << "\n";
  return 0;
}