// https://codeforces.com/contest/20/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

string solve(string ss) {
  ull n = ss.size();

  string ans;

  ans.push_back(ss[0]);

  bool last = ss[0] == '/';
  fore(i, 1, n) {
    if (!last || (last && ss[i] != '/')) {
      ans.push_back(ss[i]);
    }
    last = ss[i] == '/';
  }

  while (ans.size() > 1 && ans.back() == '/') {
    ans.pop_back();
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string ss;
  cin >> ss;

  cout << solve(ss);

  return EXIT_SUCCESS;
}
