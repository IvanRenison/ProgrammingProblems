// https://codeforces.com/contest/1989/problem/E

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

Mod solve(ull n, ull k) {

  Mod ans = 0;

  {
    vector<vm> dp(2, vm(n)), dp_sums(2, vm(n));
    dp[0][0] = dp[1][0] = Mod(1);
    dp_sums[0][0] = dp_sums[1][0] = Mod(1);
    fore(i, 1, n) {
      fore(x, 0, 2) {
        dp[x][i] = Mod(1) + dp[!x][i - 1];
        if (i > 2) {
          dp[x][i] += dp_sums[!x][i - 3];
        }
        if (i == n - 1 && i > 1) {
          dp[x][i] += dp[!x][i - 2];
        }

        dp_sums[x][i] = dp_sums[x][i - 1] + dp[x][i];
      }
    }

    ans += dp[0][n - 1];
  }
  {
    vector<vector<vm>> dp(2, vector(n, vm(k))), dp_sums(2, vector(n, vm(k)));
    dp[0][0][1] = dp[1][0][1] = Mod(1);
    dp_sums[0][0][1] = dp_sums[1][0][1] = Mod(1);
    fore(i, 1, n) {
      fore(j, 1, k) {
        fore(x, 0, 2) {
          dp[x][i][j] = Mod(j == 1) + dp[!x][i - 1][j - 1];
          if (i > 2) {
            dp[x][i][j] += dp_sums[!x][i - 3][j - 1];
          }
          if (i == n - 1 && i > 1) {
            dp[x][i][j] += dp[!x][i - 2][j - 1];
          }

          dp_sums[x][i][j] = dp_sums[x][i - 1][j] + dp[x][i][j];
        }
      }
    }

    fore(j, 1, k) {
      ans -= dp[0][n - 1][j];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, k;
  cin >> n >> k;

  auto ans = solve(n, k);
  cout << ans << '\n';

}
/*
0000 x
0001 x
0010 y -> 2111
0011 x
0100 y -> 1112
0101 y -> 1111
0110 y -> 1111
0111 x


*/