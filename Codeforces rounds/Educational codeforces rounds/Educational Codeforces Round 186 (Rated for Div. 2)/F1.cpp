// https://codeforces.com/contest/2182/problem/F1

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

const ull n_lim = 500 + 499 + 1;
const ull c_lim = 61;

vm facts(n_lim), inv_facts(n_lim);

void init() {
  facts[0] = Mod(1);
  inv_facts[0] = Mod(1);
  fore(i, 1, n_lim) {
    facts[i] = facts[i - 1] * Mod(i);
    inv_facts[i] = Mod(1) / facts[i];
  }
}

Mod comb(ull n, ull k) {
  if (k > n) {
    return Mod(0);
  } else {
    assert(n < n_lim), assert(k < n_lim);
    return facts[n] * inv_facts[k] * inv_facts[n - k];
  }
}

// Formas de elegir k o más elementos de n
Mod combMore(ull n, ull k) {
  static vector<vm> dp(n_lim, vm(n_lim));
  static vector<vb> dp_valid(n_lim, vb(n_lim, false));
  assert(n < n_lim), assert(k < n_lim);

  if (dp_valid[n][k]) {
    return dp[n][k];
  }

  Mod ans(k == n);

  if (k < n) {
    ans += comb(n, k) + combMore(n, k + 1);
  }

  dp_valid[n][k] = true;
  dp[n][k] = ans;
  return ans;
}

Mod query(vu& count, ull x) {
  vu count_sums(c_lim + 1);
  fore(c, 0, c_lim) {
    count_sums[c + 1] = count_sums[c] + count[c];
  }

  auto count_sum = [&](ull i, ull j) -> ull {
    return count_sums[j] - count_sums[i];
  };

  auto rec = [&](ull c, ull y, auto&& rec) -> Mod {
    if ((1ull << (c + 1)) <= y) {
      return 0;
    }
    if (y == 0) {
      return Mod(2)^count_sum(0, c + 1);
    }
    if (c == 0) {
      return Mod(y == 1) * ((Mod(2)^count[0]) - Mod(1));
    }

    Mod ans = 0;

    fore(cnt, 0, min(count[c] + 1, c + 1)) {
      Mod this_ans = comb(count[c], cnt);

      ull c_val = ((1ull << (c + 1)) - 1) ^ ((1ull << (c + 1 - cnt)) - 1);

      if (c_val >= y) {
        this_ans *= Mod(2)^count_sum(0, c);
      } else {
        ull ny = (1ull << cnt) * (y - c_val);
        if (ny < (1ull << c)) {
          this_ans *= rec(c - 1, ny, rec);
        } else {
          this_ans = 0;
        }
      }

      ans += this_ans;
    }
    if (count[c] > c) {
      Mod this_ans = combMore(count[c], c + 1) * (Mod(2)^(count_sum(0, c)));
      ans += this_ans;
    }

    return ans;
  };

  Mod ans = rec(c_lim - 1, x, rec);
  return ans;
}

vm solve(vu& cs, vuu& queries) {

  vu csc(c_lim);
  for (ull c : cs) {
    csc[c]++;
  }

  vm ans;
  for (auto [t, x] : queries) {
    if (t == 1) {
      csc[x]++;
    } else if (t == 2) {
      csc[x]--;
    } else if (t == 3) {
      Mod res = query(csc, x);
      ans.push_back(res);
    }
  }

  return ans;
}

Mod force_query(vu& count, ull x) {
  vu cs;
  for (ull c = c_lim; c--;) {
    fore(i, 0, count[c]) {
      cs.push_back(c);
    }
  }

  ull n = cs.size();

  Mod ans = 0;
  fore(mask, 0, (1ull << n)) {
    ull val = 0;
    ull div = 1;
    fore(i, 0, n) {
      if (mask & (1ull << i)) {
        val += (1ull << cs[i]) / div;
        div *= 2;
      }
    }
    if (val >= x) {
      ans += 1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifdef GEN
  cout << "500 500\n";
  fore(i, 0, 500) {
    cout << "60 ";
  }
  fore(i, 0, 499) {
    cout << "1 60\n";
  }
  cout << "3 1\n";

  return 0;
#endif
  init();

#ifndef TEST
  ull n, m;
  cin >> n >> m;
  vu cs(n);
  for (ull& c : cs) {
    cin >> c;
  }
  vuu queries(m);
  for (auto& [t, x] : queries) {
    cin >> t >> x;
  }

  auto ans = solve(cs, queries);
  for (Mod a : ans) {
    cout << a << '\n';
  }
#else
  fore(_, 0, 10000) {
    ull n = rand() % 5;
    vu cs(n);
    fore(i, 0, n) {
      cs[i] = rand() % 5;
    }

    vu count(c_lim);
    for (ull c : cs) {
      count[c]++;
    }

    ull x = rand() % 100;

    Mod ans = query(count, x);
    Mod fans = force_query(count, x);

    if (ans != fans) {
      cout << "ERROR:\n";
      cout << n << ' ' << "1\n";
      for (ull c : cs) {
        cout << c << ' ';
      }
      cout << '\n';
      cout << "3 " << x << '\n';
      cout << "ans = " << ans << ", fans = " << fans << '\n';
      return 1;
    }
  }
#endif
}