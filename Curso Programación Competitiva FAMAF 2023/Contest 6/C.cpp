// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)
#define MAXN ull(1e5 + 1)

struct Tree {
  //       amount, count
  typedef pair<ll, ull> T;
  static constexpr T unit = {0, 0};
  T f(T a, T b) {
    return {a.first + b.first, a.second + b.second};
  } // (any associative fn)
  vector<T> s;
  ull n;
  Tree(ull n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(ull pos, ll val) {
    pos += n;
    s[pos].first += val;
    s[pos].second = s[pos].first > 0 ? 1 : 0;
    for (; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ull b, ull e) { // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2)
        ra = f(ra, s[b++]);
      if (e % 2)
        rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

struct Problem {
  Tree rows, cols;

  Problem(ull n) : rows(n), cols(n) {}

  void put(ull x, ull y) {
    rows.update(y, 1);
    cols.update(x, 1);
  }
  void remove(ull x, ull y) {
    rows.update(y, -1);
    cols.update(x, -1);
  }
  bool query(ull x1, ull y1, ull x2, ull y2) {
    return rows.query(y1, y2 + 1).second == (y2 - y1 + 1) ||
           cols.query(x1, x2 + 1).second == (x2 - x1 + 1);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull n, q;
  cin >> n >> q;

  Problem p(n);

  fore(i, 0, q) {
    ull t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      p.put(x - 1, y - 1);
    } else if (t == 2) {
      p.remove(x - 1, y - 1);
    } else {
      ull x1, y1;
      cin >> x1 >> y1;
      if (p.query(x - 1, y - 1, x1 - 1, y1 - 1)) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }
    }
  }

  return EXIT_SUCCESS;
}
