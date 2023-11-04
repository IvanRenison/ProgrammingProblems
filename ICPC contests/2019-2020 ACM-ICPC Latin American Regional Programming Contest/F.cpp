// https://codeforces.com/gym/102428

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

const ll mod = 1e9 + 7; // change to something else

/*
  Compute ∑ (k ∈ [0,…,j) as[k]*(j-k))
*/
struct RangeSumProd {
  vu as;
  vu sums, prods;

  RangeSumProd() {}
  RangeSumProd(const vu& as) : as(as) {
    ull N = as.size();
    sums = vu(N + 1);
    fore(i, 0, as.size()) {
      sums[i + 1] = (sums[i] + as[i]) % mod;
    }
    prods = vu(N + 1);
    fore(i, 0, N) {
      prods[i + 1] = (prods[i] + sums[i] + as[i]) % mod;
    }
  }
  ull query(ull j) {
    return prods[j];
  }
};




ull solve(ull S, ull B) {
  vector<vector<ull>> dp(B + 1, vector<ull>(S + 1));
  vector<RangeSumProd> rsumprods(B + 1);
  // dp[j][i] = cantidad de ancho i con j bloques

  dp[0][0] = 1;
  fore(j, 1, B + 1) {
    rsumprods[j-1] = RangeSumProd(dp[j-1]);
    dp[j][1] = 1;

    fore(i, 2, min(j + 1, S + 1)) {
  /*     ull this_ans = dp[j - i][0];
      fore(i2, 1, min(i + 1, j - i + 1)) {
        this_ans = (this_ans + dp[j - i][i2] * (i - i2 + 1)) % mod;
      } */

      ull this_ans = rsumprods[j - i].query(i + 1);
      this_ans -= dp[j - i][0] * (i + 1);
      this_ans += dp[j - i][0];
      this_ans %= mod;

      dp[j][i] = this_ans;
    }
  }

  return dp[B][S];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull S, B;
  cin >> S >> B;

  auto ans = solve(S, B);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
