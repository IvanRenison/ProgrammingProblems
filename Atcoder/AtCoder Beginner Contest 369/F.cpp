// https://atcoder.jp/contests/abc369/tasks/abc369_f

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
  typedef uuu T;
  static constexpr T neut = {0, 0, 0};
  T f(T a, T b) { return max(a, b); } // (any associative fn)
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


pair<ull, string> solve(ull H, ull W, vuu& coins) {
  ull N = SZ(coins);

  vector<vu> coins_per_row(H);
  for (auto [R, C] : coins) {
    coins_per_row[R].push_back(C);
  }
  fore(R, 0, H) {
    sort(ALL(coins_per_row[R]));
  }

  map<uu, uu> dp;

  Tree tree(W);
  fore(R, 0, H) {
    for (ull C : coins_per_row[R]) {
      auto [d, i, j] = tree.query(0, C + 1);
      tree.upd(C, {d + 1, R, C});
      dp[{R, C}] = {i, j};
    }
  }

  auto [ans, i, j] = tree.query(0, W);

  string rec;
  fore(_, i + 1, H) {
    rec.push_back('D');
  }
  fore(_, j + 1, W) {
    rec.push_back('R');
  }

  do {
    auto [pi, pj] = dp[{i, j}];

    fore(_, pi, i) {
      rec.push_back('D');
    }
    fore(_, pj, j) {
      rec.push_back('R');
    }

    i = pi;
    j = pj;
  } while (i != 0 || j != 0);

  reverse(ALL(rec));

  return {ans, rec};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull H, W, N;
  cin >> H >> W >> N;
  vuu coins(N);
  for (auto& [R, C] : coins) {
    cin >> R >> C;
    --R, --C;
  }

  auto [ans, path] = solve(H, W, coins);
  cout << ans << '\n' << path << '\n';

}
