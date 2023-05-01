// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull n, ull m, ull k) {
  if (n < m) {
    if (k < n) {
      return n;
    }
    if (k < m) {
      return k;
    }
    return m;
  } else {
    if (k < m) {
      return m;
    }
    if (k < n) {
      return k;
    }
    return n;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    cout << solve1(n, m, k) << "\n";
  }

  return EXIT_SUCCESS;
}
