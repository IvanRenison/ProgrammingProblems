// https://codeforces.com/gym/102916/problem/K

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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

/* bool force(ull m, ull l, const vuu& ths) {
  if (l == 0) {
    return false;
  } else if (ths.empty()) {
    return true;
  }
  ull n = ths.size();
  fore(i, 0, n) {
    auto [t, h] = ths[i];
    ull l_ = l - 1;
    vuu ths_;
    if (t == 1) {
      fore(j, 0, n) if (i != j) {
        ths_.push_back(ths[j]);
      }
      l_ = min(l_ + h, m);
    } else {
      ths_ = ths;
      ths_[i].first--;
    }
    if (force(m, l_, ths_)) {
      return true;
    }
  }

  return false;
}
 */
bool solve1(ull m, const vuu& ths) {
  vuu t_less, t_more;
  for (auto [t, h] : ths) {
    if (t < h) {
      t_less.push_back({t, h});
    } else {
      t_more.push_back({t, h});
    }
  }

  sort(ALL(t_less));

  vu ones;

  ull l = m;

  for (auto [t, h] : t_less) {
    while (l < t) {
      if (ones.empty()) {
        return false;
      }
      t -= l - 1;
      l = min(m, ones.back());
      ones.pop_back();
    }
    ones.push_back(h);
    l -= t - 1;
  }

  sort(ALL(t_more), [&](uu th0, uu th1) {
    auto [t0, h0] = th0;
    auto [t1, h1] = th1;
    return h0 > h1;
  });

  for (auto [t, h] : t_more) {
    while (l < t) {
      if (ones.empty()) {
        return false;
      }
      t -= l - 1;
      l = min(m, ones.back());
      ones.pop_back();
    }
    ones.push_back(h);
    l -= t - 1;
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vuu ths(n);
    for (auto& [t, h] : ths) {
      cin >> t >> h;
    }

      bool ans = solve1(m, ths);
      if (ans) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
  }

/*   fore(_, 0, 1000) {
    ull n = rand() % 5 + 1, m = rand() % 5 + 2;
    vuu ths(n);
    for (auto& [t, h] : ths) {
      t = rand() % 5 + 1, h = rand() % 5 + 1;
    }

    bool ans = solve1(m, ths);
    bool ans2 = force(m, m, ths);
    if (ans != ans2) {
      cerr << "ERROR:\n";
      cerr << n << ' ' << m << '\n';
      for (auto [t, h] : ths) {
        cerr << t << ' ' << h << '\n';
      }
      cerr << "ans: " << ans << '\n';
      cerr << "ans2: " << ans2 << endl;
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
