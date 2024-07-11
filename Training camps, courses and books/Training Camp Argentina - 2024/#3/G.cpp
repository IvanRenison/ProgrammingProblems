// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/G
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
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
const int NMAX = 1e6+10;
const int MOD = 1e9+7;

int cr[NMAX];

ll mul(ll x, ll y){
  return (x*y)%MOD;
}
ll add(ll x, ll y){
  ll res = x+y;
  if(res>=MOD)res-=MOD;
  return res;
}
ll sub(ll x, ll y){
  ll res = x+MOD-y;
  res %= MOD;
  return res;
}

ll bin(ll b, ll e){
  if(e==0)return 1;
  ll x = bin(b,e/2);
  if(e&1){
    return mul(x,mul(b,x));
  } else {
    return mul(x,x);
  }
}


void init_sieve(){
  memset(cr,-1,sizeof(cr));
  fore(i,2,NMAX)if(cr[i]<0)for(ll j=1LL*i*i;j<NMAX;j+=i)cr[j]=i;
}
map<int,int> fact(int n){
  map<int,int> r;
  while(cr[n]>=0)r[cr[n]]++,n/=cr[n];
  if(n>1)r[n]++;
  return r;
}

vector<vector<ll>> donde(NMAX);

ll f(ll x, ll y){
  return mul(x,y);
}

typedef ll T;


#define neut 1
struct Tree {
  vector<T> s;
  ll n;
  Tree(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) {
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};


int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  init_sieve();
  int n;cin>>n;
  vector<map<int,int>> facts(n);
  vector<ll> a(n), pre_prod(n+1,1);
  fore(i,0,n){
    cin>>a[i];
    pre_prod[i+1]=mul(pre_prod[i],a[i]);
    facts[i]=fact(a[i]);
    for(auto j:facts[i]){
      donde[j.fst].pb(i);
    }
  }
  Tree st(n);
  fore(i,2,NMAX){
    if(cr[i]<0 && SZ(donde[i])){
      ll query = st.query(donde[i].back(),donde[i].back()+1);
      st.upd(donde[i].back(),mul(query,sub(1,bin(i,MOD-2))));
      donde[i].pop_back();
    }
  }
  ll q;cin>>q;
  vector<vector<pair<ll,ll>>> queries(n);
  fore(i,0,q){
    ll l,r;cin>>l>>r;--l;--r;
    queries[r].pb({l,i});
  }
  vector<ll> ans(q);
  for(int i = n-1;i>=0;--i){
    fore(j,0,SZ(queries[i])){
      ll l = queries[i][j].fst, ind = queries[i][j].snd;
      ans[ind] = st.query(l,i+1);
      ll aux = mul(pre_prod[i+1],bin(pre_prod[l],MOD-2));
      ans[ind] = mul(ans[ind],aux);
    }
    for(auto j:facts[i]){
      if(SZ(donde[j.fst])){
        ll query = st.query(donde[j.fst].back(),donde[j.fst].back()+1);
        st.upd(donde[j.fst].back(),mul(query,sub(1,bin(j.fst,MOD-2))));
        donde[j.fst].pop_back();
      }
    }
  }
  for(auto i:ans) cout << i << "\n";
}