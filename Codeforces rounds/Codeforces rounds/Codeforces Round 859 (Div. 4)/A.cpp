// https://codeforces.com/contest/1807/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    ull a, b, c;
    cin >> a >> b >> c;

    if (a + b == c) {
      cout << "+\n";
    } else {
      cout << "-\n";
    }
  }

  return EXIT_SUCCESS;
}
