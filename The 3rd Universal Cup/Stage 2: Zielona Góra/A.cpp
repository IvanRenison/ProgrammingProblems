#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

ll solve(ll n, const vii& edges) {
  vector<vi> in(n), out(n);
  for (auto [u, v] : edges) {
    in[v].push_back(u), out[u].push_back(v);
  }

  vector<bool> vis0(n, false), visn(n, false), vis(n, false);
  vi s = {0};
  vis0[0] = true;
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();
    for (ll v : out[u]) {
      if (!vis0[v]) {
        vis0[v] = true;
        s.push_back(v);
      }
    }
  }

  if (!vis0[n-1]) return 0;

  s = {n-1};
  visn[n-1] = true;
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();
    for (ll v : in[u]) {
      if (!visn[v]) {
        visn[v] = true;
        s.push_back(v);
      }
    }
  }

  ll N = 0;
  fore(i, 0, n) {
    vis[i] = vis0[i] && visn[i];
    N += vis[i];
  }

  ll M = 0;
  for (auto [u, v] : edges) {
    M += vis[u] && vis[v];
  }

  ll ans = M - N + 2;

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll n, m;
  cin >> n >> m;
  vii edges(m);
  for (auto& [a, b] : edges) {
    cin >> a >> b;
    a--; b--;
  }

  ll ans = solve(n, edges);
  cout << ans << '\n';

}
