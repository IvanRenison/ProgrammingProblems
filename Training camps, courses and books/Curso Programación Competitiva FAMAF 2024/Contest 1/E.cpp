// https://codeforces.com/group/gmV7IkT2pN/contest/516385/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

void solve1(void) {
  uint n, q;
  cin >> n >> q;

  vector<uint> as(n);
  for (uint& a : as) {
    cin >> a;
    a %= 2;
  }

  vector<uint> as_xors(n + 1);
  fore(i, 0, n) {
    as_xors[i + 1] = as_xors[i] ^ as[i];
  }

  fore(_, 0, q) {
    uint l, r, k;
    cin >> l >> r >> k;
    l--;

    k %= 2;

    uint changed_xos = as_xors[l] ^ as_xors[n] ^ as_xors[r] ^ ((k * (l - r)) % 2);

    if (changed_xos) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    solve1();
  }

  return EXIT_SUCCESS;
}
