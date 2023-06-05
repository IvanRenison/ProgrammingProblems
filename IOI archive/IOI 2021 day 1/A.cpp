// https://codeforces.com/group/32KGsXgiKA/contest/103782/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<int> vi;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#include "candies.h"

/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 * "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Status: tested
 */
// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
  static size_t i = sizeof buf;
  assert(s < i);
  return (void*)&buf[i -= s];
}
void operator delete(void*) {}

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
const int inf = 1e9;
struct Node {
  Node *l = 0, *r = 0;
  int lo, hi, mset = inf, madd = 0, val = -inf;
  Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
  Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      val = max(l->val, r->val);
    } else
      val = v[lo];
  }
  int query(int L, int R) {
    if (R <= lo || hi <= L)
      return -inf;
    if (L <= lo && hi <= R)
      return val;
    push();
    return max(l->query(L, R), r->query(L, R));
  }
  void set(int L, int R, int x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = val = x, madd = 0;
    else {
      push(), l->set(L, R, x), r->set(L, R, x);
      val = max(l->val, r->val);
    }
  }
  void add(int L, int R, int x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R) {
      if (mset != inf)
        mset += x;
      else
        madd += x;
      val += x;
    } else {
      push(), l->add(L, R, x), r->add(L, R, x);
      val = max(l->val, r->val);
    }
  }
  void push() {
    if (!l) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(lo, mid);
      r = new Node(mid, hi);
    }
    if (mset != inf)
      l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
    else if (madd)
      l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
  }
};

vector<int>
distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
  ull n = c.size();
  ull q = l.size();

  vector<vector<ull>> starts(n);
  vector<vector<ull>> ends(n);

  fore(i, 0, q) {}

  vector<int> ans(n);

  fore(i, 0, q) {
    if (v[i] > 0) {
      fore(j, l[i], r[i] + 1) {
        ans[j] = min(ans[j] + v[i], c[j]);
      }
    } else {
      fore(j, l[i], r[i] + 1) {
        ans[j] = max(0, ans[j] + v[i]);
      }
    }
  }

  return ans;
}
