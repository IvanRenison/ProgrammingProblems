// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ull Weight;
typedef tuple<Vertex, Vertex, Weight> Edge;

/*
Crear 4 grafos,
G, G_min, G_max, G_minmax

De G se puede ir a G_min y G_max por los mismos lados que dentro de G, pero con peso doble o 0
De G_min y G_max se puede ir a G_minmax, por los mismos lados que dentro de G pero con 0 o doble
*/

struct WeightedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<pair<Vertex, Weight>>> adj;

  WeightedGraph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<pair<Vertex, Weight>>>(n);
    for (auto [u, v, w] : edges) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
  }
};

pair<ull, vector<Edge>> readWeightedGraph() {
  ull n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v, w;
    cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }

  return {n, edges};
}

typedef ull State; //0b00 = G, 0b01 = G_max, 0b10 = G_min, 0b11 = G_maxmin

/* Modified version of Dijkstra for the problem */
typedef ull Distance;
vector<Distance> mDijkstra(WeightedGraph g, Vertex s) {
  array<vector<bool>, 4> visited = {
      vector<bool>(g.n, false), vector<bool>(g.n, false),
      vector<bool>(g.n, false), vector<bool>(g.n, false)};
  array<vector<Distance>, 4> dist = {
      vector<Distance>(g.n), vector<Distance>(g.n), vector<Distance>(g.n),
      vector<Distance>(g.n)};
  dist[0][s] = 0;
  visited[0][s] = 0;

  priority_queue<
      pair<Distance, pair<Vertex, State>>,
      vector<pair<Distance, pair<Vertex, State>>>,
      greater<pair<Distance, pair<Vertex, State>>>>
      pq;

  pq.push({0, {s, 0}});

  while (!pq.empty()) {
    auto [d, v_st] = pq.top();
    auto [v, st] = v_st;
    pq.pop();
    if (visited[st][v]) {
      continue;
    }

    visited[st][v] = true;
    dist[st][v] = d;

    for (auto [u, w] : g.adj[v]) {
      if (!visited[st][u]) {
        pq.push({d + w, {u, st}});
      }
      if ((st & 1ULL) == 0ULL && !visited[st | 1ULL][u]) {
        pq.push({d, {u, st | 1ULL}});
      }
      if ((st & 2ULL) == 0 && !visited[st | 2ULL][u]) {
        pq.push({d + 2 * w, {u, st | 2ULL}});
      }
    }
  }

  vector<ull> ans(g.n);

  fore(i, 0, g.n) {
    ans[i] = min(dist[0][i], dist[3][i]);
  }

  return ans;
}

vector<ull> solve(WeightedGraph g) {
  vector<ull> ans = mDijkstra(g, 0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto [n, edges] = readWeightedGraph();
  WeightedGraph g(n, edges);

  vector<ull> ans = solve(g);

  fore(i, 1, n) {
    cout << ans[i] << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}