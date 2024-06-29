// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull solve(ull n) {

  ull p = -1;
  for (ull x = 2; x * x <= n; x++) {
    if (n % x == 0) {
      p = x;
      break;
    }
  }

  if (p == -1) { // n is prime
    return 1;
  }

  if (p == 2) {
    return n / 2;
  }

  return (n - p) / 2 + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;

  ull ans = solve(n);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
