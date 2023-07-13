// https://codeforces.com/contest/1814/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> parse1(void) {
  ull a, b;
  cin >> a >> b;
  return {a, b};
}

ull min_steps_m(ull a, ull b, ull m) {
  return m - 1 + a / m + b / m + (a % m == 0 ? 0 : 1) + (b % m == 0 ? 0 : 1);
}

ull solve1(ull a, ull b) {
  ull min_steps = a + b;

  for (ull m = 1; m <= 100000; m++) {
    min_steps = min(min_steps, min_steps_m(a, b, m));
  }

  return min_steps;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [a, b] = parse1();
    cout << solve1(a, b) << endl;
  }

  return EXIT_SUCCESS;
}
