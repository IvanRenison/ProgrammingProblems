// https://cses.fi/problemset/task/1643

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;

ll solve(const vi& as) {
  ll ans = 0;
  ll sum = 0;
  for (ll a : as) {
    sum += a;
    ans = max(ans, sum);
    sum = max(sum, 0ll);
  }

  if (ans == 0) {
    ans = *max_element(as.begin(), as.end());
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
