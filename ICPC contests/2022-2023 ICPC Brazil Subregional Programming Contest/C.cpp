// https://codeforces.com/gym/103960/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

// 0: left, 1: up, 2: right, 3: down
bool not_graph_connections[1001][1001][4];

bool visited[1001][1001];

ull dfs(ull i, ull j) {
  ull ans = 0;
  vector<pair<ull, ull>> stack;
  stack.push_back({i, j});
  ans += 1;

  while (!stack.empty()) {
    auto [x, y] = stack.back();
    stack.pop_back();

    if (x > 0 && !not_graph_connections[x][y][0] && !visited[x - 1][y]) {
      stack.push_back({x - 1, y});
      ans += 1;
      visited[x - 1][y] = true;
    }
    if (y < 1000 && !not_graph_connections[x][y][1] && !visited[x][y + 1]) {
      stack.push_back({x, y + 1});
      ans += 1;
      visited[x][y + 1] = true;
    }
    if (x < 1000 && !not_graph_connections[x][y][2] && !visited[x + 1][y]) {
      stack.push_back({x + 1, y});
      ans += 1;
      visited[x + 1][y] = true;
    }
    if (y > 0 && !not_graph_connections[x][y][3] && !visited[x][y - 1]) {
      stack.push_back({x, y - 1});
      ans += 1;
      visited[x][y - 1] = true;
    }
  }

  return ans;
}

ull solve(vector<pair<ull, ull>> xys) {
  ull N = xys.size();

  fore(i, 1, N) {
    auto [old_x, old_y] = xys[i - 1];
    auto [new_x, new_y] = xys[i];

    if (old_x == new_x) {
      fore(y, min(old_y, new_y) + 1, max(old_y, new_y) + 1) {
        not_graph_connections[old_x][y][2] = true;
        not_graph_connections[old_x + 1][y][0] = true;
      }
    } else {
      fore(x, min(old_x, new_x) + 1, max(old_x, new_x) + 1) {
        not_graph_connections[x][old_y][1] = true;
        not_graph_connections[x][old_y + 1][3] = true;
      }
    }
  }

  dfs(0, 0);

  ull ans = 0;
  fore(i, 1, 1001) {
    fore(j, 1, 1001) {
      if (!visited[i][j]) {
        visited[i][j] = true;
        ull this_ans = dfs(i, j);
        ans = max(ans, this_ans);
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;

  cin >> N;

  vector<pair<ull, ull>> xys(N + 1);

  fore(i, 0, N + 1) {
    cin >> xys[i].first >> xys[i].second;
  }

  cout << solve(xys) << endl;

  return EXIT_SUCCESS;
}
