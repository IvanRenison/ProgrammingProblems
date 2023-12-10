// https://codeforces.com/group/hzSLIARNBN/contest/465346/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 1e9 + 7;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x + mod - b.x + mod) % mod);
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

Mod comb(ull n, ull k) {
  if (k > n) {
    return 0;
  }
  Mod ans = 1;
  fore(i, 0, k) {
    ans *= (n - i);
  }
  fore(i, 1, k + 1) {
    ans /= i;
  }
  return ans;
}

vector<ull> prime_factors_amounts(ull n) {
  vector<ull> ans;
  for (ull i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ull e = 0;
      while (n % i == 0) {
        n /= i;
        e++;
      }
      ans.push_back(e);
    }
  }
  if (n > 1) {
    ans.push_back(1);
  }
  return ans;
}

Mod solve_1n(ull n, ull k) {
  vector<ull> pfa = prime_factors_amounts(n);
  ull r = pfa.size();

  ull prod = 1;
  for (ull e : pfa) {
    prod *= (e + 1);
  }

  if (prod < k) {
    return 0;
  }
  if (prod == k) {
    return 1;
  }

  Mod ans = 0;
  fore(x, 0, 1 << (2 * r)) {
    ull this_prod = 1;
    fore(i, 0, r) {
      ull less = 0;
      if (x & (1 << (2 * i))) {
        less++;
      }
      if (x & (1 << (2 * i + 1))) {
        less++;
      }
      this_prod *= pfa[i] + 1 - less;
    }
    if (__builtin_popcountll(x) % 2 == 0) {
      ans += comb(this_prod, k);
    } else {
      ans -= comb(this_prod, k);
    }
  }

  return ans;
}

Mod solve(ull x, ull k) {
  Mod ans = 0;
  for (ull i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      ull n = x - i;
      if (n % i == 0) {
        ans += solve_1n(n / i, k);
      }
      ull j = x / i;
      if (i != j && j != x) {
        ull m = x - j;
        if (m % j == 0) {
          ans += solve_1n(m / j, k);
        }
      }
    }
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull x, k;
  cin >> x >> k;

  auto ans = solve(x, k);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
