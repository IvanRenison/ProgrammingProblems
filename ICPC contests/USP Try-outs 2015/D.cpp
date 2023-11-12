// https://codeforces.com/gym/101047/problem/D
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull INF = 1ull << 48;

pair<vector<ull>, vector<ull>>
Dijkstra(ull N, vector<vector<pair<ull, ull>>>& adj, ull s) {
  vector<bool> visited(N, false);
  vector<ull> dist(N, INF);

  priority_queue<pair<ll, ull>> q;
  q.push({0, s});

  vector<ull> order;

  while (!q.empty()) {
    auto [d, v] = q.top();
    q.pop();
    d = -d;

    if (visited[v]) {
      continue;
    }

    order.push_back(v);

    dist[v] = d;
    visited[v] = true;

    for (auto [u, C] : adj[v]) {
      if (!visited[u]) {
        q.push({-(ll)(d + C), u});
      }
    }
  }

  return {dist, order};
}

double solve1(ull N, ull K, vector<tuple<ull, ull, ull>>& edges) {
  vector<vector<pair<ull, ull>>> adj(N);

  for (auto [u, v, C] : edges) {
    adj[u].push_back({v, C});
    adj[v].push_back({u, C});
  }

  auto [dist, order] = Dijkstra(N, adj, N - 1);

  double plane_cost = (double)(N * K);
  double boat_cost = 0.0;
  fore(i, 1, order.size()) {
    ull u = order[i];
    double new_plane_cost = (double)N / ((double(i + 1))) * (double)K;
    double new_boat_cost =
        (boat_cost * (double)i + (double)dist[u]) / (double)(i + 1);
    if (new_plane_cost + new_boat_cost <= plane_cost + boat_cost) {
      plane_cost = new_plane_cost;
      boat_cost = new_boat_cost;
    } else {
      break;
    }
  }

  double no_plane_cost = (double)dist[0];

  return min(no_plane_cost, plane_cost + boat_cost);
}

int main() {
  FIN;

  cout << setprecision(8);

  ull T;
  cin >> T;
  while (T--) {
    ull N, M, K;
    cin >> N >> M >> K;
    vector<tuple<ull, ull, ull>> edges(M);
    for (auto& [u, v, C] : edges) {
      cin >> u >> v >> C;
      u--, v--;
    }

    cout << solve1(N, K, edges) << '\n';
  }

  return 0;
}