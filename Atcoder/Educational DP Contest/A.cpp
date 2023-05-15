// https://atcoder.jp/contests/dp/tasks/dp_a

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

ll solve(vector<ll> hs) {
  ll n = hs.size();

  ll prelast = 0;
  ll last = abs(hs[0] - hs[1]);

  fore(i, 2, n) {
    ll next =
        min(last + abs(hs[i] - hs[i - 1]), prelast + abs(hs[i] - hs[i - 2]));

    prelast = last;
    last = next;
  }

  return last;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll N;
  cin >> N;

  vector<ll> hs(N);
  fore(i, 0, N) {
    cin >> hs[i];
  }

  cout << solve(hs) << '\n';

  return EXIT_SUCCESS;
}
