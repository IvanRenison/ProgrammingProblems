// https://codeforces.com/gym/104252/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool neighbour[100][100];

static inline ull solve(ull R, ull C, map<ull, pair<ull, ull>> positions) {
  ull total_max = 0;

  fore (start, 0, R*C) {
    fore (x, 0, R) {
      fore (y, 0, C) {
        neighbour[x][y] = false;
      }
    }

    ull this_ans = 0;

    {
      auto [x, y] = positions[start];
      neighbour[x][y] = true;
    }

    fore (k, start, R*C) {
      auto [x, y] = positions[k];
      if (!neighbour[x][y]) {
        continue;
      }

      this_ans++;

      if (x > 0) {
        neighbour[x - 1][y] = true;
      }
      if (x < R - 1) {
        neighbour[x + 1][y] = true;
      }
      if (y > 0) {
        neighbour[x][y - 1] = true;
      }
      if (y < C - 1) {
        neighbour[x][y + 1] = true;
      }
    }

    total_max = max(total_max, this_ans);
  }

  return total_max;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull R, C;
  cin >> R >> C;

  map<ull, pair<ull, ull>> positions;
  fore(i, 0, R) {
    fore(j, 0, C) {
      ull x;
      cin >> x;
      positions[x - 1] = {i, j};
    }
  }

  cout << solve(R, C, positions) << endl;

  return EXIT_SUCCESS;
}
