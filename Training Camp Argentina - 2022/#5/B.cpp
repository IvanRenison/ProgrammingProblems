// https://codeforces.com/group/4zVk9dZl6Q/contest/391178/problem/B
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// dirs
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

struct Matrix {
  ull W, H;
  vector<vector<vector<bool>>> edges;

  Matrix(ull W, ull H)
      : W(W), H(H), edges(W, vector<vector<bool>>(H, vector<bool>(4, true))) {}

  void sep(ull x0, ull y0, ull dir) {
    if (dir == RIGHT) {
      edges[x0][y0][RIGHT] = false;
      if (x0 + 1 < W) {
        edges[x0 + 1][y0][LEFT] = false;
      }
    } else if (dir == UP) {
      edges[x0][y0][UP] = false;
      if (y0 + 1 < H) {
        edges[x0][y0 + 1][DOWN] = false;
      }
    }
  }

  void cut(ull x0, ull y0, ull x1, ull y1) {
    if (x0 == x1) {
      fore(y, y0, y1) {
        sep(x0 - 1, y, RIGHT);
      }
    } else {
      fore(x, x0, x1) {
        sep(x, y0 - 1, UP);
      }
    }
  }

  vector<pair<ull, ull>> vecinos(ull x, ull y) const {
    vector<pair<ull, ull>> ans;
    if (x > 0 && edges[x][y][LEFT]) {
      ans.push_back({x - 1, y});
    }
    if (y > 0 && edges[x][y][DOWN]) {
      ans.push_back({x, y - 1});
    }
    if (x + 1 < W && edges[x][y][RIGHT]) {
      ans.push_back({x + 1, y});
    }
    if (y + 1 < H && edges[x][y][UP]) {
      ans.push_back({x, y + 1});
    }
    return ans;
  }
};

vector<ull> solve(ull W, ull H, vector<tuple<ull, ull, ull, ull>> xyxys) {
  Matrix m(W, H);

  for (auto [x0, y0, x1, y1] : xyxys) {
    m.cut(x0, y0, x1, y1);
  }

  vector<ull> ans;
  vector<vector<bool>> visited(W, vector<bool>(H, false));
  fore(x, 0, W) {
    fore(y, 0, H) {
      if (!visited[x][y]) {
        ull count = 1;
        vector<pair<ull, ull>> s = {{x, y}};
        visited[x][y] = true;
        while (!s.empty()) {
          auto [x0, y0] = s.back();
          s.pop_back();

          for (auto [x1, y1] : m.vecinos(x0, y0)) {
            if (!visited[x1][y1]) {
              s.push_back({x1, y1});
              visited[x1][y1] = true;
              count++;
            }
          }
        }

        ans.push_back(count);
      }
    }
  }

  sort(ALL(ans));
  return ans;
}

int main() {
  FIN;

  ull W, H, n;
  cin >> W >> H >> n;
  vector<tuple<ull, ull, ull, ull>> xyxys(n);
  fore(i, 0, n) {
    ull x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    xyxys[i] = {x0, y0, x1, y1};
  }

  vector<ull> ans = solve(W, H, xyxys);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return 0;
}