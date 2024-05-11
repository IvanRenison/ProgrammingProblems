// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

void maxEq(ull& x, ull y) {
  x = max(x, y);
}

ull solve(string A, string B) {
  ull n = A.size(), m = B.size();

  vector<vector<ull>> dp(n + 1, vector<ull>(m + 1));
  // dp[i][j] = maximum similarity using character i-1 of A and j-1 of B

  ull total_max = 0;

  fore(i, 1, n + 1) {
    fore(j, 1, m + 1) {
      dp[i][j] = 0;
      if (dp[i][j - 1] > 0) {
        maxEq(dp[i][j], dp[i][j - 1] - 1);
      }
      if (dp[i - 1][j] > 0) {
        maxEq(dp[i][j], dp[i - 1][j] - 1);
      }
      if (A[i - 1] == B[j - 1]) {
        maxEq(dp[i][j], dp[i - 1][j - 1] + 2);
      }

      maxEq(total_max, dp[i][j]);
    }
  }

  return total_max;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;
  string A, B;
  cin >> A >> B;

  cout << solve(A, B) << '\n';

  return EXIT_SUCCESS;
}
