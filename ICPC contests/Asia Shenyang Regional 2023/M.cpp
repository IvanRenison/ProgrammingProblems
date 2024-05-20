// https://codeforces.com/gym/104869/problem/M

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

string bin(ull x, ll lim = 1) {
  string ans = "";
  fore(i, 0, 64) {
    if (x & (1ull << i)) {
      ans += "1";
    } else {
      ans += "0";
    }
  }
  while (ans.size() > lim && ans.back() == '0') {
    ans.pop_back();
  }
  for (ull i = ans.size() - 1; i > 0; i--) {
    if (ans[i] == '0') {
      ans[i] = ' ';
    } else {
      break;
    }
  }
  reverse(ALL(ans));
  return ans;
}

vu pat = {0b00, 0b01, 0b11, 0b10};

void print() {
  set<uu> vis;

  ull x = 0;

  //map<ull, ull> counter;
  ull count = 0;
  ull e = 0;
  ull i = 0;

  while (x < (1 << 20)) {
    /* for (ull i = 9; i < inf; i--) {
      cout << (x & (1ull << i) ? '1' : '0');
    } */
    /* if (64 - __builtin_clzll(x) != last_print) {
      cout << ' ' << count_last_print << '\n';
      cout << 64 - __builtin_clzll(x);
      count_last_print = 1;
      last_print = 64 - __builtin_clzll(x);
    } else {
      count_last_print++;
    } */
    //counter[x]++;
    if ((x & (0b11 << e)) == (pat[i] << e)) {
      cout << bin(x, 20) << ' ' << e << ' ' << bin(count, 20) << ' ' << 64 - __builtin_clzll(count) << '\n';
      i++;
      if (i == 4) {
        i = 0;
        e += 2;
      }
    }

    //cout << bin(x, 10) << ' ' << count << ' ' << bin(count, 10) << '\n';

    count++;

    bool find = false;
    fore(i, 0, 21) {
      ull y = x ^ (1ull << i);
      if (!vis.count({min(x, y), max(x, y)})) {
        vis.insert({min(x, y), max(x, y)});
        x = y;
        find = true;
        break;
      }
    }
    assert(find);
  }

  /* for (auto [x, c] : counter) {
    for (ull i = 13; i < inf; i--) {
      cout << (x & (1ull << i) ? '1' : '0');
    }
    cout << ' ' << c << '\n';
  } */

  /* map<ull, set<ull>> ctz_counter;
  for (auto [x, c] : counter) {
    ull ctz = __builtin_ctzll(x);
    ctz_counter[ctz].insert(c);
  }

  for (auto [ctz, s] : ctz_counter) {
    cout << ctz << ' ';
    for (ull c : s) {
      cout << c << ' ';
    }
    cout << '\n';
  } */


}


typedef array<array<Mod, 2>, 2> Mat;

Mat operator*(const Mat& a, const Mat& b) {
  Mat c;
  fore(i, 0, 2) {
    fore(j, 0, 2) {
      fore(k, 0, 2) {
        c[j][i] += a[k][i] * b[j][k];
      }
    }
  }
  return c;
}

Mat exp(Mat a, ull e) {
  Mat ans = {{{1, 0}, {0, 1}}};

  while (e > 0) {
    if (e & 1) {
      ans = ans * a;
    }
    a = a * a;
    e /= 2;
  }

  return ans;
}


/*
El 0 aparece infinitas veces
El resto de números: x aparece __builtin_clzll(x) / 2 + 1 veces


*/

vu capas = {0, 1, 3, 2};

optional<Mod> solve1(vb s, ull k) {
  if (s.empty()) { // s is 0
    Mat M = {{{4, 1}, {0, 1}}};
    /* fore(i, 0, 2) {
      fore(j, 0, 2) {
        cerr << M[i][j] << ' ';
      }
      cerr << '\n';
    }
    Mat ansM = {{{1, 0}, {0, 1}}};
    fore(_, 0, k - 1) {
      ansM = ansM * M;
      fore(i, 0, 2) {
        fore(j, 0, 2) {
          cerr << ansM[i][j] << ' ';
        }
        cerr << '\n';
      }
      cerr << '\n';
    }
    Mod ans = ansM[0][0] + ansM[0][1] - Mod(1); */
    M = exp(M, k - 1);
    Mod ans = M[0][0] + M[0][1] - Mod(1);
    return ans;
  }

  if (s.size() % 2 == 1) {
    s.push_back(0);
  }

  ull n = s.size();

  vm mods = {1};
  vm caps = {capas[(1ull & s[0]) | ((1 & s[1]) << 1)]};

  ull first_non_zero = s[0] || s[1] ? 0 : inf;

  for (ull i = 2; i < n; i += 2) {
    Mod m = mods.back() * Mod(4) + Mod(1);
    mods.push_back(m);
    Mod c = capas[(1ull & s[i]) | ((1 & s[i + 1]) << 1)];
    c *=  m;
    caps.push_back(c);
    if (first_non_zero == inf && (s[i] || s[i + 1])) {
      first_non_zero = i;
    }
  }

  if (k > first_non_zero / 2 + 1) {
    return {};
  }

  Mod ans = 0;
  for (ull i = n - 2; i < n; i -= 2) {
    //if (i > first_non_zero) {
      ans += caps[i / 2];
    //} else {
      //assert(caps[i / 2] == Mod(0));
      if (k == i / 2 + 1) {
        ans += mods[i / 2] - Mod(1);
        return ans;
      } else {
        //ans += caps[i / 2];
      }
    //}
  }



  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);


  //print();
  //return 0;

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s, t;
    ull k;

    cin >> s >> t >> k,

    reverse(ALL(s)), reverse(ALL(t));

    vb S(max(s.size(), t.size()));
    fore(i, 0, s.size()) {
      S[i] = s[i] == '1';
    }
    fore(i, 0, t.size()) {
      S[i] = S[i] ^ (t[i] == '1');
    }

    while (!S.empty() && !S.back()) {
      S.pop_back();
    }

    auto ans = solve1(S, k);
    if (!ans.has_value()) {
      cout << "-1\n";
    } else {
      cout << *ans << '\n';
    }
  }

  return EXIT_SUCCESS;
}
