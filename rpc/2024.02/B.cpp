// https://redprogramacioncompetitiva.com/contests/2024/02/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull solve(ull n) {
  return __lg(n) + 1 + (__builtin_popcountll(n) != 1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  ull ans = solve(n);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
