#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

vii eulerWalk(vector<vector<ii>>& gr, ll nedges, ll src = 0) {
  ll n = SZ(gr);
  vi D(n), its(n), eu(nedges);
  vii ret, s = {{src, -1}};
  D[src]++;
  while (!s.empty()) {
    auto [x, e] = s.back();
    ll &it = its[x], end = SZ(gr[x]);
    if (it == end) {
      ret.pb({x, e});
      s.pop_back();
      continue;
    }
    ll y;
    tie(y, e) = gr[x][it++];
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1; s.pb({y, e});
    }
  }
  for (ll x : D) if (x < 0 || SZ(ret) != nedges+1) return {};
  return {ret.rbegin(), ret.rend()};
}


bool can(ll m, const vii& edges) {
  ll n = edges.size();

  ll new_n = 1 << m;
  vii new_edges(n);
  fore(i, 0, n) {
    auto [u, v] = edges[i];
    new_edges[i] = {u & (new_n - 1), v & (new_n - 1)};
  }

  vector<vi> adj(new_n);
  for (auto [u, v] : new_edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<bool> vis(new_n, false);
  vi s = {new_edges[0].first};
  vis[new_edges[0].first] = true;
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();

    for (ll v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        s.push_back(v);
      }
    }
  }

  fore(i, 0, new_n) {
    if (adj[i].size() > 0 && !vis[i]) {
      return false;
    }
  }

  vi deg(new_n);
  for (auto [u, v] : new_edges) {
    deg[u]++, deg[v]++;
  }

  fore(i, 0, new_n) {
    if (deg[i] % 2 != 0) {
      return false;
    }
  }

  return true;
}

vi construct(ll m, const vii& edges) {
  ll n = edges.size();

  map<ll, ll> renames;
  vii new_edges(n);
  fore(i, 0, n) {
    auto [u, v] = edges[i];
    ll u0 = u & ((1 << m) - 1), v0 = v & ((1 << m) - 1);
    if (!renames.count(u0)) {
      renames[u0] = renames.size();
    }
    if (!renames.count(v0)) {
      renames[v0] = renames.size();
    }

    new_edges[i] = {renames[u0], renames[v0]};
  }
  ll new_n = new_edges.size();

  vector<vii> adj(new_n);
  fore(i, 0, n) {
    auto [u, v] = new_edges[i];
    adj[u].push_back({v, i}), adj[v].push_back({u, i});
  }

  vi ans;

  vii walk = eulerWalk(adj, n);

  for (auto [u, e] : walk) {
    if (e != -1) {
      if (new_edges[e].first == u) {
        ans.push_back(2 * e + 1);
        ans.push_back(2 * e);
      } else {
        ans.push_back(2 * e);
        ans.push_back(2 * e + 1);
      }
    }
  }

  return ans;
}


pair<ll, vi> solve(const vii& edges) {
  ll n = edges.size();

  ll l = 0, r = 21;
  while (l + 1 < r) {
    ll m = (l + r) / 2;
    bool c = can(m, edges);
    if (c) {
      l = m;
    } else {
      r = m;
    }
  }

  vi ans = construct(l, edges);
  return {l, ans};
}



int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vii edges(n);
  for (auto& [a, b] : edges) {
    cin >> a >> b;
  }

  auto [l, ans] = solve(edges);
  cout << l << '\n';
  for (ll a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';
}