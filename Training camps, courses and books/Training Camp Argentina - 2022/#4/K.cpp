// https://codeforces.com/group/4zVk9dZl6Q/contest/391067/problem/K

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
#define fore(i, a, b) for (uint i = a; i < b; i++)

/*

Cada número tiene a lo sumo 2 primos

Si hay un número que es un cuadrado lo devuelvo

Para cada número me quedo con la paridad de los exponentes de los 2 primos

Si hay dos números que quedan iguales los devuelvo


Ahora puedo plantear un grafo en el que:
    Los nodos representan primos y tienen peso 0 o 1, es 1 si hay un número
    que quedó en ese primo (si hubiera mas ya lo hubiéramos devuelto)
    Los lados son los entre los primos que forman un número que quedo

Ahora buscar un ciclo o un camino entre 1s de longitud mínima

*/

#define MAXA uint(1e6 + 1)

/* For each number until N get the smallest prime that divides it */
vector<uint> smallest_prime_factors(MAXA);
void sieve(void) {
  for (uint i = 0; i < MAXA; i++) {
    smallest_prime_factors[i] = i;
  }

  for (uint i = 2; i * i < MAXA; i++) {
    if (smallest_prime_factors[i] == i) {
      for (uint j = i * i; j < MAXA; j += i) {
        if (smallest_prime_factors[j] == j) {
          smallest_prime_factors[j] = i;
        }
      }
    }
  }
}

/* smallest_prime_factors has to have the smallest prime factor of each number until x */
vector<pair<uint, uint>> prime_factors(uint x) {
  if (x == 1) {
    return {};
  } else {
    vector<pair<uint, uint>> factors = {{smallest_prime_factors[x], 1}};
    x = uint(x / smallest_prime_factors[x]);
    while (x != 1) {
      if (smallest_prime_factors[x] != factors.back().first) {
        factors.push_back({smallest_prime_factors[x], 0});
      }
      factors.back().second++;
      x = uint(x / smallest_prime_factors[x]);
    }
    return factors;
  }
}

struct MGraph {
  uint n;
  vector<bool> marked;
  vector<vector<uint>> adj;
  vector<pair<uint, uint>> edges;

  MGraph(uint n, vector<bool>& marked, vector<pair<uint, uint>>& edges)
      : n(n), marked(marked), edges(edges), adj(n) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};

constexpr uint INF = (1 << 28);

// Find distance to closest marked node (or to itself)
uint closest(const MGraph& g, uint v, uint limit) {
  vector<bool> visited(g.n, false);

  vector<uint> next = {v};
  visited[v] = true;
  uint level = 0;

  while (!next.empty()) {
    level++;
    if (level == limit) {
      return limit;
    }
    vector<uint> new_next;
    for (uint u : next) {
      for (uint w : g.adj[u]) {
        if (!visited[w]) {
          visited[w] = true;
          if (g.marked[w]) {
            return level;
          }
          new_next.push_back(w);
        }
      }
    }
    next = new_next;
  }

  return INF;
}

// Find the shortest cicle in the graph using bfs from each node
uint shortestCicle(const MGraph& g, uint limit, const vector<uint>& primes) {
  uint ans = limit;

  fore(u, 0, g.n) {
    if (primes[u] >= 1001) {
      continue;
    }

    vector<pair<uint, uint>> next = {{u, u}};
    vector<uint> depth(g.n, INF);
    depth[u] = 0;

    for (uint level = 1; level < ans && !next.empty(); level++) {
      vector<pair<uint, uint>> new_next;
      for (auto [v, p] : next) {
        for (uint w : g.adj[v]) {
          if (depth[w] == INF) {
            depth[w] = level;
            new_next.push_back({w, v});
          } else if (w != p) {
            ans = min(ans, level + depth[w]);
          }
        }
      }
      next = new_next;
    }
  }

  return ans;
}

uint n;

uint solveMGraph(const MGraph& g, const vector<uint>& primes) {
  uint ans = INF;
  // path
  fore(u, 0, g.n) {
    if (g.marked[u]) {
      ans = min(ans, closest(g, u, ans) + 2);
    }
  }

  // cicles
  ans = shortestCicle(g, ans, primes);

  return ans;
}

optional<uint> solve(const vector<uint>& as) {
  n = as.size();

  map<uint, uint> primes;
  map<pair<uint, uint>, uint> two_primes;

  fore(i, 0, n) {
    uint a = as[i];
    if (a == 1) {
      return 1;
    }
    vector<pair<uint, uint>> facts_i = prime_factors(as[i]);

    if (facts_i.size() == 1) {
      auto [p, e] = facts_i[0];
      if (e % 2 == 0) {
        return 1;
      }

      primes[p]++;
    } else {
      // assert(facts_i.size() == 2);

      auto [p0, e0] = facts_i[0];
      auto [p1, e1] = facts_i[1];

      if (e0 % 2 == 0 && e1 % 2 == 0) {
        return 1;
      } else if (e0 % 2 == 0 && e1 % 2 == 1) {
        primes[p1]++;
      } else if (e0 % 2 == 1 && e1 % 2 == 0) {
        primes[p0]++;
      } else {
        two_primes[{p0, p1}]++;
      }
    }
  }

  for (auto [p, n] : primes) {
    if (n > 1) {
      return 2;
    }
  }
  for (auto [p, n] : two_primes) {
    if (n > 1) {
      return 2;
    }
  }

  uint g_n = 0;
  map<uint, uint> g_primes;
  vector<uint> inv_g_primes;
  vector<pair<uint, uint>> g_edges;
  for (auto [pp, _] : two_primes) {
    auto [p0, p1] = pp;
    auto p0_it = g_primes.find(p0);
    auto p1_it = g_primes.find(p1);
    uint p0_i, p1_i;

    if (p0_it == g_primes.end()) {
      g_primes[p0] = g_n;
      p0_i = g_n;
      inv_g_primes.push_back(p0);
      g_n++;
    } else {
      p0_i = p0_it->second;
    }

    if (p1_it == g_primes.end()) {
      g_primes[p1] = g_n;
      p1_i = g_n;
      inv_g_primes.push_back(p1);
      g_n++;
    } else {
      p1_i = p1_it->second;
    }

    g_edges.push_back({p0_i, p1_i});
  }

  vector<bool> marked(g_n, false);
  for (auto [p, _] : primes) {
    auto p_it = g_primes.find(p);
    if (p_it != g_primes.end()) {
      marked[p_it->second] = true;
    }
  }

  MGraph g(g_n, marked, g_edges);

  uint ans = solveMGraph(g, inv_g_primes);

  if (ans < INF) {
    return ans;
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  sieve();

  uint n;
  cin >> n;

  vector<uint> as(n);
  for (uint& a : as) {
    cin >> a;
  }

  optional<uint> ans = solve(as);
  if (ans.has_value()) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
