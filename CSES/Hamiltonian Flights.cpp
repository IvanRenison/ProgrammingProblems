// https://cses.fi/problemset/task/1690/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MOD ull(1e9 + 7)

ull solve(ull n, vector<pair<ull, ull>> edges) {
  vector<vector<ull>> adg(n, vector<ull>(n));

  for (auto [u, v] : edges) {
    adg[u][v]++;
  }

  vector<vector<ull>> dp(n - 1, vector<ull>(1 << (n - 1)));
  // dp[i][x] formas de empezar en 0, pasar por todos los bits de x y después ir a i

  dp[0][0] = 1;
  fore(x, 1, 1ull << (n - 1)) {
    fore(v, 1, n - 1) {
      if ((x & (1 << v)) == 0) {
        ull this_ans = 0;
        fore(u, 0, n - 1) {
          if ((x & (1 << u)) != 0 && adg[u][v] > 0) {
            this_ans = (this_ans + adg[u][v] * dp[u][x & ~(1 << u)]) % MOD;
          }
        }
        dp[v][x] = this_ans;
      }
    }
  }

  ull ans = 0;
  fore(v, 0, n - 1) {
    ans = (ans + adg[v][n - 1] * dp[v][((1 << (n - 1)) - 1) & ~(1 << v)]) % MOD;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  vector<pair<ull, ull>> edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  cout << solve(n, edges) << '\n';

  return EXIT_SUCCESS;
}
