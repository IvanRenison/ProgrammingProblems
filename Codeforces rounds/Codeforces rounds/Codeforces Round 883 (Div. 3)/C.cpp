// https://codeforces.com/contest/1846/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull k, vector<vector<ull>>& tss) {
  ull n = tss.size();
  vector<tuple<ull, ll, ll>> point_penalty_i(n);

  fore(i, 0, n) {
    sort(tss[i].begin(), tss[i].end());
    ull points = 0;
    ll penalty = 0, time = 0;
    for (ull t : tss[i]) {
      if (time + t > k) {
        break;
      }
      time += t, penalty += time, points++;
    }
    point_penalty_i[i] = {points, -penalty, -i};
  }

  sort(point_penalty_i.begin(), point_penalty_i.end());

  for (ull i = n - 1; i < n; i--) {
    auto [points, penalty, j] = point_penalty_i[i];
    if (j == 0) {
      return n - i - 1;
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vector<vector<ull>> tss(n, vector<ull>(m));
    fore(i, 0, n) {
      fore(j, 0, m) {
        cin >> tss[i][j];
      }
    }

    auto ans = solve1(k, tss);
    cout << ans + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
