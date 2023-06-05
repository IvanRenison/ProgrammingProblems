// https://codeforces.com/group/id8eYTCwzg/contest/445210/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull> solve(vector<ull> v_ds) {
  multiset<ull> ds(v_ds.begin(), v_ds.end());

  ull x = *ds.rbegin();

  for (ull i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      ds.erase(ds.find(i));
      if (i * i != x) {
        ds.erase(ds.find(x / i));
      }
    }
  }

  ull y = *ds.rbegin();

  return {x, y};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<ull> ds(n);
  fore(i, 0, n) {
    cin >> ds[i];
  }

  auto ans = solve(ds);
  cout << ans.first << " " << ans.second << "\n";

  return EXIT_SUCCESS;
}
