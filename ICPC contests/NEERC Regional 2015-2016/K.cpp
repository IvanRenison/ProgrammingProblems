// https://codeforces.com/gym/100851
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
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef long double ld;

optional<vi> solve(ll n, const vii& edges) {
  ll m = edges.size();
  ll d = m - n;

  vector<vi> adj_back(n);
  vector<vector<pair<ll, vi>>> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back({v, {}});
    adj_back[v].push_back(u);
  }

  fore(u, 0, n) {
    if (adj[u].empty() || adj_back[u].empty()) {
      return {};
    }
  }

  {
    vector<bool> vis(n, false);
    ll back_edges_count = 0;

    function<void(ll)> dfs = [&](ll u) {
      for (auto& [v, _] : adj[u]) {
        if (vis[v]) {
          back_edges_count++;
        } else {
          vis[v] = true;
          dfs(v);
        }
      }
    };

    vis[0] = true;
    dfs(0);

    if (back_edges_count > d + 1) {
      return {};
    }
  }

  fore(u, 1, n) {
    if (adj[u].size() == 1 && adj_back[u].size() == 1) {
      ll v = adj_back[u][0];
      auto& [w, comp_uw] = adj[u][0];
      if (v == w) continue;

      ll i = 0;
      while (adj[v][i].first != u) i++;

      adj[v][i].second.push_back(u);
      adj[v][i].second.insert(adj[v][i].second.end(), ALL(comp_uw));

      adj[v][i].first = w;

      ll j = 0;
      while (adj_back[w][j] != u) j++;

      adj_back[w][j] = v;

      adj[u].clear();
    }
  }

  ll count = 0;
  ll comp_count = 0;
  fore(u, 0, n) {
    if (!adj[u].empty()) {
      count++;
    }
    for (auto& [v, comp] : adj[u]) {
      comp_count += !comp.empty();
    }
  }

  vi ans;
  vector<bool> vis(n, false);

  function<bool(ll u, ll, ll)> backtrack = [&](ll u, ll s, ll t) -> bool {
    assert(!vis[u]);

    vis[u] = true;
    for (auto& [v, comp] : adj[u]) {
      if (v == 0 && s == count && t + !comp.empty() == comp_count) {
        ans.push_back(v);
        ans.insert(ans.end(), comp.rbegin(), comp.rend());
        ans.push_back(u);
        return true;
      }
      if (!vis[v] && backtrack(v, s + 1, t + !comp.empty())) {
        ans.insert(ans.end(), comp.rbegin(), comp.rend());
        ans.push_back(u);
        return true;
      }
    }

    vis[u] = false;

    return false;
  };

  if (!backtrack(0, 1, 0)) {
    return {};
  }

  reverse(ALL(ans));

  return ans;
}

bool check(ll n, vii edges, vi ans) {
  if (ans.size() != n + 1) {
    return false;
  }

  set<ll> ans_s(ALL(ans));
  if (ans_s.size() != n) {
    return false;
  }

  set<ii> edges_s(ALL(edges));

  fore(i, 0, n) {
    ll u = ans[i], v = ans[i + 1];
    if (!edges_s.count({u, v})) {
      return false;
    }
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("king.in", "r",stdin);
  freopen("king.out","w",stdout);
#endif

#ifndef TEST
  ll n, m;
  cin >> n >> m;
  vii edges(m);
  for (auto& [a, b] : edges) {
    cin >> a >> b;
    a--, b--;
  }

  auto ans = solve(n, edges);
  if (!ans.has_value()) {
    cout << "There is no route, Karl!\n";
  } else {
    for (ll x : *ans) {
      cout << x + 1 << ' ';
    }
    cout << '\n';
  }
#else
  fore(_, 0, 100) {
    ll n = rand() % 7 + 2;
    ll m = rand() % (min(n * (n - 1), n + 5));
    set<ii> edges_s;
    while (edges_s.size() < m) {
      ll u = rand() % n, v = rand() % n;
      if (u != v) {
        edges_s.insert({u, v});
      }
    }

    vii edges(ALL(edges_s));
    random_shuffle(ALL(edges));

    auto ans = solve(n, edges);
    if (ans.has_value()) {
      if (!check(n, edges, *ans)) {
        cerr << n << ' ' << m << '\n';
        for (auto [u, v] : edges) {
          cout << u + 1 << ' ' << v + 1 << '\n';
        }
        return 1;
      }
    }
  }
#endif
}