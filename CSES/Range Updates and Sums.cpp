// https://cses.fi/problemset/task/1735

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
const ull inf = (1ULL << 48);
struct Node {
  Node *l = 0, *r = 0;
  ull lo, hi, mset = inf, madd = 0, val = 0;
  Node(ull lo, ull hi) : lo(lo), hi(hi) {} // Large interval of 0
  Node(vector<ull>& v, ull lo, ull hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      ull mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      val = l->val + r->val;
    } else
      val = v[lo];
  }
  ull query(ull L, ull R) {
    if (R <= lo || hi <= L)
      return 0;
    if (L <= lo && hi <= R) {
      if (mset != inf)
        return mset * (hi - lo);
      else
        return val + madd * (hi - lo);
    }
    push();
    return l->query(L, R) + r->query(L, R);
  }
  void set(ull L, ull R, ull x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = x, madd = val = 0;
    else {
      push(), l->set(L, R, x), r->set(L, R, x);
      val = l->query(lo, hi) + r->query(lo, hi);
    }
  }
  void add(ull L, ull R, ull x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R) {
      if (mset != inf)
        mset += x;
      else
        madd += x;
    } else {
      push(), l->add(L, R, x), r->add(L, R, x);
      val = l->query(lo, hi) + r->query(lo, hi);

    }
  }
  void push() {
    if (!l) {
      ull mid = lo + (hi - lo) / 2;
      l = new Node(lo, mid);
      r = new Node(mid, hi);
    }
    if (mset != inf)
      l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
    else if (madd)
      l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    val = l->query(lo, hi) + r->query(lo, hi);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ull n, q;
  cin >> n >> q;

  vector<ull> ts(n);
  fore(i, 0, n) {
    cin >> ts[i];
  }

  Node N(ts, 0, n);

  fore(i, 0, q) {
    ull ty, a, b;
    cin >> ty >> a >> b;

    if (ty == 1) {
      ull x;
      cin >> x;
      N.add(a - 1, b, x);
    } else if (ty == 2) {
      ull x;
      cin >> x;
      N.set(a - 1, b, x);
    } else {
      cout << N.query(a - 1, b) << endl;
    }
  }

  return EXIT_SUCCESS;
}
