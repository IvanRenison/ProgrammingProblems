// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve1(const vuu& vab) {
  uint n = vab.size();

  uint ans = 0;
  uint win_b = 0;
  fore(i, 0, n) {
    auto [a, b] = vab[i];
    if (a <= 10 && b > win_b) {
      win_b = b;
      ans = i;
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
    vuu vab(n);
    for (auto& [a, b] : vab) {
      cin >> a >> b;
    }

    uint ans = solve1(vab);
    cout << ans + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
