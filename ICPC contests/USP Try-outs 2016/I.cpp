// https://codeforces.com/gym/101064/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;


vuuu solve(ull N, const vuu& edges) {
  ull M = edges.size();

  vector<vuu> adj(N);
  fore(i, 0, M) {
    auto [u, v] = edges[i];
    adj[u].push_back({v, i}), adj[v].push_back({u, i});
  }

  vu father(N, inf);
  vu suns_counts(N, 0);
  vu leafs;

  {
    vu s = {0};
    father[0] = 0;
    while (!s.empty()) {
      ull u = s.back();
      s.pop_back();

      for (auto [v, _] : adj[u]) {
        if (father[v] == inf) {
          father[v] = u;
          suns_counts[u]++;
          s.push_back(v);
        }
      }

      if (suns_counts[u] == 0) {
        leafs.push_back(u);
      }
    }
    father[0] = inf;
  }

  vb added(M, false);
  vuuu ans;

  while (!leafs.empty()) {
    ull u = leafs.back();
    leafs.pop_back();

    vuu non_father_edges;
    uu father_edge;

    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
      auto [v, i] = *it;
      if (v == father[u]) {
        father_edge = {v, i};
      } else if (!added[i]) {
        non_father_edges.push_back({v, i});
      }
    }

    fore(i, 0, non_father_edges.size() / 2) {
      auto [v, j] = non_father_edges[2 * i];
      auto [w, k] = non_father_edges[2 * i + 1];
      added[j] = added[k] = true;
      ans.push_back({v, u, w});
    }

    if (non_father_edges.size() % 2 == 1) {
      auto [v, j] = non_father_edges.back();
      added[j] = added[father_edge.second] = true;
      ans.push_back({v, u, father_edge.first});
    }

    if (father[u] != inf) {
      auto v = father[u];
      suns_counts[v]--;
      if (suns_counts[v] == 0) {
        leafs.push_back(v);
      }
    }

  }

  //assert(ans.size() == M / 2);

  return ans;
}

/* bool validAns(const vuuu& ans, const vuu& edges) {
  set<uu> used, ed;

  for (auto [u, v] : edges) {
    if (u > v) {
      swap(u, v);
    }
    ed.insert({u, v});
  }

  for (auto [u, v, w] : ans) {
    ull u0 = u, v0 = v, u1 = v, v1 = w;
    if (u0 > v0) {
      swap(u0, v0);
    }
    if (u1 > v1) {
      swap(u1, v1);
    }
    if (used.count({u0, v0}) || used.count({u1, v1}) || !ed.count({u0, v0}) || !ed.count({u1, v1})) {
      return false;
    }
    used.insert({u0, v0}), used.insert({u1, v1});
  }

  return used.size() == ed.size();
} */

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M;
  cin >> N >> M;
  vuu edges(M);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  vuuu ans = solve(N, edges);
  // assert(validAns(ans, edges));
  cout << ans.size() << '\n';
  for (auto [u, v, w] : ans) {
    cout << u + 1 << ' ' << v + 1 << ' ' << w  + 1 << '\n';
  }

/*   fore(_, 0, 1000) {
    ull N = 10, M = 20;

    ull m = M;
    vuu edges;
    set<uu> ed;

    fore(i, 0, N - 1) {
      edges.push_back({i, i + 1});
      ed.insert({i, i + 1});
      m--;
    }
    while (m > 0) {
      ull u = rand() % N, v = rand() % N;
      if (u == v || ed.count({u, v}) || ed.count({v, u})) {
        continue;
      }
      edges.push_back({u, v});
      ed.insert({u, v});
      m--;
    }

    vuuu ans = solve(N, edges);
    if (!validAns(ans, edges)) {
      cerr << "ERROR\n";
      cerr << N << ' ' << M << '\n';
      for (auto [u, v] : edges) {
        cerr << u + 1 << ' ' << v + 1 << '\n';
      }
      cerr << "ans: \n";
      cerr << ans.size() << '\n';
      for (auto [u, v, w] : ans) {
        cerr << u + 1 << ' ' << v + 1 << ' ' << w + 1 << '\n';
      }
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
