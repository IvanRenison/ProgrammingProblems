// https://cses.fi/problemset/task/2185

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef __uint128_t u128;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull solve(u128 n, vector<ull> as) {
  ull k = as.size();

  u128 ans = 0;

  fore(x, 1, 1 << k) {
    u128 prod = 1;
    fore(i, 0, k) {
      if ((x & (1 << i)) != 0) {
        prod *= (u128)as[i];
        if (prod > n) {
          break;
        }
      }
    }
    if (__builtin_popcountll(x) % 2 == 1) {
      ans += n / prod;
    } else {
      ans -= n / prod;
    }
  }

  return (ull)ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, k;
  cin >> n >> k;
  vector<ull> as(k);
  for (ull& a : as) {
    cin >> a;
  }

  auto ans = solve(n, as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
