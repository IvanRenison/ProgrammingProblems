// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef ull Weight;
typedef tuple<Vertex, Vertex, Weight> wEdge;

struct CompleteWeightedGraph {
  ull n;
  vector<vector<Weight>> adj;

  CompleteWeightedGraph(vector<vector<Weight>> adj) : n(adj.size()), adj(adj) {}
};

/* Find a minimum spanning tree of a complete graph in Ο(n²) starting from s
 * Return the edges of the result with out the weights */
vector<pair<Vertex, Vertex>> msp(CompleteWeightedGraph g, Vertex s) {

  // minimum cost of connecting each unconnected vertex and the edge to which connect with that cost
  vector<optional<pair<Weight, Vertex>>> connections(g.n);

  optional<Vertex> best_connection_index;

  fore(i, 0, g.n) {
    if (i != s) {
      Weight cost = g.adj[s][i];
      connections[i] = {cost, s};

      if (!best_connection_index.has_value() ||
          cost < connections[best_connection_index.value()]->first) {
        best_connection_index = i;
      }
    }
  }

  vector<pair<Vertex, Vertex>> result;

  while (best_connection_index.has_value()) {
    Vertex u = best_connection_index.value();
    auto [cost, v] = connections[u].value();
    result.push_back({u, v});

    connections[u] = {};
    best_connection_index = {};

    fore(i, 0, g.n) {
      if (connections[i].has_value()) {
        Weight new_cost = g.adj[u][i];

        if (!best_connection_index.has_value()) {
          best_connection_index = i;
        }

        if (new_cost < connections[i]->first) {
          connections[i] = {new_cost, u};
        }

        if (connections[i]->first <
            connections[best_connection_index.value()]->first) {
          best_connection_index = i;
        }
      }
    }
  }

  return result;
}

typedef ull City; // index of city
typedef ull Yen;  // amount of money

tuple<Yen, vector<City>, vector<pair<City, City>>>
solve(vector<pair<ll, ll>> xys, vector<ull> cs, vector<ull> ks) {
  ull n = xys.size();

  vector<vector<Weight>> adj(n + 1, vector<Weight>(n + 1));

  fore(j, 0, n) {
    adj[0][j + 1] = cs[j];
  }

  fore(i, 0, n) {
    adj[i + 1][0] = cs[i];
    fore(j, 0, n) {
      adj[i + 1][j + 1] =
          (ks[i] + ks[j]) * (abs(xys[i].first - xys[j].first) +
                             abs(xys[i].second - xys[j].second));
    }
  }

  CompleteWeightedGraph g(adj);

  vector<pair<Vertex, Vertex>> msp_edges = msp(g, 0);

  Yen cost = 0;
  vector<City> gens;
  vector<pair<City, City>> connections;

  for (auto [u, v] : msp_edges) {
    if (u == 0) {
      gens.push_back(v);
      cost += adj[0][v];
    } else if (v == 0) {
      gens.push_back(u);
      cost += adj[0][u];
    } else {
      connections.push_back({u, v});
      cost += adj[u][v];
    }
  }

  return {cost, gens, connections};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<pair<ll, ll>> xys(n);
  fore(i, 0, n) {
    cin >> xys[i].first >> xys[i].second;
  }

  vector<ull> cs(n);
  fore(i, 0, n) {
    cin >> cs[i];
  }

  vector<ull> ks(n);
  fore(i, 0, n) {
    cin >> ks[i];
  }

  auto [c, vs, abs] = solve(xys, cs, ks);

  cout << c << '\n';
  cout << vs.size() << '\n';
  for (ull v : vs) {
    cout << v << ' ';
  }
  cout << '\n';

  cout << abs.size() << '\n';
  for (auto [a, b] : abs) {
    cout << a << ' ' << b << '\n';
  }

  return EXIT_SUCCESS;
}
