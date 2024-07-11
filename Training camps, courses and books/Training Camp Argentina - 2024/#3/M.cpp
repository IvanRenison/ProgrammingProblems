// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/M
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
typedef vector<ii> vii;

optional<vii> solve(ll n, ll D, const vii& edges) {
  vector<vi> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  if (adj[0].size() < D) {
    return {};
  }

  vii ans;
  vi vis(n, -1);
  vector<bool> colors0;

  fore(i, 1, n) {
    if (vis[i] == -1) {
      ll c = colors0.size();
      colors0.push_back(false);
      vis[i] = c;
      vi s = {i};
      while (!s.empty()) {
        ll u = s.back();
        s.pop_back();
        for (ll v : adj[u]) {
          if (v == 0) {
            colors0.back() = true;
          } else if (vis[v] == -1) {
            vis[v] = c;
            s.push_back(v);
            ans.push_back({u, v});
          }
        }
      }
      if (!colors0.back()) {
        return {};
      }
    }
  }

  ll colors = colors0.size();
  if (colors > D) {
    return {};
  }

  vii real_ans;
  vi s;

  vector<bool> color_conn(colors, false);
  vector<bool> used(n, false);
  used[0] = true;
  for (ll u : adj[0]) {
    ll c = vis[u];
    if (!color_conn[c]) {
      used[u] = true;
      s.push_back(u);
      color_conn[c] = true;
      real_ans.push_back({0, u});
    }
  }

  vector<bool> to_remove(n);
  ll rest = D - colors;
  for (ll u : adj[0]) {
    if (rest == 0) {
      break;
    }
    if (!used[u]) {
      used[u] = true;
      s.push_back(u);
      real_ans.push_back({0, u});
      rest--;
    }
  }


  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();

    for (ll v : adj[u]) {
      if (!used[v]) {
        used[v] = true;
        s.push_back(v);
        real_ans.push_back({u, v});
      }
    }
  }

  return real_ans;

}

bool check(ll n, ll D, const vii& edges, const vii& ans) {
  set<ii> edges_set;
  for (auto [u, v] : edges) {
    edges_set.insert(minmax(u, v));
  }

  for (auto [u, v] : ans) {
    if (!edges_set.count(minmax(u, v))) {
      return false;
    }
  }

  vector<vi> ans_adj(n);
  for (auto [u, v] : ans) {
    ans_adj[u].push_back(v), ans_adj[v].push_back(u);
  }

  if (ans_adj[0].size() != D) {
    return false;
  }

  vector<bool> vis(n);
  vi s = {0};
  vis[0] = true;
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();
    for (ll v : ans_adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        s.push_back(v);
      }
    }
  }

  fore(i, 0, n) {
    if (!vis[i]) {
      return false;
    }
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m, D;
  cin >> n >> m >> D;
  vii edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  optional<vii> ans = solve(n, D, edges);
  if (ans) {
    cout << "YES\n";
    for (auto [u, v] : *ans) {
      cout << u + 1 << ' ' << v + 1 << '\n';
    }
  } else {
    cout << "NO\n";
  }

/*   fore(_, 0, 1000) {
    ll n = rand() % 5 + 2;
    ll D = rand() % (n - 1) + 1;
    ll m = rand() % (n * (n + 1) / 2);
    set<ii> edges;
    fore(_, 0, m) {
      ll u = rand() % n, v = rand() % n;
      if (u != v) {
        edges.insert(minmax(u, v));
      }
    }

    vii ed(ALL(edges));

    optional<vii> ans = solve(n, D, ed);

    if (ans) {
      bool b = check(n, D, ed, *ans);
      if (!b) {
        cerr << n << ' ' << ed.size() << ' ' << D << '\n';
        for (auto [u, v] : ed) {
          cerr << u + 1 << ' ' << v + 1 << '\n';
        }
        cerr << "ans:\n";
        for (auto [u, v] : *ans) {
          cout << u + 1 << ' ' << v + 1 << '\n';
        }
        return 1;
      }
    }

  } */


}