// https://codeforces.com/contest/2025/problem/B

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
constexpr ull mod = (1e9 + 7); // Prime number for division to work
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

vm solve(vuu& nks) {
  ull t = nks.size();

/*   ull N = 200;
  vector<vu> C(N + 1, vu(N + 1));
  for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)
    C[n][0] = 1;
    C[n][n] = 1;
    for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)
        C[n][k] = C[n][k - 1] + C[n - 1][k - 1];
  } */

  vm ans(t);
  fore(i, 0, t) {
    auto [n, k] = nks[i];
    //ans[i] = C[n][k];
    ans[i] = Mod(2) ^ k;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;
  vuu nks(t);
  fore(i, 0, t) {
    cin >> nks[i].first;
  }
  fore(i, 0, t) {
    cin >> nks[i].second;
  }

  auto ans = solve(nks);
  for (auto& a : ans) {
    cout << a << '\n';
  }

}
