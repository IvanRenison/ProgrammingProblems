#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v)sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

constexpr ull mod = (1e9 + 7);

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

struct Mod {
  ull x;
  Mod(ull xx) : x(xx % mod) {}
  Mod(ll xx) : x(xx % mod) {}
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
    return *this = *this + Mod(1ull);
  }
  Mod operator--() {
    return *this = *this - Mod(1ull);
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
      return Mod(1ull);
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

/*
Primeros términos:
                                                         f1
                                                f2
                                       f3
f4  = c**(2*4-6) * f3*f2*f1 = c**2   * f3     * f2     * f1
f5  = c**(2*5-6) * f4*f3*f2 = c**6   * f3**2  * f2**2  * f1
f6  = c**6 * f5*f4*f3       = c**14  * f3**4  * f2**3  * f1**2
f7  = c**8 * f6*f5*f4       = c**30  * f3**7  * f2**6  * f1**4
f8  = c**10 * f7*f6*f5      = c**60  * f3**13 * f2**11 * f1**7
f9  = c**12 * f8*f7*f6      = c**116 * f3**24 * f2**20 * f1**13
f10 = c**14 * f9*f8*f7      = c**220 * f3**44 * f2**37 * f1**24

Llamemos c_i, f3_i, f2_i, f1_i a los exponentes de c, f3, f2 y f1 en fi

Notar que:
  f2_i = f3_(i-1) + f3_(i-2)
  f1_i = f3_(i-1)

Así que alcanza con calcular los f3_i y los c_i

Busco una recurrencia para los f3_i:
  f3_i = f3_(i-1) + f3_(i-2) + f3_(i-3)

  [1 1 1][f3_3]   [1 1 1][1]   [1]   [f3_4]
  [1 0 0][f3_2] = [1 0 0][0] = [1] = [f3_3]
  [0 1 0][f3_1]   [0 1 0][0]   [0]   [f3_2]

  Y en general:
    [1 1 1]^k[f3_3]   [1 1 1]^k[1]   [f3_(k+3)]
    [1 0 0]  [f3_2] = [1 0 0]  [0] = [f3_(k+2)]
    [0 1 0]  [f3_1]   [0 1 0]  [0]   [f3_(k+1)]


Busco una recurrencia para los c_i:
  c_i = c_(i-1) + c_(i-2) + c_(i-3) + (2*i - 6)

  Primero vuelvo lineal la recurrencia:
    c_i - c_(i-1) = c_(i-1) + c_(i-2) + c_(i-3) + (2*i - 6) - (c_(i-2) + c_(i-3) + c_(i-4) + (2*(i-1) - 6))
                  = c_(i-1) - c_(i-4) + (2*i - 6) - (2*i - 2 - 6)
                  = c_(i-1) - c_(i-4) + 2
      ⇒
      c_i = 2*c_(i-1) - c_(i-4) + 2

    c_i - c_(i-1) = 2*c_(i-1) - c_(i-4) + 2 - (2*c_(i-2) - c_(i-5) + 2)
                  = 2*c_(i-1) - 2*c_(i-2) - c_(i-4) + c_(i-5)
      ⇒
      c_i = 3*c_(i-1) - 2*c_(i-2) - c_(i-4) + c_(i-5)

  Entonces:
  [3 -1  0 -1  1]^k[c_5]   [c_(k+5)]
  [1  0  0  0  0]  [c_4]   [c_(k+4)]
  [0  1  0  0  0]  [c_3] = [c_(k+3)]
  [0  0  1  0  0]  [c_2]   [c_(k+2)]
  [0  0  0  1  0]  [c_1]   [c_(k+1)]


Igualmente voy a usar el código de recurrencia lineal de l vasito, así que no voy usar
parte de este análisis (si la parte de volver lineal la recurrencia)

*/
constexpr ull mod_exp = mod - 1;
//init O(n^2log) query(n^2 logk)
//input: terms: first n term; trans: transition function; MOD; LOG=mxlog of k
//output calc(k): kth term mod MOD
//example: {1,1} {2,1} an=2*a_(n-1)+a_(n-2); calc(3)=3 calc(10007)=71480733
struct LinearRec {
  typedef vector<ll> vi;
  const ll LOG = 60;
  ll n;
  vi terms, trans;
  vector<vi> bin;
  vi add(vi& a, vi& b) {
    vi res(n * 2 + 1);
    fore(i, 0, n + 1) fore(j, 0, n + 1) res[i + j] =
        (res[i + j] * 1LL + (ll)a[i] * b[j]) % mod_exp;
    for (ll i = 2 * n; i > n; --i) {
      fore(j, 0, n) res[i - 1 - j] =
          (res[i - 1 - j] * 1LL + (ll)res[i] * trans[j]) % mod_exp;
      res[i] = 0;
    }
    res.erase(res.begin() + n + 1, res.end());
    return res;
  }
  LinearRec(vi& terms, vi& trans) : terms(terms), trans(trans) {
    n = trans.size();
    vi a(n + 1);
    a[1] = 1;
    bin.push_back(a);
    fore(i, 1, LOG) bin.push_back(add(bin[i - 1], bin[i - 1]));
  }
  ll calc(ll k) {
    vi a(n + 1);
    a[0] = 1;
    fore(i, 0, LOG) if ((k >> i) & 1) a = add(a, bin[i]);
    ll ret = 0;
    fore(i, 0, n) ret = ((ll)ret + (ll)a[i + 1] * terms[i]) % mod_exp;
    return ret;
  }
};

Mod solve(ull n, ull f1, ull f2, ull f3, ull c) {

  vector<ll> c_terms = {0, 0, 0, 2, 6};
  vector<ll> f3_terms = {0, 0, 1};
  vector<ll> f2_terms = {0, 1, 0};
  vector<ll> f1_terms = {1, 0, 0};

  vector<ll> c_trans = {3, mod_exp - 2, 0, mod_exp - 1, 1};
  vector<ll> f3_trans = {1, 1, 1};
  vector<ll> f2_trans = {1, 1, 1};
  vector<ll> f1_trans = {1, 1, 1};

  ll c_exp = LinearRec(c_terms, c_trans).calc(n);
  ll f3_exp = LinearRec(f3_terms, f3_trans).calc(n);
  ll f2_exp = LinearRec(f2_terms, f2_trans).calc(n);
  ll f1_exp = LinearRec(f1_terms, f1_trans).calc(n);

  return (Mod(c) ^ Mod(c_exp)) * (Mod(f1) ^ Mod(f1_exp)) *
         (Mod(f2) ^ Mod(f2_exp)) * (Mod(f3) ^ Mod(f3_exp));
}

int main() {
  FIN;

  ull n, f1, f2, f3, c;
  cin >> n >> f1 >> f2 >> f3 >> c;

  cout << solve(n, f1, f2, f3, c) << '\n';

  return 0;
}
