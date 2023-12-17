// https://codeforces.com/contest/1844/problem/E

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


bool bipartite(const vector<vu>& adj) {
  ull N = adj.size();
  vb vis(N, false);
  vb color(N, false);

  fore(i, 0, N) {
    if (vis[i]) {
      continue;
    }
    vu s = {i};
    vis[i] = true;

    while (!s.empty()) {
      ull u = s.back();
      s.pop_back();

      for (auto v : adj[u]) {
        if (!vis[v]) {
          vis[v] = true;
          color[v] = !color[u];
          s.push_back(v);
        } else if (color[v] == color[u]) {
          return false;
        }
      }
    }
  }

  return true;
}

bool solve1(ull n, ull m, const vuuuu& constraints) {

  vector<vu> adj((n - 1) + (m - 1));

  for (auto [x0, y0, x1, y1] : constraints) {
    if (y1 == y0 + 1) {
      adj.push_back({x0, (n - 1) + y0});
      adj[x0].push_back(adj.size() - 1);
      adj[(n - 1) + y0].push_back(adj.size() - 1);
    } else {
      adj[x0].push_back((n - 1) + y1);
      adj[(n - 1) + y1].push_back(x0);
    }
  }

  return bipartite(adj);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vuuuu constraints(k);
    for (auto& [x0, y0, x1, y1] : constraints) {
      cin >> x0 >> y0 >> x1 >> y1;
      x0--, y0--, x1--, y1--;
    }

    if (solve1(n, m, constraints)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
