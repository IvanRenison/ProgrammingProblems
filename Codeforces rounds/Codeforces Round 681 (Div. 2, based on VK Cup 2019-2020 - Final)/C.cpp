// https://codeforces.com/contest/1443/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<vector<ull>, vector<ull>> parse1(void) {
  ull n;
  cin >> n;
  vector<ull> as(n);
  vector<ull> bs(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  fore(i, 0, n) {
    cin >> bs[i];
  }

  return {as, bs};
}

/* Find the minimum number between a ans b for witch f is true or or b if none if true */
ull binary_search(function<bool(ull)> f, ull a, ull b) {
  ull lower = a;
  ull upper = b;
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

bool posible_for(vector<ull> as, vector<ull> bs, ull t) {
  ull n = as.size();
  ull b_time = 0;
  fore(i, 0, n) {
    if (as[i] > t) {
      b_time += bs[i];
    }
  }

  return b_time <= t;
}

ull solve1(vector<ull> as, vector<ull> bs) {
  return binary_search([&](ull t) { return posible_for(as, bs, t); }, 1, 1000000001);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [as, bs] = parse1();
    cout << solve1(as, bs) << "\n";
  }

  return EXIT_SUCCESS;
}
