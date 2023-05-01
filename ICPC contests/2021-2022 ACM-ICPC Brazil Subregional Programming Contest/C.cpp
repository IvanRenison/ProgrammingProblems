// https://codeforces.com/gym/103388/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

// Calculate de mod of an individual digit, counting from 0
// (0 is the least significant digit)
// So it calculates d * B^i % (B+1)
ull individual_mod(ull B, ull d, ull i) {
  if (i % 2 == 0) {
    return d;
  } else {
    return B + 1 - d;
  }
}

ull full_mod(ull B, vector<ull> Ds) {
  ull L = Ds.size();
  ull ans = 0;
  fore(i, 0, L) {
    ans = (ans + individual_mod(B, Ds[i], i)) % (B + 1);
  }

  return ans;
}

optional<pair<ull, ull>> solve(ull B, vector<ull> Ds) {
  ull L = Ds.size();

  reverse(Ds.begin(), Ds.end());

  ull m = full_mod(B, Ds);

  if (m == 0) {
    return {{0, 0}};
  }

  for (ull i = L; i > 0;) {
    i--;

    ull d = Ds[i];

    if (i % 2 == 0) {
      // m2 = d
      if (d >= m) {
        ull d1 = d - m;
        return {{L - i, d1}};
      }
    } else {
      // m1 = B + 1 - d
      if (d >= B + 1 - m) {
        ull d1 = d - (B + 1 - m);
        return {{L - i, d1}};
      }
    }
  }

  return {};
}

int main(void) {

  ull B, L;
  cin >> B >> L;

  vector<ull> Ds(L);
  for (ull i = 0; i < L; i++) {
    cin >> Ds[i];
  }

  optional<pair<ull, ull>> res = solve(B, Ds);

  if (res.has_value()) {
    auto [r1, r2] = res.value();
    cout << r1 << " " << r2 << "\n";
  } else {
    cout << "-1 -1"
         << "\n";
  }

  return EXIT_SUCCESS;
}
