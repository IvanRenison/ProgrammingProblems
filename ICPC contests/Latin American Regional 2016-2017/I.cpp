// https://matcomgrader.com/problem/9287/internet-trouble
#include "bits/stdc++.h"
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

vi solve(ll B, ll C, vi& Hs) {
  ll N = Hs.size();

  vi sums_up(N + 1), i_sums(N + 1), sums(N + 1), sums_down(N + 1);
  fore(i, 0, N) {
    sums_up[i + 1] = sums_up[i] + Hs[i] * i;
    sums[i + 1] = sums[i] + Hs[i];
    i_sums[i + 1] = i_sums[i] + i;
    sums_down[i + 1] = sums_down[i] + Hs[i] * (N - 1 - i);
  }

  vector<vi> blocks(N, vi(N + 1));
  fore(i, 0, N) {
    fore(j, i + 2, N + 1) {

      ll center = lower_bound(ALL(sums), (sums[i] + sums[j]) / 2) - sums.begin();

      ll ans = 1ll << 60;
      fore(c, center - 1, center + 2) {
        if (i <= c && c < j) {
          ll this_ans = (sums_down[c] - sums_down[i] - (sums[c] - sums[i]) * (N - 1 - c))
            + (sums_up[j] - sums_up[c] - (sums[j] - sums[c]) * c);
          ans = min(ans, this_ans);
        }
      }
      blocks[i][j] = ans;
    }
  }

  vector<vi> dp(N + 1, vi(N + 1)); // dp[K][i] = min partition of 0…i-1 into K blocks

  fore(i, 1, N + 1) {
    dp[1][i] = blocks[0][i];
  }
  fore(K, 2, N + 1) {

    function<void(ll,ll,ll,ll)> calc = [&](ll l, ll r, ll LO, ll HI) {
      ll m = (l + r) / 2;
      ll j_min = LO, min_val = dp[K - 1][LO] + blocks[LO][m];
      fore(j, LO + 1, min(m, HI)) {
        ll val = dp[K - 1][j] + blocks[j][m];
        if (val < min_val) {
          min_val = val;
          j_min = j;
        }
      }

      dp[K][m] = min_val;
      if (l < m) calc(l, m, LO, j_min + 1);
      if (m + 1 < r) calc(m + 1, r, j_min, HI);
    };

    calc(0, N + 1, K - 1, N);
  }

  vi ans(N);
  fore(K, 1, N + 1) {
    ans[K - 1] = dp[K][N] * C + K * B;
  }

  return ans;
}

vi force(ll B, ll C, vi& Hs) {
  ll N = Hs.size();

  vi ans(N, 1ll << 60);

  fore(x, 1, 1 << N) {
    ll cost = 0;
    fore(i, 0, N) {
      ll cost_i = 1ll << 60;
      fore(j, 0, N) {
        if (x & (1 << j)) {
          ll this_cost = abs(i - j) * Hs[i];
          cost_i = min(cost_i, this_cost);
        }
      }
      cost += cost_i;
    }

    ll K = __builtin_popcount(x);
    ans[K - 1] = min(ans[K - 1], cost * C + K * B);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
#ifndef TEST
  ll N, B, C;
  cin >> N >> B >> C;
  vi Hs(N);
  for (ll& H : Hs) {
    cin >> H;
  }
  vi ans = solve(B, C, Hs);
  for (ll a : ans) {
    cout << a << ' ';
  }
  cout << '\n';
#else
  fore(_, 0, 1000) {
    ll N = rand() % 18 + 1;
    ll B = 0; //rand() % 10 + 1;
    vi Hs(N);
    fore(i, 0, N) {
      Hs[i] = rand() % 10 + 1;
    }
    vi ans = solve(B, 1, Hs);
    vi ansf = force(B, 1, Hs);
    if (ans != ansf) {
      cerr << "ERROR\n";
      cerr << N << ' ' << B << " 1\n";
      for (ll H : Hs) {
        cerr << H << ' ';
      }
      cerr << "\nans: ";
      for (ll a : ans) {
        cerr << a << ' ';
      }
      cerr << "\nansf: ";
      for (ll a : ansf) {
        cerr << a << ' ';
      }
      cerr << endl;
      return 1;
    }
  }
#endif
}
