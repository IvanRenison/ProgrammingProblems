// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

const string hard = "hard";

bool in_hard(char c) {
  return hard.find(c) < 4;
}

bool ord_hard(char c0, char c1) {
  return hard.find(c0) < hard.find(c1);
}

ull solve(string s, vector<ull> as) {
  ull n = s.size();

  array<vector<ull>, 4> dp = {
      vector<ull>(n + 1), vector<ull>(n + 1), vector<ull>(n + 1),
      vector<ull>(n + 1)};

  fore(i, 0, 4) {
    dp[i][0] = 0;
  }

  fore(j, 1, n + 1) {
    ull a = as[j - 1];
    char c = s[j - 1];
    if (c == 'h') {
      dp[0][j] = dp[0][j - 1] + a;
    } else {
      dp[0][j] = dp[0][j - 1];
    }
  }

  fore(j, 1, n + 1) {
    ull a = as[j - 1];
    char c = s[j - 1];
    fore(i, 1, 4) {
      if (c == hard[i]) {
        dp[i][j] = min(dp[i - 1][j], dp[i][j - 1] + a);
      } else {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }

  return dp[3][n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  string s;
  vector<ull> as(n);
  cin >> s;
  fore(i, 0, n) {
    cin >> as[i];
  }

  cout << solve(s, as) << '\n';

  return EXIT_SUCCESS;
}
