// https://codeforces.com/contest/1399/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

bool solve1(vu& as) {
  uint n = as.size();
  
  sort(as.begin(), as.end());

  fore(i, 1, n) {
    if (as[i] - as[i - 1] > 1) {
      return false;
    }
  }

  return true;
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
      cin >> a;
    }

    bool ans = solve1(as);
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
