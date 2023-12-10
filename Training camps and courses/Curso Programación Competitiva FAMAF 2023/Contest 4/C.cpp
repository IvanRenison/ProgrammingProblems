// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> as(n);

  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

ull solve1(vector<ull> as) {
  ull n = as.size();

  vector<ull> dp(n);

  for (ull i = n - 1; i < n; i--) {
    if (i + as[i] < n) {
      dp[i] = as[i] + dp[i + as[i]];
    } else {
      dp[i] = as[i];
    }
  }

  ull m = dp[0];

  fore(i, 1, n) {
    m = max(m, dp[i]);
  }

  return m;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
