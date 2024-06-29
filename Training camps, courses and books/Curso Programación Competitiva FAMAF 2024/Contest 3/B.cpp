// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint max_a = 100;

uint solve1(uint c, const vu& as) {
  vu counter(max_a);

  for (uint a : as) {
    counter[a]++;
  }

  uint ans = 0;

  fore(i, 0, max_a) {
    ans += min(counter[i], c);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n, c;
    cin >> n >> c;
    vu as(n);
    for (uint& a : as) {
      cin >> a;
      a--;
    }

    uint ans = solve1(c, as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
