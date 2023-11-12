// https://codeforces.com/gym/103960/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef pair<Vertex, Vertex> Edge;

struct DirectedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj_fordward;
  vector<vector<Vertex>> adj_backward;

  DirectedGraph(ull n, vector<Edge> edges) {
    this->n = n;
    this->m = edges.size();
    this->edges = edges;
    this->adj_fordward = vector<vector<Vertex>>(n);
    this->adj_backward = vector<vector<Vertex>>(n);
    for (auto [u, v] : edges) {
      adj_fordward[u].push_back(v);
      adj_backward[v].push_back(u);
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

ull solve(DirectedGraph& g) {

  vector<ull> cc(g.n);
  ull ncc = 0;

  scc(g.adj_fordward, [&ncc, &cc](vector<Vertex>& v) {
    for (ull u : v) {
      cc[u] = ncc;
    }
    ncc++;
  });

  if (ncc == 1) {
    return 0;
  }

  vector<set<ull>> adj_forward(ncc);
  vector<set<ull>> adj_backward(ncc);
  for (auto [u, v] : g.edges) {
    if (cc[u] != cc[v]) {
      adj_forward[cc[u]].insert(cc[v]);
      adj_backward[cc[v]].insert(cc[u]);
    }
  }

  ull starts = 0;
  fore(u, 0, ncc) {
    if (adj_backward[u].empty()) {
      starts++;
    }
  }

  ull ends = 0;
  fore(u, 0, ncc) {
    if (adj_forward[u].empty()) {
      ends++;
    }
  }

  return max(starts, ends);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  auto [n, edges] = readGraph();
  DirectedGraph g(n, edges);

  cout << solve(g) << '\n';

  return EXIT_SUCCESS;
}
