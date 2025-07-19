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
typedef vector<ii> vii;

ll inf = 1ll << 60;

ll solve(vector<vi>& grid) {
  ll n = grid.size();

  ll lu = inf, u = inf, ru = inf;
  ll l  = inf, c = inf, r  = inf;
  ll ld = inf, d = inf, rd = inf;


  fore(i, 0, n/2) fore(j, 0, n/2) {
    lu = min(lu, grid[i][j]);
  }
  fore(i, 0, n/2) {
    u = min(u, grid[i][n/2]);
  }
  fore(i, 0, n/2) fore(j, n/2 + 1, n) {
    ru = min(ru, grid[i][j]);
  }

  fore(j, 0, n/2) {
    l = min(l, grid[n/2][j]);
  }
  c = grid[n/2][n/2];
  fore(j, n/2 + 1, n) {
    r = min(r, grid[n/2][j]);
  }

  fore(i, n/2 + 1, n) fore(j, 0, n/2) {
    ld = min(ld, grid[i][j]);
  }
  fore(i, n/2 + 1, n) {
    d = min(d, grid[i][n/2]);
  }
  fore(i, n/2 + 1, n) fore(j, n/2 + 1, n) {
    rd = min(rd, grid[i][j]);
  }


  ll ans = min({
    c,
    min(u, min(l, lu) + min(r, ru)) + min(d, min(l, ld) + min(r, rd)),
    min(l, min(u, lu) + min(d, ld)) + min(r, min(u, ru) + min(d, rd)),
  });

  return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vector<vi> grid(n, vi(n));
    fore(i, 0, n) fore(j, 0, n) {
      cin >> grid[i][j];
    }

    ll ans = solve(grid);
    cout << ans << '\n';
  }
}