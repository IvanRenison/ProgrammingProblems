// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T> &V) : jmp(1,V) {
    for(ll pw = 1, k =1;pw*2<=SZ(V);pw*=2,k++){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j]=min(jmp[k-1][j],jmp[k-1][j+pw]);
    }
  }
  T query(ll a, ll b){
    assert(a<b);
    ll dep = 63-__builtin_clzll(b-a);
    return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};
const ll INF = 1e18;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,c;cin>>n>>c;
  vector<ll> a(n), pre_s(n+1);
  fore(i,0,n)cin>>a[i], pre_s[i+1]=pre_s[i]+a[i];
  RMQ st(a);
  ll res = INF;
  vector<ll> dp(n+1,0);
  for(int i = n-1;i>=0;--i){
    dp[i]=a[i]+dp[i+1];
    if(i+c<=n)dp[i]=min(dp[i],pre_s[i+c]-pre_s[i]-st.query(i,i+c)+dp[i+c]);
  }
  cout << dp[0] << "\n";
}