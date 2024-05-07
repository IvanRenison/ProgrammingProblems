// https://atcoder.jp/contests/dp/tasks/dp_n

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
const ull inf = 1ull << 60;


ull solve(const vu& as) {
  ull n = as.size();

  vu sums(n + 1);
  fore(i, 0, n) {
    sums[i + 1] = sums[i] + as[i];
  }

  vector<vu> dp(n + 1, vu(n + 1));

  fore(k, 2, n + 1) {
    fore(l, 0, n + 1 - k) {
      ull r = l + k;

      ull this_ans = inf;
      fore(m, l + 1, r) {
        this_ans = min(this_ans, dp[l][m] + dp[m][r] + sums[r] - sums[l]);
      }

      dp[l][r] = this_ans;
    }
  }

  ull ans = dp[0][n];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vu as(N);
  for (ull& a : as) {
    cin >> a;
  }

  ull ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
