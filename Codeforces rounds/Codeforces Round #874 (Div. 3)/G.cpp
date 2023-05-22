// https://codeforces.com/contest/1833/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

pair<ull, vector<Edge>> readGraph() {
  ull n;
  cin >> n;

  vector<Edge> edges(n - 1);
  fore(i, 0, n - 1) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  return {n, edges};
}

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<pair<Vertex, ull>>> adj;

  Graph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<pair<Vertex, ull>>>(n);
    fore(i, 0, m) {
      auto [u, v] = edges[i];
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    }
  }
};

struct Problem {
  Graph g;
  vector<bool> visited;
  vector<ull> ans;

  Problem(ull n, vector<Edge> edges) : g(n, edges), visited(n, false) {}

  // solve for vertex and return the amount of trailing vertexes (0, 1 or 2) if there is a solution
  optional<ull> solveFor(Vertex v) {
    visited[v] = true;
    array<ull, 3> ats = {0, 0, 0};

    for (auto [u, i] : g.adj[v]) {
      if (!visited[u]) {
        optional<ull> at_u = solveFor(u);
        if (!at_u.has_value()) {
          return {};
        }
        ats[at_u.value()]++;

        if (at_u.value() == 0) {
          ans.push_back(i);
        }
      }
    }

    if (ats[1] == 0) {
      if (ats[2] == 0) {
        return 2;
      } else if (ats[2] == 1) {
        return 1;
      } else if (ats[2] == 2) {
        return 0;
      } else {
        return {};
      }
    } else if (ats[1] == 1) {
      if (ats[2] == 0) {
        return 0;
      } else {
        return {};
      }
    } else {
      return {};
    }
  }
};

optional<vector<ull>> solve1(ull n, vector<Edge> edges) {
  Problem p(n, edges);

  optional<ull> at0 = p.solveFor(0);

  if (!at0.has_value() || at0.value() != 0) {
    return {};
  } else {
    return p.ans;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, edges] = readGraph();
    optional<vector<ull>> ans = solve1(n, edges);
    if (ans.has_value()) {
      cout << ans.value().size() << '\n';
      for (auto x : ans.value()) {
        cout << x + 1 << ' ';
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
