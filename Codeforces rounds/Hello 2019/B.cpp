// https://codeforces.com/contest/1097/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(vector<ull> as) {
  ull n = as.size();

  vector<array<bool, 360>> dp(n + 1); // dp[i][j] = can we get j with the first i elements?

  dp[0][0] = 1;
  fore(i, 0, n) {
    fore(j, 0, 360) {
      if (dp[i][j]) {
        dp[i + 1][(j + as[i]) % 360] = true;
        dp[i + 1][(j + 360 - as[i]) % 360] = true;
      }
    }
  }

  return dp[n][0];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  if (solve(as)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
