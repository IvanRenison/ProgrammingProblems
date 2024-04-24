// https://cses.fi/problemset/task/1141/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(const vu& ks) {
  uint n = ks.size();

  uint ans = 0;

  set<uint> vals;

  uint i = 0, j = 0;

  while (i < n && j < n) {
    while (j < n && !vals.count(ks[j])) {
      vals.insert(ks[j]);
      j++;
    }

    ans = max(ans, j - i);

    vals.erase(ks[i]);

    i++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;

  vu ks(n);
  for (uint& k : ks) {
    cin >> k;
  }

  uint ans = solve(ks);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
