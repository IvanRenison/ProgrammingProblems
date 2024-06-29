// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/C

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

// Ans for making the string of the form 0…01…1
uint solveLeft(const string& s) {
  uint total0 = 0;
  for (char c : s) {
    total0 += c == '0';
  }

  uint ans = total0;
  uint count0 = 0, count1 = 0;
  for (char c : s) {
    ans = min(ans, count1 + total0 - count0);
    count0 += c == '0';
    count1 += c == '1';
  }

  return ans;
}

uint solve(string& s) {
  uint ans = solveLeft(s);
  reverse(s.begin(), s.end());
  ans = min(ans, solveLeft(s));
  for (char& c : s) {
    c = '0' + '1' - c;
  }
  ans = min(ans, solveLeft(s));
  reverse(s.begin(), s.end());
  ans = min(ans, solveLeft(s));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    uint ans = solve(s);
    cout << ans << '\n';
  }
}
