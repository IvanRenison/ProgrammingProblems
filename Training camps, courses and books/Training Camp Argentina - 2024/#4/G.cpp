// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll v;
  cin >> v;
  vi c(10);
  vii ps;
  fore(i, 1, 10) cin >> c[i], ps.pb({c[i], i});
  sort(ALL(ps));
  auto [mincost, cheapest] = *begin(ps);
  if (mincost > v) {
    cout << -1 << "\n";
    return 0;
  }
  ll sz = v / mincost;
  // cerr << sz << endl;
  v -= mincost * sz;
  vi res(sz, cheapest);
  fore(i, 0, sz) {
    for (ll d = 9; d > cheapest; d--) {
      if (v >= c[d] - mincost) {
        res[i] = d;
        v -= c[d] - mincost;
        break;
      }
    }
  }
  fore(i, 0, sz) cout << res[i];
  cout << "\n";
}