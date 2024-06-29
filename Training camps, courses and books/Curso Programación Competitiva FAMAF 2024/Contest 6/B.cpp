// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/B

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

uint solve(const string& s) {
  return *max_element(s.begin(), s.end()) - 'a' + 1;

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    string s;
    cin >> n >> s;

    uint ans = solve(s);
    cout << ans << '\n';
  }
}
