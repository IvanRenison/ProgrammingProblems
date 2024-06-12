// https://cses.fi/problemset/task/2420


#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define SZ(x) (x).size()

/** Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
  ull x; H(ull x=0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(SZ(str)+1), pw(ha) {
    pw[0] = 1;
    fore(i,0,SZ(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(ull a, ull b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

// hashString(s + t) = concat(hashString(s), hashString(t), pw)
// Where pw is C**|t| and can be obtained from a HashInterval
H concat(H h0, H h1, H h1pw) { return h0 * h1pw + h1; }

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
  H h, rev, Clen;
};
static const T neut = {0, 0, 1};
T f(T a, T b) {
  return {concat(a.h, b.h, b.Clen), concat(b.rev, a.rev, a.Clen), a.Clen * b.Clen};
} // (any associative fn)
struct Tree {
  vector<T> s; ull n;
  Tree(ull n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ull pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  string s;
  cin >> s;

  Tree tree(n);
  fore(i, 0, n) {
    tree.upd(i, {s[i], s[i], C});
  }

  while (m--) {
    ull t;
    cin >> t;
    if (t == 1) {
      ull k;
      char x;
      cin >> k >> x;
      k--;
      tree.upd(k, {x, x, C});
    } else {
      ull l, r;
      cin >> l >> r;
      l--;
      T res = tree.query(l, r);
      if (res.h == res.rev) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }

  return EXIT_SUCCESS;
}
