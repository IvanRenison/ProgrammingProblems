// https://codeforces.com/contest/1250/problem/M

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull maxn = 5000;

vector<vector<pair<vu, vu>>> dp(maxn + 1);

const vector<pair<vu, vu>>& solve(ull n) {
  if (n == 1) {
    return dp[n];
  }
  if (!dp[n].empty()) {
    return dp[n];
  }

  if (n == 2) {
    dp[n] = {{{0}, {1}}};
    return dp[n];
  }

  const vector<pair<vu, vu>>& rec4_ans = solve((n + 3) / 4);

  if (rec4_ans.size() + 8 < n) {
    vector<pair<vu, vu>>& ans = dp[n];

    for (const auto& [rows, cols] : rec4_ans) {
      ans.push_back({{}, {}});
      for (ull r : rows) {
        fore(d, 0, 4) {
          if (4 * r + d < n) {
            ans.back().first.push_back(4 * r + d);
          }
        }
      }
      for (ull c : cols) {
        fore(d, 0, 4) {
          if (4 * c + d < n) {
            ans.back().second.push_back(4 * c + d);
          }
        }
      }
    }

    ans.push_back({{0}, {}});
    for (ull r = 4; r < n; r += 5) {
      ans.back().first.push_back(r);
      if (r + 1 < n) {
        ans.back().first.push_back(r + 1);
      }
    }
    for (ull c = 1; c < n; c += 5) {
      ans.back().second.push_back(c);
      if (c + 1 < n) {
        ans.back().second.push_back(c + 1);
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 0; r < n; r += 5) {
      ans.back().first.push_back(r);
      if (r + 1 < n) {
        ans.back().first.push_back(r + 1);
      }
    }
    for (ull c = 2; c < n; c += 5) {
      ans.back().second.push_back(c);
      if (c + 1 < n) {
        ans.back().second.push_back(c + 1);
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 1; r < n; r += 5) {
      ans.back().first.push_back(r);
      if (r + 1 < n) {
        ans.back().first.push_back(r + 1);
      }
    }
    for (ull c = 3; c < n; c += 5) {
      ans.back().second.push_back(c);
      if (c + 1 < n) {
        ans.back().second.push_back(c + 1);
      }
    }

    ans.push_back({{}, {0}});
    for (ull r = 2; r < n; r += 5) {
      ans.back().first.push_back(r);
      if (r + 1 < n) {
        ans.back().first.push_back(r + 1);
      }
    }
    for (ull c = 4; c < n; c += 5) {
      ans.back().second.push_back(c);
      if (c + 1 < n) {
        ans.back().second.push_back(c + 1);
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 3; r < n; r += 5) {
      ans.back().first.push_back(r);
      if (r + 1 < n) {
        ans.back().first.push_back(r + 1);
      }
    }
    for (ull c = 0; c < n; c += 5) {
      ans.back().second.push_back(c);
      if (c + 1 < n) {
        ans.back().second.push_back(c + 1);
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 1; r < n; r += 8) {
      fore(d, 0, 3) {
        if (r + d < n) {
          ans.back().first.push_back(r + d);
        }
      }
    }
    for (ull c = 4; c < n; c += 8) {
      fore(d, 0, 3) {
        if (c + d < n) {
          ans.back().second.push_back(c + d);
        }
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 5; r < n; r += 8) {
      fore(d, 0, 3) {
        if (r + d < n) {
          ans.back().first.push_back(r + d);
        }
      }
    }
    for (ull c = 0; c < n; c += 8) {
      fore(d, 0, 3) {
        if (c + d < n) {
          ans.back().second.push_back(c + d);
        }
      }
    }

    return ans;
  }

  const vector<pair<vu, vu>>& rec2_ans = solve((n + 1) / 2);

  if (rec2_ans.size() + 5 < n) {

    vector<pair<vu, vu>>& ans = dp[n];

    for (const auto& [rows, cols] : rec2_ans) {
      ans.push_back({{}, {}});
      for (ull r : rows) {
        ans.back().first.push_back(2 * r);
        if (2 * r + 1 < n) {
          ans.back().first.push_back(2 * r + 1);
        }
      }
      for (ull c : cols) {
        ans.back().second.push_back(2 * c);
        if (2 * c + 1 < n) {
          ans.back().second.push_back(2 * c + 1);
        }
      }
    }

    ans.push_back({{}, {}});
    for (ull r = 0; r < n; r += 3) {
      ans.back().first.push_back(r);
    }
    for (ull c = 1; c < n; c += 3) {
      ans.back().second.push_back(c);
    }

    ans.push_back({{}, {}});
    for (ull r = 1; r < n; r += 3) {
      ans.back().first.push_back(r);
    }
    for (ull c = 2; c < n; c += 3) {
      ans.back().second.push_back(c);
    }

    ans.push_back({{}, {}});
    for (ull r = 2; r < n; r += 3) {
      ans.back().first.push_back(r);
    }
    for (ull c = 0; c < n; c += 3) {
      ans.back().second.push_back(c);
    }

    ans.push_back({{}, {}});
    for (ull r = 3; r < n; r += 4) {
      ans.back().first.push_back(r);
    }
    for (ull c = 0; c < n; c += 4) {
      ans.back().second.push_back(c);
    }

    ans.push_back({{}, {}});
    for (ull r = 1; r < n; r += 4) {
      ans.back().first.push_back(r);
    }
    for (ull c = 2; c < n; c += 4) {
      ans.back().second.push_back(c);
    }

    return ans;
  }


  vector<pair<vu, vu>>& ans = dp[n];
  ans.resize(n);

  fore(i, 0, n) {
    ans[i].first = {i};
    fore(j, 0, n) {
      if (j != i && j + 1 != i) {
        ans[i].second.push_back(j);
      }
    }
  }

  return ans;

}

string draw(ull n, const vector<pair<vu, vu>>& ans) {

  vector<vector<char>> paint(n, vector<char>(n, '#')); // Not watered
  fore(i, 0, n) {
    paint[i][i] = '@'; // Slabs
    if (i + 1 < n) {
      paint[i + 1][i] = '@'; // Slabs
    }
  }

  fore(i, 0, ans.size()) {
    const auto& [rows, cols] = ans[i];
    for (ull r : rows) {
      for (ull c : cols) {
        if (paint[r][c] == '#' || paint[r][c] == '@')
          paint[r][c] = 'a' + i;
      }
    }
  }

  string s;
  fore(i, 0, n) {
    fore(j, 0, n) {
      s += paint[i][j];
    }
    s += '\n';
  }

  return s;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  auto ans = solve(n);
  cout << ans.size() << '\n';
  for (const auto& [rows, cols] : ans) {
    cout << rows.size();
    for (ull x : rows) {
      cout << ' ' << x + 1;
    }
    cout << '\n';
    cout << cols.size();
    for (ull x : cols) {
      cout << ' ' << x + 1;
    }
    cout << '\n';

  }

  //cerr << draw(n, ans) << endl;

  return EXIT_SUCCESS;
}
