#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<ll> vi;


ull solve(vi Gs) {
  ull sum = 0, N = Gs.size();
  for(ll G : Gs) {
    sum += G;
  }

  ull c = sum/N;

  ull j;
  fore(i, 0, N) {
    if (Gs[i] >= c) {
      j = i;
      break;
    }
  }

  ull ans = 0, extra = 0;
  fore(i, j, j + 2*N) {
    ll& G = Gs[i % N];

    ans += extra;
    if (G < c) {
      if (extra >= c - G) {
        extra -= c - G;
        G = c;
      } else {
        G += extra;
        extra = 0;
      }
    } else {
      extra += G - c;
      G = c;
    }
  }

  return ans;
}


int main(){FIN;

  ull N;
  cin >> N;
  vi Gs(N);
  for(auto& G : Gs) {
    cin >> G;
  }

  ull ans = solve(Gs);
  reverse(ALL(Gs));

  ans = min(ans, solve(Gs));

  cout << ans << '\n';

  return 0;
}