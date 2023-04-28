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
typedef vector<Value> Flow;
typedef vector<Edge> Path;

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

  ll flowValue(Flow flow) {
    ll ans = 0;

    for (auto [_, e] : adj[s]) {
      if (s == edges[e].first) {
        ans += flow[e];
      }
      else {
        ans -= flow[e];
      }
    }

    return ans;
  }

  bool isFlowValid(Flow flow) {
    fore(i, 0, m) {
      if (abs(flow[i]) > (ll)cs[i]) {
        return false;
      }
    }

    return true;
  }

  ull f_capacity_to(Flow flow, Edge e, Vertex v) {
    if (v == edges[e].second) {
      // Side u v
      return (ull)((ll)cs[e] - flow[e]);
    } else {
      // Side v u
      return flow[e] + (ll)cs[e];
    }
  }

  optional<Path> find_f_path(Flow flow) {

    vector<bool> visited(n, false);
    vector<optional<Edge>> parent(n);

    vector<Vertex> queue = {s};
    ull queue_position = 0;

    while (queue_position < queue.size()) {
      Vertex u = queue[queue_position];

      for (auto [v, e] : adj[u]) {


        if (!visited[v] && f_capacity_to(flow, e, v) > 0) {
          visited[v] = true;
          parent[v] = e;
          queue.push_back(v);

          if (v == t) {
            Path path;

            while (v != s) {
              assert(visited[v]);
              assert(parent[v].has_value());
              Edge e = parent[v].value();
              path.push_back(e);
              if (v == edges[e].first) {
                v = edges[e].second;
              } else {
                v = edges[e].first;
              }
            }
            reverse(path.begin(), path.end());

            return path;
          }
        }
      }

      queue_position++;
    }

    return nullopt;
  }

  ull path_capacity(Flow flow, Path path) {
    ull ans = ULLONG_MAX;

    Vertex last = s;
    for (Edge e : path) {
      Vertex next = edges[e].first == last ? edges[e].second : edges[e].first;
      ans = min(ans, f_capacity_to(flow, e, next));
      last = next;
    }

    return ans;
  }
};

Flow EdmondsKarp(UndirectedNetwork N) {
  Flow flow(N.m, 0);

  while (true) {
    optional<Path> path = N.find_f_path(flow);

    if (!path.has_value()) {
      return flow;
    }

    ull path_cap = N.path_capacity(flow, path.value());

    assert(path_cap > 0);

    Vertex last = N.s;
    for (Edge e : path.value()) {
      Vertex u = N.edges[e].first;
      Vertex v = N.edges[e].second;

      if (u == last) {
        // Side u v
        flow[e] += path_cap;
        last = v;
      } else {
        // Side v u
        flow[e] -= path_cap;
        last = u;
      }
    }

    if (!N.isFlowValid(flow)) {
      assert(false);
    }
  }
}

ull solve(ull n, vector<pair<ull, ull>> edges, vector<ull> cs) {
  UndirectedNetwork N(n, 0, n - 1, edges, cs);

  Flow maxFlow = EdmondsKarp(N);

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
