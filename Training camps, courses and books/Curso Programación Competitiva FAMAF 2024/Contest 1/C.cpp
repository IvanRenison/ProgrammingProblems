// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

char solve1(const string& a, const string& b) {
  if (a.back() != b.back()) {
    if (a.back() == 'S' || b.back() == 'L') {
      return '<';
    } else {
      return '>';
    }
  } else {
    if (a.size() == b.size()) {
      return '=';
    } else if (a.size() < b.size()) {
      return a.back() == 'S' ? '>' : '<';
    } else {
      return a.back() == 'S' ? '<' : '>';
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    string a, b;
    cin >> a >> b;

    char ans = solve1(a, b);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
