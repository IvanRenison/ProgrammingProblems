// https://codeforces.com/gym/105321/problem/E

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
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef long long ll;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

ll floor_div(ll a, ll b) {
  assert(b > 0);
  if (a >= 0) {
    return a / b;
  } else {
    return (a - b + 1) / b;
  }
}

ull solve(ull P, vuuu& ABCs_) {
  vuuu ABCs;
  for (auto [A, B, C] : ABCs_) {
    if (B <= P) {
      ABCs.push_back({A, B, C});
    }
  }

  ull N = ABCs.size();

  sort(ALL(ABCs), [&](uuu x, uuu y) {
    if (x == y) {
      return false;
    }

    auto [Ax, Bx, Cx] = x;
    auto [Ay, By, Cy] = y;

    //cerr << "x: " << Ax << ' ' << Bx << ' ' << Cx << '\n';
    //cerr << "y: " << Ay << ' ' << By << ' ' << Cy << '\n';

    fore(p, 0, 10000) {
      ll xy = floor_div(floor_div(p - Bx, Ax) - By, Ay);
      ll yx = floor_div(floor_div(p - By, Ay) - Bx, Ax);
      if (xy > yx) {
        //cerr << "true\n" << endl;
        return true;
      } else if (xy < yx) {
        //cerr << "false\n" << endl;
        return false;
      }
    }

    //cerr << "false in end\n" << endl;
    return false;
  });

  vector<vu> dp(N + 1, vu(P + 1));
  // dp[i + 1][p] = max amount of damage in the first i having p of life

  fore(i, 0, N) {
    dp[i + 1] = dp[i];

    auto [A, B, C] = ABCs[i];
    fore(p, 0, P + 1) {
      if (p >= B) {
        ull np = (p - B) / A;
        dp[i + 1][np] = max(dp[i + 1][np], dp[i][p] + C);
      }
    }
  }

  ull ans = 0;
  fore(p, 0, P + 1) {
    ans = max(ans, dp[N][p]);
  }

  return ans;
}

ull force(ull P, vuuu ABCs) {
  ull N = ABCs.size();

  sort(ALL(ABCs));

  ull ans = 0;

  do {
    fore(x, 0, 1 << N) {
      ull p = P;
      ull this_ans = 0;
      fore(i, 0, N) {
        if (x & (1 << i)) {
          auto [A, B, C] = ABCs[i];
          if (p >= B) {
            p = (p - B) / A;
            this_ans += C;
          }
        }
      }

      ans = max(ans, this_ans);
    }
  } while (next_permutation(ALL(ABCs)));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull N, P;
  cin >> N >> P;
  vuuu ABCs(N);
  for (auto& [A, B, C] : ABCs) {
    cin >> A >> B >> C;
  }

  auto ans = solve(P, ABCs);
  cout << ans << '\n';
#else
  fore(_, 0, 10000) {
    ull N = rand() % 10 + 1;
    ull P = rand() % 10 + 1;
    vuuu ABCs(N);
    for (auto& [A, B, C] : ABCs) {
      A = rand() % 10 + 1;
      B = rand() % 10 + 1;
      C = rand() % 10 + 1;
    }

    ull ans = solve(P, ABCs);
    ull ansf = force(P, ABCs);
    if (ans != ansf) {
      cout << "ERROR" << '\n';
      cout << N << ' ' << P << '\n';
      for (auto [A, B, C] : ABCs) {
        cout << A << ' ' << B << ' ' << C << '\n';
      }
      cout << "SOLVE: " << ans << '\n';
      cout << "FORCE: " << ansf << '\n';
      return 1;
    }
  }
#endif
}
