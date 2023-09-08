// https://codeforces.com/contest/1866/problem/H
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull mod = 998244353;

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

constexpr ull fact_limit = 2 * 1e5 + 5;
Mod fact[fact_limit];

void init() {
  fact[0] = 1;
  fore(i, 1, fact_limit) {
    fact[i] = fact[i - 1] * Mod(i);
  }
}

Mod comb(ull N, ull x) {
  if (x > N) {
    return 0;
  }
  return fact[N] / (fact[x] * fact[N - x]);
}

// The same problem but with out Ø
Mod countFull(ull N, ull K) {
  if (N == 0) {
    return 1;
  }
  if (K < N) {
    return 0;
  }

  ull posible_full = K - N + 1;
  ull partial = N - 1;

  Mod ans = 0;
  /* fore(i, 1, posible_full + 1) {
    ans += fact[partial + 1] * comb(posible_full, i) *
           (Mod(N) ^ Mod(posible_full - i));
  } */
  ans = fact[partial + 1] * (((Mod(1)/Mod(N) + Mod(1)) ^ Mod(posible_full)) - Mod(1)) * (Mod(N)^Mod(posible_full));
  return ans;
}

Mod solve(ull N, ull K) {
  Mod ans = 0;

  fore(i, 0, N + 1) {
    Mod this_ans = countFull(i, K) * fact[N] / fact[N - i];
    ans += this_ans;
  }

  return ans;
}

int main() {
  FIN;
  init();
  ull N, K;
  cin >> N >> K;
  cout << solve(N, K) << '\n';

  return 0;
}
