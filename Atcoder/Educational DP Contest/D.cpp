// https://atcoder.jp/contests/dp/tasks/dp_d

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(ull W, vector<pair<ull, ull>> wvs) {
  ull N = wvs.size();

  // dp[i][j] = max value in the first i items with capacity j
  vector<vector<ull>> dp(N + 1, vector<ull>(W + 1, 0));

  fore(i, 1, N + 1) {
    auto [w, v] = wvs[i - 1];
    fore(j, 0, W + 1) {
      if (w <= j) {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[N][W];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ull N, W;
  cin >> N >> W;

  vector<pair<ull, ull>> wvs(N);

  fore(i, 0, N) {
    cin >> wvs[i].first >> wvs[i].second;
  }

  cout << solve(W, wvs) << endl;

  return EXIT_SUCCESS;
}
