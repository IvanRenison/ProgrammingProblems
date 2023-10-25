// https://atcoder.jp/contests/arc164/tasks/arc164_b

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

bool solve(Graph& g, vector<bool>& colors) {
  vector<bool> global_visited(g.n, false), local_visited(g.n, false);

  function<bool(Vertex)> dfs = [&](Vertex u) {
    global_visited[u] = true, local_visited[u] = true;

    for (auto v : g.adj[u]) {
      if (!local_visited[v]) {
        if (colors[u] != colors[v]) {
          if (dfs(v)) {
            return true;
          }
        }
      } else if (colors[u] == colors[v]) {
        return true;
      }
    }

    return false;
  };

  fore(u, 0, g.n) {
    if (!global_visited[u]) {
      local_visited.assign(g.n, false);
      if (dfs(u)) {
        return true;
      }
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  auto [n, edges] = readGraph();

  Graph g(n, edges);

  vector<bool> colors(n);
  fore(i, 0, n) {
    ull c;
    cin >> c;
    colors[i] = c == 1;
  }

  if (solve(g, colors)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
