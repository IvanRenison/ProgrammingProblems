// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/E

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
    cin >> bs[i];
  }

  return {as, bs};
}

/* Find the minimum index for witch f is true or or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
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

bool posible_for_k(vector<ull> as, vector<ull> bs, ull k) {
  ull n = bs.size();

  ull invited = 0;

  fore(i, 0, n) {
    ull b = bs[i];
    ull a = as[i];

    if (b >= invited && a >= k - invited - 1) {
      invited++;
    }
    if (invited == k) {
      return true;
    }
  }

  return false;
}

ull solve1(vector<ull> as, vector<ull> bs) {
  ull n = as.size();

  ull ans =
      binary_search([&](ull k) { return !posible_for_k(as, bs, k); }, 1, n + 1);
  ans--;

  return ans;
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
