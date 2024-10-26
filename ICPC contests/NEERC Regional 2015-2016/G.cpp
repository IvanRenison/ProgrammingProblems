// https://codeforces.com/gym/100851
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

const ll inf = 1ll << 60;

struct LCG {
  ll x0, a, b, c;
};

vii calc(LCG lcg) {

  auto [x, a, b, c] = lcg;

  vi vals(c, -1);
  for (ll i = 0; vals[x] == -1; i++) {
    vals[x] = i;
    x = (a * x + b) % c;
  }

  vii vs;
  fore(x, 0, c) {
    if (vals[x] != -1) {
      vs.push_back({x, vals[x]});
    }
  }

  return vs;
}

optional<pair<ll, vi>> solve(ll k, vector<LCG>& lcgs) {
  ll n = lcgs.size();
  vector<vii> vss(n);
  fore(i, 0, n) {
    vss[i] = calc(lcgs[i]);
  }

  ll val = 0;
  vi ans(n);
  ll best_diff = inf;
  ll best_diff_i = -1;
  ll best_diff_i_ans = -1;
  fore(i, 0, n) {
    val += vss[i].back().first;
    ans[i] = vss[i].back().second;
    for (ll a = vss[i].size() - 1; a--; ) {
      ll this_diff = vss[i].back().first - vss[i][a].first;
      if (this_diff % k != 0) {
        if (this_diff < best_diff) {
          best_diff = this_diff;
          best_diff_i = i;
          best_diff_i_ans = vss[i][a].second;
        }
      }
    }
  }

  if (val % k != 0) {
    return {{val, ans}};
  }
  if (best_diff == inf) {
    return {};
  }
  ans[best_diff_i] = best_diff_i_ans;
  val -= best_diff;
  return {{val, ans}};
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("generators.in", "r", stdin);
  freopen("generators.out", "w", stdout);
#endif

  ll n, k;
  cin >> n >> k;
  vector<LCG> lcgs(n);
  for (auto& [x0, a, b, c] : lcgs) {
    cin >> x0 >> a >> b >> c;
  }
  auto ans = solve(k, lcgs);
  if (ans) {
    auto [val, is] = *ans;
    cout << val << '\n';
    for (ll i : is) {
      cout << i << ' ';
    }
  } else {
    cout << -1;
  }
  cout << '\n';
}
