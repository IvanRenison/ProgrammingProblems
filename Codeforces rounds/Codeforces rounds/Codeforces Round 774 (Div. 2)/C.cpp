// https://codeforces.com/contest/1646/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull fact[15];

void init() {
  fact[0] = 1;
  fore(i, 1, 15) {
    fact[i] = fact[i-1] * i;
  }
}

ull solve1(ull n) {
  ull ans = __builtin_popcountll(n);

  fore(x, 1, (1ull << 15)) {
    ull facts_sum = 0;
    fore(i, 0, 15) {
      if (x & (1ull << i)) {
        facts_sum += fact[i];
      }
    }

    if (facts_sum <= n) {
      ans = min(ans, (ull)__builtin_popcountll(x) + __builtin_popcountll(n - facts_sum));
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  init();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    auto ans = solve1(n);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
