// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; i++)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull INF = 1ull << 60;

vector<optional<ull>> solve(
    vector<ll> ts, vector<tuple<ull, ull, ull>> edges,
    vector<tuple<ull, ull, ull, bool>> queries
) {
  ull N = ts.size(), R = edges.size(), Q = queries.size();

  //           k  , a  , b  , i_original
  vector<tuple<ull, ull, ull, ull>> queries_cold, queries_hot;
  fore(i, 0, Q) {
    auto [a, b, k, T] = queries[i];
    if (T) {
      queries_hot.push_back({k, a, b, i});
    } else {
      queries_cold.push_back({k, a, b, i});
    }
  }
  sort(queries_cold.begin(), queries_cold.end());
  sort(queries_hot.begin(), queries_hot.end());
  ull Q_cold = queries_cold.size(), Q_hot = queries_hot.size();

  //          t  , i_original
  vector<pair<ll, ull>> planets_by_t(N);
  fore(i, 0, N) {
    planets_by_t[i] = {ts[i], i};
  }
  sort(planets_by_t.begin(), planets_by_t.end());

  vector<optional<ull>> ans(Q);

  { // Solve for queries_cold
    vector<vector<ull>> dists(N, vector<ull>(N, INF));
    fore(i, 0, N) {
      dists[i][i] = 0;
    }
    for (auto [a, b, d] : edges) {
      dists[a][b] = d;
      dists[b][a] = d;
    }

    vector<ull> t_counts(N);
    ll t_last = planets_by_t[0].first;
    fore(i, 1, N) {
      if (planets_by_t[i].first != t_last) {
        t_last = planets_by_t[i].first;
        t_counts[i] = t_counts[i - 1] + 1;
      } else {
        t_counts[i] = t_counts[i - 1];
      }
    }

    ull j = 0;
    for (ull i = 0; i < N && j < Q_cold; i++) {
      auto [t_i, i_i] = planets_by_t[i];
      for (; j < Q_cold && get<0>(queries_cold[j]) <= t_counts[i]; j++) {
        auto [k, a, b, j_original] = queries_cold[j];
        if (dists[a][b] < INF) {
          ans[j_original] = dists[a][b];
        }
      }

      fore(u, 0, N) {
        fore(v, 0, N) {
          dists[v][u] = dists[u][v] =
              min(dists[u][v], dists[u][i_i] + dists[i_i][v]);
        }
      }
    }

    for (; j < Q_cold; j++) {
      auto [k, a, b, j_original] = queries_cold[j];
      if (dists[a][b] < INF) {
        ans[j_original] = dists[a][b];
      }
    }
  }

  reverse(planets_by_t.begin(), planets_by_t.end());
  { // Solve for queries_hot
    vector<vector<ull>> dists(N, vector<ull>(N, INF));
    fore(i, 0, N) {
      dists[i][i] = 0;
    }
    for (auto [a, b, d] : edges) {
      dists[a][b] = d;
      dists[b][a] = d;
    }

    vector<ull> t_counts(N);
    ll t_last = planets_by_t[0].first;
    fore(i, 1, N) {
      if (planets_by_t[i].first != t_last) {
        t_last = planets_by_t[i].first;
        t_counts[i] = t_counts[i - 1] + 1;
      } else {
        t_counts[i] = t_counts[i - 1];
      }
    }

    ull j = 0;
    for (ull i = 0; i < N && j < Q_hot; i++) {
      auto [t_i, i_i] = planets_by_t[i];
      for (; j < Q_hot && get<0>(queries_hot[j]) <= t_counts[i]; j++) {
        auto [k, a, b, j_original] = queries_hot[j];
        if (dists[a][b] < INF) {
          ans[j_original] = dists[a][b];
        }
      }

      fore(u, 0, N) {
        fore(v, 0, N) {
          dists[v][u] = dists[u][v] =
              min(dists[u][v], dists[u][i_i] + dists[i_i][v]);
        }
      }
    }

    for (; j < Q_hot; j++) {
      auto [k, a, b, j_original] = queries_hot[j];
      if (dists[a][b] < INF) {
        ans[j_original] = dists[a][b];
      }
    }
  }

  return ans;
}

int main() {
  FIN;

  ull N, R;
  cin >> N >> R;

  vector<ll> ts(N);
  for (ll& t : ts) {
    cin >> t;
  }

  vector<tuple<ull, ull, ull>> edges(R);
  for (auto& [x, y, d] : edges) {
    cin >> x >> y >> d;
    x--;
    y--;
  }

  ull Q;
  cin >> Q;
  vector<tuple<ull, ull, ull, bool>> queries(Q);
  for (auto& [a, b, k, T] : queries) {
    cin >> a >> b >> k >> T;
    a--;
    b--;
  }

  vector<optional<ull>> ans = solve(ts, edges, queries);
  for (auto a : ans) {
    if (a.has_value()) {
      cout << *a << '\n';
    } else {
      cout << "-1\n";
    }
  }

  return 0;
}
