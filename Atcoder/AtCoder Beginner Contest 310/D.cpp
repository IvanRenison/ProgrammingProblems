// https://atcoder.jp/contests/abc310/tasks/abc310_d

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(ull T, ull N, vector<pair<ull, ull>> edges) {
  vector<vector<bool>> adj(N, vector<bool>(N, false));
  for (auto edge : edges) {
    adj[edge.first][edge.second] = true;
    adj[edge.second][edge.first] = true;
  }

  vector<vector<ull>> dp(T, vector<ull>(1ull << N, 0));

  dp[0][0] = 0;
  fore(x, 1, 1ull << N) {
    bool valid = true;
    fore(i, 0, N) {
      if (x & (1 << i)) {
        fore(j, 0, N) {
          if (i != j && (x & (1 << j)) && adj[i][j]) {
            valid = false;
            break;
          }
        }
      }
    }
    if (valid) {
      dp[0][x] = 1;
    }
  }

  fore(t, 1, T) {
    fore(x, 0, 1ull << N) {
      ull this_ans = 0;
      fore(y, 1, x) {
        if ((y & x) == y) {
          this_ans += dp[t - 1][y] * dp[0][x ^ y];
        }
      }
      dp[t][x] = this_ans;
    }
  }

  ull fact_t = 1;
  fore(i, 1, T + 1) {
    fact_t *= i;
  }

  return dp[T - 1][(1ull << N) - 1] / fact_t;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull T, N, M;
  cin >> N >> T >> M;
  vector<pair<ull, ull>> edges(M);
  fore(i, 0, M) {
    cin >> edges[i].first >> edges[i].second;
    edges[i].first--;
    edges[i].second--;
  }

  auto ans = solve(T, N, edges);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
