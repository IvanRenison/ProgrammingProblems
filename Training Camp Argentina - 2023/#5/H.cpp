// https://codeforces.com/group/hzSLIARNBN/contest/466528/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ull count_cc(const vector<vu>& adj) {
  ull n = adj.size();
  vector<bool> visited(n, false);
  ull cc = 0;

  fore(i, 0, n) {
    if (!visited[i]) {
      cc++;

      vu s = {i};
      visited[i] = true;
      while (!s.empty()) {
        ull u = s.back();
        s.pop_back();

        for (auto v : adj[u]) {
          if (!visited[v]) {
            visited[v] = true;
            s.push_back(v);
          }
        }
      }
    }
  }

  return cc;
}

ull solve(ull n, ull m) {
  if (m > n) {
    swap(n, m);
  }

  n = m + (n - m) % (m - 1);

  vector<vu> adj(2*n + 2*m);

  fore(i, 0, n - m + 1) {
    adj[i].push_back(n + i + m - 1), adj[n + i + m - 1].push_back(i);
  }
  fore(i, n - m, n) {
    adj[i].push_back(2*n + m + n - i - 1), adj[2*n + m + n - i - 1].push_back(i);
  }

  fore(i, 0, m) {
    adj[i].push_back(2*n + i), adj[2*n + i].push_back(i);
  }
  fore(i, m - 1, n) {
    adj[i].push_back(n + i + 1 - m), adj[n + i + 1 - m].push_back(i);
  }

  fore(j, 0, m) {
    adj[2*n + j].push_back(n + m - j - 1), adj[n + m - j - 1].push_back(2*n + j);
  }

  fore(j, 0, m) {
    adj[2*n + m + j].push_back(2*n - m + j), adj[2*n - m + j].push_back(2*n + m + j);
  }

  ull ans = count_cc(adj);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;

  auto ans = solve(n, m);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
