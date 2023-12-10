// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN 1001

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = (1e9 + 7);
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator*(Mod b) {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
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

Mod fact[MAXN];

void init() {
  fact[0] = 1;
  fore(i, 1, MAXN) {
    fact[i] = fact[i - 1] * Mod(i);
  }
}

Mod solve(ull n, ull x, ull pos) {

  // Make a binary search storing the visited places
  ull count_lower = 0, count_upper = 0;
  ull lower = 0;
  ull upper = n;
  while (lower < upper) {
    ull m = (lower + upper) / 2;
    if (m <= pos) {
      lower = m + 1;
      if (m != pos) {
        count_lower++;
      }
    } else {
      upper = m;
      if (m != pos) {
        count_upper++;
      }
    }
  }

  if (x < count_lower || n - x - 1 < count_upper) {
    return 0;
  }

  return fact[x] / fact[x - count_lower] * fact[n - x - 1] /
         fact[n - x - 1 - count_upper] *
         fact[n - count_lower - count_upper - 1];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  init();

  ull n, x, pos;
  cin >> n >> x >> pos;

  cout << solve(n, x - 1, pos) << '\n';

  return EXIT_SUCCESS;
}
