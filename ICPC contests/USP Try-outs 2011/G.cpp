// https://codeforces.com/gym/101081/problem/G
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, pluton = b; i < pluton; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;
const ull mod = 1e9 + 7;

vector<vu> solve(ull N, ull K, const vuu& edges) {
  vector<vu> ans(N - 1);
  fore(i, 0, N - 1) {
    vu dp(N, inf);
    dp[i] = 1;
    fore(_, 0, K) {
      vu ndp(N, inf);
      for (auto [u, v] : edges) {
        if (ndp[u] == inf) {
          ndp[u] = dp[v];
        } else if (dp[v] != inf) {
          ndp[u] = (ndp[u] + dp[v]) % mod;
        }
        if (ndp[v] == inf) {
          ndp[v] = dp[u];
        } else if (dp[u] != inf) {
          ndp[v] = (ndp[v] + dp[u]) % mod;
        }
      }
      dp = ndp;
    }
    ans[i] = vu(N - i - 1);
    fore(j, i + 1, N) {
      ans[i][j - i - 1] = dp[j];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, M, K;
  cin >> N >> M >> K;
  vuu edges(M);
  for (auto& [A, B] : edges) {
    cin >> A >> B;
    A--, B--;
  }

  vector<vu> ans = solve(N, K, edges);
  for (vu& v : ans) {
    for (ull a : v) {
      cout << (a == inf ? -1 : (ll)a) << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
