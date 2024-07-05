//

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

//#pragma GCC optimize("Ofast,unroll-loops,modulo-sched,modulo-sched-allow-regmoves,gcse-sm,gcse-las,ipa-pta,tree-loop-im,tree-loop-ivcanon,ivopts,tree-vectorize")
//#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,tune=native")
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef int ll;
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


Mod solve(ull N, const string& S) {
  ull m = S.size();

  ll val = 0, min_val = 0;
  fore(i, 0, m) {
    if (S[i] == '(') {
      val++;
    } else {
      val--;
    }
    min_val = min(min_val, val);
  }

  vector<vector<vm>> dp(2, vector<vm>(m + 5, vm(N + 2)));
  // dp[i][c][false] = ya puse i caracteres y puse c mas '(' que ')' y todavía no puse S
  // dp[i][c][true] = ya puse i caracteres y puse c mas '(' que ')' y ya no puse S

  dp[false][0][0] = 1;

  fore(i, 0, N) {
    dp[false][(i + 1) % (m + 5)] = vm(N + 2);
    dp[true][(i + 1) % (m + 5)] = vm(N + 2);
    dp[false][(i + 1) % (m + 5)][0] = dp[false][i % (m + 5)][1]; // solo puedo poner ')'
    dp[true][(i + 1) % (m + 5)][0] = dp[true][i % (m + 5)][1]; // solo puedo poner ')'
    if (i + 1 >= m) { // Poner S
      if (val <= 0 && abs(val) >= abs(min_val) && -val <= N) {
        dp[true][(i + 1) % (m + 5)][0] += dp[false][(i + 1 - m) % (m + 5)][-val];
      }
    }

    fore(c, 1, N + 1) {
      // Poner '('
      dp[false][(i + 1) % (m + 5)][c] += dp[false][i % (m + 5)][c - 1];
      // Poner ')'
      dp[false][(i + 1) % (m + 5)][c] += dp[false][i % (m + 5)][c + 1];
      // Poner '('
      dp[true][(i + 1) % (m + 5)][c] += dp[true][i % (m + 5)][c - 1];
      // Poner ')'
      dp[true][(i + 1) % (m + 5)][c] += dp[true][i % (m + 5)][c + 1];
      if (i + 1 >= m) { // Poner S
        if (val <= (ll)c && abs(min_val) <= (ll)c - val && c - val <= N) {
          dp[true][(i + 1) % (m + 5)][c] += dp[false][(i + 1 - m) % (m + 5)][c - val];
        }
      }
    }
  }

  Mod ans = dp[true][(N) % (m + 5)][0];

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  string S;
  cin >> S;

  auto ans = solve(N, S);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
