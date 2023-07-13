// https://codeforces.com/contest/1783/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<vector<ull>, ull> parse1(void) {
  ull n, m;

  cin >> n >> m;
  vector<ull> as(n);

  fore(i, 0, n) {
    cin >> as[i];
  }

  return {as, m};
}

ull solve1(vector<ull> as, ull m) {
  ull n = as.size();

  vector<pair<ull, ull>> as_i(n);
  fore(i, 0, n) {
    as_i[i] = {as[i], i};
  }

  sort(as_i.begin(), as_i.end());

  ull sum = 0;
  ull count = 0;
  for (auto [a, i] : as_i) {
    sum += a;
    if (sum > m) {
      sum -= a;
      break;
    }
    count++;
  }

  if (count == 0) {
    return n + 1;
  }

  if (count == n) {
    return 1;
  }

  ull j = 0;
  for (; j < count; j++) {
    auto [a, i] = as_i[j];
    if (i == count) {
      return n - count;
    }
  }

  if (sum + as[count] - as_i[j - 1].first <= m) {
    return n - count;
  }

  return n - count + 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [as, m] = parse1();
    cout << solve1(as, m) << "\n";
  }

  return EXIT_SUCCESS;
}
