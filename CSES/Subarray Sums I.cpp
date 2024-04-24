// https://cses.fi/problemset/task/1660

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

uint solve1(uint x, const vu& as) {
  uint n = as.size();

  uint sum = 0, ans = 0;

  uint i = 0, j = 0;

  while (i < n) {
    while (j < n && sum < x) {
      sum += as[j];
      j++;
    }

    if (sum == x) {
      ans++;
    }

    sum -= as[i];
    i++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, x;
  cin >> n >> x;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }

  uint ans = solve1(x, as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
