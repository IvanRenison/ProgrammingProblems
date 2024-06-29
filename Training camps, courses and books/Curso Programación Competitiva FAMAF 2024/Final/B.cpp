// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/B

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(const string& s) {
  vu count(26);
  for (char c : s) {
    count[c - 'A']++;
  }

  uint ans = 0;
  fore(i, 0, 26) {
    if (count[i] > i) {
      ans++;
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;
    string s;
    cin >> s;

    uint ans = solve(s);
    cout << ans << '\n';
  }
}
