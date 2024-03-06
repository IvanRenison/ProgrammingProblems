// https://codeforces.com/gym/104441/problem/2

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull solveUp(ull N, ull K, ull P, ull U) {
  assert(P < U);

  ull d = U - P;

  // Go directly
  ull ans = d / K + d % K;

  // Go up and then down
  if (P + (d / K + 1) * K < N) {
    ans = min(ans, d / K + 1 + (P + (d / K + 1) * K - U));
  } else {
    ans = min(ans, d / K + 1 + (N - 1 - U));
  }

  // Go down and then up
  if (P < U) {
    ans = min(ans, 1 + U / K + U % K);
    if ((U / K + 1) * K < N) { // ans then down again
      ans = min(ans, 1 + U / K + 1 + (N - 1 - U));
    }
  }

  return ans;
}

ull solve(ull N, ull K, ull P, ull U) {
  if (P < U) {
    return solveUp(N, K, P, U);
  } else {
    return solveUp(N, K, N - 1 - P, N - 1 - U);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, K, P, U;
  cin >> N >> K >> P >> U;
  P--, U--; // Index channels from 0

  ull ans = solve(N, K, P, U);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
