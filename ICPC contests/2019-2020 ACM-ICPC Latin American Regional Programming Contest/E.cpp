#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){FIN;
  string b; cin >> b;

  ll s; cin >> s;
  vi es;
  fore(i, 0, SZ(b)) {
    if (b[i] == 'E') {
      es.pb(i);
    }
  }
  ll res = 0;
  fore(i, 0, SZ(es)) {
    ll dist = (es[(i + 1) % SZ(es)] - es[i] + SZ(b)) % SZ(b);
    ll x = min(s, dist);
    res += (x * (x + 1)) / 2;
    res += max(s - dist, 0ll) * x;
  }

  cout << res << "\n";


  return 0;
}