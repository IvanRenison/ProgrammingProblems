// https://codeforces.com/contest/1923/problem/D

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
  typedef ull T;
  static constexpr T unit = 0;
  T f(T a, T b) const { return a + b; } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) const { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

ull sumMore_before(const Tree& t, ull sum, ull i) {
  ull l = 0, r = i;
  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;

    ull s = t.query(m, i);

    if (s <= sum) {
      r = m;
    } else {
      l = m;
    }
  }

  ull ans = i - l;
  return ans;
}


vector<ull> solveFord(const vu& as) {
  ull n = as.size();

  vu equalFrom(n);
  equalFrom[0] = 0;
  fore(i, 1, n) {
    if (as[i] == as[i - 1]) {
      equalFrom[i] = equalFrom[i - 1];
    } else {
      equalFrom[i] = i;
    }
  }

  Tree t(n);
  fore(i, 0, n) {
    t.update(i, as[i]);
  }

  vu ans(n, inf);

  fore(i, 0, n) {
    ull a = as[i];
    if (t.query(0, i) > a) {
      if (as[i - 1] > a) {
        ans[i] = 1;
      } else {
        ull j = equalFrom[i - 1];
        ull sum = t.query(j, i);
        if (j > 0) {
          if (sum > a) {
            ans[i] = i - j + 1;
          } else {
            ans[i] = sumMore_before(t, a - sum, j) + i - j;
          }
        }
      }
    }
  }

  return ans;
}

vu solve(vu& as) {
  ull n = as.size();

  vu ans = solveFord(as);
  reverse(all(as));

  vu ans2 = solveFord(as);

  reverse(all(ans2));

  fore(i, 0, n) {
    ans[i] = min(ans[i], ans2[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(i, 0, n) {
      cin >> as[i];
    }

    auto ans = solve(as);

    for (auto a : ans) {
      if (a != inf) {
        cout << a << ' ';
      } else {
        cout << "-1 ";
      }
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
