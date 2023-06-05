// https://codeforces.com/group/id8eYTCwzg/contest/445210/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define NMAX ull(1e6 + 1)

const ull mod = (1e9 + 7);

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x - b.x + mod) % mod);
  }
  Mod operator*(Mod b) {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) {
    return x == b.x;
  }
  bool operator!=(Mod b) {
    return x != b.x;
  }
  bool operator<(Mod b) {
    return x < b.x;
  }
  bool operator>(Mod b) {
    return x > b.x;
  }
  bool operator<=(Mod b) {
    return x <= b.x;
  }
  bool operator>=(Mod b) {
    return x >= b.x;
  }

  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    ull x;
    is >> x;
    m = Mod(x);
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

Mod fact[NMAX];

void init() {
  fact[0] = 1;
  fore(i, 1, NMAX) {
    fact[i] = fact[i - 1] * Mod(i);
  }
}

Mod comb(ull n, ull k) {
  if (k > n) {
    return 0;
  }
  return fact[n] / (fact[k] * fact[n - k]);
}

struct Problem {
  ull a;
  ull b;

  ull n;

  Problem(ull a, ull b, ull n) : a(min(a, b)), b(max(a, b)), n(n) {}

  bool only_digits_ab(ull x) {
    while (x > 0) {
      ull d = x % 10;
      if (d != a && d != b) {
        return false;
      }
      x /= 10;
    }

    return true;
  }

  Mod solve() {
    vector<ull> only_ab_sums;
    fore(i, 0, b * n + 1) {
      if (only_digits_ab(i)) {
        only_ab_sums.push_back(i);
      }
    }

    Mod ans = 0;

    for (ull x : only_ab_sums) {
      /* We have to solve equation x = i * a + j * b with i + j = n

        x = i * a + j * b
        n = i + j

        x = i * a + j * b
        i = n - j

        x = (n - j) * a + j * b
        i = n - j

        x = n * a + (-a + b) * j
        i = n - j

        (x - n * a) / (-a + b) = j
        i = n - j

        j = (x - n * a) / (-a + b)
        i = n - j

        j = (x - n * a) / (b - a)
        i = n - j
      */

      if (x >= n * a) {
        ull num = x - n * a;
        ull den = b - a;
        if (num % den == 0) {
          ull j = num / den;

          ans += comb(n, j);
        }
      }
    }

    return ans;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  ull a, b, n;

  cin >> a >> b >> n;

  cout << Problem(a, b, n).solve() << '\n';

  return EXIT_SUCCESS;
}
