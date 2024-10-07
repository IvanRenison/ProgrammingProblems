// https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-1/problems/E

#ifdef PRAGMAS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>
#include <omp.h>

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

const __uint8_t inf = -1;
const ld eps = 1e-7;

// Based on ModularArithmetic of kactl
constexpr ull mod = 998244353; // Prime number for division to work
struct Mod {
  unsigned int x;
  Mod(ull xx) : x(xx % mod) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) const {
    return Mod((x + b.x) >= mod ? x + b.x - mod : x + b.x);
  }
  Mod operator-(Mod b) const {
    return Mod(x >= b.x ? x - b.x : x + mod - b.x);
  }
  Mod operator*(Mod b) const {
    return Mod(((ull)x * (ull)b.x) % mod);
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

string merge(const string& s0, const string& s1) {
  string s;
  fore(i, 0, min(s0.size(), s1.size())) {
    if (s0[i] == s1[i]) {
      s.push_back(s0[i]);
    } else if (s0[i] == '?') {
      s.push_back(s1[i]);
    } else if (s1[i] == '?') {
      s.push_back(s0[i]);
    } else {
      break;
    }
  }
  return s;
}

Mod solve(vector<string>& Ss) {
  ull N = Ss.size();

  vector<string> merges(1 << N);
  merges[0] = string(100, '?');

  Mod ans = 0;

  fore(n, 1, N + 1) {
    for (ull x = (1 << n) - 1, c, r; x < (1 << N); c = x&-x, r = x+c, x = (((r^x) >> 2)/c) | r) {
      ull i = 63 - __builtin_clzll(x);
      //assert(x & (1 << i));
      merges[x] = merge(merges[x ^ (1 << i)], Ss[i]);


      Mod p = 1;
      Mod this_ans = 1;
      for (char c : merges[x]) {
        if (c == '?') {
          p *= 26;
        }
        this_ans += p;
      }
      if (__builtin_popcount(x) % 2 == 1) {
        ans += this_ans;
      } else {
        ans -= this_ans;
      }
    }

    if (n > 1) {
      for (ull x = (1 << (n - 1)) - 1, c, r; x < (1 << N); c = x&-x, r = x+c, x = (((r^x) >> 2)/c) | r) {
        merges[x].clear();
      }
    } else {
      merges[0].clear();
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  omp_set_num_threads(16);

  ull t;
  cin >> t;

  vector<vector<string>> inputs(t);

  fore(testCase, 0, t) {
    ull N;
    cin >> N;
    vector<string> Ss(N);
    for (string& S : Ss) {
      cin >> S;
    }
    inputs[testCase] = Ss;
  }

  vm ans(t);

  #pragma omp parallel for
  for (ull testCase = 0; testCase < t; testCase++) {
    ans[testCase] = solve(inputs[testCase]);
  }

  for (ull testCase = 0; testCase < t; testCase++) {
    cout << "Case #" << testCase + 1 << ": ";
    cout << ans[testCase] << '\n';
  }
}
