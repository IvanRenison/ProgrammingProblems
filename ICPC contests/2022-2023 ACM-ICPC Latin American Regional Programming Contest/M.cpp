// https://codeforces.com/gym/104252/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool nut[100];
bool mase[100][1000];

bool visited[100][1000];
static inline bool solve_side(ull R, ull C) {
  vector<ull> nuts;
  fore(i, 0, C) {
    if (nut[i]) {
      nuts.push_back(i);
    }
  }

  if (nuts.size() == 0) {
    return true;
  }

  // Do a kind of BFS/DFS

  vector<pair<ull, ull>> to_visit;

  ull first_nut = nuts[0];

  fore(x, 0, C) {
    if (mase[x][0]) {
      bool can = true;
      for (ull j = 1; j < nuts.size() && can; j++) {
        if (!mase[(x + nuts[j] - first_nut) % C][0]) {
          can = false;
        }
      }
      if (can) {
        to_visit.push_back({x, 0});
      }
    }
  }

  while (to_visit.size() > 0) {
    auto [x, y] = to_visit.back();
    to_visit.pop_back();

    visited[x][y] = true;

    if (y == R - 1) {
      return true;
    }

    vector<pair<ull, ull>> neighbors;
    neighbors.push_back({(x + 1) % C, y});
    neighbors.push_back({(x + C - 1) % C, y});
    neighbors.push_back({x, y + 1});
    if (y > 0) {
      neighbors.push_back({x, y - 1});
    }

    for (auto [nx, ny] : neighbors) {
      if (visited[nx][ny]) {
        continue;
      }
      bool can = true;
      for (ull j = 0; j < nuts.size() && can; j++) {
        if (!mase[(nx + nuts[j] - first_nut) % C][ny]) {
          can = false;
        }
      }
      if (can) {
        to_visit.push_back({nx, ny});
      }
    }
  }

  return false;
}

static inline bool solve(ull R, ull C) {
  if (solve_side(R, C)) {
    return true;
  }

  fore(i, 0, C / 2) {
    bool temp = nut[C - i - 1];
    nut[C - i - 1] = nut[i];
    nut[i] = temp;
  }

  fore(y, 0, R) {
    fore(x, 0, C) {
      visited[x][y] = false;
    }
  }

  return solve_side(R, C);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull R, C;
  cin >> R >> C;

  fore(x, 0, C) {
    char c;
    cin >> c;
    nut[x] = c == '1';
  }

  fore(y, 0, R) {
    fore(x, 0, C) {
      char c;
      cin >> c;
      mase[x][y] = c == '0';
    }
  }

  cout << (solve(R, C) ? "Y" : "N") << endl;

  return EXIT_SUCCESS;
}
