// https://codeforces.com/group/4zVk9dZl6Q/contest/390850/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define INF (1ULL << 40)

ull solve(vector<ull> as, vector<ull> bs, vector<ull> cs) {
  ull n = as.size();

  vector<array<ull, 4>> dp(n);

  dp[0][0b00] = as[0];
  dp[0][0b01] = bs[0];
  dp[0][0b10] = 0;
  dp[0][0b11] = 0;

  fore(i, 1, n) {
    dp[i][0b00] = as[i] + max(dp[i - 1][0b01], dp[i - 1][0b11]);
    dp[i][0b01] = bs[i] + max(dp[i - 1][0b01], dp[i - 1][0b11]);
    dp[i][0b10] = bs[i] + max(dp[i - 1][0b00], dp[i - 1][0b10]);
    dp[i][0b11] = cs[i] + max(dp[i - 1][0b00], dp[i - 1][0b10]);
  }

  return max(dp[n - 1][0b00], dp[n - 1][0b10]);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vector<ull> as(n), bs(n), cs(n);
  for (ull& a : as) {
    cin >> a;
  }
  for (ull& b : bs) {
    cin >> b;
  }
  for (ull& c : cs) {
    cin >> c;
  }

  cout << solve(as, bs, cs) << '\n';

  return EXIT_SUCCESS;
}
