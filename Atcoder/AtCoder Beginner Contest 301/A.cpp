// https://atcoder.jp/contests/abc301/tasks/abc301_a

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(string ss) {
  ull n = ss.size();

  ull t = 0;
  for (char c : ss) {
    if (c == 'T') {
      t++;
    }
  }

  return t > n / 2 || (n % 2 == 0 && t == n / 2 && ss.back() == 'A');
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  string ss;
  cin >> ss;

  if (solve(ss)) {
    cout << "T\n";
  } else {
    cout << "A\n";
  }

  return EXIT_SUCCESS;
}
