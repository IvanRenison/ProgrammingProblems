// https://atcoder.jp/contests/abc309/tasks/abc309_c

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
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
const ll inf = (1ull << 48);
struct Node {
  Node *l = 0, *r = 0;
  ll lo, hi, mset = inf, madd = 0, val = 0;
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
      return 0;
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

#define MAXA ull(1e9 + 1)

ull solve(ull K, vector<pair<ull, ull>> abs) {
  Node t(0, MAXA);

  for (auto [a, b] : abs) {
    t.add(0, a, b);
  }

  ull upper = MAXA, lower = 1;

  if (t.query(0, 1) <= K) {
    return 1;
  }

  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    ull q_m = t.query(m, m + 1);
    ull q_ml = t.query(m - 1, m);

    if (q_m <= K && q_ml > K) {
      return m + 1;
    }

    if (q_m <= K) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;
  vector<pair<ull, ull>> abs(N);
  fore(i, 0, N) {
    cin >> abs[i].first >> abs[i].second;
  }

  cout << solve(K, abs) << '\n';

  return EXIT_SUCCESS;
}

/*
3+5+9+2 = 19
3+5+2 = 10
3+2 = 5
3+2 = 5


*/
