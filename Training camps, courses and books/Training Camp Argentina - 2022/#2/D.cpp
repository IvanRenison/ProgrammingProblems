// https://codeforces.com/group/4zVk9dZl6Q/contest/390678/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ull;
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

constexpr ull INF = (1 << 28);
vector<ull> distances_from(const Graph& g, ull s) {
  vector<ull> dist(g.n, INF);
  dist[s] = 0;

  queue<ull> q;
  q.push(s);
  while (!q.empty()) {
    ull u = q.front();
    q.pop();
    for (ull v : g.adj[u]) {
      if (dist[v] == INF) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }

  return dist;
}

vector<vector<ull>> distances(const Graph& g) {
  vector<vector<ull>> dists(g.n);
  fore(u, 0, g.n) {
    dists[u] = distances_from(g, u);
  }
  return dists;
}

/* Find the minimum index for witch f is true or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

double calc_cost_x(ull x, ull k, ull common, ull sep) {
  ull common_complete = x / common;
  ull common_partial = x % common;
  double common_time =
      (double)(common - common_partial) / (common_complete + 1) +
      (double)common_partial / (common_complete + 2);
  double common_cost = 2 * common_time;

  ull sep_complete = (k - x) / sep;
  ull sep_partial = (k - x) % sep;
  double sep_time = (double)(sep - sep_partial) / (sep_complete + 1) +
                    (double)sep_partial / (sep_complete + 2);
  double sep_cost = sep_time;

  return common_cost + sep_cost;
}

double calc_cost(ull k, ull common, ull sep) {
  ull total = common + sep;

  if (total == 0) {
    return 0;
  }
  if (common == 0) {
    ull sep_complete = k / sep;
    ull sep_partial = k % sep;
    double sep_time = (double)(sep - sep_partial) / (sep_complete + 1) +
                      (double)sep_partial / (sep_complete + 2);
    return sep_time;
  }
  if (sep == 0) {
    ull common_complete = k / common;
    ull common_partial = k % common;
    double common_time =
        (double)(common - common_partial) / (common_complete + 1) +
        (double)common_partial / (common_complete + 2);
    return 2 * common_time;
  }

  auto f = [k, common, sep](ull x) {
    if (x == k) {
      return true;
    }
    double cost_x = calc_cost_x(x, k, common, sep);
    double cost_x1 = calc_cost_x(x + 1, k, common, sep);
    if (x == 0) {
      return cost_x <= cost_x1;
    }
    double cost_x_1 = calc_cost_x(x - 1, k, common, sep);
    return !(cost_x_1 >= cost_x && cost_x >= cost_x1);
  };

  ull x = binary_search(f, 0, k);

  return calc_cost_x(x, k, common, sep);
}

double solve(const Graph& g, ull k, ull s0, ull t0, ull s1, ull t1) {
  vector<vector<ull>> dists = distances(g);

  ull d0 = dists[s0][t0];
  ull d1 = dists[s1][t1];

  vector<ull> common_sep(g.m + 1, INF);

  fore(i, 0, g.n) {
    fore(j, 0, g.n) {
      if (i != j) {
        ull common = dists[i][j];
        if (common < INF) {
          ull sep0 = dists[s0][i] + dists[t0][j] + dists[s1][i] + dists[t1][j];
          ull sep1 = dists[s0][i] + dists[t0][j] + dists[s1][j] + dists[t1][i];
          if (sep0 < common_sep[common]) {
            common_sep[common] = sep0;
          }
          if (sep1 < common_sep[common]) {
            common_sep[common] = sep1;
          }
        }
      }
    }
  }

  double ans = calc_cost(k, 0, d0 + d1);

  fore(common, 1, g.m + 1) {
    if (common_sep[common] < INF) {
      double cost = calc_cost(k, common, common_sep[common]);
      ans = min(ans, cost);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m, k;
  cin >> n >> m >> k;
  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }
  ull s0, t0, s1, t1;
  cin >> s0 >> t0 >> s1 >> t1;
  s0--, t0--, s1--, t1--;

  Graph g(n, edges);

  cout << fixed << setprecision(12);
  cout << solve(g, k, s0, t0, s1, t1) << '\n';

  return EXIT_SUCCESS;
}
