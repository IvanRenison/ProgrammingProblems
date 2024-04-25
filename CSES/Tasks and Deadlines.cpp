// https://cses.fi/problemset/task/1630

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

ll solve(vector<pair<ll, ll>>& ads) {
  sort(ads.begin(), ads.end(), [](pair<ll, ll> ad0, pair<ll, ll> ad1) {
    auto [a0, d0] = ad0;
    auto [a1, d1] = ad1;
    return a0 < a1 || (a0 == a1 && d0 > d1);
  });

  ull t = 0;

  ll ans = 0;

  for (auto [a, d] : ads) {
    t += a;
    ans += d - t;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vector<pair<ll, ll>> ads(n);
  for (auto& [a, b] : ads) {
    cin >> a >> b;
  }

  ll ans = solve(ads);
  cout << ans << '\n';


  return EXIT_SUCCESS;
}
