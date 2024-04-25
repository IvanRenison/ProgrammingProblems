// https://cses.fi/problemset/task/1629

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(vector<pair<uint, uint>>& times) {
  uint n = times.size();

  sort(times.begin(), times.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
  });

  uint ans = 1, t = times[0].second;

  fore(i, 1, n) {
    if (times[i].first >= t) {
      ans++;
      t = times[i].second;
    }
  }


  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;
  vector<pair<uint, uint>> times(n);
  for (auto& [a, b] : times) {
    cin >> a >> b;
  }


  uint ans = solve(times);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
