// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/D
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


struct Tree {
  typedef ll T;
  T neut = 0;
  T f(T a, T b){return a+b;}
  vector<T> st;
  vector<ll> L,R;
  ll n, rt;
  Tree(ll n) : st(1,neut), L(1),R(1),n(n),rt(0){}
  ll new_node(T v, ll l, ll r){
    st.pb(v), L.pb(l), R.pb(r);
    return SZ(st)-1;
  }
  ll upd(ll k, ll s, ll e, ll p, T v){
    ll ks = new_node(st[k],L[k],R[k]);
    if(s+1==e){
      st[ks]=v;
      return ks;
    }
    ll m = (s+e)/2;
    if(p<m)L[ks] = upd(L[ks],s,m,p,v);
    else R[ks] = upd(R[ks],m,e,p,v);
    st[ks] = f(st[L[ks]],st[R[ks]]);
    return ks;
  }
  T query(ll k, ll s, ll e, ll a, ll b){
    if(e<=a || b<=s) return neut;
    if(a<=s && e<=b) return st[k];
    ll m = (s+e)/2;
    return f(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
  ll upd(ll ver, ll p, T v){return rt=upd(ver,0,n,p,v);}
  ll upd(ll p,T v){return upd(rt,p,v);}
  T query(ll ver, ll a, ll b){return query(ver,0,n,a,b);}
};


int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,m,q;cin>>n>>m>>q;
  vector<ll> a(n);
  vector<pair<ll,ll>> a_sor(m);
  fore(i,0,n)cin>>a[i],--a[i], a_sor[a[i]].fst++;
  fore(i,0,m) a_sor[i].snd=i;
  sort(ALL(a_sor));
  vector<ll> pre_s(m+1);
  vector<ll> inv(m);
  vector<ll> roots(m);
  vector<ll> mini_par(m+1,ll(1e18));
  Tree st(m);
  fore(i,0,m){
    pre_s[i+1]=pre_s[i]+a_sor[i].fst;
    // cout << pre_s[i+1] << " ";
    inv[a_sor[i].snd]=i;
    mini_par[i+1] = min(mini_par[i],a_sor[i].snd);
  }
  // cout << "\n";
  fore(i,0,m){
    roots[i]=st.upd(inv[i],1);
  }
  // fore(i,0,m){
  //   fore(j,0,m){
  //     cout << st.query(roots[i],j,j+1) << " ";
  //   }
  //   cout << "\n";
  // }
  while(q--){
    ll k;cin>>k;
    k-=n;
    ll l = 0, r = m-1;
    while(l<=r){
      ll mid = (l+r)/2;
      ll val = a_sor[mid].fst*(mid+1)-pre_s[mid+1];
      // if(k==1 && mid==1) cout << val << " accaaaa\n";
      if(val<k)l=mid+1;
      else r=mid-1;
    }
    // cout << r << " aca\n";
    k -= a_sor[r].fst*r-pre_s[r];
    // cout << k << " acaaaa\n";
    ll mini = mini_par[r+1];
    ll resto;
    if(mini>0)resto=st.query(roots[mini-1],0,r+1);
    else resto = 0;
    k--;
    k%=(r+1);
    // cout << k << " " << resto << " " << mini << " aco\n";
    ll l1 = mini, r1 = m-1;
    while(l1<=r1){
      ll mid = (l1+r1)/2;
      if(st.query(roots[mid],0,r+1)-resto>=k+1)r1=mid-1;
      else l1=mid+1;
    }
    cout << l1+1 << "\n";
  }
}