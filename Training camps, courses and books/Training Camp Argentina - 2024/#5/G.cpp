// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;


ll dp[15][2];
string n;


ll f(ll x, ll b){
  if(x==SZ(n))return 1;
  ll &res = dp[x][b];
  if(res!=-1)return res;
  if(b){
    res = 1;
    fore(i,1,10){
      res = max(res,f(x+1,1)*i);
    }
  } else {
    res = f(x+1,0)*((n[x]-'0')>0?(n[x]-'0'):1);
    fore(i,0,n[x]-'0'){
      ll di = (i==0)?1:i;
      res = max(res,di*f(x+1,1));
    }
  }
  return res;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
 mset(dp,-1);
  cin>>n;
  ll res = f(0,0);
  cout << res << "\n";
}