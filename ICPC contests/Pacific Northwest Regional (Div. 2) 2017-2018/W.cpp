// https://codeforces.com/gym/101652

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
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


ull solve(vector<vector<char>> mat) {
  ull m = mat.size(), n = mat[0].size();

  vector<ull> lasts_B(n, 0), firsts_R(n, m + 1);


  fore(j, 0, n) {
    fore(i, 0, m) {
      if (mat[i][j] == 'B') {
        lasts_B[j] = i + 1;
      }
    }

    fore(i, 0, m) {
      if (mat[i][j] == 'R') {
        firsts_R[j] = i + 1;
        break;
      }
    }

    if (lasts_B[j] > firsts_R[j]) {
      return 0;
    }
  }

  vector<vector<ull>> dp(m + 1, vector<ull>(n));

  fore(i, lasts_B[0], firsts_R[0]) {
    dp[i][0] = 1;
  }

  fore(j, 1, n) {
    ull sum_prev = 0;
    fore(i, lasts_B[j], m + 1) {
      sum_prev += dp[i][j - 1];
    }
    fore(i, lasts_B[j], firsts_R[j]) {
      dp[i][j] = sum_prev;
      sum_prev -= dp[i][j - 1];
    }
  }

  ull ans = 0;
  fore(i, 0, m + 1) {
    ans += dp[i][n - 1];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull m, n;
  cin >> m >> n;
  vector<vector<char>> mat(m, vector<char>(n));
  for(auto& mat_i : mat) {
    for(char& mat_ij : mat_i) {
      cin >> mat_ij;
    }
  }

  auto ans = solve(mat);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
