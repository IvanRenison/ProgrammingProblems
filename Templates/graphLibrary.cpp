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

/* WeightedGraph */

typedef ull Vertex;
typedef ull Weight;
typedef tuple<Vertex, Vertex, Weight> wEdge;

class WeightedGraph {
public:
  ull n;
  ull m;
  vector<wEdge> edges;
  vector<vector<pair<Vertex, Weight>>> adj;

  WeightedGraph(ull n, vector<wEdge> edges) {
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

pair<ull, vector<wEdge>> readWeightedGraph() {
  ull n, m;
  cin >> n >> m;

  vector<wEdge> edges(m);
  fore(i, 0, m) {
    ull u, v, w;
    cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }

  return {n, edges};
}

/* The return value is a vector of size n, where the i-th element is the
 * vertex that precedes the i-th vertex in the shortest path from s to i.
 * If there is no such path, the i-th element is nullopt.
 */
typedef ull Distance;
vector<optional<Vertex>> Dijkstra(WeightedGraph g, Vertex s) {
  vector<optional<Vertex>> prev(g.n);
  vector<Distance> dist(g.n, numeric_limits<Distance>::max());
  dist[s] = 0;

  priority_queue<
      tuple<Distance, Vertex, Vertex>, vector<tuple<Distance, Vertex, Vertex>>,
      greater<tuple<Distance, Vertex, Vertex>>>
      pq;

  pq.push({0, s, s});

  while (!pq.empty()) {
    auto [d, v, by] = pq.top();
    pq.pop();
    if (prev[v].has_value()) {
      continue;
    }

    prev[v] = by;
    dist[v] = d;

    for (auto [u, w] : g.adj[v]) {
      if (!prev[u].has_value()) {
        pq.push({d + w, u, v});
      }
    }
  }

  return prev;
  // If you want to return the distances instead of the previous vertices:
  // return dist;
}

optional<vector<ull>> solve(WeightedGraph g) {
  vector<optional<Vertex>> prev = Dijkstra(g, 0);

  if (!prev[g.n - 1].has_value()) {
    return {};
  }

  vector<ull> ans;
  Vertex v = g.n - 1;
  while (v != 0) {
    ans.push_back(v);
    v = prev[v].value();
  }
  ans.push_back(0);

  reverse(ans.begin(), ans.end());

  return ans;
}