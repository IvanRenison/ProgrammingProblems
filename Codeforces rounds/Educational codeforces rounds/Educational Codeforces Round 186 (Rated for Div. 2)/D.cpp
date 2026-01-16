// https://codeforces.com/contest/2182/problem/D

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

// Based on ModularArithmetic of kactl
constexpr ull mod = 998244353; // Prime number for division to work
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
    Mod r = a ^ (mod - 2);
    return r;
  }
  Mod operator^(ull e) const {
    Mod r = Mod(1);
    Mod b = *this;
    while (e > 0) {
      if (e & 1) {
        r *= b;
      }
      b *= b;
      e /= 2;
    }
    return r;
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

ull n_lim = 51;

vm facts(n_lim), inv_facts(n_lim);

void init() {
  facts[0] = Mod(1);
  inv_facts[0] = Mod(1);
  fore(i, 1, n_lim) {
    facts[i] = facts[i - 1] * Mod(i);
    inv_facts[i] = Mod(1) / facts[i];
  }
}

Mod comb(ull n, ull k) {
  if (k > n) {
    return Mod(0);
  } else {
    return facts[n] * inv_facts[k] * inv_facts[n - k];
  }
}

Mod solve(vu& As) {
  ull n = As.size() - 1;

  ull a0 = As[0];
  vu as(As.begin() + 1, As.end());

  sort(ALL(as));
  reverse(ALL(as));

  ull maxA = as[0];
  ull count_maxA = 1;
  fore(i, 1, n) {
    if (as[i] < maxA) {
      ull d = maxA - 1 - as[i];
      if (d > a0) {
        return Mod(0);
      } else {
        as[i] += d;
        a0 -= d;
      }
    } else {
      count_maxA++;
    }
  }


  if (count_maxA + a0 >= n) {
    return facts[n];
  }

  Mod ans = comb(n - count_maxA, a0) * facts[a0 + count_maxA] * facts[n - count_maxA - a0];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n + 1);
    for (ull& a : as) {
      cin >> a;
    }

    auto ans = solve(as);
    cout << ans << '\n';
  }

}


/*   ull a_max_i = 1;
  ull a_max = as[0];
  fore(i, 1, n) {
    if (as[i] > a_max) {
      a_max = as[i];
      a_max_i = i;
    }
  }

  fore(i, 0, a_max_i) {
    ull d = a_max - as[i];
    if (d > a0) {
      return 0;
    } else {
      as[i] += d;
      a0 -= d;
    }
  }
  fore(i, a_max_i + 1, n) {
    ull d = a_max - 1 - as[i];
    if (d > a0) {
      return 0;
    } else {
      as[i] += d;
      a0 -= d;
    }
  }
  fore(i, a_max_i + 1, n) {
    if (a0 == 0) {
      break;
    }
    as[i]++;
    a0--;
  }

  if (a0 > n) {
    fore(i, 0, n) {
      as[i] += a0 / n;
    }
    a0 %= n;
  }

  fore(i, 0, a0 + 1) {
    as[i]++;
  }
  a0 = 0; */