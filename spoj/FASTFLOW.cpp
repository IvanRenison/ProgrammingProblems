// https://www.spoj.com/problems/FASTFLOW/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ull Edge;
typedef ull Capacity;
typedef ll Value;

class UndirectedNetwork {
public:
  ull n;
  ull m;

  Vertex s;
  Vertex t;

  vector<pair<Vertex, Vertex>> edges;
  vector<Capacity> cs;

  vector<vector<pair<Vertex, Edge>>> adj;

  // Constructor
  UndirectedNetwork(
      ull n, ull s, ull t, vector<pair<ull, ull>> edges, vector<ull> cs
  ) {
    this->n = n;
    this->m = edges.size();

    this->s = s;
    this->t = t;

    this->edges = edges;
    this->cs = cs;

    this->adj = vector<vector<pair<Vertex, Edge>>>(n);

    fore(i, 0, m) {
      Vertex u = edges[i].first;
      Vertex v = edges[i].second;

      this->adj[u].push_back({v, i});
      this->adj[v].push_back({u, i});
    }
  }

  ll flowValue(vector<Value> flow) {
    ll ans = 0;

    for (auto [_, e] : adj[s]) {
      ans += flow[e];
    }

    return ans;
  }

  bool isFlowEdgeTo(vector<Value> flow, Edge e, Vertex v) {
    if (v == edges[e].second) {
      // Side u v
      if (flow[e] >= 0 && flow[e] < cs[e]) {
        // Forward
        return true;
      } else if (flow[e] < 0 && -flow[e] < cs[e]) {
        // Backward
        return true;
      }
    } else {
      // Side v u
      if (flow[e] > 0 && flow[e] < cs[e]) {
        // Backward
        return true;
      } else if (flow[e] <= 0 && -flow[e] < cs[e]) {
        // Forward
        return true;
      }
    }

    return false;
  }

  optional<vector<Edge>> find_f_path(vector<Value> flow) {

    vector<bool> visited(n, false);
    vector<optional<Edge>> parent(n);

    vector<Vertex> queue = {s};
    ull queue_position = 0;

    while (queue_position < queue.size()) {
      Vertex u = queue[queue_position];

      for (auto [v, e] : adj[u]) {
        if (v == t) {
          vector<Edge> path;

          while (v != s) {
            Edge e = parent[v].value();
            path.push_back(e);
            v = edges[e].first;
          }

          reverse(path.begin(), path.end());

          return path;
        }

        if (u != v && !visited[v]) {
          if (isFlowEdgeTo(flow, e, v)) {
            visited[v] = true;
            parent[v] = e;
            queue.push_back(v);
          }
        }
      }

      queue_position++;
    }

    return nullopt;
  }
};

vector<Value> EdmondsKarp(UndirectedNetwork N) {
  vector<Value> flow(N.m, 0);

  // TODO
}

ull solve(ull n, vector<pair<ull, ull>> edges, vector<ull> cs) {
  UndirectedNetwork N(n, 0, n - 1, edges, cs);

  vector<Value> maxFlow = EdmondsKarp(N);

  return (ull)N.flowValue(maxFlow);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;

  cin >> n >> m;

  vector<pair<ull, ull>> edges(m);
  vector<ull> cs(m);

  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v >> cs[i];

    edges[i] = {u - 1, v - 1};
  }

  cout << solve(n, edges, cs) << "\n";

  return EXIT_SUCCESS;
}
