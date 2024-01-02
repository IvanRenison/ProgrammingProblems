// https://codeforces.com/contest/1917/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

#define MAXN 2000

bool solve1(ull d, vu ls) {
  ull n = ls.size();

  sort(ls.begin(), ls.end());

  if (ls[n - 1] + ls[n - 2] > d) {
    return false;
  }

  vector<bitset<MAXN + 1>> dp(d + 1);

  dp[0][0] = true;

  fore(i, 0, n) {
    ull l = ls[i];

    vector<bitset<MAXN + 1>> new_dp = dp;

    fore(j, l, d + 1) {
      if (dp[j - l][j - l]) {
        new_dp[j] |= dp[j - l] | (dp[j - l] << l);
      }
    }

    dp = new_dp;
  }

  if (!dp[d][d]) {
    return false;
  }

  if (dp[d][ls[n - 1]]) {
    return true;
  }

  fore(j, ls[n - 1], d - ls[n - 1] + 1) {
    if (dp[d][j]) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, d;
    cin >> n >> d;
    vu ls(n);
    for (ull& l : ls) {
      cin >> l;
    }

    if (solve1(d, ls)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
