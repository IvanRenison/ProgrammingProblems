// https://codeforces.com/gym/104270/problem/L

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

constexpr ull mod = (1e9 + 7);
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
  }
  Mod operator*(Mod b) const {
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
  bool operator==(Mod b) const {
    return x == b.x;
  }
  bool operator!=(Mod b) const {
    return x != b.x;
  }
  bool operator<(Mod b) const {
    return x < b.x;
  }
  bool operator>(Mod b) const {
    return x > b.x;
  }
  bool operator<=(Mod b) const {
    return x <= b.x;
  }
  bool operator>=(Mod b) const {
    return x >= b.x;
  }

  Mod invert(Mod a) const {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) const {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) const {
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
    is >> m.x;
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

const ull maxn = 1e5;

vm facts(2*maxn + 1);
vm inv_facts(2*maxn + 1);
vm pow_tows(maxn + 1);
vm inv_pow_tows(maxn + 1);

void init() {
  facts[0] = inv_facts[0] = 1;
  fore(i, 1, 2*maxn + 1) {
    facts[i] = facts[i - 1] * Mod(i);
    inv_facts[i] = Mod(1) / facts[i];
  }

  pow_tows[0] = inv_pow_tows[0] = 1;
  fore(i, 1, maxn + 1) {
    pow_tows[i] = pow_tows[i - 1] * Mod(2);
    inv_pow_tows[i] = Mod(1) / pow_tows[i];
  }
}

Mod comb(ull n, ull k) {
  assert(n >= k);
  return facts[n] * inv_facts[k] * inv_facts[n - k];
}

Mod combNoCons(ull n, ull k) {
  return comb(n - k + 1, k);
}

Mod solve1(ull n, ull m) {
  if (m > n) {
    return 0;
  }
  if (m == n) {
    return facts[n - 1] / Mod(2);
  }
  if (m == 0) {
    return 1;
  }

  ull k = n - m;


  Mod ans;

  fore(i, 0, k) { // i alone nodes
    ull j = k - i; // j chains
    if (i + 2 * j <= n) {
      Mod this_ans = comb(n, i);
      this_ans *= facts[n - i] * combNoCons(n - i - 3, j - 1) * inv_facts[j] * inv_pow_tows[k - i];

      ans += this_ans;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  init();

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    auto ans = solve1(n, m);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
