// https://cses.fi/problemset/task/1640

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

optional<pair<uint, uint>> solve(uint x, const vu& as) {
  uint n = as.size();

  vector<pair<uint, uint>> ais(n);
  fore(i, 0, n) {
    ais[i] = {as[i], i};
  }

  sort(ais.begin(), ais.end());

  uint i = 0, j = n - 1;

  while (i < j) {
    if (ais[i].first + ais[j].first == x) {
      return {{ais[i].second, ais[j].second}};
    } else if (ais[i].first + ais[j].first < x) {
      i++;
    } else {
      j--;
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, x;
  cin >> n >> x;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }

  auto ans = solve(x, as);
  if (!ans.has_value()) {
    cout << "IMPOSSIBLE\n";
  } else {
    auto [i, j] = *ans;
    cout << i + 1 << ' ' << j + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
