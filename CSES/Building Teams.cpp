// https://cses.fi/problemset/task/1668

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
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

pair<ull, vector<Edge>> readGraph() {
  ull n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  return {n, edges};
}

optional<vector<bool>> solve(Graph& g) {
  vector<bool> visited(g.n, false);
  vector<bool> ans(g.n);

  fore(i, 0, g.n) {
    if (!visited[i]) {
      vector<Vertex> s = {i};
      visited[i] = true;
      while (!s.empty()) {
        Vertex v = s.back();
        s.pop_back();

        for (Vertex u : g.adj[v]) {
          if (!visited[u]) {
            visited[u] = true;
            ans[u] = !ans[v];
            s.push_back(u);
          } else if (ans[u] == ans[v]) {
            return {};
          }
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  auto [n, edges] = readGraph();

  Graph g(n, edges);

  optional<vector<bool>> ans = solve(g);

  if (ans.has_value()) {
    for (bool b : ans.value()) {
      if (b) {
        cout << "1 ";
      } else {
        cout << "2 ";
      }
    }
    cout << '\n';
  } else {
    cout << "IMPOSSIBLE\n";
  }

  return EXIT_SUCCESS;
}
