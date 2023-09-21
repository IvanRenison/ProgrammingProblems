// https://codeforces.com/contest/1870/problem/E

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

ull solve1(const vector<ull>& as) {
  ull n = as.size();

  vector<vector<bool>> dp(n + 1, vector<bool>(n + 1, false));

  fore(i, 0, n) {
    dp[i][0] = true;
  }

  vector<vu> mexes(n + 1, vu(n + 1, 0));
  fore(l, 0, n) {
    vector<bool> mexed(n + 1, false);
    ull mex = 0;
    fore(r, l, n) {
      ull a = as[r];
      mexed[a] = true;
      while (mexed[mex]) {
        mex++;
      }
      mexes[l][r] = mex;
    }
  }

  fore(l, 0, n) {
    vector<bool> mex_used(n + 1, false);
    mex_used[0] = true;
    fore(r, l, n) {
      ull mex = mexes[l][r];
      //assert(mex <= n);
      if (!mex_used[mex] && (l == r || (mexes[l+1][r] != mex && mexes[l][r-1] != mex))) {
        fore(j, 0, n + 1) {
          if (dp[l][j]) {
            //assert((j ^ mex) <= n);
            for(ull k = r + 1; k <= n && !dp[k][j ^ mex]; k++) {
              dp[k][j ^ mex] = true;
            }
          }
        }
        mex_used[mex] = true;
      }
    }
  }


  ull ans = 0;
  fore(j, 0, n + 1) {
    if (dp[n][j]) {
      ans = j;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<ull> as(n);
    fore(i, 0, n) {
      cin >> as[i];
    }

    auto ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
