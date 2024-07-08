// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/F
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

int dp[2][460][460];

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  int n,k;cin>>n>>k;
  string s;cin>>s;
  fore(i,0,n+5){
    fore(j,0,n+5){
      dp[n % 2][i][j]=0;
    }
  }
  for(int i = n-1;i>=0;--i){
    for(int j = n;j>=0;--j){
      for(int z = n;z>=0;--z){
        if(s[i]=='0'){
          dp[i % 2][j][z]=dp[(i+1)%2][j][0];
        } else if(j>0){
          dp[i % 2][j][z]=min(z+1+dp[(i+1)%2][j][z+1],dp[(i+1)%2][j-1][0]);
        } else {
          dp[i % 2][j][z]=z+1+dp[(i+1)%2][j][z+1];
        }
      }
    }
  }
  for(int i = 0;i<=n;++i){
    if(dp[0][i][0]<=k){
      cout << i << "\n";
      return 0;
    }
  }
}