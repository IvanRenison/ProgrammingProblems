// https://codeforces.com/contest/1833/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve1(const string& s) {
  uint n = s.size();

  set<pair<char, char>> combs;

  fore(i, 0, n - 1) {
    combs.insert({s[i], s[i + 1]});
  }

  uint ans = combs.size();

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

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
