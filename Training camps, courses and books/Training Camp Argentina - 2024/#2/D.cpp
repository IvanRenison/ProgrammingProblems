// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/D
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
typedef long double ld;
const int NMAX = 1e5+10;
const ld EPS = 1e-10;

pair<int,ld> dp[NMAX][11][2];
ll n,d;
ll a[NMAX];
ld logs[NMAX];

pair<int,ld> f(ll x, ll y, ll puse){
  if(x==n && y==d && puse) return {1,0};
  if(x==n) return {0,0};
  pair<int,ld> &res = dp[x][y][puse];
  if(res.fst!=-1)return res;
  pair<int,ld> con = {f(x+1,(y*a[x])%10,1).fst,f(x+1,(y*a[x])%10,1).snd+logs[x]};
  pair<int,ld> sin = f(x+1,y,puse);

  res = max(con,sin);
  // cout << x << " " << y << " " << puse << " " << res.fst << " " << res.snd << "\n";
  return res;
}

vector<ll> ans;

void build(ll x, ll y,ll puse){
  // cout << x << " " << y << " " << puse << "\n";
  if(x==n)return;
  pair<int,ld> res = f(x,y,puse);
  if(f(x+1,(y*a[x])%10,1).fst && abs(res.snd-f(x+1,(y*a[x])%10,1).snd-logs[x])<EPS){
    ans.pb(a[x]);
    build(x+1,(y*a[x])%10,1);
  } else {
    build(x+1,y,puse);
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>d;
  fore(i,0,n){
    cin>>a[i];
    logs[i]=logl(a[i]);
  }
  fore(i,0,n+5){
    fore(j,0,11){
      fore(z,0,2){
        dp[i][j][z]={-1,-1};
      }
    }
  }
  if(f(0,1,0).fst!=1){
    cout << "-1\n";
    return 0;
  }
  build(0,1,0);
  sort(ALL(ans));
  cout << SZ(ans) << "\n";
  for(auto i:ans) cout << i << " ";
  cout << "\n";

}