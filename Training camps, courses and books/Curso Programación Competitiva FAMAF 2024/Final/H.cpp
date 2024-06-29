// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/H

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;

uint diff(uint a, uint b) {
  return a > b ? a - b : b - a;
}

uint solve(vu& as) {
  uint n = as.size();

  sort(as.begin(), as.end());

  auto can = [&](uint t) -> bool {
    uint s = as[0] + t;
    uint cnt = 1;
    for (uint a : as) {
      if (diff(a, s) > t) {
        cnt++;
        s = a + t;
      }
    }

    return cnt <= 3;
  };

  if (can(0)) return 0;

  uint l = 0, r = as[n - 1] + 1;
  while (l + 1 < r) {
    uint m = (l + r) / 2;
    if (can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;
    vu as(n);
    for (uint& a : as) {
      cin >> a;
    }

    uint ans = solve(as);
    cout << ans << '\n';
  }
}
