// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, ull>
sumDist_count(const vector<vector<ull>>& adg, ull v, ull parent) {
  ull ans = 0, count = 1, n = adg.size();

  for (ull u : adg[v]) {
    if (u != parent) {
      auto [ans_u, count_u] = sumDist_count(adg, u, v);
      ans += ans_u + count_u * (n - count_u);
      count += count_u;
    }
  }

  return {ans, count};
}

array<ull, 2> amount_per_level(
    const vector<vector<ull>>& adg, ull v, ull parent, bool initial_level
) {
  array<ull, 2> ans = {0, 0};

  ans[initial_level]++;

  for (ull u : adg[v]) {
    if (u != parent) {
      array<ull, 2> ans_u = amount_per_level(adg, u, v, !initial_level);

      ans[0] += ans_u[0];
      ans[1] += ans_u[1];
    }
  }

  return ans;
}

ull solve(vector<vector<ull>>& adg) {
  ull n = adg.size();

  auto [sumDist, _] = sumDist_count(adg, 0, n + 1);

  array<ull, 2> amountLevel = amount_per_level(adg, 0, n + 1, 0);

  return (sumDist + amountLevel[0] * amountLevel[1]) / 2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<vector<ull>> adg(n);
  fore(i, 0, n - 1) {
    ull u, v;
    cin >> u >> v;
    adg[v - 1].push_back(u - 1);
    adg[u - 1].push_back(v - 1);
  }

  cout << solve(adg);

  return EXIT_SUCCESS;
}
