// https://codeforces.com/gym/106193/problem/K

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
#define DBG(x) // cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

const ull lim_cord = 2e6 + 1;

//#define assert(x) while (!(x)) {}

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree_max {
  typedef ull T;
  static constexpr T neut = 0;
  T f(T a, T b) { return max(a, b); } // (any associative fn)
  vector<T> s; ll n;
  Tree_max(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
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

struct Tree_min {
  typedef ull T;
  static constexpr T neut = inf;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; ll n;
  Tree_min(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
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

enum Elem { Empty, Initial, Hatch, Gate, Key };

bool possible_compressed(ull s, ull h, vuu& kgs) {
  ull n = kgs.size();

  vector<pair<Elem, ull>> cave(2 * n + 2, {Empty, 0});
  cave[s].first = Initial;
  cave[h].first = Hatch;
  fore(i, 0, n) {
    auto [k, g] = kgs[i];
    cave[k] = {Key, i};
    cave[g] = {Gate, i};
  }

  ull l = s, r = s;
  vb have_key(n, false);

  while (l > 0 || r + 1 < cave.size()) {
    bool moved_left = false, moved_right = false;

    if (l > 0) {
      if (cave[l - 1].first == Hatch) {
        return true;
      } else if (cave[l - 1].first == Key) {
        have_key[cave[l - 1].second] = true;
        l--;
        moved_left = true;
      } else if (cave[l - 1].first == Empty) {
        l--;
        moved_left = true;
      } else if (cave[l - 1].first == Gate && have_key[cave[l - 1].second]) {
        l--;
        moved_left = true;
      }
    }

    if (r + 1 < cave.size()) {
      if (cave[r + 1].first == Hatch) {
        return true;
      } else if (cave[r + 1].first == Key) {
        have_key[cave[r + 1].second] = true;
        r++;
        moved_right = true;
      } else if (cave[r + 1].first == Empty) {
        r++;
        moved_right = true;
      } else if (cave[r + 1].first == Gate && have_key[cave[r + 1].second]) {
        r++;
        moved_right = true;
      }
    }

    if (!moved_left && !moved_right) {
      return false;
    }
  }

  return false;
}

bool possible(ull s, ull h, vuu& kgs) {
  ull n = kgs.size();
  // cerr << "Checking possibility (n = " << n << ")\n";

  vu vals = {s, h};
  for (auto [k, g] : kgs) {
    vals.push_back(k), vals.push_back(g);
  }

  sort(ALL(vals));
  map<ull, ull> compress;
  fore(i, 0, vals.size()) {
    compress[vals[i]] = i;
  }

  ull ns = compress[s];
  ull nh = compress[h];
  vuu nkgs(n);
  fore(i, 0, n)  {
    auto [k, g] = kgs[i];
    ull nk = compress[k];
    ull ng = compress[g];
    nkgs[i] = {nk, ng};
  }

  return possible_compressed(ns, nh, nkgs);
}

Tree_min min_keys(lim_cord);
Tree_max max_keys(lim_cord);

void init_trees() {
  fore(i, 0, lim_cord) {
    min_keys.upd(i, i);
    max_keys.upd(i, i);
  }
}

void clean(vuu& kgs) {
  for (auto [k, g] : kgs) {
    min_keys.upd(g, g);
    max_keys.upd(g, g);
  }
}

optional<ull> solve(ull s, ull h, vuu& kgs) {
  if (!possible(s, h, kgs)) {
    return {};
  }

  for (auto [k, g] : kgs) {
    max_keys.upd(g, k);
    min_keys.upd(g, k);
  }

  unordered_map<ull, ull> dp;
  dp[s] = 0;

  auto fun = [&](ull x, auto&& fun) -> ull {
    if (dp.count(x)) {
      return dp[x];
    }
    ull ans;

    //assert(x != s);
    if (x < s) {
      ull max_key = max_keys.query(x, s + 1);
      //assert(max_key > x);
      //assert(max_key < lim_cord);
      ans = fun(max_key, fun) + max_key - x;
    } else {
      ull min_key = min_keys.query(s, x + 1);
      //assert(min_key < x);
      ans = fun(min_key, fun) + x - min_key;
    }

    return dp[x] = ans;
  };

  ull ans = fun(h, fun);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  init_trees();

#ifndef TEST
  ull t;
  cin >> t;

  while (t--) {
    // cerr << "Tests case remaining: " << t + 1 << "\n";
    ull n, s, h;
    ll s0, h0;
    cin >> n >> s0 >> h0;
    s = s0 + 1e6;
    h = h0 + 1e6;
    vuu kgs(n);
    for (auto& [k, g] : kgs) {
      ll k0, g0;
      cin >> k0 >> g0;
      k = k0 + 1e6;
      g = g0 + 1e6;
    }

    auto ans = solve(s, h, kgs);

    if (ans.has_value()) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }

    if (t) {
      clean(kgs);
    }
  }
#else
  fore(_, 0, 100000) {
    cerr << "Test " << _ << "\n";
    ull n = rand() % 10 + 1;
    set<ull> used;
    while (used.size() < 2 * n + 2) {
      used.insert(rand() % ((ull)(2e6)));
    }
    vu vals(ALL(used));
    ull s = vals[0];
    ull h = vals[1];
    vuu kgs(n);
    fore(i, 0, n) {
      kgs[i] = {vals[2 + 2 * i], vals[2 + 2 * i + 1]};
    }

    auto ans = solve(s, h, kgs);
    clean(kgs);
  }
#endif
}
