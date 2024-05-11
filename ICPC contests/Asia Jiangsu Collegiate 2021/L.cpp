// https://codeforces.com/gym/103495/problem/L

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

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

const ull max_n = 200000;
array<Mod, max_n + 1> fact;

void init() {
  fact[0] = 1;
  fore(i, 0, max_n) {
    fact[i + 1] = fact[i] * Mod(i + 1);
  }
}


typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;
typedef tuple<Mod, Mod, Mod> mmm;
typedef vector<mmm> vmmm;
typedef tuple<Mod, Mod, Mod, Mod> mmmm;
typedef vector<mmmm> vmmmm;

optional<vu> necks(const vector<vu>& suns, const vu& as) {
  ull n = suns.size();

  bool ans_valid = true;
  vu ans(n, inf);

  function<ull(ull)> f = [&](ull i) -> ull {

    ull& this_ans = ans[i];

    set<ull> sun_set;
    for (ull j : suns[i]) {
      sun_set.insert(j);
    }

    for (ull j : suns[i]) {
      ull rec = f(j);
      if (rec != inf && !sun_set.count(rec)) {
        if (this_ans != inf) {
          ans_valid = false;
          return 0;
        }
        this_ans = rec;
      }
    }

    if (as[i] == inf) {
      return this_ans;
    }

    if (as[i] == i) {
      if (this_ans != inf) {
        ans_valid = false;
      } else {
        this_ans = i;
      }
    } else if (sun_set.count(as[i])) {
      return this_ans;
    } else {
      if (this_ans != inf) {
        ans_valid = false;
      } else {
        this_ans = as[i];
      }
    }
    return this_ans;
  };

  f(0);

  if (ans_valid && (ans[0] == inf || ans[0] == 0)) {
    return ans;
  } else {
    return {};
  }
}

bool possible(const vector<vu>& suns, const vu& as) {
  return necks(suns, as).has_value();
}

Mod force(const vu& ps, const vu& as) {
  ull n = ps.size() + 1;

  vector<vu> suns(n);
  fore(i, 1, n) {
    suns[ps[i - 1]].push_back(i);
  }

  vu bs(n);
  iota(ALL(bs), 0);

  Mod ans = 0;
  do {
    bool valid = true;
    fore(i, 0, n) {
      if (as[i] != inf && as[i] != bs[i]) {
        valid = false;
        break;
      }
    }
    if (valid) {
      if (possible(suns, bs)) {
        /* for (ull b : bs) {
          cerr << b + 1 << ' ';
        }
        cerr << '\n'; */
        ans += 1;
      }
    }

  } while (next_permutation(ALL(bs)));

  return ans;
}

Mod solve(const vu& ps, const vu& as) {
  ull n = ps.size() + 1;

  vector<vu> suns(n);
  fore(i, 1, n) {
    suns[ps[i - 1]].push_back(i);
  }

  optional<vu> necks_opt = necks(suns, as);
  if (!necks_opt.has_value()) {
    return 0;
  }
  vu necks = necks_opt.value();

  set<ull> as_set;
  for (ull a : as) {
    if (a != inf) {
      as_set.insert(a);
    }
  }

  function<Mod(ull)> f = [&](ull i) -> Mod {
    ull count_infs = as[i] == inf;
    for (ull j : suns[i]) {
      count_infs += necks[j] == inf;
    }
    Mod ans = fact[count_infs];
    for (ull j : suns[i]) {
      ans *= f(j);
    }
    return ans;
  };

  Mod ans = f(0);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu ps(n - 1), as(n);
    for (ull& p : ps) {
      cin >> p;
      p--;
    }
    for (ull& a : as) {
      cin >> a;
      if (a == 0) {
        a = inf;
      } else {
        a--;
      }
    }

    //cerr << "\n1 2 3 4 5 6 7\n\n";

    Mod ans = solve(ps, as);
    cout << ans << '\n';
  }

/*   fore(_, 0, 1000) {
    ull n = rand() % 5 + 2;
    vu ps(n - 1), as(n);
    fore(i, 1, n) {
      ps[i - 1] = rand() % i;
    }
    iota(ALL(as), 0);
    random_shuffle(ALL(as));
    for (ull& a : as) {
      if (rand() % 2) {
        a = inf;
      }
    }

    Mod ans1 = solve(ps, as);
    Mod ans2 = force(ps, as);

    if (ans1 != ans2) {
      cerr << "FAIL\n";
      cerr << n << '\n';
      for (ull p : ps) {
        cerr << p << ' ';
      }
      cerr << '\n';
      for (ull a : as) {
        cerr << a << ' ';
      }
      cerr << '\n';
      cerr << ans1 << ' ' << ans2 << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
/*

7
1 2 2 3 2 4
0 0 0 2 0 0 0

1234567
13572
135 2 7
14572
145 2 7
16572
165 2 7


*/