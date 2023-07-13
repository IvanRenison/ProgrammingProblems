// https://codeforces.com/contest/1826/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

vector<ll> parse1(void) {
  ll n;
  cin >> n;

  vector<ll> bs(n);
  fore(i, 0, n) {
    cin >> bs[i];
  }

  return bs;
}

ll solve1(vector<ll> bs) {
  ll n = bs.size();

  vector<array<ll, 3>> dp(n + 1);

  dp[1][0] = bs[0];

  dp[2][0] = max(dp[1][0] - 1, bs[1]);
  dp[2][1] = bs[0] + bs[1] - 1;

  dp[3][0] = max(dp[2][0] - 1, bs[2]);
  dp[3][1] = max(dp[2][1] - 1, dp[2][0] + bs[2] - 1);
  dp[3][2] = bs[0] + bs[1] + bs[2] - 2;

  fore(i, 4, n + 1) {
    ll b = bs[i - 1];
    dp[i][0] = max(dp[i - 1][0] - 1, b);
    dp[i][1] = max(dp[i - 1][1] - 1, dp[i - 1][0] + b - 1);
    dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + b - 1);
  }

  return dp[n][2];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
