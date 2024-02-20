// https://codeforces.com/contest/1922/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;


ull solve1(ull x, const vu& as) {
  ull n = as.size();

  vector<vector<vector<vu>>> dp(n, vector<vector<vu>>(n + 1, vector<vu>(x, vu(2, inf))));
  // dp[b][i][j][k] = if b then min cost to make [i..j) equal k
  //                       else min cost to make [i..j) different to k

  fore(i, 0, n) {
    dp[i][i] = vector<vu>(x, vu(2, 0));
  }

  fore(l, 1, n + 1) {
    fore(i, 0, n - l + 1) {
      ull j = i + l;
      fore(k, 0, x) {
        if (l == 1) {
          dp[i][j][k][true] = as[i] != k;
          dp[i][j][k][false] = as[i] == k;
        } else {
          fore(l_, 1, l) {
            dp[i][j][k][true] = min(dp[i][j][k][true], dp[i][i + l_][k][true] + dp[i + l_][j][k][true]);
            dp[i][j][k][false] = min(dp[i][j][k][false], dp[i][i + l_][k][false] + dp[i + l_][j][k][false]);
          }
          if (as[j - 1] == k) {
            if (as[i] == k) {
              dp[i][j][k][true] = min(dp[i][j][k][true], dp[i + 1][j - 1][k][true]);
              dp[i][j][k][false] = min(dp[i][j][k][false], dp[i][j][k][true] + 1);
              fore(k_, 0, x) if (k_ != k) {
                dp[i][j][k][false] = min(dp[i][j][k][false], dp[i + 1][j - 1][k_][false] + 1);
              }
            } else {
              dp[i][j][k][true] = min(dp[i][j][k][true], dp[i][j - 1][k][true]);
              dp[i][j][k][false] = min(dp[i][j][k][false], dp[i + 1][j][k][false]);
              fore(k_, 0, x) {
                dp[i][j][k][false] = min(dp[i][j][k][false], dp[i][j - 1][k_][false] + 1);
                if (k_ != k) {
                  dp[i][j][k][false] = min(dp[i][j][k][false], dp[i + 1][j][k_][false] + 1);
                }
              }
            }
          } else {
            if (as[i] == k) {
              dp[i][j][k][true] = min(dp[i][j][k][true], dp[i + 1][j][k][true]);
              dp[i][j][k][false] = min(dp[i][j][k][false], dp[i][j - 1][k][false]);
              fore(k_, 0, x) {
                dp[i][j][k][false] = min(dp[i][j][k][false], dp[i + 1][j][k_][false] + 1);
                if (k_ != k) {
                  dp[i][j][k][false] = min(dp[i][j][k][false], dp[i][j - 1][k_][false] + 1);
                }
              }
            } else {
              dp[i][j][k][false] = min(dp[i][j][k][false], dp[i + 1][j - 1][k][false]);
              dp[i][j][k][true] = min(dp[i][j][k][true], dp[i][j][k][false] + 1);
            }
          }
        }
      }
    }
  }

  ull ans = inf;

  fore(k, 0, x) {
    ans = min(ans, dp[0][n][k][true]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, x;
    cin >> n >> x;
    vu as(n);
    fore(i, 0, n) {
      cin >> as[i];
      as[i]--;
    }

    auto ans = solve1(x, as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
