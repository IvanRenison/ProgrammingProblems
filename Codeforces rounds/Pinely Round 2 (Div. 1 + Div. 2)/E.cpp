// https://codeforces.com/contest/1863/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

typedef ull Vertex;
typedef pair<Vertex, Vertex> Edge;

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

template <typename T>
using rev_priority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve1(ull k, vector<ull> hs, vector<Edge> edges) {
  ull n = hs.size();

  DirectedGraph g(n, edges);

  vector<ull> dp(n);
  ull last_day = 0, last_hour = 0, first_hour = 1ull << 60;

  fore(u, 0, n) {
    ull max_day = 0, max_hour = 0;

    for (Vertex v : g.adj_backward[u]) {
      if (dp[v] > max_day) {
        max_day = dp[v];
        max_hour = hs[v];
      } else if (dp[v] == max_day && hs[v] > max_hour) {
        max_hour = hs[v];
      }
    }

    if (max_hour <= hs[u]) {
      dp[u] = max_day;
      if (dp[u] == 0) {
        first_hour = min(first_hour, hs[u]);
      }
    } else {
      dp[u] = max_day + 1;
    }

    if (dp[u] > last_day) {
      last_day = dp[u];
      last_hour = hs[u];
    } else if (dp[u] == last_day && hs[u] > last_hour) {
      last_hour = hs[u];
    }
  }

  ull ans = last_day * k + last_hour - first_hour;

  vector<pair<ull, ull>> hs_i;
  fore(u, 0, n) {
    if (g.adj_backward[u].size() == 0) {
      hs_i.push_back({hs[u], u});
    }
  }

  sort(hs_i.begin(), hs_i.end());

  vector<bool> atrased(n, false);

  for (auto it = hs_i.begin(); it + 1 != hs_i.end(); it++) {
    auto [h, u] = *it;
    {
      auto it2 = it + 1;
      auto [h2, u2] = *it2;
      first_hour = h2;
    }

    rev_priority_queue<ull> q;
    q.push(u);

    while (!q.empty()) {
      Vertex v = q.top();
      q.pop();
      if (atrased[v]) {
        continue;
      }

      ull max_day = 1, max_hour = hs[v];
      for (Vertex w : g.adj_backward[v]) {
        if (dp[w] > max_day) {
          max_day = dp[w];
          max_hour = hs[w];
        } else if (dp[w] == max_day && hs[w] > max_hour) {
          max_hour = hs[w];
        }
      }
      ull old_dp_v = dp[v];
      if (max_hour <= hs[v]) {
        dp[v] = max_day;
      } else {
        dp[v] = max_day + 1;
      }
      if (dp[v] > last_day) {
        last_day = dp[v];
        last_hour = hs[v];
      } else if (dp[v] == last_day && hs[v] > last_hour) {
        last_hour = hs[v];
      }

      if (dp[v] != old_dp_v) {
        atrased[v] = true;
        for (Vertex w : g.adj_fordward[v]) {
          if (!atrased[w]) {
            q.push(w);
          }
        }
      }
    }

    ans = min(ans, last_day * k + last_hour - first_hour);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vector<ull> hs(n);
    fore(j, 0, n) cin >> hs[j];
    vector<pair<ull, ull>> edges(m);
    for (auto& [a, b] : edges) {
      cin >> a >> b;
      a--, b--;
    }

    auto ans = solve1(k, hs, edges);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
