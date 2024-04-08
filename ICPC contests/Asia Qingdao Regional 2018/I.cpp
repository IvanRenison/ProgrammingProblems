// https://codeforces.com/gym/104270/problem/I

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

/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct T {
  ll i, j; // We are interval [i, j]
  ll ai, aj;
  bool i_solo, i_left, j_solo, j_right;
  array<ll, 4> vals;
  // vals[0bxy] = ans for interval [i + x, j - y]
  bool we_are_neut;
};
T single(ll i, ll a, bool solo = true, bool left = true, bool right = true) {
  T res;
  res.i = i;
  res.j = i;
  res.ai = res.aj = a;
  res.i_solo = res.j_solo = solo;
  res.i_left = left;
  res.j_right = right;
  res.vals[0b00] = solo ? a : inf;
  res.vals[0b10] = res.vals[0b01] = -inf;
  res.vals[0b11] = inf;
  res.we_are_neut = false;
  return res;
}
static constexpr T unit = {0, 0, 0, 0, true, true, true, true, {0, 0, 0, 0}, true};
T f(T a, T b) {
  if (a.we_are_neut) {
    return b;
  }
  if (b.we_are_neut) {
    return a;
  }
  T res;
  res.i = a.i, res.j = b.j;
  res.ai = a.ai, res.aj = b.aj;
  res.i_left = a.i_left;
  res.j_right = b.j_right;
  res.we_are_neut = false;

  res.vals[0b00] = res.vals[0b01] = res.vals[0b10] = res.vals[0b11] = inf;

  res.vals[0b00] = max(a.vals[0b00], b.vals[0b00]);
  res.vals[0b01] = max(a.vals[0b00], b.vals[0b01]);
  res.vals[0b10] = max(a.vals[0b10], b.vals[0b00]);
  res.vals[0b11] = max(a.vals[0b10], b.vals[0b01]);
  if (a.j_right && b.i_left) {
    res.vals[0b00] = min(res.vals[0b00], max({a.vals[0b01], b.vals[0b10], a.aj + b.ai}));
    res.vals[0b01] = min(res.vals[0b01], max({a.vals[0b01], b.vals[0b11], a.aj + b.ai}));
    res.vals[0b10] = min(res.vals[0b10], max({a.vals[0b11], b.vals[0b10], a.aj + b.ai}));
    res.vals[0b11] = min(res.vals[0b11], max({a.vals[0b11], b.vals[0b11], a.aj + b.ai}));
  }

  return res;
} // (any associative fn)
struct Tree {
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


ll solve1(const vi& as) {
  ull n = as.size();

  if (n <= 2) {
    return 0;
  }

  Tree st(n);
  fore(i, 0, n) {
    st.update(i, single(i, as[i]));
  }

  viii possible_teams;
  fore(i, 0, n) {
    possible_teams.push_back({as[i], i, i});
  }
  fore(i, 0, n - 1) {
    possible_teams.push_back({as[i] + as[i + 1], i, i + 1});
  }

  sort(ALL(possible_teams));

  ll ans = inf;

  for (auto [_a, i, j] : possible_teams) {
    ll this_ans = st.query(0, n).vals[0b00];
    if (this_ans < (ll)inf) {
      this_ans -= _a;
      ans = min(ans, this_ans);
    } else {
      break;
    }

    if (i == j) {
      T ti = st.query(i, i + 1);
      ti.i_solo = ti.j_solo = false;
      ti.vals[0b00] = inf;
      st.update(i, ti);
    } else {
      T ti = st.query(i, i + 1);
      ti.j_right = false;
      st.update(i, ti);

      T tj = st.query(j, j + 1);
      tj.i_left = false;
      st.update(j, tj);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {

    ull n;
    cin >> n;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    auto ans = solve1(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
