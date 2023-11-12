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

int main(){FIN;

  ull N;
  cin >> N;
  char c;
  cin >> c;
  ull X, Y;
  cin >> X >> c >> Y;
  ull ans = 0;

  fore(i, 0, N) {
    ull x, y;
    cin >> c >> x >> c >> y;
    X += x;
    Y += y;
    X += Y/100;
    Y = Y % 100;
    if (Y != 0) {
      ans++;
    }
  }

  cout << ans << '\n';

  return 0;
}