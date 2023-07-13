// https://codeforces.com/contest/1829/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef unsigned int uint;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define MOD 1000000007

ull pow_mod(ull x, ull y) {
  ull res = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x) % MOD;
    }
    y = y / 2;
    x = (x * x) % MOD;
  }
  return res;
}

pair<vector<uint>, uint> parse1(void) {
  ull n;
  uint k;
  cin >> n >> k;
  vector<uint> as(n);

  fore(i, 0, n) {
    cin >> as[i];
  }

  return {as, k};
}

// For each number from 0 to 63, the numbers that have i bits in 1
vector<uint> with_bits[7];

void init() {
  fore(a, 0, 64) {
    with_bits[__builtin_popcount(a)].push_back(a);
  }
}

ull solve1(vector<uint> as, uint k) {
  ull n = as.size();

  vector<array<ull, 64>> dp(n + 1);

  fore(i, 1, n + 1) {
    uint a = as[i - 1];

    fore(j, 0, 64) {
      // Case not to use a
      dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;

      // Caso to use a
      dp[i][j & a] = (dp[i][j & a] + dp[i - 1][j]) % MOD;
    }

    // Case to start with a
    dp[i][a] = (dp[i][a] + 1) % MOD;
  }

  ull ans = 0;
  for (uint i : with_bits[k]) {
    ans = (ans + dp[n][i]) % MOD;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [as, k] = parse1();
    cout << solve1(as, k) << "\n";
  }

  return EXIT_SUCCESS;
}