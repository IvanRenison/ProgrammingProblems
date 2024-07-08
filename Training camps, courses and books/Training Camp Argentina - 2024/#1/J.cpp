// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/J
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m; cin >> n >> m;
  vector<vector<ii>> g(n);
  fore(i, 0, m) {
    ll u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[u].pb({w, v});
    g[v].pb({w, u});
  }

  vector<char> vis(n, 0);
  auto dfs = [&](ll v, auto&& dfs) -> void {
    vis[v] = 1;
    for(auto [_, u] : g[v]) if (!vis[u]) {
      dfs(u, dfs);
    }
  };
  dfs(0, dfs);
  if (!vis[n-1]) {
    cout << "inf\n";
    return 0;
  }

  string cut = "1";
  set<ll> cut_set;
  cut_set.insert(0);
  fore(i, 1, n) cut.pb('0');
  set<ii> active;
  for (ii e : g[0]) active.insert(e);
  vector<pair<string, ll>> res;

  auto play = [&]() {
      set<ii> next_active;
      ll tx = begin(active)->fst;
      res.pb({cut, tx});
      for (auto [t, to] : active) {
        next_active.insert({t - tx, to});
      }
      active = next_active;
  };
  auto update_cut = [&]() -> bool {
    set<ii> next_active;
    while (SZ(active) && begin(active)->fst == 0) {
      auto v = begin(active)->snd;
      if (v == n-1) return true;
      cut[v] = '1';
      cut_set.insert(v);
      for (auto [t, to] : g[v]) {
        next_active.insert({t, to});
      }
      active.erase({0, v});
    }
    for (auto [t, to] : active)
      next_active.insert({t, to});

    active = next_active;
    return false;
  };
  auto filter = [&]() {
    set<ii> next_active;
    for (auto [t, to] : active) {
      if (!cut_set.count(to)) next_active.insert({t, to});
    }
    active = next_active;
  };

  while(1) {
    play();
    if (update_cut())
      break;
    filter();
  }

  ll T = 0;
  for (auto [s, time] : res) T += time;
  assert(SZ(res) <= n*n);
  cout << T << " " << SZ(res) << '\n';
  for (auto [s, time] : res) {
    cout << s << " " << time << "\n";
  }

}