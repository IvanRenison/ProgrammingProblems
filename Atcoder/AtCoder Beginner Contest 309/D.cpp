// https://atcoder.jp/contests/abc309/tasks/abc309_d

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

constexpr ull INF = ull(-1);
vector<ull> bfs(Graph& g, Vertex s) {
  vector<ull> dist(g.n, INF);
  dist[s] = 0;

  queue<Vertex> q;
  q.push(s);

  while (!q.empty()) {
    Vertex u = q.front();
    q.pop();

    for (Vertex v : g.adj[u]) {
      if (dist[v] == INF) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }

  return dist;
}

ull solve(Graph& g) {
  vector<ull> dist0 = bfs(g, 0);
  vector<ull> distN = bfs(g, g.n - 1);

  ull max_dist0 = 0, max_distN = 0;
  fore(i, 0, g.n) {
    if (dist0[i] != INF) {
      max_dist0 = max(max_dist0, dist0[i]);
    }
    if (distN[i] != INF) {
      max_distN = max(max_distN, distN[i]);
    }
  }

  return max_dist0 + max_distN + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N1, N2, M;
  cin >> N1 >> N2 >> M;

  vector<Edge> edges(M);
  fore(i, 0, M) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  Graph g(N1 + N2, edges);

  cout << solve(g) << '\n';

  return EXIT_SUCCESS;
}
