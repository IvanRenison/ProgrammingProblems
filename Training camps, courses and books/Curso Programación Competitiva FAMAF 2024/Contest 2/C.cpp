// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(uint a, uint b, uint n) {
  uint ans = 0;

  for (; max(a, b) <= n; ans++) {
    if (a > b) {
      b += a;
    } else {
      a += b;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint a, b, n;
    cin >> a >> b >> n;

    uint ans = solve(a, b, n);

    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
