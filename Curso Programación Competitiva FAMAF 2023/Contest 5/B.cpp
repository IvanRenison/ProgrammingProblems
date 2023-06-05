// https://codeforces.com/group/id8eYTCwzg/contest/445210/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull parse1(void) {
  ull n;
  cin >> n;
  return n;
}

optional<ull> solve1(ull n) {
  ull ans = 1;
  while (n != 1) {
    if (n % 3 != 0) {
      return {};
    }

    if (n % 6 == 0) {
      n /= 6;
    } else {
      n *= 2;
    }
    ans++;
  }

  return ans - 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    if (ans.has_value()) {
      cout << ans.value() << "\n";
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
