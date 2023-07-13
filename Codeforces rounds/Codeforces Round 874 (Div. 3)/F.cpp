// https://codeforces.com/contest/1833/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MOD 1000000007

pair<vector<ull>, ull> parse1(void) {
  ull n, m;
  cin >> n >> m;

  vector<ull> as(n);
  fore(i, 0, n) {
    ull a;
    cin >> a;
    as[i] = a - 1;
  }

  return {as, m};
}

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

ull inverse_mod(ull x) {
  return pow_mod(x, MOD - 2);
}

ull div_mod(ull x, ull y) {
  return ((x % MOD) * (inverse_mod(y % MOD))) % MOD;
}

ull solve1(vector<ull> as, ull m) {
  map<ull, ull> amount_with_level;

  for (ull a : as) {
    amount_with_level[a]++;
  }

  ull n_levels = amount_with_level.size();

  vector<ull> levels = vector<ull>();
  levels.reserve(n_levels);
  for (auto [level, amount] : amount_with_level) {
    levels.push_back(level);
  }

  vector<ull> dp(n_levels, 0); // dp[i] = amount ending in level i

  ull ans = 0;

  ull i = 0;
  while (i + m <= n_levels) {
    bool valid_start = true;
    ull broke_index;
    ull start_amount = amount_with_level[levels[i]];
    fore(j, i + 1, i + m) {
      if (levels[j] != levels[j - 1] + 1) {
        valid_start = false;
        broke_index = j;
        break;
      }

      start_amount = (start_amount * amount_with_level[levels[j]]) % MOD;
    }

    if (!valid_start) {
      i = broke_index;
      continue;
    }

    ull j = i + m - 1;
    dp[j] = start_amount;

    ans = (ans + start_amount) % MOD;

    while (j + 1 < n_levels && levels[j + 1] == levels[j] + 1) {
      j++;
      dp[j] = div_mod(
          dp[j - 1] * amount_with_level[levels[j]],
          amount_with_level[levels[j - m]]
      );
      ans = (ans + dp[j]) % MOD;
    }

    i = j + 1;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [as, m] = parse1();
    auto ans = solve1(as, m);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
