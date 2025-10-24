// https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/B2

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


/** Author: Håkan Terelius
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: s[i] = smallest prime factor of i (except for i = 0, 1).
 * \texttt{sieve} returns sorted primes
 * less than L$. \texttt{fact} returns sorted {prime,
 * exponent} pairs of the factorization of n$.
 * Status: Stress-tested
 */
const ll L = 1e7 + 5;
array<ll, L> s;
vi p;
vi sieve() {
  for (ll i = 4; i < L; i += 2) s[i] = 2;
  for (ll i = 3; i * i < L; i += 2) if (!s[i])
    for (ll j=i*i; j < L; j += 2*i) if (!s[j]) s[j] = i;
  fore(i,2,L) if (!s[i]) p.push_back(i), s[i] = i;
  return p;
}

vector<ii> fact(ll n) {
  vector<ii> res;
  for (ull i = 1; i * i <= n; i++) {
    assert(i < L);
    if (s[i] == i) {
      ull cnt = 0;
      while (n % i == 0) n /= i, cnt++;
      if (cnt > 0) res.push_back({i, cnt});
    }
  }
  if (n > 1) res.push_back({n, 1});
  return res;
}

/** Author: Pietro Palombini
 * Date: 2024-10-11
 * License: CC0
 * Description: Given the prime factorization of a number,
 * returns all its divisors.
 * Time: O(d), where d$ is the number of divisors.
 * Status: stress-tested
 */
vi divisors(vector<ii>& f) {
  vi res = {1};
  for (auto& [p, k] : f) {
    ll sz = SZ(res);
    fore(i,0,sz) for(ll j=0,x=p;j<k;j++,x*=p) res.push_back(res[i]*x);
  }
  return res;
}

vm facts(100);
void init_facts() {
  facts[0] = Mod(1);
  fore(i, 1, 100) {
    facts[i] = facts[i - 1] * Mod(i);
  }
}

Mod simpSolve(ull N, ull A) {
  vii facsA = fact(A);

  Mod ans = 1;
  for (auto [p, e] : facsA) {
    assert(e < 100);
    Mod this_ans = 1;
    fore(x, N, N + e) {
      this_ans *= Mod(x);
    }
    fore(x, 1, e + 1) {
      this_ans /= Mod(x);
    }
    ans *= this_ans;
  }

  return ans;
}

Mod solve(ull N, ull A, ull B) {

  vii facsB = fact(B);
  vi divsB = divisors(facsB);

  Mod ans = 0;
  for (ull d : divsB) if (d <= A) {
    Mod ans_left = simpSolve(N, d);
    Mod ans_right = simpSolve(N, B / d);
    ans += ans_left * ans_right;
  }

  return ans;
}

Mod force(ull N, ull A, ull B) {
  Mod ans = 0;

  auto rec = [&](auto&& rec, vu as) {
    if (as.size() >= N && as[N - 1] > A) {
      return;
    }
    if (as.back() > B || (as.size() < N && as.back() > A)) {
      return;
    }
    if (as.size() == 2 * N) {
      if (as.back() == B) {
        ans += 1;
/*         for (ull a : as) {
          cerr << a << " ";
        }
        cerr << endl; */
      }
    } else {
      fore(x, 1, B + 1) {
        ull y = as.back() * x;
        as.push_back(y);
        rec(rec, as);
        as.pop_back();
      }
    }
  };

  fore(x, 1, B + 1) {
    vu as = {x};
    rec(rec, as);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve();
  init_facts();

#ifndef TEST
  ull t;
  cin >> t;

  fore(testCase, 0, t) {
    ull N, A, B;
    cin >> N >> A >> B;

    auto ans = solve(N, A, B);

    cout << "Case #" << testCase + 1 << ": ";
    cout << ans << '\n';
  }
#else
  fore(_, 0, 1000) {
    ull N = rand() % 10 + 1;
    ull A = rand() % 7 + 1;
    ull B = rand() % 7 + 1;

    Mod ans = solve(N, A, B);
    Mod ansf = force(N, A, B);
    if (ans != ansf) {
      cerr << "Mismatch!" << endl;
      cerr << N << " " << A << " " << B << endl;
      cerr << "ans: " << ans << endl;
      cerr << "ansf: " << ansf << endl;
      return 1;
    }
  }
#endif
}
