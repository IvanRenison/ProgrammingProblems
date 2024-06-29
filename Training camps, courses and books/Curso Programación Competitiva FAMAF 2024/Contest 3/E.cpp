// https://codeforces.com/group/gmV7IkT2pN/contest/522472/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

constexpr ull mod = 1e9 + 7;
struct Mod {
  ull x;
  Mod(ull xx = 0) : x(xx % mod) {}
  Mod operator+(Mod b) const {
    return (x + b.x) >= mod ? x + b.x - mod : x + b.x;
  }
  Mod operator*(Mod b) const {
    return (x * b.x) % mod;
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
};

ull number_with_mod3(ull l, ull r, ull x) {
  ull d = (3 - x) % 3;
  return (r + d) / 3 - (l + d - 1) / 3;
}

Mod solve(ull n, ull l, ull r) {

  array<Mod, 3> n_mod;
  fore(x, 0, 3) {
    n_mod[x] = number_with_mod3(l, r, x);
  }

  array<Mod, 3> counter = {1, 0, 0};

  fore(i, 0, n) {
    array<Mod, 3> new_counter;
    fore(x, 0, 3) {
      fore(y, 0, 3) {
        new_counter[(x + y) % 3] += counter[x] * n_mod[y];
      }
    }
    counter = new_counter;
  }

  Mod ans = counter[0];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, l, r;
  cin >> n >> l >> r;

  Mod ans = solve(n, l, r);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
