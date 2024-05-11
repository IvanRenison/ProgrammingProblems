// https://codeforces.com/group/4zVk9dZl6Q/contest/390678/problem/B
#include "bits/stdc++.h"
#define fst first
#define snd second
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

vector<ull> topoSort(const vector<vector<ull>>& gr) {
  vector<ull> indeg(gr.size()), ret;
  for (auto& li : gr)
    for (ull x : li)
      indeg[x]++;
  queue<int> q; // use priority_queue for lexic. largest ans.
  fore(i, 0, gr.size()) if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    int i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (int x : gr[i])
      if (--indeg[x] == 0)
        q.push(x);
  }
  return ret;
}

ull solve(vector<vector<ull>> perms) {
  ull n = perms[0].size(), k = perms.size();

  vector<vector<ull>> inv_perms(k, vector<ull>(n));
  fore(p, 0, k) {
    fore(i, 0, n) {
      inv_perms[p][perms[p][i]] = i;
    }
  }

  vector<vector<ull>> adg_forward(n);
  vector<vector<ull>> adg_backward(n);

  fore(i, 0, n) {
    fore(j, 0, n) {
      if (i != j) {
        bool valid = true;
        fore(p, 0, k) {
          if (inv_perms[p][i] > inv_perms[p][j]) {
            valid = false;
            break;
          }
        }
        if (valid) {
          adg_forward[i].push_back(j);
          adg_backward[j].push_back(i);
        }
      }
    }
  }

  vector<ull> order = topoSort(adg_forward);

  ull ans = 0;
  vector<ull> dp(n);
  for (ull j : order) {
    dp[j] = 1;
    for (ull i : adg_backward[j]) {
      dp[j] = max(dp[j], dp[i] + 1);
    }
    ans = max(ans, dp[j]);
  }

  return ans;
}

int main() {
  FIN;
  int n, k;
  cin >> n >> k;
  vector<vector<ull>> perms(k, vector<ull>(n));
  fore(i, 0, k) {
    fore(j, 0, n) {
      cin >> perms[i][j];
      perms[i][j]--;
    }
  }

  cout << solve(perms) << '\n';

  return 0;
}
