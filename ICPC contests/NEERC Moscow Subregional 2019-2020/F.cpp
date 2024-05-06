// https://codeforces.com/gym/104847/problem/F

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
typedef pair<ull, char> uc;
typedef vector<uc> vuc;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

/*
  a → Entrance/exit
  b → Road
*/
ull solve1(ull a, ull b, vuc& xs) {
  ull n = xs.size();

  sort(all(xs));

/*   fore(i, 0, n) {
    cerr << xs[i].second << ' ' << xs[i].first << '\n';
  }
  cerr << '\n'; */

  vector<vu> dp(n, vu(4, inf));
  // dp[i][0bet] = min cost right after i, if !e we can have new cars unidentified, if !t we can have exited cars unidentified

  dp[0][0b00] = dp[0][0b01] = 0;
  dp[0][0b10] = dp[0][0b11] = min(a, b);
  fore(i, 0, n - 1) {

    // Add a gate in the entrance/exit
    ull y = 1 << (xs[i + 1].second == 'E');
    fore(x, 0, 4) {
      dp[i + 1][x] = min(dp[i + 1][x], dp[i][x] + a);
    }

    // Add a gate before the entrance/exit
    fore(x, 0, 4) {
      dp[i + 1][y ^ 0b11] = min(dp[i + 1][y ^ 0b11], dp[i][x] + b);
    }

    // Add a gate after the entrance/exit
    fore(x, 0, 4) {
      dp[i + 1][0b00] = min(dp[i + 1][0b00], dp[i][x | y] + b);
    }

    // Don't add gate
    if (xs[i + 1].second == 'E') {
      dp[i + 1][0b00] = min(dp[i + 1][0b00], dp[i][0b10]);
      dp[i + 1][0b01] = min(dp[i + 1][0b01], dp[i][0b11]);
    } else {
      dp[i + 1][0b10] = min(dp[i + 1][0b10], dp[i][0b11]);
    }
  }

  ull ans = min({
    dp[n - 1][0b10],
    dp[n - 1][0b11],
    dp[n - 1][0b01],
    dp[n - 1][0b00]
  });

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, L, a, b;
    cin >> n >> L >> a >> b;

    vuc xs(n);
    for (auto& [x, c] : xs) {
      cin >> c >> x;
    }


    auto ans = solve1(a, b, xs);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
