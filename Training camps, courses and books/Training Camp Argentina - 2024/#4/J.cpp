// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/J

#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

optional<vu> greedyMatching(vector<vu>& adj) {
  uint N = adj.size();

  vu match(N, -1);
  vu q;
  fore(i, 0, N) {
    if (adj[i].size() == 1) {
      q.push_back(i);
    }
  }

  while (!q.empty()) {
    uint u = q.back();
    q.pop_back();

    if (match[u] != -1) {
      continue;
    }

    if (adj[u].empty()) {
      return {};
    }

    uint v = *adj[u].begin();
    adj[v].erase(lower_bound(ALL(adj[v]), u));
    adj[u].clear();
    match[u] = v;
    match[v] = u;

    for (uint w : adj[v]) {
      adj[w].erase(lower_bound(ALL(adj[w]), v));
      if (adj[w].size() == 1) {
        q.push_back(w);
      }
    }
  }

  return match;
}

bool solve(vector<string>& grid) {
  uint n = grid.size(), m = grid[0].size();

  uint count_true = 0;
  fore(i, 0, n) fore(j, 0, m) {
    count_true += grid[i][j] == '.';
  }

  auto toIdx = [&](uint i, uint j) -> uint { return i * m + j; };
  auto toPos = [&](uint idx) -> uu { return {idx / m, idx % m}; };

  vector<vu> adj(n * m);
  fore(i, 0, n) fore(j, 0, m) {
    uint idx = toIdx(i, j);
    if (grid[i][j] == '.') {
      if (i > 0 && grid[i - 1][j] == '.') {
        uint ni = i - 1, nj = j;
        uint nidx = toIdx(ni, nj);
        adj[idx].push_back(nidx);
      }
      if (i < n - 1 && grid[i + 1][j] == '.') {
        uint ni = i + 1, nj = j;
        uint nidx = toIdx(ni, nj);
        adj[idx].push_back(nidx);
      }
      if (j > 0 && grid[i][j - 1] == '.') {
        uint ni = i, nj = j - 1;
        uint nidx = toIdx(ni, nj);
        adj[idx].push_back(nidx);
      }
      if (j < m - 1 && grid[i][j + 1] == '.') {
        uint ni = i, nj = j + 1;
        uint nidx = toIdx(ni, nj);
        adj[idx].push_back(nidx);
      }
    }
  }

  fore(i, 0, n * m) {
    sort(ALL(adj[i]));
  }

  optional<vu> match = greedyMatching(adj);
  if (!match) {
    return false;
  }
  uint count = 0;
  for (uint u : *match) {
    if (u != -1) {
      count++;
    }
  }

  if (count != count_true) {
    return false;
  }

  fore(i, 0, n) fore(j, 0, m) if ((i + j) % 2 == 0 && grid[i][j] == '.') {
    uint idx = toIdx(i, j);
    uint nidx = (*match)[idx];
    auto [ni, nj] = toPos(nidx);
    if (ni == i) {
      grid[i][min(j, nj)] = '<';
      grid[i][max(j, nj)] = '>';
    } else {
      grid[min(i, ni)][j] = '^';
      grid[max(i, ni)][j] = 'v';
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  uint n, m;
  cin >> n >> m;

  vector<string> grid(n);
  fore(i, 0, n) {
    cin >> grid[i];
  }

  bool ans = solve(grid);
  if (ans) {
    for (string& s : grid) {
      cout << s << '\n';
    }
  } else {
    cout << "Not unique\n";
  }
}
