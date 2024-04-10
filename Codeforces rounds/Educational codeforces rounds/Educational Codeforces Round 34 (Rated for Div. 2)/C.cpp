// https://codeforces.com/contest/903/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

ull solve(const vu& as) {
  map<ull, ull> cnt;

  for (ull a : as) {
    cnt[a]++;
  }

  ull ans = 0;
  for (auto [_, c] : cnt) {
    ans = max(ans, c);
  }

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

  return EXIT_SUCCESS;
}
