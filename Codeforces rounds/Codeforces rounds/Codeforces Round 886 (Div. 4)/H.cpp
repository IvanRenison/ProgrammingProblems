// https://codeforces.com/contest/1850/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ll Weight;
typedef tuple<Vertex, Vertex, Weight> wEdge;

struct WeightedGraph {
  ull n;
  ull m;
  vector<wEdge> edges;
  vector<vector<pair<Vertex, Weight>>> adj;

  WeightedGraph(ull n, vector<wEdge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v, w] : edges) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, -w});
    }
  }
};

bool solve1(ull n, vector<tuple<ull, ull, ll>> abds) {
  map<pair<ull, ull>, ll> es;
  vector<tuple<ull, ull, ll>> edges;
  for (auto [a, b, d] : abds) {
    if (a > b) {
      swap(a, b);
      d = -d;
    }
    if (es.count({a, b})) {
      if (es[{a, b}] != d) {
        return false;
      }
    } else {
      es[{a, b}] = d;
      edges.push_back({a, b, d});
    }
  }

  WeightedGraph g(n, edges);

  vector<bool> visited(n, false), passed(n, false);
  vector<ll> sums(n);

  function<bool(Vertex, Vertex)> dfs = [&](Vertex u, Vertex p) {
    visited[u] = true;
    for (auto [v, w] : g.adj[u]) {
      if (v != p) {
        if (!visited[v]) {
          sums[v] = sums[u] + w;
          if (!dfs(v, u)) {
            return false;
          }
        } else if (!passed[v]) {
          if (sums[u] + w - sums[v] != 0) {
            return false;
          }
        }
      }
    }
    passed[u] = true;
    return true;
  };

  fore(u, 0, n) {
    if (!visited[u]) {
      sums[u] = 0;
      if (!dfs(u, u)) {
        return false;
      }
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vector<tuple<ull, ull, ll>> abds(m);
    for (auto& [a, b, d] : abds) {
      cin >> a >> b >> d;
      a--, b--;
    }

    if (solve1(n, abds)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
