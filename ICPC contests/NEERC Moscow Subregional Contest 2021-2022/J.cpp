// https://codeforces.com/gym/104848/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ull> du;
typedef vector<du> vdu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;
const ld eps = 1e-7;


ld solve(ull k, ull s, const vector<vu>& Fss, const vu& Qs, const vector<vu>& Pss) {
  ull n = Fss.size();

  vector<vd> dp(k + 1, vd(n, 0.0));

  dp[k][s] = 1.0;

  for (ull t = k - 1; t < k; t--) {

    vdu next_pis(n);
    fore(i, 0, n) {
      next_pis[i] = {dp[t + 1][i], i};
    }
    sort(next_pis.rbegin(), next_pis.rend());

    fore(i, 0, n) {
      ld ans = 0.0;
      ull j = 0;
      for (auto [p, i_] : next_pis) {
        ull F = Fss[i][i_];
        fore(_, 0, F) {
          ans += p * (ld)Pss[i][j] / (ld)Qs[i];
          j++;
        }
      }

      dp[t][i] = ans;
    }
  }

  return dp[0][0];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, k, s;
  cin >> n >> k >> s;
  s--;
  vector<vu> Fss(n, vu(n)), Pss(n);
  vu Qs(n);
  fore(i, 0, n) {
    ull sum_Fsi = 0;
    for (ull& F : Fss[i]) {
      cin >> F;
      sum_Fsi += F;
    }
    cin >> Qs[i];
    Pss[i] = vu(sum_Fsi);
    for (ull& P : Pss[i]) {
      cin >> P;
    }
  }

  fore(i, 0, n) {
    sort(Pss[i].rbegin(), Pss[i].rend());
  }

  auto ans = solve(k, s, Fss, Qs, Pss);
  cout << setprecision(12);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
