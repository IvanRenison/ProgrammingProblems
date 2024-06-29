// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

tuple<uint, uint, uint> solve1(uint a, uint b, uint c) {
  uint A, B, C;

  A = a > b && a > c ? 0 : max(b, c) + 1 - a;
  B = b > a && b > c ? 0 : max(a, c) + 1 - b;
  C = c > a && c > b ? 0 : max(a, b) + 1 - c;

  return {A, B, C};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint a, b, c;
    cin >> a >> b >> c;

    auto [A, B, C] = solve1(a, b, c);
    cout << A << ' ' << B << ' ' << C << '\n';
  }

  return EXIT_SUCCESS;
}
