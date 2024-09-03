// https://codeforces.com/gym/105321/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define SZ(x) (x.size())

/** Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists.
 * To get edge indices back, add .snd to s and ret.
 * Time: O(V + E)
 * Status: stress-tested
 */
vi eulerWalk(vector<vector<ii>>& gr, ll nedges, ll src=0) {
  ll n = SZ(gr);
  vi D(n), its(n), eu(nedges), ret, s = {src};
  D[src]++; // to allow Euler paths, not just cycles
  while (!s.empty()) {
    ll x = s.back(), &it = its[x], end = SZ(gr[x]);
    if (it == end){ ret.push_back(x); s.pop_back(); continue; }
    auto [y, e] = gr[x][it++];
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1; s.push_back(y);
    }}
  for (ll x : D) if (x < 0 || SZ(ret) != nedges+1) return {};
  return {ret.rbegin(), ret.rend()};
}

optional<vector<vu>> solve(vector<vb>& grid) {
  ull N = grid.size(), M = grid[0].size();

  vuu edges;
  fore(i, 0, N) {
    fore(j, 0, M) {
      if (grid[i][j]) {
        edges.push_back({i, N + j});
      }
    }
  }

  vector<vector<ii>> adj(N + M);
  fore(e, 0, edges.size()) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e});
    adj[v].push_back({u, e});
  }

  ll s = 0;
  fore(u, 0, N + M) {
    if (adj[s].empty() || adj[u].size() % 2 == 1) {
      s = u;
    }
  }

  vi path = eulerWalk(adj, edges.size(), s);
  if (path.empty()) {
    return {};
  }

  vector<vu> ans(N, vu(M, 0));
  fore(i, 0, path.size() - 1) {
    ull u = path[i], v = path[i + 1];
    if (u < N) {
      ans[u][v - N] = i + 1;
    } else {
      ans[v][u - N] = i + 1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vector<vb> grid(N, vb(M));
  fore(i, 0, N) {
    fore(j, 0, M) {
      char c;
      cin >> c;
      grid[i][j] = c == '.';
    }
  }

  auto ans = solve(grid);

  if (ans.has_value()) {
    for (vu& row : *ans) {
      for (ull x : row) {
        cout << x << ' ';
      }
      cout << '\n';
    }
  } else {
    cout << "*\n";
  }
}
