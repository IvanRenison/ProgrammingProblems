// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/G
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

struct Tree{
  typedef ll T;
  static constexpr T neut = 1e18;
  T f(T a, T b){ return min(a,b);}
  vector<T> s; ll n;
  Tree(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val){
    for (s[pos += n] = val; pos/=2;)
      s[pos] = f(s[pos*2],s[pos*2+1]);
  }
  T query(ll b, ll e){
    T ra = neut, rb = neut;
    for(b += n, e+=n;b<e;b/=2,e/=2){
      if(b&1) ra = f(ra, s[b++]);
      if(e&1) rb = f(s[--e],rb);
    }
    return f(ra,rb);
  }
};



int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n;cin>>n;
  vector<ll> a(n), c(n);
  ll res = 0;
  fore(i,0,n)cin>>a[i]>>c[i], res += c[i];
  vector<pair<ll,ll>> comp(n);
  fore(i,0,n)comp[i]={a[i],i};
  sort(ALL(comp));
  Tree st_limpio(n), st_ind(n);
  st_limpio.upd(n-1,0), st_ind.upd(n-1,comp[n-1].fst);
  for(int i = n-2;i>=0;--i){
    ll ind = comp[i].snd;
    ll priti = lower_bound(ALL(comp),make_pair(a[ind]+c[ind],0ll))-comp.begin();
    ll res = min(st_limpio.query(i+1,priti),-c[ind]-a[ind]+st_ind.query(priti,n));
    st_limpio.upd(i,res);
    st_ind.upd(i,a[ind]+res);
  }
  // fore(i,0,n){}
  res += st_limpio.query(0,1);
  cout << res << "\n";
}