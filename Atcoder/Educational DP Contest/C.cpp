// https://atcoder.jp/contests/dp/tasks/dp_c

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(array<vector<ull>, 3> abcs) {
  ull n = abcs[0].size();

  // dp[i][j] maximum happiness if we choose i-th activity on j-th day
  array<vector<ull>, 3> dp = {vector<ull>(n), vector<ull>(n), vector<ull>(n)};

  fore(i, 0, 3) {
    dp[i][0] = abcs[i][0];
  }

  fore(j, 1, n) {
    fore(i, 0, 3) {
      dp[i][j] =
          abcs[i][j] + max(dp[(i + 1) % 3][j - 1], dp[(i + 2) % 3][j - 1]);
    }
  }

  ull ans = max(dp[0][n - 1], max(dp[1][n - 1], dp[2][n - 1]));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;

  array<vector<ull>, 3> abcs = {vector<ull>(N), vector<ull>(N), vector<ull>(N)};

  fore(i, 0, N) {
    cin >> abcs[0][i] >> abcs[1][i] >> abcs[2][i];
  }

  cout << solve(abcs) << '\n';

  return EXIT_SUCCESS;
}
