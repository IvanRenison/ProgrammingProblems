// https://cses.fi/problemset/task/1694

#ifndef NDEBUG
#define NDEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ull Edge;
typedef ull Capacity;
typedef ull Value;
typedef vector<Value> Flow;
typedef vector<Edge> Path;

struct DirectedNetwork {
  ull n;
  ull m;

  Vertex s;
  Vertex t;

  vector<pair<Vertex, Vertex>> edges;
  vector<Capacity> cs;

  vector<vector<pair<Vertex, Edge>>> adj_fordward;
  vector<vector<pair<Vertex, Edge>>> adj_backward;

  DirectedNetwork(
      ull n, ull s, ull t, const vector<pair<ull, ull>>& edges,
      const vector<ull>& cs
  ) {
    this->n = n;
    this->m = edges.size();

    this->s = s;
    this->t = t;

    this->edges = edges;
    this->cs = cs;

    this->adj_fordward = vector<vector<pair<Vertex, Edge>>>(n);
    this->adj_backward = vector<vector<pair<Vertex, Edge>>>(n);

    fore(i, 0, m) {
      Vertex u = edges[i].first;
      Vertex v = edges[i].second;

      this->adj_fordward[u].push_back({v, i});
      this->adj_backward[v].push_back({u, i});
    }
  }

  ull flowValue(const Flow& flow) const {
    ull ans = 0;

    for (auto [_, e] : adj_fordward[s]) {
      ans += flow[e];
    }
    for (auto [_, e] : adj_backward[s]) {
      ans -= flow[e];
    }

    return ans;
  }

  bool isFlowValid(Flow& flow) const {
    fore(i, 0, m) {
      if (flow[i] > cs[i]) {
        return false;
      }
    }

    return true;
  }

  ull f_capacity_to(const Flow& flow, Edge e, Vertex v) const {
    if (v == edges[e].second) {
      // Side u v (fordward)
      return cs[e] - flow[e];
    } else {
      // Side v u (backward)
      return flow[e];
    }
  }

  optional<Path> find_f_path(const Flow& flow) const {

    vector<bool> visited(n, false);
    vector<optional<Edge>> parent(n);

    vector<Vertex> queue = {s};
    ull queue_position = 0;

    while (queue_position < queue.size()) {
      Vertex u = queue[queue_position];

      for (auto [v, e] : adj_fordward[u]) {

        if (!visited[v] && f_capacity_to(flow, e, v) > 0) {
          visited[v] = true;
          parent[v] = e;
          queue.push_back(v);

          if (v == t) {
            goto end;
          }
        }
      }

      for (auto [v, e] : adj_backward[u]) {

        if (!visited[v] && f_capacity_to(flow, e, v) > 0) {
          visited[v] = true;
          parent[v] = e;
          queue.push_back(v);

          if (v == t) {
            goto end;
          }
        }
      }

      queue_position++;
    }

    return {};

  end:
    Path path;
    Vertex v = t;
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

  ull path_capacity(const Flow& flow, const Path& path) const {
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

Flow EdmondsKarp(const DirectedNetwork& N) {
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
        // Side u v (fordward)
        flow[e] += path_cap;
        last = v;
      } else {
        // Side v u (backward)
        flow[e] -= path_cap;
        last = u;
      }
    }
  }
}

ull solve(ull n, vector<pair<ull, ull>>& edges, vector<ull>& cs) {
  DirectedNetwork N(n, 0, n - 1, edges, cs);

  Flow maxFlow = EdmondsKarp(N);

  return (ull)N.flowValue(maxFlow);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

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
