#include<bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ull> vu;

struct STree {
  vector<ll> t;int n;
  STree(int n):n(n),t(2*n+5,0){}
  void upd(int p, ll v){
    p+=n;
    for(t[p]=v;p>1;p>>=1) t[p>>1] = max(t[p],t[p^1]);
  }
  ll query(int l, int r){
    ll res = 0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1) res = max(res,t[l++]);
      if(r&1) res = max(res,t[--r]);
    }
    return res;
  }
};


int main(){FIN;
  ll n;cin>>n;
  vector<vector<ll>> plata(n);vector<pair<ll,ll>> lindo(n);
  vector<vector<ll>> todo(n);
  map<pair<ll,ll>,ll> ind;
  fore(i,0,n){
    ll b,f,d;cin>>b>>f>>d;
    if(ind.count({b,f})){
      todo[ind[{b,f}]][2]+=d;
      plata[i] ={0,0,i};
      lindo[i] = {0,i};
      todo[i]={0,0,0};
    } else {
      plata[i] ={f,-b,i};
      lindo[i] = {b,i};
      todo[i]={b,f,d};
      ind[{b,f}]=i;
    }
  }
  sort(ALL(plata));sort(ALL(lindo));
  vector<ll> donde(n);
  fore(i,0,n){
    donde[lindo[i].snd]=i;
  }

  STree st(n);
  for(int i = n-1;i>=0;--i){
    ll posi = lower_bound(ALL(lindo),make_pair(todo[plata[i][2]][0]+1,0LL))-lindo.begin();
    // cout << i << " " << posi << "\n";
    ll que = st.query(posi,n);
    st.upd(donde[plata[i][2]],que+todo[plata[i][2]][2]);
    // fore(i,0,n){
    //   cout <<st.query(i,i+1) << " ";
    // }
    // cout << "\n";
  }
  cout << st.query(0,n) << "\n";
  return 0;
}


// 5
// 1 2 50
// 2 1 50
// 2 2 30
// 1 1 30
// 1 1 600
// 4 3
// 0 50 0 0 0
// 3 5
// 0 50 0 0 30
// 2 3
// 0 50 660 0 30
// 1 5
// 0 50 660 50 30
// 0 3
// 0 100 660 50 30
// 660
