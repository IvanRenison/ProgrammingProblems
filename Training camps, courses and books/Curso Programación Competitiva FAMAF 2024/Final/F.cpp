// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/F

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef vector<ll> vi;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

ll solve(const vi& as) {
  uint n = as.size();

  vector<vi> dp(n + 1, vi(2));
  // dp[i][b] = max points using the first i pockemons, if b the last has to by positibe else negative
  dp[0][true] = -1e12;

  fore(i, 0, n) {
    ll a = as[i];
    dp[i + 1][false] = max(dp[i][false], dp[i][true] - a);
    dp[i + 1][true] = max(dp[i][true], dp[i][false] + a);
  }

  return dp[n][true];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n, z;
    cin >> n >> z;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    ll ans = solve(as);
    cout << ans << '\n';
  }
}
