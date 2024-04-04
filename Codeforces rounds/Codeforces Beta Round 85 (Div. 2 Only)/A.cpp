// https://codeforces.com/contest/112/problem/A

#include <bits/stdc++.h>

using namespace std;

int solve(string a, string b) {
  for (char&c : a) {
    c = tolower(c);
  }
  for (char&c : b) {
    c = tolower(c);
  }

  if (a < b) {
    return -1;
  } else if (a > b) {
    return 1;
  } else {
    return 0;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s, t;
  cin >> s >> t;

  int ans = solve(s, t);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
