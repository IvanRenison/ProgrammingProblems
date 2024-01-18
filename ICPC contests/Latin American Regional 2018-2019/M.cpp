// https://matcomgrader.com/problem/9554/mount-marathon/
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;
  ll n;cin>>n;
  vector<ll> c(n);
  fore(i,0,n)cin>>c[i];
  reverse(ALL(c));
  ll res = 0;
  fore(i,1,n){
    if(c[i]<c[i-1])++res;
  }
  cout << res+1 << '\n';
  return 0;
}