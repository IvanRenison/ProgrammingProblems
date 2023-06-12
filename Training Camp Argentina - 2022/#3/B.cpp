// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/B
#include <bits/stdc++.h>
#define pb push_back
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef int ll;
typedef unsigned int ull;

/*

1 + 2 + 3 + ... x ≥ n

x * (x + 1) / 2 ≥ n

x² + x - n/2 ≥ 0

x ≥ (-1 + √(1² + 5 * n/2)) / 2

Para n = 10⁵

x ≥ 249.5004999995

*/

pair<ull, vector<ull>> prfixes_sums[500];
ull k = 0;

static inline void init(vector<ull>& as) {
  ull n = as.size();

  map<ull, vector<ull>> counts;

  fore(i, 0, n) {
    if (as[i] <= n) {
      counts[as[i]].push_back(i);
    }
  }

  for (auto [a, is] : counts) {
    if (a <= is.size()) {
      vector<ull> pss(n + 1);

      ull j = 1;
      for (ull i : is) {
        /* fore(k, j, i + 1) {
          pss[k] = pss[k - 1];
        } */
        fill(pss.begin() + j, pss.begin() + i + 1, pss[j - 1]);

        pss[i + 1] = pss[i] + 1;
        j = i + 2;
      }

      /* fore(k, j, n + 1) {
        pss[k] = pss[k - 1];
      } */
      fill(pss.begin() + j, pss.begin() + n + 1, pss[j - 1]);

      prfixes_sums[k] = {a, pss};
      k++;
    }
  }
}

static inline ull query(ull l, ull r) {
  ull ans = 0;
  fore(j, 0, k) {
    auto &[a, pss] = prfixes_sums[j];
    if (pss[r] - pss[l - 1] == a) {
      ans++;
    }
  }

  return ans;
}

int main(void) {
  FIN;

  ull n, m;
  cin >> n >> m;

  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  init(as);

  fore(_, 0, m) {
    ull l, r;
    cin >> l >> r;
    cout << query(l, r) << '\n';
  }

  return 0;
}