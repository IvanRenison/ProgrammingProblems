// https://codeforces.com/contest/1989/problem/D

#pragma GCC optimize("Ofast")

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
typedef unsigned int uint;
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

const uint inf = 1u << 31;
const ld eps = 1e-7;

const ull alim = 1e6 + 1;

ull solve(vector<uint>& as, vector<uint>& bs, vector<uint>& cs) {
  uint n = as.size(), m = cs.size();

  vector<uint> min_diff_per_a(alim, inf);
  fore(i, 0, n) {
    uint a = as[i], b = bs[i];
    uint d = a - b;
    min_diff_per_a[as[i]] = min(min_diff_per_a[as[i]], d);
  }

  vector<uint> goods_s;
  fore(i, 0, n) {
    uint a = as[i], b = bs[i];
    uint d = a - b;
    if (min_diff_per_a[a] == d) {
      goods_s.push_back(a);
    }
  }
  sort(ALL(goods_s));
  vector<uint> goods;
  uint min_d = inf;
  fore(i, 0, goods_s.size()) {
    uint a = goods_s[i];
    uint d = min_diff_per_a[a];
    if (d < min_d) {
      goods.push_back(a);
      min_d = d;
    }
  }

  map<uint, ull> dp;

  auto f = [&](uint c, auto&& f) -> ull {
    if (dp.count(c)) {
      return dp[c];
    }

    ull ans = 0;
    auto it = upper_bound(ALL(goods), c);
    if (it != goods.begin()) {
      it--;
      uint a = *it;
      uint d = min_diff_per_a[a];
      // assert(a <= c);
      // assert(d <= a);
      // assert(d > 0);
      uint b = a - d;

      uint count = (c - b) / d;
      ans = (ull)count + f(c - count * d, f);
    }

    dp[c] = ans;
    return ans;
  };

  ull ans = 0;
  fore(i, 0, m) {
    ans += f(cs[i], f);
  }

  ans *= 2;
  return ans;


/*   ull ans = 0;

  vu is(n);
  iota(ALL(is), 0);
  sort(ALL(is), [&](ull i, ull j) {
    return as[i] - bs[i] < as[j] - bs[j];
  });

  sort(ALL(cs));

  priority_queue<uu> pq_cs;

  ull j = 0;
  fore(i, 1, m + 1) {
    if (i == m || cs[i] != cs[j]) {
      pq_cs.push({cs[j], i - j});
      j = i;
    }
  }

  for (ull i : is) {
    if (pq_cs.empty()) {
      break;
    }

    auto [c, count] = pq_cs.top();
    while (c >= as[i]) {
      pq_cs.pop();
      ull d = (c - bs[i]) / (as[i] - bs[i]);
      ans += d * count;
      c -= d * (as[i] - bs[i]);
      if (c > 0) {
        pq_cs.push({c, count});
      }
      if (pq_cs.empty()) {
        break;
      }
      tie(c, count) = pq_cs.top();
    }
  }

  ans *= 2;
  return ans; */
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, m;
  cin >> n >> m;
  vector<uint> as(n), bs(n), cs(m);
  fore(i, 0, n) {
    cin >> as[i];
  }
  fore(i, 0, n) {
    cin >> bs[i];
  }
  fore(i, 0, m) {
    cin >> cs[i];
  }

  auto ans = solve(as, bs, cs);
  cout << ans << '\n';

}
