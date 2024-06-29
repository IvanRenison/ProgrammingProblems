// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;
  vector<pair<uint, uint>> colors(n);
  for (auto& [h, a] : colors) {
    cin >> h >> a;
  }

  uint ans = 0;
  fore(i, 0, n) {
    fore(j, 0, n) if (i != j) {
      ans += colors[i].first == colors[j].second;
    }
  }

  cout << ans << '\n';

  return EXIT_SUCCESS;
}
