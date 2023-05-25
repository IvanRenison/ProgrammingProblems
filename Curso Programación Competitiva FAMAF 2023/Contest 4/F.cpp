// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

tuple<vector<ll>, vector<ll>, vector<pair<ll, ll>>> parse1() {
  ll n;

  cin >> n;

  vector<ll> ls(n), rs(n);

  fore(i, 0, n) {
    cin >> ls[i] >> rs[i];
  }

  vector<pair<ll, ll>> edges(n - 1);

  fore(i, 0, n - 1) {
    ll l, r;
    cin >> l >> r;
    edges[i] = {l - 1, r - 1};
  }

  return {ls, rs, edges};
}

typedef ll Vertex;
typedef pair<Vertex, Vertex> Edge;

struct Graph {
  ll n;
  ll m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;
  vector<Vertex> parents;

  void mark_parents(Vertex v) {
    for (Vertex u : adj[v]) {
      if (u != parents[v]) {
        parents[u] = v;
        mark_parents(u);
      }
    }
  }

  Graph(ll n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<Vertex>>(n);
    fore(i, 0, m) {
      auto [u, v] = edges[i];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    this->parents = vector<Vertex>(n);
    parents[0] = 0;
    mark_parents(0);
  }
};

enum Side { LEFT, RIGHT };

struct Problem {
  Graph g;
  vector<array<optional<ll>, 2>> dp;

  vector<array<ll, 2>> lrs;

  Problem(vector<ll> ls, vector<ll> rs, vector<Edge> edges)
      : g(ls.size(), edges), dp(ls.size()), lrs(ls.size()) {
    ll n = ls.size();
    fore(i, 0, n) {
      dp[i][LEFT] = {};
      dp[i][RIGHT] = {};
      lrs[i][LEFT] = ls[i];
      lrs[i][RIGHT] = rs[i];
    }
  }

  // solve for v starting from s
  ll solveFor(Vertex v, Side s) {
    if (dp[v][s].has_value()) {
      return dp[v][s].value();
    }

    ll ans = 0;
    for (Vertex u : g.adj[v]) {
      if (u != g.parents[v]) {
        ans +=
            max(solveFor(u, RIGHT) + abs(lrs[v][s] - lrs[u][RIGHT]),
                solveFor(u, LEFT) + abs(lrs[v][s] - lrs[u][LEFT]));
      }
    }

    dp[v][s] = ans;
    return ans;
  }
};

ll solve1(vector<ll> ls, vector<ll> rs, vector<Edge> edges) {
  Problem p(ls, rs, edges);

  return max(p.solveFor(0, LEFT), p.solveFor(0, RIGHT));
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll t;

  cin >> t;

  fore(i, 0, t) {
    auto [ls, rs, edges] = parse1();
    ll ans = solve1(ls, rs, edges);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
