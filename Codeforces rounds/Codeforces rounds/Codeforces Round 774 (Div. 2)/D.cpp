// https://codeforces.com/contest/1646/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  Graph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};

tuple<ull, ull, vector<ull>> solve(Graph g) {
  if (g.n == 2) {
    return {2, 2, {1, 1}};
  }
  vector<array<ull, 2>> dp(g.n, {0, 0});
  vector<array<bool, 2>> dp_valid(g.n, {false, false});

  function<ull(Vertex, bool, Vertex)> f = [&](Vertex u, bool s, Vertex p) {
    if (dp_valid[u][s]) {
      return dp[u][s];
    }
    if (s) {
      dp[u][s] = 1;
      for (auto v : g.adj[u]) {
        if (v != p) {
          dp[u][s] += f(v, false, u);
        }
      }
    } else {
      for (auto v : g.adj[u]) {
        if (v != p) {
          dp[u][s] += max(f(v, false, u), f(v, true, u));
        }
      }
    }
    dp_valid[u][s] = true;
    return dp[u][s];
  };

  f(0, true, 0), f(0, false, 0);

  vector<array<ull, 2>> sumw_dp(g.n, {0, 0});
  vector<array<bool, 2>> sumw_dp_valid(g.n, {false, false});

  function<ull(Vertex, bool, Vertex)> rec = [&](Vertex u, bool s, Vertex p) {
    if (sumw_dp_valid[u][s]) {
      return sumw_dp[u][s];
    }
    if (s) {
      sumw_dp[u][s] = g.adj[u].size();
      for (auto v : g.adj[u]) {
        if (v != p) {
          sumw_dp[u][s] += rec(v, false, u);
        }
      }
    } else {
      sumw_dp[u][s] = 1;
      for (auto v : g.adj[u]) {
        if (v != p) {
          if (dp[v][false] > dp[v][true]) {
            sumw_dp[u][s] += rec(v, false, u);
          } else if (dp[v][false] < dp[v][true]) {
            sumw_dp[u][s] += rec(v, true, u);
          } else {
            sumw_dp[u][s] += min(rec(v, false, u), rec(v, true, u));
          }
        }
      }
    }
    sumw_dp_valid[u][s] = true;
    return sumw_dp[u][s];
  };

  rec(0, false, 0), rec(0, true, 0);

  vector<bool> good(g.n, false);
  function<void(Vertex, bool, Vertex)> mark_goods = [&](Vertex u, bool c,
                                                        Vertex p) {
    if (c && (dp[u][true] > dp[u][false] ||
              (dp[u][true] == dp[u][false] &&
               sumw_dp[u][true] < sumw_dp[u][false]))) {
      good[u] = true;
      for (auto v : g.adj[u]) {
        if (v != p) {
          mark_goods(v, false, u);
        }
      }
    } else {
      good[u] = false;
      for (auto v : g.adj[u]) {
        if (v != p) {
          mark_goods(v, true, u);
        }
      }
    }
  };

  mark_goods(0, true, 0);

  vector<ull> ws(g.n);

  ull sum_ws = 0;
  fore(u, 0, g.n) {
    if (!good[u]) {
      ws[u] = 1;
      sum_ws += 1;
    }
  }

  ull count_good = 0;
  fore(u, 0, g.n) {
    if (good[u]) {
      count_good++;

      ull w = 0;
      for (ull v : g.adj[u]) {
        w += ws[v];
      }

      ws[u] = w;
      sum_ws += w;
    }
  }

  return {count_good, sum_ws, ws};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<Edge> edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  Graph g(n, edges);

  auto [v, w, ans] = solve(g);
  cout << v << ' ' << w << '\n';
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
