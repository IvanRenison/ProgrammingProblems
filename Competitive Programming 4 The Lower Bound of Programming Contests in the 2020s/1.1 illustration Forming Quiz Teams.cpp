// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1852
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



double solve1(vii coords) {
  ull N = coords.size() / 2;

  vector<vector<double>> dists(2 * N, vector<double>(2 * N, 0.0));
  fore(i, 0, 2*N) {
    auto [xi, yi] = coords[i];
    fore(j, i + 1, 2*N) {
      auto [xj, yj] = coords[j];
      dists[i][j] = dists[j][i] = hypot(xi - xj, yi - yj);
    }
  }

  vector<double> dp(1 << (2*N), 1e30);
  dp[0] = 0.0;

  fore(x, 1, 1 << (2*N)) {
    if (__builtin_popcountll(x) % 2 == 0) {
      fore(i, 0, 2*N) if ((x & (1 << i)) != 0) {
        fore(j, i+1, 2*N) if ((x & (1 << j)) != 0) {
          dp[x] = min(dp[x], dp[x ^ (1 << i) ^ (1 << j)] + dists[i][j]);
        }
      }
    }
  }

  return dp[(1 << (2*N)) - 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << setprecision(2) << fixed;

  for(ull i = 0;; i++) {

    ull N;
    cin >> N;
    if (N == 0) {
      break;
    }

    vii coords(2 * N);
    for(auto& [x, y] : coords) {
      string s;
      cin >> s >> x >> y;
    }

    auto ans = solve1(coords);
    cout << "Case " << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
