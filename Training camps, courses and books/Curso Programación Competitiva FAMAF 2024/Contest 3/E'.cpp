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

struct Matrix3 {
  array<array<Mod, 3>, 3> m;

  Matrix3 operator*(const Matrix3& b) const {
    Matrix3 res;
    fore(i, 0, 3) {
      fore(j, 0, 3) {
        fore(k, 0, 3) {
          res.m[i][j] += m[i][k] * b.m[k][j];
        }
      }
    }
    return res;
  }
  array<Mod, 3> operator*(const array<Mod, 3>& b) const {
    array<Mod, 3> res;
    fore(i, 0, 3) {
      fore(j, 0, 3) {
        res[(i + j) % 3] += m[i][j] * b[j];
      }
    }
    return res;
  }

  Matrix3 operator^(ull n) const {
    Matrix3 res;
    fore(i, 0, 3) {
      res.m[i][i] = 1;
    }
    Matrix3 a = *this;
    while (n) {
      if (n & 1) {
        res = res * a;
      }
      a = a * a;
      n /= 2;
    }
    return res;
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

  Matrix3 mat;

  fore(x, 0, 3) {
    fore(y, 0, 3) {
      mat.m[(x + y) % 3][x] += n_mod[y];
    }
  }

  mat = mat^n;

  Mod ans = mat.m[0][0];

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
