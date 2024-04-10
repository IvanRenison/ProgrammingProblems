#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a; i < (b); i++)

const uint inf = 1 << 30;

uint solve(uint k, const vu& hs) {
  uint n = hs.size();

  vu hs_sums(n + 1);

  fore(i, 0, n) {
    hs_sums[i + 1] = hs_sums[i] + hs[i];
  }

  uint ans_j = inf;
  uint ans_val = inf;

  fore(i, 0, n - k + 1) {
    uint this_ans_val = hs_sums[i + k] - hs_sums[i];
    if (this_ans_val < ans_val) {
      ans_val = this_ans_val;
      ans_j = i;
    }
  }

  return ans_j;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  uint n, k;
  cin >> n >> k;
  vu hs(n);

  for (uint& h : hs) {
    cin >> h;
  }

  uint ans = solve(k, hs);

  cout << ans + 1 << '\n';
}
