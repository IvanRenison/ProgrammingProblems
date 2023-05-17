// https://atcoder.jp/contests/dp/tasks/dp_h

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MOD 1000000007

ull solve(vector<vector<bool>> grid) {
  ull H = grid.size();
  ull W = grid[0].size();

  vector<vector<ull>> dp(H, vector<ull>(W));

  dp[0][0] = 1;

  fore(i, 1, H) {
    if (grid[i][0]) {
      dp[i][0] = dp[i - 1][0];
    } else {
      dp[i][0] = 0;
    }
  }

  fore(j, 1, W) {
    if (grid[0][j]) {
      dp[0][j] = dp[0][j - 1];
    } else {
      dp[0][j] = 0;
    }
  }

  fore(i, 1, H) {
    fore(j, 1, W) {
      if (grid[i][j]) {
        dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
      } else {
        grid[i][j] = 0;
      }
    }
  }

  return dp[H - 1][W - 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull H, W;

  cin >> H >> W;

  vector<vector<bool>> grid(H, vector<bool>(W));

  fore(i, 0, H) {
    fore(j, 0, W) {
      char c;
      cin >> c;
      grid[i][j] = c == '.';
    }
  }

  cout << solve(grid) << '\n';

  return EXIT_SUCCESS;
}
