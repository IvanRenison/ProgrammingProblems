// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve1(const vu& as) {
  uint n = as.size();

  vu dp(n + 1);
  for (uint i = n - 1; i < n; i--) {
    uint a = as[i];
    dp[i] = 1 + dp[i + 1];
    if (a <= n - i - 1) {
      dp[i] = min(dp[i], dp[i + a + 1]);
    }
  }

  return dp[0];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n;
    cin >> n;
    vu as(n);
    for (uint& a : as) {
      cin >> a;
    }

    uint ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
