// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solve1(const array<vu, 2>& hss) {
  ull n = hss[0].size();

  array<vu, 2> dp = {vu(n + 1), vu(n + 1)};

  fore(i, 0, n) {
    fore(j, 0, 2) {
      dp[j][i + 1] = max(dp[j][i], dp[!j][i] + hss[j][i]);
    }
  }

  ull ans = max(dp[0][n], dp[1][n]);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  array<vu, 2> hss = {vu(n), vu(n)};
  for (ull& h : hss[0]) {
    cin >> h;
  }
  for (ull& h : hss[1]) {
    cin >> h;
  }

  auto ans = solve1(hss);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
