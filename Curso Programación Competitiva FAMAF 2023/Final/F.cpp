// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ll solve(array<ll, 3> pqr, vector<ll> as) {
  ull n = as.size();
  vector<array<ll, 4>> dp(n + 1, {0, LLONG_MIN, LLONG_MIN, LLONG_MIN});
  // dp[i][j] = max with i element and j factors


  fore(i, 1, n + 1) {
    fore(j, 1, 4) {
      dp[i][j] = max(dp[i - 1][j], pqr[j - 1] * as[i - 1] + dp[i][j - 1]);
    }
  }

  return dp[n][3];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  array<ll, 3> pqr;
  cin >> n >> pqr[0] >> pqr[1] >> pqr[2];
  vector<ll> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  cout << solve(pqr, as) << '\n';

  return EXIT_SUCCESS;
}
