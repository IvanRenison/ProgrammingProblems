// https://atcoder.jp/contests/dp/tasks/dp_j

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

double solve(const vector<ull>& as) {
  ull N = as.size();

  vector<ull> counts(4);
  for (ull a : as) {
    counts[a]++;
  }

  vector<vector<vector<double>>> dp(
      counts[1] + counts[2] + counts[3] + 1,
      vector<vector<double>>(
          counts[2] + counts[3] + 1, vector<double>(counts[3] + 1, 0.0)
      )
  );

  fore(c3, 0, counts[3] + 1) {
    fore(c2, 0, counts[2] + counts[3] + 1 - c3) {
      fore(c1, 0, counts[1] + counts[2] + counts[3] + 1 - c3 - c2) {
        ull count = c1 + c2 + c3;
        if (0 < count) {
          double fcount = (double)(count);
          double p = fcount / N;
          dp[c1][c2][c3] =
              1.0 / p +
              ((c1 > 0 ? (double)c1 / fcount * dp[c1 - 1][c2][c3] : 0.0) +
               (c2 > 0 ? (double)c2 / fcount * dp[c1 + 1][c2 - 1][c3] : 0.0) +
               (c3 > 0 ? (double)c3 / fcount * dp[c1][c2 + 1][c3 - 1] : 0.0));
        }
      }
    }
  }

  return dp[counts[1]][counts[2]][counts[3]];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<ull> as(N);
  fore(i, 0, N) {

    cin >> as[i];
  }

  cout << setprecision(12) << solve(as) << '\n';

  return EXIT_SUCCESS;
}
