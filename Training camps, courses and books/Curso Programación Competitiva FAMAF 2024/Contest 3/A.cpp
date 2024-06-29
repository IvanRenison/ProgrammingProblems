// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve1(const string& s) {
  vector<bool> viewd(26, false);

  uint ans = 0;

  for (char c : s) {
    ans++;
    if (!viewd[c - 'A']) {
      viewd[c - 'A'] = true;
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n;
    string s;
    cin >> n >> s;

    uint ans = solve1(s);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
