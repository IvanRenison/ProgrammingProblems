// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define all(x) begin(x), end(x)

ull solve(const vu& as) {
  ull n = as.size();

  ull sum = accumulate(all(as), 0ull);
  ull M = *max_element(all(as));

  /*
    min e ≥ 0 such than n * (M + e) - sum ≥ M + e

    ------------

    n * (M + e) - sum = M + e
    n * e - e = M + sum - n * M
    e = (M + sum - n * M) / (n - 1)

  */

  ull e = M + sum > n * M ? (M + sum - n * M + n - 2) / (n - 1) : 0;

  return M + e;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  ull ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
