#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

struct RMQ {
  vector<vector<ll>> jmp;
  RMQ(const vector<ll>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j, 0, SZ(jmp[k])) {
        jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
      }
    }
  }
  ll query(ll a, ll b) {
    assert(a < b);
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - 1 << dep]);
  }
};

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vi hs(n);
  for (ll& h : hs) {
    cin >> h;
  }

  RMQ hs_rmq(hs);

  


}