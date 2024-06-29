// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(vector<uint>& as) {
  uint n = as.size();
  sort(as.begin(), as.end());
  as.erase(std::unique(as.begin(), as.end()), as.end());
  uint m = as.size();

  uint ans = 1;

  uint i = 0, j = 1;
  while (j < m) {
    uint d = as[j] - as[i];
    if (d >= n) {
      i++;
    } else {
      ans = max(ans, j - i + 1);
      j++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n;
    cin >> n;
    vector<uint> as(n);
    for (uint& a : as) {
      cin >> a;
    }

    uint ans = solve(as);

    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
