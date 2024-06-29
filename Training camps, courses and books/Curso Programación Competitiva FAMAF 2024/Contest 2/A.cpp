// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint a, b, c;
    cin >> a >> b >> c;

    bool ans = a == b + c || b == a + c || c == a + b;

    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }

  }

  return EXIT_SUCCESS;
}
