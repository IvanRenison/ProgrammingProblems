// https://codeforces.com/contest/1846/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

string solve1(vector<string> ss) {
  string ans = "";
  fore(i, 0, 3) {
    if (ss[i][0] != '.' && ss[i][0] == ss[i][1] && ss[i][0] == ss[i][2]) {
      ans += ss[i][0];
      return ans;
    }
  }

  fore(i, 0, 3) {
    if (ss[0][i] != '.' && ss[0][i] == ss[1][i] && ss[0][i] == ss[2][i]) {
      ans += ss[0][i];
      return ans;
    }
  }

  if (ss[0][0] != '.' && ss[0][0] == ss[1][1] && ss[0][0] == ss[2][2]) {
    ans += ss[0][0];
    return ans;
  }

  if (ss[0][2] != '.' && ss[0][2] == ss[1][1] && ss[0][2] == ss[2][0]) {
    ans += ss[0][2];
    return ans;
  }

  return "DRAW";
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    vector<string> ss(3);
    for (string& s : ss) {
      cin >> s;
    }

    auto ans = solve1(ss);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
