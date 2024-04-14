// https://codeforces.com/contest/600/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


vu solve(const vu& cs, const vuu& edges) {
  ull n = cs.size();

  vector<vu> adj(n);
  for (const auto& [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vector<map<ull, ull>> dp_counts(n);
  vector<set<ull>> dp_modes(n);
  vu modes_vals(n);
  vu ans(n);

  function<void(ull, ull)> dfs = [&](ull u, ull p) {
    assert(dp_counts[u].empty());

    dp_counts[u][cs[u]] = 1;
    dp_modes[u].insert(cs[u]);
    modes_vals[u] = 1;
    ans[u] = cs[u];

    for (ull v : adj[u]) if (v != p) {
      dfs(v, u);
      if (dp_counts[v].size() > dp_counts[u].size()) {
        swap(dp_counts[u], dp_counts[v]);
        swap(dp_modes[u], dp_modes[v]);
        swap(modes_vals[u], modes_vals[v]);
        ans[u] = ans[v];
      }
      for (auto [c, cnt] : dp_counts[v]) {
        dp_counts[u][c] += cnt;
        if (dp_counts[u][c] == modes_vals[u]) {
          dp_modes[u].insert(c);
          ans[u] += c;
        } else if (dp_counts[u][c] > modes_vals[u]) {
          dp_modes[u].clear();
          dp_modes[u].insert(c);
          modes_vals[u] = dp_counts[u][c];
          ans[u] = c;
        }
      }
    }
  };

  dfs(0, 0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu cs(n);
  for (ull& c : cs) {
    cin >> c;
  }
  vuu edges(n - 1);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  vu ans = solve(cs, edges);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
