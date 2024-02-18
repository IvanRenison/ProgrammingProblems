// https://redprogramacioncompetitiva.com/contests/2024/01/

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
static const vu unit = vu(4, 0);
struct Tree {
  typedef vu T;
  T f(T a, T b) {
    vu ans = unit;
    fore(i, 0, 4) {
      ans[i] = a[i] + b[i];
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

vector<string> solve(string s, vuu querys) {
  ull n = s.size(), m = querys.size();

  vu s_(n);
  fore(i, 0, n) {
    if (s[i] == 'A') {
      s_[i] = 0;
    } else if (s[i] == 'T') {
      s_[i] = 1;
    } else if (s[i] == 'G') {
      s_[i] = 2;
    } else if (s[i] == 'C') {
      s_[i] = 3;
    }
  }

  Tree tree(n);
  fore(i, 0, n) {
    vu val(4, 0);
    val[s_[i]] = 1;
    tree.update(i, val);
  }

  vector<string> ans(m);
  fore(k, 0, m) {
    auto [i, j] = querys[k];

    vu v = tree.query(i, j);

    vector<pair<ull, char>> vals = {{v[0], 'D'}, {v[1], 'C'}, {v[2], 'B'}, {v[3], 'A'}};
    sort(all(vals));
    reverse(all(vals));

    fore(c, 0, 4) {
      vals[c].second = vector<char>{'C', 'G', 'T', 'A' }[vals[c].second - 'A'];
    }

    string res;
    fore(c, 0, 4) {
      res += vals[c].second;
    }

    ans[k] = res;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;
  ull m;
  cin >> m;
  vuu querys(m);
  for (auto& [i, j] : querys) {
    cin >> i >> j;
    i--;
  }

  auto ans = solve(s, querys);
  for (auto& a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
