// https://codeforces.com/contest/2025/problem/F

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

struct Node {
  uu p;
  vuu suns, extra;
  Node() : p({-1, -1}) {}
};

vector<Node> getTree(ull n, vuu& edges) {
  ull m = edges.size();

  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [x, y] = edges[e];
    adj[x].push_back({y, e}), adj[y].push_back({x, e});
  }

  vector<Node> tree(n);

  vb vis(n, false), used(m, false);
  fore(i, 0, n) if (!vis[i]) {
    vis[i] = true;
    vu s = {i};
    while (!s.empty()) {
      ull u = s.back();
      s.pop_back();
      for (auto [v, e] : adj[u]) if (!vis[v]) {
        used[e] = true;
        vis[v] = true;
        tree[u].suns.push_back({v, e});
        tree[v].p = {u, e};
        s.push_back(v);
      }
    }
  }

  fore(e, 0, m) {
    if (!used[e]) {
      auto [u, v] = edges[e];
      tree[u].extra.push_back({v, e});
    }
  }

  return tree;
}

vu solve(ull n, vuu& edges) {
  ull m = edges.size();

  vector<Node> tree = getTree(n, edges);

  vu ans(m);

  auto comb = [&](optional<ull> e0, optional<ull> e1) -> optional<ull> {
    if (!e0.has_value()) return e1;
    if (!e1.has_value()) return e0;
    auto [x0, y0] = edges[*e0];
    auto [x1, y1] = edges[*e1];
    if (x0 == x1) {
      ans[*e0] = 0;
      ans[*e1] = 0;
    } else if (x0 == y1) {
      ans[*e0] = 0;
      ans[*e1] = 1;
    } else if (y0 == x1) {
      ans[*e0] = 1;
      ans[*e1] = 0;
    } else if (y0 == y1) {
      ans[*e0] = 1;
      ans[*e1] = 1;
    }
    if (*e0 < *e1) {
      ans[*e1] |= 2;
    } else {
      ans[*e0] |= 2;
    }
    return {};
  };

  vb vis(n, false);

  function<optional<ull>(ull)> dfs = [&](ull u) -> optional<ull> {
    vis[u] = true;
    optional<ull> ans;
    for (auto [v, e] : tree[u].extra) {
      ans = comb(ans, e);
    }
    for (auto [v, e] : tree[u].suns) {
      auto res = dfs(v);
      res = comb(res, e);
      ans = comb(ans, res);
    }
    return ans;
  };

  fore(i, 0, n) if (!vis[i]) {
    dfs(i);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, q;
  cin >> n >> q;
  vuu queries(q);
  for (auto& [x, y] : queries) {
    cin >> x >> y;
    x--, y--;
  }

  auto ans = solve(n, queries);
  for (ull a : ans) {
    if (a & 1) {
      cout << 'y';
    } else {
      cout << 'x';
    }
    if (a & 2) {
      cout << '-';
    } else {
      cout << '+';
    }
    cout << '\n';
  }
}
