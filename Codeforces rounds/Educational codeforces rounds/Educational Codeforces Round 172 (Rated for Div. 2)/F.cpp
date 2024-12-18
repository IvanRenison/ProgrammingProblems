// https://codeforces.com/contest/2042/problem/F

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
 * Can be changed by modifying T, f and neut.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct T {
  array<array<array<ll, 2>, 2>, 3> arr; // arr[n_segs][left_open][right_open]
  ll b_left, b_right;

  T() {
    fore(n_segs, 0, 3) fore(left_open, 0, 2) fore(right_open, 0, 2) {
      arr[n_segs][left_open][right_open] = -inf;
    }
    b_left = b_right = -inf;
  }
  T(ll a, ll b) {
    fore(n_segs, 0, 3) fore(left_open, 0, 2) fore(right_open, 0, 2) {
      arr[n_segs][left_open][right_open] = -inf;
    }
    arr[0][false][false] = 0;
    arr[1][true][false] = a + b;
    arr[1][false][true] = b + a;
    arr[1][true][true] = a;
    arr[1][false][false] = a + 2 * b;

    b_left = b_right = b;
  }

  void print() {
    cerr << "b_left = " << b_left << ", b_right = " << b_right << endl;
    fore(n_segs, 0, 3) fore(left_open, 0, 2) fore(right_open, 0, 2) if (arr[n_segs][left_open][right_open] != -(ll)inf) {
      cerr << "arr[" << n_segs << "][" << (left_open ? "true" : "false") << "][" << (right_open ? "true" : "false") << "] = " << arr[n_segs][left_open][right_open] << endl;
    }
    cerr << endl;
  }
};
const T neut = T();
T f(T l, T r) {
  if (l.b_left == -(ll)inf) return r;
  if (r.b_left == -(ll)inf) return l;
  T res;

  res.b_left = l.b_left;
  res.b_right = r.b_right;

  res.arr[0][false][false] = 0;

  res.arr[1][true][true] = l.arr[1][true][true] + r.arr[1][true][true];
  res.arr[1][true][false] = max({
      l.arr[1][true][false],
      l.arr[1][true][true] + r.arr[1][true][false],
      res.arr[1][true][true] + res.b_right
    });
  res.arr[1][false][true] = max({
      r.arr[1][false][true],
      l.arr[1][false][true] + r.arr[1][true][true],
      res.b_left + res.arr[1][true][true]
    });
  res.arr[1][false][false] = max({
      l.arr[1][false][false],
      r.arr[1][false][false],
      l.arr[1][false][true] + r.arr[1][true][false],
      res.b_left + res.arr[1][true][false],
      res.arr[1][false][true] + res.b_right,
      res.b_left + res.arr[1][true][true] + res.b_right
    });


  res.arr[2][true][true] = max({
      l.arr[2][true][true] + r.arr[1][true][true],
      l.arr[1][true][true] + r.arr[2][true][true],
      l.arr[1][true][false] + r.arr[1][false][true],
    });
  res.arr[2][false][true] = max({
      r.arr[2][false][true],
      l.arr[2][false][true] + r.arr[1][true][true],
      l.arr[1][false][true] + r.arr[2][true][true],
      l.arr[1][false][false] + r.arr[1][false][true],
      res.b_left + res.arr[2][true][true]
    });
  res.arr[2][true][false] = max({
      l.arr[2][true][false],
      l.arr[1][true][true] + r.arr[2][true][false],
      l.arr[2][true][true] + r.arr[1][true][false],
      l.arr[1][true][false] + r.arr[1][false][false],
      res.arr[2][true][true] + res.b_right
    });
  res.arr[2][false][false] = max({
      l.arr[2][false][false],
      r.arr[2][false][false],
      l.arr[1][false][false] + r.arr[1][false][false],
      l.arr[2][false][true] + r.arr[1][true][false],
      l.arr[1][false][true] + r.arr[2][true][false],
      res.arr[2][false][true] + res.b_right,
      res.b_left + res.arr[2][true][false],
      res.b_left + res.arr[2][true][true] + res.b_right
  });


  //l.print();
  //r.print();
  //res.print();
  //cerr << "----------------" << endl;

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

ll force(vi as, vi bs, ull l, ull r) {

  auto cost = [&](ull le, ull ri) -> ull {
    ull ans = bs[le] + bs[ri - 1];
    fore(i, le, ri) {
      ans += as[i];
    }
    return ans;
  };

  ll ans = -inf;
  fore(i, l, r) fore(j, i + 1, r) {
    fore(k, j, r) fore(m, k + 1, r + 1) {
      ll this_ans = cost(i, j) + cost(k, m);
      ans = max(ans, this_ans);
    }
  }

  return ans;
}

void test() {
  ull n = rand() % 5 + 4;
  vi as(n), bs(n);
  for (ll& a : as) {
    a = rand() % 11 - 5;
  }
  for (ll& b : bs) {
    b = rand() % 11 - 5;
  }

  ull i = 0, j = n;
  ll ans = force(as, bs, i, j);
  Tree tree(n);
  fore(i, 0, n) {
    tree.upd(i, T(as[i], bs[i]));
  }
  ll ans2 = tree.query(i, j).arr[2][false][false];

  if (ans != ans2) {
    cerr << "ERROR" << endl;
    cerr << n << endl;
    for (ll a : as) {
      cerr << a << " ";
    }
    cerr << endl;
    for (ll b : bs) {
      cerr << b << " ";
    }
    cerr << endl;
    cerr << "1\n3 " << i + 1 << " " << j << endl;
    cerr << "Real answer: " << ans << endl;
    cerr << "My answer: " << ans2 << endl;
    exit(1);
  }
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull n;
  cin >> n;
  vi as(n), bs(n);
  for (ll& a : as) {
    cin >> a;
  }
  for (ll& b : bs) {
    cin >> b;
  }

  Tree tree(n);
  fore(i, 0, n) {
    tree.upd(i, T(as[i], bs[i]));
  }

  ull q;
  cin >> q;

  while (q--) {
    ull type;
    cin >> type;
    if (type == 1) {
      ll p, x;
      cin >> p >> x;
      p--;
      as[p] = x;
      tree.upd(p, T(as[p], bs[p]));
    } else if (type == 2) {
      ll p, x;
      cin >> p >> x;
      p--;
      bs[p] = x;
      tree.upd(p, T(as[p], bs[p]));
    } else {
      ll l, r;
      cin >> l >> r;
      l--;
      T res = tree.query(l, r);
      cout << res.arr[2][false][false] << endl;
    }
  }
#else
  fore(_, 0, 100000) {
    test();
  }
#endif
