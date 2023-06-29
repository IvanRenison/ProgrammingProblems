// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

void solve(void) {}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<string> s(n);
  fore(i, 0, n) {
    cin >> s[i];
  }

  map<string, ull> m;
  fore(i, 0, n) {
    m[s[i]]++;
  }

  ull i = 0;
  string names[2];
  ull vals[2] = {0, 0};
  for (auto [t, c] : m) {
    names[i] = t;
    vals[i] = c;
    i++;
  }

  if (vals[1] > vals[0]) {
    cout << names[1] << '\n';
  } else {
    cout << names[0] << '\n';
  }

  return EXIT_SUCCESS;
}
