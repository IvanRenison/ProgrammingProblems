// https://codeforces.com/contest/1863/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

#define color(b) (b ? 'B' : 'W')

optional<vector<vector<char>>> solve1(const vector<vector<char>>& grid) {
  ull n = grid.size(), m = grid[0].size();

  vector<vector<char>> ans(n, vector<char>(m, '.'));

  ull count = 0;
  bool last = true;
  fore(i, 0, n-1) {
    fore(j, 0, m) {
      if (grid[i][j] == 'U') {
        count++;
        ans[i][j] = color(last);
        ans[i+1][j] = color(!last);
        last = !last;
      }
    }
    if (count % 2 == 1) {
      return {};
    }
  }

  fore(j, 0, m-1) {
    fore(i, 0, n) {
      if (grid[i][j] == 'L') {
        count++;
        ans[i][j] = color(last);
        ans[i][j+1] = color(!last);
        last = !last;
      }
    }
    if (count % 2 == 1) {
      return {};
    }
  }


  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    fore(j, 0, n) {
      fore(k, 0, m) {
        cin >> grid[j][k];
      }
    }

    auto ans = solve1(grid);
    if (ans.has_value()) {
      for (auto& s : ans.value()) {
        for (auto& c : s) {
          cout << c;
        }
        cout << '\n';
      }
    } else {
      cout << "-1\n";
    }
  }

  return EXIT_SUCCESS;
}
