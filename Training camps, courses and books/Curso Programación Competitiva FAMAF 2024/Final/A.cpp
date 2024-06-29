// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/A

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint a, b, c;
    cin >> a >> b >> c;
    uint ans = a ^ b ^ c;
    cout << ans << '\n';
  }
}
