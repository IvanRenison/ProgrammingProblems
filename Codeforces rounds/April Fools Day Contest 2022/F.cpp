// https://codeforces.com/contest/1663/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  if (s.size() == 3) {
    string word = "the";
    fore(i, 0, 3) {
      s[i] = (s[i] - 'a' + word[i] - 'a') % 26 + 'a';
    }
  } else if (s.size() == 4) {
    s = "none";
  } else if (s.size() == 5) {
    string word = "buffy";
    fore(i, 0, 5) {
      s[i] = (s[i] - 'a' + word[i] - 'a') % 26 + 'a';
    }
  } else if (s.size() == 6) {
    string word = "slayer";
    fore(i, 0, 6) {
      s[i] = (s[i] - 'a' + word[i] - 'a') % 26 + 'a';
    }
  } else {
    string word = "vampire";
    fore(i, 0, 7) {
      s[i] = (s[i] - 'a' + word[i] - 'a') % 26 + 'a';
    }
  }

  cout << s << '\n';

}
