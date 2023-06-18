//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

tuple<ull, ull, ull, ull> parse1(void) {
  ull A, B, C, k;
  cin >> A >> B >> C >> k;
  return {A, B, C, k - 1};
}

ull ull_pow(ull x, ull y) {
  ull res = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      res = (res * x);
    }
    y = y / 2;
    x = (x * x);
  }
  return res;
}

optional<tuple<ull, ull, ull>> solve1(ull A, ull B, ull C, ull k) {
  if (max(A, B) > C || max(A, B) + 1 < C) {
    return {};
  }

  ull min_a = ull_pow(10, A - 1);
  ull max_a = 10 * min_a;
  ull min_b = ull_pow(10, B - 1);
  ull max_b = 10 * min_b;
  ull min_c = ull_pow(10, C - 1);
  ull max_c = 10 * min_c;

  fore(a, min_a, max_a) {
    /*
      min_c ≤ a + b ⇔ b ≥ min_c - a
      a + b < max_c ⇔ b < max_c - a
    */
    ull start_b = max(min_b, min_c >= a ? min_c - a : 0);
    ull end_b = min(max_b, max_c - a);
    if (start_b < end_b) {
      if (k < end_b - start_b) {
        ull b = start_b + k;
        return {{a, b, a + b}};
      } else {
        k -= end_b - start_b;
      }
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [A, B, C, k] = parse1();
    auto ans = solve1(A, B, C, k);
    if (ans.has_value()) {
      auto [a, b, c] = ans.value();
      cout << a << " + " << b << " = " << c << "\n";
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
