// https://codeforces.com/gym/100623

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<char> solve(ull h) {
  if (h == 0) {
    return {'1'};
  } else if (h == 1) {
    return {'0'};
  } else if (h % 2 == 0) {
    return vector<char>(h / 2, '8');
  } else {
    vector<char> ans(h / 2 + 1, '8');
    ans[0] = '4';
    return ans;
  }
}

int main(void) {

  // Open file holes.in
  freopen("holes.in", "r", stdin);

  ull h;

  cin >> h;

  // Open file holes.out
  freopen("holes.out", "w", stdout);

  vector<char> ans = solve(h);

  for (char c : ans) {
    cout << c;
  }
  cout << '\n';

  return EXIT_SUCCESS;
}