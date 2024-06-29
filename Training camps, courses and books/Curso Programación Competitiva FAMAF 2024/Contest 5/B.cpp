// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(uint n) {
  return n;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;

    uint ans = solve(n);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
