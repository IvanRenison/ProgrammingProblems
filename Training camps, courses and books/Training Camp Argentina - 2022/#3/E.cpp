// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/E
#include <bits/stdc++.h>
#define pb push_back
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull solve(vector<pair<ll, ll>> xys) {
  ull n = xys.size();

  map<pair<ll, ll>, ull> combs;

  fore(i, 0, n) {
    auto [x0, y0] = xys[i];

    fore(j, i + 1, n) {
      auto [x1, y1] = xys[j];

      ll x = x1 - x0;
      ll y = y1 - y0;

      ll sign = y < 0 || (y == 0 && x < 0) ? -1 : 1;

      combs[{sign * x, sign * y}]++;
    }
  }

  ull ans = 0;

  for (auto [_, k] : combs) {
    if (k > 1) {
      ans += k * (k - 1) / 2;
    }
  }

  return ans / 2;
}

int main(void) {
  FIN;

  ull n;
  cin >> n;

  vector<pair<ll, ll>> xys(n);
  fore(i, 0, n) {
    cin >> xys[i].first >> xys[i].second;
  }

  cout << solve(xys) << '\n';

  return 0;
}
