// https://codeforces.com/gym/103960/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

typedef ull Vertex;
typedef tuple<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  //                 Vertex, index of edge
  vector<vector<pair<Vertex, ull>>> adj;

  Graph(ull n, vector<Edge>& edges)
      : n(n), m(edges.size()), edges(edges), adj(n) {
    fore(i, 0, m) {
      auto [u, v] = edges[i];
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    }
  }
};

ull calc_one(const map<ull, ull>& total_counts, map<ull, ull>& sub_counts) {
  ull ans = 0;
  for (auto [C, count] : sub_counts) {
    ans += count * (total_counts.at(C) - count);
  }
  return ans;
}

void convine(map<ull, ull>& total_counts, const map<ull, ull>& sub_counts) {
  for (auto [C, count] : sub_counts) {
    total_counts[C] += count;
  }
}

vector<ull> solve(const vector<ull>& Cs, const Graph& g) {
  map<ull, ull> total_counts;
  for (ull C : Cs) {
    total_counts[C]++;
  }
  map<ull, ull> small_total_counts;
  for (auto [C, count] : total_counts) {
    if (count > 1) {
      small_total_counts[C] = count;
    }
  }

  vector<ull> ans(g.n - 1);

  function<pair<ull, map<ull, ull>>(ull, ull)> dfs = [&](ull u, ull p) {
    map<ull, ull> counts;
    ull this_ans = 0;
    for (auto [v, i] : g.adj[u]) {
      if (v != p) {
        auto [sub_ans, sub_counts] = dfs(v, u);
        ans[i] = sub_ans - sub_counts[Cs[v]] + 1 + (total_counts[Cs[v]] - sub_counts[Cs[v]]) * sub_counts[Cs[v]];
        this_ans += ans[i];
        convine(counts, sub_counts);
      }
    }
    if (total_counts[Cs[u]] > 1) {
      counts[Cs[u]]++;
    }
    return make_pair(this_ans, counts);
  };

  dfs(0, 0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<ull> Cs(N);
  for (ull& C : Cs) {
    cin >> C;
    C--;
  }
  vector<Edge> edges(N - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  Graph g(N, edges);
  vector<ull> ans = solve(Cs, g);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
