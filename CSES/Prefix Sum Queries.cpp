// https://cses.fi/problemset/task/2166/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
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
const ll inf = (1ULL << 48);
struct Node {
  Node *l = 0, *r = 0;
  ll lo, hi, mset = inf, madd = 0, val = -inf;
  Node(ll lo, ll hi) : lo(lo), hi(hi) {} // Large interval of -inf
  Node(vector<ll>& v, ll lo, ll hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      ll mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      val = max(l->val, r->val);
    } else
      val = v[lo];
  }
  ll query(ll L, ll R) {
    if (R <= lo || hi <= L)
      return -inf;
    if (L <= lo && hi <= R)
      return val;
    push();
    return max(l->query(L, R), r->query(L, R));
  }
  void set(ll L, ll R, ll x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = val = x, madd = 0;
    else {
      push(), l->set(L, R, x), r->set(L, R, x);
      val = max(l->val, r->val);
    }
  }
  void add(ll L, ll R, ll x) {
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
      ll mid = lo + (hi - lo) / 2;
      l = new Node(lo, mid);
      r = new Node(mid, hi);
    }
    if (mset != inf)
      l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
    else if (madd)
      l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
  }
};

struct Problem {

  ull n;
  vector<ll> xs;
  Node* max_sums;

  Problem(vector<ll> xs) : xs(xs) {
    n = xs.size();

    ll sum = 0;
    vector<ll> pre_sums(n + 1);
    fore(i, 0, n) {
      sum += xs[i];
      pre_sums[i + 1] = sum;
    }

    max_sums = new Node(pre_sums, 0, n + 1);
  }

  void update(ull k, ll u) {
    ll diff = u - xs[k];
    xs[k] = u;
    max_sums->add(k + 1, n + 1, diff);
  }

  ull query(ull a, ull b) {
    ll start = max_sums->query(a, a + 1);
    ll max_in = max_sums->query(a, b + 1);
    return max_in - start;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, q;
  cin >> n >> q;

  vector<ll> xs(n);
  fore(i, 0, n) {
    cin >> xs[i];
  }

  Problem p(xs);

  fore(i, 0, q) {
    ll t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      p.update(a - 1, b);
    } else {
      cout << p.query(a - 1, b) << '\n';
    }
  }

  return EXIT_SUCCESS;
}
