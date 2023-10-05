// https://codeforces.com/gym/101889
#include<bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;i++)
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
const ll NMAX = 1010;


ll dp[NMAX][NMAX];
string s;ll n;

ll f(ll x, ll mod){
  if(x==SZ(s) && mod == 0)return 1;
  if(x==SZ(s)) return 0;
  ll &res = dp[x][mod];
  if(res!=-1)return res;
  if(s[x]=='?'){
    res = 0;
    ll pri = 0;
    if(x==0) pri++;
    fore(i,pri,10){
      res = max(res,f(x+1,(mod*10+i)%n));
    }
  } else {
    ll di = s[x]-'0';
    res = f(x+1,((mod*10)+di)%n);
  }
  // cout << x << " " << mod << " " << res << "\n";
  return res;
}
string ans;

void build(ll x,ll mod){
  if(x==SZ(s))return;
  if(s[x]=='?'){
    ll pri = 0;
    if(x==0) pri++;
    fore(i,pri,10){
      if(f(x+1,(mod*10+i)%n)){
        ans.pb(i+'0');
        build(x+1,(mod*10+i)%n);
        return;
      }
    }
  } else {
    ans.pb(s[x]);
    build(x+1,(mod*10+s[x]-'0')%n);
    return;
  }
}


int main(){FIN;
  cin>>s>>n;
  mset(dp,-1);
  // cout << s << " " << n << "\n";
  if(!f(0,0)){
    cout << "*\n";
    return 0;
  }
  build(0,0);

  cout << ans << "\n";

  return 0;
}