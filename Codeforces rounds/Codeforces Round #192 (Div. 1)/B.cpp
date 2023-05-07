// https://codeforces.com/contest/329/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define TREE 'T'
#define START 'S'
#define EXIT 'E'

char grid[1000][1000];
bool visited[1000][1000];

pair<ull, ull> find_door(ull c, ull r) {
  fore(i, 0, c) {
    fore(j, 0, r) {
      if (grid[i][j] == 'E') {
        return make_pair(i, j);
      }
    }
  }
}

vector<pair<ull, ull>> neighbors(ull c, ull r, ull x, ull y) {
  vector<pair<ull, ull>> ans;
  if (x > 0 && !visited[x - 1][y] && grid[x - 1][y] != 'T') {
    ans.push_back({x - 1, y});
  }
  if (y > 0 && !visited[x][y - 1] && grid[x][y - 1] != 'T') {
    ans.push_back({x, y - 1});
  }
  if (x + 1 < c && !visited[x + 1][y] && grid[x + 1][y] != 'T') {
    ans.push_back({x + 1, y});
  }
  if (y + 1 < r && !visited[x][y + 1] && grid[x][y + 1] != 'T') {
    ans.push_back({x, y + 1});
  }
  return ans;
}

ull solve(ull c, ull r) {
  auto [door_x, door_y] = find_door(c, r);
  visited[door_x][door_y] = true;

  // Count the amount of monster with distance to the door lees or equal than the start
  vector<pair<ull, ull>> next_level = neighbors(c, r, door_x, door_y);
  for (auto [x, y] : next_level) {
    visited[x][y] = true;
  }

  ull ans = 0;

  bool found_start = false;
  while (!found_start) {
    vector<pair<ull, ull>> this_level = next_level;
    next_level = {};

    for (auto [x, y] : this_level) {
      if (grid[x][y] == START) {
        found_start = true;
      } else { // In this case it has to be a digit
        ans += grid[x][y] - '0';

        vector<pair<ull, ull>> neighs = neighbors(c, r, x, y);
        for (auto [x1, y1] : neighs) {
          next_level.push_back({x1, y1});
          visited[x1][y1] = true;
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull c, r;
  cin >> r >> c;

  fore(j, 0, r) {
    fore(i, 0, c) {
      cin >> grid[i][j];
    }
  }

  cout << solve(c, r) << "\n";

  return EXIT_SUCCESS;
}
