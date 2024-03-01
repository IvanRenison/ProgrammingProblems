// https://codeforces.com/contest/1934/problem/D1

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

optional<vu> solve1(ull n, ull m) {

  if ((n ^ m) < n) {
    return {{n, m}};
  }

  ull j = __lg(n);
  assert(n & (1ull << j));
  ull i = __lg(m);
  assert(m & (1ull << i));

  assert(i < j);

  ull x = (1ull << j) | (1ull << i);

  if (x >= n || (x ^ n) >= n) {
    return {};
  }

  return {{n, x ^ n, m}};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    auto ans = solve1(n, m);
    if (ans) {
      cout << ans->size() - 1 << '\n';
      for (ull x : *ans) {
        cout << x << " ";
      }
      cout << '\n';
    } else {
      cout << "-1" << '\n';
    }
  }

  return EXIT_SUCCESS;
}
