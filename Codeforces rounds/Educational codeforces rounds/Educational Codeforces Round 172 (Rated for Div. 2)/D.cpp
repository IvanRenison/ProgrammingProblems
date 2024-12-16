// https://codeforces.com/contest/2042/problem/D

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

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  typedef ull T;
  static constexpr T neut = inf;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; ll n;
  Tree(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};


vu solve(vuu lrs) {
  ull n = SZ(lrs);


  vu ans(n);

  auto solve_upper = [&]() {
    map<uu, ull> counter;
    vu xs(2 * n);
    fore(i, 0, n) {
      auto [l, r] = lrs[i];
      xs[2 * i] = l;
      xs[2 * i + 1] = r;
      counter[{l, r}]++;
    }
    sort(ALL(xs));
    xs.erase(unique(ALL(xs)), xs.end());

    auto to_pos = [&](ull x) -> ull {
      return lower_bound(ALL(xs), x) - xs.begin();
    };

    vector<tuple<ull, bool, ull, ull>> events(2 * n);
    fore(i, 0, n) {
      auto [l, r] = lrs[i];
      events[2 * i] = {l, true, inf - r, i};
      events[2 * i + 1] = {r, false, l, i};
    }
    sort(ALL(events));

    Tree tree(xs.size());
    vector<vu> stack(xs.size(), vu(1, inf));

    for (auto [x, open, _, i] : events) {
      auto [l, r] = lrs[i];
      ull r_pos = to_pos(r);
      if (open) {
        ull this_ans = tree.query(r_pos, xs.size());
        if (this_ans != inf && counter[{l, r}] == 1) {
          ans[i] += this_ans - r;
        }

        stack[r_pos].push_back(tree.query(r_pos, r_pos + 1));
        tree.upd(r_pos, r);
      } else {
        tree.upd(r_pos, stack[r_pos].back());
        stack[r_pos].pop_back();
      }
    }
  };

  solve_upper();
  for (auto& [l, r] : lrs) {
    l = (ull)(1e10) - l;
    r = (ull)(1e10) - r;
    swap(l, r);
  }

  solve_upper();

  return ans;
}

vu force(vuu lrs) {
  ull n = SZ(lrs);

  vu ans(n);

  fore(i, 0, n) {
    auto [li, ri] = lrs[i];
    ull mn = 0, mx = inf;
    fore(j, 0, n) if (j != i) {
      auto [lj, rj] = lrs[j];
      if (lj <= li && ri <= rj) {
        mn = max(mn, lj);
        mx = min(mx, rj);
      }
    }

    if (mx != inf) {
      ans[i] = li - mn + mx - ri;
    }
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
    ull n;
    cin >> n;
    vuu lrs(n);
    for (auto& [l, r] : lrs) {
      cin >> l >> r;
      l--;
    }

    auto ans = solve(lrs);
    for (ull a : ans) {
      cout << a << "\n";
    }
    //cerr << "-------\n";
  }
#else
  fore(_, 0, 1000) {
    ull n = rand() % 3 + 1;
    vuu lrs(n);
    for (auto& [l, r] : lrs) {
      l = rand() % 10;
      r = l + rand() % 10 + 1;
    }

    auto ans = solve(lrs);
    auto ans2 = force(lrs);
    if (ans != ans2) {
      cerr << "WA\n";
      cerr << n << "\n";
      for (auto [l, r] : lrs) {
        cerr << l + 1 << " " << r << "\n";
      }
      cerr << "ans\n";
      for (ull a : ans) {
        cerr << a << " ";
      }
      cerr << "\n";
      cerr << "ans2\n";
      for (ull a : ans2) {
        cerr << a << " ";
      }
      cerr << "\n";
      return 1;
    }
  }
#endif
}
