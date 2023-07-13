// https://codeforces.com/contest/1832/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, vector<ull>> parse1(void) {
  ull n, k;
  cin >> n >> k;
  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  return {k, as};
}

ull solve1(ull k, vector<ull> as) {
  ull n = as.size();

  sort(as.begin(), as.end());

  ull sum = 0;
  fore(i, 2 * k, n) {
    sum += as[i];
  }

  ull max_sum = sum;

  fore(i, 1, k + 1) {
    ull k_front = k - i;
    ull k_back = i;

    sum -= as[n - k_back];
    sum += (as[2 * k_front] + as[2 * k_front + 1]);

    max_sum = max(max_sum, sum);
  }

  return max_sum;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [k, as] = parse1();
    auto ans = solve1(k, as);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
