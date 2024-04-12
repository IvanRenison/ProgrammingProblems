// https://codeforces.com/contest/1954/problem/D

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

Mod force(const vu& as) {
  Mod ans = 0;
  ull  n = as.size();

  fore(x, 1, 1 << n) {
    ull m = 0;
    ull total = 0;
    fore(i, 0, n) {
      if (x & (1 << i)) {
        m = max(m, as[i]);
        total += as[i];
      }
    }

    ans += max((total + 1) / 2, m);
  }

  return ans;
}

Mod solve(vu& as) {
  ull n = as.size();

  sort(ALL(as));

  vector<vm> dp_counts(n + 1, vm(5001));
  // d[i + 1][j] hasta el i, cuantos subconjuntos hay con suma igual a j
  //vector<vm> dp_sums(n + 1, vm(5001));

  dp_counts[0][0] = Mod(1);
  fore(i, 0, n) {
    ull a = as[i];
    fore(j, 0, a) {
      dp_counts[i + 1][j] = dp_counts[i][j];
      //dp_sums[i + 1][j] = dp_sums[i][j];
    }
    fore(j, a, 5001) {
      dp_counts[i + 1][j] = dp_counts[i][j] + dp_counts[i][j - a];
      //dp_sums[i + 1][j] = dp_sums[i][j] + dp_sums[i][j - a] + Mod(a);
    }
  }

  Mod ans = 0;

  fore(i, 0, n) {
    ull a = as[i];

    Mod count_le_2a;
    Mod sum_more_2a;
    fore(j, 0, 5001) {
      if (j <= a) {
        count_le_2a += dp_counts[i][j];
      } else {
        sum_more_2a += Mod((j + a + 1)/2) * dp_counts[i][j];
      }
    }

    ans += count_le_2a * Mod(a) + sum_more_2a;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;

  vu as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  auto ans = solve(as);
  cout << ans << '\n';

/*   fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    vu as(n);
    fore(i, 0, n) {
      as[i] = rand() % 10 + 1;
    }

    auto ans1 = solve(as);
    auto ans2 = force(as);
    if (ans1 != ans2) {
      cout << "Error\n";
      cout << n << '\n';
      fore(i, 0, n) {
        cout << as[i] << ' ';
      }
      cout << '\n';
      cout << ans1 << ' ' << ans2 << '\n';
      break;
    }
  } */

  return EXIT_SUCCESS;
}
