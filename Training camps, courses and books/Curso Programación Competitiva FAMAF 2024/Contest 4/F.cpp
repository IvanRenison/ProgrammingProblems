// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(const vuuu& edges, const vu& ss) {
  ull n = ss.size();

  vector<vuu> adj(n);

  for (auto [u, v, w] : edges) {
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  }

  vector<unordered_map<ull, ull>> reach(n);
  reach[0][ss[0]] = 0;

  rpriority_queue<uuu> q;
  q.push({0, ss[0], 0});

  while (!q.empty()) {
    auto [d, s, u] = q.top();
    q.pop();

    if (d > reach[u][s]) {
      continue;
    }

    vu ss_ = {s, ss[u]};

    for (auto [v, w] : adj[u]) {
      for (ull s_ : ss_) {
        ull nd = d + w * s_;
        if (!reach[v].count(s_) || nd < reach[v][s_]) {
          q.push({nd, s_, v});
          reach[v][s_] = nd;
        }
      }
    }
  }

  ull ans = LONG_LONG_MAX;

  assert(reach[n - 1].size() > 0);

  for (auto [s, d] : reach[n - 1]) {
    ans = min(ans, d);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    vuuu edges(m);
    for (auto& [u, v, w] : edges) {
      cin >> u >> v >> w;
      u--, v--;
    }

    vu ss(n);
    for (ull& s : ss) {
      cin >> s;
    }

    ull ans = solve(edges, ss);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
