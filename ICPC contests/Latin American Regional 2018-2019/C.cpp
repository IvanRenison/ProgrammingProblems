// https://matcomgrader.com/problem/9544/cheap-trips/
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
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
constexpr ll MAXN = 1e4 + 10;

  ll n;
vector<ii> trips(MAXN);
vector<vector<vi>> dp(MAXN, vector<vi>(7, vi(120, -1)));
ll f(ll pos, ll prevs, ll time) {
  if (pos == n) return 0;

  if (time >= 120) time = 0;

  ll &r = dp[pos][prevs][time];
  if (r != -1) return r;

  r = trips[pos].snd + f(pos + 1, 1, trips[pos].fst);
  if (1 <= prevs && prevs < 6 && time != 0)
    r = min(r,
      trips[pos].snd / (2*(1+(prevs>=2))) + f(pos + 1, prevs + 1, time + trips[pos].fst)
    );

  return r;

}

int main(){FIN;
  cin >> n;
fore(i, 0, n)
{
  ll d, c; cin >> d >> c;
  trips[i] = {d, c*4};
}

  cout << fixed << setprecision(2) << (ld)f(0, 0, 0) / 4.0 << "\n";

  return 0;
}
