// https://atcoder.jp/contests/abc365/tasks/abc365_e

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
struct T {
  ull N;
  ull count;
  ull left_odd, right_odd;
};
static constexpr T neut = {inf, 0, 0, 0};
T f(T a, T b) {
  if (a.N == inf) return b;
  if (b.N == inf) return a;

  T res;
  res.N = a.N + b.N;
  res.count = a.count + b.count;

  res.left_odd = b.left_odd;
  if (b.count % 2 == 0) {
    res.left_odd += a.left_odd;
  } else {
    res.left_odd += a.N - a.left_odd;
  }

  res.right_odd = a.right_odd;
  if (a.count % 2 == 0) {
    res.right_odd += b.right_odd;
  } else {
    res.right_odd += b.N - b.right_odd;
  }

  return res;
} // (any associative fn)
struct Tree {
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


ull solveBit(vb& As) {
  ull N = SZ(As);

  ull count = 0;

  Tree tree(N);
  fore(i, 0, N) {
    if (As[i]) {
      count++;
      tree.upd(i, {1, 1, 1, 1});
    } else {
      tree.upd(i, {1, 0, 0, 0});
    }
  }

  ull ans = 0;

  fore(i, 0, N) {
    T t = tree.query(i, N);
    ans += t.right_odd;
  }

  ans -= count;

  return ans;
}

ull solve(vu& As) {
  ull ans = 0;

  fore(e, 0, 28) {
    vb Bs(SZ(As));
    fore(i, 0, SZ(As)) {
      Bs[i] = (As[i] >> e) & 1;
    }

    ans += solveBit(Bs) * (1ull << e);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N;
  cin >> N;
  vu As(N);
  fore(i, 0, N) {
    cin >> As[i];
  }

  auto ans = solve(As);
  cout << ans << '\n';

}
