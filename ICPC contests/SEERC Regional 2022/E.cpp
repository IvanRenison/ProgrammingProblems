// https://codeforces.com/gym/104114/problem/E
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

bool are_pair(ll x, ll y) {
  if (x > y) swap(x, y);
  return y % 2 && x + 1 == y;
}

ll solve(const vi& vc) {
  ll n = vc.size() / 2;

  vii vci(2 * n);
  fore(i, 0, 2 * n) {
    vci[i] = {vc[i], i};
  }
  sort(ALL(vci));

  vector<tuple<ll,ll,ll,ll,ll,ll>> forms6;
  {
    vi perm = {0, 1, 2, 3, 4, 5};
    do {
      forms6.push_back({perm[0], perm[1], perm[2], perm[3], perm[4], perm[5]});
    } while (next_permutation(ALL(perm)));
  }

  vi dp(n + 1, 1ll << 60);
  dp[0] = 0;
  fore(i, 0, n) {
    if (!are_pair(vci[2*i].second, vci[2*i+1].second)) {
      dp[i + 1] = dp[i] + abs(vci[2*i].first - vci[2*i+1].first);
    }
    if (i > 0) {
      vector<tuple<ll,ll,ll,ll>> forms4 = {
        {0, 2, 1, 3},{0, 3, 1, 2}
      };
      for (auto [i0, i1, j0, j1] : forms4) {
        if (!are_pair(vci[2*(i - 1) + i0].second, vci[2*(i - 1) + i1].second)
            && !are_pair(vci[2*(i - 1) + j0].second, vci[2*(i - 1) + j1].second)) {
          ll this_ans = dp[i - 1]
            + abs(vci[2*(i - 1) + i0].first - vci[2*(i - 1) + i1].first)
            + abs(vci[2*(i - 1) + j0].first - vci[2*(i - 1) + j1].first);
          dp[i + 1] = min(dp[i + 1], this_ans);
        }
      }
    }
    if (i > 1) {
      for (auto [i0, i1, j0, j1, k0, k1] : forms6) {
        if (!are_pair(vci[2*(i - 2) + i0].second, vci[2*(i - 2) + i1].second)
            && !are_pair(vci[2*(i - 2) + j0].second, vci[2*(i - 2) + j1].second)
            && !are_pair(vci[2*(i - 2) + k0].second, vci[2*(i - 2) + k1].second)) {
          ll this_ans = dp[i - 2]
            + abs(vci[2*(i - 2) + i0].first - vci[2*(i - 2) + i1].first)
            + abs(vci[2*(i - 2) + j0].first - vci[2*(i - 2) + j1].first)
            + abs(vci[2*(i - 2) + k0].first - vci[2*(i - 2) + k1].first);
          dp[i + 1] = min(dp[i + 1], this_ans);
        }
      }
    }
  }

  ll ans = dp[n];

  return ans;
}


ll force(const vi& vc) {
  ll n = vc.size() / 2;

  vi perm(2 * n);
  iota(ALL(perm), 0ll);

  ll ans = 1ll << 60;

  do {
    bool valid = true;
    fore(i, 0, n) {
      if (are_pair(perm[2*i], perm[2*i+1])) {
        valid = false;
        break;
      }
    }
    if (valid) {
      ll val = 0;
      fore(i, 0, n) {
        val += abs(vc[perm[2*i]] - vc[perm[2*i+1]]);
      }
      ans = min(ans, val);
    }

  } while (next_permutation(ALL(perm)));

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  ll n;
  cin >> n;
  vi vc(2 * n);
  for (ll& c : vc) {
    cin >> c;
  }
  cout << solve(vc) << '\n';
#else
  fore(_, 0, 10000) {
    ll n = rand() % 5 + 1;
    vi vc(2 * n);
    for (ll& c : vc) {
      c = rand() % 5;
    }
    ll ans = solve(vc);
    ll ansf = force(vc);
    if (ans != ansf) {
      cout << n << '\n';
      for (ll c : vc) {
        cout << c << ' ';
      }
      cout << '\n';
      cout << ans << ' ' << ansf << endl;
      return 1;
    }
    cout << _ << endl;
  }
#endif
}
