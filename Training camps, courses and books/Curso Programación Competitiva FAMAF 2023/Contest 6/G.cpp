// https://codeforces.com/group/id8eYTCwzg/contest/447738/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

tuple<vector<int>, vector<int>, vector<pair<ull, ull>>> parse1(void) {
  ull n, q;
  cin >> n >> q;
  vector<int> s(n), f(n);
  fore(i, 0, n) {
    char c;
    cin >> c;
    s[i] = c == '1' ? 1 : 0;
  }
  fore(i, 0, n) {
    char c;
    cin >> c;
    f[i] = c == '1' ? 1 : 0;
  }

  vector<pair<ull, ull>> lrs(q);
  fore(i, 0, q) {
    ull l, r;
    cin >> l >> r;
    lrs[i] = {l - 1, r};
  }

  return {s, f, lrs};
}

const int inf = (1 << 30);
struct Node {
  Node *l = 0, *r = 0;
  int lo, hi, mset = inf, madd = 0, val = 0;
  Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of 0
  Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l = new Node(v, lo, mid);
      r = new Node(v, mid, hi);
      val = l->val + r->val;
    } else
      val = v[lo];
  }
  int query(int L, int R) {
    if (R <= lo || hi <= L)
      return 0;
    if (L <= lo && hi <= R)
      return val;
    push();
    return l->query(L, R) + r->query(L, R);
  }
  void set(int L, int R, int x) {
    if (R <= lo || hi <= L)
      return;
    if (L <= lo && hi <= R)
      mset = x, val = x * (hi - lo), madd = 0;
    else {
      push(), l->set(L, R, x), r->set(L, R, x);
      val = l->val + r->val;
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
      val = l->val + r->val;
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

bool solve1(vector<int>& s, vector<int>& f, vector<pair<ull, ull>>& lrs) {
  ull n = s.size(), q = lrs.size();
  Node t(f, 0, n);

  for (auto it = lrs.rbegin(); it != lrs.rend(); it++) {
    auto [l, r] = *it;

    ull sz = r - l;
    ull count = t.query(l, r);

    if (2 * count < sz) {
      t.set(l, r, 0);
    } else if (2 * count > sz) {
      t.set(l, r, 1);
    } else {
      return false;
    }
  }

  vector<int> new_s(n);
  fore(i, 0, n) {
    new_s[i] = t.query(i, i + 1) != 0 ? 1 : 0;
  }

  return s == new_s;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [s, f, lrs] = parse1();
    if (solve1(s, f, lrs)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return EXIT_SUCCESS;
}
