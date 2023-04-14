// https://codeforces.com/contest/433/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

ll solve(ll n, vector<ll> as) {
  ll m = as.size();

  ll ans = -1;

  set<ll> xs;
  map<ll, vector<ll>> bss;

  fore(i, 0, m) {
    ll a = as[i];
    xs.insert(a);

    if (i != 0) {
      bss[as[i - 1]].push_back(a);
    }
    if (i != m - 1) {
      bss[as[i + 1]].push_back(a);
    }
  }

  for (ll x : xs) {
    vector<ll> bs = bss[x];

    // Get median from bs
    sort(bs.begin(), bs.end());
    ll median = bs[bs.size() / 2];

    ll this_ans = 0;
    for (ll b : bs) {
      this_ans += abs(b - median) + abs(b - x);
    }

    if (ans == -1) {
      ans = this_ans;
    } else {
      ans = min(ans, this_ans);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n, m;
  cin >> n >> m;

  vector<ll> as(m);
  fore(i, 0, m) {
    cin >> as[i];
  }

  cout << solve(n, as) << "\n";

  return EXIT_SUCCESS;
}
