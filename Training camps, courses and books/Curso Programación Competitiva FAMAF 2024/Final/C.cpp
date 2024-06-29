// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/C

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(const vu& as) {
  uint n = as.size();

  uint max_i = 0, min_i = 0;
  fore(i, 1, n) {
    if (as[i] > as[max_i]) {
      max_i = i;
    }
    if (as[i] < as[min_i]) {
      min_i = i;
    }
  }

  uint ans = as[max_i] - as[min_i];

  // Option to remove the maximum
  {
    uint new_max = 0;
    fore(i, 0, n) if (i != max_i) {
      if (as[i] > new_max) {
        new_max = as[i];
      }
    }
    ans = min(ans, new_max - as[min_i]);
  }

  // Option to remove the minimum
  {
    uint new_min = UINT_MAX;
    fore(i, 0, n) if (i != min_i) {
      if (as[i] < new_min) {
        new_min = as[i];
      }
    }
    ans = min(ans, as[max_i] - new_min);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }

  uint ans = solve(as);
  cout << ans << '\n';
}
