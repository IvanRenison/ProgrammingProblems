// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/J
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

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  string s;cin>>s;
  ll n = SZ(s);
  vector<ll> pre_s(n+1);
  vector<ll> canti(n);
  ll act = 0;
  for(int i = n-2;i>=0;--i){
    if(s[i]=='v' && s[i+1]=='v')++act;
    if(s[i]=='o')canti[i]=act;
  }
  fore(i,0,n){
    pre_s[i+1]=pre_s[i]+canti[i];
  }
  ll res = 0;
  fore(i,0,n-1){
    if(s[i]=='v' && s[i+1]=='v'){
      res += pre_s[n]-pre_s[i+1];
    }
  }
  cout << res << "\n";
}