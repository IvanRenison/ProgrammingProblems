// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/E
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
typedef long double ld;
const int INF = 1e8;


int dp[415][215][215];

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,k;cin>>n>>k;
  vector<int> a(n);
  fore(i,0,n)cin>>a[i];
  sort(ALL(a));
  dp[n][0][0]=0;
  fore(i,0,k+1){
    fore(j,1,k+5){
      dp[n][i][j]=-INF;
    }
  }

  for(int i = n-1;i>=0;--i){
    for(int j = k;j>=0;--j){
      for(int z = k;z>=0;--z){
        if(z&&j){
          dp[i][j][z] = max(a[i]+dp[i+1][j-1][z-1],-a[i]+dp[i+1][j][z+1]);
        } else if(z) {
          dp[i][j][z] = -INF;
        } else {
          dp[i][j][z] = max(-a[i]+dp[i+1][j][z+1],dp[i+1][j][z]);
        }
        // cout << i << " " << j << " " << z << " " << dp[i][j][z] << "\n";
      }
    }
  }

  cout << dp[0][k][0] << "\n";

}