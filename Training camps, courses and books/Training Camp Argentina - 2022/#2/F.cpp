#include<bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,gmat=b; i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;


ull solve(ull n, ull k) {
  ull ans = 1;
  if (k >= 2) {
    ans += n * (n-1) / 2;
  }
  if (k >= 3) {
    ans += n * (n-1) * (n-2) / 3;
  }
  if (k >= 4) {
    ans += n*(n-1)*(n-2) * (n-3) * 3 / 8;
  }

  return ans;
}


int main() {

  ull n, k;
  cin >> n >> k;

  cout << solve(n, k) << '\n';



  return 0;
}
