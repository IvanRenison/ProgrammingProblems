// https://cses.fi/problemset/task/1090

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

uint solve(uint x, const vu& ps) {
  multiset<uint, greater<uint>> ps_set(ps.begin(), ps.end());

  uint ans = 0;

  for (; !ps_set.empty(); ans++) {

    auto it_M = ps_set.begin();

    uint M = *it_M;
    ps_set.erase(it_M);

    uint d = x - M;

    auto it_m = ps_set.lower_bound(d);

    if (it_m != ps_set.end()) {
      ps_set.erase(it_m);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, x;
  cin >> n >> x;
  vu ps(n);
  for (uint& p : ps) {
    cin >> p;
  }

  uint ans = solve(x, ps);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
