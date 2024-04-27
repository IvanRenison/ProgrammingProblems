// https://codeforces.com/gym/105053/problem/B

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long double ld;
typedef vector<ld> vd;
typedef tuple<ld, ull, ull, ld, ull, ull> duuduu;
typedef vector<duuduu> vduuduu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ld eps = 1e-10;

ld solve(ull T, ull S, const vduuduu& levels) {
  ull N = levels.size();

  auto tryWith = [&](ld e_ans) -> bool {
    vector<vd> dp(N + 1, vd(T - S + 1));

    for (ull i = N - 1; i < N; i--) {
      fore(t, S, T) {
        auto [p0, G0, B0, p1, G1, B1] = levels[i];

        ld e_good_0 = t + G0 < T ? min(e_ans, (ld)G0 + dp[i + 1][t + G0 - S]) : e_ans;
        ld e_bad_0 = t + B0 < T ? min(e_ans, (ld)B0 + dp[i + 1][t + B0 - S]) : e_ans;
        ld e_good_1 = t + G1 < T ? min(e_ans, (ld)G1 + dp[i + 1][t + G1 - S]) : e_ans;
        ld e_bad_1 = t + B1 < T ? min(e_ans, (ld)B1 + dp[i + 1][t + B1 - S]) : e_ans;

        ld e0 = p0 * e_good_0 + (1.0 - p0) * e_bad_0;
        ld e1 = p1 * e_good_1 + (1.0 - p1) * e_bad_1;

        dp[i][t - S] = min(e0, e1);
      }
    }

    ld ans = (ld)S + dp[0][S - S];

    return ans < e_ans;
  };

  ld l = 0.0, r = 1e18;

  fore(_, 0, 100) {
    ld m = (l + r) / 2.0;
    if (tryWith(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, T, S;
  cin >> N >> T >> S;
  vduuduu levels(N);
  for (auto& [p0, G0, B0, p1, G1, B1] : levels) {
    ull P0, P1;
    cin >> P0 >> G0 >> B0 >> P1 >> G1 >> B1;
    p0 = P0/100.0, p1 = P1/100.0;
  }

  ld ans = solve(T, S, levels);
  cout << setprecision(10);
  cout << (long double)ans << '\n';

  return EXIT_SUCCESS;
}
