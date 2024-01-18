// https://codeforces.com/gym/104848/problem/H
#include <bits/stdtr1c++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
const ll NMAX = 1e5+10;
string s;
set<string> poss;
ll n;
ll dp[NMAX];

ll f(ll x){
  if(x==n)return 0;
  ll &res = dp[x];
  if(res!=-1)return res;
  res = 1+f(x+1);
  string aux = "";
  aux+=s[x];
  fore(i,x+1,min(n,x+3)){
    aux+=s[i];
    if(poss.count(aux)){
      res = min(res,1+f(i+1));
    }
  }
  return res;
}
vector<string> ans;

void build(ll x){
  if(x==n)return;
  ll res = f(x);
  string aux = "";aux+=s[x];
  if(res==1+f(x+1)){
    ans.pb(aux);
    build(x+1);
    return;
  }
  fore(i,x+1,min(n,x+3)){
    aux+=s[i];
    if(poss.count(aux) && 1+f(i+1)==res){
      ans.pb(aux);
      build(i+1);
      return;
    }
  }
}

int main(){FIN;
  mset(dp,-1);
  cin>>n;
  cin>>s;
  poss.insert("MMM");poss.insert("MM");poss.insert("M");
  poss.insert("CCC");poss.insert("CC");poss.insert("CC");
  poss.insert("XXX");poss.insert("XX");poss.insert("X");
  poss.insert("III");poss.insert("II");poss.insert("I");
  poss.insert("MCM"); poss.insert("CXC");poss.insert("XIX");
  build(0);
  cout << SZ(ans) << "\n";
  fore(i,0,SZ(ans)){
    cout << ans[i] << "\n";
  }
  return 0;
}
