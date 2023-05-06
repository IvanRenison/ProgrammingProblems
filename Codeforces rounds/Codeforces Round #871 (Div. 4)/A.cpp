// https://codeforces.com/contest/1829/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

string parse1(void) {
  string ss;
  cin >> ss;
  return ss;
}

ull solve1(string ss) {
  string co = "codeforces";
  ull count = 0;
  fore(i, 0, 10) {
    if (ss[i] != co[i]) {
      count++;
    }
  }
  return count;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
