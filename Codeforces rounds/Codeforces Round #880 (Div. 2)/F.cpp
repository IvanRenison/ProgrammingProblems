// https://codeforces.com/contest/1836/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define MAXN 100001

/* For each number until N get the smallest prime that divides it */
vector<ull> smallest_prime_factors(MAXN);
void sieve(void) {
  for (ull i = 0; i < MAXN; i++) {
    smallest_prime_factors[i] = i;
  }

  for (ull i = 2; i * i < MAXN; i++) {
    if (smallest_prime_factors[i] == i) {
      for (ull j = i * i; j < MAXN; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }
}

/* smallest_prime_factors has to have the smallest prime factor of each number until x */
vector<pair<ull, ull>> prime_factors(ull x) {
  if (x == 1) {
    return {};
  } else {
    vector<pair<ull, ull>> factors = {{smallest_prime_factors[x], 1}};
    x = ull(x / smallest_prime_factors[x]);
    while (x != 1) {
      if (smallest_prime_factors[x] != factors.back().first) {
        factors.push_back({smallest_prime_factors[x], 0});
      }
      factors.back().second++;
      x = ull(x / smallest_prime_factors[x]);
    }
    return factors;
  }
}

typedef ull Vertex;
typedef pair<Vertex, Vertex> Edge;

struct DirectedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;

  DirectedGraph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj = vector<vector<Vertex>>(n);
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
    }
  }
};

/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
vector<ull> val, comp, z, cont;
ull Time, ncomps;
template <class G, class F> ull dfs(ull j, G& g, F& f) {
  ull low = val[j] = ++Time, x;
  z.push_back(j);
  for (auto e : g[j])
    if (comp[e] == ull(-1))
      low = min(low, val[e] ?: dfs(e, g, f));

  if (low == val[j]) {
    do {
      x = z.back();
      z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    f(cont);
    cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template <class G, class F> void scc(G& g, F f) {
  ull n = g.size();
  val.assign(n, 0);
  comp.assign(n, ull(-1));
  Time = ncomps = 0;
  fore(i, 0, n) if (comp[i] == ull(-1)) dfs(i, g, f);
}

/* Find the depth of some cicle in g, assuming that the graph is strongly connected */
ull cicle_depth(const DirectedGraph& g) {
  vector<ull> depth(g.n, 0);

  vector<Vertex> s = {0};
  while (!s.empty()) {
    Vertex v = s.back();
    s.pop_back();

    for (auto u : g.adj[v]) {
      if (depth[u] == 0) {
        depth[u] = depth[v] + 1;

        if (u == 0) {
          return depth[u];
        }

        s.push_back(u);
      }
    }
  }

  return 1;
}

/* Check if d is a divisor of the lengths of all cicles,
   assuming that the graph is strongly connected.
   If it is return the coloring */
optional<vector<ull>> check_cicles_divisor(const DirectedGraph& g, ull d) {
  static constexpr ull NOCOLOR = ull(-1);

  vector<ull> colors(g.n, NOCOLOR);

  vector<Vertex> s = {0};
  colors[0] = 0;

  while (!s.empty()) {
    Vertex v = s.back();
    s.pop_back();

    for (auto u : g.adj[v]) {
      if (colors[u] == NOCOLOR) {
        colors[u] = (colors[v] + 1) % d;
        s.push_back(u);
      } else if (colors[u] != (colors[v] + 1) % d) {
        return {};
      }
    }
  }

  return colors;
}

// Solve assuming that the graph is strongly connected
ull solve_scc(const DirectedGraph& g, ull k) {
  if (g.n == 1) {
    return 0;
  }

  ull d = cicle_depth(g);
  vector<pair<ull, ull>> factors = prime_factors(d);
  ull total_gcd = 1;

  for (auto [p, e] : factors) {
    for (ull i = 1, f = p; i <= e; i++, f *= p) {
      if (check_cicles_divisor(g, f).has_value()) {
        total_gcd *= p;
      }
    }
  }

  vector<ull> coloring = check_cicles_divisor(g, total_gcd).value();
  vector<ull> colors_amounts(total_gcd, 0);
  for (ull c : coloring) {
    colors_amounts[c]++;
  }

  ull ans = 0;
  if (k % total_gcd == 0) {
    for (ull a : colors_amounts) {
      ans += a + a * (a - 1) / 2;
    }
  }
  if (total_gcd % 2 == 0 && k % total_gcd == total_gcd / 2) {
    fore(c, 0, total_gcd / 2) {
      ans += colors_amounts[c] * colors_amounts[c + total_gcd / 2];
    }
  }

  return ans;
}

ull solve(const DirectedGraph& g, ull k) {
  vector<ull> cc(g.n);
  ull ncc = 0;

  scc(g.adj, [&cc, &ncc](vector<Vertex>& vs) {
    for (auto v : vs) {
      cc[v] = ncc;
    }
    ncc++;
  });

  vector<vector<Edge>> g_cc(ncc);
  for (auto [u, v] : g.edges) {
    if (cc[u] == cc[v]) {
      g_cc[cc[u]].push_back({u, v});
    }
  }

  ull ans = 0;
  fore(i, 0, ncc) {
    if (g_cc[i].size() > 0) {
      // Compress the names of the vertex of the i-th component
      map<ull, ull> names;
      ull n = 0;

      for (auto [u, v] : g_cc[i]) {
        if (names.find(u) == names.end()) {
          names[u] = n, n++;
        }
        if (names.find(v) == names.end()) {
          names[v] = n, n++;
        }
      }

      vector<Edge> edges;
      for (auto [u, v] : g_cc[i]) {
        edges.push_back({names[u], names[v]});
      }

      DirectedGraph g_cc_i(n, edges);

      // Add this ans to ans
      ans += solve_scc(g_cc_i, k);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  sieve();

  ull n, m, k;
  cin >> n >> m >> k;
  vector<Edge> edges(m);
  fore(i, 0, m) {
    Vertex u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  DirectedGraph g(n, edges);

  cout << solve(g, k) << '\n';

  return EXIT_SUCCESS;
}
