// https://codeforces.com/group/4zVk9dZl6Q/contest/391067/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
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

optional<vector<bool>> bipartite(Graph& g) {
  vector<bool> visited(g.n, false);
  vector<bool> ans(g.n);

  fore(i, 0, g.n) {
    if (!visited[i]) {
      vector<Vertex> s = {i};
      visited[i] = true;
      while (!s.empty()) {
        Vertex v = s.back();
        s.pop_back();

        for (Vertex u : g.adj[v]) {
          if (!visited[u]) {
            visited[u] = true;
            ans[u] = !ans[v];
            s.push_back(u);
          } else if (ans[u] == ans[v]) {
            return {};
          }
        }
      }
    }
  }

  return ans;
}

/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
vector<ull> topoSort(const vector<vector<ull>>& gr) {
  vector<ull> indeg(gr.size()), ret;
  for (auto& li : gr)
    for (int x : li)
      indeg[x]++;
  queue<ull> q; // use priority_queue for lexic. largest ans.
  fore(i, 0, gr.size()) if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    ull i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (ull x : gr[i])
      if (--indeg[x] == 0)
        q.push(x);
  }
  return ret;
}

enum ORI { L, R };

optional<vector<pair<ORI, ull>>> solve(
    ull n, vector<pair<ull, ull>> destined, vector<pair<ull, ull>> irrelevants
) {
  vector<Edge> edges;
  for (auto [i, j] : destined) {
    edges.push_back({i, j});
  }
  for (auto [i, j] : irrelevants) {
    edges.push_back({j, i});
  }

  Graph g(n, edges);

  auto colors = bipartite(g);
  if (!colors.has_value()) {
    return {};
  }

  vector<vector<Vertex>> adj_fordward(n);
  for (auto [i, j] : destined) {
    if ((*colors)[i]) { // i is L, j has to ve before
      adj_fordward[j].push_back(i);
    } else { // i is R, j has to be after
      adj_fordward[i].push_back(j);
    }
  }
  for (auto [i, j] : irrelevants) {
    if ((*colors)[i]) { // i is L, j has to ve after
      adj_fordward[i].push_back(j);
    } else { // i is R, j has to be before
      adj_fordward[j].push_back(i);
    }
  }

  vector<ull> ts = topoSort(adj_fordward);
  if (ts.size() < n) {
    return {};
  }

  vector<pair<ORI, ull>> ans(n);
  ull x = 0;
  for (ull t : ts) {
    ans[t] = {(*colors)[t] ? L : R, x};
    x++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  vector<pair<ull, ull>> destined, irrelevants;
  fore(_, 0, m) {
    ull t, i, j;
    cin >> t >> i >> j;
    if (t == 1) {
      irrelevants.push_back({i - 1, j - 1});
    } else {
      destined.push_back({i - 1, j - 1});
    }
  }

  auto ans = solve(n, destined, irrelevants);

  if (ans.has_value()) {
    cout << "YES\n";
    for (auto [ori, i] : *ans) {
      cout << (ori == L ? 'L' : 'R') << ' ' << i + 1 << '\n';
    }
  } else {
    cout << "NO\n";
  }

  return EXIT_SUCCESS;
}
