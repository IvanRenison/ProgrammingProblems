// https://redprogramacioncompetitiva.com/contests/2024/01/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
const ull inf = 1ull << 60;

#define max_c 1000

uu solve(ull c, const vu& as) {
  ull n = as.size();

  vector<vector<bitset<max_c + 1>>> dp(n + 1, vector<bitset<max_c + 1>>(c + 1));

  dp[0][0][0] = true;

  fore(i, 0, n) {
    ull a = as[i];
    fore(j, 0, c + 1) {
      dp[i + 1][j] |= dp[i][j] | (dp[i][j] << a);
      if (a <= j) {
        dp[i + 1][j] |= dp[i][j - a];
      }
    }
  }

  ull ans = 0;
  ull ans_i, ans_j;
  ull diff = inf;

  fore(i, 0, c + 1) {
    fore(j, 0, i + 1) {
      if (dp[n][i][j]) {
        if (i + j > ans || (i + j == ans && max(i, j) - min(i, j) <= diff)) {
          ans = i + j;
          ans_i = i, ans_j = j;
          diff = max(i, j) - min(i, j);
        }
      }
    }
  }

  return {ans_i, ans_j};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull c, n;
  cin >> c >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  auto ans = solve(c, as);
  cout << ans.first << ' ' << ans.second << '\n';

  return EXIT_SUCCESS;
}
