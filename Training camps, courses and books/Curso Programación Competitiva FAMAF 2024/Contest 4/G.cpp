// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
typedef vector<int> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

/** Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: O(\alpha(N))$
 */
struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

pair<vuu, uint> solve(const vector<vector<string>>& grids, uint w) {
  uint k = grids.size(), n = grids[0].size(), m = grids[0][0].size();

  vuuu edges;

  fore(i, 0, k) fore(j, i + 1, k) {
    uint d = 0;
    fore(x, 0, n) fore(y, 0, m) {
      d += grids[i][x][y] != grids[j][x][y];
    }
    d *= w;
    edges.push_back({d, i, j});
  }

  sort(edges.begin(), edges.end());

  UF uf(k);
  vector<vu> adj(k);
  uint ans_cost = 0;

  for (auto [d, i, j] : edges) {
    if (d >= n * m) {
      break;
    }
    if (uf.join(i, j)) {
      adj[i].push_back(j), adj[j].push_back(i);
      ans_cost += d;
    }
  }

  vuu ans;

  vb vis(k, false);

  fore(i, 0, k) {
    if (!vis[i]) {
      ans_cost += n * m;
      ans.push_back({i, -1});
      vis[i] = true;
      vu s = {i};
      while (!s.empty()) {
        uint u = s.back();
        s.pop_back();

        for (uint v : adj[u]) {
          if (!vis[v]) {
            ans.push_back({v, u});
            vis[v] = true;
            s.push_back(v);
          }
        }
      }
    }
  }

  assert(ans.size() == k);

  return {ans, ans_cost};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, m, k, w;
  cin >> n >> m >> k >> w;
  vector<vector<string>> grids(k, vector<string>(n));
  for (vector<string>& grid : grids) {
    for (string& row : grid) {
      cin >> row;
    }
  }

  auto [ans, ans_cost] = solve(grids, w);
  cout << ans_cost << '\n';
  for (auto [x, y] : ans) {
    cout << x + 1 << ' ' << (y == -1 ? 0 : y + 1) << '\n';
  }

  return EXIT_SUCCESS;
}
