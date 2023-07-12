// https://codeforces.com/group/4zVk9dZl6Q/contest/391178/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

optional<vector<vector<char>>> solve(vector<vector<char>>& board) {
  ull n = board.size(), m = board[0].size();

  function<vector<pair<ull, ull>>(pair<ull, ull>)> neighbors =
      [&](pair<ull, ull> ij) {
        auto [i, j] = ij;
        vector<pair<ull, ull>> ans;
        if (i > 0) {
          ans.push_back({i - 1, j});
        }
        if (i + 1 < n) {
          ans.push_back({i + 1, j});
        }
        if (j > 0) {
          ans.push_back({i, j - 1});
        }
        if (j + 1 < m) {
          ans.push_back({i, j + 1});
        }
        return ans;
      };

  vector<vector<optional<ull>>> ans(n, vector<optional<ull>>(m));
  ull next = 0;

  vector<set<ull>> adj;

  fore(i, 0, n) {
    fore(j, 0, m) {
      if (ans[i][j].has_value()) {
        continue;
      }
      if (board[i][j] == 'b') {
        return {};
      }
      if (board[i][j] == 'w' && !ans[i][j].has_value()) {
        adj.push_back({});
        vector<pair<ull, ull>> neighbs;
        bool vertical =
            j + 1 == m || board[i][j + 1] == '.' || ans[i][j + 1].has_value();
        if (vertical) {
          if (i + 2 >= n || board[i + 1][j] == '.' ||
              ans[i + 1][j].has_value() || board[i + 2][j] == 'b' ||
              ans[i + 2][j].has_value()) {
            return {};
          }
          ans[i][j] = next;
          ans[i + 1][j] = next;
          ans[i + 2][j] = next;

          for (auto [ni, nj] : neighbors({i, j})) {
            neighbs.push_back({ni, nj});
          }
          for (auto [ni, nj] : neighbors({i + 1, j})) {
            neighbs.push_back({ni, nj});
          }
          for (auto [ni, nj] : neighbors({i + 2, j})) {
            neighbs.push_back({ni, nj});
          }

        } else {
          if (j + 2 >= m || board[i][j + 1] == '.' ||
              ans[i][j + 1].has_value() || board[i][j + 2] == 'b' ||
              ans[i][j + 2].has_value()) {
            return {};
          }
          ans[i][j] = next;
          ans[i][j + 1] = next;
          ans[i][j + 2] = next;

          for (auto [ni, nj] : neighbors({i, j})) {
            neighbs.push_back({ni, nj});
          }
          for (auto [ni, nj] : neighbors({i, j + 1})) {
            neighbs.push_back({ni, nj});
          }
          for (auto [ni, nj] : neighbors({i, j + 2})) {
            neighbs.push_back({ni, nj});
          }
        }
        for (auto [ni, nj] : neighbs) {
          if (ans[ni][nj].has_value() && *ans[ni][nj] != next) {
            adj[next].insert(*ans[ni][nj]);
            adj[*ans[ni][nj]].insert(next);
          }
        }
        next++;
      }
    }
  }

  vector<vector<char>> cans(n, vector<char>(m, '.'));
  vector<ull> color(next, ULLONG_MAX);
  fore(i, 0, n) {
    fore(j, 0, m) {
      if (ans[i][j].has_value() && cans[i][j] == '.') {
        if (color[*ans[i][j]] == ULLONG_MAX) {
          vector<bool> used(4, false);
          for (ull c : adj[*ans[i][j]]) {
            if (color[c] != ULLONG_MAX) {
              used[color[c]] = true;
            }
          }
          fore(k, 0, 4) {
            if (!used[k]) {
              cans[i][j] = 'a' + k;
              color[*ans[i][j]] = k;
              break;
            }
          }
        } else {
          cans[i][j] = 'a' + color[*ans[i][j]];
        }
      }
    }
  }

  return cans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  vector<vector<char>> board(n, vector<char>(m));
  fore(i, 0, n) {
    fore(j, 0, m) {
      cin >> board[i][j];
    }
  }

  auto ans = solve(board);
  if (ans.has_value()) {
    cout << "YES\n";
    fore(i, 0, n) {
      fore(j, 0, m) {
        cout << ans.value()[i][j];
      }
      cout << '\n';
    }
  } else {
    cout << "NO\n";
  }

  return EXIT_SUCCESS;
}
