// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)



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

ull solve(ull n, ull k) {

  auto posible_for = [n, k](ull v) {
    for (ull count = v, ki = k; count < n; ki *= k) {
      ull vk = v / ki;
      if (vk == 0) {
        return count >= n;
      }
      count += vk;
    }
    return true;
  };

  ull ans = binary_search(posible_for, 1, n * k + 1);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, k;
  cin >> n >> k;
  cout << solve(n, k) << '\n';

  return EXIT_SUCCESS;
}
