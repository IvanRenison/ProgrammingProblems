// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

uint solve(uint n, uint x) {
  if (n < 2) {
    return 0;
  }
  n -= 2;
  return n / x + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n, x;
    cin >> n >> x;
    n--;

    uint ans = solve(n, x) + 1;
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
