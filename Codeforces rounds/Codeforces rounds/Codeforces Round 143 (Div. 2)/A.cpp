// https://codeforces.com/contest/231/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n;
  cin >> n;

  uint ans = 0;

  for (uint i = 0; i < n; i++) {
    uint a, b, c;
    cin >> a >> b >> c;

    if (a + b + c >= 2) {
      ans++;
    }
  }

  cout << ans << '\n';
}
