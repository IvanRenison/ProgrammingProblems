// https://codeforces.com/group/4zVk9dZl6Q/contest/390672/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(ull k, vector<ull> as) {
  ull n = as.size();
  ull sum = 0;
  fore(i, 0, n) {
    sum += as[i];
  }

  ull count = 0;
  while (sum + n / 2 < n * k) {
    sum += k, n++, count++;
  }

  return count;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, k;
  cin >> n >> k;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  cout << solve(k, as) << '\n';

  return EXIT_SUCCESS;
}
