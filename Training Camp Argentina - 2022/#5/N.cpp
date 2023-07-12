// https://codeforces.com/group/4zVk9dZl6Q/contest/391178/problem/N
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i, a, b) for (ull i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((ull)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define MOD ull(1e9 + 7)

ull solve(ull n, ull k, ull d) {
  vector<array<ull, 2>> dp(n + 1);
  fore(i, 1, d) {
    if (i <= n) {
      dp[i][0] = 1;
    }
  }
  fore(i, d, k + 1) {
    if (i <= n) {
      dp[i][1] = 1;
    }
  }

  ull count = dp[n][1];

  while (true) {
    vector<array<ull, 2>> next_dp(n + 1);
    fore(i, 1, k + 1) {
      if (i <= n) {
        fore(j, 1, d) {
          if (i + j <= n) {
            next_dp[i + j][0] = (next_dp[i + j][0] + dp[i][0]) % MOD;
          } else {
            break;
          }
        }
        fore(j, d, k + 1) {
          if (i + j <= n) {
            next_dp[i + j][1] = (next_dp[i + j][1] + dp[i][0]) % MOD;
          } else {
            break;
          }
        }
      } else {
        break;
      }
    }
    fore(i, 1, k + 1) {
      if (i <= n) {
        fore(j, 1, k + 1) {
          if (i + j <= n) {
            next_dp[i + j][1] = (next_dp[i + j][1] + dp[i][1]) % MOD;
          } else {
            break;
          }
        }
      } else {
        break;
      }
    }

    count = (count + next_dp[n][1]) % MOD;
    dp = next_dp;

    bool found_non_0 = false;
    fore(i, 0, n) {
      if (dp[i][0] != 0 || dp[i][1] != 0) {
        found_non_0 = true;
      }
    }

    if (!found_non_0) {
      return count;
    }
  }
}

int main() {
  FIN;

  ull n, k, d;
  cin >> n >> k >> d;

  cout << solve(n, k, d) << '\n';

  return 0;
}