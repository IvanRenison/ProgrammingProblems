// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/*

Hacer búsqueda binaria como en gross

*/

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct DirectedGraph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj_fordward;
  vector<vector<Vertex>> adj_backward;

  DirectedGraph(ull n, vector<Edge> edges)
      : n(n), m(edges.size()), edges(edges), adj_fordward(n), adj_backward(n) {
    for (auto [u, v] : edges) {
      adj_fordward[u].push_back(v);
      adj_backward[v].push_back(u);
    }
  }
};

/* Find the minimum index for witch f is true or it.size() if none if true */
ull binary_search(function<bool(ull)> f, vector<ull> it) {
  ull lower = 0;
  ull upper = it.size();
  if (f(it[lower])) {
    return lower;
  }
  if (!f(it[upper - 1])) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(it[m])) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
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
  queue<int> q; // use priority_queue for lexic. largest ans.
  fore(i, 0, gr.size()) if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    int i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (int x : gr[i])
      if (--indeg[x] == 0)
        q.push(x);
  }
  return ret;
}

optional<ull> solve(ull k, vector<ull>& as, vector<Edge>& edges) {
  ull n = as.size();

  vector<ull> as_sorted = as;
  sort(as_sorted.begin(), as_sorted.end());

  auto f = [n, k, as, edges](ull x) {
    vector<Edge> e;
    for (auto [u, v] : edges) {
      if (as[u] <= x && as[v] <= x) {
        e.push_back({u, v});
      }
    }

    DirectedGraph g(n, e);

    vector<ull> t = topoSort(g.adj_fordward);

    if (t.size() < n) {
      return true;
    }

    vector<ull> dp(n);
    ull longest = 0;
    for (ull u : t) {
      ull this_longest = 1;
      for (ull v : g.adj_backward[u]) {
        this_longest = max(dp[v] + 1, this_longest);
      }
      dp[u] = this_longest;
      longest = max(longest, this_longest);
    }

    return bool(longest >= k);
  };

  ull ans_i = binary_search(f, as_sorted);
  if (ans_i == n) {
    return {};
  } else {
    return as_sorted[ans_i];
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m, k;
  cin >> n >> m >> k;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  vector<Edge> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }

  optional<ull> ans = solve(k, as, edges);
  if (ans.has_value()) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
