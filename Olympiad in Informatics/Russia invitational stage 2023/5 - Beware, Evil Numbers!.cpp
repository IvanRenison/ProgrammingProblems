// https://codeforces.com/gym/104441/problem/5

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull solve(ull n) {
  n /= 2;
  return n / 2 - (n % 2 == 0) * (__builtin_popcount(n) % 2);
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
