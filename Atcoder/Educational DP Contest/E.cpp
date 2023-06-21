// https://atcoder.jp/contests/dp/tasks/dp_e

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define VMAX 1000
#define INF (1ull << 48)

ull solve(ull W, vector<pair<ull, ull>> wvs) {
  ull N = wvs.size();

  vector<ull> dp(N * VMAX + 1, INF); // dp[v] = min wight to get value v
  dp[0] = 0;

  for (auto [w, v] : wvs) {
    for (ull i = N * VMAX; i >= v; i--) {
      dp[i] = min(dp[i], dp[i - v] + w);
    }
  }

  for (ull i = N * VMAX; i > 0; i--) {
    if (dp[i] <= W) {
      return i;
    }
  }

  return 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  ull N, W;
  cin >> N >> W;

  vector<pair<ull, ull>> wvs(N);

  fore(i, 0, N) {
    cin >> wvs[i].first >> wvs[i].second;
  }

  cout << solve(W, wvs) << '\n';

  return EXIT_SUCCESS;
}
