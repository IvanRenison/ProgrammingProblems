// https://codeforces.com/contest/1844/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull parse1(void) {
  ull n;
  cin >> n;
  return n;
}

string solve1(ull n) {

  vector<ull> divs_n;
  fore(i, 1, n) {
    if (n % i == 0) {
      divs_n.push_back(i);
    }
  }

  vector<ull> ans(n);

  ull max_used = 0;
  ull i = 1;
  for (; i < n; i++) {
    set<ull> used;
    for (ull d : divs_n) {
      if (d > i) {
        break;
      }
      used.insert(ans[i - d]);
    }

    ull min_not_used;
    for (min_not_used = 0; used.find(min_not_used) != used.end();
         min_not_used++)
      ;

    if (min_not_used == 0) {
      break;
    }

    max_used = max(max_used, min_not_used);

    ans[i] = min_not_used;
  }

  for (; i < n; i++) {
    ans[i] = ans[i % (max_used + 1)];
  }

  string cans;
  ull max_a = 0;
  for (ull a : ans) {
    cans.push_back('a' + a);
    max_a = max(max_a, a);
  }

  //cout << max_a + 1 << ": ";

  return cans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
