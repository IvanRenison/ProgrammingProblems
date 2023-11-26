// https://codeforces.com/contest/1900/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

bool solve1(ull a, ull b, ull c) {
  return (max(b, c) - min(b, c)) % 2 == 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  while (t--) {
    ull a, b, c;
    cin >> a >> b >> c;

    bool x = solve1(a, b, c);
    bool y = solve1(b, a, c);
    bool z = solve1(c, a, b);
    cout << x << ' ' << y << ' ' << z << '\n';
  }

  return EXIT_SUCCESS;
}
