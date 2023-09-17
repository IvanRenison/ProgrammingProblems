// https://codeforces.com/contest/505/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool isPalindrome(string s) {
  fore(i, 0, s.size() / 2) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

string solve(string s) {
  ull n = s.size() + 1;
  fore(i, 0, n) {
    for(char c = 'a'; c <= 'z'; c++) {
      string t = s;
      t.insert(i, 1, c);
      if (isPalindrome(t)) {
        return t;
      }
    }
  }
  return "NA";
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;

  auto ans = solve(s);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
