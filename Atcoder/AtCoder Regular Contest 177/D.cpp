// https://atcoder.jp/contests/arc177/tasks/arc177_d

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

Mod pow(Mod m, ull e) {
  if (!e)
    return Mod(1);
  Mod r = pow(m, (e / 2));
  r = r * r;
  return e & 1 ? m * r : r;
}

//#define Mod ld

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;


vm force(ull H, const vu& Xs) {
  ull N = Xs.size();

  vuu Xs_i(N);
  fore(i, 0, N) {
    Xs_i[i] = {Xs[i], i};
  }
  sort(ALL(Xs_i));

  vector<vu> chains;
  vuu where_is(N);
  where_is[Xs_i[0].second] = {0, 0};
  chains.push_back({Xs_i[0].second});
  fore(i, 1, N) {
    if (Xs_i[i].first - Xs_i[i - 1].first <= H) {
      chains.back().push_back(Xs_i[i].second);
      where_is[Xs_i[i].second] = {chains.size() - 1, chains.back().size() - 1};
    } else {
      chains.push_back({Xs_i[i].second});
      where_is[Xs_i[i].second] = {chains.size() - 1, 0};
    }
  }

  vm ans(N);
  fore(i, 0, N) {
    fore(x, 0, 1 << (i + 1)) {

      bool valid = true;

      vb destroyed(N, false);

      fore(j, 0, i + 1) {
        auto [a, k] = where_is[j];
        if (j == i && destroyed[j]) {
          valid = false;
        }
        if (x & (1 << j)) {
          while (k < chains[a].size() && !destroyed[chains[a][k]]) {
            destroyed[chains[a][k]] = true;
            k++;
          }
        } else {
          while (k < N  && !destroyed[chains[a][k]]) {
            destroyed[chains[a][k]] = true;
            k--;
          }
        }
      }

      fore(j, 0, N) {
        if (!destroyed[j]) {
          valid = false;;
        }
      }

      if (valid) {
        ++ans[i];
      }
    }

    ans[i] *= pow(Mod(2), (N - i - 1));
  }

  return ans;
}

bool check(const vm& ans) {
  ull N = ans.size();

  Mod sum = 0;
  fore(i, 0, N) {
    sum += ans[i];
  }

  Mod p = pow(Mod(2), N);

  return sum == p;
}


/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
typedef Mod T;
static const T unit = Mod(1);
struct Tree {
  T f(T a, T b) { return a * b; } // (any associative fn)
  vector<T> s; ll n;
  Tree(ll n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct TreeMin {
  typedef ull T;
  static constexpr T unit = inf;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; ll n;
  TreeMin(ll n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct TreeMax {
  typedef ull T;
  static constexpr T unit = 0;
  T f(T a, T b) { return max(a, b); } // (any associative fn)
  vector<T> s; ll n;
  TreeMax(ll n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

vu LDS(const vu& as) {
  // ans[i] = longest decreasing subsequence starting at i
  ull N = as.size();

  vu ans(N);

  ans[N - 1] = 1;
  vu s = {as.back()};

  for (ull i = N - 2; i < N; i--) {
    ull a = as[i];
    while (!s.empty() && a < s.back()) {
      s.pop_back();
    }
    s.push_back(a);
    ans[i] = s.size();
  }

  return ans;
}

// Prov se termina de caer en tiempo t, prov ya se callo todo para el tiempo t
pair<vm, vm> solveChain(const vu& as) {
  ull N = as.size();

  if (N == 1) {
    return {{Mod(1)}, {Mod(1)}};
  }

  vu lds = LDS(as);
  vu as_reversed(as.rbegin(), as.rend());
  vu lds_reversed = LDS(as_reversed);
  reverse(ALL(lds_reversed));

  vuu as_i(N);
  fore(i, 0, N) {
    as_i[i] = {as[i], i};
  }
  sort(ALL(as_i));

  TreeMin firsts(N);
  TreeMax lasts(N);

  vm ans_before(N), ans_now(N);

  fore(a, 0, N) {
    auto [x, i] = as_i[a];
    assert(x == a);

    Mod this_ans_now = 0;
    if (i == 0) {
      ull first_right = firsts.query(1, N);

      if (first_right == inf) {
        this_ans_now = Mod(1) / Mod(2);
      } else {
        ull count = lds[first_right];
        this_ans_now = pow(Mod(1) / Mod(2), count + (first_right != 1));
      }

    } else if (i == N - 1) {
      ull last_left = lasts.query(0, N - 1);

      if (last_left == 0) {
        this_ans_now = Mod(1) / Mod(2);
      } else {
        ull count = lds_reversed[last_left - 1];
        this_ans_now = pow(Mod(1) / Mod(2), count + (last_left - 1 != N - 2));
      }
    } else {
      ull first_right = firsts.query(i + 1, N);
      ull last_left = lasts.query(0, i);

      ull count_right = first_right == inf ? 0 : lds[first_right];
      ull count_left = last_left == 0 ? 0 : lds_reversed[last_left - 1];

      ull count = count_right + count_left;

      if (first_right == i + 1) {
        this_ans_now = pow(Mod(1) / Mod(2), count + 1);
      }
      if (last_left - 1 == i - 1) {
        this_ans_now += pow(Mod(1) / Mod(2), count + 1);
      }
    }

    ans_now[i] = this_ans_now;
    if (a > 0) {
      ans_before[i] = ans_before[as_i[a - 1].second];
    }
    ans_before[i] += this_ans_now;

    firsts.update(i, i);
    lasts.update(i, i + 1);
  }

  return {ans_now, ans_before};
}

vu compress(const vu& xs) {
  ull n = xs.size();

  map<ull, vu> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vu compressed_xs(n);

  ull i = 0;
  for (auto [x, ks] : xs_map) {
    for (ull k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return compressed_xs;
}


vm solve(ull H, const vu& Xs) {
  ull N = Xs.size();

  vuu Xs_i(N);
  fore(i, 0, N) {
    Xs_i[i] = {Xs[i], i};
  }
  sort(ALL(Xs_i));

  vector<vu> chains;
  vuu where_is(N);
  where_is[Xs_i[0].second] = {0, 0};
  chains.push_back({Xs_i[0].second});
  fore(i, 1, N) {
    if (Xs_i[i].first - Xs_i[i - 1].first <= H) {
      chains.back().push_back(Xs_i[i].second);
      where_is[Xs_i[i].second] = {chains.size() - 1, chains.back().size() - 1};
    } else {
      chains.push_back({Xs_i[i].second});
      where_is[Xs_i[i].second] = {chains.size() - 1, 0};
    }
  }

  ull n_chains = chains.size();

  vector<vu> ass(n_chains);
  vector<pair<vm, vm>> solves_chains(n_chains);
  fore(i, 0, n_chains) {
    ass[i] = compress(chains[i]);
    solves_chains[i] = solveChain(ass[i]);
  }

  Tree tree(n_chains, Mod(0));

  vm ans(N);

  fore(a, 0, N) {
    auto [i, j] = where_is[a];

    Mod this_ans = 1;
    this_ans *= tree.query(0, i);
    this_ans *= tree.query(i + 1, n_chains);
    this_ans *= solves_chains[i].first[j];

    ans[a] = this_ans;

    Mod new_val = solves_chains[i].second[j];

    tree.update(i, new_val);
  }

  Mod P = pow(Mod(2), N);
  for (Mod& a : ans) {
    a *= P;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, H;
  cin >> N >> H;
  vu Xs(N);
  for (auto& x : Xs) {
    cin >> x;
  }

  auto ans = solve(H, Xs);
  //cout << setprecision(20);
  for (Mod a : ans) {
    cout << a << ' ';
  }
  cout << '\n';
  //assert(check(ans));

/*   fore(_, 0, 10000) {
    ull N = rand() % 5 + 2;
    ull H = rand() % 5 + 1;
    set<ull> Xs_set;
    while (Xs_set.size() < N) {
      Xs_set.insert(rand() % 10);
    }
    vu Xs(ALL(Xs_set));

    vm ans = solve(H, Xs);
    vm ansf = force(H, Xs);

    if (ans != ansf || !check(ans)) {
      cerr << "ERROR\n";
      cerr << N << ' ' << H << '\n';
      for (ull X : Xs) {
        cerr << X << ' ';
      }
      cerr << '\n';

      cerr << "ans: ";
      for (Mod a : ans) {
        cerr << a << ' ';
      }
      cerr << '\n' << "ansf: ";
      for (Mod a : ansf) {
        cerr << a << ' ';
      }
      cerr << endl;
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
