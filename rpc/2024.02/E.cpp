// https://redprogramacioncompetitiva.com/contests/2024/02/

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


ull solve(const vuuuu& exams) {
  ull n = exams.size();

  vector<vi> dp(n + 1, vi(n + 1, -1));
  // dp[i + 1][x] = máximo tiempo libre si tengo que aprobar x exámenes antes de ei
  dp[0][0] = 0;
  fore(i, 0, n) {
    auto [s, p, e, a] = exams[i];

    ull dt = i == 0 ? s : s - get<2>(exams[i - 1]);

    dp[i + 1][0] = dp[i][0] + dt;
    fore(x, 1, i + 2) {
      // No hacer el i
      if (dp[i][x] >= 0) {
        dp[i + 1][x] = dp[i][x] + dt;
      }

      // Hacer el i
      if (dp[i][x - 1] >= 0 && dp[i][x - 1] + dt >= a) {
        dp[i + 1][x] = max(dp[i + 1][x], (ll)(dp[i][x - 1] + dt - a + e - p));
      }
    }
  }

  ull ans = 0;

  for (ull x = n; x > 0; x--) {
    if (dp[n][x] >= 0) {
      ans = x;
      break;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vuuuu exams(n);
  for (auto& [s, p, e, a] : exams) {
    cin >> s >> p >> e >> a;
  }

  auto ans = solve(exams);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
