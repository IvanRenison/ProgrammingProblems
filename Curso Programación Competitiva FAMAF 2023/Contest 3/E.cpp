// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/E

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

ull solve(Graph g) {

  vector<bool> visited(g.n);

  ull ans = 0;

  fore(i, 0, g.n) {
    if (visited[i]) {
      continue;
    }
    visited[i] = true;

    Vertex now = i;
    bool not_circle = false;

    if (g.adj[i].size() != 2) {
      not_circle = true;
    } else {
      Vertex next = g.adj[i][0];
      visited[next] = true;
      while (next != i) {
        Vertex old = now;
        now = next;
        if (g.adj[now].size() != 2) {
          not_circle = true;
          break;
        }
        if (g.adj[now][0] == old) {
          next = g.adj[now][1];
        } else {
          next = g.adj[now][0];
        }
        visited[next] = true;
      }
    }

    if (!not_circle) {
      ans++;
    } else {
      vector<Vertex> s = {now};
      while (s.size() > 0) {
        Vertex v = s.back();
        s.pop_back();
        for (Vertex w : g.adj[v]) {
          if (!visited[w]) {
            s.push_back(w);
            visited[w] = true;
          }
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto [n, edges] = readGraph();

  Graph g(n, edges);

  cout << solve(g) << "\n";

  return EXIT_SUCCESS;
}