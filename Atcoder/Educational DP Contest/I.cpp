// https://atcoder.jp/contests/dp/tasks/dp_i

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

double solve(ull N, vector<double> ps) {

  // dp[i][j] probability of getting i heads in the first j coins
  vector<vector<double>> dp(N + 1, vector<double>(N + 1, 0.0));

  dp[0][0] = 1.0;

  fore(j, 1, N + 1) {
    double p = ps[j - 1];

    dp[0][j] = dp[0][j - 1] * (1 - p);

    fore(i, 1, j + 1) {
      dp[i][j] = dp[i - 1][j - 1] * p + dp[i][j - 1] * (1 - p);
    }
  }

  double ans = 0.0;
  fore(i, N / 2 + 1, N + 1) {
    ans += dp[i][N];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;

  vector<double> ps(N);

  fore(i, 0, N) {
    cin >> ps[i];
  }

  cout << fixed << setprecision(10);

  cout << solve(N, ps) << '\n';

  return EXIT_SUCCESS;
}
