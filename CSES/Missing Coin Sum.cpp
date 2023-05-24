// https://cses.fi/problemset/task/2183

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(vector<ull> xs) {
  sort(xs.begin(), xs.end());

  ull ans = 1;

  for (ull x : xs) {
    if (x > ans) {
      return ans;
    }

    ans += x;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<ull> xs(n);

  fore(i, 0, n) {
    cin >> xs[i];
  }

  cout << solve(xs) << '\n';

  return EXIT_SUCCESS;
}
