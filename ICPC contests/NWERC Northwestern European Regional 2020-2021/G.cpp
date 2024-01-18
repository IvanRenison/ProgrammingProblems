// https://codeforces.com/gym/103049/problem/G
#include <bits/stdc++.h>
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define ALL(x) x.begin(), x.end()
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long double ld;
typedef vector<ld> vd;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef pair<ll, ld> id;
typedef vector<id> vid;
typedef tuple<ll, ld, ll> idi;
typedef vector<idi> vidi;

const ld eps = 1e-8;

bool tryWith(ll n, ll r, const vidi& tpds, ld p00) {
  ll m = tpds.size();

  // Assume the total expected time is p00, return true if result is less

  vector<vd> dp(r + 1, vd(m + 1, p00));
  // dp[t][i] = Expected time if we arrive to trick i at time t
  // m trick is end

  fore(i, 0, r) {
    dp[i][m] = 0.0;
  }

  for (ll i = m - 1; i >= 0; i--) {
    auto [ti, p, d] = tpds[i];
    ll dt = i < m - 1 ? get<0>(tpds[i + 1]) - ti : n - ti;
    fore(t, 0, r) {
      ld good_time = t + dt < r ? dt + dp[t + dt][i + 1] : p00;
      ld bad_time = t + d + dt < r ? d + dt + dp[t + d + dt][i + 1] : p00;
      dp[t][i] = p * good_time + (1.0 - p) * min(p00, bad_time);
    }
  }

  ll t0 = get<0>(tpds[0]);

  ld ans = dp[t0][0] + t0;

  return ans < p00;
}

ld solve(ll n, ll r, const vidi& tpds) {

  ld min_t = get<1>(tpds.back());

  ld l = (ld)min_t, u = 1e10;
  while (l + eps < u) {
    ld m = (l + u) / 2.0;
    if (tryWith(n, r, tpds, m)) {
      u = m;
    } else {
      l = m;
    }
  }

  return u;
}

int main() {
  FIN;

  ll n, r, m;
  cin >> n >> r >> m;
  vidi tpds(m);
  for (auto& [t, p, d] : tpds) {
    cin >> t >> p >> d;
  }

  cout << setprecision(10);
  cout << solve(n, r, tpds) << '\n';

  return 0;
}
