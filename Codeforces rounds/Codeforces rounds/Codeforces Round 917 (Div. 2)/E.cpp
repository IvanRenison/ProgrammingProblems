// https://codeforces.com/contest/1917/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;


optional<vector<vb>> solve(ull n, ull k) {

  if (k % 2 != 0) {
    return {};
  }

  vector<vb> ans(n, vb(n, false));

  if (n == 2 && k == 2) {
    ans[0][0] = ans[0][1] = true;
    return ans;
  }

  if (k == 2 || k == n*n - 2) {
    return {};
  }

  ull klim = k % 4 == 2 ? 6 : 0;
  ull last2jlim = k % 4 == 2 ? n/2 - 2 : n/2;

  for (ull i = 0; i < n/2 && k > klim; i++) {
    for (ull j = 0; j < (i < n/2 - 2 ? n/2 : last2jlim) && k > klim; j++) {

      ull x = 2 * i, y = 2 * j;

      ans[x][y] = ans[x + 1][y] = ans[x][y + 1] = ans[x + 1][y + 1] = true;
      k -= 4;

      /* cerr << "----------\n";
      for (auto& row : ans) {
        for (bool col : row) {
          cerr << (col ? "1 " : "0 ");
        }
        cerr << '\n';
      } */
    }
  }

  if (k == 6) {
    ans[n - 3][n - 2] = ans[n - 3][n - 1] = ans[n - 2][n - 3]
      = ans[n - 2][n - 1] = ans[n - 1][n - 3] = ans[n - 1][n - 2] = true;
  } else if (k == 10) {
    fore(x, n - 4, n) {
      fore(y, n - 4, n) {
        ans[x][y] = true;
      }
    }
    ans[n - 3][n - 2] = ans[n - 3][n - 1] = ans[n - 2][n - 3]
      = ans[n - 2][n - 1] = ans[n - 1][n - 3] = ans[n - 1][n - 2] = false;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  while (t--) {
    ull n, k;
    cin >> n >> k;

    auto ans = solve(n, k);

    if (ans.has_value()) {
      cout << "Yes\n";
      for (auto& row : *ans) {
        for (bool col : row) {
          cout << (col ? "1 " : "0 ");
        }
        cout << '\n';
      }
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
