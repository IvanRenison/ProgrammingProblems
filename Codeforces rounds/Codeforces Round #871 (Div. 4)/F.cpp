// https://codeforces.com/contest/1829/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, vector<pair<ull, ull>>> parse1(void) {
  ull n, m;
  cin >> n >> m;
  vector<pair<ull, ull>> edges(m);
  fore(i, 0, m) {
    ull u, v;
    cin >> u >> v;
    edges[i] = {u - 1, v - 1};
  }
  return {n, edges};
}

pair<ull, ull> solve1(ull n, vector<pair<ull, ull>> edges) {
  vector<vector<ull>> neighbors(n);
  for (auto [u, v] : edges) {
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
  }

  ull border_vertex = 0;
  for (; neighbors[border_vertex].size() != 1; border_vertex++)
    ;

  ull medium_vertex = neighbors[border_vertex][0];

  ull neighbour = 0;
  for (; neighbors[neighbors[medium_vertex][neighbour]].size() == 1;
       neighbour++)
    ;

  ull central_vertex = neighbors[medium_vertex][neighbour];

  return {
      neighbors[central_vertex].size(), neighbors[medium_vertex].size() - 1};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, edges] = parse1();
    auto [x, y] = solve1(n, edges);
    cout << x << " " << y << "\n";
  }

  return EXIT_SUCCESS;
}
