// https://codeforces.com/gym/106193/problem/I

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
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

vu LISs(vu& as) {
  ull n = as.size();
  vu lis;
  vu ans(n);

  fore(i, 0, n) {
    ull a = as[i];
    ull pos = lower_bound(ALL(lis), a) - lis.begin();
    if (pos == lis.size()) {
      lis.push_back(a);
    } else {
      lis[pos] = a;
    }
    ans[i] = lis.size();
  }
  return ans;
}

vu solve(vu& as, vuu queries) {
  ull n = as.size(), q = queries.size();

  vector<pair<vu, vu>> tree(2 * n);
  auto fill_tree = [&](ull idx, ull l, ull r, auto&& fill_tree) {
    //cerr << idx << ' ' << l << ' ' << r << endl;
    if (l + 1 == r) {
      return;
    }
    assert(l + 1 < r);

    ull m = (l + r) / 2;

    vu as_left(m - l);
    fore(i, 0, m - l) {
      as_left[i] = n - as[m - 1 - i];
    }
    vu as_right(r - m);
    fore(i, 0, r - m) {
      as_right[i] = as[m + i];
    }

    tree[idx].first = LISs(as_left);
    tree[idx].second = LISs(as_right);

    fill_tree(idx * 2, l, m, fill_tree);
    fill_tree(idx * 2 + 1, m, r, fill_tree);
  };

  fill_tree(1, 0, n, fill_tree);


  // Solve one query assuming l ≤ ql < qr ≤ r
  auto rec = [&](ull idx, ull l, ull r, ull ql, ull qr, auto&& rec) -> ull {
    if (ql + 1 == qr) {
      return 1;
    }
    ull m = (l + r) / 2;
    if (qr <= m) {
      return rec(idx * 2, l, m, ql, qr, rec);
    } else if (ql >= m) {
      return rec(idx * 2 + 1, m, r, ql, qr, rec);
    } else {
      ull left_ans = tree[idx].first[m - 1 - ql];
      ull right_ans = tree[idx].second[qr - 1 - m];

      if (left_ans == 1 && right_ans == 1) {
        return 1 + (as[m - 1] < as[m]);
      } else {
        return max(left_ans, right_ans) * 3 / 2;
      }
    }
  };

  vu ans(q);
  fore(i, 0, q) {
    auto [ql, qr] = queries[i];
    ans[i] = rec(1, 0, n, ql, qr, rec);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, q;
    cin >> n >> q;
    vu as(n);
    for (ull& a : as) {
      cin >> a;
      a--;
    }
    vuu queries(q);
    for (auto& [l, r] : queries) {
      cin >> l >> r;
      l--;
    }

    auto ans = solve(as, queries);
    for (ull a : ans) {
      cout << a << "\n";
    }
  }

}
