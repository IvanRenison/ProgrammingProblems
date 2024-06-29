// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve1(const vu& as) {
  uint n = as.size();

  uint ans = 0;

  fore(i, 0, n) {
    map<uint, uint> counts;
    uint max_count = 0;

    fore(j, i, min(i + 100, n)) {
      uint a = as[j];
      counts[a]++;
      max_count = max(max_count, counts[a]);

      if (max_count <= counts.size()) {
        ans++;
      }
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
    vu as(n);
    for (uint& a : as) {
      char c;
      cin >> c;
      a = c - '0';
    }

    uint ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
