// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

optional<ull> solve(vu& ps, ull x, ull a, ull y, ull b, ull k) {
  ull n = ps.size();

  if (x < y) {
    swap(x, y), swap(a, b);
  }

  sort(ps.begin(), ps.end(), greater<>());

  auto can = [&](ull c) -> bool {
    assert(c <= n);
    ull both = 0, a_only = 0, b_only = 0;

    fore(i, 0, c) {
      if ((i + 1) % a == 0 && (i + 1) % b == 0) {
        both++;
      } else if ((i + 1) % a == 0) {
        a_only++;
      } else if ((i + 1) % b == 0) {
        b_only++;
      }
    }


    ull total = 0;
    fore(i, 0, both) {
      total += (x + y) * ps[i] / 100;
    }
    fore(i, both, both + a_only) {
      total += x * ps[i] / 100;
    }
    fore(i, both + a_only, both + a_only + b_only) {
      total += y * ps[i] / 100;
    }

    return total >= k;
  };

  ull l = 0, r = n + 1;

  while (l + 1 < r) {
    ull x = (l + r) / 2;
    if (can(x)) {
      r = x;
    } else {
      l = x;
    }
  }

  if (r > n) {
    return {};
  }

  return r;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull q;
  cin >> q;

  while (q--) {
    ull n;
    cin >> n;
    vu ps(n);
    for (ull& p : ps) {
      cin >> p;
    }
    ull x, a, y, b, k;
    cin >> x >> a >> y >> b >> k;

    auto ans = solve(ps, x, a, y, b, k);
    if (ans.has_value()) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
