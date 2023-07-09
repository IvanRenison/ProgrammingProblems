// https://codeforces.com/group/4zVk9dZl6Q/contest/391067/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
#define fore(i, a, b) for (uint i = a; i < b; i++)

vector<int> parse1(void) {
  uint n;
  cin >> n;

  vector<int> as(n);
  for (int& a : as) {
    cin >> a;
  }

  return as;
}

typedef uint Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct DirectedGraph {
  uint n;
  uint m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  DirectedGraph(uint n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
    }
  }
};

/*
Pasar restando el i

Pasa a ser encontrar un subset cuya suma sea igual a la suma de sus índices

Hacer un grafo con lados (b[i], i) y buscar un ciclo ahí


*/

struct findCicle {
  DirectedGraph g;
  vector<bool> visited, left;
  vector<uint> parent;

  findCicle(const DirectedGraph& g) : g(g), visited(g.n, false), left(g.n, false), parent(g.n, -1) {}

  /* Return start and end of cicle */
  optional<pair<uint, uint>> dfs(uint v) {
    visited[v] = true;
    for (auto u : g.adj[v]) {
      if (!visited[u]) {
        parent[u] = v;
        auto rec = dfs(u);
        if (rec.has_value()) {
          return rec;
        }
      } else if (!left[u]) {
        return {{u, v}};
      }
    }

    left[v] = true;
    return {};
  }

  optional<vector<Vertex>> find() {
    fore(u, 0, g.n) {
      if(!visited[u]) {
        auto d = dfs(u);
        if (d.has_value()) {
          auto [start, end] = d.value();
          vector<Vertex> cicle;
          for (auto v = end; v != start; v = parent[v]) {
            cicle.push_back(v);
          }
          cicle.push_back(start);
          return cicle;
        }
      }
    }

    return {};
  }
};

vector<uint> solve1(vector<int>& as) {
  uint n = as.size();

  fore(i, 0, n) {
    as[i] = (uint)abs(as[i] - (int)i);
  }

  vector<Edge> edges(n);
  fore(i, 0, n) {
    edges[i] = {as[i], i};
  }

  DirectedGraph g(n, edges);

  auto cicle = findCicle(g).find();

  return *cicle;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  uint t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans.size() << '\n';
    for (auto a : ans) {
      cout << a + 1 << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
