// https://codeforces.com/gym/106054/problem/L
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

const ll inf = 1ll << 60;

ll solve(ll G, vi& Ts) {
  ll N = Ts.size();

  ll lim_bar = 1;
  {
    ll sum = 1;
    while (sum <= N) {
      lim_bar++;
      sum += lim_bar;
    }
  }

  vi Ts_sums(N + 1);
  fore(i, 0, N) {
    Ts_sums[i + 1] = Ts_sums[i] + Ts[i];
  }

  auto sum = [&](ll i, ll j) -> ll {
    return Ts_sums[j] - Ts_sums[i];
  };


  vector<vi> dp(N + 1, vi(lim_bar));
  // dp[i][b] = máxima ganancia en los primeros i con el barco más grande puesto de tamaño menor o igual que b

  fore(i, 1, N + 1) fore(b, 1, min(i + 1, lim_bar)) {
    dp[i][b] = max({
      dp[i - 1][b],
      dp[i][b - 1],
      G + dp[i - b][b - 1] - sum(i - b, i)
    });
  }

  ll ans = dp[N][lim_bar - 1];

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, G;
  cin >> N >> G;
  vi Ts(N);
  for (ll& T : Ts) {
    cin >> T;
  }

  ll ans = solve(G, Ts);
  cout << ans << '\n';

}