// https://atcoder.jp/contests/dp/tasks/dp_g

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

class Graph {
public:
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  Graph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<Vertex>>(n);
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
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

struct Problem {
  Graph g;

  vector<optional<ull>> dp;

  Problem(Graph g) : g(g) {
    dp = vector<optional<ull>>(g.n);
  }

  ull solveFor(Vertex v) {
    if (dp[v].has_value()) {
      return dp[v].value();
    }

    ull ans = 0;
    for (Vertex u : g.adj[v]) {
      ans = max(ans, solveFor(u) + 1);
    }

    dp[v] = ans;
    return ans;
  }
};

ull solve(Graph g) {
  Problem p(g);
  ull ans = 0;
  fore(v, 0, g.n) {
    ans = max(ans, p.solveFor(v));
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto [n, edges] = readGraph();

  Graph g(n, edges);

  cout << solve(g) << '\n';

  return EXIT_SUCCESS;
}
