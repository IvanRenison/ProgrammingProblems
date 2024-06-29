// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull max_sum = 1e6;

typedef bitset<max_sum + 1> B;

ull solve1(ull w, ull f, const vu& ss) {
  ull sum = accumulate(ss.begin(), ss.end(), 0);

  B dp;
  dp[0] = true;

  for (ull s : ss) {
    dp |= dp << s;
  }

  auto can = [&](ull k) -> bool {
    ull W = k * w, F = k * f;
    if (W >= sum || F >= sum) {
      return true;
    }

    ull i = W;
    while (!dp[i]) {
      i--;
    }

    ull j = sum - i;

    return j <= F;
  };

  ull l = 0, r = sum;

  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull w, f, n;
    cin >> w >> f >> n;
    vu ss(n);
    for (ull& s  : ss) {
      cin >> s;
    }

    auto ans = solve1(w, f, ss);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
