// https://atcoder.jp/contests/dp/tasks/dp_f

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

string solve(string s0, string s1) {
  ull n = s0.size();
  ull m = s1.size();

  vector<vector<ull>> dp(n + 1, vector<ull>(m + 1, 0));

  fore(i, 1, n + 1) {
    fore(j, 1, m + 1) {
      if (s0[i - 1] == s1[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
      dp[i][j] = max(dp[i][j], max({dp[i - 1][j], dp[i][j - 1]}));
    }
  }

  string ans = "";
  ull i = n, j = m;
  while (i > 0 && j > 0) {
    if (s0[i - 1] == s1[j - 1]) {
      ans.push_back(s0[i - 1]);
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  reverse(ans.begin(), ans.end());

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s0, s1;
  cin >> s0 >> s1;

  cout << solve(s0, s1) << '\n';

  return EXIT_SUCCESS;
}
