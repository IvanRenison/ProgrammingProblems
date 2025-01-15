// https://codeforces.com/contest/2043/problem/C

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

/** Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct RMQ_min {
  vector<vector<T>> jmp;
  RMQ_min(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

template<class T>
struct RMQ_max {
  vector<vector<T>> jmp;
  RMQ_max(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

vi solve(vi& as) {
  ull n = as.size();

  vi as_sums(n + 1);
  as_sums[0] = 0;
  fore(i, 1, n + 1) {
    as_sums[i] = as_sums[i - 1] + as[i - 1];
  }

  ull diff = inf;
  fore(i, 0, n) {
    if (as[i] != 1 && as[i] != -1) {
      diff = i;
      break;
    }
  }

  RMQ_min<ll> rmq_min(as_sums);
  RMQ_max<ll> rmq_max(as_sums);

  vi ans;

  if (diff == inf) {
    ll max_sum = 0;
    fore(i, 0, n) {
      ll mn = rmq_min.query(0, i + 1);
      ll this_sum = as_sums[i + 1] - mn;
      max_sum = max(max_sum, this_sum);
    }

    ll min_sum = 0;
    fore(i, 0, n) {
      ll mx = rmq_max.query(0, i + 1);
      ll this_sum = as_sums[i + 1] - mx;
      min_sum = min(min_sum, this_sum);
    }

    for (ll x = min_sum; x < max_sum + 1; x++) {
      ans.push_back(x);
    }
  } else {
    {
      ll max_sum = 0;
      fore(i, 0, diff) {
        ll mn = rmq_min.query(0, i + 1);
        ll this_sum = as_sums[i + 1] - mn;
        max_sum = max(max_sum, this_sum);
      }

      ll min_sum = 0;
      fore(i, 0, diff) {
        ll mx = rmq_max.query(0, i + 1);
        ll this_sum = as_sums[i + 1] - mx;
        min_sum = min(min_sum, this_sum);
      }

      for (ll x = min_sum; x < max_sum + 1; x++) {
        ans.push_back(x);
      }
    }
    {
      ll max_sum = 0;
      fore(i, diff + 1, n) {
        ll mn = rmq_min.query(diff + 1, i + 1);
        ll this_sum = as_sums[i + 1] - mn;
        max_sum = max(max_sum, this_sum);
      }

      ll min_sum = 0;
      fore(i, diff + 1, n) {
        ll mx = rmq_max.query(diff + 1, i + 1);
        ll this_sum = as_sums[i + 1] - mx;
        min_sum = min(min_sum, this_sum);
      }

      for (ll x = min_sum; x < max_sum + 1; x++) {
        ans.push_back(x);
      }
    }

    {
      ll max_sum = as[diff];
      fore(i, diff, n) {
        ll mn = rmq_min.query(0, diff + 1);
        ll this_sum = as_sums[i + 1] - mn;
        max_sum = max(max_sum, this_sum);
      }

      ll min_sum = as[diff];
      fore(i, diff, n) {
        ll mx = rmq_max.query(0, diff + 1);
        ll this_sum = as_sums[i + 1] - mx;
        min_sum = min(min_sum, this_sum);
      }

      for (ll x = min_sum; x < max_sum + 1; x++) {
        ans.push_back(x);
      }
    }

    sort(ALL(ans));
    ans.erase(unique(ALL(ans)), ans.end());
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vi as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve(as);
    cout << SZ(ans) << '\n';
    fore(j, 0, SZ(ans)) {
      cout << ans[j] << ' ';
    }
    cout << '\n';
  }

}
