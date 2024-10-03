// https://codeforces.com/gym/104114/problem/I

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
ull solve(vu& as) {
  ull n = as.size();

  vuu ais(n);
  fore(i, 0, n) {
    ais[i] = {as[i], i};
  }
  sort(ALL(ais), greater<uu>());

  ull ans = 0;

  ull sum = 0;
  set<uu> ints; // [)

  auto add = [&](ull i) {
    if (ints.empty()) {
      ints.insert({i, i + 1});
      sum++;
    } else {
      auto it = ints.lower_bound({i, 0});
      if (it != ints.end() && it->first == i + 1) {
        ull j = it->second;
        ints.erase(it);
        it = ints.insert({i, j}).first;
        sum -= (j - (i + 1) + 1) / 2;
        sum += (j - i + 1) / 2;
      } else {
        it = ints.insert({i, i + 1}).first;
        sum++;
      }

      if (it != ints.begin()) {
        auto itp = prev(it);
        if (itp->second == i) {
          ull j = it->second;
          auto [ip, jp] = *itp;
          ints.erase(it), ints.erase(itp);
          ints.insert({ip, j});
          sum -= (j - i + 1) / 2;
          sum -= (jp - ip + 1) / 2;
          sum += (j - ip + 1) / 2;
        }
      }
    }
  };

  add(ais[0].second);
  fore(j, 1, n) {
    auto [a, i] = ais[j];
    auto [ap, ip] = ais[j - 1];
    ans += sum * (ap - a);
    add(i);
  }
  ans += sum * ais.back().first;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  ull ans = solve(as);
  cout << ans << '\n';
}
