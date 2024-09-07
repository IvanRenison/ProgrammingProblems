// https://atcoder.jp/contests/abc370/tasks/abc370_d

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

/** Author: Simon Lindholm
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Time: O(\log N)
 * Status: stress-tested
 */
set<ii>::iterator addInterval(set<ii>& is, ll L, ll R) {
  if (L == R) return is.end();
  auto it = is.lower_bound({L, R}), before = it;
  while (it != is.end() && it->first <= R) {
    R = max(R, it->second);
    before = it = is.erase(it);
  }
  if (it != is.begin() && (--it)->second >= L) {
    L = min(L, it->first);
    R = max(R, it->second);
    is.erase(it);
  }
  return is.insert(before, {L,R});
}

void removeInterval(set<ii>& is, ll L, ll R) {
  if (L == R) return;
  auto it = addInterval(is, L, R);
  auto r2 = it->second;
  if (it->first == L) is.erase(it);
  else (ll&)it->second = L;
  if (R != r2) is.emplace(R, r2);
}

set<ii>::iterator find(set<ii>& is, ll x) {
  auto it = is.lower_bound({x, 0});
  if (it != is.end() && it->first == x) {
    return it;
  }
  if (it == is.begin()) {
    return is.end();
  }
  it--;
  if (it->first <= x && x < it->second) {
    return it;
  }
  return is.end();
}

ull solve(ull H, ull W, vuu& queries) {

  vector<set<ii>> rows(H), cols(W);

  for (auto [R, C] : queries) {
    // Row
    auto it = find(rows[R], C);
    if (it == rows[R].end()) {
      addInterval(rows[R], C, C + 1);
    } else {
      auto [l, u] = *it;
      if (l > 0) {
        l--;
        addInterval(cols[l], R, R + 1);
      }
      if (u < W) {
        addInterval(cols[u], R, R + 1);
        u++;
      }
      addInterval(rows[R], l, u);
    }

    // Col
    it = find(cols[C], R);
    if (it == cols[C].end()) {
      addInterval(cols[C], R, R + 1);
    } else {
      auto [l, u] = *it;
      if (l > 0) {
        l--;
        addInterval(rows[l], C, C + 1);
      }
      if (u < H) {
        addInterval(rows[u], C, C + 1);
        u++;
      }
      addInterval(cols[C], l, u);
    }
  }

  ull ans = 0;
  fore(i, 0, H) {
    for (auto [l, u] : rows[i]) {
      ans += u - l;
    }
  }

  ans = H * W - ans;
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull H, W, Q;
  cin >> H >> W >> Q;
  vuu queries(Q);
  fore(i, 0, Q) {
    ull r, c;
    cin >> r >> c;
    r--, c--;
    queries[i] = {r, c};
  }

  auto ans = solve(H, W, queries);
  cout << ans << '\n';

}
