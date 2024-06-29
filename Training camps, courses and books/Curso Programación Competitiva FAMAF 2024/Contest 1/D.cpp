// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;

  set<pair<string, string>> s;
  fore(_, 0, n) {
    string a, b;
    cin >> a >> b;
    s.insert({a, b});
  }

  uint ans = s.size();

  cout << ans << '\n';

  return EXIT_SUCCESS;
}
