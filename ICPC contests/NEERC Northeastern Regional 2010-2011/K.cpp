// https://codeforces.com/gym/101309
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef long double ld;

pair<ll, vi> solve(ll n, const vii& edges) {
  vector<vi> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  ll k = 0;
  fore(i, 0, n) {
    k = max(k, (ll)adj[i].size());
  }

  bool all_eq_k = true;
  fore(i, 0, n) {
    if (k != adj[i].size()) {
      all_eq_k = false;
    }
  }
  assert(!(n % 2 == 1 && k % 2 == 1 && all_eq_k));

  if (k % 2 == 0) {
    k++;
  }

  vi ord__(n);
  iota(ALL(ord__), 0);

  sort(ALL(ord__), [&](ll u, ll v) {
    return adj[u].size() > adj[v].size() || (adj[u].size() == adj[v].size() && u < v);
  });

  vi ord;
  vector<bool> vis(n, false);
  function<void(ll)> dfs = [&](ll u) {
    vis[u] = true;
    for (ll v : adj[u]) {
      if (!vis[v]) {
        dfs(v);
      }
    }
    ord.push_back(u);
  };
  dfs(ord__.back());


  vi cs(n, -1);
  for (ll u : ord) {
    ll t = adj[u].size();
    vector<bool> used(t + 1, false);
    for (ll v : adj[u]) {
      if (cs[v] != -1 && cs[v] <= t) {
        used[cs[v]] = true;
      }
    }

    ll c = 0;
    while (used[c]) {
      c++;
      //assert(c <= t);
    }

    cs[u] = c;
  }

  return {k, cs};
}

bool check(ll n, const vii& edges, ll k, const vi& cs) {
  fore(i, 0, n) {
    if (cs[i] >= k) {
      return false;
    }
  }

  for (auto [u, v] : edges) {
    if (cs[u] == cs[v]) {
      return false;
    }
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("kgraph.in", "r", stdin);
  freopen("kgraph.out", "w", stdout);
#endif

#ifndef TEST
  ll n, m;
  cin >> n >> m;
  vii edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  auto [k, cs] = solve(n, edges);
  //assert(check(n, edges, k, cs));
  cout << k << '\n';
  for (ll c : cs) {
    cout << c + 1 << '\n';
  }
#else
  fore(_, 0, 10000) {
    ll n = (rand() % 5) * 2 + 3;
    ll m = rand() % 20;
    set<ii> edges;
    fore(i, 0, n - 1) {
      edges.insert({i, i + 1});
    }
    fore(_, 0, m) {
      ll u = rand() % n, v = rand() % n;
      if (u != v) {
        edges.insert(minmax(u, v));
      }
    }

    vii edges_(ALL(edges));

    auto [k, cs] = solve(n, edges_);

    cout << n << ' ' << edges_.size() << '\n';
    for (auto [u, v] : edges) {
      cout << u + 1 << ' ' << v + 1 << '\n';
    }
    cout << endl;

    assert(check(n, edges_, k, cs));
  }
#endif
}
