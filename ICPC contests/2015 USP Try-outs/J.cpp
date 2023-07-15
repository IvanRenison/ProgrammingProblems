#include <bits/stdc++.h>
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// Hacer dp de tamaño N+1 × M+1
// agregando un valor extra de costo acumulado para la transición aleatoria
// Llenar la dp al revés

double solve1(double K, string a, string b) {
  ull N = a.size(), M = b.size();

  vector<vector<pair<double, double>>> dp(
      N + 1, vector<pair<double, double>>(M + 1, {0.0, 0.0})
  );

  for (ull i = N - 1; i < N; i--) {
    dp[i][M].first =
        min(1.0 + dp[i + 1][M].first,
            K + dp[i + 1][M].second / ((double)(N - i)));
    dp[i][M].second = dp[i][M].first + dp[i + 1][M].second;
  }
  for (ull j = M - 1; j < M; j--) {
    dp[N][j].first =
        min(1.0 + dp[N][j + 1].first,
            K + dp[N][j + 1].second / ((double)(M - j)));
    dp[N][j].second = dp[N][j].first + dp[N][j + 1].second;
  }

  for (ull i = N - 1; i < N; i--) {
    for (ull j = M - 1; j < M; j--) {
      if (a[i] == b[j]) {
        dp[i][j].first = dp[i + 1][j + 1].first;
      } else {
        dp[i][j].first =
            min(1.0 + dp[i + 1][j].first, 1.0 + dp[i][j + 1].first);

        dp[i][j].first =
            min(dp[i][j].first,
                K + dp[i + 1][j + 1].second / ((double)((N - i) * (M - j))));
      }
      dp[i][j].second = dp[i][j].first + dp[i + 1][j].second +
                        dp[i][j + 1].second - dp[i + 1][j + 1].second;
    }
  }

  return dp[0][0].first;
}

int main() {
  FIN;

  cout << setprecision(8);

  ull T;
  cin >> T;
  while (T--) {
    ull N, M;
    double K;
    cin >> N >> M >> K;
    string a, b;
    cin >> a >> b;

    auto x = solve1(K, a, b);
    cout << x << "\n";
  }

  return 0;
}
