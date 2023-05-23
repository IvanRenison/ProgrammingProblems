#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

void swap(string& s, ull i, ull j) {
  char temp = s[i];
  s[i] = s[j];
  s[j] = temp;
}

bool solve(string s1, string s2, string t1, string t2) {
  ull n = s1.size();

  reverse(s2.begin(), s2.end());
  reverse(t2.begin(), t2.end());

  fore(i, 0, n) {
    ull j = i;
    while (j < n && (s1[j] != t1[i] || s2[j] != t2[i])) {
      j++;
    }

    if (j == n) {
      return false;
    }

    swap(s1, i, j);
    swap(s2, i, j);
  }

  assert(s1 == t1);

  return s2 == t2;
}

int main(void) {

  // Open file enchanted.in
  freopen("enchanted.in", "r", stdin);

  string s1, s2, t1, t2;
  cin >> s1 >> s2 >> t1 >> t2;

  // Open file enchanted.out
  freopen("enchanted.out", "w", stdout);

  bool ans = solve(s1, s2, t1, t2);

  if (ans) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}