// https://codeforces.com/contest/1625/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

ull solve(ull l, ull k, vu ds, vu as) {
  ull n = ds.size();

  if (n == 1) {
    return as[0] * l;
  }

  vector<vector<vu>> dp(n, vector<vu>(n, vu(2)));
  // dp[i][j][r] = min time starting from sign i with speed of sign j removing at most r signs

  ull last_dist = l - ds.back();
  fore(j, 0, n) {
    dp.back()[j][0] = as.back() * last_dist;
  }

  { // r = 0
    for (ull i = n - 2; i > 0; i--) {
      ull dist = ds[i + 1] - ds[i];
      fore(j, 0, i + 1) {
        dp[i][j][0] = as[i] * dist + dp[i + 1][i][0];
      }
    }
    // i = 0
    ull dist = ds[1] - ds[0];
    dp[0][0][0] = as[0] * dist + dp[1][0][0];
  }
  fore(r, 1, k + 1) {
    fore(j, 0, n) {
      dp.back()[j][r % 2] = min(as[j], as.back()) * last_dist;
    }
    for (ull i = n - 2; i > 0; i--) {
      ull dist = ds[i + 1] - ds[i];
      fore(j, 0, i + 1) {
        // removing i
        ull t0 = as[j] * dist + dp[i + 1][j][(r - 1) % 2];

        // Not removing i
        ull t1 = as[i] * dist + dp[i + 1][i][r % 2];

        dp[i][j][r % 2] = min(t0, t1);
      }
    }
    if (n > 1) {
      ull dist = ds[1] - ds[0];
      dp[0][0][r % 2] = as[0] * dist + dp[1][0][r % 2];
    }
  }

  ull ans = dp[0][0][k % 2];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, l, k;
  cin >> n >> l >> k;
  vu ds(n), as(n);
  for (ull& d : ds) {
    cin >> d;
  }
  for (ull& a : as) {
    cin >> a;
  }

  auto ans = solve(l, k, ds, as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
