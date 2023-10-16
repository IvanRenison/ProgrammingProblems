// https://codeforces.com/contest/1662/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mste(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;

  ull t;
  cin >> t;
  while(t--) {
    vi bests(10, -1);
    ull n;
    cin >> n;
    while(n--) {
      ull b, d;
      cin >> b >> d;
      d--;

      if ((ll)b > bests[d]) {
        bests[d] = b;
      }
    }

    bool p = true;
    ull ans = 0;
    fore(i, 0, 10) {
      if (bests[i] == -1) {
        p = false;
      } else {
        ans +=bests[i];
      }
    }

    if (p) {
      cout << ans << '\n';
    } else {
      cout << "MOREPROBLEMS\n";
    }
  }

	return 0;
}