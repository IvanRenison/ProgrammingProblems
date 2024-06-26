// https://codeforces.com/contest/1982/problem/F

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
typedef pair<ull, ll> ui;
typedef vector<ui> vui;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;


struct Tree {
  struct T {
    bool ord;
    ll m, M;
  };
  static constexpr T neut = {true, inf, -(ll)inf};
  T f(T a, T b) {
    return {a.ord && b.ord && a.M <= b.m, min(a.m, b.m), max(a.M, b.M)};
  } // (any associative fn)
  vector<T> s; ull n;
  Tree(ull n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};


vector<optional<uu>> solve(const vi& as, const vui& upds) {
  ull n = as.size(), q = upds.size();

  Tree t(n);
  fore(i, 0, n) {
    ll a = as[i];
    t.upd(i, {true, a, a});
  }

  auto searchStart = [&]() -> ull { // Assuming is not sorted
    ull l = 0, r = n;
    while (l + 1 < r) {
      ull m = (l + r) / 2;
      Tree::T leftT = t.query(0, m), rightT = t.query(m, n);
      bool valid = leftT.ord && leftT.M <= rightT.m;
      if (valid) {
        l = m;
      } else {
        r = m;
      }
    }
    return l;
  };

  auto searchEnd = [&]() -> ull { // Assuming is not sorted
    ull l = 0, r = n;
    while (l + 1 < r) {
      ull m = (l + r) / 2;
      Tree::T leftT = t.query(0, m), rightT = t.query(m, n);
      bool valid = rightT.ord && leftT.M <= rightT.m;
      if (valid) {
        r = m;
      } else {
        l = m;
      }
    }
    return r;
  };

  auto calc = [&]() -> optional<uu> {
    Tree::T total = t.query(0, n);
    if (total.ord) {
      return {};
    }

    ull l = searchStart();
    ull r = searchEnd();

    return {{l, r}};
  };

  vector<optional<uu>> ans(q + 1);
  ans[0] = calc();
  fore(i, 0, q) {
    auto [pos, val] = upds[i];
    t.upd(pos, {true, val, val});
    ans[i + 1] = calc();
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }
    ull q;
    cin >> q;
    vui upds(q);
    for (auto& [pos, val] : upds) {
      cin >> pos >> val;
      pos--;
    }

    auto ans = solve(as, upds);
    for (auto lr : ans) {
      if (lr) {
        auto [l, r] = *lr;
        cout << l + 1 << ' ' << r << '\n';
      } else {
        cout << "-1 -1\n";
      }
    }
  }

}
