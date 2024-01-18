// https://codeforces.com/gym/100861
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define all(x) x.begin(), x.end()
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;

const ull inf = 1ull << 60;
#define MMAX 301

ull solve(ull M, vu& xs) {
  ull N = xs.size();

  vector<vector<pair<ull, bitset<MMAX>>>> dp(N, vector<pair<ull, bitset<MMAX>>>(N + 1));
  // dp[i][j] = min days for making equal [i, i + j) and set of posible colors

  //dp[N - 1][1] = {0, {xs[N - 1]}};
  dp[N - 1][1].second.set(xs[N - 1]);


  for (ull i = N - 2; i < N; i--) {
    //dp[i][1] = {0, {xs[i]}};
    dp[i][1].second.set(xs[i]);
    if (xs[i] != xs[i + 1]) {
      //dp[i][2] = {1, {xs[i], xs[i + 1]}};
      dp[i][2].first = 1;
      dp[i][2].second.set(xs[i]);
      dp[i][2].second.set(xs[i + 1]);
    } else {
      //dp[i][2] = {0, {xs[i]}};
      dp[i][2].second.set(xs[i]);
    }
    fore(j, 3, N - i + 1) {
      ull ans = inf;
      bitset<MMAX> ans_set = {};
      fore(k, 1, j) {
        ull this_ans = dp[i][k].first + dp[i + k][j - k].first;
        bitset<MMAX> this_set = dp[i][k].second & dp[i + k][j - k].second;
        /* set_intersection(
            all(dp[i][k].second), all(dp[i + k][j - k].second),
            inserter(this_set, this_set.begin())
        ); */
        if (this_set.count() == 0) {
          this_ans++;
          this_set = dp[i][k].second | dp[i + k][j - k].second;
        }
        if (this_ans < ans) {
          ans = this_ans;
          ans_set = this_set;
        }
      }
      dp[i][j] = {ans, ans_set};
    }
  }

  return dp[0][N].first;
}

int main() {
  FIN;

  ull N, M;
  cin >> N >> M;
  vu xs(N);
  for (ull& x : xs) {
    cin >> x;
    x--;
  }

  ull ans = solve(M, xs);
  cout << ans << '\n';

  return 0;
}