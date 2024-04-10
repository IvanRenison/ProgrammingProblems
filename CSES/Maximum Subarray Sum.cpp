// https://cses.fi/problemset/task/1643

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ll inf = 1ll << 60;

ll solve(const vi& as) {
  ull n = as.size();

  vi as_sums(n + 1);
  fore(i, 0, n) {
    as_sums[i + 1] = as_sums[i] + as[i];
  }

  ll min_sum = 0;

  ll ans = -inf;

  fore(i, 1, n + 1) {
    ll this_ans = as_sums[i] - min_sum;
    ans = max(ans, this_ans);

    min_sum = min(min_sum, as_sums[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  ll ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
