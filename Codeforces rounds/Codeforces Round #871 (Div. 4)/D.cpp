// https://codeforces.com/contest/1829/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> parse1(void) {
  ull n, m;
  cin >> n >> m;
  return {n, m};
}

bool solve1(ull n, ull m) {
  if (n == m) {
    return true;
  }
  if (n < m) {
    return false;
  }

  if (n % 3 != 0) {
    return false;
  }

  return solve1(n / 3, m) || solve1(n / 3 * 2, m);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, m] = parse1();
    if (solve1(n, m)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
