// https://codeforces.com/contest/1890/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;


vu solve(vector<vu>& css) {
  ull n = css.size();

  vb vis(n, false), search(n, false);

  fore(i, 0, n) {
    if (!vis[i]) {
      fill(all(search), false);
      ull j = i;
      bool searching = true;
      while (true) {
        if (searching) {
          if (search[j]) {
            searching = false;
            continue;
          }
          if (vis[j]) {
            break;
          }
          vis[j] = search[j] = true;
          if (css[j].size() == 0) {
            break;
          }
          j = css[j].back();
        } else {
          if (!search[j]) {
            searching = true;
            continue;
          }

          assert(css[j].size() > 0);

          ull j_ = css[j].back();
          css[j].pop_back();
          vis[j] = search[j] = false;
          j = j_;
        }
      }
    }
  }

  vu dp(n, inf);
  function<ull(ull)> init = [&](ull u) {
    ull& ans = dp[u];
    if (ans != inf) {
      return ans;
    }

    if (css[u].size() == 0) {
      ans = u;
    } else {
      ans = init(css[u].back());
    }

    return ans;
  };

  vu ans(n);

  fore(i, 0, n) {
    ans[i] = init(i);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<vu> css(n);
  for (vu& cs : css) {
    ull k;
    cin >> k;
    cs = vu(k);
    for (ull& c : cs) {
      cin >> c;
      c--;
    }
  }

  auto ans = solve(css);
  for (ull a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
