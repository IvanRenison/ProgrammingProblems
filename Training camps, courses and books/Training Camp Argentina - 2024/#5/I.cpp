// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/I
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
const ll INF = 1e6;

template<class T>
struct RMQ{
  vector<vector<T>> jmp;
  RMQ(const vector<T>&V) : jmp(1,V) {
    for(ll pw = 1, k = 1;pw*2 <=SZ(V); pw *= 2, ++k){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k])){
        jmp[k][j] = min(jmp[k-1][j],jmp[k-1][j+pw]);
      }
    }
  }
  T query(ll a, ll b){
    assert(a < b);
    ll dep = 63 - __builtin_clzll(b-a);
    return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};



int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n;cin>>n;
  vector<ll> a(n);
  vector<pair<ll,ll>> armq(3*n);
  fore(i,0,n){
    cin>>a[i];
    armq[i]={a[i],i};
    armq[i+n]={a[i],i};
    armq[i+2*n]={a[i],i};
  }
  RMQ st(armq);
  vector<ll> priti(2*n,INF);
  fore(i,0,2*n){
    ll l = i+1, r = 3*n-1;
    ll val = armq[i].fst/2;
    if(armq[i].fst%2==0)--val;
    while(l<=r){
      ll mid = (l+r)/2;
      if(st.query(i+1,1+mid).fst<=val)r=mid-1;
      else l=mid+1;
    }
    if(l<3*n)priti[i]=l;
  }
  vector<ll> ans(n);
  RMQ ahora(priti);
  fore(i,0,n){
    ll que = ahora.query(i,2*n);
    if(que>=INF){ans[i]=-1;continue;}
    ans[i]=que-i;
  }
  for(auto i:ans) cout << i << " ";
  cout << "\n";
}