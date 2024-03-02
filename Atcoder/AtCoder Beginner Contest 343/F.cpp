// https://atcoder.jp/contests/abc343/tasks/abc343_f

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


/** Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
  struct T {
    ull max_val, max_count, sec_val, sec_count;
  };
  static constexpr T unit = {0, 0, 0, 0};
  T f(T a, T b) {
    map<ull, ull> vals;
    vals[a.max_val] += a.max_count;
    vals[a.sec_val] += a.sec_count;
    vals[b.max_val] += b.max_count;
    vals[b.sec_val] += b.sec_count;

    T ans = unit;
    ull i = 0;
    for (auto it = vals.rbegin(); it != vals.rend(); it++) {
      if (i == 0) {
        ans.max_val = it->first;
        ans.max_count = it->second;
      } else if (i == 1) {
        ans.sec_val = it->first;
        ans.sec_count = it->second;
      } else {
        break;
      }
      i++;
    }

    return ans;
  } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, Q;
  cin >> N >> Q;

  vu As(N);
  for (ull& A : As) {
    cin >> A;
  }

  Tree tree(N);

  fore(i, 0, N) {
    ull A = As[i];
    tree.update(i, {A, 1, 0, 0});
  }

  fore(i, 0, Q) {
    ull T, A, B;
    cin >> T >> A >> B;
    if (T == 1) {
      ull p = A - 1, x = B;
      tree.update(p, {x, 1, 0, 0});
    } else {
      ull l = A - 1, r = B;
      auto ans = tree.query(l, r);
      ull res = ans.sec_count;
      cout << res << '\n';
    }
  }



  return EXIT_SUCCESS;
}
