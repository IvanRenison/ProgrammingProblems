// https://codeforces.com/group/gmV7IkT2pN/contest/528245/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint maxa = 1e6;
vu factor(maxa + 1);

void init() {
  iota(factor.begin(), factor.end(), 0);

  fore(i, 2, maxa + 1) {
    if (factor[i] == i) {
      for (uint j = i * i; j <= maxa; j += i) {
        factor[j] = i;
      }
    }
  }
}

bool solve(const vu& as) {
  uint n = as.size();

  map<uint, uint> primes;

  for (uint a : as) {
    while (a > 1) {
      uint p = factor[a];
      a /= p;
      primes[p]++;
    }
  }

  for (auto [p, e] : primes) {
    if (e % n != 0) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;
    vu as(n);
    for (uint& a : as) {
      cin >> a;
    }

    bool ans = solve(as);
    cout << (ans ? "Yes" : "No") << '\n';
  }

  return EXIT_SUCCESS;
}
