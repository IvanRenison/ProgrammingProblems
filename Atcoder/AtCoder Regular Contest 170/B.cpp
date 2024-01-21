// https://atcoder.jp/contests/arc170/tasks/arc170_b

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

/*

Aj - Ai = Ak - Aj
2Aj - Ai - Ak = 0

1 2 1
1 3 2
1 4 3
1 5 4
1 6 5
1 7 6
1 8 7
1 9 8
1 10 9
2 3 1
2 4 2
2 5 3
2 6 4
2 7 5
2 8 6
2 9 7
2 10 8
3 4 1
3 5 2
3 6 3
3 7 4
3 8 5
3 9 6
3 10 7
4 5 1
4 6 2
4 7 3
4 8 4
4 9 5
4 10 6
5 6 1
5 7 2
5 8 3
5 9 4
5 10 5
6 7 1
6 8 2
6 9 3
6 10 4
7 8 1
7 9 2
7 10 3
8 9 1
8 10 2
9 10 1
*/

vector<vuu> ops; /* = {
  {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {8, 7}, {9, 8}, {10, 9}},
  {{3, 1}, {4, 2}, {5, 3}, {6, 4}, {7, 5}, {8, 6}, {9, 7}, {10, 8}},
  {{4, 1}, {5, 2}, {6, 3}, {7, 4}, {8, 5}, {9, 6}, {10, 7}},
  {{5, 1}, {6, 2}, {7, 3}, {8, 4}, {9, 5}, {10, 6}},
  {{6, 1}, {7, 2}, {8, 3}, {9, 4}, {10, 5}},
  {{7, 1}, {8, 2}, {9, 3}, {10, 4}},
  {{8, 1}, {9, 2}, {10, 3}},
  {{9, 1}, {10, 2}},
  {{10, 1}},
}; */

void ops_init() {
  ops = vector<vuu>(10);
  for(ll i = 1; i <= 10; i++) {
    for(ll j = 1; j <= 10; j++) {
      for(ll k = 1; k <= 10; k++) {
        if (j - i == k - j) {
          ops[i - 1].push_back({j, k});
        }
      }
    }
  }

  /* fore(i, 1, 11) {
    fore(j, 0, sz(ops[i - 1])) {
      cerr << i << " " << ops[i - 1][j].first << " " << ops[i - 1][j].second << endl;
    }
  } */

}


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
  typedef bool T;
  static constexpr T unit = false;
  T f(T a, T b) { return a || b; } // (any associative fn)
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

struct TreeMin {
  typedef ull T;
  static constexpr T unit = inf;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; int n;
  TreeMin(int n = 0, T def = unit) : s(2*n, def), n(n) {}
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

ull firstTrueFrom(Tree& t, ull l) {
  ull r = t.n;

  if (!t.query(l, r)) {
    return r;
  }

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (t.query(l, m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l;
}

ull solve(vu As) {
  ull N = As.size();

  array<Tree, 10> trees;
  for (ull i = 0; i < 10; i++) {
    trees[i] = Tree(N);
  }
  fore(i, 0, N) {
    trees[As[i] - 1].update(i, true);
  }

  vu min_op(N, inf);

  fore(i, 0, N) {
    ull A = As[i];
    for (auto [B, C] : ops[A - 1]) {
      ull j = firstTrueFrom(trees[B - 1], i + 1);
      ull k = firstTrueFrom(trees[C - 1], j + 1);
      if (k < N) {
        min_op[i] = min(min_op[i], k);
      }
    }
  }

  TreeMin tree_min(N);
  fore(i, 0, N) {
    tree_min.update(i, min_op[i]);
  }

  ull ans = 0;

  fore(i, 0, N) {
    ull j = tree_min.query(i, N);
    if (j != inf) {
      ans += N - j;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ops_init();

  ull N;
  cin >> N;
  vu As(N);
  for (ull& A : As) {
    cin >> A;
  }

  auto ans = solve(As);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
