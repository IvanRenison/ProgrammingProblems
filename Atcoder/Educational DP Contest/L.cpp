// https://atcoder.jp/contests/dp/tasks/dp_l

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solve(const vi& as) {
  ull N = as.size();

  vector<vector<vi>> dp(N + 1, vector<vi>(N + 1, vi(2)));
  // d[i][j][x] = they have taken i from left, from j to right, if x is taros turn

  fore(k, 1, N + 1) {
    fore(i, 0, N - k + 1) {
      ull j = i + k;
      dp[i][j][true] = max(
        dp[i + 1][j][false] + as[i],
        dp[i][j - 1][false] + as[j - 1]
      );
      dp[i][j][false] = min(
        dp[i + 1][j][true] - as[i],
        dp[i][j - 1][true] - as[j - 1]
      );
    }
  }

  ll ans = dp[0][N][true];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vi as(N);
  for (ll& a : as) {
    cin >> a;
  }

  ll ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
