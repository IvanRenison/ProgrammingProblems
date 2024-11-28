// https://codeforces.com/contest/2039/problem/E

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

const ull n_lim = 1e6 + 1;

vm dp(n_lim);

ll basic_withExtra(ll n) {
  if (n <= 3) {
    return 0;
  }

/*   ll ans2 = 0;
  fore(i, 0, n - 3) { // ending in 101^i
    ans2 += (n - i - 2);
  } */

  ll ans = (n - 2) * (n - 1) / 2 - 1;

  //cerr << n << ' ' << ans << ' ' << ans2 << endl;

  return ans;
}

ll basic(ll n) {
  if (n == 2) {
    return 1;
  } else if (n == 3) {
    return 2;
  } else {
    return n - 1;
  }
}

void solve() {
  Mod sum;
  fore(i, 4, n_lim) {
    dp[i] = Mod(basic_withExtra(i));
    /* fore(j, 4, i) {
      dp[i] += dp[j] * Mod(j);
    } */
    dp[i] += sum;
    sum += dp[i] * Mod(i);
  }

  fore(i, 2, n_lim) {
    dp[i] += dp[i-1];
  }
  fore(i, 2, n_lim) {
    dp[i] += basic(i);
  }
}

ll force(ll n) {
  set<vi> ans;

  function<void(vi)> rec = [&](vi xs) {
    if (xs.size() == n) {
      ans.insert(xs);
      return;
    }

    ll inv_count = 0;
    fore(i, 0, xs.size()) fore(j, 0, i) {
      if (xs[j] > xs[i]) {
        inv_count++;
      }
    }

    fore(i, 0, xs.size() + 1) {
      vi ys = xs;
      ys.insert(ys.begin() + i, inv_count);
      rec(ys);
    }
  };

  rec(vi({0, 1}));

  return ans.size();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    Mod ans = dp[n];
    cout << ans << '\n';
  }
#else
  fore(i, 2, 10) {
    ll f = force(i);
    cerr << i << ' ' << dp[i] << ' ' << f << endl;
  }
#endif
}
