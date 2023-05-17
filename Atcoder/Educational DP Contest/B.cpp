// https://atcoder.jp/contests/dp/tasks/dp_b

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

ll solve(vector<ll> hs, ll k) {
  ll n = hs.size();

  vector<ll> lasts(k + 1);
  lasts[0] = 0;

  fore(i, 1, n) {
    ll next = LLONG_MAX;

    fore(j, max(0LL, i - k), i) {
      next = min(next, lasts[j % (k + 1)] + abs(hs[i] - hs[j]));
    }

    lasts[i % (k + 1)] = next;
  }

  return lasts[(n - 1) % (k + 1)];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll N, K;
  cin >> N >> K;

  vector<ll> hs(N);
  fore(i, 0, N) {
    cin >> hs[i];
  }

  cout << solve(hs, K) << '\n';

  return EXIT_SUCCESS;
}
