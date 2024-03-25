// https://codeforces.com/gym/102916/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

dd solve(vu& as) {
  ull n = as.size();

  vector<vd> dp(n + 1, vd(n + 1, 0.l));

  fore(i, 1, n + 1) {
    if ((n - i) % 2 == 0) {
      dp[i] = dp[i - 1];
      dp[i][i - 1] = 1.l;
    } else {
      dp[i][0] = dp[i - 1][0] * (ld)(i - 1) / (ld)(i);
      fore(j, 1, i + 1) {
        dp[i][j] = dp[i - 1][j - 1] * (ld)(j) / (ld)(i) + dp[i - 1][j] * (ld)(i - j - 1) / (ld)(i);
      }
    }
  }

  sort(ALL(as));

  ld fst = 0.l, total = 0.l;

  fore(j, 0, n) {
    fst += dp[n][j] * (ld)as[j];
    total += (ld)as[j];
  }

  return {fst, total - fst};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  auto [fst, snd] = solve(as);
  cout << setprecision(10) << fixed;
  cout << fst << ' ' << snd << '\n';

  return EXIT_SUCCESS;
}
