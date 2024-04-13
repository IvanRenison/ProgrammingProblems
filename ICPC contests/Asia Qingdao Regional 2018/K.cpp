// https://codeforces.com/gym/104270/problem/K

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const int inf = 1 << 30;

vu count_left_side(const vector<vi>& x_to_y) {
  int x_lim = x_to_y.size();

  assert(x_to_y[0].empty());
  assert(x_to_y.back().empty());

  vu ans(x_lim);

  set<int> dists;

  fore(x, 0, x_lim) {
    ans[x] = dists.size();

    map<int, uint> ds;

    for (int y : x_to_y[x]) {
      ds[-x + abs(y)]++;
    }

    for (auto [d, count] : ds) {
      if (dists.count(d)) {
        dists.erase(d);
      } else {
        if (count == 1) {
          dists.insert(d);
        }
      }
    }
  }

  return ans;
}

uu solve1(int y0, vii& xys) {
  sort(ALL(xys));

  int x0 = xys[0].first - 1;
  int max_x = xys.back().first;

  int x_lim = max_x - x0 + 1;

  vector<vi> x_to_y(x_lim + 1);

  for (auto& [x, y] : xys) {
    y -= y0;
    y = abs(y);
    x -= x0;
    x_to_y[x].push_back(y);
  }

  vu left_side = count_left_side(x_to_y);
  reverse(ALL(x_to_y));
  vu right_side = count_left_side(x_to_y);
  reverse(ALL(right_side));
  reverse(ALL(x_to_y));


  uint ans_m = inf, ans_M = 0;

  fore(x, 0, x_lim + 1) {
    uint this_ans = left_side[x] + right_side[x] + x_to_y[x].size();

    ans_m = min(ans_m, this_ans), ans_M = max(ans_M, this_ans);
  }

  return {ans_m, ans_M};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  fore(i, 0, t) {
    uint n;
    int y0;
    cin >> n >> y0;
    vii xys(n);
    for (auto& [x, y] : xys) {
      cin >> x >> y;
    }

    auto [m, M] = solve1(y0, xys);
    cout << m << ' ' << M << '\n';
  }

  return EXIT_SUCCESS;
}
