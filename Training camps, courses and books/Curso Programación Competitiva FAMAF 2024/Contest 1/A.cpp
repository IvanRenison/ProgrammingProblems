// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/A

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
    int rating;
    cin >> rating;

    if (1900 <= rating) {
      cout << "Division 1\n";
    } else if (1600 <= rating) {
      cout << "Division 2\n";
    } else if (1400 <= rating) {
      cout << "Division 3\n";
    } else {
      cout << "Division 4\n";
    }
  }

  return EXIT_SUCCESS;
}
