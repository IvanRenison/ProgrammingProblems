// https://codeforces.com/group/4zVk9dZl6Q/contest/390414/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;

#define fore(i, a, b) for (ull i = a; i < b; i++)

const ull inf = 1ull << 60;

ull solve(ull n, ull k, const vuuu& edges) {

  vector<vuu> adj_back(n), adj_ford(n);
  for (auto [u, v, c] : edges) {
    if (u < v) {
      adj_ford[u].push_back({v, c});
    } else if (v < u) {
      adj_back[u].push_back({v, c});
    }
  }

  vector<vector<vu>> dp(k + 1, vector<vu>(n, vu(n, inf)));
  // dp[x][u][v]

  dp[1] = vector<vu>(n, vu(n, 0));

  fore(x, 2, k + 1) {
    fore(u, 0, n) {
      fore(v, 0, u) {
        for (auto [w, c] : adj_back[u]) if (w >= v) {
          dp[x][u][v] = min(dp[x][u][v], dp[x - 1][w][v] + c);
          dp[x][u][v] = min(dp[x][u][v], dp[x - 1][w][u - 1] + c);
        }
      }

      fore(v, u + 1, n) {
        for (auto [w, c] : adj_ford[u]) if (w <= v) {
          dp[x][u][v] = min(dp[x][u][v], dp[x - 1][w][v] + c);
          dp[x][u][v] = min(dp[x][u][v], dp[x - 1][w][u + 1] + c);
        }
      }
    }
  }

  ull ans = inf;
  fore(u, 0, n) {
    fore(v, 0, n) {
      ans = min(ans, dp[k][u][v]);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, k, m;
  cin >> n >> k >> m;
  vuuu edges(m);
  for (auto& [u, v, c] : edges) {
    cin >> u >> v >> c;
    u--, v--;
  }

  ull ans = solve(n, k, edges);
  if (ans != inf) {
    cout << ans << '\n';
  } else {
    cout << "-1\n";
  }

  return EXIT_SUCCESS;
}
