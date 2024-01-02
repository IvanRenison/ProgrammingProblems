// https://codeforces.com/contest/1916/problem/H2

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = 998244353;
struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
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

typedef vector<Mod> vm;

vm solve(ull n, ull p, ull k) {

  vm p_pow(k + 1, 1);
  fore(i, 1, k + 1) {
    p_pow[i] = p_pow[i - 1] * Mod(p);
  }

  Mod pn = Mod(p) ^ n;

  vector<Mod> pnpj2(k + 1);
  fore(j, 0, k + 1) {
    Mod pnpj = pn - p_pow[j];
    pnpj2[j] = pnpj * pnpj;
  }

  vm ans(k + 1), nums(k + 1), dens(k + 1);
  ans[0] = nums[0] = dens[0] = 1;

  fore(r, 1, k + 1) {
    nums[r] = nums[r - 1] * pnpj2[r - 1];
    dens[r] = dens[r - 1] * p_pow[r - 1] * (p_pow[r] - Mod(1));
    if (dens[r].x > 0) {
      ans[r] = nums[r] / dens[r];
    } else if (nums[r].x == 0) {
      ans[r] = 0;
    } else {
      ans[r] = 1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, p, k;
  cin >> n >> p >> k;

  vm ans = solve(n, p, k);
  for (Mod a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
