// https://codeforces.com/gym/101492/problem/G
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, carranza = b; i < carranza; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset(a, v, sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;

ll solve(ll N, vii& edges) {
  vector<vi> adj(N);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi ord;
  vector<bool> vis(N, false);
  vi s = {0};
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();
    ord.push_back(u);
    for (ll v : adj[u]) if (!vis[v]) {
      vis[v] = true;
      s.push_back(v);
    }
  }

  vector<bool> used(N + 1, false);
  vi colors(N, -1);
  for (ll v : ord) {
    vector<ll> pinted;
    for (ll u : adj[v]) {
      if (colors[u] != -1) {
        used[colors[u]] = true;
        pinted.push_back(colors[u]);
      }
    }
    ll c = 0;
    while (used[c]) {
      c++;
    }
    colors[v] = c;
    for (ll co : pinted) {
      used[co] = false;
    }
  }

  ll max_color = *max_element(ALL(colors));

  return max_color + 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, M;
  cin >> N >> M;
  vii edges(M);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  ll ans = solve(N, edges);
  cout << ans << '\n';
}
