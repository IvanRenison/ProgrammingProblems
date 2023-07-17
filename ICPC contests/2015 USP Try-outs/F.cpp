// https://codeforces.com/gym/101047/problem/F
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool solve1(ull H, ull K, vector<pair<ull, ull>>& xys) {
  ull N = xys.size();
  if (K == N) {
    return true;
  }
  vector<pair<ull, ull>> pos, neg;
  for (auto [x, y] : xys) {
    if (x <= y) {
      pos.push_back({x, y});
    } else {
      neg.push_back({x, y});
    }
  }

  sort(pos.begin(), pos.end());

  for (auto [x, y] : pos) {
    if (x >= H) {
      if (K > 0) {
        K--;
      } else {
        return false;
      }
    } else {
      H += y - x;
    }
  }

  // Para x > y order por y decreciente
  // dp[i][k] = máxima vida para matar a los primeros i monstruos y que queden k hechizos

  sort(neg.begin(), neg.end(), [&](pair<ull, ull> p0, pair<ull, ull> p1) {
    auto [x0, y0] = p0;
    auto [x1, y1] = p1;
    return y0 > y1 || (y0 == y1 && x0 <= x1);
  });

  ull n_neg = neg.size();

  vector<vector<ull>> dp(n_neg + 1, vector<ull>(K + 1, 0));
  dp[0] = vector<ull>(K + 1, H);

  fore(i, 0, n_neg) {
    auto [x, y] = neg[i];
    fore(k, 0, K) {
      if (dp[i][k] <= x) {
        dp[i + 1][k] = dp[i][k + 1];
      } else {
        dp[i + 1][k] = max(dp[i][k + 1], dp[i][k] - x + y);
      }
    }
    // k == K
    if (dp[i][K] <= x) {
      dp[i + 1][K] = 0;
    } else {
      dp[i + 1][K] = dp[i][K] - x + y;
    }
  }

  return dp[n_neg][0] > 0;
}

int main() {
  FIN;

  ull T;
  cin >> T;
  while (T--) {
    ull N, H, K;
    cin >> N >> H >> K;
    vector<pair<ull, ull>> xys(N);
    for (auto& [x, y] : xys) {
      cin >> x >> y;
    }

    if (solve1(H, K, xys)) {
      //assert(slowSolve(H, K, xys));
      cout << "Y\n";
    } else {
      //assert(!slowSolve(H, K, xys));
      cout << "N\n";
    }
  }

  return 0;
}