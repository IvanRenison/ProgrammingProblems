// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ull Weight;
typedef tuple<Vertex, Vertex, Weight> wEdge;

struct WeightedGraph {
  ull n;
  ull m;
  vector<wEdge> edges;
  vector<vector<pair<Vertex, Weight>>> adj;

  WeightedGraph(ull n, vector<wEdge> edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    for (auto [u, v, w] : edges) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
  }
};

ull solve(vector<ull> as, vector<tuple<ull, ull, ull>> xyws) {
  ull n = as.size();

  vector<pair<ull, ull>> ais(n);
  fore(i, 0, n) {
    ais[i] = {as[i], i};
  }

  sort(as.begin(), as.end());

  sort(ais.begin(), ais.end());
  map<ull, ull> pos;
  fore(i, 0, n) {
    pos[ais[i].second] = i;
  }

  for (auto& [x, y, w] : xyws) {
    x = pos[x], y = pos[y];
  }

  WeightedGraph g(n, xyws);

  ull cost = 0;

  vector<bool> added(n, false);
  ull next_to_add = 0;

  priority_queue<pair<Weight, Vertex>, vector<pair<Weight, Vertex>>, greater<pair<Weight, Vertex>>> pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();

    if (!added[u]) {
      cost += w, added[u] = true;
      while (next_to_add < n && added[next_to_add]) {
        next_to_add++;
      }

      if (next_to_add < n) {
        pq.push({as[0] + as[next_to_add], next_to_add});
      }
      for (auto [v_, w_] : g.adj[u]) {
        if (!added[v_]) {
          pq.push({w_, v_});
        }
      }
    }
  }

  return cost;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  vector<tuple<ull, ull, ull>> xyws(m);
  fore(i, 0, m) {
    ull x, y, w;
    cin >> x >> y >> w;
    x--, y--;
    xyws[i] = {x, y, w};
  }

  cout << solve(as, xyws) << '\n';

  return EXIT_SUCCESS;
}
