// https://cses.fi/problemset/task/1142/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

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
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (ull pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      fore(j,0,jmp[k].size())
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ull a, ull b) {
    assert(a < b); // or return inf if a == b
    ull dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

ull solve(const vu& as) {
  ull n = as.size();

  RMQ<ull> rmq(as);

  ull ans = 0;

  fore(i, 0, n) {
    ull a = as[i];

    ull r = n;
    {
      ull lo = i;
      while (lo + 1 < r) {
        ull m = (lo + r) / 2;
        ull h = rmq.query(i, m + 1);
        if (h < a) {
          r = m;
        } else {
          lo = m;
        }
      }
    }

    ull l = 0;
    if (rmq.query(0, i + 1) < a) {
      ull hi = i;
      while (l + 1 < hi) {
        ull m = (hi + l) / 2;
        ull h = rmq.query(m, i + 1);
        if (h >= a) {
          hi = m;
        } else {
          l = m;
        }
      }
      l++;
    }

    ull this_ans = a * (r - l);

    ans = max(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu ks(n);
  for (ull& k : ks) {
    cin >> k;
  }

  ull ans = solve(ks);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
