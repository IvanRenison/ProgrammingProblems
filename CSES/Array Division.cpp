// https://cses.fi/problemset/task/1085

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

ull solve(ull k, const vu& xs) {

  auto can = [&](ull s) -> bool {
    ull sum = 0;
    ull cnt = 1;
    for (ull x : xs) {
      if (x > s) {
        return false;
      }
      if (sum + x > s) {
        sum = x;
        cnt++;
      } else {
        sum += x;
      }
    }

    return cnt <= k;
  };

  ull l = *max_element(xs.begin(), xs.end()) - 1;
  ull r = accumulate(xs.begin(), xs.end(), 1ull);

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, k;
  cin >> n >> k;
  vu xs(n);
  for (ull& x : xs) {
    cin >> x;
  }

  ull ans = solve(k, xs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
