// https://codeforces.com/contest/2053/problem/D

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



vm solve(const vu& as, const vu& bs, const vuu& upds) {
  ull n = as.size(), q = upds.size();


  vuu as_i(n), bs_i(n);
  fore(i, 0, n) {
    as_i[i] = {as[i], i};
    bs_i[i] = {bs[i], i};
  }

  sort(ALL(as_i));
  sort(ALL(bs_i));

  vu a_poss(n), b_poss(n);
  fore(i, 0, n) {
    a_poss[as_i[i].second] = i;
    b_poss[bs_i[i].second] = i;
  }

  Mod prod = 1;
  fore(i, 0, n) {
    prod *= min(as_i[i].first, bs_i[i].first);
  }

  auto swapA = [&](ull i, ull j) {
    assert(i < n && j < n);

    auto [a_i, i_original] = as_i[i];
    auto [a_j, j_original] = as_i[j];

    prod /= min(a_i, bs_i[i].first);
    prod /= min(a_j, bs_i[j].first);

    as_i[i] = {a_j, j_original};
    as_i[j] = {a_i, i_original};

    prod *= min(a_j, bs_i[i].first);
    prod *= min(a_i, bs_i[j].first);

    a_poss[i_original] = j;
    a_poss[j_original] = i;
  };

  auto swapB = [&](ull i, ull j) {
    assert(i < n && j < n);

    auto [b_i, i_original] = bs_i[i];
    auto [b_j, j_original] = bs_i[j];

    prod /= min(as_i[i].first, b_i);
    prod /= min(as_i[j].first, b_j);

    bs_i[i] = {b_j, j_original};
    bs_i[j] = {b_i, i_original};

    prod *= min(as_i[i].first, b_j);
    prod *= min(as_i[j].first, b_i);

    b_poss[i_original] = j;
    b_poss[j_original] = i;
  };

  auto lastEqA = [&](ull i) -> ull {
    assert(i < n);
    if (i + 1 == n) {
      return i;
    }

    if (as_i[i].first != as_i[i + 1].first) {
      return i;
    } else if (as_i[i].first == as_i[n - 1].first) {
      return n - 1;
    } else {
      ull l = i, r = n - 1;
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (as_i[m].first == as_i[i].first) {
          l = m;
        } else {
          r = m;
        }
      }
      return l;
    }
  };

  auto lastEqB = [&](ull i) -> ull {
    assert(i < n);
    if (i + 1 == n) {
      return i;
    }

    if (bs_i[i].first != bs_i[i + 1].first) {
      return i;
    } else if (bs_i[i].first == bs_i[n - 1].first) {
      return n - 1;
    } else {
      ull l = i, r = n - 1;
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (bs_i[m].first == bs_i[i].first) {
          l = m;
        } else {
          r = m;
        }
      }
      return l;
    }
  };

  auto inc1A = [&](ull i) {
    assert(i < n);

    prod /= min(as_i[i].first, bs_i[i].first);
    as_i[i].first++;
    prod *= min(as_i[i].first, bs_i[i].first);
  };

  auto inc1B = [&](ull i) {
    assert(i < n);

    prod /= min(as_i[i].first, bs_i[i].first);
    bs_i[i].first++;
    prod *= min(as_i[i].first, bs_i[i].first);
  };

  vm ans(q + 1);
  ans[0] = prod;
  fore(qu, 0, q) {
    auto [ty, x] = upds[qu];

    if (ty == 1) {
      ull i = a_poss[x];
      ull j = lastEqA(i);

      inc1A(i);
      if (i != j) {
        swapA(i, j);
      }
    } else {
      ull i = b_poss[x];
      ull j = lastEqB(i);

      inc1B(i);
      if (i != j) {
        swapB(i, j);
      }
    }

    ans[qu + 1] = prod;
  }

  return ans;
}

Mod force1(vu as, vu bs) {
  Mod ans = 0;

  sort(ALL(bs));

  do {
    Mod prod = 1;
    fore(i, 0, SZ(as)) {
      prod *= min(as[i], bs[i]);
    }
    ans = max(ans, prod);
  } while (next_permutation(ALL(bs)));

  return ans;
}

vm force(vu as, vu bs, vuu upds) {
  vm ans;
  ans.push_back(force1(as, bs));

  for (auto [ty, x] : upds) {
    if (ty == 1) {
      as[x]++;
    } else {
      bs[x]++;
    }

    ans.push_back(force1(as, bs));
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, q;
    cin >> n >> q;
    vu as(n), bs(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    fore(j, 0, n) {
      cin >> bs[j];
    }
    vuu upds(q);
    fore(j, 0, q) {
      cin >> upds[j].first >> upds[j].second;
      upds[j].second--;
    }

    auto ans = solve(as, bs, upds);
    for (auto a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }
#else
  fore(_, 0, 10000) {
    ull n = rand() % 6 + 1;
    ull q = rand() % 10 + 1;

    vu as(n), bs(n);
    fore(i, 0, n) {
      as[i] = rand() % 5 + 1;
      bs[i] = rand() % 5 + 1;
    }
    vuu upds(q);
    fore(i, 0, q) {
      upds[i].first = rand() % 2 + 1;
      upds[i].second = rand() % n;
    }

    vm ans = solve(as, bs, upds);
    vm ansf = force(as, bs, upds);

    if (ans != ansf) {
      cerr << "FAIL\n";
      cerr << n << ' ' << q << '\n';
      for (auto a : as) {
        cerr << a << ' ';
      }
      cerr << '\n';
      for (auto b : bs) {
        cerr << b << ' ';
      }
      cerr << '\n';
      for (auto [ty, x] : upds) {
        cerr << ty << ' ' << x + 1 << '\n';
      }
      cerr << "ANS\n";
      for (auto a : ans) {
        cerr << a << ' ';
      }
      cerr << '\n';
      cerr << "ANSF\n";
      for (auto a : ansf) {
        cerr << a << ' ';
      }
      cerr << endl;
      return 1;
    }
  }
#endif
}
